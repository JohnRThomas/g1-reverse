### struct panel_ctx  (G1-original)  cid=param_0117

purpose: Display panel driver context manipulated by panel_on when powering the LCD panel.

This object is accessed by these functions (read their fully-named source):
  - panel_on  (as param_1)  ->  recon/readable_sources/app/g1/panel_on.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct panel_ctx {
    uint32_t     field_0x35c;  /* +0x35c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x374;  /* +0x374  rw=rw sz=4 */   <-- NAME ME
};
```