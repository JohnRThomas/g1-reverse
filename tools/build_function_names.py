"""Build durable, reversible human function-name maps for both firmware cores.

Sources are ranked, never blended by filename order:
  1. names already reviewed into readable/canonical reconstruction headers;
  2. user IDA names from classified.json (app);
  3. semantic Ghidra/catalog names;
  4. the address-derived FUN_xxxxxxxx identity.

Any name used by more than one address is rejected as a human alias rather than
silently suffixing or swapping it.  Output is committed under recon/catalogs.
"""

import collections
import glob
import json
import os
import re
import subprocess
import sys


BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCR = ("/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
       "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")

HEADER = re.compile(
    r"(?:Reconstructed|net-core)\s+([A-Za-z_$][\w$]*)\s+@\s+"
    r"(0x[0-9a-fA-F]+)")
ENTRY = re.compile(r"@\s+(0x[0-9a-fA-F]+)")
VALID_C_NAME = re.compile(r"^[A-Za-z_$][A-Za-z0-9_$]*$")
C_KEYWORDS = set("auto break case char const continue default do double else enum "
                 "extern float for goto if inline int long register restrict return "
                 "short signed sizeof static struct switch typedef union unsigned "
                 "void volatile while _Bool _Complex _Imaginary".split())


def is_human(name):
    return bool(name and not re.match(r"^(?:FUN_|sub_)0*[0-9a-fA-F]+$", name))


def c_name(name):
    if VALID_C_NAME.match(name) and name not in C_KEYWORDS:
        return name
    value = re.sub(r"[^A-Za-z0-9_$]", "_", name)
    if not value or value[0].isdigit() or value in C_KEYWORDS:
        value = "fn_" + value
    return value


def add(candidates, address, name, priority, source):
    if not name:
        return
    address = int(address) & ~1
    candidates[address].append({"name": name, "priority": priority,
                                "source": source, "human": is_human(name)})


def source_headers(core, candidates):
    # Canonical source beats its mirror, user/IDC evidence beats the legacy
    # generated readable tree, and the readable tree is enrichment only.  This
    # ordering is what detects old address/name swaps instead of reviving them.
    roots = ([(BASE + "/recon/app/src", 0),
              (BASE + "/recon/verified/src", 1),
              (BASE + "/recon/named", 20)] if core == "app" else
             [(BASE + "/recon/net/src", 0),
              (BASE + "/recon/net/named", 20)])
    for root, priority in roots:
        for path in sorted(glob.glob(root + "/*.c")):
            with open(path, errors="ignore") as stream:
                # Generated provenance blocks grow as more callees/globals get
                # readable names.  A fixed prefix can end in the middle of the
                # canonical entry address; the address regex would then accept
                # that truncated hexadecimal prefix as a distinct function.
                # Read the complete small source file so a later canonical
                # header is never parsed at an artificial buffer boundary.
                prefix = stream.read()
            match = HEADER.search(prefix)
            if match:
                add(candidates, int(match.group(2), 16), match.group(1),
                    priority, os.path.relpath(path, BASE))
                continue
            # Some reviewed sources use a descriptive leading comment rather
            # than the historical "Reconstructed NAME @ VA" spelling.  Their
            # address still has to exist in the durable map; otherwise a
            # generated tree can contain an identity the reverse map cannot
            # represent.  The raw filename is the safe presentation fallback.
            entry = ENTRY.search(prefix)
            raw_file = re.fullmatch(r"(?:FUN_|sub_)0*([0-9a-fA-F]{3,8})\.c",
                                    os.path.basename(path))
            if entry and raw_file:
                address = int(entry.group(1), 16) & ~1
                add(candidates, address, "FUN_%08x" % address, priority,
                    os.path.relpath(path, BASE))


def durable_names(core, candidates):
    """Seed the build from already-reviewed persistent naming knowledge.

    Scratch catalogs are enrichment, not authority.  In particular, a wiped
    or partially regenerated scratchpad must never turn a committed human name
    back into FUN_xxxxxxxx.  Explicit overrides and reviewed canonical source
    headers retain higher precedence and can deliberately upgrade a record.
    The generated worktree manifest is deliberately not fed back into itself:
    doing so makes a stale collision-rejected record influence the next run.
    """
    relative = "recon/catalogs/function_names_%s.json" % core
    manifests = []
    try:
        committed = subprocess.run(
            ["git", "-C", BASE, "show", "HEAD:" + relative],
            capture_output=True, text=True, check=True)
        manifests.append((json.loads(committed.stdout), 5, "committed durable map"))
    except (subprocess.CalledProcessError, ValueError, OSError):
        pass

    seen = set()
    for manifest, priority, source in manifests:
        for address, record in manifest.get("by_address", {}).items():
            key = (int(address, 16) & ~1, record.get("name"))
            if key in seen:
                continue
            seen.add(key)
            # Preserve every address identity, and most importantly every
            # reviewed human record.  Raw identities remain the lowest-value
            # candidate because add()/selection always prefer a human name.
            add(candidates, key[0], key[1] or record.get("raw_name"),
                priority, source)


def durable_aliases(core):
    """Retain reviewed reverse names without letting them win selection.

    Feeding old aliases back through add() would let a stale human alias beat a
    raw identity.  Keep them out of candidate ranking and merge them only after
    the current owner has been selected.
    """
    relative = "recon/catalogs/function_names_%s.json" % core
    try:
        committed = subprocess.run(
            ["git", "-C", BASE, "show", "HEAD:" + relative],
            capture_output=True, text=True, check=True)
        manifest = json.loads(committed.stdout)
    except (subprocess.CalledProcessError, ValueError, OSError):
        return {}
    return {
        int(address, 16) & ~1: set(record.get("aliases", []))
        for address, record in manifest.get("by_address", {}).items()
    }


def catalog_names(core, candidates):
    path = SCR + "/%s_funcs.json" % core
    with open(path) as stream:
        catalog = json.load(stream)["functions"]
    for function in catalog:
        address = function["entry"]
        add(candidates, address, function.get("name"), 30,
            "%s_funcs.json:name" % core)
        add(candidates, address, function.get("ghidra_name"), 31,
            "%s_funcs.json:ghidra_name" % core)

    if core == "app":
        with open(SCR + "/classified.json") as stream:
            classified = json.load(stream)["functions"]
        for function in classified:
            address = function["entry"]
            add(candidates, address, function.get("ida_name"), 10,
                "classified.json:ida_name")
            add(candidates, address, function.get("name"), 20,
                "classified.json:name")


def build(core):
    candidates = collections.defaultdict(list)
    old_aliases = durable_aliases(core)
    durable_names(core, candidates)
    catalog_names(core, candidates)
    source_headers(core, candidates)
    overrides_path = BASE + "/recon/catalogs/function_name_overrides.json"
    if os.path.exists(overrides_path):
        overrides = json.load(open(overrides_path)).get(core, {})
        for address, record in overrides.items():
            add(candidates, int(address, 16), record["name"], -10,
                "function_name_overrides.json: " + record.get("evidence", "reviewed"))

    chosen = {}
    for address, rows in candidates.items():
        rows.sort(key=lambda row: (not row["human"], row["priority"], row["name"]))
        best = rows[0]
        override = overrides.get("0x%08x" % address, {})
        raw = override.get("raw_name", "FUN_%08x" % address)
        aliases = sorted((old_aliases.get(address, set()) |
                          {row["name"] for row in rows}) - {best["name"]})
        chosen[address] = {
            "address": "0x%08x" % address,
            "raw_name": raw,
            "name": c_name(best["name"]) if best["human"] else raw,
            "display_name": best["name"] if best["human"] else raw,
            "human": bool(best["human"]),
            "source": best["source"],
            "aliases": aliases,
        }

    owners = collections.defaultdict(list)
    for address, record in chosen.items():
        if record["human"]:
            owners[record["name"]].append(address)
    conflicts = {name: addresses for name, addresses in owners.items()
                 if len(addresses) > 1}
    for name, addresses in conflicts.items():
        # Keep a sole highest-confidence owner and reject only stale/lower-rank
        # owners.  A tie is genuinely ambiguous, so all tied owners stay raw.
        ranks = {address: min(row["priority"] for row in candidates[address]
                              if c_name(row["name"]) == name)
                 for address in addresses}
        best_rank = min(ranks.values())
        best = [address for address in addresses if ranks[address] == best_rank]
        rejected = addresses if len(best) != 1 else [address for address in addresses
                                                      if address != best[0]]
        for address in rejected:
            record = chosen[address]
            record["rejected_name"] = name
            record["name"] = record["raw_name"]
            record["human"] = False
            record["source"] = "collision-rejected"

    by_address = {"0x%08x" % address: chosen[address]
                  for address in sorted(chosen)}
    by_name = {record["name"]: address for address, record in by_address.items()}
    data = {
        "schema": 1,
        "core": core,
        "identity": "core + even entry address",
        "by_address": by_address,
        "by_name": dict(sorted(by_name.items())),
        "conflicts": {name: ["0x%08x" % address for address in addresses]
                      for name, addresses in sorted(conflicts.items())},
    }
    out = BASE + "/recon/catalogs/function_names_%s.json" % core
    with open(out, "w") as stream:
        json.dump(data, stream, indent=1, sort_keys=False)
        stream.write("\n")
    human = sum(record["human"] for record in chosen.values())
    print("[%s] %d addresses, %d human names, %d rejected collisions -> %s" %
          (core, len(chosen), human, len(conflicts), out))
    return True


def main():
    cores = sys.argv[1:] or ["app", "net"]
    ok = True
    for core in cores:
        if core not in ("app", "net"):
            raise SystemExit("usage: build_function_names.py [app] [net]")
        ok = build(core) and ok
    raise SystemExit(0 if ok else 2)


if __name__ == "__main__":
    main()
