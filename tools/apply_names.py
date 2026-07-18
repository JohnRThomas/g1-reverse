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
RECONSTRUCTED_NAME = re.compile(
    r"(?:Reconstructed|net-core)\s+([A-Za-z_$][A-Za-z0-9_$]*)\s+@\s+"
    r"(0x[0-9a-fA-F]+)")


def protect_entry_alias(original, core, entry):
    """Hide an owner's raw back-map alias from readable-name substitution.

    Some canonical parity sources already use a human-readable implementation
    name and export the address identity as a GCC alias, for example::

        extern __typeof(readable) FUN_0100d6e8
            __attribute__((alias("readable")));

    The raw declarator is provenance, not a call/reference.  Replacing it with
    the readable name creates a self-alias and a compile-time redefinition.
    Protect only the exact entry spelling and only inside an alias declaration;
    ordinary raw callees continue through the normal substitution pass.
    """
    raw = function_names.raw_name(core, entry)
    pattern = re.compile(
        r"(?P<prefix>\bextern\s+__typeof\s*\([^;]*?\)\s+)" +
        re.escape(raw) +
        r"(?P<suffix>\s+__attribute__\s*\(\(\s*alias\s*\(\s*"
        r"\"[A-Za-z_$][A-Za-z0-9_$]*\"\s*\)\s*\)\)\s*;)",
        re.DOTALL)
    placeholder = "G1_RAW_ENTRY_ALIAS_%08X" % (int(entry) & ~1)
    protected, count = pattern.subn(
        lambda match: match.group("prefix") + placeholder +
        match.group("suffix"), original)
    return protected, placeholder, raw, count


def retarget_entry_alias(original, core, entry, public_name):
    """Rename a readable implementation selected behind its raw entry alias.

    This handles canonical sources whose leading comment is address-only, so
    ``rename_public_owner`` cannot discover the implementation identifier.  An
    exact raw GCC alias is sufficient identity evidence.  Its target is renamed
    in code and in that declaration's string while comments retain provenance.
    """
    raw = function_names.raw_name(core, entry)
    pattern = re.compile(
        r"(?P<prefix>\bextern\s+__typeof\s*\(\s*)"
        r"(?P<owner>[A-Za-z_$][A-Za-z0-9_$]*)"
        r"(?P<middle>\s*\)\s+)" + re.escape(raw) +
        r"(?P<alias>\s+__attribute__\s*\(\(\s*alias\s*\(\s*\")"
        r"(?P=owner)(?P<suffix>\"\s*\)\s*\)\)\s*;)",
        re.DOTALL)
    matches = list(pattern.finditer(original))
    if not matches:
        return original
    if len(matches) != 1:
        raise RuntimeError("ambiguous entry alias @ 0x%08x" % entry)
    old_name = matches[0].group("owner")
    if old_name == public_name:
        return original

    # Retarget the one proven alias literal before the general token pass;
    # string literals are otherwise immutable.
    def replace_alias(match):
        return (match.group("prefix") + public_name + match.group("middle") +
                raw + match.group("alias") + public_name +
                match.group("suffix"))
    original, count = pattern.subn(replace_alias, original)
    if count != 1:
        raise RuntimeError("entry alias retarget drift @ 0x%08x" % entry)

    # Rename code tokens but retain comments and unrelated literals exactly.
    token = re.compile(r"\b%s\b" % re.escape(old_name))
    skip = re.compile(
        r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
        re.DOTALL)
    output = []
    position = 0
    for match in skip.finditer(original):
        output.append(token.sub(public_name, original[position:match.start()]))
        output.append(match.group(0))
        position = match.end()
    output.append(token.sub(public_name, original[position:]))
    return "".join(output)


def render_named_body(original, core, entry, public_name):
    """Apply readable names while retaining a reversible raw entry alias."""
    original = retarget_entry_alias(original, core, entry, public_name)
    protected, placeholder, raw, alias_count = protect_entry_alias(
        original, core, entry)
    body = function_names.substitute(protected, core)
    body = rename_public_owner(body, entry, public_name)
    if alias_count:
        if body.count(placeholder) != alias_count:
            raise RuntimeError("entry-alias placeholder drift @ 0x%08x" % entry)
        body = body.replace(placeholder, raw)
    return function_names.repair_internal_control_flow_labels(
        body, core, entry)


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


def rename_public_owner(original, entry, public_name):
    """Export the durable public name without changing canonical parity C."""
    matches = [(name, int(address, 16) & ~1)
               for name, address in RECONSTRUCTED_NAME.findall(original[:1024])]
    owners = {name for name, address in matches if address == entry}
    if not owners:
        return original
    if len(owners) != 1:
        raise RuntimeError("ambiguous public owner @ 0x%08x: %s" %
                           (entry, sorted(owners)))
    old_name = next(iter(owners))
    if old_name == public_name:
        return original
    # Only code tokens move; comments and string literals retain the original
    # reconstruction provenance.
    token = re.compile(r"\b%s\b" % re.escape(old_name))
    skip = re.compile(
        r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
        re.DOTALL)
    output = []
    position = 0
    for match in skip.finditer(original):
        output.append(token.sub(public_name, original[position:match.start()]))
        output.append(match.group(0))
        position = match.end()
    output.append(token.sub(public_name, original[position:]))
    return "".join(output)


def provenance_header(core, entry, public_name, function_entries, globals_):
    # A small number of reviewed compiler-generated entries have a historical
    # raw identity such as ``tail_61200`` rather than a synthetic FUN token.
    # Keep that durable back-map in generated headers without changing the
    # address-only fallback used while rebuilding the catalog itself.
    record = function_names.records_by_address(core).get(entry)
    raw = record.get("raw_name") if record else function_names.raw_name(core, entry)
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
        body = render_named_body(original, core, entry, public_name)
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
