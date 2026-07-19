## review group param_0530  (1 cluster(s), kinds=param)

### proposal for param_0530
struct_name: ble_discovery_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: BLE GATT discovery context object handled by discovery_complete_not_found when a discovery search finishes without a match
fields:
  0x4  uint32_t     discover_state  
  0x15c  uint32_t     discover_tail_field  

<ground-truth bundle for param_0530>
### cluster param_0530  (param, 1 members, 2 fields, size>=0x160)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - discovery_complete_not_found @ 0x7f438  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0530 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x154];   /* +0x8 pad */
    uint32_t   field_0x15c;   /* +0x15c  sz=4 rw=r types=idx4 */
};
```
