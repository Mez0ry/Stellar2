#include "Logger.hpp"
#include "Core.hpp"

std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::m_ClientLogger;
bool Logger::m_Created = false;

void Logger::OnCreate(){
    std::vector<spdlog::sink_ptr> log_sinks;
	log_sinks.emplace_back(Core::CreateRef<spdlog::sinks::stdout_color_sink_mt>());
	log_sinks.emplace_back(Core::CreateRef<spdlog::sinks::basic_file_sink_mt>(std::string(STELLAR_CORE_LOGGER_NAME) + ".log", true));

    log_sinks[0]->set_pattern("[%Y-%m-%d %H:%M:%S] %^[%T] %n: %v%$");
    log_sinks[1]->set_pattern("[%Y-%m-%d %H:%M:%S] [%T] [%l] %n: %v");

    m_CoreLogger = Core::CreateRef<spdlog::logger>(STELLAR_CORE_LOGGER_NAME,begin(log_sinks), end(log_sinks));
    spdlog::register_logger(m_CoreLogger);
    m_CoreLogger->set_level(spdlog::level::trace);
    m_CoreLogger->flush_on(spdlog::level::trace);
    
    m_ClientLogger = Core::CreateRef<spdlog::logger>("App",begin(log_sinks), end(log_sinks));
    spdlog::register_logger(m_ClientLogger);
    m_ClientLogger->set_level(spdlog::level::trace);
    m_ClientLogger->flush_on(spdlog::level::trace);

    m_Created = true;
}