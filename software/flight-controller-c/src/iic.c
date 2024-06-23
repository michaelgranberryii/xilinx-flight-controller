/**
 * @author Michael Granberry
*/

#include "iic.h"

void iic_begin(IIC *InstancePtr, u16 DeviceId, int Chip_Address) {
//	InstancePtr->Iic.BaseAddress = IIC_Address;
	InstancePtr->chipAddr = Chip_Address;
//	iic_init(InstancePtr);


	InstancePtr->iic_config = XIic_LookupConfig(DeviceId);
	int status = XIic_CfgInitialize(&InstancePtr->Iic, InstancePtr->iic_config, InstancePtr->iic_config->BaseAddress);
	if(status == XST_SUCCESS)
		xil_printf("IIC Init Successful\n\r");
	else
		xil_printf("IIC Init Failed\n\r");
	 status = XIic_SelfTest(&InstancePtr->Iic);
	if(status == XST_SUCCESS) {
		xil_printf("IIC SELF TEST SUCCUSSFUL\n\r");
	} else {
		xil_printf("IIC SELF TEST FAILED\n\r");
	}

   /*
	* Start the IIC driver so that the device is enabled.
	*/
   XIic_Start(&InstancePtr->Iic);

   /*
    * Disable Global interrupt to use polled mode operation
    */
   XIic_IntrGlobalDisable(InstancePtr->Iic.BaseAddress);

   XIic_SetAddress(&InstancePtr->Iic, XII_ADDR_TO_SEND_TYPE, InstancePtr->chipAddr);
}

void iic_init(IIC *InstancePtr) {
	int status = XIic_Initialize(&InstancePtr->Iic, InstancePtr->iic_config->DeviceId);
	if(status == XST_SUCCESS)
		xil_printf("IIC Init Successful\n\r");
	else
		xil_printf("IIC Init Failed\n\r");
	 status = XIic_SelfTest(&InstancePtr->Iic);
	if(status == XST_SUCCESS) {
		xil_printf("IIC SELF TEST SUCCUSSFUL\n\r");
	} else {
		xil_printf("IIC SELF TEST FAILED\n\r");
	}

   /*
	* Start the IIC driver so that the device is enabled.
	*/
   XIic_Start(&InstancePtr->Iic);

   /*
    * Disable Global interrupt to use polled mode operation
    */
   XIic_IntrGlobalDisable(InstancePtr->Iic.BaseAddress );
}

void iic_write(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData) {
   u8 out[10];
   out[0] = reg;
   out[1] = *Data;
   int Status;

   if (InstancePtr->currentRegister != reg) {
	   InstancePtr->currentRegister = reg;
   }
   Status = XIic_Start(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
   XIic_Send(BaseAddr, InstancePtr->chipAddr, out, nData + 1, XIIC_STOP);

   Status = XIic_Stop(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
}

void iic_write_repeat(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData) {
   u8 out[10];
   out[0] = reg;
   out[1] = *Data;
   int Status;

   if (InstancePtr->currentRegister != reg) {
	   InstancePtr->currentRegister = reg;
   }
   Status = XIic_Start(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
   XIic_Send(BaseAddr, InstancePtr->chipAddr, out, nData + 1, XIIC_REPEATED_START);

   Status = XIic_Stop(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
}

void iic_read(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData) {
   int Status;
   Status = XIic_Start(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
   if (InstancePtr->currentRegister != reg) {

      XIic_Send(BaseAddr, InstancePtr->chipAddr, &reg, 1, XII_REPEATED_START_OPTION);
      InstancePtr->currentRegister = reg;
   }
   XIic_Recv(BaseAddr, InstancePtr->chipAddr, Data, nData, XIIC_STOP);

   Status = XIic_Stop(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
}

void iic_read_repeat(IIC *InstancePtr, u32 BaseAddr, u8 reg, u8 *Data, int nData) {
   int Status;
   Status = XIic_Start(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
   if (InstancePtr->currentRegister != reg) {

      XIic_Send(BaseAddr, InstancePtr->chipAddr, &reg, 1, XII_REPEATED_START_OPTION);
      InstancePtr->currentRegister = reg;
   }
   XIic_Recv(BaseAddr, InstancePtr->chipAddr, Data, nData, XII_REPEATED_START_OPTION);

   Status = XIic_Stop(&InstancePtr->Iic);
   if (Status != XST_SUCCESS) {
      return;
   }
}
