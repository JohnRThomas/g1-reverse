# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(g1_net)

# P4 iteration 29 -- the single divergence between the shipped ESB core and the
# pinned NCS v2.5.1 source: the shipped firmware pends SWI3 as the ESB event
# IRQ because MPSL already owns SWI0 on CPUNET (mpsl_init.c:38).  Force-include
# a header that defines the SDK header's own include guard, so the pinned SDK
# tree stays untouched and only the ESB library sees the change.  See
# src/esb_peripherals_g1.h for the byte evidence.
if(TARGET ..__nrf__subsys__esb)
  target_compile_options(..__nrf__subsys__esb PRIVATE
    "-include" "${CMAKE_CURRENT_LIST_DIR}/src/esb_peripherals_g1.h")
else()
  message(FATAL_ERROR
    "expected the NCS ESB library target ..__nrf__subsys__esb to exist; "
    "the G1 ESB event-IRQ override could not be applied")
endif()

# Integration probes must expose ownership collisions and unresolved calls in
# every retained reconstruction, including functions not yet reachable from
# the temporary shell entry point.  Zephyr normally garbage-collects those
# input sections, which can make an incomplete image appear to link cleanly.
# This option deliberately retains application and already-selected SDK input
# sections; it does not force archive members into the link or mask failures.
option(G1_INTEGRATION_PROBE_RETAIN_ALL
  "Retain all linked sections while auditing reconstruction ownership" ON)
if(G1_INTEGRATION_PROBE_RETAIN_ALL)
  # NCS v2.5.1 / Zephyr 3.4 exposes linker flags through this helper.
  zephyr_ld_options(-Wl,--no-gc-sections)

  # subsys/bluetooth/common/bt_str.c is unconditional, but its bt_uuid_str()
  # helper calls bt_uuid_to_str(), whose normal owner (host/uuid.c) is omitted
  # when CONFIG_BT_HCI_RAW=y disables CONFIG_BT_HCI_HOST.  Normal section GC
  # discards that unused helper in the shipped controller configuration.  The
  # retain-all audit deliberately keeps it, so select the pinned Zephyr source
  # as an audit-only dependency instead of inventing a firmware reconstruction.
  target_sources(app PRIVATE
    "${ZEPHYR_BASE}/subsys/bluetooth/host/uuid.c"
  )
endif()

set(G1_RETAINED_SOURCE_MANIFEST
    "${CMAKE_CURRENT_LIST_DIR}/../../generated/net_retained_sources.cmake")
if(NOT EXISTS "${G1_RETAINED_SOURCE_MANIFEST}")
  message(FATAL_ERROR
    "Missing generated net source manifest: ${G1_RETAINED_SOURCE_MANIFEST}\n"
    "Generate it from recon/ownership/adoption_manifest.json; do not replace "
    "it with a source glob.")
endif()

include("${G1_RETAINED_SOURCE_MANIFEST}")
if(NOT DEFINED G1_RETAINED_SOURCES)
  message(FATAL_ERROR
    "${G1_RETAINED_SOURCE_MANIFEST} must define G1_RETAINED_SOURCES")
endif()

# The timeslot closure uses its canonical raw sources because the worker and
# producer need cohesive-build relocations to the same real Zephyr message
# queue.  Remove the two older symbolized copies before adding the complete
# four-function ownership unit below.
list(FILTER G1_RETAINED_SOURCES EXCLUDE
  REGEX "/FUN_0102(a4c8|ab14|ab50|abac|ac00|ac0c|acb4|ace8|acf4|adac|adf0|afbc|b15c|b1c8|b2ac|b7d0|b900)\\.c$")

set(G1_PRODUCT_ENDPOINT_SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102a4c8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102ab14.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102ab50.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102abac.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102ac00.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102ac0c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102acb4.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102ace8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102acf4.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102adac.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102adf0.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102afbc.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b15c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b1c8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b2ac.c"
  "${CMAKE_CURRENT_LIST_DIR}/src/g1_product_endpoints.c"
)

set(G1_TIMESLOT_OWNER_SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b7d0.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b810.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b900.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b944.c"
  "${CMAKE_CURRENT_LIST_DIR}/src/timeslot_owner.c"
)

# The durable adoption manifest still records 29 private MPSL/SDC functions as
# archive-owned, and three readable private dependencies are absent from the
# generated list.  Those decisions are report-only: the obfuscated archive
# spellings are provenance, not safe link aliases.  Keep the corresponding
# CFG-proven reconstructions in the cohesive link until the manifest generator
# consumes the private-recovery receipts.  This explicit list is intentionally
# separate from G1_RETAINED_SOURCES so a clean probe cannot silently regress to
# archive substitution.
set(G1_PRIVATE_REPORT_ONLY_SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/controller_radio_state_get.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/controller_timing_snapshot_build.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/controller_radio_event_cleanup.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01021940.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01021ac0.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01022a30.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01022a50.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01022e34.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01022ea8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01022f0c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/sdc_conn_window_admit.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01023ac4.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01023d38.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01023e88.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01024440.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_0102445c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_010245d8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01024c6c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_0102524c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_010256dc.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_010257e4.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/controller_deferred_event_raise.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_0102590c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01025998.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01025a84.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01025c44.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01025c9c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01025cc8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/controller_transition_pending_check.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/FUN_01025d0c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/sdc_byte_lock_try_acquire.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/net/sdc_byte_lock_release.c"
)

# The clock callback is a real production root: FUN_0102b5bc registers the
# runtime Thumb pointer 0x0102bf59 stored at analysis literal 0x0102b660. Keep
# its complete recovered private closure, plus the two exact ESB public leaves,
# until final exact-source assembly can remove those SDK duplicates safely.
set(G1_ESB_CLOCK_CALLBACK_CLOSURE_SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b3f0.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b664.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b718.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102b758.c"
  # P4 iteration 29: FUN_01033858 (esb_start_tx) and FUN_010339d0 (esb_tx_full)
  # were the "two exact ESB public leaves" kept here.  esb.c is now proven to be
  # the STOCK NCS 2.5.1 unit (39 sections tile 0x01032764..0x01033b18 exactly
  # under CONFIG_ESB_MAX_PAYLOAD_LENGTH=251 + ESB_EVT_IRQ=SWI3), so the whole
  # unit is displaced and these two are provided by it -- keeping them here
  # would re-create the duplicate the displacement removes.
  # P4 iteration 23: the two RADIO packet-configuration trampolines
  # FUN_010333b4 stores into its callback slot as the runtime Thumb pointers
  # 0x010333a5 / 0x010333e5 (analysis 0x01032ba4 / 0x01032be4), plus the RADIO
  # PCNF0/PCNF1 packer they share (analysis 0x01032b4c), are recovered from a
  # Ghidra gap and are picked up automatically by gen_retained_sources.py once
  # their symbolized copies carry an identity header -- no explicit entry here.
)

# The recovered product main deliberately emits its reversible raw identity
# FUN_0102a720.  Bind Zephyr's public `main` entry directly to that body (with
# no wrapper instructions) and make the raw symbol a production GC root.
zephyr_ld_options(
  -Wl,-u,FUN_0102a720
  # Address-taken clock callback stored as runtime Thumb pointer 0x0102bf59;
  # the original literal has no ELF relocation for section GC to follow.
  -Wl,-u,FUN_0102b758
)

# Firmware/controller functions are selected explicitly by the generated
# manifest above; upstream controller and crypto objects remain under their
# normal NCS module CMake integration.
target_sources(app PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/../../net/src/FUN_0102a720.c"
  src/cfg_boundary_lowerings.c
  # P4 iteration 26: storage for every recovered absolute CPUNET RAM address
  # (structural close of the collision class).  Generated by
  # recon/application/gen_net_ram_relocs.py.
  src/g1_net_ram_relocs.c
  # P4 iteration 29: real 256-byte storage for the two `struct esb_payload`
  # objects the ESB session layer hands to the stock ESB core.  The generic
  # relocation blocks size them at 24 B, so every received ESB frame overruns
  # into the sibling block.  The sizing is PROVEN (see the file header) but is
  # OFF by default: enabling it unmasks the announce-response path, which halts
  # both cores after the first ESB ACK.  Enable with
  #   -DG1_ESB_REAL_RX_PAYLOAD_OBJECT (and -DG1_ESB_REAL_TX_PAYLOAD_OBJECT)
  # via target_compile_definitions when chasing that defect.
  src/g1_esb_payload_objects.c
  ${G1_RETAINED_SOURCES}
  ${G1_PRIVATE_REPORT_ONLY_SOURCES}
  ${G1_ESB_CLOCK_CALLBACK_CLOSURE_SOURCES}
  ${G1_PRODUCT_ENDPOINT_SOURCES}
  ${G1_TIMESLOT_OWNER_SOURCES}
  # Byte-exact literal/data pools split from CFG-inflated net functions.
  # These are reviewed reconstruction artifacts, not synthesized link stubs.
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x100ef04.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x101fdb8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x101fdcc.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x10217fc.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x10237a4.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x103c190.c"
)

# Canonical parity sources retain their fixed-address form by default.  The
# cohesive firmware build selects only reviewed object/callback relocations.
target_compile_definitions(app PRIVATE G1_COHESIVE_BUILD=1)

# Symbolized reconstruction inputs include the generated reversible VA/name
# declarations from this directory.
target_include_directories(app PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols"
  "${ZEPHYR_BASE}/subsys/ipc/ipc_service/backends"
)

# Symbolized sources name original-image RAM and read-only objects rather than
# embedding raw addresses.  Resolve those names with the generated, reversible
# VA pins used by the parity/full-link pipeline.  The small aliases fragment is
# separately reviewed and contains only known interior/shared-tail addresses.
# PROVIDE keeps real SDK definitions authoritative when one exists.
zephyr_linker_sources(SECTIONS
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_net_globals.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_net_aliases.ld"
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols/g1_net_function_aliases.ld"
  "${CMAKE_CURRENT_LIST_DIR}/src/stock_call_aliases.ld"
)
