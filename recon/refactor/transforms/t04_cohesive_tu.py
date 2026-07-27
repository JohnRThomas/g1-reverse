"""Stage 04 -- the SCOPED cohesive translation-unit merge (app core only).

Stage 03 gave the app core a directory structure but left it at **one function
per file**: 1,615 retained translation units for ~1,100 product functions.  A
maintainer opening ``display/`` still finds 89 files each holding one function.
Stage 04 is the batch that fixes that -- for the part of the tree where it can
be proven safe, and only for that part.

--------------------------------------------------------------------------
WHY THIS IS SCOPED, MEASURED RATHER THAN ASSUMED
--------------------------------------------------------------------------

Stage 03 declined a blanket merge because its ``DEFECTS.json`` recorded 1,014
symbol/module type disagreements, every one of which becomes a hard
``conflicting types`` error the moment two disagreeing files share a TU.  The
concurrent parity agent then repaired part of that census.  Re-running stage
03's own agreement test at HEAD ``50929c5d`` gives **902**, not 1,014 -- and,
decisively, **not one of the 22 app module directories has zero entries.**

So "merge only the modules that are provably clean" selects the EMPTY SET.
The scope that IS available is finer than a module: a maximal, ORDER-PRESERVING
run of consecutive files, within one module, that provably cannot collide.

Order preservation is the best available proxy for layout stability, and it is
worth being precise about how good a proxy it is.  Archive member order follows
``G1_RETAINED_SOURCES`` order and the toolchain compiles with
``-ffunction-sections``, so emitting each merged unit at exactly the position of
its members' contiguous span keeps the ARCHIVE order unchanged.

**It does not pin the final layout, and this was measured rather than assumed.**
The app sources link as ``app/libapp.a``, and a static archive's members are
pulled ON DEMAND to resolve undefined symbols, not in archive order.  In the
baseline, ``__ieee754_pow.c.obj`` and ``nan.c.obj`` are adjacent in the source
list and land 29 KiB apart (``0x14820`` vs ``0x0000d5a8``).  Merging them into one
member necessarily makes them adjacent, and everything after shifts.  Order
preservation therefore bounds the disturbance -- it does not remove it -- and the
stage's gate is the behavioural oracle, not a ``cmp``.

--------------------------------------------------------------------------
WHAT "PROVABLY CANNOT COLLIDE" MEANS -- the six refusal rules
--------------------------------------------------------------------------

Two files may share a TU only if NONE of the following holds.  Each rule is
symmetric and is evaluated against every file already in the run, not just the
previous one.

1. ``type``    -- a symbol declared or defined in both files with more than one
                  canonical C type (stage 03's canonicaliser, unchanged), or
                  with a declaration that cannot be canonicalised at all
                  (function-pointer declarator).  This is the ``DEFECTS.json``
                  class, applied pairwise instead of per module.
2. ``dupdef``  -- both files define the same non-static symbol.
3. ``static``  -- one file gives an identifier internal linkage and the other
                  file *names* that identifier.  This is the silent one:
                  C11 6.2.2p4 says a later ``extern`` declaration inherits the
                  visible prior INTERNAL linkage, so the second file's call
                  would silently bind to the first file's private helper.
4. ``typedef`` -- a typedef name defined by both files with different types, or
                  defined by one and named by the other.
5. ``macro``   -- a macro defined by both files with different bodies, or
                  defined by one and named by the other.  The second half is
                  what makes ``#define NAN ...`` in one file safe: any file that
                  merely *mentions* NAN is refused as a TU partner.
6. ``asmname`` -- the same ``__asm__("...")`` assembler name bound to two
                  different C identifiers.

Rules 3-5 are the class the brief calls out and that **no gate in this project
can see**: a locally redefined type or macro is harmless in its own file and
becomes wrong only when two files share a TU.  They are enforced structurally
here, so the dangerous case is unrepresentable rather than merely unlikely.

``__ieee754_exp.c`` is the named instance.  It carries
``typedef uint64_t u8;`` while ``recon/headers/g1_types.h`` says
``typedef uint8_t u8;`` and 17 other files say ``unsigned char u8``.  Rule 4
refuses to put it in a TU with any file that so much as mentions ``u8``.  It is
not special-cased: the rule found it, and the same rule found every other
instance (reported in QUARANTINE.json under ``incompatible_local_typedefs``).

A NECESSARY MEASUREMENT behind rule 4.  On this target the obvious foldings are
NOT all true.  Compiled with the project's own ``arm-zephyr-eabi-gcc
-mcpu=cortex-m33 -std=gnu11``:

    typedef uint8_t  X; typedef unsigned char      X;   -- accepted, SAME
    typedef uint16_t X; typedef unsigned short     X;   -- accepted, SAME
    typedef uint64_t X; typedef unsigned long long X;   -- accepted, SAME
    typedef int64_t  X; typedef long long          X;   -- accepted, SAME
    typedef uint32_t X; typedef unsigned int       X;   -- REJECTED, DIFFERENT
    typedef int32_t  X; typedef int                X;   -- REJECTED, DIFFERENT
    typedef uint32_t X; typedef unsigned long      X;   -- accepted, SAME

newlib on arm-zephyr-eabi types ``uint32_t`` as ``unsigned long`` and
``int32_t`` as ``long``.  Folding ``uint32_t`` onto ``unsigned int`` -- the
intuitive move, and the one the corpus makes in 30 files -- would have produced
a wrong "these agree" verdict on the single most common typedef in the tree.

--------------------------------------------------------------------------
SHAPE QUARANTINE -- files excluded from merging before any pairing
--------------------------------------------------------------------------

* ``#pragma`` anywhere.  ``#pragma GCC diagnostic ignored`` is file-scope state
  that leaks forward through a concatenated TU and silently SUPPRESSES the
  diagnostics on every later function.  Diagnostics are how this project finds
  latent defects (README C4 bucket (b)); losing them silently is worse than not
  merging.  Wrapping each segment in ``push``/``pop`` would restore the state,
  but it would also strip the pragmas that ``g1_log.h`` applies once through its
  include guard, which is a second-order change this batch will not take.
* an absolute-path ``#include`` (the two liblc3 TUs) -- those headers are
  outside the repository and their include-guard status is not ours to assert.
* a ``#include`` of a repository ``.inc`` fragment -- the fragment carries
  definitions, so two includers in one TU would be a duplicate definition; only
  one file does this today, but the rule is not conditional on that.
* ``__attribute__((alias(...)))`` -- an alias definition plus a same-asm-name
  declaration in one TU is a conflicting declaration.
* a **multi-declaration source line** -- stage 03 already refuses to read those
  declarations, so their types are UNKNOWN, and an unknown type cannot be
  proven not to collide.
* named by PATH in ``recon/application/app/CMakeLists.txt``
  (``discovery_callback.c``, which needs ``-std=gnu99`` for its
  ``register ... asm("r9")`` body).  Merging it would either drop the flag
  silently -- CMake does not error when a ``set_source_files_properties`` path
  stops existing -- or apply ``gnu99`` to every other function in the merged TU.
* the float bodies whose **per-TU** ``-ffp-contract`` contract is recovered from
  the shipped image (AGENTS.md finding 1b): ``imu_mahony_ahrs_update``,
  ``fast_inverse_sqrt``, ``orientation_get_heading_deg``,
  ``quaternion_to_euler``, ``fuel_gauge_update``, ``discovery_callback``.  The
  build does not set ``-ffp-contract`` today (measured: zero occurrences under
  ``recon/application``), but it MUST for those bodies to byte-match, and that
  flag can only ever be applied per translation unit.  Merging them forecloses
  a fix the project has already committed to.

--------------------------------------------------------------------------
R8 -- what here could reorder or coalesce a volatile MMIO access
--------------------------------------------------------------------------

Concatenation edits no statement and moves no token inside any function body:
every member's text is emitted VERBATIM, includes left exactly where they were
(all five repository headers are include-guarded, so a repeated inclusion is a
no-op, and leaving them in place avoids any question about a header whose
content depends on macros defined before it -- ``g1_app_symbols.h`` opens with
``#ifndef bool``).

What DOES change is what the optimiser may do: functions that were previously in
separate TUs are now candidates for inlining into one another, and identical
string literals may be pooled.  That is a codegen change by construction, so
unlike stages 01-03 this stage CANNOT be gated on ``cmp zephyr.bin``, and it is
the first one that cannot.  The R8 exposure is therefore real and is bounded,
not argued away: the sub-batch split below exists precisely so it can be
measured in halves.

``G1_STAGE04_BATCH`` selects how much is merged:

    A   only runs in which NO member file contains the token ``volatile``.
    B   (DEFAULT since the R7 gate) only runs in which AT LEAST ONE member
        contains ``volatile`` -- the complement of A within the clean runs.
    AB  every clean run (A united with B).
    off no merge at all -- the identity transform, for bisecting.

--------------------------------------------------------------------------
WHY THE DEFAULT IS **B** AND NOT **AB** -- the R7 gate reversed the ordering
--------------------------------------------------------------------------

The A/B split was ORIGINALLY an R8 risk ordering: A was chosen as the low-risk
half because no member performs a volatile access at all, so no inlining
decision inside a merged A unit can reorder, coalesce or drop one.  R8 exposure
of A: nil.  B carried all of it.

The oracle run of 2026-07-27 measured the opposite
(``recon/analysis/stage04_r7_validation.md``, and the R7 gate record in
``recon/refactor/README.md``).  Nine seeded Renode captures over three images:

  * **All eight side-effect regressions are sub-batch A's**, identical field
    for field on A and on AB: navigation ``twim1 p1_boot`` 371 -> 373
    (OPT3001 33 -> 35), ``twim2 p1_boot`` 1,089 transactions re-ordered
    (``7ed8ddcd...`` -> ``03537cda...``), ``counters/RADIO_TX`` 0x232 -> 0x233.
  * Comparing **AB against A** gives **0 regressions and 2 improvements**: B's
    271 further merged units, 1,087 further files, introduce not one new
    divergence and take ``twim2 p2_render`` to byte-equality with shipped.

The R8 argument was not refuted -- the failure is not a volatile reordering.
It was **irrelevant**.  Both regressions decode to pure re-phasings: the OPT3001
poll train's period is unchanged to 30 ns and its first 33 transactions are
identical and in order, but its phase moves -100.7 ms, so one extra poll fits
inside the 6 s wall.  The carrier is the **LINKED SIZE of the boot path**, and
sub-batch A's entire codegen delta is **-16 B and two functions**
(``k_uptime_get_3`` 28 -> 4 B, ``__ieee754_pow`` 2,480 -> 2,488 B).

What the ``volatile`` token actually partitions, once that is understood, is not
risk but SHAPE.  This corpus models every global as a ``volatile``
absolute-address pointer, so a file WITHOUT the token is the unusual one: a pure
computational leaf (libm) or a forwarding thunk that touches no global at all.
Merging exactly those is what lets a 28-byte thunk collapse into a 4-byte tail
branch.  A selected the files most likely to shrink; that is why the "safe" half
moved the image and the "risky" half did not.

Hence the default is B.  Note what this does NOT claim: AB-against-A measured
B's INCREMENTAL effect **on top of A**.  A B-only image is a fourth image that
has never been booted, and its ``.text`` delta is not zero (see the stage report).
Per the general lesson this pipeline now encodes as a first-class stage property
(``driver.CODEGEN_CLASS`` / ``driver.py size-gate``), **any transformation that
changes linked size can break side-effect equivalence in either direction**, so
this stage is declared ``size-changing`` and an oracle run is REQUIRED, not
optional, before it is landed.
"""

from __future__ import annotations

import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import stagelib  # noqa: E402
from guard import check_write  # noqa: E402

from transforms import t03_module_structure as t3  # noqa: E402

APP_SRC = "recon/symbolized/app/"
RETAINED_CMAKE = "recon/generated/app_retained_sources.cmake"
APP_CMAKELISTS = "recon/application/app/CMakeLists.txt"

#: ``G1_STAGE04_BATCH`` values.  A and B PARTITION the clean multi-member runs.
BATCHES = frozenset(("A", "B", "AB", "OFF"))
#: The R7 gate of 2026-07-27 charged 100 % of stage 04's eight side-effect
#: regressions to sub-batch A and measured B as introducing none.  See the
#: module docstring for why the ``volatile`` token partitions SHAPE, not risk.
DEFAULT_BATCH = "B"

#: bodies whose ``-ffp-contract`` is a per-TU contract recovered from the image
#: (AGENTS.md critical finding 1b).  Never merged: the flag has no finer grain.
FP_CONTRACT_TUS = (
    "imu_mahony_ahrs_update.c", "fast_inverse_sqrt.c",
    "orientation_get_heading_deg.c", "quaternion_to_euler.c",
    "fuel_gauge_update.c", "discovery_callback.c",
)

_STR = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')
_IDENT = re.compile(r'[A-Za-z_]\w*')
_DEFINE = re.compile(
    r'^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\([^)]*\))?'
    r'((?:[^\n\\]|\\\r?\n|\\)*)', re.M)
_PRAGMA = re.compile(r'^[ \t]*#[ \t]*pragma\b', re.M)
_INC_ABS = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"/', re.M)
_INC_FRAG = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"[^"]*\.inc"', re.M)
_TYPEDEF_KW = re.compile(r'\btypedef\b')
_TAG_DEF = re.compile(r'\b(?P<kw>struct|union|enum)[ \t\r\n]+(?P<name>[A-Za-z_]\w*)[ \t\r\n]*\{')
_ANON_ENUM = re.compile(r'\benum[ \t\r\n]*\{')

#: headers that declare no function and define no object -- only types.  Two
#: members may differ about these (see `type_only_includes` in `analyse`).
TYPE_ONLY_HEADERS = frozenset(("<stdint.h>", "<stddef.h>"))
_ASMNAME = re.compile(r'__asm__[ \t]*\(\s*"(?P<nm>[^"]+)"\s*\)')
_STATIC = re.compile(
    r'\bstatic\b(?P<rest>(?:[^;{()]|\([^()]*\))*?)'
    r'(?P<name>[A-Za-z_]\w*)[ \t]*'
    r'(?:\((?P<params>[^;{]*)\)[ \t]*(?:\r?\n)?[ \t]*\{'
    r'|(?:\[[^\]]*\])*[ \t]*(?:=|;))', re.S)

_DECL_SPECIFIERS = {
    "inline", "const", "volatile", "struct", "union", "enum", "unsigned",
    "signed", "char", "short", "int", "long", "float", "double", "void",
    "__attribute__", "_Bool", "register", "restrict", "__restrict",
}

#: base-type identities MEASURED with the project's own compiler; see the module
#: docstring.  ``uint32_t``/``int32_t`` are deliberately mapped to
#: ``unsigned long``/``long`` and NOT to ``unsigned int``/``int``.
_TDNORM = (("uint8_t", "unsigned char"), ("uint16_t", "unsigned short"),
           ("uint32_t", "unsigned long"), ("uint64_t", "unsigned long long"),
           ("int8_t", "signed char"), ("int16_t", "short"),
           ("int32_t", "long"), ("int64_t", "long long"),
           ("size_t", "unsigned int"), ("uintptr_t", "unsigned int"))


# ------------------------------------------------------------------ lexing
def _blank(span: str) -> str:
    """Same-length blanking that keeps newlines, so offsets stay aligned."""
    return "".join("\n" if ch == "\n" else " " for ch in span)


def strip_comments(t: str, drop_strings: bool = False) -> str:
    """Comment-free view of a C source.

    LENGTH-PRESERVING and newline-preserving: comments (and, with
    ``drop_strings``, string/character literal CONTENT) are replaced by spaces
    rather than removed, so an offset into the result indexes the same token as
    the same offset into the original.  Two views of one file can therefore be
    cross-indexed -- which is what lets brace depth be computed on the
    string-free view and applied to the string-bearing one.
    """
    out, i, n = [], 0, len(t)
    while i < n:
        c = t[i]
        if c == "/" and i + 1 < n and t[i + 1] == "*":
            j = t.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(_blank(t[i:j]))
            i = j
            continue
        if c == "/" and i + 1 < n and t[i + 1] == "/":
            j = t.find("\n", i)
            j = n if j < 0 else j
            out.append(_blank(t[i:j]))
            i = j
            continue
        if c in "\"'":
            m = _STR.match(t, i)
            if m:
                lit = m.group(0)
                out.append(lit[0] + _blank(lit[1:-1]) + lit[-1]
                           if drop_strings and len(lit) >= 2 else lit)
                i = m.end()
                continue
        out.append(c)
        i += 1
    return "".join(out)


def _depths(struct_view: str) -> list[int]:
    """Brace depth BEFORE the character at each offset.

    File scope is depth 0.  A ``typedef`` or ``static`` inside a function body
    has no file-scope effect, and treating one as if it had would refuse merges
    for no reason; missing a file-scope ``static`` would be far worse -- a later
    member's call would silently bind to an earlier member's private helper.
    """
    out = [0] * (len(struct_view) + 1)
    d = 0
    for i, ch in enumerate(struct_view):
        out[i] = d
        if ch == "{":
            d += 1
        elif ch == "}":
            d = max(0, d - 1)
    out[len(struct_view)] = d
    return out


def norm_type(s: str) -> str:
    s = re.sub(r"\s+", " ", s).strip()
    for a, b in _TDNORM:
        s = re.sub(r"\b%s\b" % a, b, s)
    s = re.sub(r"\bunsigned\b(?!\s+(?:int|char|short|long))", "unsigned int", s)
    s = re.sub(r"\bsigned\b(?!\s+(?:int|char|short|long))", "signed int", s)
    s = re.sub(r"\s*([*(),\[\]])\s*", r"\1", s)
    return s.strip()


def _typedef_name(body: str) -> str | None:
    b = re.sub(r"\s+", " ", body).strip()
    m = re.search(r"\(\s*\*+\s*([A-Za-z_]\w*)\s*\)\s*\(", b)   # function pointer
    if m:
        return m.group(1)
    ids = _IDENT.findall(re.sub(r"\[[^\]]*\]", "", b))
    return ids[-1] if ids else None


def analyse(text: str, module_header: str | None = None) -> dict:
    """Every fact about one source that decides whether it may share a TU."""
    code = strip_comments(text)
    nostr = strip_comments(text, drop_strings=True)
    d: dict = {}

    d["has_pragma"] = bool(_PRAGMA.search(code))
    d["has_abs_include"] = bool(_INC_ABS.search(code))
    d["has_inc_fragment"] = bool(_INC_FRAG.search(code))
    d["has_alias_attr"] = "__attribute__((alias(" in re.sub(r"\s+", "", code)
    d["has_volatile"] = bool(re.search(r"\bvolatile\b", code))

    d["defines"] = {
        m.group(1): re.sub(r"\s+", " ", (m.group(2) or "") + "=" + m.group(3)).strip()
        for m in _DEFINE.finditer(code)}

    depth = _depths(nostr)

    # ---- file-scope typedefs.  NOT line-anchored: `__ieee754_exp.c` writes
    # `typedef uint32_t u4; typedef int32_t i4; typedef uint64_t u8; ...` all on
    # ONE line, and a `^[ \t]*typedef` rule sees only the first of the four --
    # which is exactly how the named `u8 == uint64_t` hazard stays invisible.
    tds: dict[str, str] = {}
    for m in _TYPEDEF_KW.finditer(code):
        if depth[m.start()] != 0:
            continue
        j, k = m.end(), len(code)
        while j < k:                       # the terminating `;` at THIS depth
            if code[j] == ";" and depth[j] == 0:
                break
            j += 1
        body = re.sub(r"\s+", " ", code[m.end():j]).strip()
        if not body:
            continue
        nm = _typedef_name(body)
        if not nm:
            continue
        tds[nm] = norm_type(re.sub(r"\b%s\b" % re.escape(nm), "@", body, count=1))
        # `typedef unsigned long long undefined8,ulonglong;`
        if "," in body and "(" not in body:
            base = body[:body.rfind(nm)].strip()
            for extra in body.split(",")[1:]:
                e = extra.strip()
                if re.fullmatch(r"[A-Za-z_]\w*", e):
                    tds[e] = norm_type(base + " @")
    d["typedefs"] = tds

    # ---- file-scope struct/union/enum TAG definitions and enum constants.
    # A tag may be declared any number of times but DEFINED only once in a
    # scope, even identically: `struct g1_i2c_msg { ... };` appears verbatim in
    # three sources and `redefinition of 'struct g1_i2c_msg'` is a hard error.
    # (A duplicate identical TYPEDEF, by contrast, is accepted by this compiler
    # in every -std mode -- measured, c99/gnu99/gnu11 all compile it -- which is
    # why the typedef rule compares bodies and this one does not.)
    tags: dict[str, str] = {}
    enum_constants: set[str] = set()
    for m in _TAG_DEF.finditer(code):
        if depth[m.start()] != 0:
            continue
        j = nostr.find("}", m.end())
        body = re.sub(r"\s+", " ", code[m.end():j if j >= 0 else m.end()])
        tags["%s %s" % (m.group("kw"), m.group("name"))] = body.strip()
        if m.group("kw") == "enum":
            enum_constants |= set(re.findall(r"[A-Za-z_]\w*", body))
    for m in _ANON_ENUM.finditer(code):
        if depth[m.start()] != 0:
            continue
        j = nostr.find("}", m.end())
        enum_constants |= set(re.findall(r"[A-Za-z_]\w*",
                                         code[m.end():j if j >= 0 else m.end()]))
    d["tags"] = tags
    d["enum_constants"] = enum_constants

    statics: dict[str, str] = {}
    for m in _STATIC.finditer(code):
        if depth[m.start()] != 0:
            continue                       # block-scope static: cannot collide
        nm = m.group("name")
        if nm in _DECL_SPECIFIERS:
            continue
        statics[nm] = "func" if m.group("params") is not None else "obj"
    d["statics"] = statics

    # ---- function DEFINITIONS, found structurally rather than by line shape.
    # Stage 03's scanner anchors the return type at the start of a line.  The
    # corpus does not oblige: `typedef unsigned char u8;u8 is_battery_critical
    # (void){...}` and `extern int delay_scaled_busy_wait(int,int,int,int); int
    # thunk_FUN_00086384(int a,...){...}` both put a definition in mid-line, and
    # both were merged into a TU whose module header declares them with a
    # different type.  Walking back from a depth-0 `){` finds them regardless of
    # layout.
    defs: dict[str, str] = {}
    for m in re.finditer(r"\)[ \t\r\n]*\{", nostr):
        if depth[m.start()] != 0:
            continue
        # back to the matching '('
        i, level = m.start(), 0
        while i >= 0:
            if nostr[i] == ")":
                level += 1
            elif nostr[i] == "(":
                level -= 1
                if level == 0:
                    break
            i -= 1
        if i < 0:
            continue
        nm_m = re.search(r"([A-Za-z_]\w*)[ \t\r\n]*$", nostr[:i])
        if nm_m is None:
            continue
        nm = nm_m.group(1)
        start = max(nostr.rfind(";", 0, nm_m.start(1)),
                    nostr.rfind("}", 0, nm_m.start(1)),
                    nostr.rfind("{", 0, nm_m.start(1)),
                    nostr.rfind("#", 0, nm_m.start(1)))
        head = re.sub(r"\s+", " ", code[start + 1:nm_m.start(1)]).strip()
        if not head or head.split()[0] in ("if", "while", "for", "switch",
                                           "return", "else", "do", "typedef"):
            continue
        if nm in statics or "static" in head.split():
            continue                     # internal linkage: rule 3 owns it
        params = re.sub(r"\s+", " ", code[i + 1:m.start()])
        defs[nm] = t3._canon_decl("extern %s %s(%s);" % (head, nm, params))
    d["definitions"] = defs

    # ---- file-scope `extern` declarations, MULTI-LINE aware.
    # Stage 03's scanner is `^[ \t]*extern[ \t].*;[ \t]*$` -- one physical line.
    # That blind spot is not theoretical: the first stage 04 build failed on
    # `battery_soc_curve_model_init`, whose declaration in one member wraps over
    # three lines and disagrees with the definition in another member about two
    # parameter types.  A declaration that the safety rule cannot read is a
    # declaration the safety rule cannot protect.
    decls: dict[str, set] = {}
    for m in re.finditer(r"\bextern\b", nostr):
        if depth[m.start()] != 0:
            continue
        j = nostr.find(";", m.end())
        if j < 0:
            continue
        stmt = re.sub(r"\s+", " ", code[m.start():j + 1]).strip()
        sym = t3._decl_symbol(stmt)
        if sym is None:
            continue
        decls.setdefault(sym, set()).add(t3._canon_decl(stmt))
    d["decls"] = decls
    d["multi_decl_line"] = any(
        line.count(";") > 1 or line.count("extern") > 1
        for line in (m.group(0) for m in t3._DECL_LINE.finditer(code)))

    # assembler-name bindings, keyed by the asm name and valued by the WHOLE
    # normalised statement that binds it.  Two files that bind the same asm
    # name to textually identical declarations are fine (the corpus has such
    # pairs); two that bind it differently would be a conflicting declaration.
    asmn: dict[str, str] = {}
    for m in _ASMNAME.finditer(code):
        start = max(code.rfind(";", 0, m.start()), code.rfind("}", 0, m.start()),
                    code.rfind("{", 0, m.start()), code.rfind("\n", 0, m.start()))
        end = code.find(";", m.end())
        stmt = code[start + 1: end if end >= 0 else m.end()]
        asmn[m.group("nm")] = re.sub(r"\s+", " ", stmt).strip()
    # ---- object-like macros that RENAME a symbol.
    # `lib/` carries `#define zcbor_str_start_decode cbor_decode_length_prefix`
    # followed by `extern int zcbor_str_start_decode(...)`.  The declaration the
    # compiler sees is of `cbor_decode_length_prefix`, and another member of the
    # same run defines that symbol with a different type.  Recording the
    # declaration under the name the preprocessor actually produces is what
    # makes rule 1 see it.
    alias = {k: v.lstrip("=").strip() for k, v in d["defines"].items()
             if not v.startswith("(") and re.fullmatch(
                 r"=[A-Za-z_]\w*", v.replace(" ", ""))}
    if alias:
        for coll in ("decls", "definitions"):
            renamed = {}
            for k, v in d[coll].items():
                renamed[alias.get(k, k)] = v
            d[coll] = renamed
    d["macro_aliases"] = alias

    d["asmnames"] = asmn
    d["idents"] = set(_IDENT.findall(nostr))
    d["quoted_include_spellings"] = [m.group(1) for m in re.finditer(
        r'^[ \t]*#[ \t]*include[ \t]+"([^"]+)"', code, re.M)]
    d["quoted_includes"] = {os.path.basename(s)
                            for s in d["quoted_include_spellings"]}

    # ---- the include ENVIRONMENT (rule 7).
    # A member's own local `extern` declarations were checked by the compiler
    # against the headers THAT FILE includes -- and against nothing else.  Merge
    # a file that includes `<zephyr/kernel.h>` with one that writes its own
    # `extern void k_sleep(uint32_t,uint32_t);` and the authoritative
    # declaration meets the reconstructed one for the first time.  Measured, not
    # predicted: the second stage 04 build failed exactly so, on `printk`,
    # `k_sleep`, `z_impl_k_sem_take` and `memcpy`.
    #
    # Requiring the two files' declaration-bearing include sets to be EQUAL
    # makes that unrepresentable, and the proof is one line: if A and B see the
    # same headers, then everything A declares locally was already compiled
    # against B's headers and vice versa, so only local-vs-local pairings are
    # new -- and those are rules 1-6.
    #
    # Only ANGLE includes need that treatment.  A quoted include resolves to
    # repository content this pipeline can read, so its declarations, macros,
    # typedefs and static inlines are folded into the including file's own facts
    # (`fold_header` below) and then checked by rules 1-6 like any other
    # declaration.  That keeps `g1_log.h`, `g1_dedupe.h` and the module header
    # from fragmenting every run, without assuming anything about them.
    incs = set()
    for m in re.finditer(r'^[ \t]*#[ \t]*include[ \t]+(<[^>]+>)', code, re.M):
        incs.add(m.group(1))
    d["type_only_includes"] = incs & TYPE_ONLY_HEADERS
    d["declaring_includes"] = frozenset(incs - TYPE_ONLY_HEADERS)
    # `<stdint.h>`/`<stddef.h>` declare no function, so they may differ between
    # members -- but they DO typedef.  Treat including one as naming every name
    # it provides, so a partner that typedefs `uint32_t` itself is refused by
    # the ordinary typedef rule instead of failing in the build.
    if d["type_only_includes"]:
        d["idents"] |= t3._STDLIB_TYPEDEF_NAMES
    d["includes_module_header"] = bool(
        module_header and module_header in d["quoted_includes"])
    return d


def fold_header(d: dict, h: dict) -> None:
    """Fold a quoted repository header's facts into an including file's.

    After this, a file that gets ``printk`` from ``g1_log.h`` carries that
    declaration as if it had written it, so a member that declares ``printk``
    itself with a different type is refused by rule 1 rather than by the
    compiler.  Definitions are deliberately NOT folded: a header defines
    nothing with external linkage in this corpus, and pretending otherwise
    would invent a duplicate-definition conflict.
    """
    for s, forms in h["decls"].items():
        d["decls"].setdefault(s, set()).update(forms)
    for k in ("defines", "typedefs", "statics", "tags", "macro_aliases"):
        for name, val in h[k].items():
            d[k].setdefault(name, val)
    d["enum_constants"] |= h["enum_constants"]
    d["idents"] |= h["idents"]
    d["type_only_includes"] = d["type_only_includes"] | h["type_only_includes"]
    d["declaring_includes"] = frozenset(d["declaring_includes"]
                                        | h["declaring_includes"])
    if d["type_only_includes"]:
        d["idents"] |= t3._STDLIB_TYPEDEF_NAMES


def resolve_quoted(path: str, spelling: str, search_dirs: list[str]) -> str | None:
    """Resolve a quoted include the way the compiler does: relative first."""
    cand = os.path.normpath(os.path.join(os.path.dirname(path), spelling))
    if os.path.isfile(cand):
        return cand
    for d in search_dirs:
        cand = os.path.normpath(os.path.join(d, spelling))
        if os.path.isfile(cand):
            return cand
    return None


def header_decls(path: str) -> dict[str, set]:
    """Canonical declaration forms a generated module header publishes."""
    if not os.path.exists(path):
        return {}
    with open(path, encoding="utf-8", errors="surrogateescape") as fh:
        code = strip_comments(fh.read())
    out: dict[str, set] = collections.defaultdict(set)
    for m in t3._DECL_LINE.finditer(code):
        line = m.group(0)
        if line.count(";") > 1 or line.count("extern") > 1:
            continue
        sym = t3._decl_symbol(line)
        if sym is not None:
            out[sym].add(t3._canon_decl(line.strip()))
    return dict(out)


def _sym_forms(d: dict) -> dict[str, set]:
    out: dict[str, set] = collections.defaultdict(set)
    for s, forms in d["decls"].items():
        out[s] |= forms
    for s, c in d["definitions"].items():
        out[s].add(c)
    return out


def shape_refusal(base: str, d: dict, cmake_named: set[str]) -> str | None:
    """Why this file may not be merged at all, or None."""
    if base in cmake_named:
        return "named_by_path_in_app_cmakelists"
    if base in FP_CONTRACT_TUS:
        return "per_tu_ffp_contract_body"
    if d["has_pragma"]:
        return "file_scope_pragma_leaks_forward"
    if d["has_abs_include"]:
        return "absolute_path_include_outside_repository"
    if d["has_inc_fragment"]:
        return "includes_a_definition_carrying_inc_fragment"
    if d["has_alias_attr"]:
        return "attribute_alias_definition"
    if d["multi_decl_line"]:
        return "multi_declaration_line_types_unknown"
    return None


def conflicts(a: dict, b: dict, hdr: dict[str, set] | None = None
              ) -> list[tuple[str, str]]:
    """Every reason two files may not share a TU.  Symmetric.

    ``hdr`` carries the declarations of the stage 03 **generated module
    header**, and is applied whenever either file includes it.  Without this the
    merge has a blind spot with teeth: a file that was NOT converted by stage 03
    keeps its own local declaration of a symbol the module header also declares,
    which is harmless while the two are in different translation units and is a
    hard ``conflicting types`` error the moment they are merged.  Measured, not
    predicted: the first stage 04 build failed on exactly this, at
    ``battery_soc_curve_model_init`` in ``sensors/power``.
    """
    out: list[tuple[str, str]] = []
    fa, fb = _sym_forms(a), _sym_forms(b)
    if hdr and (a["includes_module_header"] or b["includes_module_header"]):
        for s, forms in hdr.items():
            fa[s] |= forms
            fb[s] |= forms
    for s in sorted(set(fa) & set(fb)):
        u = fa[s] | fb[s]
        if None in u or len(u) > 1:
            out.append(("type", s))
    for s in sorted(set(a["definitions"]) & set(b["definitions"])):
        out.append(("dupdef", s))
    for s in sorted(a["statics"]):
        if s in b["idents"]:
            out.append(("static", s))
    for s in sorted(b["statics"]):
        if s in a["idents"]:
            out.append(("static", s))
    for t, body in sorted(a["typedefs"].items()):
        if t in b["typedefs"]:
            if b["typedefs"][t] != body:
                out.append(("typedef", t))
        elif t in b["idents"]:
            out.append(("typedef", t))
    for t in sorted(b["typedefs"]):
        if t not in a["typedefs"] and t in a["idents"]:
            out.append(("typedef", t))
    for m, body in sorted(a["defines"].items()):
        if m in b["defines"]:
            if b["defines"][m] != body:
                out.append(("macro", m))
        elif m in b["idents"]:
            out.append(("macro", m))
    for m in sorted(b["defines"]):
        if m not in a["defines"] and m in a["idents"]:
            out.append(("macro", m))
    for nm, ident in sorted(a["asmnames"].items()):
        if nm in b["asmnames"] and b["asmnames"][nm] != ident:
            out.append(("asmname", nm))
    for tag in sorted(set(a["tags"]) & set(b["tags"])):
        out.append(("tag", tag))
    for c in sorted(a["enum_constants"] & b["enum_constants"]):
        out.append(("enumconst", c))
    for c in sorted(a["enum_constants"]):
        if c in b["idents"] and c not in b["enum_constants"]:
            out.append(("enumconst", c))
    for c in sorted(b["enum_constants"]):
        if c in a["idents"] and c not in a["enum_constants"]:
            out.append(("enumconst", c))
    if a["declaring_includes"] != b["declaring_includes"]:
        out.append(("includes", ",".join(sorted(
            a["declaring_includes"] ^ b["declaring_includes"]))))
    return out


# --------------------------------------------------------------- emission
_MOD_SLUG = re.compile(r"[^A-Za-z0-9]+")


def merged_name(module_dir: str, index: int) -> str:
    """Path of the merged TU.

    NOTE the name may never match ``rodata_*``: ``g1_verified_rodata_keep.ld``
    matches ``KEEP(*rodata_*.c.obj(...))`` on the OBJECT FILENAME, so a merged
    unit called ``rodata_something.c`` would silently change what survives
    ``--gc-sections`` (README C6).
    """
    slug = _MOD_SLUG.sub("_", module_dir[len(APP_SRC):]).strip("_")
    return "%s%s/g1_%s_%02d.c" % (APP_SRC, module_dir[len(APP_SRC):], slug, index)


def render(module_dir: str, members: list[str], text: dict[str, str]) -> str:
    """Concatenate members VERBATIM under one banner."""
    mod = module_dir[len(APP_SRC):]
    head = [
        "/*",
        " * Cohesive translation unit for the `%s' module." % mod,
        " *",
        " * GENERATED by recon/refactor/transforms/t04_cohesive_tu.py.  Do not",
        " * edit: a stage tree is regenerated, never hand-patched",
        " * (recon/refactor/README.md C4).",
        " *",
        " * The %d functions below were %d separate translation units until this" % (
            len(members), len(members)),
        " * stage.  Each one's text is reproduced VERBATIM and in the order the",
        " * generated source list gave it, and they were CONSECUTIVE in that list.",
        " * They were proven able to share a translation unit: no symbol is",
        " * declared here with two types, no identifier has internal linkage in one",
        " * member and is named by another, and no local typedef, macro, struct tag",
        " * or enum constant of one member is visible to a member that names it.",
        " *",
        " * members, in link order:",
    ]
    for m in members:
        head.append(" *   %s" % os.path.basename(m))
    head += [" */", ""]
    body = []
    for m in members:
        body.append("/* ---------------------------------------------------------------- */")
        body.append("/* %s */" % os.path.basename(m))
        body.append("/* ---------------------------------------------------------------- */")
        body.append(text[m].rstrip("\n"))
        body.append("")
    return "\n".join(head) + "\n".join(body) + "\n"


def rewrite_retained_cmake(text: str, absorbed: dict[str, str],
                           dropped: set[str]) -> tuple[str, int, int]:
    """Point the first member's line at the merged TU; delete the rest.

    Order is preserved EXACTLY: the merged unit occupies the position of its
    first member, and its members were contiguous in this list by construction,
    so nothing that was before a run is now after it.
    """
    rewritten = removed = 0
    out_lines = []
    for line in text.split("\n"):
        m = re.search(r"\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./symbolized/([^\"\s)]+)", line)
        if m is None:
            out_lines.append(line)
            continue
        rel = "recon/symbolized/" + m.group(1)
        if rel in dropped:
            removed += 1
            continue
        if rel in absorbed:
            out_lines.append(line.replace(
                m.group(1), absorbed[rel][len("recon/symbolized/"):]))
            rewritten += 1
            continue
        out_lines.append(line)
    return "\n".join(out_lines), rewritten, removed


# --------------------------------------------------------------------- run
def run(stage, source_root: str, relpaths: list[str]) -> dict:
    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    batch = os.environ.get("G1_STAGE04_BATCH", DEFAULT_BATCH).upper()
    if batch not in BATCHES:
        raise SystemExit("G1_STAGE04_BATCH must be one of %s, got %r"
                         % (sorted(BATCHES), batch))

    # --- the ordered, retained app source list is the ONLY merge candidate set
    cmake = text.get(RETAINED_CMAKE, "")
    order = ["recon/symbolized/" + m.group(1) for m in re.finditer(
        r"\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./symbolized/([^\"\s)]+)", cmake)]
    order = [p for p in order if p.startswith(APP_SRC) and p in text]

    cmake_named = {os.path.basename(m.group(1)) for m in re.finditer(
        r"\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./\.\./symbolized/([^\"\s)]+)",
        text.get(APP_CMAKELISTS, ""))}

    info = {p: analyse(text[p], "g1_%s.h" % os.path.basename(os.path.dirname(p)))
            for p in order}

    # the corpus-wide hazard census is taken BEFORE header folding: it is a
    # statement about what the SOURCES redefine, and folding a shared header's
    # `static inline` helpers into every includer would turn one header into 300
    # fake collisions.
    raw_facts = {p: {k: dict(info[p][k]) for k in ("typedefs", "defines", "statics")}
                 for p in order}

    # fold the facts of every QUOTED repository header, transitively.  The
    # search order is the compiler's: relative to the including file, then along
    # the -I directories the app CMakeLists passes.
    search_dirs = [os.path.join(source_root, d) for d in (
        "recon/application/app/src", "recon/app/src", "recon/headers",
        "recon/symbols", "recon/wiring")]
    hcache: dict[str, dict] = {}
    folded_headers: collections.Counter = collections.Counter()
    unresolved: collections.Counter = collections.Counter()

    def header_facts(hpath: str) -> dict:
        if hpath not in hcache:
            with open(hpath, encoding="utf-8", errors="surrogateescape") as fh:
                hcache[hpath] = analyse(fh.read())
        return hcache[hpath]

    for p in order:
        mh = "g1_%s.h" % os.path.basename(os.path.dirname(p))
        seen: set[str] = set()
        queue = [(os.path.join(source_root, p), s)
                 for s in info[p]["quoted_include_spellings"]]
        while queue:
            frm, spelling = queue.pop()
            if os.path.basename(spelling) == mh:
                continue                       # rule 1 handles it precisely
            rp = resolve_quoted(frm, spelling, search_dirs)
            if rp is None:
                unresolved[spelling] += 1
                continue
            if rp in seen:
                continue
            seen.add(rp)
            h = header_facts(rp)
            fold_header(info[p], h)
            folded_headers[os.path.basename(rp)] += 1
            queue += [(rp, s) for s in h["quoted_include_spellings"]]

    # --- shape quarantine ------------------------------------------------
    shape: dict[str, str] = {}
    for p in order:
        why = shape_refusal(os.path.basename(p), info[p], cmake_named)
        if why:
            shape[p] = why

    # --- order-preserving maximal runs, per module -----------------------
    bymod: dict[str, list[str]] = collections.OrderedDict()
    for p in order:
        bymod.setdefault(os.path.dirname(p), []).append(p)

    # the stage 03 generated module headers are INHERITED artifacts, not
    # manifest inputs, so they must be read from the previous stage's tree.
    mod_header: dict[str, dict[str, set]] = {}
    for mod in bymod:
        slug = os.path.basename(mod)
        hname = "g1_%s.h" % slug
        mod_header[mod] = header_decls(os.path.join(source_root, mod, hname))

    blocked = collections.Counter()
    blocked_detail: dict[str, collections.Counter] = collections.defaultdict(
        collections.Counter)
    runs: list[tuple[str, list[str]]] = []
    for mod, files in bymod.items():
        cur: list[str] = []
        for p in files:
            if p in shape:
                if cur:
                    runs.append((mod, cur))
                cur = []
                runs.append((mod, [p]))
                continue
            ok = True
            for q in cur:
                c = conflicts(info[q], info[p], mod_header.get(mod))
                if c:
                    ok = False
                    for kind, sym in c:
                        blocked[kind] += 1
                        blocked_detail[kind][sym] += 1
                    break
            if ok:
                cur.append(p)
            else:
                runs.append((mod, cur))
                cur = [p]
        if cur:
            runs.append((mod, cur))

    # --- sub-batch selection ---------------------------------------------
    # A and B PARTITION the clean multi-member runs; AB is their union.  The
    # partition itself is identical in every batch -- only the SELECTION differs
    # -- so a side-effect failure localises to one half and the two halves are
    # directly comparable.  The default is B: the R7 gate of 2026-07-27 charged
    # 100 % of stage 04's side-effect regressions to A (module docstring).
    def selected(members: list[str]) -> bool:
        if len(members) < 2 or batch == "OFF":
            return False
        volatile_free = not any(info[m]["has_volatile"] for m in members)
        if batch == "A":
            return volatile_free
        if batch == "B":
            return not volatile_free
        return True

    absorbed: dict[str, str] = {}      # first member -> merged path
    dropped: set[str] = set()
    merged_files: dict[str, str] = {}  # merged path -> body
    per_module: dict[str, dict] = {}
    counter: dict[str, int] = collections.Counter()
    deferred_runs = 0
    for mod, members in runs:
        if not selected(members):
            if len(members) > 1:
                deferred_runs += 1
            continue
        counter[mod] += 1
        path = merged_name(mod, counter[mod])
        merged_files[path] = render(mod, members, text)
        absorbed[members[0]] = path
        dropped.update(members[1:])
        e = per_module.setdefault(mod[len(APP_SRC):], {
            "merged_tus": 0, "files_absorbed": 0, "largest": 0})
        e["merged_tus"] += 1
        e["files_absorbed"] += len(members)
        e["largest"] = max(e["largest"], len(members))

    # --- build machinery, same transaction (C6) --------------------------
    stats: dict = {}
    if RETAINED_CMAKE in text:
        text[RETAINED_CMAKE], rw, rm = rewrite_retained_cmake(
            text[RETAINED_CMAKE], absorbed, dropped)
        stats["retained_cmake_lines_repointed"] = rw
        stats["retained_cmake_lines_removed"] = rm

    # --- emit -------------------------------------------------------------
    for rel in relpaths:
        if rel in dropped or rel in absorbed:
            continue                     # its text now lives in a merged TU
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr = {"content_changed": True} if data != src[rel] else {}
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    # the merged TU is emitted against its FIRST member as the manifest source,
    # so staleness still tracks a real input; every other member is recorded in
    # `merged_members` so nothing is silently dropped from the manifest.
    inverse: dict[str, list[str]] = {}
    for mod, members in runs:
        if members and members[0] in absorbed:
            inverse[absorbed[members[0]]] = members
    # Every absorbed member's own hash is watched through `extra_sources`,
    # otherwise an upstream defect fix landing inside member 7 of a merged TU
    # would never mark this stage stale.
    for path, body in sorted(merged_files.items()):
        members = inverse[path]
        data = body.encode("utf-8", errors="surrogateescape")
        stage.emit(path, data, os.path.join(source_root, members[0]),
                   stagelib.sha256_bytes(src[members[0]]),
                   {"merged_from": members},
                   extra_sources=[(os.path.join(source_root, m),
                                   stagelib.sha256_bytes(src[m]))
                                  for m in members[1:]])

    # --- reports ----------------------------------------------------------
    shape_counts = collections.Counter(shape.values())
    quarantine = {
        "schema": "g1.refactor.stage-quarantine/1",
        "stage": stage.number,
        "sub_batch": batch,
        "shape_refusals": {
            "count": len(shape),
            "by_reason": dict(sorted(shape_counts.items())),
            "files": {os.path.basename(k): v for k, v in sorted(shape.items())},
        },
        "pairwise_refusals": {
            "adjacencies_blocked": sum(blocked.values()),
            "by_rule": dict(sorted(blocked.items())),
            "top_symbols_per_rule": {
                k: dict(v.most_common(25)) for k, v in sorted(blocked_detail.items())},
        },
        "runs_of_length_one": sum(1 for _, m in runs if len(m) == 1),
        "clean_runs_not_selected_by_this_sub_batch": deferred_runs,
    }
    qpath = os.path.join(stage.dir, "QUARANTINE.json")
    check_write(qpath, stage.dir)
    with open(qpath, "w", encoding="utf-8") as fh:
        json.dump(quarantine, fh, indent=1)
        fh.write("\n")

    hz = hazard_census(order, raw_facts)
    hpath = os.path.join(stage.dir, "HAZARDS.json")
    check_write(hpath, stage.dir)
    with open(hpath, "w", encoding="utf-8") as fh:
        json.dump(hz, fh, indent=1)
        fh.write("\n")

    stats.update({
        "sub_batch": batch,
        "merge_candidates": len(order),
        "translation_units_before": len(order),
        "translation_units_after": len(order) - len(dropped),
        "merged_tus": len(merged_files),
        "files_absorbed": len(dropped) + len(absorbed),
        "shape_quarantined": len(shape),
        "quoted_headers_folded": dict(sorted(folded_headers.items())),
        "unresolved_quoted_includes": dict(sorted(unresolved.items())),
        "per_module": dict(sorted(per_module.items())),
        "run_length_histogram": dict(sorted(
            collections.Counter(len(m) for _, m in runs).items())),
    })

    return {
        "report": {
            "sub_batch": batch,
            "translation_units": "%d -> %d" % (len(order), len(order) - len(dropped)),
            "merged_tus": len(merged_files),
            "files_absorbed": len(dropped) + len(absorbed),
            "shape_quarantined": len(shape),
            "adjacencies_blocked": sum(blocked.values()),
            "silent_hazards_found": hz["totals"],
        },
        "manifest_extra": {
            "transform": "scoped cohesive translation-unit merge (app core only)",
            "sub_batches": stats,
            "merged_translation_units": sorted(merged_files),
        },
        "parity_extra": None,
    }


def hazard_census(order: list[str], info: dict[str, dict]) -> dict:
    """The corpus-wide sweep for 'locally redefined, dangerous only when shared'.

    This is reported for the WHOLE retained app set, not only for files this
    stage merged, because it is the class no gate in this project can see and
    it stays dangerous for every future merge attempt.
    """
    td: dict[str, dict[str, list[str]]] = collections.defaultdict(
        lambda: collections.defaultdict(list))
    mc: dict[str, dict[str, list[str]]] = collections.defaultdict(
        lambda: collections.defaultdict(list))
    st: dict[str, list[str]] = collections.defaultdict(list)
    for p in order:
        b = os.path.basename(p)
        for t, body in info[p]["typedefs"].items():
            td[t][body].append(b)
        for m, body in info[p]["defines"].items():
            mc[m][body].append(b)
        for s in info[p]["statics"]:
            st[s].append(b)
    td_conf = {t: {b: v for b, v in bodies.items()}
               for t, bodies in td.items() if len(bodies) > 1}
    mc_conf = {m: {b: v for b, v in bodies.items()}
               for m, bodies in mc.items() if len(bodies) > 1}
    st_conf = {s: v for s, v in st.items() if len(v) > 1}
    return {
        "schema": "g1.refactor.stage-hazards/1",
        "note": "A local typedef/macro redefinition is harmless in its own "
                "translation unit and becomes wrong only when two files share "
                "one.  No gate in this project observes this class; stage 04 "
                "rules 3-5 refuse it structurally.",
        "totals": {
            "typedef_names_with_incompatible_definitions": len(td_conf),
            "macro_names_with_differing_bodies": len(mc_conf),
            "static_names_used_in_more_than_one_file": len(st_conf),
        },
        "incompatible_local_typedefs": td_conf,
        "macros_with_differing_bodies": mc_conf,
        "statics_in_more_than_one_file": st_conf,
    }
