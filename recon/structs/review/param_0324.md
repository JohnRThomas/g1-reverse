## review group param_0324  (1 cluster(s), kinds=param)

### proposal for param_0324
struct_name: cJSON | is_library: True | library_name: cJSON | is_array: None | confidence: high
purpose: cJSON tree node freed recursively by cjson_delete: next/prev pointers implicit in the leading pad, child pointer, type tag, valuestring pointer, and string (key) pointer.
fields:
  0x8  void *       child  read as idx4 (pointer)
  0xc  int          type  read as idx4
  0x10  char *       valuestring  read as idx4 (pointer)
  0x20  char *       string  read as idx4 (pointer), key name

<ground-truth bundle for param_0324>
### cluster param_0324  (param, 1 members, 4 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - cjson_delete @ 0x64b1c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0324 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0xc];   /* +0x14 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```
