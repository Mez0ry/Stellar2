#ifndef __STELLAR_LOGGER_HPP__
#define __STELLAR_LOGGER_HPP__

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include "SDL2/SDL_assert.h"
#include <spdlog/async_logger.h>


#define STELLAR_CORE_LOGGER_NAME "Stellar"
#define STELLAR_CLIENT_LOGGER_NAME "App"

#define STELLAR_CORE_LOGGER spdlog::get(STELLAR_CORE_LOGGER_NAME)
#define STELLAR_LOGGER spdlog::get(STELLAR_CLIENT_LOGGER_NAME)

class Logger {
public:
  static void OnCreate();
  static auto GetCoreLogger() { return m_CoreLogger; }
  static auto GetClientLogger() { return m_ClientLogger; }
  static bool IsCreated() {return m_Created;}
private:
  Logger() = default;
  ~Logger() { 
    if(STELLAR_CORE_LOGGER->should_backtrace()) 
      STELLAR_CORE_LOGGER->dump_backtrace();

    if(STELLAR_LOGGER->should_backtrace()){
      STELLAR_LOGGER->dump_backtrace();
    }

    spdlog::shutdown();
   }
  
private:
  static std::shared_ptr<spdlog::logger> m_CoreLogger;
  static std::shared_ptr<spdlog::logger> m_ClientLogger;
  static bool m_Created;
};


namespace details{

  template<typename TFunc, typename TTag>
  inline void LogOnce(TFunc func, [[maybe_unused]] TTag tag){
    static std::once_flag flag;
    std::call_once(flag,func);
  }
} //! details

/**
 * @brief Stellar core logger
 */
#define STELLAR_CORE_TRACE(...)    if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->trace(__VA_ARGS__) 
#define STELLAR_CORE_INFO(...)     if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->info(__VA_ARGS__)
#define STELLAR_CORE_WARN(...)     if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->warn(__VA_ARGS__)
#define STELLAR_CORE_WARN_ONCE(...) details::LogOnce([&](){ if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->warn(__VA_ARGS__);},[](){})  
#define STELLAR_CORE_ERROR(...)    if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->error(__VA_ARGS__)

#define STELLAR_CORE_DEBUG(...) if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->debug(__VA_ARGS__) 
#define STELLAR_CORE_CRITICAL(...) if(STELLAR_CORE_LOGGER != nullptr) STELLAR_CORE_LOGGER->critical(__VA_ARGS__)
#define STELLAR_CORE_CRITICAL_THROW(exception_type,error_text,...) if(STELLAR_CORE_LOGGER != nullptr) {STELLAR_CORE_LOGGER->critical(__VA_ARGS__); throw  exception_type(error_text); }

#define STELLAR_CORE_ASSERT(pred,msg,...) if(!(pred)){STELLAR_CORE_ERROR(msg,__VA_ARGS__); SDL_TriggerBreakpoint();}

/**
 * @brief Stellar client logger
 */
#define STELLAR_TRACE(...)    if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->trace(__VA_ARGS__) 
#define STELLAR_INFO(...)     if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->info(__VA_ARGS__)
#define STELLAR_WARN(...)     if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->warn(__VA_ARGS__)
#define STELLAR_WARN_ONCE(...) details::LogOnce([&](){ if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->warn(__VA_ARGS__);},[](){})  
#define STELLAR_ERROR(...)    if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->error(__VA_ARGS__)

#define STELLAR_DEBUG(...) if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->debug(__VA_ARGS__) 
#define STELLAR_CRITICAL(...) if(STELLAR_LOGGER != nullptr) STELLAR_LOGGER->critical(__VA_ARGS__)
#define STELLAR_CRITICAL_THROW(exception_type,error_text,...) if(STELLAR_LOGGER != nullptr) {STELLAR_LOGGER->critical(__VA_ARGS__); throw  exception_type(error_text); }

#define STELLAR_FILENAME std::filesystem::path(__FILE__).filename().string()
#define STELLAR_LINE __LINE__

#define STELLAR_ASSERT(pred,msg,...) if(!(pred)){STELLAR_ERROR(msg,__VA_ARGS__); SDL_TriggerBreakpoint();}


#endif //!__STELLAR_LOGGER_HPP__