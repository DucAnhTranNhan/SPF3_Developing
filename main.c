#include "stm32f30x.h"
#include "usart.h"
#include "mpu6050.h"

float angle_pitch_input, angle_roll_input;

float gyro_pitch_input, gyro_roll_input, gyro_yaw_input;


void systick_init(void)
{
		if (SysTick_Config(SystemCoreClock / 1000)) // Tan so 1kHz cu sau 1ms thi xay ra 1 ngat tran
		{ 		
				while (1)
				{}
		}
}


int main() {
	i2cSetOverclock(false);
	
	i2cInit(I2CDEV_1);
	
	USART1_CONFIGURATION(9600);
  
	systick_init();	
	
	mpu6050Init();
	
	printf("Calibrating gyro....");
	for (cal_int = 0; cal_int < 2000 ; cal_int ++) {
		mpu6050Read();
		
		gyro_roll_cal += gyro_y;                      //Add roll value to gyro_roll_cal
    gyro_pitch_cal += gyro_x;                    //Add pitch value to gyro_pitch_cal
    gyro_yaw_cal += gyro_z;                        //Add yaw value to gyro_yaw_cal
		
		if(cal_int%100 == 0)printf(".");
		
	}		
	
	printf("done !\n");
	
	
	gyro_roll_cal /= 2000;                             //Divide the roll total by 2000
  gyro_pitch_cal /= 2000;                            //Divide the pitch total by 2000
  gyro_yaw_cal /= 2000;                              //Divide the yaw total by 2000
	
	while(1) {
		
		mpu6050Read();
		
		get_acc_angle();

	gyro_roll_input = (gyro_roll_input * 0.8) + ((gyro_y / 57.14286) * 0.2);            //Gyro pid input is deg/sec.
  gyro_pitch_input = (gyro_pitch_input * 0.8) + ((gyro_x / 57.14286) * 0.2);         //Gyro pid input is deg/sec.
  gyro_yaw_input = (gyro_yaw_input * 0.8) + ((gyro_z / 57.14286) * 0.2);               //Gyro pid input is deg/sec.
		
		
		
		printf("  %.2f  %.2f    %.2f  %.2f  %.2f  \n", acc_x_angle, acc_y_angle, gyro_pitch_input, gyro_roll_input, gyro_yaw_input);

		
		}
	
	
	}

	void SysTick_Handler(void)
{
		sys_time++;	
}