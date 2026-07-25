/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
extern unsigned char g1_net_ram_blk_21001ce8[];
extern unsigned char g1_net_ram_blk_210045b0[];
extern unsigned char g1_net_ram_blk_210045e0[];
extern unsigned char g1_net_ram_blk_21004b30[];
extern unsigned char g1_net_ram_blk_21004c98[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#define G1N_21001ce8 ((unsigned long)(g1_net_ram_blk_21001ce8 + 0x0))
#define G1N_21001cf8 ((unsigned long)(g1_net_ram_blk_21001ce8 + 0x10))
#define G1N_21001d00 ((unsigned long)(g1_net_ram_blk_21001ce8 + 0x18))
#define G1N_210045c0 ((unsigned long)(g1_net_ram_blk_210045b0 + 0x10))
#define G1N_210045f4 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x14))
#define G1N_21004b9e ((unsigned long)(g1_net_ram_blk_21004b30 + 0x6e))
#define G1N_21004c9e ((unsigned long)(g1_net_ram_blk_21004c98 + 0x6))
#define G1N_21004c9f ((unsigned long)(g1_net_ram_blk_21004c98 + 0x7))
#else
#define G1N_21000580 0x21000580ul
#define G1N_21001ce8 0x21001ce8ul
#define G1N_21001cf8 0x21001cf8ul
#define G1N_21001d00 0x21001d00ul
#define G1N_210045c0 0x210045c0ul
#define G1N_210045f4 0x210045f4ul
#define G1N_21004b9e 0x21004b9eul
#define G1N_21004c9e 0x21004c9eul
#define G1N_21004c9f 0x21004c9ful
#endif
/* net-core custom main [raw back-map: FUN_0102a720 @ 0x0102a720].
 *
 * The shipped image enters this routine from Zephyr bg_thread_main.  It
 * brings up the cpunet-hw-id IPC endpoint, publishes the selected radio role
 * and addresses, starts the ESB service, and then reports stable link-state
 * transitions.  Fixed addresses below retain the reversible firmware map.
 */
#ifdef G1_COHESIVE_BUILD
/* P4 iteration 20 - the recovered ESB pipe-address block at 0x21000760.
 * Twelve bytes, `.data` in the shipped image (initialiser
 * 01 e9 d3 a3 a3 a3 a3 c9 c9 c9 c9 ff, read with tools/net_extract.py), ending
 * exactly where the SHIPPED _sw_isr_table began (0x2100076c, established in
 * iteration 19).  In the cohesive link those twelve bytes land at
 * _sw_isr_table + 0x5c .. + 0x67, i.e. entries 11 and 12 of the LINKER's own
 * interrupt table.  Bind the emitted object in
 * recon/application/net/src/g1_product_endpoints.c instead.  Parity builds
 * keep the original literals. */
extern unsigned char g1_esb_pipe_addr_block[];
#define G1_NET_ESB_ADDR_BASE ((unsigned long)g1_esb_pipe_addr_block)
#else
#define G1_NET_ESB_ADDR_BASE 0x21000760ul
#endif
#define G1_NET_ESB_ADDR(off) (G1_NET_ESB_ADDR_BASE + (off))

#include <stdint.h>

/* Keep the production spelling readable while emitting the reversible raw
 * symbol expected by parity and address-map tooling. */
#define main FUN_0102a720
#define net_global_init FUN_0102ac0c
#define net_heap_alloc FUN_0103b530
#define net_memset FUN_0103b62e
#define net_sem_init FUN_0103b224
#define hw_id_endpoint_bind FUN_0102acb4
#define refresh_shared_role FUN_0102a620
#define read_device_address FUN_0102b094
#define select_fallback_role FUN_0102cfbc
#define select_bt_identity FUN_01033acc
#define prepare_esb_workers FUN_0102b2ac
#define start_esb_worker_threads FUN_0102afbc
#define esb_service_init FUN_0102b5bc
#define esb_link_state_get FUN_0102b7b8
#define publish_link_state FUN_0102a394
#define net_uptime_ticks thunk_FUN_01038284
#define net_sleep_ms FUN_0103961c
#define net_printk FUN_01039722
#define copy_c_string FUN_0102a258

extern void net_global_init(void);
extern uint32_t net_heap_alloc(uint32_t size);
extern void net_memset(void *dst, int value, uint32_t size);
extern void net_sem_init(void *sem, uint32_t initial, uint32_t limit);
extern void hw_id_endpoint_bind(void *state);
extern uint32_t refresh_shared_role(void);
extern void read_device_address(void *dst);
extern uint32_t select_fallback_role(uint32_t role);
extern void select_bt_identity(uint32_t identity);
extern void prepare_esb_workers(void *state);
extern void start_esb_worker_threads(void);
extern int esb_service_init(uint32_t primary_role, const void *event_handler);
extern uint32_t esb_link_state_get(void);
extern int publish_link_state(void);
extern uint64_t net_uptime_ticks(void);
extern void net_sleep_ms(uint32_t delay);
extern void net_printk(const char *format, ...);
extern void copy_c_string(char *dst, const char *src);
#ifdef G1_COHESIVE_BUILD
extern void FUN_0102a4c8(const void *event);
#define G1_ESB_EVENT_HANDLER ((const void *)(uintptr_t)&FUN_0102a4c8) /*=0x0102acc9*/
/* The "cpunet-hw-id" service handler.  The shipped literal 0x0102aa79 is the
 * runtime Thumb address of the reconstruction at analysis VA 0x0102a278
 * (runtime = analysis + 0x800); FUN_0102ab14 loads it back out of the
 * registered endpoint descriptor and calls it.  Left as a raw literal it lands
 * on whatever this build's layout happens to place there. */
extern int FUN_0102a278(uint8_t *state, const uint8_t *packet, uint32_t size);
#define G1_HW_ID_SERVICE_HANDLER \
    ((const void *)(uintptr_t)&FUN_0102a278) /*=0x0102aa79*/
#else
#define G1_ESB_EVENT_HANDLER ((const void *)UINT32_C(0x0102acc9))
#define G1_HW_ID_SERVICE_HANDLER ((const void *)UINT32_C(0x0102aa79))
#endif

typedef int (*ipc_send_fn)(const void *message, uint32_t size);
typedef void (*ipc_register_fn)(const void *configuration);
typedef void (*ipc_ready_fn)(void);

struct net_service_state {
    uint32_t role;                 /* +0x00: 0 waiting, 1 master, 2 slave */
    uint32_t mode;                 /* +0x04 */
    uint32_t bt_identity;          /* +0x08 */
    uint8_t sem_a[0x18];           /* +0x0c */
    uint8_t sem_b[0x18];           /* +0x24 */
    uint8_t endpoint_cfg[0x0c];    /* +0x3c */
    uint8_t endpoint_state[0x60];  /* +0x48 */
    ipc_send_fn send;              /* +0xa8 */
    ipc_register_fn register_ep;   /* +0xac */
    ipc_ready_fn ready;            /* +0xb0 */
    uint8_t private_state[0x10];   /* +0xb4 */
    uint8_t primary_addr[6];       /* +0xc4 */
    uint8_t secondary_addr[6];     /* +0xca */
};

struct ipc_endpoint_cfg {
    uint8_t id;
    uint8_t reserved[3];
    const char *name;
    const void *callback;
};

static volatile int32_t *const net_log_level = (volatile int32_t *)G1N_21000580;
static struct net_service_state **const service_slot =
    (struct net_service_state **)G1N_210045f4;

static inline __attribute__((always_inline)) int
send_retry(struct net_service_state *state, const void *message,
           uint32_t size, uint32_t delay_ms)
{
    int result = -1;
    for (uint32_t attempt = 0; attempt != 20; ++attempt) {
        result = state->send(message, size);
        if (result >= 0) {
            break;
        }
        net_sleep_ms(delay_ms);
    }
    return result;
}

int main(void)
{
    if (*net_log_level > 1) {
        net_printk((const char *)0x0103cd64u, (const char *)0x0103cd50u);
    }

    net_global_init();
    if (*net_log_level > 1) {
        net_printk((const char *)0x0103cd6cu);
    }

    struct net_service_state *state =
        (struct net_service_state *)(uintptr_t)net_heap_alloc(0xd0);
    net_memset(state, 0, 0xd0);
    *(volatile uint32_t *)&state->primary_addr[0] = UINT32_MAX;
    *(volatile uint16_t *)&state->primary_addr[4] = UINT16_MAX;
    *(volatile uint32_t *)&state->secondary_addr[0] = UINT32_MAX;
    *(volatile uint16_t *)&state->secondary_addr[4] = UINT16_MAX;
    net_sem_init(state->sem_a, 0, 1);
    net_sem_init(state->sem_b, 0, 1);
    state->bt_identity = 0xff;
    hw_id_endpoint_bind(state->endpoint_state);

    struct ipc_endpoint_cfg *cfg = (struct ipc_endpoint_cfg *)state->endpoint_cfg;
    cfg->id = 1;
    cfg->name = (const char *)0x0103cd79u;       /* "cpunet-hw-id" */
    cfg->callback = G1_HW_ID_SERVICE_HANDLER;    /* raw back-map 0x0102aa79 */
    state->register_ep(cfg);
    if (*net_log_level > 1) {
        net_printk((const char *)0x0103cd86u);
    }

    *service_slot = state;
    for (uint32_t attempt = 0; attempt != 20 && state->role == 0; ++attempt) {
        refresh_shared_role();
        uint16_t registration[4] = {0x0201, 0, 0, 0};
        state->send(registration, sizeof(registration));
        if (*net_log_level > 1) {
            net_printk((const char *)0x0103cd8cu);
        }
        if (state->role == 0) {
            net_sleep_ms(300);
        }
    }

    if (state->role == 0) {
        state = (struct net_service_state *)(uintptr_t)select_fallback_role(1);
    }
    if (*net_log_level > 1) {
        net_printk((const char *)0x0103cd94u, state->role, state->mode);
    }
    if (state->role == 1) {
        read_device_address(state->primary_addr);
        if (*net_log_level > 1) {
            net_printk((const char *)0x0103cda5u);
        }
    } else if (state->role == 2) {
        read_device_address(state->secondary_addr);
        if (*net_log_level > 1) {
            net_printk((const char *)0x0103ce32u);
        }
    }

    struct {
        uint16_t command;
        uint8_t address[6];
        uint32_t reserved[2];
    } address_message;
    ((uint32_t *)&address_message)[0] = 0;
    ((uint32_t *)&address_message)[1] = 0;
    ((uint32_t *)&address_message)[2] = 0;
    ((uint32_t *)&address_message)[3] = 0;
    address_message.command = 0x0301;
    if (state->role == 1) {
        *(uint32_t *)&address_message.address[0] = *(uint32_t *)&state->primary_addr[0];
        *(uint16_t *)&address_message.address[4] = *(uint16_t *)&state->primary_addr[4];
    } else {
        *(uint32_t *)&address_message.address[0] = *(uint32_t *)&state->secondary_addr[0];
        *(uint16_t *)&address_message.address[4] = *(uint16_t *)&state->secondary_addr[4];
    }
    send_retry(state, &address_message, sizeof(address_message), 50);

    for (uint32_t attempt = 0; attempt != 20; ++attempt) {
        if (refresh_shared_role() == 0) {
            break;
        }
        net_sleep_ms(50);
    }
    *(volatile uint32_t *)G1N_210045c0 = 0;

    select_bt_identity(state->bt_identity == 0xff ? 0 : state->bt_identity);
    if (state->bt_identity != 0xff) {
        *(volatile uint8_t *)G1N_21004b9e = (uint8_t)state->bt_identity;
    }
    if (*net_log_level > 1) {
        const volatile uint8_t *address0 = (const volatile uint8_t *)G1_NET_ESB_ADDR(0x7);
        net_printk((const char *)0x0103cdadu, address0[0], address0[1],
                   address0[2], address0[3]);
        if (*net_log_level > 1) {
            const volatile uint8_t *address1 = (const volatile uint8_t *)G1_NET_ESB_ADDR(0x3);
            net_printk((const char *)0x0103cdd1u, address1[0], address1[1],
                       address1[2], address1[3]);
        }
    }

    if (state->role == 1 || state->role == 2) {
        prepare_esb_workers((uint8_t *)state + 0xb0);
        start_esb_worker_threads();
        net_sleep_ms(1000);
        state->ready();
    }
    uint32_t primary_role = state->role == 1 ? 0 : 1;
    int error = esb_service_init(primary_role, G1_ESB_EVENT_HANDLER);
    if ((uint8_t)error != 0) {
        if (*net_log_level > 0) {
            net_printk((const char *)0x0103cdf5u);
        }
        return 0;
    }

    uint8_t build_message[32];
    *(uint32_t *)&build_message[0] = 0;
    net_memset(&build_message[4], 0, 28);
    *(uint16_t *)&build_message[0] = 0x0601;
    copy_c_string((char *)&build_message[2], (const char *)0x0103cd50u);
    send_retry(state, build_message, sizeof(build_message), 100);
    refresh_shared_role();

    volatile uint64_t *const previous_transition_ms = (volatile uint64_t *)G1N_21001ce8;
    volatile uint64_t *const current_transition_ms = (volatile uint64_t *)G1N_21001cf8;
    volatile uint64_t *const current_ticks = (volatile uint64_t *)G1N_21001d00;
    volatile uint8_t *const stable_state = (volatile uint8_t *)G1N_21004c9e;
    volatile uint8_t *const observed_state = (volatile uint8_t *)G1N_21004c9f;
    uint32_t crossing_count = 0;

    for (;;) {
        if (esb_link_state_get() != 3 && state->mode != 1) {
            uint64_t ticks = net_uptime_ticks();
            *current_ticks = ticks;
            uint64_t now_ms = (ticks * UINT64_C(1000) + UINT64_C(0x7fff)) >> 15;
            *current_transition_ms = now_ms;

            uint8_t prior = *stable_state;
            uint8_t observed = *observed_state;
            if (prior > 50) {
                if ((uint8_t)(observed - 1) < 39) {
                    ++crossing_count;
                } else {
                    crossing_count = 0;
                }
            } else if (prior < 40) {
                crossing_count = observed < 51 ? 0 : 3;
            }

            uint64_t elapsed = now_ms - *previous_transition_ms;
            if (elapsed >= UINT64_C(10000)) {
                *previous_transition_ms = now_ms;
                (void)publish_link_state();
            } else {
                int crossed = ((observed < 40 && prior > 50) ||
                               (observed > 50 && prior < 40));
                if (crossed && crossing_count > 2 &&
                    publish_link_state() != 0) {
                    *previous_transition_ms = now_ms;
                    crossing_count = 0;
                    *stable_state = observed;
                }
            }
        }
        net_sleep_ms(1000);
    }
}
