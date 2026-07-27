"""Stage 09 -- group translation units by CALL COHESION, not link adjacency.

--------------------------------------------------------------------------
WHY THIS STAGE EXISTS
--------------------------------------------------------------------------

Stage 04 merges maximal runs of **consecutive** sources in the generated source
list.  Stage 08 then measured what that grouping is worth as *structure*: the
249 merged units contain, in total, **11 internal call edges**.  Re-measured on
the live stage 08 tree, the same analyser finds **1,224 intra-module call edges
between DISTINCT retained translation units**.

1,224 against 11.  The call structure is not missing -- 99 % of it falls
between units stage 04 never considered merging, because they are not adjacent
in the generated source list.  A maintainer opening a stage 04 unit finds
functions that share a link position, not a purpose.  That is the gap this
stage closes, and the ratio is what quantifies it.

Specified in `recon/analysis/refactor_consolidated_verdict.md` §11.2.

--------------------------------------------------------------------------
WHAT IT DOES
--------------------------------------------------------------------------

Within ONE module directory, over the retained app source list:

* a **call edge** joins file A and file B when A names an identifier that B
  defines with external linkage (stage 04's own ``analyse()['definitions']``
  over a comment- and string-free view, which is the same edge relation stage
  08 used inside a unit -- so the two measurements are directly comparable);
* candidates are visited in generated-source-list order and placed **first-fit**
  into an existing group of the same module, which is accepted only when
      (a) the candidate has a call edge to at least one member already in the
          group -- so a group is always a connected subgraph of the module's
          call graph, never a bag of unrelated files, and
      (b) ``t04.conflicts`` finds nothing against **every** member already in
          the group, using the same seven refusal rules, unchanged;
* otherwise the candidate opens a new group.

First-fit is a LOWER BOUND on "connected components of the intra-module call
graph": a component whose members pairwise conflict is split into several
groups rather than forced together.  That is the intended direction -- the
refusal rules win over the grouping ambition, never the other way round.

``G1_STAGE09_BATCH`` selects the grouping rule:

    C    (DEFAULT) call cohesion -- condition (a) is required.
    M    module-wide ceiling -- condition (a) is DROPPED, so any pairwise-clean
         files of one module may share a unit.  This is the "no-adjacency
         ceiling" of the verdict's §11.1 measurement.  It absorbs far more, and
         it is NOT the default precisely because what it produces is a module
         bucket, not a cohesive unit: it answers "how much could adjacency cost
         us?" and not "do these functions belong together?".
    OFF  identity transform, for bisecting.

--------------------------------------------------------------------------
SHAPE QUARANTINE
--------------------------------------------------------------------------

Inherited from stage 04, and re-evaluated against the text each file actually
has at this stage rather than carried forward as a list: ``#pragma`` anywhere,
an absolute-path ``#include``, an include of a repository ``.inc`` fragment,
``__attribute__((alias(...)))``, a multi-declaration source line, the file
CMake names by path (``discovery_callback.c``), and the five per-TU
``-ffp-contract`` float bodies.

**Plus ONE rule stage 04 does not have**, added because the first stage 09
build failed on it: a file-scope ``extern`` statement with a comma-separated
declarator list declares several symbols that every refusal rule in this
pipeline is structurally blind to.  See ``multi_declarator_externs`` below --
it is the sixth instance of this project's recurring "textual comparison that
cannot see a semantic difference" defect class, and stage 04 has the same blind
spot on the same 2 files.

--------------------------------------------------------------------------
EMISSION, AND WHAT IT DOES TO LAYOUT
--------------------------------------------------------------------------

A merged unit is emitted at the position of the **earliest** member in the
generated source list, and its members' text is reproduced VERBATIM.  Because
candidates are visited in that order and first-fit always joins an existing
group, the earliest member is the group's first member by construction.

That bounds archive-order disturbance exactly as stage 04 bounds it -- and no
better.  Stage 04's docstring already measured why it is only a bound: the app
sources link as ``app/libapp.a`` and archive members are pulled on demand.
**Unlike stage 04, this stage merges files that were NOT adjacent**, so every
member after the first moves from its own position to the group's position.
The layout disturbance is therefore strictly larger than stage 04's, which is
the honest reason the declaration below cannot be weakened.

The unit name may never match ``rodata_*``: ``g1_verified_rodata_keep.ld``
matches ``KEEP(*rodata_*.c.obj(...))`` on the OBJECT FILENAME (README C6).  The
``g1_`` prefix makes that unrepresentable and ``merged_name`` asserts it.

--------------------------------------------------------------------------
DECLARED CLASS: ``size-changing``, ``oracle_required: true``
--------------------------------------------------------------------------

Not arguable and not measured down.  Stage 04's ``-76 B`` moved the OPT3001
poll train a whole 100.5 ms slot and broke eight navigation fields; this stage
moves more text further.  **No oracle run has been done for it.**  The ladder
beneath it fails R7 at the corrected segmentation (consolidated verdict §9.3),
so stage 09 could not be *proven* in this pass regardless of Renode
availability; what is claimed here is a correct, gated transformer and its
measurements, and nothing about behaviour.

--------------------------------------------------------------------------
WHAT THIS STAGE DELIBERATELY DOES NOT DO
--------------------------------------------------------------------------

It **merges**; it does not **compose**.  Each member keeps its own include
block, so a merged unit can carry an ``#include`` after code -- exactly the
shape stage 04 produced and stage 05 then compressed.  Re-running the stage 05
composition over a stage 09 tree is the natural follow-on and is not part of
this stage: composition is a separate, separately-gated transformation, and
folding it in here would make a single stage both restructure and rewrite,
which is the thing the ladder exists to prevent.
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

from transforms import t04_cohesive_tu as t4  # noqa: E402
from transforms import t05_cohesive_composition as t5  # noqa: E402

APP_SRC = t4.APP_SRC
RETAINED_CMAKE = t4.RETAINED_CMAKE
APP_CMAKELISTS = t4.APP_CMAKELISTS

#: ``G1_STAGE09_BATCH`` values; see the module docstring.
BATCHES = frozenset(("C", "M", "OFF"))
DEFAULT_BATCH = "C"

_MOD_SLUG = re.compile(r"[^A-Za-z0-9]+")


def _blank_groups(s: str) -> str:
    """Length-preserving blanking of every ``(...)``/``[...]``/``{...}`` group.

    What survives is the declarator list's own top-level punctuation, so a
    comma inside a parameter list or an array bound cannot be mistaken for a
    declarator separator.
    """
    out = list(s)
    depth = 0
    for i, ch in enumerate(s):
        if ch in "([{":
            depth += 1
            out[i] = " "
        elif ch in ")]}":
            depth = max(0, depth - 1)
            out[i] = " "
        elif depth > 0 and ch != "\n":
            out[i] = " "
    return "".join(out)


def multi_declarator_externs(text: str) -> list[str]:
    """File-scope ``extern`` statements that declare MORE THAN ONE symbol.

    THE SIXTH INSTANCE OF THIS PROJECT'S RECURRING DEFECT CLASS -- "a textual
    comparison that cannot see a semantic difference" -- and it was found by a
    stage 09 compile failure, not predicted.

    Stage 04 already has a shape rule whose stated intent is exactly this:
    a multi-declaration source line makes its declarations' types UNKNOWN to
    the safety rules, and an unknown type cannot be proven not to collide.  Its
    implementation is ``line.count(";") > 1 or line.count("extern") > 1``, which
    reads a comma-separated declarator list as ONE declaration::

        extern void update_box_presence_flag(void*,void*),
                    init_config_fields_default9(void*),
                    k_sleep(int,int),
                    st25dv_build_and_write_ndef_records(void*,void*,void*),
                    set_time_mark(void);

    One ``;``, one ``extern``, FIVE declarations -- and ``t03._decl_symbol``
    returns the identifier before the FIRST ``(``, so rules 1 and 2 see only
    ``update_box_presence_flag``.  The declaration of ``k_sleep(int,int)`` is
    invisible to every refusal rule in the pipeline.  Stage 09 grouped that file
    with a member declaring ``extern int32_t k_sleep(k_timeout_t);`` and GCC
    rejected it: ``conflicting types for 'k_sleep'``.

    This function is the fail-closed repair: a file carrying such a statement is
    shape-quarantined, restoring the rule's intent rather than extending its
    reach.  Decomposing the list into one canonical declaration per declarator
    would be strictly better -- the rules would then SEE the types instead of
    refusing to look -- and is deliberately not attempted here, because
    ``_decl_symbol`` misreads a function-pointer declarator (``extern int
    (*f)(void), g;`` yields ``int``) and a decomposition that is wrong is worse
    than a refusal that is total.  MEASURED COST OF REFUSING: **2 files of the
    742 retained** at stage 08, and the same 2 of 1,615 at stage 03.
    """
    code = t4.strip_comments(text)
    nostr = t4.strip_comments(text, drop_strings=True)
    depth = t4._depths(nostr)
    out: list[str] = []
    for m in re.finditer(r"\bextern\b", nostr):
        if depth[m.start()] != 0:
            continue
        j = nostr.find(";", m.end())
        if j < 0:
            continue
        stmt = code[m.start():j + 1]
        if "," in _blank_groups(stmt):
            out.append(re.sub(r"\s+", " ", stmt).strip())
    return out


def shape_refusal(base: str, d: dict, text: str, cmake_named: set[str]) -> str | None:
    """Stage 04's shape quarantine, plus the multi-declarator repair above."""
    why = t4.shape_refusal(base, d, cmake_named)
    if why:
        return why
    if multi_declarator_externs(text):
        return "multi_declarator_extern_statement_types_unknown"
    return None


def merged_name(module_dir: str, index: int) -> str:
    """Path of a stage 09 merged unit.

    The ``_cc`` infix keeps stage 09's units in a namespace disjoint from stage
    04's ``g1_<slug>_NN.c``, so a stage 09 unit can never silently take the
    name of a stage 04 unit that still exists in the same directory.
    """
    slug = _MOD_SLUG.sub("_", module_dir[len(APP_SRC):]).strip("_")
    name = "g1_%s_cc%02d.c" % (slug, index)
    assert not name.startswith("rodata_"), name          # README C6
    return "%s%s/%s" % (APP_SRC, module_dir[len(APP_SRC):], name)


def call_graph(order: list[str], info: dict[str, dict], text: dict[str, str]
               ) -> tuple[set[tuple[str, str]], dict[str, set[str]]]:
    """Directed intra-module call edges, and the undirected adjacency.

    ``(A, B)`` is an edge when A names an identifier B **defines**.  Only the
    first definer of a name is credited, which matters not at all in a corpus
    with zero duplicate external definitions (rule 2 would refuse them anyway)
    and keeps the relation a function.
    """
    owner: dict[str, str] = {}
    for p in order:
        for n in info[p]["definitions"]:
            owner.setdefault(n, p)
    edges: set[tuple[str, str]] = set()
    adj: dict[str, set[str]] = collections.defaultdict(set)
    for p in order:
        mod = os.path.dirname(p)
        ids = set(t4._IDENT.findall(t4.strip_comments(text[p], drop_strings=True)))
        for n in ids:
            q = owner.get(n)
            if q is None or q == p or os.path.dirname(q) != mod:
                continue
            edges.add((p, q))
            adj[p].add(q)
            adj[q].add(p)
    return edges, adj


def group_module(files: list[str], info: dict[str, dict],
                 adj: dict[str, set[str]], hdr: dict[str, set] | None,
                 require_edge: bool,
                 blocked: collections.Counter | None = None,
                 blocked_detail: dict | None = None,
                 no_edge: list | None = None) -> list[list[str]]:
    """First-fit greedy grouping of ONE module's candidates, in link order."""
    groups: list[list[str]] = []
    for p in files:
        placed = False
        for g in groups:
            if require_edge and not any(m in adj[p] for m in g):
                if no_edge is not None:
                    no_edge.append((p, g[0]))
                continue
            c: list[tuple[str, str]] = []
            for m in g:
                c = t4.conflicts(info[m], info[p], hdr)
                if c:
                    break
            if c:
                if blocked is not None:
                    for kind, sym in c:
                        blocked[kind] += 1
                        if blocked_detail is not None:
                            blocked_detail[kind][sym] += 1
                continue
            g.append(p)
            placed = True
            break
        if not placed:
            groups.append([p])
    return groups


def render(module_dir: str, members: list[str], text: dict[str, str],
           edges: set[tuple[str, str]]) -> str:
    """Concatenate members VERBATIM under one banner."""
    mod = module_dir[len(APP_SRC):]
    ms = set(members)
    internal = sorted((os.path.basename(a), os.path.basename(b))
                      for a, b in edges if a in ms and b in ms)
    head = [
        "/*",
        " * Call-cohesive translation unit for the `%s' module." % mod,
        " *",
        " * GENERATED by recon/refactor/transforms/t09_call_cohesion.py.  Do",
        " * not edit: a stage tree is regenerated, never hand-patched",
        " * (recon/refactor/README.md C4).",
        " *",
        " * The %d translation units below were grouped because they CALL ONE" % len(members),
        " * ANOTHER, not because they were adjacent in the generated source",
        " * list.  Each member's text is reproduced VERBATIM.  Every member was",
        " * checked pairwise against every other member already in this unit by",
        " * stage 04's seven refusal rules, unchanged: no symbol is declared",
        " * here with two types, no identifier has internal linkage in one",
        " * member and is named by another, and no local typedef, macro, struct",
        " * tag or enum constant of one member is visible to a member that",
        " * names it.",
        " *",
        " * members, in generated-source-list order:",
    ]
    for m in members:
        head.append(" *   %s" % os.path.basename(m))
    head += [" *",
             " * call edges inside this unit (caller -> callee): %d" % len(internal)]
    for a, b in internal:
        head.append(" *   %s -> %s" % (a, b))
    head += [" */", ""]
    fwd = t4.incomplete_tag_forwards([text[m] for m in members])
    if fwd:
        head += [
            "/* File-scope forward declarations for every struct/union tag this",
            " * unit names.  Without them a tag whose only appearance in a member",
            " * is inside a parameter list has PARAMETER-LIST scope, so two",
            " * textually IDENTICAL declarations in two members declare two",
            " * different incomplete types and the second is a conflicting",
            " * redeclaration (C11 6.2.1p7).  Incomplete-type forward",
            " * declarations emit no code. */",
        ] + fwd + [""]
    body = []
    for m in members:
        body.append("/* ================================================================ */")
        body.append("/* member unit: %s */" % os.path.basename(m))
        body.append("/* ================================================================ */")
        body.append(text[m].rstrip("\n"))
        body.append("")
    return "\n".join(head) + "\n".join(body) + "\n"


# --------------------------------------------------------------------- run
def run(stage, source_root: str, relpaths: list[str]) -> dict:
    batch = os.environ.get("G1_STAGE09_BATCH", DEFAULT_BATCH).upper()
    if batch not in BATCHES:
        raise SystemExit("G1_STAGE09_BATCH must be one of %s, got %r"
                         % (sorted(BATCHES), batch))

    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    cmake = text.get(RETAINED_CMAKE, "")
    order = ["recon/symbolized/" + m.group(1) for m in re.finditer(
        r"\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./symbolized/([^\"\s)]+)", cmake)]
    order = [p for p in order if p.startswith(APP_SRC) and p in text]

    cmake_named = {os.path.basename(m.group(1)) for m in re.finditer(
        r"\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./\.\./symbolized/([^\"\s)]+)",
        text.get(APP_CMAKELISTS, ""))}

    info = {p: t4.analyse(text[p], "g1_%s.h" % os.path.basename(os.path.dirname(p)))
            for p in order}

    # fold the facts of every QUOTED repository header, transitively -- the
    # compiler's own search order, exactly as stage 04 does it.
    search_dirs = [os.path.join(source_root, d) for d in (
        "recon/application/app/src", "recon/app/src", "recon/headers",
        "recon/symbols", "recon/wiring")]
    hcache: dict[str, dict] = {}
    folded_headers: collections.Counter = collections.Counter()
    unresolved: collections.Counter = collections.Counter()

    def header_facts(hpath: str) -> dict:
        if hpath not in hcache:
            with open(hpath, encoding="utf-8", errors="surrogateescape") as fh:
                hcache[hpath] = t4.analyse(fh.read())
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
            rp = t4.resolve_quoted(frm, spelling, search_dirs)
            if rp is None:
                unresolved[spelling] += 1
                continue
            if rp in seen:
                continue
            seen.add(rp)
            h = header_facts(rp)
            t4.fold_header(info[p], h)
            folded_headers[os.path.basename(rp)] += 1
            queue += [(rp, s) for s in h["quoted_include_spellings"]]

    # --- the call graph, over the SAME candidate set --------------------
    edges, adj = call_graph(order, info, text)

    # --- shape quarantine ------------------------------------------------
    shape: dict[str, str] = {}
    for p in order:
        why = shape_refusal(os.path.basename(p), info[p], text[p], cmake_named)
        if why:
            shape[p] = why

    bymod: dict[str, list[str]] = collections.OrderedDict()
    for p in order:
        bymod.setdefault(os.path.dirname(p), []).append(p)

    mod_header: dict[str, dict[str, set]] = {}
    for mod in bymod:
        hname = "g1_%s.h" % os.path.basename(mod)
        mod_header[mod] = t4.header_decls(os.path.join(source_root, mod, hname))

    blocked: collections.Counter = collections.Counter()
    blocked_detail: dict[str, collections.Counter] = collections.defaultdict(
        collections.Counter)
    no_edge_pairs: list = []
    groups: list[tuple[str, list[str]]] = []
    for mod, files in bymod.items():
        cand = [p for p in files if p not in shape]
        for g in group_module(cand, info, adj, mod_header.get(mod),
                              require_edge=(batch == "C"),
                              blocked=blocked, blocked_detail=blocked_detail,
                              no_edge=no_edge_pairs if batch == "C" else None):
            groups.append((mod, g))

    # --- emit -------------------------------------------------------------
    absorbed: dict[str, str] = {}      # first member -> merged path
    dropped: set[str] = set()
    merged_files: dict[str, str] = {}
    per_module: dict[str, dict] = {}
    counter: collections.Counter = collections.Counter()
    inverse: dict[str, list[str]] = {}
    if batch != "OFF":
        for mod, members in groups:
            if len(members) < 2:
                continue
            counter[mod] += 1
            path = merged_name(mod, counter[mod])
            merged_files[path] = render(mod, members, text, edges)
            absorbed[members[0]] = path
            dropped.update(members[1:])
            inverse[path] = members
            e = per_module.setdefault(mod[len(APP_SRC):], {
                "merged_units": 0, "units_absorbed": 0, "largest": 0})
            e["merged_units"] += 1
            e["units_absorbed"] += len(members)
            e["largest"] = max(e["largest"], len(members))

    stats: dict = {}
    if RETAINED_CMAKE in text:
        text[RETAINED_CMAKE], rw, rm = t4.rewrite_retained_cmake(
            text[RETAINED_CMAKE], absorbed, dropped)
        stats["retained_cmake_lines_repointed"] = rw
        stats["retained_cmake_lines_removed"] = rm

    for rel in relpaths:
        if rel in dropped or rel in absorbed:
            continue                     # its text now lives in a merged unit
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr = {"content_changed": True} if data != src[rel] else {}
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

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
    merged_before = [p for p in order if t5.is_merged_unit(p, text[p])]
    unit_of: dict[str, str] = {}
    for path, members in inverse.items():
        for m in members:
            unit_of[m] = path
    internal_after = sum(1 for a, b in edges
                         if unit_of.get(a) is not None
                         and unit_of.get(a) == unit_of.get(b))

    quarantine = {
        "schema": "g1.refactor.stage-quarantine/1",
        "stage": stage.number,
        "sub_batch": batch,
        "shape_refusals": {
            "count": len(shape),
            "by_reason": dict(sorted(collections.Counter(shape.values()).items())),
            "files": {os.path.basename(k): v for k, v in sorted(shape.items())},
        },
        "pairwise_refusals": {
            "placements_blocked": sum(blocked.values()),
            "by_rule": dict(sorted(blocked.items())),
            "top_symbols_per_rule": {
                k: dict(v.most_common(25)) for k, v in sorted(blocked_detail.items())},
        },
        "no_call_edge_refusals": len(no_edge_pairs),
        "groups_of_length_one": sum(1 for _m, g in groups if len(g) == 1),
        "note": "A group of length one is a translation unit this stage left "
                "exactly as stage 08 emitted it.  `no_call_edge_refusals' counts "
                "candidate/group pairs skipped for want of a call edge, which is "
                "the measurement of what sub-batch M would additionally absorb.",
    }
    qpath = os.path.join(stage.dir, "QUARANTINE.json")
    check_write(qpath, stage.dir)
    with open(qpath, "w", encoding="utf-8") as fh:
        json.dump(quarantine, fh, indent=1)
        fh.write("\n")

    stats.update({
        "sub_batch": batch,
        "merge_candidates": len(order),
        "translation_units_before": len(order),
        "translation_units_after": len(order) - len(dropped),
        "merged_units": len(merged_files),
        "units_absorbed": len(dropped) + len(absorbed),
        "shape_quarantined": len(shape),
        "stage_04_merged_units_in_input": len(merged_before),
        "single_source_units_in_input": len(order) - len(merged_before),
        "intra_module_call_edges": len(edges),
        "call_edges_inside_a_stage_09_unit": internal_after,
        "quoted_headers_folded": dict(sorted(folded_headers.items())),
        "unresolved_quoted_includes": dict(sorted(unresolved.items())),
        "per_module": dict(sorted(per_module.items())),
        "group_size_histogram": dict(sorted(
            collections.Counter(len(g) for _m, g in groups).items())),
    })

    return {
        "report": {
            "sub_batch": batch,
            "translation_units": "%d -> %d" % (len(order), len(order) - len(dropped)),
            "merged_units": len(merged_files),
            "units_absorbed": len(dropped) + len(absorbed),
            "shape_quarantined": len(shape),
            "intra_module_call_edges": len(edges),
            "call_edges_now_inside_one_unit": internal_after,
            "placements_blocked": sum(blocked.values()),
        },
        "manifest_extra": {
            "transform": "call-cohesion translation-unit grouping (app core only)",
            "sub_batches": stats,
            "merged_translation_units": sorted(merged_files),
        },
        "parity_extra": None,
    }
