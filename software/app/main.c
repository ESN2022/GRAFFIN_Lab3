#include <stdio.h>
#include "system.h"
#include "unistd.h"
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"

#define POWER_CTL  0x2D                                 // registre Power Control
#define DATA_FORMAT  0x31                               // registre Data Format
#define DATAX0  0x32                                    // bit de poids faible axe X
#define DATAX1  0x33                                    // bit de poids fort axe X
#define DATAY0  0x34                                    // bit de poids faible axe Y
#define DATAY1  0x35                                    // bit de poids fort axe Y
#define DATAZ0  0x36                                    // bit de poids faible axe Z
#define DATAZ1  0x37


void I2C_WRITE(alt_u32 base,alt_u32 reg, alt_u8 data){
	
	if(!I2C_start(base,0x1D,1)){
		//printf("start ok\n");
		if(!I2C_write(base, reg,0)){
			I2C_write(base, data, 1);
		}
	}
}	

int I2C_READ(alt_u32 base, alt_u32 reg){
	
	int data;
	
	if(!I2C_start(base,0x1D,1)){
		//printf("start ok\n");
		I2C_write(base, reg,1);
		if(!I2C_start(base,0x1D,0)){
			data = I2C_read(base,1);
			//printf("data= %x \n",data);
			return data;
		}
	}	
}






int main(void){
	
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,100000);
	I2C_WRITE(OPENCORES_I2C_0_BASE, POWER_CTL, (1 << 3));
	I2C_WRITE(OPENCORES_I2C_0_BASE, DATA_FORMAT, 1);
	int data1,data2;
	printf("init\n");
	
	//while(1){
		
		data1 = I2C_READ(OPENCORES_I2C_0_BASE, DATAX1);
		data2 = I2C_READ(OPENCORES_I2C_0_BASE, DATAX0);
		printf("data = %x\n", data1<<8 | data2);
		
		
		usleep(250000);
	//}
	
	
	return 0;
}