/* CPUAPP cJSON_GetObjectItem @ 0x0008503c.
 * Raw/address back-map: FUN_0008503c / 0x0008503c.
 */
#include <stdint.h>

#define cJSON_GetObjectItem FUN_0008503c
extern void *cjson_get_object_item(const void *, const char *, int32_t);
/* cjson_get_object_item = FUN_0006447c @ 0x0006447c */

void *cJSON_GetObjectItem(const void *object, const char *name)
{
    /* Public cJSON wrapper: preserve object/name in r0/r1 and select the
     * ASCII case-insensitive lookup path with r2 = false. */
    return cjson_get_object_item(object, name, 0);
}
