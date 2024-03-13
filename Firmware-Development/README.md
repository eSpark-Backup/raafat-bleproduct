# NRF52832 Flashing and Testing Guide.

## Table on Content
* [Setup NRF connect SDK on VS Code](#1---setup-nrf-connect-sdk-on-vs-code)
    - [VS Code Installation](#a-vs-code-installation)
    - [Add NRF Connect SDK extension in VS Code](#b-add-nrf-connect-sdk-extension-in-vs-code)
        - [Install Toolchain](#i-install-toolchain)
        - [Install SDK](#ii-install-sdk)
* [Install J-Link tools](#2---install-j-link-tools)
* [Setup power supply for the board](#3---setup-power-supply-for-the-board)
    - [Option # 1:  Power from V_BAT](#option--1-power-from-v_bat)
    - [Option # 2:  Power from 3v of debug connector/header](#option--2-power-from-3v-of-debug-connectorheader)
* [Connecting the Segger J-Link](#4---connecting-the-segger-j-link)
* [Starting the MCU](#5---starting-the-mcu)
* [Flashing the MCU using NRF Connect SDK from VS Code](#6---flashing-the-mcu-using-nrf-connect-sdk-from-vs-code)
* [Viewing the MCU Logs on RTT Viewer](#7---viewing-the-mcu-logs-on-rtt-viewer)


## 1 - Setup NRF connect SDK on VS Code
###  a) VS Code Installation

1. Download the [Visual Studio Code installer](https://go.microsoft.com/fwlink/?LinkID=534107) for Windows.
2. Once it is downloaded, run the installer (VSCodeUserSetup-{version}.exe). This will only take a minute.
3. By default, VS Code is installed under `C:\Users\{Username}\AppData\Local\Programs\Microsoft VS Code`.

Alternatively, you can also download a [Zip archive](/docs/?dv=winzip), extract it and run Code from there.

>**Tip:** Setup will add Visual Studio Code to your `%PATH%`, so from the console you can type 'code .' to open VS Code on that folder. You will need to restart your console after the installation for the change to the `%PATH%` environmental variable to take effect.

### b) Add NRF Connect SDK extension in VS Code.
Add both the nrf connect sdk extensions.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/ba714b70-cb98-41fe-82e6-e9f11e4526d9)" width = "1000" />

After installing the extensions nrf connect extension icon will appear on the left bar.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/895e1698-7df3-47f8-a39e-92a24d6211c3)" width = "1000" />

#### i) Install Toolchain
Click on Manage toolchain, then install the nRF Connect SDK Toolchain v2.5.2.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/202c63c9-fa2c-4185-82e2-833c8feec8c8)" width = "1000" />

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/5b42f6b9-dc77-4c67-b5cf-593d7d092e9f)" width = "1000" />

**Note**: Install v2.5.2 Toolchain, I have already installed that's why its not showing in the list.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/fe3a2bdd-26dc-48ed-9dc4-a4ea0a6bdcf0)" width = "1000" />

#### ii) Install SDK
Then do the same for Manage SDKs, install v2.5.1

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/6a77cee0-9248-4ed4-ba06-89ca9c80fcc2)" width = "1000" />

Note: Install v2.5.1 SDK, I have already install that's why its showing in directory c:/ncs/2.5.1.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/8b5d3bce-5645-494f-86d0-40ddc9721378)" width = "1000" />


## 2 - Install J-Link tools

Download J-Link tools from [here](https://www.segger.com/downloads/jlink/)
We used v7.94e. Download the latest from this link for the tools [here](https://www.segger.com/downloads/jlink/JLink_Windows_x86_64.exe)

Follow the installation guide and install.

<p align="center">
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/a6c424dc-f132-4e7d-9920-9985fdb77baf)" width = "700" height="300"/>
</p>


## 3 - Setup power supply for the board
### Option # 1:  Power from V_BAT
V_BAT pin are extended from the board using jumper wires.

<p align="center">
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/c9bfbe6b-30e7-4dd2-ab10-79c01f2f39c2)" width = "400" height = "500" />
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/7fc3e8bd-f98a-4baa-9786-08bbdee2afef" width="300" height = "500"/>
</p>


### Option # 2:  Power from 3v of debug connector/header
3v pin are extended from the debug connector to header. 
**IMPORTANT : apply 3v and ground to the debug connector to power the MCU if not using V_BAT**.

<p align="center">
<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/0facc2c2-c1f7-4eff-95fe-6ff5cb6e541c)" width = "400" height="500" />
<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/a910e14c-170e-42b1-af8d-ed5f86751df9" width = "400" height="300" />
</p>

## 4 - Connecting the Segger J-Link
The programming pins are extending to 6 pin Male-Header which should be connected with the J-Link Interface board female headers. Make sure to align the ground (Black wire) to the ground of J-Link Inteface board female header which are also labeled accordingly.
**Make sure the debugger 10pin ribbon connector is attached in correct orientation as shown in the image below.**

<p align="center">
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/e5f38810-0344-40a5-9013-3f100cb10a79" width = "400" height="300"/>
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/a910e14c-170e-42b1-af8d-ed5f86751df9" width = "400" height="300"/>
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/017206a2-0976-40f5-a319-1995f8709808" width = "400" height="300"/>
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/baf23ac9-a543-42fa-8db9-8224eca50084" width = "400" height="500"/>
</p>


## 5 - Starting the MCU
There are two ways that MCU starts depending upon the power configuration.
1 - If power using V_BAT, user has to push the on board button to start the MCU and press hold for 8 seconds to shut the MCU off.

<p align="center">
<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/542c817b-073c-4707-9627-6e919b3845fe)" width = "400" height="500"/>
</p>

2 - If power using 3V MCU starts directly on 3v power.

## 6 - Flashing the MCU using NRF Connect SDK from VS Code.

On the VS Code click on **Open an existing application** and open the application as shown.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/59a37219-e5f9-41ba-a804-b2389dbfe6f7)" width = "1000" height="300" />

This is how it should look like:
<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/d5c8bcd1-2956-4c11-835e-21006dec1c2a)" width = "1000" height="300"/>

**Main.c** file is located in the **src** directory.
Click on **Build** option located on the bottom tab called **NRF:CONNECT: ACTIONS:**

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/4f92c456-5112-479c-bff3-fd299d51af6f)" width = "1000" height="300"/>

then flash the hex output using **Flash** option below **Build** option.

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/cf3c3d6c-0d24-4670-8da2-efb6b09320cd)" width = "1000" height="300"/>

This is how it shows after successfully flashing

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/aa1e9b64-c2e0-4651-a625-6013dc0403f5)" width = "1000" height="300"/>

If MCU fails to start due to bad wiring or user forgot to press power button, flashing will fail

<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/09fb82cf-11ee-449a-ba5e-e7205ee114c2)" width = "1000" height="300"/>

If flashed successfully you can view the logs on the RTT Viewer which comes in the J-Link Tools.

## 7 - Viewing the MCU Logs on RTT Viewer

Open RTT Viewer from the Windows Start Bar, if not available be default search "RTT" and select the application.

<p align="center">
<img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/4a1a1e9b-82b3-45db-829c-6d19a0990e94)" width = "300" height="500"/>
</p>

Press Ok and it should connect.

<p align="center">
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/3859fa1e-6d27-4a3a-aeb0-35924a8f57bd)" width = "500" />
    <img src="https://github.com/eSpark-Consultants/raafat-BLEproduct/assets/143803999/8b0c3a27-dfab-473e-af15-0b4067762234)" width = "500" />
</p>


