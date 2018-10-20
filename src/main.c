// https://github.com/pietern/avr-i2c
# include <alloca.h>
# include <avr/interrupt.h>
# include <util/delay.h>
# include "common.h"
# include "uart.h"
# include "i2c.h"
# include "timer.h"
# include "adxl345.h"

int main (int argc , char * argv [] )
{
  sei ();
  uart_init ();
  i2c_init () ;
  //timer_init() ;

  INIT_LED();
  DISABLE_LED();

  uint8_t buffer [32];

  for (;;)
  {
  adxl345_write_reg ( REG_DATA_FORMAT , 0x01 ) ;

  uint8_t bits;

  bits = 0x00;
  bits |= 0 << 5; // LINK
  bits |= 0 << 4; // AUTO SLEEP
  bits |= 1 << 3; // MEASURE
  bits |= 0 << 2; // SLEEP
  bits |= 0;      // WAKE UP

  adxl345_write_reg ( REG_POWER_CTL , 0x08 ) ;


  uart_printf ( "dev id: %x\r\n" , adxl345_read_reg ( REG_DEVID ) ) ;

  adxl345_read_reg_buffer ( REG_DATAX0 , buffer, 6 );

  uart_printf ( "data x0: %x\r\n" , buffer[0] ); 
  uart_printf ( "data x1: %x\r\n" , buffer[1] );
  uart_printf ( "data y0: %x\r\n" , buffer[2] );
  uart_printf ( "data y1: %x\r\n" , buffer[3] );
  uart_printf ( "data z0: %x\r\n" , buffer[4] );
  uart_printf ( "data z1: %x\r\n" , buffer[5] );

  bits = 0x00;
  bits |= 0 << 5; // LINK
  bits |= 0 << 4; // AUTO SLEEP
  bits |= 0 << 3; // MEASURE
  bits |= 0 << 2; // SLEEP
  bits |= 0;      // WAKE UP

  //adxl345_write_reg ( REG_POWER_CTL , bits ) ;

  }

  return 0 ;
}

