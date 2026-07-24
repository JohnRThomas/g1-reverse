/* net-core FUN_0102b7a0 @ 0x102b7a0  (CFG-directed candidate) */
/* net-core FUN_0102b7a0 @ 0x102b7a0
 * ESB radio-state setter reached from the cpunet-hw-id IPC handler's
 * sub-command 11 ("L"): low-power request. */
void FUN_0102b7a0(void)
{
    *(volatile unsigned int *)0x210005b4u = 1u;
}
