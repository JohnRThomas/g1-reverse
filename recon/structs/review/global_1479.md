## review group global_1479  (1 cluster(s), kinds=global)

### proposal for global_1479
struct_name: hash_drv_ctx | is_library: True | library_name: nrf_cc3xx / hash driver context (unidentified exact struct) | is_array: False | confidence: low
purpose: Large (0xb10-byte) crypto hash driver context/state global manipulated by ProcessHashDrv, holding scattered status/length/pointer scalars around a big internal buffer.
fields:
  0x650  int          status  
  0x65c  int          field_0x65c  
  0x7c8  uint32_t     field_0x7c8  
  0x7cc  int          field_0x7cc  
  0x910  int          field_0x910  
  0xb0c  uint32_t     field_0xb0c  

<ground-truth bundle for global_1479>
### cluster global_1479  (global, 1 members, 6 fields, size>=0xb10)

Global object at fixed address 0x0007b3d8.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - ProcessHashDrv @ 0x7b1e4  as 0x0007b3d8  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1479 {
    uint8_t    _pad_0x0[0x650];   /* +0x0 pad */
    uint32_t   field_0x650;   /* +0x650  sz=4 rw=rw types=int */
    uint8_t    _pad_0x654[0x8];   /* +0x654 pad */
    uint32_t   field_0x65c;   /* +0x65c  sz=4 rw=r types=int */
    uint8_t    _pad_0x660[0x168];   /* +0x660 pad */
    uint32_t   field_0x7c8;   /* +0x7c8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x7cc;   /* +0x7cc  sz=4 rw=r types=int */
    uint8_t    _pad_0x7d0[0x140];   /* +0x7d0 pad */
    uint32_t   field_0x910;   /* +0x910  sz=4 rw=r types=int */
    uint8_t    _pad_0x914[0x1f8];   /* +0x914 pad */
    uint32_t   field_0xb0c;   /* +0xb0c  sz=4 rw=w types=uint */
};
```
