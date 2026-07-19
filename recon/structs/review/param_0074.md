## review group param_0074  (1 cluster(s), kinds=param)

### proposal for param_0074
struct_name: peripheral_dispatch_buf | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Large (>=0xfc6 byte) dispatch/message buffer for the low-speed peripheral dispatch test thread, with a leading status byte and trailing write-index fields.
fields:
  0x1  uint8_t      status_byte  read
  0xfc0  uint16_t     write_idx0  write-only ushort near buffer tail
  0xfc4  uint16_t     write_idx1  write-only ushort near buffer tail

<ground-truth bundle for param_0074>
### cluster param_0074  (param, 1 members, 3 fields, size>=0xfc6)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - low_speed_peripheral_dispatch_thread_for_test @ 0x2685c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0074 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=char */
    uint8_t    _pad_0x2[0xfbe];   /* +0x2 pad */
    uint16_t   field_0xfc0;   /* +0xfc0  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0xfc2[0x2];   /* +0xfc2 pad */
    uint16_t   field_0xfc4;   /* +0xfc4  sz=2 rw=w types=undefined2 */
};
```
