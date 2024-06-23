/**
 * @author Michael Granberry
*/

#ifndef IIC_H   /* prevent circular inclusions */
#define IIC_H

#include "xiic.h"


typedef struct IIC {
	XIic_Config *iic_config;
	XIic Iic;
	int chipAddr;
	u8 currentRegister;
	u8 recvbytes;
	u8 *recv;
} IIC;

void iic_begin(IIC *InstancePtr, u16 DeviceId, int Chip_Address);
void iic_init(IIC *InstancePtr);
void iic_write(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData);
void iic_write_repeat(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData);
void iic_read(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData);
void iic_read_repeat(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData);
#endif  /* end of protection macro */
