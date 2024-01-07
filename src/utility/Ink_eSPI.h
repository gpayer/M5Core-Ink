#ifndef _INK_ESPI_H_
#define _INK_ESPI_H_

#include <Arduino.h>
#include <SPI.h>
#include "soc/spi_reg.h"
#include "config.h"
#include "WFT0154CZB3_INIT.h"
#include <M5GFX.h>

// #define SPI_PORT VSPI

// #define INK_SPI_FREQUENCY 10000000

#define INK_FULL_MODE    0x00
#define INK_PARTIAL_MODE 0x01

#define INK_CLENR_MODE0 0
#define INK_CLEAR_MODE1 1

class Ink_eSPI : public M5GFX {
   public:
    Ink_eSPI()
        : M5GFX(){

          };
    void begin();
    bool isInit();

    int clear(int mode = INK_CLENR_MODE0);
    int clearDSRAM();

    int drawBuff(uint8_t* buff, bool bitMode = true);
    int drawBuff(uint8_t* lastbuff, uint8_t* buff, size_t size);

    void switchMode(epd_mode_t mode);
    epd_mode_t getMode() {
        return _mode;
    }

    void deepSleep();
    void powerHVON();
    void powerHVOFF();

   private:
    bool _isInit = false;
    int32_t _width, _height;
    epd_mode_t _mode = epd_text;
};

#endif
