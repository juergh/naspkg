#!/bin/sh

# Source some important functions
. $1/../shared/functions

# Stop the DLNA server
stop minidlna

sleep 1
