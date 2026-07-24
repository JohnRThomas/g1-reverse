# CPUNET FLASH divergence — emulator boot-parity enlargement

**Status:** deliberate emulator-vs-device divergence. Tracked; not the endgame fix.

## Summary

The cohesive CPUNET link is symbol-clean (**0 undefined, 0 duplicate**) but its
image span is **227,961 B**, which overflows the *real* usable net FLASH region
(256 KiB − 0x8800 load offset = **227,328 B**) by **633 B**. To unblock emulator
bring-up, the modeled net FLASH region was enlarged so the image links and a
loadable `zephyr.elf` is produced. Duplication elimination (the real fix) is
deferred to the byte-match endgame.

## The numbers

| Image | Size | Usable region (256K − 0x8800) | Fit |
|-------|------|-------------------------------|-----|
| Shipped `netcore_image.bin` | **225,632 B** | 227,328 B | fits, **1,696 B spare** |
| Our cohesive recovered build | **227,961 B** | 227,328 B | **overflows by 633 B** |

Our build is **227,961 − 225,632 = 2,329 B (~2.3 KiB) larger** than the shipped
image. This is a genuine **recovered↔SDK duplication residual**: the cohesive
build links lean recovered code alongside separately-compiled SDK archives
(MPSL/SDC/ESB/nrf_rpc/OpenAMP/kernel), so some functionality is present both as a
recovered reconstruction and again inside a pulled-in SDK archive member. It is
**not** bloat in the recovered sources and **not** a link defect.

## What was changed (the exact enlargement)

The linker derives the net FLASH region (no partition manager in this single-image
build — confirmed) as, from
`zephyr/include/zephyr/arch/arm/aarch32/cortex_m/scripts/linker.ld`:

```
ORIGIN = CONFIG_FLASH_BASE_ADDRESS + CONFIG_FLASH_LOAD_OFFSET   = 0x01000000 + 0x8800 = 0x01008800
LENGTH = CONFIG_FLASH_SIZE*1K       − CONFIG_FLASH_LOAD_OFFSET
```

`CONFIG_FLASH_SIZE` is derived from the devicetree `flash1` node reg size. The
authoritative knob is therefore the `flash1` reg size. It was enlarged from
**256 KiB → 260 KiB (+4 KiB, two 2048 B erase blocks)** via an auto-included net
overlay:

- **File:** `recon/application/net/app.overlay`
- **Change:** `&flash1 { reg = <0x01000000 DT_SIZE_K(260)>; };`

This grows `LENGTH` (usable FLASH) from **227,328 B → 231,424 B (226 KiB)**
**without moving the load base `0x01008800`** — mandatory, because the net image
is position-DEPENDENT and only runs linked/loaded at runtime base `0x01008800`
(`CONFIG_FLASH_LOAD_OFFSET=0x8800` is unchanged).

**Nothing else changed.** No recovered code was dropped, no
`--allow-multiple-definition`, no weak symbols, no unproven SDK-alias trims.

## Build result (actually run)

`recon/application/build_cohesive.sh net /private/tmp/g1-netfit -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF`

```
Memory region   Used Size   Region Size   %age Used
       FLASH:   227961 B    226 KB        98.50%
```

- **FLASH used:** 227,961 B / **231,424 B (226 KiB)** limit → **3,463 B headroom**.
- **0 undefined** (`arm-zephyr-eabi-nm -u zephyr.elf` → 0 symbols).
- **0 duplicate** (link succeeded with retain-all OFF; no "multiple definition").
- **ELF:** `/private/tmp/g1-netfit/zephyr/zephyr.elf`.
- Image end LMA (from readelf LOAD segments): **0x01040279**.

## This is an emulator-vs-device divergence

The physical nRF5340 network core has exactly **256 KiB** of FLASH. The shipped
firmware fits it. Our 260 KiB model is fiction that exists only to let the
duplication-inflated cohesive image link for emulator bring-up. **Real-device fit
requires eliminating the recovered↔SDK duplication** (the ~2.3 KiB residual) so
the image drops back under 227,328 B — that is the byte-match endgame, tracked
separately and **not** done here. The sanctioned ESB-leaf trim was already proven
to make the overflow ~5× worse, so no trimming was attempted here.

## Renode fit (informational for P4)

The emulator platform `armemul/platforms/nrf5340.repl` models the net flash as:

```
flash_net: Memory.MappedMemory @ sysbus 0x01000000
    size: 0x40000        # 256 KiB → ends at 0x01040000
```

Loaded at `0x01008800`, our image ends at LMA **0x01040279**, which **exceeds the
Renode `flash_net` region end `0x01040000` by 0x279 = 633 B** (the same 633 B, as
expected — Renode's 256 KiB region ends exactly where the real usable region does).

**Therefore the enlarged image will NOT fit the current Renode `flash_net`
region.** P4 must enlarge `flash_net` in `armemul/platforms/nrf5340.repl` to at
least `size: 0x41000` (260 KiB, matching the DT model above) so the whole image
plus headroom is mapped. (armemul is READ-ONLY for this task; this is a note for
the next phase, not a change made here.)
