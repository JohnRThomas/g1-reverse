"""G1 CPUAPP boot emulator (Unicorn Cortex-M33).

Implements the durable emulator described in
recon/emulator/BOOT_EMULATION_PLAN.md:

  * MCUboot image parsing + reviewed reset state;
  * only reviewed nRF5340 memory windows are mapped; any other access stops the
    run and is reported with full context (strict mode);
  * bounded instruction/MMIO ring traces + named function milestones;
  * a modeled MMIO layer (FICR/NVMC/CLOCK/QSPI) with named rules -- no blanket
    "every event register ready";
  * machine-readable JSON reports with canonical stop reasons.

Usage:
    g1_boot_emulator.py boot   <image.bin> [--budget N] [--profile P] [--report out.json]
    g1_boot_emulator.py raw    <image.bin> --base 0xADDR --entry 0xADDR ...
    g1_boot_emulator.py parse  <image.bin>

Run under: cd /tmp && PYTHONSAFEPATH=1 <repo>/.venv/bin/python <repo>/tools/g1_boot_emulator.py ...
"""
import argparse, collections, hashlib, json, os, struct, sys

from unicorn import (Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_MODE_MCLASS,
                     UC_HOOK_CODE, UC_HOOK_INTR, UC_HOOK_MEM_READ,
                     UC_HOOK_MEM_WRITE, UC_HOOK_MEM_UNMAPPED, UC_PROT_ALL,
                     UC_PROT_READ, UC_PROT_EXEC, UcError,
                     UC_MEM_READ_UNMAPPED, UC_MEM_WRITE_UNMAPPED,
                     UC_MEM_FETCH_UNMAPPED)
from unicorn.arm_const import (UC_ARM_REG_SP, UC_ARM_REG_PC, UC_ARM_REG_LR,
                               UC_ARM_REG_CPSR, UC_ARM_REG_R0, UC_ARM_REG_R1,
                               UC_ARM_REG_R2, UC_ARM_REG_R3)

REPO = "/Users/freedomcoder/Projects/G1disasm2"
MCUBOOT_MAGIC = 0x96f3b83d
APP_LINK_BASE = 0x0000c200          # payload byte 0 (file hdr_size) -> this VA
VA_FROM_FILE = 0xc000               # VA = file_offset + 0xc000

# Reviewed nRF5340 CPUAPP windows: (base, size, perms, name)
MEMMAP = [
    (0x00000000, 0x00200000, UC_PROT_READ | UC_PROT_EXEC, "code_flash"),
    (0x00ff0000, 0x00010000, UC_PROT_READ,               "ficr_uicr"),
    (0x20000000, 0x00080000, UC_PROT_ALL,                "sram"),
    (0x21000000, 0x00010000, UC_PROT_ALL,                "sram_shared"),
    (0x40000000, 0x10000000, UC_PROT_ALL,                "periph_ns"),
    (0x50000000, 0x10000000, UC_PROT_ALL,                "periph_s"),
    (0xe0000000, 0x00100000, UC_PROT_ALL,                "ppb"),
]

# MMIO register models (address -> named rule). Reads not listed default to 0
# and are recorded as an assumption; writes are recorded.
NVMC_READY_S = 0x50039400
NVMC_READY_NS = 0x40039400
QSPI_BASE_S = 0x5002b000
QSPI_BASE_NS = 0x4002b000

CANON_STOP = {
    "diagnostic_pass", "diagnostic_fail", "idle_with_no_pending_interrupt",
    "instruction_budget", "repeated_wait_loop", "unsupported_mmio",
    "unmapped_memory", "cpu_exception", "hardfault_vector",
    "write_to_read_only_qspi", "explicit_firmware_fatal", "emulator_internal_error",
}


def sha256_file(path):
    return hashlib.sha256(open(path, "rb").read()).hexdigest()


def parse_mcuboot(data):
    """Parse+validate the 32-byte MCUboot image header. Returns a dict."""
    if len(data) < 32:
        raise ValueError("image too small for MCUboot header")
    (magic, load, hdr_size, prot_tlv, img_size, flags,
     v_major, v_minor, v_rev, v_build) = struct.unpack_from("<IIHHIIBBHI", data, 0)
    if magic != MCUBOOT_MAGIC:
        raise ValueError("bad MCUboot magic 0x%08x (want 0x%08x)" % (magic, MCUBOOT_MAGIC))
    if hdr_size + img_size > len(data):
        raise ValueError("hdr_size+img_size 0x%x exceeds file 0x%x"
                         % (hdr_size + img_size, len(data)))
    payload = data[hdr_size:hdr_size + img_size]
    msp, reset = struct.unpack_from("<II", payload, 0)
    return {"magic": magic, "load_addr": load, "hdr_size": hdr_size,
            "prot_tlv_size": prot_tlv, "img_size": img_size, "flags": flags,
            "version": "%d.%d.%d+%d" % (v_major, v_minor, v_rev, v_build),
            "payload": payload, "msp": msp, "reset": reset}


def load_symbols():
    """address(int) -> name, from the committed CPUAPP function-name map."""
    p = REPO + "/recon/catalogs/function_names_app.json"
    syms = {}
    try:
        amap = json.load(open(p))["by_address"]
        for k, rec in amap.items():
            syms[int(k, 16)] = rec["name"]
    except Exception:
        pass
    return syms


def load_milestones():
    """Named boot milestones from the authoritative root inventory + a few pins."""
    ms = {}
    try:
        inv = json.load(open(REPO + "/recon/catalogs/app_root_inventory.json"))
        for lvl in inv.get("init_levels", []):
            name = lvl.get("level", "init")
            for e in lvl.get("entries", []) if isinstance(lvl, dict) else []:
                a = e.get("addr") or e.get("address")
                if a is not None:
                    ms[int(a, 16) if isinstance(a, str) else a] = "%s:%s" % (
                        name, e.get("name", "?"))
    except Exception:
        pass
    # explicit pins from the plan
    for a, n in [(0x0004c144, "nordicsemi_nrf53_init"), (0x0006058c, "clock_control_nrf_init"),
                 (0x000637b8, "sys_clock_driver_init"), (0x00060c00, "qspi_nor_init"),
                 (0x00061234, "soc_flash_nrf_init"), (0x00061aec, "mbox_nrfx_init"),
                 (0x0007eb5c, "ipc_static_vrings_init"), (0x00060174, "bt_rpmsg_init"),
                 (0x00051304, "mcumgr_handlers_init"), (0x000526b4, "smp_init")]:
        ms[a] = ms.get(a, n)
    return ms


class Ring:
    def __init__(self, n):
        self.n = n
        self.buf = collections.deque(maxlen=n)

    def push(self, x):
        self.buf.append(x)

    def list(self):
        return list(self.buf)


class Emulator:
    def __init__(self, profile="strict", budget=3_000_000, quiet=True):
        self.profile = profile
        self.budget = budget
        self.quiet = quiet
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
        self.syms = load_symbols()
        self.milestones = load_milestones()
        self.icount = 0
        self.stop_reason = None
        self.stop_pc = None
        self.unexpected = None
        self.func_entries = collections.OrderedDict()   # milestone -> (first_i, last_i)
        self.entryset = set(self.syms)                  # all known function entries
        self.func_first = {}                            # addr -> [name, first_i, count]
        self.hot = collections.Counter()
        self.mmio_r = collections.Counter()
        self.mmio_w = collections.Counter()
        self.svc = 0
        self.wfi = 0
        self.exceptions = []
        self.assumptions = set()
        self.qspi_events = []
        self.pc_ring = Ring(512)
        self.mmio_ring = Ring(128)
        self.qspi = None          # set by attach_qspi
        self._last_pcs = collections.deque(maxlen=64)
        # ARMv8-M MPU model: RNR-selected region array + aliases (arm_mpu.c reads
        # regions back to mark dynamic areas, so this must be stateful).
        self.mpu = {"ctrl": 0, "rnr": 0, "mair0": 0, "mair1": 0,
                    "rbar": [0] * 8, "rlar": [0] * 8}
        # Runtime intrinsic overrides (plan pref #4): emulate ops Unicorn lacks
        # (e.g. the CMSE TT instruction) without altering the image.
        self.intrinsics = {}
        self._install_intrinsics()
        self._map()

    def _install_intrinsics(self):
        # The CMSE `tt` instruction sits at the entry of arm_cmse_mpu_region_get.
        # Unicorn doesn't model TT, so emulate just that one instruction against
        # the modeled MPU regions and let the rest of the function run normally.
        a = {v: k for k, v in self.syms.items()}
        tt = a.get("arm_cmse_mpu_region_get")
        if tt is not None:
            self.intrinsics[tt] = self._intrinsic_tt

    def _intrinsic_tt(self, uc):
        """Emulate `tt r3, r0`: r3 = R-bit(16) | MREGION(7:0) for the MPU region
        containing r0; r3 = 0 (no valid region) otherwise. The caller (run loop)
        resumes 4 bytes later; register effect only, no PC write here."""
        addr = uc.reg_read(UC_ARM_REG_R0)
        r3 = 0
        for i in range(8):
            rlar = self.mpu["rlar"][i]
            if not (rlar & 1):
                continue
            base = self.mpu["rbar"][i] & ~0x1f
            limit = (rlar & ~0x1f) | 0x1f
            if base <= addr <= limit:
                r3 = 0x00010000 | i          # R (valid) | MREGION
                break
        uc.reg_write(UC_ARM_REG_R3, r3)
        self.assumptions.add("intrinsic:TT emulated vs modeled MPU (arm_cmse_mpu_region_get)")

    # ---- memory ----
    def _map(self):
        for base, size, perms, name in MEMMAP:
            self.uc.mem_map(base, size, perms)
        # nRF FICR/UICR read 0xFFFFFFFF when unprogrammed (flash-erased). Boot
        # code depends on this (e.g. `ldr rN,[ficr]; adds #1; beq` skips a table
        # entry whose value is 0xffffffff). Zero-filling would misfire those
        # branches, so seed the whole window to 0xff, then pin known INFO fields.
        base = 0x00ff0000
        self.uc.mem_write(base, b"\xff" * 0x10000)
        # FICR.INFO (nRF5340 application core): PART=0x5340, VARIANT, RAM/FLASH kB.
        self.uc.mem_write(base + 0x20c, struct.pack("<I", 0x00005340))  # INFO.PART
        self.uc.mem_write(base + 0x210, struct.pack("<I", 0x41414141))  # INFO.VARIANT 'AAAA'
        self.uc.mem_write(base + 0x218, struct.pack("<I", 512))         # INFO.RAM kB
        self.uc.mem_write(base + 0x21c, struct.pack("<I", 1024))        # INFO.FLASH kB

    def sym(self, addr):
        return self.syms.get(addr & ~1) or self.syms.get(addr)

    def load_image(self, path):
        data = open(path, "rb").read()
        hdr = parse_mcuboot(data)
        self.image_path = path
        self.image_sha = hashlib.sha256(data).hexdigest()
        self.hdr = hdr
        # payload byte 0 (file hdr_size) -> APP_LINK_BASE
        self.uc.mem_write(APP_LINK_BASE, hdr["payload"])
        # validate reset state
        if not (0x20000000 <= hdr["msp"] <= 0x20080000):
            raise ValueError("initial MSP 0x%08x outside CPUAPP SRAM" % hdr["msp"])
        if not (hdr["reset"] & 1):
            raise ValueError("reset vector 0x%08x not Thumb" % hdr["reset"])
        rbase = hdr["reset"] & ~1
        if not (APP_LINK_BASE <= rbase < APP_LINK_BASE + hdr["img_size"]):
            raise ValueError("reset 0x%08x outside loaded image" % rbase)
        return hdr

    def load_raw(self, path, base, entry, msp):
        data = open(path, "rb").read()
        self.image_path = path
        self.image_sha = hashlib.sha256(data).hexdigest()
        self.hdr = {"raw": True, "base": base}
        self.uc.mem_write(base, data)
        self._raw_entry = entry
        self._raw_msp = msp

    # ---- reset ----
    def setup_reset(self, msp=None, pc=None, vtor=APP_LINK_BASE):
        if msp is None:
            msp = self.hdr["msp"]
        if pc is None:
            pc = self.hdr["reset"]
        self.uc.reg_write(UC_ARM_REG_SP, msp)
        self.uc.reg_write(UC_ARM_REG_PC, pc & ~1)
        cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
        self.uc.reg_write(UC_ARM_REG_CPSR, cpsr | 0x00000020)  # Thumb (T-bit)
        # VTOR
        try:
            self.uc.mem_write(0xe000ed08, struct.pack("<I", vtor))
        except UcError:
            pass
        self._msp0, self._pc0 = msp, pc

    # ---- hooks ----
    def install_hooks(self):
        self.uc.hook_add(UC_HOOK_CODE, self._hook_code)
        self.uc.hook_add(UC_HOOK_INTR, self._hook_intr)
        for base, size, perms, name in MEMMAP:
            if name in ("periph_ns", "periph_s", "ppb"):  # FICR served from seeded memory
                self.uc.hook_add(UC_HOOK_MEM_READ, self._hook_mmio_r, begin=base, end=base + size - 1)
                self.uc.hook_add(UC_HOOK_MEM_WRITE, self._hook_mmio_w, begin=base, end=base + size - 1)
        self.uc.hook_add(UC_HOOK_MEM_UNMAPPED, self._hook_unmapped)

    def _hook_code(self, uc, addr, size, user):
        self.icount += 1
        self.pc_ring.push(addr)
        self._last_pcs.append(addr)
        fn = self.intrinsics.get(addr)
        if fn is not None:
            fn(uc)                     # apply register effect
            self._resume_pc = addr + 4  # skip the emulated 32-bit instruction
            uc.emu_stop()               # restart in Thumb from _resume_pc
            return
        if addr in self.milestones:
            name = self.milestones[addr]
            if name not in self.func_entries:
                self.func_entries[name] = [self.icount, self.icount]
            else:
                self.func_entries[name][1] = self.icount
        if addr in self.entryset:
            rec = self.func_first.get(addr)
            if rec is None:
                self.func_first[addr] = [self.syms[addr], self.icount, 1]
            else:
                rec[2] += 1
        self.hot[addr] += 1
        if self.icount >= self.budget:
            self.stop_reason = "instruction_budget"
            self.stop_pc = addr
            uc.emu_stop()

    def _hook_intr(self, uc, intno, user):
        pc = uc.reg_read(UC_ARM_REG_PC)
        # On Cortex-M, Unicorn raises intno 2 for SVC; 7 = HardFault-ish exceptions.
        self.exceptions.append({"intno": intno, "pc": "0x%08x" % pc, "i": self.icount})
        if intno == 2:                    # SVC: count and continue (kernel syscall)
            self.svc += 1
            return
        # any other CPU exception -> stop as a fault
        self.stop_reason = "cpu_exception"
        self.stop_pc = pc
        uc.emu_stop()

    def _is_qspi(self, addr):
        return (QSPI_BASE_S <= addr < QSPI_BASE_S + 0x1000 or
                QSPI_BASE_NS <= addr < QSPI_BASE_NS + 0x1000)

    def _hook_mmio_r(self, uc, access, addr, size, value, user):
        self.mmio_r[addr] += 1
        self.mmio_ring.push(("r", "0x%08x" % addr, size, self.icount))
        val = self._model_read(uc, addr, size)
        if val is not None:
            try:
                uc.mem_write(addr, struct.pack("<I", val & 0xffffffff)[:size])
            except UcError:
                pass

    def _hook_mmio_w(self, uc, access, addr, size, value, user):
        self.mmio_w[addr] += 1
        self.mmio_ring.push(("w", "0x%08x" % addr, size, value, self.icount))
        self._model_write(uc, addr, size, value)

    def _mpu_alias(self, addr):
        """Map an MPU RBAR/RLAR(_An) address to (kind, region_index) or None."""
        off = addr - 0xe000ed9c
        if 0 <= off <= 0x1c and off % 4 == 0:
            pair = off // 4                       # 0=RBAR,1=RLAR,2=RBAR_A1,...
            alias = pair // 2
            kind = "rbar" if pair % 2 == 0 else "rlar"
            region = (self.mpu["rnr"] & ~3) + alias if alias else self.mpu["rnr"]
            return kind, region & 7
        return None

    def _model_read(self, uc, addr, size):
        # Cortex-M33 System Control Block / MPU (fixed core registers).
        if addr == 0xe000ed00:      # SCB CPUID: Cortex-M33 r0p4
            return 0x410fd214
        if addr == 0xe000ed90:      # MPU_TYPE: DREGION=8 (bits [15:8]); arm_mpu.c asserts ==8
            return 0x00000800
        if addr == 0xe000ed94:      # MPU_CTRL
            return self.mpu["ctrl"]
        if addr == 0xe000ed98:      # MPU_RNR
            return self.mpu["rnr"]
        a = self._mpu_alias(addr)
        if a is not None:
            kind, region = a
            return self.mpu[kind][region]
        if addr == 0xe000edc0:      # MPU_MAIR0
            return self.mpu["mair0"]
        if addr == 0xe000edc4:      # MPU_MAIR1
            return self.mpu["mair1"]
        # Other PPB registers are plain RW: let mapped memory serve them.
        if 0xe0000000 <= addr < 0xe0100000:
            return None
        # NVMC READY = 1
        if addr in (NVMC_READY_S, NVMC_READY_NS):
            return 1
        # QSPI EVENTS_READY = 1 (transfer completes instantly)
        if self._is_qspi(addr) and (addr & 0xfff) == 0x100:
            return 1
        # CLOCK HFCLK/LFCLK running status: modeled per named rule
        # (STATE bit). Base 0x5000_5000 CLOCK; keep minimal.
        low = addr & 0xfffff
        if low in (0x0408, 0x0104, 0x0408):   # placeholders recorded as assumptions
            self.assumptions.add("clock_status@0x%08x=running" % addr)
            return 1
        # default: unmodeled peripheral register -> 0, recorded
        self.assumptions.add("unmodeled_read@0x%08x=0" % (addr & ~0xf))
        return 0

    def _model_write(self, uc, addr, size, value):
        # ARMv8-M MPU stateful registers
        if addr == 0xe000ed94:
            self.mpu["ctrl"] = value; return
        if addr == 0xe000ed98:
            self.mpu["rnr"] = value & 0xff; return
        if addr == 0xe000edc0:
            self.mpu["mair0"] = value; return
        if addr == 0xe000edc4:
            self.mpu["mair1"] = value; return
        a = self._mpu_alias(addr)
        if a is not None:
            kind, region = a
            self.mpu[kind][region] = value
            return
        # QSPI TASKS_READ -> perform modeled read
        if self._is_qspi(addr) and (addr & 0xfff) == 0x004 and value == 1:
            if self.qspi is not None:
                self.qspi.do_read(self, uc, addr & ~0xfff)
            return
        # QSPI TASKS_WRITE / erase -> reject (read-only model)
        if self._is_qspi(addr) and (addr & 0xfff) in (0x008, 0x00c, 0x010) and value == 1:
            self.stop_reason = "write_to_read_only_qspi"
            self.stop_pc = uc.reg_read(UC_ARM_REG_PC)
            uc.emu_stop()

    def _hook_unmapped(self, uc, access, addr, size, value, user):
        kind = {UC_MEM_READ_UNMAPPED: "read", UC_MEM_WRITE_UNMAPPED: "write",
                UC_MEM_FETCH_UNMAPPED: "fetch"}.get(access, "access")
        pc = uc.reg_read(UC_ARM_REG_PC)
        self.unexpected = {
            "kind": kind, "addr": "0x%08x" % addr, "size": size,
            "value": ("0x%x" % value) if access == UC_MEM_WRITE_UNMAPPED else None,
            "pc": "0x%08x" % pc, "lr": "0x%08x" % uc.reg_read(UC_ARM_REG_LR),
            "sp": "0x%08x" % uc.reg_read(UC_ARM_REG_SP),
            "function": self.sym(pc), "i": self.icount,
            "recent_pcs": ["0x%08x" % p for p in list(self._last_pcs)[-16:]],
            "recent_mmio": self.mmio_ring.list()[-8:],
        }
        self.stop_reason = "unmapped_memory"
        self.stop_pc = pc
        uc.emu_stop()
        return False

    # ---- run ----
    def run(self, start=None, budget=None):
        if budget:
            self.budget = budget
        pc = self.uc.reg_read(UC_ARM_REG_PC) if start is None else start
        self._resume_pc = None
        while True:
            try:
                self.uc.emu_start(pc | 1, 0, count=0)
            except UcError as e:
                if self.stop_reason is None:
                    self.stop_reason = "emulator_internal_error"
                    self.stop_pc = self.uc.reg_read(UC_ARM_REG_PC)
                    self.unexpected = self.unexpected or {"ucerror": str(e)}
                break
            # intrinsic requested a Thumb-safe restart past an emulated insn
            if self._resume_pc is not None and self.stop_reason is None:
                pc = self._resume_pc
                self._resume_pc = None
                continue
            break
        if self.stop_reason is None:
            self.stop_reason = "idle_with_no_pending_interrupt"
        return self.report()

    def report(self):
        return {
            "image": {"path": getattr(self, "image_path", None), "sha256": getattr(self, "image_sha", None)},
            "profile": self.profile,
            "instruction_count": self.icount,
            "initial_sp": "0x%08x" % getattr(self, "_msp0", 0),
            "reset_handler": "0x%08x" % (self.hdr.get("reset", 0) if hasattr(self, "hdr") else 0),
            "stop_reason": self.stop_reason,
            "stop_pc": ("0x%08x" % self.stop_pc) if self.stop_pc else None,
            "stop_function": self.sym(self.stop_pc) if self.stop_pc else None,
            "milestones": [{"name": k, "first_i": v[0], "last_i": v[1]}
                           for k, v in self.func_entries.items()],
            "unique_functions_entered": len(self.func_first),
            "function_trace_first64": [
                {"name": n, "first_i": fi, "calls": c}
                for n, fi, c in sorted(([r[0], r[1], r[2]] for r in self.func_first.values()),
                                       key=lambda x: x[1])[:64]],
            "exceptions": self.exceptions[:64],
            "svc_count": self.svc, "wfi_count": self.wfi,
            "qspi_events": self.qspi_events,
            "unexpected_access": self.unexpected,
            "hot_pcs": [["0x%08x" % a, c] for a, c in self.hot.most_common(20)],
            "recent_pcs": ["0x%08x" % p for p in self.pc_ring.list()[-64:]],
            "mmio_reads_top": [["0x%08x" % a, c] for a, c in self.mmio_r.most_common(20)],
            "mmio_writes_top": [["0x%08x" % a, c] for a, c in self.mmio_w.most_common(20)],
            "model_assumptions": sorted(self.assumptions)[:64],
        }


def cmd_parse(args):
    data = open(args.image, "rb").read()
    hdr = parse_mcuboot(data)
    hdr = {k: (v if k != "payload" else "<%d bytes>" % len(v)) for k, v in hdr.items()}
    hdr["sha256"] = hashlib.sha256(data).hexdigest()
    print(json.dumps(hdr, indent=2, default=lambda x: "0x%x" % x if isinstance(x, int) else x))


def cmd_boot(args):
    em = Emulator(profile=args.profile, budget=args.budget)
    em.load_image(args.image)
    em.setup_reset()
    em.install_hooks()
    rep = em.run()
    if args.report:
        json.dump(rep, open(args.report, "w"), indent=1)
    # concise summary
    print("stop_reason:", rep["stop_reason"], "| instructions:", rep["instruction_count"],
          "| stop:", rep["stop_pc"], rep["stop_function"])
    print("milestones reached:", len(rep["milestones"]),
          "| svc:", rep["svc_count"], "| assumptions:", len(rep["model_assumptions"]))
    if rep["unexpected_access"]:
        print("unexpected:", json.dumps(rep["unexpected_access"]))


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("parse"); p.add_argument("image")
    p = sub.add_parser("boot")
    p.add_argument("image"); p.add_argument("--budget", type=int, default=3_000_000)
    p.add_argument("--profile", default="strict"); p.add_argument("--report")
    args = ap.parse_args()
    {"parse": cmd_parse, "boot": cmd_boot}[args.cmd](args)


if __name__ == "__main__":
    main()
