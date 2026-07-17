cmake_minimum_required(VERSION 3.20.0)

# Keep the recovered board evidence as the baseline and layer the reviewed
# upstream-adoption choices on top.  Both paths are explicit so a build from
# this directory does not depend on the caller's working directory.
set(CONF_FILE
  "${CMAKE_CURRENT_LIST_DIR}/../../board/prj.conf"
  "${CMAKE_CURRENT_LIST_DIR}/prj.conf"
  CACHE STRING "G1 application configuration fragments" FORCE
)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(g1_cpuapp_reconstruction)

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

target_sources(app PRIVATE ${G1_RETAINED_SOURCES})
target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/../../headers
  ${CMAKE_CURRENT_LIST_DIR}/../../symbols
  ${CMAKE_CURRENT_LIST_DIR}/../../wiring
)
