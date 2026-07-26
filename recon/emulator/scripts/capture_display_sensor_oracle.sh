#!/bin/sh
# =============================================================================
# Graphics + sensor parity ORACLE capture — SHIPPED Even G1 firmware in Renode.
#
# Captures, for the ORIGINAL images, every peripheral transaction that carries
# graphics or sensor semantics, in a form our rebuilt firmware can be diffed
# against transaction-by-transaction and pixel-by-pixel:
#
#   * SPI (spim_a) -> JBD 640x480 4bpp microdisplay: full ordered transaction
#     log (opcode + payload + MISO), i.e. the panel init/ID probe, the
#     brightness/gear register writes and every 0x02 pixel-window blit.
#   * SPI (spim_b): the alternate display backend (no device attached) — traced
#     to prove the original never uses it.
#   * I2C twim1 -> OPT3001 ambient light (0x45), nPM1300 charger/fuel gauge
#     (0x6B), ST25DV NFC EEPROM (0x53 + system port 0x57).
#   * I2C twim2 -> LSM6DSO IMU (0x6B).
#   * PDM0 (microphone) and SAADC: register-level access trace (Renode's
#     built-in `sysbus LogPeripheralAccess`), which shows whether/how the
#     original programs them and with what DMA pointers.
#   * GPIOTE0/1 (touch / case-detect / button edge sources): register-level
#     access trace.
#   * ESB / RADIO L<->R sync path: modeled-radio counters + the first master
#     PTX frames in full.
#
# Stimulus is IDENTICAL to armemul/scripts/g1-selfdrive.sh (the acceptance
# harness): virtual BLE central connects over the modeled radio, writes a real
# G1 NUS frame, a 'don' head-up gesture is played on the real LSM6DSO model,
# and a virtual ESB right lens completes the L+R sync so the dashboard blits.
# Determinism knobs are IDENTICAL to the golden boot trace.
#
# READ-ONLY w.r.t. the reconstruction: this drives the SHIPPED app_update.bin /
# netcore_image.bin only.
#
# Usage:  recon/emulator/scripts/capture_display_sensor_oracle.sh [OUTDIR]
# Default OUTDIR = /tmp/g1_oracle
#
# ---------------------------------------------------------------------------
# Iteration 14 (ADDITIVE): the same capture can be pointed at OUR REBUILT
# images instead of the shipped ones, so the two runs are produced by exactly
# one script under exactly the same determinism knobs and stimulus.  With no
# variables set the behaviour is byte-for-byte the original oracle capture.
#
#   G1_RESC      machine script to include   (default $ARMEMUL/g1.resc)
#   G1_APP_ELF   app  zephyr.elf  -> emits `$app_elf=@...` before the include
#   G1_NET_ELF   net  zephyr.elf  -> emits `$net_elf=@...` before the include
#   G1_HOOKS     0 disables the four cpuapp consequence hooks (their PCs are
#                ORIGINAL-image addresses; our build relocates them) (default 1)
#   G1_CTX_FE8   address of device_ctx+0xfe8   (default 0x20054138, original)
#   G1_CTX_105A  address of device_ctx+0x105a  (default 0x200541aa, original)
#   G1_P1_SECS   phase-1 length (default 6)
#   G1_P2_SECS   phase-2 length (default 14)
#   G1_ATT_WRITE hex payload of the single GATT (NUS) write the virtual phone
#                performs during phase 1.  Default "0a0600000000" == the
#                navigation-startup command (BLE opcode 0x0a, sub-command 0),
#                which is what the original oracle captures.  Set to the empty
#                string to send NO GATT command at all: the phone still
#                connects and the link still comes up, but no BLE screen is
#                requested, so the `don` head-up gesture drives the firmware
#                into E_ID_SCREEN_DASHBOARD instead (see
#                display_sensor_oracle_dashboard.json / our_boot_bringup.md
#                iteration 34).  No memory is written either way.
#   G1_SCREEN_ID address of device_ctx+0xd5 (the live screen id) to read back
#                at the end of the run; default 0x20053225 (original image).
#
# Example (our build):
#   G1_RESC=$ARMEMUL/g1-ours.resc \
#   G1_APP_ELF=/private/tmp/g1-i14b-app/zephyr/zephyr.elf \
#   G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
#   G1_HOOKS=0 recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours
# ---------------------------------------------------------------------------
# =============================================================================
set -eu

OUT="${1:-/tmp/g1_oracle}"
ARMEMUL="${ARMEMUL:-/Users/freedomcoder/Projects/armemul}"
RENODE="${RENODE:-$HOME/tools/Renode.app/Contents/MacOS/renode}"
G1_RESC="${G1_RESC:-$ARMEMUL/g1.resc}"
G1_APP_ELF="${G1_APP_ELF:-}"
G1_NET_ELF="${G1_NET_ELF:-}"
G1_HOOKS="${G1_HOOKS:-1}"
G1_CTX_FE8="${G1_CTX_FE8:-0x20054138}"
G1_CTX_105A="${G1_CTX_105A:-0x200541aa}"
G1_P1_SECS="${G1_P1_SECS:-6}"
G1_P2_SECS="${G1_P2_SECS:-14}"
G1_ATT_WRITE="${G1_ATT_WRITE-0a0600000000}"
G1_SCREEN_ID="${G1_SCREEN_ID:-0x20053225}"
# Emitted verbatim into the capture script; empty => the phone sends no command.
if [ -n "$G1_ATT_WRITE" ]; then
  G1_ATT_WRITE_LINE="vcentral QueueAttWrite \"$G1_ATT_WRITE\""
else
  G1_ATT_WRITE_LINE=""
fi

mkdir -p "$OUT"
rm -f "$OUT"/*.trace "$OUT"/*.ppm "$OUT"/run.out "$OUT"/capture.resc

RESC="$OUT/capture.resc"
cat > "$RESC" <<EOF
# GENERATED by recon/emulator/scripts/capture_display_sensor_oracle.sh
${G1_APP_ELF:+\$app_elf=@$G1_APP_ELF}
${G1_NET_ELF:+\$net_elf=@$G1_NET_ELF}
i @$G1_RESC

# ================= DETERMINISM KNOBS (same as golden_boot_trace) ============
emulation SetGlobalQuantum "0.000010"
sysbus.cc3xx_rng Seed 0x5340CC3105340CC3
# core scheduling is serial (MasterTimeSource.ExecuteInSerial = True in g1.resc)
# ===========================================================================

# Global log = Error only, so the peripheral traces below are the only volume.
logLevel 3
logLevel 1 sysbus.pdm0
logLevel 1 sysbus.saadc
logLevel 1 sysbus.gpiote0
logLevel 1 sysbus.gpiote1
logLevel 1 esbslave
sysbus LogPeripheralAccess sysbus.pdm0 true
sysbus LogPeripheralAccess sysbus.saadc true
sysbus LogPeripheralAccess sysbus.gpiote0 true
sysbus LogPeripheralAccess sysbus.gpiote1 true

# ---- opt-in payload traces (additive model hooks, default off) -------------
sysbus.spim_a TraceFile @$OUT/spim_a.p1.trace
sysbus.spim_b TraceFile @$OUT/spim_b.p1.trace
sysbus.twim1  TraceFile @$OUT/twim1.p1.trace
sysbus.twim2  TraceFile @$OUT/twim2.p1.trace

# ---- stimulus: verbatim from armemul/scripts/g1-selfdrive.sh --------------
vcentral Enabled true
vcentral SweepHandles true
vcentral SweepLoop true
vcentral SweepStartHandle 0x0F
vcentral SweepMaxHandle 0x15
vcentral SweepDwell 4
$G1_ATT_WRITE_LINE
esbslave Enabled true
esbslave AnnounceResponse true
esbslave DumpFirstN 4

# ---- display / sensor consequence hooks (observation only) ----------------
EOF
if [ "$G1_HOOKS" = "1" ]; then
cat >> "$RESC" <<EOF
sysbus.cpuapp AddHook 0x47724 "cpu.Log(LogLevel.Error,'ORACLE spi_read_id')"
sysbus.cpuapp AddHook 0x2bc2c "cpu.Log(LogLevel.Error,'ORACLE display_START action=%d' % cpu.GetRegisterUnsafe(2).RawValue)"
sysbus.cpuapp AddHook 0x2948c "cpu.Log(LogLevel.Error,'ORACLE BLIT notify_display_mode screen=%d' % cpu.GetRegisterUnsafe(0).RawValue)"
sysbus.cpuapp AddHook 0x3727c "cpu.Log(LogLevel.Error,'ORACLE DashBoard_Reflash')"
EOF
fi
cat >> "$RESC" <<EOF

# ================== PHASE 1: autonomous boot + BLE link ====================
echo "ORACLE_PHASE_BEGIN p1_boot"
emulation RunFor "$G1_P1_SECS"
echo "ORACLE_PHASE_END p1_boot"
echo "ORACLE_VTIME_P1:"
machine ElapsedVirtualTime
echo "ORACLE_JBD_FRAMECOUNTER_P1:"
sysbus.spim_a.jbd FrameCounter
sysbus.spim_a.jbd DumpFrame @$OUT/fb_p1_boot.ppm

# rotate the payload traces at the phase boundary
sysbus.spim_a TraceFile @$OUT/spim_a.p2.trace
sysbus.spim_b TraceFile @$OUT/spim_b.p2.trace
sysbus.twim1  TraceFile @$OUT/twim1.p2.trace
sysbus.twim2  TraceFile @$OUT/twim2.p2.trace

# ================== PHASE 2: 'don' gesture -> dashboard render =============
echo "ORACLE_PHASE_BEGIN p2_render"
sysbus.twim2.lsm6dso PlayGesture "don"
emulation RunFor "$G1_P2_SECS"
echo "ORACLE_PHASE_END p2_render"
echo "ORACLE_VTIME_P2:"
machine ElapsedVirtualTime

sysbus.spim_a TraceClose
sysbus.spim_b TraceClose
sysbus.twim1  TraceClose
sysbus.twim2  TraceClose

# ================== FINAL STATE / COUNTERS =================================
sysbus.spim_a.jbd DumpFrame @$OUT/fb_p2_render.ppm
echo "ORACLE_JBD_FRAMECOUNTER_P2:"
sysbus.spim_a.jbd FrameCounter
echo "ORACLE_JBD_JOURNALCOUNT:"
sysbus.spim_a.jbd JournalCount
echo "ORACLE_RADIO_TX:"
radio TransmittedFrames
echo "ORACLE_VC_CONNECT_INDS:"
vcentral ConnectIndsSent
echo "ORACLE_VC_CONNECTED:"
vcentral Connected
echo "ORACLE_VC_DATA_EVENTS:"
vcentral DataEventsAnswered
echo "ORACLE_ESB_MASTER_FRAMES:"
esbslave MasterFramesSeen
echo "ORACLE_ESB_ACKS:"
esbslave AcksInjected
echo "ORACLE_ESB_ANNOUNCE_RESP:"
esbslave AnnounceResponsesInjected
echo "ORACLE_DISPLAY_ON_ctx_fe8:"
sysbus ReadByte $G1_CTX_FE8
echo "ORACLE_ESB_SYNC_ctx_105a:"
sysbus ReadByte $G1_CTX_105A
echo "ORACLE_SCREEN_ID_ctx_d5:"
sysbus ReadByte $G1_SCREEN_ID
echo "ORACLE_IMU_ACCEL_ENABLED:"
sysbus.twim2.lsm6dso AccelerometerEnabled
echo "ORACLE_IMU_GYRO_ENABLED:"
sysbus.twim2.lsm6dso GyroscopeEnabled
echo "ORACLE_OPT3001_CONVERSION_READY:"
sysbus.twim1.opt3001 ConversionReady
echo "ORACLE_NPM1300_CHARGING:"
sysbus.twim1.npm1300 ChargingEnabled
echo "ORACLE_JBD_JOURNAL_BEGIN"
sysbus.spim_a.jbd GetJournal
echo "ORACLE_JBD_JOURNAL_END"
quit
EOF

echo "[oracle] running Renode ($RESC) ..."
( cd "$ARMEMUL" && "$RENODE" --disable-xwt --console --plain -e "i @$RESC" ) > "$OUT/run.out" 2>&1 || true
echo "[oracle] done. raw artifacts in $OUT"
ls -la "$OUT"
