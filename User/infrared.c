#include "all.h"

// low voltage when dark
// high voltage when light

// init adc for target channel
void adcChannelInit(u8 channel) {
  ADC_InitTypeDef ADC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
  ADC_Cmd(ADC1, ENABLE);
  delay_us(1);
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1) != RESET)
    ;
}

void adcInit() {
  adcGpioInit();
  adcCheck();
}

void adcGpioInit() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
                                GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void adcCheck() {
  for (u8 i = 0; i < 10; i++) {
    adcChannelInit(i);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
      ;
    int err = ADC_GetConversionValue(ADC1) - divide[i];
    if (err < -1000 || err > 1000) {
      safe = 0;
      break;
    }
  }
}
