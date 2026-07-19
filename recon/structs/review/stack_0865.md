## review group stack_0865  (1 cluster(s), kinds=stack)

### proposal for stack_0865
struct_name: sys_setting_kv_local | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local key/value byte pair in load_sys_setting separated by an unused 15-byte gap (likely a name buffer).
fields:
  0x0  uint8_t      field_0x0  read-only byte, idx1
  0x10  uint8_t      field_0x10  read-only byte, idx1

<ground-truth bundle for stack_0865>
### cluster stack_0865  (stack, 1 members, 2 fields, size>=0x11)

Stack-frame local local_87 in load_sys_setting (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - load_sys_setting @ 0x22bd0  as local_87  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0865 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0xf];   /* +0x1 pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=idx1 */
};
```
