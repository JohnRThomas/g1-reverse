# COLLISION-04 fail-closed report: `0x00067e8c`

Status: **retain the reconstruction; do not authorize an SDK-owner adoption**.

The collision catalog currently labels `FUN_00067e8c` as
`nrfx_dppi_channel_alloc`. That identity is wrong. The shipped function is
`nrfx_wdt_channel_alloc` and is not ABI-, instruction-, or data-access-equivalent
to the configured `nrfx_dppi.c` public owner.

## Firmware evidence

- Address/extent: `0x00067e8c`, 114 bytes.
- Firmware SHA-256 over the 114-byte extent:
  `6a25aa415c2096bcbeb4b87db5ba3c49700439ccaf0be7df85c07143c60376ef`.
- ABI observed from the instructions and matching NRFX declaration:
  `nrfx_err_t nrfx_wdt_channel_alloc(nrfx_wdt_t const *p_instance,
  nrfx_wdt_channel_id *p_channel_id)`.
- `r0` is an instance pointer: the body loads the instance index from
  `[r0 + 4]` and the WDT register base from `[r0]`. `r1` is the output channel
  pointer and is independently null-checked.
- The body indexes an 8-byte-per-instance control-block array at
  `0x2000b41c`, reads/writes its state and allocation index, and sets a bit in
  the WDT `RREN` register at `p_instance->p_reg + 0x508`.
- Embedded assertion strings are `p_channel_id` and
  `p_cb->state == NRFX_DRV_STATE_INITIALIZED`. The embedded source path is
  `WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c`.
- The raw reconstruction `FUN_00067e8c` passes authoritative CFG-directed
  side-effect verification: `PASS cases=2`, with selector values for argument
  1 of `[0, 1]`.
- The current reference graph reports no recovered direct callers. This does
  not repair the public ABI mismatch and is not adoption authority.

## Configured DPPI owner is a different function

Configured source:
`modules/hal/nordic/nrfx/drivers/src/nrfx_dppi.c`, source SHA-256
`de8b37587b86c3af4e415615ada6ff625728afa5b67d3699d9a477b0333efaf6`.

Configured object SHA-256:
`a07cb1177a412b85f8338d2bc0de297c86a342919a437591c4762e046c627dc2`.
Its `.text.nrfx_dppi_channel_alloc` is 12 bytes with SHA-256
`2eeed0628de30defc1b20191e233a08656d918fe30e6956c5459d4acf843629f`.

Its ABI is `nrfx_err_t nrfx_dppi_channel_alloc(uint8_t *p_channel)`. The
entire implementation moves `r0` to `r1`, loads the address of the single
global `m_allocated_channels` into `r0`, and tail-calls
`nrfx_flag32_alloc`. It has no instance argument, WDT control-block access,
assertion path, or peripheral-register write.

The collision audit's normalized scores therefore correctly fail every gate:
opcode `0.122449`, operand shape `0.040816`, length `0.113636`, and
`normalized_exact=false`. Relocation masking cannot reconcile an ABI and CFG
that are structurally different.

## Correct semantic candidate and remaining mismatch

The configured `nrfx_wdt.c` source SHA-256 is
`a60b782155f5e3c8184f4cfc7458aa11720117704c712f321ca7d41eef4d0b7c`.
Its selected-build `nrfx_wdt_channel_alloc` section has the correct two-argument
ABI and WDT data/register accesses, but is only 84 bytes (section SHA-256
`acfabbfd06fc0a685884012b1ac1d7c1c7187452a6cb2b12bab0d8e2bd67844a`).
The configured build compiled out the two firmware assertion paths, so this is
also not an exact replacement under the current configuration.

## Safe closure plan

1. Correct the durable name/back-map for `0x00067e8c` to
   `nrfx_wdt_channel_alloc`, and correct `0x2000b41c` from the misleading
   `m_dppi_channels` name to the WDT `m_cb` control-block array. Audit the
   adjacent `0x00067d84..0x00067f1c` WDT cluster before applying those shared
   naming changes.
2. Reproduce the firmware NRFX assertion policy and rebuild `nrfx_wdt.c`; then
   compare the WDT owner with relocation-masked operands, assertion calls,
   global accesses, and CFG-directed side effects.
3. Audit every retained/public symbol contributed by `nrfx_wdt.c.obj` as one
   source-unit closure. Do not remove only this reconstruction while a
   differently configured WDT object supplies related state and functions.
4. Authorize an exclusion only if that rebuilt WDT source unit is exact and
   introduces no new undefined or wrong-owner symbols. Otherwise retain the
   recovered WDT unit. The configured DPPI owner may remain, but it is not the
   owner of firmware address `0x00067e8c`.

No adoption-manifest authorization or retained-source exclusion is permitted
for COLLISION-04 from the present evidence.
