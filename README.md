coreboot README
===============

CTF - Missing SMBIOS type 9

## Payload

LinuxBoot

## Target

UP²

## Problem

When booting into Ubuntu and running `dmidecode` the Type 9 (Physical Slot desciptor)
is missing.

## Task

Fix the mainboard code in `src/mainboard/up/squared` and add a slot description for
the PCI device 00:14.1 . Give it the name "M.2 slot".
