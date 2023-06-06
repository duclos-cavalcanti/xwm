#!/bin/bash
#
# rwm running script

print_error() {
    echo "ERROR: $*" >&2
    exit 1
}

if ! command -v Xephyr &>/dev/null; then
    print_error "xephyr has to be installed! "
    exit 1
fi

D=1
SIZE="1024x640"
XEPHYR_OPTIONS="-ac -br -noreset -screen ${SIZE}"

main() {
   # check for free DISPLAYS
    for ((i=0;;i++)); do
        if [[ ! -f "/tmp/.X${i}-lock" ]]; then
            D=$i
            break
        fi
    done

    Xephyr :$D -name xephyr_${D} ${XEPHYR_OPTIONS} >/dev/null 2>&1 &
    sleep 1s
    DISPLAY=:${D}.0 ./bin/rwm &
    sleep 1s

    echo "
    Display: $D,
    RWM PID: $(pgrep -n "rwm"),
    Xephyr PID: $(pgrep -f xephyr_${D})
    "
}

main "$@"
