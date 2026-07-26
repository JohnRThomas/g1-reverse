cmake_minimum_required(VERSION 3.20.0)

# Keep the recovered board evidence as the baseline and layer the reviewed
# upstream-adoption choices on top.  Both paths are explicit so a build from
# this directory does not depend on the caller's working directory.
set(CONF_FILE
  "${CMAKE_CURRENT_LIST_DIR}/../../board/prj.conf"
  "${CMAKE_CURRENT_LIST_DIR}/prj.conf"
  CACHE STRING "G1 application configuration fragments" FORCE
)

# The recovered device inventory is board-specific.  Keep the overlay explicit
# so a build from this directory cannot silently fall back to the DK device
# topology (which adds a Zephyr SPI device and omits the nPM1300 children).
set(DTC_OVERLAY_FILE
  "${CMAKE_CURRENT_LIST_DIR}/../../board/g1_board.overlay"
  CACHE STRING "G1 recovered CPUAPP devicetree" FORCE
)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(g1_cpuapp_reconstruction)

# fdtable.c deliberately keeps its stock source and code generation.  Its
# initialized fdtable array is translation-unit-local upstream, while several
# recovered application callers address fields in that same object directly.
# Export only the archive symbol after compilation so the linker aliases can
# converge both caller sets on one owner without copying or patching Zephyr.
add_custom_target(g1_export_fdtable_owner
  COMMAND ${CMAKE_OBJCOPY} --globalize-symbol=fdtable $<TARGET_FILE:zephyr>
  DEPENDS zephyr
  COMMENT "Expose pinned stock fdtable data owner for recovered aliases"
  VERBATIM
)
add_dependencies(app g1_export_fdtable_owner)

# Rejoin compiler-outlined SDK/header helpers with their retained owning
# callers.  The canonical parity path leaves this undefined so each historical
# BL remains an oracle boundary; the cohesive build inlines the exact pinned
# NCS 2.5.1 semantics without exporting duplicate helper bodies.
target_compile_definitions(app PRIVATE G1_APP_SDK_INLINE_COHESION=1)

# The shipped configured z_impl_k_sem_take body is retained because the pinned
# Zephyr sem.c body fails the instruction/shape ownership gates.  sem.c also
# owns unrelated semaphore APIs, so the unit cannot be removed.  Rename only
# its non-selected implementation at compile time; all external references and
# the exact public veneer then bind to the single retained strong owner.
set_source_files_properties(
  "${ZEPHYR_BASE}/kernel/sem.c"
  DIRECTORY "${ZEPHYR_BASE}/kernel"
  PROPERTIES COMPILE_DEFINITIONS
    "z_impl_k_sem_take=g1_displaced_sdk_z_impl_k_sem_take"
)

# This shell is currently an ownership/link integration probe, not a runnable
# application entry-point build.  Its temporary Zephyr main does not reference
# every recovered function, so normal --gc-sections would silently discard the
# very definitions and collisions the probe must inspect.  Retain every input
# section by default while leaving undefined and duplicate-symbol diagnostics
# fully enabled.  A later cohesive application can turn this off once its real
# roots and initialization graph are wired.
option(G1_INTEGRATION_PROBE_RETAIN_ALL
  "Retain all recovered sections while validating ownership and linkage" OFF)
if(G1_INTEGRATION_PROBE_RETAIN_ALL)
  # Zephyr 3.4.99 places its default --gc-sections in the link-library list,
  # after normal target_link_options.  Append the inverse through the same
  # interface so GNU ld sees --no-gc-sections last.
  zephyr_link_libraries(-Wl,--no-gc-sections)
else()
  # Binary-derived runtime thread candidates are not all visible through the
  # reconstructed C call graph (several are passed through recovered tables).
  # Admit only candidates that resolve to named, retained definitions.  The
  # generated receipt keeps unmapped addresses visible but never turns them
  # into numeric linker roots.
  include(${CMAKE_CURRENT_LIST_DIR}/../../generated/app_gc_roots.cmake)
  foreach(_g1_root IN LISTS G1_RECOVERED_GC_ROOTS)
    zephyr_ld_options("-Wl,--undefined=${_g1_root}")
  endforeach()
  # Original function pointers in callback/config tables are not necessarily
  # represented by relocations in the recovered C tree.  This second ledger is
  # generated from aligned Thumb words outside capped original function spans.
  # Keep admission opt-in until final section placement has room for the added
  # live closure; the generated inventory itself is always available to audit.
  option(G1_ENABLE_ADDRESS_TAKEN_ROOTS
    "Retain uniquely-owned recovered address-taken functions" OFF)
  include(${CMAKE_CURRENT_LIST_DIR}/../../generated/app_address_taken_roots.cmake)
  if(G1_ENABLE_ADDRESS_TAKEN_ROOTS)
    foreach(_g1_root IN LISTS G1_ADDRESS_TAKEN_RECOVERED_ROOTS)
      zephyr_ld_options("-Wl,--undefined=${_g1_root}")
    endforeach()
  endif()
  if(G1_UNRESOLVED_GC_ROOT_ADDRESSES)
    message(STATUS
      "CPUAPP root graph remains partial; unresolved firmware candidates: "
      "${G1_UNRESOLVED_GC_ROOT_ADDRESSES}")
  endif()
endif()

# Zephyr 3.4.99's liblc3 module exports both its public include directory and
# its private src directory through zephyr_interface.  The latter contains a
# generic common.h which then shadows nRF Security's Oberon common.h in
# psa_crypto_driver_wrappers.c, suppressing MBEDTLS_ALLOW_PRIVATE_ACCESS and
# breaking the otherwise-valid CC312/PSA build.  Keep the pinned SDK untouched:
# contain only the exact private directory on the liblc3 target that owns it.
if(CONFIG_LIBLC3 AND TARGET liblc3)
  set(_g1_liblc3_private_src "${ZEPHYR_LIBLC3_MODULE_DIR}/src")
  get_target_property(_g1_zephyr_interface_includes
    zephyr_interface INTERFACE_INCLUDE_DIRECTORIES)
  list(REMOVE_ITEM _g1_zephyr_interface_includes
    "${_g1_liblc3_private_src}")
  set_property(TARGET zephyr_interface PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    "${_g1_zephyr_interface_includes}")
  target_include_directories(liblc3 PRIVATE "${_g1_liblc3_private_src}")
  unset(_g1_zephyr_interface_includes)
  unset(_g1_liblc3_private_src)
endif()

# Generated from recon/ownership/adoption_manifest.json.  This is deliberately
# not a glob: only manifest-authorized upstream owners may displace recovered
# functions, while the canonical reconstruction files remain on disk.
include(${CMAKE_CURRENT_LIST_DIR}/../../generated/app_retained_sources.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../generated/app_verified_data_sources.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../generated/app_fixed_verified_rodata.cmake)

option(G1_ENABLE_FIXED_VERIFIED_RODATA
  "Place the reviewed verified suffix at original firmware addresses" OFF)

# Only complete, byte-exact tables above the recorded normal-GC ROM end are
# emitted by the fixed-address assembly.  Remove those C owners before adding
# the generated owner so every symbol remains unique.  Tables that collide with
# the current executable/SDK layout stay in ordinary garbage-collected rodata.
if(G1_ENABLE_FIXED_VERIFIED_RODATA)
  list(REMOVE_ITEM G1_VERIFIED_DATA_SOURCES
    ${G1_FIXED_VERIFIED_DATA_C_SOURCES})
else()
  # The ordinary byte-verified C owners stay live; only their fixed-address
  # placement is disabled for closure/layout audits.
  set(G1_FIXED_VERIFIED_DATA_ASM "")
  set(G1_FIXED_VERIFIED_DATA_LINKER "")
endif()

# One retained, parity-proven translation unit records the original r9-bound
# local with GCC's ``register ... asm("r9")`` spelling.  Zephyr's application
# interface otherwise forces strict C99, where ``asm`` is not a keyword.  Keep
# that canonical body untouched and enable GNU C99 only for its owning source;
# this changes no optimization or ABI option and avoids broadening the dialect
# for the rest of the recovered corpus.
set_source_files_properties(
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/app/discovery_callback.c"
  PROPERTIES COMPILE_OPTIONS "-std=gnu99"
)

target_sources(app PRIVATE
  ${G1_RETAINED_SOURCES}
  # The firmware uses the pinned stock LSM6DSO implementation and data/API
  # shape, but its device init entry is NULL.  This wrapper changes only that
  # instantiation detail and keeps CONFIG_LSM6DSO disabled.
  src/g1_lsm6dso_device.c
  # Compiler-outlined Zephyr header identities still called by newly recovered
  # roots.  Integration-only: canonical parity bodies remain unchanged.
  src/g1_sdk_inline_bridges.c
  # Bring-up wiring TUs (P4 iterations 5-7).  Recovered code addresses these
  # objects through absolute pins in recon/symbols/g1_app_globals.ld; where the
  # object's CONTENTS embed pointers (or an initialiser the recovered code
  # never writes) a linker rebind cannot express it, so the build emits the
  # object and the pin name is bound onto it.  Integration-only: no canonical
  # parity body changes.  These are hand-written wiring, not recovered
  # functions, so they live here rather than in the generated retained list.
  src/g1_gpio_dt_specs.c
  src/g1_app_ram_relocs.c
  # Iteration 15: the recovered RAM arena is plain .bss, but every pin below
  # 0x20003e29 is `.data` in the shipped image and therefore starts at its
  # SHIPPED INITIALISER, not at zero.  This generated TU replays the shipped
  # `.data` load image into the arena at PRE_KERNEL_1.  Regenerate with
  #   recon/application/gen_app_data_image.py --stage a2
  # (the generator documents the load-image base proof and the pointer policy).
  src/g1_app_data_image.c
  src/g1_app_font_rodata.c
  # P4 iteration 35, rodata decode BATCH 4 (recon/analysis/rodata_decode_report.md
  # §8), the single blob the dashboard needs: g1_app_rodata_02.c owns
  # `rodata_d753a`, the byte-verified 59,944-byte packed-4bpp glyph BITMAP run
  # [0xd753a, 0xe5f62) that holds the glyph pixels of font style 3 and of both
  # clock-digit families.  Its four interior pins (rodata_e123a / e17da / e4408
  # / e5248 -- the same four lines recon/application/rodata/g1_app_rodata_interior.ld
  # carries for this run) are re-pinned onto it in g1_app_globals.ld, whose
  # numeric pins for them are gone, so a link that dropped the object fails
  # loudly instead of reading our own relocated image again.  One blob per
  # build, as the report recommends, so a raster change stays attributable.
  #
  # Iteration 35b then wired the REST of the decode except g1_app_rodata_00.c:
  # measured (35.6), the glyph pixels alone leave the dashboard's ICONS blank,
  # because `resource_manger_get` case 4 -- the image/icon resource class --
  # returns literal pointers into rodata_bc097 (45,682 B, file 07) and
  # rodata_c7956 (63,517 B, file 06), i.e. the other two batch-4 blobs, plus
  # ~40 smaller ones in files 01/03/04/05.  g1_app_rodata_00.c is held back on
  # a MEASURED flash argument, not a judgement: its 68,690 B would take the
  # image to 990,265 B against a 982,528 B partition.  Its one large object,
  # rodata_aae20 (66,560 B), has no reader on the dashboard path.
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_01.c
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_02.c
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_03.c
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_04.c
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_05.c
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_06.c
  ${CMAKE_CURRENT_LIST_DIR}/../rodata/g1_app_rodata_07.c
  # Iteration 21: 2,128 of the `rodata_<hex>` PROVIDE pins in
  # recon/symbols/g1_app_globals.ld were still ABSOLUTE in the link (nm class
  # `A`), i.e. they named ORIGINAL-image flash addresses that hold unrelated
  # bytes in this relocated build.  1,793 of them are NUL-terminated printable
  # C strings and are emitted here byte-exactly, which makes the PROVIDE inert.
  # Measured motivation: bt_start() formats the advertised device name with
  # __sprintf_chk(name, 0, 0x20, rodata_9acb2, rodata_9ac7c, ...) and both
  # operands were garbage, so the result overran the 32-byte buffer and
  # fortify_chk_fail() raised K_ERR_KERNEL_OOPS.  Regenerate with
  #   recon/application/gen_app_string_rodata.py --elf <link>/zephyr/zephyr.elf
  # `--gc-sections` still drops the strings nothing references.
  src/g1_app_string_rodata.c
  src/g1_ipc_serialization_objects.c
  # Iteration 10: the 3-entry ST25DV transport ops vtable (original
  # rodata_88a38).  Its contents are original-image Thumb function pointers, so
  # like the gpio_dt_spec tables it has to be emitted, not pinned.
  src/g1_st25dv_ops_table.c
  # Iteration 15: the four nPM1300 charger `linear_range` tables (original
  # 0x8ba64..0x8baac).  Like the ops table above, the recovered code
  # DEREFERENCES the original address, so the block has to be emitted and the
  # four rodata_8baXX pins bound onto it in g1_app_globals.ld.
  src/g1_npm1300_linear_ranges.c
  # P4 iteration 22: the three advertising operands of bt_le_adv_start.  The
  # `struct bt_le_adv_param` pin (rodata_8839c) was still an ORIGINAL-image
  # address holding unrelated bytes, and the two `struct bt_data` arrays have
  # pointer-bearing `.data` initialisers that the RAM-arena restore drops.
  # Measured: bt_le_adv_start returned -EINVAL with options = 0x682e7365.
  src/g1_bt_adv_objects.c
  # P4 iteration 23: the application's own `struct bt_conn_cb` entry in the
  # `bt_conn_cb` iterable section.  The shipped section [0x87fec, 0x88058) holds
  # three 0x24-byte entries; entry 0 is {ancs_connected, ancs_disconnected,
  # ancs_security_changed}.  Our build's section held only the SDK's mcumgr
  # entry, so `ancs_connected` never ran, `g_ancs_conn` (0x20007518) stayed 0
  # and `ble_is_connected` printed 0 on a live link.
  src/g1_bt_conn_cb_objects.c
  # P4 iteration 31: the application's own GATT service — the THIRD entry of
  # the shipped `bt_gatt_service_static` section ({0x0008ad18, 6}, stock NCS
  # nus.c's BT_GATT_SERVICE_DEFINE without CONFIG_BT_NUS_AUTHEN).  Our link had
  # only Zephyr's GATT and GAP services, so the phone's ATT write had nothing
  # to land on: measured, `ble_process_req_dispatch` was hit 0 times in a 20 s
  # capture, `now_has_persist_task` returned 0 all 398 times and the display
  # START only ever arrived with `action = 0`.  The service is emitted here
  # rather than by CONFIG_BT_NUS=y because stock nus.c would bring a SECOND
  # `nus_cb` singleton; the recovered one at 0x2000a2b8 (written by the
  # retained FUN_0004f500) is the one the callbacks here read.
  src/g1_bt_nus_service.c
  # Library displacement Batch 0 (goal G2): the four out-lined
  # zephyr/include/zephyr/drivers/gpio.h static inlines are excluded in
  # adoption_manifest.json; a header `static inline` has no external symbol to
  # bind, so their historical identities are re-expressed here as thin bridges
  # over the real gpio.h API.
  src/g1_gpio_header_bridges.c
  # Library displacement Batch 1 (goal G2): twelve newlib-nano mprec/stdio
  # primitives are excluded in adoption_manifest.json but are still called by
  # name from recovered newlib TUs outside the batch, so their historical
  # identities forward onto the genuine newlib entry points here.
  src/g1_newlib_mprec_bridges.c
  # Library displacement Batch 2b (goal G2): five zephyr_kernel sched/poll
  # primitives are excluded in adoption_manifest.json but are still called by
  # name from recovered TUs outside the sub-batch, so their historical
  # identities forward onto the genuine Zephyr kernel entry points here.
  src/g1_kernel_sched_bridges.c
  # P4 iteration 20: the shipped firmware VENDORS nrf/subsys/bluetooth/services
  # /ancs_client.c.  adoption_manifest.json excluded FUN_0007f772 /
  # FUN_0007f79e in favour of the stock owner on a 1.0 instruction-shape match,
  # but the shape match is blind to the two things that differ, and both are
  # proven by disassembly:
  #   shipped 0x7f772  cmp r4,#0xff ; strh [r0,#0x870] strb [r0,#0x868] str [r0,#0x874]
  #   stock            cmp r4,#0x1f ; strh [r0,#0x110] strb [r0,#0x108] str [r0,#0x114]
  #   shipped 0x7f79e  cmp r4,#0xff ; strh [r0,#0x8f0] strb [r0,#0x8e8] str [r0,#0x8f4]
  #   stock            cmp r4,#0x1f ; strh [r0,#0x190] strb [r0,#0x188] str [r0,#0x194]
  # i.e. BT_ANCS_ATTR_DATA_MAX is 256 in the shipped build (32 upstream) and
  # `struct bt_ancs_client` is 0xa2c bytes (the recovered ancs_service_ctx_clear
  # memsets exactly 0xa2c at g_ancs_client).  MEASURED on /private/tmp/g1-i20b:
  # once bt_enable() finally succeeded, ancs_c_init's fifth registration
  # (id = 3, len = 0x100) hit the stock `cmp r4,#31` limit, returned -EINVAL and
  # ancs_main rebooted the SoC at t = 6.6 s.  The canonical raw-identity
  # reconstructions are linked here under their FUN_ names, so the stock
  # `bt_ancs_register_attr` / `bt_ancs_register_app_attr` symbols stay with
  # their upstream owner and there is no duplicate definition.
  ${CMAKE_CURRENT_LIST_DIR}/../../app/src/FUN_0007f772.c
  ${CMAKE_CURRENT_LIST_DIR}/../../app/src/FUN_0007f79e.c
  ${ZEPHYR_BASE}/drivers/sensor/stmemsc/stmemsc_i2c.c
  ${ZEPHYR_ST_MODULE_DIR}/sensor/stmemsc/lsm6dso_STdC/driver/lsm6dso_reg.c
  # Generated only after compiling every recovered table and comparing its
  # emitted bytes to app_update.bin.  Unknown/skipped tables are never added.
  ${G1_VERIFIED_DATA_SOURCES}
  ${G1_FIXED_VERIFIED_DATA_ASM}
)

# Audit-only pre-adoption probes may re-add an explicitly enumerated source
# set without changing the generated retention ledger.  Production builds
# leave this empty.  Collision receipts use it to prove exact before/after
# symbol sets from otherwise-identical configurations.
set(G1_AUDIT_EXTRA_SOURCES "" CACHE STRING
  "Semicolon-separated recovered sources restored only for ownership audits")
if(G1_AUDIT_EXTRA_SOURCES)
  target_sources(app PRIVATE ${G1_AUDIT_EXTRA_SOURCES})
endif()
target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  # The symbolized tree intentionally reuses reviewed helper headers and
  # include fragments from the canonical source tree; function bodies still
  # come exclusively from the generated retained-source list.
  ${CMAKE_CURRENT_LIST_DIR}/../../app/src
  ${CMAKE_CURRENT_LIST_DIR}/../../headers
  ${CMAKE_CURRENT_LIST_DIR}/../../symbols
  ${CMAKE_CURRENT_LIST_DIR}/../../wiring
  ${ZEPHYR_BASE}/drivers/sensor/lsm6dso
  ${ZEPHYR_BASE}/drivers/sensor/stmemsc
  ${ZEPHYR_ST_MODULE_DIR}/sensor/stmemsc/lsm6dso_STdC/driver
)

# Symbolized reconstruction inputs refer to original-image RAM objects and
# read-only bytes by their reversible names.  Resolve those names with the
# generated VA pins used by the parity/full-link pipeline.  PROVIDE is
# intentionally non-owning: a real Zephyr/module definition remains
# authoritative, while an otherwise-unresolved recovered object retains its
# exact original address.  The reviewed aliases are kept separate so this
# does not turn missing ownership into guessed storage.
zephyr_linker_sources(SECTIONS
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_globals.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_sdk_state.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_aliases.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_function_aliases.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_veneer_aliases.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_public_sdk_aliases.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_readable_aliases.ld"
)

# P4 iteration 22, library-displacement Batch 4: the newlib-nano printf closure
# is displaced to the pinned libc_nano.a (adoption_manifest.json), so the
# historical spellings that retained callers and the reversible alias files
# still use are mapped onto the upstream owners.  GNU ld evaluates PROVIDE in
# script order and zephyr_linker_sources concatenates snippets sorted by sort
# key, so this fragment needs a key that orders BEFORE the default one used by
# g1_app_function_aliases.ld -- that file chains
# `PROVIDE(FUN_00086f00 = vdprintf_to_fd)` onto a name this fragment defines.
zephyr_linker_sources(SECTIONS
  SORT_KEY 0_g1_newlib_printf
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_newlib_printf_aliases.ld"
)
# GNU ld does not extract an archive member to satisfy a symbol that is only
# named inside a linker-script expression, so the three displaced identities
# that retained Even code still calls by their historical spelling need their
# upstream owners pulled into the link explicitly.  Everything else in the
# family (`_svfprintf_r`, `__ssputs_r`, `_printf_i`, `_printf_common`,
# `__sfputs_r`, `_printf_float`, `__cvt`, `__exponent`, `_dtoa_r`, `quorem`)
# arrives through ordinary relocations from these members plus the
# `-u _printf_float` that CONFIG_NEWLIB_LIBC_FLOAT_PRINTF adds.
foreach(_g1_newlib_root __sprintf_chk sprintf _vsnprintf_r vsnprintf fprintf)
  zephyr_ld_options("-Wl,--undefined=${_g1_newlib_root}")
endforeach()

# P4 iteration 32, coherent zephyr/kernel/sched.c displacement.  The unit was
# split (20 adopted identities + 11 retained duplicate bodies over one
# `_kernel`, with sched.c's `pending_current` file-static duplicated into the
# recon RAM arena).  The manifest now excludes all 11; four of them are still
# called by their historical recovered spelling from retained Even translation
# units, so those spellings bind to the genuine upstream owners here.  Same
# ordering rule as the newlib fragment above: this must precede
# g1_app_function_aliases.ld / g1_app_veneer_aliases.ld, which chain onto these
# names.
zephyr_linker_sources(SECTIONS
  SORT_KEY 0_g1_sched_displacement
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_app_sched_displacement_aliases.ld"
)
# Same archive-extraction caveat as the newlib roots: a symbol named only in a
# linker-script expression does not pull its section in, so name the upstream
# sched.c owners the aliases above resolve to.
foreach(_g1_sched_root z_impl_k_sleep z_impl_k_yield z_impl_k_thread_priority_set
                       z_sched_start z_priq_dumb_remove)
  zephyr_ld_options("-Wl,--undefined=${_g1_sched_root}")
endforeach()
if(G1_ENABLE_FIXED_VERIFIED_RODATA)
  zephyr_linker_sources(SECTIONS "${G1_FIXED_VERIFIED_DATA_LINKER}")
endif()

# Every source selected by app_verified_data_sources.cmake has been compiled
# independently and byte-compared with app_update.bin.  Their standalone
# tables are firmware-owned roots even when a reconstructed reader still uses
# an absolute back-map alias, so retain only those object/section patterns in
# the normal rodata output section.
zephyr_linker_sources(RODATA
  "${CMAKE_CURRENT_LIST_DIR}/g1_verified_rodata_keep.ld"
)
