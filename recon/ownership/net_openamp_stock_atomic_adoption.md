# CPUNET OpenAMP `rpmsg.c` atomic adoption

The pinned OpenAMP source unit at commit
`42b7c577714b8f22ce82a901e19c1814af4609a8` owns all twelve `rpmsg.c`
sections selected in the CPUNET reference link. Every selected section is
byte-exact to the firmware after masking only its explicit ELF relocation
fields. The unused `rpmsg_release_tx_buffer` section is discarded by normal
section garbage collection; the object has no mutable source-unit state.

This operand-level audit corrects one mnemonic-only false identity:
`0x01035424` is `rpmsg_send_offchannel_raw` (`rdev->ops + 0x78`), while the
adjacent un-cataloged `0x01035450` body is `rpmsg_send_offchannel_nocopy`
(`rdev->ops + 0x88`). The raw address remains a reversible alias.

Four recovered C bodies and four previously cataloged stock bodies are now one
atomic stock source-unit group. Private SoftDevice Controller decisions are
unchanged and remain report-only. The JSON receipt is authoritative.
