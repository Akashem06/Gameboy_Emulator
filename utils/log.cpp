#include "log.hpp"

const char *Logger::short_file_name(const char *file) {
  const char *last_slash = strrchr(file, '/');
  const char *last_backslash = strrchr(file, '\\');
  const char *start = file;

  if (last_slash) {
    start = last_slash + 1;
  }
  if (last_backslash) {
    start = std::max(start, last_backslash + 1);
  }
  return start;
}

std::string Logger::format_string(const char *fmt, va_list args) {
  va_list args_copy;
  va_copy(args_copy, args);
  int len = vsnprintf(nullptr, 0, fmt, args_copy);
  va_end(args_copy);

  if (len < 0) {
    return "[FORMAT ERROR]";
  }

  std::vector<char> buffer(len + 1);
  vsnprintf(buffer.data(), buffer.size(), fmt, args);

  return std::string(buffer.data());
}

const char *Logger::level_to_color(LogLevel level) {
  switch (level) {
    case LogLevel::TRACE:
      return COLOR_TRACE;
    case LogLevel::DEBUG:
      return COLOR_DEBUG;
    case LogLevel::INFO:
      return COLOR_INFO;
    case LogLevel::WARN:
      return COLOR_WARNING;
    case LogLevel::ERROR:
      return COLOR_ERROR;
    case LogLevel::FATAL:
      return COLOR_FATAL;
    default:
      return COLOR_RESET;
  }
}

std::string Logger::level_to_string(LogLevel level) {
  switch (level) {
    case LogLevel::TRACE:
      return "TRACE";
    case LogLevel::DEBUG:
      return "DEBUG";
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::WARN:
      return "WARN";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::FATAL:
      return "FATAL";
    default:
      return "UNKNOWN";
  }
}

Logger &Logger::instance() {
  static Logger inst;
  return inst;
}

void Logger::set_log_level(LogLevel level) {
  current_level = level;
}

void Logger::log(LogLevel level, const char *file, int line, const char *fmt, ...) {
  if (level < current_level) {
    return;
  }

  va_list args;
  va_start(args, fmt);
  std::string msg = format_string(fmt, args);
  va_end(args);

  FILE *output_stream = (level >= LogLevel::ERROR) ? stderr : stdout;

  std::lock_guard<std::mutex> lock(log_mutex);

  fprintf(output_stream, "%s[%s] [%s:%d] %s%s", level_to_color(level), level_to_string(level).c_str(), short_file_name(file), line, msg.c_str(),
          COLOR_RESET);
}

Logger &global_logger = Logger::instance();
