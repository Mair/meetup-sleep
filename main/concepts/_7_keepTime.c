#include <stdio.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "esp_system.h"

#define BUTTON 25

RTC_DATA_ATTR long timeGoneToSleep = 0;

void _7_keepTime(void)
{
  rtc_gpio_deinit(BUTTON);

  rtc_gpio_pullup_en(BUTTON);
  rtc_gpio_pulldown_dis(BUTTON);
  esp_sleep_enable_ext0_wakeup(BUTTON, 0);

  struct timeval tv_now;

  gettimeofday(&tv_now, NULL);
  long time_a_seep = tv_now.tv_sec - timeGoneToSleep;
  printf("seconds since power up %ld time_a_seep %ld \n", tv_now.tv_sec, time_a_seep);
  timeGoneToSleep = tv_now.tv_sec;
  esp_deep_sleep_start();
}
