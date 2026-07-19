## review group param_0669  (1 cluster(s), kinds=param)

### proposal for param_0669
struct_name: dev_channel_mode | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Device channel-mode descriptor written by dev_write_channel_mode: a single mode/index field
fields:
  0x4  uint32_t     mode  read-only idx4

<ground-truth bundle for param_0669>
### cluster param_0669  (param, 1 members, 2 fields, size>=0xa)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dev_write_channel_mode @ 0x843ba  as param_2  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0669 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x8[0x2];   /* +0x8 pad */
};
```
