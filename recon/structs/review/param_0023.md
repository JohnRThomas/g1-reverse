## review group param_0023  (3 cluster(s), kinds=param,stack)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0023
struct_name: cjson_parse_buffer | is_library: True | library_name: cJSON parse_buffer + internal_hooks | is_array: None | confidence: medium
purpose: cJSON internal parse cursor: content pointer, length, offset, depth, and embedded malloc/free hook function pointers, shared by cjson_parse_value/cjson_parse_string/cjson_skip_whitespace.
fields:
  0x0  const unsigned char * content  typed 'code' by Ghidra; treated as cursor pointer
  0x4  uint32_t     length  
  0x8  uint32_t     offset  
  0xc  uint32_t     depth  
  0x10  void *       hooks_malloc_fn  
  0x14  void *       hooks_free_fn  

<ground-truth bundle for param_0023>
### cluster param_0023  (param, 3 members, 6 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/3 members are LIBRARY-class)

members (3 shown of 3):
  - cjson_parse_value @ 0x12910  as param_2  [APPLICATION]
  - cjson_parse_string @ 0x64290  as param_2  [APPLICATION]
  - cjson_skip_whitespace @ 0x84ed8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0023 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0731
struct_name: k_sem | is_library: True | library_name: k_sem | is_array: None | confidence: high
purpose: Zephyr kernel semaphore object initialized by z_impl_k_sem_init
fields:
  0x0  void*        wait_q_head  w, wait-queue dlist head
  0x4  void*        wait_q_tail  w, wait-queue dlist tail
  0x8  unsigned int count  w
  0xc  unsigned int limit  w
  0x10  void*        poll_events_head  w, CONFIG_POLL dlist head
  0x14  void*        poll_events_tail  w, CONFIG_POLL dlist tail

<ground-truth bundle for param_0731>
### cluster param_0731  (param, 1 members, 6 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_impl_k_sem_init @ 0x86534  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0731 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=int */
};
```

### proposal for stack_1377
struct_name: lc3_sns_shaping_coeffs | is_library: True | library_name: liblc3: SNS (Spectral Noise Shaping) coefficient array | is_array: True | confidence: medium
purpose: Local array of six spectral-shaping coefficients used in lc3_sns_spectral_shaping (LC3 SNS quantization).
fields:
  0x0  int32_t      coeff_0  read-only idx4
  0x4  int32_t      coeff_1  read-only idx4
  0x8  int32_t      coeff_2  read-only idx4
  0xc  int32_t      coeff_3  read-only idx4
  0x10  int32_t      coeff_4  read-only idx4
  0x14  int32_t      coeff_5  read-only idx4

<ground-truth bundle for stack_1377>
### cluster stack_1377  (stack, 1 members, 6 fields, size>=0x18)

Stack-frame local local_138 in lc3_sns_spectral_shaping (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_spectral_shaping @ 0x6bfc8  as local_138  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1377 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```
