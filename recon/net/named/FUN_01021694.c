/* readable reconstruction; identity: FUN_01021694 @ 0x01021694
 * public-name: FUN_01021694
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   radio_phy_airtime_tail_get               <= FUN_010209e0 @ 0x010209e0
 *   radio_phy_airtime_base_get               <= FUN_010209f0 @ 0x010209f0
 * address symbols (name @ address):
 *   rodata_103c5c4                           @ 0x0103c5c4
 */
/* net-core FUN_01021694 @ 0x1021694  (parity 300 trials PROVEN) */

extern int radio_phy_airtime_base_get(unsigned int a);
extern int radio_phy_airtime_tail_get(int a, int b, int c, int d);

int FUN_01021694(int param_1, unsigned int param_2, int param_3)
{
    int iVar2;
    unsigned long long lVar1;
    int val;
    unsigned int inner;
    iVar2 = radio_phy_airtime_base_get(param_2);
    val = *(volatile int *)(0x0103c5c4 + param_3*4 + 0x14);
    inner = (unsigned int)(param_1*1000 + val + 2999 - iVar2);
    lVar1 = (unsigned long long)0x10624dd3UL * (unsigned long long)inner;
    iVar2 = radio_phy_airtime_tail_get(param_3, 1000, iVar2, (int)lVar1);
    return iVar2 + 5 + (unsigned int)(lVar1 >> 0x26);
}
