#pragma once
class Logger {
protected:
  wofstream logFileStream;
public:
  Logger();
  ~Logger();

  friend Logger &operator << (Logger &logger, wchar_t* text) {
    wcout << Utils::TimeText() << logger.CleanSurrogates(text) << endl;
    logger.logFileStream << Utils::TimeText() << text << endl;
    return logger;
  }

  friend Logger &operator << (Logger &logger, wstring text) {
    wcout << Utils::TimeText() << logger.CleanSurrogates(text) << endl;
    logger.logFileStream << Utils::TimeText() << text << endl;
    return logger;
  }

  friend Logger &operator << (Logger &logger, COLORS color) {
    // CHANGE COLOR
    //SetConsoleTextAttribute()
    return logger;
  }

private:
  std::wstring CleanSurrogates(std::wstring str);

};