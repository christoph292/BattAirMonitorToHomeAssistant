#include <NimBLEDevice.h>
#include <vector>
#include "BattAirClass.h"
#include <ArduinoHA.h>
#include <WiFi.h>
#include <Preferences.h>

#define TARGET_DEVICE_NAME "BATAIRBattAir"  
#define TARGET_MANUFACTURER_DATA "\xba\xab\x10\x00\x00\x00\x8f\x00\x20\x0c\x19\x01\x00\x02\x64\x00\x01\xff\xff\xff\xff"
#define SERVICE_UUID "0000ba00-0000-1000-8000-00805f9b34fb"         // Ersetze durch die UUID des Services
#define CHARACTERISTIC_UUID "0000ba01-0000-1000-8000-00805f9b34fb"  // Ersetze durch die UUID der Charakteristik

//***************************Adjust****************************************************************
//Home Assistant Mqtt Broker Einstellungen
#define BROKER_ADDR IPAddress(192, 168, xxx, xxx)
#define BROKER_USERNAME     "xxx" 
#define BROKER_PASSWORD     "xxx"

//Wlan Einstellungen
const char* ssid = "xxxxxxxx";
const char* password = "xxxxxxx";
//***************************Adjust****************************************************************

//Wifi
WiFiClient client;

// HA Daten
byte mac[] = { 0x00, 0x10, 0xFA, 0x6E, 0x38, 0x4A };
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(client, device, 254);
HANumber sleepTimeCounter("SleepTimeCounter");
HASelect resetOrder("resetOrder");
HASensorNumber foundDevicesNumber("foundDevices");
HASensorNumber wakeUpCounter("lapCounter");

//Home Assistant Battery Dekleration
	//Battery 1
	HASensor bat1Name("Bat1Name");
	//HASensorNumber bat1Temperature("Bat1Temperature");
	HASensor bat1BatteryType("Bat1BatteryType");
	HASensorNumber bat1BatteryCycles("Bat1BatteryCycles");
	HASensorNumber bat1BatteryVoltage("Bat1BatteryVoltage");
	HASensorNumber bat1CellVoltage1("Bat1CellVoltage1");
	HASensorNumber bat1CellVoltage2("Bat1CellVoltage2");
	HASensorNumber bat1CellVoltage3("Bat1CellVoltage3");
	HASensorNumber bat1CellVoltage4("Bat1CellVoltage4");
	HASensorNumber bat1CellVoltage5("Bat1CellVoltage5");
	HASensorNumber bat1CellVoltage6("Bat1CellVoltage6");
	
	//Battery 2
	HASensor bat2Name("Bat2Name");
	//HASensorNumber bat2Temperature("Bat2Temperature");
	HASensor bat2BatteryType("Bat2BatteryType");
	HASensorNumber bat2BatteryCycles("Bat2BatteryCycles");
	HASensorNumber bat2BatteryVoltage("Bat2BatteryVoltage");
	HASensorNumber bat2CellVoltage1("Bat2CellVoltage1");
	HASensorNumber bat2CellVoltage2("Bat2CellVoltage2");
	HASensorNumber bat2CellVoltage3("Bat2CellVoltage3");
	HASensorNumber bat2CellVoltage4("Bat2CellVoltage4");
	HASensorNumber bat2CellVoltage5("Bat2CellVoltage5");
	HASensorNumber bat2CellVoltage6("Bat2CellVoltage6");
	
	//Battery 3
	HASensor bat3Name("Bat3Name");
	//HASensorNumber bat3Temperature("Bat3Temperature");
	HASensor bat3BatteryType("Bat3BatteryType");
	HASensorNumber bat3BatteryCycles("Bat3BatteryCycles");
	HASensorNumber bat3BatteryVoltage("Bat3BatteryVoltage");
	HASensorNumber bat3CellVoltage1("Bat3CellVoltage1");
	HASensorNumber bat3CellVoltage2("Bat3CellVoltage2");
	HASensorNumber bat3CellVoltage3("Bat3CellVoltage3");
	HASensorNumber bat3CellVoltage4("Bat3CellVoltage4");
	HASensorNumber bat3CellVoltage5("Bat3CellVoltage5");
	HASensorNumber bat3CellVoltage6("Bat3CellVoltage6");
	
	//Battery 4
	HASensor bat4Name("Bat4Name");
	//HASensorNumber bat4Temperature("Bat4Temperature");
	HASensor bat4BatteryType("Bat4BatteryType");
	HASensorNumber bat4BatteryCycles("Bat4BatteryCycles");
	HASensorNumber bat4BatteryVoltage("Bat4BatteryVoltage");
	HASensorNumber bat4CellVoltage1("Bat4CellVoltage1");
	HASensorNumber bat4CellVoltage2("Bat4CellVoltage2");
	HASensorNumber bat4CellVoltage3("Bat4CellVoltage3");
	HASensorNumber bat4CellVoltage4("Bat4CellVoltage4");
	HASensorNumber bat4CellVoltage5("Bat4CellVoltage5");
	HASensorNumber bat4CellVoltage6("Bat4CellVoltage6");
	
	//Battery 5
	HASensor bat5Name("Bat5Name");
	//HASensorNumber bat5Temperature("Bat5Temperature");
	HASensor bat5BatteryType("Bat5BatteryType");
	HASensorNumber bat5BatteryCycles("Bat5BatteryCycles");
	HASensorNumber bat5BatteryVoltage("Bat5BatteryVoltage");
	HASensorNumber bat5CellVoltage1("Bat5CellVoltage1");
	HASensorNumber bat5CellVoltage2("Bat5CellVoltage2");
	HASensorNumber bat5CellVoltage3("Bat5CellVoltage3");
	HASensorNumber bat5CellVoltage4("Bat5CellVoltage4");
	HASensorNumber bat5CellVoltage5("Bat5CellVoltage5");
	HASensorNumber bat5CellVoltage6("Bat5CellVoltage6");
	
	//Battery 6
	HASensor bat6Name("Bat6Name");
	//HASensorNumber bat6Temperature("Bat6Temperature");
	HASensor bat6BatteryType("Bat6BatteryType");
	HASensorNumber bat6BatteryCycles("Bat6BatteryCycles");
	HASensorNumber bat6BatteryVoltage("Bat6BatteryVoltage");
	HASensorNumber bat6CellVoltage1("Bat6CellVoltage1");
	HASensorNumber bat6CellVoltage2("Bat6CellVoltage2");
	HASensorNumber bat6CellVoltage3("Bat6CellVoltage3");
	HASensorNumber bat6CellVoltage4("Bat6CellVoltage4");
	HASensorNumber bat6CellVoltage5("Bat6CellVoltage5");
	HASensorNumber bat6CellVoltage6("Bat6CellVoltage6");
	
	//Battery 7
	HASensor bat7Name("Bat7Name");
	//HASensorNumber bat7Temperature("Bat7Temperature");
	HASensor bat7BatteryType("Bat7BatteryType");
	HASensorNumber bat7BatteryCycles("Bat7BatteryCycles");
	HASensorNumber bat7BatteryVoltage("Bat7BatteryVoltage");
	HASensorNumber bat7CellVoltage1("Bat7CellVoltage1");
	HASensorNumber bat7CellVoltage2("Bat7CellVoltage2");
	HASensorNumber bat7CellVoltage3("Bat7CellVoltage3");
	HASensorNumber bat7CellVoltage4("Bat7CellVoltage4");
	HASensorNumber bat7CellVoltage5("Bat7CellVoltage5");
	HASensorNumber bat7CellVoltage6("Bat7CellVoltage6");
	
	//Battery 8
	HASensor bat8Name("Bat8Name");
	//HASensorNumber bat8Temperature("Bat8Temperature");
	HASensor bat8BatteryType("Bat8BatteryType");
	HASensorNumber bat8BatteryCycles("Bat8BatteryCycles");
	HASensorNumber bat8BatteryVoltage("Bat8BatteryVoltage");
	HASensorNumber bat8CellVoltage1("Bat8CellVoltage1");
	HASensorNumber bat8CellVoltage2("Bat8CellVoltage2");
	HASensorNumber bat8CellVoltage3("Bat8CellVoltage3");
	HASensorNumber bat8CellVoltage4("Bat8CellVoltage4");
	HASensorNumber bat8CellVoltage5("Bat8CellVoltage5");
	HASensorNumber bat8CellVoltage6("Bat8CellVoltage6");
	
	//Battery 9
	HASensor bat9Name("Bat9Name");
	//HASensorNumber bat9Temperature("Bat9Temperature");
	HASensor bat9BatteryType("Bat9BatteryType");
	HASensorNumber bat9BatteryCycles("Bat9BatteryCycles");
	HASensorNumber bat9BatteryVoltage("Bat9BatteryVoltage");
	HASensorNumber bat9CellVoltage1("Bat9CellVoltage1");
	HASensorNumber bat9CellVoltage2("Bat9CellVoltage2");
	HASensorNumber bat9CellVoltage3("Bat9CellVoltage3");
	HASensorNumber bat9CellVoltage4("Bat9CellVoltage4");
	HASensorNumber bat9CellVoltage5("Bat9CellVoltage5");
	HASensorNumber bat9CellVoltage6("Bat9CellVoltage6");
	
	//Battery 10
	HASensor bat10Name("Bat10Name");
	//HASensorNumber bat10Temperature("Bat10Temperature");
	HASensor bat10BatteryType("Bat10BatteryType");
	HASensorNumber bat10BatteryCycles("Bat10BatteryCycles");
	HASensorNumber bat10BatteryVoltage("Bat10BatteryVoltage");
	HASensorNumber bat10CellVoltage1("Bat10CellVoltage1");
	HASensorNumber bat10CellVoltage2("Bat10CellVoltage2");
	HASensorNumber bat10CellVoltage3("Bat10CellVoltage3");
	HASensorNumber bat10CellVoltage4("Bat10CellVoltage4");
	HASensorNumber bat10CellVoltage5("Bat10CellVoltage5");
	HASensorNumber bat10CellVoltage6("Bat10CellVoltage6");
	
	//Battery 11
	HASensor bat11Name("Bat11Name");
	//HASensorNumber bat11Temperature("Bat11Temperature");
	HASensor bat11BatteryType("Bat11BatteryType");
	HASensorNumber bat11BatteryCycles("Bat11BatteryCycles");
	HASensorNumber bat11BatteryVoltage("Bat11BatteryVoltage");
	HASensorNumber bat11CellVoltage1("Bat11CellVoltage1");
	HASensorNumber bat11CellVoltage2("Bat11CellVoltage2");
	HASensorNumber bat11CellVoltage3("Bat11CellVoltage3");
	HASensorNumber bat11CellVoltage4("Bat11CellVoltage4");
	HASensorNumber bat11CellVoltage5("Bat11CellVoltage5");
	HASensorNumber bat11CellVoltage6("Bat11CellVoltage6");
	
	//Battery 12
	HASensor bat12Name("Bat12Name");
	//HASensorNumber bat12Temperature("Bat12Temperature");
	HASensor bat12BatteryType("Bat12BatteryType");
	HASensorNumber bat12BatteryCycles("Bat12BatteryCycles");
	HASensorNumber bat12BatteryVoltage("Bat12BatteryVoltage");
	HASensorNumber bat12CellVoltage1("Bat12CellVoltage1");
	HASensorNumber bat12CellVoltage2("Bat12CellVoltage2");
	HASensorNumber bat12CellVoltage3("Bat12CellVoltage3");
	HASensorNumber bat12CellVoltage4("Bat12CellVoltage4");
	HASensorNumber bat12CellVoltage5("Bat12CellVoltage5");
	HASensorNumber bat12CellVoltage6("Bat12CellVoltage6");
	
	//Battery 13
	HASensor bat13Name("Bat13Name");
	//HASensorNumber bat13Temperature("Bat13Temperature");
	HASensor bat13BatteryType("Bat13BatteryType");
	HASensorNumber bat13BatteryCycles("Bat13BatteryCycles");
	HASensorNumber bat13BatteryVoltage("Bat13BatteryVoltage");
	HASensorNumber bat13CellVoltage1("Bat13CellVoltage1");
	HASensorNumber bat13CellVoltage2("Bat13CellVoltage2");
	HASensorNumber bat13CellVoltage3("Bat13CellVoltage3");
	HASensorNumber bat13CellVoltage4("Bat13CellVoltage4");
	HASensorNumber bat13CellVoltage5("Bat13CellVoltage5");
	HASensorNumber bat13CellVoltage6("Bat13CellVoltage6");
	
	//Battery 14
	HASensor bat14Name("Bat14Name");
	//HASensorNumber bat14Temperature("Bat14Temperature");
	HASensor bat14BatteryType("Bat14BatteryType");
	HASensorNumber bat14BatteryCycles("Bat14BatteryCycles");
	HASensorNumber bat14BatteryVoltage("Bat14BatteryVoltage");
	HASensorNumber bat14CellVoltage1("Bat14CellVoltage1");
	HASensorNumber bat14CellVoltage2("Bat14CellVoltage2");
	HASensorNumber bat14CellVoltage3("Bat14CellVoltage3");
	HASensorNumber bat14CellVoltage4("Bat14CellVoltage4");
	HASensorNumber bat14CellVoltage5("Bat14CellVoltage5");
	HASensorNumber bat14CellVoltage6("Bat14CellVoltage6");
	
	//Battery 15
	HASensor bat15Name("Bat15Name");
	//HASensorNumber bat15Temperature("Bat15Temperature");
	HASensor bat15BatteryType("Bat15BatteryType");
	HASensorNumber bat15BatteryCycles("Bat15BatteryCycles");
	HASensorNumber bat15BatteryVoltage("Bat15BatteryVoltage");
	HASensorNumber bat15CellVoltage1("Bat15CellVoltage1");
	HASensorNumber bat15CellVoltage2("Bat15CellVoltage2");
	HASensorNumber bat15CellVoltage3("Bat15CellVoltage3");
	HASensorNumber bat15CellVoltage4("Bat15CellVoltage4");
	HASensorNumber bat15CellVoltage5("Bat15CellVoltage5");
	HASensorNumber bat15CellVoltage6("Bat15CellVoltage6");
	
	//Battery 16
	HASensor bat16Name("Bat16Name");
	//HASensorNumber bat16Temperature("Bat16Temperature");
	HASensor bat16BatteryType("Bat16BatteryType");
	HASensorNumber bat16BatteryCycles("Bat16BatteryCycles");
	HASensorNumber bat16BatteryVoltage("Bat16BatteryVoltage");
	HASensorNumber bat16CellVoltage1("Bat16CellVoltage1");
	HASensorNumber bat16CellVoltage2("Bat16CellVoltage2");
	HASensorNumber bat16CellVoltage3("Bat16CellVoltage3");
	HASensorNumber bat16CellVoltage4("Bat16CellVoltage4");
	HASensorNumber bat16CellVoltage5("Bat16CellVoltage5");
	HASensorNumber bat16CellVoltage6("Bat16CellVoltage6");
	
	//Battery 17
	HASensor bat17Name("Bat17Name");
	//HASensorNumber bat17Temperature("Bat17Temperature");
	HASensor bat17BatteryType("Bat17BatteryType");
	HASensorNumber bat17BatteryCycles("Bat17BatteryCycles");
	HASensorNumber bat17BatteryVoltage("Bat17BatteryVoltage");
	HASensorNumber bat17CellVoltage1("Bat17CellVoltage1");
	HASensorNumber bat17CellVoltage2("Bat17CellVoltage2");
	HASensorNumber bat17CellVoltage3("Bat17CellVoltage3");
	HASensorNumber bat17CellVoltage4("Bat17CellVoltage4");
	HASensorNumber bat17CellVoltage5("Bat17CellVoltage5");
	HASensorNumber bat17CellVoltage6("Bat17CellVoltage6");
	
	//Battery 18
	HASensor bat18Name("Bat18Name");
	//HASensorNumber bat18Temperature("Bat18Temperature");
	HASensor bat18BatteryType("Bat18BatteryType");
	HASensorNumber bat18BatteryCycles("Bat18BatteryCycles");
	HASensorNumber bat18BatteryVoltage("Bat18BatteryVoltage");
	HASensorNumber bat18CellVoltage1("Bat18CellVoltage1");
	HASensorNumber bat18CellVoltage2("Bat18CellVoltage2");
	HASensorNumber bat18CellVoltage3("Bat18CellVoltage3");
	HASensorNumber bat18CellVoltage4("Bat18CellVoltage4");
	HASensorNumber bat18CellVoltage5("Bat18CellVoltage5");
	HASensorNumber bat18CellVoltage6("Bat18CellVoltage6");
	
	//Battery 19
	HASensor bat19Name("Bat19Name");
	//HASensorNumber bat19Temperature("Bat19Temperature");
	HASensor bat19BatteryType("Bat19BatteryType");
	HASensorNumber bat19BatteryCycles("Bat19BatteryCycles");
	HASensorNumber bat19BatteryVoltage("Bat19BatteryVoltage");
	HASensorNumber bat19CellVoltage1("Bat19CellVoltage1");
	HASensorNumber bat19CellVoltage2("Bat19CellVoltage2");
	HASensorNumber bat19CellVoltage3("Bat19CellVoltage3");
	HASensorNumber bat19CellVoltage4("Bat19CellVoltage4");
	HASensorNumber bat19CellVoltage5("Bat19CellVoltage5");
	HASensorNumber bat19CellVoltage6("Bat19CellVoltage6");
	
	//Battery 20
	HASensor bat20Name("Bat20Name");
	//HASensorNumber bat20Temperature("Bat20Temperature");
	HASensor bat20BatteryType("Bat20BatteryType");
	HASensorNumber bat20BatteryCycles("Bat20BatteryCycles");
	HASensorNumber bat20BatteryVoltage("Bat20BatteryVoltage");
	HASensorNumber bat20CellVoltage1("Bat20CellVoltage1");
	HASensorNumber bat20CellVoltage2("Bat20CellVoltage2");
	HASensorNumber bat20CellVoltage3("Bat20CellVoltage3");
	HASensorNumber bat20CellVoltage4("Bat20CellVoltage4");
	HASensorNumber bat20CellVoltage5("Bat20CellVoltage5");
	HASensorNumber bat20CellVoltage6("Bat20CellVoltage6");
	
	//Battery 21
	HASensor bat21Name("Bat21Name");
	//HASensorNumber bat21Temperature("Bat21Temperature");
	HASensor bat21BatteryType("Bat21BatteryType");
	HASensorNumber bat21BatteryCycles("Bat21BatteryCycles");
	HASensorNumber bat21BatteryVoltage("Bat21BatteryVoltage");
	HASensorNumber bat21CellVoltage1("Bat21CellVoltage1");
	HASensorNumber bat21CellVoltage2("Bat21CellVoltage2");
	HASensorNumber bat21CellVoltage3("Bat21CellVoltage3");
	HASensorNumber bat21CellVoltage4("Bat21CellVoltage4");
	HASensorNumber bat21CellVoltage5("Bat21CellVoltage5");
	HASensorNumber bat21CellVoltage6("Bat21CellVoltage6");
	
	//Battery 22
	HASensor bat22Name("Bat22Name");
	//HASensorNumber bat22Temperature("Bat22Temperature");
	HASensor bat22BatteryType("Bat22BatteryType");
	HASensorNumber bat22BatteryCycles("Bat22BatteryCycles");
	HASensorNumber bat22BatteryVoltage("Bat22BatteryVoltage");
	HASensorNumber bat22CellVoltage1("Bat22CellVoltage1");
	HASensorNumber bat22CellVoltage2("Bat22CellVoltage2");
	HASensorNumber bat22CellVoltage3("Bat22CellVoltage3");
	HASensorNumber bat22CellVoltage4("Bat22CellVoltage4");
	HASensorNumber bat22CellVoltage5("Bat22CellVoltage5");
	HASensorNumber bat22CellVoltage6("Bat22CellVoltage6");
	
	//Battery 23
	HASensor bat23Name("Bat23Name");
	//HASensorNumber bat23Temperature("Bat23Temperature");
	HASensor bat23BatteryType("Bat23BatteryType");
	HASensorNumber bat23BatteryCycles("Bat23BatteryCycles");
	HASensorNumber bat23BatteryVoltage("Bat23BatteryVoltage");
	HASensorNumber bat23CellVoltage1("Bat23CellVoltage1");
	HASensorNumber bat23CellVoltage2("Bat23CellVoltage2");
	HASensorNumber bat23CellVoltage3("Bat23CellVoltage3");
	HASensorNumber bat23CellVoltage4("Bat23CellVoltage4");
	HASensorNumber bat23CellVoltage5("Bat23CellVoltage5");
	HASensorNumber bat23CellVoltage6("Bat23CellVoltage6");
	
	//Battery 24
	HASensor bat24Name("Bat24Name");
	//HASensorNumber bat24Temperature("Bat24Temperature");
	HASensor bat24BatteryType("Bat24BatteryType");
	HASensorNumber bat24BatteryCycles("Bat24BatteryCycles");
	HASensorNumber bat24BatteryVoltage("Bat24BatteryVoltage");
	HASensorNumber bat24CellVoltage1("Bat24CellVoltage1");
	HASensorNumber bat24CellVoltage2("Bat24CellVoltage2");
	HASensorNumber bat24CellVoltage3("Bat24CellVoltage3");
	HASensorNumber bat24CellVoltage4("Bat24CellVoltage4");
	HASensorNumber bat24CellVoltage5("Bat24CellVoltage5");
	HASensorNumber bat24CellVoltage6("Bat24CellVoltage6");
	
	//Battery 25
	HASensor bat25Name("Bat25Name");
	//HASensorNumber bat25Temperature("Bat25Temperature");
	HASensor bat25BatteryType("Bat25BatteryType");
	HASensorNumber bat25BatteryCycles("Bat25BatteryCycles");
	HASensorNumber bat25BatteryVoltage("Bat25BatteryVoltage");
	HASensorNumber bat25CellVoltage1("Bat25CellVoltage1");
	HASensorNumber bat25CellVoltage2("Bat25CellVoltage2");
	HASensorNumber bat25CellVoltage3("Bat25CellVoltage3");
	HASensorNumber bat25CellVoltage4("Bat25CellVoltage4");
	HASensorNumber bat25CellVoltage5("Bat25CellVoltage5");
	HASensorNumber bat25CellVoltage6("Bat25CellVoltage6");

	//Battery 26
	HASensor bat26Name("Bat26Name");
	//HASensorNumber bat26Temperature("Bat26Temperature");
	HASensor bat26BatteryType("Bat26BatteryType");
	HASensorNumber bat26BatteryCycles("Bat26BatteryCycles");
	HASensorNumber bat26BatteryVoltage("Bat26BatteryVoltage");
	HASensorNumber bat26CellVoltage1("Bat26CellVoltage1");
	HASensorNumber bat26CellVoltage2("Bat26CellVoltage2");
	HASensorNumber bat26CellVoltage3("Bat26CellVoltage3");
	HASensorNumber bat26CellVoltage4("Bat26CellVoltage4");
	HASensorNumber bat26CellVoltage5("Bat26CellVoltage5");
	HASensorNumber bat26CellVoltage6("Bat26CellVoltage6");
	
	//Battery 27
	HASensor bat27Name("Bat27Name");
	//HASensorNumber bat27Temperature("Bat27Temperature");
	HASensor bat27BatteryType("Bat27BatteryType");
	HASensorNumber bat27BatteryCycles("Bat27BatteryCycles");
	HASensorNumber bat27BatteryVoltage("Bat27BatteryVoltage");
	HASensorNumber bat27CellVoltage1("Bat27CellVoltage1");
	HASensorNumber bat27CellVoltage2("Bat27CellVoltage2");
	HASensorNumber bat27CellVoltage3("Bat27CellVoltage3");
	HASensorNumber bat27CellVoltage4("Bat27CellVoltage4");
	HASensorNumber bat27CellVoltage5("Bat27CellVoltage5");
	HASensorNumber bat27CellVoltage6("Bat27CellVoltage6");

	//Battery 28
	HASensor bat28Name("Bat28Name");
	//HASensorNumber bat28Temperature("Bat28Temperature");
	HASensor bat28BatteryType("Bat28BatteryType");
	HASensorNumber bat28BatteryCycles("Bat28BatteryCycles");
	HASensorNumber bat28BatteryVoltage("Bat28BatteryVoltage");
	HASensorNumber bat28CellVoltage1("Bat28CellVoltage1");
	HASensorNumber bat28CellVoltage2("Bat28CellVoltage2");
	HASensorNumber bat28CellVoltage3("Bat28CellVoltage3");
	HASensorNumber bat28CellVoltage4("Bat28CellVoltage4");
	HASensorNumber bat28CellVoltage5("Bat28CellVoltage5");
	HASensorNumber bat28CellVoltage6("Bat28CellVoltage6");
	
	//Battery 29
	HASensor bat29Name("Bat29Name");
	//HASensorNumber bat29Temperature("Bat29Temperature");
	HASensor bat29BatteryType("Bat29BatteryType");
	HASensorNumber bat29BatteryCycles("Bat29BatteryCycles");
	HASensorNumber bat29BatteryVoltage("Bat29BatteryVoltage");
	HASensorNumber bat29CellVoltage1("Bat29CellVoltage1");
	HASensorNumber bat29CellVoltage2("Bat29CellVoltage2");
	HASensorNumber bat29CellVoltage3("Bat29CellVoltage3");
	HASensorNumber bat29CellVoltage4("Bat29CellVoltage4");
	HASensorNumber bat29CellVoltage5("Bat29CellVoltage5");
	HASensorNumber bat29CellVoltage6("Bat29CellVoltage6");
	
	//Battery 30
	HASensor bat30Name("Bat30Name");
	//HASensorNumber bat30Temperature("Bat30Temperature");
	HASensor bat30BatteryType("Bat30BatteryType");
	HASensorNumber bat30BatteryCycles("Bat30BatteryCycles");
	HASensorNumber bat30BatteryVoltage("Bat30BatteryVoltage");
	HASensorNumber bat30CellVoltage1("Bat30CellVoltage1");
	HASensorNumber bat30CellVoltage2("Bat30CellVoltage2");
	HASensorNumber bat30CellVoltage3("Bat30CellVoltage3");
	HASensorNumber bat30CellVoltage4("Bat30CellVoltage4");
	HASensorNumber bat30CellVoltage5("Bat30CellVoltage5");
	HASensorNumber bat30CellVoltage6("Bat30CellVoltage6");

const char* devicename;

//Ble
bool scanComplete = false;
bool readOutComplete = false;
static NimBLERemoteCharacteristic* pRemoteCharacteristic;

String response;
uint8_t writeRequest1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
uint8_t requestArray[13][4] = { { 0x02, 0x00, 0x00, 0x00 },
                                { 0x04, 0x00, 0x00, 0x00 },
                                { 0x0E, 0x00, 0x00, 0x00 },
                                { 0x10, 0x00, 0x00, 0x00 },
                                { 0x12, 0x00, 0x00, 0x00 },
                                { 0x14, 0x00, 0x00, 0x00 },
                                { 0x16, 0x00, 0x00, 0x00 },
                                { 0x26, 0x00, 0x00, 0x00 },
                                { 0x28, 0x00, 0x00, 0x00 },
                                { 0x06, 0x00, 0x00, 0x00 },
                                { 0x04, 0x00, 0x00, 0x00 },
                                { 0x0A, 0x00, 0x00, 0x00 },
                                { 0x02, 0x00, 0x00, 0x00 }, };

//BattAirClass BattAirHandler(0);
BattAirClass BattAirHandlerArray[30];
int actualBattery = 0;

//Allgemein
std::vector<String> foundDevices;
std::vector<String> foundDevicesNames;
std::vector<String> savedDevicesOrder;
RTC_DATA_ATTR int16_t lapCounter = 1;
int32_t foundDevicesTempNumber = 0;

//Ausfallsicher speichern
// Erstelle ein Preferences-Objekt 
Preferences preferences;

//DeepSleep
int duration = 10;
int cycles = 20;
int actCycles = 0;
RTC_DATA_ATTR int sleepCount = 0;
RTC_DATA_ATTR int maxSleepCount = 1;// Anzahl der Zyklen die im Home Assistant eingestellt wurden
const uint64_t sleepDuration = 60000000;//3600000000;//1 stunde;
#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  86400//3600//60// 1 Tag/1Stunde/1min/       /* Time ESP32 will go to sleep (in seconds) */

//Funktionen
void saveToPreference(std::vector<String> data){
  if (!preferences.begin("my-app", false)) { 
    Serial.println("Failed to initialize NVS"); return; 
  }

  preferences.putUInt("vector_size", data.size()); 
  for (size_t i = 0; i < data.size(); i++) { 
    String key = String("device_") + String(i); // Verkettung in einer String-Variable speichern
    preferences.putString(key.c_str(), data[i]); 
  }
  // Beenden der Preferences-Sitzung 
  preferences.end();
}

std::vector<String> readOutPreference(){ 
  if (!preferences.begin("my-app", false)) { 
    Serial.println("Failed to initialize NVS"); 
     std::vector<String> loadedDevicesOrder(1); 
    return loadedDevicesOrder; 
  }

  size_t vector_size = preferences.getUInt("vector_size", 0); 
  std::vector<String> loadedDevicesOrder(vector_size); 
  for (size_t i = 0; i < vector_size; i++) { 
    String key = String("device_") + String(i); // Verkettung in einer String-Variable speichern
    loadedDevicesOrder[i] = preferences.getString(key.c_str(), "default"); 
    Serial.print("Gelesener String "); 
    Serial.print(i); 
    Serial.print(": "); 
    Serial.println(loadedDevicesOrder[i]);
  }
  // Beenden der Preferences-Sitzung 
  preferences.end();

  return loadedDevicesOrder;
}

void checkPreferenceList(){
    for (const auto& foundNames : foundDevicesNames) {
      bool found = false;
      for (const auto& orderNames : savedDevicesOrder) {
        if (foundNames==orderNames){
          found = true;
          break;
        }
      }
      if(found == false){
        savedDevicesOrder.push_back(foundNames);
      }
    }
}

bool isDeviceAlreadyFound(const String& address) {
  for (const auto& existingAddress : foundDevices) {
    if (existingAddress == address) {
      return true;
    }
  }
  return false;
}

int getListNumberSavedOrder(String searchName){
  int i = 0;
  //Serial.print("Search Name:");
  //Serial.println(searchName);
  bool found = false;
  for (const auto& orderNames : savedDevicesOrder) {
    //Serial.print("Compare Name:");
    //Serial.println(orderNames);
    if (searchName==orderNames){
      found = true;
      break;
    }
    i++;
  }
  //Serial.print("Number Name:");
    //Serial.println(i);
  if (found == true) return i;
  else return 99;
  
}

bool compareManufacturerData(const std::string& data) {
  Serial.print("Manufactor Data:");
  Serial.println(data.c_str());
  return data.compare(0, strlen(TARGET_MANUFACTURER_DATA), TARGET_MANUFACTURER_DATA) == 0;
}

class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) override {
    Serial.print("Advertised Device: ");
    Serial.println(advertisedDevice->getName().c_str());

    // Überprüfen, ob der Gerätename übereinstimmt und das Gerät noch nicht in der Liste ist
    if (advertisedDevice->haveName() ){//&& advertisedDevice->getName() == TARGET_DEVICE_NAME) {
    //if (advertisedDevice->haveManufacturerData()) {
      //std::string manufacturerData = advertisedDevice->getManufacturerData();
      //if (compareManufacturerData(manufacturerData)) {
      // Überprüfen, ob der Gerätename "BatAir" enthält 
      if (advertisedDevice->getName().find("BATAIR") != std::string::npos) { 
        Serial.println("BatAir-Gerät in der Nähe gefunden!"); 
        Serial.print("Match found: ");
        Serial.println(advertisedDevice->getAddress().toString().c_str());
        // Überprüfe, ob der Local Name im Advertisement-Datenpaket vorhanden ist 
        if (advertisedDevice->haveName()) { 
          Serial.print("Device Name: "); 
          Serial.println(advertisedDevice->getName().c_str()); 
        }
        String address = advertisedDevice->getAddress().toString().c_str();
        if (!isDeviceAlreadyFound(address)) {
          Serial.println("Zielgerät gefunden und hinzugefügt!");
          foundDevices.push_back(address);
          // Suche und Lösche alle Vorkommen von "0000" 
          String name = String(advertisedDevice->getName().c_str()).substring(6);
          String substring = "0000"; 
          int index = name.indexOf(substring); 
          //while (index != -1) { 
            name.remove(index, substring.length()); 
            //index = name.indexOf(substring); // Suche erneut nach "0000" 
          //}
          Serial.print("Device Name cut: "); 
          Serial.println(name); 
          foundDevicesNames.push_back(name);
        } else {
          Serial.println("Gerät bereits in der Liste.");
        } 
      }
    }
  }
};

void scanCompleteCallback(NimBLEScanResults scanResults) {
  scanComplete = true;
  checkPreferenceList();
  saveToPreference(savedDevicesOrder);
}

static void notifyCallback(NimBLERemoteCharacteristic* pNimBLERemoteCharacteristic,
                           uint8_t* pData, size_t length, bool isNotify) {
  //Serial.println("Callback");
  BattAirHandlerArray[actualBattery].setDataToEncrypt(pData, length);
}

void onSelectCommand(int8_t index, HASelect* sender){
    switch (index) {
    case 0:
        // Option "Keep" was selected
        //Serial.println("Keep Order");
        break;

    case 1:
        // Option "Reset" was selected
        preferences.begin("my-app", false);
        preferences.clear();
        preferences.end();
        //Serial.println("Reset Order");
        break;

    default:
        // unknown option
        return;
    }

    sender->setState(index); // report the selected option back to the HA panel

    // it may return null
    if (sender->getCurrentOption()) {
        //Serial.print("Current option: ");
        //Serial.println(sender->getCurrentOption());
    }
}
void onNumberCommand(HANumeric number, HANumber* sender){
    if (!number.isSet()) {
    } else {
        //int8_t sleepTimeCounter = number.toInt8();
        Serial.print("SleepCounter geändert");
        maxSleepCount =number.toInt8();
        Serial.println(number.toInt8());   
    }
    sender->setState(number); // report the selected option back to the HA panel
}

void setup() {
  Serial.begin(115200);
  esp_sleep_wakeup_cause_t wakeupReason = esp_sleep_get_wakeup_cause();
 
  if (wakeupReason != ESP_SLEEP_WAKEUP_UNDEFINED){
    Serial.print("sleep max Count");
    Serial.println(maxSleepCount);
    if (sleepCount < (maxSleepCount-1)) {
      sleepCount++; 
      Serial.print("Sleep cycle: "); 
      Serial.println(sleepCount); // Konfiguriere den Timer-Wake-Up 
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR); 
      // Gib eine Meldung aus und gehe in den Deep-Sleep-Modus 
      Serial.println("Going to sleep now"); 
      delay(1000); 
      // Gib der seriellen Ausgabe Zeit, die Nachricht zu senden 
      esp_deep_sleep_start(); 
    } else { 
      Serial.println("Maximale Deep-Sleep-Zeit erreicht!"); 
      sleepCount=0;
    }
  }else{
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR); 
  }
  // Konfiguriere den Timer-Wake-Up  für Testzwecke
  //esp_sleep_enable_timer_wakeup(duration * 1000000); 

  if(lapCounter>1000){
      lapCounter=1;
  }else{
    lapCounter++;
  }
  
  //Wifi
  WiFi.mode(WIFI_STA);  // Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  //Batteriereinfolge aus Speicher auslesen
  savedDevicesOrder = readOutPreference();

  // Set device's details (optional)
  device.setName("BattAirMonitor");
  device.setSoftwareVersion("1.6.3.7");
  device.setManufacturer("BattAir");
  device.setModel("ModelEsp");
  device.enableExtendedUniqueIds();
    
  // optional properties
  resetOrder.setIcon("mdi:restart");
  resetOrder.setName("Clear Print Order");
  
  // press callbacks
  resetOrder.onCommand(onSelectCommand);
  resetOrder.setOptions("Keep;Reset"); // use semicolons as separator of options
  resetOrder.setRetain(true);
  // handle command from the HA panel
  sleepTimeCounter.onCommand(onNumberCommand);

  // Optional configuration
  sleepTimeCounter.setIcon("mdi:sleep");
  sleepTimeCounter.setName("Sleep Duration");
  sleepTimeCounter.setUnitOfMeasurement("Days");
  sleepTimeCounter.setMin(1); 
  sleepTimeCounter.setMax(90); 
  sleepTimeCounter.setRetain(true);
  
  foundDevicesNumber.setName("Found Devices"); 
  foundDevicesNumber.setIcon("mdi:battery-charging-wireless"); 

  wakeUpCounter.setName("Wake up Counter"); 
  wakeUpCounter.setIcon("mdi:counter"); 


//Home Assistant Battery Sensoren Setup
  //Battery 1
  bat1Name.setName("BatteryA1 Name");  
  //bat1Temperature.setName("Battery1 Temperature");  
  bat1BatteryType.setName("BatteryA1 Type");
  bat1BatteryCycles.setName("BatteryA1 Cycles");
  bat1BatteryVoltage.setName("BatteryA1 Voltage");
  bat1CellVoltage1.setName("BatteryA1 Cell Voltage 1");
  bat1CellVoltage2.setName("BatteryA1 Cell Voltage 2");
  bat1CellVoltage3.setName("BatteryA1 Cell Voltage 3");
  bat1CellVoltage4.setName("BatteryA1 Cell Voltage 4");
  bat1CellVoltage5.setName("BatteryA1 Cell Voltage 5");
  bat1CellVoltage6.setName("BatteryA1 Cell Voltage 6");

  bat1Name.setIcon("mdi:battery");
  //bat1Temperature.setIcon("mdi:thermometer");
  //bat1Temperature.setUnitOfMeasurement("°C");
  bat1BatteryType.setIcon("mdi:battery");
  bat1BatteryCycles.setIcon("mdi:battery-sync");
  bat1BatteryVoltage.setIcon("mdi:battery");
  bat1BatteryVoltage.setUnitOfMeasurement("V");
  bat1CellVoltage1.setIcon("mdi:battery");
  bat1CellVoltage1.setUnitOfMeasurement("V");
  bat1CellVoltage2.setIcon("mdi:battery");
  bat1CellVoltage2.setUnitOfMeasurement("V");
  bat1CellVoltage3.setIcon("mdi:battery");
  bat1CellVoltage3.setUnitOfMeasurement("V");
  bat1CellVoltage4.setIcon("mdi:battery");
  bat1CellVoltage4.setUnitOfMeasurement("V");
  bat1CellVoltage5.setIcon("mdi:battery");
  bat1CellVoltage5.setUnitOfMeasurement("V");
  bat1CellVoltage6.setIcon("mdi:battery");
  bat1CellVoltage6.setUnitOfMeasurement("V");

  //Battery 2
  bat2Name.setName("BatteryB2 Name");  
  //bat2Temperature.setName("Battery2 Temperature");  
  bat2BatteryType.setName("BatteryB2 Type");
  bat2BatteryCycles.setName("BatteryB2 Cycles");
  bat2BatteryVoltage.setName("BatteryB2 Voltage");
  bat2CellVoltage1.setName("BatteryB2 Cell Voltage 1");
  bat2CellVoltage2.setName("BatteryB2 Cell Voltage 2");
  bat2CellVoltage3.setName("BatteryB2 Cell Voltage 3");
  bat2CellVoltage4.setName("BatteryB2 Cell Voltage 4");
  bat2CellVoltage5.setName("BatteryB2 Cell Voltage 5");
  bat2CellVoltage6.setName("BatteryB2 Cell Voltage 6");

  bat2Name.setIcon("mdi:battery");
  //bat2Temperature.setIcon("mdi:thermometer");
  //bat2Temperature.setUnitOfMeasurement("°C");
  bat2BatteryType.setIcon("mdi:battery");
  bat2BatteryCycles.setIcon("mdi:battery-sync");
  bat2BatteryVoltage.setIcon("mdi:battery");
  bat2BatteryVoltage.setUnitOfMeasurement("V");
  bat2CellVoltage1.setIcon("mdi:battery");
  bat2CellVoltage1.setUnitOfMeasurement("V");
  bat2CellVoltage2.setIcon("mdi:battery");
  bat2CellVoltage2.setUnitOfMeasurement("V");
  bat2CellVoltage3.setIcon("mdi:battery");
  bat2CellVoltage3.setUnitOfMeasurement("V");
  bat2CellVoltage4.setIcon("mdi:battery");
  bat2CellVoltage4.setUnitOfMeasurement("V");
  bat2CellVoltage5.setIcon("mdi:battery");
  bat2CellVoltage5.setUnitOfMeasurement("V");
  bat2CellVoltage6.setIcon("mdi:battery");
  bat2CellVoltage6.setUnitOfMeasurement("V");

  //Battery 3
  bat3Name.setName("BatteryC3 Name");  
  //bat3Temperature.setName("Battery3 Temperature");  
  bat3BatteryType.setName("BatteryC3 Type");
  bat3BatteryCycles.setName("BatteryC3 Cycles");
  bat3BatteryVoltage.setName("BatteryC3 Voltage");
  bat3CellVoltage1.setName("BatteryC3 Cell Voltage 1");
  bat3CellVoltage2.setName("BatteryC3 Cell Voltage 2");
  bat3CellVoltage3.setName("BatteryC3 Cell Voltage 3");
  bat3CellVoltage4.setName("BatteryC3 Cell Voltage 4");
  bat3CellVoltage5.setName("BatteryC3 Cell Voltage 5");
  bat3CellVoltage6.setName("BatteryC3 Cell Voltage 6");

  bat3Name.setIcon("mdi:battery");
  //bat3Temperature.setIcon("mdi:thermometer");
  //bat3Temperature.setUnitOfMeasurement("°C");
  bat3BatteryType.setIcon("mdi:battery");
  bat3BatteryCycles.setIcon("mdi:battery-sync");
  bat3BatteryVoltage.setIcon("mdi:battery");
  bat3BatteryVoltage.setUnitOfMeasurement("V");
  bat3CellVoltage1.setIcon("mdi:battery");
  bat3CellVoltage1.setUnitOfMeasurement("V");
  bat3CellVoltage2.setIcon("mdi:battery");
  bat3CellVoltage2.setUnitOfMeasurement("V");
  bat3CellVoltage3.setIcon("mdi:battery");
  bat3CellVoltage3.setUnitOfMeasurement("V");
  bat3CellVoltage4.setIcon("mdi:battery");
  bat3CellVoltage4.setUnitOfMeasurement("V");
  bat3CellVoltage5.setIcon("mdi:battery");
  bat3CellVoltage5.setUnitOfMeasurement("V");
  bat3CellVoltage6.setIcon("mdi:battery");
  bat3CellVoltage6.setUnitOfMeasurement("V");

  //Battery 4
  bat4Name.setName("BatteryD4 Name");  
  //bat4Temperature.setName("Battery4 Temperature");  
  bat4BatteryType.setName("BatteryD4 Type");
  bat4BatteryCycles.setName("BatteryD4 Cycles");
  bat4BatteryVoltage.setName("BatteryD4 Voltage");
  bat4CellVoltage1.setName("BatteryD4 Cell Voltage 1");
  bat4CellVoltage2.setName("BatteryD4 Cell Voltage 2");
  bat4CellVoltage3.setName("BatteryD4 Cell Voltage 3");
  bat4CellVoltage4.setName("BatteryD4 Cell Voltage 4");
  bat4CellVoltage5.setName("BatteryD4 Cell Voltage 5");
  bat4CellVoltage6.setName("BatteryD4 Cell Voltage 6");

  bat4Name.setIcon("mdi:battery");
  //bat4Temperature.setIcon("mdi:thermometer");
  //bat4Temperature.setUnitOfMeasurement("°C");
  bat4BatteryType.setIcon("mdi:battery");
  bat4BatteryCycles.setIcon("mdi:battery-sync");
  bat4BatteryVoltage.setIcon("mdi:battery");
  bat4BatteryVoltage.setUnitOfMeasurement("V");
  bat4CellVoltage1.setIcon("mdi:battery");
  bat4CellVoltage1.setUnitOfMeasurement("V");
  bat4CellVoltage2.setIcon("mdi:battery");
  bat4CellVoltage2.setUnitOfMeasurement("V");
  bat4CellVoltage3.setIcon("mdi:battery");
  bat4CellVoltage3.setUnitOfMeasurement("V");
  bat4CellVoltage4.setIcon("mdi:battery");
  bat4CellVoltage4.setUnitOfMeasurement("V");
  bat4CellVoltage5.setIcon("mdi:battery");
  bat4CellVoltage5.setUnitOfMeasurement("V");
  bat4CellVoltage6.setIcon("mdi:battery");
  bat4CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 5
  bat5Name.setName("BatteryE5 Name");  
  //bat5Temperature.setName("Battery5 Temperature");  
  bat5BatteryType.setName("BatteryE5 Type");
  bat5BatteryCycles.setName("BatteryE5 Cycles");
  bat5BatteryVoltage.setName("BatteryE5 Voltage");
  bat5CellVoltage1.setName("BatteryE5 Cell Voltage 1");
  bat5CellVoltage2.setName("BatteryE5 Cell Voltage 2");
  bat5CellVoltage3.setName("BatteryE5 Cell Voltage 3");
  bat5CellVoltage4.setName("BatteryE5 Cell Voltage 4");
  bat5CellVoltage5.setName("BatteryE5 Cell Voltage 5");
  bat5CellVoltage6.setName("BatteryE5 Cell Voltage 6");

  bat5Name.setIcon("mdi:battery");
  //bat5Temperature.setIcon("mdi:thermometer");
  //bat5Temperature.setUnitOfMeasurement("°C");
  bat5BatteryType.setIcon("mdi:battery");
  bat5BatteryCycles.setIcon("mdi:battery-sync");
  bat5BatteryVoltage.setIcon("mdi:battery");
  bat5BatteryVoltage.setUnitOfMeasurement("V");
  bat5CellVoltage1.setIcon("mdi:battery");
  bat5CellVoltage1.setUnitOfMeasurement("V");
  bat5CellVoltage2.setIcon("mdi:battery");
  bat5CellVoltage2.setUnitOfMeasurement("V");
  bat5CellVoltage3.setIcon("mdi:battery");
  bat5CellVoltage3.setUnitOfMeasurement("V");
  bat5CellVoltage4.setIcon("mdi:battery");
  bat5CellVoltage4.setUnitOfMeasurement("V");
  bat5CellVoltage5.setIcon("mdi:battery");
  bat5CellVoltage5.setUnitOfMeasurement("V");
  bat5CellVoltage6.setIcon("mdi:battery");
  bat5CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 6
  bat6Name.setName("BatteryF6 Name");  
  //bat6Temperature.setName("Battery6 Temperature");  
  bat6BatteryType.setName("BatteryF6 Type");
  bat6BatteryCycles.setName("BatteryF6 Cycles");
  bat6BatteryVoltage.setName("BatteryF6 Voltage");
  bat6CellVoltage1.setName("BatteryF6 Cell Voltage 1");
  bat6CellVoltage2.setName("BatteryF6 Cell Voltage 2");
  bat6CellVoltage3.setName("BatteryF6 Cell Voltage 3");
  bat6CellVoltage4.setName("BatteryF6 Cell Voltage 4");
  bat6CellVoltage5.setName("BatteryF6 Cell Voltage 5");
  bat6CellVoltage6.setName("BatteryF6 Cell Voltage 6");

  bat6Name.setIcon("mdi:battery");
  //bat6Temperature.setIcon("mdi:thermometer");
  //bat6Temperature.setUnitOfMeasurement("°C");
  bat6BatteryType.setIcon("mdi:battery");
  bat6BatteryCycles.setIcon("mdi:battery-sync");
  bat6BatteryVoltage.setIcon("mdi:battery");
  bat6BatteryVoltage.setUnitOfMeasurement("V");
  bat6CellVoltage1.setIcon("mdi:battery");
  bat6CellVoltage1.setUnitOfMeasurement("V");
  bat6CellVoltage2.setIcon("mdi:battery");
  bat6CellVoltage2.setUnitOfMeasurement("V");
  bat6CellVoltage3.setIcon("mdi:battery");
  bat6CellVoltage3.setUnitOfMeasurement("V");
  bat6CellVoltage4.setIcon("mdi:battery");
  bat6CellVoltage4.setUnitOfMeasurement("V");
  bat6CellVoltage5.setIcon("mdi:battery");
  bat6CellVoltage5.setUnitOfMeasurement("V");
  bat6CellVoltage6.setIcon("mdi:battery");
  bat6CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 7
  bat7Name.setName("BatteryG7 Name");  
  //bat7Temperature.setName("Battery7 Temperature");  
  bat7BatteryType.setName("BatteryG7 Type");
  bat7BatteryCycles.setName("BatteryG7 Cycles");
  bat7BatteryVoltage.setName("BatteryG7 Voltage");
  bat7CellVoltage1.setName("BatteryG7 Cell Voltage 1");
  bat7CellVoltage2.setName("BatteryG7 Cell Voltage 2");
  bat7CellVoltage3.setName("BatteryG7 Cell Voltage 3");
  bat7CellVoltage4.setName("BatteryG7 Cell Voltage 4");
  bat7CellVoltage5.setName("BatteryG7 Cell Voltage 5");
  bat7CellVoltage6.setName("BatteryG7 Cell Voltage 6");

  bat7Name.setIcon("mdi:battery");
  //bat7Temperature.setIcon("mdi:thermometer");
  //bat7Temperature.setUnitOfMeasurement("°C");
  bat7BatteryType.setIcon("mdi:battery");
  bat7BatteryCycles.setIcon("mdi:battery-sync");
  bat7BatteryVoltage.setIcon("mdi:battery");
  bat7BatteryVoltage.setUnitOfMeasurement("V");
  bat7CellVoltage1.setIcon("mdi:battery");
  bat7CellVoltage1.setUnitOfMeasurement("V");
  bat7CellVoltage2.setIcon("mdi:battery");
  bat7CellVoltage2.setUnitOfMeasurement("V");
  bat7CellVoltage3.setIcon("mdi:battery");
  bat7CellVoltage3.setUnitOfMeasurement("V");
  bat7CellVoltage4.setIcon("mdi:battery");
  bat7CellVoltage4.setUnitOfMeasurement("V");
  bat7CellVoltage5.setIcon("mdi:battery");
  bat7CellVoltage5.setUnitOfMeasurement("V");
  bat7CellVoltage6.setIcon("mdi:battery");
  bat7CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 8
  bat8Name.setName("BatteryH8 Name");  
  //bat8Temperature.setName("Battery8 Temperature");  
  bat8BatteryType.setName("BatteryH8 Type");
  bat8BatteryCycles.setName("BatteryH8 Cycles");
  bat8BatteryVoltage.setName("BatteryH8 Voltage");
  bat8CellVoltage1.setName("BatteryH8 Cell Voltage 1");
  bat8CellVoltage2.setName("BatteryH8 Cell Voltage 2");
  bat8CellVoltage3.setName("BatteryH8 Cell Voltage 3");
  bat8CellVoltage4.setName("BatteryH8 Cell Voltage 4");
  bat8CellVoltage5.setName("BatteryH8 Cell Voltage 5");
  bat8CellVoltage6.setName("BatteryH8 Cell Voltage 6");

  bat8Name.setIcon("mdi:battery");
  //bat8Temperature.setIcon("mdi:thermometer");
  //bat8Temperature.setUnitOfMeasurement("°C");
  bat8BatteryType.setIcon("mdi:battery");
  bat8BatteryCycles.setIcon("mdi:battery-sync");
  bat8BatteryVoltage.setIcon("mdi:battery");
  bat8BatteryVoltage.setUnitOfMeasurement("V");
  bat8CellVoltage1.setIcon("mdi:battery");
  bat8CellVoltage1.setUnitOfMeasurement("V");
  bat8CellVoltage2.setIcon("mdi:battery");
  bat8CellVoltage2.setUnitOfMeasurement("V");
  bat8CellVoltage3.setIcon("mdi:battery");
  bat8CellVoltage3.setUnitOfMeasurement("V");
  bat8CellVoltage4.setIcon("mdi:battery");
  bat8CellVoltage4.setUnitOfMeasurement("V");
  bat8CellVoltage5.setIcon("mdi:battery");
  bat8CellVoltage5.setUnitOfMeasurement("V");
  bat8CellVoltage6.setIcon("mdi:battery");
  bat8CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 9
  bat9Name.setName("BatteryI9 Name");  
  //bat9Temperature.setName("Battery9 Temperature");  
  bat9BatteryType.setName("BatteryI9 Type");
  bat9BatteryCycles.setName("BatteryI9 Cycles");
  bat9BatteryVoltage.setName("BatteryI9 Voltage");
  bat9CellVoltage1.setName("BatteryI9 Cell Voltage 1");
  bat9CellVoltage2.setName("BatteryI9 Cell Voltage 2");
  bat9CellVoltage3.setName("BatteryI9 Cell Voltage 3");
  bat9CellVoltage4.setName("BatteryI9 Cell Voltage 4");
  bat9CellVoltage5.setName("BatteryI9 Cell Voltage 5");
  bat9CellVoltage6.setName("BatteryI9 Cell Voltage 6");

  bat9Name.setIcon("mdi:battery");
  //bat9Temperature.setIcon("mdi:thermometer");
  //bat9Temperature.setUnitOfMeasurement("°C");
  bat9BatteryType.setIcon("mdi:battery");
  bat9BatteryCycles.setIcon("mdi:battery-sync");
  bat9BatteryVoltage.setIcon("mdi:battery");
  bat9BatteryVoltage.setUnitOfMeasurement("V");
  bat9CellVoltage1.setIcon("mdi:battery");
  bat9CellVoltage1.setUnitOfMeasurement("V");
  bat9CellVoltage2.setIcon("mdi:battery");
  bat9CellVoltage2.setUnitOfMeasurement("V");
  bat9CellVoltage3.setIcon("mdi:battery");
  bat9CellVoltage3.setUnitOfMeasurement("V");
  bat9CellVoltage4.setIcon("mdi:battery");
  bat9CellVoltage4.setUnitOfMeasurement("V");
  bat9CellVoltage5.setIcon("mdi:battery");
  bat9CellVoltage5.setUnitOfMeasurement("V");
  bat9CellVoltage6.setIcon("mdi:battery");
  bat9CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 10
  bat10Name.setName("BatteryJ10 Name");  
  //bat10Temperature.setName("Battery10 Temperature");  
  bat10BatteryType.setName("BatteryJ10 Type");
  bat10BatteryCycles.setName("BatteryJ10 Cycles");
  bat10BatteryVoltage.setName("BatteryJ10 Voltage");
  bat10CellVoltage1.setName("BatteryJ10 Cell Voltage 1");
  bat10CellVoltage2.setName("BatteryJ10 Cell Voltage 2");
  bat10CellVoltage3.setName("BatteryJ10 Cell Voltage 3");
  bat10CellVoltage4.setName("BatteryJ10 Cell Voltage 4");
  bat10CellVoltage5.setName("BatteryJ10 Cell Voltage 5");
  bat10CellVoltage6.setName("BatteryJ10 Cell Voltage 6");

  bat10Name.setIcon("mdi:battery");
  //bat10Temperature.setIcon("mdi:thermometer");
  //bat10Temperature.setUnitOfMeasurement("°C");
  bat10BatteryType.setIcon("mdi:battery");
  bat10BatteryCycles.setIcon("mdi:battery-sync");
  bat10BatteryVoltage.setIcon("mdi:battery");
  bat10BatteryVoltage.setUnitOfMeasurement("V");
  bat10CellVoltage1.setIcon("mdi:battery");
  bat10CellVoltage1.setUnitOfMeasurement("V");
  bat10CellVoltage2.setIcon("mdi:battery");
  bat10CellVoltage2.setUnitOfMeasurement("V");
  bat10CellVoltage3.setIcon("mdi:battery");
  bat10CellVoltage3.setUnitOfMeasurement("V");
  bat10CellVoltage4.setIcon("mdi:battery");
  bat10CellVoltage4.setUnitOfMeasurement("V");
  bat10CellVoltage5.setIcon("mdi:battery");
  bat10CellVoltage5.setUnitOfMeasurement("V");
  bat10CellVoltage6.setIcon("mdi:battery");
  bat10CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 11
  bat11Name.setName("BatteryK11 Name");  
  //bat11Temperature.setName("Battery10 Temperature");  
  bat11BatteryType.setName("BatteryK11 Type");
  bat11BatteryCycles.setName("BatteryK11 Cycles");
  bat11BatteryVoltage.setName("BatteryK11 Voltage");
  bat11CellVoltage1.setName("BatteryK11 Cell Voltage 1");
  bat11CellVoltage2.setName("BatteryK11 Cell Voltage 2");
  bat11CellVoltage3.setName("BatteryK11 Cell Voltage 3");
  bat11CellVoltage4.setName("BatteryK11 Cell Voltage 4");
  bat11CellVoltage5.setName("BatteryK11 Cell Voltage 5");
  bat11CellVoltage6.setName("BatteryK11 Cell Voltage 6");

  bat11Name.setIcon("mdi:battery");
  //bat11Temperature.setIcon("mdi:thermometer");
  //bat11Temperature.setUnitOfMeasurement("°C");
  bat11BatteryType.setIcon("mdi:battery");
  bat11BatteryCycles.setIcon("mdi:battery-sync");
  bat11BatteryVoltage.setIcon("mdi:battery");
  bat11BatteryVoltage.setUnitOfMeasurement("V");
  bat11CellVoltage1.setIcon("mdi:battery");
  bat11CellVoltage1.setUnitOfMeasurement("V");
  bat11CellVoltage2.setIcon("mdi:battery");
  bat11CellVoltage2.setUnitOfMeasurement("V");
  bat11CellVoltage3.setIcon("mdi:battery");
  bat11CellVoltage3.setUnitOfMeasurement("V");
  bat11CellVoltage4.setIcon("mdi:battery");
  bat11CellVoltage4.setUnitOfMeasurement("V");
  bat11CellVoltage5.setIcon("mdi:battery");
  bat11CellVoltage5.setUnitOfMeasurement("V");
  bat11CellVoltage6.setIcon("mdi:battery");
  bat11CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 12
  bat12Name.setName("BatteryL12 Name");  
  //bat12Temperature.setName("Battery10 Temperature");  
  bat12BatteryType.setName("BatteryL12 Type");
  bat12BatteryCycles.setName("BatteryL12 Cycles");
  bat12BatteryVoltage.setName("BatteryL12 Voltage");
  bat12CellVoltage1.setName("BatteryL12 Cell Voltage 1");
  bat12CellVoltage2.setName("BatteryL12 Cell Voltage 2");
  bat12CellVoltage3.setName("BatteryL12 Cell Voltage 3");
  bat12CellVoltage4.setName("BatteryL12 Cell Voltage 4");
  bat12CellVoltage5.setName("BatteryL12 Cell Voltage 5");
  bat12CellVoltage6.setName("BatteryL12 Cell Voltage 6");

  bat12Name.setIcon("mdi:battery");
  //bat12Temperature.setIcon("mdi:thermometer");
  //bat12Temperature.setUnitOfMeasurement("°C");
  bat12BatteryType.setIcon("mdi:battery");
  bat12BatteryCycles.setIcon("mdi:battery-sync");
  bat12BatteryVoltage.setIcon("mdi:battery");
  bat12BatteryVoltage.setUnitOfMeasurement("V");
  bat12CellVoltage1.setIcon("mdi:battery");
  bat12CellVoltage1.setUnitOfMeasurement("V");
  bat12CellVoltage2.setIcon("mdi:battery");
  bat12CellVoltage2.setUnitOfMeasurement("V");
  bat12CellVoltage3.setIcon("mdi:battery");
  bat12CellVoltage3.setUnitOfMeasurement("V");
  bat12CellVoltage4.setIcon("mdi:battery");
  bat12CellVoltage4.setUnitOfMeasurement("V");
  bat12CellVoltage5.setIcon("mdi:battery");
  bat12CellVoltage5.setUnitOfMeasurement("V");
  bat12CellVoltage6.setIcon("mdi:battery");
  bat12CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 13
  bat13Name.setName("BatteryM13 Name");  
  //bat13Temperature.setName("Battery10 Temperature");  
  bat13BatteryType.setName("BatteryM13 Type");
  bat13BatteryCycles.setName("BatteryM13 Cycles");
  bat13BatteryVoltage.setName("BatteryM13 Voltage");
  bat13CellVoltage1.setName("BatteryM13 Cell Voltage 1");
  bat13CellVoltage2.setName("BatteryM13 Cell Voltage 2");
  bat13CellVoltage3.setName("BatteryM13 Cell Voltage 3");
  bat13CellVoltage4.setName("BatteryM13 Cell Voltage 4");
  bat13CellVoltage5.setName("BatteryM13 Cell Voltage 5");
  bat13CellVoltage6.setName("BatteryM13 Cell Voltage 6");

  bat13Name.setIcon("mdi:battery");
  //bat13Temperature.setIcon("mdi:thermometer");
  //bat13Temperature.setUnitOfMeasurement("°C");
  bat13BatteryType.setIcon("mdi:battery");
  bat13BatteryCycles.setIcon("mdi:battery-sync");
  bat13BatteryVoltage.setIcon("mdi:battery");
  bat13BatteryVoltage.setUnitOfMeasurement("V");
  bat13CellVoltage1.setIcon("mdi:battery");
  bat13CellVoltage1.setUnitOfMeasurement("V");
  bat13CellVoltage2.setIcon("mdi:battery");
  bat13CellVoltage2.setUnitOfMeasurement("V");
  bat13CellVoltage3.setIcon("mdi:battery");
  bat13CellVoltage3.setUnitOfMeasurement("V");
  bat13CellVoltage4.setIcon("mdi:battery");
  bat13CellVoltage4.setUnitOfMeasurement("V");
  bat13CellVoltage5.setIcon("mdi:battery");
  bat13CellVoltage5.setUnitOfMeasurement("V");
  bat13CellVoltage6.setIcon("mdi:battery");
  bat13CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 14
  bat14Name.setName("BatteryN14 Name");  
  //bat14Temperature.setName("Battery10 Temperature");  
  bat14BatteryType.setName("BatteryN14 Type");
  bat14BatteryCycles.setName("BatteryN14 Cycles");
  bat14BatteryVoltage.setName("BatteryN14 Voltage");
  bat14CellVoltage1.setName("BatteryN14 Cell Voltage 1");
  bat14CellVoltage2.setName("BatteryN14 Cell Voltage 2");
  bat14CellVoltage3.setName("BatteryN14 Cell Voltage 3");
  bat14CellVoltage4.setName("BatteryN14 Cell Voltage 4");
  bat14CellVoltage5.setName("BatteryN14 Cell Voltage 5");
  bat14CellVoltage6.setName("BatteryN14 Cell Voltage 6");

  bat14Name.setIcon("mdi:battery");
  //bat14Temperature.setIcon("mdi:thermometer");
  //bat14Temperature.setUnitOfMeasurement("°C");
  bat14BatteryType.setIcon("mdi:battery");
  bat14BatteryCycles.setIcon("mdi:battery-sync");
  bat14BatteryVoltage.setIcon("mdi:battery");
  bat14BatteryVoltage.setUnitOfMeasurement("V");
  bat14CellVoltage1.setIcon("mdi:battery");
  bat14CellVoltage1.setUnitOfMeasurement("V");
  bat14CellVoltage2.setIcon("mdi:battery");
  bat14CellVoltage2.setUnitOfMeasurement("V");
  bat14CellVoltage3.setIcon("mdi:battery");
  bat14CellVoltage3.setUnitOfMeasurement("V");
  bat14CellVoltage4.setIcon("mdi:battery");
  bat14CellVoltage4.setUnitOfMeasurement("V");
  bat14CellVoltage5.setIcon("mdi:battery");
  bat14CellVoltage5.setUnitOfMeasurement("V");
  bat14CellVoltage6.setIcon("mdi:battery");
  bat14CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 15
  bat15Name.setName("BatteryO15 Name");  
  //bat15Temperature.setName("Battery10 Temperature");  
  bat15BatteryType.setName("BatteryO15 Type");
  bat15BatteryCycles.setName("BatteryO15 Cycles");
  bat15BatteryVoltage.setName("BatteryO15 Voltage");
  bat15CellVoltage1.setName("BatteryO15 Cell Voltage 1");
  bat15CellVoltage2.setName("BatteryO15 Cell Voltage 2");
  bat15CellVoltage3.setName("BatteryO15 Cell Voltage 3");
  bat15CellVoltage4.setName("BatteryO15 Cell Voltage 4");
  bat15CellVoltage5.setName("BatteryO15 Cell Voltage 5");
  bat15CellVoltage6.setName("BatteryO15 Cell Voltage 6");

  bat15Name.setIcon("mdi:battery");
  //bat15Temperature.setIcon("mdi:thermometer");
  //bat15Temperature.setUnitOfMeasurement("°C");
  bat15BatteryType.setIcon("mdi:battery");
  bat15BatteryCycles.setIcon("mdi:battery-sync");
  bat15BatteryVoltage.setIcon("mdi:battery");
  bat15BatteryVoltage.setUnitOfMeasurement("V");
  bat15CellVoltage1.setIcon("mdi:battery");
  bat15CellVoltage1.setUnitOfMeasurement("V");
  bat15CellVoltage2.setIcon("mdi:battery");
  bat15CellVoltage2.setUnitOfMeasurement("V");
  bat15CellVoltage3.setIcon("mdi:battery");
  bat15CellVoltage3.setUnitOfMeasurement("V");
  bat15CellVoltage4.setIcon("mdi:battery");
  bat15CellVoltage4.setUnitOfMeasurement("V");
  bat15CellVoltage5.setIcon("mdi:battery");
  bat15CellVoltage5.setUnitOfMeasurement("V");
  bat15CellVoltage6.setIcon("mdi:battery");
  bat15CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 16
  bat16Name.setName("BatteryP16 Name");  
  //bat16Temperature.setName("Battery10 Temperature");  
  bat16BatteryType.setName("BatteryP16 Type");
  bat16BatteryCycles.setName("BatteryP16 Cycles");
  bat16BatteryVoltage.setName("BatteryP16 Voltage");
  bat16CellVoltage1.setName("BatteryP16 Cell Voltage 1");
  bat16CellVoltage2.setName("BatteryP16 Cell Voltage 2");
  bat16CellVoltage3.setName("BatteryP16 Cell Voltage 3");
  bat16CellVoltage4.setName("BatteryP16 Cell Voltage 4");
  bat16CellVoltage5.setName("BatteryP16 Cell Voltage 5");
  bat16CellVoltage6.setName("BatteryP16 Cell Voltage 6");

  bat16Name.setIcon("mdi:battery");
  //bat16Temperature.setIcon("mdi:thermometer");
  //bat16Temperature.setUnitOfMeasurement("°C");
  bat16BatteryType.setIcon("mdi:battery");
  bat16BatteryCycles.setIcon("mdi:battery-sync");
  bat16BatteryVoltage.setIcon("mdi:battery");
  bat16BatteryVoltage.setUnitOfMeasurement("V");
  bat16CellVoltage1.setIcon("mdi:battery");
  bat16CellVoltage1.setUnitOfMeasurement("V");
  bat16CellVoltage2.setIcon("mdi:battery");
  bat16CellVoltage2.setUnitOfMeasurement("V");
  bat16CellVoltage3.setIcon("mdi:battery");
  bat16CellVoltage3.setUnitOfMeasurement("V");
  bat16CellVoltage4.setIcon("mdi:battery");
  bat16CellVoltage4.setUnitOfMeasurement("V");
  bat16CellVoltage5.setIcon("mdi:battery");
  bat16CellVoltage5.setUnitOfMeasurement("V");
  bat16CellVoltage6.setIcon("mdi:battery");
  bat16CellVoltage6.setUnitOfMeasurement("V");
  
  
  //Battery 17
  bat17Name.setName("BatteryQ17 Name");  
  //bat17Temperature.setName("Battery10 Temperature");  
  bat17BatteryType.setName("BatteryQ17 Type");
  bat17BatteryCycles.setName("BatteryQ17 Cycles");
  bat17BatteryVoltage.setName("BatteryQ17 Voltage");
  bat17CellVoltage1.setName("BatteryQ17 Cell Voltage 1");
  bat17CellVoltage2.setName("BatteryQ17 Cell Voltage 2");
  bat17CellVoltage3.setName("BatteryQ17 Cell Voltage 3");
  bat17CellVoltage4.setName("BatteryQ17 Cell Voltage 4");
  bat17CellVoltage5.setName("BatteryQ17 Cell Voltage 5");
  bat17CellVoltage6.setName("BatteryQ17 Cell Voltage 6");

  bat17Name.setIcon("mdi:battery");
  //bat17Temperature.setIcon("mdi:thermometer");
  //bat17Temperature.setUnitOfMeasurement("°C");
  bat17BatteryType.setIcon("mdi:battery");
  bat17BatteryCycles.setIcon("mdi:battery-sync");
  bat17BatteryVoltage.setIcon("mdi:battery");
  bat17BatteryVoltage.setUnitOfMeasurement("V");
  bat17CellVoltage1.setIcon("mdi:battery");
  bat17CellVoltage1.setUnitOfMeasurement("V");
  bat17CellVoltage2.setIcon("mdi:battery");
  bat17CellVoltage2.setUnitOfMeasurement("V");
  bat17CellVoltage3.setIcon("mdi:battery");
  bat17CellVoltage3.setUnitOfMeasurement("V");
  bat17CellVoltage4.setIcon("mdi:battery");
  bat17CellVoltage4.setUnitOfMeasurement("V");
  bat17CellVoltage5.setIcon("mdi:battery");
  bat17CellVoltage5.setUnitOfMeasurement("V");
  bat17CellVoltage6.setIcon("mdi:battery");
  bat17CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 18
  bat18Name.setName("BatteryR18 Name");  
  //bat18Temperature.setName("Battery10 Temperature");  
  bat18BatteryType.setName("BatteryR18 Type");
  bat18BatteryCycles.setName("BatteryR18 Cycles");
  bat18BatteryVoltage.setName("BatteryR18 Voltage");
  bat18CellVoltage1.setName("BatteryR18 Cell Voltage 1");
  bat18CellVoltage2.setName("BatteryR18 Cell Voltage 2");
  bat18CellVoltage3.setName("BatteryR18 Cell Voltage 3");
  bat18CellVoltage4.setName("BatteryR18 Cell Voltage 4");
  bat18CellVoltage5.setName("BatteryR18 Cell Voltage 5");
  bat18CellVoltage6.setName("BatteryR18 Cell Voltage 6");

  bat18Name.setIcon("mdi:battery");
  //bat18Temperature.setIcon("mdi:thermometer");
  //bat18Temperature.setUnitOfMeasurement("°C");
  bat18BatteryType.setIcon("mdi:battery");
  bat18BatteryCycles.setIcon("mdi:battery-sync");
  bat18BatteryVoltage.setIcon("mdi:battery");
  bat18BatteryVoltage.setUnitOfMeasurement("V");
  bat18CellVoltage1.setIcon("mdi:battery");
  bat18CellVoltage1.setUnitOfMeasurement("V");
  bat18CellVoltage2.setIcon("mdi:battery");
  bat18CellVoltage2.setUnitOfMeasurement("V");
  bat18CellVoltage3.setIcon("mdi:battery");
  bat18CellVoltage3.setUnitOfMeasurement("V");
  bat18CellVoltage4.setIcon("mdi:battery");
  bat18CellVoltage4.setUnitOfMeasurement("V");
  bat18CellVoltage5.setIcon("mdi:battery");
  bat18CellVoltage5.setUnitOfMeasurement("V");
  bat18CellVoltage6.setIcon("mdi:battery");
  bat18CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 19
  bat19Name.setName("BatteryS19 Name");  
  //bat19Temperature.setName("Battery10 Temperature");  
  bat19BatteryType.setName("BatteryS19 Type");
  bat19BatteryCycles.setName("BatteryS19 Cycles");
  bat19BatteryVoltage.setName("BatteryS19 Voltage");
  bat19CellVoltage1.setName("BatteryS19 Cell Voltage 1");
  bat19CellVoltage2.setName("BatteryS19 Cell Voltage 2");
  bat19CellVoltage3.setName("BatteryS19 Cell Voltage 3");
  bat19CellVoltage4.setName("BatteryS19 Cell Voltage 4");
  bat19CellVoltage5.setName("BatteryS19 Cell Voltage 5");
  bat19CellVoltage6.setName("BatteryS19 Cell Voltage 6");

  bat19Name.setIcon("mdi:battery");
  //bat19Temperature.setIcon("mdi:thermometer");
  //bat19Temperature.setUnitOfMeasurement("°C");
  bat19BatteryType.setIcon("mdi:battery");
  bat19BatteryCycles.setIcon("mdi:battery-sync");
  bat19BatteryVoltage.setIcon("mdi:battery");
  bat19BatteryVoltage.setUnitOfMeasurement("V");
  bat19CellVoltage1.setIcon("mdi:battery");
  bat19CellVoltage1.setUnitOfMeasurement("V");
  bat19CellVoltage2.setIcon("mdi:battery");
  bat19CellVoltage2.setUnitOfMeasurement("V");
  bat19CellVoltage3.setIcon("mdi:battery");
  bat19CellVoltage3.setUnitOfMeasurement("V");
  bat19CellVoltage4.setIcon("mdi:battery");
  bat19CellVoltage4.setUnitOfMeasurement("V");
  bat19CellVoltage5.setIcon("mdi:battery");
  bat19CellVoltage5.setUnitOfMeasurement("V");
  bat19CellVoltage6.setIcon("mdi:battery");
  bat19CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 20
  bat20Name.setName("BatteryT20 Name");  
  //bat20Temperature.setName("Battery10 Temperature");  
  bat20BatteryType.setName("BatteryT20 Type");
  bat20BatteryCycles.setName("BatteryT20 Cycles");
  bat20BatteryVoltage.setName("BatteryT20 Voltage");
  bat20CellVoltage1.setName("BatteryT20 Cell Voltage 1");
  bat20CellVoltage2.setName("BatteryT20 Cell Voltage 2");
  bat20CellVoltage3.setName("BatteryT20 Cell Voltage 3");
  bat20CellVoltage4.setName("BatteryT20 Cell Voltage 4");
  bat20CellVoltage5.setName("BatteryT20 Cell Voltage 5");
  bat20CellVoltage6.setName("BatteryT20 Cell Voltage 6");

  bat20Name.setIcon("mdi:battery");
  //bat20Temperature.setIcon("mdi:thermometer");
  //bat20Temperature.setUnitOfMeasurement("°C");
  bat20BatteryType.setIcon("mdi:battery");
  bat20BatteryCycles.setIcon("mdi:battery-sync");
  bat20BatteryVoltage.setIcon("mdi:battery");
  bat20BatteryVoltage.setUnitOfMeasurement("V");
  bat20CellVoltage1.setIcon("mdi:battery");
  bat20CellVoltage1.setUnitOfMeasurement("V");
  bat20CellVoltage2.setIcon("mdi:battery");
  bat20CellVoltage2.setUnitOfMeasurement("V");
  bat20CellVoltage3.setIcon("mdi:battery");
  bat20CellVoltage3.setUnitOfMeasurement("V");
  bat20CellVoltage4.setIcon("mdi:battery");
  bat20CellVoltage4.setUnitOfMeasurement("V");
  bat20CellVoltage5.setIcon("mdi:battery");
  bat20CellVoltage5.setUnitOfMeasurement("V");
  bat20CellVoltage6.setIcon("mdi:battery");
  bat20CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 21
  bat21Name.setName("BatteryU21 Name");  
  //bat21Temperature.setName("Battery10 Temperature");  
  bat21BatteryType.setName("BatteryU21 Type");
  bat21BatteryCycles.setName("BatteryU21 Cycles");
  bat21BatteryVoltage.setName("BatteryU21 Voltage");
  bat21CellVoltage1.setName("BatteryU21 Cell Voltage 1");
  bat21CellVoltage2.setName("BatteryU21 Cell Voltage 2");
  bat21CellVoltage3.setName("BatteryU21 Cell Voltage 3");
  bat21CellVoltage4.setName("BatteryU21 Cell Voltage 4");
  bat21CellVoltage5.setName("BatteryU21 Cell Voltage 5");
  bat21CellVoltage6.setName("BatteryU21 Cell Voltage 6");

  bat21Name.setIcon("mdi:battery");
  //bat21Temperature.setIcon("mdi:thermometer");
  //bat21Temperature.setUnitOfMeasurement("°C");
  bat21BatteryType.setIcon("mdi:battery");
  bat21BatteryCycles.setIcon("mdi:battery-sync");
  bat21BatteryVoltage.setIcon("mdi:battery");
  bat21BatteryVoltage.setUnitOfMeasurement("V");
  bat21CellVoltage1.setIcon("mdi:battery");
  bat21CellVoltage1.setUnitOfMeasurement("V");
  bat21CellVoltage2.setIcon("mdi:battery");
  bat21CellVoltage2.setUnitOfMeasurement("V");
  bat21CellVoltage3.setIcon("mdi:battery");
  bat21CellVoltage3.setUnitOfMeasurement("V");
  bat21CellVoltage4.setIcon("mdi:battery");
  bat21CellVoltage4.setUnitOfMeasurement("V");
  bat21CellVoltage5.setIcon("mdi:battery");
  bat21CellVoltage5.setUnitOfMeasurement("V");
  bat21CellVoltage6.setIcon("mdi:battery");
  bat21CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 22
  bat22Name.setName("BatteryV22 Name");  
  //bat22Temperature.setName("Battery10 Temperature");  
  bat22BatteryType.setName("BatteryV22 Type");
  bat22BatteryCycles.setName("BatteryV22 Cycles");
  bat22BatteryVoltage.setName("BatteryV22 Voltage");
  bat22CellVoltage1.setName("BatteryV22 Cell Voltage 1");
  bat22CellVoltage2.setName("BatteryV22 Cell Voltage 2");
  bat22CellVoltage3.setName("BatteryV22 Cell Voltage 3");
  bat22CellVoltage4.setName("BatteryV22 Cell Voltage 4");
  bat22CellVoltage5.setName("BatteryV22 Cell Voltage 5");
  bat22CellVoltage6.setName("BatteryV22 Cell Voltage 6");

  bat22Name.setIcon("mdi:battery");
  //bat22Temperature.setIcon("mdi:thermometer");
  //bat22Temperature.setUnitOfMeasurement("°C");
  bat22BatteryType.setIcon("mdi:battery");
  bat22BatteryCycles.setIcon("mdi:battery-sync");
  bat22BatteryVoltage.setIcon("mdi:battery");
  bat22BatteryVoltage.setUnitOfMeasurement("V");
  bat22CellVoltage1.setIcon("mdi:battery");
  bat22CellVoltage1.setUnitOfMeasurement("V");
  bat22CellVoltage2.setIcon("mdi:battery");
  bat22CellVoltage2.setUnitOfMeasurement("V");
  bat22CellVoltage3.setIcon("mdi:battery");
  bat22CellVoltage3.setUnitOfMeasurement("V");
  bat22CellVoltage4.setIcon("mdi:battery");
  bat22CellVoltage4.setUnitOfMeasurement("V");
  bat22CellVoltage5.setIcon("mdi:battery");
  bat22CellVoltage5.setUnitOfMeasurement("V");
  bat22CellVoltage6.setIcon("mdi:battery");
  bat22CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 23
  bat23Name.setName("BatteryW23 Name");  
  //bat23Temperature.setName("Battery10 Temperature");  
  bat23BatteryType.setName("BatteryW23 Type");
  bat23BatteryCycles.setName("BatteryW23 Cycles");
  bat23BatteryVoltage.setName("BatteryW23 Voltage");
  bat23CellVoltage1.setName("BatteryW23 Cell Voltage 1");
  bat23CellVoltage2.setName("BatteryW23 Cell Voltage 2");
  bat23CellVoltage3.setName("BatteryW23 Cell Voltage 3");
  bat23CellVoltage4.setName("BatteryW23 Cell Voltage 4");
  bat23CellVoltage5.setName("BatteryW23 Cell Voltage 5");
  bat23CellVoltage6.setName("BatteryW23 Cell Voltage 6");

  bat23Name.setIcon("mdi:battery");
  //bat23Temperature.setIcon("mdi:thermometer");
  //bat23Temperature.setUnitOfMeasurement("°C");
  bat23BatteryType.setIcon("mdi:battery");
  bat23BatteryCycles.setIcon("mdi:battery-sync");
  bat23BatteryVoltage.setIcon("mdi:battery");
  bat23BatteryVoltage.setUnitOfMeasurement("V");
  bat23CellVoltage1.setIcon("mdi:battery");
  bat23CellVoltage1.setUnitOfMeasurement("V");
  bat23CellVoltage2.setIcon("mdi:battery");
  bat23CellVoltage2.setUnitOfMeasurement("V");
  bat23CellVoltage3.setIcon("mdi:battery");
  bat23CellVoltage3.setUnitOfMeasurement("V");
  bat23CellVoltage4.setIcon("mdi:battery");
  bat23CellVoltage4.setUnitOfMeasurement("V");
  bat23CellVoltage5.setIcon("mdi:battery");
  bat23CellVoltage5.setUnitOfMeasurement("V");
  bat23CellVoltage6.setIcon("mdi:battery");
  bat23CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 24
  bat24Name.setName("BatteryX24 Name");  
  //bat24Temperature.setName("Battery10 Temperature");  
  bat24BatteryType.setName("BatteryX24 Type");
  bat24BatteryCycles.setName("BatteryX24 Cycles");
  bat24BatteryVoltage.setName("BatteryX24 Voltage");
  bat24CellVoltage1.setName("BatteryX24 Cell Voltage 1");
  bat24CellVoltage2.setName("BatteryX24 Cell Voltage 2");
  bat24CellVoltage3.setName("BatteryX24 Cell Voltage 3");
  bat24CellVoltage4.setName("BatteryX24 Cell Voltage 4");
  bat24CellVoltage5.setName("BatteryX24 Cell Voltage 5");
  bat24CellVoltage6.setName("BatteryX24 Cell Voltage 6");

  bat24Name.setIcon("mdi:battery");
  //bat24Temperature.setIcon("mdi:thermometer");
  //bat24Temperature.setUnitOfMeasurement("°C");
  bat24BatteryType.setIcon("mdi:battery");
  bat24BatteryCycles.setIcon("mdi:battery-sync");
  bat24BatteryVoltage.setIcon("mdi:battery");
  bat24BatteryVoltage.setUnitOfMeasurement("V");
  bat24CellVoltage1.setIcon("mdi:battery");
  bat24CellVoltage1.setUnitOfMeasurement("V");
  bat24CellVoltage2.setIcon("mdi:battery");
  bat24CellVoltage2.setUnitOfMeasurement("V");
  bat24CellVoltage3.setIcon("mdi:battery");
  bat24CellVoltage3.setUnitOfMeasurement("V");
  bat24CellVoltage4.setIcon("mdi:battery");
  bat24CellVoltage4.setUnitOfMeasurement("V");
  bat24CellVoltage5.setIcon("mdi:battery");
  bat24CellVoltage5.setUnitOfMeasurement("V");
  bat24CellVoltage6.setIcon("mdi:battery");
  bat24CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 25
  bat25Name.setName("BatteryY25 Name");  
  //bat25Temperature.setName("Battery10 Temperature");  
  bat25BatteryType.setName("BatteryY25 Type");
  bat25BatteryCycles.setName("BatteryY25 Cycles");
  bat25BatteryVoltage.setName("BatteryY25 Voltage");
  bat25CellVoltage1.setName("BatteryY25 Cell Voltage 1");
  bat25CellVoltage2.setName("BatteryY25 Cell Voltage 2");
  bat25CellVoltage3.setName("BatteryY25 Cell Voltage 3");
  bat25CellVoltage4.setName("BatteryY25 Cell Voltage 4");
  bat25CellVoltage5.setName("BatteryY25 Cell Voltage 5");
  bat25CellVoltage6.setName("BatteryY25 Cell Voltage 6");

  bat25Name.setIcon("mdi:battery");
  //bat25Temperature.setIcon("mdi:thermometer");
  //bat25Temperature.setUnitOfMeasurement("°C");
  bat25BatteryType.setIcon("mdi:battery");
  bat25BatteryCycles.setIcon("mdi:battery-sync");
  bat25BatteryVoltage.setIcon("mdi:battery");
  bat25BatteryVoltage.setUnitOfMeasurement("V");
  bat25CellVoltage1.setIcon("mdi:battery");
  bat25CellVoltage1.setUnitOfMeasurement("V");
  bat25CellVoltage2.setIcon("mdi:battery");
  bat25CellVoltage2.setUnitOfMeasurement("V");
  bat25CellVoltage3.setIcon("mdi:battery");
  bat25CellVoltage3.setUnitOfMeasurement("V");
  bat25CellVoltage4.setIcon("mdi:battery");
  bat25CellVoltage4.setUnitOfMeasurement("V");
  bat25CellVoltage5.setIcon("mdi:battery");
  bat25CellVoltage5.setUnitOfMeasurement("V");
  bat25CellVoltage6.setIcon("mdi:battery");
  bat25CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 26
  bat26Name.setName("BatteryZ26 Name");  
  //bat26Temperature.setName("Battery10 Temperature");  
  bat26BatteryType.setName("BatteryZ26 Type");
  bat26BatteryCycles.setName("BatteryZ26 Cycles");
  bat26BatteryVoltage.setName("BatteryZ26 Voltage");
  bat26CellVoltage1.setName("BatteryZ26 Cell Voltage 1");
  bat26CellVoltage2.setName("BatteryZ26 Cell Voltage 2");
  bat26CellVoltage3.setName("BatteryZ26 Cell Voltage 3");
  bat26CellVoltage4.setName("BatteryZ26 Cell Voltage 4");
  bat26CellVoltage5.setName("BatteryZ26 Cell Voltage 5");
  bat26CellVoltage6.setName("BatteryZ26 Cell Voltage 6");

  bat26Name.setIcon("mdi:battery");
  //bat26Temperature.setIcon("mdi:thermometer");
  //bat26Temperature.setUnitOfMeasurement("°C");
  bat26BatteryType.setIcon("mdi:battery");
  bat26BatteryCycles.setIcon("mdi:battery-sync");
  bat26BatteryVoltage.setIcon("mdi:battery");
  bat26BatteryVoltage.setUnitOfMeasurement("V");
  bat26CellVoltage1.setIcon("mdi:battery");
  bat26CellVoltage1.setUnitOfMeasurement("V");
  bat26CellVoltage2.setIcon("mdi:battery");
  bat26CellVoltage2.setUnitOfMeasurement("V");
  bat26CellVoltage3.setIcon("mdi:battery");
  bat26CellVoltage3.setUnitOfMeasurement("V");
  bat26CellVoltage4.setIcon("mdi:battery");
  bat26CellVoltage4.setUnitOfMeasurement("V");
  bat26CellVoltage5.setIcon("mdi:battery");
  bat26CellVoltage5.setUnitOfMeasurement("V");
  bat26CellVoltage6.setIcon("mdi:battery");
  bat26CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 27
  bat27Name.setName("BatteryZA27 Name");  
  //bat27Temperature.setName("Battery10 Temperature");  
  bat27BatteryType.setName("BatteryZA27 Type");
  bat27BatteryCycles.setName("BatteryZA27 Cycles");
  bat27BatteryVoltage.setName("BatteryZA27 Voltage");
  bat27CellVoltage1.setName("BatteryZA27 Cell Voltage 1");
  bat27CellVoltage2.setName("BatteryZA27 Cell Voltage 2");
  bat27CellVoltage3.setName("BatteryZA27 Cell Voltage 3");
  bat27CellVoltage4.setName("BatteryZA27 Cell Voltage 4");
  bat27CellVoltage5.setName("BatteryZA27 Cell Voltage 5");
  bat27CellVoltage6.setName("BatteryZA27 Cell Voltage 6");

  bat27Name.setIcon("mdi:battery");
  //bat27Temperature.setIcon("mdi:thermometer");
  //bat27Temperature.setUnitOfMeasurement("°C");
  bat27BatteryType.setIcon("mdi:battery");
  bat27BatteryCycles.setIcon("mdi:battery-sync");
  bat27BatteryVoltage.setIcon("mdi:battery");
  bat27BatteryVoltage.setUnitOfMeasurement("V");
  bat27CellVoltage1.setIcon("mdi:battery");
  bat27CellVoltage1.setUnitOfMeasurement("V");
  bat27CellVoltage2.setIcon("mdi:battery");
  bat27CellVoltage2.setUnitOfMeasurement("V");
  bat27CellVoltage3.setIcon("mdi:battery");
  bat27CellVoltage3.setUnitOfMeasurement("V");
  bat27CellVoltage4.setIcon("mdi:battery");
  bat27CellVoltage4.setUnitOfMeasurement("V");
  bat27CellVoltage5.setIcon("mdi:battery");
  bat27CellVoltage5.setUnitOfMeasurement("V");
  bat27CellVoltage6.setIcon("mdi:battery");
  bat27CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 28
  bat28Name.setName("BatteryZB28 Name");  
  //bat28Temperature.setName("Battery10 Temperature");  
  bat28BatteryType.setName("BatteryZB28 Type");
  bat28BatteryCycles.setName("BatteryZB28 Cycles");
  bat28BatteryVoltage.setName("BatteryZB28 Voltage");
  bat28CellVoltage1.setName("BatteryZB28 Cell Voltage 1");
  bat28CellVoltage2.setName("BatteryZB28 Cell Voltage 2");
  bat28CellVoltage3.setName("BatteryZB28 Cell Voltage 3");
  bat28CellVoltage4.setName("BatteryZB28 Cell Voltage 4");
  bat28CellVoltage5.setName("BatteryZB28 Cell Voltage 5");
  bat28CellVoltage6.setName("BatteryZB28 Cell Voltage 6");

  bat28Name.setIcon("mdi:battery");
  //bat28Temperature.setIcon("mdi:thermometer");
  //bat28Temperature.setUnitOfMeasurement("°C");
  bat28BatteryType.setIcon("mdi:battery");
  bat28BatteryCycles.setIcon("mdi:battery-sync");
  bat28BatteryVoltage.setIcon("mdi:battery");
  bat28BatteryVoltage.setUnitOfMeasurement("V");
  bat28CellVoltage1.setIcon("mdi:battery");
  bat28CellVoltage1.setUnitOfMeasurement("V");
  bat28CellVoltage2.setIcon("mdi:battery");
  bat28CellVoltage2.setUnitOfMeasurement("V");
  bat28CellVoltage3.setIcon("mdi:battery");
  bat28CellVoltage3.setUnitOfMeasurement("V");
  bat28CellVoltage4.setIcon("mdi:battery");
  bat28CellVoltage4.setUnitOfMeasurement("V");
  bat28CellVoltage5.setIcon("mdi:battery");
  bat28CellVoltage5.setUnitOfMeasurement("V");
  bat28CellVoltage6.setIcon("mdi:battery");
  bat28CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 29
  bat29Name.setName("BatteryZC29 Name");  
  //bat29Temperature.setName("Battery10 Temperature");  
  bat29BatteryType.setName("BatteryZC29 Type");
  bat29BatteryCycles.setName("BatteryZC29 Cycles");
  bat29BatteryVoltage.setName("BatteryZC29 Voltage");
  bat29CellVoltage1.setName("BatteryZC29 Cell Voltage 1");
  bat29CellVoltage2.setName("BatteryZC29 Cell Voltage 2");
  bat29CellVoltage3.setName("BatteryZC29 Cell Voltage 3");
  bat29CellVoltage4.setName("BatteryZC29 Cell Voltage 4");
  bat29CellVoltage5.setName("BatteryZC29 Cell Voltage 5");
  bat29CellVoltage6.setName("BatteryZC29 Cell Voltage 6");

  bat29Name.setIcon("mdi:battery");
  //bat29Temperature.setIcon("mdi:thermometer");
  //bat29Temperature.setUnitOfMeasurement("°C");
  bat29BatteryType.setIcon("mdi:battery");
  bat29BatteryCycles.setIcon("mdi:battery-sync");
  bat29BatteryVoltage.setIcon("mdi:battery");
  bat29BatteryVoltage.setUnitOfMeasurement("V");
  bat29CellVoltage1.setIcon("mdi:battery");
  bat29CellVoltage1.setUnitOfMeasurement("V");
  bat29CellVoltage2.setIcon("mdi:battery");
  bat29CellVoltage2.setUnitOfMeasurement("V");
  bat29CellVoltage3.setIcon("mdi:battery");
  bat29CellVoltage3.setUnitOfMeasurement("V");
  bat29CellVoltage4.setIcon("mdi:battery");
  bat29CellVoltage4.setUnitOfMeasurement("V");
  bat29CellVoltage5.setIcon("mdi:battery");
  bat29CellVoltage5.setUnitOfMeasurement("V");
  bat29CellVoltage6.setIcon("mdi:battery");
  bat29CellVoltage6.setUnitOfMeasurement("V");
  
  //Battery 30
  bat30Name.setName("BatteryZD30 Name");  
  //bat30Temperature.setName("Battery10 Temperature");  
  bat30BatteryType.setName("BatteryZD30 Type");
  bat30BatteryCycles.setName("BatteryZD30 Cycles");
  bat30BatteryVoltage.setName("BatteryZD30 Voltage");
  bat30CellVoltage1.setName("BatteryZD30 Cell Voltage 1");
  bat30CellVoltage2.setName("BatteryZD30 Cell Voltage 2");
  bat30CellVoltage3.setName("BatteryZD30 Cell Voltage 3");
  bat30CellVoltage4.setName("BatteryZD30 Cell Voltage 4");
  bat30CellVoltage5.setName("BatteryZD30 Cell Voltage 5");
  bat30CellVoltage6.setName("BatteryZD30 Cell Voltage 6");

  bat30Name.setIcon("mdi:battery");
  //bat30Temperature.setIcon("mdi:thermometer");
  //bat30Temperature.setUnitOfMeasurement("°C");
  bat30BatteryType.setIcon("mdi:battery");
  bat30BatteryCycles.setIcon("mdi:battery-sync");
  bat30BatteryVoltage.setIcon("mdi:battery");
  bat30BatteryVoltage.setUnitOfMeasurement("V");
  bat30CellVoltage1.setIcon("mdi:battery");
  bat30CellVoltage1.setUnitOfMeasurement("V");
  bat30CellVoltage2.setIcon("mdi:battery");
  bat30CellVoltage2.setUnitOfMeasurement("V");
  bat30CellVoltage3.setIcon("mdi:battery");
  bat30CellVoltage3.setUnitOfMeasurement("V");
  bat30CellVoltage4.setIcon("mdi:battery");
  bat30CellVoltage4.setUnitOfMeasurement("V");
  bat30CellVoltage5.setIcon("mdi:battery");
  bat30CellVoltage5.setUnitOfMeasurement("V");
  bat30CellVoltage6.setIcon("mdi:battery");
  bat30CellVoltage6.setUnitOfMeasurement("V");
  

  
  mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD);
  //mqtt.begin(BROKER_ADDR);

  Serial.println("Scanning...");

  // BLE initialisieren
  NimBLEDevice::init("");

  NimBLEDevice::setPower(ESP_PWR_LVL_P9);

  // Scan-Konfiguration
  NimBLEScan* pNimBLEScan = NimBLEDevice::getScan();
  pNimBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), true);
  pNimBLEScan->setActiveScan(true);             // Aaktiver Scan
  pNimBLEScan->setDuplicateFilter(true);         //Zeigt nur neue Teilnehmer an
  pNimBLEScan->start(20, scanCompleteCallback);  // Scan für 30 Sekunden
}

void loop() {
  if (readOutComplete==true){
    Serial.println("Send Data to HA");
    mqtt.loop();
    actCycles++;
    delay(1000);
  } 

  //Daten von allen Sensoren lesen
  if (scanComplete) {
    
    readOutComplete = false;
    int i=0;
    Serial.print("Es wurden ");
    Serial.print(foundDevices.size());
    foundDevicesTempNumber = static_cast<int32_t>(foundDevices.size());
    Serial.println(" Geräte gefunden.");
    for (auto& deviceAddress : foundDevices) {
      Serial.print("Versuche, eine Verbindung zu ");
      Serial.println(deviceAddress.c_str());
      Serial.print("Name: ");
      Serial.println(foundDevicesNames[i].c_str());
      actualBattery = getListNumberSavedOrder(foundDevicesNames[i]);
      BattAirHandlerArray[actualBattery].Name = foundDevicesNames[i];
      Serial.print("actualBattery: ");
      Serial.println(actualBattery);
      Serial.print("BattAirName: ");
      Serial.println(BattAirHandlerArray[actualBattery].Name);

      NimBLEClient* pClient = NimBLEDevice::createClient();
      if (pClient->connect(NimBLEAddress(deviceAddress.c_str()))) {
        Serial.print("Verbunden mit: ");
        Serial.println(deviceAddress.c_str());
        
        // Letzte zwei Stellen der MAC-Adresse extrahieren und als int speichern
        String macAddressStr = deviceAddress.c_str();
        String lastTwoDigitsStr = macAddressStr.substring(macAddressStr.length() - 2);
        int lastTwoDigits = strtol(lastTwoDigitsStr.c_str(), NULL, 16);
        Serial.print("Letzte zwei Zeichen der Mac Adresse:");
        Serial.println(lastTwoDigits);
        BattAirHandlerArray[actualBattery].setMacAdress(lastTwoDigits);

        //Mac Adresse in umgekehrter Reinfolge ins WriteRequest array schreiben
        writeRequest1[3] = strtol((macAddressStr.substring(macAddressStr.length() - 2)).c_str(), NULL, 16);
        writeRequest1[4] = strtol((macAddressStr.substring(macAddressStr.length() - 5,macAddressStr.length()-3)).c_str(), NULL, 16);
        writeRequest1[5] = strtol((macAddressStr.substring(macAddressStr.length() - 8,macAddressStr.length()-6)).c_str(), NULL, 16);
        writeRequest1[6] = strtol((macAddressStr.substring(macAddressStr.length() - 11,macAddressStr.length()-9)).c_str(), NULL, 16);
        writeRequest1[7] = strtol((macAddressStr.substring(macAddressStr.length() - 14,macAddressStr.length()-12)).c_str(), NULL, 16);
        writeRequest1[8] = strtol((macAddressStr.substring(macAddressStr.length() - 17,macAddressStr.length()-15)).c_str(), NULL, 16);
        writeRequest1[10] = strtol((macAddressStr.substring(macAddressStr.length() - 2)).c_str(), NULL, 16);
        //for(int i = 0; i<sizeof(writeRequest1);i++) {Serial.println(writeRequest1[i]);}
        // Daten auslesen
        // Service abrufen
        NimBLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
        if (pRemoteService == nullptr) {
          Serial.print("Service nicht gefunden: ");
          Serial.println(SERVICE_UUID);
          pClient->disconnect();
          return;
        }

        // Charakteristik abrufen
        pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
        if (pRemoteCharacteristic == nullptr) {
          Serial.print("Charakteristik nicht gefunden: ");
          Serial.println(CHARACTERISTIC_UUID);
          pClient->disconnect();
          return;
        }

        // Daten lesen
        if (pRemoteCharacteristic->canRead()) {
          response = pRemoteCharacteristic->readValue();
        }
        delay(200);
        // Nachricht senden 1
        uint8_t resultWriteRequest1Array[sizeof(writeRequest1)];
        for (int j = 0; j < sizeof(writeRequest1); j++) {
          resultWriteRequest1Array[j] = writeRequest1[j] ^ lastTwoDigits;
          Serial.print(resultWriteRequest1Array[j], HEX);
        }
        Serial.println("");
        pRemoteCharacteristic->writeValue(resultWriteRequest1Array, sizeof(resultWriteRequest1Array), false);

        delay(500);
        if (pRemoteCharacteristic->canNotify()) {
          //Serial.println("notify active");
          pRemoteCharacteristic->subscribe(true, notifyCallback);
        }
        delay(500);

        uint8_t writeRequest[3] = { 0x00, 0x00, 0x00 };
        uint8_t resultWriteRequestArray[4] = { 0x00, 0x00, 0x00, 0x00 };
        for (int i = 0; i < 13; i++) {
          for (int j = 0; j < 4; j++) {
            resultWriteRequestArray[j] = requestArray[i][j] ^ lastTwoDigits;
            //Serial.print(resultWriteRequestArray[j], HEX);
          }
          //Serial.println("");
          pRemoteCharacteristic->writeValue(resultWriteRequestArray, sizeof(resultWriteRequestArray), false);
          // Send Data to HA
          delay(1000);
        }

        pClient->disconnect();
        Serial.println("Verbindung getrennt");
      } else {
        Serial.println("Verbindung zum Server fehlgeschlagen.");
      }
    i++;
    }
    readOutComplete = true;
    // Reset the flag to avoid repeated connections
    
    scanComplete = false;
  }
  if(readOutComplete){
    wakeUpCounter.setValue(lapCounter);
    foundDevicesNumber.setValue(foundDevicesTempNumber);
    for(int i=0; i<30;i++){
      // Switch-Case-Anweisung 
      switch (i) { 
        case 0: 
          //Serial.println("Order ist 0");
          //if (BattAirHandlerArray[i].Name != ""){
          bat1Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat1Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat1BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat1BatteryType.setValue("NotFound");
          bat1BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat1BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat1CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat1CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat1CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat1CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat1CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat1CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break; 
        case 1: 
          //Serial.println("Order ist 1"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat2Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat2Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat2BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat2BatteryType.setValue("NotFound");
          bat2BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat2BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat2CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat2CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat2CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat2CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat2CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat2CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break; 
        case 2: 
          //Serial.println("Order ist 2"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat3Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat3Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat3BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat3BatteryType.setValue("NotFound");
          bat3BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat3BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat3CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat3CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat3CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat3CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat3CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat3CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break; 
        case 3: 
          //Serial.println("Order ist 3"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat4Name.setValue(BattAirHandlerArray[i].Name.c_str());
		      //bat4Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat4BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat4BatteryType.setValue("NotFound");
          bat4BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat4BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat4CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat4CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat4CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat4CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat4CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat4CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 4: 
          //Serial.println("Order ist 4"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat5Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat5Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
         if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat5BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat5BatteryType.setValue("NotFound");
          bat5BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat5BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat5CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat5CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat5CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat5CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat5CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat5CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 5: 
          //Serial.println("Order ist 5"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat6Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat6Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat6BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat6BatteryType.setValue("NotFound");
          bat6BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat6BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat6CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat6CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat6CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat6CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat6CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat6CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 6: 
          //Serial.println("Order ist 6"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat7Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat7Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat7BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat7BatteryType.setValue("NotFound");
          bat7BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat7BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat7CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat7CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat7CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat7CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat7CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat7CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 7: 
          //Serial.println("Order ist 7"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat8Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat8Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat8BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat8BatteryType.setValue("NotFound");
          bat8BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat8BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat8CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat8CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat8CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat8CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat8CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat8CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 8: 
          //Serial.println("Order ist 8"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat9Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat9Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat9BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat9BatteryType.setValue("NotFound");
          bat9BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat9BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat9CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat9CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat9CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat9CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat9CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat9CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 9: 
          //Serial.println("Order ist 9"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat10Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat10Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat10BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat10BatteryType.setValue("NotFound");
          bat10BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat10BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat10CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat10CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat10CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat10CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat10CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat10CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 10: 
          //Serial.println("Order ist 10"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat11Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat11Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat11BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat11BatteryType.setValue("NotFound");
          bat11BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat11BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat11CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat11CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat11CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat11CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat11CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat11CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 11: 
          //Serial.println("Order ist 11"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat12Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat12Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat12BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat12BatteryType.setValue("NotFound");
          bat12BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat12BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat12CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat12CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat12CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat12CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat12CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat12CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 12: 
          //Serial.println("Order ist 12"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat13Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat13Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat13BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat13BatteryType.setValue("NotFound");
          bat13BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat13BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat13CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat13CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat13CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat13CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat13CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat13CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 13: 
          //Serial.println("Order ist 13"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat14Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat14Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat14BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat14BatteryType.setValue("NotFound");
          bat14BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat14BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat14CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat14CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat14CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat14CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat14CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat14CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 14: 
          //Serial.println("Order ist 14"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat15Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat15Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat15BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat15BatteryType.setValue("NotFound");
          bat15BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat15BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat15CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat15CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat15CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat15CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat15CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat15CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 15: 
          //Serial.println("Order ist 15"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat16Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat16Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat16BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat16BatteryType.setValue("NotFound");
          bat16BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat16BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat16CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat16CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat16CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat16CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat16CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat16CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 16: 
          //Serial.println("Order ist 16"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat17Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat17Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat17BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat17BatteryType.setValue("NotFound");
          bat17BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat17BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat17CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat17CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat17CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat17CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat17CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat17CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 17: 
          //Serial.println("Order ist 17"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat18Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat18Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat18BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat18BatteryType.setValue("NotFound");
          bat18BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat18BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat18CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat18CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat18CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat18CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat18CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat18CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 18: 
          //Serial.println("Order ist 18"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat19Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat19Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat19BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat19BatteryType.setValue("NotFound");
          bat19BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat19BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat19CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat19CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat19CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat19CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat19CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat19CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 19: 
          //Serial.println("Order ist 19"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat20Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat20Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat20BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat20BatteryType.setValue("NotFound");
          bat20BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat20BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat20CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat20CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat20CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat20CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat20CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat20CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 20: 
          //Serial.println("Order ist 20"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat21Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat21Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat21BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat21BatteryType.setValue("NotFound");
          bat21BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat21BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat21CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat21CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat21CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat21CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat21CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat21CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 21: 
          //Serial.println("Order ist 21"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat22Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat22Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat22BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat22BatteryType.setValue("NotFound");
          bat22BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat22BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat22CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat22CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat22CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat22CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat22CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat22CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 22: 
          //Serial.println("Order ist 22"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat23Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat23Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat23BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat23BatteryType.setValue("NotFound");
          bat23BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat23BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat23CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat23CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat23CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat23CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat23CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat23CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 23: 
          //Serial.println("Order ist 23"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat24Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat24Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat24BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat24BatteryType.setValue("NotFound");
          bat24BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat24BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat24CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat24CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat24CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat24CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat24CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat24CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 24: 
          //Serial.println("Order ist 24"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat25Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat25Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat25BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat25BatteryType.setValue("NotFound");
          bat25BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat25BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat25CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat25CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat25CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat25CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat25CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat25CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 25: 
          //Serial.println("Order ist 25"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat26Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat26Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat26BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat26BatteryType.setValue("NotFound");
          bat26BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat26BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat26CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat26CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat26CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat26CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat26CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat26CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		  case 26: 
          //Serial.println("Order ist 26"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat27Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat27Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat27BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat27BatteryType.setValue("NotFound");
          bat27BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat27BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat27CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat27CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat27CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat27CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat27CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat27CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 27: 
          //Serial.println("Order ist 27"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat28Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat28Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat28BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat28BatteryType.setValue("NotFound");
          bat28BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat28BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat28CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat28CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat28CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat28CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat28CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat28CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 28: 
          //Serial.println("Order ist 28"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat29Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat29Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat29BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat29BatteryType.setValue("NotFound");
          bat29BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat29BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat29CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat29CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat29CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat29CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat29CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat29CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
		    case 29: 
          //Serial.println("Order ist 29"); 
          //if (BattAirHandlerArray[i].Name != ""){
          bat30Name.setValue(BattAirHandlerArray[i].Name.c_str());
          //bat30Temperature.setValue(BattAirHandlerArray[i].RealTimeParameter1Response.temperature);
          if (BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1>0)bat30BatteryType.setValue(BattAirHandlerArray[i].HardwareInfoClass.batteryTypeString.c_str());
          else bat30BatteryType.setValue("NotFound");
          bat30BatteryCycles.setValue(BattAirHandlerArray[i].AbnormalStatisticsResponse.batteryCycles);
          bat30BatteryVoltage.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5+BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6);
          bat30CellVoltage1.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage1);
          bat30CellVoltage2.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage2);  
          bat30CellVoltage3.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage3);
          bat30CellVoltage4.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage4); 
          bat30CellVoltage5.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage5);
          bat30CellVoltage6.setValue(BattAirHandlerArray[i].RealTimeParameter0Response.cellVoltage6); 
          //}
          break;
        case 99: 
          Serial.println("Order ist unbekannt - 99"); 
          break; 
        default: 
          Serial.println("Order ist unbekannt- default"); 
          break; 
      }
    }    
  }
  if (readOutComplete && actCycles >= cycles){
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR); 
    // Gib eine Meldung aus und gehe in den Deep-Sleep-Modus 
    Serial.println("Going to sleep now"); 
    delay(1000); // Gib der seriellen Ausgabe Zeit, die Nachricht zu senden 
    esp_deep_sleep_start();
  }
}
