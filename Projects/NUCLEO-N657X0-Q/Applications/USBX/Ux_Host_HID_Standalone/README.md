
## <b>Ux_Host_HID_Standalone Application Description</b>

This application provides an example of Eclipse USBX stack usage in standalone mode.
It shows how to develop bare metal USB Host Human Interface "HID" able to enumerate and communicate with a mouse or a keyboard.

The application’s main calls the MX_USBX_Init() function in order to initialize USBX and MX_USBPD_Init() function in order to initialize USBPD . 
USBX_Host_Process and USBPD_DPM_Run are both in the while loop.

As stated earlier, the present application runs in standalone mode without FreeRTOS, for this reason, the standalone variant of USBX is enabled by adding the following flag in ux_user.h:

 - #define UX_STANDALONE


The application is designed to behave as a USB HID Host, the code provides required requests to properly enumerate
HID devices, HID Class APIs to decode HID reports received from a mouse or a keyboard and display data on UART HyperTerminal.

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

#### <b>USBX usage hints</b>

### <b>Keywords</b>

Connectivity, USBX Host, Standalone, USB, HID, Mouse, Keyboard, UART, USART,

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

 - Resort to CubeProgrammer to add a header to the generated binary Ux_Host_HID_Standalone.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin Ux_Host_HID_Standalone.bin -nk -of 0x80000000 -t fsbl -o Ux_Host_HID_Standalone-trusted.bin -hv 2.3 -dump Ux_Host_HID_Standalone-trusted.bin*
   - The resulting binary is Ux_Host_HID_Standalone-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (Ux_Host_HID_Standalone-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.

### <b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number
of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the external HSE clock as USB source clock.

**Warning** If using CubeProgrammer v2.21 version or more recent, add *-align* option in the command line.
