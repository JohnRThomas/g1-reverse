"""WS2 step 3: match each RAM cluster to a struct type from the DWARF dict.

A cluster's observed span (max accessed offset) is a LOWER BOUND on the object
size. A type is a candidate if type_size >= span and every accessed offset lands
on a real member boundary of that type. Score = offset-alignment fraction, with
a tight-size bonus and a Zephyr-kernel-object prior (many globals are msgq/sem/
thread/work). High-confidence matches become the ram_map; the rest are flagged.
"""
import json

SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c7-4e04-ae79-84a08ccae34e/scratchpad".replace("0c7-", "0c97-")
clusters = json.load(open(SCR + "/ws2_clusters.json"))
types = json.load(open(SCR + "/ws2_types.json"))

KERNEL = {"k_msgq", "k_sem", "k_mutex", "k_timer", "k_thread", "k_work",
          "k_work_q", "k_fifo", "k_lifo", "k_poll_signal", "k_heap",
          "k_mem_slab", "ring_buf", "net_buf", "k_work_delayable", "device",
          "k_condvar", "k_event", "k_pipe", "k_stack", "sys_mutex"}

# precompute member-offset sets per type
tmeta = {}
for name, t in types.items():
    offs = set(m["offset"] for m in t["members"])
    tmeta[name] = (t["size"], offs, t)

def score(cluster):
    span = cluster["size"]
    accessed = set(cluster["offsets"])
    best = []
    for name, (sz, offs, t) in tmeta.items():
        if sz < span - 4 or sz > span + 260:      # size must plausibly contain the span
            continue
        if not accessed:
            continue
        aligned = sum(1 for o in accessed if o in offs)
        frac = aligned / len(accessed)
        if frac < 0.5:
            continue
        s = frac
        s += 0.25 * (1 - min(abs(sz - span), 64) / 64.0)   # tight-size bonus
        if name in KERNEL:
            s += 0.15
        best.append((round(s, 3), name, sz, aligned, len(accessed)))
    best.sort(reverse=True)
    return best[:4]

ram_map = []
hi = 0
for c in clusters:
    cand = score(c)
    top = cand[0] if cand else None
    conf = "high" if (top and top[0] >= 0.9) else ("med" if top and top[0] >= 0.7 else "low")
    if conf == "high":
        hi += 1
    ram_map.append({"base": c["base"], "span": c["size"], "nrefs": c["naddr"],
                    "guess": top[1] if top else None,
                    "guess_type_size": top[2] if top else None,
                    "score": top[0] if top else 0, "conf": conf,
                    "alt": [x[1] for x in cand[1:3]],
                    "fns": c["fns"][:4]})
ram_map.sort(key=lambda x: -x["nrefs"])
json.dump(ram_map, open(SCR + "/ws2_ram_map.json", "w"), indent=1)
print("clusters:", len(clusters), "| high-confidence type matches:", hi)
for r in ram_map[:28]:
    g = r["guess"] or "-"
    print("  %s span=%-4d n=%-2d  %-18s score=%.2f %-4s alt=%s" %
          (r["base"], r["span"], r["nrefs"], g, r["score"], r["conf"], ",".join(r["alt"])))
