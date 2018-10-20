# include <alloca.h>
# include "i2c.h"

# define I2C_ADDRESS  0x53

# define ALLOC_I2C_TXN(NOPS) ( alloca(sizeof(i2c_txn_t) + NOPS * sizeof(i2c_op_t)) )

# include "uart.h"

void adxl345_write_reg (const uint8_t reg , const uint8_t value )
{
  uint8_t value0 = reg;
  uint8_t value1 = value;

  i2c_txn_t * tqueue = ALLOC_I2C_TXN(2);
  i2c_txn_init(tqueue, 2);
  
  i2c_op_init_wr(&tqueue->ops[0], I2C_ADDRESS, &value0, sizeof(value0));
  i2c_op_init_wr(&tqueue->ops[1], I2C_ADDRESS, &value1, sizeof(value1));

  i2c_post(tqueue);

  while (!(tqueue->flags & I2C_TXN_DONE)) {
   //sleep_mode();
  }

  if (tqueue->flags & I2C_TXN_ERR) {
    uart_puts ("I2C_TXN_ERR");  
  } else {
    // all ok
  }

}

uint8_t adxl345_read_reg (const uint8_t reg )
{

  uint8_t value0 = reg;
  uint8_t value1 = 0xff;

  i2c_txn_t * tqueue = ALLOC_I2C_TXN(2);
  i2c_txn_init(tqueue, 2);
  
  i2c_op_init_wr(&tqueue->ops[0], I2C_ADDRESS, &value0, sizeof(value0));
  i2c_op_init_rd(&tqueue->ops[1], I2C_ADDRESS, &value1, sizeof(value1));

  i2c_post(tqueue);

  while (!(tqueue->flags & I2C_TXN_DONE)) {
   //sleep_mode();
  }

  if (tqueue->flags & I2C_TXN_ERR) {
    uart_puts ("I2C_TXN_ERR");  
  } else {
    // all ok
  }

  return value1;
}


void adxl345_read_reg_buffer (const uint8_t reg , uint8_t * buffer, const size_t size )
{
  uint8_t address = 0x80 | reg ;

  if ( size > 1 ) address = address | 0x40;

  i2c_txn_t * tqueue = ALLOC_I2C_TXN(1+size);
  i2c_txn_init(tqueue, 1+size);

  i2c_op_init_wr(&tqueue->ops[0], I2C_ADDRESS, &address, sizeof(address));

  for ( uint8_t i = 0 ; i < size ; i ++ )
    i2c_op_init_rd(&tqueue->ops[1+i], I2C_ADDRESS, buffer + i, 1 );

  if (tqueue->flags & I2C_TXN_ERR)
    uart_puts ("I2C_TXN_ERR");  

}

