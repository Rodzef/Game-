cmake_minimum_required(VERSION 2.4)

project(GAME)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

set(SOURCE_EXE main.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB FiveWindow.cpp)			# Тоже самое, но для библиотеки

add_library(FiveWindow STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

target_link_libraries(main FiveWindow)

find_package(SFML)