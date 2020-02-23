cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/libs/cmake/ArduinoToolchain.cmake)
set(ARDUINO_CXX_FLAGS "${ARDUINO_C_FLAGS} -std=c++11")

project(arduino C CXX)

set(ARDUINO_DEFAULT_BOARD mega2560)

SET(TARGET_ARDUINO "mega2560" CACHE STRING "User defined arduino target")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

file(GLOB_RECURSE SRC_FILES	*.cpp src/*.cpp libs/Encoder/*.cpp libs/SimpleTimer/*.cpp)
include_directories(include libs/Encoder libs/SimpleTimer)

generate_arduino_firmware(arduino_${TARGET_ARDUINO}_asserv
    SRCS ${SRC_FILES} ${EXTRA_SRC_FILES}
#    HDRS ${HDR_FILES}
#	LIBS HardwareSerial
    PORT ${ARDUINO_PORT}
    BOARD ${TARGET_ARDUINO}
)

