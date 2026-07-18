/* The only standalone rodata objects compiled into app/libapp.a come from
 * app_verified_data_sources.cmake, whose generator byte-compares every symbol
 * against app_update.bin.  Keep their per-symbol input sections under normal
 * --gc-sections; do not retain arbitrary recovered code or unverified data. */
KEEP(*rodata_*.c.obj(".rodata.rodata_*"))
KEEP(*rodata_*.c.obj(".rodata.litpool_*"))
