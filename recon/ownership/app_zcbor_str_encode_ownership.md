# CPUAPP zcbor static string encoder ownership

`FUN_00086228` is the independently callable static `str_encode` body from
NCS 2.5.1's pinned zcbor `src/zcbor_encode.c`, not an interior alias. Its exact
Thumb extent is `[0x00086228, 0x0008629e)` (118 bytes); the following entry is
`zcbor_int_encode`.

With `ZCBOR_STOP_ON_ERROR` enabled, GCC 12.2 emits an instruction-exact body:
all 118 bytes match after masking only the four `R_ARM_THM_CALL` relocation
words at offsets `0x18`, `0x3c`, `0x54`, and `0x68`. The two direct references
are typed tail veneers at `0x00086338` (CBOR major type 2, byte string) and
`0x0008633e` (major type 3, text string).

The canonical readable reconstruction preserves the raw address identity and
the exact return value from the nested header encoder. `cfg_verify` passes six
directed cases covering both capacity guards, nested-header failure, copying,
and in-place success.
