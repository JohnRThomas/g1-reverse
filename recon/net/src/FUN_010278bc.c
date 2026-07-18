/* CPUNET intrusive-list unlink-after helper @ 0x010278bc.
 * Raw back-map: FUN_010278bc@0x010278bc; true executable extent 0x28.
 * The argument is the predecessor's link field, so the same primitive also
 * serves as a pointer-to-link pop. Private SDC code remains readable C.
 */
#include <stdint.h>

struct sdc_link {
    struct sdc_link *next;
};

struct sdc_link *sdc_intrusive_list_unlink_after(struct sdc_link *predecessor)
{
    struct sdc_link *removed = predecessor->next;
    if (removed != 0)
        predecessor->next = removed->next;
    return removed;
}

/* Raw identity/back-map: FUN_010278bc@0x010278bc. */
extern __typeof(sdc_intrusive_list_unlink_after) FUN_010278bc
    __attribute__((alias("sdc_intrusive_list_unlink_after")));
