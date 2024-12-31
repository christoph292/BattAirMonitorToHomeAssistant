# BattAirMonitorToHomeAssistant

Bei dem Projekt handelt es sich um die Möglichkeit BattAir Adapter für Akkus auszulesen und die Daten an Home Assistant per MQTT weiterzusenden.

## Auslesbare Daten der Akkus
- `Gesamtspannung`
- `Einzelspannung bis 6s`
- `Gesamtzyklen`
- `Akku Name`
- `Akku Typ`
  
## Funktionen der Software
- `maximal 25 Akkus können ausgelesen werden`: Hier limitiert die Schnittstelle zu Home Assistant. 
- `Abrufhäufigkeit der Akkus ist einstellbar`: Über die Variable "Sleep Duration" lässt sich einstellen wie lange die Software bis zum nächsten Auslesen wartet.
- `Akkureinfolge beim auslesen wird dauerhaft gespeichert`: Da es Zufall ist welcher Akku als Erstes beim Scannen gefunden wird, wurde eine ausfallsichere Liste in der Software realisiert. Somit ist sichergestellt das die Akkus immer gleich an Home Assistant zurückgemeldet werden.
  Möchte man die Reinfolge löschen so setzt man "Clear Print Order" auf "Reset". Beim nächsten Abrufen der Akkus wird die interne Liste gelöscht und neu erstellt anhand der gefundenen Akkus. Anschließend muss die Variable "Clear Print Order" wieder auf "Keep" gesetzt werden.
- `Gefundene Akku Anzahl wird zurückgegeben`: Über die Variable "Found Devices" wird die zuletzt gefundene Anzahl an Akkus zurückgegeben. Dies kann genutzt werden um zu prüfen ob der Microcontroller am aktuellen Standort alle Akkus findet (Thema Metallkiste)
- `Mitteilung wann zuletzt die Akkus geprüft wurden`: Die Variable "Wake Up Counter" zählt von 1 bis 1000 und fängt danach wieder bei 1 an. Hierrüber ist es möglich zu prüfen wann die Akkus zuletzt ausgelesen wurden und ob der Microcontroller zuverlässig aufgewacht ist.



## FAQ
- `Was ist wenn ich mehr als 25 Akkus besitze?`: Aktuell lassen sich noch nicht mehr auslesen. Wenn aber mehr als 25 Akkus vorhanden sind und dauerhaft neben dem Microcontroller sind werden vermutlich die Daten der zuvielen Akkus nie an Home Assistant weitergeleitet. Dies konnte ich allerdings wegen fehlenden Akkus noch nicht testen.
- `Eine "BatteryName" Variable zeigt mir den richtigen Namen an, allerdings sind alle Daten 0`:
  - Der Grund hierfür ist das die Entfernung zu dem besagten Akku zu hoch ist. Beim initialen Suchen aller Akkus wird nur der Name gescannt. Teilweise kann es sein das der Akkus so gefunden wird     allerdings die Reichweite für das Daten auslesen zu hoch ist.
  - Das BattAir Modul hat keine Spannung mehr und der Akku ist somit entladen
  - `Als zusätzliche Info wird in diesem Fall in die Variable des Battery Types "Not Found" geschrieben!`
- `Wird die gespeicherte Liste gelöscht wenn ich eine neue Version per Arduino IDE aufspiele?`:
  Nein diese bleibt erhalten und muss falls gewünscht per Hand gelöscht werden.
  
## Benötige Hardware/Software
- `Microcontroller ESP32`
- `Arduino IDE`

## Installation
`Ich setzte hier Grundsetzliche Kenntnisse wie man einen Sketch in den ESP einspielt als bekannt voraus! Im Zweifel kurz googlen.`
- `Software anpassen`:
  - `BROKER_ADDR IPAddress: Zeile 16`: Hier muss die IP Adresse des MQTT Brokers bzw. von Home Assistant eingetragen werden.
  - `BROKER_USERNAME: Zeile 17`: Hier muss der Benutzername des MQTT Brokers eingetragen werden falls vorhanden.
  - `BROKER_PASSWORD: Zeile 18`: Hier muss das Password es Benutzers des MQTT Brokers eingetragen werden falls vorhanden.
  - `ssid: Zeile 20`: Hier muss die SSID des Wlans eingetragen werden. Ganz normal mit Leerzeichen falls vorhanden.
  - `password: Zeile 21`: Hier muss das Wlan Password eingetragen werden.
  - `MQTT Broker ohne extra Nutzer: Zeile 1734/1735`: Wenn ein MQTT Broker ohne extra Benutzer verwendet wird muss die Zeile 1734 auskommentiert werden und Zeile 1735 einkommentiert werden.
