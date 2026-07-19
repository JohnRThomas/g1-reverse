### struct nrfx_spim_config  (library:nrfx_spim_config_t)  cid=param_0343

purpose: nrfx SPIM peripheral configuration struct passed to nrfx_spim_configure (pin selects, IRQ priority, ORC, frequency/mode/bit-order flags).

This object is accessed by these functions (read their fully-named source):
  - nrfx_spim_configure  (as param_2)  ->  recon/readable_sources/app/library/nrfx_spim_configure.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_spim_config {
    uint32_t     sck_pin;  /* +0x4  rw=r sz=1,4 */
    uint8_t      field_0x6;  /* +0x6  rw=r sz=1 */   <-- NAME ME
    uint8_t      mosi_pin;  /* +0x8  rw=r sz=1,4 */
    uint8_t      field_0x9;  /* +0x9  rw=r sz=1 */   <-- NAME ME
    uint32_t     miso_pin;  /* +0xc  rw=r sz=4 */
    uint8_t      ss_active_high;  /* +0x12  rw=r sz=1 */
    uint32_t     irq_priority;  /* +0x14  rw=r sz=4 */
    uint8_t      orc;  /* +0x19  rw=r sz=1 */
    uint8_t      frequency;  /* +0x1a  rw=r sz=1 */
    uint32_t     mode_or_ss;  /* +0x1c  rw=r sz=4 */
    uint8_t      bit_order;  /* +0x21  rw=r sz=1 */
    uint8_t      skip_gpio_cfg;  /* +0x22  rw=r sz=1 */
    uint8_t      skip_psel_cfg;  /* +0x23  rw=r sz=1 */
};
```