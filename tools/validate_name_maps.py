"""Fail-closed validation for reversible function and address naming maps."""

import collections
import glob
import json
import keyword
import os
import re
import sys

sys.path.insert(0, "/Users/freedomcoder/Projects/G1disasm2/tools")
import function_names
import generated_identity


BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCR = ("/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
       "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")
ENTRY = re.compile(r"@\s+(0x[0-9a-fA-F]+)")
IDENT = re.compile(r"^[A-Za-z_$][A-Za-z0-9_$]*$")
C_KEYWORDS = set("auto break case char const continue default do double else enum "
                 "extern float for goto if inline int long register restrict return "
                 "short signed sizeof static struct switch typedef union unsigned "
                 "void volatile while _Bool _Complex _Imaginary".split())


def check_function_map(core, errors):
    data = function_names.load(core)
    by_address = data["by_address"]
    by_name = data["by_name"]
    overrides_path = BASE + "/recon/catalogs/function_name_overrides.json"
    overrides = {}
    if os.path.exists(overrides_path):
        overrides = json.load(open(overrides_path)).get(core, {})
    seen = {}
    for address, record in by_address.items():
        value = int(address, 16)
        if record["address"] != address:
            errors.append("%s record address mismatch: %s" % (core, address))
        override = overrides.get(address, {})
        expected_raw = override.get("raw_name", function_names.raw_name(core, value))
        if record["raw_name"] != expected_raw:
            errors.append("%s raw identity mismatch: %s" % (core, address))
        name = record["name"]
        if not IDENT.match(name) or name in C_KEYWORDS or keyword.iskeyword(name):
            errors.append("%s invalid C name %r @ %s" % (core, name, address))
        if name in seen and seen[name] != address:
            errors.append("%s name collision %s: %s/%s" %
                          (core, name, seen[name], address))
        seen[name] = address
        if by_name.get(name) != address:
            errors.append("%s reverse-map mismatch %s @ %s" % (core, name, address))
    if set(by_name) != set(seen):
        errors.append("%s by_name key set differs from by_address" % core)

    source_root = BASE + ("/recon/app/src" if core == "app" else "/recon/net/src")
    owners = collections.defaultdict(list)
    for path in glob.glob(source_root + "/*.c"):
        first = open(path).read(800)
        match = ENTRY.search(first)
        if match:
            owners[int(match.group(1), 16) & ~1].append(os.path.basename(path))
    for address, paths in owners.items():
        if len(paths) > 1:
            errors.append("%s duplicate source entry 0x%08x: %s" %
                          (core, address, ", ".join(sorted(paths))))

    expected = {int(address, 16): record
                for address, record in by_address.items()
                if int(address, 16) in owners}
    roots = ([BASE + "/recon/named", BASE + "/recon/symbolized/app"]
             if core == "app" else
             [BASE + "/recon/net/named", BASE + "/recon/symbolized/net"])
    for root in roots:
        generated = {}
        filenames = {}
        for path in sorted(glob.glob(root + "/*.c")):
            try:
                identity = generated_identity.parse(open(path).read(4096), path)
            except ValueError as exc:
                errors.append(str(exc))
                continue
            address = identity["address"]
            if address in generated:
                errors.append("%s duplicate generated address 0x%08x: %s/%s" %
                              (core, address, generated[address], path))
            generated[address] = path
            filename = os.path.basename(path)
            if filename in filenames:
                errors.append("%s duplicate generated filename %s" % (core, filename))
            filenames[filename] = address
            record = expected.get(address)
            if not record:
                errors.append("%s unexpected generated identity 0x%08x in %s" %
                              (core, address, path))
                continue
            wanted = record["name"] + ".c"
            if filename != wanted or identity["public_name"] != record["name"]:
                errors.append("%s stale generated identity 0x%08x: %s/public %s, wanted %s" %
                              (core, address, filename, identity["public_name"], wanted))
            if identity["raw_name"] != record["raw_name"]:
                errors.append("%s generated raw identity mismatch 0x%08x in %s" %
                              (core, address, path))
        missing = sorted(set(expected) - set(generated))
        extra = sorted(set(generated) - set(expected))
        if missing:
            errors.append("%s generated tree %s missing %d identities (first 0x%08x)" %
                          (core, root, len(missing), missing[0]))
        if extra:
            errors.append("%s generated tree %s has %d extra identities" %
                          (core, root, len(extra)))


def check_address_map(core, errors):
    path = BASE + "/recon/catalogs/address_names_%s.json" % core
    data = json.load(open(path))
    for address, record in data["by_address"].items():
        value = int(address, 16)
        base = int(record["base_address"], 16)
        if value - base != record["offset"]:
            errors.append("%s bad address offset %s" % (core, address))
        if data["by_name"].get(record["name"]) != record["base_address"]:
            errors.append("%s bad address reverse map %s" % (core, record["name"]))

    active = SCR + ("/symbol_map.json" if core == "app" else "/symbol_map_net.json")
    if os.path.exists(active):
        symbols = json.load(open(active))
        owners = collections.defaultdict(set)
        for address, record in symbols.items():
            name = record.get("name")
            if not name or record.get("kind") in ("const", "function_addr"):
                continue
            base = int(record.get("symbol_base", address), 16)
            offset = int(address, 16) - base
            if record.get("symbol_offset", offset) != offset:
                errors.append("%s active offset mismatch %s" % (core, address))
            owners[name].add(base)
        for name, bases in owners.items():
            if len(bases) > 1:
                errors.append("%s symbol %s has multiple bases: %s" %
                              (core, name, sorted(bases)))


def check_lexer(errors):
    sample = ('FUN_000167a8(); /* FUN_000167a8 */ "FUN_000167a8"; '\
              "'FUN_000167a8'; FUN_000167a80();")
    changed = function_names.substitute(sample, "app")
    if "get_device_info();" not in changed:
        errors.append("function lexer did not rewrite code token")
    if "/* FUN_000167a8 */" not in changed or '"FUN_000167a8"' not in changed:
        errors.append("function lexer rewrote comment/string")
    if "FUN_000167a80" not in changed:
        errors.append("function lexer rewrote longer identifier")


def main():
    errors = []
    for core in ("app", "net"):
        check_function_map(core, errors)
        check_address_map(core, errors)
    check_lexer(errors)
    if errors:
        for error in errors:
            print("ERROR:", error)
        raise SystemExit(2)
    print("name maps valid: function/address round-trip, source identity, lexer")


if __name__ == "__main__":
    main()
