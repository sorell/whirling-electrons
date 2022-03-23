EESchema Schematic File Version 4
LIBS:arduino-nano-breakout-1-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Arduino Mini Breakout"
Date "2018-11-23"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR0101
U 1 1 5BF59927
P 5150 5150
F 0 "#PWR0101" H 5150 4900 50  0001 C CNN
F 1 "GND" H 5155 4977 50  0000 C CNN
F 2 "" H 5150 5150 50  0001 C CNN
F 3 "" H 5150 5150 50  0001 C CNN
	1    5150 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5BF59B46
P 4550 2550
F 0 "#PWR0103" H 4550 2300 50  0001 C CNN
F 1 "GND" H 4555 2377 50  0000 C CNN
F 2 "" H 4550 2550 50  0001 C CNN
F 3 "" H 4550 2550 50  0001 C CNN
	1    4550 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2400 4550 2400
Wire Wire Line
	4550 2400 4550 2500
Text GLabel 4400 3400 0    50   Input ~ 0
D2
Text GLabel 4400 3500 0    50   Input ~ 0
D3
Wire Wire Line
	4550 3500 4400 3500
Text GLabel 4400 3700 0    50   Input ~ 0
D5
Text GLabel 4400 3800 0    50   Input ~ 0
D6
Wire Wire Line
	4400 3800 4550 3800
Text GLabel 4400 4100 0    50   Input ~ 0
D9
Text GLabel 4400 4200 0    50   Input ~ 0
D10
Wire Wire Line
	4400 4200 4550 4200
Text GLabel 7000 3900 0    50   Input ~ 0
D10
Text GLabel 7000 3800 0    50   Input ~ 0
D9
Wire Wire Line
	7000 3800 7100 3800
Wire Wire Line
	7000 3900 7100 3900
Text GLabel 6500 4000 1    50   Input ~ 0
D6
Text GLabel 6250 3900 1    50   Input ~ 0
D5
Text GLabel 6000 3700 1    50   Input ~ 0
D3
Text GLabel 5750 3600 1    50   Input ~ 0
D2
Wire Wire Line
	6750 4100 7100 4100
$Comp
L power:GND #PWR0104
U 1 1 5BF6D124
P 6950 4250
F 0 "#PWR0104" H 6950 4000 50  0001 C CNN
F 1 "GND" H 6955 4077 50  0000 C CNN
F 2 "" H 6950 4250 50  0001 C CNN
F 3 "" H 6950 4250 50  0001 C CNN
	1    6950 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4000 6950 4000
Wire Wire Line
	6950 4000 6950 4250
$Comp
L Jumper:SolderJumper_3_Open IO2
U 1 1 5BF6F90F
P 5750 3800
F 0 "IO2" V 5796 3868 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 5705 3868 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 5750 3800 50  0001 C CNN
F 3 "~" H 5750 3800 50  0001 C CNN
	1    5750 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6750 2200 6750 4100
Wire Wire Line
	5550 4000 5750 4000
Wire Wire Line
	5900 3800 5900 3400
$Comp
L Jumper:SolderJumper_3_Open IO3
U 1 1 5BF73B3B
P 6000 3900
F 0 "IO3" V 6046 3968 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 5955 3968 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 6000 3900 50  0001 C CNN
F 3 "~" H 6000 3900 50  0001 C CNN
	1    6000 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6000 4100 5550 4100
Wire Wire Line
	6150 3500 6150 3900
$Comp
L Jumper:SolderJumper_3_Open IO5
U 1 1 5BF74A7B
P 6250 4100
F 0 "IO5" V 6296 4168 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 6205 4168 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 6250 4100 50  0001 C CNN
F 3 "~" H 6250 4100 50  0001 C CNN
	1    6250 4100
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open IO6
U 1 1 5BF74AAB
P 6500 4200
F 0 "IO6" V 6546 4268 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 6455 4268 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 6500 4200 50  0001 C CNN
F 3 "~" H 6500 4200 50  0001 C CNN
	1    6500 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 4300 5550 4300
Wire Wire Line
	6500 4400 5550 4400
Wire Wire Line
	5900 3400 7100 3400
Wire Wire Line
	6150 3500 7100 3500
Wire Wire Line
	6400 3600 6400 4100
Wire Wire Line
	6400 3600 7100 3600
Wire Wire Line
	6650 3700 6650 4200
Wire Wire Line
	6650 3700 7100 3700
NoConn ~ 4550 3600
NoConn ~ 4550 3900
NoConn ~ 4550 4000
NoConn ~ 4550 4300
NoConn ~ 4550 4400
NoConn ~ 4550 4500
NoConn ~ 5550 4500
NoConn ~ 5550 4200
NoConn ~ 5550 3900
NoConn ~ 5550 3800
NoConn ~ 5550 3600
NoConn ~ 5550 3300
NoConn ~ 5550 3200
NoConn ~ 5150 2800
Wire Wire Line
	5050 4800 5050 4850
Wire Wire Line
	5050 4850 5150 4850
Wire Wire Line
	5150 4850 5150 4800
Wire Wire Line
	5150 4850 5150 5150
Connection ~ 5150 4850
$Comp
L Device:C C2
U 1 1 5BF6CD78
P 5400 2450
F 0 "C2" H 5515 2496 50  0000 L CNN
F 1 "100nF" H 5515 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5438 2300 50  0001 C CNN
F 3 "~" H 5400 2450 50  0001 C CNN
	1    5400 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5BF6CE4A
P 4800 2450
F 0 "C1" H 4915 2496 50  0000 L CNN
F 1 "100nF" H 4915 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4838 2300 50  0001 C CNN
F 3 "~" H 4800 2450 50  0001 C CNN
	1    4800 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5BF6DF10
P 4800 2650
F 0 "#PWR0102" H 4800 2400 50  0001 C CNN
F 1 "GND" H 4805 2477 50  0000 C CNN
F 2 "" H 4800 2650 50  0001 C CNN
F 3 "" H 4800 2650 50  0001 C CNN
	1    4800 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5BF6DF2F
P 5400 2650
F 0 "#PWR0105" H 5400 2400 50  0001 C CNN
F 1 "GND" H 5405 2477 50  0000 C CNN
F 2 "" H 5400 2650 50  0001 C CNN
F 3 "" H 5400 2650 50  0001 C CNN
	1    5400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2300 5250 2300
Wire Wire Line
	5250 2300 5250 2800
Wire Wire Line
	4950 2300 4800 2300
Connection ~ 4950 2300
Wire Wire Line
	4950 2300 4950 2800
$Comp
L SS_connectors:PJ-063AH J1
U 1 1 5BF7FA3A
P 4250 2300
F 0 "J1" H 4219 2640 50  0000 C CNN
F 1 "PJ-063AH" H 4219 2549 50  0000 C CNN
F 2 "SS_connectors:CUI_PJ-063AH-1" H 4250 2300 50  0001 L BNN
F 3 "https://www.digikey.fi/product-detail/en/cui-inc/PJ-063AH/CP-063AH-ND/2161208" H 4250 2300 50  0001 L BNN
F 4 "CUI INC" H 4250 2300 50  0001 L BNN "Field4"
F 5 "1.02" H 4250 2300 50  0001 L BNN "Field5"
	1    4250 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2500 4550 2500
Wire Wire Line
	4550 2550 4550 2500
Connection ~ 4550 2500
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5BF82757
P 4950 1800
F 0 "J2" V 5010 2040 50  0000 L CNN
F 1 "Conn_01x05_Male" V 5101 2040 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 4950 1800 50  0001 C CNN
F 3 "~" H 4950 1800 50  0001 C CNN
	1    4950 1800
	0    -1   1    0   
$EndComp
Wire Wire Line
	4550 2400 4550 2100
Connection ~ 4550 2400
Wire Wire Line
	4950 2000 4950 2300
Wire Wire Line
	5050 2000 5050 2200
Connection ~ 5050 2200
Wire Wire Line
	5050 2200 4450 2200
Wire Wire Line
	5050 2200 6750 2200
Wire Wire Line
	5250 2300 5250 2100
Wire Wire Line
	5250 2100 5150 2100
Wire Wire Line
	5150 2100 5150 2000
Connection ~ 5250 2300
Wire Wire Line
	4550 2100 4750 2100
Wire Wire Line
	4750 2100 4750 2000
NoConn ~ 4850 2000
$Comp
L Connector:Conn_01x10_Male J3
U 1 1 5BF89C91
P 7300 3700
F 0 "J3" H 7273 3580 50  0000 R CNN
F 1 "Conn_01x10_Male" H 7273 3671 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 7300 3700 50  0001 C CNN
F 3 "~" H 7300 3700 50  0001 C CNN
	1    7300 3700
	-1   0    0    1   
$EndComp
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
Text GLabel 4400 3200 0    50   Input ~ 0
D0
Text GLabel 4400 3300 0    50   Input ~ 0
D1
Wire Wire Line
	4400 3200 4550 3200
Wire Wire Line
	4400 3300 4550 3300
Wire Wire Line
	4400 3400 4550 3400
Wire Wire Line
	4400 3700 4550 3700
Wire Wire Line
	4400 4100 4550 4100
Text GLabel 7000 3200 0    50   Input ~ 0
D0
Text GLabel 7000 3300 0    50   Input ~ 0
D1
Wire Wire Line
	7000 3200 7100 3200
Wire Wire Line
	7100 3300 7000 3300
Wire Wire Line
	5400 2600 5400 2650
Wire Wire Line
	4800 2600 4800 2650
$EndSCHEMATC
