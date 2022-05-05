#ifndef LORA_LORA_SPI_H_
#define LORA_LORA_SPI_H_

#include "hal/lora_spi.h"

#include <stdint.h>

extern void spi_init( void );
extern uint16_t SpiInOut(uint16_t outData );

#endif /* LORA_LORA_SPI_H_ */
