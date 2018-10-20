# ifndef _UART_H
# define _UART_H

# include "uart.h" 

void uart_init(void);
void uart_puts (const char * s);
void uart_printf ( const char *s , ... );

# endif // _UART_H
