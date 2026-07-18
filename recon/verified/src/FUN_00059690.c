/* Reconstructed FUN_00059690 @ 0x59690. */
#include <stdint.h>

#define z_impl_k_queue_init FUN_000864e8
extern void z_impl_k_queue_init(void *queue);
extern void FUN_00086502(void *owner,void *item);
extern void FUN_0005a954(void);

void FUN_00059690(void)
{
  void *const owner = (void *)0x20003a28;
  uintptr_t item = 0x2000add4;

  z_impl_k_queue_init(owner);
  for (unsigned index = 0; index < 10; ++index, item += 0x14)
    FUN_00086502(owner,(void *)item);

  FUN_0005a954();
}
