"""WS2 step 2: extract a struct/union type dictionary from the config-matched
NCS 2.5.1 build's DWARF. For every struct type: name, byte size, and members
(name, offset, type-name). This is the dictionary we match the RAM clusters
against (by size + accessed-offset pattern). Same NCS revision as the firmware,
so layouts are authoritative even though addresses differ."""
import json
from elftools.elf.elffile import ELFFile

ELF = "/Users/freedomcoder/ncs251/refapp/build/zephyr/zephyr.elf"
OUT = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad/ws2_types.json"

def type_name(die, cache):
    # resolve a DW_AT_type reference to a readable name (best-effort)
    t = die.attributes.get("DW_AT_type")
    if not t:
        return "void"
    ref = t.value + die.cu.cu_offset
    tgt = cache.get(ref)
    if tgt is None:
        return "?"
    tag = tgt.tag
    nm = tgt.attributes.get("DW_AT_name")
    if nm:
        return nm.value.decode("utf-8", "replace")
    if tag == "DW_TAG_pointer_type":
        return type_name(tgt, cache) + "*"
    if tag in ("DW_TAG_const_type", "DW_TAG_volatile_type", "DW_TAG_typedef"):
        return type_name(tgt, cache)
    return tag.replace("DW_TAG_", "").replace("_type", "")

def main():
    f = open(ELF, "rb")
    elf = ELFFile(f)
    if not elf.has_dwarf_info():
        print("no DWARF"); return
    dw = elf.get_dwarf_info()
    structs = {}
    for cu in dw.iter_CUs():
        cache = {die.offset: die for die in cu.iter_DIEs()}
        for die in cache.values():
            if die.tag not in ("DW_TAG_structure_type", "DW_TAG_union_type"):
                continue
            nm = die.attributes.get("DW_AT_name")
            sz = die.attributes.get("DW_AT_byte_size")
            if not nm or not sz:
                continue
            name = nm.value.decode("utf-8", "replace")
            size = sz.value
            if name in structs:      # first definition wins
                continue
            members = []
            for c in die.iter_children():
                if c.tag != "DW_TAG_member":
                    continue
                mn = c.attributes.get("DW_AT_name")
                off = c.attributes.get("DW_AT_data_member_location")
                if not mn:
                    continue
                o = off.value if off else 0
                if isinstance(o, list):   # exprloc form
                    o = 0
                members.append({"name": mn.value.decode("utf-8", "replace"),
                                "offset": o, "type": type_name(c, cache)})
            structs[name] = {"size": size, "kind": die.tag.split("_")[-2],
                             "members": members}
    json.dump(structs, open(OUT, "w"))
    print("struct/union types extracted:", len(structs))
    # show the Zephyr kernel objects we care about for cluster matching
    for k in ("k_msgq", "k_sem", "k_mutex", "k_timer", "k_thread", "k_work",
              "k_fifo", "k_lifo", "device", "k_work_q", "k_poll_signal",
              "k_heap", "k_mem_slab", "ring_buf", "net_buf"):
        if k in structs:
            print("  %-14s size=%-4d members=%d" % (k, structs[k]["size"], len(structs[k]["members"])))

if __name__ == "__main__":
    main()
