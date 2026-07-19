### cluster param_0319  (param, 10 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 3/10 members are LIBRARY-class)

members (10 shown of 10):
  - boot_write_image_trailer_magic @ 0x63ff8  as param_1  [APPLICATION]
  - flash_read_boot_swap_ate @ 0x6403c  as param_1  [APPLICATION]
  - boot_set_next @ 0x641e4  as param_1  [APPLICATION]
  - flash_area_read @ 0x7ef80  as param_1  [LIBRARY]
  - flash_area_write @ 0x7efaa  as param_1  [LIBRARY]
  - flash_area_erase @ 0x7efd4  as param_1  [APPLICATION]
  - flash_area_erased_val @ 0x7f012  as param_1  [LIBRARY]
  - flash_calc_prev_ate_offset @ 0x84d64  as param_1  [APPLICATION]
  - nvs_flush_close_ate @ 0x84e58  as param_1  [APPLICATION]
  - flash_verify_write_at_current_offset @ 0x84e66  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0319 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int,uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
};
```