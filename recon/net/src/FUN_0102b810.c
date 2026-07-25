/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
extern unsigned char g1_net_ram_blk_210045e0[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#define G1N_21004638 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x58))
#else
#define G1N_21000580 0x21000580ul
#define G1N_21004638 0x21004638ul
#endif
/* CPUNET non-preemptible MPSL API worker @ 0x0102b810.
 * Raw back-map: FUN_0102b810@0x0102b810; true extent 0xc8.
 *
 * The four queue opcodes are the configured NCS distance-measurement
 * timeslot API calls: open session, request earliest, request normal, and
 * close session.  Unlike the stock sample, this image treats an API error or
 * an invalid opcode as fatal after its optional diagnostic.
 */

#include <stdint.h>

/* Readable source identity; preprocessing preserves the raw parity symbol. */
#define g1_timeslot_api_worker FUN_0102b810

extern int FUN_010362d0(const void *, void *, int32_t, int32_t);
extern int FUN_01021a38(const void *, uint8_t *);
extern int FUN_0102a122(uint8_t, void *);
extern int FUN_0102a0e6(uint8_t);
extern void FUN_01039722(const void *, ...);

#ifdef G1_COHESIVE_BUILD
#include <mpsl_timeslot.h>
struct k_msgq;
extern struct k_msgq g1_timeslot_api_msgq;
extern mpsl_timeslot_request_t g1_timeslot_request_earliest;
extern mpsl_timeslot_request_t g1_timeslot_request_normal;
extern void *FUN_0102b944(uint8_t, uint32_t, uint32_t);
#define TIMESLOT_API_QUEUE ((const void *)&g1_timeslot_api_msgq) /*=0x210008e0*/
#define TIMESLOT_EARLIEST_REQUEST ((void *)&g1_timeslot_request_earliest) /*=0x210005d8*/
#define TIMESLOT_NORMAL_REQUEST ((volatile uint32_t *)&g1_timeslot_request_normal) /*=0x210005b8*/
#define TIMESLOT_SIGNAL_CALLBACK ((const void *)FUN_0102b944) /*=0x0102c145 runtime Thumb*/
#else
#define TIMESLOT_API_QUEUE ((const void *)0x210008e0)
#define TIMESLOT_EARLIEST_REQUEST ((void *)0x210005d8)
#define TIMESLOT_NORMAL_REQUEST ((volatile uint32_t *)0x210005b8)
#define TIMESLOT_SIGNAL_CALLBACK ((const void *)0x0102c145)
#endif

static inline __attribute__((always_inline)) void
timeslot_api_fatal(const void *message, int error)
{
  if (*(volatile int32_t *)G1N_21000580 > 0) {
    FUN_01039722(message, error);
  }
  __asm volatile(
      "eors r0, r0\n"
      "msr basepri, r0\n"
      "mov r0, #3\n"
      "svc #2\n"
      : : : "r0", "cc", "memory");
}

void g1_timeslot_api_worker(void)
{
  uint8_t api_call = 0;
  uint8_t session_id = 0xff;

  for (;;) {
    if (FUN_010362d0(TIMESLOT_API_QUEUE, &api_call, -1, -1) != 0) {
      continue;
    }

    int error = 0;
    switch (api_call) {
    case 0:
      error = FUN_01021a38(TIMESLOT_SIGNAL_CALLBACK, &session_id);
      if (error != 0) {
        timeslot_api_fatal((const void *)0x0103d1d9, error);
      }
      break;

    case 1:
      error = FUN_0102a122(session_id, TIMESLOT_EARLIEST_REQUEST);
      if (error != 0) {
        timeslot_api_fatal((const void *)0x0103d1f2, error);
      }
      break;

    case 2: {
      volatile uint32_t *normal_request = TIMESLOT_NORMAL_REQUEST;
      uint32_t timeout_steps = *(volatile uint32_t *)G1N_21004638;
      if (timeout_steps != 0) {
        normal_request[2] = 50000u + 5000u * timeout_steps;
      }
      error = FUN_0102a122(session_id, (void *)normal_request);
      if (error != 0) {
        if (*(volatile int32_t *)G1N_21000580 > 0) {
          FUN_01039722((const void *)0x0103d1f2, error);
        }
        /* The shipped MLA leaves the timeout-step count live in r2 at the
           fatal SVC boundary; preserve that observable register ABI. */
        __asm volatile(
            "mov r2, %0\n"
            "eors r0, r0\n"
            "msr basepri, r0\n"
            "mov r0, #3\n"
            "svc #2\n"
            : : "r"(timeout_steps) : "r0", "r2", "cc", "memory");
      }
      break;
    }

    case 3:
      error = FUN_0102a0e6(session_id);
      if (error != 0) {
        timeslot_api_fatal((const void *)0x0103d20d, error);
      }
      break;

    default:
      timeslot_api_fatal((const void *)0x0103d226, 0);
      break;
    }
  }
}
