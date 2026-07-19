## review group param_0280  (1 cluster(s), kinds=param)

### proposal for param_0280
struct_name: net_buf | is_library: True | library_name: net_buf | is_array: None | confidence: medium
purpose: Zephyr net_buf network buffer object (fragment chain used across ATT/net_buf functions)
fields:
  0x4  struct net_buf* frags  fragment chain pointer, follows embedded sys_snode_t at +0x0
  0xa  uint8_t      pool_id  matches net_buf ref/flags/pool_id/user_data_size byte cluster
  0x10  uint16_t     len  approx position of size/len fields

<ground-truth bundle for param_0280>
### cluster param_0280  (param, 4 members, 3 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,net_buf; 1/4 members are LIBRARY-class)

members (4 shown of 4):
  - net_buf_frag_last @ 0x5f304  as param_1  [APPLICATION]
  - net_buf_append_bytes @ 0x5f450  as param_1  [APPLICATION]
  - net_buf_frags_len_0 @ 0x81bc0  as param_1  [LIBRARY]
  - att_chan_read @ 0x81e2a  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0280 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x2];   /* +0x8 pad */
    uint8_t    field_0xa;   /* +0xa  sz=1 rw=r types=byte,undefined1 */
    uint8_t    _pad_0xb[0x5];   /* +0xb pad */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
