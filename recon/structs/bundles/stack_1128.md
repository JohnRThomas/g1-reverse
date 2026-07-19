### cluster stack_1128  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local local_d4 in img_mgmt_upload (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_upload @ 0x521fc  as local_d4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1128 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```