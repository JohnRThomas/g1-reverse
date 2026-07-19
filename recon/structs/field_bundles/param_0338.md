### struct qspi_config_g1  (G1-original)  cid=param_0338

purpose: param_1 of qspi_configure_pins_and_interface: G1 QSPI config (GPIO pin words + protocol/PHY bytes readoc/writeoc/addrmode/sck_delay/spi_mode/sck_freq + flags word + irq priority).

This object is accessed by these functions (read their fully-named source):
  - qspi_configure_pins_and_interface  (as param_1)  ->  recon/readable_sources/app/library/qspi_configure_pins_and_interface.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct qspi_config_g1 {
    uint8_t      field_0x7;  /* +0x7  rw=r sz=1 */   <-- NAME ME
    uint32_t     pin_a;  /* +0x8  rw=r sz=1,4 */
    uint32_t     pin_b;  /* +0xc  rw=r sz=4 */
    uint32_t     pin_c;  /* +0x10  rw=r sz=4 */
    uint32_t     pin_d;  /* +0x14  rw=r sz=4 */
    uint32_t     pin_e;  /* +0x18  rw=r sz=4 */
    uint8_t      readoc;  /* +0x1d  rw=r sz=1 */
    uint8_t      writeoc;  /* +0x1e  rw=r sz=1 */
    uint8_t      addrmode;  /* +0x1f  rw=r sz=1 */
    uint8_t      sck_delay;  /* +0x21  rw=r sz=1 */
    uint8_t      spi_mode;  /* +0x22  rw=r sz=1 */
    uint8_t      sck_freq;  /* +0x23  rw=r sz=1 */
    uint32_t     skip_cfg_flags;  /* +0x24  rw=r sz=4 */
    uint8_t      irq_priority;  /* +0x29  rw=r sz=1 */
    uint8_t      reserved;  /* +0x2a  rw=r sz=1 */
};
```