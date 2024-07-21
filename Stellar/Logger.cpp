#include "Logger.hpp"

std::shared_ptr<spdlog::logger> Logger::m_Logger;
bool Logger::m_Created = false;

void Logger::OnCreate(){
    std::vector<spdlog::sink_ptr> log_sinks;
	log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(STELLAR_CORE_LOGGER_NAME) + ".log", true));

    log_sinks[0]->set_pattern("[%Y-%m-%d %H:%M:%S] %^[%T] %n: %v%$");
    log_sinks[1]->set_pattern("[%Y-%m-%d %H:%M:%S] [%T] [%l] %n: %v");

    m_Logger = std::make_shared<spdlog::logger>(STELLAR_CORE_LOGGER_NAME,begin(log_sinks), end(log_sinks));
    m_Logger->set_level(spdlog::level::trace);
    m_Logger->flush_on(spdlog::level::trace);
    spdlog::register_logger(m_Logger);
    
    m_Created = true;
}