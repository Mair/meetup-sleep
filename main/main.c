#include <stdio.h>
#include <string.h>
#include "connect.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "cJSON.h"
#include "./concepts/concepts.h"

void __send_email_sendgrid(void);
void app_main(void)
{
  ESP_ERROR_CHECK(nvs_flash_init());
  wifi_init();

  // comment out all lines except one

  //__benchmark_online();
  //_1_light_sleep_timer();
  //_2_light_GPIO();
  //_3_deep_sleep_timer();
  //_4_deep_sleep_EXT_0();
  //_5_deep_sleep_EXT_1();
  //_6_hibernation();
  //_7_keepTime();
  __send_email_sendgrid();
}
