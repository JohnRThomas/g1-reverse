/* readable reconstruction; identity: FUN_000840cc @ 0x000840cc
 * public-name: dev_channel_validate_and_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_channel_dispatch_range               <= FUN_00084068 @ 0x00084068
 *   dev_channel_dispatch_lookup              <= FUN_00084090 @ 0x00084090
 *   dev_channel_validate_and_set             <= FUN_000840cc @ 0x000840cc
 */
/* Reconstructed FUN_000840cc @ 0x840cc. */
#include <stdint.h>

extern int dev_channel_dispatch_range(void *owner, int value);
extern int dev_channel_dispatch_lookup(void);

struct value_limits {
    int minimum;
    int maximum;
    int initial;
    uint8_t reserved[13];
    uint8_t requires_precheck;
    uint8_t activation_flags;
};

struct value_operations {
    int (*activate)(void *owner);
    uint8_t reserved[16];
    int (*validate)(void *owner, int *value);
};

struct value_statistics {
    uint32_t reserved[5];
    uint32_t updates;
};

struct value_owner {
    uint32_t reserved;
    struct value_limits *limits;
    struct value_operations *operations;
    uint32_t reserved_0c;
    struct value_statistics *statistics;
};

int dev_channel_validate_and_set(struct value_owner *owner, int requested_value)
{
    struct value_limits *limits = owner->limits;
    struct value_operations *operations = owner->operations;
    int value = requested_value;
    int status;

    if (limits->requires_precheck != 0xff) {
        status = dev_channel_dispatch_lookup();
        if (status < 0) {
            return status;
        }
    }

    if (limits->initial != INT32_MIN) {
        status = dev_channel_dispatch_range(owner, limits->initial);
        if (status < 0) {
            return status;
        }
    }

    if (limits->minimum != INT32_MIN || limits->maximum != INT32_MAX) {
        if (operations->validate == 0) {
            return -0x58;
        }
        status = operations->validate(owner, &value);
        if (status < 0) {
            return status;
        }

        int bounded_value = value < limits->minimum ? limits->minimum :
                            value > limits->maximum ? limits->maximum : value;
        if (bounded_value != value) {
            status = dev_channel_dispatch_range(owner, bounded_value);
            if (status < 0) {
                return status;
            }
        }
    }

    if (requested_value == 0) {
        if ((limits->activation_flags & 3u) == 0) {
            return 0;
        }
        status = operations->activate(owner);
        if (status < 0) {
            return status;
        }
    }

    owner->statistics->updates++;
    return 0;
}
