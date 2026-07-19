# G1 CPUAPP firmware boot-emulation plan

Status date: 2026-07-19  
Target: Even Realities G1 CPUAPP firmware, Nordic nRF5340 Cortex-M33  
Primary shipped image: `app_update.bin`  
Diagnostic patched image: `recon/diagnostics/qspi_ble_exporter/build/app_update_qspi_exporter.signed.bin`

## 1. Purpose and success criteria

The purpose of this work is to establish a repeatable, evidence-producing
firmware test environment before any reconstructed or diagnostically patched
image is installed on physical glasses.

The emulator is not intended to claim cycle-accurate nRF5340 equivalence.
Instead, it provides progressively stronger gates:

1. Validate MCUboot image parsing, vector-table placement and CPU reset state.
2. Execute small standalone Cortex-M33 diagnostic images.
3. Execute selected recovered firmware functions against modeled peripherals.
4. Execute the shipped CPUAPP image through reset and Zephyr initialization.
5. Execute the signed QSPI-exporter image through the same path.
6. Identify every point where progress depends on an unmodeled peripheral,
   interrupt, coprocessor or second CPU.
7. Permit narrowly documented diagnostic bypasses only when modeling the real
   dependency is not yet practical.
8. Produce deterministic traces that allow original and patched firmware to be
   compared under identical modeled hardware.

The first hardware-facing OTA test should happen only after:

- the signed image passes structural and cryptographic checks;
- the reset and kernel-start paths execute in emulation;
- the QSPI exporter passes a recovered-function diagnostic;
- malformed and out-of-bounds requests are rejected;
- the same image and OTA procedure have been exercised on the nRF5340 DK;
- an SWD recovery procedure has been tested.

## 2. Current verified facts

### 2.1 Image and reset state

Both the original and QSPI-exporter images use the same application vectors:

```text
MCUboot header size:       0x200
Application vector VA:    0x0000c200
Initial MSP:              0x200312f0
Reset handler raw value:  0x00050a99
Reset handler code VA:    0x00050a98
CPU mode:                 Cortex-M33 Thumb/M-profile
```

The original image SHA-256 is:

```text
e0614feb3609fc2f251a00c16ca66f01c9fb8153de81ca1818cab5f79b42fd3b
```

The signed QSPI-exporter image SHA-256 is:

```text
deb9f2abfa13bd295a22b79fa70dc6d28faa00d5379be0457e941e9543bd18de
```

The exporter image's RSA-2048 signature has been verified with OpenSSL. Its
key hash matches the key hash in the shipped image.

### 2.2 First exploratory boot result

A temporary Unicorn Cortex-M33 harness was used to load the application
payload at `0x0000c200`, initialize MSP/PC from the vector table, and map the
CPUAPP address space.

The first failure occurred after 12 instructions:

```text
Invalid read: 0x00ff0130
PC:           0x00064cc0
```

`0x00ff0000` is the nRF53 factory-information/configuration window. After
mapping that window and setting the NVMC READY register, the original firmware
executed approximately 453,000 instructions before reaching an SVC
instruction. Handling SVC through Unicorn's interrupt hook allowed continued
execution.

The original image subsequently executed 3,000,000 instructions without an
unmapped-memory fault. During that run it repeatedly entered Zephyr kernel,
logging, memory and scheduling code. This is evidence that:

- the vectors and reset state are correct;
- `.data`/`.bss` initialization progresses;
- substantial Zephyr initialization executes;
- the image reaches SVC-based kernel activity;
- there is no immediate corrupt-image, invalid-vector or early HardFault
  failure under the current model.

This is not yet proof of a complete application boot. Scheduler ticks,
interrupt delivery, CPUNET IPC and several peripherals are not modeled yet.

### 2.3 Authoritative boot inventory

Use:

```text
recon/catalogs/app_root_inventory.json
```

It records:

- vector entries;
- Zephyr initialization levels;
- exact initialization function addresses and owners;
- device objects;
- interrupt owners;
- static message queues;
- dynamic application and SDK threads.

The emulator should turn these addresses into named milestones rather than
reporting only raw program counters.

Important milestones include:

```text
0x0004c144  nordicsemi_nrf53_init
0x0006058c  clock_control_nrf_init
0x000637b8  sys_clock_driver_init
0x00060c00  qspi_nor_init
0x00061234  soc_flash_nrf_init
0x00061aec  mbox_nrfx_init
0x0007eb5c  ipc_static_vrings_init
0x00060174  bt_rpmsg_init
0x00051304  mcumgr_handlers_init
0x000526b4  smp_init
```

Application thread entries from the inventory must also be tracked. Reaching
one or more application thread bodies is a stronger gate than merely reaching
the kernel scheduler.

## 3. Planned directory structure

The intended durable layout is:

```text
tools/
  g1_boot_emulator.py             reusable emulator CLI and library
  test_g1_boot_emulator.py        deterministic unit/integration tests

recon/emulator/
  BOOT_EMULATION_PLAN.md          this handoff and design document
  README.md                       final user-facing usage guide
  diagnostics/
    linker.ld                     diagnostic image memory layout
    reset_smoke.S                 reset/vector/RAM/WFI smoke image
    qspi_recovered_read.S         calls recovered QSPI functions
    build_diagnostics.py          reproducible assembler/linker wrapper
    build/                        generated ELF/bin/disassembly artifacts
  fixtures/
    qspi_pattern.bin              deterministic synthetic QSPI contents
    expected_qspi_pattern.json    pattern formula/hash and checked ranges
  reports/
    reset_smoke.json
    qspi_recovered_read.json
    original_boot.json
    exporter_boot.json
    original_vs_exporter.json
    boot_blockers.md
  patches/
    README.md                     diagnostic-bypass policy and inventory
    *.json                        exact preimage/replacement records
```

Generated artifacts may be checked in when they are needed for reproducibility
or direct review. Large transient traces should remain outside the repository,
with hashes and summaries checked in.

## 4. Emulator architecture

### 4.1 CPU engine

Use Unicorn in:

```python
Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
```

The emulator must explicitly initialize:

- MSP from vector word zero;
- PC from vector word one, with Thumb state retained;
- XPSR T-bit (`0x01000000`);
- PRIMASK, BASEPRI and CONTROL to reviewed reset values;
- VTOR to `0x0000c200` when required by the startup path.

It must not treat arbitrary missing addresses as zero-filled RAM. Only reviewed
nRF5340 windows may be mapped. An unexpected access must stop the run and be
reported with:

- access kind;
- address and size;
- value for writes;
- current PC/LR/SP;
- containing function name;
- recent PC history;
- recent MMIO history.

### 4.2 Memory map

Initial map:

| Range | Purpose |
|---|---|
| `0x00000000–0x001fffff` | CPUAPP code/flash window |
| `0x00ff0000–0x00ffffff` | FICR/UICR/configuration window |
| `0x20000000–0x2007ffff` | CPUAPP SRAM |
| `0x40000000–0x40ffffff` | non-secure peripheral aliases |
| `0x50000000–0x50ffffff` | secure peripheral aliases |
| `0xe0000000–0xe00fffff` | PPB/NVIC/SCB/CoreDebug |

Later add the shared SRAM and CPUNET-facing windows only when observed by the
boot path.

### 4.3 Image loader

The loader must:

1. Parse and validate the 32-byte MCUboot header fields.
2. Require the known magic `0x96f3b83d`.
3. Read `hdr_size`, `img_size`, flags and load address.
4. Locate and validate the regular TLV header.
5. Load only the signed payload, not TLV bytes, into executable memory.
6. Place file offset `hdr_size` at virtual address `0x0000c200`.
7. Validate that initial MSP falls inside CPUAPP SRAM.
8. Validate that the reset vector is Thumb and falls inside the loaded image.
9. Record the input SHA-256 in every run report.

Support raw diagnostic ELF/bin images separately; do not confuse their format
with MCUboot images.

### 4.4 Trace model

Keep two trace levels:

- Summary: named function milestones, peripheral events, exceptions and stop
  reason.
- Diagnostic: bounded ring buffer of recent instructions and MMIO operations.

Do not retain every instruction from a multi-million-instruction boot in
memory. Maintain:

- total instruction count;
- unique function entries;
- first and last visit instruction for each milestone;
- hot-PC counts;
- SVC/WFI/WFE counts;
- MMIO read/write counts grouped by address;
- last 128–512 instruction addresses;
- last 128 MMIO operations.

## 5. Peripheral models

### 5.1 QSPI model

The QSPI model is the first required functional peripheral because the new BLE
exporter depends on it.

Relevant controller base:

```text
NRF_QSPI_BASE = 0x5002b000
```

Recovered `qspi_xfer` behavior:

| Register | Address | Meaning |
|---|---:|---|
| TASKS_ACTIVATE | `0x5002b000` | activate controller |
| TASKS_READ | `0x5002b004` | start QSPI-to-RAM transfer |
| TASKS_WRITE | `0x5002b008` | start RAM-to-QSPI transfer |
| EVENTS_READY | `0x5002b100` | operation completed |
| READ.CNT | `0x5002b504` | byte count |
| READ.DST | `0x5002b508` | destination SRAM address |
| READ.SRC | `0x5002b50c` | QSPI byte offset |
| WRITE.CNT | `0x5002b510` | byte count |
| WRITE.SRC | `0x5002b514` | source SRAM address |
| WRITE.DST | `0x5002b518` | QSPI byte offset |

When firmware writes `1` to TASKS_READ, the model must:

1. Read count, SRAM destination and QSPI offset from the registers.
2. Validate SRAM destination alignment and bounds.
3. Validate QSPI range without integer overflow.
4. Copy bytes from the synthetic/dump-backed QSPI store into SRAM.
5. Set EVENTS_READY to `1`.
6. Record one QSPI read event.

The initial model is read-only. TASKS_WRITE, erase instructions and chip erase
must be rejected and reported unless a specific test explicitly enables a
copy-on-write QSPI layer. No test should modify the source dump.

The model should support:

- a deterministic 32 MiB generated pattern;
- a user-supplied 32 MiB dump;
- sparse storage for tests that touch only selected regions;
- per-range SHA-256 verification;
- optional fault injection for read failures and truncation.

### 5.2 NVMC and configuration

Minimum initial model:

```text
NVMC READY @ 0x50039400 = 1
```

Configuration register writes must be recorded. Flash erase/write operations
must default to rejected/read-only behavior.

FICR/UICR values should be deterministic and documented. Start with zeroed
storage except for values required by observed startup branches. Promote a
field into the model only with a cited access and expected nRF5340 meaning.

### 5.3 CLOCK/POWER

Model task/event pairs for HFCLK and LFCLK:

- task write starts the modeled clock;
- corresponding event becomes `1`;
- status/source registers return deterministic configured values.

Do not mark every event register ready generically. Each modeled event needs a
named rule so a missing peripheral cannot silently appear functional.

### 5.4 RTC/timer and scheduler progress

The exploratory run reaches SVC-based kernel activity, but useful application
progress requires time.

Implement a deterministic virtual tick counter:

- advance based on executed instruction quanta, not wall-clock time;
- update the modeled RTC counter on reads;
- schedule compare events when the counter reaches CC values;
- eventually inject the correct IRQ through the firmware vector path.

Until interrupt injection is implemented, a diagnostic `cooperative-time`
mode may advance counter registers and skip WFI. This mode must be labeled as a
boot-progress aid, not a hardware-faithful result.

### 5.5 NVIC/SCB and exceptions

Required handling:

- SVC must be observed through Unicorn's interrupt hook without incorrectly
  advancing PC twice. The exploratory test showed that Unicorn already presents
  the post-SVC PC to the hook.
- WFI/WFE should stop a standalone diagnostic successfully, but in full boot
  mode should yield to pending modeled interrupts or virtual-time advancement.
- writes to NVIC enable/pending registers must be tracked.
- VTOR, AIRCR, CCR, SHCSR and fault-status registers must be modeled or stored.
- a genuine HardFault/MemManage/BusFault/UsageFault vector must be reported as
  a firmware fault, not treated as normal control flow.

### 5.6 IPC/CPUNET

The complete G1 application expects CPUNET to boot and communicate through
shared SRAM/rpmsg/OpenAMP.

Implement in stages:

1. Record CPUNET reset/release requests.
2. Model the shared SRAM range.
3. Provide a minimal mailbox event model.
4. Provide deterministic rpmsg endpoint readiness responses sufficient to
   observe CPUAPP behavior when CPUNET is absent.
5. Later run CPUNET concurrently or connect a second emulator instance.

Do not fabricate successful BLE operation merely by returning success from all
IPC calls. The boot report must distinguish:

- CPUAPP booted with CPUNET absent;
- CPUAPP reached BLE wait state;
- CPUAPP/CPUNET IPC handshake completed;
- BLE host/controller traffic was actually exchanged.

### 5.7 Remaining peripherals

Add models in observed-blocker order:

- GPIO and pinctrl;
- UARTE console/log sink;
- watchdog;
- I2C/TWIM with nPM1300, IMU and ambient-light stubs;
- PDM/audio;
- ADC;
- crypto/entropy;
- projector SPIM buses.

Each device stub should support explicit outcomes such as `ready`, `absent`,
`timeout` and `fault`. Startup should be tested under both expected presence and
absence where the production firmware has an error path.

## 6. Diagnostic firmware stages

### Stage D0: reset smoke image

Build a tiny image containing:

- vector table at `0x0000c200`;
- valid MSP;
- Thumb reset handler;
- one SRAM magic write;
- WFI.

Expected result:

```text
RAM marker = 0x47513142
stop reason = diagnostic WFI
no unexpected memory access
```

This proves the emulator, assembler/linker layout and reset machinery without
any dependency on the recovered firmware.

### Stage D1: QSPI MMIO smoke image

Use a small assembly program that programs the recovered QSPI READ registers,
starts TASKS_READ, waits for EVENTS_READY, validates a known pattern and writes
a pass/fail marker.

This isolates the QSPI model from the recovered driver implementation.

### Stage D2: recovered QSPI function image

Build a small reset/vector wrapper that calls the original recovered function:

```text
nrfx_qspi_read @ 0x00085206
```

Load only its reviewed dependency closure from `app_update.bin` at the original
addresses:

```text
nrfx_qspi_read     0x00085206
qspi_xfer          0x00066524
qspi_ready_wait    0x0006649c
qspi_activate      0x000664f0
```

The wrapper initializes the minimum recovered driver state at
`0x2000b348`, calls the function with an SRAM destination, known QSPI offset and
length, and verifies:

- return value `0x0bad0000`;
- expected SRAM bytes;
- exactly one modeled QSPI read;
- no write/erase event;
- correct READY behavior.

This is the principal gate for the QSPI exporter because it tests recovered
production code, not merely a synthetic register sequence.

### Stage D3: exporter handler unit image

Execute the appended handler at `0x000faa40` with a synthetic
`ble_process_get_req` stack/context/request state.

Test:

- valid read at offset zero;
- valid read crossing ordinary page boundaries;
- final valid read ending at `0x02000000`;
- zero length;
- length 181;
- offset equal to `0x02000000`;
- overflow in `offset + length`;
- mismatched declared lengths;
- QSPI read failure;
- non-`0x2f` command resumes at `0x0001a714`.

Capture the callback bytes and compare them to the documented response format.

### Stage D4: Zephyr DK diagnostic build

Build a small NCS 2.5.1 application for the nRF5340 DK with the same logical
QSPI-export protocol. Initially use a RAM-backed flash device if no external
QSPI chip is attached. Then repeat with a physical QSPI NOR part.

This validates BLE framing, disconnect/retry behavior and host tooling outside
the emulator.

## 7. Full-image boot stages

### Stage B0: original image, strict hardware model

Run from reset with only documented peripheral behavior. Stop on the first
unsupported dependency. Add one model at a time.

Every report should state the deepest reached phase:

```text
image parsed
reset entered
SoC init entered/completed
PRE_KERNEL_1 completed
PRE_KERNEL_2 completed
POST_KERNEL completed
APPLICATION init completed
scheduler entered
application thread entered
MCUmgr SMP initialized
BLE/CPUNET wait or handshake reached
idle loop reached
```

### Stage B1: exporter image, strict model

Run under the identical model and instruction budget. Before command `0x2f` is
invoked, the named milestone trace should match the original except for:

- MCUboot header `img_size`;
- the four-byte hook site, which is not executed during normal boot;
- appended unreachable diagnostic code;
- signature/TLV bytes, which are not loaded as application code.

Any earlier divergence is a critical patching or signing error.

### Stage B2: original-versus-exporter differential boot

Compare:

- ordered named milestones;
- MMIO trace through the shared prefix;
- SRAM writes through the shared prefix;
- exception sequence;
- scheduler/SVC sequence;
- stop reason;
- first divergence PC.

This is not the same as function parity. It is a system-level shared-prefix
check intended to prove that the dormant exporter patch does not perturb boot.

### Stage B3: exporter command after boot

Once a synthetic BLE context can be reached or injected, issue command `0x2f`
and validate the response against the QSPI fixture. This may initially be done
by invoking `ble_process_get_req` directly after a successful boot snapshot.

## 8. Diagnostic bypass-patch policy

The user has authorized precise patches to disable error paths when necessary.
That authorization should be used conservatively.

### 8.1 Preference order

For each blocker:

1. Model the real peripheral behavior.
2. Supply realistic reset/configuration data.
3. Inject the expected interrupt or CPUNET response.
4. Use a runtime emulator override that does not alter the image.
5. Only then create a binary diagnostic bypass.

### 8.2 Requirements for every binary bypass

Each patch must record:

- source image SHA-256;
- CPU virtual address and file offset;
- containing function and recovered name;
- original bytes and disassembly;
- replacement bytes and disassembly;
- exact branch condition/outcome changed;
- evidence that the path is caused by absent emulated hardware;
- normal behavior being simulated;
- affected registers/flags;
- rollback bytes;
- patched-image SHA-256;
- whether the image was re-signed;
- original-versus-patched boot trace divergence.

The patcher must refuse to run unless the source hash and preimage bytes match.

### 8.3 Acceptable bypasses

Examples:

- convert a bounded peripheral timeout failure into the success result the real
  ready peripheral would return;
- skip a fatal assert caused solely by an intentionally absent DK peripheral;
- force a device-ready branch for a device whose API behavior is separately
  modeled;
- bypass waiting for CPUNET only in a labeled CPUAPP-isolation profile.

### 8.4 Unacceptable bypasses

Do not:

- suppress HardFault globally;
- turn all device initialization calls into success;
- skip the entire Zephyr initialization framework;
- disable bounds checks or image verification;
- disable QSPI read errors in the exporter tests;
- patch scheduler or memory-corruption failures without root cause;
- call an image bootable merely because a fatal loop was bypassed.

## 9. Reports and stop reasons

Use machine-readable JSON plus a concise Markdown summary.

Suggested JSON fields:

```json
{
  "image": {"path": "...", "sha256": "..."},
  "profile": "strict|cooperative-time|cpunet-absent|diagnostic",
  "instruction_count": 0,
  "initial_sp": "0x...",
  "reset_handler": "0x...",
  "stop_reason": "...",
  "stop_pc": "0x...",
  "stop_function": "...",
  "milestones": [],
  "exceptions": [],
  "qspi_events": [],
  "unexpected_access": null,
  "hot_pcs": [],
  "recent_pcs": [],
  "model_assumptions": [],
  "diagnostic_patches": []
}
```

Canonical stop reasons:

```text
diagnostic_pass
diagnostic_fail
idle_with_no_pending_interrupt
instruction_budget
repeated_wait_loop
unsupported_mmio
unmapped_memory
cpu_exception
hardfault_vector
write_to_read_only_qspi
explicit_firmware_fatal
emulator_internal_error
```

## 10. Testing strategy

### 10.1 Unit tests

- MCUboot header and TLV parsing.
- Reset-vector validation.
- QSPI range and overflow checks.
- QSPI task register decoding.
- read-only rejection of writes/erases.
- deterministic QSPI pattern generation.
- report serialization.
- symbol/milestone lookup.
- exact patch preimage enforcement.

### 10.2 Integration tests

- D0 reset smoke.
- D1 direct QSPI MMIO.
- D2 recovered QSPI function closure.
- D3 exporter handler cases.
- original boot reaches a pinned milestone sequence.
- exporter boot reaches the same pinned milestone sequence.

### 10.3 Negative controls

Tests must fail when:

- the reset vector is altered;
- the QSPI READY event is never raised;
- QSPI data differs from the expected fixture;
- a QSPI write occurs;
- the exporter length cap is removed;
- the QSPI end bound is increased past 32 MiB;
- the four-byte hook preimage changes;
- the non-`0x2f` resume branch is redirected;
- the signed image digest or signature is corrupted.

## 11. Performance and determinism

The emulator should support instruction budgets rather than wall-time limits.
Initial budgets:

```text
D0 reset smoke:             10,000
D1 direct QSPI:             50,000
D2 recovered QSPI:         250,000
D3 exporter handler:       500,000 per case
B0/B1 exploratory boot:  3,000,000
B0/B1 extended boot:     25,000,000
```

All virtual time, random/entropy data, device identifiers and QSPI fixtures
must derive from explicit seeds included in the report.

## 12. DK validation plan

The nRF5340 DK is the recovery and realism bridge.

1. Verify SWD erase/reflash and recoverability with a trivial image.
2. Build an MCUboot + BLE SMP baseline using NCS 2.5.1.
3. OTA between two trivial signed versions.
4. Test wrong-key rejection and interrupted upload recovery.
5. Run the diagnostic request protocol against RAM-backed QSPI data.
6. Add a compatible external QSPI NOR chip when available.
7. Run the recovered-function-equivalent QSPI transaction sequence.
8. Confirm request-envelope byte offsets using a BLE capture.
9. Rebuild/re-sign the exporter if the inferred envelope differs.
10. Only after these gates consider a fully recoverable glasses test.

## 13. Exact continuation procedure

At the start of the next session:

```sh
cd /Users/freedomcoder/Projects/G1disasm2
git status --short
git log --oneline -5
sed -n '1,260p' recon/SESSION_COORDINATION.md
```

Remember for every Python invocation:

```sh
cd /tmp
PYTHONSAFEPATH=1 \
  /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/<script>
```

Then implement in this order:

1. Create `tools/g1_boot_emulator.py` with image parsing, reviewed memory maps,
   reset initialization, trace rings and strict unexpected-access reporting.
2. Add the QSPI read model and deterministic 32 MiB fixture.
3. Add `reset_smoke.S`, linker script and diagnostic builder.
4. Run D0 and save `reset_smoke.json`.
5. Add direct QSPI MMIO diagnostic D1.
6. Add recovered-function closure loader and run D2.
7. Add exporter-handler unit cases D3.
8. Load `app_root_inventory.json` and add named boot milestones.
9. Run original B0 at 3 million instructions.
10. Run exporter B1 under the identical model.
11. Generate a shared-prefix comparison report.
12. Identify the deepest common milestone and first genuine blocker.
13. Add the next peripheral model; avoid binary bypasses initially.
14. If a bypass becomes necessary, create a fail-closed patch manifest under
    `recon/emulator/patches/` and re-run original-versus-patched comparison.
15. Commit after each completed diagnostic or peripheral-model milestone.

## 14. Known risks and unresolved questions

- Unicorn is not a cycle-accurate nRF5340 simulator.
- M-profile exception and exclusive-access behavior may require workarounds.
- Full Zephyr scheduling requires deterministic interrupt/timer modeling.
- BLE depends on CPUNET; CPUAPP-only emulation cannot prove radio behavior.
- The QSPI map spans 32 MiB, while an older board document names an 8 MiB
  `MX25R6435F`. The compiled flash map is authoritative for address geometry,
  but the physical flash identity should be confirmed from hardware or SFDP.
- The exporter request envelope offsets remain inferred and must be confirmed
  on the DK or from a stock BLE capture.
- The current exporter calls `flash_settings_read`, which may retry and sleep on
  failure. Emulator and DK tests must cover this behavior.
- An emulated successful boot cannot replace physical peripheral testing; it
  reduces the first-device risk and makes failures diagnosable.

## 15. Definition of “bootable” used by this project

Use explicit levels rather than one ambiguous boolean:

| Level | Meaning |
|---|---|
| E0 | MCUboot image parses and vectors validate |
| E1 | reset handler executes and initializes memory |
| E2 | SoC and Zephyr pre-kernel initialization progresses |
| E3 | kernel scheduler/SVC path is reached without fault |
| E4 | application initialization completes |
| E5 | at least one recovered G1 application thread executes |
| E6 | MCUmgr/SMP service initialization completes |
| E7 | CPUAPP/CPUNET IPC handshake completes |
| E8 | diagnostic BLE request reaches handler and returns correct QSPI data |
| H1 | same image boots on DK with mocked/available peripherals |
| H2 | OTA and recovery procedure passes on DK |
| H3 | image boots on recoverable G1 hardware |

The exploratory original-image run currently establishes evidence through E3,
subject to formalizing the trace and SVC handling in the durable emulator.
No claim beyond E3 should be made yet.
