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

static inline __attribute__((always_inline)) void
timeslot_api_fatal(const void *message, int error)
{
  if (*(volatile int32_t *)0x21000580 > 0) {
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
    if (FUN_010362d0((const void *)0x210008e0, &api_call, -1, -1) != 0) {
      continue;
    }

    int error = 0;
    switch (api_call) {
    case 0:
      error = FUN_01021a38((const void *)0x0102c145, &session_id);
      if (error != 0) {
        timeslot_api_fatal((const void *)0x0103d1d9, error);
      }
      break;

    case 1:
      error = FUN_0102a122(session_id, (void *)0x210005d8);
      if (error != 0) {
        timeslot_api_fatal((const void *)0x0103d1f2, error);
      }
      break;

    case 2: {
      volatile uint32_t *normal_request = (volatile uint32_t *)0x210005b8;
      uint32_t timeout_steps = *(volatile uint32_t *)0x21004638;
      if (timeout_steps != 0) {
        normal_request[2] = 50000u + 5000u * timeout_steps;
      }
      error = FUN_0102a122(session_id, (void *)normal_request);
      if (error != 0) {
        if (*(volatile int32_t *)0x21000580 > 0) {
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
