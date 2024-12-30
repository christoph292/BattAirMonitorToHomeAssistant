#ifndef BattAirClass_H
#define BattAirClass_H

#include <Arduino.h>

class BattAirClass {
  public:
    BattAirClass(int macAdress);
    BattAirClass();
    void setDataToEncrypt(uint8_t* data, size_t length);
    void setMacAdress(int macAdress);
    void getEncryptData();
    int publicVariable; // Öffentliche Variable
    String Name;

    struct BatteryOEMParametersResponseState {
      int chargingRate;
      int dischargingRate;
      int selfDischargeEnable;
      int singleCoreDischargeVoltage;
      int singleCoreFullChargingVoltage;
      int singleCoreOverDischargeVoltage;
      int singleCoreStorageVoltage;
      int storageHighTemperatureLimit;
      int storageLowTemperatureLimit;
      int useHighTemperatureLimit;
      int useLowTemperatureLimit;
    } BatteryOEMParametersResponse; // Öffentliche Strukturvariable

    struct RealTimeParameter1ResponseState {
      int bleID;
      int chargingCurrent;
      int dischargingCurrent;
      int electricity;
      int32_t temperature;
    } RealTimeParameter1Response; // Öffentliche Strukturvariable

    struct RealTimeParameter0ResponseState {
      int bleID;
      int32_t cellVoltage1;
      int32_t cellVoltage2;
      int32_t cellVoltage3;
      int32_t cellVoltage4;
      int32_t cellVoltage5;
      int32_t cellVoltage6;
    } RealTimeParameter0Response; // Öffentliche Strukturvariable

    struct HardwareInfoClassState {
      int ambientTemperature;
      int appID;
      int balanceFunction;
      int batteryTemperature;
      int batteryType;
      int bleID;
      int cellVoltage;
      int cells;
      int mainHardwareVersion;
      int mainSoftwareVersion;
      int oEMCustomerNumber;
      int overDischargeProtection;
      int overchargeProtection;
      int productionDate;
      int subHardwareVersion;
      int subSoftwareVersion;
      int versionFlag;
      String batteryTypeString;
    } HardwareInfoClass; // Öffentliche Strukturvariable

    struct LoopRecordResponseState {
      int bleID;
      long cycleInformation;
      int cycleNumber;
      int recordNumber;
    } LoopRecordResponse; // Öffentliche Strukturvariable

    struct AbnormalStatisticsResponseState {
      int abnormalTemperatureRecord;
      int32_t batteryCycles;
      int bleID;
      int errorLogRecord;
      int outagesRecord;
      int overDischargeRecord;
      int overpressureRecord;
    } AbnormalStatisticsResponse; // Öffentliche Strukturvariable

    struct UserParameterResponseState {
      int bleID;
      int lEDEnable;
      int userFullChargeCutOffVoltage;
      int userRechargingCurrent;
      int userSelfDischargeTiming;
      int32_t userStorageVoltage;
    } UserParameterResponse; // Öffentliche Strukturvariable

    struct BleNameResponseState {
      int cmdWord;
      int bleID;
      int length;
      String bleName;
    } BleNameResponse; // Öffentliche Strukturvariable

  private:
    int _macAdress;
    void parseBatteryOEMParametersResponse(uint8_t* response, size_t length);
    void parseRealTimeParameter1Response(uint8_t* response, size_t length);
    void parseRealTimeParameter0Response(uint8_t* response, size_t length);
    void parseHardwareInfoClass(uint8_t* response, size_t length);
    void parseLoopRecordResponse(uint8_t* response, size_t length);
    void parseAbnormalStatisticsResponse(uint8_t* response, size_t length);
    void parseUserParameterResponse(uint8_t* response, size_t length);
    void parseBleNameResponse(uint8_t* response, size_t length);

    int16_t convertToInt16(uint8_t* array, int startIndex, size_t length);
};

#endif

