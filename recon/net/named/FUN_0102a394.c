/* readable reconstruction; identity: FUN_0102a394 @ 0x0102a394
 * public-name: FUN_0102a394
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ctrl_report_field0                 @ 0x210045e8
 *   g_net_ctrl_report_field1                 @ 0x210045ec
 *   g_net_ctrl_report_field2                 @ 0x210045f0
 *   g_sdc_hci_transport_obj                  @ 0x210045f4
 *   g_net_ctrl_status_byte                   @ 0x21004c9f
 */
/* net-core FUN_0102a394 @ 0x102a394  (parity 300 trials PROVEN) */
extern void FUN_0103b62e(void *dst, int val, int len);
extern void FUN_0103961c(int a);

typedef int (*call_fn_t)(void *buf, int len);

void FUN_0102a394(void)
{
    unsigned char buf[0x24];
    unsigned int *pu = (unsigned int *)0x210045f0;
    int *piVar1 = (int *)0x210045f4;
    unsigned int *pu2 = (unsigned int *)0x210045ec;
    unsigned int *pu3 = (unsigned int *)0x210045e8;
    unsigned char *pu4 = (unsigned char *)0x21004c9f;
    char cVar3 = 10;

    FUN_0103b62e(buf + 4, 0, 0x1c);

    *(unsigned short *)(buf + 0) = 0x701;
    *(unsigned int *)(buf + 2) = *pu;
    *(unsigned int *)(buf + 6) = *pu2;
    *(unsigned int *)(buf + 0xa) = *pu3;
    *(unsigned char *)(buf + 0xe) = *pu4;

    while (1) {
        int obj = *(int *)piVar1;
        call_fn_t f = *(call_fn_t *)(obj + 0xa8);
        int iVar2 = f(buf, 0x20);
        if (iVar2 > 0) {
            break;
        }
        cVar3 = (char)(cVar3 - 1);
        if ((cVar3 & 0xff) == 0) {
            break;
        }
        FUN_0103961c(10);
    }
}
