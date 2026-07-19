## review group global_1166  (1 cluster(s), kinds=global)

### proposal for global_1166
struct_name: bt_dev | is_library: True | library_name: bt_dev | is_array: None | confidence: medium
purpose: Zephyr BLE host global device-state singleton (accessed here by bt_id_add for identity/OOB flags near end of struct)
fields:
  0x120  uint8_t      field_0x120  read-only flag/count byte
  0x121  uint8_t      field_0x121  read-write flag byte, e.g. id_count or oob_local flag

<ground-truth bundle for global_1166>
### cluster global_1166  (global, 1 members, 2 fields, size>=0x122)

Global object at fixed address 0x00055090.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_id_add @ 0x5505c  as 0x00055090  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1166 {
    uint8_t    _pad_0x0[0x120];   /* +0x0 pad */
    uint8_t    field_0x120;   /* +0x120  sz=1 rw=r types=byte */
    uint8_t    field_0x121;   /* +0x121  sz=1 rw=rw types=byte */
};
```
