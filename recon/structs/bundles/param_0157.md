### cluster param_0157  (param, 3 members, 19 fields, size>=0x868)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - ancs_gatt_dm_assign_handles @ 0x4ee68  as param_2  [APPLICATION]
  - ancs_subscribe_notification_source @ 0x4f040  as param_1  [APPLICATION]
  - ancs_subscribe_data_source @ 0x4f0ec  as param_1  [APPLICATION]

layout notes: overlap at 0x3 (prev field ends 0x4); overlap at 0xa (prev field ends 0xc); overlap at 0xe (prev field ends 0x10); overlap at 0x20e (prev field ends 0x20f); overlap at 0x216 (prev field ends 0x217)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0157 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=2,4 rw=rw types=idx4,undefined2 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x1fd];   /* +0x10 pad */
    uint16_t   field_0x20d;   /* +0x20d  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x20f[0x6];   /* +0x20f pad */
    uint16_t   field_0x215;   /* +0x215  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x217[0x611];   /* +0x217 pad */
    uint32_t   field_0x828;   /* +0x828  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x82c[0xa];   /* +0x82c pad */
    uint16_t   field_0x836;   /* +0x836  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x838[0x4];   /* +0x838 pad */
    uint32_t   field_0x83c;   /* +0x83c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x840[0x4];   /* +0x840 pad */
    uint32_t   field_0x844;   /* +0x844  sz=4 rw=r types=idx4 */
    uint32_t   field_0x848;   /* +0x848  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x84c[0xa];   /* +0x84c pad */
    uint16_t   field_0x856;   /* +0x856  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x858[0x4];   /* +0x858 pad */
    uint32_t   field_0x85c;   /* +0x85c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x860[0x4];   /* +0x860 pad */
    uint32_t   field_0x864;   /* +0x864  sz=4 rw=r types=idx4 */
};
```