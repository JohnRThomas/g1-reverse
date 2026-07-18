/* CPUNET intrusive-list head pop @ 0x01027894.
 * Raw back-map: FUN_01027894@0x01027894; true executable extent 0x28.
 * Private SDC implementation retained as readable C.
 */
#include <stdint.h>

struct sdc_link {
    struct sdc_link *next;
};

struct sdc_link *sdc_intrusive_list_pop_head(struct sdc_link **head)
{
    struct sdc_link *removed = *head;
    if (removed != 0)
        *head = removed->next;
    return removed;
}

/* Raw identity/back-map: FUN_01027894@0x01027894. */
extern __typeof(sdc_intrusive_list_pop_head) FUN_01027894
    __attribute__((alias("sdc_intrusive_list_pop_head")));
