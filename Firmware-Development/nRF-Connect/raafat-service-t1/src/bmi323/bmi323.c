#include <zephyr/kernel.h>
// #include "raafat_bmi323.h"
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>
#include <math.h>

#include "bmi323.h"

#define I2C0_NODE DT_NODELABEL(mysensor)

/*! Earth's gravity in m/s^2 */
#define GRAVITY_EARTH  (9.80665f)

#define BMI323_CHIP_ID_REG 0x00
#define BMI323_TEMP_REG 0x09
#define BMI323_CMD_REG 0x7E

#define BMI323_ACCX_REG 0x03
#define BMI323_ACCY_REG 0x04
#define BMI323_ACCZ_REG 0x05
#define BMI323_ACC_CONF_REG 0x20

#define BMI323_GYX_REG 0x06
#define BMI323_GYY_REG 0x07
#define BMI323_GYZ_REG 0x08
#define BMI323_GYRO_CONF_REG 0x21

/*Bit mask and shifts*/
// Bit masks and shifts, based on the configuration provided for ACCEL
#define OUTPUT_DATA_RATE_MASK 0x000F
#define ACCELEROMETER_RANGE_MASK 0x0070
#define BAND_WIDTH_MASK 0x0080
#define SAMPLE_AVERAGE_NUM_MASK 0x0700
#define ACCELEROMETER_MODE_MASK 0x7000

/* onfiguration provided for GYRO */
#define GYROSCOPE_OUTPUT_DATA_RATE 0x8
#define GYROSCOPE_RANGE 0x0
#define GYROSCOPE_BAND_WIDTH 0x0
#define GYROSCOPE_SAMPLE_AVERAGE_NUM 0x3
#define GYROSCOPE_MODE 0x4

/* Accelerometer config bit shifts */
#define OUTPUT_DATA_RATE_SHIFT 0
#define ACCELEROMETER_RANGE_SHIFT 4
#define BAND_WIDTH_SHIFT 7

#define SAMPLE_AVERAGE_NUM_SHIFT 0
#define ACCELEROMETER_MODE_SHIFT 4

/* Gyroscope config bit shifts */
#define GYROSCOPE_OUTPUT_DATA_RATE_SHIFT 0
#define GYROSCOPE_RANGE_SHIFT 4
#define GYROSCOPE_BAND_WIDTH_SHIFT 7

#define GYROSCOPE_SAMPLE_AVERAGE_NUM_SHIFT 0
#define GYROSCOPE_MODE_SHIFT 4


// Example configuration values - replace these with your actual desired settings
/*low byte*/
uint16_t outputDataRateValue = 0xE; // Example value for output data rate
uint16_t accelerometerRangeValue = 0x0; // Example value for accelerometer range
uint16_t bandWidthValue = 0x1; // Example for band width

/*high byte*/
uint16_t sampleAverageNumValue = 0x6; // Example for sample average number
uint16_t accelerometerModeValue = 0x7; // Example for accelerometer mode

static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

static uint8_t acc_config[3] = {BMI323_ACC_CONF_REG, 0, 0};
static uint8_t gyro_config[3] = {BMI323_GYRO_CONF_REG, 0, 0};
static uint8_t sensor_regs = 0x00;
static uint8_t data[25] = {0};
static float x = 0, y = 0, z = 0;

static float lsb_to_mps2(int16_t val, int8_t g_range, uint8_t bit_width);

static raafat_data_t* s_new_raafat_data;

int bmi323_init(raafat_data_t* new_raafat_data)
{
    int ret = 0;
    if (!device_is_ready(dev_i2c.bus)) {
            printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
            return 1;
    }
    s_new_raafat_data = new_raafat_data;

    // /* Write */
    // uint8_t config[2] = {0x03,0x8C};
    // ret = i2c_write_dt(&dev_i2c, config, sizeof(config));
    // if(ret != 0){
    //         printk("Failed to write to I2C device address %x at reg. %x \n\r", dev_i2c.addr,config[0]);
    // }

    // /* Read */
    // uint8_t data;
    // ret = i2c_read_dt(&dev_i2c, &data, sizeof(data));
    // if(ret != 0){
    //         printk("Failed to read from I2C device address %x at Reg. %x \n\r", dev_i2c.addr,config[0]);
    // }

    // /* Multiple reg read */
    // uint8_t rgb_value[6]= {0};
    // //Do a burst read of 6 bytes as each color channel is 2 bytes
    // ret = i2c_burst_read_dt(&dev_i2c, BMI323_TEMP_REG,rgb_value,sizeof(rgb_value));

    // /* Write read back to back */
    // uint8_t sensor_regs[2] ={0x02,0x00};
    // uint8_t temp_reading[2]= {0};	
    // ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[0],1,&temp_reading[0],1);
    // if(ret != 0){
    //         printk("Failed to write/read I2C device address %x at Reg. %x \n\r", dev_i2c.addr,sensor_regs[0]);
    // }

    // uint8_t temp_reading[2]= {0};
    // uint8_t sensor_regs = BMI323_TEMP_REG;
    // ret = i2c_write_read_dt(&dev_i2c,&sensor_regs,1,&temp_reading[0],1);
    // if(ret != 0){
    //         printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs);
    // }
    // ret = i2c_write_read_dt(&dev_i2c,&sensor_regs,1,&temp_reading[1],1);
    // if(ret != 0){
    //         printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs);
    // }


    uint16_t chip_id = 0;
    bmi323_soft_reset();
    k_sleep(K_SECONDS(1));
    acc_config[1] = (outputDataRateValue << OUTPUT_DATA_RATE_SHIFT) | (accelerometerRangeValue << ACCELEROMETER_RANGE_SHIFT) | (bandWidthValue << BAND_WIDTH_SHIFT);
    acc_config[2] = (sampleAverageNumValue << SAMPLE_AVERAGE_NUM_SHIFT) | (accelerometerModeValue << ACCELEROMETER_MODE_SHIFT);
    
    gyro_config[0] = BMI323_GYRO_CONF_REG;
    gyro_config[1] = (GYROSCOPE_OUTPUT_DATA_RATE << GYROSCOPE_OUTPUT_DATA_RATE_SHIFT) | (GYROSCOPE_RANGE << GYROSCOPE_RANGE_SHIFT) | (GYROSCOPE_BAND_WIDTH << GYROSCOPE_BAND_WIDTH_SHIFT);
    gyro_config[2] = (GYROSCOPE_SAMPLE_AVERAGE_NUM << GYROSCOPE_SAMPLE_AVERAGE_NUM_SHIFT) | (GYROSCOPE_MODE << GYROSCOPE_MODE_SHIFT);
    
    i2c_write_dt(&dev_i2c, &acc_config, sizeof(acc_config));
    i2c_write_dt(&dev_i2c, &gyro_config, sizeof(gyro_config));
}

void bmi323_read_acc()
{
                // bmi323_read_data(&data, &sensor_regs, 2);
                // // i2c_write_read_dt(&dev_i2c,&sensor_regs,1,&data,4);       
                // printk("CHIP DATA = %d, %d, %d, %d\n", data[0], data[1], data[2], data[3]);
                // chip_id = data[2];
                // printk("CHIP_ID = %d", chip_id);

                // sensor_regs = 0x02;
                // bmi323_read_data(&data, &sensor_regs, 1);
                // // i2c_write_read_dt(&dev_i2c,&sensor_regs,1,&data,4);       
                // printk("CHIP DATA = %d, %d, %d, %d\n", data[0], data[1], data[2], data[3]);
                // chip_id = data[2];
                // printk("CHIP_ID = %d", chip_id);



                sensor_regs = BMI323_ACCX_REG;
                bmi323_read_data(&data, &sensor_regs, 6);

                /* Converting lsb to meter per second squared for 16 bit accelerometer at 2G range. */
                x = lsb_to_mps2((int16_t)(((uint16_t)data[3] << 8)|((uint16_t)data[2] << 0)), 2, 16);
                y = lsb_to_mps2((int16_t)(((uint16_t)data[5] << 8)|((uint16_t)data[4] << 0)), 2, 16);
                z = lsb_to_mps2((int16_t)(((uint16_t)data[7] << 8)|((uint16_t)data[6] << 0)), 2, 16);

                // printk("ACC DATA = %d.%03d, %d.%03d, %d.%03d\n", 
                //             data[3], 
                //             data[2], 
                //             data[5], 
                //             data[4],
                //             data[7], 
                //             data[6]
                //         );

                s_new_raafat_data->accX_val1 = data[3];
                s_new_raafat_data->accX_val2 = data[2];
                s_new_raafat_data->accY_val1 = data[5];
                s_new_raafat_data->accY_val2 = data[4];
                s_new_raafat_data->accZ_val1 = data[7];
                s_new_raafat_data->accZ_val2 = data[6];

                printf("ACC DATA = %f, %f, %f\n", 
                        (float)((int16_t)data[3] << 8 | data[2]) / 256.0F, 
                        (float)((int16_t)data[5] << 8 | data[4]) / 256.0F,
                        (float)((int16_t)data[7] << 8 | data[6]) / 256.0F
                        );

                // printk("Config : %x, %x", acc_config[1], acc_config[2]);

                // printk("ACC DATA : %d, %d, %d\n", x, y ,z);

                // sensor_regs = 0x7E;
                // bmi323_read_data(&data, &sensor_regs, 2);
                // printk("ACC DATA = %d, %d, %d, %d, %d\n", data[0], data[1], data[2], data[3], data[4]);
}

void bmi323_read_gyro()
{
    sensor_regs = BMI323_GYX_REG;
    bmi323_read_data(&data, &sensor_regs, 6);

    // printk("GYRO DATA 1 = %d.%03d, %d.%03d, %d.%03d\n", 
    //         data[3], 
    //         data[2], 
    //         data[5],
    //         data[4],
    //         data[7],                    
    //         data[6]
    //         );
    printf("GYRO DATA = %f, %f, %f\n", 
        (float)((int16_t)data[3] << 8 | data[2]) / 256.0F, 
        (float)((int16_t)data[5] << 8 | data[4]) / 256.0F,
        (float)((int16_t)data[7] << 8 | data[6]) / 256.0F
        );

    // printk("GYRO DATA = %d, %d, %d\n", 
    //         data[3], 
    //         data[5],
    //         data[7]              
    //         );

    s_new_raafat_data->gyroX_val1 = data[3];
    s_new_raafat_data->gyroX_val2 = data[2];
    s_new_raafat_data->gyroY_val1 = data[5];
    s_new_raafat_data->gyroY_val2 = data[4];
    s_new_raafat_data->gyroZ_val1 = data[7];
    s_new_raafat_data->gyroZ_val2 = data[6];
}


void bmi323_read_temp()
{
    sensor_regs = BMI323_TEMP_REG;
    bmi323_read_data(&data, &sensor_regs, 2);
    // printk("TEMP DATA = %d, %d, %d, %d\n", data[0], data[1], data[2], data[3]);   
    
    s_new_raafat_data->temp_h = data[3]; //7 MSB 0-128 = -41-87 also 23 celc = 0x0000
    s_new_raafat_data->temp_l = data[2]; //9 LSB 512 LSB/kelvin 2^9 = 512

    /* Temp calculations */
    float temp = (((((int16_t)data[3]) << 8) | (data[2])) / 512.0F) + 23.0F;
    int16_t temp_raw = (((uint16_t)data[3]) << 8) | (uint16_t)(data[2]);
    // printk("TEMP H %x\n", data[3]);
    // printk("TEMP L %x\n", data[2]);
    // printk("TEMP = %d.%03u\n", (int)data[3], (unsigned int)(data[2])/255.0F*100.0F);
    float mTemp = temp_raw/512.0F;
    printf("BMI TEMPERATURE %f\xB0""C\n", mTemp+23.0F);

}


void bmi323_read_data(uint8_t* data, uint8_t* address, uint8_t bytes_to_read)
{       
    #define DUMMY_BYTE_LEN 2
    i2c_write_read_dt(&dev_i2c,address,1,data,bytes_to_read + DUMMY_BYTE_LEN);       
}

void bmi323_soft_reset() 
{
    uint8_t config[2] = {BMI323_CMD_REG,0xDEAF};
    i2c_write_dt(&dev_i2c, &config, sizeof(config));
}

void bmi323_acc_config()
{

}

void bmi323_gyro_config()
{

}


/*!
 * @brief This function converts lsb to meter per second squared for 16 bit accelerometer at
 * range 2G, 4G, 8G or 16G.
 */
static float lsb_to_mps2(int16_t val, int8_t g_range, uint8_t bit_width)
{
    double power = 2;

    float half_scale = (float)((pow((double)power, (double)bit_width) / 2.0f));

    return (GRAVITY_EARTH * val * g_range) / half_scale;
}
