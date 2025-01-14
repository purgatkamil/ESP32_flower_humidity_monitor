#include "wifi_credentials.h"

#define TAG "WIFI_CREDENTIALS"

void read_credentials(char* ssid, char* password)
{

    ESP_LOGI(TAG, "Reading credentials..");
    FILE *file = fopen("/storage/secrets.conf", "r");
    if (file == NULL)
    {
        printf("Failed to open secrets.conf\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (strcmp(key, "SSID") == 0) {
            strcpy(ssid, value);
        } else if (strcmp(key, "PASSWORD") == 0) {
            strcpy(password, value);
        }
    }

    fclose(file);
}

void get_recent_ip_from_file(char* recent_ip)
{
    FILE *file = fopen("/storage/secrets.conf", "r");
    if (file == NULL) {
        printf("Failed to open secrets.conf\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (strcmp(key, "RECENT_IP") == 0) {
            strcpy(recent_ip, value);
        }
    }

    fclose(file);
}

#define IP_BUFFER_SIZE 30  // Rozmiar bufora dla adresu IP
#define MAX_LINES 4

void save_ip_to_file(const char *ip)
{
    ESP_LOGI(TAG, "Opening file for reading...");
    FILE *f = fopen("/storage/secrets.conf", "r");

    // Dynamicznie alokowana tablica wskaźników na linie
    char *lines[MAX_LINES] = {0};
    int line_count = 0;
    bool ip_replaced = false;

    if (f) {
        ESP_LOGI(TAG, "File opened successfully for reading.");
        char buffer[IP_BUFFER_SIZE];
        while (fgets(buffer, sizeof(buffer), f) && line_count < MAX_LINES) {
            // Alokujemy pamięć dla każdej linii na podstawie jej długości
            lines[line_count] = strdup(buffer);
            
            // Sprawdzenie, czy linia zawiera "RECENT_IP"
            if (strstr(lines[line_count], "RECENT_IP=") != NULL) {
                ESP_LOGI(TAG, "Found RECENT_IP line, replacing with new IP.");
                free(lines[line_count]);  // Zwolnij starą linię
                asprintf(&lines[line_count], "RECENT_IP=%s\n", ip);  // Alokuj nową linię z nowym IP
                ip_replaced = true;
            }
            line_count++;
        }
        fclose(f);
        ESP_LOGI(TAG, "Finished reading file.");
    } else {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }

    // Jeśli nie znaleziono linii z "RECENT_IP", dodaj ją na końcu
    if (!ip_replaced && line_count < MAX_LINES) {
        ESP_LOGI(TAG, "RECENT_IP not found, adding new entry.");
        asprintf(&lines[line_count], "RECENT_IP=%s\n", ip);  // Dodaj nową linię
        line_count++;
    }

    ESP_LOGI(TAG, "Opening file for writing...");
    f = fopen("/storage/secrets.conf", "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        // Zwolnij pamięć
        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        return;
    }

    ESP_LOGI(TAG, "Writing updated lines to file...");
    for (int i = 0; i < line_count; i++) {
        fprintf(f, "%s", lines[i]);  // Zapisz każdą linię do pliku
        free(lines[i]);  // Zwolnij pamięć po zapisaniu linii
    }
    fclose(f);
    ESP_LOGI(TAG, "File writing complete. Saved or updated IP: RECENT_IP=\"%s\"", ip);
}