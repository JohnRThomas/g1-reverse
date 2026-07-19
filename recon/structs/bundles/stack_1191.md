### cluster stack_1191  (stack, 1 members, 4 fields, size>=0x28)

Stack-frame local local_14 in bt_l2cap_connected (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_l2cap_connected @ 0x5791c  as local_14  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1191 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=uint */
    uint16_t   field_0x14;   /* +0x14  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x16[0xe];   /* +0x16 pad */
    uint16_t   field_0x24;   /* +0x24  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x26[0x2];   /* +0x26 pad */
};
```