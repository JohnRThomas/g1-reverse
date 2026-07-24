/* net-core FUN_0102b7ac @ 0x102b7ac  (CFG-directed candidate) */
/* net-core FUN_0102b7ac @ 0x102b7ac
 * ESB radio-state setter reached from the cpunet-hw-id IPC handler's
 * sub-command 12 ("P"): pairing request. */
void FUN_0102b7ac(void)
{
    *(volatile unsigned int *)0x210005b4u = 3u;
}
