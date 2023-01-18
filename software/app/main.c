#include <stdio.h>
#include "system.h"
#include "unistd.h"
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"



#define ADRR 0x1D										// I2C adress									
#define POWER_CTL  0x2D                                 // registre Power Control
#define DATA_FORMAT  0x31                               // registre Data Format
#define DATAX0  0x32                                    // bit de poids faible axe X
#define DATAX1  0x33                                    // bit de poids fort axe X
#define DATAY0  0x34                                    // bit de poids faible axe Y
#define DATAY1  0x35                                    // bit de poids fort axe Y
#define DATAZ0  0x36                                    // bit de poids faible axe Z
#define DATAZ1  0x37


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
	printf("dataz = %d\n", a);
	
	printf("\n");
	usleep(1000000);
}


void INIT_ADXL345(void){
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,100000);
	I2C_WRITE(OPENCORES_I2C_0_BASE, POWER_CTL, (1 << 3));
	I2C_WRITE(OPENCORES_I2C_0_BASE, DATA_FORMAT, (1 << 3));
	
	printf("init\n\n");
	
}






int main(void){
	
	
	INIT_ADXL345();
	
		
	
	
	
	
	while(1){
		READ_XYZ();
		
	}
	
	
	return 0;
}


/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

int main(){
    // Initialisation des variables
    int file;
    int accel_addr = 0x53;
    char buf[2];
    int retval;
    float x,y,z;

    // Ouverture du fichier de l'interface i2c
    if ((file = open("/dev/i2c-1", O_RDWR)) < 0){
        printf("Impossible d'ouvrir le fichier\n");
        return -1;
    }

    // Configuration et ouverture de l'accéléromètre
    if (ioctl(file, I2C_SLAVE, accel_addr) < 0){
        printf("Impossible de configurer le capteur\n");
        return -1;
    }

    // Réinitialisation de l'accéléromètre
    buf[0] = 0x2D;
    buf[1] = 0x08;
    retval = write(file, buf, 2);
    if (retval != 2) {
        printf("Erreur lors de la réinitialisation du capteur\n");
        return -1;
    }

    // Définition du mode de mesure
    buf[0] = 0x31;
    buf[1] = 0x08;
    retval = write(file, buf, 2);
    if (retval != 2) {
        printf("Erreur lors de la définition du mode de mesure\n");
        return -1;
    }

    // Lecture des données
    buf[0] = 0x32;
    retval = write(file, buf, 1);
    if (retval != 1) {
        printf("Erreur lors de la lecture des données\n");
        return -1;
    }
    retval = read(file, buf, 6);
    if (retval != 6) {
        printf("Erreur lors de la lecture des données\n");
        return -1;
    }

    // Conversion des données
    x = (buf[1] << 8) | buf[0];
    y = (buf[3] << 8) | buf[2];
    z = (buf[5] << 8) | buf[4];
    x = x * 0.0039;
    y = y * 0.0039;
    z = z * 0.0039;

    // Affichage des données
    printf("x: %.2f\n", x);
    printf("y: %.2f\n", y);
    printf("z: %.2f\n", z);

    return 0;
}

*/