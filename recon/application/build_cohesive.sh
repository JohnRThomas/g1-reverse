#!/usr/bin/env bash
# Reproducible clean entry point for the recovered dual-core integration probes.
set -euo pipefail

usage() {
  echo "usage: $0 <app|net> [build-dir] [west build arguments ...]" >&2
  exit 2
}

[[ $# -ge 1 ]] || usage
core=$1
shift

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(cd "${script_dir}/../.." && pwd)
ncs_root=${NCS_ROOT:-"${HOME}/ncs251"}

case "${core}" in
  app)
    board=nrf5340dk_nrf5340_cpuapp
    source_dir="${script_dir}/app"
    ;;
  net)
    board=nrf5340dk_nrf5340_cpunet
    source_dir="${script_dir}/net"
    ;;
  *)
    usage
    ;;
esac

if [[ $# -ge 1 && $1 != -* ]]; then
  build_dir=$1
  shift
else
  build_dir="/private/tmp/g1-cohesive-${core}-build"
fi

zephyr_base="${ncs_root}/zephyr"
venv_site=$(find "${repo_root}/.venv/lib" -maxdepth 2 -type d \
  -name site-packages -print -quit 2>/dev/null || true)
if [[ -z "${venv_site}" ]]; then
  echo "missing repository virtualenv site-packages under ${repo_root}/.venv" >&2
  exit 2
fi
for required in \
  "${zephyr_base}" \
  "${ncs_root}/nrf/scripts" \
  "${ncs_root}/zephyr/scripts/kconfig" \
  "${ncs_root}/bootloader/mcuboot/scripts"; do
  if [[ ! -d "${required}" ]]; then
    echo "missing pinned NCS path: ${required}" >&2
    exit 2
  fi
done

# PYTHONSAFEPATH is mandatory in this repository because struct.py at the root
# otherwise shadows Python's standard-library struct module.  Partition Manager
# and child-image configuration additionally import modules from all three NCS
# script directories below; omitting nrf/scripts breaks a clean multi-image
# configure even when an incremental build happens to work.
export PYTHONSAFEPATH=1
export PYTHONPATH="${venv_site}:${ncs_root}/bootloader/mcuboot/scripts:${ncs_root}/zephyr/scripts/kconfig:${ncs_root}/nrf/scripts${PYTHONPATH:+:${PYTHONPATH}}"
export ZEPHYR_BASE="${zephyr_base}"

west_command=${G1_WEST:-west}
cd /tmp
exec "${west_command}" build -p always -b "${board}" -d "${build_dir}" \
  "${source_dir}" "$@"
