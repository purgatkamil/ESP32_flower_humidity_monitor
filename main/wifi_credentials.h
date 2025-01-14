#pragma once

#include "spiffs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "esp_err.h"
#include "esp_log.h"

#include "esp_spiffs.h"

void read_credentials(char* ssid, char* password);
void get_recent_ip_from_file(char* recent_ip);
void save_ip_to_file(const char *ip);