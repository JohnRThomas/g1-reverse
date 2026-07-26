/* readable reconstruction; identity: FUN_00018c48 @ 0x00018c48
 * public-name: bt_ancs_data_source_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   enqueue_ancs                             <= FUN_00018bb4 @ 0x00018bb4
 *   bt_ancs_data_source_handler              <= FUN_00018c48 @ 0x00018c48
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   k_uptime_get_32                          <= FUN_0007c0c8 @ 0x0007c0c8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9a992                             @ 0x0009a992   [INLINED -- G6 literal batch]
 *   rodata_9a9cd                             @ 0x0009a9cd   [INLINED -- G6 literal batch]
 *   rodata_9b20d                             @ 0x0009b20d   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_last_cmd_id                       @ 0x2000231c
 *   g_ancs_notif_attr_id_latest              @ 0x20006aa0
 *   g_ancs_notif_evt_id_latest               @ 0x20006aac
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ancs_attr_data_pending                 @ 0x2000ff71
 */
/* Reconstructed FUN_00018c48 @ 0x18c48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int log_message(int, ...);
extern int get_device_info(void);
extern int ancs_get_conn_ctx(int);
extern int enqueue_ancs(int);
extern int debug_print(uintptr_t, ...);
extern int k_sem_give(int);
extern int k_uptime_get_32(void);
extern int memset_bytes(int,int,int);

void bt_ancs_data_source_handler(int param_1, unsigned char *param_2, int param_3)
{
    volatile uint32_t *puVar1 = (volatile uint32_t*)0x20006aa0;
    volatile char *pcVar2 = (volatile char*)0x2000ff71;
    volatile int *piVar3 = (volatile int*)0x20006aac;
    volatile int *piVar4 = (volatile int*)0x2000230c;
    volatile int *piVar5 = (volatile int*)0x2000231c;
    volatile int *g_d70 = (volatile int*)0x20007554;
    int iVar6, iVar7, iVar8;
    unsigned int uVar9, uVar10;

    iVar6 = ancs_get_conn_ctx(param_1);
    if (0 < *piVar4) {
        if (*g_d70 == 0) {
            log_message(((unsigned long)"%s(): bt_ancs_data_source_handler response->command_id %d\n"), ((unsigned long)"bt_ancs_data_source_handler"), (unsigned int)*param_2, 0, param_1, (int)param_2, param_3);
        } else {
            debug_print(((unsigned long)"%s(): bt_ancs_data_source_handler response->command_id %d\n"), ((unsigned long)"bt_ancs_data_source_handler"), (unsigned int)*param_2,
                         *(volatile unsigned int*)0x20007554, param_1,
                         (uintptr_t)param_2, param_3);
        }
    }
    if (*param_2 == 0) {
        if (*(int *)(param_2 + 8) == 0) {
            uVar9 = *(uint32_t *)(param_2 + 8);
            uVar10 = *(uint32_t *)(param_2 + 0xc);
            *puVar1 = *(uint32_t *)(param_2 + 4);
            puVar1[1] = uVar9;
            puVar1[2] = uVar10;
            *pcVar2 = '\x01';
        }
    } else if ((*param_2 == 1) && (*pcVar2 != '\0')) {
        if (*piVar3 != *piVar5) {
            iVar7 = k_uptime_get_32();
            iVar8 = get_device_info();
            if (9999 < (unsigned int)(iVar7 - *(int *)(iVar8 + 0xae8))) {
                iVar7 = get_device_info();
                if (*(char *)(iVar7 + 0xd5) != '\v') {
                    iVar7 = get_device_info();
                    if (*(char *)(iVar7 + 0xd5) != '\n') {
                        iVar7 = get_device_info();
                        if (*(char *)(iVar7 + 0xd5) != '\t') {
                            iVar7 = get_device_info();
                            if (*(char *)(iVar7 + 0xd5) != '\f') {
                                iVar7 = get_device_info();
                                if ((*(char *)(iVar7 + 0xd5) != '\x10') &&
                                    (iVar7 = get_device_info(), *(char *)(iVar7 + 0xd5) != '\x0e')) {
                                    *piVar5 = *piVar3;
                                    *(unsigned int *)(iVar6 + 0x1e4) = (unsigned int)*(unsigned char *)((int)piVar3 + 4);
                                    enqueue_ancs(iVar6 + 0x34);
                                    if (0 < *piVar4) {
                                        if (*g_d70 == 0) {
                                            log_message(((unsigned long)"%s(): =========================>bt_ancs_get_attr_data_sem %d evt_id %d action %d\n"), ((unsigned long)"bt_ancs_data_source_handler"), *piVar3, (unsigned int)*(unsigned char *)((int)piVar3 + 4),
                                                        *(uint32_t *)(iVar6 + 0x1e4));
                                        } else {
                                            debug_print(((unsigned long)"%s(): =========================>bt_ancs_get_attr_data_sem %d evt_id %d action %d\n"), ((unsigned long)"bt_ancs_data_source_handler"),
                                                         *piVar3,
                                                         (unsigned int)*(unsigned char *)((int)piVar3 + 4),
                                                         *(uint32_t *)(iVar6 + 0x1e4));
                                        }
                                    }
                                    memset_bytes(iVar6 + 0x34, 0, 0x1b4);
                                    k_sem_give(iVar6 + 0x1e8);
                                    *pcVar2 = '\0';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
