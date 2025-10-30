
## <b>Ux_Device_CDC_ACM Application Description </b>

This application provides an example of Eclipse USBX stack usage on NUCLEO-N657X0-Q board,
it shows how to develop USB Device communication class "CDC_ACM"  based application.

The application is designed to emulate a USB-to-UART bridge following the Virtual COM Port (VCP) implementation, the code provides all required device descriptors framework
and associated to both classes descriptor report to build a composite compliant USB _CDC_ACM device.

The application has three threads:

  - app_ux_device_thread_entry: used to initialize USB_OTG HAL PCD driver and start the device.
  - usbx_cdc_acm_read_thread_entry: used to read the received data from Virtual COM Port.
  - usbx_cdc_acm_write_thread_entry: used to send the received data over UART.

During enumeration phase, three communication pipes "endpoints" are declared in the CDC class implementation :

 - 1 x Bulk IN endpoint for receiving data from STM32 device to PC host:
   When data are received over UART they are saved in the buffer "UserTxBufferFS". Periodically, in a
   usbx_cdc_acm_write_thread_entry the state of the buffer "UserTxBufferFS" is checked. If there are available data, they
   are transmitted in response to IN token otherwise it is NAKed.

 - 1 x Bulk OUT endpoint for transmitting data from PC host to STM32 device:
   When data are received through this endpoint they are saved in the buffer "UserRxBufferFS" then they are transmitted
   over UART using DMA mode and in meanwhile the OUT endpoint is NAKed.
   Once the transmission is over, the OUT endpoint is prepared to receive next packet in HAL_UART_RxCpltCallback().

 - 1 x Interrupt IN endpoint for setting and getting serial-port parameters:
   When control setup is received, the corresponding request is executed in USBD_CDC_ACM_ParameterChange.

In CDC_ACM application, two requests are implemented:

    - Set line: Set the bit rate, number of stop bits, parity, and number of data bits
    - Get line: Get the bit rate, number of stop bits, parity, and number of data bits
      The other requests (send break, control line state) are not implemented.

<b>Notes</b>

- Receiving data over UART is handled by interrupt while transmitting is handled by DMA allowing hence the application to receive
  data at the same time it is transmitting another data (full- duplex feature).
- The user has to check the list of the COM ports in Device Manager to find out the COM port number that have been assigned (by OS) to the VCP interface.

#### <b>Expected success behavior</b>

When plugged to PC host, the NUCLEO-N657X0-Q must be properly enumerated as an USB Serial device and an STlink COM port.
During the enumeration phase, device provides host with the requested descriptors (device descriptor, configuration descriptor, string descriptors).
Those descriptors are used by host driver to identify the device capabilities.
Once the NUCLEO-N657X0-Q USB device successfully completed the enumeration phase, open two hyperterminals (USB com port and UART com port(USB STLink VCP))
to send/receive data to/from host from/to device.

#### <b>Error behaviors</b>

Host PC shows that USB device does not operate as designed (CDC Device enumeration failed, PC and Device can not communicate over VCP ports).

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and CDC_ACM class specification.

#### <b>Known limitations</b>

None.

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

RTOS, FreeRTOS, USBX Device, USB_OTG, High Speed, CDC, VCP, USART, DMA.

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q boards Revision MB1940-N657XOQ-C01 and can be easily tailored to any other supported device and development board.
  - NUCLEO-N657X0-Q set-up:
    - Connect the NUCLEO-N657X0-Q board CN8 to the PC through "TYPE-C" to "Standard A" cable.
    - For VCP the configuration is dynamic for example it can be :
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - Stop Bit = 1
        - Parity = None
        - Flow control = None

  - The USART1 interface available on PE5 and PE6 of the microcontroller are connected to ST-LINK MCU. By default the USART1 communication between the target MCU and ST-LINK MCU is enabled.
  Its configuration is as follows:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

<b>Note</b>

 - When we configure the VCP baudrate under 9600 the USART1 baudrate shall be set to 9600.

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

 - Resort to CubeProgrammer to add a header to the generated binary Ux_Device_CDC_ACM.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin Ux_Device_CDC_ACM.bin -nk -of 0x80000000 -t fsbl -o Ux_Device_CDC_ACM-trusted.bin -hv 2.3 -dump Ux_Device_CDC_ACM-trusted.bin*
   - The resulting binary is Ux_Device_CDC_ACM-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (Ux_Device_CDC_ACM-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.

### <b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number
of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the external HSE clock as USB source clock.

**Warning** If using CubeProgrammer v2.21 version or more recent, add *-align* option in the command line.
