#!/usr/bin/env bash
#------------------------------------------------------------------------------
# OKGame / bob's game - Linux Launch Script
#------------------------------------------------------------------------------
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN_PATH="${SCRIPT_DIR}/bobsgame"

# Set up library search path including local libraries and subdirectories
export LD_LIBRARY_PATH="${SCRIPT_DIR}:${SCRIPT_DIR}/libs:${LD_LIBRARY_PATH:-}"

if [[ ! -x "${BIN_PATH}" ]]; then
    if [[ -f "${BIN_PATH}" ]]; then
        chmod +x "${BIN_PATH}"
    else
        echo "Error: bobsgame binary not found at ${BIN_PATH}." >&2
        exit 1
    fi
fi

exec "${BIN_PATH}" "$@"
