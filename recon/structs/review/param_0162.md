## review group param_0162  (1 cluster(s), kinds=param)

### proposal for param_0162
struct_name: module_state_event | is_library: True | library_name: nRF Connect SDK CAF: struct module_state_event | is_array: None | confidence: medium
purpose: CAF (Common Application Framework) module_state_event carrying a module name pointer and state, handled by module_state_event_log_handler.
fields:
  0x4  const char * module  pointer, likely module name string
  0x8  void *       field_0x8  pointer, purpose unclear (possibly unused/name dup)
  0xc  uint8_t      state  byte, module_state enum value

<ground-truth bundle for param_0162>
### cluster param_0162  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - module_state_event_log_handler @ 0x4f860  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0162 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=byte */
    uint8_t    _pad_0xd[0x3];   /* +0xd pad */
};
```
