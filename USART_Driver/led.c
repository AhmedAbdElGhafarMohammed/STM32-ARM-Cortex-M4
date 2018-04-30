
#include "hal_gpio_driver.h"
#include "led.h"

#define GPIO_BUTTON	0

void led_init(void){
	GPIO_PIN_CONF_t led_pin_conf;
	
	_HAL_RCC_GPIOD_CLK_ENABLE();
	
	led_pin_conf.pin = LED_GREEN;
	led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	led_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	led_pin_conf.pull = GPIO_PIN_NO_PULL_UP_DOWN;
	hal_gpio_init(GPIO_PORT_D,&led_pin_conf);
	
	led_pin_conf.pin = LED_BLUE;
	hal_gpio_init(GPIO_PORT_D,&led_pin_conf);
	led_pin_conf.pin = LED_ORANGE;
	hal_gpio_init(GPIO_PORT_D,&led_pin_conf);
	led_pin_conf.pin = LED_RED;
	hal_gpio_init(GPIO_PORT_D,&led_pin_conf);
}

void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin){
	hal_gpio_write_pin(GPIOx,pin,1);
}

void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin){
	hal_gpio_write_pin(GPIOx,pin,0);
}

void led_turn_toggel(GPIO_TypeDef *GPIOx, uint16_t pin){
	if(hal_gpio_read_pin(GPIOx,pin)){
		hal_gpio_write_pin(GPIOx,pin,0);
	}
	else{
		hal_gpio_write_pin(GPIOx,pin,1);
	}
}

void delay(void)
{
	volatile uint32_t x;
	for(x=0;x<250000;x++)
	{
		__ASM("nop");
		__ASM("nop");
		__ASM("nop");
		__ASM("nop");
		__ASM("nop");
		__ASM("nop");
		__ASM("nop");
		__ASM("nop");
	}
}

int main(void){
	led_init();
	
	_HAL_RCC_GPIOA_CLK_ENABLE();
	hal_gpio_configure_interrupt(GPIO_BUTTON, INT_RISING_FALLING_EDGE);
	hal_gpio_enable_interrupt(GPIO_BUTTON, EXTI0_IRQn);
	for(;;)
	{
		led_turn_toggel(GPIO_PORT_D,LED_BLUE);
		delay();
	}
	return 0;
}

void EXTI0_IRQHandler(void){
	hal_gpio_clear_interrupt(GPIO_BUTTON);
	led_turn_toggel(GPIO_PORT_D,LED_ORANGE);
}




