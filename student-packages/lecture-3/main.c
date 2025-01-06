#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include <stdio.h>

#define LED_PIN 6

int main()
{
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125);
    pwm_config_set_wrap(&config, 1000);
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(LED_PIN, 1000);
    stdio_init_all();

    while (1)
    {
        for (int level = 0; level <= 1000; level++)
        {
            pwm_set_gpio_level(LED_PIN, level);
            printf("\nFade Up: %d", level);
            sleep_ms(1);
        }

        for (int level = 1000; level >= 0; level--)
        {
            pwm_set_gpio_level(LED_PIN, level);
            printf("\nFade Down: %d", level);
            sleep_ms(1);
        }
    }
    return 0;
}