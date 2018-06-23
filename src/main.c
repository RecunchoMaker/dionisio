// https://github.com/pietern/avr-i2c
# include <alloca.h>
# include <avr/interrupt.h>
# include <util/delay.h>
# include "i2c.h"

# define ENABLE_LED() (PORTB |= 1<<5)
# define DISABLE_LED() (PORTB &= ~(1<<5))

# define I2C_ADDRESS  9

i2c_txn_t *tqueue;

uint8_t reg;

volatile uint8_t timecounter;
volatile uint8_t duty;

#define FCLOCK(HZ) ((F_CPU)/((HZ)*64L)-1);

void timer_init (void )
{
  const uint8_t sreg = SREG;
  cli();

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = FCLOCK(16000); 
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  timecounter = 0;

  SREG = sreg;
}

ISR(TIMER0_COMPA_vect){

  timecounter ++ ;

  const uint8_t pwm = timecounter % 0xFF ;

  if (pwm < duty )
  {
    ENABLE_LED();
  }
  else
  {
    DISABLE_LED();
  }

}

void write_reg (const uint8_t value )
{
  reg = value;

  i2c_op_init_wr(&tqueue->ops[0], I2C_ADDRESS, &reg, sizeof(reg));
  i2c_post(tqueue);
  
  while (!(tqueue->flags & I2C_TXN_DONE)) {
  /* You can do whatever you want here. */
  //sleep_mode();
  }
  
  if (tqueue->flags & I2C_TXN_ERR) {
    // error
  } else {
    // all ok
  }

}

int main (int argc , char * argv [] )
{
  sei ();
  i2c_init () ;
  timer_init() ;

  tqueue = alloca(sizeof(*tqueue) + 1 * sizeof(tqueue->ops[0]));

  i2c_txn_init(tqueue, 1);

  DDRB |= 1<<5;

  for (;;)
  {
    //ENABLE_LED ();
    write_reg ('0');
    duty = 16; 
    _delay_ms (2000);
    //DISABLE_LED ();
    write_reg ('1');
    duty = 127;
    _delay_ms (2000);
  }

  return 0 ;
}

