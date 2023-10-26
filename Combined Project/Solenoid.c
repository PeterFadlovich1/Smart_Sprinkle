#include "Solenoid.h"
uint16_t pin = 0;
void gpio_isr1(void *cbdata)
{
    mxc_gpio_cfg_t *cfg = cbdata;
    MXC_GPIO_OutToggle(cfg->port, cfg->mask);
    MXC_TMR_Start(OST_TIMER1);
    printf("turned back on1!\n");
    pin = 1;
}

void gpio_isr2(void *cbdata)
{
    mxc_gpio_cfg_t *cfg = cbdata;
    MXC_GPIO_OutToggle(cfg->port, cfg->mask);
    MXC_TMR_Start(OST_TIMER1);
    printf("turned back on2!\n");
    pin = 2;
}


void OneshotTimerHandler(void)
{
    // Clear interrupt
    MXC_TMR_ClearFlags(OST_TIMER1);

    // Clear interrupt
    if (MXC_TMR4->wkfl & MXC_F_TMR_WKFL_A) {
        MXC_TMR4->wkfl = MXC_F_TMR_WKFL_A;
        MXC_GPIO_OutToggle( pin == 1 ? MXC_GPIO_PORT_INTERRUPT_STATUS1 : MXC_GPIO_PORT_INTERRUPT_STATUS2,  pin == 1 ? MXC_GPIO_PIN_INTERRUPT_STATUS1 : MXC_GPIO_PIN_INTERRUPT_STATUS2);
    }
}
int Solenoid_init(){
    mxc_gpio_cfg_t gpio_interrupt1;
    mxc_gpio_cfg_t gpio_interrupt2;
    mxc_gpio_cfg_t gpio_interrupt_status1;
    mxc_gpio_cfg_t gpio_interrupt_status2;
    MXC_NVIC_SetVector(TMR4_IRQn, OneshotTimerHandler);
    NVIC_EnableIRQ(TMR4_IRQn);

    OneshotTimer(OST_TIMER1);
    gpio_interrupt_status1.port = MXC_GPIO_PORT_INTERRUPT_STATUS1;
    gpio_interrupt_status1.mask = MXC_GPIO_PIN_INTERRUPT_STATUS1;
    gpio_interrupt_status1.pad = MXC_GPIO_PAD_NONE;
    gpio_interrupt_status1.func = MXC_GPIO_FUNC_OUT;
    gpio_interrupt_status1.vssel = MXC_GPIO_VSSEL_VDDIOH;
    MXC_GPIO_Config(&gpio_interrupt_status1);

    gpio_interrupt_status2.port = MXC_GPIO_PORT_INTERRUPT_STATUS2;
    gpio_interrupt_status2.mask = MXC_GPIO_PIN_INTERRUPT_STATUS2;
    gpio_interrupt_status2.pad = MXC_GPIO_PAD_NONE;
    gpio_interrupt_status2.func = MXC_GPIO_FUNC_OUT;
    gpio_interrupt_status2.vssel = MXC_GPIO_VSSEL_VDDIOH;
    MXC_GPIO_Config(&gpio_interrupt_status2);

    MXC_GPIO_OutClr( MXC_GPIO_PORT_INTERRUPT_STATUS2,  MXC_GPIO_PIN_INTERRUPT_STATUS2);

    gpio_interrupt1.port = MXC_GPIO_PORT_INTERRUPT_IN1;
    gpio_interrupt1.mask = MXC_GPIO_PIN_INTERRUPT_IN1;
    gpio_interrupt1.pad = MXC_GPIO_PAD_PULL_UP;
    gpio_interrupt1.func = MXC_GPIO_FUNC_IN;
    gpio_interrupt1.vssel = MXC_GPIO_VSSEL_VDDIO;
    MXC_GPIO_Config(&gpio_interrupt1);
    MXC_GPIO_RegisterCallback(&gpio_interrupt1, gpio_isr1, &gpio_interrupt_status1);
    MXC_GPIO_IntConfig(&gpio_interrupt1, MXC_GPIO_INT_FALLING);
    MXC_GPIO_EnableInt(gpio_interrupt1.port, gpio_interrupt1.mask);
    NVIC_EnableIRQ(MXC_GPIO_GET_IRQ(MXC_GPIO_GET_IDX(MXC_GPIO_PORT_INTERRUPT_IN1)));

    gpio_interrupt2.port = MXC_GPIO_PORT_INTERRUPT_IN2;
    gpio_interrupt2.mask = MXC_GPIO_PIN_INTERRUPT_IN2;
    gpio_interrupt2.pad = MXC_GPIO_PAD_PULL_UP;
    gpio_interrupt2.func = MXC_GPIO_FUNC_IN;
    gpio_interrupt2.vssel = MXC_GPIO_VSSEL_VDDIO;
    MXC_GPIO_Config(&gpio_interrupt2);
    MXC_GPIO_RegisterCallback(&gpio_interrupt2, gpio_isr2, &gpio_interrupt_status2);
    MXC_GPIO_IntConfig(&gpio_interrupt2, MXC_GPIO_INT_FALLING);
    MXC_GPIO_EnableInt(gpio_interrupt2.port, gpio_interrupt2.mask);
    NVIC_EnableIRQ(MXC_GPIO_GET_IRQ(MXC_GPIO_GET_IDX(MXC_GPIO_PORT_INTERRUPT_IN2)));
    return 0;
}