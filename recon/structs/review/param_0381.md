## review group param_0381  (5 cluster(s), kinds=param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0381
struct_name: lc3_sns_scale_table | is_library: True | library_name: lc3 (sns internal tables) | is_array: True | confidence: medium
purpose: LC3 SNS (spectral noise shaping) unquantization scale-factor table read as a uniform array by lc3_sns_unquantize.
fields:
  0x4  uint32_t     entry_1  
  0x8  uint32_t     entry_2  
  0xc  uint32_t     entry_3  
  0x10  uint32_t     entry_4  
  0x14  uint32_t     entry_5  
  0x18  uint32_t     entry_6  
  0x1c  uint32_t     entry_7  
  0x20  uint32_t     entry_8  
  0x24  uint32_t     entry_9  
  0x28  uint32_t     entry_10  
  0x2c  uint32_t     entry_11  
  0x30  uint32_t     entry_12  
  0x34  uint32_t     entry_13  
  0x38  uint32_t     entry_14  
  0x3c  uint32_t     entry_15  

<ground-truth bundle for param_0381>
### cluster param_0381  (param, 1 members, 15 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_unquantize @ 0x6bd74  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0381 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0382
struct_name: lc3_sns_scratch_array | is_library: True | library_name: LC3 codec internal array (int16/int32 coeff buffer) | is_array: True | confidence: medium
purpose: LC3 audio codec scalar-noise-shaping unquantized coefficient scratch buffer (uniform int array) used by lc3_sns_unquantize.
fields:
  0x4  int32_t      coeff[0]  array element, uniform stride 4
  0x8  int32_t      coeff[1]  array element
  0xc  int32_t      coeff[2]  array element
  0x10  int32_t      coeff[3]  array element
  0x14  int32_t      coeff[4]  array element
  0x18  int32_t      coeff[5]  array element
  0x1c  int32_t      coeff[6]  array element
  0x20  int32_t      coeff[7]  array element
  0x24  int32_t      coeff[8]  array element
  0x28  int32_t      coeff[9]  array element
  0x2c  int32_t      coeff[10]  array element
  0x30  int32_t      coeff[11]  array element
  0x34  int32_t      coeff[12]  array element
  0x38  int32_t      coeff[13]  array element
  0x3c  int32_t      coeff[14]  array element

<ground-truth bundle for param_0382>
### cluster param_0382  (param, 1 members, 15 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_unquantize @ 0x6bd74  as param_6  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0382 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0383
struct_name: lc3_sns_shaping_state | is_library: True | library_name: lc3 (liblc3 internal) | is_array: True | confidence: low
purpose: LC3 audio codec spectral noise shaping (SNS) internal state buffer used by lc3_sns_spectral_shaping, a uniform array of 16 coefficient words
fields:
  0x4  int32_t      coeff_0  
  0x8  int32_t      coeff_1  
  0xc  int32_t      coeff_2  
  0x10  int32_t      coeff_3  
  0x14  int32_t      coeff_4  
  0x18  int32_t      coeff_5  
  0x1c  int32_t      coeff_6  
  0x20  int32_t      coeff_7  
  0x24  int32_t      coeff_8  
  0x28  int32_t      coeff_9  
  0x2c  int32_t      coeff_10  
  0x30  int32_t      coeff_11  
  0x34  int32_t      coeff_12  
  0x38  int32_t      coeff_13  
  0x3c  int32_t      coeff_14  

<ground-truth bundle for param_0383>
### cluster param_0383  (param, 1 members, 15 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_spectral_shaping @ 0x6bfc8  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0383 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0546
struct_name: tc_aes_key_sched_struct | is_library: True | library_name: tc_aes_key_sched_struct | is_array: True | confidence: high
purpose: AES round-key words consumed by add_round_key (tinycrypt AES) — same key-schedule array type as global_1098, here accessed further into the word array.
fields:
  0x4  uint32_t     words_1  
  0x8  uint32_t     words_2  
  0xc  uint32_t     words_3  
  0x10  uint32_t     words_4  
  0x14  uint32_t     words_5  
  0x18  uint32_t     words_6  
  0x1c  uint32_t     words_7  
  0x20  uint32_t     words_8  
  0x24  uint32_t     words_9  
  0x28  uint32_t     words_10  
  0x2c  uint32_t     words_11  
  0x30  uint32_t     words_12  
  0x34  uint32_t     words_13  
  0x38  uint32_t     words_14  
  0x3c  uint32_t     words_15  

<ground-truth bundle for param_0546>
### cluster param_0546  (param, 1 members, 15 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - add_round_key @ 0x7feda  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0546 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0547
struct_name: aes_state_words | is_library: True | library_name:  | is_array: True | confidence: medium
purpose: AES round-state represented as 16 32-bit words, read by shift_rows
fields:
  0x4  uint32_t     word_0  r
  0x8  uint32_t     word_1  r
  0xc  uint32_t     word_2  r
  0x10  uint32_t     word_3  r
  0x14  uint32_t     word_4  r
  0x18  uint32_t     word_5  r
  0x1c  uint32_t     word_6  r
  0x20  uint32_t     word_7  r
  0x24  uint32_t     word_8  r
  0x28  uint32_t     word_9  r
  0x2c  uint32_t     word_10  r
  0x30  uint32_t     word_11  r
  0x34  uint32_t     word_12  r
  0x38  uint32_t     word_13  r
  0x3c  uint32_t     word_14  r

<ground-truth bundle for param_0547>
### cluster param_0547  (param, 1 members, 15 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - shift_rows @ 0x7ff64  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0547 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```
