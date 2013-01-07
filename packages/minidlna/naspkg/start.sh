#!/bin/sh

# Source some important functions
. $1/../shared/functions

# Start the DLNA server
start $1/bin/minidlna -f $1/etc/minidlna.conf

sleep 1
