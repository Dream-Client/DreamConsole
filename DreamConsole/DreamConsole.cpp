#include "stdafx.h"
#include "DreamConsole.h"

#include "CommandLine.h"

#include "Logger.h"

#define TEXT_BUFFER_SIZE 1024

HANDLE DreamConsole::_pipe = INVALID_HANDLE_VALUE;
HANDLE DreamConsole::_console = INVALID_HANDLE_VALUE;

Logger DreamConsole::_logger;
bool DreamConsole::_shouldLoop = true;

void DreamConsole::Run() {

  CommandLine::Init();

  _console = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTitleW(L"Dream Console v2.0.0");

  OpenPipe();
  Loop();

  CloseHandle(_pipe);

  _logger << L"VRChat was closed or crashed";
  _logger << L"";
  wcout << L"Press any key to close console..." << endl;
  getchar();
}

void DreamConsole::OpenPipe() {
  wstringstream ss;

  ss << L"\\\\.\\pipe\\" << CommandLine::pipeName;

  while(true) {
    _pipe = CreateFileW(
      ss.str().c_str(), // pipe name
      GENERIC_READ,     // read access
      0,                // no sharing
      NULL,             // no security attributes
      OPEN_EXISTING,    // opens existing pipe
      0,                // default attributes
      NULL);            // no template file

    // Pipe opened
    if(_pipe != INVALID_HANDLE_VALUE)
      break;

    // Exit if an error other than ERROR_PIPE_BUSY occurs.
    DWORD dwError = GetLastError();
    if(dwError != ERROR_PIPE_BUSY) {
      wcout << L"Could not open pipe. Error:" << endl;
      wcout << Utils::GetLastErrorAsString(dwError) << endl;
      return;
    }

    // All pipe instances are busy, wait for up to 20 seconds.
    if(!WaitNamedPipeW(ss.str().c_str(), 20000)) {
      wcout << L"WaitNamedPipeW timed out." << endl;
      return;
    }

    Sleep(500);
  }
}

void DreamConsole::Loop() {
  DWORD bytesRead;
  BYTE command;

  while(_shouldLoop) {
    if(!Read<BYTE>(&command, &bytesRead) || bytesRead != sizeof(BYTE)) {
      _shouldLoop = false;
      break;
    }

    switch((COMMANDS)command) {
    case COMMANDS::WRITE:
    {
      HandleWriteCommand();
      continue;
    }
    case COMMANDS::COLOR:
    {
      HandleColorCommand();
      continue;
    }
    }
  }
}

void DreamConsole::HandleWriteCommand() {
  DWORD bytesRead;
  DWORD bytesToRead = 0;

  if(!Read<DWORD>(&bytesToRead, &bytesRead) || bytesRead != sizeof(DWORD)) {
    _shouldLoop = false;
    return;
  }

  wstring text = L"";
  wchar_t* buffer = new wchar_t[TEXT_BUFFER_SIZE];
  while(bytesToRead > 0) {
    DWORD maxRead = TEXT_BUFFER_SIZE * sizeof(wchar_t) < bytesToRead ? TEXT_BUFFER_SIZE * sizeof(wchar_t) : bytesToRead;
    //memset(buffer, 0, TEXT_BUFFER_SIZE * sizeof(wchar_t));
    if(!ReadFile(_pipe, buffer, maxRead, &bytesRead, nullptr)) {
      _shouldLoop = false;
      return;
    }
    text += wstring(buffer, bytesRead / 2);
    bytesToRead -= bytesRead;
  }

  _logger << text;
}

void DreamConsole::HandleColorCommand() {
  DWORD bytesRead;
  BYTE color;

  if(!Read<BYTE>(&color, &bytesRead) || bytesRead != sizeof(BYTE)) {
    _shouldLoop = false;
    return;
  }

  SetConsoleTextAttribute(_console, (WORD)color);
}

