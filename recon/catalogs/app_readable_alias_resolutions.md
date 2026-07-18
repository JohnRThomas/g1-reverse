# CPUAPP readable alias resolutions

These aliases resolve human-readable call spellings back to their
CFG-proven firmware identities without changing function bodies.

| Symbol | Target | VA | Evidence |
|---|---|---:|---|
| `dispatch_hci_event` | `FUN_00053658` | 0x00053658 | Readable caller declaration retains the raw FUN_00053658 back-map; the target is the CFG-proven 88-byte event-table dispatcher. |
| `process_number_completed_packets` | `FUN_00056394` | 0x00056394 | Readable caller declaration retains the raw FUN_00056394 back-map; the target is present in the authoritative 2113/2113 CPUAPP PASS corpus. |
| `version_string` | `ver_str` | 0x00053344 | Readable caller declaration retains the raw FUN_00053344 back-map and the durable function catalog names that identity ver_str. |
