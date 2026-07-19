#!/bin/sh
set -eu

ROOT=$(CDPATH= cd -- "$(dirname "$0")/../.." && pwd)
cd /tmp
export PYTHONSAFEPATH=1
exec "$ROOT/.venv/bin/python" "$ROOT/tools/symbol_browser/server.py" "$@"
