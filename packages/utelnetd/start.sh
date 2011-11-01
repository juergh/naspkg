#!/bin/sh

# Source some important functions
. $1/../shared/functions

# Install the required shared packages
install busybox

# Create the device nodes
test -e /dev/ptyp0 || ( mknod /dev/ptyp0 c 2 0 && chmod 0666 /dev/ptyp0 )
test -e /dev/ttyp0 || ( mknod /dev/ttyp0 c 3 0 && chmod 0666 /dev/ttyp0 )

# Start the telnet daemon
start $1/bin/utelnetd -l /bin/sh -d

sleep 1
