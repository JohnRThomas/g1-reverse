/* net-core ipc_rpmsg_static_vrings_open @ 0x0102d708; raw: FUN_0102d708 */
/*
 * Zephyr IPC static-vrings backend open routine.
 *
 * Raw identity/back-map: FUN_0102d708 @ 0x0102d708
 * True executable extent: [0x0102d708, 0x0102d8a0) (408 bytes).
 * Upstream identity was recovered by a 0.931 normalized-opcode match against
 * NCS 2.5.1 ipc_rpmsg_static_vrings.c:open().  The descriptive C names below
 * are connected to the address-derived symbols by the reversible function-name
 * manifest and generated linker aliases.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum backend_state {
    BACKEND_READY = 0,
    BACKEND_BUSY = 1,
    BACKEND_INITIALIZED = 2,
};

struct mbox_driver_api_overlay {
    uint32_t reserved_00;
    int (*register_callback)(void *device, uint32_t channel,
                             uintptr_t callback, void *user_data);
    uint32_t reserved_08[2];
    int (*set_enabled)(void *device, uint32_t channel, uint32_t enabled);
};

struct mbox_device_overlay {
    uint32_t reserved_00[2];
    const struct mbox_driver_api_overlay *api;
};

struct backend_config_overlay {
    uint32_t role;                    /* +0x00 */
    uintptr_t shared_memory_address;  /* +0x04 */
    uint32_t shared_memory_size;      /* +0x08 */
    uint32_t mbox_tx[2];              /* +0x0c */
    struct mbox_device_overlay *mbox_rx_device; /* +0x14 */
    uint32_t mbox_rx_channel;         /* +0x18 */
    uint32_t work_queue_priority_type;/* +0x1c */
    uint32_t work_queue_priority;     /* +0x20 */
    uint32_t instance_id;             /* +0x24 */
    uint32_t rpmsg_buffer_size;       /* +0x28 */
};

struct ipc_static_vrings_overlay {
    uint8_t reserved_000[0x40];
    uintptr_t shared_region_virtual_address; /* backend +0x208 */
    uint8_t reserved_044[4];
    uint32_t shared_region_size;             /* backend +0x210 */
    uint8_t reserved_04c[0x3c];
    volatile uintptr_t status_register_address;    /* backend +0x250 */
    volatile uintptr_t tx_vring_address;           /* backend +0x254 */
    volatile uintptr_t rx_vring_address;           /* backend +0x258 */
    volatile uint32_t descriptor_count;             /* backend +0x25c */
    volatile uintptr_t shared_buffers_address;     /* backend +0x260 */
    volatile uint32_t required_shared_memory_size; /* backend +0x264 */
    void *shared_memory_io;                  /* backend +0x268 */
    uint8_t reserved_0a4[0x38];
    const struct backend_config_overlay *volatile notify_context; /* +0x2a4 */
    volatile uintptr_t notify_callback;                         /* +0x2a8 */
    uint8_t reserved_0e4[4];
};

struct backend_data_overlay {
    uint8_t rpmsg_instance_prefix[0xe0];
    uint8_t rpmsg_virtio_device[0xc8];
    uintptr_t endpoint_bound_callback; /* +0x1a8 */
    uintptr_t endpoint_rx_callback;    /* +0x1ac */
    uint8_t rpmsg_instance_suffix[0x18];
    struct ipc_static_vrings_overlay vrings; /* +0x1c8 */
    uint8_t mailbox_work[0x10];              /* +0x2b0 */
    uint8_t mailbox_work_queue[0xb8];        /* +0x2c0 */
    uint32_t role;                           /* +0x378 */
    volatile uint32_t state;                 /* +0x37c */
    int32_t tx_buffer_size;                  /* +0x380 */
};

struct backend_device_overlay {
    uint32_t reserved_00;
    const struct backend_config_overlay *config; /* +0x04 */
    uint8_t reserved_08[8];
    struct backend_data_overlay *data;            /* +0x10 */
};

/* Known NCS/Zephyr functions; raw identities are recorded beside each one. */
extern uint32_t ipc_static_vrings_shm_size(uint32_t descriptor_count,
                                           uint32_t buffer_size); /* FUN_0103a056 */
extern int ipc_static_vrings_init(struct ipc_static_vrings_overlay *vrings,
                                  uint32_t role); /* FUN_0102db30 */
extern void k_work_queue_init(void *queue); /* FUN_01036cb8 */
extern void k_work_queue_start(void *queue, void *stack, uint32_t stack_size,
                               int32_t priority, void *config); /* FUN_01036ce4 */
extern void k_work_init(void *work, uintptr_t handler); /* FUN_01036bec */
extern int ipc_rpmsg_init(void *instance, uint32_t role, uint32_t buffer_size,
                          void *shared_io, void *virtio_device,
                          uintptr_t shared_region_address,
                          uint32_t shared_region_size,
                          uintptr_t namespace_bind_callback); /* FUN_0102dac0 */
extern int rpmsg_virtio_get_buffer_size(void *rpmsg_virtio_device); /* FUN_010357ec */
extern void atomic_set(volatile uint32_t *target, uint32_t value); /* FUN_01039fb6 */

enum recovered_addresses {
    VIRTIO_NOTIFY_CALLBACK = 0x0103a79f,       /* virtio_notify_cb */
    MAILBOX_WORK_HANDLER = 0x0103a785,         /* mbox_callback_process */
    MAILBOX_CALLBACK = 0x0103a779,             /* mbox_callback */
    ENDPOINT_BOUND_CALLBACK = 0x0102e0bd,      /* bound_cb */
    ENDPOINT_RX_CALLBACK = 0x0103a92d,         /* ept_cb */
    NAMESPACE_BIND_CALLBACK = 0x0103a7e7,      /* ns_bind_cb */
    MAILBOX_STACK_ARRAY = 0x21007d80,
};

static uint32_t optimal_descriptor_count(uint32_t memory_size,
                                         uint32_t buffer_size)
{
    uint32_t available = memory_size - 4; /* VDEV_STATUS_SIZE */
    uint32_t descriptor_count = 1;

    while (available >
           ipc_static_vrings_shm_size(descriptor_count, buffer_size)) {
        ++descriptor_count;
    }

    if (--descriptor_count == 0) {
        return 0;
    }
    return 1u << (31u - (uint32_t)__builtin_clz(descriptor_count));
}

int ipc_rpmsg_static_vrings_open(struct backend_device_overlay *instance)
{
    const struct backend_config_overlay *config = instance->config;
    struct backend_data_overlay *data = instance->data;
    uint32_t expected_state = BACKEND_READY;
    int result;

    if (!__atomic_compare_exchange_n(&data->state, &expected_state,
                                     BACKEND_BUSY, false,
                                     __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)) {
        return -120; /* -EALREADY in the shipped Zephyr errno layout */
    }

    uint32_t descriptors = optimal_descriptor_count(
        config->shared_memory_size, config->rpmsg_buffer_size);
    if (descriptors == 0) {
        result = -12; /* -ENOMEM */
        goto error;
    }

    struct ipc_static_vrings_overlay *vrings = &data->vrings;
    vrings->shared_buffers_address =
        (config->shared_memory_address + 7u) & ~3u;
    vrings->required_shared_memory_size =
        ipc_static_vrings_shm_size(descriptors, config->rpmsg_buffer_size);

    uint32_t payload_size =
        (descriptors * config->rpmsg_buffer_size + 3u) & ~3u;
    uint32_t vring_size =
        ((descriptors * 18u + 9u) & ~3u) + descriptors * 8u;
    vrings->rx_vring_address =
        vrings->shared_buffers_address + payload_size * 2u;
    vrings->tx_vring_address = vrings->rx_vring_address + vring_size + 8u;
    vrings->descriptor_count = descriptors;
    vrings->status_register_address = config->shared_memory_address;
    vrings->notify_context = config;
    vrings->notify_callback = VIRTIO_NOTIFY_CALLBACK;

    result = ipc_static_vrings_init(vrings, config->role);
    if (result != 0) {
        goto error;
    }

    int32_t queue_priority = (int32_t)config->work_queue_priority;
    if (config->work_queue_priority_type == 1) {
        queue_priority -= 16;
    }
    k_work_queue_init(data->mailbox_work_queue);
    k_work_queue_start(
        data->mailbox_work_queue,
        (void *)(uintptr_t)(MAILBOX_STACK_ARRAY +
                            0x440u * config->instance_id),
        0x400, queue_priority, NULL);
    k_work_init(data->mailbox_work, MAILBOX_WORK_HANDLER);

    struct mbox_device_overlay *mailbox = config->mbox_rx_device;
    if (mailbox->api->register_callback == NULL) {
        result = -88; /* -ENOSYS */
        goto error;
    }
    result = mailbox->api->register_callback(
        mailbox, config->mbox_rx_channel, MAILBOX_CALLBACK, data);
    if (result != 0) {
        goto error;
    }

    if (mailbox->api->set_enabled == NULL) {
        result = -88; /* -ENOSYS */
        goto error;
    }
    result = mailbox->api->set_enabled(mailbox, config->mbox_rx_channel, 1);
    if (result != 0) {
        goto error;
    }

    data->endpoint_bound_callback = ENDPOINT_BOUND_CALLBACK;
    data->endpoint_rx_callback = ENDPOINT_RX_CALLBACK;
    result = ipc_rpmsg_init(
        data, data->role, config->rpmsg_buffer_size,
        vrings->shared_memory_io, vrings,
        vrings->shared_region_virtual_address,
        vrings->shared_region_size, NAMESPACE_BIND_CALLBACK);
    if (result != 0) {
        goto error;
    }

    data->tx_buffer_size = rpmsg_virtio_get_buffer_size(
        data->rpmsg_virtio_device);
    if (data->tx_buffer_size < 0) {
        result = -22; /* -EINVAL */
        goto error;
    }

    atomic_set(&data->state, BACKEND_INITIALIZED);
    return 0;

error:
    atomic_set(&data->state, BACKEND_READY);
    return result;
}
