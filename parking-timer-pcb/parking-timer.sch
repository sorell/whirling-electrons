EESchema Schematic File Version 4
EELAYER 30 0
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
L Device:Antenna AE1
U 1 1 5FA7C4B6
P 10350 1800
F 0 "AE1" H 10430 1791 50  0000 L CNN
F 1 "Antenna" H 10430 1700 50  0000 L CNN
F 2 "parking-timer-pcb:FM-printed-antenna" H 10350 1800 50  0001 C CNN
F 3 "~" H 10350 1800 50  0001 C CNN
	1    10350 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5FA7D28D
P 10750 2900
F 0 "C2" V 10498 2900 50  0000 C CNN
F 1 "68pF" V 10589 2900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10788 2750 50  0001 C CNN
F 3 "~" H 10750 2900 50  0001 C CNN
	1    10750 2900
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5FA7D338
P 10750 2500
F 0 "C1" V 10498 2500 50  0000 C CNN
F 1 "82pF" V 10589 2500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10788 2350 50  0001 C CNN
F 3 "~" H 10750 2500 50  0001 C CNN
	1    10750 2500
	0    1    1    0   
$EndComp
$Comp
L Device:L L2
U 1 1 5FA7D3B3
P 10350 2700
F 0 "L2" H 10403 2746 50  0000 L CNN
F 1 "100nH" H 10403 2655 50  0000 L CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 10350 2700 50  0001 C CNN
F 3 "~" H 10350 2700 50  0001 C CNN
	1    10350 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5FA7D447
P 10350 2300
F 0 "L1" H 10403 2346 50  0000 L CNN
F 1 "1.5nH" H 10403 2255 50  0000 L CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 10350 2300 50  0001 C CNN
F 3 "~" H 10350 2300 50  0001 C CNN
	1    10350 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:L L3
U 1 1 5FA7D46F
P 10750 2100
F 0 "L3" V 10940 2100 50  0000 C CNN
F 1 "68nH" V 10849 2100 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 10750 2100 50  0001 C CNN
F 3 "~" H 10750 2100 50  0001 C CNN
	1    10750 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10350 2850 10350 2900
Wire Wire Line
	10350 3000 10200 3000
Wire Wire Line
	10350 2900 10600 2900
Connection ~ 10350 2900
Wire Wire Line
	10350 2900 10350 3000
Wire Wire Line
	10600 2500 10350 2500
Wire Wire Line
	10350 2500 10350 2450
Wire Wire Line
	10350 2550 10350 2500
Connection ~ 10350 2500
Wire Wire Line
	10600 2100 10350 2100
Wire Wire Line
	10350 2100 10350 2150
Wire Wire Line
	10350 2000 10350 2100
Connection ~ 10350 2100
$Comp
L power:GND #PWR0101
U 1 1 5FA8330E
P 11000 3000
F 0 "#PWR0101" H 11000 2750 50  0001 C CNN
F 1 "GND" H 11005 2827 50  0000 C CNN
F 2 "" H 11000 3000 50  0001 C CNN
F 3 "" H 11000 3000 50  0001 C CNN
	1    11000 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 2100 11000 2100
Wire Wire Line
	11000 2100 11000 2500
Wire Wire Line
	10900 2900 11000 2900
Connection ~ 11000 2900
Wire Wire Line
	11000 2900 11000 3000
Wire Wire Line
	10900 2500 11000 2500
Connection ~ 11000 2500
Wire Wire Line
	11000 2500 11000 2900
NoConn ~ 10200 3200
NoConn ~ 10200 3300
$Comp
L power:GND #PWR0102
U 1 1 5FA84BAF
P 10300 3500
F 0 "#PWR0102" H 10300 3250 50  0001 C CNN
F 1 "GND" H 10305 3327 50  0000 C CNN
F 2 "" H 10300 3500 50  0001 C CNN
F 3 "" H 10300 3500 50  0001 C CNN
	1    10300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 3400 10300 3400
Wire Wire Line
	10300 3400 10300 3500
Wire Wire Line
	9000 3400 8800 3400
$Comp
L Device:C C3
U 1 1 5FA89BD2
P 8800 3600
F 0 "C3" V 8548 3600 50  0000 C CNN
F 1 "100nF" V 8639 3600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8838 3450 50  0001 C CNN
F 3 "~" H 8800 3600 50  0001 C CNN
	1    8800 3600
	-1   0    0    1   
$EndComp
Connection ~ 8800 3400
Wire Wire Line
	8800 3350 8800 3400
Wire Wire Line
	8800 3400 8800 3450
$Comp
L power:GND #PWR0104
U 1 1 5FA8B7DD
P 8800 3800
F 0 "#PWR0104" H 8800 3550 50  0001 C CNN
F 1 "GND" H 8805 3627 50  0000 C CNN
F 2 "" H 8800 3800 50  0001 C CNN
F 3 "" H 8800 3800 50  0001 C CNN
	1    8800 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 3750 8800 3800
$Comp
L MCU_ST_STM8:STM8L101F3P U2
U 1 1 5FAA9DF4
P 5900 3600
F 0 "U2" H 5900 4681 50  0000 C CNN
F 1 "STM8L101F3P" H 5900 4590 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 5950 4600 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00220591.pdf" H 5900 3200 50  0001 C CNN
	1    5900 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5FAABB50
P 5900 4600
F 0 "#PWR0105" H 5900 4350 50  0001 C CNN
F 1 "GND" H 5905 4427 50  0000 C CNN
F 2 "" H 5900 4600 50  0001 C CNN
F 3 "" H 5900 4600 50  0001 C CNN
	1    5900 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4500 5900 4600
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J2
U 1 1 5FAC1F81
P 9450 5250
F 0 "J2" H 9500 5567 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 9500 5476 50  0000 C CNN
F 2 "parking-timer-pcb:ER-EPM029-1_Module" H 9450 5250 50  0001 C CNN
F 3 "~" H 9450 5250 50  0001 C CNN
	1    9450 5250
	1    0    0    -1  
$EndComp
Text GLabel 8700 3000 0    50   BiDi ~ 0
I2C_SDA
Text GLabel 6650 3000 2    50   BiDi ~ 0
I2C_SDA
Wire Wire Line
	8700 3000 9000 3000
Text GLabel 8700 3100 0    50   Input ~ 0
I2C_SDC
Wire Wire Line
	8700 3100 9000 3100
Text GLabel 6650 3100 2    50   Output ~ 0
I2C_SDC
Text GLabel 9050 5250 0    50   Input ~ 0
SPI_MOSI
Text GLabel 9950 5250 2    50   Input ~ 0
SPI_SCK
$Comp
L parking-timer-kicad:RDA5807M_Module U1
U 1 1 5FAAB35B
P 9600 3200
F 0 "U1" H 9600 3665 50  0000 C CNN
F 1 "RDA5807M_Module" H 9600 3574 50  0000 C CNN
F 2 "parking-timer-pcb:RDA5807M-through-hole" H 9600 3300 50  0001 C CNN
F 3 "" H 9600 3300 50  0001 C CNN
	1    9600 3200
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0103
U 1 1 5FAAC213
P 5900 1800
F 0 "#PWR0103" H 5900 1650 50  0001 C CNN
F 1 "VDD" H 5915 1973 50  0000 C CNN
F 2 "" H 5900 1800 50  0001 C CNN
F 3 "" H 5900 1800 50  0001 C CNN
	1    5900 1800
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0106
U 1 1 5FAADA33
P 8800 3350
F 0 "#PWR0106" H 8800 3200 50  0001 C CNN
F 1 "VDD" H 8815 3523 50  0000 C CNN
F 2 "" H 8800 3350 50  0001 C CNN
F 3 "" H 8800 3350 50  0001 C CNN
	1    8800 3350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0107
U 1 1 5FAAE9C1
P 9000 5050
F 0 "#PWR0107" H 9000 4900 50  0001 C CNN
F 1 "VDD" H 9015 5223 50  0000 C CNN
F 2 "" H 9000 5050 50  0001 C CNN
F 3 "" H 9000 5050 50  0001 C CNN
	1    9000 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 5050 9000 5150
Wire Wire Line
	9000 5150 9250 5150
$Comp
L power:GND #PWR0108
U 1 1 5FAAF785
P 9850 5600
F 0 "#PWR0108" H 9850 5350 50  0001 C CNN
F 1 "GND" H 9855 5427 50  0000 C CNN
F 2 "" H 9850 5600 50  0001 C CNN
F 3 "" H 9850 5600 50  0001 C CNN
	1    9850 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 5250 9950 5250
Wire Wire Line
	9250 5250 9050 5250
Text GLabel 9050 5350 0    50   Input ~ 0
DISP_CS
Wire Wire Line
	9050 5350 9250 5350
Text GLabel 5150 4000 0    50   Output ~ 0
SPI_SCK
Text GLabel 5150 4100 0    50   Output ~ 0
SPI_MOSI
Wire Wire Line
	5300 4000 5150 4000
Wire Wire Line
	6500 3000 6650 3000
Wire Wire Line
	6650 3100 6500 3100
Wire Wire Line
	5150 4100 5300 4100
Text GLabel 6650 3300 2    50   Output ~ 0
UART_TX
Wire Wire Line
	6500 3300 6650 3300
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5FAB5D44
P 1700 3300
F 0 "J1" H 1618 2975 50  0000 C CNN
F 1 "Conn_01x02" H 1618 3066 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1700 3300 50  0001 C CNN
F 3 "~" H 1700 3300 50  0001 C CNN
	1    1700 3300
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5FAB6667
P 2200 3350
F 0 "#PWR0109" H 2200 3100 50  0001 C CNN
F 1 "GND" H 2205 3177 50  0000 C CNN
F 2 "" H 2200 3350 50  0001 C CNN
F 3 "" H 2200 3350 50  0001 C CNN
	1    2200 3350
	1    0    0    -1  
$EndComp
Text GLabel 9050 5450 0    50   Input ~ 0
DIST_RST
Text GLabel 9950 5350 2    50   Input ~ 0
DISP_DC
Text GLabel 9950 5450 2    50   Output ~ 0
DISP_BUSY
Wire Wire Line
	9750 5350 9950 5350
Wire Wire Line
	9950 5450 9750 5450
Wire Wire Line
	9250 5450 9050 5450
Text GLabel 5150 3000 0    50   BiDi ~ 0
SWIM
Wire Wire Line
	5150 3000 5300 3000
Text GLabel 5150 3100 0    50   Input ~ 0
NRST
Wire Wire Line
	5150 3100 5300 3100
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5FAEE0CE
P 1700 4050
F 0 "J3" H 1618 4367 50  0000 C CNN
F 1 "Conn_01x04" H 1618 4276 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1700 4050 50  0001 C CNN
F 3 "~" H 1700 4050 50  0001 C CNN
	1    1700 4050
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5FAEFBE5
P 2050 4350
F 0 "#PWR0110" H 2050 4100 50  0001 C CNN
F 1 "GND" H 2055 4177 50  0000 C CNN
F 2 "" H 2050 4350 50  0001 C CNN
F 3 "" H 2050 4350 50  0001 C CNN
	1    2050 4350
	1    0    0    -1  
$EndComp
Text GLabel 2150 4250 2    50   Output ~ 0
NRST
Wire Wire Line
	1900 4250 2150 4250
Wire Wire Line
	1900 4150 2050 4150
Wire Wire Line
	2050 4150 2050 4350
Text GLabel 2150 4050 2    50   BiDi ~ 0
SWIM
Wire Wire Line
	1900 4050 2150 4050
Text GLabel 2500 2900 2    50   Output ~ 0
NRST
$Comp
L power:VDD #PWR0111
U 1 1 5FAF3D2C
P 2050 3850
F 0 "#PWR0111" H 2050 3700 50  0001 C CNN
F 1 "VDD" H 2065 4023 50  0000 C CNN
F 2 "" H 2050 3850 50  0001 C CNN
F 3 "" H 2050 3850 50  0001 C CNN
	1    2050 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 3950 2050 3950
Wire Wire Line
	2050 3950 2050 3850
$Comp
L Device:C C4
U 1 1 5FAF73AA
P 2200 3100
F 0 "C4" H 2315 3146 50  0000 L CNN
F 1 "100nF" H 2315 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2238 2950 50  0001 C CNN
F 3 "~" H 2200 3100 50  0001 C CNN
	1    2200 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 3300 2200 3300
Wire Wire Line
	2200 3300 2200 3250
Wire Wire Line
	1900 3200 2050 3200
Wire Wire Line
	2050 3200 2050 2900
Wire Wire Line
	2050 2900 2200 2900
Wire Wire Line
	2200 2900 2200 2950
Wire Wire Line
	2200 2900 2500 2900
Connection ~ 2200 2900
Wire Wire Line
	2200 3300 2200 3350
Connection ~ 2200 3300
$Comp
L Device:C C6
U 1 1 5FB00D8C
P 6600 2100
F 0 "C6" H 6715 2146 50  0000 L CNN
F 1 "1uF" H 6715 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6638 1950 50  0001 C CNN
F 3 "~" H 6600 2100 50  0001 C CNN
	1    6600 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5FB01EFB
P 6150 2100
F 0 "C5" H 6265 2146 50  0000 L CNN
F 1 "100nF" H 6265 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6188 1950 50  0001 C CNN
F 3 "~" H 6150 2100 50  0001 C CNN
	1    6150 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 1800 5900 1900
Wire Wire Line
	5900 1900 6150 1900
Wire Wire Line
	6150 1900 6150 1950
Connection ~ 5900 1900
Wire Wire Line
	5900 1900 5900 2700
Wire Wire Line
	6150 1900 6600 1900
Wire Wire Line
	6600 1900 6600 1950
Connection ~ 6150 1900
$Comp
L power:GND #PWR0112
U 1 1 5FB08483
P 6600 2350
F 0 "#PWR0112" H 6600 2100 50  0001 C CNN
F 1 "GND" H 6605 2177 50  0000 C CNN
F 2 "" H 6600 2350 50  0001 C CNN
F 3 "" H 6600 2350 50  0001 C CNN
	1    6600 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2250 6150 2300
Wire Wire Line
	6150 2300 6600 2300
Wire Wire Line
	6600 2300 6600 2350
Wire Wire Line
	6600 2300 6600 2250
Connection ~ 6600 2300
Wire Wire Line
	9750 5150 9850 5150
Wire Wire Line
	9850 5150 9850 5600
$Comp
L power:VDD #PWR0113
U 1 1 5FB260AD
P 2050 5300
F 0 "#PWR0113" H 2050 5150 50  0001 C CNN
F 1 "VDD" H 2065 5473 50  0000 C CNN
F 2 "" H 2050 5300 50  0001 C CNN
F 3 "" H 2050 5300 50  0001 C CNN
	1    2050 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5FB285B5
P 2050 6650
F 0 "#PWR0114" H 2050 6400 50  0001 C CNN
F 1 "GND" H 2055 6477 50  0000 C CNN
F 2 "" H 2050 6650 50  0001 C CNN
F 3 "" H 2050 6650 50  0001 C CNN
	1    2050 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 5550 2050 6250
NoConn ~ 1900 6350
NoConn ~ 1900 6150
Text GLabel 2200 6050 2    50   Output ~ 0
ACCE_INT1
Wire Wire Line
	1900 6050 2200 6050
Text GLabel 2200 5950 2    50   Input ~ 0
ACCE_CS
Wire Wire Line
	1900 5950 2200 5950
$Comp
L Connector_Generic:Conn_01x11 J4
U 1 1 5FB34D01
P 1700 5950
F 0 "J4" H 1618 6667 50  0000 C CNN
F 1 "Conn_01x11" H 1618 6576 50  0000 C CNN
F 2 "parking-timer-pcb:LIS3DSH_Module" H 1700 5950 50  0001 C CNN
F 3 "~" H 1700 5950 50  0001 C CNN
	1    1700 5950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1900 5550 2050 5550
Wire Wire Line
	1900 5450 2050 5450
Wire Wire Line
	2050 5450 2050 5300
Text GLabel 2200 5650 2    50   Input ~ 0
SPI_SCL
Text GLabel 2200 5750 2    50   Input ~ 0
SPI_MOSI
Text GLabel 2200 5850 2    50   Output ~ 0
SPI_MISO
Wire Wire Line
	1900 5650 2200 5650
Wire Wire Line
	2200 5750 1900 5750
Wire Wire Line
	1900 5850 2200 5850
Text GLabel 5150 4200 0    50   Input ~ 0
SPI_MISO
Wire Wire Line
	5150 4200 5300 4200
Wire Wire Line
	1900 6250 2050 6250
Connection ~ 2050 6250
Wire Wire Line
	2050 6250 2050 6450
Wire Wire Line
	1900 6450 2050 6450
Connection ~ 2050 6450
Wire Wire Line
	2050 6450 2050 6650
$EndSCHEMATC
