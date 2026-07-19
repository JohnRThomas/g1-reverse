### struct net_buf_simple  (library:net_buf_simple)  cid=param_0647

purpose: Zephyr net_buf_simple header read by net_buf_simple_tailroom (a LIBRARY fn): current len, total size, and backing storage pointer __buf.

This object is accessed by these functions (read their fully-named source):
  - net_buf_simple_tailroom  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct net_buf_simple {
    uint16_t     field_0x1;  /* +0x1  rw=r sz=2 */   <-- NAME ME
    uint16_t     size;  /* +0x6  rw=r sz=2 */
    uint8_t *    __buf;  /* +0x8  rw=r sz=4 */
};
```