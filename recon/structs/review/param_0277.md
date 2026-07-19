## review group param_0277  (1 cluster(s), kinds=param)

### proposal for param_0277
struct_name: net_buf_pool | is_library: True | library_name: net_buf_pool | is_array: False | confidence: medium
purpose: Zephyr net_buf pool descriptor used by net_buf_alloc_len / net_buf_pool_get / bt_conn_alloc_pdu_buf to allocate ACL/PDU buffers
fields:
  0x4  uint32_t     buf_count  
  0x20  uint16_t     uninit_count  
  0x22  uint16_t     avail_count  
  0x24  uint8_t      pool_id  
  0x2c  int32_t      cb_or_alloc_fn  
  0x30  int32_t      pool_flags  

<ground-truth bundle for param_0277>
### cluster param_0277  (param, 3 members, 6 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,net_buf; 0/3 members are LIBRARY-class)

members (3 shown of 3):
  - net_buf_alloc_len @ 0x5eeb4  as param_1  [APPLICATION]
  - net_buf_pool_get_727ac @ 0x727ac  as param_1  [APPLICATION]
  - bt_conn_alloc_pdu_buf @ 0x836de  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0277 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x18];   /* +0x8 pad */
    uint16_t   field_0x20;   /* +0x20  sz=2 rw=r types=ushort */
    uint16_t   field_0x22;   /* +0x22  sz=2 rw=rw types=ushort */
    uint8_t    field_0x24;   /* +0x24  sz=1 rw=r types=byte,undefined1 */
    uint8_t    _pad_0x25[0x7];   /* +0x25 pad */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=int */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=int */
};
```
