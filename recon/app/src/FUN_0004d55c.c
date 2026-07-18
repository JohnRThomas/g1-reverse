/* Reconstructed FUN_0004d55c @ 0x4d55c. */
/* mpsc_pbuf_alloc <= FUN_0004bc8c @ 0x0004bc8c.  k_timeout_t is two words. */
extern int mpsc_pbuf_alloc(void *object, unsigned int value,
                           unsigned int low, unsigned int high);

int FUN_0004d55c(unsigned int param_1)
{
    return mpsc_pbuf_alloc((void *)0x20003648, param_1, 0, 0);
}
