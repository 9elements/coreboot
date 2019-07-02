coreboot README
===============

CTF - Missing IOMMU support

## Payload

LinuxBoot

## Target

UP²

## Problem

The Ubuntu bootet from eMMC cannot use the IOMMU as the DMAR table isn't generated
by coreboot.

## Task

Fix the mainboard code in `src/mainboard/up/squared` and make DMAR table appear
so that the Ubuntu can enable the IOMMU.
