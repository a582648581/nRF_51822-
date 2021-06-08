#include <stdio.h>
#include <sdk_config.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

int main()
{
		//GPIO初始化
		//初始化LED1
		//nrf_gpio_cfg_output(LED_1);
	  //点亮LED1
		//nrf_gpio_pin_write(LED_1,0);
	  //nrf_gpio_pin_clear(LED_1);
		
	
	 //流水灯
		bsp_board_leds_init();
	
	  while (true)
    {
				for (int i = 0; i < LEDS_NUMBER; i++)
        {
            bsp_board_led_invert(i);
            nrf_delay_ms(500);
	    	}
  	}
	
//  例程代码	
//	 /* Configure board. */
//    bsp_board_leds_init();

//    /* Toggle LEDs. */
//    while (true)
//    {
//			for (int i = 0; i < LEDS_NUMBER; i++)
//        {
//            bsp_board_led_invert(i);
//            nrf_delay_ms(500);
//        }
//    }
	
}
