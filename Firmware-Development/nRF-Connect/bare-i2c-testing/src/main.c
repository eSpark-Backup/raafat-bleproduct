#include <zephyr/kernel.h>
#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include "bmi323.h"

int main(void)
{
        int ret =  0;
        k_sleep(K_SECONDS(1));
        bmi323_init();
        bmi323_soft_reset();
        while(true)
        {
                // bmi323_read_acc();
                bmi323_read_gyro();
                k_sleep(K_MSEC(10));
        }

        return ret;

}


