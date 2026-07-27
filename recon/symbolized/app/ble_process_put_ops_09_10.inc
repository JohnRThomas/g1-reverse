/* Case 9/10 support types and byte-exact accessors.
 *
 * The handlers consume packed, unaligned wire data.  Do not replace these
 * helpers with casts: Cortex permits them, but the original explicitly builds
 * several LE words and differential traces depend on read width/order.
 */
#ifndef BLE_PROCESS_PUT_OPS_09_10_INC
#define BLE_PROCESS_PUT_OPS_09_10_INC

#include <stdint.h>
#include <stddef.h>

extern int get_device_type();
extern int get_device_info();
extern void debug_print(unsigned long, ...);
extern int ble_work_queue_lock();
extern int ble_work_queue_unlock();
extern int audio_fw_load_get_wrapper();
extern int send_response_data_to_msgqueue();
extern int get_synced_clock_time();
extern int store_device_info_bytes_cd_cf();
extern int safe_memcpy_checked();
extern int memcpy();
extern int memset_bytes();
extern void log_message(unsigned long, ...);
extern int update_persist_task_status();

#define OP10_LOG_LEVEL (*(volatile int32_t *)(uintptr_t)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define OP10_IS_DEBUG  (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define OP10_NAV_CHANGED (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_20010324) /*=0x20010324*/)
#define OP10_PAN_READY   (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_20010325) /*=0x20010325*/)
#define OP10_MAP_READY   (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_20010326) /*=0x20010326*/)
#define OP10_NAV_DATA_READY (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_20010323) /*=0x20010323*/)
#define OP10_OVERVIEW_TOTAL (*(volatile uint16_t *)(uintptr_t)0x2000d704)
#define OP10_OVERVIEW_PACKET (*(volatile uint16_t *)(uintptr_t)0x2000d706)
#define OP10_OVERVIEW_SIZE (*(volatile uint16_t *)(uintptr_t)0x2000d708)
#define OP10_OVERVIEW_MAP ((volatile uint8_t *)(uintptr_t)((unsigned long)&g_20015e52) /*=0x20015e52*/)
#define OP10_PAN_TOTAL (*(volatile uint16_t *)(uintptr_t)0x2000d6fc)
#define OP10_PAN_PACKET (*(volatile uint16_t *)(uintptr_t)0x2000d6fe)
#define OP10_PAN_SIZE (*(volatile uint16_t *)(uintptr_t)0x2000d700)
#define OP10_PAN_MAP ((volatile uint8_t *)(uintptr_t)((unsigned long)&g_20011d82) /*=0x20011d82*/)
#define OP10_PAN_DATA_READY (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_20010322) /*=0x20010322*/)
#define OP10_NAV_SYNC_COUNT (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_20007568) /*=0x20007568*/)
#define OP9_TEXT_SIZE (*(volatile uint16_t *)(uintptr_t)0x2000d702)
#define OP9_ASSEMBLY ((volatile uint8_t *)(uintptr_t)0x2001046b)
#define OP9_ASSEMBLY_TEXT ((volatile uint8_t *)(uintptr_t)0x20010482)
#define OP9_ACTION7_FLAG (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_2001046a) /*=0x2001046a*/)

typedef int (*ble_put_post_fn)(const void *, uint32_t);

struct ble_put_context_09_10 {
    uint8_t reserved_000[0x0c];
    ble_put_post_fn post_to_host;
    uint8_t *rx;
    uint32_t frame_length;
    uint8_t reserved_018[0x858];
    uint8_t *imu_state;          /* +0x870 (used indirectly by common state) */
    uint8_t reserved_874[0x0c];
    uint8_t *teleprompter;       /* +0x880 */
};

struct ble_put_ack20 {
    uint8_t b[20];
};

BLE_PUT_ALWAYS_INLINE uint16_t ble_put_rd16(const uint8_t *p)
{
    return (uint16_t)p[0] | (uint16_t)((uint16_t)p[1] << 8);
}

BLE_PUT_ALWAYS_INLINE uint32_t ble_put_rd32_explicit(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

BLE_PUT_ALWAYS_INLINE void ble_put_wr16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
}

BLE_PUT_ALWAYS_INLINE void ble_put_wr32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

BLE_PUT_ALWAYS_INLINE void ble_put_ack_copy9(struct ble_put_ack20 *ack,
                                     const uint8_t *payload, uint8_t status)
{
    /* Matches _local_13c=*param_3; local_138=param_3[1]; local_134=...
     * followed by uStack_133=status. Bytes 10..19 are caller-owned because
     * several original paths do not initialize them. */
    for (unsigned i = 0; i != 9; ++i)
        ack->b[i] = payload[i];
    ack->b[9] = status;
}

BLE_PUT_ALWAYS_INLINE void ble_put_ack_copy10(struct ble_put_ack20 *ack,
                                      const uint8_t *payload, uint8_t status)
{
    for (unsigned i = 0; i != 10; ++i)
        ack->b[i] = payload[i];
    ack->b[10] = status;
}

BLE_PUT_ALWAYS_INLINE void ble_put_ack_copy9_zero_tail(struct ble_put_ack20 *ack,
                                               const uint8_t *payload)
{
    for (unsigned i = 9; i != 20; ++i)
        ack->b[i] = 0;
    for (unsigned i = 0; i != 9; ++i)
        ack->b[i] = payload[i];
}

BLE_PUT_ALWAYS_INLINE void ble_put_ack_copy5_zero_tail(struct ble_put_ack20 *ack,
                                               const uint8_t *payload,
                                               uint8_t status)
{
    for (unsigned i = 5; i != 20; ++i)
        ack->b[i] = 0;
    for (unsigned i = 0; i != 5; ++i)
        ack->b[i] = payload[i];
    ack->b[5] = status;
}

BLE_PUT_ALWAYS_INLINE uint8_t ble_put_normalize_bool(uint8_t v)
{
    return v == 1 ? 1 : 0;
}

/* Implements navigation subcommands 0 and 1 only.  Return 1 when consumed and
 * 0 for another subcommand.  The caller has already established case 10 and
 * actual == advertised, exactly as the outer decompilation does. */
static inline __attribute__((always_inline))
int ble_put_op10_subcmd_0_1(struct ble_put_context_09_10 *ctx,
                           const uint8_t *request, uint16_t actual,
                           uint8_t response[20])
{
    uint8_t subcmd = request[4];
    uint8_t *root;
    uint8_t *nav;
    int ret;

    if (subcmd == 0) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): received navigation func startup  packet ....\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): received navigation func startup  packet ....\n"),
                            "ble_process_put_req");
        }
        root = (uint8_t *)(uintptr_t)get_device_info();
        nav = *(uint8_t **)(void *)(root + 0x1000);
        *((uint8_t *)(void *)ctx - 0x6af) = request[3];
        memset_bytes(nav, 0, 0xf5);
        root = (uint8_t *)(uintptr_t)get_device_info();
        memset_bytes(*(uint8_t **)(void *)(root + 0x1000), 0, 0xf5);
        nav[0xaf] = 0;
        nav[0] = 1;
        nav[0xb0] = request[3];
        OP10_MAP_READY = 0;
        OP10_PAN_READY = 0;
        root = (uint8_t *)(uintptr_t)get_device_info();
        update_persist_task_status(root, 10, 2);

        memset_bytes(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        response[5] = 0;
        if (get_device_type() == 1) {
            send_response_data_to_msgqueue(response, 6);
        } else {
            ret = ctx->post_to_host(response, 6);
            if (ret < 0 && OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
                else
                    debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
            }
        }
        return 1;
    }

    if (subcmd == 1) {
        size_t n0, n1, n2, n3, n4;
        size_t pos;
        root = (uint8_t *)(uintptr_t)get_device_info();
        nav = *(uint8_t **)(void *)(root + 0x1000);
        root = (uint8_t *)(uintptr_t)get_device_info();
        root[0xcd] = request[3];
        nav[1] = request[5];
        *(uint16_t *)(void *)(nav + 8) = ble_put_rd16(request + 6);
        *(uint16_t *)(void *)(nav + 10) = ble_put_rd16(request + 8);
        if ((ble_put_rd16(request + 6) > 0x1e8 ||
             ble_put_rd16(request + 8) > 0x88) && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): app send x/y parameter overstep!!! x= %d,y= %d\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): app send x/y parameter overstep!!! x= %d,y= %d\n"),
                             "ble_process_put_req");
        }

#define OP10_SCAN(_n, _pos, _max) do {                                      \
            (_n) = 0;                                                        \
            while ((_pos) + (_n) + 1 < actual && request[(_pos)+(_n)+1] != 0)\
                ++(_n);                                                      \
            if ((_pos) + (_n) + 1 >= actual || (_n) > (_max))               \
                goto op10_string_error;                                      \
        } while (0)
        pos = 9; OP10_SCAN(n0, pos, 0x18); pos += n0 + 1;
        memset_bytes(nav + 0x0d, 0, 0x18); memcpy(nav + 0x0d, request + 10, n0 + 1);
        OP10_SCAN(n1, pos, 0x18); pos += n1 + 1;
        memset_bytes(nav + 0x25, 0, 0x18); memcpy(nav + 0x25, request + pos - n1, n1 + 1);
        OP10_SCAN(n2, pos, 0x40); pos += n2 + 1;
        memset_bytes(nav + 0x3d, 0, 0x40); memcpy(nav + 0x3d, request + pos - n2, n2 + 1);
        OP10_SCAN(n3, pos, 0x18); pos += n3 + 1;
        memset_bytes(nav + 0x7d, 0, 0x18); memcpy(nav + 0x7d, request + pos - n3, n3 + 1);
        OP10_SCAN(n4, pos, 0x18);
        memset_bytes(nav + 0x95, 0, 0x18); memcpy(nav + 0x95, request + pos + 1, n4 + 1);
#undef OP10_SCAN
        nav[6] = 1; nav[0xaf] = 1; nav[0xb0] = request[3];
        memset_bytes(response + 5, 0, 15);
        OP10_NAV_CHANGED = 1;
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        if (get_device_type() == 1) send_response_data_to_msgqueue(response, 6);
        else (void)ctx->post_to_host(response, 6);
        return 1;

op10_string_error:
        memset_bytes(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4]; response[5] = 1;
        (void)ctx->post_to_host(response, 6);
        return 1;
    }
    return 0;
}

/* Overview-map multipart receiver (navigation subcommand 2).  The caller has
 * already checked the outer packet length.  Exactly bytes 0..9 of response
 * are initialized on the ten-byte acknowledgements. */
static inline __attribute__((always_inline))
int ble_put_op10_subcmd_2(struct ble_put_context_09_10 *ctx,
                         const uint8_t *request, uint16_t advertised,
                         uint8_t response[20])
{
    uint16_t total = ble_put_rd16(request + 5);
    uint16_t sequence = ble_put_rd16(request + 7);
    uint16_t data_length = (uint16_t)(advertised - 9U);
    uint8_t *root;
    uint8_t *nav;
    uint32_t pending;
    int ret;

    if (sequence == 1U) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): Received multiple initialization packets, currently the first packet of data,total packet = %d\n"),
                            "ble_process_put_req", (unsigned)total);
            else
                debug_print(((unsigned long)"%s(): Received multiple initialization packets, currently the first packet of data,total packet = %d\n"),
                            "ble_process_put_req", (unsigned)total);
        }
        OP10_OVERVIEW_TOTAL = total;
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_SIZE = 0;
        root = (uint8_t *)(uintptr_t)get_device_info();
        nav = *(uint8_t **)(void *)(root + 0x1000);
        OP10_MAP_READY = 0;
        ble_work_queue_lock(0xffffffffU, 0xffffffffU);
        memset_bytes((void *)(uintptr_t)OP10_OVERVIEW_MAP, 0, 0x1210);
        safe_memcpy_checked((void *)(uintptr_t)OP10_OVERVIEW_MAP, request + 9,
                     (uint32_t)(advertised - 9U), 0x1210);
        ble_work_queue_unlock();
        OP10_OVERVIEW_SIZE = data_length;
        OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
        if (total == 1U) {
            nav[6] = (uint8_t)total;
            OP10_NAV_DATA_READY = (uint8_t)total;
            OP10_MAP_READY = (uint8_t)total;
            nav[0xaf] = 2;
            nav[0xb0] = request[3];
            *(uint32_t *)(void *)(nav + 0xb1) = (uint32_t)OP10_OVERVIEW_SIZE;
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): Successfully received navigation data .Maps are compressed to only one pack!!!\n"),
                                "ble_process_put_req");
                else
                    debug_print(((unsigned long)"%s(): Successfully received navigation data .Maps are compressed to only one pack!!!\n"),
                                "ble_process_put_req");
            }
            OP10_OVERVIEW_TOTAL = 0;
            OP10_OVERVIEW_PACKET = 0;
            OP10_OVERVIEW_SIZE = 0;
        }
        ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 0);
        (void)ctx->post_to_host(response, 10);
        return 1;
    }

    if (sequence < total) {
        if ((uint32_t)OP10_OVERVIEW_PACKET == (uint32_t)sequence - 1U) {
            pending = (uint32_t)OP10_OVERVIEW_SIZE - 9U + advertised;
            if (pending < 0x1210U) {
                (void)get_device_info();
                ble_work_queue_lock(0xffffffffU, 0xffffffffU);
                memcpy((void *)(uintptr_t)(((unsigned long)&g_20015e52) /*=0x20015e52*/ + OP10_OVERVIEW_SIZE),
                             request + 9, (uint32_t)(advertised - 9U));
                ble_work_queue_unlock();
                OP10_MAP_READY = 0;
                OP10_OVERVIEW_SIZE = (uint16_t)pending;
                if (OP10_LOG_LEVEL > 2) {
                    if (OP10_IS_DEBUG == 0)
                        log_message(((unsigned long)"%s(): Successfully received the subpackage content, the packet sequence is %d,total size = %d\n"),
                                    "ble_process_put_req", (unsigned)sequence,
                                    (unsigned)OP10_OVERVIEW_SIZE);
                    else
                        debug_print(((unsigned long)"%s(): Successfully received the subpackage content, the packet sequence is %d,total size = %d\n"),
                                     "ble_process_put_req", (unsigned)sequence,
                                     (unsigned)OP10_OVERVIEW_SIZE);
                }
                OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
            } else if (OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): overview map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                "ble_process_put_req", (unsigned)OP10_OVERVIEW_SIZE,
                                (unsigned)pending);
                else
                    debug_print(((unsigned long)"%s(): overview map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                 "ble_process_put_req", (unsigned)OP10_OVERVIEW_SIZE,
                                 (unsigned)pending);
            }
            return 1;
        }
        goto op10_overview_order_error_with_lookup;
    }

    if (sequence == total) {
        if ((uint32_t)OP10_OVERVIEW_PACKET == (uint32_t)sequence - 1U &&
            sequence == OP10_OVERVIEW_TOTAL) {
            pending = (uint32_t)OP10_OVERVIEW_SIZE - 9U + advertised;
            if (pending < 0x1211U) {
                *((uint8_t *)(void *)ctx - 0x6af) = request[3];
                root = (uint8_t *)(uintptr_t)get_device_info();
                nav = *(uint8_t **)(void *)(root + 0x1000);
                ble_work_queue_lock(0xffffffffU, 0xffffffffU);
                memcpy((void *)(uintptr_t)(((unsigned long)&g_20015e52) /*=0x20015e52*/ + OP10_OVERVIEW_SIZE),
                             request + 9, (uint32_t)(advertised - 9U));
                ble_work_queue_unlock();
                OP10_OVERVIEW_SIZE = (uint16_t)pending;
                if (OP10_LOG_LEVEL > 2) {
                    if (OP10_IS_DEBUG == 0)
                        log_message(((unsigned long)"%s(): Successfully received the last packet,packet length = %d,total packet size = %d\n"),
                                    "ble_process_put_req", (unsigned)sequence,
                                    (unsigned)OP10_OVERVIEW_SIZE);
                    else
                        debug_print(((unsigned long)"%s(): Successfully received the last packet,packet length = %d,total packet size = %d\n"),
                                     "ble_process_put_req", (unsigned)sequence,
                                     (unsigned)OP10_OVERVIEW_SIZE);
                }
                nav[6] = 1;
                OP10_MAP_READY = 1;
                OP10_NAV_DATA_READY = 1;
                nav[0xaf] = 2;
                nav[0xb0] = request[3];
                *(uint32_t *)(void *)(nav + 0xb1) = (uint32_t)OP10_OVERVIEW_SIZE;
                ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 0);
                OP10_OVERVIEW_PACKET =
                    (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
                OP10_OVERVIEW_TOTAL = 0;
                OP10_OVERVIEW_PACKET = 0;
                OP10_OVERVIEW_SIZE = 0;
                if (get_device_type() == 1)
                    send_response_data_to_msgqueue(response, 10);
                else {
                    ret = ctx->post_to_host(response, 10);
                    if (ret < 0 && OP10_LOG_LEVEL > 0) {
                        if (OP10_IS_DEBUG == 0)
                            log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                        "ble_process_put_req", ret);
                        else
                            debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                        "ble_process_put_req", ret);
                    }
                }
            } else if (OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): overview map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                "ble_process_put_req", (unsigned)OP10_OVERVIEW_SIZE,
                                (unsigned)pending);
                else
                    debug_print(((unsigned long)"%s(): overview map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                 "ble_process_put_req", (unsigned)OP10_OVERVIEW_SIZE,
                                 (unsigned)pending);
            }
            return 1;
        }
op10_overview_order_error_with_lookup:
        if (OP10_LOG_LEVEL > 1) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                            "ble_process_put_req", (unsigned)sequence,
                            (unsigned)(OP10_OVERVIEW_PACKET + 1U));
            else
                debug_print(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                             "ble_process_put_req", (unsigned)sequence,
                             (unsigned)(OP10_OVERVIEW_PACKET + 1U));
        }
        OP10_OVERVIEW_TOTAL = total;
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_SIZE = 0;
        ble_work_queue_lock(0xffffffffU, 0xffffffffU);
        memset_bytes((void *)(uintptr_t)OP10_OVERVIEW_MAP, 0, 0x1210);
        ble_work_queue_unlock();
        (void)get_device_info();
        OP10_MAP_READY = 0;
        ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 1);
        (void)ctx->post_to_host(response, 10);
        return 1;
    }

    if (OP10_LOG_LEVEL > 1) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                        "ble_process_put_req", (unsigned)sequence,
                        (unsigned)(OP10_OVERVIEW_PACKET + 1U));
        else
            debug_print(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                         "ble_process_put_req", (unsigned)sequence,
                         (unsigned)(OP10_OVERVIEW_PACKET + 1U));
    }
    OP10_OVERVIEW_TOTAL = total;
    OP10_OVERVIEW_PACKET = 0;
    OP10_OVERVIEW_SIZE = 0;
    ble_work_queue_lock(0xffffffffU, 0xffffffffU);
    memset_bytes((void *)(uintptr_t)OP10_OVERVIEW_MAP, 0, 0x1210);
    ble_work_queue_unlock();
    ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 1);
    (void)ctx->post_to_host(response, 10);
    return 1;
}

/* Panoramic-map multipart receiver (navigation subcommand 3). */
static inline __attribute__((always_inline))
int ble_put_op10_subcmd_3(struct ble_put_context_09_10 *ctx,
                         const uint8_t *request, uint16_t advertised,
                         uint8_t response[20])
{
    uint16_t total = ble_put_rd16(request + 5);
    uint16_t sequence = ble_put_rd16(request + 7);
    uint32_t pending;
    uint32_t first_length;
    uint8_t *root;
    uint8_t *nav;
    int ret;

    if (OP10_LOG_LEVEL > 2) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): received navigation panoramic map data packet ....\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): received navigation panoramic map data packet ....\n"),
                        "ble_process_put_req");
    }

    if (sequence == 1U) {
        first_length = (uint32_t)advertised - 10U;
        OP10_PAN_TOTAL = total;
        OP10_PAN_PACKET = 0;
        OP10_PAN_SIZE = 0;
        root = (uint8_t *)(uintptr_t)get_device_info();
        OP10_PAN_READY = 0;
        nav = *(uint8_t **)(void *)(root + 0x1000);
        nav[0xad] = request[9];
        memset_bytes((void *)(uintptr_t)OP10_PAN_MAP, 0, 0x40d0);
        safe_memcpy_checked((void *)(uintptr_t)OP10_PAN_MAP, request + 10,
                     first_length, 0x40d0);
        OP10_PAN_SIZE = (uint16_t)first_length;
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): Successfully received multiple initialization packets, currently the first packet of data,received data size = %d,total packet len = %d\n"),
                            "ble_process_put_req", (unsigned)(first_length & 0xffffU),
                            (unsigned)OP10_PAN_TOTAL);
            else
                debug_print(((unsigned long)"%s(): Successfully received multiple initialization packets, currently the first packet of data,received data size = %d,total packet len = %d\n"),
                             "ble_process_put_req", (unsigned)(first_length & 0xffffU),
                             (unsigned)OP10_PAN_TOTAL);
        }
        OP10_PAN_PACKET = (uint16_t)(OP10_PAN_PACKET + 1U);
        ble_put_ack_copy10((struct ble_put_ack20 *)(void *)response, request, 0);
        (void)ctx->post_to_host(response, 11);
        return 1;
    }

    if (sequence < total) {
        (void)get_device_info();
        if ((uint32_t)OP10_PAN_PACKET == (uint32_t)sequence - 1U) {
            pending = (uint32_t)OP10_PAN_SIZE - 10U + advertised;
            if (pending < 0x40d0U) {
                OP10_PAN_READY = 0;
                memcpy((void *)(uintptr_t)(((unsigned long)&g_20011d82) /*=0x20011d82*/ + OP10_PAN_SIZE),
                             request + 10, (uint32_t)(advertised - 10U));
                OP10_PAN_SIZE = (uint16_t)pending;
                if (OP10_LOG_LEVEL > 2) {
                    if (OP10_IS_DEBUG == 0)
                        log_message(((unsigned long)"%s(): Successfully received the subpackage content, the packet sequence is %d,total received size = %d\n"),
                                    "ble_process_put_req", (unsigned)sequence,
                                    (unsigned)OP10_PAN_SIZE);
                    else
                        debug_print(((unsigned long)"%s(): Successfully received the subpackage content, the packet sequence is %d,total received size = %d\n"),
                                     "ble_process_put_req", (unsigned)sequence,
                                     (unsigned)OP10_PAN_SIZE);
                }
                OP10_PAN_PACKET = (uint16_t)(OP10_PAN_PACKET + 1U);
            } else if (OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): Panoramic map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                "ble_process_put_req", (unsigned)OP10_PAN_SIZE,
                                (unsigned)pending);
                else
                    debug_print(((unsigned long)"%s(): Panoramic map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                 "ble_process_put_req", (unsigned)OP10_PAN_SIZE,
                                 (unsigned)pending);
            }
            return 1;
        }
        goto op10_pan_order_error;
    }

    if (sequence == total) {
        root = (uint8_t *)(uintptr_t)get_device_info();
        nav = *(uint8_t **)(void *)(root + 0x1000);
        if ((uint32_t)OP10_PAN_PACKET == (uint32_t)sequence - 1U &&
            sequence == OP10_PAN_TOTAL) {
            pending = (uint32_t)OP10_PAN_SIZE - 10U + advertised;
            if (pending < 0x40d1U) {
                *((uint8_t *)(void *)ctx - 0x6af) = request[3];
                memcpy((void *)(uintptr_t)(((unsigned long)&g_20011d82) /*=0x20011d82*/ + OP10_PAN_SIZE),
                             request + 10, (uint32_t)(advertised - 10U));
                OP10_PAN_SIZE = (uint16_t)pending;
                OP10_PAN_PACKET = (uint16_t)(OP10_PAN_PACKET + 1U);
                if (OP10_LOG_LEVEL > 2) {
                    if (OP10_IS_DEBUG == 0)
                        log_message(((unsigned long)"%s(): Successfully received panoramic map  last packet,Packet id = %d,total received size = %d\n"),
                                    "ble_process_put_req", (unsigned)sequence,
                                    (unsigned)OP10_PAN_SIZE);
                    else
                        debug_print(((unsigned long)"%s(): Successfully received panoramic map  last packet,Packet id = %d,total received size = %d\n"),
                                     "ble_process_put_req", (unsigned)sequence,
                                     (unsigned)OP10_PAN_SIZE);
                }
                OP10_PAN_READY = 1;
                OP10_PAN_DATA_READY = 1;
                nav[6] = 1;
                nav[0xaf] = 3;
                nav[0xb0] = request[3];
                ble_put_ack_copy10((struct ble_put_ack20 *)(void *)response, request, 0);
                OP10_PAN_TOTAL = 0;
                OP10_PAN_PACKET = 0;
                OP10_PAN_SIZE = 0;
                if (get_device_type() == 1)
                    send_response_data_to_msgqueue(response, 11);
                else {
                    ret = ctx->post_to_host(response, 11);
                    if (ret < 0 && OP10_LOG_LEVEL > 0) {
                        if (OP10_IS_DEBUG == 0)
                            log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                        "ble_process_put_req", ret);
                        else
                            debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                        "ble_process_put_req", ret);
                    }
                }
            } else if (OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): Panoramic map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                "ble_process_put_req", (unsigned)OP10_PAN_SIZE,
                                (unsigned)pending);
                else
                    debug_print(((unsigned long)"%s(): Panoramic map : The data length of the current packet is too long, the current data length %d,wait write data length = %d\n"),
                                 "ble_process_put_req", (unsigned)OP10_PAN_SIZE,
                                 (unsigned)pending);
            }
            return 1;
        }
op10_pan_order_error:
        if (OP10_LOG_LEVEL > 1) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                            "ble_process_put_req", (unsigned)sequence,
                            (unsigned)(OP10_PAN_PACKET + 1U));
            else
                debug_print(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                             "ble_process_put_req", (unsigned)sequence,
                             (unsigned)(OP10_PAN_PACKET + 1U));
        }
        OP10_PAN_TOTAL = total;
        OP10_PAN_PACKET = 0;
        OP10_PAN_SIZE = 0;
        memset_bytes((void *)(uintptr_t)OP10_PAN_MAP, 0, 0x40d0);
        OP10_PAN_READY = 0;
        ble_put_ack_copy10((struct ble_put_ack20 *)(void *)response, request, 1);
        (void)ctx->post_to_host(response, 11);
        return 1;
    }

    (void)get_device_info();
    if (OP10_LOG_LEVEL > 1) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                        "ble_process_put_req", (unsigned)sequence,
                        (unsigned)(OP10_PAN_PACKET + 1U));
        else
            debug_print(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                         "ble_process_put_req", (unsigned)sequence,
                         (unsigned)(OP10_PAN_PACKET + 1U));
    }
    OP10_PAN_TOTAL = total;
    OP10_PAN_PACKET = 0;
    OP10_PAN_SIZE = 0;
    memset_bytes((void *)(uintptr_t)OP10_PAN_MAP, 0, 0x40d0);
    OP10_PAN_READY = 0;
    ble_put_ack_copy10((struct ble_put_ack20 *)(void *)response, request, 1);
    (void)ctx->post_to_host(response, 11);
    return 1;
}

/* Navigation sync, exit, and arrived-status commands (subcommands 4..6). */
static inline __attribute__((always_inline))
int ble_put_op10_subcmd_4_6(struct ble_put_context_09_10 *ctx,
                           const uint8_t *request, uint16_t advertised,
                           uint8_t response[20])
{
    uint8_t subcmd = request[4];
    uint8_t *root;
    uint8_t *nav;
    uint8_t status;
    uint32_t copied;
    int ret;

    if (subcmd == 4U) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): received app send sync packet ....\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): received app send sync packet ....\n"),
                            "ble_process_put_req");
        }
        root = (uint8_t *)(uintptr_t)get_device_info();
        nav = *(uint8_t **)(void *)(root + 0x1000);
        memset_bytes(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        response[5] = request[5];
        if (nav[0] == 0) {
            response[5] = 0;
            if (OP10_LOG_LEVEL > 1) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): navigation don't startup, sync packet return\n"),
                                "ble_process_put_req");
                else
                    debug_print(((unsigned long)"%s(): navigation don't startup, sync packet return\n"),
                                "ble_process_put_req");
            }
        } else {
            OP10_NAV_SYNC_COUNT = OP10_NAV_SYNC_COUNT + 1U;
        }
        (void)ctx->post_to_host(response, 6);
        return 1;
    }

    if (subcmd == 5U) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): received navigation func exit packet ....\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): received navigation func exit packet ....\n"),
                            "ble_process_put_req");
        }
        root = (uint8_t *)(uintptr_t)get_device_info();
        nav = *(uint8_t **)(void *)(root + 0x1000);
        *((uint8_t *)(void *)ctx - 0x6af) = request[3];
        memset_bytes(nav + 1, 0, 0xf4);
        nav[0] = 0;
        memset_bytes(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        response[5] = 1;
        (void)ctx->post_to_host(response, 6);
        return 1;
    }

    if (subcmd != 6U)
        return 0;

    root = (uint8_t *)(uintptr_t)get_device_info();
    nav = *(uint8_t **)(void *)(root + 0x1000);
    *((uint8_t *)(void *)ctx - 0x6af) = request[3];
    nav[6] = 1;
    nav[0xae] = request[5];
    nav[0xaf] = 6;
    nav[0xb0] = request[3];
    memset_bytes(response + 6, 0, 14);
    *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
    response[4] = request[4];
    response[5] = request[5];
    copied = (uint32_t)memset_bytes(nav + 0xb5, 0, 0x40);
    if ((uint32_t)advertised - 6U < 0x40U) {
        copied = (uint32_t)memcpy((void *)(uintptr_t)copied, request + 6,
                                       (uint32_t)advertised - 6U);
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): received arrived status packet. arrived status = %d ,arrived prompt word = %s\n"),
                            "ble_process_put_req", (unsigned)request[5], copied);
            else
                debug_print(((unsigned long)"%s(): received arrived status packet. arrived status = %d ,arrived prompt word = %s\n"),
                            "ble_process_put_req", (unsigned)request[5], copied);
        }
        status = 0;
    } else {
        if (OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): app send prompt word oversize,drop it...\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): app send prompt word oversize,drop it...\n"),
                            "ble_process_put_req");
        }
        status = 1;
    }
    response[5] = status;
    if (get_device_type() == 1) {
        send_response_data_to_msgqueue(response, 6);
    } else {
        ret = ctx->post_to_host(response, 6);
        if (ret < 0 && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
            else
                debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
        }
    }
    return 1;
}

/* Complete outer navigation command (PUT request type 10).  `packet` is the
 * frame header copied into ctx->rx by the common prologue; `request` is the
 * request body used by the original param_3 accesses. */
static inline __attribute__((always_inline))
int ble_put_op10_dispatch(struct ble_put_context_09_10 *ctx,
                          const uint8_t *packet, const uint8_t *request,
                          uint8_t response[20])
{
    uint16_t advertised = ble_put_rd16(request + 1);
    uint16_t actual = ble_put_rd16(packet + 2);
    uint8_t subcmd;

    if (advertised != actual) {
        if (OP10_LOG_LEVEL < 2)
            return 1;
        if (OP10_IS_DEBUG != 0) {
            debug_print(((unsigned long)"%s(): packet length error,input data length = %d,packet data length = %d\n"),
                         "ble_process_put_req", (unsigned)actual,
                         (unsigned)advertised);
            return 1;
        }
        log_message(((unsigned long)"%s(): packet length error,input data length = %d,packet data length = %d\n"),
                    "ble_process_put_req", (unsigned)actual,
                    (unsigned)advertised);
        return 1;
    }

    subcmd = request[4];
    if (subcmd <= 1U)
        return ble_put_op10_subcmd_0_1(ctx, request, advertised, response);
    if (subcmd == 2U)
        return ble_put_op10_subcmd_2(ctx, request, advertised, response);
    if (subcmd == 3U)
        return ble_put_op10_subcmd_3(ctx, request, advertised, response);
    if (subcmd <= 6U)
        return ble_put_op10_subcmd_4_6(ctx, request, advertised, response);
    return 1;
}

/* Teleprompter action 5 only.  Return zero for every other action so the
 * still-unrecovered case-9 actions cannot be mistaken for handled commands.
 * The outer case-9 length gate/action switch remains the caller's concern. */
static inline __attribute__((always_inline))
int ble_put_op9_action5_exit(struct ble_put_context_09_10 *ctx,
                            const uint8_t *request, uint8_t response[20])
{
    uint32_t completion[2];
    int ret;

    if (request[4] != 5U)
        return 0;
    if (OP10_LOG_LEVEL > 2) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): received teleprompter func exit packet ....\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): received teleprompter func exit packet ....\n"),
                        "ble_process_put_req");
    }
    if (get_device_type() == 1) {
        *((uint8_t *)(void *)ctx - 0x6af) = request[3];
        store_device_info_bytes_cd_cf(request[3], 0);
        memset_bytes(ctx->rx + 4, 0, 0x217);
        ctx->frame_length = (uint32_t)ble_put_rd16(ctx->rx + 2) + 4U;
        audio_fw_load_get_wrapper(ctx, completion, 8);
    }
    memset_bytes(response + 6, 0, 14);
    *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
    response[4] = request[4];
    response[5] = request[5];
    ret = ctx->post_to_host(response, 6);
    if (ret < 0 && OP10_LOG_LEVEL > 0) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                        "ble_process_put_req", ret);
        else
            debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                        "ble_process_put_req", ret);
    }
    return 1;
}

/* Teleprompter action 2: update the marked text position and its application
 * timestamp.  The timestamp fields are deliberately written as two unaligned
 * 32-bit stores at object offsets 2 and 6, matching the original. */
static inline __attribute__((always_inline))
int ble_put_op9_action2_mark(struct ble_put_context_09_10 *ctx,
                            const uint8_t *request, uint16_t advertised,
                            uint8_t response[20])
{
    volatile uint8_t *teleprompter;
    uint32_t timestamp_lo;
    uint32_t timestamp_hi;
    int ret;

    if (request[4] != 2U)
        return 0;
    *((uint8_t *)(void *)ctx - 0x6af) = request[3];
    store_device_info_bytes_cd_cf(request[3], 0);
    ctx->frame_length = (uint32_t)ble_put_rd16(ctx->rx + 2) + 4U;
    teleprompter = ctx->teleprompter;
    *(uint16_t *)(void *)(teleprompter + 0x0e) = ble_put_rd16(request + 6);
    teleprompter[0x0d] = request[5];
    teleprompter[0x0a] = 2;
    timestamp_lo = ble_put_rd32_explicit(request + (uint32_t)advertised - 8U);
    timestamp_hi = *(const uint32_t *)(const void *)(request + (uint32_t)advertised - 4U);
    *(uint32_t *)(void *)(teleprompter + 2) = timestamp_lo;
    *(uint32_t *)(void *)(teleprompter + 6) = timestamp_hi;
    if (OP10_LOG_LEVEL > 2) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): MARK POSITION = %d\n"), "ble_process_put_req",
                        (unsigned)*(uint16_t *)(void *)(teleprompter + 0x0e));
        else
            debug_print(((unsigned long)"%s(): MARK POSITION = %d\n"), "ble_process_put_req",
                        (unsigned)*(uint16_t *)(void *)(teleprompter + 0x0e));
    }
    memset_bytes(response + 5, 0, 15);
    *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
    response[4] = request[4];
    if (get_device_type() == 1) {
        send_response_data_to_msgqueue(response, 6);
    } else {
        ret = ctx->post_to_host(response, 6);
        if (ret < 0 && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
            else
                debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
        }
    }
    return 1;
}

/* Teleprompter action 1, including the multipart assembly state machine. */
static inline __attribute__((always_inline))
int ble_put_op9_action1_single(struct ble_put_context_09_10 *ctx,
                              const uint8_t *packet, const uint8_t *request,
                              uint16_t advertised, uint8_t response[20])
{
    uint8_t *tele = ctx->rx;
    uint16_t total;
    uint16_t sequence;
    uint16_t text_length;
    uint32_t app_time_lo;
    uint32_t app_time_hi;
    uint32_t system_time[2] = { 0, 0 };
    uint32_t completion[2];
    int ret;

    if (request[4] != 1U)
        return 0;
    total = ble_put_rd16(request + 5);
    sequence = ble_put_rd16(request + 7);
    if (OP10_LOG_LEVEL > 2) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): received teleprompter init  packet ....\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): received teleprompter init  packet ....\n"),
                        "ble_process_put_req");
    }
    memset_bytes(tele + 4, 0, 0x217);
    if (total == 1U) {
    if (OP10_LOG_LEVEL > 2) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): received teleprompter init packet,total packet = 1\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): received teleprompter init packet,total packet = 1\n"),
                        "ble_process_put_req");
    }
    *((uint8_t *)(void *)ctx - 0x6af) = request[3];
    store_device_info_bytes_cd_cf(request[3], 0);
    tele[0x0e] = 1;
    tele[0x05] = 1;
    tele[0x04] = request[10] & 0x0fU;
    tele[0x0f] = request[10] & 0x80U;
    tele[0x10] = request[9];
    tele[0x11] = request[11];
    tele[0x12] = 0;
    tele[0x13] = 0;
    tele[0x14] = 0;
    text_length = (uint16_t)(advertised - 0x14U);
    memcpy(tele + 0x1b, request + 12, (uint32_t)(advertised - 0x14U));
    *(uint16_t *)(void *)(tele + 0x19) = text_length;
    app_time_hi = *(const uint32_t *)(const void *)(request + (uint32_t)advertised - 4U);
    app_time_lo = ble_put_rd32_explicit(request + (uint32_t)advertised - 8U);
    *(uint32_t *)(void *)(tele + 6) = app_time_lo;
    *(uint32_t *)(void *)(tele + 10) = app_time_hi;
    get_synced_clock_time(system_time);
    if (OP10_LOG_LEVEL > 0) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                        "ble_process_put_req", app_time_lo, app_time_hi,
                        system_time[0], system_time[1]);
        else
            debug_print(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                        "ble_process_put_req", app_time_lo, app_time_hi,
                        system_time[0], system_time[1]);
    }
    *(uint16_t *)(void *)(tele + 2) = ble_put_rd16(packet + 2);
    ctx->frame_length = (uint32_t)ble_put_rd16(packet + 2) + 4U;
    audio_fw_load_get_wrapper(ctx, completion, 8);
    ble_put_ack_copy9_zero_tail((struct ble_put_ack20 *)(void *)response,
                                request);
    if (get_device_type() == 1) {
        send_response_data_to_msgqueue(response, 10);
    } else {
        ret = ctx->post_to_host(response, 10);
        if (ret < 0 && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
            else
                debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
        }
    }
    return 1;
    }

    if (sequence == 1U) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): Action ID = 1,Received multiple initialization packets, currently the first packet of data\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): Action ID = 1,Received multiple initialization packets, currently the first packet of data\n"),
                            "ble_process_put_req");
        }
        OP10_OVERVIEW_TOTAL = total;
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_SIZE = 0;
        OP9_TEXT_SIZE = 0;
        memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
        OP9_ASSEMBLY[0x0a] = 1;
        OP9_ASSEMBLY[1] = 0;
        OP9_ASSEMBLY[0] = request[10] & 0x0fU;
        OP9_ASSEMBLY[0x0b] = request[10] & 0x80U;
        OP9_ASSEMBLY[0x0c] = request[9];
        OP9_ASSEMBLY[0x0d] = request[11];
        OP9_ASSEMBLY[0x0e] = 0;
        OP9_ASSEMBLY[0x0f] = 0;
        for (unsigned i = 2; i < 10; ++i)
            OP9_ASSEMBLY[i] = 0;
        safe_memcpy_checked((void *)(uintptr_t)OP9_ASSEMBLY_TEXT, request + 12,
                     (uint32_t)(advertised - 12U), 0x200);
        OP9_TEXT_SIZE = (uint16_t)(advertised - 12U);
        OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
        ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 0);
        ret = ctx->post_to_host(response, 10);
        if (ret < 0 && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
            else
                debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
        }
        return 1;
    }

    if (sequence < total) {
        if ((uint32_t)OP10_OVERVIEW_PACKET == (uint32_t)sequence - 1U) {
            memcpy((void *)(uintptr_t)(0x20010482U + OP9_TEXT_SIZE),
                         request + 12, (uint32_t)(advertised - 12U));
            OP9_TEXT_SIZE = (uint16_t)((uint32_t)OP9_TEXT_SIZE - 12U + advertised);
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): ACTION ID = 1,Successfully received the subpackage content, the packet sequence is %d\n"),
                                "ble_process_put_req", (unsigned)sequence);
                else
                    debug_print(((unsigned long)"%s(): ACTION ID = 1,Successfully received the subpackage content, the packet sequence is %d\n"),
                                "ble_process_put_req", (unsigned)sequence);
            }
            OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
            ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 0);
            ret = ctx->post_to_host(response, 10);
            if (ret < 0 && OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
                else
                    debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
            }
            return 1;
        }
        if (OP10_LOG_LEVEL > 1) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                            "ble_process_put_req", (unsigned)sequence,
                            (unsigned)(OP10_OVERVIEW_PACKET + 1U));
            else
                debug_print(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                             "ble_process_put_req", (unsigned)sequence,
                             (unsigned)(OP10_OVERVIEW_PACKET + 1U));
        }
        OP10_OVERVIEW_TOTAL = total;
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_SIZE = 0;
        memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
        ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 1);
        ret = ctx->post_to_host(response, 10);
        if (ret < 0 && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
            else
                debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
        }
        return 1;
    }

    if (sequence == total) {
        if ((uint32_t)OP10_OVERVIEW_PACKET == (uint32_t)sequence - 1U &&
            OP10_OVERVIEW_TOTAL == sequence) {
            uint8_t *root;
            uint32_t system_final[2] = { 0, 0 };
            *((uint8_t *)(void *)ctx - 0x6af) = request[3];
            store_device_info_bytes_cd_cf(request[3], 0);
            memcpy((void *)(uintptr_t)(0x20010482U + OP9_TEXT_SIZE),
                         request + 12, (uint32_t)(advertised - 20U));
            OP9_TEXT_SIZE = (uint16_t)((uint32_t)OP9_TEXT_SIZE - 20U + advertised);
            *(uint16_t *)(void *)(OP9_ASSEMBLY + 0x15) = OP9_TEXT_SIZE;
            *(volatile uint32_t *)(void *)(OP9_ASSEMBLY + 2) =
                ble_put_rd32_explicit(request + (uint32_t)advertised - 8U);
            *(volatile uint32_t *)(void *)(OP9_ASSEMBLY + 6) =
                *(const uint32_t *)(const void *)(request + (uint32_t)advertised - 4U);
            get_synced_clock_time(system_final);
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                                "ble_process_put_req",
                                *(uint32_t *)(void *)(OP9_ASSEMBLY + 2),
                                *(uint32_t *)(void *)(OP9_ASSEMBLY + 6),
                                system_final[0], system_final[1]);
                else
                    debug_print(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                                "ble_process_put_req",
                                *(uint32_t *)(void *)(OP9_ASSEMBLY + 2),
                                *(uint32_t *)(void *)(OP9_ASSEMBLY + 6),
                                system_final[0], system_final[1]);
            }
            OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
            OP9_ASSEMBLY[1] = 1;
            root = (uint8_t *)(uintptr_t)get_device_info();
            memcpy(*(void **)(void *)(root + 0xffc),
                         (const void *)(uintptr_t)OP9_ASSEMBLY, 0x217);
            if (OP9_ASSEMBLY[1] != 0)
                update_persist_task_status((uint8_t *)(void *)ctx - 0x77c,
                                           9, 2);
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): ACTION ID = 1,Successfully assembled multiple packages of data, and updated the complete content to the UI thread for data update.\n"),
                                "ble_process_put_req");
                else
                    debug_print(((unsigned long)"%s(): ACTION ID = 1,Successfully assembled multiple packages of data, and updated the complete content to the UI thread for data update.\n"),
                                "ble_process_put_req");
            }
            OP10_OVERVIEW_TOTAL = 0;
            OP10_OVERVIEW_PACKET = 0;
            ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 0);
            if (get_device_type() == 1)
                send_response_data_to_msgqueue(response, 10);
            else {
                ret = ctx->post_to_host(response, 10);
                if (ret < 0 && OP10_LOG_LEVEL > 0) {
                    if (OP10_IS_DEBUG == 0)
                        log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                    "ble_process_put_req", ret);
                    else
                        debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                    "ble_process_put_req", ret);
                }
            }
            return 1;
        }
        if (OP10_LOG_LEVEL > 1) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                            "ble_process_put_req", (unsigned)sequence,
                            (unsigned)(OP10_OVERVIEW_PACKET + 1U));
            else
                debug_print(((unsigned long)"%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                             "ble_process_put_req", (unsigned)sequence,
                             (unsigned)(OP10_OVERVIEW_PACKET + 1U));
        }
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_TOTAL = total;
        memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
        ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 1);
        ret = ctx->post_to_host(response, 10);
        if (ret < 0 && OP10_LOG_LEVEL > 0) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
            else
                debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                            "ble_process_put_req", ret);
        }
        return 1;
    }

    if (OP10_LOG_LEVEL > 0) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): A serious packet order error occurred!\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): A serious packet order error occurred!\n"),
                        "ble_process_put_req");
    }
    OP10_OVERVIEW_TOTAL = 0;
    OP10_OVERVIEW_PACKET = 0;
    memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
    ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, 1);
    ret = ctx->post_to_host(response, 10);
    if (ret < 0 && OP10_LOG_LEVEL > 0) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                        "ble_process_put_req", ret);
        else
            debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                        "ble_process_put_req", ret);
    }
    return 1;
}

static inline __attribute__((always_inline))
void ble_put_op9_ack9(struct ble_put_context_09_10 *ctx,
                      const uint8_t *request, uint8_t response[20],
                      uint8_t status, int permit_local)
{
    int ret;
    ble_put_ack_copy9((struct ble_put_ack20 *)(void *)response, request, status);
    if (permit_local && get_device_type() == 1) {
        send_response_data_to_msgqueue(response, 10);
        return;
    }
    ret = ctx->post_to_host(response, 10);
    if (ret < 0 && OP10_LOG_LEVEL > 0) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                        "ble_process_put_req", ret);
        else
            debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                        "ble_process_put_req", ret);
    }
}

/* Teleprompter text-upgrade actions 3 and 7. */
static inline __attribute__((always_inline))
int ble_put_op9_action3_7(struct ble_put_context_09_10 *ctx,
                         const uint8_t *packet, const uint8_t *request,
                         uint16_t advertised, uint8_t response[20])
{
    uint8_t action = request[4];
    uint16_t total;
    uint16_t sequence;
    uint8_t *tele;
    uint32_t now[2] = { 0, 0 };
    int ret;

    if (action != 3U && action != 7U)
        return 0;
    if (OP10_LOG_LEVEL > 2) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): received teleprompter text upgrade packet ....\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): received teleprompter text upgrade packet ....\n"),
                        "ble_process_put_req");
    }
    total = ble_put_rd16(request + 5);
    sequence = ble_put_rd16(request + 7);
    tele = ctx->teleprompter;

    if (total == 1U) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): received TEXT UPGRADE Single PACKET ...\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): received TEXT UPGRADE Single PACKET ...\n"),
                            "ble_process_put_req");
        }
        *((uint8_t *)(void *)ctx - 0x6af) = request[3];
        store_device_info_bytes_cd_cf(request[3], 0);
        tele[0x0a] = 3;
        tele[1] = 1;
        tele[0x0d] = request[9];
        *(uint16_t *)(void *)(tele + 0x0e) = ble_put_rd16(request + 10);
        memset_bytes(tele + 0x17, 0, 0x200);
        memcpy(tele + 0x17, request + 12,
                     (uint32_t)(advertised - 20U));
        *(uint16_t *)(void *)(tele + 0x15) = (uint16_t)(advertised - 20U);
        *(uint32_t *)(void *)(tele + 2) =
            ble_put_rd32_explicit(request + (uint32_t)advertised - 8U);
        *(uint32_t *)(void *)(tele + 6) =
            *(const uint32_t *)(const void *)(request + (uint32_t)advertised - 4U);
        get_synced_clock_time(now);
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                            "ble_process_put_req",
                            *(uint32_t *)(void *)(tele + 2),
                            *(uint32_t *)(void *)(tele + 6), now[0], now[1]);
            else
                debug_print(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                            "ble_process_put_req",
                            *(uint32_t *)(void *)(tele + 2),
                            *(uint32_t *)(void *)(tele + 6), now[0], now[1]);
        }
        if (action == 7U)
            OP9_ACTION7_FLAG = 1;
        *(uint16_t *)(void *)(ctx->rx + 2) = ble_put_rd16(packet + 2);
        ctx->frame_length = (uint32_t)ble_put_rd16(packet + 2) + 4U;
        ble_put_ack_copy9_zero_tail((struct ble_put_ack20 *)(void *)response,
                                    request);
        if (get_device_type() == 1) {
            send_response_data_to_msgqueue(response, 10);
        } else {
            ret = ctx->post_to_host(response, 10);
            if (ret < 0 && OP10_LOG_LEVEL > 0) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
                else
                    debug_print(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
            }
        }
        return 1;
    }

    if (sequence == 1U) {
        if (OP10_LOG_LEVEL > 2) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): ACTION ID = 3,Received multiple initialization packets, currently the first packet of data\n"),
                            "ble_process_put_req");
            else
                debug_print(((unsigned long)"%s(): ACTION ID = 3,Received multiple initialization packets, currently the first packet of data\n"),
                            "ble_process_put_req");
        }
        OP10_OVERVIEW_TOTAL = total;
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_SIZE = 0;
        memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
        safe_memcpy_checked((void *)(uintptr_t)OP9_ASSEMBLY, request + 12,
                     (uint32_t)(advertised - 12U), 0x217);
        OP10_OVERVIEW_SIZE = (uint16_t)(advertised - 12U);
        OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
        for (unsigned i = 2; i != 10; ++i)
            tele[i] = 0;
        ble_put_op9_ack9(ctx, request, response, 0, 0);
        return 1;
    }

    if (sequence < total) {
        if ((uint32_t)OP10_OVERVIEW_PACKET == (uint32_t)sequence - 1U) {
            memcpy((void *)(uintptr_t)(0x2001046bU + OP10_OVERVIEW_SIZE),
                         request + 12, (uint32_t)(advertised - 12U));
            OP10_OVERVIEW_SIZE =
                (uint16_t)((uint32_t)OP10_OVERVIEW_SIZE - 12U + advertised);
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): ACTION ID = 3,Successfully received the subpackage content, the packet sequence is %d\n"),
                                "ble_process_put_req", (unsigned)sequence);
                else
                    debug_print(((unsigned long)"%s(): ACTION ID = 3,Successfully received the subpackage content, the packet sequence is %d\n"),
                                "ble_process_put_req", (unsigned)sequence);
            }
            OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
            ble_put_op9_ack9(ctx, request, response, 0, 0);
            return 1;
        }
        goto op9_action3_order_reset_zero_total;
    }

    if (sequence == total) {
        if ((uint32_t)OP10_OVERVIEW_PACKET == (uint32_t)total - 1U &&
            OP10_OVERVIEW_TOTAL == total) {
            *((uint8_t *)(void *)ctx - 0x6af) = request[3];
            store_device_info_bytes_cd_cf(request[3], 0);
            memcpy((void *)(uintptr_t)(0x2001046bU + OP10_OVERVIEW_SIZE),
                         request + 12, (uint32_t)(advertised - 20U));
            OP10_OVERVIEW_SIZE =
                (uint16_t)((uint32_t)OP10_OVERVIEW_SIZE - 20U + advertised);
            OP10_OVERVIEW_PACKET = (uint16_t)(OP10_OVERVIEW_PACKET + 1U);
            memset_bytes(tele + 0x17, 0, 0x200);
            memcpy(tele + 0x17, (const void *)(uintptr_t)OP9_ASSEMBLY,
                         (uint32_t)OP10_OVERVIEW_SIZE);
            *(uint16_t *)(void *)(tele + 0x15) = OP10_OVERVIEW_SIZE;
            tele[0x0a] = 3;
            tele[0x0d] = request[9];
            *(uint16_t *)(void *)(tele + 0x0e) = ble_put_rd16(request + 10);
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): ACTIION ID = 3,Successfully assembled multiple packages of data, and updated the complete content to the UI thread for data update.\n"),
                                "ble_process_put_req");
                else
                    debug_print(((unsigned long)"%s(): ACTIION ID = 3,Successfully assembled multiple packages of data, and updated the complete content to the UI thread for data update.\n"),
                                "ble_process_put_req");
            }
            *(uint32_t *)(void *)(tele + 2) =
                ble_put_rd32_explicit(request + (uint32_t)advertised - 8U);
            *(uint32_t *)(void *)(tele + 6) =
                *(const uint32_t *)(const void *)(request + (uint32_t)advertised - 4U);
            now[0] = 0; now[1] = 0;
            get_synced_clock_time(now);
            if (OP10_LOG_LEVEL > 2) {
                if (OP10_IS_DEBUG == 0)
                    log_message(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                                "ble_process_put_req",
                                *(uint32_t *)(void *)(tele + 2),
                                *(uint32_t *)(void *)(tele + 6), now[0], now[1]);
                else
                    debug_print(((unsigned long)"%s(): *******************------ received app send timestamp = %lld,current system timestamp = %lld\n"),
                                "ble_process_put_req",
                                *(uint32_t *)(void *)(tele + 2),
                                *(uint32_t *)(void *)(tele + 6), now[0], now[1]);
            }
            if (action == 7U)
                OP9_ACTION7_FLAG = 1;
            OP10_OVERVIEW_TOTAL = 0;
            OP10_OVERVIEW_PACKET = 0;
            ble_put_op9_ack9(ctx, request, response, 0, 1);
            return 1;
        }
        if (OP10_LOG_LEVEL > 1) {
            if (OP10_IS_DEBUG == 0)
                log_message(((unsigned long)"%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                            "ble_process_put_req", (unsigned)sequence,
                            (unsigned)(OP10_OVERVIEW_PACKET + 1U));
            else
                debug_print(((unsigned long)"%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                             "ble_process_put_req", (unsigned)sequence,
                             (unsigned)(OP10_OVERVIEW_PACKET + 1U));
        }
        OP10_OVERVIEW_PACKET = 0;
        OP10_OVERVIEW_SIZE = 0;
        OP10_OVERVIEW_TOTAL = total;
        memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
        ble_put_op9_ack9(ctx, request, response, 1, 0);
        return 1;
    }

    if (OP10_LOG_LEVEL > 0) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): ACTION ID = 3,A serious packet order error occurred!\n"),
                        "ble_process_put_req");
        else
            debug_print(((unsigned long)"%s(): ACTION ID = 3,A serious packet order error occurred!\n"),
                        "ble_process_put_req");
    }
    OP10_OVERVIEW_TOTAL = 0;
    OP10_OVERVIEW_PACKET = 0;
    OP10_OVERVIEW_SIZE = 0;
    memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
    ble_put_op9_ack9(ctx, request, response, 1, 0);
    return 1;

op9_action3_order_reset_zero_total:
    if (OP10_LOG_LEVEL > 1) {
        if (OP10_IS_DEBUG == 0)
            log_message(((unsigned long)"%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                        "ble_process_put_req", (unsigned)sequence,
                        (unsigned)(OP10_OVERVIEW_PACKET + 1U));
        else
            debug_print(((unsigned long)"%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n"),
                         "ble_process_put_req", (unsigned)sequence,
                         (unsigned)(OP10_OVERVIEW_PACKET + 1U));
    }
    OP10_OVERVIEW_TOTAL = 0;
    OP10_OVERVIEW_PACKET = 0;
    OP10_OVERVIEW_SIZE = 0;
    memset_bytes((void *)(uintptr_t)OP9_ASSEMBLY, 0, 0x217);
    ble_put_op9_ack9(ctx, request, response, 1, 0);
    return 1;
}

/* Outer teleprompter command (PUT request type 9).  The switch intentionally
 * routes only recovered actions; adding another action is a single new case. */
static inline __attribute__((always_inline))
int ble_put_op9_dispatch(struct ble_put_context_09_10 *ctx,
                         const uint8_t *packet, const uint8_t *request,
                         uint8_t response[20])
{
    uint16_t advertised = ble_put_rd16(request + 1);
    uint16_t actual = ble_put_rd16(packet + 2);

    if (advertised != actual) {
        if (OP10_LOG_LEVEL < 1)
            return 1;
        if (OP10_IS_DEBUG != 0) {
            debug_print(((unsigned long)"%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n"),
                         "ble_process_put_req", (unsigned)actual,
                         (unsigned)advertised);
            return 1;
        }
        log_message(((unsigned long)"%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n"),
                    "ble_process_put_req", (unsigned)actual,
                    (unsigned)advertised);
        return 1;
    }

    switch (request[4]) {
    case 1:
        return ble_put_op9_action1_single(ctx, packet, request, advertised,
                                         response);
    case 2:
        return ble_put_op9_action2_mark(ctx, request, advertised, response);
    case 3:
    case 7:
        return ble_put_op9_action3_7(ctx, packet, request, advertised,
                                    response);
    case 5:
        return ble_put_op9_action5_exit(ctx, request, response);
    default:
        return 1;
    }
}

_Static_assert(offsetof(struct ble_put_context_09_10, post_to_host) == 0x0c,
               "post callback offset");
_Static_assert(offsetof(struct ble_put_context_09_10, rx) == 0x10,
               "rx offset");
_Static_assert(offsetof(struct ble_put_context_09_10, frame_length) == 0x14,
               "frame length offset");
_Static_assert(offsetof(struct ble_put_context_09_10, imu_state) == 0x870,
               "state offset");
_Static_assert(offsetof(struct ble_put_context_09_10, teleprompter) == 0x880,
               "teleprompter offset");

#endif
