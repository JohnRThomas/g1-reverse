/* net-core FUN_010108b8 @ 0x010108b8
 * Readable identity: sdc_ecb_crypt_block_ordered.
 * Raw callee backmaps: FUN_0100d3a0=reverse_copy_u8,
 * FUN_0100a7e8=sdc_ecb_run_blocking.
 */
#include <stdint.h>

extern void FUN_0100d3a0(void *destination, const void *source,
                         uint32_t length);
extern void sdc_ecb_run_blocking(void *ecb_job);

#define reverse_copy_u8 FUN_0100d3a0

void FUN_010108b8(const void *key, const void *input,
                  uint32_t reverse_output, uint32_t *output)
{
    struct {
        uint8_t key[16];
        uint8_t input[16];
        uint32_t output[4];
    } job;

    reverse_copy_u8(job.key, key, 16u);
    reverse_copy_u8(job.input, input, 16u);
    sdc_ecb_run_blocking(&job);

    if (reverse_output != 0u) {
        reverse_copy_u8(output, job.output, 16u);
    } else {
        output[0] = job.output[0];
        output[1] = job.output[1];
        output[2] = job.output[2];
        output[3] = job.output[3];
    }
}
