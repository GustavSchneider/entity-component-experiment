#include "logger.hpp"

logger& logger::instance() {
    static logger instance;
    return instance;
}

void logger::error(std::string message) {
    error_queue.push(message);
}

void logger::warning(std::string message) {
    warning_queue.push(message);
}

void logger::info(std::string message) {
    info_queue.push(message);
}

bool logger::has_error() {
    return !error_queue.empty();
}

bool logger::has_warning() {
    return !warning_queue.empty();
}

bool logger::has_info() {
    return !info_queue.empty();
}

std::string logger::get_error() {
    std::string message = error_queue.front();
    error_queue.pop();
    return message;
}

std::string logger::get_warning() {
    std::string message = warning_queue.front();
    warning_queue.pop();
    return message;
}

std::string logger::get_info() {
    std::string message = info_queue.front();
    info_queue.pop();
    return message;
}
    
