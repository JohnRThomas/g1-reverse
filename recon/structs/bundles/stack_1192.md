### cluster stack_1192  (stack, 1 members, 7 fields, size>=0xbd)

Stack-frame local local_44 in l2cap_recv (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - l2cap_recv @ 0x57db0  as local_44  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1192 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x8[0xc];   /* +0x8 pad */
    uint16_t   field_0x14;   /* +0x14  sz=2 rw=r types=undefined2 */
    uint16_t   field_0x16;   /* +0x16  sz=2 rw=r types=undefined2 */
    uint16_t   field_0x18;   /* +0x18  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x1a[0x2];   /* +0x1a pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x20[0x94];   /* +0x20 pad */
    uint8_t    field_0xb4;   /* +0xb4  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xb5[0x4];   /* +0xb5 pad */
    uint8_t    field_0xb9;   /* +0xb9  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xba[0x3];   /* +0xba pad */
};
```