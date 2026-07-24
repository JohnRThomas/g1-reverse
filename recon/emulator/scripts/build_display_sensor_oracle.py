#!/usr/bin/env python3
"""Build the graphics + sensor parity ORACLE from a capture produced by
recon/emulator/scripts/capture_display_sensor_oracle.sh.

Inputs  (OUTDIR, default /tmp/g1_oracle):
    spim_a.p{1,2}.trace  spim_b.p{1,2}.trace   SPI transaction payload traces
    twim1.p{1,2}.trace   twim2.p{1,2}.trace    I2C transaction payload traces
    run.out                                     Renode console: register-access
                                                traces (PDM/SAADC/GPIOTE),
                                                counters, JBD journal
    fb_p1_boot.ppm  fb_p2_render.ppm            model-side framebuffer dumps

Outputs (recon/emulator/reports/):
    display_sensor_oracle.json
    golden_framebuffer_p1_boot.{raw,pgm,png}
    golden_framebuffer_p2_render.{raw,pgm,png}

The framebuffer is reconstructed INDEPENDENTLY from the SPI transaction stream
(exactly what a rebuilt firmware must reproduce) and cross-checked against the
JBD model's own dump; the check result is recorded in the oracle.

Usage:
    PYTHONSAFEPATH=1 .venv/bin/python \
        recon/emulator/scripts/build_display_sensor_oracle.py [OUTDIR] [REPORTDIR]
"""
import hashlib
import json
import os
import re
import sys
import zlib

# JBD panel geometry (models/JBD_Display.cs, corroborated by
# recon/analysis/display_subsystem_report.md).
WIDTH = 640
HEIGHT = 480
BYTES_PER_ROW = 320
FB_BYTES = BYTES_PER_ROW * HEIGHT  # 153600
CANVAS_H = 200  # active 640x200 dashboard canvas inside the 640x480 panel

PHASES = ["p1_boot", "p2_render"]

I2C_DEVICES = {
    ("TWIM1", 0x45): "opt3001_ambient_light",
    ("TWIM1", 0x6B): "npm1300_charger_fuelgauge",
    ("TWIM1", 0x53): "st25dv_nfc_eeprom",
    ("TWIM1", 0x57): "st25dv_system_port",
    ("TWIM2", 0x6B): "lsm6dso_imu",
}

# JBD SPI opcodes (models/JBD_Display.cs + display_subsystem_report.md sec.3)
OPCODE_MEANING = {
    0x9F: "panel_id_probe (expects 0x4010)",
    0x02: "pixel_window_write",
    0x46: "brightness_reg_write (set_brightness_to_panel_reg)",
    0x31: "brightness_reg_latch",
    0x97: "display_update/refresh",
    0x66: "panel_cmd",
    0x99: "panel_cmd",
    0x06: "panel_cmd",
    0x01: "panel_cmd",
    0xC0: "panel_cmd",
    0x71: "panel_cmd",
    0x73: "panel_cmd",
    0x36: "panel_cmd",
    0xA3: "panel_cmd",
    0xA9: "panel_cmd",
    0xB9: "panel_cmd",
}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_sha(path: str) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


# --------------------------------------------------------------------------
# trace parsing
# --------------------------------------------------------------------------
SPI_RE = re.compile(
    r"^(\S+) seq=(\d+) tick=(\d+) txn=(\d+) rxn=(\d+) tx=(\S+) rx=(\S+)\s*$")
I2C_RE = re.compile(
    r"^(\S+) seq=(\d+) tick=(\d+) dev=0x([0-9A-Fa-f]+) dir=(\w) n=(\d+) data=(\S*)\s*$")


def parse_spi(path):
    out = []
    if not os.path.exists(path):
        return out
    with open(path, "r", errors="replace") as fh:
        for line in fh:
            m = SPI_RE.match(line)
            if not m:
                continue
            tx = b"" if m.group(6) == "-" else bytes.fromhex(m.group(6))
            rx = b"" if m.group(7) == "-" else bytes.fromhex(m.group(7))
            out.append({"tick": int(m.group(3)), "tx": tx, "rx": rx})
    return out


def parse_i2c(path):
    out = []
    if not os.path.exists(path):
        return out
    with open(path, "r", errors="replace") as fh:
        for line in fh:
            m = I2C_RE.match(line)
            if not m:
                continue
            out.append({
                "bus": m.group(1),
                "tick": int(m.group(3)),
                "dev": int(m.group(4), 16),
                "dir": m.group(5),
                "data": bytes.fromhex(m.group(7)) if m.group(7) else b"",
            })
    return out


# --------------------------------------------------------------------------
# JBD display decoding + framebuffer reconstruction
# --------------------------------------------------------------------------
def decode_jbd(tx: bytes):
    """Decode one SPI transaction as a JBD panel command.

    Mirrors models/JBD_Display.cs with the g1.resc configuration
    (CoordBigEndian=true, IdReadLatency=1).
    """
    if not tx:
        return {"opcode": None, "kind": "empty"}
    op = tx[0]
    if op == 0x02:
        if len(tx) < 5:
            return {"opcode": op, "kind": "pixel_window_truncated"}
        coord = ((tx[1] << 16) | (tx[2] << 8) | tx[3]) & 0x7FFFF
        marker = tx[4]
        # last byte of the transfer is a trailing dummy (not written)
        pix = tx[5:-1] if len(tx) > 5 else b""
        x = coord & 0x3FF
        y = (coord >> 10) & 0x1FF
        return {"opcode": op, "kind": "pixel_window", "x": x, "y": y,
                "marker": marker, "pixel_bytes": pix}
    return {"opcode": op, "kind": "command", "payload": tx[1:]}


def replay_framebuffer(transactions, fb=None):
    """Reconstruct the panel framebuffer from the ordered SPI stream."""
    if fb is None:
        fb = bytearray(FB_BYTES)
    windows = 0
    for t in transactions:
        d = decode_jbd(t["tx"])
        if d["kind"] != "pixel_window":
            continue
        if d["marker"] != 0xFF:
            continue
        if d["x"] >= WIDTH or d["y"] >= HEIGHT:
            continue
        off = d["y"] * BYTES_PER_ROW + d["x"] // 2
        for b in d["pixel_bytes"]:
            fb[off] = b
            off = (off + 1) % FB_BYTES
        windows += 1
    return fb, windows


def fb_stats(fb: bytes):
    lit_bytes = sum(1 for b in fb if b)
    lit_px = 0
    minx = miny = 1 << 30
    maxx = maxy = -1
    for y in range(HEIGHT):
        row = fb[y * BYTES_PER_ROW:(y + 1) * BYTES_PER_ROW]
        if not any(row):
            continue
        for i, b in enumerate(row):
            if not b:
                continue
            for half in (0, 1):
                v = (b >> 4) & 0xF if half == 0 else b & 0xF
                if v:
                    x = i * 2 + half
                    lit_px += 1
                    minx = min(minx, x)
                    maxx = max(maxx, x)
                    miny = min(miny, y)
                    maxy = max(maxy, y)
    bbox = None
    if maxx >= 0:
        bbox = {"x0": minx, "y0": miny, "x1": maxx, "y1": maxy,
                "w": maxx - minx + 1, "h": maxy - miny + 1}
    return {"lit_bytes": lit_bytes, "lit_pixels": lit_px, "bbox": bbox}


def fb_to_gray(fb: bytes) -> bytes:
    """Expand 4bpp (high nibble = left pixel) to 8-bit gray, value*17."""
    out = bytearray(WIDTH * HEIGHT)
    o = 0
    for b in fb:
        out[o] = ((b >> 4) & 0xF) * 17
        out[o + 1] = (b & 0xF) * 17
        o += 2
    return bytes(out)


def write_pgm(path, gray: bytes):
    with open(path, "wb") as fh:
        fh.write(b"P5\n%d %d\n255\n" % (WIDTH, HEIGHT))
        fh.write(gray)


def write_png(path, gray: bytes, w=WIDTH, h=HEIGHT):
    """Grayscale PNG, no external deps (stdlib zlib only)."""
    WIDTH, HEIGHT = w, h
    raw = bytearray()
    for y in range(HEIGHT):
        raw.append(0)  # filter type 0
        raw += gray[y * WIDTH:(y + 1) * WIDTH]

    def chunk(tag, data):
        return (len(data).to_bytes(4, "big") + tag + data +
                (zlib.crc32(tag + data) & 0xFFFFFFFF).to_bytes(4, "big"))

    ihdr = (WIDTH.to_bytes(4, "big") + HEIGHT.to_bytes(4, "big") +
            bytes([8, 0, 0, 0, 0]))
    with open(path, "wb") as fh:
        fh.write(b"\x89PNG\r\n\x1a\n")
        fh.write(chunk(b"IHDR", ihdr))
        fh.write(chunk(b"IDAT", zlib.compress(bytes(raw), 9)))
        fh.write(chunk(b"IEND", b""))


def read_ppm(path):
    """Read the JBD model's P6 dump back into a 4bpp framebuffer."""
    with open(path, "rb") as fh:
        data = fh.read()
    parts = data.split(b"\n", 3)
    w, h = map(int, parts[1].split())
    body = parts[3]
    fb = bytearray(w * h // 2)
    for y in range(h):
        for x in range(0, w, 2):
            i = (y * w + x) * 3
            hi = body[i] // 17
            lo = body[i + 3] // 17 if i + 3 < len(body) else 0
            fb[y * (w // 2) + x // 2] = (hi << 4) | lo
    return bytes(fb), w, h


# --------------------------------------------------------------------------
# run.out parsing (register-access traces + counters)
# --------------------------------------------------------------------------
ACCESS_RE = re.compile(
    r"^\d\d:\d\d:\d\d\.\d+ \[\w+\] (\w+): \[(\w+): 0x([0-9A-Fa-f]+)\] "
    r"(Read|Write)(\w+) (?:from|to) 0x([0-9A-Fa-f]+) \(([^)]*)\), "
    r"(?:value|returned) 0x([0-9A-Fa-f]+)")


def parse_run_out(path):
    reg_access = {}
    counters = {}
    esb_frames = []
    fw_events = {}
    journal = []
    in_journal = False
    pending = None
    with open(path, "r", errors="replace") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if line.startswith("ORACLE_JBD_JOURNAL_BEGIN"):
                in_journal = True
                continue
            if line.startswith("ORACLE_JBD_JOURNAL_END"):
                in_journal = False
                continue
            if in_journal:
                s = line.strip()
                if s and not s.startswith("("):
                    journal.append(s)
                continue
            m = ACCESS_RE.match(line)
            if m:
                periph = m.group(1)
                reg_access.setdefault(periph, []).append({
                    "cpu": m.group(2),
                    "pc": "0x%s" % m.group(3).upper(),
                    "op": m.group(4).lower(),
                    "width": m.group(5),
                    "offset": "0x%s" % m.group(6).upper(),
                    "reg": m.group(7),
                    "value": "0x%s" % m.group(8).upper(),
                })
                continue
            m2 = re.search(r"ORACLE (\S+)", line)
            if m2 and "[" in line:
                key = m2.group(1)
                fw_events[key] = fw_events.get(key, 0) + 1
                continue
            m3 = re.search(r"ESBDUMP tx#(\d+) len=(\d+) ([0-9A-Fa-f]{8,})", line)
            if m3:
                esb_frames.append({"tx": int(m3.group(1)),
                                   "len": int(m3.group(2)),
                                   "hex": m3.group(3).upper()})
                continue
            m4 = re.match(r"^ORACLE_(\w+):\s*$", line)
            if m4:
                pending = m4.group(1)
                continue
            if pending:
                s = line.strip()
                if s:
                    mt = re.search(r"Elapsed Virtual Time: ([0-9:.]+)", s)
                    counters[pending] = mt.group(1) if mt else s
                    pending = None
    return reg_access, counters, esb_frames, fw_events, journal


# --------------------------------------------------------------------------
# canonicalisation / RLE
# --------------------------------------------------------------------------
def rle(items):
    """Collapse consecutive identical entries into {..., 'repeat': n}."""
    out = []
    for it in items:
        if out and out[-1][0] == it:
            out[-1][1] += 1
        else:
            out.append([it, 1])
    res = []
    for val, n in out:
        e = dict(val)
        if n > 1:
            e["repeat"] = n
        res.append(e)
    return res


def spi_canonical_line(t):
    return "%s|%s" % (t["tx"].hex().upper(), t["rx"].hex().upper())


def i2c_canonical_line(t):
    return "%02X|%s|%s" % (t["dev"], t["dir"], t["data"].hex().upper())


def summarise_spi(transactions):
    """Compact, order-preserving, fully diffable SPI description."""
    entries = []
    ophist = {}
    for t in transactions:
        d = decode_jbd(t["tx"])
        op = d["opcode"]
        key = "0x%02X" % op if op is not None else "empty"
        ophist[key] = ophist.get(key, 0) + 1
        if d["kind"] == "pixel_window":
            entries.append({
                "op": "0x02", "kind": "pixel_window",
                "x": d["x"], "y": d["y"],
                "n_pixel_bytes": len(d["pixel_bytes"]),
                "pixel_sha256": sha(d["pixel_bytes"]),
            })
        else:
            payload = d.get("payload", b"")
            e = {"op": key, "kind": d["kind"], "n_tx": len(t["tx"]),
                 "n_rx": len(t["rx"])}
            if len(payload) <= 32:
                e["payload"] = payload.hex().upper()
            else:
                e["payload_sha256"] = sha(payload)
                e["n_payload"] = len(payload)
            if t["rx"] and any(t["rx"]):
                e["rx"] = t["rx"].hex().upper()
            entries.append(e)
    return entries, ophist


def summarise_i2c(transactions):
    per_dev = {}
    for t in transactions:
        name = I2C_DEVICES.get((t["bus"], t["dev"]), "unknown_0x%02X" % t["dev"])
        per_dev.setdefault(name, []).append(t)
    out = {}
    for name, txs in per_dev.items():
        entries = [{"dev": "0x%02X" % t["dev"], "dir": t["dir"],
                    "data": t["data"].hex().upper()} for t in txs]
        # register-access profile: for writes reg = data[0]; reads follow the
        # last write's register on this device (I2C register protocol).
        profile = {}
        last_reg = None
        for t in txs:
            if t["dir"] == "W" and t["data"]:
                last_reg = t["data"][0]
                key = "0x%02X" % last_reg
                p = profile.setdefault(key, {"writes": 0, "reads": 0,
                                             "written_values": [],
                                             "read_values": []})
                p["writes"] += 1
                v = t["data"][1:].hex().upper()
                if v and v not in p["written_values"]:
                    p["written_values"].append(v)
            elif t["dir"] == "R":
                key = "0x%02X" % last_reg if last_reg is not None else "unknown"
                p = profile.setdefault(key, {"writes": 0, "reads": 0,
                                             "written_values": [],
                                             "read_values": []})
                p["reads"] += 1
                v = t["data"].hex().upper()
                if v and len(p["read_values"]) < 8 and v not in p["read_values"]:
                    p["read_values"].append(v)
        for p in profile.values():
            p["written_values"] = sorted(p["written_values"])[:16]
        out[name] = {
            "transaction_count": len(txs),
            "stream_sha256": sha("\n".join(i2c_canonical_line(t)
                                           for t in txs).encode()),
            "register_profile": dict(sorted(profile.items())),
            "transactions_rle": rle(entries),
        }
    return out


def summarise_regaccess(accesses):
    if not accesses:
        return {"access_count": 0, "note": "peripheral never accessed by the firmware"}
    entries = [{"op": a["op"], "reg": a["reg"], "offset": a["offset"],
                "value": a["value"]} for a in accesses]
    reg_hist = {}
    for a in accesses:
        reg_hist[a["reg"]] = reg_hist.get(a["reg"], 0) + 1
    return {
        "access_count": len(accesses),
        "stream_sha256": sha("\n".join(
            "%s|%s|%s" % (a["op"], a["offset"], a["value"]) for a in accesses
        ).encode()),
        "register_histogram": dict(sorted(reg_hist.items())),
        "distinct_pcs": sorted({a["pc"] for a in accesses}),
        "accesses_rle": rle(entries),
    }


# --------------------------------------------------------------------------
def main():
    outdir = sys.argv[1] if len(sys.argv) > 1 else "/tmp/g1_oracle"
    repo = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
    reports = sys.argv[2] if len(sys.argv) > 2 else os.path.join(
        repo, "recon", "emulator", "reports")
    os.makedirs(reports, exist_ok=True)

    reg_access, counters, esb_frames, fw_events, journal = parse_run_out(
        os.path.join(outdir, "run.out"))

    oracle = {
        "schema": "g1.display_sensor_oracle/1",
        "what": ("Peripheral-transaction oracle of the SHIPPED Even G1 firmware: "
                 "every display (SPI/JBD) and sensor (I2C/PDM/SAADC/GPIOTE/ESB) "
                 "transaction the original performs, captured in Renode under "
                 "the same determinism knobs as golden_boot_trace.json."),
        "images": {},
        "determinism": {
            "emulator": "Renode (armemul g1.resc, shipped images)",
            "global_quantum_s": "0.000010",
            "core_scheduling": "serial (MasterTimeSource.ExecuteInSerial=True in g1.resc)",
            "cc312_seed": "0x5340CC3105340CC3",
            "virtual_time_budget_s": 20.0,
            "phases": {
                "p1_boot": "t=0..6 s — autonomous boot + virtual BLE central connect/GATT",
                "p2_render": "t=6..20 s — 'don' head-up gesture on the real LSM6DSO model -> display START -> ESB L/R sync -> dashboard blit",
            },
            "stimulus": ("identical to armemul/scripts/g1-selfdrive.sh: "
                         "vcentral (virtual phone, real radio CONNECT_IND + NUS ATT write "
                         "'0a0600000000'), esbslave (virtual right lens, AnnounceResponse), "
                         "lsm6dso PlayGesture 'don'"),
            "observation_method": {
                "spim_a/spim_b": "additive opt-in TraceFile hook in armemul/models/NRF5340_SPIM.cs (logs the tx/rx buffers the model already built; default off)",
                "twim1/twim2": "additive opt-in TraceFile hook in armemul/models/NRF5340_TWIM.cs (logs the EasyDMA payloads; default off)",
                "pdm0/saadc/gpiote0/gpiote1": "Renode built-in `sysbus LogPeripheralAccess <p> true` (no model change)",
                "radio/esb": "existing model counters (radio TransmittedFrames, esbslave MasterFramesSeen/AcksInjected/AnnounceResponsesInjected, esbslave DumpFirstN)",
            },
        },
        "regenerate": (
            "recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_oracle && "
            "PYTHONSAFEPATH=1 .venv/bin/python "
            "recon/emulator/scripts/build_display_sensor_oracle.py /tmp/g1_oracle"),
        "determinism_verification": {
            "method": "the whole capture was run twice end-to-end and the two oracles diffed field-by-field",
            "bit_identical_across_runs": [
                "framebuffer/*/sha256 and every row_sha256",
                "peripherals/spim_a/phases/*/stream_sha256 (the entire display transaction stream)",
                "peripherals/spim_b (empty both runs)",
                "peripherals/twim2/phases/*/stream_sha256 (LSM6DSO IMU)",
                "peripherals/twim1/phases/*/devices/*/stream_sha256 (every I2C device stream taken on its own)",
                "peripherals/{pdm0,saadc,gpiote0,gpiote1}/whole_run/stream_sha256",
                "counters/JBD_FRAMECOUNTER_*, DISPLAY_ON_ctx_fe8, ESB_SYNC_ctx_105a, ESB_MASTER_FRAMES, ESB_ACKS",
                "firmware_events",
            ],
            "NOT_stable_across_runs": {
                "peripherals/twim1/phases/*/stream_sha256": (
                    "the MERGED twim1 bus stream. The per-device sub-streams are identical; only "
                    "the interleaving between OPT3001 / nPM1300 / ST25DV (three independent "
                    "firmware threads sharing one bus) reorders. Diff twim1 PER DEVICE, not per bus."),
                "counters/RADIO_TX, counters/VC_DATA_EVENTS, peripherals/radio_esb/announce_responses_injected": (
                    "+/- ~2 frames of BLE/ESB radio-model cadence; a property of NRF5340_RADIO "
                    "timing, not of the firmware. Compare with a tolerance, or compare only the "
                    "boolean 'link established / ESB sync reached 2'."),
            },
        },
        "parity_criteria": {
            "graphics": [
                "G-1 PASS/FAIL: framebuffer/p2_render/sha256 must match byte-for-byte (pixel-exact, 640x480x4bpp = 153600 B).",
                "G-2 PASS/FAIL: framebuffer/p1_boot/sha256 must match byte-for-byte.",
                "G-3 PASS/FAIL: peripherals/spim_a/phases/{p1_boot,p2_render}/stream_sha256 must match (the exact ordered SPI byte stream: same opcodes, same payloads, same MISO).",
                "G-4 (localiser, not an extra gate): on a G-1/G-2 failure, framebuffer/*/row_sha256 identifies the first differing panel row.",
                "G-5 PASS/FAIL: the panel init sequence (the ordered non-0x02 opcode/payload list in spim_a p1_boot) must match exactly, including the 0x9F ID probe answering 0x4010 and the 0x46/0x31 brightness pair values.",
                "G-6 PASS/FAIL: spim_b must remain empty (0 transactions) - the original never uses the alternate display backend.",
            ],
            "sensors": [
                "S-IMU  PASS/FAIL: peripherals/twim2/phases/*/stream_sha256 (LSM6DSO): identical init register writes AND identical steady-state polling of 0x22/0x28.",
                "S-ALS  PASS/FAIL: twim1 devices.opt3001_ambient_light stream_sha256 per phase.",
                "S-PMIC PASS/FAIL: twim1 devices.npm1300_charger_fuelgauge stream_sha256 per phase.",
                "S-NFC  PASS/FAIL: twim1 devices.st25dv_nfc_eeprom + st25dv_system_port stream_sha256 per phase.",
                "S-ADC  PASS/FAIL: peripherals/saadc/whole_run/stream_sha256 (channel/PSELP/resolution/oversample/ptr + start/sample/stop cadence).",
                "S-MIC  PASS/FAIL: peripherals/pdm0/whole_run/stream_sha256 - the original writes ONLY PSEL.CLK=0x2D and PSEL.DIN=0x2E and never enables/starts the PDM in this scenario. Our build must do the same (no spurious ENABLE/START).",
                "S-KEYS PASS/FAIL: peripherals/gpiote0/whole_run/stream_sha256 - the two IN-event channels and their CONFIG words.",
                "S-ESB  PASS/FAIL (boolean, not counter-exact): counters/ESB_SYNC_ctx_105a must reach 0x02 and counters/DISPLAY_ON_ctx_fe8 must reach 0x01; ESB master PTX frames > 0.",
            ],
            "how_to_diff": (
                "Run the same capture script against g1-ours.resc (our build) into a different "
                "OUTDIR, rebuild the oracle into a scratch report dir, then compare the two JSON "
                "files field-by-field, ignoring the NOT_stable_across_runs fields listed above."),
        },
        "counters": counters,
        "firmware_events": fw_events,
        "peripherals": {},
        "framebuffer": {},
    }

    for name, path in (("cpuapp", os.path.join(repo, "app_update.bin")),
                       ("cpunet", os.path.join(repo, "netcore_image.bin"))):
        if os.path.exists(path):
            oracle["images"][name] = {"file": os.path.basename(path),
                                      "sha256": file_sha(path)}

    # ---------------- SPI / display -------------------------------------
    all_spi = {}
    for bus in ("spim_a", "spim_b"):
        per_phase = {}
        for ph in PHASES:
            txs = parse_spi(os.path.join(outdir, "%s.%s.trace" %
                                         (bus, ph.split("_")[0])))
            all_spi.setdefault(bus, []).extend(txs)
            entries, ophist = summarise_spi(txs)
            per_phase[ph] = {
                "transaction_count": len(txs),
                "stream_sha256": sha("\n".join(spi_canonical_line(t)
                                               for t in txs).encode()),
                "opcode_histogram": dict(sorted(ophist.items())),
                "opcode_meaning": {k: OPCODE_MEANING.get(int(k, 16), "unknown")
                                   for k in sorted(ophist) if k != "empty"},
                "transactions_rle": rle(entries),
            }
        oracle["peripherals"][bus] = {
            "controller": ("SPIM4 @0x4000A000 (firmware label SPIM2)"
                           if bus == "spim_a" else
                           "SPIM3 @0x4000C000 (firmware label SPIM4)"),
            "device": "JBD_Display 640x480 4bpp micro-LED" if bus == "spim_a" else "(none attached)",
            "phases": per_phase,
        }

    # ---------------- I2C / sensors --------------------------------------
    for bus in ("twim1", "twim2"):
        per_phase = {}
        for ph in PHASES:
            txs = parse_i2c(os.path.join(outdir, "%s.%s.trace" %
                                         (bus, ph.split("_")[0])))
            per_phase[ph] = {
                "transaction_count": len(txs),
                "stream_sha256": sha("\n".join(i2c_canonical_line(t)
                                               for t in txs).encode()),
                "devices": summarise_i2c(txs),
            }
        oracle["peripherals"][bus] = {
            "controller": ("TWIM1 @0x40009000 (SDA P0.05 / SCL P0.04)"
                           if bus == "twim1" else
                           "TWIM2 @0x4000B000 (SDA P1.02 / SCL P1.03, firmware label TWIM3)"),
            "devices_on_bus": [v for (b, _), v in I2C_DEVICES.items()
                               if b == bus.upper().replace("TWIM", "TWIM")],
            "phases": per_phase,
        }
    oracle["peripherals"]["twim1"]["devices_on_bus"] = [
        v for (b, _), v in I2C_DEVICES.items() if b == "TWIM1"]
    oracle["peripherals"]["twim2"]["devices_on_bus"] = [
        v for (b, _), v in I2C_DEVICES.items() if b == "TWIM2"]

    # ---------------- register-access peripherals -------------------------
    for periph, label in (("pdm0", "PDM (microphone)"),
                          ("saadc", "SAADC (analog inputs)"),
                          ("gpiote0", "GPIOTE0 (pin events: touch / case-detect / buttons)"),
                          ("gpiote1", "GPIOTE1 (pin events, secure domain)")):
        oracle["peripherals"][periph] = {
            "description": label,
            "observation": "Renode `sysbus LogPeripheralAccess` (register level; whole run, not phase split)",
            "whole_run": summarise_regaccess(reg_access.get(periph, [])),
        }

    # ---------------- ESB / radio ----------------------------------------
    oracle["peripherals"]["radio_esb"] = {
        "description": "Nordic ESB L<->R lens sync over the net-core RADIO",
        "master_ptx_frames_seen_by_virtual_slave": counters.get("ESB_MASTER_FRAMES"),
        "acks_injected": counters.get("ESB_ACKS"),
        "announce_responses_injected": counters.get("ESB_ANNOUNCE_RESP"),
        "ble_radio_transmitted_frames": counters.get("RADIO_TX"),
        "first_master_ptx_frames_hex": esb_frames[:4],
        "esb_sync_state_byte_ctx_0x105a": counters.get("ESB_SYNC_ctx_105a"),
        "display_on_flag_ctx_0xfe8": counters.get("DISPLAY_ON_ctx_fe8"),
    }

    # ---------------- framebuffer ----------------------------------------
    fb = bytearray(FB_BYTES)
    cumulative = {}
    for ph in PHASES:
        txs = parse_spi(os.path.join(outdir, "spim_a.%s.trace" % ph.split("_")[0]))
        fb, nwin = replay_framebuffer(txs, fb)
        snapshot = bytes(fb)
        cumulative[ph] = (snapshot, nwin)

        base = os.path.join(reports, "golden_framebuffer_%s" % ph)
        with open(base + ".raw", "wb") as f:
            f.write(snapshot)
        gray = fb_to_gray(snapshot)
        write_pgm(base + ".pgm", gray)
        write_png(base + ".png", gray)

        st = fb_stats(snapshot)
        # human-viewable crop of the lit region, 3x nearest-neighbour upscale
        if st["bbox"]:
            bb = st["bbox"]
            cw, ch, scale = bb["w"], bb["h"], 3
            crop = bytearray(cw * scale * ch * scale)
            for yy in range(ch * scale):
                sy = bb["y0"] + yy // scale
                for xx in range(cw * scale):
                    sx = bb["x0"] + xx // scale
                    crop[yy * cw * scale + xx] = gray[sy * WIDTH + sx]
            write_png(base + "_crop.png", bytes(crop), cw * scale, ch * scale)
        entry = {
            "format": "4bpp packed, high nibble = left pixel, 320 bytes/row",
            "width": WIDTH, "height": HEIGHT,
            "active_canvas": "640x%d dashboard canvas inside the 640x480 panel" % CANVAS_H,
            "raw_bytes": FB_BYTES,
            "pixel_windows_applied": nwin,
            "sha256": sha(snapshot),
            "lit_bytes": st["lit_bytes"],
            "lit_pixels": st["lit_pixels"],
            "bbox": st["bbox"],
            "row_sha256": {},
            "artifacts": {
                "raw": "recon/emulator/reports/golden_framebuffer_%s.raw" % ph,
                "pgm": "recon/emulator/reports/golden_framebuffer_%s.pgm" % ph,
                "png": "recon/emulator/reports/golden_framebuffer_%s.png" % ph,
                "crop_png": "recon/emulator/reports/golden_framebuffer_%s_crop.png (lit bbox, 3x upscale, human-viewable only)" % ph,
            },
        }
        # per-row hashes for non-blank rows -> pinpoints a pixel divergence
        for y in range(HEIGHT):
            row = snapshot[y * BYTES_PER_ROW:(y + 1) * BYTES_PER_ROW]
            if any(row):
                entry["row_sha256"]["%d" % y] = sha(row)
        # cross-check against the JBD model's own dump
        ppm = os.path.join(outdir, "fb_%s.ppm" % ph)
        if os.path.exists(ppm):
            model_fb, w, h = read_ppm(ppm)
            entry["model_dump_cross_check"] = {
                "model_ppm": os.path.basename(ppm),
                "model_dims": "%dx%d" % (w, h),
                "model_sha256": sha(model_fb),
                "matches_spi_replay": sha(model_fb) == sha(snapshot),
            }
        oracle["framebuffer"][ph] = entry

    oracle["jbd_journal_tail"] = journal[-40:]

    outfile = os.path.join(reports, "display_sensor_oracle.json")
    with open(outfile, "w") as fh:
        json.dump(oracle, fh, indent=1, sort_keys=False)
    print("wrote %s (%d bytes)" % (outfile, os.path.getsize(outfile)))
    for ph in PHASES:
        e = oracle["framebuffer"][ph]
        print("  %-10s windows=%-6d lit_px=%-6d bbox=%s xcheck=%s" % (
            ph, e["pixel_windows_applied"], e["lit_pixels"], e["bbox"],
            e.get("model_dump_cross_check", {}).get("matches_spi_replay")))
    for p, v in oracle["peripherals"].items():
        if "phases" in v:
            tot = sum(v["phases"][ph]["transaction_count"] for ph in PHASES)
            print("  %-10s transactions=%d" % (p, tot))
        elif "whole_run" in v:
            print("  %-10s reg_accesses=%d" % (p, v["whole_run"]["access_count"]))


if __name__ == "__main__":
    main()
