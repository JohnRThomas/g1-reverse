## review group param_0059  (1 cluster(s), kinds=param)

### proposal for param_0059
struct_name: ipc_ept_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: IPC endpoint context used across locked-retry send helpers and pt_comm transport write
fields:
  0x4  void *       ipc_instance_ptr  
  0x8  uint32_t     ept_id  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0059>
### cluster param_0059  (param, 3 members, 3 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - ipc_ept_op_a_locked_retry @ 0x256dc  as param_1  [APPLICATION]
  - ipc_send_len_prefixed_packet_locked_retry @ 0x25788  as param_1  [APPLICATION]
  - pt_comm_transport_write @ 0x30cd0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0059 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
};
```
