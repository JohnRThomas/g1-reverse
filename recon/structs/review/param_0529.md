## review group param_0529  (1 cluster(s), kinds=param)

### proposal for param_0529
struct_name: bt_gatt_discover_params | is_library: True | library_name: bt_gatt_discover_params | is_array: None | confidence: low
purpose: Zephyr GATT discovery parameters/context, whose error-completion path is handled by discovery_complete_error.
fields:
  0x4  uint32_t     field_0x4  discovery UUID or callback pointer
  0x15c  uint32_t     field_0x15c  end-handle or state field near struct tail

<ground-truth bundle for param_0529>
### cluster param_0529  (param, 1 members, 2 fields, size>=0x160)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - discovery_complete_error @ 0x7f40c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0529 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x154];   /* +0x8 pad */
    uint32_t   field_0x15c;   /* +0x15c  sz=4 rw=r types=idx4 */
};
```
