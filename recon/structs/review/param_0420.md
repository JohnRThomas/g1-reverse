## review group param_0420  (1 cluster(s), kinds=param)

### proposal for param_0420
struct_name: reent_stdio_state | is_library: True | library_name: struct _reent (newlib/picolibc) | is_array: False | confidence: medium
purpose: Newlib/Picolibc per-task reentrancy struct (_reent) initialized by __sinit to set up standard I/O streams.
fields:
  0x4  uint32_t     field_0x4  rw word, e.g. errno or stdin ptr
  0x8  uint32_t     field_0x8  rw word, e.g. stdout ptr
  0xc  uint32_t     field_0xc  rw word, e.g. stderr ptr
  0x18  int32_t      field_0x18  rw word
  0x28  uint32_t     field_0x28  write-only word
  0x48  uint32_t     field_0x48  write-only word
  0x4c  uint32_t     field_0x4c  write-only word
  0x50  uint32_t     field_0x50  write-only word

<ground-truth bundle for param_0420>
### cluster param_0420  (param, 1 members, 8 fields, size>=0x54)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - __sinit @ 0x76bcc  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0420 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=undefined4 */
    uint8_t    _pad_0x10[0x8];   /* +0x10 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0x1c[0xc];   /* +0x1c pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x2c[0x1c];   /* +0x2c pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=w types=undefined4 */
};
```
