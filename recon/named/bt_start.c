/* readable reconstruction; identity: FUN_00019308 @ 0x00019308
 * public-name: bt_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_device_serial_buf                    <= FUN_000232b0 @ 0x000232b0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   bt_set_name_internal                     <= FUN_00054c74 @ 0x00054c74
 *   bt_le_adv_start                          <= FUN_00055998 @ 0x00055998
 *   k_msleep_ticks32768_d                    <= FUN_0007c0a8 @ 0x0007c0a8
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   uptime_ticks_get                         <= FUN_00086698 @ 0x00086698
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 *   __strcpy_chk                             <= FUN_00086ffe @ 0x00086ffe
 * address symbols (name @ address):
 *   rodata_8839c                             @ 0x0008839c
 *   rodata_9ac4c                             @ 0x0009ac4c   [INLINED -- G6 literal batch]
 *   rodata_9ac60                             @ 0x0009ac60   [INLINED -- G6 literal batch]
 *   rodata_9ac7c                             @ 0x0009ac7c
 *   rodata_9ac84                             @ 0x0009ac84   [INLINED -- G6 literal batch]
 *   rodata_9ac9d                             @ 0x0009ac9d   [INLINED -- G6 literal batch]
 *   rodata_9acb2                             @ 0x0009acb2   [INLINED -- G6 literal batch]
 *   rodata_9acc4                             @ 0x0009acc4   [INLINED -- G6 literal batch]
 *   rodata_9ace0                             @ 0x0009ace0   [INLINED -- G6 literal batch]
 *   rodata_9acf9                             @ 0x0009acf9   [INLINED -- G6 literal batch]
 *   rodata_9ad0e                             @ 0x0009ad0e   [INLINED -- G6 literal batch]
 *   rodata_9ad20                             @ 0x0009ad20   [INLINED -- G6 literal batch]
 *   rodata_9ad4b                             @ 0x0009ad4b   [INLINED -- G6 literal batch]
 *   rodata_9b13f                             @ 0x0009b13f   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_20002350                               @ 0x20002350
 *   g_20002358                               @ 0x20002358
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2000ff72                               @ 0x2000ff72
 *   g_2000ff73                               @ 0x2000ff73
 *   g_2000ff87                               @ 0x2000ff87
 */
/* Reconstructed bt_start @ 0x00019308 (FUN_00019308; CFG-verified). */
/* Firmware application Bluetooth-start owner; prior LIBRARY class was incorrect. */
#include <stdint.h>
#include <stddef.h>
extern void k_msleep_ticks32768_d(uint32_t);
extern uintptr_t get_device_info(void);
extern int get_device_type(void);
extern uintptr_t get_device_serial_buf(void);
extern void __strcpy_chk(void *, const void *, uint32_t);
extern void log_message(uintptr_t, ...);
extern void debug_print(void);
extern int is_battery_critical(void);
extern void vdprintf_to_fd(uintptr_t, ...);
extern uint32_t strlen(uintptr_t);
extern int bt_set_name_internal(uintptr_t);
extern int bt_le_adv_start(void *, uintptr_t, uint32_t, uintptr_t, uint32_t);
extern uint64_t uptime_ticks_get(void);

#define INFO_BYTE(offset) (*(volatile uint8_t *)(get_device_info() + (offset)))

int bt_start(void)
{
    volatile uint8_t *busy = (volatile uint8_t *)(uintptr_t)0x2000ff72u;
    while (*busy != 0u) k_msleep_ticks32768_d(1u);
    *busy = 1u;
    int result;
    uintptr_t info = get_device_info();
    uint8_t state = *(volatile uint8_t *)(info + 0x1058u);
    if (state == 2u) { result = 0; goto out; }
    info = get_device_info();
    if (*(volatile uint8_t *)(info + 0x1058u) == 0u) { result = 0; goto out; }

    volatile uint8_t *adv = (volatile uint8_t *)(uintptr_t)0x20002358u;
    volatile uint8_t *name_data = (volatile uint8_t *)(uintptr_t)0x2000ff73u;
    *(volatile uint16_t *)(adv + 8u) = 0x14ffu;
    uint32_t device_kind = get_device_type() == 1 ? 1u : 2u;
    *(volatile uintptr_t *)(adv + 0x0cu) = (uintptr_t)name_data;
    *name_data = (uint8_t)device_kind;
    __strcpy_chk((void *)(name_data + 1u), (const void *)get_device_serial_buf(), 0x13u);
    log_message(0x0009ac4cu, INFO_BYTE(2u), 19u, device_kind);

    int left = get_device_type() == 1;
    int critical = is_battery_critical() == 1;
    const uintptr_t name = 0x2000ff87u;
    const uintptr_t base = 0x0009ac7cu;
    uint8_t id = INFO_BYTE(2u);
    if (left) {
        if (critical) {
            if (id != 0xffu) {
                id=INFO_BYTE(2u);
                uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
                vdprintf_to_fd(name,0u,0x20u,0x0009ac60u,base,1u,4u,5u,id,a,b,c);
            } else {
                uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
                vdprintf_to_fd(name,0u,0x20u,0x0009ac84u,base,1u,4u,5u,a,b,c);
            }
        } else if (id != 0xffu) {
            id=INFO_BYTE(2u);
            uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
            vdprintf_to_fd(name,0u,0x20u,0x0009ac9du,base,id,a,b,c);
        } else {
            uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
            vdprintf_to_fd(name,0u,0x20u,0x0009acb2u,base,a,b,c);
        }
    } else {
        if (critical) {
            if (id != 0xffu) {
                id=INFO_BYTE(2u);
                uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
                vdprintf_to_fd(name,0u,0x20u,0x0009acc4u,base,1u,4u,5u,id,a,b,c);
            } else {
                uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
                vdprintf_to_fd(name,0u,0x20u,0x0009ace0u,base,1u,4u,5u,a,b,c);
            }
        } else if (id != 0xffu) {
            id=INFO_BYTE(2u);
            uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
            vdprintf_to_fd(name,0u,0x20u,0x0009acf9u,base,id,a,b,c);
        } else {
            uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
            vdprintf_to_fd(name,0u,0x20u,0x0009ad0eu,base,a,b,c);
        }
    }

    volatile uint8_t *name_ad = (volatile uint8_t *)(uintptr_t)0x20002350u;
    *(volatile uintptr_t *)(name_ad + 4u) = name;
    *(volatile uint8_t *)(name_ad + 1u) = (uint8_t)strlen(name);
    result = bt_set_name_internal(name);
    if (result != 0) {
        if (*(volatile int32_t *)(uintptr_t)0x2000230cu > 0) {
            if (*(volatile uint32_t *)(uintptr_t)0x20007554u == 0u)
                log_message(0x0009ad20u,0x0009b13fu,result);
            else debug_print();
        }
        goto out;
    }

    uint32_t params[5];
    const volatile uint32_t *defaults=(const volatile uint32_t *)(uintptr_t)0x0008839cu;
    for (unsigned i=0;i<5;i++) params[i]=defaults[i];
    result = bt_le_adv_start(params,0x20002358u,2u,0x20002350u,1u);
    if (result == 0) {
        info=get_device_info();
        *(volatile uint8_t *)(info+0x1058u)=2u;
        uint64_t ms=(uptime_ticks_get()*1000u+0x7fffu)>>15;
        log_message(0x0009ad4bu,name,(uint32_t)ms,(uint32_t)(ms>>32));
    }
out:
    *busy=0u;
    return result;
}
