/* readable reconstruction; identity: FUN_00071684 @ 0x00071684
 * public-name: z_fatal_error
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   arm_mpu_configure_partition_region       <= FUN_00050b8c @ 0x00050b8c
 *   fatal_log_and_reset                      <= FUN_00063b7c @ 0x00063b7c
 *   z_fatal_error                            <= FUN_00071684 @ 0x00071684
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   posix_stub_zero                          <= FUN_00086418 @ 0x00086418
 * address symbols (name @ address):
 *   rodata_88258                             @ 0x00088258
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_ef596                             @ 0x000ef596
 *   rodata_f7c9c                             @ 0x000f7c9c
 *   rodata_f7cc4                             @ 0x000f7cc4
 *   rodata_f7ce5                             @ 0x000f7ce5
 *   rodata_f7cfd                             @ 0x000f7cfd
 *   rodata_f7d1f                             @ 0x000f7d1f
 *   rodata_f7d3c                             @ 0x000f7d3c
 */
/* Reconstructed FUN_00071684 @ 0x71684 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void z_log_msg_runtime_create(uint32_t, uint32_t, const void *, uint32_t);
extern void arm_mpu_configure_partition_region(int);
extern void fatal_log_and_reset(uint32_t, int);
extern int k_current_get(void);
extern void assert_post_action(uint32_t, uint32_t);
extern void printk(uint32_t, ...);
extern char *posix_stub_zero(int);

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

void z_fatal_error(uint32_t event, int context)
{
  uint32_t previous_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();

  int handle = k_current_get();
  const char *event_name = (const char *)0x000f7c8e;
  if (event < 5) {
    event_name = *(const char **)(0x00098658 + event * sizeof(void *));
  }

  struct event_log_record event_log = {
    0x01000005, 0x000f7c9c, event, event_name, 0, 0x0301
  };
  z_log_msg_runtime_create(0x00088258, 0x2c40, &event_log, 0);

  if (context != 0 && (*(uint32_t *)(context + 0x1c) & 0x1ff) != 0) {
    struct log_argument queued = {2, (const void *)0x000f7cc4};
    z_log_msg_runtime_create(0x00088258, 0x1040, &queued, 0);
  }

  const char *handle_name = (const char *)0x000ef596;
  if (handle != 0) {
    char *candidate = posix_stub_zero(handle);
    if (candidate != 0 && candidate[0] != '\0') {
      handle_name = candidate;
    }
  }

  struct compact_log_record handle_log = {
    0x01000004, 0x000f7ce5, (uint32_t)handle, handle_name, 0x0301
  };
  z_log_msg_runtime_create(0x00088258, 0x2440, &handle_log, 0);

  fatal_log_and_reset(event, context);
  if (event == 4) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f7d1f, 0x000f7cfd, 0x93);
    printk(0x000f7d3c);
    assert_post_action(0x000f7cfd, 0x93);
  }

  __set_BASEPRI(previous_priority);
  __ISB();
  arm_mpu_configure_partition_region(handle);
}
