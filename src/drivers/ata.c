#include <stdint.h>
#include "../kernel/io.h"
#include "../libc/stdio.h"

#define ATA_PRIMARY_IO 		0x1F0
#define ATA_PRIMARY_CTRL 	0x3F6
#define ATA_CMD_READ_PIO	0x20
#define ATA_CMD_WRITE_PIO 	0x30
#define ATA_IDENTIFY 		0xEC

#define ATA_REG_DATA 		0x00
#define ATA_REG_ERROR 		0x01
#define ATA_REG_SECCOUNT0 	0x02
#define ATA_REG_LBA0 		0x03
#define ATA_REG_LBA1 		0x04
#define ATA_REG_LBA2 		0x05
#define ATA_REG_HDDEVSEL 	0x06
#define ATA_REG_COMMAND 	0x07
#define ATA_REG_STATUS 		0x07

#define ATA_SR_BSY 		0x80
#define ATA_SR_DRDY 		0x40
#define ATA_SR_DRQ 		0x08
#define ATA_SR_ERR 		0x01

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
