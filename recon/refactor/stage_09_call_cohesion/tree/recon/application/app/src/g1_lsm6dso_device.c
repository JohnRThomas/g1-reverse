/*
 * Firmware-shaped LSM6DSO device owner.
 *
 * Original-image backmap:
 *   init entry  0x00087b10: { .init_fn = NULL, .dev = 0x00087d58 }
 *   device      0x00087d58: name/config/api/state/data/pm
 *   config      0x0008b9d8: stock NCS 2.5.1 LSM6DSO I2C config
 *   sensor API  0x0008b9f8: attr_set/sample_fetch/channel_get
 *   state       0x200035da
 *   data        0x2000b2ac
 *
 * The shipped image has the stock v3.4.99-ncs1-1 LSM6DSO config, data and
 * sensor API, but deliberately records a NULL device initializer.  Include
 * the pinned stock driver implementation and alter only its device-definition
 * macro so Zephyr emits that observed NULL-init entry.  CONFIG_LSM6DSO stays
 * disabled, preventing a second, non-matching lsm6dso_init owner.
 */

#define DT_DRV_COMPAT st_lsm6dso

#include <zephyr/drivers/sensor.h>

/* sensor.h is include-guarded when the pinned driver includes it below. */
#undef SENSOR_DEVICE_DT_INST_DEFINE
#define SENSOR_DEVICE_DT_INST_DEFINE(inst, ignored_init_fn, pm_device,         \
				     data_ptr, cfg_ptr, level, prio, api_ptr, ...) \
	SENSOR_DEVICE_DT_DEFINE(DT_DRV_INST(inst), NULL, pm_device, data_ptr,    \
				cfg_ptr, level, prio, api_ptr, __VA_ARGS__)

/* Compiled from the pinned ZEPHYR_BASE; no copied or inferred driver body. */
#include "lsm6dso.c"

/*
 * Existing recovered callers retain the reversible name for original address
 * 0x00087d58.  A real definition overrides the globals.ld PROVIDE and makes
 * those callers resolve to this candidate device instead of a raw VA.
 */
extern const struct device rodata_87d58
	__attribute__((alias(STRINGIFY(DEVICE_DT_NAME_GET(DT_DRV_INST(0))))));
