# Flashing Binaries using nRF Connect Desktop Programmer Tool

This guide will walk you through the steps to flash binaries onto your device using the nRF Connect Desktop application. Note that this guide is demonstrated using the nRF52840 device, but the steps are applicable to other devices such as the nRF52832.

## Prerequisites

1. **nRF Connect Desktop**: Make sure you have nRF Connect Desktop installed on your computer. You can download it from [nRF Connect for Desktop](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-desktop).
2. **Programmer Tool**: The Programmer Tool must be installed in the nRF Connect Desktop.
3. **nRF Device**: Ensure your nRF device is connected to your computer via USB.
4. **J-Link Tools**: Install the SEGGER J-Link software, which is required for communication with the nRF device.

## Installing J-Link Tools

1. **Download J-Link Software**
   - Go to the SEGGER website and download the J-Link Software and Documentation Pack from [SEGGER J-Link Downloads](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack).
   
![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/42e23392-d3da-449a-8d0b-3d0fd86b26af)
   *Screenshot 1: SEGGER J-Link Download Page*

2. **Install J-Link Software**
   - Run the installer and follow the on-screen instructions to complete the installation.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/9262463b-cbf4-4f4f-9568-542cb84a512d)
   *Screenshot 2: J-Link Installation Wizard*

3. **Verify Installation**
   - Open a command prompt or terminal and type `JLink Commander`. You should see the J-Link Commander interface, indicating that the installation was successful.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/649e591a-711c-4010-9700-de7d2be5c004)
   *Screenshot 3: J-Link Commander Interface*

## Steps to Flash Binaries

### 1. Open nRF Connect Desktop
   Launch the nRF Connect Desktop application on your computer.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/d31fd4b8-2cf6-4c33-970e-55da20afbdb2)
   *Screenshot 4: nRF Connect Desktop Home Screen*

### 2. Open the Programmer Tool
   Select and open the Programmer Tool from the list of available applications.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/99880cdb-efda-43f6-ab8e-e869ff01a173)
   *Screenshot 5: Programmer Tool Selection*

### 3. Connect Your Device
   Ensure your nRF device is connected via USB. The device should appear in the Programmer Tool. Select your device from the list.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/2e43c5a8-cd6b-4a2c-900b-413078910d28)
   *Screenshot 6: Device Connection Screen*

### 4. Load the Binary File
   Click on the "Add file" button and select the binary file you want to flash onto your device. Note that your file path may be different.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/7b379267-69c1-4ed6-8492-7951116a99d3)
   *Screenshot 7: Load Binary File Screen*

### 5. Erase the Device (Optional but Recommended)
   Before flashing the new firmware, it's often recommended to erase the existing firmware. Click on the "Erase & write" button.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/d2f1a198-c427-462e-be2b-dcd65262904a)
   *Screenshot 8: Erase Device Button*

### 6. Flash the Binary
   After the device is erased, click on the "Erase and Write" button to flash the new binary file onto your device.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/8c3b5efa-5ce8-495d-9e34-549cc662680d)
   *Screenshot 9: Flash Binary Button*

### 7. Verify the Flash
   Once the flashing process is complete, verify that the new firmware is correctly installed on your device. You can do this by checking the log output in the Programmer Tool.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/35b67544-fd82-4774-8053-c70d74db1496)
   *Screenshot 10: Verification Log*

#### Using RTT Viewer for Verification
   - Open RTT Viewer from the J-Link software package.
   - Connect to your device by selecting the correct COM port and settings.
   - Verify that the device output matches the expected results.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/ad41b6a9-e950-4bb6-8a25-4e185c6b5dfb)
   *Screenshot 11: RTT Viewer Interface*

### 8. Disconnect the Device
   Safely disconnect your device from the USB port.

## Troubleshooting

- **Device Not Recognized**: Ensure the USB cable is properly connected and the device is powered on.
- **Flashing Failed**: Check the connection and try erasing the device before flashing again.
- **Verification Errors**: Ensure the binary file is compatible with your device.

## Additional Resources

- [nRF Connect for Desktop Documentation](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf_connect_for_desktop%2FUG_nRF_Connect_for_Desktop.html)
- [Nordic DevZone](https://devzone.nordicsemi.com/)
