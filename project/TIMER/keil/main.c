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
void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)//��ʱ���¼�����
{
    static uint32_t i;
    uint32_t led_to_invert = ((i++) % LEDS_NUMBER);//ÿ�ζ�ʱʱ�䵽����LED���

    switch (event_type)  //�ж��¼��Ƚ�ͨ��
    {
        case NRF_TIMER_EVENT_COMPARE0:
            bsp_board_led_invert(led_to_invert);  //��תLED״̬
            break;

        default:
            //Do nothing.
            break;
    }
}


int main()
{
		uint32_t time_ms = 500; //�����Ƚ��¼�֮���ʱ��(����)��
    uint32_t time_ticks;    //��ʱ������
    uint32_t err_code = NRF_SUCCESS;  

    //LED��ʼ��
    bsp_board_leds_init();

    //Configure TIMER_LED for generating simple light effect - leds on board will invert his state one after the other.
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;  //���涨ʱ��ģʽ����
    err_code = nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms); //����ʱʱ��תΪ������

    nrf_drv_timer_extended_compare(
         &TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true); //�󶨶�ʱ��ͨ��

    nrf_drv_timer_enable(&TIMER_LED);//ʹ�ܶ�ʱ��

    while (1)
    {
        __WFI();
    }
}
