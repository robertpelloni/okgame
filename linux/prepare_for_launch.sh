#!/usr/bin/env bash
#------------------------------------------------------------------------------
# OKGame / bob's game - Linux Deployment Preparation Script
# Copies runtime shared object dependencies and strips non-system libraries.
#------------------------------------------------------------------------------
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}"

echo "Preparing bobsgame environment in ${SCRIPT_DIR}..."

if [[ -f "./bobsgame" ]]; then
    chmod 755 "./bobsgame"
    if command -v strip >/dev/null 2>&1; then
        strip "./bobsgame" || true
    fi
else
    echo "Notice: ./bobsgame binary not found yet; skipping strip."
fi

# Blacklist of system libraries that must NOT be vendored locally to prevent glibc/driver conflicts
BLACKLIST=(
    "VBoxOGLcrutil.so"
    "libGL.so*"
    "libc.so*"
    "libdl.so*"
    "libm.so*"
    "libpthread.so*"
    "libresolv.so*"
    "libasyncns*"
    "libdbus*"
    "libffi*"
    "libgcc_s*"
    "libglib*"
    "libnsl*"
    "libreadline*"
    "librt*"
    "libstdc++*"
    "libtinfo*"
    "libway*"
    "libwrap*"
    "libX*"
    "libxcb*"
    "libxkbcommon*"
    "libxshm*"
    "libasound.so.2"
    "libpulse*"
)

for pattern in "${BLACKLIST[@]}"; do
    # Remove matching files non-destructively ignoring if missing
    find . -maxdepth 1 -name "${pattern}" -exec rm -f {} + 2>/dev/null || true
done

echo "Environment preparation complete."
