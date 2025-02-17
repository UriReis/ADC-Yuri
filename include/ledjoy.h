#ifndef LEDJOY_H
#define LEDJOY_H


void inipwm();
void ledjoy();
void gpio_irq_handler(uint gpio, uint32_t events);

#endif