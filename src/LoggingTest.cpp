#include "Logger.h"

int main()
{
	Logger::SetPriority(Debug);

	Logger::Trace("Logging int: %d", 1);
	Logger::Debug("Logging int: %d", 2);
	Logger::Info("Logging int: %d", 3);
	Logger::Warning("Logging int: %d", 4);
	Logger::Error("Logging int: %d", 5);
	Logger::Critical("Logging int: %d", 6);

	return 0;
}