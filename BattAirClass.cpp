#include "BattAirClass.h"

BattAirClass::BattAirClass(int macAdress) {
  _macAdress = macAdress;
  Name = "";
  Rssi = 0;
  Status = "";

}
BattAirClass::BattAirClass() {
  Name = "";
  Rssi = 0;
  Status = "";
}

void BattAirClass::setMacAdress(int macAdress){
  _macAdress = macAdress;
}
void BattAirClass::setDataToEncrypt( uint8_t* data, size_t length) {
  /*delay(100);
  Serial.println(length);
  delay(100);*/
  for (int i = 0; i < length; i++){
    data[i] = (data[i] ^ _macAdress);
  }


  switch (data[0] & 0xFF) {
  case 21:
    //Serial.print("Parse Funktion:BatteryOEMParameters gefunden. Byte: ");
     //Serial.println(data[0]);
    parseBatteryOEMParametersResponse(data,length);
    break;
  case 19:
    //Serial.print("Parse Funktion:parseRealTimeParameter1Response gefunden. Byte: ");
    //Serial.println(data[0]);
    parseRealTimeParameter1Response(data,length);
    break;
  case 17:
    //Serial.print("Parse Funktion:parseRealTimeParameter0Response gefunden. Byte: ");
     //Serial.println(data[0]);
    parseRealTimeParameter0Response(data,length);
    break;
  case 15:
    //Serial.print("Parse Funktion:parseUserParameterResponse gefunden. Byte: ");
     //Serial.println(data[0]);
    parseUserParameterResponse(data,length);
    break;
  case 7:
    //Serial.print("Parse Funktion:parseBleNameResponse gefunden. Byte: ");
     //Serial.println(data[0]);
    parseBleNameResponse(data,length);
    break;
  case 11:
    //Serial.print("Parse Funktion:parseLoopRecordResponse gefunden. Byte: ");
     //Serial.println(data[0]);
    parseLoopRecordResponse(data,length);
    break;
  case 5:
    //Serial.print("Parse Funktion:parseAbnormalStatisticsResponse gefunden. Byte: ");
     //Serial.println(data[0]);
    parseAbnormalStatisticsResponse(data,length);
    break;
  case 3:
    //Serial.print("Parse Funktion:parseHardwareInfoClass gefunden. Byte: ");
     //Serial.println(data[0]);
    parseHardwareInfoClass(data,length);
    break;


  default:
    // Statement(s)
   //Serial.println("Keine passende Parse Funktion gefunden. Byte: " + data[0]);
    break; // Wird nicht benötigt, wenn Statement(s) vorhanden sind
}          

}

void BattAirClass::getEncryptData() {
  digitalWrite(_macAdress, LOW);
}

void BattAirClass::parseBatteryOEMParametersResponse(uint8_t* response, size_t length) {
  /*  Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
  Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/

  int i = response[1] & 0xFF;
  i = response[3] & 0xFF;
  BatteryOEMParametersResponse.singleCoreOverDischargeVoltage = i;
  BatteryOEMParametersResponse.singleCoreOverDischargeVoltage = (response[4] & 0xFF) << 8 | i;
  i = response[5] & 0xFF;
  BatteryOEMParametersResponse.singleCoreDischargeVoltage = i;
  BatteryOEMParametersResponse.singleCoreDischargeVoltage = (response[6] & 0xFF) << 8 | i;
  i = response[7] & 0xFF;
  BatteryOEMParametersResponse.singleCoreFullChargingVoltage = i;
  BatteryOEMParametersResponse.singleCoreFullChargingVoltage = i | (response[8] & 0xFF) << 8;
  i = response[9] & 0xFF;
  BatteryOEMParametersResponse.singleCoreStorageVoltage = i;
  BatteryOEMParametersResponse.singleCoreStorageVoltage = (response[10] & 0xFF) << 8 | i;
  i = response[11] & 0xFF;
  BatteryOEMParametersResponse.chargingRate = i;
  BatteryOEMParametersResponse.chargingRate = (response[12] & 0xFF) << 8 | i;
  i = response[13] & 0xFF;
  BatteryOEMParametersResponse.dischargingRate = i;
  BatteryOEMParametersResponse.dischargingRate = (response[14] & 0xFF) << 8 | i;
  BatteryOEMParametersResponse.useLowTemperatureLimit = response[15];
  BatteryOEMParametersResponse.useHighTemperatureLimit = response[16] & 0xFF;
  BatteryOEMParametersResponse.storageLowTemperatureLimit = response[17];
  BatteryOEMParametersResponse.storageHighTemperatureLimit = response[18] & 0xFF;
  BatteryOEMParametersResponse.selfDischargeEnable = response[19] & 0xFF;

  /*Serial.print("singleCoreOverDischargeVoltage: ");
  Serial.println(BatteryOEMParametersResponse.singleCoreOverDischargeVoltage);
  Serial.print("singleCoreDischargeVoltage: ");
  Serial.println(BatteryOEMParametersResponse.singleCoreDischargeVoltage);
  Serial.print("singleCoreFullChargingVoltage: ");
  Serial.println(BatteryOEMParametersResponse.singleCoreFullChargingVoltage);
  Serial.print("singleCoreStorageVoltage: ");
  Serial.println(BatteryOEMParametersResponse.singleCoreStorageVoltage);
  Serial.print("chargingRate: ");
  Serial.println(BatteryOEMParametersResponse.chargingRate);
  Serial.print("dischargingRate: ");
  Serial.println(BatteryOEMParametersResponse.dischargingRate);
  Serial.print("useLowTemperatureLimit: ");
  Serial.println(BatteryOEMParametersResponse.useLowTemperatureLimit);
  Serial.print("useHighTemperatureLimit: ");
  Serial.println(BatteryOEMParametersResponse.useHighTemperatureLimit);
  Serial.print("storageLowTemperatureLimit: ");
  Serial.println(BatteryOEMParametersResponse.storageLowTemperatureLimit);
  Serial.print("storageHighTemperatureLimit: ");
  Serial.println(BatteryOEMParametersResponse.storageHighTemperatureLimit);
  Serial.print("selfDischargeEnable: ");
  Serial.println(BatteryOEMParametersResponse.selfDischargeEnable);*/
}

void BattAirClass::parseRealTimeParameter1Response(uint8_t* response, size_t length) {
  /*Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/
  int i = response[1] & 0xFF;
  RealTimeParameter1Response.bleID = i;
  RealTimeParameter1Response.bleID = (response[2] & 0xFF) << 8 | i;
  RealTimeParameter1Response.temperature = response[3];
  i = response[4] & 0xFF;
  RealTimeParameter1Response.dischargingCurrent = i;
  i |= (response[5] & 0xFF) << 8;
  RealTimeParameter1Response.dischargingCurrent = i;
  i |= (response[6] & 0xFF) << 16;
  RealTimeParameter1Response.dischargingCurrent = i;
  RealTimeParameter1Response.dischargingCurrent = i | (response[7] & 0xFF) << 24;
  i = response[8] & 0xFF;
  RealTimeParameter1Response.chargingCurrent = i;
  i = (response[9] & 0xFF) << 8 | i;
  RealTimeParameter1Response.chargingCurrent = i;
  i |= (response[10] & 0xFF) << 16;
  RealTimeParameter1Response.chargingCurrent = i;
  RealTimeParameter1Response.chargingCurrent = i | (response[11] & 0xFF) << 24;
  if (length > 12)
  {
      RealTimeParameter1Response.electricity = response[12];
      
  }
  /*  Serial.print("temperature: ");
    Serial.println(RealTimeParameter1Response.temperature);
    Serial.print("dischargingCurrent: ");
    Serial.println(RealTimeParameter1Response.dischargingCurrent);
    Serial.print("chargingCurrent: ");
    Serial.println(RealTimeParameter1Response.chargingCurrent);
    Serial.print("electricity: ");
    Serial.println(RealTimeParameter1Response.electricity);*/
}

void BattAirClass::parseRealTimeParameter0Response(uint8_t* response, size_t length) {
 /*Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/
  int i = response[1] & 0xFF;

  RealTimeParameter0Response.bleID = i;
  //Serial.print("CellNumber:");
  //Serial.println(HardwareInfoClass.cells);

  switch (HardwareInfoClass.cells) { 
    case 2: 
      RealTimeParameter0Response.cellVoltage1 = convertToInt16(response,4,length);
      RealTimeParameter0Response.cellVoltage2 = convertToInt16(response,6,length);
      break;
    case 3:
      RealTimeParameter0Response.cellVoltage1 = convertToInt16(response,4,length);
      RealTimeParameter0Response.cellVoltage2 = convertToInt16(response,6,length);
      RealTimeParameter0Response.cellVoltage3 = convertToInt16(response,8,length); 
      break;
    case 4:
      RealTimeParameter0Response.cellVoltage1 = convertToInt16(response,4,length);
      RealTimeParameter0Response.cellVoltage2 = convertToInt16(response,6,length);
      RealTimeParameter0Response.cellVoltage3 = convertToInt16(response,8,length);
      RealTimeParameter0Response.cellVoltage4 = convertToInt16(response,10,length);
      break;
    case 5:
      RealTimeParameter0Response.cellVoltage1 = convertToInt16(response,4,length);
      RealTimeParameter0Response.cellVoltage2 = convertToInt16(response,6,length);
      RealTimeParameter0Response.cellVoltage3 = convertToInt16(response,8,length);
      RealTimeParameter0Response.cellVoltage4 = convertToInt16(response,10,length);
      RealTimeParameter0Response.cellVoltage5 = convertToInt16(response,12,length);
      break;
    case 6:
      RealTimeParameter0Response.cellVoltage1 = convertToInt16(response,4,length);
      RealTimeParameter0Response.cellVoltage2 = convertToInt16(response,6,length);
      RealTimeParameter0Response.cellVoltage3 = convertToInt16(response,8,length);
      RealTimeParameter0Response.cellVoltage4 = convertToInt16(response,10,length);
      RealTimeParameter0Response.cellVoltage5 = convertToInt16(response,12,length);
      RealTimeParameter0Response.cellVoltage6 = convertToInt16(response,14,length);
      break;
    default:
      RealTimeParameter0Response.cellVoltage1 = 0;
  }

 
  
    /*Serial.print("cellVoltage 1: ");
    Serial.println(RealTimeParameter0Response.cellVoltage1);
    Serial.print("cellVoltage 2: ");
    Serial.println(RealTimeParameter0Response.cellVoltage2);
    Serial.print("cellVoltage 3: ");
    Serial.println(RealTimeParameter0Response.cellVoltage3);
    Serial.print("cellVoltage 4: ");
    Serial.println(RealTimeParameter0Response.cellVoltage4);
    Serial.print("cellVoltage 5: ");
    Serial.println(RealTimeParameter0Response.cellVoltage5);
    Serial.print("cellVoltage 6: ");
    Serial.println(RealTimeParameter0Response.cellVoltage6);*/
}

void BattAirClass::parseHardwareInfoClass(uint8_t* response, size_t length) {
 /* Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/

  int i = response[1] & 0xFF;

  HardwareInfoClass.bleID = i;
  HardwareInfoClass.bleID = i | (response[2] & 0xFF) << 8;
  HardwareInfoClass.mainHardwareVersion = response[3] & 0xFF;
  HardwareInfoClass.subHardwareVersion = response[4] & 0xFF;
  HardwareInfoClass.mainSoftwareVersion = response[5] & 0xFF;
  HardwareInfoClass.subSoftwareVersion = response[6] & 0xFF;
  HardwareInfoClass.versionFlag = response[7] & 0xFF;
  HardwareInfoClass.appID = response[8] & 0xFF;
  HardwareInfoClass.batteryType = response[9] & 0xFF;
  HardwareInfoClass.cells = response[10] & 0xFF;
  i = response[11];
  HardwareInfoClass.balanceFunction = i & 0x1;
  HardwareInfoClass.batteryTemperature = i >> 1 & 0x1;
  HardwareInfoClass.ambientTemperature = i >> 2 & 0x1;
  HardwareInfoClass.cellVoltage = i >> 3 & 0x1;
  HardwareInfoClass.overchargeProtection = i >> 4 & 0x1;
  HardwareInfoClass.overDischargeProtection = 0x1 & i >> 5;
  i = response[12] & 0xFF;
  HardwareInfoClass.oEMCustomerNumber = i;
  HardwareInfoClass.oEMCustomerNumber = (response[13] & 0xFF) << 8 | i;
  i = response[14] & 0xFF;
  HardwareInfoClass.productionDate = i;
  i = (response[15] & 0xFF) << 8 | i;
  HardwareInfoClass.productionDate = i;
  i |= (response[16] & 0xFF) << 16;
  HardwareInfoClass.productionDate = i;
  HardwareInfoClass.productionDate = (response[17] & 0xFF) << 24 | i;

   switch (HardwareInfoClass.batteryType) { 
        case 0:
          HardwareInfoClass.batteryTypeString = "LiHv";
          break;
        case 1:
          HardwareInfoClass.batteryTypeString = "LiPo";
          break;
        case 2:
          HardwareInfoClass.batteryTypeString = "LiIon";
          break;
        case 3:
          HardwareInfoClass.batteryTypeString = "LiFe";
          break;
        case 4:
          HardwareInfoClass.batteryTypeString = "Pb";
          break;
        case 5:
          HardwareInfoClass.batteryTypeString = "NiMh/Cd";
          break;
        case 6:
          HardwareInfoClass.batteryTypeString = "LiUHv";
          break;
        default:
          HardwareInfoClass.batteryTypeString = "";
          break;
        
   }

   /* Serial.print("mainHardwareVersion: ");
    Serial.println(HardwareInfoClass.mainHardwareVersion);
    Serial.print("subHardwareVersion: ");
    Serial.println(HardwareInfoClass.subHardwareVersion);
    Serial.print("mainSoftwareVersion: ");
    Serial.println(HardwareInfoClass.mainSoftwareVersion);
    Serial.print("subSoftwareVersion: ");
    Serial.println(HardwareInfoClass.subSoftwareVersion);
    Serial.print("versionFlag: ");
    Serial.println(HardwareInfoClass.versionFlag);
    Serial.print("appID: ");
    Serial.println(HardwareInfoClass.appID);
    Serial.print("batteryType: ");
    Serial.println(HardwareInfoClass.batteryType);
    Serial.print("batteryTypeString: ");
    Serial.println(HardwareInfoClass.batteryTypeString);
    Serial.print("cells: ");
    Serial.println(HardwareInfoClass.cells);
    Serial.print("balanceFunction: ");
    Serial.println(HardwareInfoClass.balanceFunction);
    Serial.print("batteryTemperature: ");
    Serial.println(HardwareInfoClass.batteryTemperature);
    Serial.print("ambientTemperature: ");
    Serial.println(HardwareInfoClass.ambientTemperature);
    Serial.print("cellVoltage: ");
    Serial.println(HardwareInfoClass.cellVoltage);
    Serial.print("overchargeProtection: ");
    Serial.println(HardwareInfoClass.overchargeProtection);
    Serial.print("overDischargeProtection: ");
    Serial.println(HardwareInfoClass.overDischargeProtection);
    Serial.print("oEMCustomerNumber: ");
    Serial.println(HardwareInfoClass.oEMCustomerNumber);
    Serial.print("productionDate: ");
    Serial.println(HardwareInfoClass.productionDate);*/
    
}
void BattAirClass::parseLoopRecordResponse(uint8_t* response, size_t length) {
  /*Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/

  int i = response[1] & 0xFF;

  LoopRecordResponse.bleID = i;
  LoopRecordResponse.bleID = (response[2] & 0xFF) << 8 | i;
  i = response[3] & 0xFF;
  LoopRecordResponse.recordNumber = i;
  LoopRecordResponse.recordNumber = (response[4] & 0xFF) << 8 | i;
  i = response[5] & 0xFF;
  LoopRecordResponse.cycleNumber = i;
  LoopRecordResponse.cycleNumber = (response[6] & 0xFF) << 8 | i;
  long l = response[7] & 0xFF;
  LoopRecordResponse.cycleInformation = l;
  l |= (response[8] & 0xFF) << 8;
  LoopRecordResponse.cycleInformation = l;
  l |= (response[9] & 0xFF) << 16;
  LoopRecordResponse.cycleInformation = l;
  l |= (response[10] & 0xFF) << 24;
  LoopRecordResponse.cycleInformation = l;
  LoopRecordResponse.cycleInformation = l | (response[11] & 0xFF) << 32;


/*    Serial.print("recordNumber: ");
    Serial.println(LoopRecordResponse.recordNumber);
    Serial.print("cycleNumber: ");
    Serial.println(LoopRecordResponse.cycleNumber);
    Serial.print("cycleInformation: ");
    Serial.println(LoopRecordResponse.cycleInformation);*/
    
}

void BattAirClass::parseAbnormalStatisticsResponse(uint8_t* response, size_t length) {
  /*Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/

  int i = response[1] & 0xFF;

  AbnormalStatisticsResponse.bleID = i;
  AbnormalStatisticsResponse.bleID = (response[2] & 0xFF) << 8 | i;
  i = response[3] & 0xFF;
  AbnormalStatisticsResponse.batteryCycles = i;
  AbnormalStatisticsResponse.batteryCycles = (response[4] & 0xFF) << 8 | i;
  i = response[5] & 0xFF;
  AbnormalStatisticsResponse.errorLogRecord = i;
  AbnormalStatisticsResponse.errorLogRecord = (response[6] & 0xFF) << 8 | i;
  AbnormalStatisticsResponse.outagesRecord = response[7] & 0xFF;
  i = response[8] & 0xFF;
  AbnormalStatisticsResponse.abnormalTemperatureRecord = i;
  AbnormalStatisticsResponse.abnormalTemperatureRecord = (response[9] & 0xFF) << 8| i;
  i = response[10] & 0xFF;
  AbnormalStatisticsResponse.overpressureRecord = i;
  AbnormalStatisticsResponse.overpressureRecord = (response[11] & 0xFF) << 8 | i;
  i = response[12] & 0xFF;
  AbnormalStatisticsResponse.overDischargeRecord = i;
  AbnormalStatisticsResponse.overDischargeRecord = (response[13] & 0xFF) << 8 | i;



    /*Serial.print("batteryCycles: ");
    Serial.println(AbnormalStatisticsResponse.batteryCycles);
    Serial.print("errorLogRecord: ");
    Serial.println(AbnormalStatisticsResponse.errorLogRecord);
    Serial.print("outagesRecord: ");
    Serial.println(AbnormalStatisticsResponse.outagesRecord);
    Serial.print("abnormalTemperatureRecord: ");
    Serial.println(AbnormalStatisticsResponse.abnormalTemperatureRecord);
    Serial.print("overpressureRecord: ");
    Serial.println(AbnormalStatisticsResponse.overpressureRecord);
    Serial.print("overDischargeRecord: ");
    Serial.println(AbnormalStatisticsResponse.overDischargeRecord);*/
    
}
void BattAirClass::parseUserParameterResponse(uint8_t* response, size_t length) {
 /* Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/

  int i = response[1] & 0xFF;

      UserParameterResponse.bleID = i;
      UserParameterResponse.bleID = (response[2] & 0xFF) << 8 | i;
      i = response[3] & 0xFF;
      UserParameterResponse.userRechargingCurrent = i;
      i = (response[4] & 0xFF) << 8 | i;
      UserParameterResponse.userRechargingCurrent = i;
      UserParameterResponse.userRechargingCurrent = i | (response[5] & 0xFF) << 16;
      i = response[6] & 0xFF;
      UserParameterResponse.userStorageVoltage = i;
      UserParameterResponse.userStorageVoltage = (response[7] & 0xFF) << 8 | i;
      i = response[8] & 0xFF;
      UserParameterResponse.userFullChargeCutOffVoltage = i;
      UserParameterResponse.userFullChargeCutOffVoltage = (response[9] & 0xFF) << 8 | i;
      UserParameterResponse.userSelfDischargeTiming = response[10] & 0xFF;
      UserParameterResponse.lEDEnable = response[11] & 0xFF;



   /* Serial.print("userRechargingCurrent: ");
    Serial.println(UserParameterResponse.userRechargingCurrent);
    Serial.print("userStorageVoltage: ");
    Serial.println(UserParameterResponse.userStorageVoltage);
    Serial.print("userFullChargeCutOffVoltage: ");
    Serial.println(UserParameterResponse.userFullChargeCutOffVoltage);
    Serial.print("userSelfDischargeTiming: ");
    Serial.println(UserParameterResponse.userSelfDischargeTiming);
    Serial.print("lEDEnable: ");
    Serial.println(UserParameterResponse.lEDEnable);*/
    
}

void BattAirClass::parseBleNameResponse(uint8_t* response, size_t length) {
  /*Serial.println("Response:");
  for(int i=0; i<length;i++){
    Serial.print(response[i]);
  }
    Serial.println("");
  delay(100);
    Serial.println(length);
  delay(100);*/
  BleNameResponse.cmdWord = response[0];
  int j = 0;
  int i = response[1] & 0xFF;
      
      BleNameResponse.bleID = i;
      BleNameResponse.bleID = (response[2] & 0xFF) << 8 | i;
      i = 4;
      int k = response[3] & 0xFF;
      BleNameResponse.length = k;
      byte arrayOfByte[k];
      while (j < length) { 
        arrayOfByte[j] = response[i]; 
        j++; 
        i++; 
      }
      BleNameResponse.bleName = String((char*)arrayOfByte);


    /*Serial.print("cmdWord: ");
    Serial.println(BleNameResponse.cmdWord);
    Serial.print("length: ");
    Serial.println(BleNameResponse.length);
    Serial.print("bleName: ");
    Serial.println(BleNameResponse.bleName);    */
}


// Funktion zur Umwandlung
int16_t BattAirClass::convertToInt16(uint8_t* array, int startIndex, size_t length) {
  if (startIndex < 0 || startIndex + 1 >= length) {
    // Fehlerbehandlung für ungültigen Startindex
    return -1; 
  }
  
  uint8_t lowByte = array[startIndex];
  uint8_t highByte = array[startIndex + 1];
  
  // Konvertierung der beiden Werte zu einem int16 (Little Endian)
  int16_t result = (highByte << 8) | lowByte;
  
  return result;
}



