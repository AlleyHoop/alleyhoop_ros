//IMU libs
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9250.h"

//imu data <based on example by grove called IMU_10DOF_TEST>
//the example can be found here : https://github.com/Seeed-Studio/IMU_10DOF/blob/master/examples/IMU_10DOF_Test/IMU_10DOF_Test.ino

MPU9250 accelgyro;
I2Cdev   I2C_M;

uint8_t buffer_m[6];
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t   mx, my, mz;

float Axyz[3]; //accel data
float Gxyz[3]; //gyro data
float Mxyz[3]; //compass data
#define sample_num_mdate  5000

//calibration data
static float mx_centre = 0;
static float my_centre = 0;
static float mz_centre = 0;

void getAccel_Data(void); //
void getGyro_Data(void); //
void getCompass_Data(void); //
void getCompassDate_calibrated(void); //

//setup function
void setup_imu()
{
    //imu init
    Wire.begin();
    accelgyro.initialize();
    accelgyro.testConnection();
    delay(1000);
}

//update function
void update_imu()
{
    getAccel_Data();
    getGyro_Data();
    getCompassDate_calibrated(); 
}


void getAccel_Data(void)
{
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Axyz[0] = (double) ax / 16384;
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;
}

void getGyro_Data(void)
{
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Gxyz[0] = (double) gx * 250 / 32768;
    Gxyz[1] = (double) gy * 250 / 32768;
    Gxyz[2] = (double) gz * 250 / 32768;
}

void getCompass_Data(void)
{
    I2C_M.writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01);
    delay(10);
    I2C_M.readBytes(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer_m);

    mx = ((int16_t)(buffer_m[1]) << 8) | buffer_m[0] ;
    my = ((int16_t)(buffer_m[3]) << 8) | buffer_m[2] ;
    mz = ((int16_t)(buffer_m[5]) << 8) | buffer_m[4] ;

    Mxyz[0] = (double) mx * 1200 / 4096;
    Mxyz[1] = (double) my * 1200 / 4096;
    Mxyz[2] = (double) mz * 1200 / 4096;
}

void getCompassDate_calibrated (void)
{
    getCompass_Data();
    Mxyz[0] = Mxyz[0] - mx_centre;
    Mxyz[1] = Mxyz[1] - my_centre;
    Mxyz[2] = Mxyz[2] - mz_centre;
}