### cluster param_0213  (param, 1 members, 5 fields, size>=0xa0)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_get_info @ 0x56f4c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0213 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x84];   /* +0xc pad */
    uint32_t   field_0x90;   /* +0x90  sz=4 rw=r types=idx4 */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x98[0x4];   /* +0x98 pad */
    uint32_t   field_0x9c;   /* +0x9c  sz=4 rw=r types=idx4 */
};
```