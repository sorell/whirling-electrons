EESchema Schematic File Version 4
LIBS:arduino-nano-breakout-1-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5BF57DB9
P 5050 3800
F 0 "A1" H 5050 2714 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 5050 2623 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5200 2850 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5050 2800 50  0001 C CNN
	1    5050 3800
	1    0    0    -1  
$EndComp
$Comp
L SS_connectors:PJ-002A J1
U 1 1 5BF57EB7
P 4250 2300
F 0 "J1" H 4219 2640 50  0000 C CNN
F 1 "PJ-002A" H 4219 2549 50  0000 C CNN
F 2 "CUI_PJ-002A" H 4250 2300 50  0001 L BNN
F 3 "Manufacturer recommendations" H 4250 2300 50  0001 L BNN
F 4 "CUI INC" H 4250 2300 50  0001 L BNN "Field4"
	1    4250 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5BF5969D
P 5150 1900
F 0 "J2" V 5210 2040 50  0000 L CNN
F 1 "Conn_01x03_Male" V 5301 2040 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5150 1900 50  0001 C CNN
F 3 "~" H 5150 1900 50  0001 C CNN
	1    5150 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 2200 5150 2100
$Comp
L power:GND #PWR0101
U 1 1 5BF59927
P 5200 5150
F 0 "#PWR0101" H 5200 4900 50  0001 C CNN
F 1 "GND" H 5205 4977 50  0000 C CNN
F 2 "" H 5200 5150 50  0001 C CNN
F 3 "" H 5200 5150 50  0001 C CNN
	1    5200 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5BF59956
P 5000 5150
F 0 "#PWR0102" H 5000 4900 50  0001 C CNN
F 1 "GND" H 5005 4977 50  0000 C CNN
F 2 "" H 5000 5150 50  0001 C CNN
F 3 "" H 5000 5150 50  0001 C CNN
	1    5000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4800 5200 5150
Wire Wire Line
	5000 4800 5000 5150
Wire Wire Line
	5200 4800 5150 4800
Wire Wire Line
	5050 4800 5000 4800
$Comp
L power:GND #PWR0103
U 1 1 5BF59B46
P 4550 2500
F 0 "#PWR0103" H 4550 2250 50  0001 C CNN
F 1 "GND" H 4555 2327 50  0000 C CNN
F 2 "" H 4550 2500 50  0001 C CNN
F 3 "" H 4550 2500 50  0001 C CNN
	1    4550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2400 4550 2400
Wire Wire Line
	4550 2400 4550 2500
NoConn ~ 4450 2300
Wire Wire Line
	5150 2200 4450 2200
Wire Wire Line
	5050 2100 5050 2650
Wire Wire Line
	5050 2650 4950 2650
Wire Wire Line
	4950 2650 4950 2800
$Comp
L Connector:Conn_01x08_Male J4
U 1 1 5BF5B051
P 6950 3700
F 0 "J4" H 6923 3580 50  0000 R CNN
F 1 "Conn_01x08_Male" H 6923 3671 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 6950 3700 50  0001 C CNN
F 3 "~" H 6950 3700 50  0001 C CNN
	1    6950 3700
	-1   0    0    1   
$EndComp
Text GLabel 4250 3400 0    50   Input ~ 0
IO2
Wire Wire Line
	4250 3400 4550 3400
Text GLabel 4400 3500 0    50   Input ~ 0
IO3
Wire Wire Line
	4550 3500 4400 3500
Text GLabel 4250 3700 0    50   Input ~ 0
IO5
Text GLabel 4400 3800 0    50   Input ~ 0
IO6
Wire Wire Line
	4250 3700 4550 3700
Wire Wire Line
	4400 3800 4550 3800
Text GLabel 4250 4100 0    50   Input ~ 0
IO9
Text GLabel 4400 4200 0    50   Input ~ 0
IO10
Wire Wire Line
	4250 4100 4550 4100
Wire Wire Line
	4400 4200 4550 4200
Text GLabel 6650 3300 0    50   Input ~ 0
IO10
Text GLabel 6650 3400 0    50   Input ~ 0
IO9
Wire Wire Line
	6650 3400 6750 3400
Wire Wire Line
	6650 3300 6750 3300
Wire Wire Line
	6400 3900 6750 3900
Wire Wire Line
	6400 4000 6400 4800
Wire Wire Line
	6400 4800 5200 4800
Wire Wire Line
	6400 4000 6750 4000
Connection ~ 5200 4800
Text GLabel 6650 3500 0    50   Input ~ 0
IO6
Text GLabel 6650 3600 0    50   Input ~ 0
IO5
Text GLabel 6650 3700 0    50   Input ~ 0
IO3
Text GLabel 6650 3800 0    50   Input ~ 0
IO2
Wire Wire Line
	6650 3500 6750 3500
Wire Wire Line
	6650 3600 6750 3600
Wire Wire Line
	6650 3700 6750 3700
Wire Wire Line
	6650 3800 6750 3800
Wire Wire Line
	5250 2100 5250 2800
Wire Wire Line
	6400 3900 6400 2200
Wire Wire Line
	6400 2200 5150 2200
Connection ~ 5150 2200
$EndSCHEMATC
