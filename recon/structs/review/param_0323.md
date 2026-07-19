## review group param_0323  (1 cluster(s), kinds=param)

### proposal for param_0323
struct_name: cjson_print_ctx | is_library: True | library_name: printbuffer (cJSON) | is_array: False | confidence: medium
purpose: cJSON print buffer state used by cjson_print_value: output buffer pointer, format flag, offset/length counters.
fields:
  0x8  char *       buffer  output buffer pointer
  0xc  uint8_t      noalloc  flag byte
  0x10  uint32_t     length  buffer length
  0x18  uint32_t     offset  write offset
  0x1c  uint32_t     depth  nesting depth/format

<ground-truth bundle for param_0323>
### cluster param_0323  (param, 1 members, 5 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - cjson_print_value @ 0x646c0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0323 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=byte */
    uint8_t    _pad_0xd[0x3];   /* +0xd pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x14[0x4];   /* +0x14 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=uint */
};
```
