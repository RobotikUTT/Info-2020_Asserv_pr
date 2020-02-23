#!/bin/bash

USER_TARGET=""
ARDUINO_PORT="" 

function generate_cmake() {
	rm -rf build
	mkdir -p build
	cd build
	cmake ../ -DTARGET_ARDUINO:STRING=$USER_TARGET -DARDUINO_PORT:STRING=$ARDUINO_PORT
}

function compile_program() {
	if [ ! "${PWD##*/}" = "build" ]; then
		printf "Not in the right place for build..."
	fi
	make
}

function upload_program() {
	if [ "$ARDUINO_PORT" = "" ]; then
        printf "Compilation successful, no arduino detected. Not uploading to board."
        exit 0
    fi
	make upload
}

function ask_user() {
	printf "What's the target (nano, uno, leonardo, mega) ?"
	read answer

	if [ "$answer" = "uno" ] || [ "$answer" = "leonardo" ]; then
		USER_TARGET="$answer"
	elif [ "$answer" = "nano" ]; then
		USER_TARGET="nano328"
	elif [ "$answer" = "mega" ]; then
		USER_TARGET="mega2560"
	fi

	if [ "$USER_TARGET" = "" ]; then
		printf "Incorrect parameters, please relaunch the script with correct parameters...\n"
		exit 1
	fi
}

function find_arduino_port() {
    if [ "$USER_TARGET" = "nano328" ]; then
        ARDUINO_PORT="/dev/ttyUSB"
    else
        ARDUINO_PORT="/dev/ttyACM"
    fi

    ARDUINO_PORT=$(find $ARDUINO_PORT*)
}

# "Main"
ask_user
find_arduino_port
generate_cmake
compile_program
upload_program