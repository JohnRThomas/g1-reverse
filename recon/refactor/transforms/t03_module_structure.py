"""Stage 03 -- production-grade module structure (app core).

Stages 01 and 02 were *mechanical*: they rewrote expressions and statements in
place and left the file layout exactly as they found it.  Stage 03 is the first
**structural** stage.  It changes where code lives and how it is declared.

R7 is what makes that safe.  The acceptance bar is observable side-effect
equivalence with the SHIPPED binaries, not per-function positional parity, so
the flat one-function-per-file address keying of ``recon/symbolized/`` carries
no evidentiary weight in the BUILD tree.  (It carries all of it in the
CANONICAL trees, which this pipeline may never write -- R1 -- and which are
untouched here.)  Grouping files into cohesive module directories, hoisting
declarations into real module headers and giving the build a directory
structure are therefore all permitted.

Scope decision, stated up front: **the app core only.**  The net core is frozen
at 225,581 B with ~1.7 kB of real headroom, is ~100 % stock (452/452 functions
are SDK-owned; ``net_function_ownership.json`` records zero product-owned net
functions needing readable C), and its CMakeLists carries a *path-keyed*
``list(FILTER G1_RETAINED_SOURCES EXCLUDE REGEX "/FUN_0102(a4c8|...)\\.c$")``
that a restructuring pass would have to reason about for no benefit.  There is
no module structure to recover on net.  It is left byte-for-byte alone, which
also means its image is byte-identical to stage 02's by construction.

--------------------------------------------------------------------------
SUB-BATCHES, ordered most-mechanical / least-risky first (README stage order)
--------------------------------------------------------------------------

A. **module directory materialisation** -- move each retained app source into
   ``recon/symbolized/app/<module path>/``, fix the relative ``#include``
   depth, and regenerate the two build artifacts that name sources by path:
   ``recon/generated/app_retained_sources.cmake`` (order preserved EXACTLY --
   see below) and the ``set_source_files_properties`` line in
   ``recon/application/app/CMakeLists.txt`` that gives ``discovery_callback.c``
   its ``-std=gnu99``.

   *Why the order matters and why this batch can be gated on a byte-identical
   image.*  The archive member order, and hence ``.text`` layout, follows the
   order of ``G1_RETAINED_SOURCES``.  Emitting the same list in the same order
   with only the directory component changed leaves link order untouched.
   Nothing else about a source's identity reaches the image: there is **no**
   ``__FILE__`` anywhere in ``recon/symbolized`` (measured: 0 files), and object
   paths live only in debug info, which ``zephyr.bin`` does not carry.  So
   sub-batch A predicts a **byte-identical** app image, and that prediction is
   the gate.

B. **module header materialisation** -- for each module, hoist into
   ``g1_<module>.h`` every ``extern`` declaration on whose **C TYPE** all of the
   module's files agree, and delete the per-file copies.  A symbol whose
   declarations disagree inside one module is NOT hoisted; it is quarantined and
   reported as a candidate latent defect, because a module that cannot agree
   with itself about a callee's type is telling us something.

   "Agree" is type identity, not text identity.  Exactly three differences are
   folded, each provable and each already used by stage 02 sub-batch A:
   whitespace; ``unsigned`` == ``unsigned int`` (C11 6.7.2); and parameter NAMES
   (C11 6.7.6.3 -- prototype identifiers have no linkage and leave scope at the
   end of the declarator).  ``int`` is never merged with ``unsigned int``,
   ``uint32_t`` is never resolved, and ``__attribute__((noreturn))`` keeps a
   declaration DISTINCT.

   Where the module also owns the symbol's DEFINITION, the definition is part of
   the agreement test.  That check exists because a module header puts callers
   and callee in one translation unit for the first time, so the compiler starts
   checking a pairing nothing had ever checked -- and under R4 a compile failure
   is a transformer bug, so the transformer has to make that check itself rather
   than discover it in a build log.

   This is the transformation that turns a directory of files into a module:
   one declaration site per symbol, in a header named after the module, instead
   of the same ``extern`` re-typed in forty files.

--------------------------------------------------------------------------
R8 -- which of this can reorder or coalesce a volatile MMIO access
--------------------------------------------------------------------------

Neither sub-batch touches a statement.  A never edits inside a function body at
all (only ``#include`` path depth, outside any function).  B moves *declarations*
between files; a declaration emits no instruction and cannot reorder an access.
The one thing B could in principle change is codegen where a hoisted
declaration denotes a different type from the local one it replaces -- so B
hoists ONLY on type identity across every occurrence in the module AND the
definition where the module owns one, which makes that case unrepresentable
rather than merely unlikely.

The residual R8 exposure of this stage is therefore **nil for A** and **nil for
B given the type-identity requirement**, and the byte-identical image measured
for A+B together is the empirical proof of both: a transformation that emits the
same instruction stream cannot have added, removed or reordered a bus
transaction.

Note for whoever writes the cohesive-TU merge next: it will be the FIRST
transformation in this pipeline that cannot make that claim, because merging N
files into one object changes archive member granularity and therefore section
layout.  It needs the behavioural oracle, not a ``cmp``.  And it is blocked
until the 1,014 declaration disagreements this stage catalogued are repaired in
the canonical trees -- concatenating those files today turns every one of them
into a simultaneous hard error.
"""

from __future__ import annotations

import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import sdk_symbols  # noqa: E402
import stagelib  # noqa: E402
from guard import REPO_ROOT, check_write  # noqa: E402

APP_SRC = "recon/symbolized/app/"
RETAINED_CMAKE = "recon/generated/app_retained_sources.cmake"
APP_CMAKELISTS = "recon/application/app/CMakeLists.txt"
MODULE_MAP = os.path.join(REPO_ROOT, "recon", "ownership", "refactor_module_map.json")

#: module -> directory under ``recon/symbolized/app/``.  Taken from
#: ``refactor_module_map.json``'s own ``directory_map`` with its ``app/src/``
#: prefix stripped, so the names are the plan's names and not invented ones.
#: ``needs_judgement`` deliberately keeps an explicit, ugly directory: it is a
#: quarantine, and a quarantine that looks like a real module is a lie.
FALLBACK_DIR = "unsorted"

#: files that must NOT move, with the measured reason.
_FROZEN_PREFIXES = (
    # rodata filenames are load-bearing: g1_verified_rodata_keep.ld matches
    # KEEP(*rodata_*.c.obj(".rodata.rodata_*")) on the OBJECT FILENAME.  A
    # directory move is absorbed by the leading `*`, but these files are not in
    # recon/symbolized/app anyway; listed for the record.
)

_INCLUDE_REL = re.compile(r'(#\s*include\s+")(\.\./\.\./)([^"]+)(")')
_EXTERN_DECL = re.compile(
    r'^[ \t]*extern[ \t][^;{}\n]*?\b(?P<name>[A-Za-z_][A-Za-z_0-9]*)[ \t]*'
    r'(?:\([^;{}]*\))?[ \t]*(?:__asm__[ \t]*\([^;]*\))?[ \t]*;[ \t]*$',
    re.M)


# ----------------------------------------------------------------- helpers
def _dir_map() -> dict[str, str]:
    with open(MODULE_MAP, encoding="utf-8") as fh:
        doc = json.load(fh)
    out = {}
    for module, path in doc["directory_map"].items():
        p = path
        for pref in ("app/src/", "net/src/"):
            if p.startswith(pref):
                p = p[len(pref):]
        out[module] = p
    # `directory_map` in refactor_module_map.json is INCOMPLETE: it has no
    # entry for `lib`, although `summary.app.module_sizes` reports lib = 482 --
    # by far the largest group.  Without this the 482 recovered-stock files
    # silently land in the quarantine directory, which would be a plain lie
    # about what they are.  The plan's target layout (§2 of
    # production_refactor_plan.md) does name `app/src/lib/`, so the value is
    # the plan's, not invented.
    out.setdefault("lib", "lib")
    out["needs_judgement"] = FALLBACK_DIR
    return out, doc


def _module_by_name() -> dict[str, str]:
    _, doc = _dir_map()
    out = {}
    for row in doc["app"]:
        if row.get("target_path") and row.get("module"):
            out[row["name"]] = row["module"]
    return out


def _fix_include_depth(text: str, extra_up: int) -> tuple[str, int]:
    """Rewrite ``#include "../../x"`` for a file that moved ``extra_up`` deeper."""
    if extra_up <= 0:
        return text, 0
    n = 0

    def sub(m):
        nonlocal n
        n += 1
        return m.group(1) + "../" * (2 + extra_up) + m.group(3) + m.group(4)

    return _INCLUDE_REL.sub(sub, text), n


# --------------------------------------------------------------- sub-batch A
def batch_a(relpaths, text, stats):
    """Decide the new path of every app source. Returns rel -> new_rel."""
    dirmap, _ = _dir_map()
    mod_by_name = _module_by_name()

    app_files = [r for r in relpaths
                 if r.startswith(APP_SRC) and r.count("/") == 3
                 and r.endswith((".c", ".inc", ".h"))]

    # 1. every .c gets its module from the map, or the quarantine directory
    module_of: dict[str, str] = {}
    unmapped: list[str] = []
    for r in app_files:
        base = os.path.basename(r)
        if base.endswith(".c"):
            m = mod_by_name.get(base[:-2])
            if m is None:
                unmapped.append(base)
                m = "needs_judgement"
            module_of[r] = m

    # 2. fragments (.inc/.h) follow the module of the file(s) that include
    #    them.  Measured: all 6 app fragments are reached from exactly one
    #    module, so this is a decision, not a heuristic.  A fragment reached
    #    from two modules would be ambiguous and is refused.
    frag_users: dict[str, set[str]] = {}
    for r in app_files:
        for m in re.finditer(r'#\s*include\s+"([^"/]+\.(?:inc|h))"', text[r]):
            tgt = APP_SRC + m.group(1)
            if tgt in text:
                frag_users.setdefault(tgt, set()).add(r)

    ambiguous_fragments = []
    # resolve iteratively: a fragment included only by other fragments inherits
    # from them once those are resolved.
    for _ in range(4):
        for frag, users in frag_users.items():
            if frag in module_of:
                continue
            mods = {module_of[u] for u in users if u in module_of}
            if len(mods) == 1:
                module_of[frag] = mods.pop()
    for frag, users in frag_users.items():
        if frag not in module_of:
            mods = sorted({module_of.get(u, "?") for u in users})
            ambiguous_fragments.append({"fragment": frag, "modules": mods})
            module_of[frag] = "needs_judgement"

    # 3. build the rename table
    moves: dict[str, str] = {}
    per_module: dict[str, int] = {}
    for r, m in sorted(module_of.items()):
        d = dirmap.get(m, FALLBACK_DIR)
        new = APP_SRC + d + "/" + os.path.basename(r)
        if new != r:
            moves[r] = new
        per_module[d] = per_module.get(d, 0) + 1

    # 4. include-depth fixups
    depth_fixed = 0
    files_depth_fixed = 0
    for r, new in moves.items():
        extra = new.count("/") - r.count("/")
        t, n = _fix_include_depth(text[r], extra)
        if n:
            text[r] = t
            depth_fixed += n
            files_depth_fixed += 1

    stats["A_module_layout"] = {
        "files_moved": len(moves),
        "modules": dict(sorted(per_module.items())),
        "unmapped_to_quarantine": sorted(unmapped),
        "unmapped_count": len(unmapped),
        "fragments_placed_with_their_includer": sorted(
            f for f in frag_users if f in moves),
        "ambiguous_fragments": ambiguous_fragments,
        "include_depth_rewrites": depth_fixed,
        "files_with_include_depth_rewrites": files_depth_fixed,
    }
    return moves


def rewrite_retained_cmake(text: str, moves: dict[str, str]) -> tuple[str, int]:
    """Rewrite the generated source list IN PLACE, preserving order exactly.

    Order preservation is not cosmetic: archive member order follows this list
    and determines ``.text`` layout.  A sorted or regrouped list would change
    the image without changing a single instruction, and would destroy the
    byte-identical gate this batch is built around.
    """
    n = 0

    def sub(m):
        nonlocal n
        rel = "recon/symbolized/" + m.group(2)
        if rel in moves:
            n += 1
            return m.group(1) + moves[rel][len("recon/symbolized/"):] + m.group(3)
        return m.group(0)

    out = re.sub(r'(\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./symbolized/)([^"\s)]+)()',
                 sub, text)
    return out, n


def rewrite_app_cmakelists(text: str, moves: dict[str, str]) -> tuple[str, int]:
    """Repoint every explicit ``symbolized/app/<file>`` path in the CMakeLists.

    The live file has exactly one: the ``set_source_files_properties`` giving
    ``discovery_callback.c`` ``-std=gnu99`` for its ``register ... asm("r9")``
    body.  CMake does NOT error when that path stops existing -- the property
    silently applies to nothing and the TU then fails under strict C99.  That
    is the single most dangerous silent coupling in a move batch.
    """
    n = 0

    def sub(m):
        nonlocal n
        rel = "recon/symbolized/" + m.group(2)
        if rel in moves:
            n += 1
            return m.group(1) + moves[rel][len("recon/symbolized/"):]
        return m.group(0)

    out = re.sub(r'(\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./\.\./symbolized/)([^"\s)]+)',
                 sub, text)
    return out, n


# --------------------------------------------------------------- sub-batch B
_DECL_LINE = re.compile(r'^[ \t]*extern[ \t].*;[ \t]*$', re.M)

#: a line tail that is nothing but whitespace and COMPLETE comments.  Used to
#: decide whether a declaration line may be withdrawn whole: a line whose tail
#: opens a comment it does not close cannot be, or the removal would leave the
#: next lines inside an unterminated comment.
_COMMENT_TAIL = re.compile(r'^[ \t]*(?:/\*(?:[^*]|\*(?!/))*\*/[ \t]*|//.*)*$')


def _blank_comments(text: str) -> str:
    """Length- and newline-preserving comment blanking.

    ``_DECL_LINE`` anchors the terminating ``;`` at end of line, so a
    declaration carrying a trailing comment is INVISIBLE to it::

        extern void memset_bytes(void *, int, size_t);   /* memset */

    That is not hypothetical.  At HEAD ``ff99f0c6`` the concurrent agent's
    canonicalisation left exactly that line in
    ``ui/navigation/ui_navigation_task.c`` while the rest of the module agreed
    on ``(void*,int,int)``.  Stage 03, unable to see it, judged the module
    unanimous, hoisted ``(void*,int,int)`` into ``g1_navigation.h`` -- and the
    build failed with ``conflicting types for 'memset_bytes'`` against the very
    declaration the scanner could not read.

    A declaration the safety rule cannot read is a declaration the safety rule
    cannot protect.  Blanking rather than deleting keeps every offset and line
    number aligned with the original text, so the two views can be zipped line
    for line at withdrawal time.
    """
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("".join("\n" if ch == "\n" else " " for ch in text[i:j]))
            i = j
            continue
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
            continue
        if c in "\"'":
            m = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'').match(text, i)
            if m:
                out.append(m.group(0))
                i = m.end()
                continue
        out.append(c)
        i += 1
    return "".join(out)
_DECL_NAME = re.compile(r'\b([A-Za-z_][A-Za-z_0-9]*)[ \t]*(?:\[[^\]]*\])?[ \t]*'
                        r'(?:\(|;|__asm__)')


def _strip_attributes(s: str) -> tuple[str, str]:
    """Remove ``__attribute__((...))`` groups, returning (attrs, rest).

    These MUST come out before anything looks for the declared identifier.
    ``extern __attribute__((noreturn)) void assert_post_action(uintptr_t, uint32_t);``
    otherwise parses its symbol as ``__attribute__`` -- it is the first
    identifier followed by ``(`` -- which files the declaration under the wrong
    name, hoists it under the wrong name, and then injects it into a file that
    still carries its own, differently-typed declaration of the real symbol.
    That is precisely the compile failure this function exists to prevent.
    """
    attrs = []
    out = []
    i = 0
    while True:
        m = re.compile(r'__attribute__[ \t]*\(').search(s, i)
        if m is None:
            out.append(s[i:])
            break
        out.append(s[i:m.start()])
        depth = 0
        j = m.end() - 1
        while j < len(s):
            if s[j] == "(":
                depth += 1
            elif s[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        attrs.append(re.sub(r'\s+', "", s[m.start():j + 1]))
        i = j + 1
    return "".join(sorted(attrs)), "".join(out)


def _decl_symbol(line: str) -> str | None:
    """The declared identifier of a one-line ``extern`` declaration."""
    body = line.strip()
    if not body.startswith("extern"):
        return None
    # strip an __asm__("...") alias tail -- the declared C identifier is the
    # one before it, and the asm name must ride along with the declaration.
    core = re.sub(r'__asm__[ \t]*\([^)]*\)', '', body)
    _, core = _strip_attributes(core)
    core = core.rstrip(";").rstrip()
    # function declarator: name immediately before the first '('
    m = re.search(r'([A-Za-z_][A-Za-z_0-9]*)[ \t]*\(', core)
    if m:
        return m.group(1)
    # object declarator: last identifier, ignoring array bounds
    core = re.sub(r'\[[^\]]*\]', '', core)
    ids = re.findall(r'[A-Za-z_][A-Za-z_0-9]*', core)
    return ids[-1] if ids else None


_KEYWORDS = {
    "extern", "const", "volatile", "static", "struct", "union", "enum",
    "unsigned", "signed", "void", "char", "short", "int", "long", "float",
    "double", "restrict", "_Bool", "__restrict", "inline", "register",
}


def _canon_decl(line: str) -> str | None:
    """Canonical form of a one-line ``extern`` declaration, or None.

    Two declarations with the same canonical form designate the **same C type**
    and are therefore interchangeable without any codegen consequence.  Exactly
    three equivalences are applied, each provable and each already used by
    stage 02 sub-batch A:

      1. whitespace is not part of a type;
      2. ``unsigned`` == ``unsigned int`` and ``signed`` == ``signed int``
         (C11 6.7.2);
      3. a parameter NAME is not part of a function type
         (C11 6.7.6.3: identifiers in a prototype have no linkage and go out of
         scope at the end of the declarator).

    Nothing else is folded.  ``int`` is never merged with ``unsigned int``,
    ``uint32_t`` is never resolved to its underlying type, and a differing
    return type or arity always yields a differing canonical form -- those are
    the disagreements worth reporting, not worth flattening.
    """
    s = line.strip()
    if not s.startswith("extern") or not s.endswith(";"):
        return None
    # attributes are part of the declaration's meaning (noreturn changes what
    # the caller may assume) but not part of its declarator syntax, so they are
    # lifted out for parsing and appended to the canonical form.  Two
    # declarations that differ only in an attribute stay DIFFERENT.
    attrs, s = _strip_attributes(s)
    s = re.sub(r'\s+', " ", s).strip()
    if "(*" in s.replace(" ", ""):
        return None            # function-pointer declarator: not canonicalised
    m = re.match(r'^(?P<head>.*?)\((?P<params>.*)\)(?P<tail>[^()]*);$', s)
    if m is None:
        # object declaration: whitespace + unsigned/signed only
        return attrs + _canon_tokens(s)
    params = []
    depth = 0
    cur = ""
    for ch in m.group("params"):
        if ch == "," and depth == 0:
            params.append(cur)
            cur = ""
            continue
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        cur += ch
    if cur.strip() or not params:
        params.append(cur)
    out = []
    for p in params:
        toks = re.findall(r'[A-Za-z_][A-Za-z_0-9]*|\*|\[|\]|[0-9]+', p)
        # drop a trailing parameter NAME: a plain identifier that is not a
        # keyword and is not the only token of the parameter.
        if len(toks) >= 2 and toks[-1] not in _KEYWORDS and \
                re.match(r'^[A-Za-z_]', toks[-1]):
            # only if what precedes it can be a type (another token exists)
            if any(t in _KEYWORDS or re.match(r'^[A-Za-z_]', t) or t == "*"
                   for t in toks[:-1]):
                toks = toks[:-1]
        out.append(_canon_tokens(" ".join(toks)))
    return attrs + _canon_tokens(m.group("head")) + "(" + ",".join(out) + ")" + \
        _canon_tokens(m.group("tail")) + ";"


def _canon_tokens(s: str) -> str:
    s = re.sub(r'\bunsigned\b(?!\s+(?:int|char|short|long))', "unsigned int", s)
    s = re.sub(r'\bsigned\b(?!\s+(?:int|char|short|long))', "signed int", s)
    s = re.sub(r'\s*([*(),;\[\]])\s*', r'\1', s)
    s = re.sub(r'\s+', " ", s)
    return s.strip()


_DEFINITION = re.compile(
    r'^(?P<head>[A-Za-z_][A-Za-z_0-9 \t*]*?)\b(?P<name>[A-Za-z_][A-Za-z_0-9]*)'
    r'[ \t]*\((?P<params>[^;{}()]*)\)[ \t]*\r?\n?[ \t]*\{', re.M)


def _definitions(text: str) -> dict[str, str]:
    """Top-level function DEFINITIONS in one file, as canonical declarations.

    A module header is included by the module's own files, including the file
    that defines the symbol -- which is the whole point of a real header, and
    which means the compiler now checks the callers' declaration against the
    definition for the first time.  The transformer must make that check
    itself, because under R4 a compile failure is a transformer bug, not a
    task to hand-fix: a disagreement is refused and reported, never forced.
    """
    out: dict[str, str] = {}
    for m in _DEFINITION.finditer(text):
        head = m.group("head").strip()
        if not head or head.split()[0] in ("if", "while", "for", "switch",
                                           "return", "else", "do", "typedef"):
            continue
        canon = _canon_decl("extern %s %s(%s);"
                            % (head, m.group("name"), m.group("params")))
        if canon:
            out[m.group("name")] = canon
    return out


def _divergence_class(canon_forms: list[str]) -> str:
    """Classify HOW a symbol's declarations disagree, most severe first.

    Arity is the severe one: a call site compiled against a 3-argument
    prototype for a function whose shipped body reads 5 registers is exactly
    the dropped-register-argument class the Unicorn differential harness is
    structurally blind to (19 confirmed instances already).
    """
    arities, returns, params = set(), set(), set()
    for c in canon_forms:
        m = re.match(r'^(?P<head>.*?)\((?P<params>.*)\)(?P<tail>.*);$', c)
        if m is None:
            returns.add(c)
            continue
        p = m.group("params")
        plist = [x for x in p.split(",") if x.strip()]
        if plist == ["void"]:
            plist = []
        arities.add(len(plist))
        head = m.group("head")
        returns.add(head[:head.rfind(next(reversed(
            re.findall(r'[A-Za-z_][A-Za-z_0-9]*', head)) or " "))]
            if re.findall(r'[A-Za-z_][A-Za-z_0-9]*', head) else head)
        params.add(p)
    if len(arities) > 1:
        return "arity_differs"
    if len(returns) > 1:
        return "return_type_differs"
    if len(params) > 1:
        return "parameter_type_differs"
    return "other"


#: names that ``<stdint.h>`` / ``<stddef.h>`` themselves typedef.  A generated
#: module header MUST include those two headers to be self-contained (round 1
#: of this transformer, `int64_t` unknown) -- but a source that typedefs one of
#: these names itself then meets the real one in the same translation unit and
#: the compiler rejects one of them.  Which order they arrive in does not
#: matter: `typedef unsigned short ... wchar_t;` and stddef's
#: `typedef unsigned int wchar_t;` are conflicting types either way.
#:
#: This is a bucket-(b) find rather than a design choice: it did not exist when
#: stage 03 first landed and appeared when the concurrent parity agent's
#: type-disagreement repair made `check_work_mode.c` newly eligible for a hoist.
#: The file is a genuine latent reconstruction defect -- a Ghidra
#: `typedef unsigned short undefined2,ushort,uint2,wchar_t;` line -- and until it
#: is repaired in the canonical tree the honest move is to leave that file out
#: of the hoist, not to drop the header's self-containment for everyone else.
_STDLIB_TYPEDEF_NAMES = frozenset("""
wchar_t size_t ptrdiff_t max_align_t
int8_t int16_t int32_t int64_t uint8_t uint16_t uint32_t uint64_t
intptr_t uintptr_t intmax_t uintmax_t
int_least8_t int_least16_t int_least32_t int_least64_t
uint_least8_t uint_least16_t uint_least32_t uint_least64_t
int_fast8_t int_fast16_t int_fast32_t int_fast64_t
uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t
""".split())

_TYPEDEF_STMT = re.compile(r'\btypedef\b([^;{}]*);')


def _typedef_declared_names(text: str) -> set[str]:
    """Names a source declares with ``typedef``, including comma lists."""
    out: set[str] = set()
    for m in _TYPEDEF_STMT.finditer(text):
        body = re.sub(r'\s+', ' ', m.group(1)).strip()
        fp = re.search(r'\(\s*\*+\s*([A-Za-z_]\w*)\s*\)\s*\(', body)
        if fp:
            out.add(fp.group(1))
            continue
        # `unsigned short undefined2,ushort,uint2,wchar_t`
        for part in body.split(","):
            ids = re.findall(r'[A-Za-z_]\w*', re.sub(r'\[[^\]]*\]', '', part))
            if ids:
                out.add(ids[-1])
    return out


def batch_b(moves, text, stats, defects):
    """Hoist module-wide type-identical extern declarations into a module header."""
    # group the moved .c/.inc files by their new directory
    by_dir: dict[str, list[str]] = {}
    for r, new in moves.items():
        if not new.endswith((".c", ".inc")):
            continue
        by_dir.setdefault(os.path.dirname(new), []).append(r)

    headers: dict[str, str] = {}
    hoisted_total = 0
    per_module = {}
    divergent_total = 0
    multi_total = 0

    # the measured set of identifiers the SDK angle headers declare
    # (recon/refactor/sdk_symbols.py).  Absent evidence yields the empty set,
    # which reproduces the pre-evidence behaviour exactly.
    sdk_syms = sdk_symbols.load()
    sdk_refused: list[dict] = []

    stdlib_shadow: list[str] = []
    for d in sorted(by_dir):
        files = []
        for r in sorted(by_dir[d]):
            shadowed = _typedef_declared_names(text[r]) & _STDLIB_TYPEDEF_NAMES
            if shadowed:
                stdlib_shadow.append("%s: %s" % (os.path.basename(r),
                                                 ",".join(sorted(shadowed))))
                continue
            files.append(r)
        if len(files) < 2:
            continue
        # symbol -> {canonical type -> {source spelling -> [files]}}
        decls: dict[str, dict[str, dict[str, list[str]]]] = {}
        uncanon: set[str] = set()
        multi_decl_lines: set[str] = set()
        defined_here: dict[str, tuple[str, str]] = {}
        # comment-blanked views, aligned line for line with the originals
        blanked = {r: _blank_comments(text[r]) for r in files}
        for r in files:
            for name, canon in _definitions(text[r]).items():
                defined_here[name] = (canon, r)
        for r in files:
            seen_here = set()
            for m in _DECL_LINE.finditer(blanked[r]):
                line = m.group(0)
                # Some symbolized files put several declarations on ONE line.
                # Treating such a line as a single declaration produces
                # nonsense like
                #   extern int get_device_info(int,extern int gui_screen_clear int,)
                # so a multi-declaration line is skipped whole: splitting it
                # would be a rewrite, and this batch only ever moves a
                # declaration it can read verbatim.
                if line.count(";") > 1 or line.count("extern") > 1:
                    multi_decl_lines.add(r)
                    continue
                sym = _decl_symbol(line)
                if sym is None:
                    continue
                key = line.strip()
                if (sym, key) in seen_here:
                    continue
                seen_here.add((sym, key))
                canon = _canon_decl(key)
                if canon is None:
                    uncanon.add(sym)
                    continue
                decls.setdefault(sym, {}).setdefault(canon, {}) \
                     .setdefault(key, []).append(r)

        hoist: dict[str, str] = {}
        divergent = []
        for sym, forms in decls.items():
            if sym in uncanon:
                continue          # a form of this symbol could not be canonicalised
            if sym in sdk_syms:
                # ---- REFUSAL: the SDK already declares this symbol.
                # Hoisting publishes a declaration into every module file that
                # lost a copy of ANY hoisted symbol -- including files that
                # never declared THIS one and that get the authoritative
                # spelling from an angle header.  Measured, not predicted: at
                # HEAD ff99f0c6 the concurrent agent's type-disagreement repair
                # made `k_sem_give`, `k_sleep` and `strlen` newly type-identical
                # across `unsorted/`, stage 03 hoisted all three unchanged, and
                # the baseline build failed with `conflicting types for
                # 'k_sem_give'` in `imu_fusion_init.c` -- which includes
                # <zephyr/kernel.h> on line 1 and never declared it.
                #
                # The refusal is deliberately NOT "reconcile with the SDK
                # prototype": that would rewrite a reconstructed declaration to
                # match a header, which is inventing evidence about the shipped
                # ABI in exactly the way this transformer refuses elsewhere.
                # It is reported as a defect instead.
                sdk_refused.append({
                    "module_dir": d, "symbol": sym,
                    "class": "reconstructed_declaration_shadows_an_sdk_symbol",
                    "types": {c: sum(len(v) for v in sp.values())
                              for c, sp in sorted(forms.items())},
                    "files": sorted({os.path.basename(f)
                                     for sp in forms.values()
                                     for v in sp.values() for f in v}),
                })
                continue
            if len(forms) == 1:
                canon = next(iter(forms))
                spellings = forms[canon]
                users = {f for v in spellings.values() for f in v}
                if sym in defined_here and defined_here[sym][0] != canon:
                    # the module DEFINES this symbol and the definition
                    # disagrees with what its callers declare.  Refusing is not
                    # caution: forcing the hoist would make the compiler reject
                    # the defining TU, and picking a winner would invent
                    # evidence about a shipped ABI.
                    divergent.append({
                        "module_dir": d,
                        "symbol": sym,
                        "class": "declaration_disagrees_with_definition",
                        "distinct_types": 2,
                        "types": {canon: len(users),
                                  defined_here[sym][0]: 1},
                        "definition_file": os.path.basename(defined_here[sym][1]),
                        "files": sorted({os.path.basename(f) for f in users}),
                    })
                    continue
                if len(users) >= 2:
                    # emit the most common source spelling, so the header reads
                    # like the code it replaces rather than like a canonicaliser's
                    # output.  Every spelling in this group designates the same
                    # type, so the choice is cosmetic by construction.
                    best = max(sorted(spellings), key=lambda k: len(spellings[k]))
                    hoist[sym] = best
            else:
                divergent.append({
                    "module_dir": d,
                    "symbol": sym,
                    "class": _divergence_class(list(forms)),
                    "distinct_types": len(forms),
                    "types": {c: sum(len(v) for v in sp.values())
                              for c, sp in sorted(forms.items())},
                    "files": sorted({os.path.basename(f)
                                     for sp in forms.values()
                                     for v in sp.values() for f in v}),
                })
        divergent_total += len(divergent)
        multi_total += len(multi_decl_lines)
        defects.extend(divergent)

        if not hoist:
            continue

        module = os.path.basename(d)
        hname = "g1_" + module + ".h"
        guard = "G1_MODULE_" + module.upper() + "_H"
        lines = [
            "/*",
            " * %s -- consolidated declarations for the `%s' module."
            % (hname, d[len(APP_SRC):]),
            " *",
            " * GENERATED by recon/refactor/transforms/t03_module_structure.py,",
            " * sub-batch B.  Do not edit: regenerate the stage.",
            " *",
            " * Every declaration below appeared in two or more translation units of",
            " * this module, and every occurrence designated the SAME C TYPE.  The",
            " * only differences folded are whitespace, `unsigned' vs `unsigned int'",
            " * (C11 6.7.2) and parameter names (C11 6.7.6.3) -- none of which is",
            " * part of a type, so no declaration reaching the compiler changed.",
            " *",
            " * Hoisting is REFUSED for any symbol whose declarations disagree about",
            " * a type anywhere in this module.  Such a disagreement is a candidate",
            " * reconstruction defect and is reported in DEFECTS.json rather than",
            " * resolved by this transformer: picking a winner would be inventing",
            " * evidence about a shipped ABI.",
            " */",
            "#ifndef %s" % guard,
            "#define %s" % guard,
            "",
            "/* A header must be self-contained: it is included by files that did",
            " * not previously need <stdint.h>, and a hoisted `int64_t' or",
            " * `uint8_t *' declaration would otherwise fail to compile in exactly",
            " * those files.  Both are type-only and emit no code. */",
            "#include <stdint.h>",
            "#include <stddef.h>",
            "",
        ]
        for sym in sorted(hoist):
            lines.append(hoist[sym])
        lines += ["", "#endif /* %s */" % guard, ""]
        headers[d + "/" + hname] = "\n".join(lines)

        # withdraw the hoisted declarations from every file and include instead
        removed = 0
        for r in files:
            t = text[r]
            out_lines = []
            touched = False
            # zip the original against its comment-blanked view so a
            # declaration carrying a trailing comment is withdrawn too -- the
            # comment belongs to the declaration and leaves with it.
            for line, bline in zip(t.split("\n"), blanked[r].split("\n")):
                s = bline.strip()
                if s.startswith("extern") and s.endswith(";"):
                    # refuse to drop a line whose tail opens a comment it does
                    # not close: removing it would swallow the following lines.
                    tail = line[len(bline.rstrip()):]
                    if not _COMMENT_TAIL.match(tail):
                        out_lines.append(line)
                        continue
                    sym = _decl_symbol(s)
                    if sym in hoist and _canon_decl(s) is not None and \
                            _canon_decl(s) == _canon_decl(hoist[sym]):
                        removed += 1
                        touched = True
                        continue
                out_lines.append(line)
            if touched:
                text[r] = _insert_include("\n".join(out_lines), hname)
        hoisted_total += len(hoist)
        per_module[d[len(APP_SRC):]] = {"declarations_hoisted": len(hoist),
                                        "per_file_copies_removed": removed,
                                        "files": len(files)}

    defects.extend(sdk_refused)
    stats["B_module_headers"] = {
        "headers_generated": len(headers),
        "files_excluded_shadowing_a_stdlib_typedef": sorted(stdlib_shadow),
        "files_excluded_shadowing_a_stdlib_typedef_count": len(stdlib_shadow),
        "files_with_multi_declaration_lines": multi_total,
        "declarations_hoisted": hoisted_total,
        "symbols_refused_divergent_spelling": divergent_total,
        "sdk_evidence_present": bool(sdk_syms),
        "sdk_declared_symbol_count": len(sdk_syms),
        "symbols_refused_shadowing_an_sdk_symbol": len(sdk_refused),
        "symbols_refused_shadowing_an_sdk_symbol_names": sorted(
            {e["symbol"] for e in sdk_refused}),
        "per_module": dict(sorted(per_module.items())),
    }
    return headers


def _insert_include(text: str, hname: str) -> str:
    """Insert ``#include "<hname>"`` after the last existing quoted include."""
    inc = '#include "%s"' % hname
    if inc in text:
        return text
    last = None
    for m in re.finditer(r'^[ \t]*#[ \t]*include[ \t]+[<"][^>"]+[>"][ \t]*$',
                         text, re.M):
        last = m
    if last is None:
        return inc + "\n" + text
    return text[:last.end()] + "\n" + inc + text[last.end():]


# --------------------------------------------------------------------- run
def run(stage, source_root: str, relpaths: list[str]) -> dict:
    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    stats: dict = {}
    defects: list = []

    moves = batch_a(relpaths, text, stats)

    enable_b = os.environ.get("G1_STAGE03_MODULE_HEADERS", "1") != "0"
    headers = batch_b(moves, text, stats, defects) if enable_b else {}
    if not enable_b:
        stats["B_module_headers"] = {"disabled": True}

    # build machinery, rewritten in the SAME transaction as the moves (C6)
    if RETAINED_CMAKE in text:
        text[RETAINED_CMAKE], n = rewrite_retained_cmake(text[RETAINED_CMAKE], moves)
        stats["A_retained_cmake_paths_rewritten"] = n
    if APP_CMAKELISTS in text:
        text[APP_CMAKELISTS], n = rewrite_app_cmakelists(text[APP_CMAKELISTS], moves)
        stats["A_cmakelists_paths_rewritten"] = n

    # ---- emit ---------------------------------------------------------
    moved = 0
    changed = 0
    for rel in relpaths:
        out_rel = moves.get(rel, rel)
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr = {}
        if out_rel != rel:
            tr["moved_from"] = rel
            moved += 1
        if data != src[rel]:
            tr["content_changed"] = True
            changed += 1
        stage.emit(out_rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    # generated module headers are OUTPUTS, not inputs: written straight into
    # the tree and recorded in manifest_extra, never in `files` (staleness
    # would then look for a source that does not exist).
    for rel, body in sorted(headers.items()):
        p = os.path.join(stage.tree, rel)
        check_write(p, stage.dir)
        os.makedirs(os.path.dirname(p), exist_ok=True)
        if os.path.islink(p):
            os.unlink(p)
        with open(p, "w", encoding="utf-8") as fh:
            fh.write(body)

    dpath = os.path.join(stage.dir, "DEFECTS.json")
    check_write(dpath, stage.dir)
    with open(dpath, "w", encoding="utf-8") as fh:
        json.dump({"schema": "g1.refactor.stage-defects/1", "stage": stage.number,
                   "count": len(defects), "entries": defects}, fh, indent=1)
        fh.write("\n")

    return {
        "report": {
            "files_moved": moved,
            "files_content_changed": changed,
            "module_headers_generated": len(headers),
            "declarations_hoisted":
                stats["B_module_headers"].get("declarations_hoisted", 0),
            "divergent_declaration_symbols":
                stats["B_module_headers"].get(
                    "symbols_refused_divergent_spelling", 0),
        },
        "manifest_extra": {
            "transform": "module structure (app core only; net untouched)",
            "sub_batches": stats,
            "generated_module_headers": sorted(headers),
        },
        "parity_extra": None,
    }
