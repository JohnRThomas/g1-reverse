#!/usr/bin/env bash
set -euo pipefail

# ─── ADJUST ME ──────────────────────────────────────────────────────────
ZEPHYR_TAG="v3.7.0"
BOARD="nrf5340dk_nrf5340_cpuapp"

IDA="/Applications/IDA Professional 9.0.app/Contents/MacOS"    # idat64 lives here
FLAIR="/Applications/IDA_FLAIR_11"                             # contains bin/sigmake
IDB2PAT="${IDA}/python/idb2pat.py"                             # copy there in step 1
# ────────────────────────────────────────────────────────────────────────

# derived paths
WORKDIR="$HOME/zephyr_sigwork_${ZEPHYR_TAG}"
BUILD_DIR="${WORKDIR}/build"
ELF="${BUILD_DIR}/zephyr/zephyr.elf"
PAT="${WORKDIR}/zephyr_${ZEPHYR_TAG}.pat"
SIG="${WORKDIR}/zephyr_${ZEPHYR_TAG}.sig"
SIG_DST="${IDA}/sig/arm"
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

# ─── New Section: SDK Setup ───────────────────────────────────────────────
if [ ! -d "${SDK_DIR}" ]; then
    echo "→ Zephyr SDK not found, downloading and installing..."
    ARCH="aarch64"
    SDK_TAR_XZ="zephyr-sdk-${SDK_VERSION}_macos-${ARCH}.tar.xz"
    SDK_URL="https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${SDK_VERSION}/${SDK_TAR_XZ}"

    cd "$HOME"
    wget "${SDK_URL}"
    tar xvf "${SDK_TAR_XZ}"
    rm "${SDK_TAR_XZ}"

    cd "${SDK_DIR}"
    ./setup.sh
else
    echo "→ Found existing Zephyr SDK in ${SDK_DIR}"
fi

export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
export ZEPHYR_SDK_INSTALL_DIR="${SDK_DIR}"

echo "→ initialising Zephyr workspace (${ZEPHYR_TAG})"
#rm -rf "${WORKDIR}"

#west init -m https://github.com/zephyrproject-rtos/zephyr \
#          --mr "${ZEPHYR_TAG}"  "${WORKDIR}"
cd "${WORKDIR}"

#west update
west zephyr-export

echo "→ installing Python dependencies"
pip install -r zephyr/scripts/requirements.txt

echo "→ building dummy app"
mkdir -p app

cat > app/CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS \${ZEPHYR_BASE})
project(sigmaker)

target_sources(app PRIVATE src/main.c)
EOF

cat > app/prj.conf <<EOF
CONFIG_DEBUG=n
CONFIG_LTO=n
#CONFIG_NO_OPTIMIZATIONS=y
#CONFIG_DEBUG_OPTIMIZATIONS=y
CONFIG_COMPILER_SAVE_TEMPS=y
# Add these for better signatures:
CONFIG_DEBUG_INFO=y
CONFIG_DEBUG_THREAD_INFO=y
CONFIG_THREAD_MONITOR=y
CONFIG_INIT_STACKS=y
CONFIG_THREAD_STACK_INFO=y
CONFIG_THREAD_NAME=y
EOF


mkdir -p app/src
cat > app/src/main.c <<EOF
#include <zephyr/kernel.h>

int main(void)
{
    printk("Dummy app for signature generation\n");
    return 0;
}
EOF

west build -p=always -b "${BOARD}" app --build-dir "${BUILD_DIR}"
ELF="${BUILD_DIR}/zephyr/zephyr.elf"

# ─── run IDA (headless) to produce zephyr.pat ───────────────────────────
#echo "→ IDA headless pass (idb2pat)"
#export IDB2PAT_OUT="${PAT}"          # idb2pat.py will use this instead of ask_file()
#
#"${IDA}/idat" -A -S"${IDB2PAT}" "${ELF}"
#
## sanity
#[[ -f "${PAT}" ]] || { echo "✘ idb2pat failed to create ${PAT}"; exit 1; }
#
## ─── sigmake: .pat → .sig ───────────────────────────────────────────────
#echo "→ sigmake ${SIG}"
#"${FLAIR}/bin/sigmake" -o "${SIG}" "${PAT}"

#mkdir -p "${SIG_DST}"
#cp -v "${SIG}" "${SIG_DST}/"
#
#echo "✓ ${SIG##*/} installed in ${SIG_DST}"
#echo "   Open any nRF5340 firmware in IDA → Zephyr functions are recognised."