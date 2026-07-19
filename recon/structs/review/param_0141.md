## review group param_0141  (1 cluster(s), kinds=param)

### proposal for param_0141
struct_name: ipc_rpmsg_backend_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: RPMsg IPC backend registration context (endpoint pointer plus a config word)
fields:
  0x4  void *       ept_ptr  
  0x10  uint32_t     backend_flags  

<ground-truth bundle for param_0141>
### cluster param_0141  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ipc_rpmsg_backend_register @ 0x4cd4c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0141 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
