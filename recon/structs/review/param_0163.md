## review group param_0163  (1 cluster(s), kinds=param)

### proposal for param_0163
struct_name: power_restrict_event_entry | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: Power-manager restrict-event log entry: a pointer (context/name), a value/timestamp, and a status byte.
fields:
  0x4  void *       ctx_ptr  
  0x8  uint32_t     value  
  0xc  uint8_t      status  

<ground-truth bundle for param_0163>
### cluster param_0163  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - power_manager_restrict_event_log @ 0x4f92c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0163 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=byte */
    uint8_t    _pad_0xd[0x3];   /* +0xd pad */
};
```
