
#include <iostream>
#include <Windows.h>
#include <io.h>
#include <time.h> 
#include <math.h>
#include "ConsoleLib.h"
#include "Game.h"
#include "ForStructures.h"
using namespace std;

//#define Debug

int main()
{
	ShowCursor(false);
	system("mode con cols=90 lines=20");
	srand((unsigned)time(0));

	GlobPar ParGlob = { 90,20,10,20 };
	Mas Arr;
	SymChars SymForPole;
	SymChars SymForCell;
	Pole You;
	Pole Pc;
	Pole ForInstShips;
	Coor Pos;
	Symbol Sym;
	CountBoat Col;
	D S;
	S.Sh1 = { 53,54,13,13,1,2,2,1 };
	S.Sh2H = { 53,56,11,11,1,4,4,2 };
	S.Sh3H = { 53,58,9,9,1,6,6,3 };
	S.Sh4H = { 53,60,7,7,1,8,8,4 };
	Col.B.CountGlobShipsPc = 0;
	Col.B.CountGlobShipsYour = 0;
	Warship MyWarship = { 1,2,3,4,5,6,7 }; //Идентификатор корабля
	MyMousePos Mouse;
	Shot G;
	Turn T;
	T.Victory = false;
	T.SwForTurn2 = false;
	T.SwForTurn3 = false;
	T.SwForTurn4 = false;
	T.SwGameModeAll = false;
	T.SwYourShot = true;

	InitSymForCell(SymForCell);
	InitSymPol(SymForPole);
	InitYou(You, ParGlob);
	InitPc(Pc, ParGlob);
	InitForInstShips(ForInstShips);

	Pos.You = You;
	Pos.Pc = Pc;
	Pos.ForInstShips = ForInstShips;
	Sym.ForCell = SymForCell;
	Sym.ForPole = SymForPole;
	DWORD dwOldMode, dwMode, dwNumRead;

	GetConsoleMode(hStdIn, &dwOldMode);

	dwMode = ENABLE_MOUSE_INPUT;

	SetConsoleMode(hStdIn, dwMode);

	INPUT_RECORD irInBuf[128];
	COORD mousePos;
	DWORD mouseButtonState;
	bool SwPrintMainMenu = false;
	bool SwPrintInsS = false;
	bool SwPrintStatistics = false;
	clock_t t1MM = 0;
	clock_t t2MM = 0;
	clock_t t1InsS = 0;
	clock_t t2InsS = 0;
	clock_t t1Auto = 0;
	clock_t t2Auto = 0;
	clock_t t1Manual = 0;
	clock_t t2Manual = 0;
	clock_t t1GM = 0;
	clock_t t2GM = 0;
	clock_t t1St = 0;
	clock_t t2St = 0;
	int CountMainMenu = 0;
	int CountInstS = 0;
	int CountManual = 0;
	int CountAuto = 0;
	int CountGameMode = 0;
	int CountStatistics = 0;
	int ClickButton;

	SetColor(Yellow, Black);
	PrintFon(0, ParGlob);
	PrintMainMenu(Pos.MainMenu, SymForCell);

	FILE *File = nullptr;
	if (_access("Save.bin", 0) != -1)
	{
		T.ImpSet = true;
		SetColor(Yellow, Black);
		PrintImport(Pos.Import, SymForPole);
		WriteStr(48, 9, "Load last save?");
		PrintOkImport(Pos.OkImport, Sym.ForCell);
		PrintNoImport(Pos.NoImport, Sym.ForCell);
	}
	else
		NoFile(Pos, Sym, ParGlob, Col, Arr, T);

	while (true)
	{
		ReadConsoleInput(hStdIn, irInBuf, 128, &dwNumRead);

		for (DWORD i = 0; i < dwNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case MOUSE_EVENT:
			{
				mousePos = irInBuf[i].Event.MouseEvent.dwMousePosition;
				mouseButtonState = irInBuf[i].Event.MouseEvent.dwButtonState;

				if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && ItsButton(Pos, mousePos, ClickButton, SwPrintMainMenu, T))
					switch (ClickButton)
					{
					case OkImport:
					{
						SetColor(Yellow, Red);
						PrintOkImport(Pos.OkImport, Sym.ForCell);
						Sleep(50);
						SetColor(Yellow, Black);
						PrintOkImport(Pos.OkImport, Sym.ForCell);
						SetColor(Blue, LightGray);
						PrintFon(0, ParGlob);
						SetColor(Yellow, Black);
						PrintMainMenu(Pos.MainMenu, SymForCell);
						SetColor(Blue, LightGray);
						PrintForInstShips(Pos, SymForPole);
						PrintPole(You, SymForPole, ParGlob);
						PrintPole(Pc, SymForPole, ParGlob);
						Read(Arr, File, T, Col);

						if (Col.B.CountGlobShipsYour && Col.B.CountGlobShipsPc)
						{
							SetColor(Cyan, LightGray);
							WriteStr(21, 1, "Your Shot!");
						}

						SetColor(Red, LightGray);
						WriteStr(48, 2, "LEFT TO KILL");
						WriteInt(35, 2, Col.B.CountGlobShipsYour);
						WriteInt(70, 2, Col.B.CountGlobShipsPc);
						SetColor(Blue, LightGray);
						PrintArrYou(Arr, You);
#ifdef Debug
						PrintArrPcDebug(Arr, Pc);
#else
						PrintArrPcRelease(Arr, Pc);
#endif
						T.ImpSet = false;

						break;
					}
					case NoImport:
					{
						SetColor(Yellow, Red);
						PrintNoImport(Pos.NoImport, Sym.ForCell);
						Sleep(50);
						SetColor(Yellow, Black);
						PrintNoImport(Pos.NoImport, Sym.ForCell);
						SetColor(Blue, LightGray);
						PrintFon(0, ParGlob);
						SetColor(Yellow, Black);
						PrintMainMenu(Pos.MainMenu, SymForCell);
						SetColor(Blue, LightGray);
						PrintForInstShips(Pos, SymForPole);
						PrintPole(You, SymForPole, ParGlob);
						PrintPole(Pc, SymForPole, ParGlob);
						SetColor(Red, LightGray);
						WriteStr(48, 2, "LEFT TO KILL");
						WriteInt(35, 2, Col.B.CountGlobShipsYour);
						WriteInt(70, 2, Col.B.CountGlobShipsPc);
						SetColor(Blue, LightGray);

						for (int i = 0; i < 10; i++)
							for (int j = 0; j < 20; j++)
							{
								Arr.M.YouArr[i][j] = 0;
								Arr.M.PcArr[i][j] = 0;
							}

						PrintArrYou(Arr, You);
#ifdef Debug
						PrintArrPcDebug(Arr, Pc);
#else
						PrintArrPcRelease(Arr, Pc);
#endif
						T.ImpSet = false;
						break;
					}
					case MainMenu:
					{
						CountMainMenu++;
						CountMainMenu % 2 ? t1MM = clock() : t2MM = clock();

						if (ItsAClick(t1MM, t2MM))
						{
							if (!SwPrintMainMenu)
							{
								SwPrintInsS = false;
								SetColor(LightBlue, LightCyan);
								PrintMainMenu(Pos.MainMenu, SymForCell);
								SetColor(Yellow, Black);
								PrintAllMenu(Pos.MainMenu, SymForCell);
								PrintMainMenu(Pos.MainMenu, SymForCell);
						
								if (Col.B.CountGlobShipsYour && Col.B.CountGlobShipsPc)
								{
									SetColor(Cyan, LightGray);
									WriteStr(21, 1, "Your Shot!");
								}
								
								SetColor(Red, LightGray);
								WriteStr(48, 2, "LEFT TO KILL");
								WriteInt(35, 2, Col.B.CountGlobShipsYour);
								WriteInt(70, 2, Col.B.CountGlobShipsPc);
								SetColor(Yellow, Black);
							}
							else if (SwPrintMainMenu)
							{
								SwPrintMainMenu = false;
								SetColor(Blue, LightGray);
								CleanFon(3, 19, 20);
								SetColor(Blue, LightGray);
								PrintForInstShips(Pos, SymForPole);
								PrintPole(You, SymForPole, ParGlob);
								PrintPole(Pc, SymForPole, ParGlob);
								PrintArrYou(Arr, You);
#ifdef Debug
								PrintArrPcDebug(Arr, Pc);
#else
								PrintArrPcRelease(Arr, Pc);
#endif
								if (Col.B.CountGlobShipsYour && Col.B.CountGlobShipsPc)
								{
									SetColor(Cyan, LightGray);
									WriteStr(21, 1, "Your Shot!");
								}
								
								SetColor(Red, LightGray);
								WriteStr(48, 2, "LEFT TO KILL");
								WriteInt(35, 2, Col.B.CountGlobShipsYour);
								WriteInt(70, 2, Col.B.CountGlobShipsPc);
								SetColor(Blue, LightGray);
								break;
							}
							SwPrintMainMenu = true;
						}
						break;
					}
					case InstallShips:
					{
						CountInstS++;
						CountInstS % 2 ? t1InsS = clock() : t2InsS = clock();
						if (ItsAClick(t1InsS, t2InsS))
						{
							if (!SwPrintInsS)
							{
								SetColor(Blue, LightGray);
								SetColor(LightBlue, LightCyan);
								PrintInstallShips(Pos.InstShBut, Sym.ForCell);
								SetColor(Yellow, Black);
								PrintManual(Pos.Manual, Sym.ForCell);
								PrintAuto(Pos.Auto, Sym.ForCell);
							}
							else if (SwPrintInsS)
							{
								SwPrintInsS = false;
								SetColor(Yellow, Black);
								PrintInstallShips(Pos.InstShBut, Sym.ForCell);
								SetColor(Blue, LightGray);
								CleanFon(0, 11, 40, 20);
								PrintForInstShips(Pos, SymForPole);
								PrintPole(You, SymForPole, ParGlob);
								PrintPole(Pc, SymForPole, ParGlob);
								PrintArrYou(Arr, You);
								if (Col.B.CountGlobShipsYour && Col.B.CountGlobShipsPc)
								{
									SetColor(Cyan, LightGray);
									WriteStr(21, 1, "Your Shot!");
								}
								SetColor(Red, LightGray);
								WriteStr(48, 2, "LEFT TO KILL");
								WriteInt(35, 2, Col.B.CountGlobShipsYour);
								WriteInt(70, 2, Col.B.CountGlobShipsPc);
								SetColor(Blue, LightGray);
#ifdef Debug
								PrintArrPcDebug(Arr, Pc);
#else
								PrintArrPcRelease(Arr, Pc);
#endif 
								break;
							}
							SwPrintInsS = true;
						}
						break;
					}
					case Manual:
					{
						if (SwPrintInsS)
						{
							SwPrintMainMenu = false;
							SwPrintInsS = false;
							SetConsoleMode(hStdIn, dwOldMode);
							T.SwGameModeAll = ManualStateShips(Pos, ParGlob, Sym, Arr, S, T, Mouse, Col);
							SetColor(Yellow, Black);
							PrintInstallShips(Pos.InstShBut, Sym.ForCell);
							SetColor(Blue, LightGray);
							CleanFon(3, 15, 20);
							PrintForInstShips(Pos, SymForPole);
							PrintPole(You, SymForPole, ParGlob);
							PrintPole(Pc, SymForPole, ParGlob);
							PrintArrYou(Arr, You);
#ifdef Debug
							PrintArrPcDebug(Arr, Pc);
#else
							PrintArrPcRelease(Arr, Pc);
#endif
							SetColor(Red, LightGray);
							WriteStr(48, 2, "LEFT TO KILL");
							WriteInt(35, 2, Col.B.CountGlobShipsYour);
							WriteInt(70, 2, Col.B.CountGlobShipsPc);
							SetColor(Cyan, LightGray);

							if (T.SwGameModeAll)
							{
								if (!T.Victory && (Col.B.CountGlobShipsPc < 10 || Col.B.CountGlobShipsYour < 10))
								{
									WriteStr(21, 1, "Your Shot!");
									T.SwYourShot = true;
								}
								else if (!T.Victory)
								{
									WriteStr(21, 1, "So it's game on!");
									Sleep(1500);
									WriteStr(21, 1, "                ");
								}
								if (Col.B.CountGlobShipsPc == 10 && Col.B.CountGlobShipsYour == 10)
									T.SwYourShot = rand() % 2;
								if (T.SwYourShot && Col.B.CountGlobShipsPc == 10 && Col.B.CountGlobShipsYour == 10)
									WriteStr(21, 1, "Your Shot!");
								else if (!T.SwYourShot && Col.B.CountGlobShipsPc == 10 && Col.B.CountGlobShipsYour == 10)
								{
									WriteStr(21, 1, "Pc Shot!");
									Sleep(1100);
									T.SwYourShot = PlayPc(Pos, Arr, G, Col, dwOldMode, dwMode);
								}
								SetColor(Blue, LightGray);
							}
						}

						break;
					}
					case Auto:
					{
						if (SwPrintInsS)
						{
							CountAuto++;
							CountAuto % 2 ? t1Auto = clock() : t2Auto = clock();
							if (ItsAClick(t1Auto, t2Auto, 0.2))
							{
								SwPrintInsS = false;
								SwPrintMainMenu = false;
								SetColor(Yellow, Black);
								T.SwGameModeAll = AutoStateShips(Pos, ParGlob, Sym, Arr, Col, T, G);
								CleanFon(3, 15, 20);
								SetColor(Blue, LightGray);
								PrintForInstShips(Pos, Sym.ForCell);
								PrintPole(You, SymForPole, ParGlob);
								PrintPole(Pc, SymForPole, ParGlob);
								PrintArrYou(Arr, You);
#ifdef Debug
								PrintArrPcDebug(Arr, Pc);
#else
								PrintArrPcRelease(Arr, Pc);
#endif
								SetColor(Red, LightGray);
								WriteStr(48, 2, "LEFT TO KILL");
								WriteInt(35, 2, Col.B.CountGlobShipsYour);
								WriteInt(70, 2, Col.B.CountGlobShipsPc);
								SetColor(Cyan, LightGray);

								if (T.SwGameModeAll)
								{
									if (!T.Victory && (Col.B.CountGlobShipsPc < 10 || Col.B.CountGlobShipsYour < 10))
									{
										WriteStr(21, 1, "Your Shot!");
										T.SwYourShot = true;
									}
									else if (!T.Victory)
									{
										WriteStr(21, 1, "So it's game on!");
										Sleep(1500);
										WriteStr(21, 1, "                ");
									}
									if (Col.B.CountGlobShipsPc == 10 && Col.B.CountGlobShipsYour == 10)
										T.SwYourShot = rand() % 2;
									if (T.SwYourShot && Col.B.CountGlobShipsPc == 10 && Col.B.CountGlobShipsYour == 10)
										WriteStr(21, 1, "Your Shot!");
									else if (!T.SwYourShot && Col.B.CountGlobShipsPc == 10 && Col.B.CountGlobShipsYour == 10)
									{
										WriteStr(21, 1, "Pc Shot!");
										Sleep(1100);
										T.SwYourShot = PlayPc(Pos, Arr, G, Col, dwOldMode, dwMode);
									}
									SetColor(Blue, LightGray);
								}
							}
						}
						break;
					}
					case GameMode:
					{
						if (T.SwGameModeAll)
						{
							CountGameMode++;
							CountGameMode % 2 ? t1GM = clock() : t2GM = clock();
							if (ItsAClick(t1GM, t2GM, 0.1))
							{
								if (T.SwYourShot)
								{
									int temp = Col.B.CountGlobShipsPc;

									SetColor(Cyan, LightGray);
									WriteStr(21, 1, "Your Shot!");
									SetColor(Blue, LightGray);
									T.SwYourShot = PlayYou(mousePos, Pos, Arr, Sym, Col);
#ifdef Debug
									PrintArrPcDebug(Arr, Pc);
#else
									PrintArrPcRelease(Arr, Pc);
#endif
									SetColor(Red, LightGray);
									WriteStr(35, 2, "  ");
									WriteStr(70, 2, "  ");
									WriteInt(35, 2, Col.B.CountGlobShipsYour);
									WriteInt(70, 2, Col.B.CountGlobShipsPc);
									SetColor(Blue, LightGray);
									if (!Col.B.CountGlobShipsPc)
										T.Victory = true;
									if (T.SwYourShot && temp >= Col.B.CountGlobShipsPc)
									{
										SetColor(Cyan, LightGray);
										WriteStr(21, 1, "Your Shot!           ");
										SetColor(Blue, LightGray);
									}
								}
								if (!T.SwYourShot)
								{
									SetColor(Cyan, LightGray);
									WriteStr(21, 1, "Pc Shot!             ");
									SetColor(Blue, LightGray);
									Sleep(250);
									T.SwYourShot = PlayPc(Pos, Arr, G, Col, dwOldMode, dwMode);
									PrintArrYou(Arr, You);
									SetColor(Red, LightGray);
									WriteStr(35, 2, "  ");
									WriteStr(70, 2, "  ");
									WriteInt(35, 2, Col.B.CountGlobShipsYour);
									WriteInt(70, 2, Col.B.CountGlobShipsPc);
									SetColor(Blue, LightGray);
									if (!Col.B.CountGlobShipsYour)
										T.Victory = true;
								}
							}
							if (T.Victory)
							{
								SetConsoleMode(hStdIn, dwOldMode);
								Sleep(1000);
								SetColor(Yellow, Black);
								PrintForInstShips(Pos, SymForPole);
								if (!Col.B.CountGlobShipsPc)
								{
									SetColor(Green, Black);
									Sleep(50);
									for (int i = 1; i < 10; i++)
									{
										if (i > 1)
											WriteStr(51, i - 1, "          ");
										WriteStr(51, i, "YOU WON!!!");
										Sleep(350);
									}
								}
								else
								{
									SetColor(Red, Black);
									Sleep(50);
									for (int i = 18; i >= 9; i--)
									{
										if (i <= 17)
											WriteStr(50, i + 1, "           ");
										WriteStr(50, i, "YOU LOST!!!");
										Sleep(350);
									}
								}

								Sleep(2000);
								SetColor(Blue, LightGray);
								CleanFon(3, 19, 20);
								SetColor(Blue, LightGray);
								PrintForInstShips(Pos, SymForPole);
								PrintPole(You, SymForPole, ParGlob);
								PrintPole(Pc, SymForPole, ParGlob);
								PrintArrYou(Arr, You);
#ifdef Debug
								PrintArrPcDebug(Arr, Pc);
#else
								PrintArrPcRelease(Arr, Pc);
#endif
								SetColor(Red, LightGray);
								WriteStr(48, 2, "LEFT TO KILL");
								WriteInt(35, 2, Col.B.CountGlobShipsYour);
								WriteInt(70, 2, Col.B.CountGlobShipsPc);
								SetColor(Blue, LightGray);
								SetConsoleMode(hStdIn, dwMode);
							}
						}
						break;
					}
					case Exit:
					{
						SetColor(LightBlue, LightCyan);
						PrintExit(Pos.Exit, SymForCell);
						Sleep(75);
						SetColor(Yellow, Black);
						PrintExit(Pos.Exit, SymForCell);
						SetColor(Yellow, Black);
						Write(Arr, File, T, Col);
						SetConsoleMode(hStdIn, dwOldMode);
						ShowCursor(true);
						exit(0);
					}
					}
			}
			}
		}
	}
}