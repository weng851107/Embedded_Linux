#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include "i2c_lib.h"




static int i2c_write(char *port, unsigned char slave_addr, unsigned char data[], int bytes);
static int i2c_read(char *port, unsigned char slave_addr, unsigned char data[], int bytes);



/*******************************************************************************
*                          GLOBAL FUNCTION PROTOTYPE
*******************************************************************************/
/*******************************************************************************
* Description : I2C write function
* Parameter   : port = I2C_PORT_0, I2C_PORT_1, I2C_PORT_2, ...
*               slave_addr = 7-bit slave address without R/W bit
*               data[] = the data array will be written
*               bytes = how many bytes will be written
* Return      : I2C_SUCCESS or I2C_ERR_XXX
* Note        : This function only support 7-bit slave address. 10-bit is not supported.
*******************************************************************************/
static int i2c_write(char *port, unsigned char slave_addr, unsigned char data[], int bytes)
{
	int ret = 0;
	int fd = 0;
	
	fd = open(port, O_RDWR, 0);
	if (fd < 0)
	{
		DEBUG("open fail");
		close(fd);
		return I2C_ERR_OPEN_FAIL;
	}	
	
	ret = ioctl(fd, I2C_TENBIT, 0);	/* 0 = 7-bit slave address */
	if (ret < 0)
	{
		DEBUG("config 7-bit fail");
		return I2C_ERR_CONFIG_7_BIT_FAIL;
	}
	
	ret = ioctl(fd, I2C_SLAVE, slave_addr);
	if (ret < 0)
	{
		DEBUG("set slave address fail");
		return I2C_ERR_SET_SLAVE_ADDR_FAIL;
	}

	ret = write(fd, data, bytes);
	if (ret != bytes)
	{
		DEBUG("write fail! want to write %d byte, but only %d byte actually", ret, bytes);
		return I2C_ERR_WRITE_FAIL;
	}

	close(fd);
	
	return I2C_SUCCESS;
}

/*******************************************************************************
* Description : I2C read function
* Parameter   : port = I2C_PORT_0, I2C_PORT_1, I2C_PORT_2, ...
*               slave_addr = 7-bit slave address without R/W bit
*               data[] = the data array will store all data read
*               bytes = how many bytes will be read
* Return      : I2C_SUCCESS or I2C_ERR_XXX
* Note        : This function only support 7-bit slave address. 10-bit is not supported.
*******************************************************************************/
static int i2c_read(char *port, unsigned char slave_addr, unsigned char data[], int bytes)
{
	int ret = 0;
	int fd = 0;
	
	fd = open(port, O_RDWR, 0);
	if (fd < 0)
	{
		DEBUG("open fail");
		close(fd);
		return I2C_ERR_OPEN_FAIL;
	}	
	
	ret = ioctl(fd, I2C_TENBIT, 0);	/* 0 = 7-bit slave address */
	if (ret < 0)
	{
		DEBUG("config 7-bit fail");
		return I2C_ERR_CONFIG_7_BIT_FAIL;
	}
	
	ret = ioctl(fd, I2C_SLAVE, slave_addr);
	if (ret < 0)
	{
		DEBUG("set slave address fail");
		return I2C_ERR_SET_SLAVE_ADDR_FAIL;
	}

	ret = read(fd, data, bytes);
	if (ret != bytes)
	{
		DEBUG("read fail! want to read %d byte, but only %d byte actually", ret, bytes);
		return I2C_ERR_READ_FAIL;
	}

	close(fd);
	
	return I2C_SUCCESS;
}

/*******************************************************************************
* Description : Write data to device.
* Parameter   : port = I2C_PORT_0, I2C_PORT_1, I2C_PORT_2, ...
*               slave_addr = 7-bit slave address without R/W bit
*               reg = register of device which start to write, only 8-bit register supported
*               data[] = the data array will be written
*               bytes = how many bytes will be written
* Return      : I2C_SUCCESS or I2C_ERR_XXX
* Note        : This function only support 7-bit slave address. 10-bit is not supported.
*******************************************************************************/
int i2c_write_reg(char *port, unsigned char slave_addr, unsigned char reg, unsigned char data[], int bytes)
{
	int ret = 0;
	unsigned char *w_data = NULL;
	
	w_data = (unsigned char *)malloc(bytes + 1);
	if (w_data == NULL)
	{
		DEBUG("allocate write buffer fail");
		return I2C_ERR_ALLOCATE_BUF_FAIL;
	}
	memcpy(w_data, &reg, 1);
	memcpy(w_data + 1, data, bytes);
	
	ret = i2c_write(port, slave_addr, w_data, bytes + 1);
	if (ret)
	{
		return ret;
	}
	
	free(w_data);
	
	return I2C_SUCCESS;
}

/*******************************************************************************
* Description : Read data from device.
* Parameter   : port = I2C_PORT_0, I2C_PORT_1, I2C_PORT_2, ...
*               slave_addr = 7-bit slave address without R/W bit
*               reg = register of device which start to read, only 8-bit register supported
*               data[] = the data array will store all data read
*               bytes = how many bytes will be read
* Return      : I2C_SUCCESS or I2C_ERR_XXX
* Note        : This function only support 7-bit slave address. 10-bit is not supported.
*******************************************************************************/
int i2c_read_reg(char *port, unsigned char slave_addr, unsigned char reg, unsigned char data[], int bytes)
{
	int ret = 0;
	unsigned char w_data[1] = {0};
	
	w_data[0] = reg;

	ret = i2c_write(port, slave_addr, w_data, 1);
	if (ret)
	{
		printf("%s: i2c port (%s) write reg (%#x) to slave addr (%#x) failed\n", __func__, port, w_data[0], slave_addr);
		return ret;
	}
	
	ret = i2c_read(port, slave_addr, data, bytes);
	if (ret)
	{
		printf("%s: i2c read failed\n", __func__);
		return ret;
	}
	
	return I2C_SUCCESS;
}