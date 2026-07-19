## review group param_0453  (1 cluster(s), kinds=param)

### proposal for param_0453
struct_name: hash_drv_context | is_library: True | library_name: CryptoCell HASH driver context (HashDrvContext_t, exact header unverified) | is_array: True | confidence: low
purpose: Hash driver working state finalized by FinishHashDrv: an 8-word running digest plus additional internal counters/buffer words, characteristic of a SHA-family hash context (CryptoCell hash driver).
fields:
  0x8  uint32_t     state_0  
  0xc  uint32_t     state_1  
  0x10  uint32_t     state_2  
  0x14  uint32_t     state_3  
  0x18  uint32_t     state_4  
  0x1c  uint32_t     state_5  
  0x20  uint32_t     state_6  
  0x24  uint32_t     state_7  
  0x28  uint32_t     word_8  
  0x2c  uint32_t     word_9  
  0x30  uint32_t     word_10  
  0x34  uint32_t     word_11  
  0x38  uint32_t     word_12  
  0x3c  uint32_t     word_13  
  0x40  uint32_t     word_14  
  0x44  uint32_t     word_15  

<ground-truth bundle for param_0453>
### cluster param_0453  (param, 1 members, 16 fields, size>=0x48)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - FinishHashDrv @ 0x7b3f4  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0453 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=uint */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=uint */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=rw types=uint */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=uint */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=uint */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=rw types=uint */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=rw types=uint */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=rw types=uint */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=rw types=uint */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=rw types=uint */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=rw types=uint */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=rw types=uint */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=rw types=uint */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=rw types=uint */
};
```
