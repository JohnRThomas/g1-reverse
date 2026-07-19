### struct fmt_conv_spec  (G1-original)  cid=param_0430

purpose: Internal printf/scanf conversion-specifier fragment shared by vfprintf_core, vfprintf_field_scan_match, and scanf_convert_integer_field (a width/flags 16-bit field).

This object is accessed by these functions (read their fully-named source):
  - vfprintf_core  (as param_2)  ->  recon/readable_sources/app/library/vfprintf_core.c
  - vfprintf_field_scan_match  (as param_3)  ->  recon/readable_sources/app/library/vfprintf_field_scan_match.c
  - scanf_convert_integer_field  (as param_3)  ->  recon/readable_sources/app/g1/scanf_convert_integer_field.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct fmt_conv_spec {
    uint16_t     width_or_flags;  /* +0x3  rw=r sz=2 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
};
```