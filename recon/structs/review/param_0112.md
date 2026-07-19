## review group param_0112  (1 cluster(s), kinds=param)

### proposal for param_0112
struct_name: panoramic_map_view_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: View/tile state for navigation_panoramic_map_display: a coordinate pair plus a trailing data pointer/counter used to render the panoramic map.
fields:
  0x8  uint16_t     pos_x  read
  0xa  uint16_t     pos_y  read
  0xb1  uint32_t     tile_data_ref  read, unaligned offset suggests packed byte buffer preceding it

<ground-truth bundle for param_0112>
### cluster param_0112  (param, 1 members, 3 fields, size>=0xb5)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - navigation_panoramic_map_display @ 0x3e7f8  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0112 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint16_t   field_0x8;   /* +0x8  sz=2 rw=r types=ushort */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=ushort */
    uint8_t    _pad_0xc[0xa5];   /* +0xc pad */
    uint32_t   field_0xb1;   /* +0xb1  sz=4 rw=r types=int,undefined4 */
};
```
