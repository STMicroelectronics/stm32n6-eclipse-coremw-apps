
## <b>Fx_uSD_File_Edit Application Description</b>

This application provides an example of Eclipse FileX stack usage on STM32N6570-DK, it shows how to develop a basic SD card file
operations application. The application is designed to handle SD card insertion/removal events, and depending on that state, it starts
and stops file operations from and into the SD card.

The application is developed using HAL, so managing LEDs, SD initialisation or any SD card insertion/removal mechanisms are implemented using HAL drivers without any reference to BSP.

A single thread is created:

  - fx_app_thread: used to initialize the SD driver and starting FileX's file operations.

A message queue is used to signal the SD card detection event to the fx_app_thread thread:

  - msg_queue: used to notify the fx_app_thread about the SD card insertion status.

The fx_app_thread starts by checking whether the SD card is initially inserted or not. If it is, it sends a message to the queue to ensure
that the first iteration starts properly. The wait for the message queue blocks until it receives a new message indicating whether the SD card has been inserted
or removed. Interrupt callback for SD detection is registered and it is used to send the event information to the message queue.

The fx_app_thread uses FileX services to open the SD media for file operations and attempts to create file STM32.TXT. If the file already exists,
it will be overwritten. Dummy content is then written into the file and it is closed. The file is opened once again in read mode and its content
is checked if matches what was previously written.

It is possible to unplug/plug or replace the SD card without any need to reset the STM32N6570-DK.
That is why MX_SDMMC1_SD_Init() should be public to initialize the newly plugged SD card.

#### <b>Expected success behavior</b>

- A file named STM32.TXT should be visible in the root directory of the SD card.
- A blinking green LED light marks the success of the file operations.

#### <b>Error behaviors</b>

- On failure, the red LED should start blinking.
- Error handler is called at the spot where the error occurred.

#### <b>Assumptions if any</b>

- The SD card should be plugged prior to run the application.

#### <b>Known limitations</b>

None.

#### <b>FreeRTOS usage hints</b>

 The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

The SDMMC2_IRQn interrupt must have lower priority (numerically higher) than the configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.

#### <b>FileX/LevelX usage hints</b>

- When calling the fx_media_format() API, it is highly recommended to understand all the parameters used by the API to correctly generate a valid filesystem.
- FileX is using data buffers, passed as arguments to fx_media_open(), fx_media_read() and fx_media_write() API it is recommended that these buffers are multiple of sector size and "32 bytes" aligned to avoid cache maintenance issues.

### <b>Keywords</b>

RTOS, FreeRTOS, FileX, File system, SDMMC, FAT32

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics STM32N6570-DK boards revision MB1939-N6570-C01 and can be easily tailored to any other supported device and development board.

  - **EWARM** : To monitor a variable in the live watch window, you must proceed as follow :
    - Start a debugging session.
    - Open the View > Images.
    - Double-click to deselect the second instance of project.out.

### <b>How to use it ?</b>


In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 1-3, BOOT0 switch position doesn't matter).
 - Open EWARM project
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

 Next, this program can be run in boot from flash mode. This is done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary Fx_uSD_File_Edit.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin Fx_uSD_File_Edit_FSBL.bin -nk -of 0x80000000 -t fsbl -o Fx_uSD_File_Edit-trusted.bin -hv 2.3 -dump Fx_uSD_File_Edit-trusted.bin*
   - The resulting binary is Fx_uSD_File_Edit-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (Fx_uSD_File_Edit-trusted.bin) in DK board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Press the reset button. The code then executes in boot from external Flash mode.


**Warning** If using CubeProgrammer v2.21 version or more recent, add *-align* option in the command line.
