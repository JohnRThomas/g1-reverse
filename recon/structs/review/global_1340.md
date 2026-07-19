## review group global_1340  (2 cluster(s), kinds=global)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_1340
struct_name: qspi_workaround_state | is_library: True | library_name: nrfx_qspi (partial, driver instance tail) | is_array: None | confidence: low
purpose: Tail fields of a large fixed global (likely nrfx QSPI driver instance/context) touched by qspi_workaround_apply, which patches known nRF5340 QSPI erratum registers/state.
fields:
  0x524  uint32_t     field_0x524  
  0x528  uint32_t     field_0x528  
  0x530  uint32_t     field_0x530  
  0x534  uint32_t     field_0x534  
  0x538  uint32_t     field_0x538  
  0x53c  uint32_t     field_0x53c  

<ground-truth bundle for global_1340>
### cluster global_1340  (global, 1 members, 6 fields, size>=0x540)

Global object at fixed address 0x0006684c.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - qspi_workaround_apply @ 0x667e0  as 0x0006684c  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1340 {
    uint8_t    _pad_0x0[0x524];   /* +0x0 pad */
    uint32_t   field_0x524;   /* +0x524  sz=4 rw=r types=uint */
    uint32_t   field_0x528;   /* +0x528  sz=4 rw=r types=uint */
    uint8_t    _pad_0x52c[0x4];   /* +0x52c pad */
    uint32_t   field_0x530;   /* +0x530  sz=4 rw=r types=uint */
    uint32_t   field_0x534;   /* +0x534  sz=4 rw=r types=uint */
    uint32_t   field_0x538;   /* +0x538  sz=4 rw=r types=uint */
    uint32_t   field_0x53c;   /* +0x53c  sz=4 rw=r types=uint */
};
```

### proposal for global_1347
struct_name: nrfx_qspi_cb | is_library: True | library_name: nrfx_qspi internal cb_t | is_array: None | confidence: medium
purpose: Internal nrfx QSPI driver control block (singleton) used by nrfx_qspi_uninit.
fields:
  0x524  uint32_t     field_0x524  driver state/handler
  0x528  uint32_t     field_0x528  driver state
  0x530  uint32_t     field_0x530  driver state
  0x534  uint32_t     field_0x534  driver state
  0x538  uint32_t     field_0x538  driver state
  0x53c  uint32_t     field_0x53c  driver state

<ground-truth bundle for global_1347>
### cluster global_1347  (global, 1 members, 6 fields, size>=0x540)

Global object at fixed address 0x00066bc0.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_qspi_uninit @ 0x66b24  as 0x00066bc0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1347 {
    uint8_t    _pad_0x0[0x524];   /* +0x0 pad */
    uint32_t   field_0x524;   /* +0x524  sz=4 rw=r types=uint */
    uint32_t   field_0x528;   /* +0x528  sz=4 rw=r types=uint */
    uint8_t    _pad_0x52c[0x4];   /* +0x52c pad */
    uint32_t   field_0x530;   /* +0x530  sz=4 rw=r types=uint */
    uint32_t   field_0x534;   /* +0x534  sz=4 rw=r types=uint */
    uint32_t   field_0x538;   /* +0x538  sz=4 rw=r types=uint */
    uint32_t   field_0x53c;   /* +0x53c  sz=4 rw=r types=uint */
};
```
