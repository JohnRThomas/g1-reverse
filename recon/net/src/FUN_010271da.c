/* sdc_free_list_advance @ 0x010271da; raw FUN_010271da.
 * Private controller identity; true executable extent 0x1c bytes.
 */
#include <stdint.h>
struct sdc_free_block { struct sdc_free_block *next; uint16_t size; };
void sdc_free_list_advance(struct sdc_free_block **link)
{
    *link = (*link)->next;
}
/* Raw identity/back-map: FUN_010271da@0x010271da. */
extern __typeof(sdc_free_list_advance) FUN_010271da
    __attribute__((alias("sdc_free_list_advance")));
