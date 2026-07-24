#!/usr/bin/env python3
"""Post-process Renode PC execution traces into per-core function-entry events.
Trace line index == cpu.ExecutedInstructions index (0-based)."""
import json, sys, bisect

REPO = "/Users/freedomcoder/Projects/G1disasm2"

def load_app():
    d = json.load(open(f"{REPO}/recon/catalogs/function_names_app.json"))
    pairs = []
    for k, v in d["by_address"].items():
        a = int(v["address"], 16)
        pairs.append((a, v["name"]))
    pairs.sort()
    return [p[0] for p in pairs], pairs

def load_net():
    d = json.load(open(f"{REPO}/recon/catalogs/net_address_spaces.json"))
    pairs = []
    for f in d["functions"]:
        a = int(f["runtime_address"], 16)
        pairs.append((a, f["name"]))
    pairs.sort()
    return [p[0] for p in pairs], pairs

def enclosing(addrs, pairs, pc):
    i = bisect.bisect_right(addrs, pc) - 1
    if i < 0:
        return None, None
    return pairs[i][0], pairs[i][1]

def process(path, addrs, pairs):
    first_i = {}     # name -> first instruction index entered
    entry_count = {} # name -> number of transitions INTO this function
    total_instr = {} # name -> instructions executed inside
    order = []       # names in order of first entry
    prev_name = None
    n = 0
    with open(path) as fh:
        for line in fh:
            line = line.strip()
            if not line:
                continue
            pc = int(line, 16)
            start, name = enclosing(addrs, pairs, pc)
            if name is None:
                name = f"<unmapped:{line}>"
            total_instr[name] = total_instr.get(name, 0) + 1
            if name != prev_name:
                # entry (or re-entry) event
                if name not in first_i:
                    first_i[name] = n
                    order.append(name)
                entry_count[name] = entry_count.get(name, 0) + 1
            prev_name = name
            n += 1
    events = []
    for name in order:
        events.append({
            "name": name,
            "first_i": first_i[name],
            "entries": entry_count[name],
            "instr": total_instr[name],
        })
    return events, n

def first_index_of_addr(path, target):
    """First trace line (instr index) whose PC == target address."""
    ts = f"0x{target:X}".upper().replace("0X", "0x")
    n = 0
    with open(path) as fh:
        for line in fh:
            s = line.strip()
            if not s:
                continue
            if int(s, 16) == target:
                return n
            n += 1
    return None

if __name__ == "__main__":
    core = sys.argv[1]
    path = sys.argv[2]
    out = sys.argv[3]
    if core == "app":
        addrs, pairs = load_app()
    else:
        addrs, pairs = load_net()
    events, total = process(path, addrs, pairs)
    json.dump({"core": core, "total_instr": total, "unique_functions": len(events),
               "events": events}, open(out, "w"), indent=1)
    print(f"{core}: {total} instr, {len(events)} unique functions -> {out}")
    print("first 40 entered:")
    for e in events[:40]:
        print(f"  i={e['first_i']:>9} x{e['entries']:<6} instr={e['instr']:<8} {e['name']}")
    print("last 15 entered:")
    for e in events[-15:]:
        print(f"  i={e['first_i']:>9} x{e['entries']:<6} instr={e['instr']:<8} {e['name']}")
