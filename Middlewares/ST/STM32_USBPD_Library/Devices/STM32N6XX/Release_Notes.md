---
pagetitle: Release Notes for STM32 USB-C Power Delivery N6 Device Driver
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for
# <mark>STM32 USB-C Power Delivery N6 Device Driver</mark>
Copyright &copy; 2023 STMicroelectronics\

[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# Purpose

The USB-PD device driver provides a set of functions to manage the physical layer (i.e. low level of the type C state machine and low level of message transport). This includes :

- Type C state machine: SRC, SNK or DRP

- Physical layer : message handling SOP, SOP', SOP'', HARDRESET, ...

- Timer server to handle GOODCRC, PRL repetition timing

The USB-PD device driver is developed following the Universal Serial Bus Power Delivery Specification Revision 3.2, V1.1 (October, 2024) and Universal Serial Bus type-C Cable
and Connector Specification, Revision 2.0 (August, 2019).
:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section3" checked aria-hidden="true">
<label for="collapse-section3" aria-hidden="true">V1.1.0 / 23-Jan-2026</label>
<div>

## Main Changes

  Headline
  --------
  Add support of Debug Accessory Mode (DAM) in Sink mode
  Fix USBPD timer config value

## Known limitations

  Outstanding bugs list : None

  Requirements not met or planned in a forthcoming release : None

## Supported Devices and boards

  All STM32N6xx devices embedding USBPD IP

## Backward compatibility

  No compatibility break with previous version

## Dependencies

 This software release is compatible with USB-C Power Delivery Core Stack Library v5.4.0

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section2" aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">V1.0.1 / 25-Sep-2025</label>
<div>

## Main Changes

  Headline
  --------
  SLA0044 Legal terms updated to latest revision (Rev 6 / October 2025)

## Known limitations

  Outstanding bugs list : None

  Requirements not met or planned in a forthcoming release : None

## Supported Devices and boards

  All STM32N6xx devices embedding USBPD IP

## Backward compatibility

  No compatibility break with previous version

## Dependencies

 This software release is compatible with USB-C Power Delivery Core Stack Library v5.3.1

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">V1.0.0 / 11-April-2023</label>
<div>

## Main Changes

### Initial release

## Contents
**Fixed bugs list**

  Headline
  --------
  First official version for STM32N6xx device (source code available)

## Known limitations

  Outstanding bugs list : None

  Requirements not met or planned in a forthcoming release : None

## Development Toolchains and Compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V9.20.1
- RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.31
- STM32CubeIDE v1.9.0

## Supported Devices and boards

  All STM32N6xx devices embedding USBPD IP

## Backward compatibility

  No compatibility break with previous version

## Dependencies

 This software release is compatible with USB-C Power Delivery Core Stack Library v5.0.0

</div>
:::

:::
:::

<footer class="sticky">
For complete documentation on **STM32 32-bit Arm Cortex MCUs**,
visit: [http://www.st.com/STM32](http://www.st.com/STM32)

This release note uses up to date web standards and, for this reason, should not
be opened with Internet Explorer but preferably with popular browsers such as
Google Chrome, Mozilla Firefox, Opera or Microsoft Edge.
</footer>
