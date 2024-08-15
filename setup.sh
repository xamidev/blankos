#!/bin/bash

# A script to create a FAT32 loopback device, place a kernel onto it, and install GRUB.
# Inspired by JakeSteinburger's SpecOS setup script!

if [ "$EUID" -ne 0 ]; then
    echo "Please execute this script with root privileges."
    exit
fi

if [ -f "blankos-fat.img" ]; then
    echo "Deleting previous disk image..."
    rm blankos-fat.img
fi

if [ -d "/mnt/blankos" ]; then
    echo "Deleting previous mountpoint..."
    rm -rf /mnt/blankos
fi

echo "Creating new mountpoint..."
mkdir /mnt/blankos

echo "Creating an empty disk image..."
dd if=/dev/zero of=blankos-fat.img bs=512 count=131072

echo "Appending a parition to disk image..."
fdisk blankos-fat.img << EOF
n
p
1


a
w
EOF

echo "Creating loopback devices..."
losetup -fP blankos-fat.img

# Get first partition loopback
LOOP_DEVICE=$(losetup -l | grep blankos-fat.img | awk '{print $1}')
PARTITION="${LOOP_DEVICE}p1"

echo "Creating FAT32 partition..."
mkfs.vfat -F 32 $PARTITION

echo "Mounting partition..."
mount $PARTITION /mnt/blankos

echo "Installing GRUB on $LOOP_DEVICE"
grub-install --root-directory=/mnt/blankos --target=i386-pc --no-floppy --modules="normal part_msdos fat multiboot" $LOOP_DEVICE

echo "Copying kernel file and GRUB configuration file..."

cp kernel.elf /mnt/blankos/boot/
cp grub.cfg /mnt/blankos/boot/grub/

echo "Appending test files..."
mkdir /mnt/blankos/hello
echo "Hello, world from FAT32 text file." > /mnt/blankos/hello/testfile.txt

# cp program.elf /mnt/blankos/programs/
# In the future, when the OS can load programs and parse ELF

echo "Unmounting partition..."
umount /mnt/blankos

echo "Freeing loopback devices..."
losetup -d $LOOP_DEVICE

echo "Fixing disk image permissions..."
sudo chmod 666 blankos-fat.img

echo "The blankos-fat.img disk image is ready for use with QEMU or real hardware."
