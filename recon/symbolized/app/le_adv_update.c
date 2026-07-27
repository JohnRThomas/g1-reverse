#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000811ce @ 0x000811ce
 * public-name: le_adv_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   bt_dev_get                               <= FUN_00054ce0 @ 0x00054ce0
 *   hci_set_ad                               <= FUN_00055534 @ 0x00055534
 *   le_adv_update                            <= FUN_000811ce @ 0x000811ce
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_000811ce @ 0x811ce. */
#include <stdint.h>
extern uint8_t strlen(int);
extern unsigned int bt_dev_get(void);
extern int hci_set_ad(int,void*,int);
extern void memset_bytes(void*,int,int);

struct advertising_request {
    uint8_t type;
    uint8_t context_tag;
    uint16_t reserved;
    uint32_t context;
    const void *records;
    uint32_t record_count;
    const void *metadata;
    uint32_t metadata_count;
};

static int contains_reserved_record(const void *records, uint32_t count)
{
    const uint8_t *entry = records;
    for (uint32_t i = 0; i != count; ++i, entry += 8) {
        if ((uint8_t)(entry[0] - 8) < 2)
            return 1;
    }
    return 0;
}

int le_adv_update(uintptr_t owner, const void *records, uint32_t record_count,
                 const void *metadata, uint32_t metadata_count,
                 uint8_t publish_metadata, uint8_t request_type)
{
    struct advertising_request request;
    memset_bytes(&request.records, 0, 16);

    int request_words = 1;
    if (request_type != 0) {
        request.context = (uint32_t)bt_dev_get();
        if (records != 0 && contains_reserved_record(records, record_count))
            return -22;
        if (metadata != 0 &&
            contains_reserved_record(metadata, metadata_count))
            return -22;

        request.context_tag = strlen((int)request.context);
        request.type = 9;
        if (request_type == 1) {
            request.metadata = &request.type;
            request.metadata_count = 1;
            request_words = 2;
        }
    }

    request.records = records;
    request.record_count = record_count;
    int result = hci_set_ad(0x2008, &request.records, request_words);
    if (result != 0)
        return result;

    if (publish_metadata != 0) {
        request_words = 1;
        if (request_type == 2) {
            request.metadata = &request.type;
            request.metadata_count = 1;
            request_words = 2;
        }
        request.records = metadata;
        request.record_count = metadata_count;
        result = hci_set_ad(0x2009, &request.records, request_words);
        if (result != 0)
            return result;
    }

    __atomic_fetch_or((uint32_t *)(owner + 0x10), 4, __ATOMIC_RELEASE);
    return 0;
}
