#include "stdint.h"
#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_gpio.h"
#include "dji_typedef.h"

#define FLASH_SIZE                     (0x100000)  /* //flash size:1024 KBytes */

//flash sector address
#define ADDR_FLASH_SECTOR_0            ((uint32_t)0x08000000)    //sector 0 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_1            ((uint32_t)0x08004000)    //sector 1 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_2            ((uint32_t)0x08008000)    //sector 2 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_3            ((uint32_t)0x0800C000)    //sector 3 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_4            ((uint32_t)0x08010000)    //sector 4 start address, 64 Kbytes
#define ADDR_FLASH_SECTOR_5            ((uint32_t)0x08020000)    //sector 5 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_6            ((uint32_t)0x08040000)    //sector 6 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_7            ((uint32_t)0x08060000)    //sector 7 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_8            ((uint32_t)0x08080000)    //sector 8 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_9            ((uint32_t)0x080A0000)    //sector 9 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_10           ((uint32_t)0x080C0000)    //sector 10 start address,128 Kbytes
#define ADDR_FLASH_SECTOR_11           ((uint32_t)0x080E0000)    //sector 11 start address,128 Kbytes

#define FLASH_SETTING_START_ADDR       ADDR_FLASH_SECTOR_10
#define FLASH_SETTING_END_ADDR         (ADDR_FLASH_SECTOR_11 - 1)

#define PARAM_FLASH_SIZE               2048
#define FLASH_IMAGE_SIZE               (FLASH_APP_END_ADDR - FLASH_APP_START_ADDR)

INTERFACE int flash_read_data(uint32_t addr, uint8_t *buf, uint32_t len);
INTERFACE int flash_write_byte(uint32_t addr, uint8_t data);
INTERFACE int flash_write_word(uint32_t addr, uint32_t data);
INTERFACE int flash_wirte_data(uint32_t *addr, uint32_t *data, uint16_t len);

INTERFACE int flash_read_user_settings(uint8_t * setting);
INTERFACE int flash_write_user_settings(uint8_t *setting);
INTERFACE int flash_erase(uint32_t startAddr,uint32_t endAddr);

INTERFACE uint32_t flash_read_settings(void);
INTERFACE void flash_wirte_settings(uint32_t setting);

