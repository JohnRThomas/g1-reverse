# CPUNET Oberon constant-time owner

The 92 firmware bytes at analysis addresses `0x01008810..0x0100886b` are
byte-for-byte identical to the complete `.text` section of
`liboberon_3.0.13.a(ocrypto_constant_time.s.obj)` from the pinned NCS 2.5.1
nrfxlib checkout. They contain `ocrypto_constant_time_equal`,
`ocrypto_constant_time_is_zero`, and the uncatalogued but linked
`ocrypto_constant_time_xor` tail.

Both catalogued APIs require `length > 0`. Their assembly uses a do/while
decrement, so a verifier-generated zero count means 2^32 iterations and caused
the sweep timeouts. It is a violated API precondition, not firmware
nontermination. CFG verification now uses controlled lengths 1, 2, 3, and the
only callers' actual P-256 width 32, with equal/non-equal and zero/nonzero byte
fixtures. Mutations of each accumulation operator are rejected.

This receipt changes no SoftDevice Controller decision. SDC internals remain
report-only. The receipt records both exact public names alongside the durable
raw identities `FUN_01008810` and `FUN_01008838`; the generated-name catalog is
updated separately because it is shared by concurrent integration work.
