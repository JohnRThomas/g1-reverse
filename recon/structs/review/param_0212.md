## review group param_0212  (1 cluster(s), kinds=param)

### proposal for param_0212
struct_name: bt_conn_info | is_library: True | library_name: bt_conn_info | is_array: False | confidence: medium
purpose: Zephyr Bluetooth connection info structure filled by bt_conn_get_info
fields:
  0x2  uint8_t      type  BT_CONN_TYPE_*
  0x3  uint8_t      role  BT_CONN_ROLE_*
  0x8  uint8_t      id  
  0x9  uint8_t      le_state_or_flag  
  0xd  uint8_t      le_addr_byte  
  0xa6  uint16_t     le_interval  
  0xac  uint16_t     le_latency  
  0xae  uint16_t     le_timeout  
  0xc0  int32_t      security_or_err  

<ground-truth bundle for param_0212>
### cluster param_0212  (param, 1 members, 9 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_get_info @ 0x56f4c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0212 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=char,undefined1 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=char,undefined1 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=byte,undefined1 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0xa[0x3];   /* +0xa pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=byte */
    uint8_t    _pad_0xe[0x98];   /* +0xe pad */
    uint16_t   field_0xa6;   /* +0xa6  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0xa8[0x4];   /* +0xa8 pad */
    uint16_t   field_0xac;   /* +0xac  sz=2 rw=r types=undefined2 */
    uint16_t   field_0xae;   /* +0xae  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0xb0[0x10];   /* +0xb0 pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=r types=int */
};
```
