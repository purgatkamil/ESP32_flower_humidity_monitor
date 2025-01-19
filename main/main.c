#include <stdio.h>

#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "wifi.h"
#include "spiffs.h"

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    spiffs_init();
    spiffs_list_files();
    wifi_init();
}