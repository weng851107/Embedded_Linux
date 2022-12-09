#ifndef _I2C_LIB_H_
#define _I2C_LIB_H_

#define I2C_SUCCESS                 0
#define I2C_ERR_OPEN_FAIL           -1
#define I2C_ERR_CONFIG_7_BIT_FAIL   -2
#define I2C_ERR_SET_SLAVE_ADDR_FAIL -3
#define I2C_ERR_WRITE_FAIL          -4
#define I2C_ERR_READ_FAIL           -5
#define I2C_ERR_ALLOCATE_BUF_FAIL   -6
#define I2C_MAX_DATA_LEN			2

#define I2C_PORT_0 "/dev/i2c-0"	/* IDC1 */
#define I2C_PORT_1 "/dev/i2c-1"	/* IDC2 */
#define I2C_PORT_2 "/dev/i2c-2"	/* IDC3 */
#define DEBUG	printf
#define CMD_READ_REG		(0x01)
#define CMD_WRITE_REG		(0x02)
#define CMD_ADC_READ_H_L	(0x03)
#define CMD_ADC_SET_TH		(0x04)

int i2c_write_reg(char *port, unsigned char slave_addr, unsigned char reg, unsigned char data[], int bytes);
int i2c_read_reg(char *port, unsigned char slave_addr, unsigned char reg, unsigned char data[], int bytes);


#endif