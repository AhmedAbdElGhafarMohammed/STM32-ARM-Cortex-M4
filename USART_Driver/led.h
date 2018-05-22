
#ifndef _LED_H
#define _LED_H
	
#define LED_GREEN		12
#define LED_ORANGE		13
#define LED_RED			14
#define LED_BLUE		15

void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin);
void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin);
void led_turn_toggel(GPIO_TypeDef *GPIOx, uint16_t pin);
void delay(void);

#endif
