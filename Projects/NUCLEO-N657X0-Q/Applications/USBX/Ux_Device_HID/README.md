
## <b>Ux_Device_HID Application Description</b>

This application provides an example of Eclipse USBX stack usage on NUCLEO-N657X0-Q board,
it shows how to develop USB Device Human Interface "HID" mouse based application.

The application is designed to emulate a USB HID mouse device, the code provides all required device descriptors framework
and associated class descriptor report to build a compliant USB HID mouse device.

The application has two threads:

  - app_ux_device_thread_entry: used to initialize USB_OTG HAL PCD driver and start the device.
  - usbx_hid_thread_entry: used to send HID reports to move automatically the PC host machine cursor.

To customize the HID application by sending the mouse position step by step every 10ms.
For each 10ms, the application calls the GetPointerData() API to update the mouse position (x, y) and send
the report buffer through the ux_device_class_hid_event_set() API.


#### <b>Expected success behavior</b>

When plugged to PC host, the NUCLEO-N657X0-Q must be properly enumerated as a USB HID mouse device.
During the enumeration phase, device provides host with the requested descriptors (Device, configuration, string).
Those descriptors are used by host driver to identify the device capabilities.
Once the NUCLEO-N657X0-Q USB device successfully completed the enumeration phase, the device sends an HID report after a user button press.
Each report sent should move the mouse cursor by one step on host side.

#### <b>Error behaviors</b>

Host PC shows that USB device does not operate as designed (Mouse enumeration failed, the mouse pointer doesn't move).

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" Specification and HID class Specification.

#### <b>Known limitations</b>

The remote wakeup feature is not yet implemented (used to bring the USB suspended bus back to the active condition).

#### <b>Notes</b>

The user has to check the list of the COM ports in Device Manager to find out the COM port number that have been assigned (by OS) to the VCP interface.

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".


### <b>Keywords</b>

RTOS, FreeRTOS, USBX Device, USBPD, USB_OTG, High Speed, HID, Mouse

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q boards Revision MB1940-N657XOQ-C01 and can be easily tailored to any other supported device and development board.

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of project.out.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open EWARM project
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary Ux_Device_HID.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin Ux_Device_HID.bin -nk -of 0x80000000 -t fsbl -o Ux_Device_HID-trusted.bin -hv 2.3 -dump Ux_Device_HID-trusted.bin*
   - The resulting binary is Ux_Device_HID-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (Ux_Device_HID-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.
 
### <b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number
of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the external HSE clock as USB source clock.

**Warning** If using CubeProgrammer v2.21 version or more recent, add *-align* option in the command line.
