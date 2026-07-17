/* readable reconstruction; identity: FUN_0007a9c8 @ 0x0007a9c8
 * public-name: LLF_RND_GetTrngSource
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   getTrngSource                            <= FUN_0007a720 @ 0x0007a720
 *   LLF_RND_GetTrngSource                    <= FUN_0007a9c8 @ 0x0007a9c8
 */
/* Reconstructed FUN_0007a9c8 @ 0x7a9c8  (parity: 300/300 trials, PROVEN) */

extern void getTrngSource(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void LLF_RND_GetTrngSource(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3u, unsigned int s0, unsigned int s1, unsigned int s2)
{
    getTrngSource(r0, r1, r2, s0, s1, s2, 0);
}
