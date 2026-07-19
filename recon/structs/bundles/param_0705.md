### cluster param_0705  (param, 1 members, 6 fields, size>=0x2a)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dma_xfer_end_handler @ 0x857e0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0705 {
    uint32_t   field_0x0;   /* +0x0  sz=2,4 rw=r types=code,ushort */
    uint8_t    _pad_0x4[0xc];   /* +0x4 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x24[0x2];   /* +0x24 pad */
    uint16_t   field_0x26;   /* +0x26  sz=2 rw=rw types=undefined2,ushort */
    uint8_t    _pad_0x28[0x2];   /* +0x28 pad */
};
```