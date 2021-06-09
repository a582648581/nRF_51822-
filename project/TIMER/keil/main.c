#include <stdio.h>
#include <sdk_config.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"
#include "nrf_gpio.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"
#include "nrf.h"


const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);  //creating a timer driver instance

const uint8_t leds_list[LEDS_NUMBER] = LEDS_LIST;

/**
 * @brief Handler for timer events.
 */
void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)//定时器事件函数
{
    static uint32_t i;
    uint32_t led_to_invert = ((i++) % LEDS_NUMBER);//每次定时时间到递增LED序号

    switch (event_type)  //判断事件比较通道
    {
        case NRF_TIMER_EVENT_COMPARE0:
            bsp_board_led_invert(led_to_invert);  //翻转LED状态
            break;

        default:
            //Do nothing.
            break;
    }
}


int main()
{
		uint32_t time_ms = 500; //连续比较事件之间的时间(毫秒)。
    uint32_t time_ticks;    //定时器节拍
    uint32_t err_code = NRF_SUCCESS;  

    //LED初始化
    bsp_board_leds_init();

    //Configure TIMER_LED for generating simple light effect - leds on board will invert his state one after the other.
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;  //常规定时器模式设置
    err_code = nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms); //将定时时间转为节拍数

    nrf_drv_timer_extended_compare(
         &TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true); //绑定定时器通道

    nrf_drv_timer_enable(&TIMER_LED);//使能定时器

    while (1)
    {
        __WFI();
    }
}
