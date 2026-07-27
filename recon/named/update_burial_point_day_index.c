/* readable reconstruction; identity: FUN_0004a5b0 @ 0x0004a5b0
 * public-name: update_burial_point_day_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   update_burial_point_day_index            <= FUN_0004a5b0 @ 0x0004a5b0
 *   get_system_unix_time                     <= FUN_0007d216 @ 0x0007d216
 * address symbols (name @ address):
 *   rodata_f0310                             @ 0x000f0310   [INLINED -- G6 literal batch]
 *   rodata_f04c1                             @ 0x000f04c1   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0004a5b0 @ 0x4a5b0. */
#include <stdint.h>

extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void unix_timestamp_to_datetime(uint32_t,void *);
extern uint32_t get_system_unix_time(void);
extern uintptr_t get_device_info(void);

#define STATE() ((volatile uint8_t *)get_device_info())

static inline uint8_t state_index(volatile uint8_t *state)
{
  return state[0x10db];
}

int update_burial_point_day_index(uint32_t context,uint32_t unused_2,
                 uint32_t unused_3,uint32_t unused_4)
{
  uint16_t calendar[6] = {0};
  uint32_t now = get_system_unix_time();
  (void)unused_2; (void)unused_3; (void)unused_4;
  unix_timestamp_to_datetime(now,calendar);

  uint16_t year = calendar[0];
  uint16_t month = calendar[1];
  uint16_t day = calendar[2];
  if (year < 2025 && ((uint16_t)(month | day) < 2)) {
    if (*(volatile int *)0x2000230c > 1) {
      if (*(volatile int *)0x20007554 == 0)
        log_message(((unsigned long)"%s(): burial point date was not init!\n"),((unsigned long)"update_burial_point_day_index"),day,0,context);
      else
        debug_print(((unsigned long)"%s(): burial point date was not init!\n"),((unsigned long)"update_burial_point_day_index"),day,0,context);
    }
    return -1;
  }

  volatile uint8_t *state = STATE();
  if (state_index(state) > 6)
    STATE()[0x10db] = 0;

  state = STATE();
  volatile uint8_t *index_state = STATE();
  unsigned index = state_index(index_state);
  if (*(volatile int16_t *)(state + 0x10de + index * 12) == (int16_t)year) {
    state = STATE(); index_state = STATE(); index = state_index(index_state);
    if (state[0x10e0 + index * 12] == (uint8_t)month) {
      state = STATE(); index_state = STATE(); index = state_index(index_state);
      if (state[0x10e1 + index * 12] == (uint8_t)day)
        return 0;
    }
  }

  unsigned selected;
  for (selected = 0; selected < 7; ++selected) {
    state = STATE();
    if (state_index(state) == (uint8_t)selected)
      continue;
    state = STATE();
    unsigned offset = selected * 12;
    if (*(volatile int16_t *)(state + 0x10de + offset) != (int16_t)year)
      continue;
    state = STATE();
    if (state[0x10e0 + offset] != (uint8_t)month)
      continue;
    state = STATE();
    if (state[0x10e1 + offset] != (uint8_t)day)
      continue;
    STATE()[0x10db] = (uint8_t)selected;
    goto publish;
  }

  state = STATE();
  state[0x10db] = (uint8_t)(state[0x10db] + 1);
  state = STATE();
  if (state_index(state) > 6)
    STATE()[0x10db] = 0;

publish:
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  *(volatile int16_t *)(state + 0x10de + index * 12) = (int16_t)year;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  state[0x10e0 + index * 12] = (uint8_t)month;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  state[0x10e1 + index * 12] = (uint8_t)day;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  *(volatile uint16_t *)(state + 0x10e2 + index * 12) = 0;
  *(volatile uint16_t *)(state + 0x10e4 + index * 12) = 0;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  *(volatile uint16_t *)(state + 0x10e6 + index * 12) = 0;
  *(volatile uint16_t *)(state + 0x10e8 + index * 12) = 0;

  state = STATE(); index_state = STATE(); index = state_index(index_state);
  *(volatile int16_t *)(state + 0x1132 + index * 12) = (int16_t)year;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  state[0x1134 + index * 12] = (uint8_t)month;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  state[0x1135 + index * 12] = (uint8_t)day;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  *(volatile uint16_t *)(state + 0x1136 + index * 12) = 0;
  *(volatile uint16_t *)(state + 0x1138 + index * 12) = 0;
  state = STATE(); index_state = STATE(); index = state_index(index_state);
  *(volatile uint16_t *)(state + 0x113a + index * 12) = 0;
  *(volatile uint16_t *)(state + 0x113c + index * 12) = 0;
  return 0;
}
