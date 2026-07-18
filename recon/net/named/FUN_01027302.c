/* readable reconstruction; identity: FUN_01027302 @ 0x01027302
 * public-name: FUN_01027302
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private ordered-block split/remove @ 0x01027302.
 * Raw back-map: FUN_01027302@0x01027302; extent 0xc4. */
#include <stdint.h>

extern void sdc_assertion_fail(unsigned module, unsigned line) __attribute__((noreturn));
extern void FUN_01027196(void *block, uint16_t size);
extern void FUN_010271b8(void *block, void *link);
extern void FUN_010271da(void *link);
extern int FUN_0102722c(void *block, uint16_t split);

void *FUN_01027302(void **head, unsigned split)
{
    void **link;
    uint8_t *block;
    if (split <= 7u || split > 0xfffeu)
        sdc_assertion_fail(0x15, 0x1d2);
    if (*head == 0)
        return 0;
    link = head;
    while (*(uint16_t *)((uint8_t *)*link + 4) != split &&
           *(void **)*link != 0)
        link = (void **)*link;
    block = (uint8_t *)*link;
    if (*(uint16_t *)(block + 4) == split) {
        FUN_010271da(link);
        return block;
    }
    if (FUN_0102722c(block, (uint16_t)split) == 0)
        return 0;
    {
        uint16_t remainder = *(uint16_t *)(block + 4) - (uint16_t)split;
        uint8_t *tail = block + split;
        FUN_01027196(tail, remainder);
        FUN_010271da(link);
        FUN_010271b8(tail, link);
    }
    return block;
}
