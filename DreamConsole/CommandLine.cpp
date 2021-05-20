#include "stdafx.h"

#include "CommandLine.h"

wstring CommandLine::pipeName = L"";

void CommandLine::Init() {
  LPWSTR *szArglist;
  int nArgs;
  int i;

  szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
  if(nullptr == szArglist) {
    wcout << L"CommandLineToArgvW failed." << endl;
    return;
  }
  
  // First argument is path
  for(i = 1; i < nArgs; i++) {

    if(wcscmp(L"--pipe", szArglist[i]) == 0) {
      if(i + 1 >= nArgs) {
        wcout << L"Pipe file name missing." << endl;
        goto END;
      }

      i++;
      pipeName = szArglist[i];
      continue;
    }
  }
  // Free memory allocated for CommandLineToArgvW arguments.
END:
  LocalFree(szArglist);
}
