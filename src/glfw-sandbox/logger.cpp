#include "logger.hpp"
#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

// work in progres, adding some basic stuff at the moment
// https://github.com/gabime/spdlog



void logger::trace(std::string text) {

	spdlog::trace(text);

}

void logger::debug(std::string text) {

	spdlog::debug(text);

}

void logger::info(std::string text){

	spdlog::info(text);

}

void logger::warning(std::string text) {

	spdlog::warn(text);

}

void logger::error(std::string text) {

	spdlog::error(text);

}

void logger::critical(std::string text) {

	spdlog::critical(text);

}