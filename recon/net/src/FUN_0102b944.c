/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
extern unsigned char g1_net_ram_blk_21004fa0[];
#define G1N_2100462c ((unsigned long)(g1_net_ram_blk_210045e0 + 0x4c))
#define G1N_21004630 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x50))
#define G1N_21004638 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x58))
#define G1N_21004fa4 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x4))
#define G1N_21004fa6 ((unsigned long)(g1_net_ram_blk_21004fa0 + 0x6))
#else
#define G1N_2100462c 0x2100462cul
#define G1N_21004630 0x21004630ul
#define G1N_21004638 0x21004638ul
#define G1N_21004fa4 0x21004fa4ul
#define G1N_21004fa6 0x21004fa6ul
#endif
/* net-core FUN_0102b944 @ 0x0102b944; true code extent 0x232. */
#include <stdint.h>

extern uint32_t FUN_0102a4a4(void);
extern uint32_t FUN_0102b7c4(void);
extern void FUN_0102b7d0(uint32_t enabled);
extern int FUN_0102b900(uint32_t value);
extern uint32_t FUN_0102a498(void);
extern void FUN_010327d8(void);

typedef struct {
    volatile uint8_t action;
    uint8_t reserved[3];
    volatile void *request;
} timeslot_return_t;

#define RETURN_PARAM ((timeslot_return_t *)G1N_21004630)
/* P4 iteration 21 - the three shipped mpsl_timeslot_request_t objects.
 *
 * netcore .data (read with tools/net_extract.py at the net .data LMA,
 * analysis 0x0103e524 + VMA offset) holds them back to back:
 *   0x210005b8  NORMAL   hfclk=1 prio=0 distance=50000 length=5000   (role 0)
 *   0x210005c8  NORMAL   hfclk=1 prio=0 distance=50000 length=5000   (role 1)
 *   0x210005d8  EARLIEST hfclk=1 prio=0 length=5000 timeout=1000000
 * They are emitted by recon/application/net/src/timeslot_owner.c.  Left as raw
 * literals in the cohesive link they landed at
 * g1_timeslot_request_earliest+0x4, g1_timeslot_request_normal+0x4 and
 * nrf53_sync_offset+0x0 -- all three wrong, and this body is the timeslot
 * SIGNAL callback, so MPSL would have followed them.  Parity keeps the
 * original literals. */
#ifdef G1_COHESIVE_BUILD
#include <mpsl_timeslot.h>
extern mpsl_timeslot_request_t g1_timeslot_request_normal;
extern mpsl_timeslot_request_t g1_timeslot_request_normal_role1;
extern mpsl_timeslot_request_t g1_timeslot_request_earliest;
#define ROLE_REQUEST_1 ((void *)&g1_timeslot_request_normal_role1) /*=0x210005c8*/
#define ROLE_REQUEST_0 ((void *)&g1_timeslot_request_normal)       /*=0x210005b8*/
#define SPECIAL_REQUEST ((void *)&g1_timeslot_request_earliest)    /*=0x210005d8*/
#else
#define ROLE_REQUEST_1 ((void *)0x210005c8u)
#define ROLE_REQUEST_0 ((void *)0x210005b8u)
#define SPECIAL_REQUEST ((void *)0x210005d8u)
#endif
#define RADIO_BASE ((volatile uint32_t *)0x41008000u)
#define DPPIC_BASE ((volatile uint32_t *)0x4100c000u)
#define NVIC_BASE ((volatile uint32_t *)0xe000e100u)

static inline void timeslot_io_set(void)
{
    *(volatile uint32_t *)0x418c0508u = 0x10000000u;
}

static inline void timeslot_io_clear(void)
{
    *(volatile uint32_t *)0x418c050cu = 0x10000000u;
}

static inline void select_role_request(void)
{
    RETURN_PARAM->request = (FUN_0102a4a4() == 1u) ?
                            ROLE_REQUEST_1 : ROLE_REQUEST_0;
}

timeslot_return_t *FUN_0102b944(uint8_t session_id, uint32_t signal_type,
                                uint32_t incoming_r2)
{
    (void)session_id;
    timeslot_io_set();

    switch (signal_type) {
    case 0:
        RETURN_PARAM->action = 0;
        select_role_request();
        *(volatile uint8_t *)G1N_21004fa4 = 0;
        *(volatile uint32_t *)G1N_21004638 = 0;
        NVIC_BASE[0x180u / 4u] = 0x100u;
        RADIO_BASE[0xffcu / 4u] = 0;
        RADIO_BASE[0xffcu / 4u] = 1;
        NVIC_BASE[0x180u / 4u] = 0x100u;
        DPPIC_BASE[0x508u / 4u] |= 3u;
        DPPIC_BASE[0x540u / 4u] = 0xf49u;
        DPPIC_BASE[0x304u / 4u] = 0x10000u;
        DPPIC_BASE[0x544u / 4u] = 0x12cdu;
        DPPIC_BASE[0x304u / 4u] = 0x20000u;
        FUN_0102b7d0(1);
        break;

    case 1: {
        uint32_t role_signal = (uint8_t)FUN_0102b7c4();
        volatile uint32_t *retry = (volatile uint32_t *)G1N_2100462c;

        if (DPPIC_BASE[0x140u / 4u] != 0u) {
            DPPIC_BASE[0x308u / 4u] = 0x10000u;
            DPPIC_BASE[0x140u / 4u] = 0;
            (void)DPPIC_BASE[0x140u / 4u];

            uint32_t role = FUN_0102a4a4();
            if (role_signal == 0u) {
                uint32_t delay = 50000u + 5000u * *retry;
                RETURN_PARAM->action = 0;
                ((volatile uint32_t *)(role == 1u ? ROLE_REQUEST_1 :
                                       ROLE_REQUEST_0))[2] = delay;
                *retry = 0;
                FUN_0102b7d0(0);
            } else {
                *retry = *retry + 1u;
                RETURN_PARAM->action = 1;
                RETURN_PARAM->request = (void *)5000u;
            }
        } else if (DPPIC_BASE[0x144u / 4u] != 0u) {
            DPPIC_BASE[0x308u / 4u] = 0x20000u;
            DPPIC_BASE[0x144u / 4u] = 0;
            (void)DPPIC_BASE[0x144u / 4u];
            select_role_request();
            uint8_t pending = *(volatile uint8_t *)G1N_21004fa4;
            RETURN_PARAM->action = 3;
            if (pending != 0u) {
                RETURN_PARAM->request = SPECIAL_REQUEST;
            }
        }
        break;
    }

    case 2:
        RETURN_PARAM->action = 0;
        if (*(volatile uint8_t *)G1N_21004fa6 != 0u) {
            FUN_010327d8();
        } else {
            NVIC_BASE[0x180u / 4u] = 0x100u;
            NVIC_BASE[0x080u / 4u] = 0x100u;
            __asm volatile("dsb sy\n\tisb sy" ::: "memory");
        }
        break;

    case 3:
        RETURN_PARAM->action = 0;
        *(volatile uint8_t *)G1N_21004fa4 = 1;
        *(volatile uint32_t *)G1N_2100462c = 0;
        FUN_0102b7d0(0);
        break;

    case 4: {
        RETURN_PARAM->action = 0;
        uint32_t endpoint = DPPIC_BASE[0x540u / 4u] + 5000u;
        DPPIC_BASE[0x508u / 4u] |= 3u;
        DPPIC_BASE[0x540u / 4u] = endpoint;
        DPPIC_BASE[0x304u / 4u] = 0x10000u;
        endpoint = DPPIC_BASE[0x544u / 4u] + 5000u;
        DPPIC_BASE[0x508u / 4u] |= 3u;
        DPPIC_BASE[0x544u / 4u] = endpoint;
        DPPIC_BASE[0x304u / 4u] = 0x20000u;
        break;
    }

    case 5:
        RETURN_PARAM->action = 0;
        FUN_0102b7d0(0);
        if (FUN_0102a498() != 1u) {
            uint32_t role = FUN_0102a4a4();
            if (role != 1u) {
                ++*(volatile uint32_t *)G1N_21004638;
                role = 2;
            }
            FUN_0102b900(role);
        }
        break;

    case 6:
        RETURN_PARAM->action = 0;
        FUN_0102b7d0(0);
        FUN_0102b900(1);
        break;

    case 7:
        FUN_0102b900(1);
        RETURN_PARAM->action = 0;
        FUN_0102b7d0(0);
        break;

    case 8:
    case 10:
        RETURN_PARAM->action = 2;
        FUN_0102b7d0(0);
        FUN_0102b900(1);
        break;

    case 9:
        RETURN_PARAM->action = 0;
        FUN_0102b7d0(0);
        break;

    default:
        __asm volatile(
            "eors r0, r0\n\t"
            "msr basepri, r0\n\t"
            "mov r1, %0\n\t"
            "mov r2, %1\n\t"
            "mov.w r3, #0x10000000\n\t"
            "mov r0, #3\n\t"
            "svc #2"
            :: "r"(signal_type), "r"(incoming_r2)
            : "r0", "r1", "r2", "r3", "cc", "memory");
        timeslot_io_clear();
        return (timeslot_return_t *)0;
    }

    timeslot_io_clear();
    return RETURN_PARAM;
}
