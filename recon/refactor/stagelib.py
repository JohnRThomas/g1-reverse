"""Stage materialisation, MANIFEST/PARITY_MAP emission and staleness.

Contract (see README.md):

  stage_00  = verbatim snapshot of the compilable input set
  stage_N   = transformer_N(stage_N-1)          for N >= 1

A stage directory is:

  recon/refactor/stage_NN_<slug>/
    MANIFEST.json      per file: source path, source SHA-256, output SHA-256,
                       transformations applied with site counts
    PARITY_MAP.json    original address <-> canonical name <-> stage file path
                       <-> symbol name   (traceability + integrity, R7)
    tree/              a BUILDABLE root: the transformed files are real files,
                       everything else the build needs is a relative symlink
                       back into the repository

Staleness: a stage is stale iff any input's content hash differs from the hash
recorded in its MANIFEST.  The repair is ALWAYS ``driver.py materialize`` -- a
stage tree is never hand-patched, because reproducibility is what lets a stage
be regenerated when the concurrent parity agent lands a defect fix upstream.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from guard import REPO_ROOT, WriteGuardError, check_write, is_protected  # noqa: E402

REFACTOR_DIR = os.path.join(REPO_ROOT, "recon", "refactor")

_IDENTITY = re.compile(
    r"identity:\s*(?P<raw>[A-Za-z_][A-Za-z_0-9]*)\s*@\s*(?P<va>0x[0-9a-fA-F]+)"
)
_PUBLIC = re.compile(r"^\s*\*\s*public-name:\s*(?P<name>\S+)\s*$", re.M)


def sha256_file(path: str) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 16), b""):
            h.update(chunk)
    return h.hexdigest()


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def stage_dir(number: int, slug: str) -> str:
    return os.path.join(REFACTOR_DIR, "stage_%02d_%s" % (number, slug))


def _relsym(target_abs: str, link_abs: str) -> str:
    return os.path.relpath(target_abs, os.path.dirname(link_abs))


class Stage:
    """One materialised stage."""

    def __init__(self, number: int, slug: str, description: str):
        self.number = number
        self.slug = slug
        self.description = description
        self.dir = stage_dir(number, slug)
        self.tree = os.path.join(self.dir, "tree")
        self.files: dict[str, dict] = {}

    # -- writing -------------------------------------------------------
    def emit(self, relpath: str, data: bytes, source_abs: str,
             source_sha: str, transforms: dict) -> None:
        """Write one materialised file into the stage tree."""
        out = os.path.join(self.tree, relpath)
        check_write(out, self.dir)
        os.makedirs(os.path.dirname(out), exist_ok=True)
        if os.path.islink(out):
            os.unlink(out)
        with open(out, "wb") as fh:
            fh.write(data)
        self.files[relpath] = {
            "source": os.path.relpath(source_abs, REPO_ROOT).replace(os.sep, "/"),
            "source_sha256": source_sha,
            "output_sha256": sha256_bytes(data),
            "bytes": len(data),
            "transformations": transforms,
        }

    # -- manifests -----------------------------------------------------
    def write_manifest(self, extra: dict) -> str:
        doc = {
            "schema": "g1.refactor.stage-manifest/1",
            "stage": self.number,
            "slug": self.slug,
            "description": self.description,
            "input_stage": extra.pop("input_stage", None),
            "generated_by": "recon/refactor/driver.py",
            "reproduce": "PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize %d"
                         % self.number,
            "repair_policy": "A stale or failing stage is REGENERATED, never hand-edited. "
                             "A compile failure in a stage tree is proof the transformer is "
                             "wrong, not a task to hand-fix.",
            "file_count": len(self.files),
            "files": self.files,
        }
        doc.update(extra)
        path = os.path.join(self.dir, "MANIFEST.json")
        check_write(path, self.dir)
        with open(path, "w", encoding="utf-8") as fh:
            json.dump(doc, fh, indent=1, sort_keys=False)
            fh.write("\n")
        return path

    def write_parity_map(self, rows: list[dict], extra: dict | None = None) -> str:
        doc = {
            "schema": "g1.refactor.parity-map/1",
            "stage": self.number,
            "slug": self.slug,
            "purpose": "Traceability and an integrity check, NOT the thing being proven. "
                       "The acceptance bar is observable side-effect equivalence with the "
                       "SHIPPED binaries (R7); this map exists so that when equivalence "
                       "fails, an original address can be walked to the stage file that "
                       "now carries it.",
            "row_count": len(rows),
            "rows": rows,
        }
        if extra:
            doc.update(extra)
        path = os.path.join(self.dir, "PARITY_MAP.json")
        check_write(path, self.dir)
        with open(path, "w", encoding="utf-8") as fh:
            json.dump(doc, fh, indent=1)
            fh.write("\n")
        return path


def parity_rows(tree_root: str, relpaths: list[str]) -> list[dict]:
    """Extract (original address, canonical raw name, stage path, symbol) rows."""
    rows = []
    for rp in relpaths:
        ap = os.path.join(tree_root, rp)
        if not ap.endswith((".c", ".inc")) or not os.path.exists(ap):
            continue
        with open(ap, encoding="utf-8", errors="replace") as fh:
            head = fh.read(4096)
        m = _IDENTITY.search(head)
        if not m:
            continue
        pm = _PUBLIC.search(head)
        rows.append({
            "address": m.group("va").lower(),
            "canonical_name": m.group("raw"),
            "symbol": pm.group("name") if pm else m.group("raw"),
            "stage_path": rp,
        })
    rows.sort(key=lambda r: (r["address"], r["stage_path"]))
    return rows


def load_manifest(number: int, slug: str) -> dict | None:
    p = os.path.join(stage_dir(number, slug), "MANIFEST.json")
    if not os.path.exists(p):
        return None
    with open(p, encoding="utf-8") as fh:
        return json.load(fh)


def staleness(number: int, slug: str) -> dict:
    """A stage is stale iff an input content hash changed."""
    man = load_manifest(number, slug)
    if man is None:
        return {"stage": number, "state": "absent"}
    changed, missing, ok = [], [], 0
    for rel, rec in man["files"].items():
        src = os.path.join(REPO_ROOT, rec["source"])
        if not os.path.exists(src):
            missing.append(rec["source"])
            continue
        if sha256_file(src) != rec["source_sha256"]:
            changed.append(rec["source"])
        else:
            ok += 1
    return {
        "stage": number,
        "slug": slug,
        "state": "stale" if (changed or missing) else "current",
        "inputs_unchanged": ok,
        "inputs_changed": sorted(changed),
        "inputs_missing": sorted(missing),
        "repair": "PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize %d"
                  % number,
    }


def address_set(number: int, slug: str) -> set[str]:
    p = os.path.join(stage_dir(number, slug), "PARITY_MAP.json")
    if not os.path.exists(p):
        return set()
    with open(p, encoding="utf-8") as fh:
        doc = json.load(fh)
    return {r["address"] for r in doc["rows"]}
