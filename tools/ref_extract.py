"""
Build a normalized-signature reference DB from the user's compiled NCS ELFs.

For every function symbol in each reference ELF we disassemble its Thumb body
and emit a *normalized token stream*: mnemonic + operand shape, with immediates,
branch targets and PC-relative literal loads masked out. This is resilient to
link-time address differences (relocations) while preserving real logic, so a
firmware function that IS a given library routine will hash-match its reference.

Output: ref_db.json  { "by_sig": {sighash: [names...]},
                       "names": set of all library symbol names,
                       "by_name_sig": {name: [sighash,...]} }
"""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths
import json, sys, hashlib
from capstone import *
from elftools.elf.elffile import ELFFile

md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
md.detail = True

# mnemonics whose immediate/target operands are address-dependent -> mask
BRANCH = {"b", "bl", "blx", "bx", "cbz", "cbnz", "b.w", "bl.w"}

def norm_tokens(code, addr):
    toks = []
    for insn in md.disasm(code, addr):
        m = insn.mnemonic
        ops = insn.op_str
        # mask literal pool loads (ldr rX,[pc,#..]) and address immediates
        if "[pc" in ops:
            ops = "LIT"
        elif m in BRANCH:
            # keep whether it's conditional but drop the absolute target
            ops = "TGT"
        else:
            # mask bare #imm immediates (keep registers/structure)
            out = []
            for part in ops.split(", "):
                p = part.strip()
                if p.startswith("#"):
                    out.append("#i")
                elif p.startswith("0x"):
                    out.append("#i")
                else:
                    out.append(p)
            ops = ", ".join(out)
        toks.append(m + " " + ops)
    return toks

def sig_of(code, addr):
    toks = norm_tokens(code, addr)
    if len(toks) < 4:            # too short -> unreliable, skip
        return None, toks
    h = hashlib.sha256(("\n".join(toks)).encode()).hexdigest()
    return h, toks

def process_elf(path, db):
    with open(path, "rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return
        # build address->section data map
        for sym in symtab.iter_symbols():
            if sym["st_info"]["type"] != "STT_FUNC":
                continue
            size = sym["st_size"]
            if size < 8:
                continue
            addr = sym["st_value"]
            name = sym.name
            if not name:
                continue
            # find section containing addr
            code = None
            for sec in elf.iter_sections():
                sh = sec["sh_addr"]
                if sh and sh <= (addr & ~1) < sh + sec["sh_size"] and sec.data():
                    off = (addr & ~1) - sh
                    code = sec.data()[off:off+size]
                    break
            if not code or len(code) < 8:
                continue
            h, toks = sig_of(code, addr & ~1)
            if h is None:
                continue
            db["by_sig"].setdefault(h, [])
            if name not in db["by_sig"][h]:
                db["by_sig"][h].append(name)
            db["names"][name] = db["names"].get(name, 0) + 1

if __name__ == "__main__":
    elfs = sys.argv[1:]
    db = {"by_sig": {}, "names": {}}
    for e in elfs:
        process_elf(e, db)
        print("processed", e, "-> sigs:", len(db["by_sig"]), "names:", len(db["names"]))
    out = _g1_paths.scratchpad() + '/ref_db.json'
    json.dump(db, open(out, "w"))
    print("wrote", out, "| unique sigs:", len(db["by_sig"]), "| library names:", len(db["names"]))
