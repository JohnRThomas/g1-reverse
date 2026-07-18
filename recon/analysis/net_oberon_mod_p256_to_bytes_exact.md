# CPUNET Oberon P-256 serializer identity correction

`FUN_01038fa4` is the pinned Oberon 3.0.13
`ocrypto_mod_p256_to_bytes`, not `ocrypto_mod_p256_from_bytes`.

The complete 52-byte firmware body is byte-exact to
`liboberon_3.0.13.a(ocrypto_mod_p256.c.obj)` section
`.text.ocrypto_mod_p256_to_bytes`; neither section has relocations. The
neighboring `from_bytes` owner is at `0x01038f70`.

The direction is unambiguous:

- `from_bytes` loads big-endian input words at ascending offsets and stores
  internal limbs at descending offsets.
- `to_bytes`—the body at `0x01038fa4`—loads internal limbs at descending
  offsets and stores big-endian output words at ascending offsets.

Call structure agrees. `ocrypto_curve_p256_to32bytes` at `0x01038d9c` is a
tail veneer, and `ocrypto_curve_p256_to64bytes` at `0x01038da0` invokes the
owner twice for the point's two 32-byte coordinates. The inferred internal ABI
is `void(uint8_t output[32], const ocrypto_mod_p256 *input)`, where the pinned
public type defines `ocrypto_mod_p256` as eight 32-bit words.

The exact archive Git blob is shared by all checked NCS 2.4.x and 2.5.x tags.
NCS 2.3.x carries Oberon 3.0.12 and NCS 2.6.x carries 3.0.14. Therefore this
body identifies the Oberon 3.0.13 family but cannot select an exact NCS patch;
the west-manifest pin supplies exact `v2.5.1` provenance.

The raw `FUN_01038fa4` back-map is retained. No central adoption manifest,
generated source tree, build configuration, or SDC decision is changed here.
