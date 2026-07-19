## review group param_0026  (1 cluster(s), kinds=param)

### proposal for param_0026
struct_name: esbs_ipc_msg | is_library: False | library_name:  | is_array: None | confidence: low
purpose: IPC message structure passed to local_esbs_ipc_service_recv, holding four consecutive index/data words
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0026>
### cluster param_0026  (param, 1 members, 5 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - local_esbs_ipc_service_recv @ 0x15960  as param_2  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 3 to next field (overlap/union); 0x7: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0026 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4[0x3];   /* +0x4 pad */
    uint8_t    field_0x7;   /* +0x7  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
