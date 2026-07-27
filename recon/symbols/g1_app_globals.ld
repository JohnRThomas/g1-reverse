/* Auto-generated: pin reconstructed app-core symbols to their original
 * addresses so &name resolves to the real VA (whole-image byte-match).
 * 3337 symbols. Include via: INSERT or -T with the main linker script. */

PROVIDE(rodata_f000 = 0x0000f000);
PROVIDE(rodata_fa08 = 0x0000fa08);
PROVIDE(rodata_fc09 = 0x0000fc09);
PROVIDE(rodata_fd00 = 0x0000fd00);
PROVIDE(rodata_ff20 = 0x0000ff20);
PROVIDE(rodata_ff41 = 0x0000ff41);
PROVIDE(rodata_10000 = 0x00010000);
PROVIDE(rodata_1253c = 0x0001253c);
PROVIDE(rodata_12540 = 0x00012540);
PROVIDE(rodata_12544 = 0x00012544);
PROVIDE(rodata_12548 = 0x00012548);
PROVIDE(rodata_1254c = 0x0001254c);
PROVIDE(rodata_12554 = 0x00012554);
PROVIDE(rodata_12558 = 0x00012558);
PROVIDE(rodata_1255c = 0x0001255c);
PROVIDE(rodata_1256c = 0x0001256c);
PROVIDE(rodata_1274f = 0x0001274f);
PROVIDE(rodata_162ed = local_ipc_service_recv | 1); /* iteration 8 rebind */
PROVIDE(rodata_16bf1 = local_esbm_ipc_service_recv | 1); /* iteration 8 rebind */
PROVIDE(rodata_17819 = 0x00017819);
PROVIDE(rodata_1827d = 0x0001827d);
PROVIDE(rodata_18ef5 = 0x00018ef5);
PROVIDE(rodata_19ff1 = 0x00019ff1);
PROVIDE(rodata_1f400 = 0x0001f400);
PROVIDE(rodata_22121 = 0x00022121);
PROVIDE(rodata_243dc = 0x000243dc);
PROVIDE(rodata_243e0 = 0x000243e0);
PROVIDE(rodata_243e4 = 0x000243e4);
PROVIDE(rodata_243e8 = 0x000243e8);
PROVIDE(rodata_243ec = 0x000243ec);
PROVIDE(rodata_243f0 = 0x000243f0);
PROVIDE(rodata_243f4 = 0x000243f4);
PROVIDE(rodata_243f8 = 0x000243f8);
/* CODE-POINTER REBIND (iteration 40): rodata_24a41 / rodata_24ad9 /
 * rodata_25021 / rodata_25059 -- and rodata_7c38b / rodata_7c39d below --
 * were the six odd (Thumb) op-vtable entries that event_record_init and
 * fill_record_type8 plant at record+4/+8/+12.  All six targets are now
 * recovered functions (recon/app/src/FUN_0007c38a.c, FUN_00024a40.c,
 * FUN_00025020.c and their type-8 siblings), and the two constructors take
 * their addresses through ADDR_<name>_THUMB in recon/symbols/g1_app_symbols.h,
 * which also ROOTS them against --gc-sections (a lazy PROVIDE would not).
 * The numeric pins are therefore gone, so a link that lost one of the six
 * fails loudly instead of `bx`ing into our own relocated .text again. */
/* CODE-POINTER REBIND (iteration 4): odd (Thumb) flash pin was the
 * original-image entry 0x25ae8 of the IPC-service registrar, stored raw into
 * ctx[0x64] by register_ipc_service_context and later called by main through
 * ldr r2,[r4,#0x778]; blx r2.  Unrelocated in our build it landed inside
 * check_sw0_status, which aborted the boot with a usage fault.
 * Evidence: bytes at 0x25ae8 are a complete function (push {r0,r1,r4,lr} ...
 * pop {r4,pc}) in the uncatalogued Ghidra gap 0x25ad2..0x25b78, reconstructed
 * and parity-proven as register_ipc_service_recv_callback (its own %s()
 * log argument at 0x9f6a3 names it). */
PROVIDE(rodata_25ae9 = register_ipc_service_recv_callback | 1);
/* CODE-POINTER REBIND (iteration 13): these four odd (Thumb) flash pins are the
 * IMU-fusion vtable that register_imu_funsion_context (0x26250) writes into its
 * context at +0x8c/+0x90/+0x94/+0x98, and main() calls the +0x8c slot as
 * `ldr r3,[r4,#0xf70] ; blx r3`.  Ghidra catalogued none of the four targets
 * (gaps 0x25d8c..0x25ecc and 0x25f90..0x26100), so they stayed literal and
 * main() branched into the middle of low_speed_peripheral_dispatch_thread in
 * our link -- the boot's first divergence at 2.0 s.  All four are now
 * reconstructed (cfg_verify PASS 200/200 each) and bound to their real
 * definitions.  0x25fac == imu_fusion_init holds the 13th k_thread_create call
 * (0x260c2), which is the only site that creates imu_fusion_thread. */
PROVIDE(rodata_25d8d = set_imu_thread_delay | 1);
PROVIDE(rodata_25dc5 = imu_fusion_resume | 1);
PROVIDE(rodata_25df9 = imu_fusion_suspend | 1);
PROVIDE(rodata_25fad = imu_fusion_init | 1);
/* imu_fusion_init's own literals: the log-tag / format strings it passes. */
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of master_display_thread; unrelocated in our build.
 * Evidence: durable-map exact entry 0x2692c; z_impl_k_thread_create entry arg in run_main_dispatch_thread. */
PROVIDE(rodata_2692d = master_display_thread | 1);
PROVIDE(rodata_27cf8 = 0x00027cf8);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of slave_display_thread; unrelocated in our build.
 * Evidence: durable-map exact entry 0x27cfc; z_impl_k_thread_create entry arg in run_main_dispatch_thread. */
PROVIDE(rodata_27cfd = slave_display_thread | 1);
PROVIDE(rodata_28000 = 0x00028000);
PROVIDE(rodata_2e301 = 0x0002e301);
PROVIDE(rodata_30000 = 0x00030000);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of aging_mode_thread; unrelocated in our build.
 * Evidence: durable-map exact entry 0x32420; z_impl_k_thread_create entry arg in start_aging_mode_thread. */
PROVIDE(rodata_32421 = aging_mode_thread | 1);
PROVIDE(rodata_33c44 = 0x00033c44);
PROVIDE(rodata_33c48 = 0x00033c48);
PROVIDE(rodata_35775 = panel_render_screen_dispatch | 1); /* iteration 14 rebind */
PROVIDE(rodata_40000 = 0x00040000);
PROVIDE(rodata_40002 = 0x00040002);
PROVIDE(rodata_40202 = 0x00040202);
PROVIDE(rodata_46ce9 = panel_set_brightness_level | 1); /* iteration 14 rebind */
PROVIDE(rodata_46d8d = panel_suspend | 1); /* iteration 14 rebind */
PROVIDE(rodata_46f21 = panel_resume | 1); /* iteration 14 rebind */
PROVIDE(rodata_4b1b5 = 0x0004b1b5);
PROVIDE(rodata_4b8a5 = 0x0004b8a5);
PROVIDE(rodata_4c38d = 0x0004c38d);
PROVIDE(rodata_4daad = 0x0004daad);
/* P4 iteration 31: nus.c's `on_sent`, installed as
 * bt_gatt_notify_params.func by the recovered bt_nus_send
 * (FUN_0004f518 / gatt_notify_config_change).  Bound onto the emitted
 * service in recon/application/app/src/g1_bt_nus_service.c; `+ 1` is the
 * Thumb bit a linker-script assignment does not add by itself. */
PROVIDE(rodata_4f4f1 = g1_nus_on_sent + 1);
PROVIDE(rodata_50100 = 0x00050100);
PROVIDE(rodata_57525 = 0x00057525);
PROVIDE(rodata_582b4 = 0x000582b4);
PROVIDE(rodata_588b5 = 0x000588b5);
PROVIDE(rodata_5a2d5 = 0x0005a2d5);
PROVIDE(rodata_5a2fd = 0x0005a2fd);
PROVIDE(rodata_5a329 = 0x0005a329);
PROVIDE(rodata_5b4bd = 0x0005b4bd);
PROVIDE(rodata_5e41d = 0x0005e41d);
PROVIDE(rodata_60635 = 0x00060635);
PROVIDE(rodata_72ab1 = 0x00072ab1);
PROVIDE(rodata_72dad = 0x00072dad);
PROVIDE(rodata_73729 = 0x00073729);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of z_timer_expiration_handler; unrelocated in our build.
 * Evidence: 24 leading bytes byte-identical to our z_timer_expiration_handler; z_add_timeout handler arg in z_impl_k_timer_start. */
PROVIDE(rodata_75005 = z_timer_expiration_handler | 1);
PROVIDE(rodata_76b91 = 0x00076b91);
PROVIDE(rodata_79274 = 0x00079274);
PROVIDE(rodata_7c00d = local_esbs_ctrl_ipc_service_recv | 1); /* iteration 8 rebind */
PROVIDE(rodata_7c26b = 0x0007c26b);
/* rodata_7c38b / rodata_7c39d: see the iteration-40 note above. */
PROVIDE(rodata_7d4cb = projector_clear_canvas | 1); /* iteration 14 rebind */
PROVIDE(rodata_7d4d7 = projector_flush_canvas | 1); /* iteration 14 rebind */
PROVIDE(rodata_7d86d = 0x0007d86d);
PROVIDE(rodata_7eb11 = 0x0007eb11);
PROVIDE(rodata_7eb1d = 0x0007eb1d);
PROVIDE(rodata_7eb37 = 0x0007eb37);
PROVIDE(rodata_7ed27 = 0x0007ed27);
PROVIDE(rodata_7f071 = 0x0007f071);
PROVIDE(rodata_7f5c5 = 0x0007f5c5);
PROVIDE(rodata_80e81 = 0x00080e81);
PROVIDE(rodata_81035 = 0x00081035);
PROVIDE(rodata_810ab = 0x000810ab);
PROVIDE(rodata_813d1 = 0x000813d1);
PROVIDE(rodata_81699 = 0x00081699);
PROVIDE(rodata_816af = 0x000816af);
PROVIDE(rodata_81b83 = 0x00081b83);
PROVIDE(rodata_825bb = 0x000825bb);
PROVIDE(rodata_825fb = 0x000825fb);
PROVIDE(rodata_82603 = 0x00082603);
PROVIDE(rodata_82a67 = 0x00082a67);
PROVIDE(rodata_82cb3 = 0x00082cb3);
PROVIDE(rodata_837a9 = 0x000837a9);
PROVIDE(rodata_838cb = 0x000838cb);
PROVIDE(rodata_84c57 = 0x00084c57);
PROVIDE(rodata_859a3 = 0x000859a3);
PROVIDE(rodata_859b1 = 0x000859b1);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of zcbor_uint32_decode; unrelocated in our build.
 * Evidence: 32 leading bytes byte-identical modulo b.w relocs; zcbor decoder fn-ptr table in img_mgmt_upload. */
PROVIDE(rodata_85f8d = zcbor_uint32_decode | 1);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of zcbor_size_decode; unrelocated in our build.
 * Evidence: 32 leading bytes byte-identical modulo b.w relocs; zcbor decoder fn-ptr table in img_mgmt_upload. */
PROVIDE(rodata_85f93 = zcbor_size_decode | 1);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of zcbor_bstr_decode; unrelocated in our build.
 * Evidence: 32 leading bytes byte-identical modulo b.w relocs; zcbor decoder fn-ptr table in img_mgmt_upload. */
PROVIDE(rodata_85f97 = zcbor_bstr_decode | 1);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of z_thread_timeout; unrelocated in our build.
 * Evidence: 8-byte fn byte-identical modulo the b.w reloc, and the function immediately after it (z_unpend_all) is byte-identical in both images; z_add_timeout handler arg in z_impl_k_thread_create/pend_locked/z_init_static_threads. */
PROVIDE(rodata_86661 = z_thread_timeout | 1);
/* CODE-POINTER REBIND (systematic sweep): odd (Thumb) flash pin was the
 * original-image address of __sread; unrelocated in our build.
 * Evidence: 10 leading bytes byte-identical modulo the bl reloc + app_toolchain_exact_matches.json newlib lib_a-stdio.o .text.__sread archive match at 0x86f34; FILE-op fn ptr in newlib_stdio_init_stream. */
PROVIDE(rodata_86f35 = __sread | 1);
PROVIDE(rodata_86f57 = 0x00086f57);
PROVIDE(rodata_86fb7 = 0x00086fb7);
PROVIDE(rodata_877ed = 0x000877ed);
PROVIDE(rodata_87b30 = 0x00087b30);
/* DATA-POINTER REBIND (iteration 5) — `struct device` instances.
 * These four pins were the ORIGINAL-image addresses of Zephyr device objects.
 * Our relocated build places its own device objects in the `device_area`
 * iterable section (`__device_dts_ord_<N>`), so the original addresses now hold
 * unrelated rodata and every `dev->config/api/data` walk read garbage.
 * Identification is by the device NAME STRING stored in the original object
 * (word0 -> C string), matched against the same name in our linked ELF:
 *   0x87b48 "gpio@842800"     -> DT gpio1        ord 22  @0x80068
 *   0x87b60 "gpio@842500"     -> DT gpio0        ord 12  @0x80080
 *   0x87b90 "crypto@50844000" -> DT cryptocell   ord 86  @0x800b0
 *   0x87cc8 "watchdog"        -> npm1300 wdt     ord 148 @0x801e8
 * (ordinals re-verified against THIS build's devicetree_generated.h + nm). */
PROVIDE(g_gpio1_dev = __device_dts_ord_22);
PROVIDE(g_gpio0_dev = __device_dts_ord_12);
PROVIDE(entropy_dev = __device_dts_ord_86);
PROVIDE(rodata_87bc0 = 0x00087bc0);
PROVIDE(rodata_87bd8 = 0x00087bd8);
/* DATA-POINTER REBIND (iteration 5 sweep, 2nd pass) — `struct device`
 * "mx25r6435f@0" (external QSPI NOR; original 0x87bf0, name string 0xf5b8e).
 * z_device_is_ready()/flash-API dispatch in ext_flash_api_init and
 * flash_settings_read.  With the absolute pin, flash_settings_read's readiness
 * check failed and it entered its 10 x k_sleep(3277 ms) retry loop, which is
 * what stalled the boot after settings_subsys_init.  ord 160 in this build. */
PROVIDE(rodata_87bf0 = __device_dts_ord_160);
PROVIDE(rodata_87bf8 = 0x00087bf8);
/* DATA-POINTER REBIND (iteration 5 sweep) — `struct device` "ipc0"
 * (original 0x87c08, name string 0x9f71c = "ipc0"); passed as the instance
 * argument of ipc_service_open_instance()/serialization_register_endpoint()
 * in serialization_init (executed on this boot, previously reading garbage
 * at 0xC016CBE4).  Our build: DT ipc0 = __device_dts_ord_29.
 *
 * REVERTED (iteration 5, measured): the rebind is CORRECT but it REGRESSES the
 * boot, so per the no-regression gate it is left pinned for now.  With
 * __device_dts_ord_29 the real OpenAMP/rpmsg instance is opened, main() then
 * blocks waiting for the endpoint bind (serialization_register_endpoint slips
 * 4,668,377 -> 4,705,055) and the app core drops into `idle`/`arch_cpu_idle`
 * forever: it never reaches register_ipc_service_context, spi_master_install_ops,
 * button_init or settings_subsys_init (521 unique fns / 4,738,510 instr vs
 * 557 / 5,061,646 with the pin left absolute).  The blocker is the net-core
 * rpmsg handshake, not this pin.  Re-apply once the CPUNET rpmsg/IPC bring-up
 * completes the bind.  Evidence: recon/emulator/reports/our_boot_bringup.md
 * §Iteration 5.
 *
 * RE-APPLIED then REVERTED AGAIN (iteration 6, measured).  The CPUNET side of
 * the handshake was fixed this iteration (its own "ipc0" device pin
 * rodata_103bfac + the dropped-argument defect in FUN_0102d558), and the net
 * core now completes open_instance -> ipc_static_vrings_init -> ipc_rpmsg_init
 * -> rpmsg_create_ept -> rpmsg_send_ns_message -> mbox_nrf_send, and the app
 * receives it: mbox_callback_process -> virtqueue_notification ->
 * rpmsg_virtio_rx_callback -> rpmsg_virtio_ns_callback -> ns_bind_cb with the
 * announced name "ipc0".  The bind STILL does not complete, and the reason is
 * a THIRD unrelocated pin: the app's own `struct ipc_ept_cfg` at 0x00089748,
 * whose cfg->name reads back 0x0004bc05 (a code address inside open()) instead
 * of a string, so ns_bind_cb's get_ept_slot_with_name() never matches and
 * bound_cb() is never called.  With this pin applied main() therefore still
 * blocks in serialization_init's k_sem_take and the app never reaches
 * button_init / settings_subsys_init / flash_settings_read
 * (4,720,087 instr / 525 unique fns, vs 5,042,715 / 612 with the pin left
 * absolute).  Per the no-regression gate it is reverted again.  RE-APPLY
 * TOGETHER WITH emitting a relocated ipc_ept_cfg for 0x00089748 (contents
 * embed a name pointer + callback pointers, so it must be emitted like the
 * gpio_dt_spec tables of iteration 5 §2, not merely rebound).
 * Evidence: recon/emulator/reports/our_boot_bringup.md §Iteration 6.
 *
 * CORRECTION + RE-APPLIED (iteration 7).  Iteration 6's diagnosis of the
 * *third* pin was wrong in its address: 0x00089748 is NOT an ipc_ept_cfg in
 * the shipped image at all (those bytes are LC3 float tables), it was simply
 * the stale r2 our codegen happened to leave at the call.  The real cause was
 * a DROPPED ARGUMENT: `serialization_register_endpoint` (0x4cbec) tail-calls
 * backend->register_endpoint(instance, &ept->token, cfg) with r2 untouched
 * since entry (image bytes 0x4cc34..0x4cc40), but Ghidra's
 * "treating indirect jump as call" heuristic emitted a 2-argument call, so
 * `cfg` was never passed.  The real cfg is `g_serialization_ipc_ept_ctx`
 * (0x200023dc), a .data `struct ipc_ept_cfg` that our build neither relocated
 * nor initialised.  Both are fixed in iteration 7 (see the rebind comments on
 * g_serialization_ipc_ept_ctx / g_serialization_ipc_mutex below), so this pin
 * is re-applied.  Evidence: our_boot_bringup.md §Iteration 7 Step A. */
PROVIDE(rodata_87c08 = __device_dts_ord_29);
/* DATA-POINTER REBIND (iteration 11) — `struct device` "adc@e000" (the
 * nRF5340 SAADC; original 0x87c20).  Decoded from the shipped image:
 *   0x87c20 name  = 0xf5648 -> "adc@e000"
 *   0x87c24 config= 0
 *   0x87c28 api   = 0x8b58c -> { channel_setup 0x5f655, read 0x5f761,
 *                                read_async 0, ref_internal 0x258 = 600 mV }
 *   0x87c2c state = 0x200035b4
 * `adc_nfc_run` (0x24c14) loads dev->api (+8) and calls api->read (+4) with an
 * adc_sequence; left absolute it read unrelated rodata and `blx r3` branched
 * to 0 -> USAGE FAULT "Illegal use of the EPSR" at adc_nfc_run+0x2a (this was
 * iteration 11's first divergence at 0.2847 s).  ord 88 =
 * DT_N_S_soc_S_peripheral_50000000_S_adc_e000_ORD in this build. */
PROVIDE(rodata_87c20 = __device_dts_ord_88);
/* DATA-POINTER REBIND (iteration 5 sweep) — `struct device` "regulators"
 * (nPM1300 regulators node; original 0x87cb0, name string 0xf6160).
 * main() does z_device_is_ready() + api dispatch on it.  ord 149. */
PROVIDE(rodata_87cb0 = __device_dts_ord_149);
PROVIDE(g_watchdog_device = __device_dts_ord_148);   /* "watchdog" (npm1300) — see note above */
/* DATA-POINTER REBIND (iteration 9) — the two nPM1300 regulator `struct
 * device` instances used by the display power sequence.  Identified by the
 * name string stored in word0 of the original object:
 *   0x87cf8 name 0x000f614f "LDO1"  -> DT .../pmic@6b/regulators/LDO1  ord 152
 *   0x87d10 name 0x000f6154 "BUCK2" -> DT .../pmic@6b/regulators/BUCK2 ord 151
 * power_for_panel/power_down_panel/enable_ship_mode dereference
 * dev->config->mfd (config + 0x1c) and call the nPM1300 register API on it.
 * Verified in THIS build: config(ord 152) + 0x1c == config(ord 151) + 0x1c ==
 * __device_dts_ord_145, the pmic@6b mfd parent, exactly as the shipped image's
 * 0x8b8b8 + 0x1c == 0x8b8f8 + 0x1c == 0x87c80.  Left absolute, dev->config
 * read unrelated rodata and dev_ctrl_write1 called through a NULL API. */
PROVIDE(rodata_87cf8 = __device_dts_ord_152);
PROVIDE(rodata_87d10 = __device_dts_ord_151);
/* Same class, same block: 0x87ce0 name 0x000f614a "LDO2" -> ord 153.
 * power_for_imu_and_mic() dereferences it exactly like power_for_panel()
 * does LDO1, and was the next fault once LDO1/BUCK2 were relocated. */
PROVIDE(rodata_87ce0 = __device_dts_ord_153);
PROVIDE(rodata_87d40 = 0x00087d40);
/* DATA-POINTER REBIND (iteration 5 sweep) — `struct device` "lsm6dso@6b"
 * (original 0x87d58, name string 0xf649d); main() -> lsm6dso_init_chip(dev).
 * ord 155. */
PROVIDE(rodata_87d58 = __device_dts_ord_155);
/* DATA-POINTER REBIND (iteration 5 sweep) — `struct device` "charger"
 * (nPM1300 charger/fuel-gauge node; original 0x87d70, name string 0xf64b0);
 * main()/low_speed_peripheral_dispatch_thread -> fuel_gauge_update(dev,0).
 * ord 146. */
PROVIDE(rodata_87d70 = __device_dts_ord_146);
PROVIDE(rodata_87fc8 = 0x00087fc8);
PROVIDE(rodata_87fec = 0x00087fec);
PROVIDE(rodata_88058 = 0x00088058);
PROVIDE(rodata_88070 = 0x00088070);
PROVIDE(rodata_880d8 = 0x000880d8);
PROVIDE(rodata_880e0 = 0x000880e0);
PROVIDE(rodata_880e8 = 0x000880e8);
PROVIDE(rodata_880f0 = 0x000880f0);
PROVIDE(rodata_880f8 = 0x000880f8);
PROVIDE(rodata_88100 = 0x00088100);
PROVIDE(log_module_bt_conn = 0x00088108);
PROVIDE(rodata_88120 = 0x00088120);
PROVIDE(rodata_88128 = 0x00088128);
PROVIDE(rodata_88130 = 0x00088130);
PROVIDE(rodata_88138 = 0x00088138);
PROVIDE(rodata_88148 = 0x00088148);
PROVIDE(rodata_88150 = 0x00088150);
PROVIDE(rodata_88158 = 0x00088158);
PROVIDE(rodata_88160 = 0x00088160);
PROVIDE(rodata_88178 = 0x00088178);
PROVIDE(rodata_88180 = 0x00088180);
PROVIDE(rodata_88188 = 0x00088188);
PROVIDE(rodata_881a0 = 0x000881a0);
PROVIDE(rodata_881a8 = 0x000881a8);
PROVIDE(rodata_881b0 = 0x000881b0);
PROVIDE(rodata_881b8 = 0x000881b8);
PROVIDE(rodata_881c0 = 0x000881c0);
PROVIDE(rodata_881d8 = 0x000881d8);
PROVIDE(rodata_881e0 = 0x000881e0);
PROVIDE(rodata_881f8 = 0x000881f8);
PROVIDE(rodata_88208 = 0x00088208);
PROVIDE(rodata_88220 = 0x00088220);
PROVIDE(rodata_88228 = 0x00088228);
PROVIDE(rodata_88250 = 0x00088250);
PROVIDE(rodata_88258 = 0x00088258);
PROVIDE(rodata_88268 = 0x00088268);
PROVIDE(rodata_88270 = 0x00088270);
PROVIDE(rodata_88278 = 0x00088278);
PROVIDE(rodata_88288 = 0x00088288);
PROVIDE(rodata_88290 = 0x00088290);
/* Iter-2 rebind (boot bring-up): these two pins are NOT generic rodata — they
 * are the Zephyr log-backend iterable-section boundaries, mislabeled by the
 * symbolizer as `rodata_882a0` / `__settings_handler_static_list_start` because
 * in the ORIGINAL image the log-backend list ended (0x882b0) exactly where the
 * settings-handler list began (adjacent sections). In the relocated build those
 * sections MOVE, so the 0x882a0/0x882b0 absolute pins point into foreign rodata
 * and log_msg_process walked garbage -> QSPI-XIP abort. Bind to the linker's own
 * boundary symbols instead. In this build _log_backend_list_end (0x80650) ==
 * _settings_handler_static_list_start (0x80650), so this single value is also
 * correct for the settings functions that read `__settings_handler_static_list_start`
 * as their list start. (The settings-list END is a separate hardcoded 0x88328
 * literal in the settings .c sources — a canonical-recon defect, not a pin.) */
PROVIDE(rodata_882a0 = _log_backend_list_start);
PROVIDE(__settings_handler_static_list_start = _log_backend_list_end);
/* DATA-TABLE RE-EMISSION (iteration 5) — `struct gpio_dt_spec` tables.
 * 0x88340 is a 9-entry gpio_dt_spec[] read by button_init; its entries EMBED an
 * absolute `struct device *` (0x87b60 = gpio0), so the pin cannot be rebound to
 * any linker symbol — the table itself has to be emitted by the build so both
 * the table address AND the device pointers inside it get relocated.  It is now
 * defined in the wiring TU recon/symbolized/app/button_init.c; this PROVIDE
 * keeps the recovered name bound to that definition for any other consumer.
 * Original bytes (app_update.bin @0x88340, 9 x 8B):
 *   port=0x87b60(gpio0) pin = 26,25,28,27,24,19,21,30,23  dt_flags = 0 */
PROVIDE(rodata_88340 = g1_button_gpio_specs);
PROVIDE(rodata_88388 = 0x00088388);
/* Iteration 22 — the `struct bt_le_adv_param` bt_start copies into its stack
 * local before calling bt_le_adv_start.  The identity pin named an
 * ORIGINAL-image address that holds ASCII debug-path bytes in this build, so
 * `options` read 0x682e7365 and bt_le_adv_start returned -EINVAL.  Emitted
 * byte-exactly by recon/application/app/src/g1_bt_adv_objects.c. */
PROVIDE(rodata_8839c = g1_bt_le_adv_param);
/* Iteration 16 Step A — the SPIM `p_reg` defect that kept every panel transfer
 * from ever reaching `spim_a`.
 *
 * `spi_master_init` (FUN_00026418 @ 0x26418) builds the `nrfx_spim_t` for
 * mode 4 by COPYING TWO WORDS OF FLASH DATA:
 *   mode4.base = *(uint32_t *)0x883b0 ;  mode4.tag = *(uint32_t *)0x883b4
 * and the shipped image holds exactly the nrfx instance descriptor there:
 *   app_update.bin @0x883b0 = 00 a0 00 50   -> 0x5000a000  (NRF_SPIM, `spim_a`)
 *   app_update.bin @0x883b4 = 01 00 00 00   -> drv_inst_idx 1
 * These were still IDENTITY pins, so our build read its OWN unrelated rodata
 * at 0x883b0 (measured in g1-i15e-app: `78 b9 08 00 d0 b9 08 00` = 0x0008b978 /
 * 0x0008b9d0).  `p_reg` therefore pointed into FLASH, `nrfx_spim_xfer` wrote
 * TASKS_START into read-only memory and then polled EVENTS_END at
 * 0x0008b978+0x118 forever -- the 187,696,414-instruction spin of iteration 15
 * section 15.5, and the reason `sysbus LogPeripheralAccess` saw ZERO register
 * accesses on both `spim_a` and `spim_b`.
 *
 * recon/data/rodata_0x88340.c is the byte-verified owner of this block (it is
 * already compiled through app_verified_data_sources.cmake), so the three pins
 * are bound at their original relative offsets instead of being emitted again.
 *   0x883b0 = rodata_0x88340 + 0x70,  0x883b4 = +0x74,  0x883b8 = +0x78 */
PROVIDE(rodata_883b0 = rodata_0x88340 + 0x70);
PROVIDE(rodata_883b4 = rodata_0x88340 + 0x74);
PROVIDE(rodata_883b8 = rodata_0x88340 + 0x78);
PROVIDE(rodata_883c8 = 0x000883c8);
PROVIDE(rodata_883ec = 0x000883ec);
PROVIDE(rodata_88410 = 0x00088410);
PROVIDE(rodata_88434 = 0x00088434);
PROVIDE(rodata_8843e = 0x0008843e);
PROVIDE(rodata_88480 = 0x00088480);
PROVIDE(lc3_attdet_nbytes_ranges = 0x000884d0);
PROVIDE(lc3_bwdet_thresholds = 0x000884f0);
PROVIDE(lc3_tns_subdivision_table = 0x0008853c);
/* RODATA REBIND + EMISSION (iteration 38) — the battery state-of-charge EKF
 * process-noise matrix Q, 4x4 binary32 diag(1e-6, 1e-6, 1e-8, 2e-4), 64 B
 * (extent closed by the next pin, rodata_885b0).  `batt_soc_curve_estimate`
 * (0xe2b4) copies the whole struct out of it into
 * `battery_soc_curve_model_init` (0xe53c), which bakes it into the estimator
 * workspace.  Left absolute it read our OWN rodata at 0x88570 — an unrelated
 * pointer table that reads as ~1e-40 floats — so Q was effectively zero, the
 * estimator never moved and `device_info[0xfc0]` (battery percent) stayed
 * below the `> 0x1d` gate at `handle_box_placement_event+0xbc` (0x255ec).
 * Measured consequence: `box_placement_animation_step` never ran, so one of
 * the three per-tick `read_nfc_adc_scaled` call sites was missing (SAADC 30
 * conversion cycles per 20 s against the oracle's 45 — 15 bursts of 2 instead
 * of 15 bursts of 3, fingerprinted by the distinct `SAADC.RESULT.PTR` stack
 * addresses) and the ST25DV NDEF/WLC record write never happened.  Storage:
 * recon/data/rodata_0x88570.c (byte-verified by tools/verify_data.py). */
PROVIDE(rodata_88570 = rodata_0x88570);
PROVIDE(rodata_885b0 = 0x000885b0);
PROVIDE(rodata_885cc = 0x000885cc);
PROVIDE(rodata_88697 = rodata_88694 + 0x3);
PROVIDE(rodata_887b7 = 0x000887b7);
PROVIDE(rodata_887c8 = rodata_887b7 + 0x11);
PROVIDE(rodata_887d9 = rodata_887b7 + 0x22);
PROVIDE(rodata_887ea = rodata_887b7 + 0x33);
PROVIDE(rodata_88848 = rodata_887b7 + 0x91);
PROVIDE(rodata_88858 = rodata_887b7 + 0xa1);
PROVIDE(rodata_88868 = rodata_887b7 + 0xb1);
PROVIDE(rodata_88878 = rodata_887b7 + 0xc1);
PROVIDE(rodata_88888 = rodata_887b7 + 0xd1);
PROVIDE(rodata_888a8 = rodata_887b7 + 0xf1);
PROVIDE(rodata_888e0 = rodata_887b7 + 0x129);
PROVIDE(rodata_88908 = rodata_887b7 + 0x151);
/* Same class as rodata_88340: single `struct gpio_dt_spec` objects whose first
 * word is the absolute gpio1 device (0x87b48).  Original bytes:
 *   0x889d0 = { gpio1, pin  9, dt_flags 0x0011 }   (button/NFC-field line)
 *   0x889e0 = { gpio1, pin 10, dt_flags 0x0011 }
 * (0x0011 = GPIO_ACTIVE_LOW | GPIO_PULL_UP).  Re-emitted in button_init.c. */
PROVIDE(rodata_889d0 = g1_gpio1_pin9_spec);
PROVIDE(rodata_889e0 = g1_gpio1_pin10_spec);
/* iteration 14: same class -- { gpio0, pin 23, dt_flags 0 }. */
PROVIDE(rodata_889d8 = g1_gpio0_pin23_spec);
/* iteration 13: same class as 0x889d0/0x889e0 -- the descriptor itself
 * embeds an absolute `struct device *`, so it must be emitted by the build. */
PROVIDE(rodata_889e8 = g1_gpio0_pin30_spec);
PROVIDE(rodata_889f0 = g1_gpio0_pin21_spec);
PROVIDE(rodata_889f8 = g1_gpio0_pin24_spec);
PROVIDE(rodata_88a00 = 0x00088a00);
PROVIDE(rodata_88a0c = 0x00088a0c);
/* RODATA REBIND + EMISSION (iteration 38) — the SAADC `struct adc_channel_cfg`
 * `adc_nfc_init` (0x24b98) passes to `adc_channel_setup`.  Left absolute it
 * read unrelated rebuilt-image rodata, so channel 3 was never configured and
 * every `adc_read` failed with "<err> adc_nrfx_saadc: Channel 3 not configured"
 * (our `saadc` stream stopped at the CH0..CH2 deselect loop: 95 register
 * accesses against the oracle's 998).  Shipped bytes at 0x88a2a are
 * `00 04 00 00 03 04 00` = { ADC_GAIN_1_6, ADC_REF_INTERNAL,
 * ADC_ACQ_TIME_DEFAULT, channel_id 3, single-ended, AIN3, disabled }, which is
 * exactly what §4.5 of display_sensor_parity.md decodes from the shipped
 * CH3.PSELP/PSELN/CONFIG writes.  Storage:
 * recon/application/app/src/g1_adc_channel_cfg.c. */
PROVIDE(rodata_88a2a = g1_adc_nfc_channel_cfg);
/* RODATA REBIND + EMISSION (iteration 10) — the ST25DV transport ops
 * vtable.  0x88a38..0x88a44 is three ORIGINAL-image Thumb function pointers
 * (0x25789, 0x256dd, 0x7c86d); both the table address and its contents have
 * to relocate, so the build emits it.  Storage:
 * recon/application/app/src/g1_st25dv_ops_table.c. */
PROVIDE(rodata_88a38 = g1_st25dv_ops_table);
/* P4 iteration 40: the two NFC-Forum WLC NDEF record TYPE descriptors
 * (original .data 0x200023bc / 0x200023c4).  Their contents are
 * original-image flash pointers to the "WLCSTAI"/"WLCCAP" type-name strings,
 * which the arena .data restore drops and which nothing else emits, so like
 * the ops table above the objects are emitted and the pins bound onto them:
 * recon/application/app/src/g1_wlc_ndef_type_records.c. */
PROVIDE(g_wlcstai_record_type = g1_wlcstai_ndef_type);
PROVIDE(g_wlccap_record_type = g1_wlccap_ndef_type);
PROVIDE(rodata_88a44 = 0x00088a44);
/* RODATA EMISSION (iteration 39) — the battery state-of-charge model CURVE
 * TABLE, 5632 B (0x1600).  There was NO pin for it at all before this
 * iteration: the ledger jumped 0x88a44 -> 0x8a050, and 0x8a050 - 0x88a50 is
 * exactly the 0x1600 that `battery_soc_curve_model_init` (0xe53c) memcpy's
 * into the estimator workspace at +0x144, so the extent is closed twice over.
 * The address reaches the estimator as WORD 3 OF A STACK RECORD:
 * `fuel_gauge_sample_init_timestamp` (0x2ea28) does
 * `ldr r3,[pc,#0x40]` (literal @0x2ea70 = 0x00088a50) / `str r3,[sp,#0x14]`,
 * and our reconstruction declared that record with only three words, so
 * `batt_soc_curve_estimate` was handed a stale stack value (measured
 * 0x0009d5ba) and memcpy'd 5632 bytes of unrelated .rodata in as the battery
 * curve.  Measured consequence: the EKF covariance went to NaN, the reported
 * battery percent stuck at 0 for the whole run, and the
 * `device_info[0xfc0] > 0x1d` gate at `handle_box_placement_event+0xbc`
 * (0x255ec) never opened -- which is what suppressed BOTH the SAADC's third
 * per-tick conversion call site and the ST25DV NDEF/WLC record write.
 * Storage: recon/data/rodata_0x88a50.c (byte-verified by tools/verify_data.py). */
PROVIDE(rodata_88a50 = rodata_0x88a50);
PROVIDE(rodata_8a050 = 0x0008a050);
PROVIDE(rodata_8a0a8 = 0x0008a0a8);
PROVIDE(rodata_8a208 = 0x0008a208);
/* P4 iteration 36: rodata_8a3e0 -- localized string table 1 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8a4e8 -- localized string table 2 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8a5f0 -- localized string table 3 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8a6f8 -- localized string table 4 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8a800 -- localized string table 5 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8a908 -- localized string table 6 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8aa10 -- localized string table 7 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_8ab18 -- localized string table 8 of 8, 66 RELOCATED pointer entries is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
PROVIDE(rodata_8ac20 = 0x0008ac20);
/* P4 iteration 33: this is the shipped word at 0x8ac28, i.e. element [2] of
 * the already byte-verified recon/data table rodata_0x8ac20 (= 0x14c = 332).
 * The old numeric pin read OUR image at 0x8ac28, which holds 0x2000b448, so
 * get_default_font_glyph_offset's directory scan ran 536,918,600 iterations
 * and the display thread never returned -- the measured iteration-33 stall. */
PROVIDE(g_default_font_glyph_table_count = rodata_0x8ac20 + 8);
/* P4 iteration 35: the SAME argument, for the other three font families.
 * 0x8ac2c/0x8ac30/0x8ac34 are elements [3]/[4]/[5] of that same byte-verified
 * recon/data table rodata_0x8ac20 and hold the glyph counts of font style 3
 * (0x60 = 96), the small clock digits (0x0b = 11) and the large clock digits
 * (0x0b = 11).  0x8ac2c additionally had a 2-BYTE string stub
 * (`rodata_8ac2c[2] = {0x60,0x00}`) in g1_app_string_rodata.c, so the
 * `*(volatile int*)` load in get_font_style3_glyph_offset read two bytes past
 * the object.  Binding all three onto their real owner retires both defects. */
PROVIDE(rodata_8ac2c = rodata_0x8ac20 + 0xc);
PROVIDE(rodata_8ac30 = rodata_0x8ac20 + 0x10);
PROVIDE(rodata_8ac34 = rodata_0x8ac20 + 0x14);
PROVIDE(rodata_8aca0 = 0x0008aca0);
PROVIDE(rodata_8acb4 = 0x0008acb4);
PROVIDE(rodata_8acc4 = 0x0008acc4);
PROVIDE(rodata_8acd8 = 0x0008acd8);
PROVIDE(rodata_8ad08 = 0x0008ad08);
/* P4 iteration 31: &attrs_nus_svc[2], the NUS TX value attribute the
 * recovered bt_nus_send hands to bt_gatt_notify_cb.  Attribute stride is
 * 20 bytes (BUILD_ASSERT in g1_bt_nus_service.c). */
PROVIDE(rodata_8ad40 = attr_g1_nus_svc + 40);
PROVIDE(rodata_8af10 = 0x0008af10);
PROVIDE(rodata_8af4c = 0x0008af4c);
PROVIDE(rodata_8b190 = 0x0008b190);
PROVIDE(rodata_8b264 = 0x0008b264);
PROVIDE(rodata_8b29c = 0x0008b29c);
PROVIDE(rodata_8b2b4 = 0x0008b2b4);
PROVIDE(rodata_8b3dc = 0x0008b3dc);
PROVIDE(rodata_8b508 = 0x0008b508);
PROVIDE(rodata_8b5fc = 0x0008b5fc);
/* Iteration 15: the four nPM1300 charger `linear_range` tables are DATA the
 * recovered npm1300_charger_init dereferences, not addresses it merely
 * compares, so an identity pin to original flash 0x8ba64.. handed it our
 * build's unrelated bytes and layout_select_region returned -EINVAL, which
 * made main skip jdb_panel_init / pt_nfc_eeprom_link_start /
 * notification_system_init (the E4 blocker).  Bind all four onto the one
 * emitted 72-byte block in
 * recon/application/app/src/g1_npm1300_linear_ranges.c, keeping their
 * original relative offsets. */
PROVIDE(rodata_8ba64 = g1_npm1300_linear_ranges + 0x00);
PROVIDE(rodata_8ba7c = g1_npm1300_linear_ranges + 0x18);
PROVIDE(rodata_8ba88 = g1_npm1300_linear_ranges + 0x24);
PROVIDE(rodata_8ba94 = g1_npm1300_linear_ranges + 0x30);
PROVIDE(rodata_8bb90 = 0x0008bb90);
PROVIDE(lc3_bwdet_l_table = 0x0008bbc0);
PROVIDE(lc3_bwdet_bws_table = 0x0008bbe0);
PROVIDE(lc3_energy_n1_table = 0x0008bc60);
PROVIDE(rodata_8bc88 = 0x0008bc88);
PROVIDE(rodata_8bc98 = 0x0008bc98);
PROVIDE(rodata_8c938 = 0x0008c938);
PROVIDE(lc3_sns_dct16_matrix = 0x0008ce4c);
PROVIDE(rodata_8d24c = 0x0008d24c);
PROVIDE(lc3_spec_iq_table = 0x0008d350);
PROVIDE(lc3_spectrum_bits = 0x0008d3d0);
PROVIDE(lc3_spectrum_lookup = 0x0008ed50);
PROVIDE(lc3_tns_coeffs_bits = 0x0008fd50);
PROVIDE(lc3_tns_coeffs_models = 0x0008fe60);
PROVIDE(lc3_tns_coeffs_models_row1 = 0x0008fea4);
PROVIDE(lc3_tns_coeffs_models_row2 = 0x0008fee8);
PROVIDE(lc3_tns_coeffs_models_row3 = 0x0008ff2c);
PROVIDE(lc3_tns_coeffs_models_row4 = 0x0008ff70);
PROVIDE(lc3_tns_coeffs_models_row5 = 0x0008ffb4);
PROVIDE(lc3_tns_coeffs_models_row6 = 0x0008fff8);
PROVIDE(lc3_tns_coeffs_models_row7 = 0x0009003c);
PROVIDE(lc3_tns_order_bits = 0x00090080);
PROVIDE(lc3_sns_mpvq_offsets = 0x00090128);
PROVIDE(lc3_sns_vq_gains = 0x000903e8);
PROVIDE(lc3_sns_hfcb = 0x00090450);
PROVIDE(lc3_sns_lfcb = 0x00090850);
PROVIDE(lc3_band_lim = 0x00090c50);
PROVIDE(lc3_tns_rc_levels = 0x00098540);
PROVIDE(lc3_tns_rc_thresholds = 0x00098564);
PROVIDE(rodata_98684 = 0x00098684);
PROVIDE(rodata_98690 = rodata_98684 + 0xc);
PROVIDE(rodata_9869c = rodata_98684 + 0x18);
PROVIDE(rodata_986a4 = rodata_98684 + 0x20);
PROVIDE(rodata_986ac = rodata_98684 + 0x28);
PROVIDE(rodata_9873c = 0x0009873c);
PROVIDE(rodata_98768 = 0x00098768);
PROVIDE(rodata_98774 = 0x00098774);
PROVIDE(rodata_988a8 = 0x000988a8);
/* rodata_9890c: P4 iteration 33 -- the default-font glyph DIRECTORY, now
 * defined byte-exact in g1_app_font_rodata.c.  The numeric pin read our own
 * image at the original VA and returned unrelated bytes. */
/* rodata_98e3c / rodata_98fbc / rodata_98fe8: P4 iteration 35 -- the glyph
 * DIRECTORIES of the remaining three font families (style 3, 96 entries;
 * small clock digits, 11; large clock digits, 11), now defined byte-exact in
 * g1_app_font_rodata.c exactly as the default font's rodata_9890c was in
 * iteration 33.  gen_app_string_rodata.py had classified all three as STRINGS
 * and emitted 2-byte stubs, so get_font_style3_glyph_offset walked 96 entries
 * of unrelated bytes and returned a bogus glyph descriptor: measured
 * (iteration 34.10) as a 3,354-byte memcpy into the 676-byte glyph buffer and
 * a fortify_chk_fail() kernel oops the first time the dashboard drew the
 * comma of "Mon, Jan 1". */
PROVIDE(rodata_99014 = 0x00099014);
PROVIDE(rodata_99042 = 0x00099042);
PROVIDE(rodata_9905e = 0x0009905e);
PROVIDE(rodata_9907c = 0x0009907c);
PROVIDE(rodata_990cf = 0x000990cf);
PROVIDE(rodata_99329 = 0x00099329);
PROVIDE(rodata_9938c = 0x0009938c);
PROVIDE(rodata_9940b = 0x0009940b);
PROVIDE(rodata_998da = 0x000998da);
PROVIDE(rodata_998e7 = 0x000998e7);
PROVIDE(rodata_998fc = 0x000998fc);
PROVIDE(rodata_99908 = 0x00099908);
PROVIDE(rodata_99969 = 0x00099969);
PROVIDE(rodata_999e4 = 0x000999e4);
PROVIDE(rodata_99a23 = 0x00099a23);
PROVIDE(rodata_99a3e = 0x00099a3e);
PROVIDE(rodata_99a60 = 0x00099a60);
PROVIDE(rodata_99c53 = 0x00099c53);
PROVIDE(rodata_99d17 = 0x00099d17);
PROVIDE(rodata_99e30 = 0x00099e30);
PROVIDE(rodata_99ec7 = 0x00099ec7);
PROVIDE(rodata_99ef2 = rodata_99ec7 + 0x2b);
PROVIDE(rodata_9a1c8 = 0x0009a1c8);
PROVIDE(rodata_9a1cf = 0x0009a1cf);
PROVIDE(rodata_9a1d6 = 0x0009a1d6);
PROVIDE(rodata_9a1dd = 0x0009a1dd);
PROVIDE(rodata_9a1e0 = 0x0009a1e0);
PROVIDE(rodata_9a1ea = 0x0009a1ea);
PROVIDE(rodata_9a71e = 0x0009a71e);
PROVIDE(rodata_9a788 = 0x0009a788);
PROVIDE(rodata_9a854 = 0x0009a854);
PROVIDE(rodata_9a88a = 0x0009a88a);
PROVIDE(rodata_9ac7c = 0x0009ac7c);
PROVIDE(rodata_9adaa = 0x0009adaa);
PROVIDE(rodata_9b257 = 0x0009b257);
PROVIDE(rodata_9b708 = 0x0009b708);
PROVIDE(rodata_9b74b = 0x0009b74b);
PROVIDE(rodata_9bbbf = 0x0009bbbf);
PROVIDE(rodata_9d000 = 0x0009d000);
PROVIDE(rodata_9d69e = 0x0009d69e);
PROVIDE(rodata_9d6ee = 0x0009d6ee);
PROVIDE(rodata_9d70f = 0x0009d70f);
PROVIDE(rodata_9d759 = 0x0009d759);
PROVIDE(rodata_9d768 = 0x0009d768);
PROVIDE(rodata_9d76c = 0x0009d76c);
PROVIDE(rodata_9d775 = 0x0009d775);
PROVIDE(rodata_9d790 = 0x0009d790);
PROVIDE(rodata_9d79d = 0x0009d79d);
PROVIDE(rodata_9d7b8 = 0x0009d7b8);
PROVIDE(rodata_9d7cc = 0x0009d7cc);
PROVIDE(rodata_9d7d4 = 0x0009d7d4);
PROVIDE(rodata_9d7e1 = 0x0009d7e1);
PROVIDE(rodata_9d7e8 = 0x0009d7e8);
PROVIDE(rodata_9d7f7 = 0x0009d7f7);
PROVIDE(rodata_9d81e = 0x0009d81e);
PROVIDE(rodata_9d857 = 0x0009d857);
PROVIDE(rodata_9d88c = 0x0009d88c);
PROVIDE(rodata_9d8b1 = 0x0009d8b1);
PROVIDE(rodata_9d8da = 0x0009d8da);
PROVIDE(rodata_9da61 = 0x0009da61);
PROVIDE(rodata_9dc17 = 0x0009dc17);
PROVIDE(rodata_9dd24 = 0x0009dd24);
PROVIDE(rodata_9dd4b = 0x0009dd4b);
PROVIDE(rodata_9dd6a = 0x0009dd6a);
PROVIDE(rodata_9dd6d = 0x0009dd6d);
PROVIDE(rodata_9dd70 = 0x0009dd70);
PROVIDE(rodata_9dd91 = 0x0009dd91);
PROVIDE(rodata_9ddb9 = 0x0009ddb9);
PROVIDE(rodata_9ddbc = 0x0009ddbc);
PROVIDE(rodata_9ddbf = 0x0009ddbf);
PROVIDE(rodata_9ddc8 = 0x0009ddc8);
PROVIDE(rodata_9ddcb = 0x0009ddcb);
PROVIDE(rodata_9ddd8 = 0x0009ddd8);
PROVIDE(rodata_9dddb = 0x0009dddb);
PROVIDE(rodata_9dde8 = 0x0009dde8);
PROVIDE(rodata_9de32 = 0x0009de32);
PROVIDE(rodata_9de4c = 0x0009de4c);
PROVIDE(rodata_9de5e = 0x0009de5e);
PROVIDE(rodata_9de63 = 0x0009de63);
PROVIDE(rodata_9de6e = 0x0009de6e);
PROVIDE(rodata_9de71 = 0x0009de71);
PROVIDE(rodata_9dfbf = 0x0009dfbf);
PROVIDE(rodata_9e1a8 = 0x0009e1a8);
PROVIDE(rodata_9e1b6 = 0x0009e1b6);
PROVIDE(rodata_9e1de = 0x0009e1de);
PROVIDE(rodata_9e201 = 0x0009e201);
PROVIDE(rodata_9e20e = 0x0009e20e);
PROVIDE(rodata_9e21f = 0x0009e21f);
PROVIDE(rodata_9e230 = 0x0009e230);
PROVIDE(rodata_9e235 = 0x0009e235);
PROVIDE(rodata_9e23c = 0x0009e23c);
PROVIDE(rodata_9e249 = 0x0009e249);
PROVIDE(rodata_9e259 = 0x0009e259);
PROVIDE(rodata_9e266 = 0x0009e266);
PROVIDE(rodata_9e2cb = 0x0009e2cb);
PROVIDE(rodata_9e3e7 = 0x0009e3e7);
PROVIDE(rodata_9e430 = 0x0009e430);
PROVIDE(rodata_9e44d = 0x0009e44d);
PROVIDE(rodata_9e549 = 0x0009e549);
PROVIDE(rodata_9e580 = 0x0009e580);
PROVIDE(rodata_9e5a6 = 0x0009e5a6);
PROVIDE(rodata_9e5c8 = 0x0009e5c8);
PROVIDE(rodata_9e9ea = 0x0009e9ea);
PROVIDE(rodata_9ea0a = 0x0009ea0a);
PROVIDE(rodata_9eba7 = 0x0009eba7);
PROVIDE(rodata_9ebc6 = 0x0009ebc6);
PROVIDE(rodata_9ee54 = 0x0009ee54);
/* iteration 4: format/name strings consumed by register_ipc_service_recv_callback
 * (0x9f512 "%s(): ipc_service_register(%d,%s) %d,SUCCESS\n",
 *  0x9f540 "%s(): ipc_service_register(%d,%s) %d,total must < %d\n",
 *  0x9f6a3 "register_ipc_service_recv_callback"). Same absolute-rodata pin
 * convention as every other reconstructed log site (see iteration 2 §2 for the
 * still-open interior-rodata-pin class). */
PROVIDE(rodata_9fb42 = 0x0009fb42);
PROVIDE(rodata_9fb59 = 0x0009fb59);
PROVIDE(rodata_9fc5d = 0x0009fc5d);
PROVIDE(rodata_9fede = 0x0009fede);
PROVIDE(rodata_9ff05 = 0x0009ff05);
PROVIDE(rodata_9ff92 = 0x0009ff92);
PROVIDE(rodata_a0102 = 0x000a0102);
PROVIDE(rodata_a0210 = 0x000a0210);
PROVIDE(rodata_a0354 = 0x000a0354);
PROVIDE(rodata_a036a = 0x000a036a);
PROVIDE(rodata_a0396 = 0x000a0396);
PROVIDE(rodata_a03b3 = 0x000a03b3);
PROVIDE(rodata_a03d9 = 0x000a03d9);
PROVIDE(rodata_a03f5 = 0x000a03f5);
PROVIDE(rodata_a0434 = 0x000a0434);
PROVIDE(rodata_a044e = 0x000a044e);
PROVIDE(rodata_a0477 = 0x000a0477);
PROVIDE(rodata_a04cb = 0x000a04cb);
PROVIDE(rodata_a050a = 0x000a050a);
PROVIDE(rodata_a052d = 0x000a052d);
PROVIDE(rodata_a0568 = 0x000a0568);
PROVIDE(rodata_a05c2 = 0x000a05c2);
PROVIDE(rodata_a0621 = 0x000a0621);
PROVIDE(rodata_a067b = 0x000a067b);
PROVIDE(rodata_a06d7 = 0x000a06d7);
PROVIDE(rodata_a07eb = 0x000a07eb);
PROVIDE(rodata_a0889 = 0x000a0889);
PROVIDE(rodata_a0932 = 0x000a0932);
PROVIDE(rodata_a0962 = 0x000a0962);
PROVIDE(rodata_a09ac = 0x000a09ac);
PROVIDE(rodata_a09ee = 0x000a09ee);
PROVIDE(rodata_a0a04 = 0x000a0a04);
PROVIDE(rodata_a0a2e = 0x000a0a2e);
PROVIDE(rodata_a0a47 = 0x000a0a47);
PROVIDE(rodata_a0a61 = 0x000a0a61);
PROVIDE(rodata_a0a7b = 0x000a0a7b);
PROVIDE(rodata_a1a43 = 0x000a1a43);
PROVIDE(rodata_a1bbc = 0x000a1bbc);
PROVIDE(rodata_a1c17 = 0x000a1c17);
PROVIDE(rodata_a1ca4 = 0x000a1ca4);
PROVIDE(rodata_a1ce0 = 0x000a1ce0);
PROVIDE(rodata_a1cfc = 0x000a1cfc);
PROVIDE(rodata_a1d06 = 0x000a1d06);
PROVIDE(rodata_a1d31 = 0x000a1d31);
PROVIDE(rodata_a1d59 = 0x000a1d59);
PROVIDE(rodata_a1dbe = 0x000a1dbe);
PROVIDE(rodata_a1df5 = 0x000a1df5);
PROVIDE(rodata_a1e3a = 0x000a1e3a);
PROVIDE(rodata_a1e66 = 0x000a1e66);
PROVIDE(rodata_a1ead = 0x000a1ead);
PROVIDE(rodata_a1edb = 0x000a1edb);
PROVIDE(rodata_a1f1a = 0x000a1f1a);
PROVIDE(rodata_a1f20 = 0x000a1f20);
PROVIDE(rodata_a1f24 = 0x000a1f24);
PROVIDE(rodata_a1f35 = 0x000a1f35);
PROVIDE(rodata_a1f49 = 0x000a1f49);
PROVIDE(rodata_a1f4d = 0x000a1f4d);
PROVIDE(rodata_a1f4e = 0x000a1f4e);
PROVIDE(rodata_a1f7d = 0x000a1f7d);
PROVIDE(rodata_a1fc7 = 0x000a1fc7);
PROVIDE(rodata_a1ff2 = 0x000a1ff2);
PROVIDE(rodata_a201b = 0x000a201b);
PROVIDE(rodata_a2041 = 0x000a2041);
PROVIDE(rodata_a2061 = 0x000a2061);
PROVIDE(rodata_a20c2 = 0x000a20c2);
PROVIDE(rodata_a20e9 = 0x000a20e9);
PROVIDE(rodata_a211e = 0x000a211e);
PROVIDE(rodata_a2184 = 0x000a2184);
PROVIDE(rodata_a21c4 = 0x000a21c4);
PROVIDE(rodata_a21f9 = 0x000a21f9);
PROVIDE(rodata_a2227 = 0x000a2227);
PROVIDE(rodata_a22b8 = 0x000a22b8);
PROVIDE(rodata_a2334 = 0x000a2334);
PROVIDE(rodata_a2364 = 0x000a2364);
PROVIDE(rodata_a2383 = 0x000a2383);
PROVIDE(rodata_a23a0 = 0x000a23a0);
PROVIDE(rodata_a23cd = 0x000a23cd);
PROVIDE(rodata_a23d0 = 0x000a23d0);
PROVIDE(rodata_a23e8 = 0x000a23e8);
PROVIDE(rodata_a23ff = 0x000a23ff);
PROVIDE(rodata_a2416 = 0x000a2416);
PROVIDE(rodata_a243a = 0x000a243a);
PROVIDE(rodata_a245b = 0x000a245b);
PROVIDE(rodata_a24dc = 0x000a24dc);
PROVIDE(rodata_a24e0 = 0x000a24e0);
PROVIDE(rodata_a24e4 = 0x000a24e4);
PROVIDE(rodata_a2597 = 0x000a2597);
PROVIDE(rodata_a25b9 = 0x000a25b9);
PROVIDE(rodata_a25d9 = 0x000a25d9);
PROVIDE(rodata_a2733 = 0x000a2733);
PROVIDE(rodata_a2768 = 0x000a2768);
PROVIDE(rodata_a2795 = 0x000a2795);
PROVIDE(rodata_a2831 = 0x000a2831);
PROVIDE(rodata_a28d4 = 0x000a28d4);
PROVIDE(rodata_a291d = 0x000a291d);
PROVIDE(rodata_a294a = 0x000a294a);
PROVIDE(rodata_a2a21 = 0x000a2a21);
PROVIDE(rodata_a2a32 = 0x000a2a32);
PROVIDE(rodata_a2ad4 = 0x000a2ad4);
PROVIDE(rodata_a2ba7 = 0x000a2ba7);
PROVIDE(rodata_a2c70 = 0x000a2c70);
PROVIDE(rodata_a2ce2 = 0x000a2ce2);
PROVIDE(rodata_a2cfc = 0x000a2cfc);
PROVIDE(rodata_a2d5a = 0x000a2d5a);
PROVIDE(rodata_a2de3 = 0x000a2de3);
PROVIDE(rodata_a2e5b = 0x000a2e5b);
PROVIDE(rodata_a2e7c = 0x000a2e7c);
PROVIDE(rodata_a2f08 = 0x000a2f08);
PROVIDE(rodata_a2f7e = 0x000a2f7e);
PROVIDE(rodata_a2f9c = 0x000a2f9c);
PROVIDE(rodata_a3071 = 0x000a3071);
PROVIDE(rodata_a30e5 = 0x000a30e5);
PROVIDE(rodata_a3104 = 0x000a3104);
PROVIDE(rodata_a318d = 0x000a318d);
PROVIDE(rodata_a3201 = 0x000a3201);
PROVIDE(rodata_a3215 = 0x000a3215);
PROVIDE(rodata_a3244 = 0x000a3244);
PROVIDE(rodata_a32df = 0x000a32df);
PROVIDE(rodata_a32ef = 0x000a32ef);
PROVIDE(rodata_a3305 = 0x000a3305);
PROVIDE(rodata_a3311 = 0x000a3311);
PROVIDE(rodata_a3325 = 0x000a3325);
PROVIDE(rodata_a339b = 0x000a339b);
PROVIDE(rodata_a33aa = 0x000a33aa);
PROVIDE(rodata_a33bf = 0x000a33bf);
PROVIDE(rodata_a33de = 0x000a33de);
PROVIDE(rodata_a3456 = 0x000a3456);
PROVIDE(rodata_a3468 = 0x000a3468);
PROVIDE(rodata_a3480 = 0x000a3480);
PROVIDE(rodata_a34a2 = 0x000a34a2);
PROVIDE(rodata_a35cd = 0x000a35cd);
PROVIDE(rodata_a35df = 0x000a35df);
PROVIDE(rodata_a35f7 = 0x000a35f7);
PROVIDE(rodata_a3619 = 0x000a3619);
PROVIDE(rodata_a3758 = 0x000a3758);
PROVIDE(rodata_a37f6 = 0x000a37f6);
PROVIDE(rodata_a383d = 0x000a383d);
PROVIDE(rodata_a3886 = 0x000a3886);
PROVIDE(rodata_a38be = 0x000a38be);
PROVIDE(rodata_a38dd = 0x000a38dd);
PROVIDE(rodata_a38f9 = 0x000a38f9);
PROVIDE(rodata_a3930 = 0x000a3930);
PROVIDE(rodata_a394b = 0x000a394b);
PROVIDE(rodata_a3967 = 0x000a3967);
PROVIDE(rodata_a3982 = 0x000a3982);
PROVIDE(rodata_a39a0 = 0x000a39a0);
PROVIDE(rodata_a39bb = 0x000a39bb);
PROVIDE(rodata_a3b5a = 0x000a3b5a);
PROVIDE(rodata_a3b8e = 0x000a3b8e);
PROVIDE(rodata_a40ec = 0x000a40ec);
PROVIDE(rodata_a420e = 0x000a420e);
PROVIDE(rodata_a4233 = 0x000a4233);
PROVIDE(rodata_a4253 = 0x000a4253);
PROVIDE(rodata_a427e = 0x000a427e);
PROVIDE(rodata_a48fa = 0x000a48fa);
PROVIDE(rodata_a49ed = 0x000a49ed);
PROVIDE(rodata_a64ed = 0x000a64ed);
PROVIDE(rodata_a6589 = 0x000a6589);
PROVIDE(rodata_a71cd = 0x000a71cd);
PROVIDE(rodata_a776c = 0x000a776c);
PROVIDE(rodata_a7780 = 0x000a7780);
PROVIDE(rodata_a779f = 0x000a779f);
PROVIDE(rodata_a77b5 = 0x000a77b5);
PROVIDE(rodata_a77cc = 0x000a77cc);
PROVIDE(rodata_a780d = 0x000a780d);
PROVIDE(rodata_a7882 = 0x000a7882);
PROVIDE(rodata_a7993 = 0x000a7993);
PROVIDE(rodata_a79eb = 0x000a79eb);
PROVIDE(rodata_a7c2d = 0x000a7c2d);
PROVIDE(rodata_a7c4a = 0x000a7c4a);
PROVIDE(rodata_a7c9c = 0x000a7c9c);
PROVIDE(rodata_a7cb6 = 0x000a7cb6);
PROVIDE(rodata_a7cd6 = 0x000a7cd6);
PROVIDE(rodata_a7cf4 = 0x000a7cf4);
PROVIDE(rodata_a7dc5 = 0x000a7dc5);
PROVIDE(rodata_a7e3d = 0x000a7e3d);
PROVIDE(rodata_a7e85 = 0x000a7e85);
PROVIDE(rodata_a7ec3 = 0x000a7ec3);
PROVIDE(rodata_a7fae = 0x000a7fae);
PROVIDE(rodata_a819e = 0x000a819e);
PROVIDE(rodata_a81b7 = 0x000a81b7);
PROVIDE(rodata_a81d0 = 0x000a81d0);
PROVIDE(rodata_a81e6 = 0x000a81e6);
PROVIDE(rodata_a81fa = 0x000a81fa);
PROVIDE(rodata_a823b = 0x000a823b);
PROVIDE(rodata_a8248 = 0x000a8248);
PROVIDE(rodata_a829f = 0x000a829f);
PROVIDE(rodata_a82c4 = 0x000a82c4);
PROVIDE(rodata_a82e2 = 0x000a82e2);
PROVIDE(rodata_a835e = 0x000a835e);
PROVIDE(rodata_a8373 = 0x000a8373);
PROVIDE(rodata_a83ca = 0x000a83ca);
PROVIDE(rodata_a83d1 = 0x000a83d1);
PROVIDE(rodata_a83d8 = 0x000a83d8);
PROVIDE(rodata_a8400 = 0x000a8400);
PROVIDE(rodata_a842e = 0x000a842e);
PROVIDE(rodata_a844e = 0x000a844e);
PROVIDE(rodata_a84a2 = 0x000a84a2);
PROVIDE(rodata_a84c4 = 0x000a84c4);
PROVIDE(rodata_a862c = 0x000a862c);
PROVIDE(rodata_a8638 = 0x000a8638);
PROVIDE(rodata_a864e = 0x000a864e);
PROVIDE(rodata_a866e = 0x000a866e);
PROVIDE(rodata_a869b = 0x000a869b);
PROVIDE(rodata_a870b = 0x000a870b);
PROVIDE(rodata_a88a9 = 0x000a88a9);
PROVIDE(rodata_a88d8 = 0x000a88d8);
PROVIDE(rodata_a8afb = 0x000a8afb);
PROVIDE(rodata_a8b01 = 0x000a8b01);
PROVIDE(rodata_a8b0d = 0x000a8b0d);
PROVIDE(rodata_a8b19 = 0x000a8b19);
PROVIDE(rodata_a8b21 = 0x000a8b21);
PROVIDE(rodata_a8b2b = 0x000a8b2b);
PROVIDE(rodata_a8b2f = 0x000a8b2f);
PROVIDE(rodata_a8b37 = 0x000a8b37);
PROVIDE(rodata_a8b7e = 0x000a8b7e);
PROVIDE(rodata_a8b8a = 0x000a8b8a);
PROVIDE(rodata_a8b96 = 0x000a8b96);
PROVIDE(rodata_a8c37 = 0x000a8c37);
PROVIDE(rodata_a8c57 = 0x000a8c57);
PROVIDE(rodata_a8d52 = 0x000a8d52);
PROVIDE(rodata_a8d5d = 0x000a8d5d);
PROVIDE(rodata_a8da5 = 0x000a8da5);
PROVIDE(rodata_a8dc1 = 0x000a8dc1);
PROVIDE(rodata_a8e98 = 0x000a8e98);
/* P4 iteration 36: rodata_a8ea0 -- the 1-byte empty localized string is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
PROVIDE(rodata_a8ea1 = 0x000a8ea1);
PROVIDE(rodata_a8eb5 = 0x000a8eb5);
PROVIDE(rodata_a8ec6 = 0x000a8ec6);
PROVIDE(rodata_a8edd = 0x000a8edd);
PROVIDE(rodata_a9c18 = 0x000a9c18);
PROVIDE(rodata_a9da3 = 0x000a9da3);
PROVIDE(rodata_a9ee1 = 0x000a9ee1);
PROVIDE(rodata_a9eff = 0x000a9eff);
PROVIDE(rodata_a9f2a = 0x000a9f2a);
PROVIDE(rodata_a9f6f = 0x000a9f6f);
PROVIDE(rodata_a9f93 = 0x000a9f93);
PROVIDE(rodata_a9fcd = 0x000a9fcd);
PROVIDE(rodata_a9fe6 = 0x000a9fe6);
PROVIDE(rodata_a9ff7 = 0x000a9ff7);
PROVIDE(rodata_aa01a = 0x000aa01a);
PROVIDE(rodata_aa02b = 0x000aa02b);
PROVIDE(rodata_aa056 = 0x000aa056);
PROVIDE(rodata_aa070 = 0x000aa070);
PROVIDE(rodata_aa091 = 0x000aa091);
PROVIDE(rodata_aa425 = 0x000aa425);
PROVIDE(rodata_aa4ea = 0x000aa4ea);
PROVIDE(rodata_aa600 = 0x000aa600);
PROVIDE(rodata_aa604 = 0x000aa604);
PROVIDE(rodata_aa608 = 0x000aa608);
PROVIDE(rodata_aa60e = 0x000aa60e);
PROVIDE(rodata_aa661 = 0x000aa661);
PROVIDE(rodata_aa665 = 0x000aa665);
PROVIDE(rodata_aa669 = 0x000aa669);
PROVIDE(rodata_aa66d = 0x000aa66d);
PROVIDE(rodata_aa671 = 0x000aa671);
PROVIDE(rodata_aa675 = 0x000aa675);
PROVIDE(rodata_aa86c = 0x000aa86c);
PROVIDE(rodata_aa891 = 0x000aa891);
PROVIDE(rodata_aa8eb = 0x000aa8eb);
PROVIDE(rodata_aa923 = 0x000aa923);
PROVIDE(rodata_aa96d = 0x000aa96d);
PROVIDE(rodata_aaa58 = 0x000aaa58);
PROVIDE(rodata_aaaac = 0x000aaaac);
PROVIDE(rodata_aab3b = 0x000aab3b);
PROVIDE(rodata_aacc8 = 0x000aacc8);
PROVIDE(rodata_aadb9 = 0x000aadb9);
PROVIDE(rodata_aae0f = 0x000aae0f);
/* P4 iteration 36: rodata_aae20 -- the 66,560-byte display fade/dither MASK ATLAS [0xaae20,0xbb220) is a REAL OBJECT now
 * (recon/application/app/src/g1_app_fade_mask_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
/* P4 iteration 36: rodata_bb220 -- the 3,534-byte localized string POOL [0xbb220,0xbbfee) is a REAL OBJECT now
 * (recon/application/app/src/g1_app_localized_rodata.c).  The numeric
 * pin is deleted deliberately -- a link that failed to retain the object must
 * error out instead of silently reading our own relocated image again. */
PROVIDE(rodata_bc083 = 0x000bc083);
PROVIDE(rodata_bc097 = 0x000bc097);
PROVIDE(rodata_bc181 = rodata_bc097 + 0xea);
PROVIDE(rodata_bc26b = rodata_bc097 + 0x1d4);
PROVIDE(rodata_bc355 = rodata_bc097 + 0x2be);
PROVIDE(rodata_bc43f = rodata_bc097 + 0x3a8);
PROVIDE(rodata_bc529 = rodata_bc097 + 0x492);
PROVIDE(rodata_bc613 = rodata_bc097 + 0x57c);
PROVIDE(rodata_bc6fd = rodata_bc097 + 0x666);
PROVIDE(rodata_bc7ca = rodata_bc097 + 0x733);
PROVIDE(rodata_bc7e0 = rodata_bc097 + 0x749);
PROVIDE(rodata_bc7f1 = rodata_bc097 + 0x75a);
PROVIDE(rodata_bccd3 = rodata_bc097 + 0xc3c);
PROVIDE(rodata_bd1b5 = rodata_bc097 + 0x111e);
PROVIDE(rodata_bd697 = rodata_bc097 + 0x1600);
PROVIDE(rodata_bdb79 = rodata_bc097 + 0x1ae2);
PROVIDE(rodata_be05b = rodata_bc097 + 0x1fc4);
PROVIDE(rodata_be53d = rodata_bc097 + 0x24a6);
PROVIDE(rodata_bea1f = rodata_bc097 + 0x2988);
PROVIDE(rodata_bef01 = rodata_bc097 + 0x2e6a);
PROVIDE(rodata_bf3e3 = rodata_bc097 + 0x334c);
PROVIDE(rodata_bf8c5 = rodata_bc097 + 0x382e);
PROVIDE(rodata_bfda7 = rodata_bc097 + 0x3d10);
PROVIDE(rodata_c0289 = rodata_bc097 + 0x41f2);
PROVIDE(rodata_c076b = rodata_bc097 + 0x46d4);
PROVIDE(rodata_c0c4d = rodata_bc097 + 0x4bb6);
PROVIDE(rodata_c112f = rodata_bc097 + 0x5098);
PROVIDE(rodata_c1611 = rodata_bc097 + 0x557a);
PROVIDE(rodata_c1af3 = rodata_bc097 + 0x5a5c);
PROVIDE(rodata_c1fd5 = rodata_bc097 + 0x5f3e);
PROVIDE(rodata_c24b7 = rodata_bc097 + 0x6420);
PROVIDE(rodata_c2999 = rodata_bc097 + 0x6902);
PROVIDE(rodata_c2e7b = rodata_bc097 + 0x6de4);
PROVIDE(rodata_c335d = rodata_bc097 + 0x72c6);
PROVIDE(rodata_c383f = rodata_bc097 + 0x77a8);
PROVIDE(rodata_c3d21 = rodata_bc097 + 0x7c8a);
PROVIDE(rodata_c4203 = rodata_bc097 + 0x816c);
PROVIDE(rodata_c46e5 = rodata_bc097 + 0x864e);
PROVIDE(rodata_c4bc7 = rodata_bc097 + 0x8b30);
PROVIDE(rodata_c50a9 = rodata_bc097 + 0x9012);
PROVIDE(rodata_c558b = rodata_bc097 + 0x94f4);
PROVIDE(rodata_c5a6d = rodata_bc097 + 0x99d6);
PROVIDE(rodata_c5f4f = rodata_bc097 + 0x9eb8);
PROVIDE(rodata_c6431 = rodata_bc097 + 0xa39a);
PROVIDE(rodata_c6913 = rodata_bc097 + 0xa87c);
PROVIDE(rodata_c6df5 = rodata_bc097 + 0xad5e);
PROVIDE(rodata_c72d7 = rodata_bc097 + 0xb240);
PROVIDE(rodata_c7309 = 0x000c7309);
PROVIDE(rodata_c733b = 0x000c733b);
PROVIDE(rodata_c736d = 0x000c736d);
PROVIDE(rodata_c739f = 0x000c739f);
PROVIDE(rodata_c73fa = rodata_c739f + 0x5b);
PROVIDE(rodata_c74c2 = rodata_c739f + 0x123);
PROVIDE(rodata_c758a = rodata_c739f + 0x1eb);
PROVIDE(rodata_c760a = rodata_c739f + 0x26b);
PROVIDE(rodata_c768a = 0x000c768a);
PROVIDE(rodata_c77c4 = 0x000c77c4);
PROVIDE(rodata_c7956 = 0x000c7956);
PROVIDE(rodata_c7a90 = rodata_c7956 + 0x13a);
PROVIDE(rodata_c7c22 = rodata_c7956 + 0x2cc);
PROVIDE(rodata_c7e92 = rodata_c7956 + 0x53c);
PROVIDE(rodata_c7f5a = rodata_c7956 + 0x604);
PROVIDE(rodata_c805e = rodata_c7956 + 0x708);
PROVIDE(rodata_c8162 = rodata_c7956 + 0x80c);
PROVIDE(rodata_c81a3 = rodata_c7956 + 0x84d);
PROVIDE(rodata_c82db = rodata_c7956 + 0x985);
PROVIDE(rodata_c83a3 = rodata_c7956 + 0xa4d);
PROVIDE(rodata_c846b = rodata_c7956 + 0xb15);
PROVIDE(rodata_c8533 = rodata_c7956 + 0xbdd);
PROVIDE(rodata_c85fb = rodata_c7956 + 0xca5);
PROVIDE(rodata_c86c3 = rodata_c7956 + 0xd6d);
PROVIDE(rodata_c87c7 = rodata_c7956 + 0xe71);
PROVIDE(rodata_c88cb = rodata_c7956 + 0xf75);
PROVIDE(rodata_c89cf = rodata_c7956 + 0x1079);
PROVIDE(rodata_c8a97 = rodata_c7956 + 0x1141);
PROVIDE(rodata_c8b5f = rodata_c7956 + 0x1209);
PROVIDE(rodata_c8c27 = rodata_c7956 + 0x12d1);
PROVIDE(rodata_c8cef = rodata_c7956 + 0x1399);
PROVIDE(rodata_c8db7 = rodata_c7956 + 0x1461);
PROVIDE(rodata_c8e7f = rodata_c7956 + 0x1529);
PROVIDE(rodata_c8f47 = rodata_c7956 + 0x15f1);
PROVIDE(rodata_c900f = rodata_c7956 + 0x16b9);
PROVIDE(rodata_c9113 = rodata_c7956 + 0x17bd);
PROVIDE(rodata_c9217 = rodata_c7956 + 0x18c1);
PROVIDE(rodata_c931b = rodata_c7956 + 0x19c5);
PROVIDE(rodata_c941f = rodata_c7956 + 0x1ac9);
PROVIDE(rodata_c9523 = rodata_c7956 + 0x1bcd);
PROVIDE(rodata_c9627 = rodata_c7956 + 0x1cd1);
PROVIDE(rodata_c972b = rodata_c7956 + 0x1dd5);
PROVIDE(rodata_c982f = rodata_c7956 + 0x1ed9);
PROVIDE(rodata_c9933 = rodata_c7956 + 0x1fdd);
PROVIDE(rodata_c9a37 = rodata_c7956 + 0x20e1);
PROVIDE(rodata_c9b3b = rodata_c7956 + 0x21e5);
PROVIDE(rodata_c9c3f = rodata_c7956 + 0x22e9);
PROVIDE(rodata_c9d43 = rodata_c7956 + 0x23ed);
PROVIDE(rodata_c9e47 = rodata_c7956 + 0x24f1);
PROVIDE(rodata_c9f4b = rodata_c7956 + 0x25f5);
PROVIDE(rodata_ca04f = rodata_c7956 + 0x26f9);
PROVIDE(rodata_ca153 = rodata_c7956 + 0x27fd);
PROVIDE(rodata_cb7fb = rodata_c7956 + 0x3ea5);
PROVIDE(rodata_cc863 = rodata_c7956 + 0x4f0d);
PROVIDE(rodata_cd5ab = rodata_c7956 + 0x5c55);
PROVIDE(rodata_ce483 = rodata_c7956 + 0x6b2d);
PROVIDE(rodata_cff13 = rodata_c7956 + 0x85bd);
PROVIDE(rodata_d06cf = rodata_c7956 + 0x8d79);
PROVIDE(rodata_d0e9f = rodata_c7956 + 0x9549);
PROVIDE(rodata_d15a7 = rodata_c7956 + 0x9c51);
PROVIDE(rodata_d215f = rodata_c7956 + 0xa809);
PROVIDE(rodata_d328f = rodata_c7956 + 0xb939);
PROVIDE(rodata_d43bf = rodata_c7956 + 0xca69);
/* ---- iteration 14: the projector-controller vtable (quicknote_buffer_pool_init
 * @0x47148, called from main() at 0x17324 with r0 = device_ctx + 0xb6c).
 * Nine code pointers land at ctx+0xb6c..ctx+0xb8c; Ghidra catalogued only
 * three of the targets (jdb_panel_init / panel_off / panel_on) and folded the
 * other six into the tail of the preceding symbol, so they stayed raw flash
 * literals.  global_system_suspend dispatches through slot +0x04 (ctx+0xb70)
 * = panel_suspend, which is why the boot faulted with "Illegal use of the
 * EPSR".  All six are now reconstructed (cfg_verify PASS 200/200 each) and
 * bound to their real definitions; the archive members are pulled in by
 * quicknote_buffer_pool_init referencing ADDR_<name>_THUMB. */
/* log-tag / format strings used by the six new panel vtable bodies. */
PROVIDE(rodata_d74d7 = 0x000d74d7);
/* P4 iteration 35, rodata batch 4 (recon/analysis/rodata_decode_report.md
 * §8): rodata_d753a is the 59,944-byte packed-4bpp glyph BITMAP run
 * [0xd753a, 0xe5f62) emitted byte-exact by
 * recon/application/rodata/g1_app_rodata_02.c.  Its numeric pin is gone so a
 * link that failed to retain the object errors out instead of silently
 * reading our own relocated image again, and the four pins interior to the
 * run are re-pinned onto it -- the same four lines
 * recon/application/rodata/g1_app_rodata_interior.ld carries.  The extents
 * close to the byte in both directions:
 *   0xe17da + sum(w_i)*0x1a = 0xe17da + 435*26 = 0xe4408  (= small clock)
 *   0xe4408 + 114*0x20                          = 0xe5248  (= large clock)
 *   0xe5248 +  86*0x27                          = 0xe5f62  (= rodata_e5f62,
 *   the default-font blob recovered in iteration 33). */
/* P4 iteration 36 SPLITS that run in three (see
 * recon/application/app/src/g1_app_glyph_bitmap_rodata.c, which now owns
 * `rodata_d753a` and `rodata_e123a` instead of g1_app_rodata_02.c):
 *   [0xd753a, 0xd793a)  1,024 B  nibble-expansion LUT              EMITTED
 *   [0xd793a, 0xe123a) 39,680 B  low-battery DEMO IMAGE           WITHHELD
 *   [0xe123a, 0xe5f62) 19,752 B  icons + the three glyph runs      EMITTED
 * The demo image's only reader is update_demo_image_display via
 * demo_image_get_position(0) = rodata_0x8ac20[0] = 0x000d793a, which
 * ui_refalsh_warp reaches only when is_battery_critical() == 1; neither
 * display-parity phase enters it, and that shipped absolute word is left
 * exactly as it is.  Withholding it buys the 39,168 B the fade-mask atlas
 * needed against a 982,528 B partition holding a 977,805 B shipped image.
 * The three glyph pins are therefore re-expressed on rodata_e123a. */
PROVIDE(rodata_e17da = rodata_e123a + 0x5a0);
PROVIDE(rodata_e4408 = rodata_e123a + 0x31ce);
PROVIDE(rodata_e5248 = rodata_e123a + 0x400e);
/* rodata_e5f62: P4 iteration 33 -- the default-font glyph BITMAP blob, now
 * defined byte-exact in g1_app_font_rodata.c (37050 B, 0xe5f62..0xef01c). */
PROVIDE(rodata_ef081 = 0x000ef081);
PROVIDE(rodata_ef0fb = 0x000ef0fb);
PROVIDE(rodata_ef214 = 0x000ef214);
PROVIDE(rodata_ef29b = 0x000ef29b);
PROVIDE(rodata_ef3e2 = 0x000ef3e2);
PROVIDE(rodata_ef596 = 0x000ef596);
PROVIDE(rodata_ef5df = 0x000ef5df);
PROVIDE(rodata_ef76f = 0x000ef76f);
PROVIDE(rodata_f0000 = 0x000f0000);
PROVIDE(rodata_f02a3 = 0x000f02a3);
PROVIDE(rodata_f04ef = 0x000f04ef);
PROVIDE(rodata_f059f = 0x000f059f);
PROVIDE(rodata_f0661 = 0x000f0661);
PROVIDE(rodata_f0692 = 0x000f0692);
PROVIDE(rodata_f0824 = 0x000f0824);
PROVIDE(rodata_f08c7 = 0x000f08c7);
PROVIDE(rodata_f0959 = 0x000f0959);
PROVIDE(rodata_f0982 = 0x000f0982);
PROVIDE(rodata_f09d1 = 0x000f09d1);
PROVIDE(rodata_f0a68 = 0x000f0a68);
PROVIDE(rodata_f0ae4 = 0x000f0ae4);
PROVIDE(rodata_f0be7 = 0x000f0be7);
PROVIDE(rodata_f0c14 = 0x000f0c14);
PROVIDE(rodata_f0c32 = 0x000f0c32);
PROVIDE(rodata_f0cae = 0x000f0cae);
PROVIDE(rodata_f0da7 = 0x000f0da7);
PROVIDE(rodata_f0e73 = 0x000f0e73);
PROVIDE(rodata_f0ed2 = rodata_f0e73 + 0x5f);
PROVIDE(rodata_f0ee3 = 0x000f0ee3);
PROVIDE(rodata_f0ee7 = 0x000f0ee7);
PROVIDE(rodata_f0ef0 = 0x000f0ef0);
PROVIDE(rodata_f0f0c = 0x000f0f0c);
PROVIDE(rodata_f0f12 = 0x000f0f12);
PROVIDE(rodata_f0f16 = 0x000f0f16);
PROVIDE(rodata_f0f24 = 0x000f0f24);
PROVIDE(rodata_f0f26 = 0x000f0f26);
PROVIDE(rodata_f0f29 = rodata_f0f26 + 0x3);
PROVIDE(rodata_f0f45 = rodata_f0f26 + 0x1f);
PROVIDE(rodata_f0f61 = 0x000f0f61);
PROVIDE(rodata_f0fed = 0x000f0fed);
PROVIDE(rodata_f0ff1 = rodata_f0fed + 0x4);
PROVIDE(rodata_f1015 = rodata_f0fed + 0x28);
PROVIDE(rodata_f1031 = 0x000f1031);
PROVIDE(rodata_f1036 = 0x000f1036);
PROVIDE(rodata_f1105 = 0x000f1105);
PROVIDE(rodata_f1126 = 0x000f1126);
PROVIDE(rodata_f1180 = 0x000f1180);
PROVIDE(rodata_f11bc = 0x000f11bc);
PROVIDE(rodata_f1237 = 0x000f1237);
PROVIDE(rodata_f1253 = 0x000f1253);
PROVIDE(rodata_f1270 = 0x000f1270);
PROVIDE(rodata_f1284 = 0x000f1284);
PROVIDE(rodata_f1299 = 0x000f1299);
PROVIDE(rodata_f13bc = 0x000f13bc);
PROVIDE(rodata_f1404 = 0x000f1404);
PROVIDE(rodata_f1432 = 0x000f1432);
PROVIDE(rodata_f1459 = 0x000f1459);
PROVIDE(rodata_f1484 = 0x000f1484);
PROVIDE(rodata_f154a = 0x000f154a);
PROVIDE(rodata_f1574 = 0x000f1574);
PROVIDE(rodata_f1590 = 0x000f1590);
PROVIDE(rodata_f159e = 0x000f159e);
PROVIDE(rodata_f15cc = 0x000f15cc);
PROVIDE(rodata_f15f9 = 0x000f15f9);
PROVIDE(rodata_f1625 = 0x000f1625);
PROVIDE(rodata_f1681 = 0x000f1681);
PROVIDE(rodata_f1754 = 0x000f1754);
PROVIDE(rodata_f1968 = 0x000f1968);
PROVIDE(rodata_f1abb = 0x000f1abb);
PROVIDE(rodata_f1aea = 0x000f1aea);
PROVIDE(rodata_f1b19 = 0x000f1b19);
PROVIDE(rodata_f1b28 = 0x000f1b28);
PROVIDE(rodata_f1b6b = 0x000f1b6b);
PROVIDE(rodata_f1b7a = 0x000f1b7a);
PROVIDE(rodata_f1ba8 = 0x000f1ba8);
PROVIDE(rodata_f1c39 = 0x000f1c39);
PROVIDE(rodata_f1c4f = 0x000f1c4f);
PROVIDE(rodata_f1c82 = 0x000f1c82);
PROVIDE(rodata_f1c95 = 0x000f1c95);
PROVIDE(rodata_f1cad = 0x000f1cad);
PROVIDE(rodata_f1cc3 = 0x000f1cc3);
PROVIDE(rodata_f1ce2 = 0x000f1ce2);
PROVIDE(rodata_f1d11 = 0x000f1d11);
PROVIDE(rodata_f1df9 = 0x000f1df9);
PROVIDE(rodata_f1e0f = 0x000f1e0f);
PROVIDE(rodata_f1e20 = 0x000f1e20);
PROVIDE(rodata_f1e39 = 0x000f1e39);
PROVIDE(rodata_f1e4e = 0x000f1e4e);
PROVIDE(rodata_f1e69 = 0x000f1e69);
PROVIDE(rodata_f1e81 = 0x000f1e81);
PROVIDE(rodata_f1e99 = 0x000f1e99);
PROVIDE(rodata_f1eac = 0x000f1eac);
PROVIDE(rodata_f1ec6 = 0x000f1ec6);
PROVIDE(rodata_f1ef0 = 0x000f1ef0);
PROVIDE(rodata_f1f0e = 0x000f1f0e);
PROVIDE(rodata_f1f33 = 0x000f1f33);
PROVIDE(rodata_f1f4d = 0x000f1f4d);
PROVIDE(rodata_f2087 = 0x000f2087);
PROVIDE(rodata_f20f7 = 0x000f20f7);
PROVIDE(rodata_f211b = rodata_f20f7 + 0x24);
PROVIDE(rodata_f212c = 0x000f212c);
PROVIDE(rodata_f2132 = 0x000f2132);
PROVIDE(rodata_f2158 = 0x000f2158);
PROVIDE(rodata_f217b = 0x000f217b);
PROVIDE(rodata_f219e = 0x000f219e);
PROVIDE(rodata_f2201 = 0x000f2201);
PROVIDE(rodata_f23d3 = 0x000f23d3);
PROVIDE(rodata_f23d4 = 0x000f23d4);
PROVIDE(rodata_f2432 = 0x000f2432);
PROVIDE(rodata_f2558 = 0x000f2558);
PROVIDE(rodata_f255b = 0x000f255b);
PROVIDE(rodata_f2561 = 0x000f2561);
PROVIDE(rodata_f25fb = 0x000f25fb);
PROVIDE(rodata_f261f = 0x000f261f);
PROVIDE(rodata_f2634 = 0x000f2634);
PROVIDE(rodata_f26c1 = 0x000f26c1);
PROVIDE(rodata_f26c4 = 0x000f26c4);
PROVIDE(rodata_f26e7 = 0x000f26e7);
PROVIDE(rodata_f270e = rodata_f26e7 + 0x27);
PROVIDE(rodata_f272f = 0x000f272f);
PROVIDE(rodata_f2734 = 0x000f2734);
PROVIDE(rodata_f273a = 0x000f273a);
PROVIDE(rodata_f2743 = 0x000f2743);
PROVIDE(rodata_f274b = 0x000f274b);
PROVIDE(rodata_f2755 = 0x000f2755);
PROVIDE(rodata_f275f = 0x000f275f);
PROVIDE(rodata_f2766 = 0x000f2766);
PROVIDE(rodata_f2772 = 0x000f2772);
PROVIDE(rodata_f27cc = rodata_f2772 + 0x5a);
PROVIDE(rodata_f27cf = rodata_f2772 + 0x5d);
PROVIDE(rodata_f27db = 0x000f27db);
PROVIDE(rodata_f27df = 0x000f27df);
PROVIDE(rodata_f27e3 = 0x000f27e3);
PROVIDE(rodata_f27eb = 0x000f27eb);
PROVIDE(rodata_f280b = 0x000f280b);
PROVIDE(rodata_f289a = 0x000f289a);
PROVIDE(rodata_f28b4 = 0x000f28b4);
PROVIDE(rodata_f28d4 = 0x000f28d4);
PROVIDE(rodata_f2963 = 0x000f2963);
PROVIDE(rodata_f2abf = 0x000f2abf);
PROVIDE(rodata_f2b33 = 0x000f2b33);
PROVIDE(rodata_f2b3a = rodata_f2b33 + 0x7);
PROVIDE(rodata_f2b41 = rodata_f2b33 + 0xe);
PROVIDE(rodata_f2b47 = rodata_f2b33 + 0x14);
PROVIDE(rodata_f2b65 = 0x000f2b65);
PROVIDE(rodata_f2b86 = 0x000f2b86);
PROVIDE(rodata_f2baa = 0x000f2baa);
PROVIDE(rodata_f2bcf = 0x000f2bcf);
PROVIDE(rodata_f2c01 = 0x000f2c01);
PROVIDE(rodata_f2c25 = 0x000f2c25);
PROVIDE(rodata_f2c6b = 0x000f2c6b);
PROVIDE(rodata_f2c71 = 0x000f2c71);
PROVIDE(rodata_f2c8c = 0x000f2c8c);
PROVIDE(rodata_f2cc8 = 0x000f2cc8);
PROVIDE(rodata_f2db7 = 0x000f2db7);
PROVIDE(rodata_f2e3c = 0x000f2e3c);
PROVIDE(rodata_f2e84 = 0x000f2e84);
/* iteration 17: this pin was missing from the generated set while every other
 * log-format string in bt_hci_core_recv_event (rodata_f2ddb / f2ef5 / f2f45)
 * was present.  The gap only became visible once the `.data` restore rooted
 * bt_hci_core_recv_event, which the previous links garbage-collected. */
PROVIDE(rodata_f2f59 = 0x000f2f59);
PROVIDE(rodata_f2f8e = 0x000f2f8e);
PROVIDE(rodata_f304a = 0x000f304a);
PROVIDE(rodata_f30dd = 0x000f30dd);
PROVIDE(rodata_f3103 = 0x000f3103);
PROVIDE(rodata_f3157 = 0x000f3157);
PROVIDE(rodata_f3191 = 0x000f3191);
PROVIDE(rodata_f31a5 = 0x000f31a5);
PROVIDE(rodata_f327f = 0x000f327f);
PROVIDE(rodata_f3324 = 0x000f3324);
PROVIDE(rodata_f3376 = 0x000f3376);
PROVIDE(rodata_f338f = 0x000f338f);
PROVIDE(rodata_f3395 = 0x000f3395);
PROVIDE(rodata_f339b = 0x000f339b);
PROVIDE(rodata_f33b7 = 0x000f33b7);
PROVIDE(rodata_f33d4 = 0x000f33d4);
PROVIDE(rodata_f33e4 = 0x000f33e4);
PROVIDE(rodata_f341d = 0x000f341d);
PROVIDE(rodata_f3449 = 0x000f3449);
PROVIDE(rodata_f349f = 0x000f349f);
PROVIDE(rodata_f3509 = 0x000f3509);
PROVIDE(rodata_f35e4 = 0x000f35e4);
PROVIDE(rodata_f3615 = rodata_f35e4 + 0x31);
PROVIDE(rodata_f3630 = 0x000f3630);
PROVIDE(rodata_f36b3 = 0x000f36b3);
PROVIDE(rodata_f36e0 = 0x000f36e0);
PROVIDE(rodata_f3705 = 0x000f3705);
PROVIDE(rodata_f3733 = 0x000f3733);
PROVIDE(rodata_f374c = 0x000f374c);
PROVIDE(rodata_f376a = 0x000f376a);
PROVIDE(rodata_f3796 = 0x000f3796);
PROVIDE(rodata_f37b6 = 0x000f37b6);
PROVIDE(rodata_f37df = 0x000f37df);
PROVIDE(rodata_f381d = 0x000f381d);
PROVIDE(rodata_f394f = 0x000f394f);
PROVIDE(rodata_f3966 = 0x000f3966);
PROVIDE(rodata_f398f = 0x000f398f);
PROVIDE(rodata_f39ae = 0x000f39ae);
PROVIDE(rodata_f39ca = 0x000f39ca);
PROVIDE(rodata_f39f4 = 0x000f39f4);
PROVIDE(rodata_f3a5d = 0x000f3a5d);
PROVIDE(rodata_f3aa8 = 0x000f3aa8);
PROVIDE(rodata_f3b12 = 0x000f3b12);
PROVIDE(rodata_f3b2f = 0x000f3b2f);
PROVIDE(rodata_f3b4d = rodata_f3b2f + 0x1e);
PROVIDE(rodata_f3b6f = 0x000f3b6f);
PROVIDE(rodata_f3b74 = 0x000f3b74);
PROVIDE(rodata_f3b92 = 0x000f3b92);
PROVIDE(rodata_f3bd2 = 0x000f3bd2);
PROVIDE(rodata_f3be1 = rodata_f3bd2 + 0xf);
PROVIDE(rodata_f3c02 = 0x000f3c02);
PROVIDE(rodata_f3c7b = 0x000f3c7b);
PROVIDE(rodata_f3d84 = 0x000f3d84);
PROVIDE(rodata_f3dc4 = 0x000f3dc4);
PROVIDE(rodata_f3dff = 0x000f3dff);
PROVIDE(rodata_f3e24 = 0x000f3e24);
PROVIDE(rodata_f3e4e = rodata_f3e24 + 0x2a);
PROVIDE(rodata_f3ebd = 0x000f3ebd);
PROVIDE(rodata_f3ec2 = 0x000f3ec2);
PROVIDE(rodata_f3eea = 0x000f3eea);
PROVIDE(rodata_f3f11 = 0x000f3f11);
PROVIDE(rodata_f3f55 = 0x000f3f55);
PROVIDE(rodata_f3f86 = 0x000f3f86);
PROVIDE(rodata_f3fde = 0x000f3fde);
PROVIDE(rodata_f402a = 0x000f402a);
PROVIDE(rodata_f4079 = 0x000f4079);
PROVIDE(rodata_f4207 = 0x000f4207);
PROVIDE(rodata_f4223 = rodata_f4207 + 0x1c);
PROVIDE(rodata_f4240 = 0x000f4240);
PROVIDE(rodata_f4346 = 0x000f4346);
PROVIDE(rodata_f4388 = 0x000f4388);
PROVIDE(rodata_f43b8 = 0x000f43b8);
PROVIDE(rodata_f43ca = 0x000f43ca);
PROVIDE(rodata_f43e9 = 0x000f43e9);
PROVIDE(rodata_f4475 = 0x000f4475);
PROVIDE(rodata_f449a = 0x000f449a);
PROVIDE(rodata_f44c2 = 0x000f44c2);
PROVIDE(rodata_f4557 = 0x000f4557);
PROVIDE(rodata_f4590 = 0x000f4590);
PROVIDE(rodata_f45be = 0x000f45be);
PROVIDE(rodata_f4617 = 0x000f4617);
PROVIDE(rodata_f4636 = 0x000f4636);
PROVIDE(rodata_f4651 = 0x000f4651);
PROVIDE(rodata_f4680 = 0x000f4680);
PROVIDE(rodata_f4697 = 0x000f4697);
PROVIDE(rodata_f46b8 = 0x000f46b8);
PROVIDE(rodata_f472a = 0x000f472a);
PROVIDE(rodata_f4746 = 0x000f4746);
PROVIDE(rodata_f4761 = 0x000f4761);
PROVIDE(rodata_f4783 = 0x000f4783);
PROVIDE(rodata_f47a4 = 0x000f47a4);
PROVIDE(rodata_f47c1 = 0x000f47c1);
PROVIDE(rodata_f47d7 = 0x000f47d7);
PROVIDE(rodata_f47f3 = 0x000f47f3);
PROVIDE(rodata_f4812 = 0x000f4812);
PROVIDE(rodata_f486f = 0x000f486f);
PROVIDE(rodata_f4889 = 0x000f4889);
PROVIDE(rodata_f48b5 = 0x000f48b5);
PROVIDE(rodata_f48d7 = 0x000f48d7);
PROVIDE(rodata_f492b = 0x000f492b);
PROVIDE(rodata_f497c = 0x000f497c);
PROVIDE(rodata_f49a5 = 0x000f49a5);
PROVIDE(rodata_f49ac = 0x000f49ac);
PROVIDE(rodata_f49d4 = 0x000f49d4);
PROVIDE(rodata_f49ed = 0x000f49ed);
PROVIDE(rodata_f4a01 = 0x000f4a01);
PROVIDE(rodata_f4a06 = 0x000f4a06);
PROVIDE(rodata_f4a9e = 0x000f4a9e);
PROVIDE(rodata_f4aa1 = 0x000f4aa1);
PROVIDE(rodata_f4ad5 = 0x000f4ad5);
PROVIDE(rodata_f4aeb = 0x000f4aeb);
PROVIDE(rodata_f4b16 = 0x000f4b16);
PROVIDE(rodata_f4b44 = 0x000f4b44);
PROVIDE(rodata_f4bde = 0x000f4bde);
PROVIDE(rodata_f4c4b = 0x000f4c4b);
PROVIDE(rodata_f4ca5 = 0x000f4ca5);
PROVIDE(rodata_f4ca8 = 0x000f4ca8);
PROVIDE(rodata_f4cbc = 0x000f4cbc);
PROVIDE(rodata_f4db4 = 0x000f4db4);
PROVIDE(rodata_f4ddd = rodata_f4db4 + 0x29);
PROVIDE(rodata_f4de3 = 0x000f4de3);
PROVIDE(rodata_f4e22 = 0x000f4e22);
PROVIDE(rodata_f4e47 = 0x000f4e47);
PROVIDE(rodata_f4e60 = 0x000f4e60);
PROVIDE(rodata_f4e7a = 0x000f4e7a);
PROVIDE(rodata_f4e96 = 0x000f4e96);
PROVIDE(rodata_f4eb1 = 0x000f4eb1);
PROVIDE(rodata_f4f89 = 0x000f4f89);
PROVIDE(rodata_f4f98 = 0x000f4f98);
PROVIDE(rodata_f4ff0 = 0x000f4ff0);
PROVIDE(rodata_f500b = 0x000f500b);
PROVIDE(rodata_f503c = 0x000f503c);
PROVIDE(rodata_f505e = rodata_f503c + 0x22);
PROVIDE(rodata_f5071 = 0x000f5071);
PROVIDE(rodata_f5078 = 0x000f5078);
PROVIDE(rodata_f516d = 0x000f516d);
PROVIDE(rodata_f5182 = 0x000f5182);
PROVIDE(rodata_f519d = 0x000f519d);
PROVIDE(rodata_f51c4 = 0x000f51c4);
PROVIDE(rodata_f520f = 0x000f520f);
PROVIDE(rodata_f5220 = rodata_f520f + 0x11);
PROVIDE(rodata_f5248 = rodata_f520f + 0x39);
PROVIDE(rodata_f5268 = 0x000f5268);
PROVIDE(rodata_f52c0 = 0x000f52c0);
PROVIDE(rodata_f5353 = 0x000f5353);
PROVIDE(rodata_f5373 = 0x000f5373);
PROVIDE(rodata_f539a = 0x000f539a);
PROVIDE(rodata_f53ff = 0x000f53ff);
PROVIDE(rodata_f5400 = 0x000f5400);
PROVIDE(rodata_f540e = 0x000f540e);
PROVIDE(rodata_f541c = rodata_f540e + 0xe);
PROVIDE(rodata_f542d = rodata_f540e + 0x1f);
PROVIDE(rodata_f54a8 = 0x000f54a8);
PROVIDE(rodata_f5503 = 0x000f5503);
PROVIDE(rodata_f5522 = 0x000f5522);
PROVIDE(rodata_f5546 = 0x000f5546);
PROVIDE(rodata_f5660 = 0x000f5660);
PROVIDE(rodata_f5679 = 0x000f5679);
PROVIDE(rodata_f5692 = 0x000f5692);
PROVIDE(rodata_f5702 = 0x000f5702);
PROVIDE(rodata_f586b = 0x000f586b);
PROVIDE(rodata_f5871 = 0x000f5871);
PROVIDE(rodata_f5bd6 = 0x000f5bd6);
PROVIDE(rodata_f5c20 = 0x000f5c20);
PROVIDE(rodata_f5c9c = 0x000f5c9c);
PROVIDE(rodata_f5cba = 0x000f5cba);
PROVIDE(rodata_f5cd8 = 0x000f5cd8);
PROVIDE(rodata_f5d81 = 0x000f5d81);
PROVIDE(rodata_f5d9e = 0x000f5d9e);
PROVIDE(rodata_f5dbd = 0x000f5dbd);
PROVIDE(rodata_f5dfc = 0x000f5dfc);
PROVIDE(rodata_f5e79 = 0x000f5e79);
PROVIDE(rodata_f5eeb = 0x000f5eeb);
PROVIDE(rodata_f60c5 = 0x000f60c5);
PROVIDE(rodata_f6292 = 0x000f6292);
PROVIDE(rodata_f62ac = 0x000f62ac);
PROVIDE(rodata_f62e6 = 0x000f62e6);
PROVIDE(rodata_f62fd = 0x000f62fd);
PROVIDE(rodata_f6315 = 0x000f6315);
PROVIDE(rodata_f6378 = 0x000f6378);
PROVIDE(rodata_f639f = 0x000f639f);
PROVIDE(rodata_f63c1 = 0x000f63c1);
PROVIDE(rodata_f63f9 = 0x000f63f9);
PROVIDE(rodata_f642d = 0x000f642d);
PROVIDE(rodata_f644e = 0x000f644e);
PROVIDE(rodata_f6468 = 0x000f6468);
PROVIDE(rodata_f6589 = 0x000f6589);
PROVIDE(rodata_f6607 = 0x000f6607);
PROVIDE(rodata_f6659 = 0x000f6659);
PROVIDE(rodata_f66c1 = 0x000f66c1);
PROVIDE(rodata_f6716 = 0x000f6716);
PROVIDE(rodata_f67a5 = 0x000f67a5);
PROVIDE(rodata_f680e = 0x000f680e);
PROVIDE(rodata_f68d7 = 0x000f68d7);
PROVIDE(rodata_f692c = 0x000f692c);
PROVIDE(rodata_f693a = 0x000f693a);
PROVIDE(rodata_f694f = rodata_f693a + 0x15);
PROVIDE(rodata_f696e = 0x000f696e);
PROVIDE(rodata_f6977 = 0x000f6977);
PROVIDE(rodata_f6983 = 0x000f6983);
PROVIDE(rodata_f698e = 0x000f698e);
PROVIDE(rodata_f6994 = 0x000f6994);
PROVIDE(rodata_f6999 = 0x000f6999);
PROVIDE(rodata_f6a09 = 0x000f6a09);
PROVIDE(rodata_f6a46 = 0x000f6a46);
PROVIDE(rodata_f6a4a = 0x000f6a4a);
PROVIDE(rodata_f6a4e = 0x000f6a4e);
PROVIDE(rodata_f6acd = 0x000f6acd);
PROVIDE(rodata_f6b00 = 0x000f6b00);
PROVIDE(rodata_f6b3e = 0x000f6b3e);
PROVIDE(rodata_f6ba7 = 0x000f6ba7);
PROVIDE(rodata_f6bb7 = rodata_f6ba7 + 0x10);
PROVIDE(rodata_f6bc5 = 0x000f6bc5);
PROVIDE(rodata_f6c32 = 0x000f6c32);
PROVIDE(rodata_f6ceb = 0x000f6ceb);
PROVIDE(rodata_f6d26 = 0x000f6d26);
PROVIDE(rodata_f6d5e = rodata_f6d26 + 0x38);
PROVIDE(rodata_f6d9a = 0x000f6d9a);
PROVIDE(rodata_f6dc6 = 0x000f6dc6);
PROVIDE(rodata_f6dde = 0x000f6dde);
PROVIDE(rodata_f6df0 = 0x000f6df0);
PROVIDE(rodata_f6e2c = 0x000f6e2c);
PROVIDE(rodata_f6e32 = 0x000f6e32);
PROVIDE(rodata_f6e3a = 0x000f6e3a);
PROVIDE(rodata_f6e66 = 0x000f6e66);
PROVIDE(rodata_f6ead = 0x000f6ead);
PROVIDE(rodata_f6ef4 = 0x000f6ef4);
PROVIDE(rodata_f6fa3 = 0x000f6fa3);
PROVIDE(rodata_f6fd9 = 0x000f6fd9);
PROVIDE(rodata_f6fef = 0x000f6fef);
PROVIDE(rodata_f702b = 0x000f702b);
PROVIDE(rodata_f7052 = 0x000f7052);
PROVIDE(rodata_f707c = 0x000f707c);
PROVIDE(rodata_f78d1 = 0x000f78d1);
PROVIDE(rodata_f7921 = 0x000f7921);
PROVIDE(rodata_f7971 = 0x000f7971);
PROVIDE(rodata_f7987 = 0x000f7987);
PROVIDE(rodata_f799d = 0x000f799d);
PROVIDE(rodata_f79c8 = 0x000f79c8);
PROVIDE(rodata_f7a03 = 0x000f7a03);
PROVIDE(rodata_f7a1b = 0x000f7a1b);
PROVIDE(rodata_f7a30 = 0x000f7a30);
PROVIDE(rodata_f7a31 = 0x000f7a31);
PROVIDE(rodata_f7a32 = 0x000f7a32);
PROVIDE(rodata_f7a3f = 0x000f7a3f);
PROVIDE(rodata_f7a8a = 0x000f7a8a);
PROVIDE(rodata_f7a8c = 0x000f7a8c);
PROVIDE(rodata_f7a9f = 0x000f7a9f);
PROVIDE(rodata_f7ad6 = 0x000f7ad6);
PROVIDE(rodata_f7b6d = 0x000f7b6d);
PROVIDE(rodata_f7b6f = 0x000f7b6f);
PROVIDE(rodata_f7b84 = 0x000f7b84);
PROVIDE(rodata_f7ba6 = 0x000f7ba6);
PROVIDE(rodata_f7be9 = 0x000f7be9);
PROVIDE(rodata_f7c02 = 0x000f7c02);
PROVIDE(rodata_f7c0e = 0x000f7c0e);
PROVIDE(rodata_f7c1a = 0x000f7c1a);
PROVIDE(rodata_f7c24 = 0x000f7c24);
PROVIDE(rodata_f7c28 = 0x000f7c28);
PROVIDE(rodata_f7c2e = 0x000f7c2e);
PROVIDE(rodata_f7c34 = 0x000f7c34);
PROVIDE(rodata_f7c9c = 0x000f7c9c);
PROVIDE(rodata_f7cc4 = 0x000f7cc4);
PROVIDE(rodata_f7ce5 = 0x000f7ce5);
PROVIDE(rodata_f7cfd = 0x000f7cfd);
PROVIDE(rodata_f7d1f = 0x000f7d1f);
PROVIDE(rodata_f7d3c = 0x000f7d3c);
PROVIDE(rodata_f7dbe = 0x000f7dbe);
PROVIDE(rodata_f7df6 = 0x000f7df6);
PROVIDE(rodata_f7e3c = 0x000f7e3c);
PROVIDE(rodata_f7e7e = 0x000f7e7e);
PROVIDE(rodata_f7f29 = 0x000f7f29);
PROVIDE(rodata_f7f4b = 0x000f7f4b);
PROVIDE(rodata_f7f6e = 0x000f7f6e);
PROVIDE(rodata_f7fee = 0x000f7fee);
PROVIDE(rodata_f801f = 0x000f801f);
PROVIDE(rodata_f8031 = 0x000f8031);
PROVIDE(rodata_f8056 = 0x000f8056);
PROVIDE(rodata_f80cc = 0x000f80cc);
PROVIDE(rodata_f80ee = 0x000f80ee);
PROVIDE(rodata_f813a = 0x000f813a);
PROVIDE(rodata_f815c = 0x000f815c);
PROVIDE(rodata_f8181 = 0x000f8181);
PROVIDE(rodata_f8198 = 0x000f8198);
PROVIDE(rodata_f81b8 = 0x000f81b8);
PROVIDE(rodata_f820f = 0x000f820f);
PROVIDE(rodata_f8230 = 0x000f8230);
PROVIDE(rodata_f8247 = 0x000f8247);
PROVIDE(rodata_f824d = 0x000f824d);
PROVIDE(rodata_f8262 = 0x000f8262);
PROVIDE(rodata_f8291 = 0x000f8291);
PROVIDE(rodata_f82a5 = 0x000f82a5);
PROVIDE(rodata_f82ab = 0x000f82ab);
PROVIDE(rodata_f82df = 0x000f82df);
PROVIDE(rodata_f82e0 = 0x000f82e0);
PROVIDE(rodata_f82f4 = 0x000f82f4);
PROVIDE(rodata_f84af = 0x000f84af);
PROVIDE(rodata_f84d6 = 0x000f84d6);
PROVIDE(rodata_f84f7 = 0x000f84f7);
PROVIDE(rodata_f8522 = 0x000f8522);
PROVIDE(rodata_f8553 = 0x000f8553);
PROVIDE(rodata_f8584 = 0x000f8584);
PROVIDE(rodata_f85bb = 0x000f85bb);
PROVIDE(rodata_f85d2 = 0x000f85d2);
PROVIDE(rodata_f8658 = 0x000f8658);
PROVIDE(rodata_f8698 = 0x000f8698);
PROVIDE(rodata_f86b7 = 0x000f86b7);
PROVIDE(rodata_f86d9 = 0x000f86d9);
PROVIDE(rodata_f86fd = 0x000f86fd);
PROVIDE(rodata_f871d = 0x000f871d);
PROVIDE(rodata_f873e = 0x000f873e);
PROVIDE(rodata_f875b = 0x000f875b);
PROVIDE(rodata_f8775 = 0x000f8775);
PROVIDE(rodata_f878a = 0x000f878a);
PROVIDE(rodata_f87a6 = 0x000f87a6);
PROVIDE(rodata_f87b7 = 0x000f87b7);
PROVIDE(rodata_f87d4 = 0x000f87d4);
PROVIDE(rodata_f87eb = 0x000f87eb);
PROVIDE(rodata_f8806 = 0x000f8806);
PROVIDE(rodata_f881f = 0x000f881f);
PROVIDE(rodata_f8835 = 0x000f8835);
PROVIDE(rodata_f8855 = 0x000f8855);
PROVIDE(rodata_f887b = 0x000f887b);
PROVIDE(rodata_f889f = 0x000f889f);
PROVIDE(rodata_f88af = 0x000f88af);
PROVIDE(rodata_f88c2 = 0x000f88c2);
PROVIDE(rodata_f88dc = 0x000f88dc);
PROVIDE(rodata_f88f2 = 0x000f88f2);
PROVIDE(rodata_f8901 = 0x000f8901);
PROVIDE(rodata_f8911 = 0x000f8911);
PROVIDE(rodata_f891e = 0x000f891e);
PROVIDE(rodata_f8942 = 0x000f8942);
PROVIDE(rodata_f8974 = 0x000f8974);
PROVIDE(rodata_f899c = 0x000f899c);
PROVIDE(rodata_f89d9 = 0x000f89d9);
PROVIDE(rodata_f8a2e = 0x000f8a2e);
PROVIDE(rodata_f8a3b = 0x000f8a3b);
PROVIDE(rodata_f8a6b = 0x000f8a6b);
PROVIDE(rodata_f8b6b = 0x000f8b6b);
PROVIDE(rodata_f8b71 = 0x000f8b71);
PROVIDE(rodata_f8b75 = 0x000f8b75);
PROVIDE(rodata_f8b88 = 0x000f8b88);
PROVIDE(rodata_f8baa = 0x000f8baa);
PROVIDE(rodata_f8bb3 = 0x000f8bb3);
PROVIDE(rodata_f8bb7 = 0x000f8bb7);
PROVIDE(rodata_f8bce = 0x000f8bce);
PROVIDE(rodata_f8c42 = 0x000f8c42);
PROVIDE(rodata_f8c53 = 0x000f8c53);
PROVIDE(rodata_f8cd5 = 0x000f8cd5);
PROVIDE(rodata_fa9b4 = 0x000fa9b4);
PROVIDE(rodata_fa9cc = 0x000fa9cc);
PROVIDE(rodata_faa14 = 0x000faa14);
PROVIDE(rodata_faa2c = 0x000faa2c);
PROVIDE(g_sram_base_word = 0x20000000);
PROVIDE(g_20000800 = 0x20000800);
PROVIDE(g_ble_dev_state = bt_dev);
PROVIDE(g_bt_le_legacy_adv = bt_dev + 0x18);
PROVIDE(g_ble_adv_ctx_peer_addr = bt_dev + 0x21);
PROVIDE(g_ble_adv_ctx_flags = bt_dev + 0x28);
PROVIDE(g_20002069 = bt_dev + 0x69);
PROVIDE(g_2000206f = bt_dev + 0x6f);
PROVIDE(g_ble_dev_acl_buf_info = bt_dev + 0x78);
PROVIDE(g_ble_dev_ncmd_sem = bt_dev + 0xd4);
PROVIDE(g_ble_dev_le_features = bt_dev + 0xd8);
PROVIDE(g_bt_dev_hci_buf_ready = bt_dev + 0x104);
PROVIDE(g_ble_dev_le_pkts_sem = bt_dev + 0x108);
PROVIDE(g_ble_conn_ext_mode_pending = bt_dev + 0x110);
PROVIDE(g_ble_rl_entries_max = bt_dev + 0x120);
PROVIDE(g_ble_rl_entries_cnt = bt_dev + 0x121);
PROVIDE(g_20002128 = bt_dev + 0x128);
PROVIDE(g_20002140 = bt_dev + 0x140);
PROVIDE(g_bt_hci_recv_fifo = bt_dev + 0x144);
PROVIDE(hci_cmd_pool = bt_dev + 0x14c);
PROVIDE(g_20002168 = bt_dev + 0x168);
PROVIDE(g_bt_dev_name = bt_dev + 0x16c);
PROVIDE(adc_context = g1_ram_arena + 0x190);
PROVIDE(g_adc_context_lock = g1_ram_arena + 0x1d0);
PROVIDE(g_adc_saadc_ctrl_mutex = g1_ram_arena + 0x1e8);
PROVIDE(m_adc_channel_input_cfg = g1_ram_arena + 0x230);
PROVIDE(g_log_level = g1_ram_arena + 0x30c);
/* iteration 14: the 16-entry (16 B stride) screen-render table that
 * panel_render_screen_dispatch (0x35774) indexes; original 0x20002430. */
PROVIDE(g_screen_render_table = g1_ram_arena + 0x430);
PROVIDE(g_ancs_notify_sync_obj = g1_ram_arena + 0x310);
PROVIDE(g_ancs_last_cmd_id = g1_ram_arena + 0x31c);
PROVIDE(g_20002320 = g1_ram_arena + 0x320);
PROVIDE(g_20002328 = g1_ram_arena + 0x328);
PROVIDE(g_20002338 = g1_ram_arena + 0x338);
/* Iteration 22 — the advertising / scan-response `struct bt_data` arrays.
 * Both shipped initialisers contain POINTERS, so the arena `.data` restore
 * drops the run (measured: nothing between arena offsets 0x34c and 0x368) and
 * bt_start advertised a zeroed AD set.  Emitted with their shipped contents by
 * recon/application/app/src/g1_bt_adv_objects.c and bound here. */
PROVIDE(g_20002350 = g1_bt_adv_scan_rsp);
PROVIDE(g_20002358 = g1_bt_adv_data);
PROVIDE(g_t_init = g1_ram_arena + 0x368);
PROVIDE(g_box_event_state_buf = g1_ram_arena + 0x380);
PROVIDE(g_st25dv_i2c_dev = g1_st25dv_i2c_dev);
/* RAM-PIN REBIND + EMISSION (iteration 7) — the app's `struct ipc_ept_cfg`.
 * 0x200023dc is .data in the original (load image at flash 0xf9140) and holds
 * { .name = "ipc0" (0x9f71c), .prio = 0, .cb.bound = 0x25b6d,
 *   .cb.received = 0x25a49 (ipc0_ept_recv), .cb.error = NULL, .priv = NULL }.
 * Nothing in the recovered corpus writes it, so pinning it left cfg->name
 * pointing at whatever our build placed there (in OUR build 0x200023dc is
 * inside `fdtable`).  Emitted, initialiser and all, by
 * recon/application/app/src/g1_ipc_serialization_objects.c. */
PROVIDE(g_serialization_ipc_ept_ctx = g1_serialization_ipc_ept_cfg);
PROVIDE(g_level_calc_result_cache = g1_ram_arena + 0x3f4);
PROVIDE(g_panel_calib_last_divisor = g1_ram_arena + 0x3f8);
PROVIDE(g_opt3007_bus_dev = g1_ram_arena + 0x3fc);
PROVIDE(g_audio_flash_write_offset = g1_ram_arena + 0x404);
PROVIDE(g_pt_nfc_link_cfg_static = g1_ram_arena + 0x408);
PROVIDE(g_misc_dev_handle_2418 = g1_ram_arena + 0x418);
PROVIDE(g_20002420 = g1_ram_arena + 0x420);
PROVIDE(g_fuel_gauge_dev = g1_ram_arena + 0x424);
PROVIDE(g_pt_comm_dev = g1_ram_arena + 0x428);
PROVIDE(g_pt_comm_state = g1_ram_arena + 0x42c);
PROVIDE(g_demo_img_cached_height = g1_ram_arena + 0x4e0);
PROVIDE(g_demo_img_cached_width = g1_ram_arena + 0x4e4);
PROVIDE(g_quicknote_warn_offset_ms = g1_ram_arena + 0x4e8);
PROVIDE(g_even_ai_saved_page_index = g1_ram_arena + 0x4ec);
PROVIDE(g_status_icon_last_state = g1_ram_arena + 0x4f0);
PROVIDE(g_translate_lang_string_table = g1_ram_arena + 0x4f4);
PROVIDE(g_display_canvas_y_cache = g1_ram_arena + 0x53c);
PROVIDE(g_display_canvas_x_cache = g1_ram_arena + 0x540);
PROVIDE(g_dashboard_display_level = g1_ram_arena + 0x544);
PROVIDE(g_fdtable_entries = fdtable);      /* strong owner in g1_app_sdk_state.ld */
PROVIDE(g_fdtable_refcount_field = fdtable + 8); /* strong owner in g1_app_sdk_state.ld */
PROVIDE(g_misc_val_27c8 = g1_ram_arena + 0x7c8);
PROVIDE(g_200027f8 = g1_ram_arena + 0x7f8);
PROVIDE(g_settings_nvs_backend_list_next = g1_ram_arena + 0x7fc);
/* RAM-PIN REBIND + EMISSION (iteration 7) — the Application Event Manager's
 * `struct k_work`.  .data in the shipped image (load image flash 0xf959c):
 * { .node.next = 0, .handler = 0x0004f5b1 = app_event_manager_process_events,
 *   .queue = 0, .flags = 0 }.  The pin lands inside nrfx_gpiote's `.data.m_cb`
 * in our build, so the handler word read gpiote state; measured to fire
 * work_queue_main's __ASSERT(handler != NULL) once the RAM layout shifted.
 * Storage + initialiser: recon/application/app/src/g1_app_ram_relocs.c. */
PROVIDE(g_20002838 = g1_app_event_processor_work);
PROVIDE(g_misc_286c_val = g1_ram_arena + 0x86c);
PROVIDE(g_200028b8 = g1_ram_arena + 0x8b8);
PROVIDE(g_200028ec = g1_ram_arena + 0x8ec);
PROVIDE(g_ancs_notify_work = g1_ram_arena + 0x934);
PROVIDE(g_20002944 = g1_ram_arena + 0x944);
PROVIDE(g_20002958 = g1_ram_arena + 0x958);
PROVIDE(g_bt_hci_rx_work = g1_ram_arena + 0x980);
PROVIDE(g_ble_conn_poll_signal = g1_ram_arena + 0x990);
PROVIDE(att_prep_write_rsp_buf = g1_ram_arena + 0x9a0);
PROVIDE(g_bt_att_chan_ops = g1_ram_arena + 0x9ac);
PROVIDE(g_200029d4 = g1_ram_arena + 0x9d4);
PROVIDE(g_200029f8 = g1_ram_arena + 0x9f8);
PROVIDE(g_bt_gatt_sc_ccc = g1_ram_arena + 0xa20);
PROVIDE(g_bt_smp_settings_load_cb = g1_ram_arena + 0xa50);
PROVIDE(g_cjson_hooks = g1_ram_arena + 0xbac);
PROVIDE(g_cjson_free_hook = g1_ram_arena + 0xbb0);
PROVIDE(g_20002bb8 = g1_ram_arena + 0xbb8);
PROVIDE(g_flag32_channel_alloc_mask = g1_ram_arena + 0xbbc);
PROVIDE(g_gpiote_cb = g1_ram_arena + 0xbc0);
PROVIDE(g_gpiote_cb_evt = g1_ram_arena + 0xbc4);
PROVIDE(g_ancs_notify_sync_field0_2bc8 = g1_ram_arena + 0xbc8);
PROVIDE(g_ancs_notify_sync_field1_2bcc = g1_ram_arena + 0xbcc);
PROVIDE(g_gpiote_lock = g1_ram_arena + 0xc30);
PROVIDE(g_nrfx_gpiote_channels_mask = g1_ram_arena + 0xc34);
PROVIDE(g_module_registry_node = g1_ram_arena + 0xc3c);
PROVIDE(g_20002c68 = g1_ram_arena + 0xc68);
PROVIDE(g_20002c90 = g1_ram_arena + 0xc90);
PROVIDE(g_20002cb8 = g1_ram_arena + 0xcb8);
PROVIDE(g_20002cf4 = g1_ram_arena + 0xcf4);
PROVIDE(g_20002cfc = g1_ram_arena + 0xcfc);
PROVIDE(g_20002d00 = g1_ram_arena + 0xd00);
PROVIDE(g_audio_755f8_wait_obj = g1_ram_arena + 0xd04);
PROVIDE(g_batt_soc_curve_charge_lo = g1_ram_arena + 0xd14);
PROVIDE(g_batt_soc_curve_charge_hi = g1_ram_arena + 0xd18);
PROVIDE(g_spline_nan_sentinel = g1_ram_arena + 0xd1c);
/* P4 iteration 21: `g_libc_heap_ctrl` (original 0x20002d20) is newlib's
   `_impure_ptr`: fifteen recovered libc TUs read it as
   `*(int *)&g_libc_heap_ctrl` and pass the result as the leading `struct
   _reent *` of `_vsnprintf_r` / `_malloc_r` / `_free_r` / `_strtol_r` ...
   Bound into the RAM arena it is a `.data` POINTER word, and the arena
   restore deliberately drops pointer words (see
   recon/application/gen_app_data_image.py), so it read 0.  Measured
   (iteration 21): `vsnprintf_impl` called `_vsnprintf_r(NULL, ...)`, which
   wrote nothing and returned 131; `__sprintf_chk` compared 131 >= 32 and
   raised the FORTIFY buffer-overflow oops that reset the app core the
   moment `bt_start()` first formatted the advertised device name.  The
   linked newlib-nano owns exactly this word, so bind the identity onto it.
   (was: PROVIDE(g_libc_heap_ctrl = g1_ram_arena + 0xd20);) */
PROVIDE(g_libc_heap_ctrl = _impure_ptr);
PROVIDE(g_20002d84 = g1_ram_arena + 0xd84);
PROVIDE(g_misc_static_ctx_ptr = g1_ram_arena + 0xe74);
PROVIDE(g_misc_deferred_req_params = g1_ram_arena + 0xef8);
PROVIDE(g_misc_deferred_call_desc = g1_ram_arena + 0xf0c);
PROVIDE(g_ancs_conn_param = g1_ram_arena + 0xf60);
PROVIDE(g_esb_bringup_log_pending_flag = g1_ram_arena + 0xfe0);
PROVIDE(g_product_code_buf = g1_ram_arena + 0xfe3);
PROVIDE(g_device_serial_buf = g1_ram_arena + 0x1003);
PROVIDE(g_20003023 = g1_ram_arena + 0x1023);
PROVIDE(g_level_calc_input_c_cache = g1_ram_arena + 0x1024);
PROVIDE(g_check_work_mode_ed5_field_cache = g1_ram_arena + 0x1025);
PROVIDE(g_glassbox_lid_debounced_state = g1_ram_arena + 0x1026);
PROVIDE(g_last_reported_battery_pct = g1_ram_arena + 0x1027);
PROVIDE(g_last_reported_box_charge_status = g1_ram_arena + 0x1028);
PROVIDE(g_last_reported_box_charge_pct = g1_ram_arena + 0x1029);
PROVIDE(g_charge_notify_state_init_flag = g1_ram_arena + 0x102a);
PROVIDE(g_esb_sync_inbound_status = g1_ram_arena + 0x102b);
PROVIDE(g_flash_crc_active_flag = g1_ram_arena + 0x102c);
PROVIDE(g_last_standby_event_id = g1_ram_arena + 0x102d);
PROVIDE(g_send_event_pending_id = g1_ram_arena + 0x102e);
PROVIDE(g_low_battery_sync_flag = g1_ram_arena + 0x102f);
PROVIDE(g_pt_nfc_link_init_active = g1_ram_arena + 0x1030);
PROVIDE(g_periodic_check_ok_flag = g1_ram_arena + 0x1031);
PROVIDE(g_200033d2 = g1_ram_arena + 0x13d2);
PROVIDE(g_200033d3 = g1_ram_arena + 0x13d3);
PROVIDE(g_demo_image_last_page_idx = g1_ram_arena + 0x13d4);
PROVIDE(g_200034f3 = g1_ram_arena + 0x14f3);
PROVIDE(onboarding_last_step_cache = g1_ram_arena + 0x14f5);
PROVIDE(g_gui_dark_light_dither_mask = g1_ram_arena + 0x14f6);
PROVIDE(g_md5_padding = g1_ram_arena + 0x14f7);
PROVIDE(g_smp_bondable_default = g1_ram_arena + 0x15ae);
PROVIDE(g_libm_ieee_mode_flag = g1_ram_arena + 0x15af);
PROVIDE(g_log_msg_mpsc_buffer = g1_ram_arena + 0x1648);
PROVIDE(g_200036c8 = g1_ram_arena + 0x16c8);
PROVIDE(g_20003700 = g1_ram_arena + 0x1700);
PROVIDE(g_bt_att_slab = g1_ram_arena + 0x1738);
PROVIDE(g_bt_att_chan_slab = g1_ram_arena + 0x1758);
PROVIDE(req_slab = g1_ram_arena + 0x1798);
PROVIDE(g_uart_rx_mem_slab = g1_ram_arena + 0x17b8);
PROVIDE(g_malloc_lock = g1_ram_arena + 0x17f0);
PROVIDE(g_malloc_mutex = g1_ram_arena + 0x1804);
PROVIDE(g_env_mutex = g1_ram_arena + 0x1818);
PROVIDE(g_settings_lock = g1_ram_arena + 0x1868);
PROVIDE(g_audio_msgq = g1_ram_arena + 0x1890);
PROVIDE(g_display_msgq = g1_ram_arena + 0x18c4);
PROVIDE(g_bt_data_pipe = g1_ram_arena + 0x18f8);
PROVIDE(g_dashboard_response_msgq = g1_ram_arena + 0x192c);
PROVIDE(g_quicknote_flash_msgq = g1_ram_arena + 0x1960);
PROVIDE(g_flash_store_cmd_msgq = g1_ram_arena + 0x1994);
/* RAM-PIN REBIND + EMISSION (iteration 7) — the endpoint-bind semaphore.
 * 0x200039c8 is .data in the original; its load image (flash 0xfa72c) is a
 * `struct k_sem` with self-referential wait_q/poll_events, count 0, limit 1 —
 * i.e. K_SEM_DEFINE(g_serialization_ipc_mutex, 0, 1).  Nothing in the
 * recovered corpus initialises it, and in OUR build the pin lands inside
 * `posix_thread_pool`.  Emitted by
 * recon/application/app/src/g1_ipc_serialization_objects.c. */
PROVIDE(g_serialization_ipc_mutex = g1_serialization_ipc_sem);
PROVIDE(g_200039f8 = g1_ram_arena + 0x19f8);
PROVIDE(g_bt_att_pool = g1_ram_arena + 0x1a28);
PROVIDE(free_l2cap_tx_meta_data = g1_ram_arena + 0x1a44);
PROVIDE(g_bt_conn_tx_pending_cnt = g1_ram_arena + 0x1a60);
PROVIDE(acl_tx_pool = g1_ram_arena + 0x1a7c);
PROVIDE(g_bt_conn_frag_pool = g1_ram_arena + 0x1b18);
PROVIDE(g_hci_cmd_pool = g1_ram_arena + 0x1b4c);
PROVIDE(g_ancs_notify_3be8 = g1_ram_arena + 0x1be8);
PROVIDE(g_ancs_work_thread = g1_ram_arena + 0x1c50);
PROVIDE(g_ble_work_timer = g1_ram_arena + 0x1d28);
PROVIDE(g_ble_work_thread = g1_ram_arena + 0x1d60);
PROVIDE(g_flash_ops_thread = g1_ram_arena + 0x1e38);
PROVIDE(g_brightness_thread = g1_ram_arena + 0x1f10);
/* iteration 13: imu_fusion_init's k_thread_create thread object (0x20003fe8). */
PROVIDE(g_imu_fusion_thread = g1_ram_arena + 0x1fe8);
PROVIDE(g_delay_deadline_ticks = g1_ram_arena + 0x20c8);
PROVIDE(g_200040d0 = g1_ram_arena + 0x20d0);
PROVIDE(g_200041a8 = g1_ram_arena + 0x21a8);
PROVIDE(g_20004280 = g1_ram_arena + 0x2280);
PROVIDE(g_20004358 = g1_ram_arena + 0x2358);
PROVIDE(g_20004430 = g1_ram_arena + 0x2430);
PROVIDE(g_20004508 = g1_ram_arena + 0x2508);
PROVIDE(g_200045e0 = g1_ram_arena + 0x25e0);
PROVIDE(g_200046b8 = g1_ram_arena + 0x26b8);
PROVIDE(g_fuel_gauge_init_timestamp = g1_ram_arena + 0x2790);
PROVIDE(g_aging_mode_aux_thread = g1_ram_arena + 0x2798);
PROVIDE(g_aging_mode_thread = g1_ram_arena + 0x2870);
PROVIDE(g_deadline_10s = g1_ram_arena + 0x2948);
PROVIDE(g_dashboard_widget_state = g1_ram_arena + 0x2950);
PROVIDE(g_display_last_drawn_lang = g1_ram_arena + 0x2968);
PROVIDE(g_dashboard_disp_mode = g1_ram_arena + 0x296a);
PROVIDE(g_quicknote_info = g1_ram_arena + 0x2978);
PROVIDE(g_notification_display_buffer = g1_ram_arena + 0x2988);
PROVIDE(g_200049b8 = g1_ram_arena + 0x29b8);
PROVIDE(g_ipc_or_evt_ctx = g1_ram_arena + 0x2bb8);
PROVIDE(g_20004bbc = g1_ram_arena + 0x2bbc);
PROVIDE(g_20004bbd = g1_ram_arena + 0x2bbd);
PROVIDE(g_20004bbe = g1_ram_arena + 0x2bbe);
PROVIDE(g_20004bc6 = g1_ram_arena + 0x2bc6);
PROVIDE(g_20004bc8 = g1_ram_arena + 0x2bc8);
PROVIDE(g_20004bcc = g1_ram_arena + 0x2bcc);
PROVIDE(g_20004bcd = g1_ram_arena + 0x2bcd);
PROVIDE(g_20004bd0 = g1_ram_arena + 0x2bd0);
PROVIDE(g_20004bd8 = g1_ram_arena + 0x2bd8);
PROVIDE(g_20004be0 = g1_ram_arena + 0x2be0);
PROVIDE(g_20004be5 = g1_ram_arena + 0x2be5);
PROVIDE(g_20004be8 = g1_ram_arena + 0x2be8);
PROVIDE(g_onboarding_step_retry_cnt = g1_ram_arena + 0x2bf0);
PROVIDE(g_proxy_thread = g1_ram_arena + 0x2c08);
PROVIDE(g_some_k_timer = g1_ram_arena + 0x2ce0);
PROVIDE(g_display_thread = g1_ram_arena + 0x2d18);
PROVIDE(g_dashboard_startup_snapshot = g1_ram_arena + 0x2df0);
PROVIDE(g_dashboard_dwell_base_hi = g1_ram_arena + 0x2df4);
PROVIDE(g_sync_baseline_timestamp = g1_ram_arena + 0x2df8);
PROVIDE(g_dashboard_dwell_start_ts_hi = g1_ram_arena + 0x2dfc);
PROVIDE(log_process_timestamp = g1_ram_arena + 0x36a0);
PROVIDE(g_200056a8 = g1_ram_arena + 0x36a8);
PROVIDE(smp_work_queue = g1_ram_arena + 0x3bb8);
PROVIDE(g_active_transfer_conn = g1_ram_arena + 0x3cb0);
PROVIDE(g_sys_work_q = g1_ram_arena + 0x3d38);
PROVIDE(rx_thread_data = g1_ram_arena + 0x3e30);
PROVIDE(bt_workqueue = g1_ram_arena + 0x3f08);
PROVIDE(g_hmac_prng_ctx = g1_ram_arena + 0x4000);
PROVIDE(g_ble_conn_pool = g1_ram_arena + 0x4138);
PROVIDE(g_ble_conn_ext_signal_buf = g1_ram_arena + 0x4170);
PROVIDE(g_ble_conn_pool_enabled = g1_ram_arena + 0x4208);
PROVIDE(g_l2cap_fixed_chan_ctx = g1_ram_arena + 0x4210);
PROVIDE(g_bt_gatt_sc_cfg = g1_ram_arena + 0x4328);
PROVIDE(g_bt_gatt_sc_cfg_addr = g1_ram_arena + 0x4329);
PROVIDE(g_bt_gatt_sc_cfg0_flags = g1_ram_arena + 0x4330);
PROVIDE(g_bt_gatt_sc_cfg1_flags = g1_ram_arena + 0x433c);
PROVIDE(g_bt_gatt_sc_cfg2_flags = g1_ram_arena + 0x4348);
PROVIDE(g_bt_gatt_delayed_store_work = g1_ram_arena + 0x4350);
PROVIDE(g_bt_gatt_db_hash = g1_ram_arena + 0x4380);
PROVIDE(g_20006390 = g1_ram_arena + 0x4390);
PROVIDE(g_bt_gatt_db_hash_work = g1_ram_arena + 0x43a0);
PROVIDE(g_bt_gatt_db_hash_work_63d0 = g1_ram_arena + 0x43d0);
PROVIDE(g_service_changed_range = g1_ram_arena + 0x43f8);
PROVIDE(g_bt_gatt_sc_work = g1_ram_arena + 0x4418);
PROVIDE(g_bt_gatt_flags = g1_ram_arena + 0x4448);
PROVIDE(g_misc_kobj_6454 = g1_ram_arena + 0x4454);
PROVIDE(g_20006690 = g1_ram_arena + 0x4690);
PROVIDE(g_rtc_cycle_range_minmax = g1_ram_arena + 0x46b8);
PROVIDE(g_uptime_ref_tick_hi = g1_ram_arena + 0x46bc);
PROVIDE(g_caf_power_manager_timer = g1_ram_arena + 0x46f0);
PROVIDE(g_audio_module_spinlock = g1_ram_arena + 0x48d0);
PROVIDE(g_curr_tick_lo = g1_ram_arena + 0x49e0);
PROVIDE(g_curr_tick_hi = g1_ram_arena + 0x49e4);
PROVIDE(g_battery_percent = g1_ram_arena + 0x49e8);
PROVIDE(g_200069ec = g1_ram_arena + 0x49ec);
PROVIDE(g_200069f0 = g1_ram_arena + 0x49f0);
PROVIDE(g_200069f4 = g1_ram_arena + 0x49f4);
PROVIDE(g_ambient_light_sensor_ready = g1_ram_arena + 0x49f8);
PROVIDE(device_info = g1_ram_arena + 0x49fc);
PROVIDE(g_touch_key_irq_pending = g1_ram_arena + 0x4a00);
PROVIDE(g_button_irq_cb2 = g1_ram_arena + 0x4a04);
PROVIDE(g_button_irq_cb2_handler = g1_ram_arena + 0x4a08);
PROVIDE(g_button_irq_cb1 = g1_ram_arena + 0x4a10);
PROVIDE(g_button_irq_cb1_handler = g1_ram_arena + 0x4a14);
PROVIDE(g_settings_notify_mutex = g1_ram_arena + 0x4a1c);
PROVIDE(g_ble_conn_ctx_ptr = g1_ram_arena + 0x4a30);
PROVIDE(g_ancs_security_fail_cnt = g1_ram_arena + 0x4a34);
PROVIDE(g_uid_pipe = g1_ram_arena + 0x4a38);
PROVIDE(g_ancs_msgq = g1_ram_arena + 0x4a6c);
PROVIDE(g_ancs_notif_attr_id_latest = g1_ram_arena + 0x4aa0);
PROVIDE(g_ancs_notif_evt_id_latest = g1_ram_arena + 0x4aac);
PROVIDE(g_20006ab2 = g1_ram_arena + 0x4ab2);
PROVIDE(g_gatt_discovery_flags = g1_ram_arena + 0x4ab4);
PROVIDE(g_ancs_active_conn = g1_ram_arena + 0x4ab8);
PROVIDE(g_ancs_discover_params = g1_ram_arena + 0x4abc);
PROVIDE(g_ancs_client = g1_ram_arena + 0x4ae8);
/* RAM-PIN REBIND (iteration 6): these five pins span 0x20007514..0x20007558,
 * which in OUR build is the TOP of `logging_stack` (0x20006d58 + 2048) — i.e.
 * exactly where arch_new_thread puts the log thread's initial exception frame
 * (PSP 0x20007538).  Measured: debug_print+0x4a wrote 1 to 0x20007550, the
 * stacked-PC slot, so the next switch to the log thread resumed at PC=1 and
 * usage-faulted (Renode watchpoint + z_arm_pendsv hook; see
 * recon/emulator/reports/our_boot_bringup.md Iteration 6 §3).
 * Real storage is defined in recon/application/app/src/g1_app_ram_relocs.c. */
PROVIDE(g_bonded_count = g1_bonded_count);
PROVIDE(g_ancs_conn = g1_ancs_conn);
PROVIDE(g_debug_msg_pipe = g1_debug_msg_pipe);
PROVIDE(g_ring_log_pending = g1_ring_log_pending);
PROVIDE(g_log_use_alt_sink = g1_log_use_alt_sink);
PROVIDE(g_dmic_send_fail_cnt = g1_ram_arena + 0x5558);
PROVIDE(g_dmic_send_pos_cnt = g1_ram_arena + 0x555c);
PROVIDE(g_dmic_send_hundreds_cnt = g1_ram_arena + 0x5560);
PROVIDE(g_20007564 = g1_ram_arena + 0x5564);
PROVIDE(g_20007568 = g1_ram_arena + 0x5568);
PROVIDE(g_dashboard_lock_sent_flags = g1_ram_arena + 0x556c);
PROVIDE(g_dashboard_lock_ready_flags = g1_ram_arena + 0x5570);
PROVIDE(g_ble_work_queue = g1_ram_arena + 0x5574);
PROVIDE(g_crc32_table = g1_ram_arena + 0x55a0);
PROVIDE(g_file_msg_pipe = g1_ram_arena + 0x59a0);
PROVIDE(g_200079c4 = g1_ram_arena + 0x59c4);
PROVIDE(g_font_total_size = g1_ram_arena + 0x59d4);
PROVIDE(g_font_buf_len = g1_ram_arena + 0x59d8);
PROVIDE(g_font_flash_write_offset = g1_ram_arena + 0x59dc);
PROVIDE(g_font_crc32 = g1_ram_arena + 0x59e0);
PROVIDE(g_app_language_msgq = g1_ram_arena + 0x59e4);
PROVIDE(g_box_mailbox_synced_flag = g1_ram_arena + 0x59fc);
PROVIDE(g_20007a00 = g1_ram_arena + 0x5a00);
PROVIDE(g_wlcstai_fragment_cursor = g1_ram_arena + 0x5a08);
PROVIDE(g_wlccap_fragment_cursor = g1_ram_arena + 0x5a0c);
PROVIDE(g_20007a04 = g1_ram_arena + 0x5a04);
PROVIDE(g_box_last_seen_uptime = g1_ram_arena + 0x5a10);
PROVIDE(g_st25dv_mailbox_msg = g1_ram_arena + 0x5a14);
PROVIDE(g_box_field_timer = g1_ram_arena + 0x5a24);
PROVIDE(g_elapsed_time_mark = g1_ram_arena + 0x5a28);
PROVIDE(g_box_field_timer_cfg_buf = g1_ram_arena + 0x5a2c);
PROVIDE(g_box_field_raw_timestamp = g1_ram_arena + 0x5a34);
PROVIDE(g_st25dv_dev = g1_ram_arena + 0x5a44);
PROVIDE(g_st25dv_i2c_cfg = g1_ram_arena + 0x5a48);
PROVIDE(g_eeprom_comm_mutex = g1_ram_arena + 0x5a60);
/* RAM-PIN REBIND (iteration 7) — the four .bss companions of the ipc0
 * endpoint registration.  In OUR build 0x20007a74..0x20007a88 is inside
 * `smp_work_queue_stack` (0x200075a0, 2048 B), a live thread stack; the
 * recovered code writes all four (serialization_init sets _ready,
 * serialization_register_endpoint writes ept->instance, and
 * register_ipc_service_context stores the endpoint pointer), so they were
 * corrupting that stack.  Storage in
 * recon/application/app/src/g1_ipc_serialization_objects.c. */
PROVIDE(g_ipc_send_fail_cnt = g1_ipc_send_fail_cnt);
PROVIDE(g_serialization_ipc_ept = g1_serialization_ipc_ept);
PROVIDE(g_serialization_ipc_ready = g1_serialization_ipc_ready);
PROVIDE(g_ipc0_endpoint = g1_ipc0_endpoint);
PROVIDE(g_20007a88 = g1_ram_arena + 0x5a88);
PROVIDE(g_20007a8c = g1_ram_arena + 0x5a8c);
PROVIDE(g_20007a90 = g1_ram_arena + 0x5a90);
PROVIDE(g_20007a94 = g1_ram_arena + 0x5a94);
PROVIDE(g_panel_calib_last_param84 = g1_ram_arena + 0x5a98);
PROVIDE(g_level_calc_input_sl_cache = g1_ram_arena + 0x5a9c);
PROVIDE(g_dashboard_reset_pending_flags = g1_ram_arena + 0x5aa0);
PROVIDE(g_dashboard_lock_pending_flag = g1_ram_arena + 0x5aa4);
PROVIDE(g_app_switch_pending_flag = g1_ram_arena + 0x5aa8);
PROVIDE(g_ble_switch_status_reason = g1_ram_arena + 0x5aac);
PROVIDE(g_20007ab0 = g1_ram_arena + 0x5ab0);
PROVIDE(g_20007ab1 = g1_ram_arena + 0x5ab1);
PROVIDE(g_20007ab4 = g1_ram_arena + 0x5ab4);
PROVIDE(g_20007ab8 = g1_ram_arena + 0x5ab8);
PROVIDE(g_20007abc = g1_ram_arena + 0x5abc);
PROVIDE(g_20007ac0 = g1_ram_arena + 0x5ac0);
PROVIDE(g_20007ac4 = g1_ram_arena + 0x5ac4);
PROVIDE(g_20007ac8 = g1_ram_arena + 0x5ac8);
PROVIDE(g_20007acc = g1_ram_arena + 0x5acc);
PROVIDE(g_20007ad0 = g1_ram_arena + 0x5ad0);
PROVIDE(g_20007ad4 = g1_ram_arena + 0x5ad4);
PROVIDE(g_20007ad8 = g1_ram_arena + 0x5ad8);
PROVIDE(g_20007adc = g1_ram_arena + 0x5adc);
PROVIDE(g_20007ae0 = g1_ram_arena + 0x5ae0);
PROVIDE(g_20007ae4 = g1_ram_arena + 0x5ae4);
PROVIDE(g_20007ae8 = g1_ram_arena + 0x5ae8);
PROVIDE(g_20007aec = g1_ram_arena + 0x5aec);
PROVIDE(g_sw0_irq_low_cnt = g1_ram_arena + 0x5af0);
PROVIDE(g_20007af4 = g1_ram_arena + 0x5af4);
PROVIDE(g_20007af8 = g1_ram_arena + 0x5af8);
PROVIDE(g_20007afc = g1_ram_arena + 0x5afc);
PROVIDE(g_misc_dispatch_ctx = g1_ram_arena + 0x5b00);
PROVIDE(g_touch_key_reset_reason = g1_ram_arena + 0x5b18);
PROVIDE(g_some_module_sem = g1_ram_arena + 0x5b1c);
PROVIDE(g_20007b38 = g1_ram_arena + 0x5b38);
PROVIDE(g_ui_state_mutex = g1_ram_arena + 0x5b3c);
PROVIDE(g_wdt_channel_id = g1_ram_arena + 0x5b50);
PROVIDE(g_ext_flash_mutex = g1_ram_arena + 0x5b54);
PROVIDE(g_ext_flash_dev = g1_ram_arena + 0x5b68);
PROVIDE(g_opt3007_dev = g1_ram_arena + 0x5b6c);
PROVIDE(g_20007b70 = g1_ram_arena + 0x5b70);
PROVIDE(g_20007b74 = g1_ram_arena + 0x5b74);
PROVIDE(g_pending_event_word = g1_ram_arena + 0x5b78);
PROVIDE(g_dmic_msgq = g1_ram_arena + 0x5b7c);
PROVIDE(g_atomic_scratch_20007bb0 = g1_ram_arena + 0x5bb0);
PROVIDE(g_20007bb4 = g1_ram_arena + 0x5bb4);
PROVIDE(g_20007bb8 = g1_ram_arena + 0x5bb8);
PROVIDE(g_20007bbc = g1_ram_arena + 0x5bbc);
PROVIDE(g_pt_nfc_link_cfg = g1_ram_arena + 0x5bc0);
PROVIDE(g_pt_nfc_link_attr_0x4414_cache = g1_ram_arena + 0x5bc4);
PROVIDE(g_pt_nfc_link_ready_flag = g1_ram_arena + 0x5bc8);
PROVIDE(g_pt_nfc_link_ready = g1_ram_arena + 0x5bcc);
PROVIDE(g_20007bd4 = g1_ram_arena + 0x5bd4);
PROVIDE(g_periodic_check_last_uptime_ms = g1_ram_arena + 0x5bf0);
PROVIDE(g_esb_notify_ring_staging_buf = g1_ram_arena + 0x5bf4);
PROVIDE(g_ancs_notify_rx_buf = g1_ram_arena + 0x5da8);
/* RAM-PIN REBIND (iteration 10): the 20-slot message pool.  `msg_queue_init`
 * (0x33c5c) memsets 20 x 436 = 8720 B from g_message_pool, i.e. the original
 * range 0x20007dac..0x20009fbc.  In OUR build that window covers six live
 * Zephyr objects (smp_work_queue_stack, bt_lw_stack_area,
 * _k_mem_slab_buf_chan_slab, z_interrupt_stacks, z_idle_stacks, z_main_stack).
 * Measured: memset(0x20008d00, 0, 436) from msg_queue_init+0x1c zeroed the
 * idle thread's stack, so the next z_arm_pendsv restored PC = 0 and the boot
 * usage-faulted at 0.048 s (Renode byte-watchpoint + memset hook; see
 * recon/emulator/reports/our_boot_bringup.md Iteration 10 §A).
 * The other three pins are interior views of the same pool and are rebound at
 * their original relative offsets.  Storage:
 * recon/application/app/src/g1_app_ram_relocs.c (group 3). */
PROVIDE(g_message_pool = g1_message_pool);
PROVIDE(g_notif_app_pkg_table_buf = g1_message_pool + 0x10);
PROVIDE(g_message_table_mirror = g1_message_pool + 0x1108);
PROVIDE(g_message_table_mirror_ovfl_slot = g1_message_pool + 0x205c);
PROVIDE(g_whitelist_app_parse_buf = g1_ram_arena + 0x7fbc);
PROVIDE(g_misc_last_uptime_ms = g1_ram_arena + 0x7fc0);
PROVIDE(g_pixel4bit_bitpos = g1_ram_arena + 0x7fc4);
PROVIDE(g_pixel4bit_row_buf_off = g1_ram_arena + 0x7fc8);
PROVIDE(g_pixel4bit_row_buf = g1_ram_arena + 0x7fcc);
PROVIDE(g_dashboard_reflash_frame_idx = g1_ram_arena + 0x7fd0);
PROVIDE(g_20009fd4 = g1_ram_arena + 0x7fd4);
PROVIDE(g_even_ai_frame_idx = g1_ram_arena + 0x7fd8);
PROVIDE(g_20009fdc = g1_ram_arena + 0x7fdc);
PROVIDE(g_20009fe0 = g1_ram_arena + 0x7fe0);
PROVIDE(g_20009fe4 = g1_ram_arena + 0x7fe4);
PROVIDE(g_20009fe8 = g1_ram_arena + 0x7fe8);
PROVIDE(g_20009fec = g1_ram_arena + 0x7fec);
PROVIDE(g_20009ff0 = g1_ram_arena + 0x7ff0);
PROVIDE(g_20009ff4 = g1_ram_arena + 0x7ff4);
PROVIDE(g_imu_pitch_render_state0 = g1_ram_arena + 0x8018);
PROVIDE(g_imu_pitch_render_state1 = g1_ram_arena + 0x801c);
PROVIDE(g_imu_pitch_render_state2 = g1_ram_arena + 0x8020);
PROVIDE(g_imu_pitch_render_state3 = g1_ram_arena + 0x8024);
PROVIDE(g_imu_pitch_render_state4 = g1_ram_arena + 0x8028);
PROVIDE(g_imu_pitch_render_state5 = g1_ram_arena + 0x802c);
PROVIDE(g_gui_canvas_flags = g1_ram_arena + 0x8030);
PROVIDE(g_gui_active_canvas = g1_ram_arena + 0x8034);
PROVIDE(g_even_ai_render_state = g1_ram_arena + 0x8038);
PROVIDE(g_panel_reg_y_cache = g1_ram_arena + 0x8058);
PROVIDE(g_panel_reg_x_cache = g1_ram_arena + 0x805c);
PROVIDE(g_projector_bus_lock = g1_ram_arena + 0x8060);
PROVIDE(g_panel_spi_id = g1_ram_arena + 0x8074);
PROVIDE(g_2000a078 = g1_ram_arena + 0x8078);
PROVIDE(g_2000a07c = g1_ram_arena + 0x807c);
PROVIDE(g_2000a080 = g1_ram_arena + 0x8080);
PROVIDE(g_2000a084 = g1_ram_arena + 0x8084);
PROVIDE(g_2000a088 = g1_ram_arena + 0x8088);
PROVIDE(g_2000a08c = g1_ram_arena + 0x808c);
PROVIDE(g_proxy_thread_id = g1_ram_arena + 0x8090);
PROVIDE(g_delayexitvalue = g1_ram_arena + 0x8094);
PROVIDE(g_2000a098 = g1_ram_arena + 0x8098);
PROVIDE(g_display_thread_id = g1_ram_arena + 0x809c);
PROVIDE(g_progress_tick_ms = g1_ram_arena + 0x80a0);
PROVIDE(g_boot_uptime_s = g1_ram_arena + 0x80b0);
PROVIDE(g_analytics_evt_tick_buf = g1_ram_arena + 0x80b4);
PROVIDE(g_2000a0c8 = g1_ram_arena + 0x80c8);
PROVIDE(g_log_msg_pool_ptr = g1_ram_arena + 0x80cc);
PROVIDE(g_2000a0d0 = g1_ram_arena + 0x80d0);
PROVIDE(log_backend_count = g1_ram_arena + 0x80d4);
PROVIDE(log_buffered_cnt = g1_ram_arena + 0x80d8);
PROVIDE(z_log_process_guard = g1_ram_arena + 0x80dc);
PROVIDE(g_2000a0e0 = g1_ram_arena + 0x80e0);
PROVIDE(g_2000a0e4 = g1_ram_arena + 0x80e4);
PROVIDE(g_settings_nvs_backend = g1_ram_arena + 0x8100);
PROVIDE(g_settings_stores = g1_ram_arena + 0x8104);
PROVIDE(g_settings_handlers = g1_ram_arena + 0x810c);
PROVIDE(g_settings_nvs_default_backend = g1_ram_arena + 0x8114);
PROVIDE(cur_service_val = g1_ram_arena + 0x8154);
PROVIDE(g_gatt_dm_context = g1_ram_arena + 0x8158);
PROVIDE(g_gatt_dm_discover_params_uuid = g1_ram_arena + 0x815c);
PROVIDE(g_gatt_dm_discover_params_func = g1_ram_arena + 0x8160);
PROVIDE(g_gatt_dm_discover_params_start_handle = g1_ram_arena + 0x8164);
PROVIDE(g_gatt_dm_discover_params_end_handle = g1_ram_arena + 0x816a);
PROVIDE(g_gatt_dm_discover_params_type = g1_ram_arena + 0x816c);
PROVIDE(g_gatt_dm_attr_count = g1_ram_arena + 0x8288);
PROVIDE(g_gatt_dm_in_progress_flag = g1_ram_arena + 0x828c);
PROVIDE(g_gatt_dm_svc_uuid_buf = g1_ram_arena + 0x8290);
PROVIDE(g_gatt_dm_chunk_list_head = g1_ram_arena + 0x82a4);
PROVIDE(g_gatt_dm_chunk_list_tail = g1_ram_arena + 0x82a8);
PROVIDE(g_gatt_dm_chunk_used_len = g1_ram_arena + 0x82ac);
PROVIDE(g_gatt_dm_svc_range_end = g1_ram_arena + 0x82b0);
PROVIDE(g_gatt_dm_has_uuid_flag = g1_ram_arena + 0x82b4);
PROVIDE(g_2000a2b8 = g1_ram_arena + 0x82b8);
/* RAM-PIN REBIND (iteration 7) — Application Event Manager state.  These two
 * pins land inside `z_main_stack` in our build, and the k_work they go with
 * (g_20002838, rebound below) lands inside nrfx_gpiote's `.data.m_cb`.
 * Storage: recon/application/app/src/g1_app_ram_relocs.c (group 2). */
PROVIDE(g_notify_pending_lock = g1_notify_pending_lock);
PROVIDE(g_notify_pending_slist = g1_notify_pending_slist);
PROVIDE(g_notify_pending_flags_bitmap = g1_notify_pending_flags_bitmap);
PROVIDE(g_arm_mpu_dynamic_regions_tbl = g1_ram_arena + 0x87f4);
PROVIDE(g_heap_brk = g1_ram_arena + 0x8808);
PROVIDE(g_mgmt_group_list_head = g1_ram_arena + 0x894c);
PROVIDE(g_img_mgmt_flash_area = g1_ram_arena + 0x8954);
PROVIDE(g_img_mgmt_active_slot = g1_ram_arena + 0x8b7c);
PROVIDE(img_mgmt_state = g1_ram_arena + 0x8b80);
PROVIDE(g_img_mgmt_flash_area_align = g1_ram_arena + 0x8b88);
PROVIDE(g_misc_kobj_abac = g1_ram_arena + 0x8bac);
PROVIDE(bt_hci_cmd_data = g1_ram_arena + 0x8bf4);
PROVIDE(ready_cb = g1_ram_arena + 0x8c6c);
PROVIDE(g_bt_dh_key_cb = g1_ram_arena + 0x8c70);
PROVIDE(g_bt_pub_key_cb_slist = g1_ram_arena + 0x8c74);
PROVIDE(g_bt_conn_pool = g1_ram_arena + 0x8c7c);
PROVIDE(g_ble_conn_cb_list_head = g1_ram_arena + 0x8d1c);
PROVIDE(g_bt_conn_auth_info_cb_list = g1_ram_arena + 0x8d20);
PROVIDE(auth_info_cbs = g1_ram_arena + 0x8d24);
PROVIDE(g_bt_conn_auth_cb = g1_ram_arena + 0x8d28);
PROVIDE(g_2000ad2c = g1_ram_arena + 0x8d2c);
PROVIDE(l2cap_tx_meta_data_storage = g1_ram_arena + 0x8d34);
PROVIDE(g_bt_gatt_indicate_ctx_pool = g1_ram_arena + 0x8dd4);
PROVIDE(att_handle_rsp_thread = g1_ram_arena + 0x8e9c);
PROVIDE(cancel_req = g1_ram_arena + 0x8ea0);
PROVIDE(g_bt_gatt_cf_cfg = g1_ram_arena + 0x8ed4);
PROVIDE(g_2000aed5 = g1_ram_arena + 0x8ed5);
PROVIDE(gatt_service_init_guard = g1_ram_arena + 0x8f04);
PROVIDE(g_bt_gatt_dynamic_db = g1_ram_arena + 0x8f08);
PROVIDE(g_2000af0c = g1_ram_arena + 0x8f0c);
PROVIDE(g_bt_gatt_callback_list_head = g1_ram_arena + 0x8f10);
PROVIDE(g_2000af14 = g1_ram_arena + 0x8f14);
PROVIDE(g_known_device_table = g1_ram_arena + 0x8f18);
PROVIDE(g_known_device_table_addr0 = g1_ram_arena + 0x8f19);
PROVIDE(g_smp_local_public_key = g1_ram_arena + 0x8f48);
PROVIDE(bt_keys_pool = g1_ram_arena + 0x8f4c);
PROVIDE(g_bt_keys_pool_entry0_addr = g1_ram_arena + 0x8f4d);
PROVIDE(bt_keys_pool_0_irk = g1_ram_arena + 0x8f76);
PROVIDE(bt_keys_pool_1 = g1_ram_arena + 0x8fa8);
PROVIDE(g_bt_keys_pool_entry1_addr = g1_ram_arena + 0x8fa9);
PROVIDE(bt_keys_pool_1_irk = g1_ram_arena + 0x8fd2);
PROVIDE(bt_keys_pool_1_addr = g1_ram_arena + 0x8fe2);
PROVIDE(g_net_buf_slist_lock = g1_ram_arena + 0x9004);
PROVIDE(g_pdm_mic_ctrl_blk = g1_ram_arena + 0x9008);
PROVIDE(g_pdm_mic_rx_msgq = g1_ram_arena + 0x9024);
PROVIDE(g_2000b084 = g1_ram_arena + 0x9084);
PROVIDE(g_2000b094 = g1_ram_arena + 0x9094);
PROVIDE(g_2000b0b8 = g1_ram_arena + 0x90b8);
PROVIDE(g_2000b154 = g1_ram_arena + 0x9154);
PROVIDE(g_gpio_pin_latch_mask = g1_ram_arena + 0x92d0);
PROVIDE(nrf_rtc_timer_free_channels = g1_ram_arena + 0x92d4);
PROVIDE(g_gpio_pin_enabled_mask = g1_ram_arena + 0x92d8);
PROVIDE(g_uptime_tick_overflow_state = g1_ram_arena + 0x92dc);
PROVIDE(g_ancs_notify_slot_table = g1_ram_arena + 0x9308);
PROVIDE(g_caf_power_manager_wake_evt_cnt = g1_ram_arena + 0x9310);
PROVIDE(g_2000b314 = g1_ram_arena + 0x9314);
PROVIDE(g_clock_cb = g1_ram_arena + 0x931c);
PROVIDE(nrfx_clock_module_initialized = g1_ram_arena + 0x9320);
PROVIDE(g_nrfx_hal_init_flag = g1_ram_arena + 0x9324);
PROVIDE(g_nrfx_gpiote_init_flag = g1_ram_arena + 0x9328);
PROVIDE(g_nrfx_gpiote_init_ctx = g1_ram_arena + 0x932c);
PROVIDE(g_pdm_cb = g1_ram_arena + 0x9330);
PROVIDE(nrfx_pdm_drv_state = g1_ram_arena + 0x9340);
PROVIDE(nrfx_pdm_state = g1_ram_arena + 0x9341);
PROVIDE(g_qspi_cb = g1_ram_arena + 0x9348);
PROVIDE(g_qspi_drv_state = g1_ram_arena + 0x9378);
PROVIDE(g_qspi_skip_activate_flag = g1_ram_arena + 0x9380);
PROVIDE(g_nrfx_spim_cb = g1_ram_arena + 0x9384);
PROVIDE(g_nrfx_twim_cb = g1_ram_arena + 0x93cc);
PROVIDE(m_dppi_channels = g1_ram_arena + 0x941c);
PROVIDE(g_metal_generic_bus = g1_ram_arena + 0x9424);
PROVIDE(metal_log_handler = g1_ram_arena + 0x9428);
PROVIDE(_kernel = g1_ram_arena + 0x9448);
/* iteration 12: interior views of the real linked `_kernel` (original base
 * 0x2000b448, size 0x28 == struct z_kernel).  The arena binding pointed the
 * recovered scheduler at dead storage while the STOCK sched.c code used the
 * real _kernel, so unready_thread() unlinked from an empty private runq and
 * the sleeping thread was never actually removed from the ready queue --
 * z_tick_sleep then asserted _THREAD_SUSPENDED after z_swap returned.
 *   +0x08 cpus[0].current   +0x10 cpus[0].id   +0x1c ready_q.runq
 * Iteration 12 measured `g_current_thread_ptr` alone and REVERTED it because it
 * unmasked a CC312-PAL/AES livelock.  Iteration 13 root-caused that livelock to
 * `sys_rand32_get` (FUN_00052c40) dropping the `length = 4` register argument at
 * its call to `entropy_get_entropy_isr_call` (FUN_00052bf8) -- the original does
 * `movs r1,#4 ; add.w r0,sp,r1 ; bl 0x52bf8` at 0x52c68.  With that fixed the two
 * land together. */
PROVIDE(g_current_thread_ptr = _kernel + 0x8);
PROVIDE(g_spinlock_validate_owner = _kernel + 0x10);
PROVIDE(g_sched_ready_runq = _kernel + 0x1c);
PROVIDE(mutex_spinlock_b470 = g1_ram_arena + 0x9470);
PROVIDE(g_mutex_lock_spinlock = g1_ram_arena + 0x9474);
PROVIDE(g_2000b478 = g1_ram_arena + 0x9478);
PROVIDE(timer_spinlock = g1_ram_arena + 0x9480);
PROVIDE(g_pend_locked_thread_tmp = g1_ram_arena + 0x9484);
PROVIDE(g_sched_ready_runq_prio_cache = g1_ram_arena + 0x9488);
PROVIDE(g_sched_ready_runq_nonempty_flag = g1_ram_arena + 0x948c);
PROVIDE(sched_spinlock = g1_ram_arena + 0x9490);
PROVIDE(g_rtc_elapsed_calc_disabled_flag = g1_ram_arena + 0x9494);
PROVIDE(g_timeout_list_spinlock = g1_ram_arena + 0x9498);
PROVIDE(poll_spinlock = g1_ram_arena + 0x94a0);
PROVIDE(g_batt_soc_curve_interp_buf = g1_ram_arena + 0x94a4);
PROVIDE(g_batt_soc_curve_val_hi = g1_ram_arena + 0x94ec);
PROVIDE(g_batt_soc_curve_val_lo = g1_ram_arena + 0x94f0);
PROVIDE(g_malloc_sbrk_start = g1_ram_arena + 0xac1c);
PROVIDE(g_malloc_free_list = g1_ram_arena + 0xac20);
PROVIDE(g_errno = g1_ram_arena + 0xac24);
PROVIDE(g_pkcs7_rx_msg_id = g1_ram_arena + 0xb6f0);
PROVIDE(g_pkcs7_rx_offset = g1_ram_arena + 0xb6f2);
PROVIDE(g_pkcs7_pack_offset = g1_ram_arena + 0xb6f4);
PROVIDE(g_2000d716 = g1_ram_arena + 0xb716);
PROVIDE(g_2000f6e4 = g1_ram_arena + 0xd6e4);
PROVIDE(g_esb_sync_last_result = g1_ram_arena + 0xd6e6);
PROVIDE(g_2000f6ec = g1_ram_arena + 0xd6ec);
PROVIDE(g_gui_dynbmp_cycle_count = g1_ram_arena + 0xd6fe);
PROVIDE(g_gui_dynbmp_frame_index = g1_ram_arena + 0xd700);
PROVIDE(g_gui_dynbmp_frame_limit = g1_ram_arena + 0xd702);
PROVIDE(g_utf16_conv_buf = g1_ram_arena + 0xd704);
PROVIDE(g_2000ff04 = g1_ram_arena + 0xdf04);
PROVIDE(g_bt_hci_pending_opcode = g1_ram_arena + 0xdf06);
PROVIDE(g_bt_hci_acl_frag_conn_handle = g1_ram_arena + 0xdf08);
PROVIDE(sc_range = g1_ram_arena + 0xdf14);
PROVIDE(sc_cfg = g1_ram_arena + 0xdf18);
/* iteration 12: NOT rebound.  The 0x2000ff18/+1 pair really is an interior
 * view, but gatt.c's `sc_cfg` is a FILE-LOCAL static (nm: `b`), so no
 * linker-script reference can reach it -- the iteration-11 class (b)
 * limitation.  Both stay in the arena, which keeps their mutual offset. */
PROVIDE(g_bt_gatt_sc_cfg_addr_ff19 = g1_ram_arena + 0xdf19);
PROVIDE(last_static_handle = g1_ram_arena + 0xdf3c);
PROVIDE(g_change_work_mode_busy = g1_ram_arena + 0xdf4b);
PROVIDE(g_notify_wakeup_msg_sync_flag = g1_ram_arena + 0xdf4d);
PROVIDE(g_2000ff4e = g1_ram_arena + 0xdf4e);
PROVIDE(g_runtime_mode_flag = g1_ram_arena + 0xdf6e);
PROVIDE(g_ble_indicate_sc_retry_count = g1_ram_arena + 0xdf70);
PROVIDE(g_ancs_attr_data_pending = g1_ram_arena + 0xdf71);
PROVIDE(g_2000ff72 = g1_ram_arena + 0xdf72);
PROVIDE(g_2000ff73 = g1_ram_arena + 0xdf73);
PROVIDE(g_2000ff87 = g1_ram_arena + 0xdf87);
PROVIDE(g_2000ffa7 = g1_ram_arena + 0xdfa7);
PROVIDE(g_debug_msg_scratch_buf = g1_ram_arena + 0xe257);
PROVIDE(g_pkcs7_rx_cmd_id = g1_ram_arena + 0xe31f);
PROVIDE(g_pkcs7_pack_cmd_id = g1_ram_arena + 0xe320);
PROVIDE(g_dmic_msg_seq = g1_ram_arena + 0xe321);
PROVIDE(g_20010322 = g1_ram_arena + 0xe322);
PROVIDE(g_20010323 = g1_ram_arena + 0xe323);
PROVIDE(g_20010324 = g1_ram_arena + 0xe324);
PROVIDE(g_20010325 = g1_ram_arena + 0xe325);
PROVIDE(g_20010326 = g1_ram_arena + 0xe326);
PROVIDE(g_2001046a = g1_ram_arena + 0xe46a);
PROVIDE(g_200107e3 = g1_ram_arena + 0xe7e3);
PROVIDE(g_2001197a = g1_ram_arena + 0xf97a);
PROVIDE(g_200119ba = g1_ram_arena + 0xf9ba);
PROVIDE(g_200119da = g1_ram_arena + 0xf9da);
PROVIDE(g_20011d81 = g1_ram_arena + 0xfd81);
PROVIDE(g_20011d82 = g1_ram_arena + 0xfd82);
PROVIDE(g_20013dea = g1_ram_arena + 0x11dea);
PROVIDE(g_20015e52 = g1_ram_arena + 0x13e52);
PROVIDE(g_font_write_buf = g1_ram_arena + 0x15062);
PROVIDE(g_ui_mode_flag = g1_ram_arena + 0x16462);
PROVIDE(g_20018463 = g1_ram_arena + 0x16463);
PROVIDE(g_quicknote_flash_page_buf = g1_ram_arena + 0x16465);
PROVIDE(g_20018c65 = g1_ram_arena + 0x16c65);
PROVIDE(g_20018c66 = g1_ram_arena + 0x16c66);
PROVIDE(g_wlc_fragment_staging_byte = g1_ram_arena + 0x16c67);
PROVIDE(g_box_present_flag = g1_ram_arena + 0x16c68);
PROVIDE(g_board_rev_flag = g1_ram_arena + 0x16c69);
PROVIDE(g_ndef_build_status_flag = g1_ram_arena + 0x16c6a);
PROVIDE(g_level_calc_input_b_cache = g1_ram_arena + 0x16c6b);
PROVIDE(g_20018c6c = g1_ram_arena + 0x16c6c);
PROVIDE(g_20018c6d = g1_ram_arena + 0x16c6d);
PROVIDE(g_20018c6e = g1_ram_arena + 0x16c6e);
PROVIDE(g_esb_seg_tx_frame_opcode = g1_ram_arena + 0x16c6f);
PROVIDE(g_esb_seg_tx_frame_payload = g1_ram_arena + 0x16c71);
PROVIDE(g_esb_seg_ack_echo_buf = g1_ram_arena + 0x16d6b);
PROVIDE(g_esb_notify_sync_retry_cnt = g1_ram_arena + 0x16d82);
PROVIDE(g_bind_status_log_debounce_cnt = g1_ram_arena + 0x16d83);
PROVIDE(g_box_state_debounce_cnt = g1_ram_arena + 0x16d84);
PROVIDE(g_glassbox_status_debounce_cnt = g1_ram_arena + 0x16d85);
PROVIDE(g_nfc_link_retry_cnt = g1_ram_arena + 0x16d86);
PROVIDE(g_wear_state_debounce_cnt = g1_ram_arena + 0x16d87);
PROVIDE(g_misc_dispatch_pending_flag = g1_ram_arena + 0x16d88);
PROVIDE(g_touch_key_press_active = g1_ram_arena + 0x16d89);
PROVIDE(g_some_module_init_done_flag = g1_ram_arena + 0x16d8a);
PROVIDE(g_suspend_pending_flag = g1_ram_arena + 0x16d8b);
PROVIDE(g_esb_seg_tx_lock_flag = g1_ram_arena + 0x16d8c);
PROVIDE(g_new_notification_pending_flag = g1_ram_arena + 0x16d8d);
PROVIDE(g_msg_queue_busy = g1_ram_arena + 0x16d8e);
PROVIDE(g_esb_sync_tx_busy_flag = g1_ram_arena + 0x16d8f);
PROVIDE(g_flash_crc_skip_watchdog_flag = g1_ram_arena + 0x16d90);
PROVIDE(g_box_lid_or_charge_state = g1_ram_arena + 0x16d91);
PROVIDE(g_wear_off_confirm_cnt = g1_ram_arena + 0x16d92);
PROVIDE(onboarding_pending_flag = g1_ram_arena + 0x16d93);
PROVIDE(g_low_power_mode_enabled = g1_ram_arena + 0x16d94);
PROVIDE(g_20018d95 = g1_ram_arena + 0x16d95);
PROVIDE(g_20018d96 = g1_ram_arena + 0x16d96);
PROVIDE(g_notify_wakeup_delay_flag = g1_ram_arena + 0x16d97);
PROVIDE(g_esb_notify_sync_substate = g1_ram_arena + 0x16d98);
PROVIDE(g_ble_xfer_seq_prev = g1_ram_arena + 0x16d99);
PROVIDE(g_ble_xfer_seq_cur = g1_ram_arena + 0x16d9a);
PROVIDE(g_ble_dispatch_pending_marker = g1_ram_arena + 0x16d9b);
PROVIDE(g_persist_task_status_lock = g1_ram_arena + 0x16d9c);
PROVIDE(g_persist_task_status = g1_ram_arena + 0x16d9d);
PROVIDE(g_pending_message_flag = g1_ram_arena + 0x16d9e);
PROVIDE(g_esb_notify_slave_role_guard = g1_ram_arena + 0x16d9f);
PROVIDE(g_battery_level_bucket = g1_ram_arena + 0x16da0);
PROVIDE(g_opt3007_chip_ready = g1_ram_arena + 0x16da1);
PROVIDE(g_20018da2 = g1_ram_arena + 0x16da2);
PROVIDE(g_confirmed_state_flag_2 = g1_ram_arena + 0x16da3);
PROVIDE(g_confirmed_state_flag_1 = g1_ram_arena + 0x16da4);
PROVIDE(g_ancs_inbox_flag_cached = g1_ram_arena + 0x16da5);
PROVIDE(g_ancs_inbox_flag_current = g1_ram_arena + 0x16da6);
PROVIDE(g_lid_closed_flag = g1_ram_arena + 0x16da7);
PROVIDE(g_charging_flag = g1_ram_arena + 0x16da8);
PROVIDE(g_20018da9 = g1_ram_arena + 0x16da9);
PROVIDE(g_voice_block_dir_buf = g1_ram_arena + 0x16daa);
PROVIDE(g_20019daa = g1_ram_arena + 0x17daa);
PROVIDE(g_audio_stream_mgr_busy_flag = g1_ram_arena + 0x17dab);
PROVIDE(g_touch_key_irq_line_status = g1_ram_arena + 0x17dac);
PROVIDE(g_pt_nfc_link_busy = g1_ram_arena + 0x17dad);
PROVIDE(g_fuel_gauge_poll_stop_flag = g1_ram_arena + 0x17dae);
PROVIDE(g_flash_info = g1_ram_arena + 0x17daf);
PROVIDE(g_periodic_check_fail_cnt = g1_ram_arena + 0x17ef0);
PROVIDE(g_aging_mode_thread_started_flag = g1_ram_arena + 0x17ef1);
PROVIDE(g_click_dispatch_flag = g1_ram_arena + 0x17ef2);
PROVIDE(g_test_mode_flag = g1_ram_arena + 0x17ef3);
PROVIDE(g_glassbox_charge_status_byte = g1_ram_arena + 0x17ef4);
PROVIDE(g_pt_msg_encode_buf = g1_ram_arena + 0x17ef5);
PROVIDE(g_system_19ff5 = g1_ram_arena + 0x17ff5);
PROVIDE(g_pt_status_msg_buf = g1_ram_arena + 0x180f5);
PROVIDE(g_serial_port_ready = g1_ram_arena + 0x18127);
PROVIDE(g_uart_rx_frame_len = g1_ram_arena + 0x18128);
PROVIDE(g_uart_rx_frame_buf = g1_ram_arena + 0x18129);
PROVIDE(g_2001a12d = g1_ram_arena + 0x1812d);
PROVIDE(g_message_pending_state = g1_ram_arena + 0x18229);
PROVIDE(g_message_pool_index = g1_ram_arena + 0x1822a);
PROVIDE(g_message_table_slot_count = g1_ram_arena + 0x1822b);
PROVIDE(g_app_whitelist_buffer = g1_ram_arena + 0x1822c);
PROVIDE(g_on_whitelist_by_identifier = g1_ram_arena + 0x1822d);
PROVIDE(g_new_message_pending_flag = g1_ram_arena + 0x1980e);
PROVIDE(g_dashboard_close_pending = g1_ram_arena + 0x1980f);
PROVIDE(g_display_page_index = g1_ram_arena + 0x19810);
PROVIDE(g_display_page_dirty_flag = g1_ram_arena + 0x19811);
PROVIDE(g_2001b812 = g1_ram_arena + 0x19812);
PROVIDE(g_2001b813 = g1_ram_arena + 0x19813);
PROVIDE(g_news_widget_index_raw = g1_ram_arena + 0x19814);
PROVIDE(g_stocks_widget_index_raw = g1_ram_arena + 0x19815);
PROVIDE(g_widget0_index_raw = g1_ram_arena + 0x19816);
PROVIDE(g_quicknote_hint_shown = g1_ram_arena + 0x19817);
PROVIDE(g_even_ai_line_text_buf = g1_ram_arena + 0x19818);
PROVIDE(g_even_ai_active_flag = g1_ram_arena + 0x199a8);
PROVIDE(g_not_disturb_settings = g1_ram_arena + 0x199aa);
PROVIDE(g_even_ai_mic_icon_visible = g1_ram_arena + 0x199ab);
PROVIDE(g_buf_2001b9ac = g1_ram_arena + 0x199ac);
PROVIDE(g_2001ba2c = g1_ram_arena + 0x19a2c);
PROVIDE(g_2001ba2d = g1_ram_arena + 0x19a2d);
PROVIDE(g_buf_2001ba2e = g1_ram_arena + 0x19a2e);
PROVIDE(g_2001c336 = g1_ram_arena + 0x1a336);
PROVIDE(g_2001cc3e = g1_ram_arena + 0x1ac3e);
PROVIDE(onboarding_secondary_reset_flag = g1_ram_arena + 0x1adce);
PROVIDE(g_onboarding_primary_reset_flag = g1_ram_arena + 0x1adcf);
PROVIDE(g_2001cdd0 = g1_ram_arena + 0x1add0);
PROVIDE(onboarding_retry_counter = g1_ram_arena + 0x1add1);
PROVIDE(onboarding_attempt_counter = g1_ram_arena + 0x1add2);
PROVIDE(onboarding_watchdog_active_flag = g1_ram_arena + 0x1add3);
PROVIDE(g_gui_dark_light_flag = g1_ram_arena + 0x1add4);
PROVIDE(g_even_ai_render_state_init_val = g1_ram_arena + 0x1add7);
PROVIDE(g_glyph_bitmap_cache_buf = g1_ram_arena + 0x1ae57);
PROVIDE(g_imu_pitch_task_state = g1_ram_arena + 0x1af8f);
PROVIDE(g_imu_pitch_last_state = g1_ram_arena + 0x1af91);
PROVIDE(g_chinese_glyph_bitmap_buf = g1_ram_arena + 0x1af92);
PROVIDE(g_icon_bitmap_buf = g1_ram_arena + 0x1b142);
PROVIDE(g_2001d262 = g1_ram_arena + 0x1b262);
PROVIDE(g_2001d263 = g1_ram_arena + 0x1b263);
PROVIDE(g_2001d264 = g1_ram_arena + 0x1b264);
PROVIDE(g_2001d26a = g1_ram_arena + 0x1b26a);
PROVIDE(g_2001d26e = g1_ram_arena + 0x1b26e);
PROVIDE(g_2001d34a = g1_ram_arena + 0x1b34a);
PROVIDE(g_2001d34b = g1_ram_arena + 0x1b34b);
PROVIDE(g_2001d431 = g1_ram_arena + 0x1b431);
PROVIDE(g_2001d432 = g1_ram_arena + 0x1b432);
PROVIDE(g_display_reflash_pending = g1_ram_arena + 0x1b446);
PROVIDE(g_2001d447 = g1_ram_arena + 0x1b447);
PROVIDE(g_analytics_evt_hist_ready = g1_ram_arena + 0x1b449);
PROVIDE(g_analytics_evt_buf_idx = g1_ram_arena + 0x1b44a);
PROVIDE(log_process_active = g1_ram_arena + 0x1b44b);
PROVIDE(g_log_initialized_flag = g1_ram_arena + 0x1b44c);
PROVIDE(log_output_flush_done = g1_ram_arena + 0x1b44e);
PROVIDE(g_arm_mpu_static_regions_num = g1_ram_arena + 0x1b450);
PROVIDE(g_smp_pairing_event_cnt = g1_ram_arena + 0x1b531);
PROVIDE(g_bt_settings_load_done = g1_ram_arena + 0x1b532);
PROVIDE(g_smp_pair_method_unbonded = g1_ram_arena + 0x1b533);
PROVIDE(g_smp_pair_method_bonded = g1_ram_arena + 0x1b534);
PROVIDE(g_qspi_nor_initialized = g1_ram_arena + 0x1b535);
PROVIDE(g_caf_power_manager_system_off_flag = g1_ram_arena + 0x1b563);
PROVIDE(g_tx_yield_allowed_flag = g1_ram_arena + 0x1b564);
PROVIDE(g_percpu_timeout_abort_flag = g1_ram_arena + 0x1b565);
PROVIDE(g_ancs_work_thread_stack = g1_ram_arena + 0x1b568);
PROVIDE(g_ble_work_thread_stack = g1_ram_arena + 0x1c968);
PROVIDE(g_flash_ops_thread_stack = g1_ram_arena + 0x1f968);
PROVIDE(g_brightness_thread_stack = g1_ram_arena + 0x20168);
/* iteration 13: imu_fusion_init's k_thread_create operands (0x260c2).
 * The stack top 0x20023568 + 0x700 == 0x20023c68 is already pinned below as
 * g_20023c68, which corroborates the size. */
PROVIDE(g_imu_fusion_thread_stack = g1_ram_arena + 0x21568);
PROVIDE(g_20023c68 = g1_ram_arena + 0x21c68);
PROVIDE(g_20024868 = g1_ram_arena + 0x22868);
PROVIDE(g_20024c68 = g1_ram_arena + 0x22c68);
PROVIDE(g_20025068 = g1_ram_arena + 0x23068);
PROVIDE(g_20025468 = g1_ram_arena + 0x23468);
PROVIDE(g_20025a68 = g1_ram_arena + 0x23a68);
PROVIDE(g_20026268 = g1_ram_arena + 0x24268);
PROVIDE(g_20026a68 = g1_ram_arena + 0x24a68);
PROVIDE(g_aging_mode_aux_thread_stack = g1_ram_arena + 0x25668);
PROVIDE(g_aging_mode_thread_stack = g1_ram_arena + 0x25a68);
PROVIDE(g_proxy_thread_stack = g1_ram_arena + 0x26668);
PROVIDE(g_display_thread_stack_buf = g1_ram_arena + 0x26e68);
PROVIDE(rx_thread_stack = 0x2002bb80);
PROVIDE(bt_workqueue_stack = 0x2002bf80);
PROVIDE(g_dashboard_startup_mode_info_defaults = 0x2007fc00);
PROVIDE(g_all_static_info_fc04 = 0x2007fc04);
PROVIDE(g_dashboard_startup_mode_info_field_05 = 0x2007fc05);
PROVIDE(g_all_static_info_fc08 = 0x2007fc08);
PROVIDE(g_all_static_info_fc0c = 0x2007fc0c);
PROVIDE(g_all_static_info = 0x2007fc10);
PROVIDE(g_dashboard_startup_mode_info_field_14 = 0x2007fc14);
PROVIDE(g_dashboard_startup_mode_info_field_18 = 0x2007fc18);
PROVIDE(g_dashboard_startup_mode_info_field_1c = 0x2007fc1c);
PROVIDE(g_all_static_info_fc35 = 0x2007fc35);
PROVIDE(g_dashboard_startup_mode_info_field_39 = 0x2007fc39);
PROVIDE(g_all_static_info_fc5f = 0x2007fc5f);
PROVIDE(g_all_static_info_fc60 = 0x2007fc60);
PROVIDE(g_dashboard_startup_mode_info_field_61 = 0x2007fc61);
PROVIDE(g_all_static_info_fc62 = 0x2007fc62);
PROVIDE(g_all_static_info_fc68 = 0x2007fc68);
PROVIDE(g_dashboard_default_widget0_index = 0x2007fc69);
PROVIDE(g_2007fc70 = 0x2007fc70);

/* Absolute-address back-map pins omitted by the symbol_map that seeded this
 * generated file (a symbol_map coverage gap, not a rename artifact). Each is a
 * non-owning PROVIDE identical in kind to the entries above, declared extern in
 * g1_app_symbols.h and referenced by dmic_stream_start (FUN_0002f080). Addresses
 * are the literal VAs encoded in each symbol name and confirmed by the source
 * identity headers. Completes the closure so the cohesive link resolves. */
PROVIDE(rodata_88694 = 0x00088694);
PROVIDE(g_20003778 = g1_ram_arena + 0x1778);

/* Iteration 8: interior rodata string pins and two absolute RAM cells used by
 * the three reconstructed IPC-service handlers (local_ipc_service_recv @
 * 0x162ec, local_esbm_ipc_service_recv @ 0x16bf0). Same non-owning PROVIDE
 * kind as the entries above; each address is the literal VA the shipped code
 * loads from its own literal pool. */
PROVIDE(g_20007b34 = g1_ram_arena + 0x5b34); /* iteration 8: local_esbm_ipc_service_recv atomic shutdown-request flags */
PROVIDE(g_2000ff4a = g1_ram_arena + 0xdf4a); /* iteration 8: local_esbm_ipc_service_recv last-handled esbm sequence */
