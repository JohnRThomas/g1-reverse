### cluster param_0079  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - process_for_new_message_come_on @ 0x2c498  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0079 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x2[0x5];   /* +0x2 pad */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=rw types=byte,char,undefined1 */
};
```