EESchema Schematic File Version 4
LIBS:parking-timer-cache
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
L parking-timer-kicad:RDA5807M U1
U 1 1 5FA6ADE6
P 8800 3250
F 0 "U1" H 8800 3715 50  0000 C CNN
F 1 "RDA5807M" H 8800 3624 50  0000 C CNN
F 2 "parking-timer-pcb:RDA5807M-through-hole" H 8800 3350 50  0001 C CNN
F 3 "" H 8800 3350 50  0001 C CNN
	1    8800 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:Antenna AE1
U 1 1 5FA7C4B6
P 9550 1850
F 0 "AE1" H 9630 1841 50  0000 L CNN
F 1 "Antenna" H 9630 1750 50  0000 L CNN
F 2 "parking-timer-pcb:FM-printed-antenna" H 9550 1850 50  0001 C CNN
F 3 "~" H 9550 1850 50  0001 C CNN
	1    9550 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5FA7D28D
P 9950 2950
F 0 "C2" V 9698 2950 50  0000 C CNN
F 1 "68pF" V 9789 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9988 2800 50  0001 C CNN
F 3 "~" H 9950 2950 50  0001 C CNN
	1    9950 2950
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5FA7D338
P 9950 2550
F 0 "C1" V 9698 2550 50  0000 C CNN
F 1 "82pF" V 9789 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9988 2400 50  0001 C CNN
F 3 "~" H 9950 2550 50  0001 C CNN
	1    9950 2550
	0    1    1    0   
$EndComp
$Comp
L Device:L L2
U 1 1 5FA7D3B3
P 9550 2750
F 0 "L2" H 9603 2796 50  0000 L CNN
F 1 "100nH" H 9603 2705 50  0000 L CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 9550 2750 50  0001 C CNN
F 3 "~" H 9550 2750 50  0001 C CNN
	1    9550 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5FA7D447
P 9550 2350
F 0 "L1" H 9603 2396 50  0000 L CNN
F 1 "1.5nH" H 9603 2305 50  0000 L CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 9550 2350 50  0001 C CNN
F 3 "~" H 9550 2350 50  0001 C CNN
	1    9550 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:L L3
U 1 1 5FA7D46F
P 9950 2150
F 0 "L3" V 10140 2150 50  0000 C CNN
F 1 "68nH" V 10049 2150 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 9950 2150 50  0001 C CNN
F 3 "~" H 9950 2150 50  0001 C CNN
	1    9950 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9550 2900 9550 2950
Wire Wire Line
	9550 3050 9400 3050
Wire Wire Line
	9550 2950 9800 2950
Connection ~ 9550 2950
Wire Wire Line
	9550 2950 9550 3050
Wire Wire Line
	9800 2550 9550 2550
Wire Wire Line
	9550 2550 9550 2500
Wire Wire Line
	9550 2600 9550 2550
Connection ~ 9550 2550
Wire Wire Line
	9800 2150 9550 2150
Wire Wire Line
	9550 2150 9550 2200
Wire Wire Line
	9550 2050 9550 2150
Connection ~ 9550 2150
$EndSCHEMATC
