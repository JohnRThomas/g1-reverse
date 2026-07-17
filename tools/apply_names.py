"""Generate agent-readable sources with reversible function/global names.

This is a presentation pass over canonical parity sources.  Function identity
stays keyed by core + address in ``recon/catalogs/function_names_*.json``; every
generated file carries a compact back-map in its header.  Absolute data/global
addresses remain literals here and are handled later by ``symbolize.py``.
"""

import glob
import json
import os
import re
import sys

sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import function_names
import generated_identity


BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCR = ("/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
       "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")
ADDRESS = re.compile(r"0x[0-9a-fA-F]{4,8}")
ENTRY = re.compile(r"@\s+(0x[0-9a-fA-F]+)")
RAW_FUNCTION = re.compile(r"\b(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})\b")


def paths(core):
    if core == "app":
        return (BASE + "/recon/app/src", BASE + "/recon/named",
                SCR + "/symbol_map.json")
    if core == "net":
        return (BASE + "/recon/net/src", BASE + "/recon/net/named",
                SCR + "/symbol_map_net.json")
    raise ValueError("unknown core: %r" % core)


def load_address_symbols(path):
    try:
        with open(path) as stream:
            data = json.load(stream)
    except (OSError, ValueError):
        return {}
    # Current schema is address -> record.  Explicitly reject the obsolete
    # address -> function-name shape that caused the old apply_names.py swap.
    return {int(address, 16): record for address, record in data.items()
            if isinstance(record, dict) and record.get("name")}


def function_backmap(original, core):
    records = function_names.records_by_address(core)
    entries = {}
    for token in function_names.raw_references(original):
        match = RAW_FUNCTION.fullmatch(token)
        address = int(match.group(1), 16) & ~1
        record = records.get(address)
        if record and record.get("human"):
            entries[address] = record
    return entries


def global_backmap(original, address_symbols):
    entries = {}
    for match in ADDRESS.finditer(original):
        address = int(match.group(0), 16)
        record = address_symbols.get(address)
        if record and record.get("name"):
            entries[address] = record
    return entries


def provenance_header(core, entry, public_name, function_entries, globals_):
    raw = function_names.raw_name(core, entry)
    lines = ["/* readable reconstruction; identity: %s @ 0x%08x" % (raw, entry),
             " * public-name: %s" % public_name,
             " * durable-map: recon/catalogs/function_names_%s.json" % core]
    if function_entries:
        lines.append(" * callees (readable <= raw @ address):")
        for address, record in sorted(function_entries.items()):
            lines.append(" *   %-40s <= %-12s @ 0x%08x" %
                         (record["name"], record["raw_name"], address))
    if globals_:
        lines.append(" * address symbols (name @ address):")
        for address, record in sorted(globals_.items()):
            lines.append(" *   %-40s @ 0x%08x" % (record["name"], address))
    lines.append(" */")
    return "\n".join(lines) + "\n"


def main():
    core = sys.argv[1] if len(sys.argv) > 1 else "app"
    source, output, address_map = paths(core)
    records = function_names.records_by_address(core)
    address_symbols = load_address_symbols(address_map)
    os.makedirs(output, exist_ok=True)

    planned = {}
    identities = {}
    renamed = 0
    for path in sorted(glob.glob(source + "/*.c")):
        with open(path) as stream:
            original = stream.read()
        first = original.split("\n", 1)[0]
        match = ENTRY.search(first)
        if not match:
            raw_match = re.fullmatch(r"(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})\.c",
                                     os.path.basename(path))
            if not raw_match:
                raise RuntimeError("missing entry address in %s" % path)
            entry = int(raw_match.group(1), 16) & ~1
        else:
            entry = int(match.group(1), 16) & ~1
        record = records.get(entry)
        public_name = record["name"] if record else function_names.raw_name(core, entry)
        body = function_names.substitute(original, core)
        header = provenance_header(core, entry, public_name,
                                   function_backmap(original, core),
                                   global_backmap(original, address_symbols))
        outname = public_name + ".c"
        rendered = header + body
        rendered = "\n".join(line.rstrip() for line in rendered.splitlines()).rstrip() + "\n"
        generated_identity.add(planned, identities, outname, entry, path, rendered)
        renamed += bool(record and record.get("human"))

    # Do not touch the output tree until every filename and address is known to
    # be unique.  This is the key guard against a stale readable alias silently
    # overwriting the source that actually owns that alias.
    for outname, item in sorted(planned.items()):
        generated_identity.atomic_write(os.path.join(output, outname),
                                        item["rendered"])

    # Remove only stale generated C files.  Non-C notes/assets are untouched.
    for path in glob.glob(output + "/*.c"):
        if os.path.basename(path) not in planned:
            os.unlink(path)
    print("[%s] readable sources: %d | human public names: %d -> %s" %
          (core, len(planned), renamed, output))


if __name__ == "__main__":
    main()
