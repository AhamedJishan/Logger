#pragma once

#include <stdio.h>

enum LogPriority
{
	Trace,
	Debug,
	Info,
	Warning,
	Error,
	Critical
};

class Logger
{
private:
	LogPriority logPriority = LogPriority::Info;


public:
	static void SetPriority(LogPriority newPriority)
	{
		get_instance().logPriority = newPriority;
	}

	template<typename... Args>
	static void Trace(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Trace, "[Trace]\t", msg, args...);
	}
	template<typename... Args>
	static void Debug(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Debug, "[Debug]\t", msg, args...);
	}
	template<typename... Args>
	static void Info(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Info, "[Info]\t", msg, args...);
	}
	template<typename... Args>
	static void Warning(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Warning, "[Warn]\t", msg, args...);
	}
	template<typename... Args>
	static void Error(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Error, "[Error]\t", msg, args...);
	}
	template<typename... Args>
	static void Critical(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Critical, "[Crit]\t", msg, args...);
	}

private:
	Logger() = default;
	~Logger()
	{

	}

	// Copy and Assignment constructors are deleted as only one instance is required
	Logger(const Logger&) = delete;
	Logger operator=(const Logger&) = delete;

	static Logger& get_instance()
	{
		static Logger instance;
		return instance;
	}

	template<typename... Args>
	void log(LogPriority priority, const char* logPriorityString, const char* msg, Args... args)
	{
		if (priority >= logPriority)
		{
			printf(logPriorityString);
			printf(msg, args...);
			printf("\n");
		}
	}
};