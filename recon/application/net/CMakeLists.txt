# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(g1_net)

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

# This is only the Zephyr application entry. Firmware/controller functions are
# selected explicitly by the generated manifest above; upstream controller and
# crypto objects remain under their normal NCS module CMake integration.
target_sources(app PRIVATE
  src/main.c
  src/cfg_boundary_lowerings.c
  ${G1_RETAINED_SOURCES}
  # Byte-exact literal/data pools split from CFG-inflated net functions.
  # These are reviewed reconstruction artifacts, not synthesized link stubs.
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x100ef04.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x101fdb8.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x101fdcc.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x10217fc.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x10237a4.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../net/data/rodata_0x103c190.c"
)

# Symbolized reconstruction inputs include the generated reversible VA/name
# declarations from this directory.
target_include_directories(app PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/../../symbols"
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
)
