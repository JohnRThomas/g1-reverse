### cluster param_0159  (param, 2 members, 13 fields, size>=0x92c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - parse_app_id_config_stream @ 0x4f1d0  as param_1  [APPLICATION]
  - invoke_object_callback_864 @ 0x7f7c8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0159 {
    uint8_t    _pad_0x0[0x864];   /* +0x0 pad */
    void *     field_0x864;   /* +0x864  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x868[0x94];   /* +0x868 pad */
    uint32_t   field_0x8fc;   /* +0x8fc  sz=4 rw=rw types=int */
    uint32_t   field_0x900;   /* +0x900  sz=4 rw=rw types=uint,undefined4 */
    uint32_t   field_0x904;   /* +0x904  sz=4 rw=rw types=int */
    uint8_t    field_0x908;   /* +0x908  sz=1 rw=rw types=undefined1 */
    uint8_t    field_0x909;   /* +0x909  sz=1 rw=w types=char */
    uint8_t    _pad_0x90a[0x6];   /* +0x90a pad */
    uint16_t   field_0x910;   /* +0x910  sz=2 rw=rw types=undefined2,ushort */
    uint8_t    _pad_0x912[0x2];   /* +0x912 pad */
    uint32_t   field_0x914;   /* +0x914  sz=4 rw=rw types=uint,undefined4 */
    uint8_t    field_0x918;   /* +0x918  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x919[0x3];   /* +0x919 pad */
    uint16_t   field_0x91c;   /* +0x91c  sz=2 rw=rw types=short,ushort */
    uint8_t    _pad_0x91e[0x2];   /* +0x91e pad */
    uint32_t   field_0x920;   /* +0x920  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x924;   /* +0x924  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x928;   /* +0x928  sz=4 rw=w types=undefined4 */
};
```