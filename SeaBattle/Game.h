#pragma once
#include <iostream>
#include "ConsoleLib.h"
#include "ForStructures.h"

void InitSymPol(SymChars &SymForPole);
void InitYou(Pole &You, GlobPar &ParGlob);
void InitPc(Pole &Pc, GlobPar &ParGlob);
void InitForInstShips(Pole &Inst);
void InitSymForCell(SymChars &SymForCell);
bool ItsButton(Coor &Pos, COORD & mousePos, int &ClickButton, bool &SwPrintMainMenu, Turn &T);
bool ItsAClick(clock_t &t1, clock_t &t2, double t = 0.35);
bool ItSClickOk(Cell &Ok, COORD &mP);
bool ItSClickXX(Cell &XX, COORD &mP);
bool ItsADeckTrue(COORD &mousePos, D &S);
bool ItsCountBoatYou(CountBoat &Col);
bool PlayYou(COORD mousePos, Coor Pos, Mas &Arr, Symbol &Sym, CountBoat &Col);
bool PlayPc(Coor Pos, Mas &Arr, Shot &G, CountBoat &Col, DWORD &dwOldMode, DWORD &dwMode);
bool ManualStateShips(Coor &Pos, GlobPar &ParGlob, Symbol &Sym, Mas &Arr, D &S, Turn &T, MyMousePos &Mouse, CountBoat &Col);
bool AutoStateShipsPc(Mas &Arr, CountBoat &Col);
bool AutoStateShipsUser(Mas &Arr, CountBoat &Col);
bool AutoStateShips(Coor &Pos, GlobPar &ParGlob, Symbol &Sym, Mas &Arr, CountBoat &Col, Turn &T, Shot &G);
int GiveBoat(COORD &mousePos, D &S);
void CleanFon(int yUp, int yDown, int len, int x = 0);
void CleanFonStruct(Ships &AllVert, Ships &AllHor);
void PrintFon(int x, GlobPar &ParGlob);
void PrintPole(Pole All, SymChars SymForPole, GlobPar &ParGlob);
void PrintArrYou(Mas &Arr, Pole All, const int Y = 10, const int X = 20);
void PrintArrPcDebug(Mas &Arr, Pole All, const int Y = 10, const int X = 20);
void PrintArrPcRelease(Mas &Arr, Pole All, const int Y = 10, const int X = 20);
void PrintShipsStat(D &S, Mas &Arr);
void PrintForInstShips(Coor &Pos, SymChars &SymForPole); // Это поле для установки кораблей
void PrintMainMenu(Cell &M, SymChars &S);
void PrintAllMenu(Cell &M, SymChars &S);
void PrintInstallShips(Cell &M, SymChars &S);
void PrintExit(Cell &M, SymChars &S);
void PrintCreateUser(Cell &M, SymChars &S);
void PrintImport(Pole All, SymChars SymForPole);
void PrintSettings(Cell &M, SymChars &S);
void PrintOk(Cell &M, SymChars &S);
void PrintOkImport(Cell &M, SymChars &S);
void PrintNoImport(Cell &M, SymChars &S);
void PrintXX(Cell &M, SymChars &S);
void PrintInfo(Cell &M, SymChars &S);
void PrintManual(Cell &M, SymChars &S);
void PrintAuto(Cell &M, SymChars &S);
void PrintNext(Cell &M, SymChars &S);
void PrintPoleForChoice(Pole All, SymChars SymForPole);
void PrintShipChoice(int &Boat, Mas &Arr, SymChars &ForPole);
void NoFile(Coor & Pos, Symbol &Sym, GlobPar &ParGlob, CountBoat &Col, Mas &Arr, Turn &T);
void Write(Mas &Arr, FILE *File, Turn &T, CountBoat &Col);
void Read(Mas &Arr, FILE *File, Turn &T, CountBoat &Col);


