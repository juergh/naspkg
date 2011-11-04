#!/bin/sh

# Copy the binary
cp $1/bin/sudo /bin/sudo

# Fix the permissions
chmod 4755 /bin/sudo

# Create the sudoers file
echo "admin ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers && chmod 0440 /etc/sudoers
