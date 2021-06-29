#include "logger.hpp"
#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

// work in progres, adding some basic stuff at the moment
// https://github.com/gabime/spdlog



void logger::trace(const std::string& text) {

	spdlog::trace(text);

}

void logger::debug(const std::string& text) {

	spdlog::debug(text);

}

void logger::info(const std::string& text){

	spdlog::info(text);

}

void logger::warning(const std::string& text) {

	spdlog::warn(text);

}

void logger::error(const std::string& text) {

	spdlog::error(text);

}

void logger::critical(const std::string& text) {

	spdlog::critical(text);

}