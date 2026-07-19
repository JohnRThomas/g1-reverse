### cluster param_0102  (param, 1 members, 2 fields, size>=0x3)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - send_whitelist_json_chunked @ 0x35498  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0102 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=w types=char,undefined1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=w types=char */
};
```