## review group param_0647  (1 cluster(s), kinds=param)

### proposal for param_0647
struct_name: net_buf_simple_state | is_library: True | library_name: struct net_buf_simple | is_array: False | confidence: medium
purpose: Zephyr net_buf_simple header describing a buffer's length, size and backing storage, read by net_buf_simple_tailroom.
fields:
  0x1  uint16_t     len  current buffer length (offset approximate/unaligned in candidate layout)
  0x6  uint16_t     size  total buffer capacity
  0x8  uint8_t*     buf  pointer to backing storage (__buf)

<ground-truth bundle for param_0647>
### cluster param_0647  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_simple_tailroom @ 0x83730  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0647 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x3[0x3];   /* +0x3 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=ushort */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
