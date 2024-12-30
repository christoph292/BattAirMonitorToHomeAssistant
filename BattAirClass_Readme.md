# BattAirClass.cpp Documentation

This file is part of the BattAirMonitorToHomeAssistant project. It defines the `BattAirClass` class, which is used to handle various battery parameters and responses.

## Includes
- `BattAirClass.h`: Header file for the `BattAirClass` class.

## Class Constructor
### `BattAirClass::BattAirClass(int macAdress)`
Initializes the class with a given MAC address and sets default values for the `Name` and `publicVariable` attributes.

### `BattAirClass::BattAirClass()`
Default constructor that initializes the `Name` attribute.

## Methods
### `void setMacAdress(int macAdress)`
Sets the MAC address of the device.

### `void setDataToEncrypt(uint8_t* data, size_t length)`
Encrypts data using the MAC address and parses the response based on the first byte of the data.

### `void getEncryptData()`
Activates the device by setting the corresponding pin to LOW.

### `void parseBatteryOEMParametersResponse(uint8_t* response, size_t length)`
Parses the response for battery OEM parameters and stores the values in the `BatteryOEMParametersResponse` struct.

### `void parseRealTimeParameter1Response(uint8_t* response, size_t length)`
Parses the response for real-time parameters (set 1) and stores the values in the `RealTimeParameter1Response` struct.

### `void parseRealTimeParameter0Response(uint8_t* response, size_t length)`
Parses the response for real-time parameters (set 0) and stores the values in the `RealTimeParameter0Response` struct.

### `void parseHardwareInfoClass(uint8_t* response, size_t length)`
Parses the response for hardware information and stores the values in the `HardwareInfoClass` struct.

### `void parseLoopRecordResponse(uint8_t* response, size_t length)`
Parses the response for loop records and stores the values in the `LoopRecordResponse` struct.

### `void parseAbnormalStatisticsResponse(uint8_t* response, size_t length)`
Parses the response for abnormal statistics and stores the values in the `AbnormalStatisticsResponse` struct.

### `void parseUserParameterResponse(uint8_t* response, size_t length)`
Parses the response for user parameters and stores the values in the `UserParameterResponse` struct.

### `void parseBleNameResponse(uint8_t* response, size_t length)`
Parses the response for BLE name and stores the values in the `BleNameResponse` struct.

### `int16_t convertToInt16(uint8_t* array, int startIndex, size_t length)`
Converts two bytes from the array starting at `startIndex` to an `int16_t` value.

For more details, you can view the [source file](https://github.com/christoph292/BattAirMonitorToHomeAssistant/blob/main/BattAirClass.cpp).
