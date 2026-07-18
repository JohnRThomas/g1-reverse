/* sdc_intrusive_list_remove @ 0x010278e4; raw FUN_010278e4.
 * Private controller identity; true executable extent 0x90 bytes.
 */
#include <stdint.h>
#include <cmsis_gcc.h>
struct sdc_link { struct sdc_link *next; };
extern struct sdc_link *FUN_01027894(struct sdc_link **head);
extern struct sdc_link *FUN_010278bc(struct sdc_link *predecessor);
#define sdc_intrusive_list_pop_head FUN_01027894
#define sdc_intrusive_list_unlink_after FUN_010278bc

struct sdc_link *sdc_intrusive_list_remove(struct sdc_link **head,
                                            struct sdc_link *target)
{
    struct sdc_link *removed = 0;
    if (target == *head) {
        uint32_t key = __get_PRIMASK();
        __disable_irq();
        removed = sdc_intrusive_list_pop_head(head);
        if (key == 0u) {
            __enable_irq();
        }
        return removed;
    }

    struct sdc_link *predecessor = *head;
    if (predecessor != 0) {
        while (predecessor->next != 0) {
            if (target == predecessor->next) {
                uint32_t key = __get_PRIMASK();
                __disable_irq();
                removed = sdc_intrusive_list_unlink_after(predecessor);
                if (key == 0u) {
                    __enable_irq();
                }
                return removed;
            }
            predecessor = predecessor->next;
        }
    }
    return removed;
}
/* Raw identity/back-map: FUN_010278e4@0x010278e4. */
extern __typeof(sdc_intrusive_list_remove) FUN_010278e4
    __attribute__((alias("sdc_intrusive_list_remove")));
