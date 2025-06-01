#include <iostream>
#include <stringstream>

#include "common.hpp"

enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NONE };

#ifndef LOG_LEVEL
#define LOG_LEVEL LogLevel::DEBUG
#endif

class Logger {
 private:
  LogLevel current_level = LOG_LEVEL;

  std::string levelToString(LogLevel level) {
    switch (level) {
      case LogLevel::TRACE:
        return "-T";
      case LogLevel::DEBUG:
        return "-D";
      case LogLevel::INFO:
        return "-I";
      case LogLevel::WARN:
        return "-W";
      case LogLevel::ERROR:
        return "-E";
      case LogLevel::FATAL:
        return "-F";
      default:
        return "UNKNOWN";
    }
  }

  std::string shortFileName(const std::string &path) {
    return path.substr(path.find_last_of("/\\") + 1);
  }

 public:
  static Logger &instance() {
    static Logger inst;
    return inst;
  }

  void setLogLevel(LogLevel level) {
    current_level = level;
  }

  void log(LogLevel level, const std::string &message, const char *file, int line) {
    if (level < current_level) return;

    std::ostringstream log_stream;

    log_stream << "[" << levelToString(level) << "] "
               << "[" << shortFileName(file) << ":" << line << "] " << message;

    std::cout << log_stream.str() << std::endl;
  }
}