#pragma once
class DreamConsole {
public:
  static HANDLE _pipe;
  static HANDLE _console;

  static void Run();
private:
  static Logger _logger;
  static bool _shouldLoop;

  static void OpenPipe();
  static void Loop();
  static void HandleWriteCommand();
  static void HandleColorCommand();

  template<typename T>
  static bool Read(void* ptr, LPDWORD bytesRead) {
    return ReadFile(_pipe, ptr, sizeof(T), bytesRead, NULL);
  }
};