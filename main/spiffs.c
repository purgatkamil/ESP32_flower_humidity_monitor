#include "spiffs.h"

#define TAG "SPIFFS"

esp_err_t spiffs_init(void)
{
    esp_vfs_spiffs_conf_t credentials_conf =
    {
        .base_path = "/storage",
        .partition_label = "storage",
        .max_files = 5,
        .format_if_mount_failed = false
    };

    esp_err_t ret = esp_vfs_spiffs_register(&credentials_conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            printf("STORAGE: Failed to mount or format filesystem\n");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            printf("STORAGE: Failed to find SPIFFS partition\n");
        }
        else
        {
            printf("STORAGE: Failed to initialize SPIFFS (%s)\n", esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    size_t total = 0, used = 0;

    ret = esp_spiffs_info("storage", &total, &used);
    if (ret != ESP_OK)
    {
        printf("STORAGE: Failed to get SPIFFS partition information (%s)\n", esp_err_to_name(ret));
    }
    else
    {
        printf("STORAGE: Partition size: total: %d, used: %d\n", total, used);
    }
    return ESP_OK;
}

void spiffs_list_files(void)
{
    struct dirent *entry;
    DIR *dp = opendir("/storage");

    if (dp == NULL)
    {
        printf("Failed to open directory\n");
        return;
    }

    while ((entry = readdir(dp)))
    {
        printf("Found file: %s\n", entry->d_name);
    }

    closedir(dp);
}