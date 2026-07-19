## review group param_0145  (1 cluster(s), kinds=param)

### proposal for param_0145
struct_name: ipc_static_vrings | is_library: True | library_name: struct ipc_static_vrings (Zephyr ipc_service static_vrings backend) | is_array: None | confidence: medium
purpose: Zephyr/OpenAMP static-vrings IPC service backend instance, initialized by ipc_static_vrings_init (holds vring descriptors, shared-memory addresses, and virtqueue/rpmsg configuration).
fields:
  0x18  uint32_t     field_0x18  
  0x20  uint32_t     field_0x20  
  0x28  uint32_t     field_0x28  
  0x2c  uint32_t     field_0x2c  
  0x30  uint32_t     field_0x30  
  0x34  uint32_t     field_0x34  
  0x3c  uint32_t     field_0x3c  
  0x8c  uint32_t     field_0x8c  
  0x90  uint32_t     field_0x90  
  0x94  uint32_t     field_0x94  
  0x98  uint32_t     field_0x98  
  0x9c  uint32_t     field_0x9c  
  0xa0  uint32_t     field_0xa0  
  0xa4  uint32_t     field_0xa4  
  0xa8  uint32_t     field_0xa8  
  0xac  uint32_t     field_0xac  
  0xb0  uint16_t     field_0xb0  
  0xb8  uint32_t     field_0xb8  
  0xbc  uint32_t     field_0xbc  
  0xc0  uint32_t     field_0xc0  
  0xc4  uint32_t     field_0xc4  
  0xc8  uint16_t     field_0xc8  
  0xd0  uint32_t     field_0xd0  
  0xd4  uint32_t     field_0xd4  
  0xd8  uint32_t     field_0xd8  

<ground-truth bundle for param_0145>
### cluster param_0145  (param, 1 members, 25 fields, size>=0xdc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - ipc_static_vrings_init @ 0x4d170  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0145 {
    uint8_t    _pad_0x0[0x18];   /* +0x0 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x1c[0x4];   /* +0x1c pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x24[0x4];   /* +0x24 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=w types=int */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x38[0x4];   /* +0x38 pad */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x40[0x4c];   /* +0x40 pad */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x90;   /* +0x90  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x94;   /* +0x94  sz=2,4 rw=r types=undefined2,undefined4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x9c;   /* +0x9c  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xac;   /* +0xac  sz=4 rw=w types=undefined4 */
    uint16_t   field_0xb0;   /* +0xb0  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0xb2[0x6];   /* +0xb2 pad */
    uint32_t   field_0xb8;   /* +0xb8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xbc;   /* +0xbc  sz=4 rw=w types=int */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc4;   /* +0xc4  sz=4 rw=w types=undefined4 */
    uint16_t   field_0xc8;   /* +0xc8  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0xca[0x6];   /* +0xca pad */
    uint32_t   field_0xd0;   /* +0xd0  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xd4;   /* +0xd4  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=w types=int */
};
```
