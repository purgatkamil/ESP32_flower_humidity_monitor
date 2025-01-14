#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_err.h"
#include "esp_spiffs.h"
#include "esp_log.h"

#include "esp_vfs.h"
#include "dirent.h"

esp_err_t spiffs_init(void);
void spiffs_list_files(void);