#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"
#include "opencores_i2c.h"
#include "altera_avalon_pio_regs.h"

#define ADRR 0x1D										// I2C adresse									

#define POWER_CTL  0x2D                                 // registre Power Control
#define DATA_FORMAT  0x31                               // registre Data Format

#define DATAX0  0x32                                    // bit de poids faible axe X
#define DATAX1  0x33                                    // bit de poids fort axe X
#define DATAY0  0x34                                    // bit de poids faible axe Y
#define DATAY1  0x35                                    // bit de poids fort axe Y
#define DATAZ0  0x36                                    // bit de poids faible axe Z
#define DATAZ1  0x37									// bit de poids fort axe Z

#define OFSX	0x1E
#define OFSY	0x1F
#define OFSZ	0x20

#define OFSX	0x1E
#define OFSY	0x1F
#define OFSZ	0x20

void I2C_WRITE(alt_u32 base,alt_u8 reg, alt_u8 data){
	
	I2C_start(base,ADRR,0);
	I2C_write(base, reg, 0);
	I2C_write(base, data, 1);
	
	return;
}	

int I2C_READ(alt_u32 base, alt_u8 reg){
	
	int data;
	
	I2C_start(base,ADRR,0);
	I2C_write(base, reg,0);
	I2C_start(base,ADRR,1);
	data = I2C_read(base,1);
	
	return data;	
}


void READ_XYZ (void){
	
	alt_16 data;
	alt_32 a;
	
	data = I2C_READ(OPENCORES_I2C_0_BASE, DATAX0);
	data = data | (I2C_READ(OPENCORES_I2C_0_BASE, DATAX1)<<8);
	a = data*4;
	printf("datax = %d\n", a);
		
	data = I2C_READ(OPENCORES_I2C_0_BASE, DATAY0);
	data = data | (I2C_READ(OPENCORES_I2C_0_BASE, DATAY1)<<8);
	a = data*4;
	printf("datay = %d\n", a);

	data = I2C_READ(OPENCORES_I2C_0_BASE, DATAZ0);
	data = data | (I2C_READ(OPENCORES_I2C_0_BASE, DATAZ1)<<8);
	a = data*4;
	
	int signe;
	
	if (a<0){
		signe=0b1111;
		a=-a;
	}
	else{
		signe=0b1110;
	}
	
	
	
	int unit,diz,cent,mil;
	
	unit=a%10;
	a-=unit;
	diz=a%100;
	a-=diz;
	cent=a%1000;
	a-=cent;
	mil=a%10000;
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, (signe << 16) | (mil/1000<<12) | (cent/100<<8) | (diz/10<<4) | unit);
	
	
	printf("dataz = %d\n", a);
	
	printf("\n");
}


void INIT_ADXL345(void){
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,100000);
	I2C_WRITE(OPENCORES_I2C_0_BASE, POWER_CTL, (1 << 3));
	I2C_WRITE(OPENCORES_I2C_0_BASE, DATA_FORMAT, (1 << 3));
	
	printf("init\n\n");
}


void CALIBRATE_XYZ(void){
	
	I2C_WRITE(OPENCORES_I2C_0_BASE, OFSX, (alt_u8) (0/15.6));
	usleep(10000);
	I2C_WRITE(OPENCORES_I2C_0_BASE, OFSY, (alt_u8) (0/15.6));
	usleep(10000);
	I2C_WRITE(OPENCORES_I2C_0_BASE, OFSZ, (alt_u8) (8/15.6));
	usleep(10000);
	
	printf("offset x = %d\n",(I2C_READ(OPENCORES_I2C_0_BASE, OFSX)));
	printf("offset y = %d\n",(I2C_READ(OPENCORES_I2C_0_BASE, OFSY)));
	printf("offset z = %d\n",(I2C_READ(OPENCORES_I2C_0_BASE, OFSZ)));
}




static void timer_interrupts(void* context){
	READ_XYZ();
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}



int main(void){

	INIT_ADXL345();
	CALIBRATE_XYZ();


    // Register the ISR for timer event
    alt_irq_register(TIMER_0_IRQ, NULL,(void*)timer_interrupts);
    // Start timer
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0x0007);	
	
	
	
	
	while(1){}
	
	

	return 0;
}
