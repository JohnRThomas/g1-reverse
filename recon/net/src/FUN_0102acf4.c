/* net-core FUN_0102acf4 @ 0x0102acf4
 * Readable identity: g1_hci_rpmsg_tx_thread.
 * Raw back-map: FUN_0102afbc stores runtime Thumb pointer 0x0102b4f5.
 */
#include <stdint.h>

#define g1_hci_rpmsg_tx_thread FUN_0102acf4

extern int FUN_0103689c(void *sem, int64_t timeout);
extern void *FUN_0103a456(void *fifo, int64_t timeout);
extern void FUN_0103a45a(void *simple, uint32_t byte);
extern int FUN_0102d618(void *endpoint, const void *data, uint32_t size);
extern void FUN_0102ff94(void *buffer);
extern void FUN_01037a60(void);
extern void FUN_01039722(const char *format, ...);

struct g1_net_buf {
    uint8_t reserved[12];
    const void *data;
    uint16_t len;
    uint8_t reserved2[6];
    uint8_t type;
};

void g1_hci_rpmsg_tx_thread(void)
{
    FUN_0103689c((void *)0x2100092cu, -1);
    for (;;) {
        struct g1_net_buf *buffer = FUN_0103a456((void *)0x2100095cu, -1);
        *(volatile uint32_t *)0x418c0508u = 0x40000000u;
        uint32_t indicator;
        if (buffer->type == 3)
            indicator = 2;
        else if (buffer->type == 5)
            indicator = 5;
        else if (buffer->type == 1)
            indicator = 4;
        else {
            if (*(volatile int32_t *)0x21000580u > 0)
                FUN_01039722((const char *)0x0103cf17u, buffer->type);
            FUN_0102ff94(buffer);
            *(volatile uint32_t *)0x418c050cu = 0x40000000u;
            continue;
        }
        FUN_0103a45a((uint8_t *)buffer + 12, indicator);
        uint8_t failures = 0;
        while (FUN_0102d618((void *)0x21004608u,
                            buffer->data, buffer->len) < 0) {
            failures = (uint8_t)(failures + 1u);
            if (failures == 11) {
                if (*(volatile int32_t *)0x21000580u > 1)
                    FUN_01039722((const char *)0x0103cf28u);
                failures = 0;
            }
            FUN_01037a60();
        }
        FUN_0102ff94(buffer);
        *(volatile uint32_t *)0x418c050cu = 0x40000000u;
    }
}
