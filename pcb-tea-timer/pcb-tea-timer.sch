EESchema Schematic File Version 4
LIBS:pcb-tea-timer-cache
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
U 1 1 5C6DAA22
P 4900 4150
F 0 "A1" H 4900 3064 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 4900 2973 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5050 3200 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4900 3150 50  0001 C CNN
	1    4900 4150
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Female J1
U 1 1 5C6DAAB6
P 8050 4250
F 0 "J1" H 8077 4276 50  0000 L CNN
F 1 "Conn_01x07_Female" H 8077 4185 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 8050 4250 50  0001 C CNN
F 3 "~" H 8050 4250 50  0001 C CNN
	1    8050 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 5C6E50A5
P 4900 2800
F 0 "#PWR0102" H 4900 2650 50  0001 C CNN
F 1 "+3V3" H 4915 2973 50  0000 C CNN
F 2 "" H 4900 2800 50  0001 C CNN
F 3 "" H 4900 2800 50  0001 C CNN
	1    4900 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5C6E50D2
P 4700 2800
F 0 "#PWR0103" H 4700 2650 50  0001 C CNN
F 1 "+5V" H 4715 2973 50  0000 C CNN
F 2 "" H 4700 2800 50  0001 C CNN
F 3 "" H 4700 2800 50  0001 C CNN
	1    4700 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4550 5400 4550
Wire Wire Line
	7850 4250 7750 4250
Wire Wire Line
	7750 4250 7750 4650
Wire Wire Line
	7750 4650 5400 4650
Wire Wire Line
	7850 4150 7650 4150
Wire Wire Line
	7650 4150 7650 4850
Wire Wire Line
	7650 4850 5400 4850
Wire Wire Line
	4700 3150 4700 2800
Wire Wire Line
	4800 3150 4800 2950
Wire Wire Line
	4800 2950 4900 2950
Wire Wire Line
	4900 2950 4900 2800
$Comp
L power:GND #PWR0104
U 1 1 5C6E6194
P 4850 5450
F 0 "#PWR0104" H 4850 5200 50  0001 C CNN
F 1 "GND" H 4855 5277 50  0000 C CNN
F 2 "" H 4850 5450 50  0001 C CNN
F 3 "" H 4850 5450 50  0001 C CNN
	1    4850 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 5C6E6741
P 7750 3800
F 0 "#PWR0105" H 7750 3650 50  0001 C CNN
F 1 "+3V3" H 7765 3973 50  0000 C CNN
F 2 "" H 7750 3800 50  0001 C CNN
F 3 "" H 7750 3800 50  0001 C CNN
	1    7750 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5C6E6E1C
P 7500 4100
F 0 "#PWR0106" H 7500 3850 50  0001 C CNN
F 1 "GND" H 7505 3927 50  0000 C CNN
F 2 "" H 7500 4100 50  0001 C CNN
F 3 "" H 7500 4100 50  0001 C CNN
	1    7500 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 3950 7500 3950
Wire Wire Line
	7500 3950 7500 4100
Wire Wire Line
	7850 4050 7750 4050
Wire Wire Line
	7750 4050 7750 3800
Text Notes 8150 4450 0    50   ~ 0
SSD1331 OLED
Wire Wire Line
	4800 5400 4850 5400
Wire Wire Line
	4850 5400 4850 5450
Wire Wire Line
	4850 5400 4900 5400
Wire Wire Line
	4900 5400 4900 5150
Connection ~ 4850 5400
$Comp
L Device:Buzzer BZ1
U 1 1 5C6E8171
P 7600 2800
F 0 "BZ1" H 7753 2829 50  0000 L CNN
F 1 "Buzzer" H 7753 2738 50  0000 L CNN
F 2 "SS_Connectors:Round Piezo 1" V 7575 2900 50  0001 C CNN
F 3 "~" V 7575 2900 50  0001 C CNN
	1    7600 2800
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5C6E893E
P 7400 3300
F 0 "Q1" H 7605 3346 50  0000 L CNN
F 1 "2N7002" H 7605 3255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7600 3225 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 7400 3300 50  0001 L CNN
	1    7400 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2900 7500 3100
Wire Wire Line
	7500 3500 7500 3950
Connection ~ 7500 3950
$Comp
L Device:R R1
U 1 1 5C6EA0EF
P 6950 3300
F 0 "R1" H 7020 3346 50  0000 L CNN
F 1 "10k" H 7020 3255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6880 3300 50  0001 C CNN
F 3 "~" H 6950 3300 50  0001 C CNN
	1    6950 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 3300 7200 3300
$Comp
L Switch:SW_Push_Dual SW1
U 1 1 5C6EBFD0
P 6450 2650
F 0 "SW1" H 6450 2935 50  0000 C CNN
F 1 "SW_Push_Dual" H 6450 2844 50  0000 C CNN
F 2 "SS_Connectors:Push Button 12x12mm" H 6450 2850 50  0001 C CNN
F 3 "" H 6450 2850 50  0001 C CNN
	1    6450 2650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW2
U 1 1 5C6EEE95
P 6450 3300
F 0 "SW2" H 6450 3585 50  0000 C CNN
F 1 "SW_Push_Dual" H 6450 3494 50  0000 C CNN
F 2 "SS_Connectors:Push Button 12x12mm" H 6450 3500 50  0001 C CNN
F 3 "" H 6450 3500 50  0001 C CNN
	1    6450 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4250 7150 3300
Wire Wire Line
	6250 3300 6150 3300
Wire Wire Line
	6650 3300 6750 3300
Wire Wire Line
	6750 3300 6750 3500
Wire Wire Line
	6750 3500 6650 3500
Connection ~ 6750 3500
Wire Wire Line
	6750 2850 6750 3300
Connection ~ 6750 3300
Wire Wire Line
	6650 2850 6750 2850
Wire Wire Line
	6750 2650 6750 2850
Wire Wire Line
	6650 2650 6750 2650
Connection ~ 6750 2850
$Comp
L power:+5V #PWR0108
U 1 1 5C6F65F8
P 7500 2550
F 0 "#PWR0108" H 7500 2400 50  0001 C CNN
F 1 "+5V" H 7515 2723 50  0000 C CNN
F 2 "" H 7500 2550 50  0001 C CNN
F 3 "" H 7500 2550 50  0001 C CNN
	1    7500 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2700 7500 2550
$Comp
L Device:C C2
U 1 1 5C6E88E7
P 6150 3700
F 0 "C2" H 6265 3746 50  0000 L CNN
F 1 "1nF" H 6265 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6188 3550 50  0001 C CNN
F 3 "~" H 6150 3700 50  0001 C CNN
	1    6150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3300 6150 3500
Connection ~ 6150 3300
$Comp
L Device:C C1
U 1 1 5C6ED1EC
P 5850 3700
F 0 "C1" H 5965 3746 50  0000 L CNN
F 1 "1nF" H 5965 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5888 3550 50  0001 C CNN
F 3 "~" H 5850 3700 50  0001 C CNN
	1    5850 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3750 5400 3750
Wire Wire Line
	6750 3500 6750 3950
Wire Wire Line
	6150 3850 6150 3950
Wire Wire Line
	6150 3950 6750 3950
Wire Wire Line
	5550 2850 5850 2850
Wire Wire Line
	5550 2850 5550 3750
Connection ~ 5850 2850
Wire Wire Line
	5850 2850 6250 2850
Wire Wire Line
	6250 2650 5850 2650
Wire Wire Line
	5850 2650 5850 2850
Wire Wire Line
	5650 3300 5650 3850
Wire Wire Line
	5650 3850 5400 3850
Wire Wire Line
	5650 3300 6150 3300
NoConn ~ 5000 3150
NoConn ~ 5400 3550
NoConn ~ 5400 3650
NoConn ~ 4400 4150
NoConn ~ 4400 4250
NoConn ~ 4400 4350
NoConn ~ 4400 4450
NoConn ~ 4400 4550
NoConn ~ 4400 4650
NoConn ~ 4400 4750
NoConn ~ 4400 4850
NoConn ~ 4400 3950
NoConn ~ 4400 3650
NoConn ~ 4400 3550
NoConn ~ 5400 4750
$Comp
L power:GND #PWR0101
U 1 1 5C714566
P 6750 4000
F 0 "#PWR0101" H 6750 3750 50  0001 C CNN
F 1 "GND" H 6755 3827 50  0000 C CNN
F 2 "" H 6750 4000 50  0001 C CNN
F 3 "" H 6750 4000 50  0001 C CNN
	1    6750 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3950 6750 4000
Connection ~ 6750 3950
Wire Wire Line
	5850 2850 5850 3550
Wire Wire Line
	5850 3850 5850 3950
Wire Wire Line
	5850 3950 6150 3950
Connection ~ 6150 3950
Wire Wire Line
	6250 3500 6150 3500
Connection ~ 6150 3500
Wire Wire Line
	6150 3500 6150 3550
Wire Wire Line
	7150 4250 6150 4250
Wire Wire Line
	6150 4250 6150 4150
Wire Wire Line
	6150 4150 5400 4150
NoConn ~ 5400 3950
NoConn ~ 5400 4050
NoConn ~ 5400 4250
Wire Wire Line
	4800 5150 4800 5400
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 5C6F23C0
P 6250 5250
F 0 "J2" H 6277 5226 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6277 5135 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6250 5250 50  0001 C CNN
F 3 "~" H 6250 5250 50  0001 C CNN
	1    6250 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5C6F46C1
P 5950 5450
F 0 "#PWR0109" H 5950 5200 50  0001 C CNN
F 1 "GND" H 5955 5277 50  0000 C CNN
F 2 "" H 5950 5450 50  0001 C CNN
F 3 "" H 5950 5450 50  0001 C CNN
	1    5950 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5250 5950 5250
Wire Wire Line
	5950 5250 5950 5350
Wire Wire Line
	6050 5350 5950 5350
Connection ~ 5950 5350
Wire Wire Line
	5950 5350 5950 5450
Text Notes 6050 5500 0    50   ~ 0
Physical support for the display
Wire Wire Line
	7850 4450 6650 4450
Wire Wire Line
	6650 4450 6550 4350
Wire Wire Line
	6550 4350 5400 4350
Wire Wire Line
	7850 4350 6650 4350
Wire Wire Line
	6650 4350 6550 4450
Wire Wire Line
	6550 4450 5400 4450
Wire Wire Line
	7100 3300 7150 3300
Connection ~ 7150 3300
Wire Wire Line
	6800 3300 6750 3300
$EndSCHEMATC
