EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "Oven"
Date "2021-06-01"
Rev "3"
Comp "HPVDT"
Comment1 "Uses a K-Type thermocouple"
Comment2 ""
Comment3 "Intended to control a heater to achieve a two step curing process"
Comment4 "General purpose oven board"
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328-AU U1
U 1 1 60B6B07B
P 1800 2550
F 0 "U1" H 1350 4000 50  0000 C CNN
F 1 "ATmega328-AU" H 1700 2550 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 1800 2550 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 1800 2550 50  0001 C CNN
	1    1800 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J8
U 1 1 60B6C0AF
P 3550 3450
F 0 "J8" H 3630 3442 50  0000 L CNN
F 1 "NUMPAD" H 3630 3351 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Horizontal" H 3550 3450 50  0001 C CNN
F 3 "~" H 3550 3450 50  0001 C CNN
	1    3550 3450
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J7
U 1 1 60B6C7B3
P 6000 5600
F 0 "J7" H 6080 5592 50  0000 L CNN
F 1 "DISPLAY" H 6080 5501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 6000 5600 50  0001 C CNN
F 3 "~" H 6000 5600 50  0001 C CNN
	1    6000 5600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x09 J5
U 1 1 60B6D0AA
P 9200 6000
F 0 "J5" H 9280 6042 50  0000 L CNN
F 1 "OUTPUT" H 9280 5951 50  0000 L CNN
F 2 "oven:9POS-TERMBLOCK" H 9200 6000 50  0001 C CNN
F 3 "~" H 9200 6000 50  0001 C CNN
	1    9200 6000
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 60B6DB6D
P 3550 1450
F 0 "J6" H 3468 1125 50  0000 C CNN
F 1 "RELAY_CTRL" H 3468 1216 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 3550 1450 50  0001 C CNN
F 3 "~" H 3550 1450 50  0001 C CNN
	1    3550 1450
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 60B6E1E9
P 8700 5400
F 0 "J4" H 8618 5075 50  0000 C CNN
F 1 "LIVE" H 8618 5166 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-2sqmm_1x02_P7.8mm_D2mm_OD3.9mm" H 8700 5400 50  0001 C CNN
F 3 "~" H 8700 5400 50  0001 C CNN
	1    8700 5400
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 60B6F452
P 6250 7450
F 0 "J2" H 6168 7125 50  0000 C CNN
F 1 "5V_IN" H 6168 7216 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 6250 7450 50  0001 C CNN
F 3 "~" H 6250 7450 50  0001 C CNN
	1    6250 7450
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 60B6FD08
P 8000 6000
F 0 "J3" H 8150 6050 50  0000 C CNN
F 1 "RELAY_PWR" H 8300 5950 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-2sqmm_1x01_D2mm_OD3.9mm" H 8000 6000 50  0001 C CNN
F 3 "~" H 8000 6000 50  0001 C CNN
	1    8000 6000
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 60B7038D
P 7950 6750
F 0 "J1" H 8100 6700 50  0000 C CNN
F 1 "NEUTRAL" H 8200 6800 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-2sqmm_1x01_D2mm_OD3.9mm" H 7950 6750 50  0001 C CNN
F 3 "~" H 7950 6750 50  0001 C CNN
	1    7950 6750
	-1   0    0    1   
$EndComp
$Comp
L power:GNDPWR #PWR06
U 1 1 60B76F5D
P 8900 5600
F 0 "#PWR06" H 8900 5400 50  0001 C CNN
F 1 "GNDPWR" V 8900 5450 50  0000 R CNN
F 2 "" H 8900 5550 50  0001 C CNN
F 3 "" H 8900 5550 50  0001 C CNN
	1    8900 5600
	0    1    1    0   
$EndComp
$Comp
L power:LINE #PWR07
U 1 1 60B793C1
P 8900 5700
F 0 "#PWR07" H 8900 5550 50  0001 C CNN
F 1 "LINE" V 8900 5850 50  0000 L CNN
F 2 "" H 8900 5700 50  0001 C CNN
F 3 "" H 8900 5700 50  0001 C CNN
	1    8900 5700
	0    -1   -1   0   
$EndComp
$Comp
L power:NEUT #PWR08
U 1 1 60B79F22
P 8900 5900
F 0 "#PWR08" H 8900 5750 50  0001 C CNN
F 1 "NEUT" V 8900 6050 50  0000 L CNN
F 2 "" H 8900 5900 50  0001 C CNN
F 3 "" H 8900 5900 50  0001 C CNN
	1    8900 5900
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 60B96775
P 5650 7350
F 0 "#PWR04" H 5650 7200 50  0001 C CNN
F 1 "+5V" V 5650 7500 50  0000 L CNN
F 2 "" H 5650 7350 50  0001 C CNN
F 3 "" H 5650 7350 50  0001 C CNN
	1    5650 7350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 60B99F7C
P 3350 1450
F 0 "#PWR09" H 3350 1200 50  0001 C CNN
F 1 "GND" H 3355 1277 50  0000 C CNN
F 2 "" H 3350 1450 50  0001 C CNN
F 3 "" H 3350 1450 50  0001 C CNN
	1    3350 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 60B9C977
P 6050 7450
F 0 "#PWR05" H 6050 7200 50  0001 C CNN
F 1 "GND" H 6055 7277 50  0000 C CNN
F 2 "" H 6050 7450 50  0001 C CNN
F 3 "" H 6050 7450 50  0001 C CNN
	1    6050 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 6000 9000 6000
Wire Wire Line
	8900 5900 8950 5900
Wire Wire Line
	8900 5700 8950 5700
Wire Wire Line
	8900 5600 9000 5600
Wire Wire Line
	8950 5700 8950 5400
Wire Wire Line
	8950 5300 8900 5300
Connection ~ 8950 5700
Wire Wire Line
	8950 5700 9000 5700
Wire Wire Line
	8900 5400 8950 5400
Connection ~ 8950 5400
Wire Wire Line
	8950 5400 8950 5300
Text Notes 9050 5350 0    50   ~ 0
Live used for relay and 5V supply.
$Comp
L power:GND #PWR010
U 1 1 60BAE1CA
P 5800 5500
F 0 "#PWR010" H 5800 5250 50  0001 C CNN
F 1 "GND" V 5800 5350 50  0000 R CNN
F 2 "" H 5800 5500 50  0001 C CNN
F 3 "" H 5800 5500 50  0001 C CNN
	1    5800 5500
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 60BAF096
P 1800 1050
F 0 "#PWR01" H 1800 900 50  0001 C CNN
F 1 "+5V" H 1815 1223 50  0000 C CNN
F 2 "" H 1800 1050 50  0001 C CNN
F 3 "" H 1800 1050 50  0001 C CNN
	1    1800 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 60BB12C3
P 1800 4050
F 0 "#PWR02" H 1800 3800 50  0001 C CNN
F 1 "GND" H 1805 3877 50  0000 C CNN
F 2 "" H 1800 4050 50  0001 C CNN
F 3 "" H 1800 4050 50  0001 C CNN
	1    1800 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1050 1900 1050
Connection ~ 1800 1050
NoConn ~ 1200 1350
NoConn ~ 1200 1550
NoConn ~ 1200 1650
Wire Wire Line
	8950 5800 8950 5900
Wire Wire Line
	8950 5800 9000 5800
Connection ~ 8950 5900
Wire Wire Line
	8950 5900 9000 5900
$Comp
L power:NEUT #PWR03
U 1 1 60BC5D78
P 8150 6750
F 0 "#PWR03" H 8150 6600 50  0001 C CNN
F 1 "NEUT" V 8150 6900 50  0000 L CNN
F 2 "" H 8150 6750 50  0001 C CNN
F 3 "" H 8150 6750 50  0001 C CNN
	1    8150 6750
	0    1    1    0   
$EndComp
Text Notes 7600 6950 0    50   ~ 0
Return from 5V adapter
$Comp
L power:+5V #PWR011
U 1 1 60BCD982
P 5800 5600
F 0 "#PWR011" H 5800 5450 50  0001 C CNN
F 1 "+5V" V 5800 5750 50  0000 L CNN
F 2 "" H 5800 5600 50  0001 C CNN
F 3 "" H 5800 5600 50  0001 C CNN
	1    5800 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 5700 5800 5700
Wire Wire Line
	5500 5800 5800 5800
Text Label 5500 5700 0    50   ~ 0
SDA
Text Label 5500 5800 0    50   ~ 0
SCL
NoConn ~ 9000 6100
NoConn ~ 9000 6200
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 60B7EED6
P 9450 6950
F 0 "H1" V 9404 7100 50  0000 L CNN
F 1 "M3" V 9495 7100 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm_Pad_Via" H 9450 6950 50  0001 C CNN
F 3 "~" H 9450 6950 50  0001 C CNN
	1    9450 6950
	0    1    1    0   
$EndComp
$Comp
L power:GNDPWR #PWR0101
U 1 1 60B7FA28
P 9350 6950
F 0 "#PWR0101" H 9350 6750 50  0001 C CNN
F 1 "GNDPWR" V 9350 6800 50  0000 R CNN
F 2 "" H 9350 6900 50  0001 C CNN
F 3 "" H 9350 6900 50  0001 C CNN
	1    9350 6950
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60B80446
P 9850 6950
F 0 "H2" H 9950 6996 50  0000 L CNN
F 1 "M3" H 9950 6905 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 9850 6950 50  0001 C CNN
F 3 "~" H 9850 6950 50  0001 C CNN
	1    9850 6950
	1    0    0    -1  
$EndComp
$Comp
L Connector:AVR-ISP-6 J9
U 1 1 60B7B90C
P 2000 5150
F 0 "J9" H 1671 5246 50  0000 R CNN
F 1 "AVR-ISP-6" H 1671 5155 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" V 1750 5200 50  0001 C CNN
F 3 " ~" H 725 4600 50  0001 C CNN
	1    2000 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60B7CC78
P 1900 5550
F 0 "#PWR0102" H 1900 5300 50  0001 C CNN
F 1 "GND" H 1905 5377 50  0000 C CNN
F 2 "" H 1900 5550 50  0001 C CNN
F 3 "" H 1900 5550 50  0001 C CNN
	1    1900 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 60B7D30D
P 1900 4650
F 0 "#PWR0103" H 1900 4500 50  0001 C CNN
F 1 "+5V" H 1915 4823 50  0000 C CNN
F 2 "" H 1900 4650 50  0001 C CNN
F 3 "" H 1900 4650 50  0001 C CNN
	1    1900 4650
	1    0    0    -1  
$EndComp
$Comp
L oven:MAX6675 U2
U 1 1 60B8137D
P 2050 7400
F 0 "U2" H 2050 7815 50  0000 C CNN
F 1 "MAX6675" H 2050 7724 50  0000 C CNN
F 2 "Package_SO:SO-8_5.3x6.2mm_P1.27mm" H 2050 7100 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX6675.pdf" H 2050 7700 50  0001 C CNN
	1    2050 7400
	1    0    0    -1  
$EndComp
Text Label 2650 2850 2    50   ~ 0
RST
Text Label 2650 2750 2    50   ~ 0
SCL
Text Label 2650 2650 2    50   ~ 0
SDA
Text Label 2650 1650 2    50   ~ 0
MOSI
Text Label 2650 1750 2    50   ~ 0
MISO
Text Label 2650 1850 2    50   ~ 0
SCK
Text Label 2650 3050 2    50   ~ 0
RX
Text Label 2650 3150 2    50   ~ 0
TX
Wire Wire Line
	2650 2650 2400 2650
Wire Wire Line
	2650 2750 2400 2750
Wire Wire Line
	2650 2850 2400 2850
Wire Wire Line
	2650 1650 2400 1650
Wire Wire Line
	2650 1750 2400 1750
Wire Wire Line
	2650 1850 2400 1850
Wire Wire Line
	2650 3050 2400 3050
Wire Wire Line
	2650 3150 2400 3150
Text Label 2650 1350 2    50   ~ 0
RELAY
Wire Wire Line
	1700 7450 1700 7550
Wire Wire Line
	9000 6300 8750 6300
Text Label 8750 6300 0    50   ~ 0
TC+
$Comp
L power:GND #PWR0104
U 1 1 60BA5A27
P 1700 7550
F 0 "#PWR0104" H 1700 7300 50  0001 C CNN
F 1 "GND" H 1705 7377 50  0000 C CNN
F 2 "" H 1700 7550 50  0001 C CNN
F 3 "" H 1700 7550 50  0001 C CNN
	1    1700 7550
	1    0    0    -1  
$EndComp
Connection ~ 1700 7550
$Comp
L power:GND #PWR0105
U 1 1 60BA6036
P 9000 6400
F 0 "#PWR0105" H 9000 6150 50  0001 C CNN
F 1 "GND" V 9000 6200 50  0000 C CNN
F 2 "" H 9000 6400 50  0001 C CNN
F 3 "" H 9000 6400 50  0001 C CNN
	1    9000 6400
	0    1    1    0   
$EndComp
Text Notes 7750 6450 0    50   ~ 0
TC- connects to ground
Text Label 1500 7350 0    50   ~ 0
TC+
Wire Wire Line
	1500 7350 1700 7350
$Comp
L power:+5V #PWR0106
U 1 1 60BA8A56
P 1300 7250
F 0 "#PWR0106" H 1300 7100 50  0001 C CNN
F 1 "+5V" V 1300 7400 50  0000 L CNN
F 2 "" H 1300 7250 50  0001 C CNN
F 3 "" H 1300 7250 50  0001 C CNN
	1    1300 7250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C1
U 1 1 60BA964E
P 1300 7400
F 0 "C1" H 1185 7354 50  0000 R CNN
F 1 "100n" H 1185 7445 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1338 7250 50  0001 C CNN
F 3 "~" H 1300 7400 50  0001 C CNN
	1    1300 7400
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 60BAA492
P 1300 7550
F 0 "#PWR0107" H 1300 7300 50  0001 C CNN
F 1 "GND" H 1305 7377 50  0000 C CNN
F 2 "" H 1300 7550 50  0001 C CNN
F 3 "" H 1300 7550 50  0001 C CNN
	1    1300 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 7250 1700 7250
Connection ~ 1300 7250
Text Label 2650 5250 2    50   ~ 0
RST
Wire Wire Line
	2650 5250 2400 5250
Text Label 2650 5050 2    50   ~ 0
MOSI
Text Label 2650 4950 2    50   ~ 0
MISO
Text Label 2650 5150 2    50   ~ 0
SCK
Wire Wire Line
	2650 5050 2400 5050
Wire Wire Line
	2650 4950 2400 4950
Wire Wire Line
	2650 5150 2400 5150
Text Label 2650 7500 2    50   ~ 0
MISO
Wire Wire Line
	2650 7500 2400 7500
Text Label 2650 7300 2    50   ~ 0
SCK
Wire Wire Line
	2650 7300 2400 7300
Text Label 2650 1450 2    50   ~ 0
TCSS
Wire Wire Line
	2650 1450 2400 1450
Text Label 2650 7400 2    50   ~ 0
TCSS
Wire Wire Line
	2650 7400 2400 7400
$Comp
L Device:Resonator Y1
U 1 1 60BCB0C5
P 3300 2200
F 0 "Y1" H 3100 2100 50  0000 C CNN
F 1 "16M" H 3550 2100 50  0000 C CNN
F 2 "Crystal:Resonator_SMD_muRata_CSTxExxV-3Pin_3.0x1.1mm" H 3275 2200 50  0001 C CNN
F 3 "~" H 3275 2200 50  0001 C CNN
	1    3300 2200
	1    0    0    -1  
$EndComp
Entry Wire Line
	2650 2850 2750 2950
Entry Wire Line
	2650 1850 2750 1950
Entry Wire Line
	2650 1750 2750 1850
Entry Wire Line
	2650 1650 2750 1750
Entry Wire Line
	2650 4950 2750 4850
Entry Wire Line
	2650 5050 2750 4950
Entry Wire Line
	2650 5150 2750 5050
Entry Wire Line
	2650 5250 2750 5150
Entry Wire Line
	2650 7300 2750 7200
Entry Wire Line
	2650 7500 2750 7400
Entry Wire Line
	2650 7400 2750 7300
Entry Wire Line
	2650 1450 2750 1550
$Comp
L power:GND #PWR0108
U 1 1 60C024DC
P 3300 2400
F 0 "#PWR0108" H 3300 2150 50  0001 C CNN
F 1 "GND" H 3305 2227 50  0000 C CNN
F 2 "" H 3300 2400 50  0001 C CNN
F 3 "" H 3300 2400 50  0001 C CNN
	1    3300 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1950 2650 1950
Wire Wire Line
	2650 1950 2650 2050
Wire Wire Line
	3550 2050 3550 2200
Wire Wire Line
	3550 2200 3450 2200
Wire Wire Line
	2550 2200 2550 2050
Wire Wire Line
	2550 2050 2400 2050
NoConn ~ 2400 1550
$Comp
L Connector_Generic:Conn_01x06 J10
U 1 1 60C0B394
P 9350 2700
F 0 "J10" H 9268 2175 50  0000 C CNN
F 1 "SERIAL" H 9268 2266 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 9350 2700 50  0001 C CNN
F 3 "~" H 9350 2700 50  0001 C CNN
	1    9350 2700
	1    0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 60C147F3
P 8700 2400
F 0 "C3" V 8448 2400 50  0000 C CNN
F 1 "100n" V 8539 2400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8738 2250 50  0001 C CNN
F 3 "~" H 8700 2400 50  0001 C CNN
	1    8700 2400
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 60C158FF
P 8300 2250
F 0 "R1" H 8368 2296 50  0000 L CNN
F 1 "10K" H 8368 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8340 2240 50  0001 C CNN
F 3 "~" H 8300 2250 50  0001 C CNN
	1    8300 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2400 8300 2400
Connection ~ 8300 2400
Wire Wire Line
	8300 2400 8050 2400
Text Label 8050 2400 0    50   ~ 0
RST
$Comp
L power:+5V #PWR0109
U 1 1 60C17B17
P 8300 2100
F 0 "#PWR0109" H 8300 1950 50  0001 C CNN
F 1 "+5V" H 8315 2273 50  0000 C CNN
F 2 "" H 8300 2100 50  0001 C CNN
F 3 "" H 8300 2100 50  0001 C CNN
	1    8300 2100
	1    0    0    -1  
$EndComp
Text Label 8950 2400 0    50   ~ 0
DTR
$Comp
L power:GND #PWR0110
U 1 1 60C19D01
P 9150 2900
F 0 "#PWR0110" H 9150 2650 50  0001 C CNN
F 1 "GND" H 9155 2727 50  0000 C CNN
F 2 "" H 9150 2900 50  0001 C CNN
F 3 "" H 9150 2900 50  0001 C CNN
	1    9150 2900
	1    0    0    -1  
$EndComp
NoConn ~ 9150 2800
$Comp
L power:+5V #PWR0111
U 1 1 60C1B3DC
P 9150 2700
F 0 "#PWR0111" H 9150 2550 50  0001 C CNN
F 1 "+5V" V 9150 2900 50  0000 C CNN
F 2 "" H 9150 2700 50  0001 C CNN
F 3 "" H 9150 2700 50  0001 C CNN
	1    9150 2700
	0    -1   -1   0   
$EndComp
Text Label 8950 2500 0    50   ~ 0
TX
Text Label 8950 2600 0    50   ~ 0
RX
Wire Wire Line
	8950 2500 9150 2500
Wire Wire Line
	8950 2600 9150 2600
$Comp
L Device:C C2
U 1 1 60C299AE
P 8300 2550
F 0 "C2" H 8185 2504 50  0000 R CNN
F 1 "4n7" H 8185 2595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8338 2400 50  0001 C CNN
F 3 "~" H 8300 2550 50  0001 C CNN
	1    8300 2550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 60C2A5B9
P 8300 2700
F 0 "#PWR0112" H 8300 2450 50  0001 C CNN
F 1 "GND" H 8305 2527 50  0000 C CNN
F 2 "" H 8300 2700 50  0001 C CNN
F 3 "" H 8300 2700 50  0001 C CNN
	1    8300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 2400 9150 2400
$Comp
L Jumper:Jumper_2_Bridged JP1
U 1 1 60C36818
P 5850 7350
F 0 "JP1" H 5850 7545 50  0000 C CNN
F 1 "5V_SUP" H 5850 7454 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_Pad1.0x1.5mm" H 5850 7350 50  0001 C CNN
F 3 "~" H 5850 7350 50  0001 C CNN
	1    5850 7350
	1    0    0    -1  
$EndComp
Wire Notes Line width 12
	7300 7000 7300 4400
Wire Notes Line width 12
	7300 4400 10400 4400
Text Notes 7400 4600 0    100  ~ 20
120V Zone
Text Notes 7800 4950 0    50   ~ 0
Terminal block where all connections are made.\nAll are at 120VAC, except for the thermocouple terminals.
Wire Wire Line
	2400 3250 3350 3250
Wire Wire Line
	2400 3350 3350 3350
Wire Wire Line
	2400 3450 3350 3450
Wire Wire Line
	2400 3550 3350 3550
Wire Wire Line
	2400 3650 3350 3650
Wire Wire Line
	2400 3750 3350 3750
Wire Wire Line
	2400 2550 2850 2550
Wire Wire Line
	2850 2550 2850 3150
Wire Wire Line
	2850 3150 3350 3150
Wire Wire Line
	2950 2450 2400 2450
Wire Wire Line
	2950 3050 3350 3050
Wire Wire Line
	2950 2450 2950 3050
NoConn ~ 2400 2250
NoConn ~ 2400 2350
Text Label 2650 2450 2    50   ~ 0
ROW1
Text Label 2650 2550 2    50   ~ 0
ROW2
Text Label 2650 3250 2    50   ~ 0
ROW3
Text Label 2650 3350 2    50   ~ 0
ROW4
Text Label 2650 3450 2    50   ~ 0
COL1
Text Label 2650 3550 2    50   ~ 0
COL2
Text Label 2650 3650 2    50   ~ 0
COL3
Text Label 2650 3750 2    50   ~ 0
COL4
Wire Wire Line
	2650 2050 3550 2050
Wire Wire Line
	2550 2200 3150 2200
$Comp
L Device:C C4
U 1 1 60CDB00B
P 850 2350
F 0 "C4" H 735 2304 50  0000 R CNN
F 1 "100n" H 735 2395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 888 2200 50  0001 C CNN
F 3 "~" H 850 2350 50  0001 C CNN
	1    850  2350
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 60CDC119
P 850 2200
F 0 "#PWR0113" H 850 2050 50  0001 C CNN
F 1 "+5V" H 865 2373 50  0000 C CNN
F 2 "" H 850 2200 50  0001 C CNN
F 3 "" H 850 2200 50  0001 C CNN
	1    850  2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 60CDC8CD
P 850 2500
F 0 "#PWR0114" H 850 2250 50  0001 C CNN
F 1 "GND" H 855 2327 50  0000 C CNN
F 2 "" H 850 2500 50  0001 C CNN
F 3 "" H 850 2500 50  0001 C CNN
	1    850  2500
	1    0    0    -1  
$EndComp
Text Label 8250 6000 0    50   ~ 0
RELAY_RTN
Text Notes 700  6850 0    50   ~ 0
Used to read in temperature of oven
Text Notes 4950 5250 0    50   ~ 0
An LCD character display with 20 columns and 4 rows.\nOnly user output interface for the system.
Text Notes 7600 3450 0    50   ~ 0
Added to allow potentially "Arduino"-like programming expirence
Text Notes 7550 1800 0    100  Italic 20
Serial Programming Header
Text Notes 4950 5050 0    100  Italic 20
Display Connection
Text Notes 2300 800  0    100  Italic 20
Microcontroller
Text Notes 700  6750 0    100  Italic 20
Thermocouple IC
Text Notes 1150 5900 0    50   Italic 0
Intended method of programming
Text Notes 3650 3700 0    50   ~ 0
Used to collect user input.\n4 x 4 grid of buttons.
Wire Wire Line
	2400 1350 3350 1350
Text Notes 3650 1450 0    50   ~ 0
Controls the solid state relay which \ncontrols current to heater
Text Notes 4950 7050 0    50   ~ 0
Connects to the output of a USB charger.\nCan be disconnected and reconnected as needed.
Text Notes 4950 6850 0    100  Italic 20
5V Input
Text Notes 2300 900  0    50   ~ 0
Configured like an Arduino Nano
Text Notes 700  7000 0    50   Italic 0
K-Type Thermocouples!
Wire Notes Line
	7300 4400 7300 600 
Wire Notes Line
	4650 7950 4650 4400
Wire Notes Line
	4650 4400 7300 4400
Wire Notes Line
	550  6300 7300 6300
Text Notes 9000 6800 0    50   Italic 0
One bolt is used to ground chassis
Wire Bus Line
	2750 1550 2750 7400
$EndSCHEMATC
