### cluster stack_1001  (stack, 1 members, 4 fields, size>=0x5c)

Stack-frame local local_7c in DashBoard_Reflash (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - DashBoard_Reflash @ 0x3727c  as local_7c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1001 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x4c];   /* +0xc pad */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
};
```