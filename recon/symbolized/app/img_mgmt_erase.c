#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052180 @ 0x00052180
 * public-name: img_mgmt_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_add_cmd_err                          <= FUN_0005160c @ 0x0005160c
 *   img_mgmt_erase_slot                      <= FUN_000516ac @ 0x000516ac
 *   img_mgmt_reset_upload                    <= FUN_00051fe4 @ 0x00051fe4
 *   img_mgmt_read_info                       <= FUN_00052038 @ 0x00052038
 *   img_mgmt_erase                           <= FUN_00052180 @ 0x00052180
 *   cbor_map_decode_fields                   <= FUN_00080872 @ 0x00080872
 *   img_mgmt_slot_in_use                     <= FUN_000809f6 @ 0x000809f6
 * address symbols (name @ address):
 *   rodata_85f8d                             @ 0x00085f8d
 *   rodata_f272f                             @ 0x000f272f
 */
/* Reconstructed FUN_00052180 @ 0x52180. */
#include <stdint.h>

extern int cbor_map_decode_fields(int source, void *descriptor, unsigned int count,
                        uint32_t *auxiliary);
extern int img_mgmt_read_info(uint32_t handle, void *scratch,
                        uint32_t option, uint32_t context);
extern int img_mgmt_slot_in_use(uint32_t handle);
extern unsigned int img_mgmt_erase_slot(uint32_t handle);
extern void img_mgmt_reset_upload(void);
extern void smp_add_cmd_err(int destination, unsigned int command,
                         unsigned int status);

struct parse_result {
    uint32_t handle;
    uint32_t auxiliary;
};

struct request_descriptor {
    uint32_t token;
    uint32_t token_length;
    uint32_t callback;
    struct parse_result *result;
    uint8_t flags;
};

uint32_t img_mgmt_erase(const uint8_t *request)
{
    int destination = *(const int *)(request + 8);
    struct parse_result result = {1, 0};
    uint8_t parse_scratch[8];
    struct request_descriptor descriptor = {
        ((unsigned long)&rodata_f272f) /*=0xf272f*/, 4, ((unsigned long)&rodata_85f8d) /*=0x85f8d*/, &result, 0
    };

    int status = cbor_map_decode_fields(*(const int *)(request + 4) + 4,
                              &descriptor, 1, &result.auxiliary);
    if (status != 0)
        return 3;

    status = img_mgmt_read_info(result.handle, parse_scratch, 0, 0);
    unsigned int response;
    if (status == 0 && img_mgmt_slot_in_use(result.handle) != 0) {
        response = 9;
    } else {
        response = img_mgmt_erase_slot(result.handle);
        img_mgmt_reset_upload();
        if (response == 0)
            return 0;
        response &= 0xffffu;
    }

    smp_add_cmd_err(destination + 4, 1, response);
    return 0;
}
