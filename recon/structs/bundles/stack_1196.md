### cluster stack_1196  (stack, 1 members, 3 fields, size>=0x124)

Stack-frame local local_1c in bt_att_accept (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_att_accept @ 0x58930  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1196 {
    uint8_t    _pad_0x0[0x1e];   /* +0x0 pad */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x20[0xe];   /* +0x20 pad */
    uint16_t   field_0x2e;   /* +0x2e  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x30[0xf0];   /* +0x30 pad */
    uint32_t   field_0x120;   /* +0x120  sz=4 rw=r types=idx4 */
};
```