#include "logger.hpp"
#include <iostream>
#include <string>

//template<typename T>
void logger::info(std::string text){

	std::cout << text << std::endl;

}

template<typename T>
void logger::error(T text) {

	std::cout << "[X]Error: " << text << std::endl;

}

template<typename T>
void logger::warning(T text) {

	std::cout << "[!]Warning: " << text << std::endl;

}

template<typename T>
void logger::debug(T text) {

	std::cout << "[~]Debug: " << text << std::endl;

}