### struct lcd_fb_xfer_local  (G1-original)  cid=stack_1036

purpose: Stack local (local_38) in reflash_fb_data_to_lcd: pair of status/index bytes during framebuffer-to-LCD transfer.

This object is accessed by these functions (read their fully-named source):
  - reflash_fb_data_to_lcd  (as local_38)  ->  recon/readable_sources/app/g1/reflash_fb_data_to_lcd.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lcd_fb_xfer_local {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=r sz=1 */   <-- NAME ME
};
```