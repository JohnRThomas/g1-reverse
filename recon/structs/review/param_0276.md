## review group param_0276  (1 cluster(s), kinds=param)

### proposal for param_0276
struct_name: net_buf | is_library: True | library_name: net_buf | is_array: None | confidence: medium
purpose: Zephyr net_buf network buffer object manipulated by net_buf_reset and wrapped by cbor_nb_writer_init for CBOR encoding.
fields:
  0x4  uint32_t     ref  reference count (net_buf.ref)
  0x9  uint8_t      flags  buffer flags byte
  0xc  uint32_t     len  buffer data length
  0x10  uint16_t     size  buffer allocated size, write-only here (reset)
  0x14  uint32_t     data  pointer/offset to buffer data start

<ground-truth bundle for param_0276>
### cluster param_0276  (param, 2 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - net_buf_reset @ 0x5ee6c  as param_1  [APPLICATION]
  - cbor_nb_writer_init @ 0x80830  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0276 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x1];   /* +0x8 pad */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=char */
    uint8_t    _pad_0xa[0x2];   /* +0xa pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int,undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=undefined4 */
};
```
