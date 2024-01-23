# raafat-BLEproduct

Develop a BLE project that includes PCB design as well as the firmware. Components of the design include:

- Input of external 5 analog sensors through connector with 5V voltage output. The altogether current will be 150mA. The analog connector will be 7 pads and should be the larger the better.
    - VCC (5V)
    - Signal (0.2V - 2.8V) (INPUT1, INPUT2, INPUT3, INPUT4, INPUT5)
    - GND
- Gyro, Accelerometer and Temperature sensor, 10 DOF MEMS IMU, all in one IC
- Battery operated, EEMB LIR2450 Rechargeable Battery 3.7V Li-ion Coin (not finialized).
- Battery charging circuit with MicroUSB port.
- RGB LED
- Power Switch
- Header TX RX for debugging
- Power input detect pin
- Battery status detection and percentage detection
- Use smallest size components as a PCB size of 9mm X 9mm needs to be acheived.
- For MCU we can use NRF51822 (suggestions welcome)

## Unit Testing v1.1 (Power-Jack-Moved)
### Number of Assmebled Board received:  10 Boards 
### Number of Bare Boards received:  Nil
### Details of peripherals received: Nil

| S.No       | Status (working / faulty) | Remarks (Cause of fault) | Location (PK / Client) | Board Images (front / back / peripherals) |
| ----------- | ----------- |-------------| --- | --- |
| 1      | Working |  | PK | [Board Images](https://drive.google.com/drive/folders/1n3w0knsRiWI5llz53cg9I2Modn-9HDNM?usp=sharing) |
