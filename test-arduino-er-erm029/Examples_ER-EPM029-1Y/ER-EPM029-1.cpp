/***************************************************
/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#include <stdlib.h>
#include "ER-EPM029-1.h"

Epd::~Epd() {
};

Epd::Epd() {
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
};

int Epd::Init(void) {
    /* this calls the peripheral hardware interface, see epdif */
    if (IfInit() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    Reset();
  
 	SendCommand(0x74);  //Set Analog Block Control
        SendData(0x54);
        SendCommand(0x7E);  //Set Digital Block Control
        SendData(0x3B);
        SendCommand(0x2B);  // Reduce glitch under ACVCOM	
        SendData(0x04);           
        SendData(0x63);
 
	 SendCommand(BOOSTER_SOFT_START_CONTROL);		  // Booster Soft start Control
	SendData(0x8B);		   
	SendData(0x9C);		   
	SendData(0x96);			   
	SendData(0x0F);
    
        
	SendCommand(DRIVER_OUTPUT_CONTROL);  // Driver Output control
        SendData(0x27);  
        SendData(0x01);
        SendData(0x00);     
        
        SendCommand(DATA_ENTRY_MODE_SETTING);  // Data Entry mode setting
        SendData(0x03);         
        SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION); //Set RAM X - address Start / End position
        SendData(0x00); // RAM x address start at 0
        SendData(0x0F); //RAM x address end at 0Fh(15+1)*8->128
        SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION); //Set Ram Y- address Start / End position
        SendData(0x27); // RAM y address start 
        SendData(0x01);
        SendData(0x00); // RAM y address end 
        SendData(0x00);
        
        
        SendCommand(BORDER_WAVEFORM_CONTROL); // Border Waveform Control
        SendData(0x01); // HIZ

        SendCommand(DISPLAY_UPDATE_CONTROL_1);
        SendData(0x00);//Normal

        
 //       unsigned char temp1,temp2;	
	SendCommand(0x18);//Temperature Sensor Control
	SendData(0x80);  //Internal temperature sensor
	SendCommand(DISPLAY_UPDATE_CONTROL_2);//Display UpdateControl 2
	SendData(0xB1);	//Load Temperature and waveform setting.
	SendCommand(MASTER_ACTIVATION); //Master Activation
	WaitUntilIdle();	     

    return 0;
}

/**
 *  @brief: basic function for sending commands
 */
void Epd::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes LOW
 */
void Epd::WaitUntilIdle(void) {
    while(DigitalRead(busy_pin) == HIGH) {      //LOW: idle, HIGH: busy
        DelayMs(100);
    }      
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(200);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);    
}


/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void Epd::SetFrameMemoryBlack(
    const unsigned char* image_buffer,
    int x,
    int y,
    int image_width,
    int image_height
) {
    int x_end;
    int y_end;

    if (
        image_buffer == NULL ||
        x < 0 || image_width < 0 ||
        y < 0 || image_height < 0
    ) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= this->width) {
        x_end = this->width - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= this->height) {
        y_end = this->height - 1;
    } else {
        y_end = y + image_height - 1;
    }
    SetMemoryArea(x, y, x_end, y_end);
    /* set the frame memory line by line */
    for (int j = y; j <= y_end; j++) {
        SetMemoryPointer(x, j);
        SendCommand(WRITE_RAM_BW);
        for (int i = x / 8; i <= x_end / 8; i++) {
            SendData(image_buffer[(i - x / 8) + (j - y) * (image_width / 8)]);
        }
    }
 
    
}


/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void Epd::SetFrameMemoryRed(
    const unsigned char* image_buffer,
    int x,
    int y,
    int image_width,
    int image_height
) {
    int x_end;
    int y_end;

    if (
        image_buffer == NULL ||
        x < 0 || image_width < 0 ||
        y < 0 || image_height < 0
    ) {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= this->width) {
        x_end = this->width - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= this->height) {
        y_end = this->height - 1;
    } else {
        y_end = y + image_height - 1;
    }
    SetMemoryArea(x, y, x_end, y_end);
    /* set the frame memory line by line */
    for (int j = y; j <= y_end; j++) {
        SetMemoryPointer(x, j);
        SendCommand(WRITE_RAM_RED);
        for (int i = x / 8; i <= x_end / 8; i++) {
            SendData(image_buffer[(i - x / 8) + (j - y) * (image_width / 8)]);
        }
    }
 
    
}

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 *
 *          Question: When do you use this function instead of 
 *          void SetFrameMemory(
 *              const unsigned char* image_buffer,
 *              int x,
 *              int y,
 *              int image_width,
 *              int image_height
 *          );
 *          Answer: SetFrameMemory with parameters only reads image data
 *          from the RAM but not from the flash in AVR chips (for AVR chips,
 *          you have to use the function pgm_read_byte to read buffers 
 *          from the flash).
 */
void Epd::SetFrameMemory(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red) {
    SetMemoryArea(0, 0, this->width - 1, this->height - 1);
    /* set the frame memory line by line */
    for (int j = 0; j < this->height; j++) {
        SetMemoryPointer(0, j);
        SendCommand(WRITE_RAM_BW);
        for (int i = 0; i < this->width / 8; i++) {
            SendData(pgm_read_byte(&frame_buffer_black[i + j * (this->width / 8)]));
        }
    }
    
    for (int j = 0; j < this->height; j++) {
        SetMemoryPointer(0, j);
        SendCommand(WRITE_RAM_RED);
        for (int i = 0; i < this->width / 8; i++) {
            SendData(pgm_read_byte(&frame_buffer_red[i + j * (this->width / 8)]));
        }
    }    
    
}

/**
 *  @brief: clear the frame memory with the specified color.
 *          this won't update the display.
 */
void Epd::ClearFrameMemory(void) {
    SetMemoryArea(0, 0, this->width - 1, this->height - 1);
    /* set the frame memory line by line */
    for (int j = 0; j < this->height; j++) {
        SetMemoryPointer(0, j);
        SendCommand(WRITE_RAM_BW);
        for (int i = 0; i < this->width / 8; i++) {
            SendData(0xff);
        }
    }
    for (int j = 0; j < this->height; j++) {
        SetMemoryPointer(0, j);
        SendCommand(WRITE_RAM_RED);
        for (int i = 0; i < this->width / 8; i++) {
            SendData(0x00);
        }
    }    
    
}

/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will 
 *          set the other memory area.
 */
void Epd::DisplayFrame(void) {
    SendCommand(DISPLAY_UPDATE_CONTROL_2);
    SendData(0xC7);
    SendCommand(MASTER_ACTIVATION);
    WaitUntilIdle();
}

/**
 *  @brief: private function to specify the memory area for data R/W
 */
void Epd::SetMemoryArea(int x_start, int y_start, int x_end, int y_end) {
    SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x_start >> 3) & 0xFF);
    SendData((x_end >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
    SendData(y_start & 0xFF);
    SendData((y_start >> 8) & 0xFF);
    SendData(y_end & 0xFF);
    SendData((y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void Epd::SetMemoryPointer(int x, int y) {
    SendCommand(SET_RAM_X_ADDRESS_COUNTER);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
    SendData(y & 0xFF);
    SendData((y >> 8) & 0xFF);
    WaitUntilIdle();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the 
 *          deep-sleep mode to save power. 
 *          The deep sleep mode would return to standby by hardware reset. 
 *          You can use Epd::Init() to awaken
 */
void Epd::Sleep() {
    SendCommand(DEEP_SLEEP_MODE);
    SendData(0x01);    
    WaitUntilIdle();
}
	
/* END OF FILE */


