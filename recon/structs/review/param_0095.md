## review group param_0095  (1 cluster(s), kinds=param)

### proposal for param_0095
struct_name: uart_event_data | is_library: True | library_name: struct uart_event (partial) | is_array: False | confidence: medium
purpose: UART driver callback event payload (param_2 of uart_callback) carrying a type/id and two associated length/count fields.
fields:
  0x4  int          evt_field  
  0x8  uint32_t     len_or_offset  
  0xc  uint32_t     count  

<ground-truth bundle for param_0095>
### cluster param_0095  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - uart_callback @ 0x33384  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0095 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=uint,undefined4 */
};
```
