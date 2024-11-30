cmake_minimum_required(VERSION 3.30)

project(Calculator)

file(GLOB SOURCES "src/*.c")

add_executable(Calculator ${SOURCES})
