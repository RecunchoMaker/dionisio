# include "uart.h"
# include <stdarg.h>
# include <stdio.h>
# include <avr/interrupt.h>

# define BAUD 9600
# include <util/setbaud.h>

static char uart_buffer [32];

void uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if UART_USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void uart_putchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = c;
}

char uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

void uart_puts (const char * s)
{
  while (*s)
  {
    uart_putchar (*s++);
  }

}

void uart_printf ( const char *s , ... )
{
  va_list arguments;                     
  va_start ( arguments , s );
  vsprintf ( uart_buffer , s , arguments );
  va_end ( arguments );
  uart_puts (uart_buffer);
}

