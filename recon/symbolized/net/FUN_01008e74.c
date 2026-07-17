#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01008e74 @ 0x01008e74
 * public-name: FUN_01008e74
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 *   g_net_mac_pib_ext                        @ 0x21000a40
 */
/* net-core FUN_01008e74 @ 0x1008e74  (parity 500 trials PROVEN) */

#include <stdint.h>

extern int  FUN_01008a58(int, int);
extern void FUN_0101fbbc(void);
/* Ghidra split these two reachable return blocks out of the declared body.
 * Keep them as explicit tail-block oracles rather than silently inlining them. */
/* Original interior labels: 0x01008fc0 => -45, 0x01008fc6 => -12. */
static int FUN_01008fc0(void) { return -45; }
static int FUN_01008fc6(void) { return -12; }

int FUN_01008e74(int param_1, int param_2, uint16_t *param_3)
{
    volatile uint8_t *D = (volatile uint8_t *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/; /* DAT_01008fcc */
    volatile uint8_t *E = (volatile uint8_t *)((unsigned long)&g_net_mac_pib_ext) /*=0x21000a40*/; /* DAT_01008fd0 */
    uint8_t *q;
    int r;

    if (param_1 != 0)
        return FUN_01008fc0();
    if (D[0x2c] != 0)
        return -1;

    if (param_2 != 0) {
        if (param_3 == 0)
            return -0x16;
        q = (uint8_t *)param_3;
        switch (param_2) {
        case 1:
            D[0] = q[0];
            break;
        case 2:
            D[1] = q[0];
            break;
        case 3:
            if (q[2] == 0 || q[3] == 0 || q[0] < 0x1b || q[1] < 0x1b)
                return -0x16;
            *(volatile uint32_t *)(D + 5) = *(uint32_t *)param_3;
            break;
        case 4:
            if (q[0] < D[3])
                return -0x16;
            D[2] = q[0];
            break;
        case 5:
            if (D[0x1f] != 0 && q[0] < 2)
                return -0x16;
            D[9] = q[0];
            break;
        case 6:
            *(volatile uint16_t *)(D + 0xa) = param_3[0];
            break;
        case 7:
            if (param_3[0] > 0xff)
                return -0x16;
            D[0xc] = (uint8_t)param_3[0];
            break;
        case 8:
            if (q[0] > D[2])
                return -0x16;
            D[3] = q[0];
            break;
        case 9:
            D[4] = q[0];
            break;
        case 0xa:
            if (D[0x1e] == 0) {
                if (q[0] > 1) { D[0xd] = q[0]; break; }
            } else {
                if (q[0] != 0) { D[0xd] = q[0]; break; }
            }
            return -0x16;
        case 0xb:
            if (q[0] > 8)
                return -0x16;
            D[0xe] = q[0];
            break;
        case 0xc:
            if (q[0] > D[2])
                return -0x16;
            D[0xf] = q[0];
            break;
        case 0xd:
            if (q[0] == 0 || (uint8_t)(q[1] - 1) > 0xf8)
                return -0x16;
            *(volatile uint16_t *)(D + 0x10) = param_3[0];
            E[2] = q[2];
            break;
        case 0xe:
            D[0x13] = q[0];
            FUN_0101fbbc();
            break;
        case 0xf:
            if (q[0] == 0)
                return -0x16;
            D[0x14] = q[0];
            break;
        case 0x10:
            D[0x15] = q[0];
            break;
        case 0x11:
            if (q[0] > 0xe)
                return -0x16;
            D[0x16] = q[0];
            break;
        case 0x12:
            D[0x17] = q[0];
            break;
        case 0x13:
            D[0x18] = q[0];
            break;
        case 0x14:
            D[0x19] = q[0];
            break;
        case 0x15:
            D[0x1a] = q[0];
            break;
        case 0x16:
            *(volatile uint16_t *)(D + 0x1b) = param_3[0];
            break;
        default:
            return FUN_01008fc0();
        }
    }

    /* LAB_01008eb4 */
    r = FUN_01008a58(0, 1);
    if (r < 0x10000)
        D[0x2d] = 1;
    else
        r = FUN_01008fc6();
    return r;
}
