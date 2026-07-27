#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d2f8 @ 0x0007d2f8
 * public-name: device_info_set_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   device_info_set_mode                     <= FUN_0007d2f8 @ 0x0007d2f8
 */
/* Reconstructed FUN_0007d2f8 @ 0x7d2f8  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);

void device_info_set_mode(unsigned int param_1)
{
  if (param_1 <= 2) {
    void *p = get_device_info();
    int *ptr = *(int**)((char*)p + 0x1010);
    unsigned char b = *(unsigned char*)((char*)ptr + 2);
    int mismatch = (b != (unsigned char)param_1);
    if (!mismatch) {
      void *p2 = get_device_info();
      unsigned char b2 = *(unsigned char*)((char*)p2 + 0xd5);
      mismatch = (b2 != 7);
    }
    if (mismatch) {
      void *p3 = get_device_info();
      int *ptr3 = *(int**)((char*)p3 + 0x1010);
      *(unsigned char*)((char*)ptr3 + 2) = (unsigned char)param_1;
      void *p4 = get_device_info();
      int *ptr4 = *(int**)((char*)p4 + 0x1010);
      *(unsigned char*)((char*)ptr4 + 1) = 1;
    }
  }
}
