#include "Timer_lib.h"


/***** Globals *****/


/***** Functions *****/


void OneshotTimer(mxc_tmr_regs_t *timer)
{
    // Declare variables
    mxc_tmr_cfg_t tmr;
    uint32_t periodTicks = MXC_TMR_GetPeriod(timer, OST_CLOCK_SOURCE, 128, OST_FREQ);
    mxc_tmr_cfg_t *test = &tmr;
    /*
    Steps for configuring a timer for PWM mode:
    1. Disable the timer
    2. Set the prescale value
    3  Configure the timer for continuous mode
    4. Set polarity, timer parameters
    5. Enable Timer
    */
    MXC_TMR_Shutdown(timer);
    tmr.pres = TMR_PRES_128;
    tmr.mode = TMR_MODE_ONESHOT;
    tmr.bitMode = TMR_BIT_MODE_32;
    tmr.clock = OST_CLOCK_SOURCE;
    tmr.cmp_cnt = periodTicks; //SystemCoreClock*(1/interval_time);
    tmr.pol = 0;

    if (MXC_TMR_Init(timer, &tmr, true) != E_NO_ERROR) {
        printf("Failed Continuous timer Initialization.\n");
        return;
    }

    MXC_TMR_EnableInt(timer);

    // Clear Wakeup status
    MXC_LP_ClearWakeStatus();
    // Enable wkup source in Poower seq register
    MXC_LP_EnableTimerWakeup(timer);
    // Enable Timer wake-up source
    MXC_TMR_EnableWakeup(timer, &tmr);

    MXC_TMR_Start(timer);
}

