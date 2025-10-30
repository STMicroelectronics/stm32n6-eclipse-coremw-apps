
## <b>Ux_Host_HID Application Description</b>

This application provides an example of Eclipse USBX stack usage .
It shows how to develop a USB Host Human Interface "HID" able to enumerate and communicate with a mouse or a keyboard.

The application is designed to behave as a USB HID Host, the code provides required requests to properly enumerate
HID devices, HID class APIs to decode HID reports received from a mouse or a keyboard and display data on UART HyperTerminal.

The application creates 3 threads:

  - app_ux_host_thread_entry: used to initialize USB OTG HAL HCD driver and start the Host.
  - hid_mouse_thread_entry: used to decode HID reports received  from a mouse.
  - hid_keyboard_thread_entry: used to decode HID reports received  from a keyboard.

#### <b>Expected success behavior</b>

When a HID device is plugged to NUCLEO-N657X0-Q board, a message will be displayed on the UART HyperTerminal showing
the Vendor ID and Product ID of the attached device.
After enumeration phase, a message will indicate that the device is ready for use.
The host must be able to properly decode HID reports sent by the corresponding device and display those information on the HyperTerminal.

The received HID reports are used by host to identify:

In case of a mouse:

   - (x,y) mouse position
   - Wheel position
   - Pressed mouse buttons

In case of a keyboard:

   - Pressed key

#### <b>Error behaviors</b>

Errors are detected (such as unsupported device, enumeration fail) and the corresponding message is displayed on the HyperTerminal.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and HID class specification.

#### <b>Known limitations</b>

None

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

Connectivity, USBX Host, FreeRTOS, USB, HID, Mouse, Keyboard, UART, USART,

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q boards Revision MB1940-N657XOQ-C01 and can be easily tailored to any other supported device and development board.

- NUCLEO-N657X0-Q Set-up
    - Plug the USB HID device into the STM32N657xx board through 'Type C  to A-Female' cable to the connector:
      - CN8 : to use USB High Speed OTG IP
    - Connect ST-Link cable to the PC USB port to display data on the HyperTerminal.

  - A virtual COM port will then appear in the HyperTerminal:
     - Hyperterminal configuration
       - Data Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - Flow control: None

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

 - Resort to CubeProgrammer to add a header to the generated binary Ux_Host_HID.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin Ux_Host_HID.bin -nk -of 0x80000000 -t fsbl -o Ux_Host_HID-trusted.bin -hv 2.3 -dump Ux_Host_HID-trusted.bin*
   - The resulting binary is Ux_Host_HID-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (Ux_Host_HID-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.

### <b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number
of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the external HSE clock as USB source clock.

**Warning** If using CubeProgrammer v2.21 version or more recent, add *-align* option in the command line.
