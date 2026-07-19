## review group param_0415  (1 cluster(s), kinds=param)

### proposal for param_0415
struct_name: event_registration | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Event registration record (callback pointer, count, list pointer) shared by register_events and add_event
fields:
  0x4  uint32_t     event_id  
  0x8  void *       callback  
  0xc  uint32_t     count  
  0x10  void *       next  

<ground-truth bundle for param_0415>
### cluster param_0415  (param, 2 members, 5 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - register_events @ 0x751d0  as param_1  [APPLICATION]
  - add_event @ 0x86778  as param_2  [APPLICATION]

layout notes: 0xc: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0415 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    void *     field_0x8;   /* +0x8  sz=4 rw=w types=ptr,undefined4 */
    uint8_t    field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=byte */
    uint8_t    _pad_0xe[0x2];   /* +0xe pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=int,ptr */
};
```
