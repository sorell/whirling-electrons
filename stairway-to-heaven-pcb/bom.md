# Checklist

* SENSORS!
* Sensor silks
* Double-check sensor input ports react to 3V3



# BOM

| Component     | € / 1 pcs | pcs | Link | Datasheet | Comment |
|---------------|-----------|-----|------|-----------|---------|
| Mega 2560 Pro | 22,2      | 1   | [link](https://www.aliexpress.com/item/32833214300.html) | [link](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/ATmega640-1280-1281-2560-2561-Datasheet-DS40002211A.pdf) | Mcu 5V 7-9V IO:54+16 |
| LM2575T-5  | 2,66      | 1   | [link](https://www.triopak.fi/fi/tuote/LM2575T-5) | [link](https://www.ti.com/lit/ds/symlink/lm2575-n.pdf) | Step-Down Voltage Regulator 5V |
| Regulator components  | 4,7      | 1   | - | - | Voltage Regulator components |
| FDN337N       | 0,31      | 42  | [link](https://www.triopak.fi/fi/tuote/FDN337N) | [link](https://www.triopak.fi/files/product/Fairchild/FDN337N_eng_datasheet.pdf) | Mos N-Fet 30V 2,2A 65mohms, SOT-23 |
| Led strip     | 7,59      | 3   | [link](https://www.aliexpress.com/item/32903257649.html) | - | RGB LED strip, 5m, smd 5050 |
| 3386P503      | 0,36      | 1   | [link](https://www.triopak.fi/fi/tuote/3386P503) | - | Trimmer potentiometer, 50 kOhm
| xxxxxxx       |           |     |   |   |   |
| Total cost    | 65,71     |     |   |   |   |

# Specs

14 x 3 FET driven PWM controlled LED power lines

## Current consumption

The leds come in 5 m strips and have 3 separate colors.

Measured current consumption for an unopened reel after temperature rise has stopped:
Blue: 1,29 A
Red: 1,33 A
Green: 1,12 A 
-> Total current = 3,74 A / 5 m = **0,748 A/m**.

We want the board to be able to drive up to **14 meters** of led strip, so this gives the **maximum current of 10,472 A**. At [PCBWay](https://www.pcbway.com) the price of a board increases more than eightfold when going from 1 oz to 2 oz copper thickness, so we want to try to design a board with 1 oz thickness. We can place the led connectors on both sides of the board, so the maximum **current per side is 5,236 A**. Pcb industry counter-intuitively uses a unit of volume to measure thickness, which derives from oz per area of one square feet. 

For a pcb with copper thickness of 1 oz, allowed temperature rise of 10 C and trace length of 10 cm a [PCB trace width calculator](https://www.4pcb.com/trace-width-calculator.html) gives trace width **7,6 mm, or 300 mils**. We can live with that. The maximum current for a single color per 1 m is then 1,33 A / 5 m = 0,266 A -> trace width for the outputs is **0,126 mm, or 4,95 mils**. I think we can be generous and make them wider.

# Sourcing

## Mega 2560 PRO

https://www.aliexpress.com/item/32833214300.html

Howto: https://wiki.keyestudio.com/KS0502_Keyestudio_MEGA_2560_PRO_Development_Board(Black_and_Eco-friendly)

## Arduino Mega 2560 Rev3

https://store.arduino.cc/collections/boards/products/arduino-mega-2560-rev3

## Photosensor ?

ToS sensor module: https://www.aliexpress.com/item/4000088283170.html
PIR sensor module: https://www.aliexpress.com/item/1874938103.html
Phototransistor + IR led?

https://www.probotronix.com/product/pir-motion-sensor-detector-module-hc-sr501/

## Photosensor GP2Y0D21YK

The GP2Y0D21YK is a distance measuring sensor with integrated signal processing and digital output.

[Datasheet](https://media.digikey.com/pdf/Data%20Sheets/Sharp%20PDFs/GP2Y0D21YK.pdf)

## Switching regulator LM2575T-5

https://www.triopak.fi/fi/tuote/LM2575T-5
https://www.ti.com/lit/ds/symlink/lm2575-n.pdf

## N-channel MOSFET SOT-23 30V 2,2A

https://www.triopak.fi/fi/tuote/FDN337N
https://www.triopak.fi/files/product/Fairchild/FDN337N_eng_datasheet.pdf
0,31 € / 1 pcs

## N-channel MOSFET SOT-23-3 20V 4,6A

https://www.mouser.fi/ProductDetail/Diodes-Incorporated/DMN2058U-7?qs=G1ssh2j%252Bqz5xShP2%2FdgDNQ%3D%3D
https://www.mouser.fi/datasheet/2/115/DIOD_S_A0011183505_1-2543669.pdf
0,289 € / 1 pcs @ 10 pcs

## 2x N-channel MOSFET TSOT-26-6 30V 3,5A

https://www.mouser.fi/ProductDetail/Diodes-Incorporated/DMN3135LVT-7?qs=gfe7vQ8txpXcd87ExB4f9Q%3D%3D
https://www.diodes.com/assets/Datasheets/DMN3135LVT.pdf
0,385 € / 1 pcs @ 10 pcs

## Barrel jack ?

