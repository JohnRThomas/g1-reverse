/* readable reconstruction; identity: FUN_010215d8 @ 0x010215d8
 * public-name: controller_radio_time_mode2_to_mode1
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   radio_phy_airtime_base_get               <= FUN_010209f0 @ 0x010209f0
 *   controller_radio_time_mode2_to_mode1     <= FUN_010215d8 @ 0x010215d8
 */
/* net-core FUN_010215d8 @ 0x10215d8  (parity 300 trials PROVEN) */

extern unsigned int radio_phy_airtime_base_get(unsigned int);
#define DAT_010215f0 ((unsigned int)0x10624dd3)

int controller_radio_time_mode2_to_mode1(int param_1, unsigned int param_2)
{
    unsigned int uVar1 = radio_phy_airtime_base_get(param_2);
    unsigned long long prod = (unsigned long long)DAT_010215f0 * (unsigned long long)uVar1;
    return param_1 - (unsigned int)(prod >> 0x26);
}
