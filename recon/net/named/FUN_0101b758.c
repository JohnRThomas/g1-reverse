/* readable reconstruction; identity: FUN_0101b758 @ 0x0101b758
 * public-name: FUN_0101b758
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_conn_teardown_busy_flag            @ 0x2100111c
 */
/* net-core FUN_0101b758 @ 0x101b758  (parity 300 trials PROVEN) */
#define P_0101b7e0 0x2100111c

extern void sdc_assertion_fail(int, int);
extern int FUN_01009dd8(void *);
extern int FUN_01009d18(int, int);
extern void FUN_0102411c(int);
extern int FUN_01022ebc(int);
extern void FUN_0101dd0c(int);

void FUN_0101b758(void)
{
  unsigned char *puVar1;
  int iVar2;
  int iVar3;
  struct {
    short *item;
    unsigned int metadata;
    /* The queue API owns a full receive slot even though this consumer only
       interprets its two-word header. */
    unsigned int queue_storage[4];
  } message;

  puVar1 = (unsigned char *)P_0101b7e0;
  *(volatile unsigned char *)P_0101b7e0 = 1;

L_loop_top:
  message.item = (short *)0;
  message.metadata = 0;

L_inner:
  iVar3 = FUN_01009dd8(&message);
  if (iVar3 != 0) goto LAB_end;
  if (message.item == (short *)0 ||
      *((unsigned char *)message.item + 0x300) == 0) goto L_inner;

  if (*message.item == (short)-1) goto LAB_end;
  iVar3 = FUN_01009d18(*message.item, 0);
  if (iVar3 == 0) goto L_abort1;

  FUN_0102411c(*(unsigned char *)(iVar3 + 0x301));
  *(unsigned char *)(iVar3 + 0x300) = 0;
  iVar2 = FUN_01022ebc(*(unsigned char *)(iVar3 + 0x301));
  if (iVar2 == 0) goto L_abort2;

  *(unsigned char *)(iVar3 + 0x301) = 0x20;
  FUN_0101dd0c(iVar3 + 0x2d8);
  goto L_loop_top;

L_abort1:
  sdc_assertion_fail(0x35, 0x1d0);
L_abort2:
  sdc_assertion_fail(0x35, 0x1bf);
  return;

LAB_end:
  *puVar1 = 0;
  return;
}
