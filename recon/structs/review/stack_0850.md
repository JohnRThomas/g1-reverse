## review group stack_0850  (1 cluster(s), kinds=stack)

### proposal for stack_0850
struct_name: ble_get_req_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local response/parse buffer in ble_process_get_req with header and trailer byte markers
fields:
  0x0  uint8_t      header_byte  idx1
  0xf4  uint8_t      trailer_byte  idx1

<ground-truth bundle for stack_0850>
### cluster stack_0850  (stack, 1 members, 2 fields, size>=0xf5)

Stack-frame local local_118 in ble_process_get_req (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ble_process_get_req @ 0x1a064  as local_118  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0850 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0xf3];   /* +0x1 pad */
    uint8_t    field_0xf4;   /* +0xf4  sz=1 rw=r types=idx1 */
};
```
