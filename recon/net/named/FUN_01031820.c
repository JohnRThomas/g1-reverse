/* readable reconstruction; identity: FUN_01031820 @ 0x01031820
 * public-name: FUN_01031820
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c064                           @ 0x0103c064
 *   rodata_103e16a                           @ 0x0103e16a
 */
/* net-core controller fatal-reset path @ 0x01031820.
 *
 * Raw provenance: the executable body is 0x01031820..0x01031841.  The NOP at
 * 0x01031842 is alignment and 0x01031844/0x01031848 are literal-pool words,
 * not a fall-through continuation.  FUN_0102f4ec is the noreturn sys_reboot
 * implementation, so no code after that call belongs to this function.
 */
#include <stdint.h>

extern void FUN_0102e000(void);
extern void FUN_0102e284(uint32_t channel, uint32_t format,
                         const void *record, uint32_t flags);
extern __attribute__((noreturn)) void FUN_0102f4ec(uint32_t reboot_type);

#define controller_participants_initialize FUN_0102e000
#define publish_controller_diagnostic       FUN_0102e284
#define sys_reboot                          FUN_0102f4ec

typedef struct {
    uint32_t kind;
    uintptr_t message;
} controller_reset_diagnostic_t;

__attribute__((noreturn)) void FUN_01031820(void)
{
    controller_reset_diagnostic_t record;

    controller_participants_initialize();
    record.kind = 2;
    record.message = 0x0103e16au;
    publish_controller_diagnostic(0x0103c064u, 0x1040u, &record, 0);
    sys_reboot(0);
    __builtin_unreachable();
}
