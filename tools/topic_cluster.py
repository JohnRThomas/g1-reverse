"""Group proven application functions into coupled SUBSYSTEMS for semantic
naming. Named functions seed a topic (by keyword); unnamed functions inherit the
majority topic of their call-graph neighbours (propagation). Result: coherent
subsystem groups anchored by known names, each small enough for one Opus agent.
"""
import json, glob, re
from collections import defaultdict, Counter
SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"

TOPICS = [
    ("ancs_notify", "ancs|notification|notif|whitelist|message_come|msg_expir"),
    ("dashboard",   "dashboard|dash_"),
    ("display",     "display|panel|jbd|jdb|raster|projector|brightness|screen|render|lcd|micro_?led"),
    ("gui_text",    "gui|utf|font|bitmap|wordwrap|draw|glyph|truncate|align"),
    ("audio",       "audio|dmic|pdm|mic|stream|record|voice|whisper"),
    ("flash_store", "flash|nvs|settings|storage|sett_|save_|read_usr|persist|burn|ext_flash"),
    ("ble_proto",   "ble|gatt|att_|spec_ble|process_req|process_get|dispatch|indicate|conn|pairing|bond|auth|smp"),
    ("esb_sync",    "esb|sync|master|slave|_to_slave|node"),
    ("imu_motion",  "imu|attitude|motion|wakeup|anti_shake|fusion|accel|gyro|lsm|bmi|angle"),
    ("touch_key",   "touch|key_|button|click|sw0|gesture"),
    ("battery",     "battery|fuel|charge|soc|glassbox|power_down|power_for|opt300|lux"),
    ("teleprompt",  "teleprompt|tpm_"),
    ("navigation",  "navigation|nav_|map_|overview|panoramic"),
    ("onboarding",  "onboard"),
    ("translate",   "translate|language|lang_"),
    ("quicknote",   "quicknote|quick_note|note_"),
    ("analytics",   "burial|buried|analytic|record_info|point_record"),
    ("system",      "system|power|boot|dfu|reset|reboot|watchdog|work_mode|device_info|aging|main|init$"),
    ("ipc_core",    "ipc|rpmsg|ept|mbox|dispatch_thread|msgq"),
]

def topic_of(name):
    low = name.lower()
    for t, pat in TOPICS:
        if re.search(pat, low):
            return t
    return None

def main():
    fw = {f["entry"]: f for f in json.load(open(SCR+"/app_funcs.json"))["functions"]}
    cls = {c["entry"]: c for c in json.load(open(SCR+"/classified.json"))["functions"]}
    proven = set()
    for f in glob.glob(SCR+"/ledger_*.json")+[SCR+"/recon_ledger.json"]:
        try:
            for x in json.load(open(f)):
                if x.get("pass"):
                    proven.add(int(x["entry_hex"], 16))
        except Exception:
            pass
    app = [e for e in proven if e in cls and cls[e]["class"] == "APPLICATION"]
    # name resolution for callees
    name2addr = {}
    for e, f in fw.items():
        name2addr[f["name"]] = e
    def callee_addrs(e):
        out = []
        for c in fw[e]["callees"]:
            m = re.match(r"(?:FUN_|sub_)0*([0-9a-fA-F]+)", c)
            if m:
                out.append(int(m.group(1), 16))
            elif c in name2addr:
                out.append(name2addr[c])
        return out
    # build undirected neighbour graph among app functions
    nbr = defaultdict(set)
    for e in app:
        for c in callee_addrs(e):
            if c in set(app):
                nbr[e].add(c); nbr[c].add(e)
    # seed topics from names
    topic = {}
    for e in app:
        nm = cls[e].get("name") or fw[e]["name"]
        t = topic_of(nm)
        if t:
            topic[e] = t
    seeded = len(topic)
    # propagate to unnamed via neighbour majority (several passes)
    for _ in range(6):
        changed = 0
        for e in app:
            if e in topic:
                continue
            votes = Counter(topic[n] for n in nbr[e] if n in topic)
            if votes:
                topic[e] = votes.most_common(1)[0][0]; changed += 1
        if not changed:
            break
    # leftover -> 'misc'
    groups = defaultdict(list)
    for e in app:
        groups[topic.get(e, "misc")].append(e)
    out = {}
    for t, es in groups.items():
        es.sort()
        out[t] = [{"addr": "0x%x" % e,
                   "name": cls[e].get("name") or fw[e]["name"],
                   "named": bool(cls[e].get("ida_name") and not cls[e]["ida_name"].startswith(("FUN_", "sub_")))}
                  for e in es]
    json.dump(out, open(SCR+"/topic_groups.json", "w"), indent=1)
    print("seeded from names:", seeded, "/ app proven:", len(app))
    for t in sorted(out, key=lambda k: -len(out[k])):
        n_named = sum(1 for x in out[t] if x["named"])
        print("  %-13s %3d funcs (%d named, %d to-name)" % (t, len(out[t]), n_named, len(out[t])-n_named))

if __name__ == "__main__":
    main()
