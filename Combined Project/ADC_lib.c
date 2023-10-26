#include "ADC_lib.h"
volatile unsigned int adc_done = 0;

int ADC_init(mxc_adc_monitor_t adc_mon, mxc_adc_chsel_t adc_chan){
    if (MXC_ADC_Init() != E_NO_ERROR) {
        printf("Error Bad Parameter\n");
        return E_BAD_PARAM;
    }

    /* Set up LIMIT0 to monitor high and low trip points */
    MXC_ADC_SetMonitorChannel(adc_mon, adc_chan);
    MXC_ADC_SetMonitorHighThreshold(adc_mon, 0x3ff);
    MXC_ADC_SetMonitorLowThreshold(adc_mon, 0x0);
    MXC_ADC_EnableMonitor(adc_mon);
    return E_NO_ERROR;

}

int ADC_conversion(mxc_adc_chsel_t adc_chan){
    int adc_val = 0;
    if ((adc_val = MXC_ADC_StartConversion(adc_chan)) == E_OVERFLOW){
        return E_OVERFLOW;
    }
    return adc_val;
}