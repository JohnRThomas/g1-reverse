# CPUAPP normal cohesive-link audit

Configured against pinned NCS 2.5.1 with `G1_INTEGRATION_PROBE_RETAIN_ALL=OFF`. No linker relaxation or archive mutation.

The final ELF **does not link**. GNU ld rejects all 112 strong-symbol collisions before any owner can win; they are real cohesive-link blockers, not retain-all-only diagnostics.

- Collision symbols: **112**
- Source-unit batches: **37**
- Undefined-reference diagnostics: **0**
- Winning owners: **0**
- Wrong-owner findings: **0 assessable** (no ELF; 112 not assessable)

| Symbol | Firmware VA | Reconstruction owner | Upstream owner | Catalog decision |
|---|---:|---|---|---|
| `__retarget_lock_acquire_recursive` | `0x000510fc` | `app/libapp.a(__retarget_lock_acquire_recursive.c.obj)` | `zephyr/lib/libc/newlib/liblib__libc__newlib.a(libc-hooks.c.obj)` | `retain_reconstruction` |
| `__retarget_lock_release_recursive` | `0x00051134` | `app/libapp.a(__retarget_lock_release_recursive.c.obj)` | `zephyr/lib/libc/newlib/liblib__libc__newlib.a(libc-hooks.c.obj)` | `retain_reconstruction` |
| `__sinit` | `0x00076bcc` | `app/libapp.a(__sinit.c.obj)` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a(lib_a-findfp.o)` | `blocked` |
| `__sinit_lock_release` | `0x00076bc0` | `app/libapp.a(__sinit_lock_release.c.obj)` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a(lib_a-findfp.o)` | `blocked` |
| `_malloc_r` | `0x00076e20` | `app/libapp.a(_malloc_r.c.obj)` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a(lib_a-nano-mallocr.o)` | `blocked` |
| `_strtoul_r` | `0x00077b38` | `app/libapp.a(_strtoul_r.c.obj)` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a(lib_a-strtoul.o)` | `blocked` |
| `bt_att_create_pdu` | `0x00058eb0` | `app/libapp.a(bt_att_create_pdu.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(att.c.obj)` | `retain_reconstruction` |
| `bt_att_req_send` | `0x00059a90` | `app/libapp.a(bt_att_req_send.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(att.c.obj)` | `retain_reconstruction` |
| `bt_conn_le_param_update` | `0x0008157a` | `app/libapp.a(bt_conn_le_param_update.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(conn.c.obj)` | `retain_reconstruction` |
| `bt_conn_send_cb` | `0x000564cc` | `app/libapp.a(bt_conn_send_cb.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(conn.c.obj)` | `adopt_sdk_whole_public_owner` |
| `bt_conn_set_security` | `0x0008149a` | `app/libapp.a(bt_conn_set_security.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(conn.c.obj)` | `retain_reconstruction` |
| `bt_foreach_bond` | `0x0005e6d4` | `app/libapp.a(bt_foreach_bond.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_gatt_att_max_mtu_changed` | `0x0005c76c` | `app/libapp.a(bt_gatt_att_max_mtu_changed.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `adopt_sdk_whole_public_owner` |
| `bt_gatt_attr_get_handle` | `0x0005a9f4` | `app/libapp.a(bt_gatt_attr_get_handle.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_connected` | `0x0005c6c8` | `app/libapp.a(bt_gatt_connected.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `adopt_sdk_whole_public_owner` |
| `bt_gatt_disconnected` | `0x0005c9a4` | `app/libapp.a(bt_gatt_disconnected.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `adopt_sdk_whole_public_owner` |
| `bt_gatt_discover` | `0x0005b9cc` | `app/libapp.a(bt_gatt_discover.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_foreach_attr_type` | `0x0005aa84` | `app/libapp.a(bt_gatt_foreach_attr_type.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_indicate` | `0x0005b378` | `app/libapp.a(bt_gatt_indicate.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_init` | `0x0005a954` | `app/libapp.a(bt_gatt_init.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_notify_cb` | `0x0005b754` | `app/libapp.a(bt_gatt_notify_cb.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_read` | `0x0005c22c` | `app/libapp.a(bt_gatt_read.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_service_register` | `0x0005ad38` | `app/libapp.a(bt_gatt_service_register.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_gatt_subscribe` | `0x0005c4f0` | `app/libapp.a(bt_gatt_subscribe.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(gatt.c.obj)` | `retain_reconstruction` |
| `bt_hci_cmd_create` | `0x00053cd4` | `app/libapp.a(bt_hci_cmd_create.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(hci_core.c.obj)` | `retain_reconstruction` |
| `bt_hci_cmd_state_set_init` | `0x00053cb0` | `app/libapp.a(bt_hci_cmd_state_set_init.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(hci_core.c.obj)` | `retain_reconstruction` |
| `bt_id_add` | `0x00054ea8` | `app/libapp.a(bt_id_add.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(id.c.obj)` | `caller_cohesion` |
| `bt_keys_add_type` | `0x0005e9a0` | `app/libapp.a(bt_keys_add_type.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_clear` | `0x0005ea18` | `app/libapp.a(bt_keys_clear.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_find` | `0x0005e7c8` | `app/libapp.a(bt_keys_find.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_find_addr` | `0x0005e938` | `app/libapp.a(bt_keys_find_addr.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_find_irk` | `0x0005e83c` | `app/libapp.a(bt_keys_find_irk.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_foreach_type` | `0x0005e758` | `app/libapp.a(bt_keys_foreach_type.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_get_addr` | `0x0005e6a8` | `app/libapp.a(bt_keys_get_addr.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_get_type` | `0x0005e9d0` | `app/libapp.a(bt_keys_get_type.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_keys_store` | `0x0005ec18` | `app/libapp.a(bt_keys_store.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(keys.c.obj)` | `retain_reconstruction` |
| `bt_l2cap_connected` | `0x0005791c` | `app/libapp.a(bt_l2cap_connected.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(l2cap.c.obj)` | `retain_reconstruction` |
| `bt_l2cap_init` | `0x000579d0` | `app/libapp.a(bt_l2cap_init.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(l2cap.c.obj)` | `retain_reconstruction` |
| `bt_l2cap_recv` | `0x00057cc4` | `app/libapp.a(bt_l2cap_recv.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(l2cap.c.obj)` | `retain_reconstruction` |
| `bt_send` | `0x00054a44` | `app/libapp.a(bt_send.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(hci_core.c.obj)` | `retain_reconstruction` |
| `bt_settings_delete` | `0x00052fbc` | `app/libapp.a(bt_settings_delete.c.obj)` | `zephyr/subsys/bluetooth/host/libsubsys__bluetooth__host.a(settings.c.obj)` | `adopt_sdk_whole_public_owner` |
| `crc16_reflect` | `0x0007d9c0` | `app/libapp.a(crc16_reflect.c.obj)` | `zephyr/libzephyr.a(crc16_sw.c.obj)` | `retain_reconstruction` |
| `k_aligned_alloc` | `0x000758cc` | `app/libapp.a(k_aligned_alloc.c.obj)` | `zephyr/kernel/libkernel.a(mempool.c.obj)` | `retain_reconstruction` |
| `k_heap_free` | `0x00071b2c` | `app/libapp.a(k_heap_free.c.obj)` | `zephyr/kernel/libkernel.a(kheap.c.obj)` | `retain_reconstruction` |
| `k_mem_slab_alloc` | `0x00071c20` | `app/libapp.a(k_mem_slab_alloc.c.obj)` | `zephyr/kernel/libkernel.a(mem_slab.c.obj)` | `retain_reconstruction` |
| `k_mem_slab_free` | `0x00071cf4` | `app/libapp.a(k_mem_slab_free.c.obj)` | `zephyr/kernel/libkernel.a(mem_slab.c.obj)` | `retain_reconstruction` |
| `k_work_busy_get` | `0x00072e9c` | `app/libapp.a(k_work_busy_get.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `k_work_cancel` | `0x00072fe8` | `app/libapp.a(k_work_cancel.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `k_work_init` | `0x00072e50` | `app/libapp.a(k_work_init.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `k_work_queue_init` | `0x000730b4` | `app/libapp.a(k_work_queue_init.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `k_work_queue_start` | `0x000730e8` | `app/libapp.a(k_work_queue_start.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `k_work_reschedule_for_queue` | `0x00073424` | `app/libapp.a(k_work_reschedule_for_queue.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `k_work_schedule_for_queue` | `0x0007332c` | `app/libapp.a(k_work_schedule_for_queue.c.obj)` | `zephyr/kernel/libkernel.a(work.c.obj)` | `caller_cohesion` |
| `log_init` | `0x0004d678` | `app/libapp.a(log_init.c.obj)` | `zephyr/libzephyr.a(log_core.c.obj)` | `retain_reconstruction` |
| `log_output_dropped_process` | `0x0004de68` | `app/libapp.a(log_output_dropped_process.c.obj)` | `zephyr/libzephyr.a(log_output.c.obj)` | `adopt_sdk_whole_public_owner` |
| `log_output_process` | `0x0004def8` | `app/libapp.a(log_output_process.c.obj)` | `zephyr/libzephyr.a(log_output.c.obj)` | `caller_cohesion` |
| `malloc` | `0x00076d6c` | `app/libapp.a(malloc.c.obj)` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a(lib_a-malloc.o)` | `blocked` |
| `metal_bus_unregister` | `0x000680f8` | `app/libapp.a(metal_bus_unregister.c.obj)` | `modules/libmetal/libmetal/lib/libmetal.a(device.c.obj)` | `adopt_sdk_whole_public_owner` |
| `mpsc_pbuf_claim` | `0x0004d56c` | `app/libapp.a(mpsc_pbuf_claim.c.obj)` | `zephyr/libzephyr.a(mpsc_pbuf.c.obj)` | `retain_reconstruction` |
| `mpsc_pbuf_commit` | `0x0004be0c` | `app/libapp.a(mpsc_pbuf_commit.c.obj)` | `zephyr/libzephyr.a(mpsc_pbuf.c.obj)` | `retain_reconstruction` |
| `mpsc_pbuf_free` | `0x0004bfc8` | `app/libapp.a(mpsc_pbuf_free.c.obj)` | `zephyr/libzephyr.a(mpsc_pbuf.c.obj)` | `retain_reconstruction` |
| `mpsc_pbuf_init` | `0x0004bc28` | `app/libapp.a(mpsc_pbuf_init.c.obj)` | `zephyr/libzephyr.a(mpsc_pbuf.c.obj)` | `retain_reconstruction` |
| `net_buf_append_bytes` | `0x0005f450` | `app/libapp.a(net_buf_append_bytes.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_frag_add` | `0x0005f390` | `app/libapp.a(net_buf_frag_add.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_frag_insert` | `0x0005f338` | `app/libapp.a(net_buf_frag_insert.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_frag_last` | `0x0005f304` | `app/libapp.a(net_buf_frag_last.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_put` | `0x0005f200` | `app/libapp.a(net_buf_put.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_ref` | `0x0005f2d4` | `app/libapp.a(net_buf_ref.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_reset` | `0x0005ee6c` | `app/libapp.a(net_buf_reset.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_simple_add` | `0x0005f5d0` | `app/libapp.a(net_buf_simple_add.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf_simple.c.obj)` | `retain_reconstruction` |
| `net_buf_simple_push` | `0x0005f518` | `app/libapp.a(net_buf_simple_push.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf_simple.c.obj)` | `retain_reconstruction` |
| `net_buf_simple_reserve` | `0x0005f4d4` | `app/libapp.a(net_buf_simple_reserve.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf_simple.c.obj)` | `retain_reconstruction` |
| `net_buf_slist_get` | `0x0005f148` | `app/libapp.a(net_buf_slist_get.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_slist_put` | `0x0005f074` | `app/libapp.a(net_buf_slist_put.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `net_buf_unref` | `0x0005f24c` | `app/libapp.a(net_buf_unref.c.obj)` | `zephyr/subsys/net/libsubsys__net.a(buf.c.obj)` | `retain_reconstruction` |
| `nrfx_clock_init` | `0x00065190` | `app/libapp.a(nrfx_clock_init.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_clock.c.obj)` | `retain_reconstruction` |
| `nrfx_clock_stop` | `0x00065000` | `app/libapp.a(nrfx_clock_stop.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_clock.c.obj)` | `retain_reconstruction` |
| `nrfx_dppi_channel_alloc` | `0x00067e8c` | `app/libapp.a(nrfx_dppi_channel_alloc.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_dppi.c.obj)` | `retain_reconstruction` |
| `nrfx_gpiote_init` | `0x00065940` | `app/libapp.a(nrfx_gpiote_init.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_gpiote.c.obj)` | `retain_reconstruction` |
| `nrfx_gppi_task_endpoint_clear` | `0x00064fd4` | `app/libapp.a(nrfx_gppi_task_endpoint_clear.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_gppi_dppi.c.obj)` | `retain_reconstruction` |
| `nrfx_gppi_task_endpoint_setup` | `0x00064f78` | `app/libapp.a(nrfx_gppi_task_endpoint_setup.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_gppi_dppi.c.obj)` | `retain_reconstruction` |
| `nrfx_nvmc_page_erase` | `0x00065f1c` | `app/libapp.a(nrfx_nvmc_page_erase.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_nvmc.c.obj)` | `retain_reconstruction` |
| `nrfx_nvmc_word_write` | `0x00065f80` | `app/libapp.a(nrfx_nvmc_word_write.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_nvmc.c.obj)` | `retain_reconstruction` |
| `nrfx_pdm_buffer_set` | `0x00066270` | `app/libapp.a(nrfx_pdm_buffer_set.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_pdm.c.obj)` | `retain_reconstruction` |
| `nrfx_pdm_init` | `0x0006615c` | `app/libapp.a(nrfx_pdm_init.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_pdm.c.obj)` | `retain_reconstruction` |
| `nrfx_pdm_start` | `0x00066214` | `app/libapp.a(nrfx_pdm_start.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_pdm.c.obj)` | `retain_reconstruction` |
| `nrfx_pdm_stop` | `0x00066300` | `app/libapp.a(nrfx_pdm_stop.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_pdm.c.obj)` | `retain_reconstruction` |
| `nrfx_pdm_uninit` | `0x000661dc` | `app/libapp.a(nrfx_pdm_uninit.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_pdm.c.obj)` | `retain_reconstruction` |
| `nrfx_qspi_erase` | `0x000669f4` | `app/libapp.a(nrfx_qspi_erase.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_qspi.c.obj)` | `retain_reconstruction` |
| `nrfx_qspi_init` | `0x00066994` | `app/libapp.a(nrfx_qspi_init.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_qspi.c.obj)` | `retain_reconstruction` |
| `nrfx_qspi_read` | `0x00066bc4` | `app/libapp.a(nrfx_qspi_read.c.obj)` | `modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a(nrfx_qspi.c.obj)` | `retain_reconstruction` |
| `rpmsg_init_vdev` | `0x00071560` | `app/libapp.a(rpmsg_init_vdev.c.obj)` | `modules/open-amp/open-amp/lib/libopen_amp.a(rpmsg_virtio.c.obj)` | `adopt_sdk_whole_public_owner` |
| `settings_commit_subtree` | `0x0004e6a8` | `app/libapp.a(settings_commit_subtree.c.obj)` | `zephyr/libzephyr.a(settings.c.obj)` | `retain_reconstruction` |
| `settings_load` | `0x0007f192` | `app/libapp.a(settings_load.c.obj)` | `zephyr/libzephyr.a(settings_store.c.obj)` | `retain_reconstruction` |
| `settings_load_subtree` | `0x0004e3e8` | `app/libapp.a(settings_load_subtree.c.obj)` | `zephyr/libzephyr.a(settings_store.c.obj)` | `adopt_sdk_whole_public_owner` |
| `settings_load_subtree_direct` | `0x0004e434` | `app/libapp.a(settings_load_subtree_direct.c.obj)` | `zephyr/libzephyr.a(settings_store.c.obj)` | `retain_reconstruction` |
| `settings_parse_and_lookup` | `0x0004e540` | `app/libapp.a(settings_parse_and_lookup.c.obj)` | `zephyr/libzephyr.a(settings.c.obj)` | `retain_reconstruction` |
| `settings_register` | `0x0004e494` | `app/libapp.a(settings_register.c.obj)` | `zephyr/libzephyr.a(settings.c.obj)` | `retain_reconstruction` |
| `sys_heap_alloc` | `0x0007e12a` | `app/libapp.a(sys_heap_alloc.c.obj)` | `zephyr/libzephyr.a(heap.c.obj)` | `caller_cohesion` |
| `sys_heap_init` | `0x0004b3c8` | `app/libapp.a(sys_heap_init.c.obj)` | `zephyr/libzephyr.a(heap.c.obj)` | `caller_cohesion` |
| `virtqueue_free` | `0x00070ee4` | `app/libapp.a(virtqueue_free.c.obj)` | `modules/open-amp/open-amp/lib/libopen_amp.a(virtqueue.c.obj)` | `retain_reconstruction` |
| `z_arm_bus_fault` | `0x00050558` | `app/libapp.a(z_arm_bus_fault.c.obj)` | `zephyr/arch/arch/arm/core/aarch32/cortex_m/libarch__arm__core__aarch32__cortex_m.a(fault_s.S.obj)` | `blocked` |
| `z_arm_fault` | `0x000507d4` | `app/libapp.a(z_arm_fault.c.obj)` | `zephyr/arch/arch/arm/core/aarch32/cortex_m/libarch__arm__core__aarch32__cortex_m.a(fault.c.obj)` | `retain_reconstruction` |
| `z_arm_mpu_fault` | `0x000503d8` | `app/libapp.a(z_arm_mpu_fault.c.obj)` | `zephyr/arch/arch/arm/core/aarch32/cortex_m/libarch__arm__core__aarch32__cortex_m.a(fault_s.S.obj)` | `blocked` |
| `z_arm_usage_fault` | `0x000506ac` | `app/libapp.a(z_arm_usage_fault.c.obj)` | `zephyr/arch/arch/arm/core/aarch32/cortex_m/libarch__arm__core__aarch32__cortex_m.a(fault_s.S.obj)` | `blocked` |
| `z_impl_k_queue_init` | `0x000864e8` | `app/libapp.a(z_impl_k_queue_init.c.obj)` | `zephyr/kernel/libkernel.a(queue.c.obj)` | `retain_reconstruction` |
| `z_log_msg_free` | `0x0004d578` | `app/libapp.a(z_log_msg_free.c.obj)` | `zephyr/libzephyr.a(log_core.c.obj)` | `retain_reconstruction` |
| `z_log_msg_pending` | `0x0004d588` | `app/libapp.a(z_log_msg_pending.c.obj)` | `zephyr/libzephyr.a(log_core.c.obj)` | `retain_reconstruction` |
| `z_reschedule` | `0x000739f0` | `app/libapp.a(z_reschedule.c.obj)` | `zephyr/kernel/libkernel.a(sched.c.obj)` | `retain_reconstruction` |
| `z_thread_abort` | `0x000748b8` | `app/libapp.a(z_thread_abort.c.obj)` | `zephyr/kernel/libkernel.a(sched.c.obj)` | `retain_reconstruction` |
| `z_thread_priority_set` | `0x00074184` | `app/libapp.a(z_thread_priority_set.c.obj)` | `zephyr/kernel/libkernel.a(sched.c.obj)` | `retain_reconstruction` |
| `z_unpend_first_thread` | `0x000744a4` | `app/libapp.a(z_unpend_first_thread.c.obj)` | `zephyr/kernel/libkernel.a(sched.c.obj)` | `retain_reconstruction` |
