## review group global_1358  (7 cluster(s), kinds=global,param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_1358
struct_name: lc3_attdet_state | is_library: True | library_name: lc3_attdet_analysis | is_array: None | confidence: low
purpose: LC3 codec attack-detector running state used by lc3_attdet_run
fields:
  0x4  int32_t      attdet_param_0  
  0x8  int32_t      attdet_param_1  
  0xc  int32_t      attdet_param_2  
  0x10  int32_t      attdet_param_3  
  0x14  int32_t      attdet_param_4  
  0x18  int32_t      attdet_param_5  
  0x1c  int32_t      attdet_param_6  

<ground-truth bundle for global_1358>
### cluster global_1358  (global, 1 members, 7 fields, size>=0x20)

Global object at fixed address 0x000684a4.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_attdet_run @ 0x682f0  as 0x000684a4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1358 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0061
struct_name: ipc0_ept_recv_ctx | is_library: True | library_name: ipc_ept | is_array: None | confidence: medium
purpose: IPC endpoint receive context/message descriptor for ipc0_ept_recv (nRF IPC service endpoint callback data)
fields:
  0x4  uint32_t     field_0x4  idx4
  0x8  uint32_t     field_0x8  idx4
  0xc  uint32_t     field_0xc  idx4
  0x10  uint32_t     field_0x10  idx4
  0x14  uint32_t     field_0x14  idx4
  0x18  uint32_t     field_0x18  idx4
  0x1c  uint32_t     field_0x1c  idx4

<ground-truth bundle for param_0061>
### cluster param_0061  (param, 1 members, 7 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ipc0_ept_recv @ 0x25a48  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0061 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0175
struct_name: img_mgmt_upload_req | is_library: True | library_name: img_mgmt (mcumgr) upload req | is_array: None | confidence: medium
purpose: MCUmgr img_mgmt image-upload request descriptor inspected by img_mgmt_upload_inspect (offset/length/hash fields of a firmware upload chunk).
fields:
  0x4  uint32_t     off  upload offset field
  0x8  uint32_t     size  total image size field
  0xc  uint32_t     data_len  chunk data length
  0x10  uint32_t     field_0x10  additional descriptor word
  0x14  uint32_t     field_0x14  additional descriptor word
  0x18  uint32_t     field_0x18  additional descriptor word
  0x1c  uint32_t     field_0x1c  additional descriptor word

<ground-truth bundle for param_0175>
### cluster param_0175  (param, 1 members, 7 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_upload_inspect @ 0x518a8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0175 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0335
struct_name: nrf_qspi_cinstr_conf | is_library: True | library_name: nrf_qspi_cinstr_conf_t | is_array: True | confidence: medium
purpose: nrfx QSPI custom-instruction configuration struct read by nrf_qspi_cinstrdata_get: sequence of uint32 config words (opcode/length/io-level/wait/addr fields).
fields:
  0x4  uint32_t     cfg_word0  
  0x8  uint32_t     cfg_word1  
  0xc  uint32_t     cfg_word2  
  0x10  uint32_t     cfg_word3  
  0x14  uint32_t     cfg_word4  
  0x18  uint32_t     cfg_word5  
  0x1c  uint32_t     cfg_word6  

<ground-truth bundle for param_0335>
### cluster param_0335  (param, 1 members, 7 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrf_qspi_cinstrdata_get @ 0x666e0  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0335 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0336
struct_name: nrf_qspi_regs_partial | is_library: True | library_name: NRF_QSPI_Type | is_array: None | confidence: low
purpose: Fields read from what is likely the NRF QSPI peripheral register block (or an nrf_qspi_cinstr_conf_t-like config) passed to nrf_qspi_cinstrdata_set
fields:
  0x4  uint32_t     reg_0  r, idx4
  0x8  uint32_t     reg_1  r, idx4
  0xc  uint32_t     reg_2  r, idx4
  0x10  uint32_t     reg_3  r, idx4
  0x14  uint32_t     reg_4  r, idx4
  0x18  uint32_t     reg_5  r, idx4
  0x1c  uint32_t     reg_6  r, idx4

<ground-truth bundle for param_0336>
### cluster param_0336  (param, 1 members, 7 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrf_qspi_cinstrdata_set @ 0x66720  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0336 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0574
struct_name: le_serialize_buffer | is_library: True | library_name: sys_put_le64 (Zephyr byteorder helpers) output buffer | is_array: True | confidence: low
purpose: Output buffer progressively filled by repeated sys_put_le64 calls across call sites (little-endian value serialization).
fields:
  0x4  uint32_t     word_0  array element
  0x8  uint32_t     word_1  array element
  0xc  uint32_t     word_2  array element
  0x10  uint32_t     word_3  array element
  0x14  uint32_t     word_4  array element
  0x18  uint32_t     word_5  array element
  0x1c  uint32_t     word_6  array element

<ground-truth bundle for param_0574>
### cluster param_0574  (param, 1 members, 7 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: sys; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - sys_put_le64 @ 0x80eb8  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0574 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0693
struct_name: metal_io_region | is_library: True | library_name: metal_io_region | is_array: None | confidence: medium
purpose: libmetal I/O region descriptor initialized by metal_io_init (physmap/size/page-shift/mask/flags/ops).
fields:
  0x4  uint32_t     physmap  read as idx4
  0x8  uint32_t     size  read as idx4
  0xc  uint32_t     page_shift  read as idx4
  0x10  uint32_t     page_mask  read as idx4
  0x14  uint32_t     mem_flags  read as idx4
  0x18  void *       ops_map  read as idx4, function pointer
  0x1c  void *       ops_offset  read as idx4, function pointer

<ground-truth bundle for param_0693>
### cluster param_0693  (param, 1 members, 7 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - metal_io_init @ 0x85442  as param_7  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0693 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```
