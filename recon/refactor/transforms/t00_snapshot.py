"""Stage 00 -- verbatim snapshot of the compilable input set.

The identity transform.  It exists so that stage 01 has a frozen, hash-pinned
input that does not move underneath it while the concurrent parity agent edits
the live tree, and so that the buildable-root mechanism can be *proved*: the
stage-00 build must produce a ``zephyr.bin`` byte-identical to the in-tree
build.  If it does not, the mechanism is wrong and nothing downstream of it can
be trusted.
"""

from __future__ import annotations

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import stagelib  # noqa: E402


def run(stage, source_root: str, relpaths: list[str]) -> dict:
    copied = 0
    for rel in relpaths:
        src = os.path.join(source_root, rel)
        with open(src, "rb") as fh:
            data = fh.read()
        stage.emit(rel, data, src, stagelib.sha256_bytes(data), {})
        copied += 1
    return {
        "report": {"files_copied": copied, "transformations": 0},
        "manifest_extra": {
            "transform": "identity",
            "transform_note": "verbatim snapshot; every output_sha256 equals its "
                              "source_sha256 by construction",
        },
    }
