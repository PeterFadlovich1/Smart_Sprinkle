#ifndef TIMER_LIB_H
#define TIMER_LIB_H
#include "tmr.h"
#include "stdio.h"
#include "nvic_table.h"
#include "lp.h"


#define OST_CLOCK_SOURCE MXC_TMR_32K_CLK // \ref mxc_tmr_clock_t
#define PWM_CLOCK_SOURCE MXC_TMR_APB_CLK // \ref mxc_tmr_clock_t
#define CONT_CLOCK_SOURCE MXC_TMR_8M_CLK // \ref mxc_tmr_clock_t




// Parameters for Continuous timer
#define OST_FREQ 20 // (Hz)


#define MXC_GPIO_PORT_INTERRUPT_STATUS1 MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_STATUS1 MXC_GPIO_PIN_31
#define MXC_GPIO_PORT_INTERRUPT_STATUS2 MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_STATUS2 MXC_GPIO_PIN_30


#define OST_TIMER1 MXC_TMR4 // Can be MXC_TMR0 through MXC_TMR5

void OneshotTimer(mxc_tmr_regs_t *timer);
void OneshotTimerHandler(void);

void gpio_isr1(void *cbdata);

void gpio_isr2(void *cbdata);

#endif