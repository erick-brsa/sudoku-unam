cmake_minimum_required(VERSION 3.27)
project(sudoku C)

set(CMAKE_C_STANDARD 23)

set(SOURCES
    main.c
)

option(GENERAR_ARCHIVOS "Generar archivos durante la ejecución" OFF)

set(GENERATED_FILES_DIR "${CMAKE_BINARY_DIR}")

add_executable(sudoku ${SOURCES})

file(GLOB GENERATED_TEXT_FILES "./*.txt")
foreach(TEXT_FILE ${GENERATED_TEXT_FILES})
    configure_file(${TEXT_FILE} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()