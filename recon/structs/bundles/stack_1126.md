### cluster stack_1126  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_f0 in img_mgmt_upload (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_upload @ 0x521fc  as local_f0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1126 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```