# COLLISION-20 fail-closed report: `0x0007d9c0`

Status: **retain the reconstruction; do not authorize the configured SDK
`crc16_reflect` owner**.

The readable-name catalog currently labels `FUN_0007d9c0` as
`crc16_reflect`. That identity is wrong. The shipped function is a configurable,
seven-argument CRC-16 implementation and is not ABI-, instruction-, or
control-flow-equivalent to Zephyr's configured four-argument
`crc16_reflect`.

## Firmware evidence

- Address/extent: `0x0007d9c0`, 138 bytes.
- Firmware extent SHA-256:
  `f139580dbdc1df0fd61ae6b4c3074a8096c380e4e2a988c615bc6d8bac8fbcfe`.
- Namespaced reconstructed source SHA-256:
  `6d10ec63a0024f0a1c8f3eb1797b5dd3dbff5f8080ff2d3264abec2287db0d6d`.
- Observed machine-word ABI (the CRC state is logically 16-bit):
  `unsigned configurable_crc16(unsigned seed, unsigned polynomial,
  unsigned xor_out, bool reflect_input, bool reflect_output,
  const uint8_t *src, size_t len)`.
- The first four arguments arrive in `r0` through `r3`; `reflect_output`,
  `src`, and `len` are loaded independently from the stack. The body can
  reverse every input byte, applies a caller-selected polynomial, can reverse
  the 16-bit result, and finally XORs the caller-selected output value.
- The authoritative verifier passes the retained body with two CFG-directed
  cases for the `reflect_input` selector: `FUN_0007d9c0 PASS cases=2`.

The sole recovered direct caller is `FUN_0007da4a` at `0x0007da4a`, currently
misnamed `crc16_ansi`. Its instructions establish the real closure: `r0` is a
caller-supplied seed, `r1`/`r2` are the source and length, and it calls the
seven-argument function with polynomial `0x8005`, XOR-out `0xffff`, and both
reflection flags set. The caller passes authoritative CFG verification with
four cases covering null source and non-positive length:
`FUN_0007da4a PASS cases=4`. Its namespaced retained source SHA-256 is
`20255f8d9a7acdaa6bdb2b943cab0f19f4a2cebf9b754eed5ee0e0f3781ba1af`.
The recovered `calc_flash_crc` caller was ABI-reconciled with the wrapper and
also passes authoritative verification: `FUN_00022974 PASS cases=4`.

## Configured Zephyr owner is a different function

Configured source: `zephyr/lib/crc/crc16_sw.c`, source SHA-256
`738d1382a4fede5d30f3e44070719e6bb45818e43f52842f5d53a7659ff878cc`.

Configured object SHA-256:
`503c615e86ab849c827afcd175194849648b656c3977407126e2ddccf6ffd86b`.
Its `.text.crc16_reflect` is 42 bytes with SHA-256
`a118102d4a564f306bbfe2de38512ca7f878728f368c4dc1ddf03d4689d1b74a`.
The section has **zero relocations**, so there are no address-bearing operands
that could be masked to improve the comparison. Only 3 of the 42 aligned bytes
match the firmware prefix, and the firmware continues for another 96 bytes.

The SDK ABI is instead
`uint16_t crc16_reflect(uint16_t polynomial, uint16_t seed,
const uint8_t *src, size_t len)`. It always uses the reflected right-shift
algorithm and has no XOR-out or independently selectable input/output
reflection. Conversely, the firmware uses a left-shift/MSB polynomial loop
after optionally reversing input bytes and optionally reverses the result.

The collision audit therefore correctly fails every identity gate: opcode
`0.314286`, operand shape `0.257143`, length `0.346154`, and
`normalized_exact=false`. The current collision-row receipt SHA-256 is
`958333a7f84cae01ba8202d1385085d6871f9789fa5d3a6d5655b75d3a1b2b18`.

## Safe closure plan

1. Keep `FUN_0007d9c0` reconstructed. Add no COLLISION-20 authorization and
   do not remove its canonical body on the basis of `crc16_sw.c`.
2. Correct the durable readable identity to a reconstruction-owned namespace,
   such as `g1_recon_crc16_configurable`, with the seven-argument ABI above.
   Correct the sole caller to a namespaced seeded ANSI wrapper and preserve
   both raw-address back-mappings.
3. Regenerate readable/symbolized/link metadata, then re-run authoritative CFG
   verification for both raw functions.
4. Rebuild retain-all. Namespace isolation must remove exactly the
   `crc16_reflect` collision while keeping the firmware body, introduce no new
   collision or undefined symbol, and leave the configured Zephyr
   `crc16_reflect` owner untouched.

This is namespace isolation of a retained firmware implementation, not SDK
adoption. It must not create an exclusion overlay or a weak/alias owner.
