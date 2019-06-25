coreboot README
===============

CTF - Missing onboard PCI device

## Payload

LinuxBoot

## Target

UP²

## Problem

The following devices appear in lspci:
```
0000:00:00.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series Host Bridge
0000:00:00.1: Intel Corporation 5a8c
0000:00:02.0: Intel Corporation 5a85
0000:00:0e.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series Audio Cluster
0000:00:0f.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series Trusted Execution Engine
0000:00:0f.1: Intel Corporation 5a9c
0000:00:0f.2: Intel Corporation 5a9e
0000:00:12.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series SATA AHCI Controller
0000:00:13.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series PCI Express Port A #1
0000:00:13.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series PCI Express Port A #2
0000:00:13.2: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series PCI Express Port A #3
0000:00:13.3: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series PCI Express Port A #4
0000:00:14.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series PCI Express Port B #1
0000:00:14.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series PCI Express Port B #2
0000:00:15.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series USB xHCI
0000:00:15.1: Intel Corporation 5aaa
0000:00:16.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #1
0000:00:16.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #2
0000:00:16.2: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #3
0000:00:16.3: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #4
0000:00:17.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #5
0000:00:17.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #6
0000:00:17.2: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #7
0000:00:17.3: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series I2C Controller #8
0000:00:18.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series HSUART Controller #1
0000:00:18.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series HSUART Controller #2
0000:00:19.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series SPI Controller #1
0000:00:19.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series SPI Controller #2
0000:00:19.2: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series SPI Controller #3
0000:00:1e.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series SDIO Controller
0000:00:1f.0: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series Low Pin Count Interface
0000:00:1f.1: Intel Corporation Celeron N3350/Pentium N4200/Atom E3900 Series SMBus Controller
0000:02:00.0: Realtek Semiconductor Co., Ltd. RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller
```

The eMMC device is missing.

## Task

Fix the mainboard code in `src/mainboard/up/squared` and make the PCI device appear in
GNU/Linux.
