/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#else
#define G1N_21000580 0x21000580ul
#endif
/* net-core FUN_0102adf0 @ 0x0102adf0
 * Readable identity: hci_rpmsg_rx.
 * Raw back-map: initialized endpoint stores Thumb pointer 0x0102b5f1.
 */
#include <stdint.h>

#ifdef G1_COHESIVE_BUILD
#include <zephyr/logging/log.h>
#include <zephyr/net/buf.h>
LOG_MODULE_REGISTER(hci_rpmsg, LOG_LEVEL_INF);
#define FUN_0103a468(simple) \
    net_buf_simple_tailroom((struct net_buf_simple *)(simple))
#define FUN_0103a478(simple, data, size) \
    net_buf_simple_add_mem((struct net_buf_simple *)(simple), (data), (size))
#else
extern uint32_t FUN_0103a468(void *buffer_simple);
extern void FUN_0103a478(void *buffer_simple, const void *data, uint32_t size);
#endif

#define hci_rpmsg_rx FUN_0102adf0

extern void *FUN_0102fc30(uint32_t type, uint32_t aligned_pad,
                          uint32_t timeout_low, uint32_t timeout_high,
                          const void *header, uint32_t header_size);
extern void FUN_0102ff94(void *buffer);
extern void FUN_0102ff54(void *queue, void *buffer);
extern void FUN_01039722(const char *format, ...);

static volatile int32_t *const log_level = (volatile int32_t *)G1N_21000580;
/* P4 iteration 18: see recon/net/src/FUN_0102adac.c -- 0x21000978 (the shipped
 * `static K_FIFO_DEFINE(tx_queue)`) lands inside net_buf_pool_area in the
 * cohesive link. */
#ifdef G1_COHESIVE_BUILD
extern struct k_fifo g1_hci_tx_queue;
static void *const tx_queue = (void *)&g1_hci_tx_queue;
#else
static void *const tx_queue = (void *)0x21000978u;
#endif

void hci_rpmsg_rx(uint8_t *data, uint32_t length)
{
    uint8_t indicator = *data++;
    uint32_t remaining = length - 1u;
    void *buffer;
    uint32_t header_size;
    uint32_t expected;
    uint32_t type;

    if (indicator == 1) {
        header_size = 3;
        if (remaining < header_size) {
            if (*log_level > 0)
                FUN_01039722((const char *)0x0103cf5eu, indicator);
            return;
        }
        type = 0;
        expected = data[2];
    } else if (indicator == 2) {
        header_size = 4;
        if (remaining < header_size) {
            if (*log_level > 0)
                FUN_01039722((const char *)0x0103cfc3u, indicator);
            return;
        }
        type = 2;
        expected = (uint32_t)data[2] | ((uint32_t)data[3] << 8);
    } else if (indicator == 5) {
        header_size = 4;
        if (remaining < header_size) {
            if (*log_level > 0)
                FUN_01039722((const char *)0x0103d00bu, indicator);
            return;
        }
        type = 4;
        expected = ((uint32_t)data[2] | ((uint32_t)data[3] << 8)) & 0x3fffu;
    } else {
        if (*log_level > 0)
            FUN_01039722((const char *)0x0103d053u, indicator);
        return;
    }

    /* The source API's 64-bit timeout is even-register aligned.  The shipped
     * call leaves the packet indicator in the r1 alignment hole. */
    buffer = FUN_0102fc30(type, indicator, 0, 0, data, header_size);
    if (buffer == 0) {
        const char *message = indicator == 1 ? (const char *)0x0103cf78u :
                              indicator == 2 ? (const char *)0x0103cfd9u :
                                               (const char *)0x0103d021u;
        if (*log_level > 0)
            FUN_01039722(message);
        return;
    }

    data += header_size;
    remaining -= header_size;
    if (remaining != expected) {
        const char *message = indicator == 1 ? (const char *)0x0103cf96u :
                              indicator == 2 ? (const char *)0x0103cff3u :
                                               (const char *)0x0103d03bu;
        if (*log_level > 0)
            FUN_01039722(message);
        FUN_0102ff94(buffer);
        return;
    }

    void *simple = (uint8_t *)buffer + 12;
    if (remaining > FUN_0103a468(simple)) {
        if (*log_level > 0)
            FUN_01039722((const char *)0x0103cfb2u);
        FUN_0102ff94(buffer);
        return;
    }

    FUN_0103a478(simple, data, remaining);
    FUN_0102ff54(tx_queue, buffer);
}
