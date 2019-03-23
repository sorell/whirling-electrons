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
P 4000 4150
F 0 "A1" H 4000 3064 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 4000 2973 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 4150 3200 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4000 3150 50  0001 C CNN
	1    4000 4150
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Female J1
U 1 1 5C6DAAB6
P 9250 4250
F 0 "J1" H 9277 4276 50  0000 L CNN
F 1 "Conn_01x07_Female" H 9277 4185 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 9250 4250 50  0001 C CNN
F 3 "~" H 9250 4250 50  0001 C CNN
	1    9250 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 5C6E50A5
P 3950 2800
F 0 "#PWR0102" H 3950 2650 50  0001 C CNN
F 1 "+3V3" H 3965 2973 50  0000 C CNN
F 2 "" H 3950 2800 50  0001 C CNN
F 3 "" H 3950 2800 50  0001 C CNN
	1    3950 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5C6E50D2
P 3800 2800
F 0 "#PWR0103" H 3800 2650 50  0001 C CNN
F 1 "+5V" H 3815 2973 50  0000 C CNN
F 2 "" H 3800 2800 50  0001 C CNN
F 3 "" H 3800 2800 50  0001 C CNN
	1    3800 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4550 4500 4550
Wire Wire Line
	9050 4250 7750 4250
Wire Wire Line
	7750 4250 7750 4650
Wire Wire Line
	7750 4650 4500 4650
Wire Wire Line
	9050 4150 7650 4150
Wire Wire Line
	7650 4150 7650 4850
Wire Wire Line
	7650 4850 4500 4850
Wire Wire Line
	3800 3150 3800 2800
$Comp
L power:GND #PWR0104
U 1 1 5C6E6194
P 3950 5600
F 0 "#PWR0104" H 3950 5350 50  0001 C CNN
F 1 "GND" H 3955 5427 50  0000 C CNN
F 2 "" H 3950 5600 50  0001 C CNN
F 3 "" H 3950 5600 50  0001 C CNN
	1    3950 5600
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
	9050 3950 7500 3950
Wire Wire Line
	7500 3950 7500 4100
Wire Wire Line
	9050 4050 7750 4050
Wire Wire Line
	7750 4050 7750 3800
Text Notes 9350 4450 0    50   ~ 0
SSD1331 OLED
Wire Wire Line
	3900 5450 3950 5500
Wire Wire Line
	3950 5500 3950 5600
Wire Wire Line
	3950 5500 4000 5450
Wire Wire Line
	4000 5450 4000 5150
Connection ~ 3950 5500
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
	7500 2900 7500 3000
Wire Wire Line
	7500 3500 7500 3950
Connection ~ 7500 3950
$Comp
L Device:R R1
U 1 1 5C6EA0EF
P 7100 3550
F 0 "R1" H 7170 3596 50  0000 L CNN
F 1 "10k" H 7170 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7030 3550 50  0001 C CNN
F 3 "~" H 7100 3550 50  0001 C CNN
	1    7100 3550
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_Dual SW1
U 1 1 5C6EBFD0
P 5850 2050
F 0 "SW1" H 5850 2335 50  0000 C CNN
F 1 "SW_Push_Dual" H 5850 2244 50  0000 C CNN
F 2 "SS_Connectors:Push Button 12x12mm" H 5850 2250 50  0001 C CNN
F 3 "" H 5850 2250 50  0001 C CNN
	1    5850 2050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW2
U 1 1 5C6EEE95
P 5850 2650
F 0 "SW2" H 5850 2935 50  0000 C CNN
F 1 "SW_Push_Dual" H 5850 2844 50  0000 C CNN
F 2 "SS_Connectors:Push Button 12x12mm" H 5850 2850 50  0001 C CNN
F 3 "" H 5850 2850 50  0001 C CNN
	1    5850 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2650 5550 2650
Wire Wire Line
	6050 2650 6150 2650
Wire Wire Line
	6150 2650 6150 2850
Wire Wire Line
	6150 2850 6050 2850
Connection ~ 6150 2850
Wire Wire Line
	6150 2250 6150 2650
Connection ~ 6150 2650
Wire Wire Line
	6050 2250 6150 2250
Wire Wire Line
	6150 2050 6150 2250
Wire Wire Line
	6050 2050 6150 2050
Connection ~ 6150 2250
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
	7500 2700 7500 2600
$Comp
L Device:C C2
U 1 1 5C6E88E7
P 5550 3150
F 0 "C2" H 5665 3196 50  0000 L CNN
F 1 "1nF" H 5665 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5588 3000 50  0001 C CNN
F 3 "~" H 5550 3150 50  0001 C CNN
	1    5550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2650 5550 2850
Wire Wire Line
	6150 2850 6150 3350
Wire Wire Line
	5550 3300 5550 3350
Wire Wire Line
	5550 3350 6150 3350
Wire Wire Line
	4950 2250 5250 2250
Connection ~ 5250 2250
Wire Wire Line
	5250 2250 5650 2250
Wire Wire Line
	5650 2050 5250 2050
Wire Wire Line
	5250 2050 5250 2250
NoConn ~ 4100 3150
NoConn ~ 4500 3550
NoConn ~ 4500 3650
NoConn ~ 3500 4150
NoConn ~ 3500 4250
NoConn ~ 3500 4350
NoConn ~ 3500 4450
NoConn ~ 3500 4550
NoConn ~ 3500 4650
NoConn ~ 3500 4750
NoConn ~ 3500 4850
NoConn ~ 3500 3950
NoConn ~ 3500 3650
NoConn ~ 3500 3550
NoConn ~ 4500 4750
$Comp
L power:GND #PWR0101
U 1 1 5C714566
P 5550 3450
F 0 "#PWR0101" H 5550 3200 50  0001 C CNN
F 1 "GND" H 5555 3277 50  0000 C CNN
F 2 "" H 5550 3450 50  0001 C CNN
F 3 "" H 5550 3450 50  0001 C CNN
	1    5550 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3350 5550 3350
Connection ~ 5550 3350
Wire Wire Line
	5650 2850 5550 2850
Connection ~ 5550 2850
Wire Wire Line
	5550 2850 5550 3000
NoConn ~ 4500 3950
NoConn ~ 4500 4050
NoConn ~ 4500 4250
Wire Wire Line
	3900 5150 3900 5450
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
	9050 4450 6650 4450
Wire Wire Line
	6650 4450 6550 4350
Wire Wire Line
	6550 4350 4500 4350
Wire Wire Line
	9050 4350 6650 4350
Wire Wire Line
	6650 4350 6550 4450
Wire Wire Line
	6550 4450 4500 4450
Wire Wire Line
	3950 2800 3950 2950
Wire Wire Line
	3950 2950 3900 2950
Wire Wire Line
	3900 2950 3900 3150
Wire Wire Line
	5550 3350 5550 3450
$Comp
L power:GND #PWR0107
U 1 1 5C98F758
P 7100 3850
F 0 "#PWR0107" H 7100 3600 50  0001 C CNN
F 1 "GND" H 7105 3677 50  0000 C CNN
F 2 "" H 7100 3850 50  0001 C CNN
F 3 "" H 7100 3850 50  0001 C CNN
	1    7100 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3700 7100 3850
Wire Wire Line
	7200 3300 7100 3300
Wire Wire Line
	7100 3300 7100 3400
Wire Wire Line
	7100 3300 6850 3300
Wire Wire Line
	6850 3300 6850 4150
Wire Wire Line
	6850 4150 4500 4150
Connection ~ 7100 3300
$Comp
L Device:C C1
U 1 1 5C9A3DB7
P 5250 2450
F 0 "C1" H 5365 2496 50  0000 L CNN
F 1 "1nF" H 5365 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5288 2300 50  0001 C CNN
F 3 "~" H 5250 2450 50  0001 C CNN
	1    5250 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2300 5250 2250
Wire Wire Line
	5250 2600 5250 3350
Wire Wire Line
	5050 2850 5550 2850
$Comp
L Device:R R2
U 1 1 5C9AE1BE
P 7300 2800
F 0 "R2" H 7370 2846 50  0000 L CNN
F 1 "1k" H 7370 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7230 2800 50  0001 C CNN
F 3 "~" H 7300 2800 50  0001 C CNN
	1    7300 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	7300 2650 7300 2600
Wire Wire Line
	7300 2600 7500 2600
Connection ~ 7500 2600
Wire Wire Line
	7500 2600 7500 2550
Wire Wire Line
	7500 3000 7300 3000
Wire Wire Line
	7300 3000 7300 2950
Connection ~ 7500 3000
Wire Wire Line
	7500 3000 7500 3100
Wire Wire Line
	4950 2250 4950 3750
Wire Wire Line
	4950 3750 4500 3750
Wire Wire Line
	5050 2850 5050 3850
Wire Wire Line
	5050 3850 4500 3850
$EndSCHEMATC
