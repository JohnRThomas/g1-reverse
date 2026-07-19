## review group param_0060  (1 cluster(s), kinds=param)

### proposal for param_0060
struct_name: ipc_ept_locked_retry_ctx | is_library: True | library_name: ipc_ept (Zephyr IPC service) | is_array: None | confidence: low
purpose: IPC endpoint operation context used by locked-retry handlers for OpenAMP/IPC-service endpoints B and C
fields:
  0x4  int32_t      retry_count  
  0x10  uint32_t     ept_state  

<ground-truth bundle for param_0060>
### cluster param_0060  (param, 2 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - ipc_ept_op_b_locked_retry @ 0x257ec  as param_1  [APPLICATION]
  - ipc_ept_op_c_locked_retry @ 0x25850  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0060 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
};
```
