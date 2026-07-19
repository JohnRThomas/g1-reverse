## review group stack_0757  (13 cluster(s), kinds=stack)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for stack_0757
struct_name: batt_model_calc_locals | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local stack scratch used inside battery_model_state_update to hold five sequential model computation values (voltage/current/capacity/temperature/SoC style intermediates).
fields:
  0x0  uint32_t     value_0  read as idx4
  0x4  uint32_t     value_1  read as idx4
  0x8  uint32_t     value_2  read as idx4
  0xc  uint32_t     value_3  read as idx4
  0x10  uint32_t     value_4  read as idx4

<ground-truth bundle for stack_0757>
### cluster stack_0757  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_1e0 in battery_model_state_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as local_1e0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0757 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_0760
struct_name: battery_model_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local scratch aggregate in battery_model_state_update holding five consecutive computed values (voltage/current/capacity/soc/temp-like quantities).
fields:
  0x0  int32_t      field_0x0  read-only idx4
  0x4  int32_t      field_0x4  read-only idx4
  0x8  int32_t      field_0x8  read-only idx4
  0xc  int32_t      field_0xc  read-only idx4
  0x10  int32_t      field_0x10  read-only idx4

<ground-truth bundle for stack_0760>
### cluster stack_0760  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_1a0 in battery_model_state_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as local_1a0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0760 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_0761
struct_name: batt_model_calc_tmp | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local scratch array/record of five uint32 values used mid-computation in battery_model_state_update (likely intermediate coefficients or curve-lookup results).
fields:
  0x0  uint32_t     v0  
  0x4  uint32_t     v1  
  0x8  uint32_t     v2  
  0xc  uint32_t     v3  
  0x10  uint32_t     v4  

<ground-truth bundle for stack_0761>
### cluster stack_0761  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_190 in battery_model_state_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as local_190  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0761 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_0778
struct_name: spline_interp_points | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Stack-local set of five control-point/coefficient words consumed by spline_interp_pair_2out for two-output spline interpolation.
fields:
  0x0  uint32_t     p0  
  0x4  uint32_t     p1  
  0x8  uint32_t     p2  
  0xc  uint32_t     p3  
  0x10  uint32_t     p4  

<ground-truth bundle for stack_0778>
### cluster stack_0778  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_58 in spline_interp_pair_2out (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - spline_interp_pair_2out @ 0xea70  as local_58  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0778 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_0896
struct_name: ndef_record_local | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local buffer of five words used to build NDEF records in st25dv_build_and_write_ndef_records
fields:
  0x0  uint32_t     word0  
  0x4  uint32_t     word1  
  0x8  uint32_t     word2  
  0xc  uint32_t     word3  
  0x10  uint32_t     word4  

<ground-truth bundle for stack_0896>
### cluster stack_0896  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_88 in st25dv_build_and_write_ndef_records (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - st25dv_build_and_write_ndef_records @ 0x250f8  as local_88  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0896 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_0964
struct_name: ble_chunk_scratch | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local scratch array of five 32-bit words used while splitting outbound data into BLE notification chunks in send_data_in_ble_chunks.
fields:
  0x0  uint32_t     word_0  
  0x4  uint32_t     word_1  
  0x8  uint32_t     word_2  
  0xc  uint32_t     word_3  
  0x10  uint32_t     word_4  

<ground-truth bundle for stack_0964>
### cluster stack_0964  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_3c in send_data_in_ble_chunks (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - send_data_in_ble_chunks @ 0x3384c  as local_3c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0964 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1097
struct_name: tc_aes_key_sched_words | is_library: True | library_name: tc_aes_key_sched_struct (TinyCrypt, partial) | is_array: True | confidence: medium
purpose: TinyCrypt AES-128 key schedule local (5 round-key words) computed inside tc_aes128_set_encrypt_key.
fields:
  0x0  uint32_t     word_0  read-only key schedule word
  0x4  uint32_t     word_1  read-only key schedule word
  0x8  uint32_t     word_2  read-only key schedule word
  0xc  uint32_t     word_3  read-only key schedule word
  0x10  uint32_t     word_4  read-only key schedule word

<ground-truth bundle for stack_1097>
### cluster stack_1097  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_44 in tc_aes128_set_encrypt_key (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: tc; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - tc_aes128_set_encrypt_key @ 0x4fa34  as local_44  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1097 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1356
struct_name: lc3_attdet_energy | is_library: True | library_name: lc3 (liblc3 internal) | is_array: True | confidence: low
purpose: Local array of five energy/attack-detection metrics computed inside lc3_attdet_run for LC3 codec transient (attack) detection
fields:
  0x0  int32_t      energy_0  
  0x4  int32_t      energy_1  
  0x8  int32_t      energy_2  
  0xc  int32_t      energy_3  
  0x10  int32_t      energy_4  

<ground-truth bundle for stack_1356>
### cluster stack_1356  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_58 in lc3_attdet_run (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_attdet_run @ 0x682f0  as local_58  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1356 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1357
struct_name: lc3_attdet_local | is_library: True | library_name: lc3_attdet_analysis | is_array: None | confidence: low
purpose: Local stack struct in lc3_attdet_run holding five 32-bit LC3 attack-detection intermediate values
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for stack_1357>
### cluster stack_1357  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_48 in lc3_attdet_run (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_attdet_run @ 0x682f0  as local_48  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1357 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1378
struct_name: lc3_sns_analysis_buf | is_library: True | library_name: lc3 SNS analysis scratch buffer | is_array: True | confidence: low
purpose: Local scratch array of five uint32 values used during LC3 spectral-noise-shaping (SNS) analysis in lc3_sns_analyze.
fields:
  0x0  uint32_t     v0  
  0x4  uint32_t     v1  
  0x8  uint32_t     v2  
  0xc  uint32_t     v3  
  0x10  uint32_t     v4  

<ground-truth bundle for stack_1378>
### cluster stack_1378  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_2e8 in lc3_sns_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_analyze @ 0x6c778  as local_2e8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1378 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1379
struct_name: lc3_sns_energy_buf | is_library: True | library_name:  | is_array: True | confidence: medium
purpose: Local array of 5 band-energy/index values used by the LC3 SNS (spectral noise shaping) analysis routine
fields:
  0x0  uint32_t     val_0  r, idx4
  0x4  uint32_t     val_1  r, idx4
  0x8  uint32_t     val_2  r, idx4
  0xc  uint32_t     val_3  r, idx4
  0x10  uint32_t     val_4  r, idx4

<ground-truth bundle for stack_1379>
### cluster stack_1379  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_2a8 in lc3_sns_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_analyze @ 0x6c778  as local_2a8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1379 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1385
struct_name: lc3_spec_analysis_state | is_library: True | library_name: lc3_spec_analysis | is_array: True | confidence: low
purpose: LC3 codec spectral-analysis local workspace in lc3_spec_analyze: a run of 5 uniform 32-bit values (energy/coefficient accumulators)
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for stack_1385>
### cluster stack_1385  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_6c in lc3_spec_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_spec_analyze @ 0x6f4a0  as local_6c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1385 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1388
struct_name: lc3_tns_analyze_scratch | is_library: True | library_name: lc3_tns_analyze local state (liblc3) | is_array: None | confidence: low
purpose: Stack-local coefficient array inside lc3_tns_analyze (LC3 codec Temporal Noise Shaping analysis).
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for stack_1388>
### cluster stack_1388  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_11c in lc3_tns_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_tns_analyze @ 0x6ffd8  as local_11c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1388 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
