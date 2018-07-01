// https://github.com/pietern/avr-i2c
# include <alloca.h>
# include <avr/interrupt.h>
# include <util/delay.h>
# include "common.h"
# include "i2c.h"
# include "timer.h"
# include "adxl345.h"


int main (int argc , char * argv [] )
{
  sei ();
  i2c_init () ;
  //timer_init() ;

  INIT_LED();
  DISABLE_LED();

  for (;;)
  {
    //ENABLE_LED();
    //_delay_ms (500);
    //DISABLE_LED();
    //set_duty (16); 
    //_delay_ms (2000);
    ENABLE_LED();
    adxl345_write_reg ( 0x0 );
    //set_duty (32);

    _delay_ms (500);
    DISABLE_LED();
    _delay_ms (500);
  }

  return 0 ;
}

