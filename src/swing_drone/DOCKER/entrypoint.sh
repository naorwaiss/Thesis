#!/bin/bash
set -e

source /opt/ros/jazzy/setup.bash

export DISPLAY=${DISPLAY}
export QT_X11_NO_MITSHM=1
export XDG_RUNTIME_DIR=/tmp/runtime-root
export LIBGL_ALWAYS_SOFTWARE=1



exec "$@"
