## review group param_0210  (1 cluster(s), kinds=param)

### proposal for param_0210
struct_name: bt_conn_ctx | is_library: True | library_name: struct bt_conn (partial) | is_array: None | confidence: low
purpose: Bluetooth connection object shared by ble_notify_remote_info_available and bt_smp_request_ltk (SMP/LTK request flags near the front, a status/handle word farther in).
fields:
  0x8  uint8_t      field_0x8  
  0x9  uint8_t      field_0x9  
  0xa  uint8_t      field_0xa  
  0xc0  uint32_t     field_0xc0  

<ground-truth bundle for param_0210>
### cluster param_0210  (param, 2 members, 4 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - ble_notify_remote_info_available @ 0x56da8  as param_1  [APPLICATION]
  - bt_smp_request_ltk @ 0x83370  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0210 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=undefined1 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=undefined1 */
    uint8_t    field_0xa;   /* +0xa  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xb[0xb5];   /* +0xb pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=rw types=int,undefined4 */
};
```
