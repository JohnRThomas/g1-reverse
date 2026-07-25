/* Exact configured-SDK state ownership for Zephyr settings.
 * Strong assignments converge the stock settings.c/settings_store.c owner on
 * the shipped firmware's private RAM identities. Generic reconstruction names
 * remain non-owning PROVIDE aliases in g1_app_globals.ld.
 */
settings_lock = g1_ram_arena + 0x1868;
settings_save_dst = g1_ram_arena + 0x8100;
settings_load_srcs = g1_ram_arena + 0x8104;
settings_handlers = g1_ram_arena + 0x810c;

/* The pinned fdtable.c owns one initialized 16-entry array.  The cohesive
 * build globalizes only this otherwise-local ELF symbol after archiving, so
 * retained non-stock callers and the selected stock functions share one
 * object.  Final absolute placement remains a section-layout gate; these are
 * ownership aliases, not guessed duplicate storage. */
g_fdtable_entries = fdtable;
g_fdtable_refcount_field = fdtable + 8;

/* The recovered veneer at 0x00086698 predates readable-owner generation and
 * still exports its durable thunk spelling. Keep current readable callers on
 * the same owner until that canonical veneer is mechanically renamed. */
uptime_ticks_get = thunk_FUN_00074f68;
