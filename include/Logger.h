#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <cstdio>
#include <ctime>
#include <thread>
#include <mutex>


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
	std::mutex threadLock;

	LogPriority logPriority = LogPriority::Info;
	std::FILE* file = 0;

	char timestampBuffer[80];
	const char* timestampFormat = "%T %d-%m-%Y  ";

public:
	static void SetPriority(LogPriority newPriority)
	{
		get_instance().logPriority = newPriority;
	}
	static LogPriority GetPriority()
	{
		return get_instance().logPriority;
	}

	static void EnableFileOutput()
	{
		get_instance().enable_file_output("log/logs.txt");
	}
	static void EnableFileOutput(const char* filepath)
	{
		get_instance().enable_file_output(filepath);
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
		get_instance().log(LogPriority::Info, "[Info ]\t", msg, args...);
	}
	template<typename... Args>
	static void Warning(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Warning, "[Warn ]\t", msg, args...);
	}
	template<typename... Args>
	static void Error(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Error, "[Error]\t", msg, args...);
	}
	template<typename... Args>
	static void Critical(const char* msg, Args... args)
	{
		get_instance().log(LogPriority::Critical, "[Crit ]\t", msg, args...);
	}

private:
	Logger() = default;
	~Logger()
	{
		if (file)
		{
			close_file();
		}
	}

	// Copy and Assignment constructors are deleted as only one instance is required
	Logger(const Logger&) = delete;
	Logger operator=(const Logger&) = delete;

	static Logger& get_instance()
	{
		static Logger instance;
		return instance;
	}

	void enable_file_output(const char* filepath)
	{
		if (file)
		{
			close_file();
		}

		file = std::fopen(filepath, "w");

		if (!file)
		{
			Error("Failed to open the log's file");
		}
	}
	void close_file()
	{
		if (file)
		{
			std::fclose(file);
			file = 0;
		}
	}

	template<typename... Args>
	void log(LogPriority priority, const char* logPriorityString, const char* msg, Args... args)
	{
		// Thread Safety
		std::lock_guard<std::mutex> lock(threadLock);

		if (priority >= logPriority)
		{
			printf(get_timestamp());
			printf(logPriorityString);
			printf(msg, args...);
			printf("\n");

			if (file)
			{
				fprintf(file, get_timestamp());
				fprintf(file, logPriorityString);
				fprintf(file, msg, args...);
				fprintf(file, "\n");
			}
		}
	}

	const char* get_timestamp()
	{
		std::time_t current_time = std::time(0);
		std::tm* timestamp = localtime(&current_time);

		std::strftime(timestampBuffer, sizeof(timestampBuffer), timestampFormat, timestamp);
		return timestampBuffer;
	}
};