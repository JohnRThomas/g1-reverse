## review group param_0025  (1 cluster(s), kinds=param)

### proposal for param_0025
struct_name: esbs_ipc_recv_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Large (~4KB) local ESB/IPC service receive context: header flags/state bytes at low offsets, a mid-region status byte, a big data payload region, then trailing pointer + counters
fields:
  0xc9  uint8_t      field_0xc9  state/flag byte, rw
  0xca  uint8_t      field_0xca  state/flag byte, rw
  0xcb  uint8_t      field_0xcb  write-only flag
  0xcc  uint8_t      field_0xcc  read-only flag
  0xcd  uint8_t      field_0xcd  
  0xce  char         field_0xce  
  0xcf  char         field_0xcf  
  0xd5  uint8_t      field_0xd5  
  0xda  char         field_0xda  rw
  0xe4  uint8_t      field_0xe4  rw flag
  0xe9  uint8_t      field_0xe9  write-only
  0xea  uint8_t      field_0xea  
  0xeb  uint8_t      field_0xeb  
  0xec  uint8_t      field_0xec  
  0xee4  uint8_t      field_0xee4  write-only, likely marks end of a large payload buffer region
  0xfe6  char         field_0xfe6  
  0xfec  void *       data_ptr  rw pointer, likely buffer/next-node pointer
  0xff4  uint32_t     field_0xff4  read-only int, likely length/size
  0x1024  uint32_t     field_0x1024  
  0x1028  uint32_t     field_0x1028  

<ground-truth bundle for param_0025>
### cluster param_0025  (param, 1 members, 20 fields, size>=0x102c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - local_esbs_ipc_service_recv @ 0x15960  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0025 {
    uint8_t    _pad_0x0[0xc9];   /* +0x0 pad */
    uint8_t    field_0xc9;   /* +0xc9  sz=1 rw=rw types=byte */
    uint8_t    field_0xca;   /* +0xca  sz=1 rw=rw types=byte,char */
    uint8_t    field_0xcb;   /* +0xcb  sz=1 rw=w types=byte */
    uint8_t    field_0xcc;   /* +0xcc  sz=1 rw=r types=byte */
    uint8_t    field_0xcd;   /* +0xcd  sz=1 rw=r types=byte */
    uint8_t    field_0xce;   /* +0xce  sz=1 rw=r types=char */
    uint8_t    field_0xcf;   /* +0xcf  sz=1 rw=r types=char */
    uint8_t    _pad_0xd0[0x5];   /* +0xd0 pad */
    uint8_t    field_0xd5;   /* +0xd5  sz=1 rw=r types=char,undefined1 */
    uint8_t    _pad_0xd6[0x4];   /* +0xd6 pad */
    uint8_t    field_0xda;   /* +0xda  sz=1 rw=rw types=char */
    uint8_t    _pad_0xdb[0x9];   /* +0xdb pad */
    uint8_t    field_0xe4;   /* +0xe4  sz=1 rw=rw types=byte */
    uint8_t    _pad_0xe5[0x4];   /* +0xe5 pad */
    uint8_t    field_0xe9;   /* +0xe9  sz=1 rw=w types=byte */
    uint8_t    field_0xea;   /* +0xea  sz=1 rw=w types=byte */
    uint8_t    field_0xeb;   /* +0xeb  sz=1 rw=w types=byte */
    uint8_t    field_0xec;   /* +0xec  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xed[0xdf7];   /* +0xed pad */
    uint8_t    field_0xee4;   /* +0xee4  sz=1 rw=w types=byte */
    uint8_t    _pad_0xee5[0x101];   /* +0xee5 pad */
    uint8_t    field_0xfe6;   /* +0xfe6  sz=1 rw=r types=char */
    uint8_t    _pad_0xfe7[0x5];   /* +0xfe7 pad */
    void *     field_0xfec;   /* +0xfec  sz=4 rw=rw types=ptr */
    uint8_t    _pad_0xff0[0x4];   /* +0xff0 pad */
    uint32_t   field_0xff4;   /* +0xff4  sz=4 rw=r types=int */
    uint8_t    _pad_0xff8[0x2c];   /* +0xff8 pad */
    uint32_t   field_0x1024;   /* +0x1024  sz=4 rw=r types=int */
    uint32_t   field_0x1028;   /* +0x1028  sz=4 rw=r types=int */
};
```
