# Znajdź wszystkie pliki źródłowe w katalogu main
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/main/*.*)

# Zarejestruj komponent z plikami źródłowymi oraz dołączanymi plikami
idf_component_register(SRCS ${app_sources}
                    INCLUDE_DIRS ".")
