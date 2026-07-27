"""Stage 08 -- order a merged unit's functions by call structure (app core).

Stage 05 §7 item 5, and the last of the four things a maintainer would still
object to in a merged unit::

    Functions inside a merged unit are still in LINK order, not call order.
    Reordering them changes `.text' layout, so under §3's rule it is a
    `size-changing' transformation and needs the oracle.  It was not attempted.

That assessment is adopted verbatim, including its conclusion.  This stage is
declared ``size-changing`` **by default and on principle**, not on the strength
of whatever total the build happens to report: reordering moves every function
after the first change point even when the byte total is identical, and the
Stage 04 gate established that it is layout, not size, that re-phases a bus
stream -- the size total is merely the cheapest observable proxy for it.  A
measured ``.text`` delta of 0 would therefore NOT downgrade this stage, and
``driver.py size-gate`` reporting ``byte-identical`` is the only outcome that
could (because then the image is the same bits, and there is nothing to prove).

--------------------------------------------------------------------------
WHAT IT DOES
--------------------------------------------------------------------------

A stage 04 merged unit is a preamble (banner + the unit's include block) and
then one block per absorbed member, each introduced by the one-line banner
stage 05 compressed::

    /* ---- compute_lux_brightness_bucket.c ---- */

The blocks are reordered by a STABLE topological sort of the unit's own call
graph -- callee before caller -- so that a reader meets a helper before the
function that uses it, and every member with no relationship to another keeps
its original relative position.  A cycle (mutual recursion) is left in its
original order: a topological sort of a cyclic graph does not exist, and
inventing one would be choosing arbitrarily and calling it structure.

Every ``identity:`` provenance banner travels inside its own block and is
therefore preserved byte for byte; ``driver.py check-addresses 7 8`` is the
check that it was.

--------------------------------------------------------------------------
WHEN IT REFUSES
--------------------------------------------------------------------------

* **any member block contains a preprocessor directive.**  Moving a block that
  carries a ``#define``, ``#undef``, ``#if`` or a late ``#include`` moves the
  macro state it establishes relative to the code that reads it -- which is the
  one way a pure reordering of file-scope definitions could change meaning
  rather than layout.  Stage 06 hoisted every include it could prove safe, so
  what is left here is exactly the residue stage 06 refused.
* **any member block declares a file-scope ``static``.**  A ``static`` helper
  and its users are order-sensitive in a way a block move can break (C11
  6.2.2p7 again: a ``static`` definition may not follow a non-``static``
  declaration, and after stage 07 there are 137 more of them than there were).
* **the unit's block structure cannot be recovered** -- no member banners, or a
  banner inside a string or comment.
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

BATCHES = frozenset(("R", "OFF"))
DEFAULT_BATCH = "R"

_MEMBER_BANNER = re.compile(r'^/\* ---- (?P<f>[A-Za-z_0-9.\-]+\.(?:c|inc)) ---- \*/$')
_DIRECTIVE = re.compile(r'^[ \t]*#[ \t]*[A-Za-z_]')
_IDENT = re.compile(r'[A-Za-z_]\w*')


def split_members(text: str) -> tuple[list[str], list[tuple[str, list[str]]]]:
    """(preamble lines, [(member name, block lines)])."""
    lines = text.split("\n")
    pre: list[str] = []
    members: list[tuple[str, list[str]]] = []
    cur: list[str] | None = None
    for line in lines:
        m = _MEMBER_BANNER.match(line.strip())
        if m:
            cur = [line]
            members.append((m.group("f"), cur))
            continue
        (cur if cur is not None else pre).append(line)

    # The unit's include block sits INSIDE the first member's block, because
    # stage 04 emits `banner, includes, code' per member and stage 06 hoists
    # into the leading run of blank/comment/include lines -- which begins after
    # the first banner.  Measured the hard way: without this lift every one of
    # the 249 units refused with `member_block_carries_a_preprocessor_directive'
    # and the stage did nothing while reporting success.  The leading directive
    # run of the first block belongs to the UNIT, so it is lifted into the
    # preamble, above the first member banner, which is also where a reader
    # expects it.
    if members:
        name, block = members[0]
        i = 1                                   # keep the banner with the block
        blanked = t4.strip_comments("\n".join(block)).split("\n")
        last = 0
        while i < len(block):
            s = blanked[i].strip()
            if not s:
                i += 1
                continue
            if s.startswith("#") and re.match(r'^[ \t]*#[ \t]*include\b', blanked[i]):
                last = i
                i += 1
                continue
            break
        if last:
            pre.extend(block[1:last + 1])
            members[0] = (name, [block[0]] + block[last + 1:])
    return pre, members


def reorder(text: str) -> tuple[str, dict]:
    pre, members = split_members(text)
    if len(members) < 2:
        return text, {"refused": "fewer_than_two_member_blocks"}

    blocks = ["\n".join(b) for _n, b in members]
    for b in blocks:
        if any(_DIRECTIVE.match(l) for l in t4.strip_comments(b).split("\n")):
            return text, {"refused": "member_block_carries_a_preprocessor_directive"}

    facts = [t4.analyse(b) for b in blocks]
    for f in facts:
        if f["statics"]:
            return text, {"refused": "member_block_declares_a_file_scope_static"}

    owner: dict[str, int] = {}
    for i, f in enumerate(facts):
        for n in f["definitions"]:
            owner.setdefault(n, i)

    # edge callee -> caller, from the identifiers each block mentions
    uses: list[set[int]] = []
    for i, b in enumerate(blocks):
        ids = set(_IDENT.findall(t4.strip_comments(b, drop_strings=True)))
        uses.append({owner[n] for n in ids if n in owner and owner[n] != i})

    indeg = [0] * len(blocks)
    succ: dict[int, list[int]] = collections.defaultdict(list)
    for caller, callees in enumerate(uses):
        for callee in callees:
            succ[callee].append(caller)
            indeg[caller] += 1

    import heapq
    ready = [i for i in range(len(blocks)) if indeg[i] == 0]
    heapq.heapify(ready)
    order: list[int] = []
    while ready:
        i = heapq.heappop(ready)
        order.append(i)
        for j in succ[i]:
            indeg[j] -= 1
            if indeg[j] == 0:
                heapq.heappush(ready, j)
    if len(order) != len(blocks):
        return text, {"refused": "call_graph_has_a_cycle",
                      "members": len(blocks),
                      "ordered": len(order)}
    if order == list(range(len(blocks))):
        return text, {"unchanged": True, "members": len(blocks)}

    moved = sum(1 for k, i in enumerate(order) if k != i)
    out = "\n".join(pre + [blocks[i] for i in order])
    return out, {"members": len(blocks), "blocks_moved": moved}


def run(stage, source_root: str, relpaths: list[str]) -> dict:
    batch = os.environ.get("G1_STAGE08_BATCH", DEFAULT_BATCH).upper()
    if batch not in BATCHES:
        raise SystemExit("G1_STAGE08_BATCH must be one of %s, got %r"
                         % (sorted(BATCHES), batch))

    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    merged = [r for r in relpaths if t5.is_merged_unit(r, text[r])]
    refused: collections.Counter = collections.Counter()
    reordered = 0
    blocks_moved = 0
    unchanged = 0
    per_unit: dict[str, int] = {}
    if batch == "R":
        for rel in merged:
            new, info = reorder(text[rel])
            if "refused" in info:
                refused[info["refused"]] += 1
                continue
            if info.get("unchanged"):
                unchanged += 1
                continue
            text[rel] = new
            reordered += 1
            blocks_moved += info["blocks_moved"]
            per_unit[rel] = info["blocks_moved"]

    changed = 0
    for rel in relpaths:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr: dict = {}
        if data != src[rel]:
            changed += 1
            tr = {"content_changed": True}
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    quarantine = {
        "schema": "g1.refactor.stage-quarantine/1",
        "stage": stage.number,
        "sub_batch": batch,
        "units_refused": dict(refused),
        "note": "Every refusal is a unit whose members could move only by "
                "moving a preprocessor directive or a file-scope `static' with "
                "them, or whose call graph is cyclic.  A refusal leaves the "
                "unit exactly as stage 07 emitted it.",
    }
    qp = os.path.join(stage.dir, "QUARANTINE.json")
    check_write(qp, stage.dir)
    with open(qp, "w", encoding="utf-8") as fh:
        json.dump(quarantine, fh, indent=1)
        fh.write("\n")

    return {
        "report": {
            "sub_batch": batch,
            "files_changed": changed,
            "merged_units_seen": len(merged),
            "units_reordered": reordered,
            "units_already_in_call_order": unchanged,
            "member_blocks_moved": blocks_moved,
            "units_refused": dict(refused),
        },
        "manifest_extra": {
            "transform": "call-order function reordering inside merged units "
                         "(app core only)",
            "sub_batch": batch,
            "call_order": {
                "merged_units_seen": len(merged),
                "units_reordered": reordered,
                "units_already_in_call_order": unchanged,
                "member_blocks_moved": blocks_moved,
                "refused": dict(refused),
                "per_unit_blocks_moved": dict(sorted(per_unit.items())),
            },
        },
        "parity_extra": None,
    }
