"""Symbol -> (tree, file, VA) index over ANY reconstruction tree.

The whole point of this module is that a test binds to a SYMBOL, never to a
path.  The canonical tree is flat and one-function-per-file; the refactored
tree is modular and a single TU can hold up to 39 functions.  Both carry the
same per-function provenance banner, emitted by tools/symbolize.py and
preserved verbatim by every refactor stage:

    /* readable reconstruction; identity: FUN_000868fc @ 0x000868fc
     * public-name: floorf

so the banner -- not the filename, not the directory -- is the identity.  A
merged unit simply carries several banners, and the index records the same TU
for each of its members.

Provenance caveat that matters: the banner's `identity` is the ORIGINAL
firmware VA.  That is what makes a test non-circular, because the expectation
is later derived from the bytes at that VA in the shipped image, not from any
reconstruction.
"""

from __future__ import annotations

import os
import re
from dataclasses import dataclass, field

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.dirname(REPO) if os.path.basename(REPO) == "tools" else REPO

#: One banner.  Kept deliberately loose on the left so a banner that has been
#: re-indented or re-wrapped by a composition stage still matches, and anchored
#: on `identity:` rather than on the start of a line.  Anchoring at end of line
#: has been defeated six times in this repository; this pattern never does it.
_BANNER = re.compile(
    r'identity:\s*(?P<raw>FUN_[0-9a-fA-F]+)\s*@\s*(?P<va>0x[0-9a-fA-F]+)'
    r'(?P<rest>(?:.|\n){0,400}?)', re.MULTILINE)
_PUBLIC = re.compile(r'public-name:\s*(?P<name>[A-Za-z_$][\w$]*)')

#: Include-search order the two CMakeLists actually pass, from
#: recon/refactor/input_set.INCLUDE_SEARCH_DIRS.  Resolved relative to a TREE
#: root so a stage tree compiles against ITS OWN headers, never the repo's.
INCLUDE_SEARCH_DIRS = (
    "recon/application/app/src",
    "recon/application/net/src",
    "recon/app/src",
    "recon/net/src",
    "recon/headers",
    "recon/symbols",
    "recon/wiring",
)


@dataclass
class Unit:
    """One translation unit in one tree."""
    path: str                       # absolute
    rel: str                        # relative to <tree>/recon/symbolized/<core>
    module: str                     # first path component, or "" when flat
    members: list = field(default_factory=list)   # [(symbol, raw, va)]

    @property
    def text(self):
        with open(self.path, errors="replace") as handle:
            return handle.read()

    @property
    def is_single(self):
        return len(self.members) <= 1


@dataclass
class Tree:
    name: str
    root: str                       # absolute path to the tree root
    core: str
    units: dict = field(default_factory=dict)     # rel -> Unit
    by_symbol: dict = field(default_factory=dict)  # symbol -> Unit
    by_va: dict = field(default_factory=dict)      # va -> (symbol, Unit)

    def include_dirs(self):
        out = []
        for rel in INCLUDE_SEARCH_DIRS:
            path = os.path.join(self.root, rel)
            if os.path.isdir(path):
                out.append(path)
        return out

    def unit_for(self, symbol):
        return self.by_symbol.get(symbol)


def _members(text):
    """Every (public_name, raw_name, va) banner in a TU, in file order."""
    out = []
    for match in _BANNER.finditer(text):
        raw = match.group("raw")
        va = int(match.group("va"), 16)
        # The public-name line, when present, is the FIRST one after this
        # banner and before the next one.  Bound the window by the next
        # banner rather than by a line count.
        tail = text[match.end():]
        stop = _BANNER.search(tail)
        window = tail[:stop.start()] if stop else tail
        public = _PUBLIC.search(window)
        name = public.group("name") if public else raw
        out.append((name, raw, va))
    return out


def build(tree_root, core="app", name=None, modules_only=True):
    """Index <tree_root>/recon/symbolized/<core>.

    `modules_only` keeps only files that live under a module DIRECTORY.  A
    stage tree still carries the pre-stage-03 flat files at the top level
    (2,147 of them in stage 09); those are not what the build compiles after
    stage 03 and indexing them would silently shadow the module copies.  The
    canonical/flat tree sets modules_only=False.
    """
    base = os.path.join(tree_root, "recon", "symbolized", core)
    if not os.path.isdir(base):
        raise FileNotFoundError(base)
    tree = Tree(name=name or os.path.basename(tree_root.rstrip("/")),
                root=tree_root, core=core)
    for dirpath, _dirnames, filenames in os.walk(base):
        for filename in sorted(filenames):
            if not filename.endswith(".c"):
                continue
            path = os.path.join(dirpath, filename)
            rel = os.path.relpath(path, base)
            module = rel.split(os.sep)[0] if os.sep in rel else ""
            if modules_only and not module:
                continue
            if not modules_only and module:
                continue
            with open(path, errors="replace") as handle:
                text = handle.read()
            unit = Unit(path=path, rel=rel, module=module,
                        members=_members(text))
            tree.units[rel] = unit
            for symbol, _raw, va in unit.members:
                # A symbol defined in two units is a real defect; record the
                # collision rather than silently keeping the last one.
                previous = tree.by_symbol.get(symbol)
                if previous is not None and previous.rel != rel:
                    tree.by_symbol.setdefault("!dup:" + symbol, previous)
                tree.by_symbol[symbol] = unit
                tree.by_va[va] = (symbol, unit)
    return tree


def default_trees(core="app"):
    """The two trees this harness A/Bs by default.

    A = stage 00, the verbatim snapshot of the compilable input set -- flat,
        one function per file.  This is "the canonical/original tree" as the
        refactor pipeline sees it.
    B = stage 09, the head of the refactor ladder -- modular, merged TUs.
    """
    return {
        "canonical": build(
            os.path.join(REPO, "recon/refactor/stage_00_snapshot/tree"),
            core=core, name="canonical(stage00)", modules_only=False),
        "refactored": build(
            os.path.join(REPO, "recon/refactor/stage_09_call_cohesion/tree"),
            core=core, name="refactored(stage09)", modules_only=True),
    }


if __name__ == "__main__":
    import sys
    core = sys.argv[1] if len(sys.argv) > 1 else "app"
    for label, tree in default_trees(core).items():
        dups = [k for k in tree.by_symbol if k.startswith("!dup:")]
        merged = sum(1 for u in tree.units.values() if not u.is_single)
        print("%-22s units=%5d symbols=%5d merged_units=%4d dup_symbols=%d"
              % (label, len(tree.units),
                 len([k for k in tree.by_symbol if not k.startswith("!dup:")]),
                 merged, len(dups)))
        if dups:
            print("   duplicates:", sorted(d[5:] for d in dups)[:10])
