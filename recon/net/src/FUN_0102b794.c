/* net-core FUN_0102b794 @ 0x102b794  (CFG-directed candidate) */
/* net-core FUN_0102b794 @ 0x102b794
 * ESB radio-state setter reached from the cpunet-hw-id IPC handler's
 * sub-command 10 ("H"): high-power request. */
void FUN_0102b794(void)
{
    *(volatile unsigned int *)0x210005b4u = 2u;
}
