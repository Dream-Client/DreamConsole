// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"

#include "DreamConsole.h"

int main() {
  _setmode(_fileno(stdout), _O_U16TEXT);

  wcout << L"==============================================================" << endl;
  wcout << L"= Dream Console v2.0.0" << endl;
  wcout << L"= Unicode test: \x043a\x043e\x0448\x043a\x0430 \x65e5\x672c\x56fd" << endl;
  wcout << L"==============================================================" << endl;

	DreamConsole::Run();
}
