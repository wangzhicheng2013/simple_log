#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "time_utility.hpp"
class simple_log {
public:
    simple_log() = default;
    virtual ~simple_log() = default;
public:
    inline void set_log_file_format(const char *str) {
        log_file_format = str;
    }
    inline void set_log_file_path(const char *str) {
        log_file_path = str;
    }
    #define log_debug(...) simple_log::log("DEBUG", __FILE__, __func__, __LINE__, __VA_ARGS__)
    #define log_warn(...)  simple_log::log("WARN", __FILE__, __func__, __LINE__, __VA_ARGS__)
    #define log_info(...)  simple_log::log("INFO", __FILE__, __func__, __LINE__, __VA_ARGS__)
    #define log_error(...) simple_log::log("ERROR", __FILE__, __func__, __LINE__, __VA_ARGS__)
    #define log_fatal(...) simple_log::log("FATAL", __FILE__, __func__, __LINE__, __VA_ARGS__)
public:
    void log(const char *level,
                   const char *file, 
                   const char *function, 
                   uint32_t line,
                   const char *format, ...) {
        if (!format[0]) {
            return;
        }
        char buf[1024] = "";
        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);
        _log(level, file, function, line, buf);
    }
    void _log(const char *level, 
             const char *file, 
             const char *function, 
             uint32_t line, 
             const char *str) {
        std::string log_file_name = log_file_path;
        log_file_name += G_TIME_UTILITY.get_cur_time(log_file_format);
        std::ofstream ofs(log_file_name.c_str(), std::ios::app);
        if (!ofs || !ofs.is_open()) {
            return;
        }
        ofs << G_TIME_UTILITY.get_cur_time() << "|" 
            << std::this_thread::get_id() << "|" 
            << level << "|" 
            << file << "|" 
            << function << "|"
            << line << "|" 
            << str << std::endl;
        ofs.close();
    }
private:
    const char *log_file_format = "ips%y%m%d.log";
    const char *log_file_path = "./";
};