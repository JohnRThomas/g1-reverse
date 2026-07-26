"""Write guard for the staged refactor pipeline.

R1: the canonical, byte-verified, address-keyed evidence trees never receive a
refactoring transformation.  ~40 tools and ~50 test files resolve a function as
``os.path.join(<flat dir>, name + ".c")`` inside them; rewriting a body there
silently changes what the whole test corpus MEANS.

This module is the single choke point every writer in ``recon/refactor`` goes
through.  It is deliberately a *path* guard rather than a convention: a
transformer cannot write outside its own stage directory even by accident, and
it can never write into a protected tree at all.

Both properties are unit-tested by ``test_guard.py`` in this directory.
"""

from __future__ import annotations

import os

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
REFACTOR_ROOT = os.path.join(REPO_ROOT, "recon", "refactor")

#: Trees that are EVIDENCE.  Never written, never transformed, never staged as
#: mutable content.  Listed as repo-relative directory prefixes.
PROTECTED_TREES = (
    "recon/app/src",
    "recon/app/src_sym",
    "recon/net/src",
    "recon/verified/src",
    "recon/verified/src_sym",
    "recon/data",
    "recon/net/data",
    "recon/emulator",
    "tools",
)


class WriteGuardError(RuntimeError):
    """Raised when a transformer attempts a write it is not allowed to make."""


def _rel(path: str) -> str:
    return os.path.relpath(os.path.abspath(path), REPO_ROOT).replace(os.sep, "/")


def is_protected(path: str) -> bool:
    """True iff ``path`` lies inside a protected evidence tree."""
    rel = _rel(path)
    for tree in PROTECTED_TREES:
        if rel == tree or rel.startswith(tree + "/"):
            return True
    return False


def check_write(path: str, stage_dir: str) -> str:
    """Authorise a write to ``path`` on behalf of the stage rooted at ``stage_dir``.

    Two independent conditions, both necessary:

    1. ``path`` must not be inside a protected evidence tree (R1);
    2. ``path`` must be inside ``stage_dir`` (R3/R4 - a stage owns exactly its
       own directory, so regenerating a stage cannot damage anything else).

    Returns the absolute path on success; raises ``WriteGuardError`` otherwise.
    """
    ap = os.path.abspath(path)
    if is_protected(ap):
        raise WriteGuardError(
            "refusing to write into protected evidence tree: %s\n"
            "R1: canonical/verified/data/emulator/tools trees are evidence and "
            "never receive refactoring transformations." % _rel(ap)
        )
    sd = os.path.abspath(stage_dir)
    if not (ap == sd or ap.startswith(sd + os.sep)):
        raise WriteGuardError(
            "refusing to write outside the stage directory: %s not under %s"
            % (_rel(ap), _rel(sd))
        )
    return ap


def guarded_write_text(path: str, stage_dir: str, text: str) -> str:
    ap = check_write(path, stage_dir)
    os.makedirs(os.path.dirname(ap), exist_ok=True)
    with open(ap, "w", encoding="utf-8", newline="") as fh:
        fh.write(text)
    return ap


def guarded_write_bytes(path: str, stage_dir: str, data: bytes) -> str:
    ap = check_write(path, stage_dir)
    os.makedirs(os.path.dirname(ap), exist_ok=True)
    with open(ap, "wb") as fh:
        fh.write(data)
    return ap
