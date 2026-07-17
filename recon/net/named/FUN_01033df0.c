/* readable reconstruction; identity: FUN_01033df0 @ 0x01033df0
 * public-name: FUN_01033df0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 * address symbols (name @ address):
 *   rodata_103c05c                           @ 0x0103c05c
 *   rodata_103e4af                           @ 0x0103e4af
 *   rodata_103e4d1                           @ 0x0103e4d1
 *   g_net_radio_trx_ppi_ch_a                 @ 0x2100645a
 *   g_esb_ppi_ch_id_1                        @ 0x2100645b
 *   g_154_dppi_channel_ack                   @ 0x2100645c
 *   g_esb_ppi_ch_id_3                        @ 0x2100645d
 *   g_net_radio_trx_ppi_ch_e                 @ 0x2100645e
 *   g_esb_ppi_ch_id_5                        @ 0x2100645f
 *   g_esb_ppi_ch_id_6                        @ 0x21006460
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01033df0 @ 0x1033df0  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_01034458(unsigned int a);
extern int FUN_01034480(unsigned int a);
extern void z_impl_z_log_msg_static_create(unsigned int a, unsigned int b, void *c, unsigned int d);

#define DAT_eb0 0x21006460u
#define DAT_eb4 0x0bad0000
#define DAT_eb8 0x2100645fu
#define DAT_ebc 0x2100645eu
#define DAT_ec0 0x2100645du
#define DAT_ec4 0x2100645cu
#define DAT_ec8 0x2100645bu
#define DAT_ecc 0x2100645au
#define DAT_ed0 0x0103e4afu
#define DAT_ed4 0x0103c05cu
#define DAT_ed8 0x41008000u
#define DAT_edc 0x4100f000u
#define DAT_ee0 0x0103e4d1u

typedef struct {
    int severity;
    unsigned int message;
    int status;
    unsigned int transport_reserved[3];
} diagnostic_record_t;

unsigned int FUN_01033df0(void)
{
    int iStack_20;
    int iVar3 = DAT_eb4;
    unsigned char *pbVar2;
    int matched;

    iStack_20 = FUN_01034458(DAT_eb0);
    matched = 0;
    if (iStack_20 == iVar3) {
        iStack_20 = FUN_01034458(DAT_eb8);
        if (iStack_20 == iVar3) {
            iStack_20 = FUN_01034458(DAT_ebc);
            pbVar2 = (unsigned char *)DAT_ec0;
            if (iStack_20 == iVar3) {
                iStack_20 = FUN_01034458(DAT_ec0);
                if (iStack_20 == iVar3) {
                    iStack_20 = FUN_01034458(DAT_ec4);
                    if (iStack_20 == iVar3) {
                        iStack_20 = FUN_01034458(DAT_ec8);
                        if (iStack_20 == iVar3) {
                            matched = 1;
                        }
                    }
                }
            }
        }
    }

    if (matched) {
        int rv = FUN_01034480(DAT_ecc);
        if (rv == iStack_20) {
            unsigned char bVar1 = *pbVar2;
            *(volatile unsigned int *)(DAT_ed8 + 400) = (unsigned int)bVar1 | 0x80000000u;
            *(volatile unsigned int *)(DAT_edc + 0x504) = 1u << (unsigned int)bVar1;
            return 0;
        } else {
            diagnostic_record_t local;
            local.severity = 3;
            local.message = DAT_ed0;
            local.status = rv;
            z_impl_z_log_msg_static_create(DAT_ed4, 0x1840, &local, 0);
            return 0xffffffed;
        }
    } else {
        diagnostic_record_t local;
        local.severity = 3;
        local.message = DAT_ee0;
        local.status = iStack_20;
        z_impl_z_log_msg_static_create(DAT_ed4, 0x1840, &local, 0);
        return 0xffffffed;
    }
}
