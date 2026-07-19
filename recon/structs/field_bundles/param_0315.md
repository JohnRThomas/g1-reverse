### struct wdt_timeout_cfg_view  (library:wdt_timeout_cfg)  cid=param_0315

purpose: param_1 of wdt_install_timeout: watchdog timeout config with a callback/window pointer near front and a second pointer at 0x10.

This object is accessed by these functions (read their fully-named source):
  - wdt_install_timeout  (as param_1)  ->  recon/readable_sources/app/g1/wdt_install_timeout.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct wdt_timeout_cfg_view {
    void *       callback_ptr;  /* +0x4  rw=r sz=4 */
    void *       field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```