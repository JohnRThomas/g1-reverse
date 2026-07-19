## review group global_1480  (1 cluster(s), kinds=global)

### proposal for global_1480
struct_name: aes_init_tables | is_library: True | library_name:  | is_array: None | confidence: low
purpose: AES table/context initialized by InitAes (S-box/round-key tables plus a status word)
fields:
  0x4c0  uint32_t     init_flag  write-only, set once tables built
  0x910  uint32_t     status  read-only trailing status/ready word

<ground-truth bundle for global_1480>
### cluster global_1480  (global, 1 members, 2 fields, size>=0x914)

Global object at fixed address 0x0007b518.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - InitAes @ 0x7b468  as 0x0007b518  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1480 {
    uint8_t    _pad_0x0[0x4c0];   /* +0x0 pad */
    uint32_t   field_0x4c0;   /* +0x4c0  sz=4 rw=w types=uint */
    uint8_t    _pad_0x4c4[0x44c];   /* +0x4c4 pad */
    uint32_t   field_0x910;   /* +0x910  sz=4 rw=r types=int */
};
```
