cmake_minimum_required(VERSION 3.10)

# Версия проекта — берём из CI (если запущено через GitHub Actions),
# а если локально — подставляем 0.0.0 
if(NOT DEFINED PROJECT_VERSION_MAJOR)
  set(PROJECT_VERSION_MAJOR 0)
endif()
if(NOT DEFINED PROJECT_VERSION_MINOR)
  set(PROJECT_VERSION_MINOR 0)
endif()
if(NOT DEFINED PATCH_VERSION)
  set(PATCH_VERSION 0)
endif()

set(PROJECT_VERSION_PATCH ${PATCH_VERSION})

# Объявляем проект с динамической версией: major.minor.patch
project(lab2 VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

# Настройки упаковки (для CPack)
# Имя пакета и формат имени архива: Lab2-1.2.3-Linux.zip и т.д.
set(CPACK_PACKAGE_NAME "Lab2")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/package")  # кладём всё в build/package/

# Собираем functions как статическую библиотеку — чисто для структуры,
# чтобы не тащить всё в один main.cpp
add_library(functions STATIC functions.cpp)
# Даём main.cpp доступ к functions.h — PUBLIC, потому что заголовки нужны при компиляции lab2
target_include_directories(functions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Основной исполняемый файл
add_executable(lab2 main.cpp)
# Линкуем с нашей статической библиотекой
target_link_libraries(lab2 PRIVATE functions)

# Важно! Передаём путь к ip_filter.tsv в код как строковый литерал,
# чтобы программа всегда знала, где искать файл — даже если запущена из другой папки.
# Экранируем кавычки, иначе C++ решит, что это не строка, а мусор.
set(IP_FILTER_PATH "${CMAKE_SOURCE_DIR}/ip_filter.tsv")
target_compile_definitions(lab2 PRIVATE "IP_FILTER_PATH=\"${CMAKE_SOURCE_DIR}/ip_filter.tsv\"")

# Тесты на отдельной поддиректории — gtest лежит в ./gtest_tests/
add_subdirectory(gtest_tests)

# Повторно задаём CPack-переменные
set(CPACK_PACKAGE_NAME "Lab2")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/package")

# Выбираем формат пакета в зависимости от ОС:
# Windows - ZIP 
# Linux - .deb 
if(WIN32)
  set(CPACK_GENERATOR "ZIP")
elseif(UNIX)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "apranovich <apranovich@tpu.ru>")
endif()

# Куда установится исполняемый файл при `cmake --install`
install(TARGETS lab2 DESTINATION bin)

include(CPack)