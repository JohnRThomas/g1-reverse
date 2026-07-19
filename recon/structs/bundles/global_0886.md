### cluster global_0886  (global, 1 members, 2 fields, size>=0x3)

Global object at fixed address 0x000243e8.

library hint: likely G1-original

members (1 shown of 1):
  - SettingStoreHandler @ 0x23f04  as 0x000243e8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0886 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=rw types=byte,undefined1 */
};
```