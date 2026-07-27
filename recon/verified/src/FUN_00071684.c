/* Reconstructed FUN_00071684 @ 0x71684 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void FUN_0004d944(uint32_t, uint32_t, const void *, uint32_t);
extern void FUN_00050b8c(int);
extern void FUN_00063b7c(uint32_t, int);
extern int FUN_000748ac(void);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern char *FUN_00086418(int);

struct event_log_record {
  uint32_t metadata;
  uint32_t format;
  uint32_t value;
  const void *text;
  uint32_t flags;
  uint16_t argument_types;
};

struct compact_log_record {
  uint32_t metadata;
  uint32_t format;
  uint32_t value;
  const void *text;
  uint16_t argument_types;
};

struct log_argument {
  uint32_t type;
  const void *value;
};

void FUN_00071684(uint32_t event, int context)
{
  uint32_t previous_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();

  int handle = FUN_000748ac();
  const char *event_name = (const char *)0x000f7c8e;
  if (event < 5) {
    event_name = *(const char **)(0x00098658 + event * sizeof(void *));
  }

  struct event_log_record event_log = {
    0x01000005, 0x000f7c9c, event, event_name, 0, 0x0301
  };
  FUN_0004d944(0x00088258, 0x2c40, &event_log, 0);

  if (context != 0 && (*(uint32_t *)(context + 0x1c) & 0x1ff) != 0) {
    struct log_argument queued = {2, (const void *)0x000f7cc4};
    FUN_0004d944(0x00088258, 0x1040, &queued, 0);
  }

  const char *handle_name = (const char *)0x000ef596;
  if (handle != 0) {
    char *candidate = FUN_00086418(handle);
    if (candidate != 0 && candidate[0] != '\0') {
      handle_name = candidate;
    }
  }

  struct compact_log_record handle_log = {
    0x01000004, 0x000f7ce5, (uint32_t)handle, handle_name, 0x0301
  };
  FUN_0004d944(0x00088258, 0x2440, &handle_log, 0);

  FUN_00063b7c(event, context);
  if (event == 4) {
    FUN_0007e2fa(0x00099cbd, 0x000f7d1f, 0x000f7cfd, 0x93);
    FUN_0007e2fa(0x000f7d3c);
    FUN_0007e2ec(0x000f7cfd, 0x93);
  }

  __set_BASEPRI(previous_priority);
  __ISB();
  FUN_00050b8c(handle);
}
