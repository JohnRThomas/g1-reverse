/* net-core FUN_0102b7ac @ 0x102b7ac  (CFG-directed candidate) */
/* net-core FUN_0102b7ac @ 0x102b7ac
 * ESB radio-state setter reached from the cpunet-hw-id IPC handler's
 * sub-command 12 ("P"): pairing request. */
void FUN_0102b7ac(void)
{
#ifdef G1_COHESIVE_BUILD
/* P4 iteration 21 - the ESB radio operating-state word (original VA
 * 0x210005b4) is emitted by recon/application/net/src/timeslot_owner.c.  Left
 * as a raw literal it landed inside the emitted g1_timeslot_request_earliest
 * and overwrote that request's `request_type` byte.  Parity keeps the
 * original literal. */
extern volatile unsigned int g_net_radio_op_state;
#define G1_NET_RADIO_OP_STATE (&g_net_radio_op_state)
#else
#define G1_NET_RADIO_OP_STATE ((volatile unsigned int *)0x210005b4u)
#endif

    *G1_NET_RADIO_OP_STATE = 3u;
}
