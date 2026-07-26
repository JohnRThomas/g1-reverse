/* readable reconstruction; identity: FUN_000235a4 @ 0x000235a4
 * public-name: dequeue_file
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dequeue_file                             <= FUN_000235a4 @ 0x000235a4
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9e85d                             @ 0x0009e85d   [INLINED -- G6 literal batch]
 *   g_file_msg_pipe                          @ 0x200079a0
 */
/* Reconstructed FUN_000235a4 @ 0x235a4  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int, void*, int, int);
extern void memcpy(unsigned int, void*, int);
extern void log_message(unsigned int);

int dequeue_file(unsigned int param_1)
{
    /* The controller response is 201 bytes; retain three spare bytes. */
    unsigned char buf[204];
    int iVar1 = k_msgq_get(0x200079a0U, buf, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, buf, 0xc9);
    } else {
        log_message(0x9e85dU);
    }
    return iVar1;
}
