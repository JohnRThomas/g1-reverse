### cluster global_1117  (global, 1 members, 2 fields, size>=0x10)

Global object at fixed address 0x00051a3c.

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_upload_inspect @ 0x518a8  as 0x00051a3c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1117 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```