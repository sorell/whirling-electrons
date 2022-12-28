EESchema Schematic File Version 4
LIBS:advent-calendar-rnd-cache
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
NoConn ~ 8400 2600
NoConn ~ 8400 2500
$Comp
L MCU_Module:Arduino_Nano_v3.x A?
U 1 1 5DB07718
P 8900 3100
F 0 "A?" H 8900 2014 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 8900 1923 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 9050 2150 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 8900 2100 50  0001 C CNN
	1    8900 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB08403
P 4450 4150
F 0 "D?" H 4441 4366 50  0000 C CNN
F 1 "LED" H 4441 4275 50  0000 C CNN
F 2 "" H 4450 4150 50  0001 C CNN
F 3 "~" H 4450 4150 50  0001 C CNN
	1    4450 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB084D3
P 3800 4150
F 0 "D?" H 3791 4366 50  0000 C CNN
F 1 "LED" H 3791 4275 50  0000 C CNN
F 2 "" H 3800 4150 50  0001 C CNN
F 3 "~" H 3800 4150 50  0001 C CNN
	1    3800 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4150 4650 4150
Wire Wire Line
	4650 4150 4650 4300
Wire Wire Line
	4650 4300 4000 4300
Wire Wire Line
	4000 4300 4000 4150
Wire Wire Line
	4000 4150 3950 4150
$Comp
L Device:LED D?
U 1 1 5DB08661
P 3150 4150
F 0 "D?" H 3141 4366 50  0000 C CNN
F 1 "LED" H 3141 4275 50  0000 C CNN
F 2 "" H 3150 4150 50  0001 C CNN
F 3 "~" H 3150 4150 50  0001 C CNN
	1    3150 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4300 3350 4300
Wire Wire Line
	3350 4300 3350 4150
Wire Wire Line
	3350 4150 3300 4150
Connection ~ 4000 4300
$Comp
L Device:LED D?
U 1 1 5DB08971
P 4450 4600
F 0 "D?" H 4441 4816 50  0000 C CNN
F 1 "LED" H 4441 4725 50  0000 C CNN
F 2 "" H 4450 4600 50  0001 C CNN
F 3 "~" H 4450 4600 50  0001 C CNN
	1    4450 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4150 4250 4150
Wire Wire Line
	4250 4150 4250 4600
Wire Wire Line
	4250 4600 4300 4600
$Comp
L Device:LED D?
U 1 1 5DB08AC1
P 3800 4600
F 0 "D?" H 3791 4816 50  0000 C CNN
F 1 "LED" H 3791 4725 50  0000 C CNN
F 2 "" H 3800 4600 50  0001 C CNN
F 3 "~" H 3800 4600 50  0001 C CNN
	1    3800 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB08AF5
P 3150 4600
F 0 "D?" H 3141 4816 50  0000 C CNN
F 1 "LED" H 3141 4725 50  0000 C CNN
F 2 "" H 3150 4600 50  0001 C CNN
F 3 "~" H 3150 4600 50  0001 C CNN
	1    3150 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4150 3600 4150
Wire Wire Line
	3600 4150 3600 4600
Wire Wire Line
	3600 4600 3650 4600
Wire Wire Line
	3000 4150 2950 4150
Wire Wire Line
	2950 4150 2950 4600
Wire Wire Line
	2950 4600 3000 4600
$Comp
L Device:LED D?
U 1 1 5DB08F2E
P 2500 4150
F 0 "D?" H 2491 4366 50  0000 C CNN
F 1 "LED" H 2491 4275 50  0000 C CNN
F 2 "" H 2500 4150 50  0001 C CNN
F 3 "~" H 2500 4150 50  0001 C CNN
	1    2500 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4300 2700 4300
Wire Wire Line
	2700 4300 2700 4150
Wire Wire Line
	2700 4150 2650 4150
Connection ~ 3350 4300
$Comp
L Device:LED D?
U 1 1 5DB09295
P 2500 4600
F 0 "D?" H 2491 4816 50  0000 C CNN
F 1 "LED" H 2491 4725 50  0000 C CNN
F 2 "" H 2500 4600 50  0001 C CNN
F 3 "~" H 2500 4600 50  0001 C CNN
	1    2500 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4150 2300 4150
Wire Wire Line
	2300 4150 2300 4600
Wire Wire Line
	2300 4600 2350 4600
Wire Wire Line
	4600 4600 4650 4600
Wire Wire Line
	4650 4600 4650 4750
Wire Wire Line
	4650 4750 4000 4750
Wire Wire Line
	4000 4750 4000 4600
Wire Wire Line
	4000 4600 3950 4600
Wire Wire Line
	4000 4750 3350 4750
Wire Wire Line
	3350 4750 3350 4600
Wire Wire Line
	3350 4600 3300 4600
Connection ~ 4000 4750
Wire Wire Line
	3350 4750 2700 4750
Wire Wire Line
	2700 4750 2700 4600
Wire Wire Line
	2700 4600 2650 4600
Connection ~ 3350 4750
$Comp
L Device:LED D?
U 1 1 5DB0AAF7
P 4450 5050
F 0 "D?" H 4441 5266 50  0000 C CNN
F 1 "LED" H 4441 5175 50  0000 C CNN
F 2 "" H 4450 5050 50  0001 C CNN
F 3 "~" H 4450 5050 50  0001 C CNN
	1    4450 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB0AAFE
P 3800 5050
F 0 "D?" H 3791 5266 50  0000 C CNN
F 1 "LED" H 3791 5175 50  0000 C CNN
F 2 "" H 3800 5050 50  0001 C CNN
F 3 "~" H 3800 5050 50  0001 C CNN
	1    3800 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 5050 4650 5050
Wire Wire Line
	4650 5050 4650 5200
Wire Wire Line
	4650 5200 4000 5200
Wire Wire Line
	4000 5200 4000 5050
Wire Wire Line
	4000 5050 3950 5050
$Comp
L Device:LED D?
U 1 1 5DB0AB0A
P 3150 5050
F 0 "D?" H 3141 5266 50  0000 C CNN
F 1 "LED" H 3141 5175 50  0000 C CNN
F 2 "" H 3150 5050 50  0001 C CNN
F 3 "~" H 3150 5050 50  0001 C CNN
	1    3150 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5200 3350 5200
Wire Wire Line
	3350 5200 3350 5050
Wire Wire Line
	3350 5050 3300 5050
Connection ~ 4000 5200
$Comp
L Device:LED D?
U 1 1 5DB0AB15
P 4450 5500
F 0 "D?" H 4441 5716 50  0000 C CNN
F 1 "LED" H 4441 5625 50  0000 C CNN
F 2 "" H 4450 5500 50  0001 C CNN
F 3 "~" H 4450 5500 50  0001 C CNN
	1    4450 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 5050 4250 5050
Wire Wire Line
	4250 5050 4250 5500
Wire Wire Line
	4250 5500 4300 5500
$Comp
L Device:LED D?
U 1 1 5DB0AB1F
P 3800 5500
F 0 "D?" H 3791 5716 50  0000 C CNN
F 1 "LED" H 3791 5625 50  0000 C CNN
F 2 "" H 3800 5500 50  0001 C CNN
F 3 "~" H 3800 5500 50  0001 C CNN
	1    3800 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB0AB26
P 3150 5500
F 0 "D?" H 3141 5716 50  0000 C CNN
F 1 "LED" H 3141 5625 50  0000 C CNN
F 2 "" H 3150 5500 50  0001 C CNN
F 3 "~" H 3150 5500 50  0001 C CNN
	1    3150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5050 3600 5050
Wire Wire Line
	3600 5050 3600 5500
Wire Wire Line
	3600 5500 3650 5500
Wire Wire Line
	3000 5050 2950 5050
Wire Wire Line
	2950 5050 2950 5500
Wire Wire Line
	2950 5500 3000 5500
$Comp
L Device:LED D?
U 1 1 5DB0AB33
P 2500 5050
F 0 "D?" H 2491 5266 50  0000 C CNN
F 1 "LED" H 2491 5175 50  0000 C CNN
F 2 "" H 2500 5050 50  0001 C CNN
F 3 "~" H 2500 5050 50  0001 C CNN
	1    2500 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5200 2700 5200
Wire Wire Line
	2700 5200 2700 5050
Wire Wire Line
	2700 5050 2650 5050
Connection ~ 3350 5200
$Comp
L Device:LED D?
U 1 1 5DB0AB3E
P 2500 5500
F 0 "D?" H 2491 5716 50  0000 C CNN
F 1 "LED" H 2491 5625 50  0000 C CNN
F 2 "" H 2500 5500 50  0001 C CNN
F 3 "~" H 2500 5500 50  0001 C CNN
	1    2500 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5050 2300 5050
Wire Wire Line
	2300 5050 2300 5500
Wire Wire Line
	2300 5500 2350 5500
Wire Wire Line
	4600 5500 4650 5500
Wire Wire Line
	4650 5500 4650 5650
Wire Wire Line
	4650 5650 4000 5650
Wire Wire Line
	4000 5650 4000 5500
Wire Wire Line
	4000 5500 3950 5500
Wire Wire Line
	4000 5650 3350 5650
Wire Wire Line
	3350 5650 3350 5500
Wire Wire Line
	3350 5500 3300 5500
Connection ~ 4000 5650
Wire Wire Line
	3350 5650 2700 5650
Wire Wire Line
	2700 5650 2700 5500
Wire Wire Line
	2700 5500 2650 5500
Connection ~ 3350 5650
Wire Wire Line
	4250 4600 4250 5050
Connection ~ 4250 4600
Connection ~ 4250 5050
Wire Wire Line
	3600 4600 3600 5050
Connection ~ 3600 4600
Connection ~ 3600 5050
Wire Wire Line
	2950 4600 2950 5050
Connection ~ 2950 4600
Connection ~ 2950 5050
Wire Wire Line
	2300 4600 2300 5050
Connection ~ 2300 4600
Connection ~ 2300 5050
$Comp
L Device:LED D?
U 1 1 5DB1325E
P 5750 4150
F 0 "D?" H 5741 4366 50  0000 C CNN
F 1 "LED" H 5741 4275 50  0000 C CNN
F 2 "" H 5750 4150 50  0001 C CNN
F 3 "~" H 5750 4150 50  0001 C CNN
	1    5750 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB13265
P 5100 4150
F 0 "D?" H 5091 4366 50  0000 C CNN
F 1 "LED" H 5091 4275 50  0000 C CNN
F 2 "" H 5100 4150 50  0001 C CNN
F 3 "~" H 5100 4150 50  0001 C CNN
	1    5100 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4150 5950 4150
Wire Wire Line
	5950 4150 5950 4300
Wire Wire Line
	5950 4300 5300 4300
Wire Wire Line
	5300 4300 5300 4150
Wire Wire Line
	5300 4150 5250 4150
$Comp
L Device:LED D?
U 1 1 5DB13273
P 5750 4600
F 0 "D?" H 5741 4816 50  0000 C CNN
F 1 "LED" H 5741 4725 50  0000 C CNN
F 2 "" H 5750 4600 50  0001 C CNN
F 3 "~" H 5750 4600 50  0001 C CNN
	1    5750 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4150 5550 4150
Wire Wire Line
	5550 4150 5550 4600
Wire Wire Line
	5550 4600 5600 4600
$Comp
L Device:LED D?
U 1 1 5DB1327D
P 5100 4600
F 0 "D?" H 5091 4816 50  0000 C CNN
F 1 "LED" H 5091 4725 50  0000 C CNN
F 2 "" H 5100 4600 50  0001 C CNN
F 3 "~" H 5100 4600 50  0001 C CNN
	1    5100 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4150 4900 4150
Wire Wire Line
	4900 4150 4900 4600
Wire Wire Line
	4900 4600 4950 4600
Wire Wire Line
	5900 4600 5950 4600
Wire Wire Line
	5950 4600 5950 4750
Wire Wire Line
	5950 4750 5300 4750
Wire Wire Line
	5300 4750 5300 4600
Wire Wire Line
	5300 4600 5250 4600
$Comp
L Device:LED D?
U 1 1 5DB1328E
P 5750 5050
F 0 "D?" H 5741 5266 50  0000 C CNN
F 1 "LED" H 5741 5175 50  0000 C CNN
F 2 "" H 5750 5050 50  0001 C CNN
F 3 "~" H 5750 5050 50  0001 C CNN
	1    5750 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5DB13295
P 5100 5050
F 0 "D?" H 5091 5266 50  0000 C CNN
F 1 "LED" H 5091 5175 50  0000 C CNN
F 2 "" H 5100 5050 50  0001 C CNN
F 3 "~" H 5100 5050 50  0001 C CNN
	1    5100 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 5050 5950 5050
Wire Wire Line
	5950 5050 5950 5200
Wire Wire Line
	5950 5200 5300 5200
Wire Wire Line
	5300 5200 5300 5050
Wire Wire Line
	5300 5050 5250 5050
$Comp
L Device:LED D?
U 1 1 5DB132A3
P 5750 5500
F 0 "D?" H 5741 5716 50  0000 C CNN
F 1 "LED" H 5741 5625 50  0000 C CNN
F 2 "" H 5750 5500 50  0001 C CNN
F 3 "~" H 5750 5500 50  0001 C CNN
	1    5750 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 5050 5550 5050
Wire Wire Line
	5550 5050 5550 5500
Wire Wire Line
	5550 5500 5600 5500
$Comp
L Device:LED D?
U 1 1 5DB132AD
P 5100 5500
F 0 "D?" H 5091 5716 50  0000 C CNN
F 1 "LED" H 5091 5625 50  0000 C CNN
F 2 "" H 5100 5500 50  0001 C CNN
F 3 "~" H 5100 5500 50  0001 C CNN
	1    5100 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 5050 4900 5050
Wire Wire Line
	4900 5050 4900 5500
Wire Wire Line
	4900 5500 4950 5500
Wire Wire Line
	5900 5500 5950 5500
Wire Wire Line
	5950 5500 5950 5650
Wire Wire Line
	5950 5650 5300 5650
Wire Wire Line
	5300 5650 5300 5500
Wire Wire Line
	5300 5500 5250 5500
Wire Wire Line
	5550 4600 5550 5050
Connection ~ 5550 4600
Connection ~ 5550 5050
Wire Wire Line
	4900 4600 4900 5050
Connection ~ 4900 4600
Connection ~ 4900 5050
Wire Wire Line
	5300 5650 4650 5650
Connection ~ 5300 5650
Connection ~ 4650 5650
Wire Wire Line
	5300 5200 4650 5200
Connection ~ 5300 5200
Connection ~ 4650 5200
Wire Wire Line
	5300 4750 4650 4750
Connection ~ 5300 4750
Connection ~ 4650 4750
Wire Wire Line
	5300 4300 4650 4300
Connection ~ 5300 4300
Connection ~ 4650 4300
Wire Wire Line
	2300 5750 2300 5500
Connection ~ 2300 5500
Wire Wire Line
	2950 5800 2950 5500
Connection ~ 2950 5500
Wire Wire Line
	3600 5850 3600 5500
Connection ~ 3600 5500
Wire Wire Line
	4250 5900 4250 5500
Connection ~ 4250 5500
Wire Wire Line
	4900 5950 4900 5500
Connection ~ 4900 5500
Wire Wire Line
	5550 6000 5550 5500
Connection ~ 5550 5500
$Comp
L Device:R R?
U 1 1 5DB65CCC
P 6200 4150
F 0 "R?" V 5993 4150 50  0000 C CNN
F 1 "R" V 6084 4150 50  0000 C CNN
F 2 "" V 6130 4150 50  0001 C CNN
F 3 "~" H 6200 4150 50  0001 C CNN
	1    6200 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DB6E97F
P 6200 4600
F 0 "R?" V 5993 4600 50  0000 C CNN
F 1 "R" V 6084 4600 50  0000 C CNN
F 2 "" V 6130 4600 50  0001 C CNN
F 3 "~" H 6200 4600 50  0001 C CNN
	1    6200 4600
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DB6E9D3
P 6200 5050
F 0 "R?" V 5993 5050 50  0000 C CNN
F 1 "R" V 6084 5050 50  0000 C CNN
F 2 "" V 6130 5050 50  0001 C CNN
F 3 "~" H 6200 5050 50  0001 C CNN
	1    6200 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DB6EA29
P 6200 5500
F 0 "R?" V 5993 5500 50  0000 C CNN
F 1 "R" V 6084 5500 50  0000 C CNN
F 2 "" V 6130 5500 50  0001 C CNN
F 3 "~" H 6200 5500 50  0001 C CNN
	1    6200 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 4150 6050 4150
Connection ~ 5950 4150
Wire Wire Line
	6050 4600 5950 4600
Connection ~ 5950 4600
Wire Wire Line
	5950 5050 6050 5050
Connection ~ 5950 5050
Wire Wire Line
	6050 5500 5950 5500
Connection ~ 5950 5500
Wire Wire Line
	6500 4600 6350 4600
Wire Wire Line
	6550 5050 6350 5050
Wire Wire Line
	6600 5500 6350 5500
Wire Wire Line
	2300 5750 6700 5750
Wire Wire Line
	2950 5800 6750 5800
Wire Wire Line
	3600 5850 6800 5850
Wire Wire Line
	4250 5900 6850 5900
Wire Wire Line
	4900 5950 6900 5950
Wire Wire Line
	5550 6000 6950 6000
$Comp
L Switch:SW_Push SW?
U 1 1 5DBC17BA
P 6050 3100
F 0 "SW?" V 6096 3052 50  0000 R CNN
F 1 "SW_Push" V 6005 3052 50  0000 R CNN
F 2 "" H 6050 3300 50  0001 C CNN
F 3 "" H 6050 3300 50  0001 C CNN
	1    6050 3100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DBC18AA
P 6050 3400
F 0 "#PWR?" H 6050 3150 50  0001 C CNN
F 1 "GND" H 6055 3227 50  0000 C CNN
F 2 "" H 6050 3400 50  0001 C CNN
F 3 "" H 6050 3400 50  0001 C CNN
	1    6050 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3300 6050 3400
Wire Wire Line
	6450 4150 6350 4150
Wire Wire Line
	6050 2900 6050 2700
Wire Wire Line
	6050 2700 8400 2700
NoConn ~ 8400 3800
NoConn ~ 9400 2500
NoConn ~ 9400 2600
NoConn ~ 9400 2900
NoConn ~ 9400 3100
NoConn ~ 9400 3200
NoConn ~ 9400 3300
NoConn ~ 9400 3400
NoConn ~ 9400 3500
NoConn ~ 9400 3600
NoConn ~ 9400 3700
NoConn ~ 9400 3800
NoConn ~ 8800 2100
NoConn ~ 9000 2100
NoConn ~ 9100 2100
Wire Wire Line
	8900 4100 8900 4400
Wire Wire Line
	8900 4400 9000 4400
Wire Wire Line
	9000 4400 9000 4100
$Comp
L power:GND #PWR?
U 1 1 5DF849A6
P 9000 4500
F 0 "#PWR?" H 9000 4250 50  0001 C CNN
F 1 "GND" H 9005 4327 50  0000 C CNN
F 2 "" H 9000 4500 50  0001 C CNN
F 3 "" H 9000 4500 50  0001 C CNN
	1    9000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4400 9000 4500
Connection ~ 9000 4400
Wire Wire Line
	8400 3400 6450 3400
Wire Wire Line
	6450 3400 6450 4150
Wire Wire Line
	6500 4600 6500 3500
Wire Wire Line
	6500 3500 8400 3500
Wire Wire Line
	8400 3600 6550 3600
Wire Wire Line
	6550 3600 6550 5050
Wire Wire Line
	6600 5500 6600 3700
Wire Wire Line
	6600 3700 8400 3700
Wire Wire Line
	6700 5750 6700 2800
Wire Wire Line
	6700 2800 8400 2800
Wire Wire Line
	8400 2900 6750 2900
Wire Wire Line
	6750 2900 6750 5800
Wire Wire Line
	6800 5850 6800 3000
Wire Wire Line
	6800 3000 8400 3000
Wire Wire Line
	8400 3100 6850 3100
Wire Wire Line
	6850 3100 6850 5900
Wire Wire Line
	6900 5950 6900 3200
Wire Wire Line
	6900 3200 8400 3200
Wire Wire Line
	8400 3300 6950 3300
Wire Wire Line
	6950 3300 6950 6000
$EndSCHEMATC
