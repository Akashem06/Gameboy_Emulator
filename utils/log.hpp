#pragma once

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NONE };

#ifndef LOG_LEVEL
#define LOG_LEVEL LogLevel::TRACE
#endif

class Logger {
 private:
  const char *COLOR_TRACE = "\033[1;30m";
  const char *COLOR_DEBUG = "\033[0;37m";
  const char *COLOR_INFO = "\033[0;34m";
  const char *COLOR_WARNING = "\033[0;33m";
  const char *COLOR_ERROR = "\033[0;31m";
  const char *COLOR_FATAL = "\033[1;31m";
  const char *COLOR_UNIMPLEMENTED = "\033[1;35m";
  const char *COLOR_RESET = "\033[0m";

  LogLevel current_level = LOG_LEVEL;
  std::mutex log_mutex;

  const char *short_file_name(const char *file);
  std::string format_string(const char *fmt, va_list args);
  const char *level_to_color(LogLevel level);
  std::string level_to_string(LogLevel level);

 public:
  static Logger &instance();
  void set_log_level(LogLevel level);
  void log(LogLevel level, const char *file, int line, const char *fmt, ...);
};

extern Logger &global_logger;

#define log_trace(...) global_logger.log(LogLevel::TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) global_logger.log(LogLevel::DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) global_logger.log(LogLevel::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) global_logger.log(LogLevel::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) global_logger.log(LogLevel::ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) global_logger.log(LogLevel::FATAL, __FILE__, __LINE__, __VA_ARGS__)
