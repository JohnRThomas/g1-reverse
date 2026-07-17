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
  ${G1_RETAINED_SOURCES}
)
