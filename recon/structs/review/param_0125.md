## review group param_0125  (1 cluster(s), kinds=param)

### proposal for param_0125
struct_name: md5_state | is_library: True | library_name: md5 digest context (generic MD5, e.g. mbedtls_md5_context.state) | is_array: True | confidence: medium
purpose: MD5 digest state (running hash words A/B/C/D) processed one 64-byte block at a time by md5_process_block.
fields:
  0x4  uint32_t     state_1  digest word (e.g. B)
  0x8  uint32_t     state_2  digest word (e.g. C)
  0xc  uint32_t     state_3  digest word (e.g. D)

<ground-truth bundle for param_0125>
### cluster param_0125  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - md5_process_block @ 0x49acc  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0125 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
