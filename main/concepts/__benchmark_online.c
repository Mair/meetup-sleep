#include <stdio.h>
#include <string.h>
#include "connect.h"
#include "esp_http_client.h"
#include "esp_log.h"

static const char *TAG = "BENCHMARK";

static esp_err_t on_client_data(esp_http_client_event_t *evt)
{
  static uint64_t _time;
  static int chunk_count;
  static int total_length;
  static int total_bytes_in_1_sec;
  static int second_count;

  switch (evt->event_id)
  {

  case HTTP_EVENT_ON_DATA:

    if (_time == 0)
      _time = esp_timer_get_time() + 1000000;
    chunk_count++;
    total_length += evt->data_len;
    total_bytes_in_1_sec += evt->data_len;
    if (esp_timer_get_time() > _time)
    {
      second_count++;
      double MBs = (double)total_bytes_in_1_sec * 8.0 / 1000000.0;
      ESP_LOGI(TAG, "second_count=%d chunk_length=%d total_chunks=%d, total_length=%d MBs=%f\n", second_count, evt->data_len, chunk_count, total_length, MBs);
      total_bytes_in_1_sec = 0;
      _time = esp_timer_get_time() + 1000000;
    }

    break;

  default:
    break;
  }
  return ESP_OK;
}

void benchmark_online()
{

  esp_http_client_config_t esp_http_client_config = {
      .url = "https://www.gutenberg.org/files/2600/2600-0.txt",
      .method = HTTP_METHOD_GET,
      .event_handler = on_client_data,
  };
  esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);

  esp_err_t err = esp_http_client_perform(client);
  if (err == ESP_OK)
  {
    ESP_LOGI(TAG, "HTTP GET status = %d\n", esp_http_client_get_status_code(client));
  }
  else
  {
    ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
  }
  esp_http_client_cleanup(client);
}

void __benchmark_online(void)
{
  ESP_ERROR_CHECK(wifi_connect_sta("POCO", "password", 10000));
  benchmark_online();
  wifi_disconnect();
}