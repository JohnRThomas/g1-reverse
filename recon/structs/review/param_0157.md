## review group param_0157  (1 cluster(s), kinds=param)

### proposal for param_0157
struct_name: ancs_notif_ctx | is_library: True | library_name: bt_ancs_client (nRF Connect SDK ANCS client context) | is_array: False | confidence: medium
purpose: Context struct for Apple Notification Center Service (ANCS) GATT discovery/subscription: ancs_gatt_dm_assign_handles, ancs_subscribe_notification_source, ancs_subscribe_data_source share this object, which holds GATT handle values (uint16 CCC/char handles) and repeated idx4 fields for subscribe params/params blocks.
fields:
  0x2  uint16_t     field_0x2  write-only handle
  0x4  uint32_t     field_0x4  rw, overlapping 16/32-bit
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x20d  uint16_t     field_0x20d  write-only gatt handle
  0x215  uint16_t     field_0x215  write-only gatt handle
  0x828  uint32_t     field_0x828  
  0x836  uint16_t     field_0x836  write-only gatt handle
  0x83c  uint32_t     field_0x83c  
  0x844  uint32_t     field_0x844  
  0x848  uint32_t     field_0x848  
  0x856  uint16_t     field_0x856  write-only gatt handle
  0x85c  uint32_t     field_0x85c  
  0x864  uint32_t     field_0x864  

<ground-truth bundle for param_0157>
### cluster param_0157  (param, 3 members, 19 fields, size>=0x868)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - ancs_gatt_dm_assign_handles @ 0x4ee68  as param_2  [APPLICATION]
  - ancs_subscribe_notification_source @ 0x4f040  as param_1  [APPLICATION]
  - ancs_subscribe_data_source @ 0x4f0ec  as param_1  [APPLICATION]

layout notes: 0x2: access width 2 exceeds gap 1 to next field (overlap/union); 0x3: access width 2 exceeds gap 1 to next field (overlap/union); 0x8: access width 4 exceeds gap 2 to next field (overlap/union); 0xc: access width 4 exceeds gap 2 to next field (overlap/union); 0x20d: access width 2 exceeds gap 1 to next field (overlap/union); 0x215: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0157 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=2 rw=w types=undefined2 */
    uint8_t    field_0x3;   /* +0x3  sz=2 rw=rw types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=2,4 rw=rw types=idx4,undefined2 */
    uint16_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=rw types=undefined2 */
    uint16_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=rw types=undefined2 */
    uint8_t    _pad_0x10[0x1fd];   /* +0x10 pad */
    uint8_t    field_0x20d;   /* +0x20d  sz=2 rw=w types=undefined2 */
    uint16_t   field_0x20e;   /* +0x20e  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x210[0x5];   /* +0x210 pad */
    uint8_t    field_0x215;   /* +0x215  sz=2 rw=w types=undefined2 */
    uint16_t   field_0x216;   /* +0x216  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x218[0x610];   /* +0x218 pad */
    uint32_t   field_0x828;   /* +0x828  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x82c[0xa];   /* +0x82c pad */
    uint16_t   field_0x836;   /* +0x836  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x838[0x4];   /* +0x838 pad */
    uint32_t   field_0x83c;   /* +0x83c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x840[0x4];   /* +0x840 pad */
    uint32_t   field_0x844;   /* +0x844  sz=4 rw=r types=idx4 */
    uint32_t   field_0x848;   /* +0x848  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x84c[0xa];   /* +0x84c pad */
    uint16_t   field_0x856;   /* +0x856  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x858[0x4];   /* +0x858 pad */
    uint32_t   field_0x85c;   /* +0x85c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x860[0x4];   /* +0x860 pad */
    uint32_t   field_0x864;   /* +0x864  sz=4 rw=r types=idx4 */
};
```
