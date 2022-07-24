#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "logger_manager.hpp"

std::unique_ptr<LoggerManager>LoggerManager::instance_;
std::once_flag LoggerManager::gOnceFlag;

LoggerManager &LoggerManager::GetInstance()
{
//#ifdef LINUX
//    if(instance_==NULL){
//		instance_=std::unique_ptr<LoggerManager>(new LoggerManager);
//	}
//#else
    std::call_once(gOnceFlag,
                   [] {
                       instance_.reset(new LoggerManager);
                   });
//#endif
    return *instance_.get();
}

LoggerManager::LoggerManager() {

    p_Logger= spdlog::rotating_logger_mt("engine","logs/engine_log.txt", max_size,max_files);
    spdlog::flush_on(spdlog::level::n_levels);
}

std::shared_ptr<spdlog::logger> LoggerManager::GetLogger() {
    return p_Logger;
}