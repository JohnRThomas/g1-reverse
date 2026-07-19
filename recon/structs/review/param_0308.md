## review group param_0308  (1 cluster(s), kinds=param)

### proposal for param_0308
struct_name: lsm6dso_dev_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: LSM6DSO IMU driver context used by lsm6dso_init_chip: device/config int and a bus handle pointer
fields:
  0x4  uint32_t     field_0x4  read-only int, likely chip id/config
  0x10  void *       field_0x10  read-only pointer, likely bus/device handle

<ground-truth bundle for param_0308>
### cluster param_0308  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - lsm6dso_init_chip @ 0x622a0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0308 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=int,ptr */
};
```
