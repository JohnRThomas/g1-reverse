#!/usr/bin/env python3
"""Validate readable CPUNET back-maps and generate their linker aliases."""

import json
import os
import re
import sys


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CATALOG = os.path.join(ROOT, "recon/catalogs/net_readable_alias_resolutions.json")
NAMES = os.path.join(ROOT, "recon/catalogs/function_names_net.json")
MANIFEST = os.path.join(ROOT, "recon/ownership/adoption_manifest.json")
SOURCE = os.path.join(ROOT, "recon/net/src")
OUTPUT = os.path.join(ROOT, "recon/symbols/g1_net_readable_aliases.ld")
MARKDOWN = os.path.join(ROOT, "recon/catalogs/net_readable_alias_resolutions.md")
IDENT = re.compile(r"^[A-Za-z_$][A-Za-z0-9_$]*$")


def load():
    with open(CATALOG) as stream:
        catalog = json.load(stream)
    with open(NAMES) as stream:
        names = json.load(stream)["by_address"]
    with open(MANIFEST) as stream:
        manifest_data = json.load(stream)
    manifest = {
        row["va"].lower(): row
        for row in manifest_data["cores"]["net"]["entries"]
    }
    return catalog, names, manifest


def canonical_backmaps(symbol, va):
    raw = "FUN_%08x" % int(va, 16)
    matches = []
    for filename in sorted(os.listdir(SOURCE)):
        if not filename.endswith(".c"):
            continue
        path = os.path.join(SOURCE, filename)
        with open(path, errors="replace") as stream:
            text = stream.read()
        if re.search(r"\b%s\s*\(" % re.escape(symbol), text) and raw in text:
            matches.append(os.path.relpath(path, ROOT))
    return matches


def validate():
    catalog, names, manifest = load()
    seen = set()
    for row in catalog["retained_aliases"]:
        symbol, target, va = row["symbol"], row["target"], row["va"].lower()
        if not IDENT.fullmatch(symbol) or not IDENT.fullmatch(target):
            raise ValueError("invalid alias identifier: %r" % row)
        if symbol in seen:
            raise ValueError("duplicate readable alias: %s" % symbol)
        seen.add(symbol)
        identity = names.get(va)
        if not identity:
            raise ValueError("alias VA absent from function map: %s" % va)
        raw = identity["raw_name"]
        if target not in (raw, identity["name"]):
            raise ValueError("alias target does not own %s: %s" % (va, target))
        source = os.path.join(ROOT, "recon/symbolized/net", identity["name"] + ".c")
        if not os.path.isfile(source):
            raise ValueError("retained alias target source missing: %s" % source)
        if not canonical_backmaps(symbol, va):
            raise ValueError("canonical readable back-map missing: %s -> %s" %
                             (symbol, va))

    for row in catalog["sdk_owners"]:
        symbol, va = row["symbol"], row["va"].lower()
        if symbol in seen:
            raise ValueError("symbol has multiple resolution classes: %s" % symbol)
        seen.add(symbol)
        owner = manifest.get(va)
        if not owner or not owner.get("exclude_reconstruction"):
            raise ValueError("SDK owner is not manifest-approved: %s" % symbol)
        if owner.get("upstream_symbol") != row["upstream_symbol"]:
            raise ValueError("SDK owner drift for %s" % symbol)
        if not canonical_backmaps(symbol, va):
            raise ValueError("canonical SDK back-map missing: %s -> %s" %
                             (symbol, va))

    for row in catalog["unresolved"]:
        if row["symbol"] in seen:
            raise ValueError("resolved symbol also marked unresolved: %s" % row["symbol"])
        seen.add(row["symbol"])
        if not canonical_backmaps(row["symbol"], row["va"]):
            raise ValueError("unresolved back-map missing: %s" % row["symbol"])
    return catalog


def render(catalog):
    lines = [
        "/* Generated from net_readable_alias_resolutions.json.",
        " * Every alias has a canonical raw-VA back-map and retained target. */",
    ]
    for row in sorted(catalog["retained_aliases"], key=lambda item: item["symbol"]):
        lines.append("PROVIDE(%s = %s); /* %s */" %
                     (row["symbol"], row["target"], row["va"]))
    return "\n".join(lines) + "\n"


def render_markdown(catalog):
    lines = [
        "# CPUNET readable alias resolutions", "",
        "Every retained alias below is backed by a canonical declaration that",
        "preserves its raw firmware VA. SDK owners require an existing manifest",
        "exclusion; the private controller row remains report-only.", "",
        "## Retained-body aliases", "", "| Symbol | Target | VA |",
        "|---|---|---:|",
    ]
    for row in catalog["retained_aliases"]:
        lines.append("| `%s` | `%s` | %s |" %
                     (row["symbol"], row["target"], row["va"]))
    lines.extend(["", "## Manifest-approved SDK owners", "",
                  "| Readable spelling | Upstream owner | VA |", "|---|---|---:|"])
    for row in catalog["sdk_owners"]:
        lines.append("| `%s` | `%s` | %s |" %
                     (row["symbol"], row["upstream_symbol"], row["va"]))
    lines.extend(["", "## Deliberately unresolved", "",
                  "| Symbol | VA | Reason |", "|---|---:|---|"])
    for row in catalog["unresolved"]:
        lines.append("| `%s` | %s | %s |" %
                     (row["symbol"], row["va"], row["reason"]))
    return "\n".join(lines) + "\n"


def main(argv=None):
    argv = argv or sys.argv[1:]
    check = argv == ["--check"]
    if argv not in ([], ["--check"]):
        raise SystemExit("usage: build_net_readable_alias_resolutions.py [--check]")
    catalog = validate()
    content = render(catalog)
    markdown = render_markdown(catalog)
    with open(OUTPUT) as stream:
        old = stream.read()
    old_markdown = None
    if os.path.exists(MARKDOWN):
        with open(MARKDOWN) as stream:
            old_markdown = stream.read()
    if check:
        if old != content or old_markdown != markdown:
            raise SystemExit("net readable alias artifacts are stale")
        print("net readable alias catalog and fragment: valid")
    else:
        with open(OUTPUT, "w") as stream:
            stream.write(content)
        with open(MARKDOWN, "w") as stream:
            stream.write(markdown)
        print("generated %d net readable aliases -> %s" %
              (content.count("PROVIDE("), OUTPUT))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
