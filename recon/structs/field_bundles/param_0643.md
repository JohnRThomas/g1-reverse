### struct smp_f6_input_buf  (library:bt_crypto f6 input buffer)  cid=param_0643

purpose: Byte buffer carrying key/material fragments passed as param_6 to bt_crypto_f6 (SM crypto f6 confirm-value function).

This object is accessed by these functions (read their fully-named source):
  - bt_crypto_f6  (as param_6)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_f6_input_buf {
    uint32_t     field_0x1;  /* +0x1  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x5;  /* +0x5  rw=r sz=2 */   <-- NAME ME
};
```