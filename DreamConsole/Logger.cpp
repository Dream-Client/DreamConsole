#include "stdafx.h"

#include "Logger.h"

#define LOGS_DIRECTORY L".\\DreamVR\\Logs"

Logger::Logger() {
  std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);

  namespace fs = std::filesystem;
  if(!fs::exists(LOGS_DIRECTORY)) {
    fs::create_directory(LOGS_DIRECTORY);
  }

  wstringstream ss;
  ss << LOGS_DIRECTORY << L"\\" << Utils::DateText() << L".log";
  logFileStream.open(ss.str().c_str(), ios::out | ios::app);
  logFileStream.imbue(loc);
}

Logger::~Logger() {
  logFileStream.close();
}

std::wstring Logger::CleanSurrogates(std::wstring str) {
  if(str.length() == 0)
    return str;

  //U+D800..U+DBFF
  int i = 0;
  while(i < str.length()) {
    if(str[i] >= 0xD800 && str[i] <= 0xDBFF) {
      // Replace with spaces
      str[i] = 0x0020;
      str[i + 1] = 0x0020;
      //str.erase(i, 2);
      //continue;
    }
    i++;
  }
  return str;
}