#ifndef ADCLIB_H
#define ADCLIB_H
#include <stdio.h>
#include <stdint.h>
#include <mxc.h>
#include "adc.h"

int ADC_init(mxc_adc_monitor_t adc_mon, mxc_adc_chsel_t adc_chan);
int ADC_conversion(mxc_adc_chsel_t adc_chan);

#endif