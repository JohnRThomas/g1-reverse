# Final zero-collision CPUAPP ownership milestone

The pinned configured Zephyr `lib/os/heap.c` owner has 19 uniquely relocation-normalized exact firmware sections; only `sys_heap_usable_size` and `sys_heap_aligned_realloc` are absent. `sys_heap_init` and `sys_heap_alloc` are therefore excluded atomically while recovered C and address backmaps remain evidence.

The corrected Bluetooth `id.c` mapping is `0x54ea8 = bt_id_add.part.0`, `0x5505c = bt_id_add`, and `0x80fd2 = hci_id_add`. The implementation part and public wrapper move together, and the sole recovered caller binds the SDK public wrapper.

The real retain-all ownership link moves **3 -> 0** with no added collision. A separate non-retain-all build produces `zephyr.elf`, `zephyr.bin`, and a merged-domain HEX with no undefined symbols. The two embedded SVC continuations remain the unchanged unresolved input surface. Remaining non-collision work is recorded separately in the machine receipt: production CPUAPP roots, the embedded SVC continuations, recovered CPUNET project ownership, and final section comparison. Private SDC remains report-only.
