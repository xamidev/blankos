#include "io.h"
#include "serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
  outb(SERIAL_LINE_CMD_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
  /*
  d b p   s dl
  0 0 000 0 11 = 0x03
  
  Length 8 bits, no parity bit, one stop bit, break control off
  */

  outb(SERIAL_LINE_CMD_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com)
{
  /*
  lv b r d c c e
  11 0 0 0 1 1 1 = 0xC7
  
  Enable FIFO, clear FIFO queues, use 14 bytes as queue size
  */

  outb(SERIAL_LINE_CMD_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
  /*
  
  r r a l a a r d
  0 0 0 0 0 0 1 1 = 0x03

  Ready to transmit, data terminal ready
  */

  outb(SERIAL_LINE_CMD_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com)
{
  return (inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20);
}

void serial_write(const char* buf, unsigned short com)
{
  serial_configure_baud_rate(com, 2);
  serial_configure_line(com);
  serial_configure_buffer(com);
  serial_configure_modem(com);

  for (unsigned int i = 0; i<sizeof(buf); i++)
  {
    while (serial_is_transmit_fifo_empty(com))
    {
      outb(SERIAL_DATA_PORT(com), buf[i]);
    }
  }
  return;
}
