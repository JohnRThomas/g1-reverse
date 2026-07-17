#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00021460 @ 0x00021460
 * public-name: ble_process_req_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   audio_fw_load_get_wrapper                <= FUN_00019b54 @ 0x00019b54
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   send_dmic_msg                            <= FUN_00019ed4 @ 0x00019ed4
 *   build_status_notify_packet               <= FUN_00021334 @ 0x00021334
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   post_notification_cmd_process            <= FUN_000338ec @ 0x000338ec
 *   z_impl_k_timer_start                     <= FUN_00075174 @ 0x00075174
 *   ble_flush_queued_indications             <= FUN_0007c20a @ 0x0007c20a
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_9b8fd                             @ 0x0009b8fd
 *   rodata_9d4e4                             @ 0x0009d4e4
 *   rodata_9d518                             @ 0x0009d518
 *   rodata_9d546                             @ 0x0009d546
 *   rodata_9d587                             @ 0x0009d587
 *   rodata_9d5af                             @ 0x0009d5af
 *   rodata_9d5da                             @ 0x0009d5da
 *   rodata_9d64e                             @ 0x0009d64e
 *   rodata_9d671                             @ 0x0009d671
 *   rodata_9d681                             @ 0x0009d681
 *   rodata_9d69e                             @ 0x0009d69e
 *   rodata_9e032                             @ 0x0009e032
 *   rodata_9e04e                             @ 0x0009e04e
 *   rodata_9e08b                             @ 0x0009e08b
 *   g_log_level                              @ 0x2000230c
 *   g_ble_work_timer                         @ 0x20003d28
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dashboard_lock_sent_flags              @ 0x2000756c
 *   g_dashboard_lock_ready_flags             @ 0x20007570
 *   g_2000ffa7                               @ 0x2000ffa7
 *   g_ble_xfer_seq_prev                      @ 0x20018d99
 *   g_ble_xfer_seq_cur                       @ 0x20018d9a
 *   g_ble_dispatch_pending_marker            @ 0x20018d9b
 */
/* Reconstructed ble_process_req_dispatch @ 0x21460  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern void log_message(uint32_t, uint32_t, ...);
extern int  get_device_type(void);
extern uintptr_t get_device_info(void);
extern int  FUN_00019b2c(void);
extern void audio_fw_load_get_wrapper(void *, void *, uint32_t);
extern void debug_print(uint32_t, uint32_t, ...);
extern void send_dmic_msg(void *);
extern void build_status_notify_packet(void *, void *);
extern void mark_master_or_low_battery_flag(void);
extern void post_notification_cmd_process(void *, void *, void *);
extern void FUN_00056a68(int, uint32_t);
extern void z_impl_k_timer_start(uint32_t, uint32_t, uint32_t, uint32_t,
                         uint32_t, uint32_t);
extern void FUN_0007c176(uint32_t, uint32_t);
extern void FUN_0007c1aa(uintptr_t, uint32_t, uint32_t, uint32_t);
extern void ble_flush_queued_indications(void *);
extern void memcpy(void *, const void *, uint32_t);
extern void FUN_00086c1e(void *, const void *, uint32_t, uint32_t);
extern void memset_bytes(void *, int, uint32_t);
extern void strcpy(char *, const char *);
extern void ble_process_get_req(uint8_t *context, uint8_t *packet,
                                uint8_t *request_state);
extern void ble_process_put_req(uint8_t *context, uint8_t *packet,
                                uint8_t *request_state);

#define LVL_A (*(volatile int32_t*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LVL_B (*(volatile int32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define P_20007570 ((volatile uint32_t*)((unsigned long)&g_dashboard_lock_ready_flags) /*=0x20007570*/)
#define P_2000756c ((volatile uint32_t*)((unsigned long)&g_dashboard_lock_sent_flags) /*=0x2000756c*/)
#define G_20018d9b (*(volatile uint8_t*)((unsigned long)&g_ble_dispatch_pending_marker) /*=0x20018d9b*/)
#define G_20018d9a (*(volatile uint8_t*)((unsigned long)&g_ble_xfer_seq_cur) /*=0x20018d9a*/)
#define G_20018d99 (*(volatile uint8_t*)((unsigned long)&g_ble_xfer_seq_prev) /*=0x20018d99*/)

typedef void (*response_callback_t)(const void *, uint32_t);

typedef struct __attribute__((packed)) { uint16_t value; } packed_u16_t;
typedef struct __attribute__((packed)) { int16_t value; } packed_i16_t;
typedef struct __attribute__((packed)) { uint32_t value; } packed_u32_t;

static inline uint16_t load_u16(const volatile void *address)
{
    return ((const volatile packed_u16_t *)address)->value;
}

static inline int16_t load_i16(const volatile void *address)
{
    return ((const volatile packed_i16_t *)address)->value;
}

static inline uint32_t load_u32(const volatile void *address)
{
    return ((const volatile packed_u32_t *)address)->value;
}

static inline void store_u16(volatile void *address, uint16_t value)
{
    ((volatile packed_u16_t *)address)->value = value;
}

static inline void store_u32(volatile void *address, uint32_t value)
{
    ((volatile packed_u32_t *)address)->value = value;
}

unsigned int ble_process_req_dispatch(uint8_t *param_1, uint8_t *packet, uint8_t *param_3)
{
    uint32_t command_id = *packet;
    uint8_t *puVar15;
    int32_t iVar13, iVar14;
    uint8_t bVar10, bVar3;
    uint16_t uVar2;
    uint8_t returnStatus;
    uint8_t *puVar12;
    uint8_t response[20];
    uint8_t transfer[0x84];

    if ((uint32_t)(command_id - 1) < 0x27u) {
        ble_process_put_req(param_1, packet, param_3);
        return 0;
    }
    if ((uint32_t)(command_id - 0x29u) < 0x1du) {
        ble_process_get_req(param_1, packet, param_3);
        return 0;
    }
    if ((uint32_t)(command_id - 0x47u) > 9u) {
        if (((command_id + 0xfu) & 0xffu) > 5u) {
            if (0 < LVL_A) {
                uint32_t backend_state = (uint32_t)LVL_B;
                if (backend_state == 0) {
                    log_message(((unsigned long)&rodata_9d681) /*=0x9d681*/, ((unsigned long)&rodata_9e08b) /*=0x9e08b*/, command_id);
                } else {
                    debug_print(((unsigned long)&rodata_9d681) /*=0x9d681*/, ((unsigned long)&rodata_9e08b) /*=0x9e08b*/, command_id);
                }
            }
            {
                response_callback_t pc = *(response_callback_t *)(param_1 + 0xc);
                pc((const void *)((unsigned long)&rodata_9d69e) /*=0x9d69e*/, 3);
            }
            return 0;
        }
        store_u32(transfer, 0);
        memset_bytes(transfer + 4, 0, 0x11);
        if (command_id == 0xf4) { ble_flush_queued_indications(param_1); return 0; }
        if (command_id == 0xf5) { build_status_notify_packet(param_1, param_3); return 0; }
        if (command_id == 0xf1) {
            if ((*(volatile uint8_t *)(param_3 + 2) & 0xfd) == 0xc9) { return 0; }
            if (*(volatile uint8_t *)(param_3 + 2) == 0xcc) {
                send_dmic_msg(param_1);
                return 0;
            }
            if (1 < LVL_A) {
                uint32_t backend_state = (uint32_t)LVL_B;
                if (backend_state == 0) {
                    log_message(((unsigned long)&rodata_9d64e) /*=0x9d64e*/, ((unsigned long)&rodata_9e032) /*=0x9e032*/, command_id);
                } else {
                    debug_print(((unsigned long)&rodata_9d64e) /*=0x9d64e*/, ((unsigned long)&rodata_9e032) /*=0x9e032*/, command_id);
                }
            }
        } else if (1 < LVL_A) {
            uint32_t backend_state = (uint32_t)LVL_B;
            if (backend_state == 0) {
                log_message(((unsigned long)&rodata_9d64e) /*=0x9d64e*/, ((unsigned long)&rodata_9e032) /*=0x9e032*/, command_id);
            } else {
                debug_print(((unsigned long)&rodata_9d64e) /*=0x9d64e*/, ((unsigned long)&rodata_9e032) /*=0x9e032*/, command_id);
            }
        }
        transfer[1] = 0xca;
        transfer[2] = 0x15;
        strcpy(transfer + 2, (const void *)((unsigned long)&rodata_9d671) /*=0x9d671*/);
        {
            response_callback_t pc = *(response_callback_t *)(param_1 + 0xc);
            pc(transfer, 20);
        }
        return 0;
    }

    puVar15 = (uint8_t *)(uintptr_t)load_u32(param_1 + 0x10);
    store_u32(response, 0);
    memset_bytes(response + 4, 0, 16);
    store_u32(puVar15, load_u32(packet));
    store_u32(param_1 + 0x14, (uint32_t)load_u16(packet + 2) + 4);
    response[0] = packet[0];

    switch (*packet) {
    case 0x47: {
        if (1 < LVL_A) {
            if (LVL_B == 0)
                log_message(((unsigned long)&rodata_9d4e4) /*=0x9d4e4*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
            else
                debug_print(((unsigned long)&rodata_9d4e4) /*=0x9d4e4*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
        }
        {
            response_callback_t pc = *(response_callback_t *)(param_1 + 0xc);
            response[1] = 0xc9;
            pc(response, sizeof(response));
        }
        iVar13 = FUN_00019b2c();
        if (iVar13 == 0) { return 0; }
        if (0 < LVL_A) {
            if (LVL_B == 0)
                log_message(((unsigned long)&rodata_9d518) /*=0x9d518*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
            else
                debug_print(((unsigned long)&rodata_9d518) /*=0x9d518*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
        }
        FUN_00056a68(iVar13, 0x13);
        return 0;
    }
    default:
        if (1 < LVL_A) {
            if (LVL_B == 0)
                log_message(((unsigned long)&rodata_9d64e) /*=0x9d64e*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/, command_id);
            else
                debug_print(((unsigned long)&rodata_9d64e) /*=0x9d64e*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/, command_id);
        }
        response[1] = 0xca;
        response[2] = 0x15;
        strcpy(response + 2, (const void *)((unsigned long)&rodata_9d671) /*=0x9d671*/);
        break;
    case 0x49:
    case 0x4d:
        goto switchD_caseD_49;
    case 0x4a:
        store_u32(puVar15, load_u32(packet));
        memcpy((uint8_t *)puVar15 + 4, param_3 + 1,
                     (uint32_t)load_u16(packet + 2) - 1);
        store_u32(param_1 + 0x14, (uint32_t)load_u16(packet + 2) + 4);
        goto switchD_caseD_49;
    case 0x4b:
        post_notification_cmd_process(param_1, packet, param_3);
        return 0;
    case 0x4c:
        if (2 < LVL_A) {
            if (LVL_B == 0)
                log_message(((unsigned long)&rodata_9d546) /*=0x9d546*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
            else
                debug_print(((unsigned long)&rodata_9d546) /*=0x9d546*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
        }
        memcpy((uint8_t *)puVar15 + 4, param_3 + 1,
                     (uint32_t)load_u16(packet + 2) - 1);
switchD_caseD_49:
        audio_fw_load_get_wrapper(param_1, transfer, 8);
        response[1] = 0xc9;
        break;
    case 0x4e:
        if (load_i16(packet + 2) != 0) {
            memset_bytes((void *)((unsigned long)&g_2000ffa7) /*=0x2000ffa7*/, 0, 0x158);
            if ((uint32_t)*(volatile uint8_t *)(param_3 + 3) ==
                (uint32_t)(uint8_t)(*(volatile uint8_t *)(param_3 + 2) - 1)) {
                returnStatus = 0xc9;
            } else {
                iVar13 = get_device_info();
                iVar14 = *(volatile int32_t *)(iVar13 + 0x100c);
                iVar13 = get_device_info();
                FUN_0007c1aa(iVar14, 0x199,
                             *(volatile uint8_t *)(iVar13 + 0xcc), 1);
                FUN_0007c176(*(volatile uint8_t *)(param_3 + 1), 1);
                returnStatus = 0xcb;
            }
            FUN_00086c1e((void *)((unsigned long)&g_2000ffa7) /*=0x2000ffa7*/, param_3 + 9,
                         (uint32_t)load_u16(packet + 2) - 9,
                         0x158);
            response[1] = returnStatus;
        }
        if (*(volatile int8_t *)(param_3 + 3) == 0) {
            iVar13 = get_device_info();
            iVar14 = *(volatile int32_t *)(iVar13 + 0x100c);
            memset_bytes((uint8_t *)(intptr_t)iVar14 + 7, 0, 0x190);
            iVar13 = get_device_info();
            iVar14 = *(volatile int32_t *)(iVar13 + 0x100c);
            *(volatile uint8_t *)(iVar14 + 0x197) = 0;
            *(volatile uint8_t *)(iVar14 + 0x198) = 0;
            iVar13 = get_device_info();
            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 1) =
                *(volatile uint8_t *)(param_3 + 4);
            bVar10 = *(volatile uint8_t *)(param_3 + 5);
            bVar3 = *(volatile uint8_t *)(param_3 + 6);
            iVar13 = get_device_info();
            store_u16((void *)(uintptr_t)
                          (*(volatile int32_t *)(iVar13 + 0x100c) + 2),
                      (uint16_t)((uint16_t)bVar10 * 0x100 + (uint16_t)bVar3));
            iVar13 = get_device_info();
            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 4) =
                *(volatile uint8_t *)(param_3 + 7);
            iVar13 = get_device_info();
            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 5) =
                *(volatile uint8_t *)(param_3 + 8);
        }
        iVar13 = get_device_info();
        iVar14 = *(volatile int32_t *)(iVar13 + 0x100c);
        iVar13 = get_device_info();
        memcpy((uint8_t *)(intptr_t)iVar14 +
                         load_u16((void *)(uintptr_t)
                                      (*(volatile int32_t *)(iVar13 + 0x100c) + 0x197)) + 7,
                     (const void *)((unsigned long)&g_2000ffa7) /*=0x2000ffa7*/,
                     (uint32_t)load_u16(packet + 2) - 9);
        iVar13 = get_device_info();
        {
            void *offset = (void *)(uintptr_t)
                (*(volatile int32_t *)(iVar13 + 0x100c) + 0x197);
            store_u16(offset, (uint16_t)(load_i16(offset) +
                                        load_i16(packet + 2) - 9));
        }
        uVar2 = load_u16(packet + 2);
        store_u16(puVar15 + 2, uVar2);
        store_u32(param_1 + 0x14, (uint32_t)uVar2 + 4);
        response[2] = param_3[1];
        response[3] = param_3[2];
        response[4] = param_3[3];
        if ((uint32_t)*(volatile uint8_t *)(param_3 + 3) ==
            (uint32_t)(uint8_t)(*(volatile uint8_t *)(param_3 + 2) - 1)) {
            audio_fw_load_get_wrapper(param_1, transfer, 8);
            bVar10 = *(volatile uint8_t *)(param_3 + 4) & 0xf0;
            if (bVar10 == 0x60) {
                mark_master_or_low_battery_flag();
                iVar13 = get_device_info();
                *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) = 10;
            } else {
                if (bVar10 == 0x70) {
                    iVar13 = get_device_info();
                    returnStatus = 0xf;
                    puVar12 = *(volatile uint8_t **)(iVar13 + 0x100c);
LAB_00021706:
                    *puVar12 = returnStatus;
                    iVar13 = get_device_info();
                    returnStatus = 0;
                } else {
                    iVar13 = get_device_info();
                    bVar10 = *(volatile uint8_t *)(param_3 + 4) & 0xf0;
                    if (*(volatile int8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) == 6) {
                        if (bVar10 == 0x40) goto LAB_0002175e;
                    } else if (bVar10 != 0x30) {
                        if (bVar10 == 0x40) {
LAB_0002175e:
                            iVar13 = get_device_info();
                            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) = 8;
                            iVar13 = get_device_info();
                            *(volatile uint8_t *)(iVar13 + 0xdb) = 8;
                        } else {
                            iVar13 = get_device_info();
                            if (6 < *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c))) {
                                bVar10 = *(volatile uint8_t *)(param_3 + 4) & 0xf0;
                                if (bVar10 == 0x40) goto LAB_0002175e;
                                if (bVar10 == 0x50) {
                                    iVar13 = get_device_info();
                                    returnStatus = 9;
                                    puVar12 = *(volatile uint8_t **)(iVar13 + 0x100c);
                                    goto LAB_00021706;
                                }
                            }
                        }
                        goto LAB_000216b4;
                    }
                    iVar13 = get_device_info();
                    *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) = 7;
                    iVar13 = get_device_info();
                    returnStatus = 0x10;
                }
                *(volatile uint8_t *)(iVar13 + 0xdb) = returnStatus;
            }
        }
LAB_000216b4:
        iVar13 = get_device_type();
        bVar10 = *(volatile uint8_t *)(param_3 + 3);
        bVar3 = *(volatile uint8_t *)(param_3 + 2);
        if (iVar13 == 1) {
            if ((uint32_t)bVar10 == (uint32_t)(uint8_t)(bVar3 - 1)) {
                G_20018d9b = 0x4e;
                G_20018d9a = bVar3;
                G_20018d99 = bVar10;
                FUN_0007c176(*(volatile uint8_t *)(param_3 + 1), 0);
                return 0;
            }
        } else if ((uint32_t)bVar10 == (uint32_t)(uint8_t)(bVar3 - 1)) {
            FUN_0007c176(*(volatile uint8_t *)(param_3 + 1), 0);
        }
        break;
    case 0x4f:
        store_u32(puVar15, load_u32(packet));
        memcpy((uint8_t *)puVar15 + 4, param_3 + 1,
                     (uint32_t)load_u16(packet + 2) - 1);
        audio_fw_load_get_wrapper(param_1, transfer, 8);
        response[1] = transfer[0];
        response[2] = transfer[1];
        break;
    case 0x50:
        if (load_i16(param_3 + 1) == load_i16(packet + 2)) {
            int8_t cVar1;
            volatile int8_t *pcVar8;
            int32_t iVar13x;
            uint32_t error_format;
            if (2 < LVL_A) {
                if (LVL_B == 0)
                    log_message(((unsigned long)&rodata_9d587) /*=0x9d587*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
                else
                    debug_print(((unsigned long)&rodata_9d587) /*=0x9d587*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
            }
            cVar1 = *(volatile int8_t *)(param_3 + 4);
            pcVar8 = (volatile int8_t *)(intptr_t)get_device_info();
            if (*pcVar8 == 1) {
                if (cVar1 == 1) {
                    uint32_t flags = __atomic_load_n(P_20007570,
                                                     __ATOMIC_ACQUIRE);
                    if ((int32_t)(flags << 0x1e) < 0) { return 0; }
                    if (2 < LVL_A) {
                        if (LVL_B == 0)
                            log_message(((unsigned long)&rodata_9d5af) /*=0x9d5af*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
                        else
                            debug_print(((unsigned long)&rodata_9d5af) /*=0x9d5af*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
                    }
                    (void)__atomic_fetch_or(P_20007570, 2,
                                            __ATOMIC_ACQ_REL);
                    {
                        uint32_t previous = __atomic_fetch_and(
                            P_2000756c, 0xfffffffdu, __ATOMIC_ACQ_REL);
                        uint32_t cleared = previous & 0xfffffffdu;
                        z_impl_k_timer_start(((unsigned long)&g_ble_work_timer) /*=0x20003d28*/, cleared, 0x8000u,
                                     0, 0, 0);
                    }
                    return 0;
                }
                if (LVL_A < 1) { return 0; }
                error_format = ((unsigned long)&rodata_9d5da) /*=0x9d5da*/;
                iVar13x = LVL_B;
            } else {
                if (LVL_A < 1) { return 0; }
                error_format = 0x0009d60fu;
                iVar13x = LVL_B;
            }
            if (iVar13x != 0) {
                debug_print(error_format, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
                return 0;
            }
            log_message(error_format, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/);
            return 0;
        }
        if (LVL_A < 2) { return 0; }
        if (LVL_B != 0) {
            debug_print(((unsigned long)&rodata_9b8fd) /*=0x9b8fd*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/,
                         load_u16(packet + 2), load_u16(param_3 + 1));
            return 0;
        }
        log_message(((unsigned long)&rodata_9b8fd) /*=0x9b8fd*/, ((unsigned long)&rodata_9e04e) /*=0x9e04e*/,
                    load_u16(packet + 2), load_u16(param_3 + 1));
        return 0;
    }

    {
        response_callback_t pc = *(response_callback_t *)(param_1 + 0xc);
        pc(response, sizeof(response));
    }
    return 0;
}
