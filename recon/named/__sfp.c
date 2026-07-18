/* readable reconstruction; identity: FUN_00076c3c @ 0x00076c3c
 * public-name: __sfp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __sfp_lock_acquire                       <= FUN_00076b9c @ 0x00076b9c
 *   __sfp_lock_release                       <= FUN_00076ba8 @ 0x00076ba8
 *   __sinit                                  <= FUN_00076bcc @ 0x00076bcc
 *   __sfp                                    <= FUN_00076c3c @ 0x00076c3c
 *   __sfmoreglue                             <= FUN_00086b14 @ 0x00086b14
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9873c                             @ 0x0009873c
 */
/* Reconstructed FUN_00076c3c @ 0x76c3c */
#include <stdint.h>
#include <stddef.h>
extern void __sfp_lock_acquire(void);
extern void __sfp_lock_release(void);
extern void __sinit(void *);
extern void FUN_0005109c(void *);
extern void *__sfmoreglue(void *, uint32_t);
extern void *memset_bytes(void *, int, size_t);

void *__sfp(uint32_t *error)
{
    __sfp_lock_acquire();
    uint8_t *root = *(uint8_t **)(uintptr_t)0x0009873c;
    if (*(uint32_t *)(root + 0x18) == 0) __sinit(root);
    uint8_t *block = root + 0x48;
    for (;;) {
        int32_t count = *(int32_t *)(block + 4);
        volatile uint8_t *slot = *(uint8_t **)(block + 8);
        while (--count >= 0) {
            if (*(volatile int16_t *)(slot + 0x0c) == 0) {
                *(volatile uint32_t *)(slot + 0x64) = 0;
                *(volatile uint32_t *)(slot + 0x0c) = 0xffff0001;
                FUN_0005109c((void *)(slot + 0x58));
                __sfp_lock_release();
                *(volatile uint32_t *)(slot + 0x00) = 0;
                *(volatile uint32_t *)(slot + 0x18) = 0;
                *(volatile uint32_t *)(slot + 0x04) = 0;
                *(volatile uint32_t *)(slot + 0x08) = 0;
                *(volatile uint32_t *)(slot + 0x10) = 0;
                *(volatile uint32_t *)(slot + 0x14) = 0;
                memset_bytes((void *)(slot + 0x5c), 0, 8);
                *(volatile uint32_t *)(slot + 0x34) = 0;
                *(volatile uint32_t *)(slot + 0x38) = 0;
                *(volatile uint32_t *)(slot + 0x48) = 0;
                *(volatile uint32_t *)(slot + 0x4c) = 0;
                return (void *)slot;
            }
            slot += 0x68;
        }
        if (*(uint8_t **)block == 0) {
            void *next = __sfmoreglue(error, 4);
            *(void **)block = next;
            if (!next) { __sfp_lock_release(); *error = 12; return 0; }
        }
        block = *(uint8_t **)block;
    }
}
