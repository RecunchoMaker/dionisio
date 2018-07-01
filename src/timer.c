# include <stdint.h>
# include <avr/interrupt.h>
# include "common.h"
# include "timer.h"

# define FCLOCK(HZ) ((F_CPU)/((HZ)*64L)-1);

volatile uint8_t timecounter;
volatile uint8_t current_duty;

void set_duty (const uint8_t duty )
{
  current_duty = duty;
}

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

  if (pwm < current_duty )
  {
    ENABLE_LED();
  }
  else
  {
    DISABLE_LED();
  }

}

