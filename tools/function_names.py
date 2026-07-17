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
_ALIAS_CACHE = {}


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


def records_by_alias(core):
    """Return only bijective historical identifier -> address records.

    Some canonical files predate the address-keyed readable map and export a
    Ghidra thunk spelling (for example ``thunk_FUN_01025034``) rather than the
    raw entry spelling.  Those spellings live in each record's reversible
    ``aliases`` array.  They must be treated exactly like raw FUN names during
    presentation generation, but only when the mapping is one-to-one.  An
    ambiguous spelling is deliberately omitted, so it stays visible in the
    generated source for an explicit identity repair instead of being guessed.
    """
    if core not in _ALIAS_CACHE:
        candidates = {}
        for record in records_by_address(core).values():
            for alias in record.get("aliases", []):
                candidates.setdefault(alias, []).append(record)
        _ALIAS_CACHE[core] = {
            alias: records[0] for alias, records in candidates.items()
            if len({record["address"] for record in records}) == 1
        }
    return _ALIAS_CACHE[core]


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
    aliases = records_by_alias(core)
    alias_pattern = (re.compile(r"\b(?:%s)\b" % "|".join(
        re.escape(alias) for alias in sorted(aliases, key=len, reverse=True)))
        if aliases else None)

    def replace(match):
        address = int(match.group(1), 16) & ~1
        record = records.get(address)
        if not record or not record.get("human"):
            return match.group(0)
        name = record["name"]
        if provenance:
            return "%s /*=%s@0x%08x*/" % (name, match.group(0), address)
        return name

    def replace_alias(match):
        record = aliases[match.group(0)]
        if not record.get("human"):
            return match.group(0)
        name = record["name"]
        if provenance:
            return "%s /*=%s@%s*/" % (name, match.group(0),
                                       record["address"])
        return name

    def replace_segment(segment):
        segment = _RAW_TOKEN.sub(replace, segment)
        return alias_pattern.sub(replace_alias, segment) if alias_pattern else segment

    output = []
    position = 0
    for match in _SKIP.finditer(text):
        output.append(replace_segment(text[position:match.start()]))
        output.append(match.group(0))
        position = match.end()
    output.append(replace_segment(text[position:]))
    return "".join(output)


def repair_internal_control_flow_labels(text, core, entry):
    """Materialize verified interior labels locally in presentation sources.

    The parity source for the controller setter models two branches beyond its
    catalogued CFG extent as external oracles.  Original Thumb decoding proves
    that both targets are instruction boundaries inside the same owner and set
    fixed return codes before the owner's epilogue.  A cohesive C build must
    not expose those labels as global functions.  Keep the parity source
    unchanged and close them locally in the generated readable tree.

    This is intentionally fail-closed: source drift must stop regeneration
    instead of silently leaving either pseudo-function unresolved.
    """
    if core != "net" or int(entry) != 0x01008E74:
        return text
    declarations = (
        "extern int FUN_01008fc0(void);\n"
        "extern int FUN_01008fc6(void);"
    )
    if text.count(declarations) != 1:
        raise ValueError("FUN_01008e74 interior-label declarations drifted")
    definitions = (
        "/* Original interior labels: 0x01008fc0 => -45, "
        "0x01008fc6 => -12. */\n"
        "static int FUN_01008fc0(void) { return -45; }\n"
        "static int FUN_01008fc6(void) { return -12; }"
    )
    repaired = text.replace(declarations, definitions)
    for symbol in ("FUN_01008fc0", "FUN_01008fc6"):
        if repaired.count("extern int %s" % symbol):
            raise ValueError("interior label remained external: %s" % symbol)
    return repaired


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
