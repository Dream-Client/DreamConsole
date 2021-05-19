#include "stdafx.h"
#include "DreamConsole.h"

#include "CommandLine.h"

HANDLE DreamConsole::_pipe = INVALID_HANDLE_VALUE;

void DreamConsole::Run() {

  CommandLine::Init();
  


  system("pause");
}
