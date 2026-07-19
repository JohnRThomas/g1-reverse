## review group param_0062  (1 cluster(s), kinds=param)

### proposal for param_0062
struct_name: ipc_service_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Context object registered by register_ipc_service_context; tail two words appear to be output/callback pointers written by the register call.
fields:
  0x60  uint32_t     field_0x60  write-only, likely handle or status
  0x64  uint32_t     field_0x64  write-only, likely handle or status

<ground-truth bundle for param_0062>
### cluster param_0062  (param, 1 members, 2 fields, size>=0x68)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - register_ipc_service_context @ 0x25d40  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0062 {
    uint8_t    _pad_0x0[0x60];   /* +0x0 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=w types=undefined4 */
};
```
