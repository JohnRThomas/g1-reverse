### cluster param_0022  (param, 2 members, 5 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - cjson_parse_value @ 0x12910  as param_1  [APPLICATION]
  - cjson_parse_string @ 0x64290  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0022 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=w types=ptr */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
    void *     field_0x10;   /* +0x10  sz=4 rw=w types=ptr */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=undefined4 */
    uint64_t   field_0x18;   /* +0x18  sz=8 rw=w types=undefined8 */
};
```