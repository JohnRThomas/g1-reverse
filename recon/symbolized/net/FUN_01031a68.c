#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01031a68 @ 0x01031a68
 * public-name: FUN_01031a68
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 *   k_work_init                              <= FUN_01036bec @ 0x01036bec
 *   z_device_is_ready                        <= FUN_0103b0f0 @ 0x0103b0f0
 * address symbols (name @ address):
 *   rodata_10320d9                           @ 0x010320d9
 *   rodata_103bf70                           @ 0x0103bf70
 *   rodata_103c044                           @ 0x0103c044
 *   rodata_103c11c                           @ 0x0103c11c
 *   rodata_103d73e                           @ 0x0103d73e
 *   rodata_103e216                           @ 0x0103e216
 *   rodata_103e23d                           @ 0x0103e23d
 *   rodata_103e25d                           @ 0x0103e25d
 */
/* net-core FUN_01031a68 @ 0x1031a68  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void k_work_init(unsigned int a, unsigned int b);
extern void FUN_01032680(void);
extern void FUN_01009054(void *a);
extern void z_impl_z_log_msg_static_create(unsigned int a, unsigned int b, void *c, void *d);
extern int z_device_is_ready(unsigned int a);
extern int FUN_010091e8(void *a);
extern int FUN_01031804(unsigned int a, unsigned int b);
extern int32_t sdc_default_tx_power_set(int8_t requested_power_level); /* FUN_010091cc */
extern int FUN_01008fd4(unsigned int a, unsigned int b);
extern int thunk_FUN_0101f650(void *a);
extern void FUN_01031814(void);

#define DAT_b50 0x0103af63u
#define DAT_b54 0x21004974u
#define DAT_b58 ((unsigned long)&rodata_103d73e) /*=0x103d73e*/
#define DAT_b5c ((unsigned long)&rodata_103e216) /*=0x103e216*/
#define DAT_b60 0x01000003u
#define DAT_b64 0x01401cc0u
#define DAT_b68 ((unsigned long)&rodata_103c044) /*=0x103c044*/
#define DAT_b6c ((unsigned long)&rodata_103bf70) /*=0x103bf70*/
#define DAT_b70 ((unsigned long)&rodata_103e23d) /*=0x103e23d*/
#define DAT_b74 ((unsigned long)&rodata_103c11c) /*=0x103c11c*/
#define DAT_b78 ((unsigned long)&rodata_103e25d) /*=0x103e25d*/
#define DAT_b7c 0x21002b90u
#define DAT_b80 ((unsigned long)&rodata_10320d9) /*=0x10320d9*/
#define DAT_b84 0x003d0900u

typedef struct {
    unsigned int code;
    unsigned int message;
    int status;
    unsigned short tag;
    unsigned short reserved;
} diagnostic_record_t;

typedef struct {
    unsigned int timer_period;
    unsigned char startup_context[20];
    unsigned int credentials[3];
    unsigned int reserved;
    struct {
        unsigned int code;
        unsigned int message;
    } missing_service;
    unsigned int tail_reserved;
} init_frame_t;

typedef struct {
    unsigned int transport_reserved[4];
    diagnostic_record_t startup;
    init_frame_t frame;
    unsigned int alignment_reserved;
} init_workspace_t;

int FUN_01031a68(void)
{
    int iVar1, iVar2;
    init_workspace_t workspace;

    k_work_init(DAT_b54, DAT_b50);
    FUN_01032680();
    FUN_01009054(workspace.frame.startup_context);

    workspace.startup.code = DAT_b60;
    workspace.startup.message = DAT_b58;
    workspace.startup.status = (int)DAT_b5c;
    workspace.startup.tag = 0x200;
    z_impl_z_log_msg_static_create(DAT_b68, DAT_b64, &workspace.startup,
                 workspace.frame.startup_context);

    iVar1 = z_device_is_ready(DAT_b6c);
    if (iVar1 == 0) {
        workspace.frame.missing_service.code = 2;
        workspace.frame.missing_service.message = DAT_b70;
        z_impl_z_log_msg_static_create(DAT_b68, 0x1040,
                     &workspace.frame.missing_service, 0);
        return -0x13;
    }

    {
        unsigned int *src = (unsigned int *)DAT_b74;
        workspace.frame.credentials[0] = src[0];
        workspace.frame.credentials[1] = src[1];
        workspace.frame.credentials[2] = src[2];
    }
    iVar1 = FUN_010091e8(workspace.frame.credentials);
    if (iVar1 != 0) {
        workspace.startup.code = 3;
        workspace.startup.message = DAT_b78;
        workspace.startup.status = iVar1;
        z_impl_z_log_msg_static_create(DAT_b68, 0x1840, &workspace.startup, 0);
        return -0x16;
    }

    iVar1 = FUN_01031804(0xffffffffu, 0xffffffffu);
    if (iVar1 != 0) {
        return iVar1;
    }

    iVar1 = sdc_default_tx_power_set(3);
    if (iVar1 == 0) {
        iVar1 = FUN_01008fd4(DAT_b80, DAT_b7c);
        if (iVar1 == 0) {
            workspace.frame.timer_period = DAT_b84;
            iVar2 = thunk_FUN_0101f650(&workspace.frame.timer_period);
            if (iVar2 != 0) {
                goto LAB_b24;
            }
        }
        FUN_01031814();
    } else {
    LAB_b24:
        FUN_01031814();
        iVar1 = -0x86;
    }
    return iVar1;
}
