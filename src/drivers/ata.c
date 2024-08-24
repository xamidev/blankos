// ATA PIO driver implementation
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#include <stdint.h>
#include "../kernel/io.h"
#include "../libc/stdio.h"
#include "ata.h"

static inline uint16_t inw(uint16_t port) {
    uint16_t result;
    asm volatile("inw %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

static inline void outw(uint16_t port, uint16_t data) {
    asm volatile("outw %1, %0" : : "dN"(port), "a"(data));
}

void ata_wait_bsy() {
    while (inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & ATA_SR_BSY);
}

void ata_wait_drq() {
    while (!(inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & ATA_SR_DRQ));
}

void ata_select_drive(uint8_t drive) {
    outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xE0 | (drive << 4));
}

void ata_read_sector(uint32_t lba, uint8_t* buffer) {
    ata_wait_bsy();
    ata_select_drive(0);

    outb(ATA_PRIMARY_IO + ATA_REG_SECCOUNT0, 1);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA0, (uint8_t)lba);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA1, (uint8_t)(lba >> 8));
    outb(ATA_PRIMARY_IO + ATA_REG_LBA2, (uint8_t)(lba >> 16));
    outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xE0 | ((lba >> 24) & 0x0F));

    outb(ATA_PRIMARY_IO + ATA_REG_COMMAND, ATA_CMD_READ_PIO);

    ata_wait_bsy();
    ata_wait_drq();

    for (int i = 0; i < 256; i++) {
        ((uint16_t*)buffer)[i] = inw(ATA_PRIMARY_IO + ATA_REG_DATA);
    }
}

// Works only w/o paging
void test_read_sector() {
    uint8_t buffer[512];
    ata_read_sector(0, buffer);

    for (int i = 0; i < 512; i++) {
        if (i%25==0) puts("\n");
	printf("%02x ", buffer[i]);
    }
}
