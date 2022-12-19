#ifndef IMAGES_H_INCLUDED
#define IMAGES_H_INCLUDED

#include "FilConfig.h"
#if(EXTERNAL_SSD1306 == 1)
#include "stdint.h"
uint8_t logo_RCR_50x50 [350];
uint8_t logo_RCR_20x20[60];
uint8_t logo_RCR_40x40[200];
uint8_t logo_DSTU_40x40 [200];
uint8_t Tank_60x60[510];
uint8_t Sad_50x50[350];
uint8_t Heart_50x50[350];
#endif /* IMAGES_H_INCLUDED */
#endif /*EXTERNAL_SSD1306*/
