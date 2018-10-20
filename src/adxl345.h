# ifndef DIONISION_ADXL345_H
# define DIONISION_ADXL345_H

# include <stdint.h>

// Register Map
// Order is "Type, Reset Value, Description".
# define REG_DEVID          0x00    // R,     11100101,   Device ID
# define REG_THRESH_TAP     0x1D    // R/W,   00000000,   Tap threshold
# define REG_OFSX           0x1E    // R/W,   00000000,   X-axis offset
# define REG_OFSY           0x1F    // R/W,   00000000,   Y-axis offset
# define REG_OFSZ           0x20    // R/W,   00000000,   Z-axis offset
# define REG_DUR            0x21    // R/W,   00000000,   Tap duration
# define REG_LATENT         0x22    // R/W,   00000000,   Tap latency
# define REG_WINDOW         0x23    // R/W,   00000000,   Tap window
# define REG_THRESH_ACT     0x24    // R/W,   00000000,   Activity threshold
# define REG_THRESH_INACT   0x25    // R/W,   00000000,   Inactivity threshold
# define REG_TIME_INACT     0x26    // R/W,   00000000,   Inactivity time
# define REG_ACT_INACT_CTL  0x27    // R/W,   00000000,   Axis enable control for activity and inactiv ity detection
# define REG_THRESH_FF      0x28    // R/W,   00000000,   Free-fall threshold
# define REG_TIME_FF        0x29    // R/W,   00000000,   Free-fall time
# define REG_TAP_AXES       0x2A    // R/W,   00000000,   Axis control for single tap/double tap
# define REG_ACT_TAP_STATUS 0x2B    // R,     00000000,   Source of single tap/double tap
# define REG_BW_RATE        0x2C    // R/W,   00001010,   Data rate and power mode control
# define REG_POWER_CTL      0x2D    // R/W,   00000000,   Power-saving features control
# define REG_INT_ENABLE     0x2E    // R/W,   00000000,   Interrupt enable control
# define REG_INT_MAP        0x2F    // R/W,   00000000,   Interrupt mapping control
# define REG_INT_SOUCE      0x30    // R,     00000010,   Source of interrupts
# define REG_DATA_FORMAT    0x31    // R/W,   00000000,   Data format control
# define REG_DATAX0         0x32    // R,     00000000,   X-Axis Data 0
# define REG_DATAX1         0x33    // R,     00000000,   X-Axis Data 1
# define REG_DATAY0         0x34    // R,     00000000,   Y-Axis Data 0
# define REG_DATAY1         0x35    // R,     00000000,   Y-Axis Data 1
# define REG_DATAZ0         0x36    // R,     00000000,   Z-Axis Data 0
# define REG_DATAZ1         0x37    // R,     00000000,   Z-Axis Data 1
# define REG_FIFO_CTL       0x38    // R/W,   00000000,   FIFO control
# define REG_FIFO_STATUS    0x39    // R,     00000000,   FIFO status

void adxl345_write_reg (const uint8_t reg , const uint8_t value );
uint8_t adxl345_read_reg (const uint8_t addr );
void adxl345_read_reg_buffer (const uint8_t reg , uint8_t * buffer, const size_t size );

# endif // DIONISION_ADXL345_H
