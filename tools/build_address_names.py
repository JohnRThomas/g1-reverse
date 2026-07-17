"""Recover durable address-symbol back-maps from committed headers/linker pins.

The scratch ``symbol_map*.json`` files are derived data and may disappear.  The
committed symbol headers and PROVIDE fragments retain exact name/address pairs;
this script checks their agreement and stores the result under recon/catalogs.
"""

import collections
import json
import os
import re
import sys


BASE = "/Users/freedomcoder/Projects/G1disasm2"
HEADER_ADDRESS = re.compile(
    r"\b([A-Za-z_$][\w$]*)\s*(?:\[\])?\s*;[^\n]*@\s*(0x[0-9a-fA-F]+)")
DEFINE_ADDRESS = re.compile(
    r"^#define\s+([A-Za-z_$][\w$]*)\s+(0x[0-9a-fA-F]+)(?:UL|U|L)?\b", re.M)
PROVIDE_ADDRESS = re.compile(
    r"PROVIDE\(\s*([A-Za-z_$][\w$]*)\s*=\s*(0x[0-9a-fA-F]+)\s*\)")


def build(core):
    header = BASE + "/recon/symbols/g1_%s_symbols.h" % core
    linker = BASE + "/recon/symbols/g1_%s_globals.ld" % core
    pairs = []
    htext = open(header).read()
    ltext = open(linker).read()
    pairs.extend((name, int(address, 16), "header")
                 for name, address in HEADER_ADDRESS.findall(htext))
    pairs.extend((name, int(address, 16), "header-define")
                 for name, address in DEFINE_ADDRESS.findall(htext))
    pairs.extend((name, int(address, 16), "linker")
                 for name, address in PROVIDE_ADDRESS.findall(ltext))

    by_name_candidates = collections.defaultdict(set)
    by_address_candidates = collections.defaultdict(set)
    evidence = collections.defaultdict(set)
    for name, address, source in pairs:
        by_name_candidates[name].add(address)
        by_address_candidates[address].add(name)
        evidence[(address, name)].add(source)
    linker_by_name = collections.defaultdict(set)
    for name, address in PROVIDE_ADDRESS.findall(ltext):
        linker_by_name[name].add(int(address, 16))
    define_by_name = {name: int(address, 16)
                      for name, address in DEFINE_ADDRESS.findall(htext)}
    bad_names = {name: values for name, values in linker_by_name.items()
                 if len(values) != 1}
    bad_addresses = {address: values for address, values in by_address_candidates.items()
                     if len(values) != 1}
    if bad_names or bad_addresses:
        raise SystemExit("non-bijective %s address symbols: names=%r addresses=%r" %
                         (core, bad_names, bad_addresses))

    by_address = {}
    for address, names in sorted(by_address_candidates.items()):
        name = next(iter(names))
        bases = linker_by_name.get(name)
        if bases:
            base = next(iter(bases))
        elif name in define_by_name:
            base = define_by_name[name]
        elif len(by_name_candidates[name]) == 1:
            base = address
        else:
            raise SystemExit("%s has multiple addresses but no linker base: %s" %
                             (name, sorted(by_name_candidates[name])))
        by_address["0x%08x" % address] = {
            "address": "0x%08x" % address,
            "name": name,
            "base_address": "0x%08x" % base,
            "offset": address - base,
            "evidence": sorted(evidence[(address, name)]),
        }
    by_name = {}
    for name, addresses in by_name_candidates.items():
        if name in linker_by_name:
            base = next(iter(linker_by_name[name]))
        elif name in define_by_name:
            base = define_by_name[name]
        else:
            base = next(iter(addresses))
        by_name[name] = "0x%08x" % base
    data = {"schema": 1, "core": core, "by_address": by_address,
            "by_name": dict(sorted(by_name.items()))}
    out = BASE + "/recon/catalogs/address_names_%s.json" % core
    with open(out, "w") as stream:
        json.dump(data, stream, indent=1)
        stream.write("\n")
    print("[%s] %d durable address names -> %s" % (core, len(by_address), out))


def main():
    cores = sys.argv[1:] or ["app", "net"]
    for core in cores:
        if core not in ("app", "net"):
            raise SystemExit("usage: build_address_names.py [app] [net]")
        build(core)


if __name__ == "__main__":
    main()
