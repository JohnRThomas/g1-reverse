# Read-only BLE QSPI exporter diagnostic patch

This directory produces a signed diagnostic variant of the shipped CPUAPP
image. It adds reserved GET command `0x2f`, which reads bounded chunks from the
existing initialized QSPI device. It does not add any erase or write path.

The only replacement inside existing executable code is at `0x0001a710`:

```text
before: 0d 4b 1b 68    ldr r3,[pc,#52]; ldr r3,[r3]
after:  e0 f0 96 b9    b.w 0x000faa40
```

Commands other than `0x2f` execute the two displaced loads in the appended
handler and resume at `0x0001a714`, preserving the original error path.

## Wire format

The diagnostic request uses the same assembled GET request envelope used by
the stock handler:

```text
packet[0]       = 0x2f
packet[2:4]     = declared length, at least 10
request[1:3]    = same declared length
request[5:9]    = QSPI offset, little-endian uint32
request[9]      = byte count, 1..180
```

The response is:

```text
[0]      0x2f
[1]      0xc9 success, 0xca error
[2]      0 success, 1 invalid request, 2 QSPI read failed
[3]      returned byte count
[4:8]    requested QSPI offset
[8:]     data
```

All offsets are restricted to the recovered 32 MiB QSPI range. Reads use the
stock `flash_settings_read` function at `0x000225b4`, including its existing
device-ready check and retry behavior.

## Reproduce

From `/tmp`, run:

```sh
PYTHONSAFEPATH=1 \
  /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/recon/diagnostics/qspi_ble_exporter/build_patch.py
```

Generated files appear in `build/`, including the signed image, handler and
hook disassembly, signature material, and `manifest.json` with hashes and exact
patch bytes.

## Safety status

The artifact is signed and structurally verified, but it is not authorized for
the glasses until the request-envelope offsets are confirmed on the Nordic DK
or from a captured stock GET request. First test malformed requests, boundary
offsets, disconnects, and concurrent MCUmgr activity on the DK. Do not run the
export command while an OTA upload is writing the QSPI secondary slot.
