# USB Device Driver for Linux Kernel

This is a simple Linux kernel USB driver that detects and logs information about a 
USB device with Vendor ID `0xcb32` and Product ID `0x132f`.

## Features

- Registers a USB driver with the kernel
- Handles device detection (`probe`) and disconnection
- Logs USB interface and endpoint information to `dmesg`
- Demonstrates basic USB subsystem integration for embedded and systems programming

## USB Device Details

This driver targets a USB device with:

- **Vendor ID:** `0xcb32`
- **Product ID:** `0x132f`

## Files

- `usb_driver.c` – The main driver source file

## How to Build

1. Ensure you have kernel headers installed:
   ```bash
   sudo apt install linux-headers-$(uname -r)
