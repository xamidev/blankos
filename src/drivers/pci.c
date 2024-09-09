// PCI bus driver implementation 
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include <stdint.h>
#include "pci.h"
#include "../libc/stdio.h"

static inline void outl(uint16_t port, uint32_t value)
{
	__asm__ volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t ret;
	__asm__ volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void pci_write_config_address(uint32_t address)
{
	outl(PCI_CONFIG_ADDRESS, address);
}

uint32_t pci_read_config_data()
{
	return inl(PCI_CONFIG_DATA);
}

uint32_t pci_config_address(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset)
{
    return (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC);
}

uint32_t pci_read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset)
{
    uint32_t address = pci_config_address(bus, device, function, offset);
    pci_write_config_address(address);
    return pci_read_config_data();
}

pci_device_t pci_get_device(uint8_t bus, uint8_t device, uint8_t function)
{
    pci_device_t dev;

    uint32_t reg0 = pci_read(bus, device, function, 0x00);  // Vendor ID, Device ID
    uint32_t reg2 = pci_read(bus, device, function, 0x08);  // Class, Subclass, Prog IF, Revision

    dev.vendor_id = reg0 & 0xFFFF;
    dev.device_id = (reg0 >> 16) & 0xFFFF;
    dev.class_code = (reg2 >> 24) & 0xFF;
    dev.subclass = (reg2 >> 16) & 0xFF;
    dev.prog_if = (reg2 >> 8) & 0xFF;
    dev.revision_id = reg2 & 0xFF;
    dev.bus = bus;
    dev.device = device;
    dev.function = function;

    return dev;
}

void scan_pci_bus()
{
    for (uint16_t bus = 0; bus < 256; bus++) {
        for (uint8_t device = 0; device < 32; device++) {
            for (uint8_t function = 0; function < 8; function++) {
                pci_device_t dev = pci_get_device(bus, device, function);
                
                if (dev.vendor_id != 0xFFFF) {
			
		    // Maybe put that in a database in initrd.tar?
		    char* vendor_string;
		    switch(dev.vendor_id)
		    {
			case 0x8086:
				vendor_string = "Intel Corporation";
				break;
			case 0x1234:
				vendor_string = "Brain Actuated Technologies";
				break;
			default:
				vendor_string = "Unknown";
				break;
		    }

		    char* device_string;
		    switch(dev.device_id)
		    {
			default:
				device_string = "Unknown";
				break;
		    }

                    printf("PCI Device found: Bus %u, Device %u, Function %u, Vendor ID: 0x%x (%s), Device ID: 0x%x (%s), Class: 0x%x\n",
                           dev.bus, dev.device, dev.function, dev.vendor_id, vendor_string, dev.device_id, device_string, dev.class_code);    
		}
            }
        }
    }
}

