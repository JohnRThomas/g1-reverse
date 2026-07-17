"""Reversible function-name maps shared by reconstruction tooling.

The parity identity of a function is its core + even entry address.  Human names
are presentation aliases only: this module never uses a readable name as the
primary key.  Maps are committed under ``recon/catalogs`` so a scratchpad wipe
cannot silently return agent prompts to FUN_xxxxxxxx-only decompilation.
"""

import json
import os
import re


BASE = "/Users/freedomcoder/Projects/G1disasm2"
MAP_PATH = {
    "app": BASE + "/recon/catalogs/function_names_app.json",
    "net": BASE + "/recon/catalogs/function_names_net.json",
}

_RAW_TOKEN = re.compile(r"\b(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})\b")
_SKIP = re.compile(
    r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
    re.DOTALL)
_CACHE = {}
_ADDRESS_CACHE = {}


def raw_name(core, address):
    width = 8
    return "FUN_%0*x" % (width, int(address) & ~1)


def load(core):
    """Load and minimally validate the committed address-keyed map."""
    if core not in MAP_PATH:
        raise ValueError("unknown core: %r" % (core,))
    if core in _CACHE:
        return _CACHE[core]
    with open(MAP_PATH[core]) as stream:
        data = json.load(stream)
    if data.get("core") != core or data.get("schema") != 1:
        raise ValueError("invalid function-name map: %s" % MAP_PATH[core])
    _CACHE[core] = data
    return data


def records_by_address(core):
    if core not in _ADDRESS_CACHE:
        _ADDRESS_CACHE[core] = {
            int(address, 16): record
            for address, record in load(core)["by_address"].items()}
    return _ADDRESS_CACHE[core]


def readable_name(core, address):
    address = int(address) & ~1
    record = records_by_address(core).get(address)
    return record.get("name") if record else raw_name(core, address)


def address_for_name(core, name):
    value = load(core).get("by_name", {}).get(name)
    return int(value, 16) if value is not None else None


def substitute(text, core, provenance=False):
    """Replace raw function tokens with unambiguous readable aliases.

    When ``provenance`` is true, append an inline address comment at each
    changed token.  The default is deliberately clean for decompiler text shown
    to reconstruction agents; its caller can provide the map separately.
    """
    records = records_by_address(core)

    def replace(match):
        address = int(match.group(1), 16) & ~1
        record = records.get(address)
        if not record or not record.get("human"):
            return match.group(0)
        name = record["name"]
        if provenance:
            return "%s /*=%s@0x%08x*/" % (name, match.group(0), address)
        return name

    output = []
    position = 0
    for match in _SKIP.finditer(text):
        output.append(_RAW_TOKEN.sub(replace, text[position:match.start()]))
        output.append(match.group(0))
        position = match.end()
    output.append(_RAW_TOKEN.sub(replace, text[position:]))
    return "".join(output)


def raw_references(text):
    """Return raw function references from code, excluding comments/literals."""
    references = []
    position = 0
    for match in _SKIP.finditer(text):
        references.extend(_RAW_TOKEN.finditer(text[position:match.start()]))
        position = match.end()
    references.extend(_RAW_TOKEN.finditer(text[position:]))
    return [item.group(0) for item in references]


def backmap_for_text(text, core):
    """Return readable symbols used by *text* and their stable addresses."""
    data = load(core)
    hits = []
    for name, address in data.get("by_name", {}).items():
        if re.search(r"\b%s\b" % re.escape(name), text):
            record = data["by_address"][address]
            if record.get("human"):
                hits.append({"name": name, "address": address,
                             "raw_name": record["raw_name"]})
    return sorted(hits, key=lambda item: int(item["address"], 16))


def available(core):
    return os.path.exists(MAP_PATH.get(core, ""))
