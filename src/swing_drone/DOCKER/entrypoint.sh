#!/bin/bash
set -e

source /opt/ros/humble/setup.bash

export DISPLAY=${DISPLAY}
export QT_X11_NO_MITSHM=1
export XDG_RUNTIME_DIR=/tmp/runtime-root

exec "$@"
