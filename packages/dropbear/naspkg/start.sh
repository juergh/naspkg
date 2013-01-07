#!/bin/sh

# Source some important functions
. $1/../shared/functions

# Install the required shared packages
install busybox
install sudo

# Create the device nodes
test -e /dev/ptmx || mknod /dev/ptmx c 5 2
test -d /dev/pts || mkdir /dev/pts
for pts in 0 1 2 3 4 5 6 ; do
    test -e /dev/pts/$pts || mknod /dev/pts/$pts c 136 $pts
done

# Generate the private key
test -d $1/etc/dropbear || mkdir -p $1/etc/dropbear
test -e $1/etc/dropbear/dropbear_rsa_host_key || \
    $1/bin/dropbearkey -t rsa -f $1/etc/dropbear/dropbear_rsa_host_key

# Create the admin home directory
test -d /home/admin || \
    ( mkdir /home/admin && chown -R admin:500 /home/admin )

# Create the symlinks
ln -s $1/bin/scp /bin/scp

# Run the SSH server
start $1/bin/dropbear -r $1/etc/dropbear/dropbear_rsa_host_key

sleep 1
