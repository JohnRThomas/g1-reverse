### struct bt_hci_cmd_state_set  (library:bt_hci_cmd_state_set)  cid=param_0189

purpose: Zephyr BT HCI command-state descriptor set up by bt_hci_cmd_state_set_init (param_2).

This object is accessed by these functions (read their fully-named source):
  - bt_hci_cmd_state_set_init  (as param_2)  ->  recon/readable_sources/app/library/bt_hci_cmd_state_set_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_hci_cmd_state_set {
    uint8_t      field_0x2;  /* +0x2  rw=w sz=1 */   <-- NAME ME
    uint32_t     bit_or_val;  /* +0x4  rw=r sz=4 */
};
```