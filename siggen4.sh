#!/usr/bin/env bash
set -euo pipefail

# ─── ADJUST ME ──────────────────────────────────────────────────────────
ZEPHYR_TAG="v2.5.1"
BOARD="nrf5340dk_nrf5340_cpuapp"

IDA="/Applications/IDA Professional 9.0.app/Contents/MacOS"
FLAIR="/Applications/IDA_FLAIR_11"
IDB2PAT="${IDA}/python/idb2pat.py"
# ────────────────────────────────────────────────────────────────────────

# derived paths
WORKDIR="$HOME/zephyr_sigwork_${ZEPHYR_TAG}"
BUILD_DIR="${WORKDIR}/build"
VENV="${WORKDIR}/venv"

# Create and activate virtual environment
echo "→ setting up Python virtual environment"
python3 -m venv "${VENV}"
source "${VENV}/bin/activate"

# west in venv
echo "→ installing west in virtual environment"
pip install west

SDK_VERSION="0.16.5-1"
SDK_DIR="$HOME/zephyr-sdk-${SDK_VERSION}"

# SDK setup (keeping your existing code)
if [ ! -d "${SDK_DIR}" ]; then
    echo "→ Zephyr SDK not found, downloading and installing..."
    ARCH="aarch64"
    SDK_TAR_XZ="zephyr-sdk-${SDK_VERSION}_macos-${ARCH}.tar.xz"
    SDK_URL="https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${SDK_VERSION}/${SDK_TAR_XZ}"

    cd "$HOME"
    curl -L -O "${SDK_URL}"
    tar xvf "${SDK_TAR_XZ}"
    rm "${SDK_TAR_XZ}"

    cd "${SDK_DIR}"
    ./setup.sh
else
    echo "→ Found existing Zephyr SDK in ${SDK_DIR}"
fi

export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
export ZEPHYR_SDK_INSTALL_DIR="${SDK_DIR}"

echo "→ initialising Zephyr workspace with Nordic SDK (${ZEPHYR_TAG})"
cd "$HOME"
# Don't delete existing workspace - user may have spent time downloading it
# rm -rf "${WORKDIR}"

# Initialize with Nordic SDK which includes Zephyr only if it doesn't exist or is incomplete
if [ ! -d "${WORKDIR}/zephyr" ] || [ ! -d "${WORKDIR}/nrf" ]; then
    echo "→ Workspace incomplete or missing, reinitializing..."
    rm -rf "${WORKDIR}"
    west init -m https://github.com/nrfconnect/sdk-nrf \
              --mr v2.5.1 "${WORKDIR}"  # Use a compatible nRF Connect SDK version
    cd "${WORKDIR}"
    west update
    
    # Recreate virtual environment since workspace was recreated
    echo "→ Recreating Python virtual environment"
    python3 -m venv "${VENV}"
    source "${VENV}/bin/activate"
    pip install west
else
    echo "→ Using existing complete workspace at ${WORKDIR}"
    cd "${WORKDIR}"
fi

# Export both Zephyr and nRF paths
west zephyr-export

echo "→ installing Python dependencies"
pip install -r zephyr/scripts/requirements.txt

# Build multiple variants with different optimization levels
OPTIMIZATION_CONFIGS=(
#    "CONFIG_SPEED_OPTIMIZATIONS=y"
    "CONFIG_SIZE_OPTIMIZATIONS=y"
#    "CONFIG_DEBUG_OPTIMIZATIONS=y"
#    "CONFIG_NO_OPTIMIZATIONS=y"
)

for opt_config in "${OPTIMIZATION_CONFIGS[@]}"; do
    opt_name=$(echo $opt_config | cut -d'=' -f1 | cut -d'_' -f2- | tr '[:upper:]' '[:lower:]')
    BUILD_VARIANT="${BUILD_DIR}_${opt_name}"

    echo "→ Building with ${opt_config}"

    mkdir -p app

    # Enhanced CMakeLists.txt to include Nordic SDK components
    cat > app/CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.20.0)

# Find Zephyr and Nordic SDK
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(sigmaker)

# Add Nordic SDK include paths
zephyr_include_directories(${ZEPHYR_NRF_MODULE_DIR}/include)

# CRITICAL: Force inclusion of all functions by disabling garbage collection
# and section-based optimizations
zephyr_cc_option(-fno-function-sections)
zephyr_cc_option(-fno-data-sections)

# Disable linker garbage collection to keep all functions
zephyr_ld_options(-Wl,--no-gc-sections)

# Keep all symbols and sections
zephyr_ld_options(-Wl,--export-dynamic)
zephyr_ld_options(-Wl,--print-gc-sections)

target_sources(app PRIVATE src/main.c)
EOF

    # Enhanced prj.conf for Nordic SDK with settings to keep all code
    cat > app/prj.conf <<EOF
# Core settings
CONFIG_DEBUG=n
${opt_config}
CONFIG_COMPILER_SAVE_TEMPS=y
CONFIG_DEBUG_INFO=y


# CRITICAL: Prevent function elimination
# CONFIG_COMPILER_FFUNCTION_SECTIONS=n  # Undefined symbol
# CONFIG_COMPILER_FDATA_SECTIONS=n      # Undefined symbol
CONFIG_LINKER_ORPHAN_SECTION_PLACE=y
CONFIG_LINKER_ORPHAN_SECTION_WARN=n
CONFIG_FORCE_NO_ASSERT=n

# Force all modules to be included
# CONFIG_MODULES=y  # Undefined symbol

# Enable all subsystems to maximize function inclusion
# CONFIG_KERNEL_INIT_PRIORITY_OBJECTS=y  # Invalid value type
CONFIG_APPLICATION_INIT_PRIORITY=90

# Threading and kernel - enable everything
CONFIG_MULTITHREADING=y
CONFIG_THREAD_MONITOR=y
CONFIG_INIT_STACKS=y
CONFIG_THREAD_STACK_INFO=y
CONFIG_THREAD_NAME=y
CONFIG_HEAP_MEM_POOL_SIZE=8192
CONFIG_MAIN_STACK_SIZE=4096
CONFIG_IDLE_STACK_SIZE=2048
CONFIG_ISR_STACK_SIZE=2048
CONFIG_THREAD_MAX_NAME_LEN=32
# CONFIG_MAX_THREAD_BYTES=3  # Requires USERSPACE
CONFIG_SCHED_DUMB=n
CONFIG_SCHED_SCALABLE=y
CONFIG_SCHED_MULTIQ=n
CONFIG_WAITQ_SCALABLE=y

# Enable all kernel features
CONFIG_NUM_COOP_PRIORITIES=16
CONFIG_NUM_PREEMPT_PRIORITIES=15
CONFIG_TIMESLICING=y
CONFIG_POLL=y
CONFIG_EVENTS=y
CONFIG_PIPES=y
# CONFIG_DYNAMIC_THREAD=y

# Memory management - enable all
CONFIG_KERNEL_MEM_POOL=y
CONFIG_HEAP_MEM_POOL_SIZE=16384
CONFIG_SYS_HEAP_VALIDATE=y
CONFIG_SYS_HEAP_ALLOC_LOOPS=3

# Enable all synchronization primitives
# CONFIG_SEMAPHORES=y           # Undefined symbol
# CONFIG_MUTEXES=y              # Undefined symbol
# CONFIG_CONDITION_VARIABLES=y  # Undefined symbol
# CONFIG_SPINLOCK=y             # Undefined symbol

# Logging subsystem - comprehensive
CONFIG_LOG=y
CONFIG_LOG_BACKEND_UART=y
CONFIG_LOG_MODE_IMMEDIATE=y
CONFIG_LOG_FUNC_NAME_PREFIX_DBG=y
CONFIG_LOG_FUNC_NAME_PREFIX_INF=y
CONFIG_LOG_FUNC_NAME_PREFIX_WRN=y
CONFIG_LOG_FUNC_NAME_PREFIX_ERR=y

# Logging subsystem
CONFIG_LOG=y
CONFIG_LOG_BACKEND_UART=y
CONFIG_LOG_MODE_IMMEDIATE=y
CONFIG_LOG_FUNC_NAME_PREFIX_DBG=y
CONFIG_LOG_FUNC_NAME_PREFIX_INF=y
CONFIG_LOG_FUNC_NAME_PREFIX_WRN=y
CONFIG_LOG_FUNC_NAME_PREFIX_ERR=y

# Network buffers
CONFIG_NETWORKING=y
CONFIG_NET_BUF=y

# GPIO and peripherals
CONFIG_GPIO=y
CONFIG_SERIAL=y
CONFIG_UART_INTERRUPT_DRIVEN=y
CONFIG_I2C=y
CONFIG_SPI=y
CONFIG_PWM=y
CONFIG_ADC=y
CONFIG_WATCHDOG=y
CONFIG_COUNTER=y
CONFIG_ENTROPY_GENERATOR=y
CONFIG_CRYPTO=y

CONFIG_FLASH=y
CONFIG_FLASH_MAP=y
CONFIG_FCB=y
CONFIG_SETTINGS=y
CONFIG_SETTINGS_FCB=y
CONFIG_NVS=y

# Nordic ESB - disabled for nrf5340 app core compatibility
#CONFIG_ESB=y
# CONFIG_ESB_MAX_PAYLOAD_LENGTH=32
# CONFIG_ESB_TX_FIFO_SIZE=8
# CONFIG_ESB_RX_FIFO_SIZE=8

# MPSL - disabled for nrf5340 app core compatibility
# CONFIG_MPSL=y
# CONFIG_MPSL_WORK_STACK_SIZE=1024

CONFIG_ARM_MPU=y
CONFIG_ARM_TRUSTZONE_M=n
CONFIG_RUNTIME_NMI=y
CONFIG_PLATFORM_SPECIFIC_INIT=y

# Clock control
CONFIG_CLOCK_CONTROL=y
CONFIG_CLOCK_CONTROL_NRF=y

# IPC and RPMSG for dual-core
CONFIG_IPC_SERVICE=y
CONFIG_IPC_SERVICE_BACKEND_RPMSG=y
CONFIG_OPENAMP=y
CONFIG_OPENAMP_RSC_TABLE=y

# POSIX APIs
CONFIG_POSIX_API=y
CONFIG_POSIX_CLOCK=y
# CONFIG_POSIX_FS=y             # Requires FILE_SYSTEM
CONFIG_POSIX_MAX_FDS=32
CONFIG_POSIX_MQUEUE=y
CONFIG_PTHREAD_IPC=y

# Memory management
CONFIG_KERNEL_MEM_POOL=y

# Additional kernel features
CONFIG_POLL=y
CONFIG_EVENTS=y
CONFIG_SCHED_SCALABLE=y
CONFIG_WAITQ_SCALABLE=y

# ARM specific
CONFIG_ARM_MPU=y

# Bluetooth (minimal, just HCI)
CONFIG_BT=y
CONFIG_BT_HCI=y
CONFIG_BT_PERIPHERAL=n
CONFIG_BT_CENTRAL=n
CONFIG_BT_GATT_CLIENT=y
CONFIG_BT_SMP=y
CONFIG_BT_PERIPHERAL=y
CONFIG_BT_CENTRAL=y
CONFIG_BT_OBSERVER=y
CONFIG_BT_BROADCASTER=y


# JSON
CONFIG_JSON_LIBRARY=y

# Enable polling and events
CONFIG_POLL=y
CONFIG_EVENTS=y

# Enable timers and timeouts
CONFIG_TIMER=y
CONFIG_TIMEOUT_64BIT=y


# Enable memory pool and heap
CONFIG_HEAP_MEM_POOL_SIZE=16384
CONFIG_KERNEL_MEM_POOL=y

# Ring buffer
CONFIG_RING_BUFFER=y

# Base64
CONFIG_BASE64=y

# CRC
CONFIG_CRC=y

# Random
CONFIG_TEST_RANDOM_GENERATOR=y

# Minimal C library features
CONFIG_MINIMAL_LIBC=y
CONFIG_MINIMAL_LIBC_MALLOC=y
CONFIG_MINIMAL_LIBC_CALLOC=y
CONFIG_MINIMAL_LIBC_REALLOCARRAY=y


CONFIG_BUILD_OUTPUT_BIN=n
CONFIG_BUILD_OUTPUT_STRIPPED=n

CONFIG_MBOX=y
CONFIG_MBOX_NRFX_IPC=y
EOF

    # Enhanced main.c with auto-generated functions
    mkdir -p app/src
    
    # Copy the auto-generated functions header
#    cp /Users/freedomcoder/Projects/G1disasm/auto_functions.h app/src/
        mkdir -p app/boards
    cat > app/${BOARD}.overlay <<'EOF'
/*
 * Give the existing IPC peripheral the extra label "mbox_bt"
 * so the Bluetooth RPMsg driver can obtain a mailbox device.
 */
&ipc0 {
        status = "okay";
};

/* Second label that points to the same node */
mbox_bt: &ipc0 {};
EOF

    cat > app/src/main.c <<EOF
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/entropy.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/buf.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/posix/pthread.h>
#include <zephyr/sys/mpsc_pbuf.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/random/rand32.h>
#include <zephyr/sys/hash_function.h>
#include <zephyr/sys/ring_buffer.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/sys/mutex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

static struct k_heap test_heap;
static K_HEAP_DEFINE(sys_heap, 2048);
static struct k_mutex test_mutex;
static struct k_sem test_sem;
static struct k_msgq test_msgq;
static struct k_work test_work;
static struct k_work_delayable delayed_work;
static struct k_timer test_timer;
static struct k_poll_event poll_events[4];
static struct k_fifo test_fifo;
static struct k_lifo test_lifo;
static struct k_stack test_stack;
static struct k_mem_slab test_slab;
static struct k_condvar test_condvar;
static struct k_spinlock test_spinlock;
static struct ring_buf test_ring_buf;
static pthread_mutex_t posix_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t posix_cond = PTHREAD_COND_INITIALIZER;
static pthread_barrier_t posix_barrier;
static atomic_t test_atomic = ATOMIC_INIT(0);

#define MSGQ_SIZE 10
#define STACK_SIZE 512
#define SLAB_BLOCK_SIZE 64
#define SLAB_NUM_BLOCKS 8
#define RING_BUF_SIZE 256

static char msgq_buffer[MSGQ_SIZE * sizeof(uint32_t)];
static K_THREAD_STACK_DEFINE(test_stack_area, STACK_SIZE);
static char slab_buffer[SLAB_BLOCK_SIZE * SLAB_NUM_BLOCKS];
static uint8_t ring_buf_data[RING_BUF_SIZE];

// ESB payload - disabled due to dependency conflicts
// static struct esb_payload rx_payload;
// static struct esb_payload tx_payload = ESB_CREATE_PAYLOAD(0, 0x01, 0x02, 0x03, 0x04);

static void work_handler(struct k_work *work)
{
    LOG_INF("Work handler executed");
}

static void delayed_work_handler(struct k_work *work)
{
    LOG_INF("Delayed work handler executed");
}

static void timer_handler(struct k_timer *timer)
{
    LOG_INF("Timer handler executed");
}

// Use auto-generated comprehensive function table
// The auto_functions.h file contains 114,958 functions from all modules

// ESB event handler - disabled due to dependency conflicts
/*
static void esb_event_handler(struct esb_evt const *event)
{
    switch (event->evt_id) {
    case ESB_EVENT_TX_SUCCESS:
        LOG_DBG("TX SUCCESS");
        break;
    case ESB_EVENT_TX_FAILED:
        LOG_DBG("TX FAILED");
        break;
    case ESB_EVENT_RX_RECEIVED:
        LOG_DBG("RX RECEIVED");
        if (esb_read_rx_payload(&rx_payload) == 0) {
            LOG_DBG("Payload received, len: %d", rx_payload.length);
        }
        break;
    }
}
*/

int main(void)
{
    int ret;
    const struct device *gpio_dev;
    const struct device *entropy_dev;
    struct net_buf_simple simple_buf_struct;
    struct net_buf_simple *simple_buf = &simple_buf_struct;
    uint8_t random_data[16];
    uint8_t simple_buf_data[64];

    LOG_INF("G1 signature generation build - forcing all functions");

    // CRITICAL: Force inclusion of all auto-discovered functions
    //force_auto_discovered_functions();

    // Initialize ALL kernel objects to force their inclusion
    k_mutex_init(&test_mutex);
    k_sem_init(&test_sem, 0, 1);
    k_work_init(&test_work, work_handler);
    k_work_init_delayable(&delayed_work, delayed_work_handler);
    k_timer_init(&test_timer, timer_handler, NULL);
    k_msgq_init(&test_msgq, msgq_buffer, sizeof(uint32_t), MSGQ_SIZE);
    k_fifo_init(&test_fifo);
    k_lifo_init(&test_lifo);
    k_stack_init(&test_stack, test_stack_area, STACK_SIZE);
    k_mem_slab_init(&test_slab, slab_buffer, SLAB_BLOCK_SIZE, SLAB_NUM_BLOCKS);
    k_condvar_init(&test_condvar);
    // k_spin_lock_init(&test_spinlock); // Function doesn't exist in this version
    ring_buf_init(&test_ring_buf, RING_BUF_SIZE, ring_buf_data);

    // Test heap operations
    void *mem = k_heap_alloc(&sys_heap, 64, K_NO_WAIT);
    if (mem) {
        k_heap_free(&sys_heap, mem);
    }

    // GPIO operations
    gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
    if (device_is_ready(gpio_dev)) {
        gpio_pin_configure(gpio_dev, 0, GPIO_OUTPUT);
        gpio_pin_set(gpio_dev, 0, 1);
    }

    // Entropy operations
    entropy_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_entropy));
    if (device_is_ready(entropy_dev)) {
        entropy_get_entropy(entropy_dev, random_data, sizeof(random_data));
    }

    // Network buffer operations
    net_buf_simple_init(simple_buf, sizeof(simple_buf_data));
    simple_buf->data = simple_buf_data;
    simple_buf->size = sizeof(simple_buf_data);
    net_buf_simple_add(simple_buf, 10);
    net_buf_simple_reset(simple_buf);

    // ESB initialization - disabled due to dependency conflicts
    /*
    struct esb_config esb_cfg = ESB_DEFAULT_CONFIG;
    esb_cfg.event_handler = esb_event_handler;
    esb_cfg.bitrate = ESB_BITRATE_2MBPS;
    esb_cfg.mode = ESB_MODE_PTX;
    esb_cfg.tx_output_power = 0;

    ret = esb_init(&esb_cfg);
    if (ret == 0) {
        LOG_INF("ESB initialized");
        esb_set_base_address_0(0xE7E7E7E7);
        esb_set_prefixes((uint8_t[]){0xE7}, 1);
    }
    */

    // MPSL initialization - disabled due to dependency conflicts
    // mpsl_lib_init();
    
    ret = 0; // Set ret to 0 since ESB init is disabled

    // POSIX operations
    pthread_mutex_lock(&posix_mutex);
    pthread_mutex_unlock(&posix_mutex);

    pthread_barrier_init(&posix_barrier, NULL, 2);
    pthread_barrier_destroy(&posix_barrier);

    // Logging operations
    LOG_INF("Test info message");
    LOG_DBG("Test debug message");
    LOG_ERR("Test error message");

    // Submit work
    k_work_submit(&test_work);

    // Thread operations
    k_sleep(K_MSEC(100));
    k_yield();

    // Try ESB transmission - disabled due to dependency conflicts
    /*
    if (ret == 0) {
        esb_write_payload(&tx_payload);
        esb_start_tx();
    }
    */

    return 0;
}
EOF

    # Build with specific optimization - use forced configs to bypass warnings
    west build -p=always -b nrf5340dk_nrf5340_cpuapp app --build-dir "${BUILD_VARIANT}"

    # Copy all zephyr* files for IDA analysis
    TARGET_DIR="/Users/freedomcoder/Projects/G1disasm/zephyr_${opt_name}"
    mkdir -p "${TARGET_DIR}"
    
    # Copy all zephyr* files from the build directory
    cp "${BUILD_VARIANT}/zephyr"/zephyr* "${TARGET_DIR}/" 2>/dev/null || true
    
    # Also keep the main ELF in the elfs directory for backward compatibility
    mkdir -p "/Users/freedomcoder/Projects/G1disasm/elfs"
    cp "${BUILD_VARIANT}/zephyr/zephyr.elf" "/Users/freedomcoder/Projects/G1disasm/elfs/zephyr_${opt_name}.elf"

    echo "→ Copied all zephyr* files to ${TARGET_DIR}/"
done


echo "✓ Multiple signature variants created and installed"
