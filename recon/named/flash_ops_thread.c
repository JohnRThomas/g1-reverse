/* readable reconstruction; identity: FUN_00023480 @ 0x00023480
 * public-name: flash_ops_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_store_cmd_msgq_used_count          <= FUN_00023ef8 @ 0x00023ef8
 *   quicknote_flash_msgq_read_field24        <= FUN_00024678 @ 0x00024678
 *   getQuickNoteBKPQueueCacheData            <= FUN_00024684 @ 0x00024684
 *   get_audio_msgq_used_count                <= FUN_0002f758 @ 0x0002f758
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 * address symbols (name @ address):
 *   rodata_9e7da                             @ 0x0009e7da   [INLINED -- G6 literal batch]
 *   rodata_9e8be                             @ 0x0009e8be   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Recovered flash_ops_thread <= FUN_00023480 @ 0x00023480.
 * Executable extent is exactly 0x54 bytes (0x23480..0x234d3).  The five
 * literal words at 0x234d4..0x234e7 belong to this body; FUN_000234e8 is the
 * next independent entry.  Durable reverse mapping:
 * recon/catalogs/function_names_app.json.
 */
#include <stdint.h>
#include "../headers/g1_log.h"

/* alias of FUN_0007dda4 */
/* FUN_00019c70 @ 0x19c70 */

/* Semantic aliases retain the exact raw linker identities. */
#define wait_for_flash_work z_impl_k_sem_take
extern int z_impl_k_sem_take(void *object, uint64_t timeout); /* @ 0x72908 */

#define audio_flash_queue_pending get_audio_msgq_used_count
extern unsigned int get_audio_msgq_used_count(void); /* @ 0x2f758 */
#define process_audio_flash_request audioStreamFileManagerHandler
extern void audioStreamFileManagerHandler(void); /* FUN_0002f94c @ 0x2f94c */

#define quicknote_flash_queue_pending quicknote_flash_msgq_read_field24
extern unsigned int quicknote_flash_msgq_read_field24(void); /* @ 0x24678 */
#define process_quicknote_flash_request getQuickNoteBKPQueueCacheData
extern void getQuickNoteBKPQueueCacheData(void); /* @ 0x24684; incoming registers are unused */

#define settings_flash_queue_pending flash_store_cmd_msgq_used_count
extern unsigned int flash_store_cmd_msgq_used_count(void); /* @ 0x23ef8 */
#define process_settings_flash_request SettingStoreHandler
extern void SettingStoreHandler(void); /* FUN_00023f04 @ 0x23f04 */

static volatile int32_t *const log_level_reg =
    (volatile int32_t *)(uintptr_t)0x2000230c;
static volatile uint32_t *const g_log_backend =
    (volatile uint32_t *)(uintptr_t)0x20007554;
static void *const g_flash_work_semaphore =
    (void *)(uintptr_t)0x200079e4; /* g_app_language_msgq raw export */

static inline void log_thread_started(void)
{
    if (*log_level_reg > 2) {
        if (*g_log_backend == 0)
            log_message(((unsigned long)"%s(): flash op thread startup ...\n"), ((unsigned long)"flash_ops_thread"));
        else
            debug_print(((unsigned long)"%s(): flash op thread startup ...\n"), ((unsigned long)"flash_ops_thread"));
    }
}

void flash_ops_thread(void)
{
    log_thread_started();

    for (;;) {
        wait_for_flash_work(g_flash_work_semaphore, UINT64_MAX);

        while (audio_flash_queue_pending() != 0)
            process_audio_flash_request();

        while (quicknote_flash_queue_pending() != 0)
            process_quicknote_flash_request();

        while (settings_flash_queue_pending() != 0)
            process_settings_flash_request();
    }
}
