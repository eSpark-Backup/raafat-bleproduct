#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(Application);

int main(void)
{
        while (1)
        {
                LOG_INF("Hello");
                k_msleep(1000);
        }
        
        return 0;
}
