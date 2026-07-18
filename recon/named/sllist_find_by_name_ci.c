/* readable reconstruction; identity: FUN_0008503c @ 0x0008503c
 * public-name: sllist_find_by_name_ci
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sllist_find_by_name_ci                   <= FUN_0008503c @ 0x0008503c
 */
/* CPUAPP cJSON_GetObjectItem @ 0x0008503c.
 * Raw/address back-map: FUN_0008503c / 0x0008503c.
 */
#include <stdint.h>

#define cJSON_GetObjectItem sllist_find_by_name_ci
extern void *cjson_get_object_item(const void *, const char *, int32_t);
/* cjson_get_object_item = FUN_0006447c @ 0x0006447c */

void *cJSON_GetObjectItem(const void *object, const char *name)
{
    /* Public cJSON wrapper: preserve object/name in r0/r1 and select the
     * ASCII case-insensitive lookup path with r2 = false. */
    return cjson_get_object_item(object, name, 0);
}
