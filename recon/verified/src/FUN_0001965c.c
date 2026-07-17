/* Reconstructed FUN_0001965c @ 0x1965c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern int FUN_00018d94(void*);
extern void FUN_00019c70(uint32_t, void*);
extern void FUN_00021460(uint32_t, void*, void*);
extern void FUN_0003384c(void*);
extern int FUN_00034bd4(void*);
extern void FUN_0004a3d0(uint32_t, void*);
extern int FUN_0007ca80(void*);
extern int FUN_0007d224(void);
extern void FUN_00086c78(void*, int, int);
extern void FUN_0008705a(void*, uint32_t, int);

struct ancs_record {
  uint32_t uid[2];
  uint32_t device_state;
  uint32_t reserved;
  char text[384];
  uint8_t work[32];
  uint32_t status;
};

struct command_record {
  uint32_t opcode;
  struct ancs_record notification;
};

_Static_assert(sizeof(struct ancs_record) == 0x1b4, "ANCS record layout");
_Static_assert(sizeof(struct command_record) == 0x1b8, "command record layout");

void FUN_0001965c(uint32_t channel)
{
  struct command_record local;
  int kind;
  uint8_t mode;

  local.opcode = 0x4b;
  FUN_00086c78(&local.notification, 0, sizeof(local.notification));
  if (FUN_00018d94(&local.notification) != 0 ||
      (local.notification.status <= 1 && local.notification.text[0] == 0)) {
    return;
  }

  local.notification.uid[0] = (uint32_t)FUN_0007d224();
  if (local.notification.uid[0] == 0) {
    local.notification.uid[0] = 1;
  }
  local.notification.device_state = *(volatile uint32_t*)0x20006aacUL;
  FUN_0004a3d0(0x0009ad7cUL, &local.notification);

  if (local.notification.status < 2) {
    kind = FUN_00034bd4(local.notification.text);
    if (kind != 2) {
      if (kind == 3) {
        mode = 4;
      } else {
        if (kind != 1) {
          return;
        }
        if (*(volatile uint32_t*)0x20007554UL == 0) {
          DEBUG_PRINT(0x0009ad86UL, local.notification.text);
        } else {
          FUN_00019c70(0x0009ad86UL, local.notification.text);
        }
        FUN_0003384c(&local.notification);
        return;
      }
    } else {
      mode = 2;
    }
  } else {
    mode = 2;
  }

  ((uint8_t*)&local.opcode)[1] = mode;
  if (*(volatile uint8_t*)0x20006ab2UL == 2) {
    FUN_0008705a(local.notification.text, 0x0009adaaUL, 0x20);
  }
  FUN_0007ca80(local.notification.work);
  FUN_00021460(channel, &local.opcode, &local.notification);
}
