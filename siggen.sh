#!/usr/bin/env bash
set -euo pipefail

# ─── Configuration ──────────────────────────────────────────────────────────
# Zephyr revision you want to match (tag, branch or full SHA)
ZEPHYR_TAG="v3.7.0"

# Board / CPU: application core of the nRF5340
BOARD="nrf5340dk_nrf5340_cpuapp"

# Where to put the temporary build
WORKDIR="$HOME/zephyr_sigwork_${ZEPHYR_TAG}"

# Absolute path to your IDA installation (edit if your IDA lives elsewhere)
IDA="/Applications/IDA Professional 9.0.app/Contents/MacOS"

# ─── Derived paths – normally you do not have to touch these ────────────────
ZEPHYR_DIR="${WORKDIR}/zephyr"
APP_DIR="${WORKDIR}/app"
BUILD_DIR="${WORKDIR}/build"
SIGMAKE="${IDA}/utils/sigmake/sigmake"
SIG_DST="${IDA}/sig/ARM"                # Zephyr for nRF5340 is Thumb-2 → ARM dir

# ─── Pre-flight checks ──────────────────────────────────────────────────────
for cmd in git cmake ninja python3; do
    command -v "$cmd" >/dev/null 2>&1 || {
        echo "✘ $cmd not found – install it with Homebrew (brew install $cmd)"; exit 1;}
done

[[ -x "${SIGMAKE}" ]] || { echo "✘ sigmake not found at ${SIGMAKE}"; exit 1; }

# The GNU Arm Embedded toolchain is easiest on macOS:
command -v arm-none-eabi-gcc >/dev/null 2>&1 || {
    echo "✘ arm-none-eabi-gcc not found – install with Homebrew:"
    echo "    brew tap ArmMbed/homebrew-formulae && brew install arm-none-eabi-gcc"
    exit 1; }

echo "✓ All prerequisites found"

# ─── Clone Zephyr and its modules (west) ─────────────────────────────────────
rm -rf "${WORKDIR}"; mkdir -p "${WORKDIR}"
cd "${WORKDIR}"

echo "→ Initialising Zephyr ${ZEPHYR_TAG}"
west init -l "${WORKDIR}" || true            # creates .west if needed
west update --fetch-opt=--depth=1 --tag "${ZEPHYR_TAG}"
west zephyr-export

# ─── Minimal dummy application just to make libzephyr.a ─────────────────────
echo "→ Preparing dummy application"
mkdir -p "${APP_DIR}"
cat > "${APP_DIR}/CMakeLists.txt" <<EOF
cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS \${ZEPHYR_BASE})
project(libmaker)
EOF
cat > "${APP_DIR}/prj.conf" <<EOF
CONFIG_BUILD_OUTPUT_LIB=y     # make libzephyr.a
CONFIG_DEBUG=y
CONFIG_LTO=n
CONFIG_NO_OPTIMIZATIONS=y
EOF

# ─── Build ──────────────────────────────────────────────────────────────────
echo "→ west build (${BOARD})"
west build -p=always -b "${BOARD}" "${APP_DIR}" \
     --build-dir "${BUILD_DIR}"

LIB_DIR="${BUILD_DIR}/zephyr"
[[ -f "${LIB_DIR}/libzephyr.a" ]] || { echo "✘ libzephyr.a not created"; exit 1; }

# ─── Produce .pat and .sig ──────────────────────────────────────────────────
echo "→ Generating FLIRT pattern"
PAT="${WORKDIR}/zephyr_${ZEPHYR_TAG}.pat"
SIG="${WORKDIR}/zephyr_${ZEPHYR_TAG}.sig"

${SIGMAKE} -nw -cxx -o "${PAT}" "${LIB_DIR}/libzephyr.a"

# (Optional) add more libs – just append them:
# ${SIGMAKE} -nw -cxx -a "${PAT}" "${BUILD_DIR}/lib/libc/minimal/libc.a"

echo "→ Compiling pattern into final signature"
${SIGMAKE} -o "${SIG}" "${PAT}"

# ─── Install the .sig ───────────────────────────────────────────────────────
mkdir -p "${SIG_DST}"
cp -v "${SIG}" "${SIG_DST}/"

echo "✓ zephyr_${ZEPHYR_TAG}.sig installed in ${SIG_DST}"
echo "   Open any stripped nRF5340 firmware in IDA; Zephyr functions"
echo "   will be recognised automatically."

exit 0