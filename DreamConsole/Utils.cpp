#include "stdafx.h"
#include "Utils.h"

wstring Utils::GetLastErrorAsString(DWORD dwError) {
  LPWSTR messageBuffer = nullptr;

  size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               nullptr, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, nullptr);

  wstring message(messageBuffer, size);

  //Free the Win32's string's buffer.
  LocalFree(messageBuffer);

  return message;
}

wstring Utils::TimeText() {
  time_t rawtime;
  struct tm timeinfo;

  time(&rawtime);
  localtime_s(&timeinfo, &rawtime);

  wchar_t buffer[80];

  wcsftime(buffer, sizeof(buffer), L"%H:%M:%S | ", &timeinfo);

  return wstring(buffer);
}

wstring Utils::DateText() {
  time_t rawtime;
  struct tm timeinfo;

  time(&rawtime);
  localtime_s(&timeinfo, &rawtime);

  wchar_t buffer[80];

  wcsftime(buffer, sizeof(buffer), L"%Y-%m-%d", &timeinfo);

  return wstring(buffer);
}
