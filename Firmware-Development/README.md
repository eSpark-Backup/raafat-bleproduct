# NRF52832 Flashing and Testing Guide.

## 1 - Setup NRF connect SDK on VS Code
###  a) VS Code Installation

1. Download the [Visual Studio Code installer](https://go.microsoft.com/fwlink/?LinkID=534107) for Windows.
2. Once it is downloaded, run the installer (VSCodeUserSetup-{version}.exe). This will only take a minute.
3. By default, VS Code is installed under `C:\Users\{Username}\AppData\Local\Programs\Microsoft VS Code`.

Alternatively, you can also download a [Zip archive](/docs/?dv=winzip), extract it and run Code from there.

>**Tip:** Setup will add Visual Studio Code to your `%PATH%`, so from the console you can type 'code .' to open VS Code on that folder. You will need to restart your console after the installation for the change to the `%PATH%` environmental variable to take effect.

### b) Add NRF Connect SDK extension in VS Code.
Add both the nrf connect sdk extensions.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/ba714b70-cb98-41fe-82e6-e9f11e4526d9)

After installing the extensions nrf connect extension icon will appear on the left bar.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/895e1698-7df3-47f8-a39e-92a24d6211c3)

#### i) Install Toolchain
Click on Manage toolchain, then install the nRF Connect SDK Toolchain v2.5.2.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/202c63c9-fa2c-4185-82e2-833c8feec8c8)

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/5b42f6b9-dc77-4c67-b5cf-593d7d092e9f)

**Note**: Install v2.5.2 Toolchain, I have already installed that's why its not showing in the list.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/fe3a2bdd-26dc-48ed-9dc4-a4ea0a6bdcf0)

#### ii) Install SDK
Then do the same for Manage SDKs, install v2.5.1

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/6a77cee0-9248-4ed4-ba06-89ca9c80fcc2)

Note: Install v2.5.1 SDK, I have already install that's why its showing in directory c:/ncs/2.5.1.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/8b5d3bce-5645-494f-86d0-40ddc9721378)


## 2 - Install J-Link tools

Download J-Link tools from [here](https://www.segger.com/downloads/jlink/)
We used v7.94e. Download the latest from this link for the tools [here](https://www.segger.com/downloads/jlink/JLink_Windows_x86_64.exe)

Follow the installation guide and install.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/a6c424dc-f132-4e7d-9920-9985fdb77baf)


## 3 - Setup power supply for the board
### Option # 1:  Power from V_BAT
V_BAT pin are extended from the board using jumper wires.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/c9bfbe6b-30e7-4dd2-ab10-79c01f2f39c2)

### Option # 2:  Power from 3v of debug connector/header
3v pin are extended from the debug connector to header. apply 3v and ground to the debug connector to power the MCU.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/0facc2c2-c1f7-4eff-95fe-6ff5cb6e541c)

## 4 - Starting the MCU
There are two ways that MCU starts depending upon the power configuration.
1 - If power using V_BAT, user has to push the on board button to start the MCU and press hold for 8 seconds to shut the MCU off.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/542c817b-073c-4707-9627-6e919b3845fe)

2 - If power using 3V MCU starts directly on 3v power.

## 5 - Flashing the MCU using NRF Connect SDK from VS Code.

On the VS Code click on **Open an existing application** and open the application as shown.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/59a37219-e5f9-41ba-a804-b2389dbfe6f7)

This is how it should look like:
![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/d5c8bcd1-2956-4c11-835e-21006dec1c2a)

**Main.c** file is located in the **src** directory.
Click on **Build** option located on the bottom tab called **NRF:CONNECT: ACTIONS:**

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/4f92c456-5112-479c-bff3-fd299d51af6f)

then flash the hex output using **Flash** option below **Build** option.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/cf3c3d6c-0d24-4670-8da2-efb6b09320cd)

This is how it shows after successfully flashing

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/aa1e9b64-c2e0-4651-a625-6013dc0403f5)

If MCU fails to start due to bad wiring or user forgot to press power button, flashing will fail

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/09fb82cf-11ee-449a-ba5e-e7205ee114c2)

If flashed successfully you can view the logs on the RTT Viewer which comes in the J-Link Tools.

## 6 Viewing the MCU Logs on RTT Viewer

Open RTT Viewer from the Windows Start Bar, if not available be default search "RTT" and select the application.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/4a1a1e9b-82b3-45db-829c-6d19a0990e94)

Press Ok and it should connect.

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/3859fa1e-6d27-4a3a-aeb0-35924a8f57bd)

![image](https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/8b0c3a27-dfab-473e-af15-0b4067762234)


