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
P 7600 4250
F 0 "J1" H 7627 4276 50  0000 L CNN
F 1 "Conn_01x07_Female" H 7627 4185 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 7600 4250 50  0001 C CNN
F 3 "~" H 7600 4250 50  0001 C CNN
	1    7600 4250
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
	7400 4350 5400 4350
Wire Wire Line
	5400 4450 7400 4450
Wire Wire Line
	7400 4550 5400 4550
Wire Wire Line
	7400 4250 7300 4250
Wire Wire Line
	7300 4250 7300 4650
Wire Wire Line
	7300 4650 5400 4650
Wire Wire Line
	7400 4150 7200 4150
Wire Wire Line
	7200 4150 7200 4850
Wire Wire Line
	7200 4850 5400 4850
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
P 7300 3800
F 0 "#PWR0105" H 7300 3650 50  0001 C CNN
F 1 "+3V3" H 7315 3973 50  0000 C CNN
F 2 "" H 7300 3800 50  0001 C CNN
F 3 "" H 7300 3800 50  0001 C CNN
	1    7300 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5C6E6E1C
P 7050 4100
F 0 "#PWR0106" H 7050 3850 50  0001 C CNN
F 1 "GND" H 7055 3927 50  0000 C CNN
F 2 "" H 7050 4100 50  0001 C CNN
F 3 "" H 7050 4100 50  0001 C CNN
	1    7050 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3950 7050 3950
Wire Wire Line
	7050 3950 7050 4100
Wire Wire Line
	7400 4050 7300 4050
Wire Wire Line
	7300 4050 7300 3800
Text Notes 7700 4450 0    50   ~ 0
SSD1331 OLED
Wire Wire Line
	4800 5150 4800 5400
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
P 7150 2850
F 0 "BZ1" H 7303 2879 50  0000 L CNN
F 1 "Buzzer" H 7303 2788 50  0000 L CNN
F 2 "" V 7125 2950 50  0001 C CNN
F 3 "~" V 7125 2950 50  0001 C CNN
	1    7150 2850
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5C6E893E
P 6950 3350
F 0 "Q1" H 7155 3396 50  0000 L CNN
F 1 "2N7002" H 7155 3305 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7150 3275 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 6950 3350 50  0001 L CNN
	1    6950 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2950 7050 3150
Wire Wire Line
	7050 3550 7050 3950
Connection ~ 7050 3950
$Comp
L Device:R R1
U 1 1 5C6EA0EF
P 6650 3100
F 0 "R1" H 6720 3146 50  0000 L CNN
F 1 "10k" H 6720 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6580 3100 50  0001 C CNN
F 3 "~" H 6650 3100 50  0001 C CNN
	1    6650 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 5C6EA18F
P 6650 2850
F 0 "#PWR0107" H 6650 2700 50  0001 C CNN
F 1 "+5V" H 6665 3023 50  0000 C CNN
F 2 "" H 6650 2850 50  0001 C CNN
F 3 "" H 6650 2850 50  0001 C CNN
	1    6650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2850 6650 2950
Wire Wire Line
	6650 3250 6650 3350
Wire Wire Line
	6650 3350 6750 3350
$Comp
L Switch:SW_Push_Dual SW1
U 1 1 5C6EBFD0
P 5950 3000
F 0 "SW1" H 5950 3285 50  0000 C CNN
F 1 "SW_Push_Dual" H 5950 3194 50  0000 C CNN
F 2 "" H 5950 3200 50  0001 C CNN
F 3 "" H 5950 3200 50  0001 C CNN
	1    5950 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3000 5750 3000
Wire Wire Line
	5650 3000 5650 3200
Wire Wire Line
	5750 3200 5650 3200
Connection ~ 5650 3200
Wire Wire Line
	5650 3750 5400 3750
Wire Wire Line
	5650 3200 5650 3750
$Comp
L Switch:SW_Push_Dual SW2
U 1 1 5C6EEE95
P 6050 3650
F 0 "SW2" H 6050 3935 50  0000 C CNN
F 1 "SW_Push_Dual" H 6050 3844 50  0000 C CNN
F 2 "" H 6050 3850 50  0001 C CNN
F 3 "" H 6050 3850 50  0001 C CNN
	1    6050 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4250 6650 4250
Wire Wire Line
	6650 4250 6650 3350
Connection ~ 6650 3350
Wire Wire Line
	5400 3850 5750 3850
Wire Wire Line
	5850 3650 5750 3650
Wire Wire Line
	5750 3650 5750 3850
Connection ~ 5750 3850
Wire Wire Line
	5750 3850 5850 3850
Wire Wire Line
	6250 3650 6350 3650
Wire Wire Line
	6350 3650 6350 3850
Wire Wire Line
	6350 3850 6250 3850
$Comp
L power:GND #PWR0101
U 1 1 5C6F4A9A
P 6350 3950
F 0 "#PWR0101" H 6350 3700 50  0001 C CNN
F 1 "GND" H 6355 3777 50  0000 C CNN
F 2 "" H 6350 3950 50  0001 C CNN
F 3 "" H 6350 3950 50  0001 C CNN
	1    6350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3850 6350 3950
Connection ~ 6350 3850
Wire Wire Line
	6350 3200 6350 3650
Connection ~ 6350 3650
Wire Wire Line
	6150 3200 6350 3200
Wire Wire Line
	6350 3000 6350 3200
Wire Wire Line
	6150 3000 6350 3000
Connection ~ 6350 3200
$Comp
L power:+5V #PWR0108
U 1 1 5C6F65F8
P 7050 2600
F 0 "#PWR0108" H 7050 2450 50  0001 C CNN
F 1 "+5V" H 7065 2773 50  0000 C CNN
F 2 "" H 7050 2600 50  0001 C CNN
F 3 "" H 7050 2600 50  0001 C CNN
	1    7050 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2750 7050 2600
$EndSCHEMATC
