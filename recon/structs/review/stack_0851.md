## review group stack_0851  (1 cluster(s), kinds=stack)

### proposal for stack_0851
struct_name: status_notify_packet_locals | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local scratch buffer in build_status_notify_packet holding two header/trailer bytes of an outgoing status-notify BLE packet.
fields:
  0x0  uint8_t      packet_header_byte  
  0x14  uint8_t      packet_trailer_byte  

<ground-truth bundle for stack_0851>
### cluster stack_0851  (stack, 1 members, 2 fields, size>=0x15)

Stack-frame local local_24 in build_status_notify_packet (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - build_status_notify_packet @ 0x21334  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0851 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x13];   /* +0x1 pad */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=r types=idx1 */
};
```
