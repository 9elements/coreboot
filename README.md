coreboot README
===============

CTF - Missing SMBIOS type 17

## Payload

LinuxBoot

## Target

UP²

## Problem

In Ubuntu when running `$ dmidecode` there's no "Type 17" entry (that holds the current
DRAM speed and density installed).

## Task

Fix the `src/mainboard/up/squared` code to add support for type 17 entry.
