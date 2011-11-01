#!/bin/sh

# Copy the busybox binary and create the symlinks
cp -f $1/bin/busybox /bin
for prog in `cat $1/busybox.links` ; do
    ln -s /bin/busybox $prog && ls -l $prog
done
