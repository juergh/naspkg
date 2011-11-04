#!/bin/sh

# Source some important functions
. $1/../shared/functions

# Stop the telnet daemon
stop utelnetd

# Remove the required shared packages
remove busybox

sleep 1
