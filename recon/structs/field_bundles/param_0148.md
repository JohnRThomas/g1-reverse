### struct log_msg_hdr  (library:log_msg / log_msg_generic header)  cid=param_0148

purpose: Zephyr logging message header/descriptor read by log_output_msg_process while formatting a log message (packed source-id/level/length header word plus following data word).

This object is accessed by these functions (read their fully-named source):
  - log_output_msg_process  (as param_2)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct log_msg_hdr {
    uint32_t     hdr_word;  /* +0x0  rw=r sz=4 */
    uint16_t     hdr_hi;  /* +0x2  rw=r sz=4 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
};
```