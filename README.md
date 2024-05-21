# Logger

This is a simple, thread-safe, single-header logger written in C++. It supports various logging levels, console output, and file output with customizable timestamp formats.

## Features

- **Log Levels**: Trace, Debug, Info, Warning, Error, Critical
- **Thread Safety**: Ensures thread-safe logging using `std::mutex`.
- **File Output**: Optional logging to a file.
- **Timestamp Customization**: Allows custom timestamp formats.

## Usage

### Integration

To use this logger in your project, simply include the `Logger.h` file from the include directory.

```cpp
#include "Logger.h"
```

### Setting Log Priority

Set the minimum log priority level. Messages below this priority will not be logged.

```cpp
Logger::SetPriority(LogPriority::Debug);
```

### Enabling File Output

Enable logging to a file. If no file path is specified, it defaults to logs.txt.

```cpp
Logger::EnableFileOutput();
Logger::EnableFileOutput("my_logs.txt");
```

### Customizing Timestamp Format

Set a custom timestamp format using strftime format specifiers.

```cpp
Logger::SetTimeStampFormat("%H:%M:%S %d-%m-%Y");
```

### Logging Messages

Log messages at various levels. The logger supports printf-style formatting.

```cpp
Logger::Trace("This is a trace message: %d", 1);
Logger::Debug("This is a debug message: %s", "debug");
Logger::Info("This is an info message");
Logger::Warning("This is a warning message");
Logger::Error("This is an error message");
Logger::Critical("This is a critical message");
```

### Sample Example

Here is a complete example of how to use the logger:

```cpp
#include "Logger.h"

int main() {
    // Set the logging priority
    Logger::SetPriority(LogPriority::Debug);

    // Enable file output
    Logger::EnableFileOutput("app_log.txt");

    // Set custom timestamp format
    Logger::SetTimeStampFormat("%Y-%m-%d %H:%M:%S");

    // Log messages of different priorities
    Logger::Trace("Trace message");
    Logger::Debug("Debug message");
    Logger::Info("Info message");
    Logger::Warning("Warning message");
    Logger::Error("Error message");
    Logger::Critical("Critical message");

    return 0;
}
```

## Thread Safety

The logger uses std::mutex to ensure thread safety, allowing concurrent logging from multiple threads without data corruption.

## Thank You

Thank you for using this logger! If you find it useful, please give it a star on GitHub. Your support is greatly appreciated.
