#pragma once
class Utils {
public:
  static wstring GetLastErrorAsString(DWORD dwError);
  static wstring TimeText();
  static wstring DateText();
};

