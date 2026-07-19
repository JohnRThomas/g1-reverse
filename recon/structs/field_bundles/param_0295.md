### struct pdm_config_g1  (G1-original)  cid=param_0295

purpose: param_2 of pdm_configure_clock_and_init: G1 PDM mic config (pin/clock word + config words for mode/edge/gain), later translated into nrfx_pdm calls.

This object is accessed by these functions (read their fully-named source):
  - pdm_configure_clock_and_init  (as param_2)  ->  recon/readable_sources/app/g1/pdm_configure_clock_and_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pdm_config_g1 {
    uint32_t     pin_clk;  /* +0x4  rw=r sz=4 */
    uint32_t     pin_din;  /* +0x10  rw=r sz=4 */
    uint32_t     mode;  /* +0x14  rw=r sz=4 */
    uint32_t     edge;  /* +0x18  rw=r sz=4 */
    uint32_t     clock_freq;  /* +0x1c  rw=r sz=4 */
    uint32_t     gain_l;  /* +0x20  rw=r sz=4 */
    uint32_t     gain_r;  /* +0x24  rw=r sz=4 */
    uint8_t      field_0x25;  /* +0x25  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0x26;  /* +0x26  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x27;  /* +0x27  rw=w sz=1 */   <-- NAME ME
};
```