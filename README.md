coreboot README
===============

CTF - mainboard has wrong manufacturer name in SMBIOS

## Problem

When booted into the Ubuntu on eMMC the SMBIOS shows a wrong mainboard
manufacturer in `$ dmidecode -t2`.

## Payload

LinuxBoot + systemboot

## Target

UP²

## Task

* Make changes to `src/mainboard/up/squared`
* Change the mainboard manufacturer to `AAEON`
