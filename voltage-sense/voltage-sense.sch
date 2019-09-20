EESchema Schematic File Version 4
LIBS:voltage-sense-cache
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
L Comparator:LMV331 U?
U 1 1 5D849803
P 4500 3200
F 0 "U?" H 4841 3246 50  0000 L CNN
F 1 "LMV331" H 4841 3155 50  0000 L CNN
F 2 "" H 4500 3300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lmv331.pdf" H 4500 3400 50  0001 C CNN
	1    4500 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D84990B
P 4400 3950
F 0 "#PWR?" H 4400 3700 50  0001 C CNN
F 1 "GND" H 4405 3777 50  0000 C CNN
F 2 "" H 4400 3950 50  0001 C CNN
F 3 "" H 4400 3950 50  0001 C CNN
	1    4400 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5D849947
P 2900 2400
F 0 "#PWR?" H 2900 2250 50  0001 C CNN
F 1 "+5V" H 2915 2573 50  0000 C CNN
F 2 "" H 2900 2400 50  0001 C CNN
F 3 "" H 2900 2400 50  0001 C CNN
	1    2900 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2600 4400 2900
$Comp
L Device:CP1 C?
U 1 1 5D84AE0F
P 3800 2850
F 0 "C?" H 3915 2896 50  0000 L CNN
F 1 "CP1" H 3915 2805 50  0000 L CNN
F 2 "" H 3800 2850 50  0001 C CNN
F 3 "~" H 3800 2850 50  0001 C CNN
	1    3800 2850
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 5D84AEB5
P 3400 2600
F 0 "D?" H 3400 2865 50  0000 C CNN
F 1 "DIODE" H 3400 2774 50  0000 C CNN
F 2 "" H 3400 2600 50  0001 C CNN
F 3 "~" H 3400 2600 50  0001 C CNN
	1    3400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2400 2900 2600
Wire Wire Line
	2900 2600 3200 2600
Wire Wire Line
	3600 2600 3800 2600
Wire Wire Line
	3800 2600 3800 2700
$Comp
L Device:R R?
U 1 1 5D84AFD4
P 2900 2850
F 0 "R?" H 2970 2896 50  0000 L CNN
F 1 "R" H 2970 2805 50  0000 L CNN
F 2 "" V 2830 2850 50  0001 C CNN
F 3 "~" H 2900 2850 50  0001 C CNN
	1    2900 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D84B08A
P 2900 3350
F 0 "R?" H 2970 3396 50  0000 L CNN
F 1 "R" H 2970 3305 50  0000 L CNN
F 2 "" V 2830 3350 50  0001 C CNN
F 3 "~" H 2900 3350 50  0001 C CNN
	1    2900 3350
	1    0    0    -1  
$EndComp
Connection ~ 3800 2600
Wire Wire Line
	4400 3500 4400 3800
Wire Wire Line
	2900 3800 3800 3800
Connection ~ 4400 3800
Wire Wire Line
	4400 3800 4400 3950
Wire Wire Line
	3800 3000 3800 3800
Connection ~ 3800 3800
Wire Wire Line
	3800 3800 4400 3800
Wire Wire Line
	3800 2600 4150 2600
Wire Wire Line
	4200 3100 2900 3100
Wire Wire Line
	2900 3100 2900 3000
Wire Wire Line
	2900 2700 2900 2600
Connection ~ 2900 2600
Wire Wire Line
	2900 3100 2900 3200
Connection ~ 2900 3100
Wire Wire Line
	2900 3500 2900 3800
Wire Wire Line
	4200 3300 4150 3300
Wire Wire Line
	4150 3300 4150 2600
Connection ~ 4150 2600
Wire Wire Line
	4150 2600 4400 2600
$EndSCHEMATC
