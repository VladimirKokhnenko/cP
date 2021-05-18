#pragma once
#include <iostream>
#include <iomanip>
#include "ConsoleLib.h"
#include "ForStructures.h"
#include "Game.h"
using namespace std;

void CleanFon(int yUp, int yDown, int len, int x)
{
	for (int i = yUp; i <= yDown; i++)
		WriteChars(x, i, ' ', len);
}

void CleanFonStruct(Ships &AllVert, Ships &AllHor)
{
	int startI = AllVert.UpY - 1;
	int finishI = AllVert.DownY + 1;
	int begJ = AllHor.LeftX - 1;
	int  endJ = AllHor.Len + 2;

	for (int i = startI; i <= finishI; i++)
		WriteChars(begJ, i, ' ', endJ);
}

void PrintFon(int x, GlobPar &ParGlob)
{
	for (int i = 0; i < ParGlob.SizeLine; i++)
		WriteChars(x, i, ' ', ParGlob.SizeCol - x);
}

void PrintPole(Pole All, SymChars SymForPole, GlobPar &ParGlob)
{
	int Start = All.UpY;
	int Finish = All.DownY - 1;
	int ForNum = All.LeftX - 2;

	for (int i = Start; i <= Finish; i++)
	{
		if (i == Start)
		{
			WriteStr(All.LeftX, i - 1, "  A B C D E F G H I J");
			WriteChar(All.LeftX, i, SymForPole.TopLeft);
			WriteChars(All.LeftX + 1, i, SymForPole.HorCh, ParGlob.LenPole);
			WriteChar(All.RightX, i, SymForPole.TopRight);
		}
		if (i > Start && i < Finish)
		{
			GotoXY(ForNum, i);
			i < Finish - 1 ? cout << setw(2) << (char)('1' + i - 6) : cout << "10";
			WriteChar(All.LeftX, i, SymForPole.VertCh);
			WriteChar(All.RightX, i, SymForPole.VertCh);

		}
		if (i == Finish)
		{
			WriteChar(All.LeftX, i, SymForPole.DownLeft);
			WriteChars(All.LeftX + 1, i, SymForPole.HorCh, ParGlob.LenPole);
			WriteChar(All.RightX, i, SymForPole.DownRight);
		}
	}
}

void PrintArrYou(Mas &Arr, Pole All, const int Y, const int X)
{
	int y1 = All.UpY + 1;
	int y2 = All.UpY + 1 + Y;
	int x1 = All.LeftX + 1;
	int x2 = All.LeftX + 1 + X;

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			WriteChar(j, i, (char)Arr.M.YouArr[i - y1][j - x1]);
}
void PrintArrPcDebug(Mas &Arr, Pole All, const int Y, const int X)
{
	int y1 = All.UpY + 1;
	int y2 = All.UpY + 1 + Y;
	int x1 = All.LeftX + 1;
	int x2 = All.LeftX + 1 + X;

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			WriteChar(j, i, (char)Arr.M.PcArr[i - y1][j - x1]);
}

void PrintArrPcRelease(Mas &Arr, Pole All, const int Y, const int X)
{
	int y1 = All.UpY + 1;
	int y2 = All.UpY + 1 + Y;
	int x1 = All.LeftX + 1;
	int x2 = All.LeftX + 1 + X;

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			if(Arr.M.PcArr[i - y1][j - x1] != 219)
			WriteChar(j, i, (char)Arr.M.PcArr[i - y1][j - x1]);
}


void PrintShipsStat(D &S, Mas &Arr)//Статическая установка кораблей по заданным ячейкам в режиме редактирования игрового поля	
{
	int Y = 1;
	int X = 2;

	for (int i = 0; i < Y; i++)
	{
		GotoXY(S.Sh1.LeftX, S.Sh1.UpY + i);

		for (int j = 0; j < X; j++)
			if (Arr.M.D1A[i][j])
				j != X ? cout << (char)Arr.M.D1A[i][j] : cout << endl;
	}

	Y = 1;
	X = 4;

	for (int i = 0; i < Y; i++)
	{
		GotoXY(S.Sh2H.LeftX, S.Sh2H.UpY + i);

		for (int j = 0; j < X; j++)
			if (Arr.M.D2AH[i][j])
				j != X ? cout << (char)Arr.M.D2AH[i][j] : cout << endl;
	}

	Y = 1;
	X = 6;

	for (int i = 0; i < Y; i++)
	{
		GotoXY(S.Sh3H.LeftX, S.Sh3H.UpY + i);

		for (int j = 0; j < X; j++)
			if (Arr.M.D3AH[i][j])
				j != X ? cout << (char)Arr.M.D3AH[i][j] : cout << endl;
	}

	Y = 1;
	X = 8;

	for (int i = 0; i < Y; i++)
	{
		GotoXY(S.Sh4H.LeftX, S.Sh4H.UpY + i);

		for (int j = 0; j < X; j++)
			if (Arr.M.D4AH[i][j])
				j != X ? cout << (char)Arr.M.D4AH[i][j] : cout << endl;
	}
}

void PrintForInstShips(Coor &Pos, SymChars &SymForPole) // Это поле для установки кораблей
{
	int startI = Pos.ForInstShips.UpY;
	int finishI = Pos.ForInstShips.DownY;

	for (int i = startI; i <= finishI; i++)
	{
		if (i == startI)
		{
			WriteChar(Pos.ForInstShips.LeftX, i, SymForPole.TopLeft);
			WriteChars(Pos.ForInstShips.LeftX + 1, i, SymForPole.HorCh, Pos.ForInstShips.Len);
			WriteChar(Pos.ForInstShips.RightX, i, SymForPole.TopRight);
		}
		if (i > startI && i < finishI)
		{
			WriteChar(Pos.ForInstShips.LeftX, i, SymForPole.VertCh);
			WriteChars(Pos.ForInstShips.LeftX + 1, i, ' ', Pos.ForInstShips.Len);
			WriteChar(Pos.ForInstShips.RightX, i, SymForPole.VertCh);
		}
		if (i == finishI)
		{
			WriteChar(Pos.ForInstShips.LeftX, i, SymForPole.DownLeft);
			WriteChars(Pos.ForInstShips.LeftX + 1, i, SymForPole.HorCh, Pos.ForInstShips.Len);
			WriteChar(Pos.ForInstShips.RightX, i, SymForPole.DownRight);
		}
	}
}

void PrintMainMenu(Cell &M, SymChars &S)
{
	for (int i = M.UpY; i < M.HeightCell; i++)
	{
		if (i == M.LeftX)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > M.UpY && i < M.HeightCell - 1)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.WidthCell / 2 - 1, i, "Menu");
		}
		if (i == M.HeightCell - 1)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintAllMenu(Cell &M, SymChars &S)
{
	const int count = 2;
	int start;
	int finish;

	for (int i = 1; i <= count; i++)
	{
		start = M.DownY * i;
		finish = start + M.HeightCell - 1;

		for (int j = start; j <= finish; j++)
		{
			if (j == start)
			{
				WriteChar(M.LeftX, j, S.TopLeft);
				WriteChars(M.LeftX + 1, j, S.HorCh, M.WidthCell - 1);
				WriteChar(M.RightX, j, S.TopRight);
			}
			if (j == start + 1)
			{
				WriteChar(M.LeftX, j, S.VertCh);
				WriteChars(M.LeftX + 1, j, S.Pusto, M.WidthCell - 1);
				WriteChar(M.RightX, j, S.VertCh);

				switch (i)
				{
				case 1:
					WriteStr(M.WidthCell / 2 - 6, j, "Install Ships");
					break;
				case 2:
					WriteStr(M.WidthCell / 2 - 1, j, "Exit");
					break;
				}
			}
			if (j == finish)
			{
				WriteChar(M.LeftX, j, S.DownLeft);
				WriteChars(M.LeftX + 1, j, S.HorCh, M.WidthCell - 1);
				WriteChar(M.RightX, j, S.DownRight);
			}
		}
	}
}

void PrintInstallShips(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.WidthCell / 2 - 6, i, "Install Ships");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintExit(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.WidthCell / 2 - 1, i, "Exit");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintCreateUser(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.RightX - M.WidthCell / 2 - 5, i, "Create User");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintInfo(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.RightX - M.WidthCell / 2, i, "?");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

//void PrintStatisticsData(size_t &count, User *&PtrUser)
//{
//	WriteStr(22, 1, "NAME");
//	WriteStr(42, 1, "WINS");
//	WriteStr(50, 1, "LOSESS");
//
//	for (size_t i = 0, j = 2; i < count; i++, j++)
//	{
//		GotoXY(22, j);
//		cout << PtrUser[i].Name;
//		GotoXY(43, j);
//		cout << PtrUser[i].CountWins;
//		GotoXY(53, j);
//		cout << PtrUser[i].CountLosses;
//	}
//}

void PrintSettings(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.RightX - M.WidthCell / 2 - 5, i, "Settings");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell - 1);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintOk(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.RightX - M.WidthCell / 2 - 1, i, "Ok");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintOkImport(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.RightX - M.WidthCell / 2 - 1, i, "Ok");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}
void PrintNoImport(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);
			WriteStr(M.RightX - M.WidthCell / 2 - 1, i, "No");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintXX(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);
			//WriteChar(M.RightX - M.WidthCell / 2 - 1, i, 62);
			//WriteChar(M.RightX - M.WidthCell / 2, i, 60);

			WriteStr(M.RightX - M.WidthCell / 2, i, "X");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintManual(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);
			//WriteChar(M.RightX - M.WidthCell / 2 - 1, i, 62);
			//WriteChar(M.RightX - M.WidthCell / 2, i, 60);

			WriteStr(M.RightX - M.WidthCell / 2 - 3, i, "Manual");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintAuto(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);
			//WriteChar(M.RightX - M.WidthCell / 2 - 1, i, 62);
			//WriteChar(M.RightX - M.WidthCell / 2, i, 60);

			WriteStr(M.RightX - M.WidthCell / 2 - 2, i, "Auto");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintNext(Cell &M, SymChars &S)
{
	int start = M.UpY;
	int finish = M.DownY;
	for (int i = start; i <= finish; i++)
	{
		if (i == start)
		{
			WriteChar(M.LeftX, i, S.TopLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.TopRight);
		}
		if (i > start && i < finish)
		{
			WriteChar(M.LeftX, i, S.VertCh);
			WriteChars(M.LeftX + 1, i, S.Pusto, M.WidthCell);
			WriteChar(M.RightX, i, S.VertCh);

			WriteStr(M.RightX - M.WidthCell / 2 - 2, i, "Next");
		}
		if (i == finish)
		{
			WriteChar(M.LeftX, i, S.DownLeft);
			WriteChars(M.LeftX + 1, i, S.HorCh, M.WidthCell);
			WriteChar(M.RightX, i, S.DownRight);
		}
	}
}

void PrintImport(Pole All, SymChars SymForPole)
{
	int Start = All.UpY;
	int Finish = All.DownY - 1;

	for (int i = Start; i <= Finish; i++)
	{
		if (i == Start)
		{
			WriteChar(All.LeftX, i, SymForPole.TopLeft);
			WriteChars(All.LeftX + 1, i, SymForPole.HorCh, All.Len);
			WriteChar(All.RightX, i, SymForPole.TopRight);
		}
		if (i > Start && i < Finish)
		{
			WriteChar(All.LeftX, i, SymForPole.VertCh);
			WriteChars(All.LeftX + 1, i, SymForPole.Pusto, All.Len);
			WriteChar(All.RightX, i, SymForPole.VertCh);

		}
		if (i == Finish)
		{
			WriteChar(All.LeftX, i, SymForPole.DownLeft);
			WriteChars(All.LeftX + 1, i, SymForPole.HorCh, All.Len);
			WriteChar(All.RightX, i, SymForPole.DownRight);
		}
	}
}

void PrintPoleForChoice(Pole All, SymChars SymForPole)
{
	int Start = All.UpY;
	int Finish = All.DownY - 1;

	for (int i = Start; i <= Finish; i++)
	{
		if (i == Start)
		{
			WriteChar(All.LeftX, i, SymForPole.TopLeft);
			WriteChars(All.LeftX + 1, i, SymForPole.HorCh, All.Len);
			WriteChar(All.RightX, i, SymForPole.TopRight);
		}
		if (i > Start && i < Finish)
		{
			WriteChar(All.LeftX, i, SymForPole.VertCh);
			WriteChar(All.RightX, i, SymForPole.VertCh);

		}
		if (i == Finish)
		{
			WriteChar(All.LeftX, i, SymForPole.DownLeft);
			WriteChars(All.LeftX + 1, i, SymForPole.HorCh, All.Len);
			WriteChar(All.RightX, i, SymForPole.DownRight);
		}
	}
}
void PrintShipChoice(int &Boat, Mas &Arr, SymChars &ForPole)
{
	int Xc = 71;
	int Yc = 9;
	int x = Arr.M.XD1A;
	int y = Arr.M.YD1A;
	int Len = Arr.M.XD1A + 1;
	int ArrAll[4][8] = {};

	CleanFon(8, 13, Arr.M.XD4AH + 2, 67);

	switch (Boat)
	{
	case Boat1:
	{
		x = Arr.M.XD1A;
		y = Arr.M.YD1A;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D1A[i][j];
			}

		Xc = 72;
		Yc = 9;
		Len = Arr.M.XD1A + 1;
		break;
	}
	case BoatV2:
	{
		x = Arr.M.XD1A;
		y = Arr.M.YD2AV;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D2AV[i][j];
			}

		Xc = 72;
		Yc = 9;
		break;
	}
	case BoatV3:
	{
		x = Arr.M.XD1A;
		y = Arr.M.YD3AV;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D3AV[i][j];
			}

		Xc = 72;
		Yc = 9;
		break;
	}
	case BoatV4:
	{
		x = Arr.M.XD1A;
		y = Arr.M.YD4AV;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D4AV[i][j];
			}

		Xc = 72;
		Yc = 9;
		break;
	}
	case BoatH2:
	{
		x = Arr.M.XD2AH;
		y = Arr.M.YD1A;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D2AH[i][j];
			}

		Xc = 68;
		Yc = 10;
		Len = Arr.M.XD2AH + 1;
		break;
	}
	case BoatH3:
	{
		x = Arr.M.XD3AH;
		y = Arr.M.YD1A;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D3AH[i][j];
			}

		Xc = 68;
		Yc = 10;
		Len = Arr.M.XD3AH + 1;
		break;
	}
	case BoatH4:
	{
		x = Arr.M.XD4AH;
		y = Arr.M.YD1A;

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				ArrAll[i][j] = Arr.M.D4AH[i][j];
			}

		Xc = 68;
		Yc = 10;
		Len = Arr.M.XD4AH + 1;
		break;
	}
	}

	for (int i = 0; i <= y; i++)
	{
		if (i == 0)
		{
			WriteChar(Xc - 1, Yc - 1, ForPole.TopLeft);
			WriteChars(Xc, Yc - 1, ForPole.HorCh, Len - 1);
			WriteChar(Xc + Len - 1, Yc - 1, ForPole.TopRight);
		}
		if (i < y)
		{
			WriteChar(Xc - 1, Yc + i, ForPole.VertCh);
			WriteChar(Xc + Len - 1, Yc + i, ForPole.VertCh);
		}
		if (i == y)
		{
			WriteChar(Xc - 1, Yc + i, ForPole.DownLeft);
			WriteChars(Xc, Yc + i, ForPole.HorCh, Len - 1);
			WriteChar(Xc + Len - 1, Yc + i, ForPole.DownRight);
		}
	}

	GotoXY(Xc, Yc);
	for (int i = 0, k = 1; i < y; i++, k++)
	{
		for (int j = 0; j < x; j++)
			cout << (char)ArrAll[i][j];
		GotoXY(Xc, Yc + k);
	}
}

