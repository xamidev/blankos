// PCI bus driver implementation header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef PCI_H
#define PCI_H

#include <stdint.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

typedef struct
{
	uint16_t vendor_id;
	uint16_t device_id;
	uint8_t  class_code;
	uint8_t  subclass;
	uint8_t  prog_if;
	uint8_t  revision_id;
	uint8_t  bus;
	uint8_t  device;
	uint8_t  function;
} pci_device_t;

void scan_pci_bus();

#endif
