/* net-core FUN_0102adac @ 0x0102adac
 * Readable identity: hci_rpmsg_tx_thread.
 * Raw back-map: FUN_0102afbc stores runtime Thumb pointer 0x0102b5ad.
 */
#include <stdint.h>

#define hci_rpmsg_tx_thread FUN_0102adac

extern void *FUN_0103a456(void *fifo, int64_t timeout);
extern int FUN_0102fcd8(void *buffer);
extern void FUN_0102ff94(void *buffer);
extern void FUN_01037a60(void);
extern void FUN_01039722(const char *format, ...);

void hci_rpmsg_tx_thread(void)
{
    for (;;) {
        void *buffer = FUN_0103a456((void *)0x21000978u, -1);
        int status = FUN_0102fcd8(buffer);
        if (status != 0) {
            if (*(volatile int32_t *)0x21000580u > 0)
                FUN_01039722((const char *)0x0103cf46u, status);
            FUN_0102ff94(buffer);
        }
        FUN_01037a60();
    }
}
