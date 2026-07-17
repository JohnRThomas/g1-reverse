/* Reconstructed bt_hci_evt_get_flags @ 0x00080e14 from hci_core.c.
 * Raw backmap: FUN_00080e14@0x00080e14. */

#include <stdint.h>
uint32_t bt_hci_evt_get_flags(uint32_t event){if(event<=0x0fu){if(event>0x0du)return 1u;return event==5u?3u:2u;}if(event==0x13u)return 1u;if(event==0x1au)return 1u;return 2u;}
