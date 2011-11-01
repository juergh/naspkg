#!/bin/sh

# Source some important functions
. $1/../shared/functions

# Stop the SSH server
stop dropbear

# Remove the required shared packages
remove busybox
remove sudo

sleep 1
