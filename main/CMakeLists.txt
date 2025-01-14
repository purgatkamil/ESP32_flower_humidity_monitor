# Znajdź wszystkie pliki źródłowe w katalogu main
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/main/*.*)

# Zarejestruj komponent z plikami źródłowymi oraz dołączanymi plikami
idf_component_register(SRCS ${app_sources}
                    INCLUDE_DIRS ".")
                    
# Tworzenie obrazu SPIFFS z plików w katalogu spiffs_image
set(WEB_SRC_DIR2 "${CMAKE_CURRENT_SOURCE_DIR}/spiffs_image")
spiffs_create_partition_image(storage ${WEB_SRC_DIR2} FLASH_IN_PROJECT)
