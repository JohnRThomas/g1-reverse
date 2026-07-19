## review group global_1168  (1 cluster(s), kinds=global)

### proposal for global_1168
struct_name: ble_privacy_id_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global state used by BLE privacy identity removal
fields:
  0x120  uint8_t      field_0x120  
  0x121  uint8_t      field_0x121  read/write, possibly status/refcount

<ground-truth bundle for global_1168>
### cluster global_1168  (global, 1 members, 2 fields, size>=0x122)

Global object at fixed address 0x000551dc.

library hint: likely G1-original

members (1 shown of 1):
  - ble_privacy_id_remove @ 0x55094  as 0x000551dc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1168 {
    uint8_t    _pad_0x0[0x120];   /* +0x0 pad */
    uint8_t    field_0x120;   /* +0x120  sz=1 rw=r types=byte */
    uint8_t    field_0x121;   /* +0x121  sz=1 rw=rw types=byte */
};
```
