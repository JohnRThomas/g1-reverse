/* Exact configured-SDK state ownership for Zephyr settings.
 * Strong assignments converge the stock settings.c/settings_store.c owner on
 * the shipped firmware's private RAM identities. Generic reconstruction names
 * remain non-owning PROVIDE aliases in g1_app_globals.ld.
 */
settings_lock = 0x20003868;
settings_save_dst = 0x2000a100;
settings_load_srcs = 0x2000a104;
settings_handlers = 0x2000a10c;

/* The recovered veneer at 0x00086698 predates readable-owner generation and
 * still exports its durable thunk spelling. Keep current readable callers on
 * the same owner until that canonical veneer is mechanically renamed. */
uptime_ticks_get = thunk_FUN_00074f68;
