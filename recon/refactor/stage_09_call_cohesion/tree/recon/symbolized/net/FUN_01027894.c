#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027894 @ 0x01027894
 * public-name: FUN_01027894
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET intrusive-list head pop @ 0x01027894.
 * Raw back-map: FUN_01027894@0x01027894; true executable extent 0x28.
 * Private SDC implementation retained as readable C.
 */
#include <stdint.h>

struct sdc_link {
    struct sdc_link *next;
};

struct sdc_link *FUN_01027894(struct sdc_link **head)
{
    struct sdc_link *removed = *head;
    if (removed != 0)
        *head = removed->next;
    return removed;
}

/* Raw identity/back-map: FUN_01027894@0x01027894. */
