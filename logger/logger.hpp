#pragma once

#include <string>
#include <queue>

/* Very simple logger class, we need something like this if
 * we want to output the information to anything else than
 * the standard streams.
 */

class logger {
private:    
    std::queue<std::string> error_queue;
    std::queue<std::string> warning_queue;
    std::queue<std::string> info_queue;
    
    logger() {}
public:
    logger(const logger&) = delete;
    void operator=(logger const&) = delete;
    static logger& instance();
    
    void error(std::string message);
    void warning(std::string message);
    void info(std::string message);

    bool has_error();
    bool has_warning();
    bool has_info();

    std::string get_error();
    std::string get_warning();
    std::string get_info();
};
