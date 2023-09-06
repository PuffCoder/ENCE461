/**
 * @file battery_monitor.c
 * @author Heng Yin, Jamie Thomas
 * @brief battery monitor
 * @date 2023-05-22
 */

#include <stdlib.h>
#include <string.h>
#include "battery_monitor.h"

int count = 0;

static circBuf_t voltage_buffer;

/* static adc_t *adc; */
adc_t adc;

bool battery_monitor_init(void)
{
  adc_cfg_t adc_cfg =
      {
          .bits = 12,
          .channels = BIT(BATTERY_ADC_CHANNEL),
          .trigger = ADC_TRIGGER_SW,
          .clock_speed_kHz = 1000};

  adc = adc_init(&adc_cfg);
  /* if (!adc) */
  /* pio_config_set(LED_ERROR_PIO,PIO_OUTPUT_HIGH); */

  initCircBuf(&voltage_buffer, BUF_SIZE);

  for (int i = 0; i < BUF_SIZE; i++)
  {
    poll_battery();
  }

  return !(!adc);
}

/* I use 7.4 V ana value is 4095  */
// to-do chech 7 voltage value

// double adc_send(void)
void batt_States(void)
{
  uint16_t data[1];
  double battV;
  /* uint16_t data[1]; */
  adc_read(adc, data, sizeof(data));
  // printf("%d\n",data[0]);
  // Example data at 3.3 volts: data = 1330
  battV = (data[0] - 1000);
  printf("%f\n", battV);

  writeCircBuf(&voltage_buffer, battV);
  /* return  data[0] * 7.4/65535; */
  // return  data[0] *100 /4100;

  // return battV < 50 ? 0 : 1;
  // if (battV < 50)
  //   panic(LED_STATUS_PIO, 6);
  // else
  //   pio_output_high(LED_STATUS_PIO);

  /* return check; */
}

/**
 * Polls the battery and adds voltage to the buffer.
 */
void poll_battery(void)
{
  uint16_t data[1];
  int16_t battV;

  adc_read(adc, data, sizeof(data));

  battV = (data[0] / BATTERY_ADC_LIMIT);

  writeCircBuf(&voltage_buffer, battV);
}

/**
 * Returns false if the battery is below 5.3V.
 */
bool check_battery_ok(void)
{

  int16_t voltage = readAverageCircBuf(&voltage_buffer);
  return (voltage > 53);
}
