# ifndef DIONISION_COMMON_H
# define DIONISION_COMMON_H

# include <avr/io.h>

# define SetBit(adr, bit)                       ( adr  |=  _BV(bit) )
# define ClearBit(adr, bit)                     ( adr  &= ~_BV(bit) )
# define BitIsSet(adr, bit)                     ((adr  &   _BV(bit) ) ? 1 : 0 )
# define BitIsClear(adr, bit)                   ((adr  &   _BV(bit) ) ? 0 : 1 )
# define BitAck(adr, bit)                       ( adr  =~  _BV(bit) )

//

# define INIT_LED()    ( SetBit (DDRB , 5) )
# define ENABLE_LED()  ( SetBit (PORTB , 5) )
# define DISABLE_LED() ( ClearBit (PORTB , 5) )

# endif // DIONISION_COMMON_H 
