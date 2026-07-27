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


# ---------------------------------------------------------------------------
# P4 iteration 42, TASK 4b -- the ANALOGUE-SAMPLE canonicalisation.
#
# `stream_sha256` hashes the payload the LSM6DSO MODEL returns for a read of
# OUTX_L_A (0x28).  That payload is not firmware output: it is the modelled
# `don` gesture waveform evaluated at the virtual time the poll happens.  Renode
# charges virtual time per instruction, so any reconstruction whose `.text` is
# not byte-identical reaches the first I2C write at a different virtual time
# (measured at HEAD: +3.45 ms on twim1, +6.81 ms on twim2, +6.37 ms on spim_a)
# and every accelerometer sample thereafter lands a few ms further along the
# same ramp.  Measured consequence, navigation, seeded both sides: 3 of 1,200
# transactions differ, ALL of them 0x28 reads, and OUR values interleave exactly
# between consecutive shipped values (X: 3730 -> 37DD -> 39E2 -> 3A8E ...).
#
# `stream_sha256_regprog` therefore replaces the payload of an accelerometer
# sample read with its ordinal, so it gates the REGISTER PROGRAMME -- which
# device, which register, which direction, which write payload, in which order,
# how many times -- and not the analogue value.  It is ADDITIVE: `stream_sha256`
# is unchanged and still published.
#
# WHAT THIS DELIBERATELY STOPS CATCHING: a defect that keeps the poll cadence
# and the register programme intact but reads the accelerometer at a
# systematically different PHASE of the gesture.  `accel_sample_payloads` is
# published so that class stays measurable -- a comparer can count how many
# samples differ and check the implied offset against the polling period
# (80.11 ms here); a phase error large enough to matter shows up as many
# differing samples, not three.
ACCEL_SAMPLE_REGS = {("TWIM2", 0x6B): {0x28}}


def i2c_regprog_line(t, sample_ordinal):
    """Canonical line with modelled-analogue read payloads replaced by ordinal."""
    if sample_ordinal is not None:
        return "%02X|%s|SAMPLE#%d" % (t["dev"], t["dir"], sample_ordinal)
    return i2c_canonical_line(t)


def annotate_analogue_samples(txs):
    """Return (ordinals, payloads): ordinals[i] is the sample index for txs[i]
    when it is an analogue sample read, else None."""
    ordinals = [None] * len(txs)
    payloads = []
    last_reg = {}
    for i, t in enumerate(txs):
        key = (t["bus"], t["dev"])
        if t["dir"] == "W" and t["data"]:
            last_reg[key] = t["data"][0]
        elif t["dir"] == "R":
            reg = last_reg.get(key)
            if reg is not None and reg in ACCEL_SAMPLE_REGS.get(key, ()):
                ordinals[i] = len(payloads)
                payloads.append(t["data"].hex().upper())
    return ordinals, payloads


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
        ordinals, samples = annotate_analogue_samples(txs)
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
        if samples:
            out[name]["stream_sha256_regprog"] = sha("\n".join(
                i2c_regprog_line(t, o) for t, o in zip(txs, ordinals)).encode())
            out[name]["analogue_sample_reg"] = sorted(
                "0x%02X" % r for r in ACCEL_SAMPLE_REGS[(txs[0]["bus"], txs[0]["dev"])])
            out[name]["analogue_sample_count"] = len(samples)
            out[name]["analogue_sample_payloads"] = samples
            out[name]["analogue_sample_note"] = (
                "MODELLED sensor output, not firmware output: the LSM6DSO model's "
                "gesture waveform evaluated at the virtual time of each poll. "
                "stream_sha256_regprog is the gate; this list is informational and "
                "is what makes a real sampling-PHASE error measurable.")
    return out


# ---------------------------------------------------------------------------
# P4 iteration 42, TASK 4a -- the RAM-POINTER canonicalisation.
#
# `saadc/whole_run/stream_sha256` hashed three RAM ADDRESSES.  Measured on the
# seeded navigation pair at HEAD: of 1,000 `saadc:` log lines exactly 45 differ
# and every single one of them is `WriteUInt32 to 0x62C (ResultPtr)`; the diff
# of everything else -- ChPselP, ChConfig, Resolution, Oversample, Enable,
# TasksStart, TasksSample, every EventsEnd poll, TasksStop, and the ordering --
# is EMPTY.  Those writes come from ONE pc inside `saadc_start_read`
# (FUN_0005f760), which stores its caller-supplied `param_2` straight into
# SAADC.RESULT.PTR.  The three distinct values, 15 uses each, in an identical
# A,B,C,A,B,C... interleave on both sides:
#     shipped 0x200275CE / 0x200275A6 / 0x200275BE
#     ours    0x20028766 / 0x20028736 / 0x20028786   (+0x1198 / +0x1190 / +0x11C8)
# They are STACK addresses -- `nm -n` puts all three between `g_20026a68`
# (0x20027c08) and `g_aging_mode_aux_thread_stack` (0x20028808) with no symbol
# in between, `g1_app_globals.ld` pins nothing in 0x20026000..0x20029000, they
# are 2-byte aligned (an int16_t local, the SAADC one-shot result type), and
# `saadc_start_read` is never reached by a direct BL anywhere in the image.
# A differently-linked image can never reproduce them and nothing about the
# register programme is different.
#
# So the hashed value of such a register becomes its FIRST-APPEARANCE INDEX.
# The raw pointers are still published, un-hashed, because their DELTAS are
# informative: the +0x1198 / +0x1190 / +0x11C8 spread says one reconstructed
# caller's frame is 0x30 B deeper than the original's.
#
# WHAT THIS DELIBERATELY STOPS CATCHING: a defect that hands SAADC a *different
# number* of distinct buffers, or the same buffers in a different ORDER, is
# still caught (the index sequence changes).  What is no longer caught is a
# defect that puts the DMA pointer in the wrong place while keeping the count
# and order -- e.g. aiming RESULT.PTR at a static instead of a stack local, or
# at an address of the wrong alignment.  `pointer_values_raw` and
# `pointer_alignment` are published so that class stays inspectable by eye.
POINTER_REGS = {"saadc": {"ResultPtr"}}


# ===========================================================================
# P4 -- the PHASE-TOLERANT criterion (recon/analysis/phase_tolerant_criterion.md)
#
# Everything above this line is WALL-ANCHORED: a stream is cut at the 6 s phase
# boundary and the two halves are counted and hashed.  That makes every field
# above sensitive to the ABSOLUTE placement of a periodic train in wall time --
# a train that shifts by one poll period gains or loses a burst inside the
# window and every count and hash downstream of it moves, with no change to
# what the firmware exchanged with the device.
#
# The block below is TRAIN-ANCHORED and ADDITIVE.  Nothing above changes.
#
#   burst   a maximal run of consecutive transactions on one (bus, device)
#           separated by no more than BURST_GAP_NS.  The gap distribution is
#           strongly bimodal (measured, shipped navigation capture: intra-burst
#           gaps <= 1e6 ns, inter-burst gaps >= 1e7 ns) and the separation is
#           ASSERTED per capture in `gap_separation`, so a future capture that
#           violates it is reported rather than silently mis-segmented.
#   train   the bursts sharing one key, in time order.  The key is the burst's
#           REGISTER PROGRAMME: every write payload verbatim, every read reduced
#           to (selected register, payload length).  A read payload is the
#           MODEL talking, not the firmware; a write payload is the firmware
#           talking.  Keying on writes is what makes a train's membership stable
#           when a modelled sensor value crosses a threshold at a slightly
#           different virtual time.
#
# `starts_ns` is published for every train so a comparer can measure the phase
# offset directly.  The strict wall-anchored fields stay exactly as they were.
# ===========================================================================
BURST_GAP_NS = 5_000_000          # 5 ms; sits inside the measured bimodal void
OBSERVATION_WALL_NS = 20_000_000_000


def i2c_program_line(t, last_reg):
    """Register-programme line: writes verbatim, reads as (register, length)."""
    if t["dir"] == "W":
        return "%02X|W|%s" % (t["dev"], t["data"].hex().upper())
    reg = "%02X" % last_reg if last_reg is not None else "--"
    return "%02X|R|%s|n%d" % (t["dev"], reg, len(t["data"]))


def i2c_program_lines(txs):
    last, out = {}, []
    for t in txs:
        key = (t["bus"], t["dev"])
        if t["dir"] == "W" and t["data"]:
            last[key] = t["data"][0]
        out.append(i2c_program_line(t, last.get(key)))
    return out


def split_bursts(ticks, gap_ns=BURST_GAP_NS):
    """Return (list of index ranges, max intra-burst gap, min inter-burst gap)."""
    if not ticks:
        return [], None, None
    ranges, start = [], 0
    max_intra, min_inter = None, None
    for i in range(1, len(ticks)):
        g = ticks[i] - ticks[i - 1]
        if g > gap_ns:
            ranges.append((start, i))
            start = i
            min_inter = g if min_inter is None else min(min_inter, g)
        else:
            max_intra = g if max_intra is None else max(max_intra, g)
    ranges.append((start, len(ticks)))
    return ranges, max_intra, min_inter


def _train_block(ticks, lines, label):
    ranges, max_intra, min_inter = split_bursts(ticks)
    trains = {}
    for a, b in ranges:
        key = "|".join(lines[a:b])
        trains.setdefault(key, []).append((ticks[a], b - a))
    out = []
    for key, members in trains.items():
        starts = [t for t, _ in members]
        periods = [starts[i + 1] - starts[i] for i in range(len(starts) - 1)]
        out.append({
            "key_sha256": sha(key.encode()),
            "key_head": key[:96],
            "key_chars": len(key),
            "burst_transactions": members[0][1],
            "count": len(members),
            "starts_ns": starts,
            "period_ns": ({"min": min(periods), "median": sorted(periods)[len(periods) // 2],
                           "max": max(periods)} if periods else None),
        })
    out.sort(key=lambda e: (-e["count"], e["starts_ns"][0]))
    return {
        "label": label,
        "transaction_count": len(ticks),
        "burst_count": len(ranges),
        "train_count": len(out),
        "gap_separation": {
            "burst_gap_ns": BURST_GAP_NS,
            "max_intra_burst_gap_ns": max_intra,
            "min_inter_burst_gap_ns": min_inter,
            "separated": (max_intra is None or min_inter is None
                          or (max_intra <= BURST_GAP_NS < min_inter)),
        },
        "trains": out,
    }


def summarise_i2c_trains(txs):
    per_dev = {}
    for t in txs:
        name = I2C_DEVICES.get((t["bus"], t["dev"]), "unknown_0x%02X" % t["dev"])
        per_dev.setdefault(name, []).append(t)
    out = {}
    for name, dtx in per_dev.items():
        lines = i2c_program_lines(dtx)
        out[name] = _train_block([t["tick"] for t in dtx], lines, name)
    return out


def summarise_spi_trains(txs, label):
    if not txs:
        return {}
    lines = [spi_canonical_line(t) for t in txs]
    return {label: _train_block([t["tick"] for t in txs], lines, label)}


TRAIN_CRITERION_NOTE = {
    "name": "phase-tolerant stream criterion (whole run, train-anchored)",
    "why": (
        "Every field under peripherals/<bus>/phases is cut at the 6 s wall, so a "
        "periodic train that shifts in time gains or loses a burst inside the "
        "window and its count and stream_sha256 both move with NO change to what "
        "the firmware exchanged.  This block is anchored to the train instead."),
    "burst": "consecutive transactions on one (bus,device) separated by <= burst_gap_ns",
    "train_key": (
        "the burst's REGISTER PROGRAMME -- every write payload verbatim, every "
        "read reduced to (selected register, payload length).  I2C only; SPI "
        "bursts are keyed on the full tx|rx content."),
    "gates": [
        "P1 train set: the set of key_sha256 must be identical",
        "P2 population: per-train burst counts must be equal, or differ only by "
        "bursts the observation wall clipped, which is checked by extrapolating "
        "the train's own measured period across the wall",
        "P3 phase: |starts_ns[i] ours - starts_ns[i] shipped| <= phase_bound for "
        "every i, on trains whose alignment is unambiguous",
        "P4 cadence: gated THROUGH P3 -- a period error e accumulates to "
        "|delta| > bound after ceil(bound/e) bursts",
        "P5 order: a reordering is admissible only when every burst involved "
        "stays within phase_bound of its counterpart",
    ],
    "phase_measurable": (
        "a train is phase-measurable iff max|delta| < min(period)/2; above that "
        "the i-th-to-i-th correspondence is ambiguous and the train's phase "
        "carries no information (its content and population are still gated)"),
    "strict_fields_retained": [
        "peripherals/<bus>/phases/<phase>/transaction_count",
        "peripherals/<bus>/phases/<phase>/stream_sha256",
        "peripherals/<bus>/phases/<phase>/stream_sha256_regprog",
        "peripherals/<bus>/phases/<phase>/devices/<dev>/stream_sha256",
        "peripherals/twim2/phases/<phase>/devices/lsm6dso_imu/analogue_sample_payloads",
    ],
}


def summarise_regaccess(accesses, periph=None):
    if not accesses:
        return {"access_count": 0, "note": "peripheral never accessed by the firmware"}
    entries = [{"op": a["op"], "reg": a["reg"], "offset": a["offset"],
                "value": a["value"]} for a in accesses]
    reg_hist = {}
    for a in accesses:
        reg_hist[a["reg"]] = reg_hist.get(a["reg"], 0) + 1

    ptr_regs = POINTER_REGS.get(periph, set())
    ptr_order = {}          # reg -> [raw values, first-appearance order]

    def canon_value(a):
        if a["reg"] in ptr_regs:
            seq = ptr_order.setdefault(a["reg"], [])
            if a["value"] not in seq:
                seq.append(a["value"])
            return "PTR#%d" % seq.index(a["value"])
        return a["value"]

    stream = "\n".join("%s|%s|%s" % (a["op"], a["offset"], canon_value(a))
                       for a in accesses)
    out = {
        "access_count": len(accesses),
        "stream_sha256": sha(stream.encode()),
        "register_histogram": dict(sorted(reg_hist.items())),
        "distinct_pcs": sorted({a["pc"] for a in accesses}),
        "accesses_rle": rle(entries),
    }
    if ptr_order:
        out["stream_sha256_raw_pointers"] = sha("\n".join(
            "%s|%s|%s" % (a["op"], a["offset"], a["value"])
            for a in accesses).encode())
        out["pointer_registers_canonicalised"] = sorted(ptr_order)
        out["pointer_values_raw"] = {k: v for k, v in sorted(ptr_order.items())}
        out["pointer_alignment"] = {
            k: sorted({int(x, 16) & 3 for x in v})
            for k, v in sorted(ptr_order.items())}
        out["pointer_note"] = (
            "These registers carry a RAM ADDRESS supplied by a caller (SAADC "
            "RESULT.PTR is `saadc_start_read`'s param_2, a live stack frame). "
            "stream_sha256 hashes their FIRST-APPEARANCE INDEX, not the address, "
            "because a differently-linked image can never reproduce the address. "
            "stream_sha256_raw_pointers keeps the old, non-portable hash.")
    return out


# --------------------------------------------------------------------------
# SCREEN PROFILES.  The same capture machinery produces two oracles that differ
# ONLY in the stimulus (the navigation one writes the GATT command
# `0a0600000000`; the dashboard one writes nothing at all and lets the firmware's
# own IMU:wakeup branch pick E_ID_SCREEN_DASHBOARD).  Everything measured is
# identical in shape, so only the PROSE, the OUTPUT FILE NAMES and the
# PARITY-CRITERIA prefix are per-screen.  Before this existed the script emitted
# the navigation schema unconditionally, and regenerating the dashboard oracle
# would have silently deleted its D-1..D-7 criteria and its `screen` block
# (our_boot_bringup.md sec.42.10 item 8).
#
# Select with `--screen=dashboard` (default `navigation`).
SCREEN_PROFILES = {
    "navigation": {
        "schema": "g1.display_sensor_oracle/1",
        "outfile": "display_sensor_oracle.json",
        "fb_prefix": "golden_framebuffer_%s",
        "what": ("Peripheral-transaction oracle of the SHIPPED Even G1 firmware: "
                 "every display (SPI/JBD) and sensor (I2C/PDM/SAADC/GPIOTE/ESB) "
                 "transaction the original performs, captured in Renode under "
                 "the same determinism knobs as golden_boot_trace.json."),
        "regenerate": (
            "recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_oracle && "
            "PYTHONSAFEPATH=1 .venv/bin/python "
            "recon/emulator/scripts/build_display_sensor_oracle.py /tmp/g1_oracle"),
        "phases": {
            "p1_boot": "t=0..6 s — autonomous boot + virtual BLE central connect/GATT",
            "p2_render": "t=6..20 s — 'don' head-up gesture on the real LSM6DSO model -> display START -> ESB L/R sync -> dashboard blit",
        },
        "stimulus": ("identical to armemul/scripts/g1-selfdrive.sh: "
                     "vcentral (virtual phone, real radio CONNECT_IND + NUS ATT write "
                     "'0a0600000000'), esbslave (virtual right lens, AnnounceResponse), "
                     "lsm6dso PlayGesture 'don'"),
    },
    "dashboard": {
        "schema": "g1.display_sensor_oracle_dashboard/1",
        "outfile": "display_sensor_oracle_dashboard.json",
        "fb_prefix": "golden_framebuffer_dashboard_%s",
        "what": ("Peripheral-transaction oracle of the SHIPPED Even G1 firmware driven "
                 "to E_ID_SCREEN_DASHBOARD (screen id 6) by REAL STIMULUS ONLY -- no "
                 "memory pokes, no forced state. Sibling of display_sensor_oracle.json "
                 "(which captures E_ID_SCREEN_NAVIGATION). The ONLY difference in "
                 "stimulus is that the virtual phone sends NO GATT command at all: with "
                 "the navigation-startup command 0a0600000000 suppressed, nothing "
                 "installs a persist task, so process_for_new_task stays in case 0 "
                 "(IDLE) and the 'don' head-up gesture takes the firmware's own "
                 "IMU:wakeup:dashboard branch (update_temp_task_status(device_ctx, 6, 2) "
                 "at 0x0002e1a2) into the dashboard."),
        "regenerate": (
            "G1_ATT_WRITE=\"\" G1_SEED=305419896 "
            "recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_oracle_dash && "
            "PYTHONSAFEPATH=1 .venv/bin/python "
            "recon/emulator/scripts/build_display_sensor_oracle.py --screen=dashboard "
            "/private/tmp/g1_oracle_dash"),
        "phases": {
            "p1_boot": ("t=0..6 s -- autonomous boot + virtual BLE central connect. NO "
                        "GATT command is written. The panel is initialised and cleared; "
                        "NOTHING is painted (framebuffer stays all-zero)."),
            "p2_render": ("t=6..20 s -- 'don' head-up gesture on the real LSM6DSO model "
                          "-> imu_fusion_thread sets device_ctx[0xee4]=2 -> "
                          "process_for_new_task case 0 takes the IMU:wakeup:dashboard "
                          "branch -> ctx[0xd5]=6 -> ui_refalsh_warp case 6 -> "
                          "ui_DashBoard_task -> continuous dashboard repaint."),
        },
        "stimulus": ("vcentral (virtual phone, real radio CONNECT_IND, handle sweep, NO "
                     "ATT write), esbslave (virtual right lens, AnnounceResponse), "
                     "lsm6dso PlayGesture 'don' at t=6 s. NO memory write, NO register "
                     "poke, NO forced state anywhere."),
        "screen": {
            "screen_id_ctx_d5": 6,
            "name": "E_ID_SCREEN_DASHBOARD",
            "evidence": [
                "process_for_new_task FUN_0002c99c case 6 log 0xa2aad = '%s(): switch -> E_ID_SCREEN_DASHBOARD\\n', tag 0xa39bb = 'process_for_DASHBOARD_show'",
                "ui_refalsh_warp 0x00048b5c case 6 -> ui_DashBoard_task 0x0003af78",
                "selected at 0x0002e1a2: movs r2,#2 / movs r1,#6 / bl 0x2bffc (update_temp_task_status) then trigger_screen_state_change with reason string 0xa2733 = 'IMU:wakeup:dashboard'",
                "a whole-image BL scan finds NO update_persist_task_status(_,6,_) call site: the dashboard is not phone-commandable",
            ],
            "renders": ("date 'Mon, Jan 1', large '00:00' clock, Bluetooth glyph, "
                        "vertical divider, note glyph, 'Hold Right TouchBar / to Add "
                        "QuickNote' hint"),
        },
    },
}


def dashboard_determinism_verification(oracle):
    """Dashboard `determinism_verification`, derived from the SEEDED measurement.

    The block this replaces was written from two UNSEEDED runs and listed
    `spim_a/p2_render`, `twim2/p2_render` and `JBD_FRAMECOUNTER_P2` as
    non-deterministic.  Iteration 41 proved the net core's stock RNG is
    re-seeded randomly per launch when `emulation SetSeed` is not issued, and
    iteration 42 measured those three streams byte-identical across two SEEDED
    shipped runs.  The old annotation was therefore excusing a real 3,013-
    transaction gap on our build.  It is gone, and what replaces it is a
    statement of what was actually measured.
    """
    fb = oracle["framebuffer"]
    spim = oracle["peripherals"]["spim_a"]["phases"]
    return {
        "method": ("the whole dashboard capture was run twice end-to-end WITH "
                   "`emulation SetSeed 305419896` (G1_SEED) and the two capture "
                   "directories compared with `cmp` file by file, including the "
                   "nanosecond tick column of every trace"),
        "seed": "0x12345678 (305419896) — `emulation SetSeed` before platform creation",
        "bit_identical_across_runs": [
            "EVERY trace file byte-for-byte: spim_a.p{1,2}, spim_b.p{1,2}, "
            "twim1.p{1,2}, twim2.p{1,2}, fb_p1_boot.ppm, fb_p2_render.ppm",
            "framebuffer/*/sha256 and every row_sha256",
            "peripherals/spim_a/phases/*/stream_sha256 AND transaction_count "
            "(p1_boot %d, p2_render %d)" % (
                spim["p1_boot"]["transaction_count"],
                spim["p2_render"]["transaction_count"]),
            "peripherals/twim2/phases/*/stream_sha256 AND transaction_count",
            "peripherals/twim1/phases/*/devices/*/stream_sha256",
            "peripherals/{pdm0,saadc,gpiote0,gpiote1}/whole_run/stream_sha256",
            "counters/* — including JBD_FRAMECOUNTER_P2, RADIO_TX, "
            "VC_DATA_EVENTS, ESB_MASTER_FRAMES and ESB_ACKS",
            "firmware_events",
        ],
        "NOT_stable_across_runs": {
            "peripherals/twim1/phases/*/stream_sha256": (
                "the MERGED twim1 bus stream. The per-device sub-streams are "
                "identical; only the interleaving between OPT3001 / nPM1300 / "
                "ST25DV (three independent firmware threads sharing one bus) "
                "reorders. Diff twim1 PER DEVICE, not per bus."),
        },
        "WITHDRAWN_annotations": {
            "peripherals/spim_a/phases/p2_render": (
                "PREVIOUSLY annotated 'run1 12225, run2 12161 -- not stable, gate on "
                "the framebuffer instead'. WITHDRAWN: those two runs were UNSEEDED. "
                "Seeded, the shipped image gives %d in both runs, and the annotation "
                "was masking a real, stable deficit on our rebuilt image "
                "(our_boot_bringup.md sec.42.1 item 3)." % spim["p2_render"]["transaction_count"]),
            "peripherals/twim2/phases/p2_render": (
                "PREVIOUSLY 'run1 1206, run2 1202'. WITHDRAWN for the same reason; "
                "seeded it is %d in both runs." % oracle["peripherals"]["twim2"][
                    "phases"]["p2_render"]["transaction_count"]),
            "counters/JBD_FRAMECOUNTER_P2": (
                "PREVIOUSLY 'run1 0x2E65, run2 0x2E27'. WITHDRAWN; seeded it is %s "
                "in both runs." % counters_get(oracle, "JBD_FRAMECOUNTER_P2")),
            "counters/RADIO_TX, VC_DATA_EVENTS, ESB_MASTER_FRAMES, ESB_ACKS, ESB_ANNOUNCE_RESP": (
                "PREVIOUSLY '+/- 1-11 frames of radio-model cadence'. WITHDRAWN as a "
                "DETERMINISM statement: seeded, every one of them is identical across "
                "two shipped runs. A tolerance may still be justified when comparing a "
                "DIFFERENTLY-LINKED image, but that is a comparison tolerance and must "
                "be argued on its own; it is not licensed by run-to-run noise, because "
                "there is none."),
        },
        "what_this_now_FAILS_to_catch": (
            "Nothing in the shipped capture is excused any more except the merged "
            "twim1 bus interleaving, which is genuinely a three-thread arbitration "
            "order on one bus and is fully covered by the per-device sub-streams. "
            "The residue that remains unmeasured is what the per-device split "
            "deliberately drops: the RELATIVE ORDER of transactions belonging to "
            "different devices on twim1. A defect that reorders OPT3001 against "
            "nPM1300 without changing either device's own stream is invisible here."),
        "fb_%s" % "p2_render": {
            "sha256": fb["p2_render"]["sha256"],
            "lit_pixels": fb["p2_render"]["lit_pixels"],
        },
    }


def counters_get(oracle, key):
    v = oracle.get("counters", {}).get(key)
    return v if v is not None else "(absent)"


def dashboard_parity_criteria(oracle):
    """The D-* criteria, regenerated from the measurement in hand.

    Every criterion of the recorded oracle is preserved.  D-1/D-2/D-3 carry
    their oracle VALUES inline, so they are formatted from this capture rather
    than copied, which is what keeps a regenerated file self-consistent.  The
    one change of substance is the final bullet: the "NOT A GATE (measured
    non-deterministic)" line is replaced by D-8/D-9, which promote
    `spim_a p2_render` and `JBD_FRAMECOUNTER_P2` to real gates.
    """
    fb = oracle["framebuffer"]
    spim = oracle["peripherals"]["spim_a"]["phases"]
    bb = fb["p2_render"]["bbox"] or {}
    bbtxt = ("bbox (%d,%d)-(%d,%d) %dx%d" % (
        bb.get("x0", 0), bb.get("y0", 0), bb.get("x1", 0), bb.get("y1", 0),
        bb.get("w", 0), bb.get("h", 0))) if bb else "bbox (empty)"
    return {
        "note": ("These are the DASHBOARD criteria (prefix D-). They are INDEPENDENT "
                 "of and ADDITIVE to the navigation criteria G-1..G-6 / S-* in "
                 "display_sensor_oracle.json, which remain in force unchanged."),
        "graphics": [
            "D-1 PASS/FAIL (THE ACCEPTANCE BAR): framebuffer/p2_render/sha256 must "
            "match byte-for-byte (640x480x4bpp = 153600 B). Oracle = %s, %d lit "
            "pixels, %s." % (fb["p2_render"]["sha256"],
                             fb["p2_render"]["lit_pixels"], bbtxt),
            "D-2 PASS/FAIL: framebuffer/p1_boot/sha256 must match byte-for-byte. "
            "Oracle = %s (all-zero: with no GATT command nothing is painted in the "
            "first 6 s)." % fb["p1_boot"]["sha256"],
            "D-3 PASS/FAIL: peripherals/spim_a/phases/p1_boot/stream_sha256 must "
            "match (%d transactions: panel ID probe, brightness/gear registers, the "
            "three full-screen clears). Oracle = %s." % (
                spim["p1_boot"]["transaction_count"],
                spim["p1_boot"]["stream_sha256"]),
            "D-4 (localiser, not an extra gate): on a D-1 failure, "
            "framebuffer/p2_render/row_sha256 identifies the first differing panel "
            "row, and the first differing pixel inside it.",
            "D-5 PASS/FAIL: counters/SCREEN_ID_ctx_d5 must be 0x06 "
            "(E_ID_SCREEN_DASHBOARD). This is the honest-stimulus gate: it proves "
            "the firmware SELECTED the dashboard itself.",
            "D-6 PASS/FAIL: counters/DISPLAY_ON_ctx_fe8 == 0x01 and "
            "counters/ESB_SYNC_ctx_105a == 0x02.",
            "D-7 PASS/FAIL: peripherals/spim_b must be empty (0 transactions, both "
            "phases).",
            "D-8 PASS/FAIL (NEW, and it REPLACES a withdrawn exemption): "
            "peripherals/spim_a/phases/p2_render/transaction_count == %d and its "
            "stream_sha256 must match. The recorded oracle used to exempt this "
            "stream as non-deterministic; that annotation came from two UNSEEDED "
            "runs and is withdrawn (see determinism_verification/"
            "WITHDRAWN_annotations). Seeded, it is identical across shipped runs, "
            "and it is the repaint-cadence gate: the dashboard is a continuously "
            "repainting screen and this count is how many pixel windows the "
            "firmware completes in the 14 s phase." % spim["p2_render"]["transaction_count"],
            "D-9 PASS/FAIL (NEW, same provenance as D-8): "
            "counters/JBD_FRAMECOUNTER_P2 == %s. It is the panel-side view of the "
            "same repaint cadence and moves with D-8." % counters_get(
                oracle, "JBD_FRAMECOUNTER_P2"),
        ],
        "sensors": [
            "S-D-IMU: peripherals/twim2/phases/p1_boot/stream_sha256 must match "
            "(p2_render is cadence-dependent; compare volume with tolerance).",
            "S-D-I2C: peripherals/twim1/phases/*/devices/*/stream_sha256 must match "
            "PER DEVICE (never per bus).",
            "S-D-MIC/KEYS/ADC: peripherals/{pdm0,gpiote0,gpiote1,saadc}/whole_run/"
            "stream_sha256 must match.",
        ],
    }


def dashboard_screen_events(run_out, fw_events):
    """The `screen/observed_firmware_events` block, MEASURED from run.out.

    The recorded oracle carried these four numbers hand-derived; they are read
    off the consequence-hook lines here instead, so a regenerated file cannot
    silently keep a stale count.  Note that these lines only exist when the
    capture ran with G1_HOOKS=1 (i.e. against the SHIPPED image, whose PCs the
    hooks are written for); against a rebuilt image they are all absent and the
    block reports zeroes, which is correct and not a defect.
    """
    blit_screens = {}
    start_actions = []
    navtask = 0
    if os.path.exists(run_out):
        with open(run_out, "r", errors="replace") as fh:
            for line in fh:
                m = re.search(r"ORACLE BLIT notify_display_mode screen=(\d+)", line)
                if m:
                    k = int(m.group(1))
                    blit_screens[k] = blit_screens.get(k, 0) + 1
                    continue
                m = re.search(r"ORACLE display_START action=(\d+)", line)
                if m:
                    start_actions.append(int(m.group(1)))
                    continue
                if re.search(r"ORACLE ui_navigation_task", line):
                    navtask += 1
    return {
        "DashBoard_Reflash": fw_events.get("DashBoard_Reflash", 0),
        "notify_display_mode_by_screen_id": {str(k): v for k, v
                                             in sorted(blit_screens.items())},
        "display_START_actions_in_order": start_actions,
        "ui_navigation_task": navtask,
        "measured_from": "the G1_HOOKS=1 cpuapp consequence hooks in run.out",
    }


def main():
    argv = [a for a in sys.argv[1:]]
    screen = "navigation"
    rest = []
    for a in argv:
        if a.startswith("--screen="):
            screen = a.split("=", 1)[1]
        elif a in ("--dashboard", "--navigation"):
            screen = a[2:]
        else:
            rest.append(a)
    if screen not in SCREEN_PROFILES:
        sys.exit("unknown --screen=%s (known: %s)"
                 % (screen, ", ".join(sorted(SCREEN_PROFILES))))
    profile = SCREEN_PROFILES[screen]

    outdir = rest[0] if len(rest) > 0 else "/tmp/g1_oracle"
    repo = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
    reports = rest[1] if len(rest) > 1 else os.path.join(
        repo, "recon", "emulator", "reports")
    os.makedirs(reports, exist_ok=True)

    reg_access, counters, esb_frames, fw_events, journal = parse_run_out(
        os.path.join(outdir, "run.out"))

    oracle = {
        "schema": profile["schema"],
        "what": profile["what"],
        "images": {},
        "determinism": {
            "emulator": "Renode (armemul g1.resc, shipped images)",
            "global_quantum_s": "0.000010",
            "core_scheduling": "serial (MasterTimeSource.ExecuteInSerial=True in g1.resc)",
            "cc312_seed": "0x5340CC3105340CC3",
            "virtual_time_budget_s": 20.0,
            "phases": profile["phases"],
            "stimulus": profile["stimulus"],
            "observation_method": {
                "spim_a/spim_b": "additive opt-in TraceFile hook in armemul/models/NRF5340_SPIM.cs (logs the tx/rx buffers the model already built; default off)",
                "twim1/twim2": "additive opt-in TraceFile hook in armemul/models/NRF5340_TWIM.cs (logs the EasyDMA payloads; default off)",
                "pdm0/saadc/gpiote0/gpiote1": "Renode built-in `sysbus LogPeripheralAccess <p> true` (no model change)",
                "radio/esb": "existing model counters (radio TransmittedFrames, esbslave MasterFramesSeen/AcksInjected/AnnounceResponsesInjected, esbslave DumpFirstN)",
            },
        },
        "regenerate": profile["regenerate"],
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
            "whole_run_trains": {
                "criterion": TRAIN_CRITERION_NOTE,
                "burst_gap_ns": BURST_GAP_NS,
                "observation_wall_ns": OBSERVATION_WALL_NS,
                "devices": summarise_spi_trains(
                    all_spi.get(bus, []),
                    "jbd_display" if bus == "spim_a" else "none"),
            },
        }

    # ---------------- I2C / sensors --------------------------------------
    all_i2c = {}
    for bus in ("twim1", "twim2"):
        per_phase = {}
        for ph in PHASES:
            txs = parse_i2c(os.path.join(outdir, "%s.%s.trace" %
                                         (bus, ph.split("_")[0])))
            all_i2c.setdefault(bus, []).extend(txs)
            ordinals, samples = annotate_analogue_samples(txs)
            per_phase[ph] = {
                "transaction_count": len(txs),
                "stream_sha256": sha("\n".join(i2c_canonical_line(t)
                                               for t in txs).encode()),
                "devices": summarise_i2c(txs),
            }
            if samples:
                per_phase[ph]["stream_sha256_regprog"] = sha("\n".join(
                    i2c_regprog_line(t, o)
                    for t, o in zip(txs, ordinals)).encode())
        oracle["peripherals"][bus] = {
            "controller": ("TWIM1 @0x40009000 (SDA P0.05 / SCL P0.04)"
                           if bus == "twim1" else
                           "TWIM2 @0x4000B000 (SDA P1.02 / SCL P1.03, firmware label TWIM3)"),
            "devices_on_bus": [v for (b, _), v in I2C_DEVICES.items()
                               if b == bus.upper().replace("TWIM", "TWIM")],
            "phases": per_phase,
            "whole_run_trains": {
                "criterion": TRAIN_CRITERION_NOTE,
                "burst_gap_ns": BURST_GAP_NS,
                "observation_wall_ns": OBSERVATION_WALL_NS,
                "devices": summarise_i2c_trains(all_i2c.get(bus, [])),
            },
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
            "whole_run": summarise_regaccess(reg_access.get(periph, []), periph),
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

        fbname = profile["fb_prefix"] % ph
        base = os.path.join(reports, fbname)
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
                "raw": "recon/emulator/reports/%s.raw" % fbname,
                "pgm": "recon/emulator/reports/%s.pgm" % fbname,
                "png": "recon/emulator/reports/%s.png" % fbname,
                "crop_png": "recon/emulator/reports/%s_crop.png (lit bbox, 3x upscale, human-viewable only)" % fbname,
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

    if screen == "dashboard":
        # Everything below is derived from the measurement in hand, so a
        # regenerated dashboard oracle stays self-consistent instead of
        # carrying values from a previous (unseeded) capture.
        oracle["determinism_verification"] = dashboard_determinism_verification(oracle)
        oracle["parity_criteria"] = dashboard_parity_criteria(oracle)
        scr = dict(profile["screen"])
        scr["observed_firmware_events"] = dashboard_screen_events(
            os.path.join(outdir, "run.out"), fw_events)
        oracle["screen"] = scr

    outfile = os.path.join(reports, profile["outfile"])
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
