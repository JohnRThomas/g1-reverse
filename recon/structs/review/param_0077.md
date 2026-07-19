## review group param_0077  (1 cluster(s), kinds=param)

### proposal for param_0077
struct_name: system_suspend_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Large global system state/context object referenced by global_system_suspend during power-suspend handling.
fields:
  0xb70  void*        field_0xb70  pointer to a subsystem context or callback
  0xfe6  uint8_t      field_0xfe6  read-write status/flag byte near end of struct

<ground-truth bundle for param_0077>
### cluster param_0077  (param, 1 members, 2 fields, size>=0xfea)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - global_system_suspend @ 0x2bd7c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0077 {
    uint8_t    _pad_0x0[0xb70];   /* +0x0 pad */
    void *     field_0xb70;   /* +0xb70  sz=4 rw=r types=ptr */
    uint8_t    _pad_0xb74[0x472];   /* +0xb74 pad */
    uint8_t    field_0xfe6;   /* +0xfe6  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0xfe7[0x3];   /* +0xfe7 pad */
};
```
