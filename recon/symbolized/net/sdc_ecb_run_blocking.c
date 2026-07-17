#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a7e8 @ 0x0100a7e8
 * public-name: sdc_ecb_run_blocking
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_ecb_run_blocking                     <= FUN_0100a7e8 @ 0x0100a7e8
 * address symbols (name @ address):
 *   REG_4100d000                             @ 0x4100d000
 */
/* net-core sdc_ecb_run_blocking @ 0x0100a7e8
 * Back-map: FUN_0100a7e8.  Runs one 48-byte key/plaintext/ciphertext ECB
 * transaction against the nRF5340 network-core ECB peripheral.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int sdc_byte_lock_try_acquire(volatile uint8_t *lock);
extern void sdc_byte_lock_release(volatile uint8_t *lock);
extern void sdc_cpu_relax(void);

struct nrf_ecb_registers {
    volatile uint32_t TASKS_STARTECB;              /* 0x000 */
    volatile uint32_t TASKS_STOPECB;               /* 0x004 */
    uint32_t reserved_008[62];
    volatile uint32_t EVENTS_ENDECB;               /* 0x100 */
    volatile uint32_t EVENTS_ERRORECB;             /* 0x104 */
    uint32_t reserved_108[127];
    volatile uint32_t INTENSET;                    /* 0x304 */
    volatile uint32_t INTENCLR;                    /* 0x308 */
    uint32_t reserved_30c[126];
    volatile uint32_t ECBDATAPTR;                  /* 0x504 */
};

enum {
    ECB_INTERRUPT_MASK = 3,
    ECB_NETWORK_IRQ_PENDING_MASK = 0x2000,
    SCB_SCR_SEVONPEND_MASK = 0x10,
};

void sdc_ecb_run_blocking(uint32_t ecb_data_address)
{
    volatile uint8_t *const ownership = (volatile uint8_t *)0x21000bf4;
    volatile struct nrf_ecb_registers *const ecb =
        (volatile struct nrf_ecb_registers *)REG_4100d000 /*=0x4100d000*/;
    volatile uint32_t *const scb_scr = (volatile uint32_t *)0xe000ed10;
    volatile uint32_t *const nvic_icpr2 = (volatile uint32_t *)0xe000e280;
    int lock_status;

    for (;;) {
        lock_status = sdc_byte_lock_try_acquire(ownership);
        if (lock_status != 0) {
            ownership[1] = 0xff;
        }

        do {
            ecb->TASKS_STOPECB = 1;
            ecb->EVENTS_ENDECB = 0;
            ecb->EVENTS_ERRORECB = 0;
            ecb->ECBDATAPTR = ecb_data_address;
            ecb->TASKS_STARTECB = 1;

            while ((ecb->EVENTS_ENDECB == 0) &&
                   (ecb->EVENTS_ERRORECB == 0)) {
                /* SDC supports callers that set SCR.SEVONPEND while waiting.
                 * Clear the ECB pending bit and poll once with interrupts
                 * masked so the weak wait hook cannot race event delivery. */
                if ((*scb_scr & SCB_SCR_SEVONPEND_MASK) != 0) {
                    uint32_t saved_primask;

                    *nvic_icpr2 = ECB_NETWORK_IRQ_PENDING_MASK;
                    saved_primask = __get_PRIMASK();
                    __disable_irq();
                    ecb->INTENSET = ECB_INTERRUPT_MASK;
                    if ((ecb->EVENTS_ENDECB == 0) &&
                        (ecb->EVENTS_ERRORECB == 0)) {
                        sdc_cpu_relax();
                    }
                    if (saved_primask == 0) {
                        __enable_irq();
                    }
                }
            }
        } while (ecb->EVENTS_ERRORECB != 0);

        if (lock_status != 0) {
            return;
        }

        {
            uint8_t retry_requested = ownership[1];
            ownership[1] = 0;
            ecb->INTENCLR = ECB_INTERRUPT_MASK;
            ecb->EVENTS_ERRORECB = 0;
            ecb->EVENTS_ENDECB = 0;
            *nvic_icpr2 = ECB_NETWORK_IRQ_PENDING_MASK;
            sdc_byte_lock_release(ownership);
            if (retry_requested == 0) {
                return;
            }
        }
    }
}
