#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include "SDL2/SDL_assert.h"
#include <spdlog/async_logger.h>

#define STELLAR_CORE_LOGGER_NAME "Stellar"
#define STELLAR_CORE_LOGGER spdlog::get(STELLAR_CORE_LOGGER_NAME)

class Logger {
public:
  static void OnCreate();
  static auto GetLogger() { return m_Logger; }
  static bool IsCreated() {return m_Created;}
  
private:
  Logger() = default;
  ~Logger() { if(STELLAR_CORE_LOGGER->should_backtrace()) STELLAR_CORE_LOGGER->dump_backtrace(); spdlog::shutdown();}
  
private:
  static std::shared_ptr<spdlog::logger> m_Logger;
  static bool m_Created;
};

#define STELLAR_CORE_TRACE(...)    if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->trace(__VA_ARGS__) 
#define STELLAR_CORE_INFO(...)     if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->info(__VA_ARGS__)
#define STELLAR_CORE_WARN(...)     if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->warn(__VA_ARGS__)
#define STELLAR_CORE_ERROR(...)    if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->error(__VA_ARGS__)

#define STELLAR_CORE_DEBUG(...) if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->debug(__VA_ARGS__) 
#define STELLAR_CORE_CRITICAL(...) if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->critical(__VA_ARGS__)
#define STELLAR_CORE_CRITICAL_THROW(exception_type,error_text,...) if(STELLAR_CORE_LOGGER != nullptr) {STELLAR_CORE_LOGGER->critical(__VA_ARGS__); throw  exception_type(error_text); }

#define STELLAR_FILENAME std::filesystem::path(__FILE__).filename().string()
#define STELLAR_LINE __LINE__

#define STELLAR_ASSERT(pred,msg,...) if(!(pred)){STELLAR_CORE_ERROR(msg,__VA_ARGS__); SDL_TriggerBreakpoint();}

#endif //!__LOGGER_HPP__