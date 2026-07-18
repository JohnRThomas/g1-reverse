/* Reconstructed cJSON get_object_item @ 0x0006447c.
 * Raw/address back-map: FUN_0006447c / 0x0006447c.
 */
#include <stdint.h>

struct cjson_item_raw {
    struct cjson_item_raw *next;
    struct cjson_item_raw *previous;
    struct cjson_item_raw *child;
    int32_t type;
    char *value_string;
    int32_t value_integer;
    double value_double;
    char *name;
};

#define cjson_string_compare FUN_0000eefe /*=0x0000eefe*/
extern int cjson_string_compare(const char *left, const char *right);

#define CJSON_CTYPE_TABLE \
    ((volatile const uint8_t *)0x000f8a6b) /*=0x000f8a6b*/

static __attribute__((always_inline)) inline uint8_t
cjson_ascii_tolower(uint8_t character)
{
    return ((CJSON_CTYPE_TABLE[character] & 3u) == 1u)
        ? (uint8_t)(character + 0x20u)
        : character;
}

static int cjson_case_insensitive_compare(const uint8_t *left,
                                          const uint8_t *right)
{
    if (left == 0 || right == 0) {
        return 1;
    }
    if (left == right) {
        return 0;
    }

    while (cjson_ascii_tolower(*left) == cjson_ascii_tolower(*right)) {
        if (*left == 0u) {
            return 0;
        }
        left++;
        right++;
    }

    return (int)cjson_ascii_tolower(*left) -
           (int)cjson_ascii_tolower(*right);
}

#define cjson_get_object_item FUN_0006447c
struct cjson_item_raw *cjson_get_object_item(
    const struct cjson_item_raw *object, const char *name,
    int32_t case_sensitive)
{
    struct cjson_item_raw *current;

    if (object == 0 || name == 0) {
        return 0;
    }

    current = object->child;
    if (case_sensitive != 0) {
        while (current != 0 && current->name != 0 &&
               cjson_string_compare(name, current->name) != 0) {
            current = current->next;
        }
    } else {
        while (current != 0 &&
               cjson_case_insensitive_compare(
                   (const uint8_t *)name,
                   (const uint8_t *)current->name) != 0) {
            current = current->next;
        }
    }

    if (current == 0 || current->name == 0) {
        return 0;
    }
    return current;
}
