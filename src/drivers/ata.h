#ifndef ATA_H
#define ATA_H

#include <stdint.h>

void ata_read_sector(uint32_t lba, uint8_t* buffer);
void test_read_sector();

#endif
