#ifndef SOLENOID_H
#define SOLENOID_H
#include "mxc_device.h"
#include "nvic_table.h"
#include "pb.h"
#include "board.h"
#include "gpio.h"


#define MXC_GPIO_PORT_INTERRUPT_STATUS1 MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_STATUS1 MXC_GPIO_PIN_31
#define MXC_GPIO_PORT_INTERRUPT_STATUS2 MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_STATUS2 MXC_GPIO_PIN_30

#define MXC_GPIO_PORT_INTERRUPT_IN1 MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_IN1 MXC_GPIO_PIN_3

#define MXC_GPIO_PORT_INTERRUPT_IN2 MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_IN2 MXC_GPIO_PIN_2

#include "Timer_lib.h"
int Solenoid_init();

#endif