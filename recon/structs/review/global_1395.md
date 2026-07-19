## review group global_1395  (1 cluster(s), kinds=global)

### proposal for global_1395
struct_name: k_spinlock | is_library: True | library_name: k_spinlock | is_array: False | confidence: medium
purpose: Zephyr SMP spinlock object whose owner/thread fields are set by z_spin_lock_set_owner in debug/validate builds
fields:
  0x8  uint32_t     owner_thread  tid/owner pointer set on lock acquisition (SPIN_VALIDATE debug field)
  0x10  uint8_t      lock_flag  locked byte / lock_key debug flag

<ground-truth bundle for global_1395>
### cluster global_1395  (global, 1 members, 2 fields, size>=0x14)

Global object at fixed address 0x00072084.

library hint: LIKELY LIBRARY (prefixes: z; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_spin_lock_set_owner @ 0x72078  as 0x00072084  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1395 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=byte */
    uint8_t    _pad_0x11[0x3];   /* +0x11 pad */
};
```
