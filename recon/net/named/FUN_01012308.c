/* readable reconstruction; identity: FUN_01012308 @ 0x01012308
 * public-name: FUN_01012308
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core record submission entry FUN_01012308 @ 0x01012308. */
#include <stdint.h>

extern void FUN_01011d14(uint32_t value, const void *description);

struct record_description_12308 {
  uint8_t *payload;
  uint16_t flags;
  uint16_t reserved;
  uint32_t context;
  uint16_t type;
};

void FUN_01012308(uint8_t *record, uint32_t value, uint32_t unused, uint16_t flags)
{
  struct record_description_12308 description;

  (void)unused;
  description.payload = record + 0x28;
  description.flags = flags;
  description.context = *(uint32_t *)(record + 8);
  description.type = *(uint16_t *)(record + 4);
  FUN_01011d14(value, &description);
}
