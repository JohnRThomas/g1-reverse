### struct vfprintf_conv_state  (G1-original)  cid=param_0421

purpose: picolibc/newlib vfprintf conversion-spec state (width/precision/flags, pad char, sign, formatted-digit buffer) shared by printf_render_float/vfprintf_format_engine/vfprintf_emit_padded_field.

This object is accessed by these functions (read their fully-named source):
  - printf_render_float  (as param_2)  ->  recon/readable_sources/app/g1/printf_render_float.c
  - vfprintf_format_engine  (as param_2)  ->  recon/readable_sources/app/library/vfprintf_format_engine.c
  - vfprintf_emit_padded_field  (as param_2)  ->  recon/readable_sources/app/library/vfprintf_emit_padded_field.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct vfprintf_conv_state {
    uint32_t     width_or_flags;  /* +0x4  rw=r sz=4 */
    uint32_t     precision;  /* +0x8  rw=r sz=4 */
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint8_t      pad_char;  /* +0x42  rw=w sz=1 */
    uint8_t      sign_flag;  /* +0x43  rw=rw sz=1 */
    uint8_t      field_0x45;  /* +0x45  rw=rw sz=1 */   <-- NAME ME
    uint32_t     digit_buf_ptr;  /* +0x48  rw=r sz=4 */
    uint32_t     digit_count;  /* +0x4c  rw=r sz=4 */
    uint32_t     field_0x58;  /* +0x58  rw=r sz=4 */   <-- NAME ME
};
```