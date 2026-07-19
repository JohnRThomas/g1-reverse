## review group param_0114  (1 cluster(s), kinds=param)

### proposal for param_0114
struct_name: onboarding_ble_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Large onboarding/BLE processing context buffer with a status byte and a trailing pointer/handle
fields:
  0xcd  uint8_t      onboarding_state  
  0x1014  void *       conn_or_handle_ptr  

<ground-truth bundle for param_0114>
### cluster param_0114  (param, 1 members, 2 fields, size>=0x1018)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - onboarding_ble_process @ 0x42a64  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0114 {
    uint8_t    _pad_0x0[0xcd];   /* +0x0 pad */
    uint8_t    field_0xcd;   /* +0xcd  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xce[0xf46];   /* +0xce pad */
    void *     field_0x1014;   /* +0x1014  sz=4 rw=rw types=int,ptr */
};
```
