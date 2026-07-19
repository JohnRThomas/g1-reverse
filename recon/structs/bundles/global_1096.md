### cluster global_1096  (global, 1 members, 2 fields, size>=0x8)

Global object at fixed address 0x0004f850.

library hint: likely G1-original

members (1 shown of 1):
  - app_event_manager_submit @ 0x4f770  as 0x0004f850  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1096 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```