#pragma warning(disable : 4996)
#include <iostream>
#include <time.h>          // time, clock_t, clock
#include "ConsoleLib.h"
#include "ForStructures.h"
#include "Game.h"
using namespace std;

void InitSymPol(SymChars &SymForPole)
{
	SymForPole.TopLeft = (char)201;	//218
	SymForPole.TopRight = (char)187;	//
	SymForPole.DownLeft = (char)200;	//192;
	SymForPole.DownRight = (char)188;	//217;
	SymForPole.HorCh = (char)205;		//196
	SymForPole.VertCh = (char)186;	//179
	SymForPole.Pusto = ' ';
}

void InitYou(Pole &You, GlobPar &ParGlob)
{
	You.LeftX = 25;
	You.RightX = You.LeftX + ParGlob.LenPole + 1;
	You.UpY = (ParGlob.SizeLine - ParGlob.HightPole) / 2;
	You.DownY = You.UpY + ParGlob.HightPole + 2;
	You.Len = You.RightX - You.LeftX - 1;
	You.Hight = You.DownY - You.UpY - 2;
}
void InitPc(Pole &Pc, GlobPar &ParGlob)
{
	Pc.LeftX = ParGlob.SizeCol / 6 * 4;
	Pc.RightX = Pc.LeftX + ParGlob.LenPole + 1;
	Pc.UpY = (ParGlob.SizeLine - ParGlob.HightPole) / 2;
	Pc.DownY = Pc.UpY + ParGlob.HightPole + 2;
	Pc.Len = Pc.RightX - Pc.LeftX - 1;
	Pc.Hight = Pc.DownY - Pc.UpY - 2;
}
void InitForInstShips(Pole &Inst)
{
	Inst.LeftX = 20;
	Inst.RightX = 89;
	Inst.UpY = 0;
	Inst.DownY = 19;
	Inst.Len = Inst.RightX - Inst.LeftX;
	Inst.Hight = Inst.DownY - Inst.UpY;
}

void InitSymForCell(SymChars &SymForCell)
{
	SymForCell.TopLeft = (char)218;
	SymForCell.TopRight = (char)191;
	SymForCell.MidLeft = (char)195;
	SymForCell.MidRight = (char)180;
	SymForCell.DownLeft = (char)192;
	SymForCell.DownRight = (char)217;
	SymForCell.VertCh = (char)179;
	SymForCell.HorCh = (char)196;
	SymForCell.Pusto = ' ';
};


void Write(Mas &Arr, FILE *File, Turn &T, CountBoat &Col)
{
	if ((File = fopen("Save.bin", "wb")) == nullptr)
	{
		GotoXY(22, 19);
		cout << "Error";
		exit(1);
	}

	fwrite(Arr.M.YouArr, sizeof(Arr.M.YouArr[0][0]), 200, File);
	fwrite(Arr.M.PcArr, sizeof(Arr.M.YouArr[0][0]), 200, File);
	fwrite(&T.SwGameModeAll, sizeof(T.SwGameModeAll), 1, File);
	fwrite(&T.SwYourShot, sizeof(T.SwYourShot), 1, File);
	fwrite(&Col.B.CountGlobShipsPc, sizeof(Col.B.CountGlobShipsPc), 1, File);
	fwrite(&Col.B.CountGlobShipsYour, sizeof(Col.B.CountGlobShipsYour), 1, File);
	fwrite(&T.Victory, sizeof(T.Victory), 1, File);
	fclose(File);
}

void Read(Mas &Arr, FILE *File, Turn &T, CountBoat &Col)
{
	if ((File = fopen("Save.bin", "rb")) == nullptr)
	{
		GotoXY(22, 19);
		cout << "Error\n";
		exit(2);
	}

	fread(Arr.M.YouArr, sizeof(Arr.M.YouArr[0][0]), 200, File);
	fread(Arr.M.PcArr, sizeof(Arr.M.PcArr[0][0]), 200, File);
	fread(&T.SwGameModeAll, sizeof(T.SwGameModeAll), 1, File);
	fread(&T.SwYourShot, sizeof(T.SwYourShot), 1, File);
	fread(&Col.B.CountGlobShipsPc, sizeof(Col.B.CountGlobShipsPc), 1, File);
	fread(&Col.B.CountGlobShipsYour, sizeof(Col.B.CountGlobShipsYour), 1, File);
	fread(&T.Victory, sizeof(T.Victory), 1, File);
	fclose(File);
}

void NoFile(Coor & Pos, Symbol &Sym, GlobPar &ParGlob, CountBoat &Col, Mas &Arr, Turn &T)
{
	SetColor(Blue, LightGray);
	PrintFon(0, ParGlob);
	SetColor(Yellow, Black);
	PrintMainMenu(Pos.MainMenu, Sym.ForCell);
	SetColor(Blue, LightGray);
	PrintForInstShips(Pos, Sym.ForPole);
	PrintPole(Pos.You, Sym.ForPole, ParGlob);
	PrintPole(Pos.Pc, Sym.ForPole, ParGlob);
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

	PrintArrYou(Arr, Pos.You);
#ifdef Debug
	PrintArrPcDebug(Arr, Pc);
#else
	PrintArrPcRelease(Arr, Pos.Pc);
#endif
	T.ImpSet = false;
}

int GiveBoat(COORD &mousePos, D &S)
{
	if (mousePos.X >= S.Sh1.LeftX && mousePos.X <= S.Sh1.RightX && mousePos.Y == S.Sh1.UpY)
		return Boat1;

	if (mousePos.X >= S.Sh2H.LeftX && mousePos.X <= S.Sh2H.RightX
		&& mousePos.Y >= S.Sh2H.UpY && mousePos.Y <= S.Sh2H.DownY)
		return BoatH2;

	if (mousePos.X >= S.Sh3H.LeftX && mousePos.X <= S.Sh3H.RightX
		&& mousePos.Y >= S.Sh3H.UpY && mousePos.Y <= S.Sh3H.DownY)
		return BoatH3;

	if (mousePos.X >= S.Sh4H.LeftX && mousePos.X <= S.Sh4H.RightX
		&& mousePos.Y >= S.Sh4H.UpY && mousePos.Y <= S.Sh4H.DownY)
		return BoatH4;
	return Boat1;
}

bool PlayYou(COORD mousePos, Coor Pos, Mas &Arr, Symbol &Sym, CountBoat &Col)
{
	int xShot = mousePos.X - Pos.Pc.LeftX - 1;
	int yShot = mousePos.Y - Pos.Pc.UpY - 1;

	if (mousePos.X % 2 == 0)
		xShot = mousePos.X - Pos.Pc.LeftX - 2;

	int coorLeftX = 0;
	int coorRightX;
	int coorUpY = 0;
	int coorDownY = 0;
	int swOn;

	if (Arr.M.PcArr[yShot][xShot] == Arr.M.Active)
		swOn = 3;
	else if (!Arr.M.PcArr[yShot][xShot])
		swOn = 2;
	else
		swOn = 1;

	switch (swOn)
	{
	case 1:
		return true;
	case 2:
	{
		for (int j = xShot; j < xShot + 2; j++)
			Arr.M.PcArr[yShot][j] = Arr.M.Missed;
		return false;
	}
	case 3:
	{
		for (int j = xShot; j < xShot + 2; j++)
			Arr.M.PcArr[yShot][j] = Arr.M.Sank;

		for (int j = xShot; j < 20; j++)
			if (!Arr.M.PcArr[yShot][j] || j == 19 || Arr.M.PcArr[yShot][j] == Arr.M.Missed)
			{
				coorRightX = j;
				break;
			}
		for (int j = xShot; j >= 0; j--)
			if (!Arr.M.PcArr[yShot][j] || Arr.M.PcArr[yShot][j] == Arr.M.Missed || !j)
			{
				coorLeftX = j;
				break;
			}
		for (int i = yShot; i < 10; i++)
			if (!Arr.M.PcArr[i][xShot] || i == 9 || Arr.M.PcArr[i][xShot] == Arr.M.Missed)
			{
				coorDownY = i;
				break;
			}
		for (int i = yShot; i >= 0; i--)
			if (!Arr.M.PcArr[i][xShot] || Arr.M.PcArr[i][xShot] == Arr.M.Missed || !i)
			{
				coorUpY = i;
				break;
			}

		bool boatSnak = true;

		for (int i = coorUpY; i <= coorDownY; i++)
			for (int j = coorLeftX; j <= coorRightX; j++)
				if (Arr.M.PcArr[i][j] == Arr.M.Active)
					boatSnak = false;
		if (boatSnak)
		{
			for (int i = coorUpY; i <= coorDownY; i++)
				for (int j = coorLeftX - 1; j <= coorRightX + 1; j++)
					if (Arr.M.PcArr[i][j] == 0 && j >= 0 && j < 20)
						Arr.M.PcArr[i][j] = Arr.M.Missed;
			Col.B.CountGlobShipsPc--;
		}
		return true;
	}
	}
	return false;
}

bool PlayPc(Coor Pos, Mas &Arr, Shot &G, CountBoat &Col, DWORD &dwOldMode, DWORD &dwMode)
{
	SetConsoleMode(hStdIn, dwOldMode);


	int xShot, yShot;
	int coorLeftX;
	int coorRightX;
	int coorUpY;
	int coorDownY;
	int swOn;

	do
	{
		int temp = G.CountShotPc;

		if (!G.Hit && !temp)//по умолчанию false
		{
			G.First.X = xShot = rand() % 20;
			G.First.Y = yShot = rand() % 10;
		}
		else if (temp == 1)
		{
			if (!Arr.M.YouArr[G.First.Y - 1][G.First.X] && G.First.Y != 0 || Arr.M.YouArr[G.First.Y - 1][G.First.X] == Arr.M.Active && G.First.Y != 0)
			{
				G.Second.X = xShot = G.First.X;
				G.Second.Y = yShot = G.First.Y - 1;
			}
			else if (!Arr.M.YouArr[G.First.Y + 1][G.First.X] && G.First.Y + 1 != 10 || Arr.M.YouArr[G.First.Y + 1][G.First.X] == Arr.M.Active && G.First.Y + 1 != 10)
			{
				G.Second.X = xShot = G.First.X;
				G.Second.Y = yShot = G.First.Y + 1;
			}
			else if (!Arr.M.YouArr[G.First.Y][G.First.X - 2] && G.First.X != 0 || Arr.M.YouArr[G.First.Y][G.First.X - 2] == Arr.M.Active && G.First.X != 0)
			{
				G.Second.X = xShot = G.First.X - 2;
				G.Second.Y = yShot = G.First.Y;
			}
			else if (!Arr.M.YouArr[G.First.Y][G.First.X + 2] && G.First.X + 2 != 20 || Arr.M.YouArr[G.First.Y][G.First.X + 2] == Arr.M.Active && G.First.X + 2 != 20)
			{
				G.Second.X = xShot = G.First.X + 2;
				G.Second.Y = yShot = G.First.Y;
			}
		}
		else if (temp >= 2)
		{
			if (Arr.M.YouArr[G.Second.Y][G.Second.X] == Arr.M.Sank && Arr.M.YouArr[G.First.Y][G.First.X] == Arr.M.Sank && G.Second.Y == G.First.Y)
			{
				yShot = G.First.Y;
				for (int j = G.First.X; j >= 0; j--)
				{
					if (Arr.M.YouArr[G.First.Y][j] == Arr.M.Active || !Arr.M.YouArr[G.First.Y][j])
					{
						xShot = j;
						break;
					}
					if (Arr.M.YouArr[G.First.Y][j] == Arr.M.Missed || !j)
						break;
				}
			}
			if (Arr.M.YouArr[G.Second.Y][G.Second.X] == Arr.M.Sank && Arr.M.YouArr[G.First.Y][G.First.X] == Arr.M.Sank && G.Second.Y == G.First.Y)
			{
				yShot = G.First.Y;
				for (int j = G.First.X; j < 20; j++)
				{
					if (Arr.M.YouArr[G.First.Y][j] == Arr.M.Active || !Arr.M.YouArr[G.First.Y][j])
					{
						xShot = j;
						break;
					}
					if (Arr.M.YouArr[G.First.Y][j] == Arr.M.Missed || j == 19)
						break;
				}
			}
			if (Arr.M.YouArr[G.Second.Y][G.Second.X] == Arr.M.Sank && Arr.M.YouArr[G.First.Y][G.First.X] == Arr.M.Sank && G.Second.X == G.First.X)
			{
				xShot = G.First.X;
				for (int i = G.First.Y; i >= 0; i--)
				{
					if (Arr.M.YouArr[i][G.First.X] == Arr.M.Active || !Arr.M.YouArr[i][G.First.X])
					{
						yShot = i;
						break;
					}
					if (Arr.M.YouArr[i][G.First.X] == Arr.M.Missed || !i)
						break;
				}
			}
			if (Arr.M.YouArr[G.Second.Y][G.Second.X] == Arr.M.Sank && Arr.M.YouArr[G.First.Y][G.First.X] == Arr.M.Sank && G.Second.X == G.First.X)
			{
				xShot = G.First.X;
				for (int i = G.First.Y; i < 10; i++)
				{
					if (Arr.M.YouArr[i][G.First.X] == Arr.M.Active || !Arr.M.YouArr[i][G.First.X])
					{
						yShot = i;
						break;
					}
					if (Arr.M.YouArr[i][G.First.X] == Arr.M.Missed || i == 9)
						break;
				}
			}
		}
		if (xShot % 2)
		{
			xShot -= 1;
			G.First.X -= 1;
		}

		if (!Arr.M.YouArr[yShot][xShot])
			swOn = 1;
		else if (Arr.M.YouArr[yShot][xShot] == Arr.M.Active)
			swOn = 2;
		else if (Arr.M.YouArr[yShot][xShot] == Arr.M.Missed || Arr.M.YouArr[yShot][xShot] == Arr.M.Sank)
			swOn = 3;

		switch (swOn)
		{
		case 1:
		{
			Arr.M.YouArr[yShot][xShot] = Arr.M.Missed;
			Arr.M.YouArr[yShot][xShot + 1] = Arr.M.Missed;
			G.Hit = false;

			SetColor(Blue, LightGray);
			PrintArrYou(Arr, Pos.You);
			Sleep(500);
			SetColor(Cyan, LightGray);
			WriteStr(21, 1, "Your Shot!           ");
			SetColor(Blue, LightGray);
			SetConsoleMode(hStdIn, dwMode);
			return true;
		}
		case 2:
		{
			G.Hit = true;
			G.CountShotPc++;

			for (int j = xShot; j < xShot + 2; j++)
				Arr.M.YouArr[yShot][j] = Arr.M.Sank;
			SetColor(Blue, LightGray);
			PrintArrYou(Arr, Pos.You);

			for (int j = G.First.X; j < 20; j++)
				if (!Arr.M.YouArr[G.First.Y][j] || j == 19 || Arr.M.YouArr[G.First.Y][j] == Arr.M.Missed)
				{
					coorRightX = j;
					break;
				}
			for (int j = G.First.X; j >= 0; j--)
				if (!Arr.M.YouArr[G.First.Y][j] || Arr.M.YouArr[G.First.Y][j] == Arr.M.Missed || !j)
				{
					coorLeftX = j;
					break;
				}
			for (int i = G.First.Y; i < 10; i++)
				if (!Arr.M.YouArr[i][G.First.X] || i == 9 || Arr.M.YouArr[i][G.First.X] == Arr.M.Missed)
				{
					coorDownY = i;
					break;
				}
			for (int i = G.First.Y; i >= 0; i--)
				if (!Arr.M.YouArr[i][G.First.X] || Arr.M.YouArr[i][G.First.X] == Arr.M.Missed || !i)
				{
					coorUpY = i;
					break;
				}

			bool boatSnak = true;

			for (int i = coorUpY; i <= coorDownY; i++)
			{
				for (int j = coorLeftX; j <= coorRightX; j++)
					if (Arr.M.YouArr[i][j] == Arr.M.Active)
					{
						boatSnak = false;
						break;
					}
				if (!boatSnak)
				{
					SetColor(Blue, LightGray);
					PrintArrYou(Arr, Pos.You);
					Sleep(500);
					break;
				}
			}
			if (boatSnak)
			{
				for (int i = coorUpY; i <= coorDownY; i++)
					for (int j = coorLeftX - 1; j <= coorRightX + 1; j++)
						if (Arr.M.YouArr[i][j] == 0 && j >= 0 && j < 20)
							Arr.M.YouArr[i][j] = Arr.M.Missed;
				G.Hit = false;
				G.CountShotPc = 0;
				G.First.X = 100;
				G.First.Y = 100;
				Col.B.CountGlobShipsYour--;

				//				Sleep(500);
				SetColor(Red, LightGray);
				WriteStr(35, 2, "  ");
				WriteStr(70, 2, "  ");
				WriteInt(35, 2, Col.B.CountGlobShipsYour);
				WriteInt(70, 2, Col.B.CountGlobShipsPc);
				SetColor(Blue, LightGray);
				Sleep(500);
				PrintArrYou(Arr, Pos.You);
				Sleep(500);
				if (!Col.B.CountGlobShipsYour)
				{
					SetConsoleMode(hStdIn, dwMode);
					return true;
				}
			}

			break;
		}
		case 3://Pc попал в поле в которое уже стрел€л, цикл продолжаетс€
			break;
		}

	} while (true);
}

bool ManualStateShips(Coor &Pos, GlobPar &ParGlob, Symbol &Sym, Mas &Arr, D &S, Turn &T, MyMousePos &Mouse, CountBoat &Col)
{
	int tempArrYou[10][20] = {};
	int tempArrPc[10][20] = {};
	int tempYou1 = Col.B.CountBoatYou1;
	int tempYou2 = Col.B.CountBoatYou2;
	int tempYou3 = Col.B.CountBoatYou3;
	int tempYou4 = Col.B.CountBoatYou4;
	int tempPc1 = Col.B.CountBoatPc1;
	int tempPc2 = Col.B.CountBoatPc2;
	int tempPc3 = Col.B.CountBoatPc3;
	int tempPc4 = Col.B.CountBoatPc4;
	bool tempVictory = T.Victory;
	int tempCountGlobShipsPc = Col.B.CountGlobShipsPc;
	int tempCountGlobShipsYour = Col.B.CountGlobShipsYour;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
		{
			tempArrYou[i][j] = Arr.M.YouArr[i][j];
			tempArrPc[i][j] = Arr.M.PcArr[i][j];

			Arr.M.YouArr[i][j] = 0;
			Arr.M.PcArr[i][j] = 0;
		}
	Col.B.CountBoatYou1 = 4;
	Col.B.CountBoatYou2 = 3;
	Col.B.CountBoatYou3 = 2;
	Col.B.CountBoatYou4 = 1;
	Col.B.CountBoatPc1 = 4;
	Col.B.CountBoatPc2 = 3;
	Col.B.CountBoatPc3 = 2;
	Col.B.CountBoatPc4 = 1;

	SetColor(LightCyan, Blue);
	PrintForInstShips(Pos, Sym.ForPole);
	PrintPole(Pos.You, Sym.ForPole, ParGlob);
	PrintArrYou(Arr, Pos.You);
	PrintShipsStat(S, Arr);

	SetColor(Black, LightGray);
	PrintOk(Pos.Ok, Sym.ForCell);
	PrintXX(Pos.XX, Sym.ForCell);
	PrintInfo(Pos.Info, Sym.ForCell);
	SetColor(LightCyan, Blue);

	PrintShipsStat(S, Arr);
	WriteInt(49, 7, Col.B.CountBoatYou4);
	WriteInt(49, 9, Col.B.CountBoatYou3);
	WriteInt(49, 11, Col.B.CountBoatYou2);
	WriteInt(49, 13, Col.B.CountBoatYou1);

	DWORD dwMode, dwNumRead;
	dwMode = ENABLE_MOUSE_INPUT;
	INPUT_RECORD irInBuf[128];
	COORD mousePos;
	DWORD mouseButtonState;

	int Boat = 1;
	int x1, x2, y1, y2, XD1, XD2, YD1, YD2, X1, X2, Y1, Y2;
	int ArrAll[4][8];
	int Xb = 49;
	int Yb;
	int WQ = 1;
	int *CountGlob = &WQ;

	clock_t t1RB = 0;
	clock_t t2RB = 0;
	clock_t t1L2B = 0;
	clock_t t2L2B = 0;
	clock_t t1L1B = 0;
	clock_t t2L1B = 0;
	clock_t t1Info = 0;
	clock_t t2Info = 0;
	int CountInfo = 0;
	int CountRightBut = 0;
	int CountL2But = 0;
	int CountLeftBut = 0;
	bool SwInfo = true;
	bool SwBoatAll = true;
	bool SwBoat1 = false;
	bool SwBoat2 = false;
	bool SwBoat3 = false;
	bool SwBoat4 = false;
	bool SwCountDel = false;
	PrintShipChoice(Boat, Arr, Sym.ForPole);
	SetConsoleMode(hStdIn, dwMode);

	while (true)
	{
		ReadConsoleInput(hStdIn, irInBuf, 128, &dwNumRead);

		for (DWORD i = 0; i < dwNumRead; i++)
		{
			mousePos = irInBuf[i].Event.MouseEvent.dwMousePosition;

			// —осто€ние кнопок мыши
			mouseButtonState = irInBuf[i].Event.MouseEvent.dwButtonState;

			// Ќажата лева€ кнопка мыши

			if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && ItsADeckTrue(mousePos, S) && SwInfo)
			{
				Boat = GiveBoat(mousePos, S);
				SwBoatAll = false;
				PrintShipChoice(Boat, Arr, Sym.ForPole);
			}

			if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePos.X > Pos.You.LeftX && mousePos.X < Pos.You.RightX && mousePos.Y > Pos.You.UpY && mousePos.Y < Pos.You.DownY && SwInfo)
			{
				if (SwBoatAll)
					Boat = Boat1;

				CountLeftBut++;
				CountLeftBut % 2 ? t1L1B = clock() : t2L1B = clock();

				if (ItsAClick(t1L1B, t2L1B, 0.25))
				{
					switch (Boat)
					{
					case Boat1:
					{
						Yb = 13;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD1A - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD1A; i++)
							for (int j = 0; j < 2; j++)
								ArrAll[i][j] = Arr.M.D1A[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou1;
						SwBoat1 = true;
						SwBoat2 = false;
						SwBoat3 = false;
						SwBoat4 = false;
						break;
					}
					case BoatH2:
					{
						Yb = 11;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD2AH - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD1A - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD1A; i++)
							for (int j = 0; j < Arr.M.XD2AH; j++)
								ArrAll[i][j] = Arr.M.D2AH[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD2AH - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou2;
						SwBoat1 = false;
						SwBoat2 = true;
						SwBoat3 = false;
						SwBoat4 = false;
						break;
					}
					case BoatH3:
					{
						Yb = 9;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD3AH - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD1A - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD1A; i++)
							for (int j = 0; j < Arr.M.XD3AH; j++)
								ArrAll[i][j] = Arr.M.D3AH[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD3AH - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou3;
						SwBoat1 = false;
						SwBoat2 = false;
						SwBoat3 = true;
						SwBoat4 = false;
						break;
					}
					case BoatH4:
					{
						Yb = 7;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD4AH - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD1A - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD1A; i++)
							for (int j = 0; j < Arr.M.XD4AH; j++)
								ArrAll[i][j] = Arr.M.D4AH[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD4AH - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou4;
						SwBoat1 = false;
						SwBoat2 = false;
						SwBoat3 = false;
						SwBoat4 = true;
						break;
					}
					case BoatV2:
					{
						Yb = 11;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD2AV - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD2AV; i++)
							for (int j = 0; j < Arr.M.XD1A; j++)
								ArrAll[i][j] = Arr.M.D2AV[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou2;
						SwBoat1 = false;
						SwBoat2 = true;
						SwBoat3 = false;
						SwBoat4 = false;
						break;
					}
					case BoatV3:
					{
						Yb = 9;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD3AV - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD3AV; i++)
							for (int j = 0; j < Arr.M.XD1A; j++)
								ArrAll[i][j] = Arr.M.D3AV[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou3;
						SwBoat1 = false;
						SwBoat2 = false;
						SwBoat3 = true;
						SwBoat4 = false;
						break;
					}
					case BoatV4:
					{
						Yb = 7;
						X1 = mousePos.X - Pos.You.LeftX - 1;
						X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 1;
						Y1 = mousePos.Y - Pos.You.UpY - 1;
						Y2 = mousePos.Y + Arr.M.YD4AV - Pos.You.UpY - 1;

						for (int i = 0; i < Arr.M.YD4AV; i++)
							for (int j = 0; j < Arr.M.XD1A; j++)
								ArrAll[i][j] = Arr.M.D4AV[i][j];
						if (mousePos.X % 2)
						{
							X1 = mousePos.X - Pos.You.LeftX - 2;
							X2 = mousePos.X + Arr.M.XD1A - Pos.You.LeftX - 2;
						}
						CountGlob = &Col.B.CountBoatYou4;
						SwBoat1 = false;
						SwBoat2 = false;
						SwBoat3 = false;
						SwBoat4 = true;
						break;
					}
					}

					x1 = X1;
					x2 = X2;
					y1 = Y1;
					y2 = Y2;

					bool Sw = true;

					for (int i = y1 - 1; i <= y2; i++)
					{
						for (int j = x1 - 1; j <= x2; j++)
							if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219 || x2 > 20 || y2 > 10)
							{
								Sw = false;
								break;
							}
						if (!Sw)
							break;
					}

					if (Sw && Col.B.CountBoatYou1 && SwBoat1 || Sw && Col.B.CountBoatYou2 && SwBoat2
						|| Sw && Col.B.CountBoatYou3 && SwBoat3 || Sw && Col.B.CountBoatYou4 && SwBoat4)
					{
						for (int i = y1; i < y2; i++)
							for (int j = x1; j < x2; j++)
							{
								Arr.M.YouArr[i][j] = ArrAll[i - y1][j - x1];
							}

						(*CountGlob)--;
						SwCountDel = true;

						XD1 = x1;
						XD2 = x2;
						YD1 = y1;
						YD2 = y2;
					}
					PrintArrYou(Arr, Pos.You);
					WriteInt(Xb, Yb, *CountGlob);
				}
			}

			if (mouseButtonState == FROM_LEFT_2ND_BUTTON_PRESSED && SwCountDel && ItsCountBoatYou(Col) && SwInfo)
			{
				CountL2But++;
				CountL2But % 2 ? t1L2B = clock() : t2L2B = clock();

				if (ItsAClick(t1L2B, t2L2B, 0.5))
				{
					for (int i = YD1; i < YD2; i++)
						for (int j = XD1; j < XD2; j++)
						{
							Arr.M.YouArr[i][j] = 0;
						}

					(*CountGlob)++;

					PrintArrYou(Arr, Pos.You);
					WriteInt(Xb, Yb, *CountGlob);
					SwCountDel = false;
				}
			}

			if (mouseButtonState == RIGHTMOST_BUTTON_PRESSED && SwInfo)
			{
				CountRightBut++;
				CountRightBut % 2 ? t1RB = clock() : t2RB = clock();

				if (ItsAClick(t1RB, t2RB, 0.1))
				{
					switch (Boat)
					{
					case BoatH2:
						Boat = BoatV2;
						break;
					case BoatH3:
						Boat = BoatV3;
						break;
					case BoatH4:
						Boat = BoatV4;
						break;
					case BoatV2:
						Boat = BoatH2;
						break;
					case BoatV3:
						Boat = BoatH3;
						break;
					case BoatV4:
						Boat = BoatH4;
						break;
					}
					PrintShipChoice(Boat, Arr, Sym.ForPole);
				}
			}
			if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePos.X >= Pos.Info.LeftX && mousePos.X <= Pos.Info.RightX && mousePos.Y >= Pos.Info.UpY && mousePos.Y <= Pos.Info.DownY)
			{
				CountInfo++;
				CountInfo% 2 ? t1Info = clock() : t2Info = clock();
				
				if (SwInfo && ItsAClick(t1Info, t2Info))
				{
					SetColor(LightCyan, Blue);
					PrintForInstShips(Pos, Sym.ForPole);
					SetColor(Black, Red);
					PrintInfo(Pos.Info, Sym.ForCell);
					Sleep(75);
					SetColor(Black, LightGray);
					PrintInfo(Pos.Info, Sym.ForCell);
					SetColor(LightCyan, Blue);
					WriteStr(23, 5, "Control is carried out with the mouse.");
					WriteStr(23, 6, "To install ships, hover the cursor on the field to install");
					WriteStr(23, 7, "ships and click the left mouse button.");
					WriteStr(23, 8, "The default is single deck ship.");
					WriteStr(23, 9, "To select the next ship, move the cursor over the ship and");
					WriteStr(23, 10, "click the left mouse button.");
					WriteStr(23, 11, "In order to change the location of the ship, right click.");
					WriteStr(23, 12, "There are two options: vertical and horizontal.");
					WriteStr(23, 13, "To cancel the last installation of the ship,");
					WriteStr(23, 14, "click on the central mouse button.");
				}
				else if (!SwInfo)
				{
					SetColor(LightCyan, Blue);
					PrintForInstShips(Pos, Sym.ForPole);
					SetColor(Black, Red);
					PrintInfo(Pos.Info, Sym.ForCell);
					Sleep(75);
					SetColor(Black, LightGray);
					PrintInfo(Pos.Info, Sym.ForCell);
					SetColor(LightCyan, Blue);
					PrintPole(Pos.You, Sym.ForPole, ParGlob);
					PrintArrYou(Arr, Pos.You);
					PrintShipsStat(S, Arr);
					WriteInt(49, 7, Col.B.CountBoatYou4);
					WriteInt(49, 9, Col.B.CountBoatYou3);
					WriteInt(49, 11, Col.B.CountBoatYou2);
					WriteInt(49, 13, Col.B.CountBoatYou1);
					PrintShipChoice(Boat, Arr, Sym.ForPole);
					SetColor(Black, LightGray);
					PrintOk(Pos.Ok, Sym.ForCell);
					PrintXX(Pos.XX, Sym.ForCell);
					SetColor(LightCyan, Blue);
					SwInfo = true;
					break;
				}
				SwInfo = false;


			}
			if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePos.X >= Pos.Ok.LeftX && mousePos.X <= Pos.Ok.RightX && mousePos.Y >= Pos.Ok.UpY && mousePos.Y <= Pos.Ok.DownY && SwInfo)
			{
				SetColor(Black, Red);
				PrintOk(Pos.Ok, Sym.ForCell);
				Sleep(75);
				SetColor(Black, LightGray);
				PrintOk(Pos.Ok, Sym.ForCell);
				AutoStateShipsPc(Arr, Col);

				int count1 = 0;
				int count2 = 0;
				for (int i = 0; i < Arr.M.YArr; i++)
					for (int j = 0; j < Arr.M.XArr; j++)
					{
						if (Arr.M.YouArr[i][j] == Arr.M.Active || Arr.M.YouArr[i][j] == Arr.M.Sank)
							count1++;
						if (Arr.M.PcArr[i][j] == Arr.M.Active || Arr.M.PcArr[i][j] == Arr.M.Sank)
							count2++;
					}
				if (count1 == 40 && count2 == 40)
				{
					T.Victory = false;
					Col.B.CountGlobShipsPc = 10;
					Col.B.CountGlobShipsYour = 10;
					return true;
				}
				else
					return false;
			}
			if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mousePos.X >= Pos.XX.LeftX && mousePos.X <= Pos.XX.RightX && mousePos.Y >= Pos.XX.UpY && mousePos.Y <= Pos.XX.DownY && SwInfo)
			{
				SetColor(Black, Red);
				PrintXX(Pos.XX, Sym.ForCell);
				Sleep(75);

				int countAllShipsYou = 0;
				int countAllShipsPc = 0;

				for (int i = 0; i < Arr.M.YArr; i++)
					for (int j = 0; j < Arr.M.XArr; j++)
					{
						Arr.M.YouArr[i][j] = tempArrYou[i][j];
						Arr.M.PcArr[i][j] = tempArrPc[i][j];

						if (Arr.M.YouArr[i][j] == Arr.M.Active || Arr.M.YouArr[i][j] == Arr.M.Sank)
							countAllShipsYou++;
						if (Arr.M.PcArr[i][j] == Arr.M.Active || Arr.M.PcArr[i][j] == Arr.M.Sank)
							countAllShipsPc++;
					}
				SetColor(Black, LightGray);
				PrintXX(Pos.XX, Sym.ForCell);

				Col.B.CountBoatPc1 = tempPc1;
				Col.B.CountBoatPc2 = tempPc2;
				Col.B.CountBoatPc3 = tempPc3;
				Col.B.CountBoatPc4 = tempPc4;
				Col.B.CountBoatYou1 = tempYou1;
				Col.B.CountBoatYou2 = tempYou2;
				Col.B.CountBoatYou3 = tempYou3;
				Col.B.CountBoatYou4 = tempYou4;
				T.Victory = tempVictory;
				Col.B.CountGlobShipsPc = tempCountGlobShipsPc;
				Col.B.CountGlobShipsYour = tempCountGlobShipsYour;

				if (countAllShipsPc == 40 && countAllShipsYou == 40)
					return true;
				else
					return false;
			}
		}
	}
}

bool AutoStateShipsPc(Mas &Arr, CountBoat &Col)
{
	bool vert;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;


	vert = rand() % 2;

	if (vert)
	{
		x1 = rand() % 19;
		y1 = rand() % 7;
		y2 = y1 + Arr.M.YD4AV;

		if (x1 % 2 != 0)
			x1 -= 1;
		x2 = x1 + Arr.M.XD1A;

		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				Arr.M.PcArr[i][j] = Arr.M.D4AV[i - y1][j - x1];
		Col.B.CountBoatPc4--;
	}
	else
	{
		x1 = rand() % 13;
		if (x1 % 2 != 0)
			x1 -= 1;
		x2 = x1 + Arr.M.XD4AH;

		y1 = rand() % 10;
		y2 = y1 + Arr.M.YD1A;
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				Arr.M.PcArr[i][j] = Arr.M.D4AH[i - y1][j - x1];
		Col.B.CountBoatPc4--;
	}


	do
	{
		vert = rand() % 2;
		if (vert)
		{
			x1 = rand() % 19;
			y1 = rand() % 8;
			y2 = y1 + Arr.M.YD3AV;

			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.PcArr[i][j] == 219/* || x2 > 20 || y2 > 10*/)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatPc3)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.PcArr[i][j] = Arr.M.D3AV[i - y1][j - x1];
				Col.B.CountBoatPc3--;
			}

		}
		else if (!vert)
		{
			x1 = rand() % 15;
			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD3AH;

			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.PcArr[i][j] == 219)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatPc3)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.PcArr[i][j] = Arr.M.D3AH[i - y1][j - x1];
				Col.B.CountBoatPc3--;
			}
		}
	} while (Col.B.CountBoatPc3);

	do
	{
		vert = rand() % 2;
		if (vert)
		{
			x1 = rand() % 19;
			y1 = rand() % 9;
			y2 = y1 + Arr.M.YD2AV;

			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.PcArr[i][j] == 219/* || x2 > 20 || y2 > 10*/)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatPc2)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.PcArr[i][j] = Arr.M.D2AV[i - y1][j - x1];
				Col.B.CountBoatPc2--;
			}

		}
		else if (!vert)
		{
			x1 = rand() % 17;
			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD2AH;

			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.PcArr[i][j] == 219)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatPc2)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.PcArr[i][j] = Arr.M.D2AH[i - y1][j - x1];
				Col.B.CountBoatPc2--;
			}
		}
	} while (Col.B.CountBoatPc2);

	do
	{
		vert = rand() % 2;
		if (vert)
		{
			x1 = rand() % 19;
			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.PcArr[i][j] == 219/* || x2 > 20 || y2 > 10*/)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatPc1)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.PcArr[i][j] = Arr.M.D1A[i - y1][j - x1];
				Col.B.CountBoatPc1--;
			}

		}
		else if (!vert)
		{
			x1 = rand() % 19;
			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.PcArr[i][j] == 219)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatPc1)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.PcArr[i][j] = Arr.M.D1A[i - y1][j - x1];
				Col.B.CountBoatPc1--;
			}
		}
	} while (Col.B.CountBoatPc1);

	return true;
}

bool AutoStateShipsUser(Mas &Arr, CountBoat &Col)
{
	bool vert;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;


	vert = rand() % 2;

	if (vert)
	{
		x1 = rand() % 19;
		y1 = rand() % 7;
		y2 = y1 + Arr.M.YD4AV;

		if (x1 % 2 != 0)
			x1 -= 1;
		x2 = x1 + Arr.M.XD1A;

		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				Arr.M.YouArr[i][j] = Arr.M.D4AV[i - y1][j - x1];
		Col.B.CountBoatYou4--;
	}
	else
	{
		x1 = rand() % 13;
		if (x1 % 2 != 0)
			x1 -= 1;
		x2 = x1 + Arr.M.XD4AH;

		y1 = rand() % 10;
		y2 = y1 + Arr.M.YD1A;
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				Arr.M.YouArr[i][j] = Arr.M.D4AH[i - y1][j - x1];
		Col.B.CountBoatYou4--;
	}


	do
	{
		vert = rand() % 2;
		if (vert)
		{
			x1 = rand() % 19;
			y1 = rand() % 8;
			y2 = y1 + Arr.M.YD3AV;

			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219/* || x2 > 20 || y2 > 10*/)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatYou3)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.YouArr[i][j] = Arr.M.D3AV[i - y1][j - x1];
				Col.B.CountBoatYou3--;
			}

		}
		else if (!vert)
		{
			x1 = rand() % 15;
			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD3AH;

			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatYou3)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.YouArr[i][j] = Arr.M.D3AH[i - y1][j - x1];
				Col.B.CountBoatYou3--;
			}
		}
	} while (Col.B.CountBoatYou3);

	do
	{
		vert = rand() % 2;
		if (vert)
		{
			x1 = rand() % 19;
			y1 = rand() % 9;
			y2 = y1 + Arr.M.YD2AV;

			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219/* || x2 > 20 || y2 > 10*/)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatYou2)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.YouArr[i][j] = Arr.M.D2AV[i - y1][j - x1];
				Col.B.CountBoatYou2--;
			}

		}
		else if (!vert)
		{
			x1 = rand() % 17;
			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD2AH;

			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatYou2)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.YouArr[i][j] = Arr.M.D2AH[i - y1][j - x1];
				Col.B.CountBoatYou2--;
			}
		}
	} while (Col.B.CountBoatYou2);

	do
	{
		vert = rand() % 2;
		if (vert)
		{
			x1 = rand() % 19;
			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219/* || x2 > 20 || y2 > 10*/)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatYou1)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.YouArr[i][j] = Arr.M.D1A[i - y1][j - x1];
				Col.B.CountBoatYou1--;
			}

		}
		else if (!vert)
		{
			x1 = rand() % 19;
			if (x1 % 2 != 0)
				x1 -= 1;
			x2 = x1 + Arr.M.XD1A;

			y1 = rand() % 10;
			y2 = y1 + Arr.M.YD1A;

			bool Sw = true;
			for (int i = y1 - 1; i <= y2; i++)
			{
				for (int j = x1 - 1; j <= x2; j++)
					if (j >= 0 && j <= 19 && Arr.M.YouArr[i][j] == 219)
					{
						Sw = false;
						break;
					}
				if (!Sw)
					break;
			}
			if (Sw && Col.B.CountBoatYou1)
			{
				for (int i = y1; i < y2; i++)
					for (int j = x1; j < x2; j++)
						Arr.M.YouArr[i][j] = Arr.M.D1A[i - y1][j - x1];
				Col.B.CountBoatYou1--;
			}
		}
	} while (Col.B.CountBoatYou1);

	return true;
}

bool AutoStateShips(Coor &Pos, GlobPar &ParGlob, Symbol &Sym, Mas &Arr, CountBoat &Col, Turn &T, Shot &G)
{
	DWORD dwMode, dwNumRead;
	dwMode = ENABLE_MOUSE_INPUT;
	INPUT_RECORD irInBuf[128];
	COORD mousePos;
	DWORD mouseButtonState;

	SetColor(Yellow, Black);
	PrintInstallShips(Pos.InstShBut, Sym.ForCell);
	SetColor(LightCyan, Blue);
	PrintForInstShips(Pos, Sym.ForPole);
	PrintPole(Pos.You, Sym.ForPole, ParGlob);
	SetColor(Black, LightGray);
	PrintOk(Pos.Ok, Sym.ForCell);
	PrintXX(Pos.XX, Sym.ForCell);
	PrintNext(Pos.Next, Sym.ForCell);

	clock_t t1Next = 0;
	clock_t t2Next = 0;
	int countNext = 0;
	int tempArrYou[10][20] = {};
	int tempArrPc[10][20] = {};
	int tempYou1 = Col.B.CountBoatYou1;
	int tempYou2 = Col.B.CountBoatYou2;
	int tempYou3 = Col.B.CountBoatYou3;
	int tempYou4 = Col.B.CountBoatYou4;
	int tempPc1 = Col.B.CountBoatPc1;
	int tempPc2 = Col.B.CountBoatPc2;
	int tempPc3 = Col.B.CountBoatPc3;
	int tempPc4 = Col.B.CountBoatPc4;
	bool tempVictory = T.Victory;
	int tempCountGlobShipsPc = Col.B.CountGlobShipsPc;
	int tempCountGlobShipsYour = Col.B.CountGlobShipsYour;


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
		{
			tempArrYou[i][j] = Arr.M.YouArr[i][j];
			tempArrPc[i][j] = Arr.M.PcArr[i][j];
		}

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
		
				if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
					mousePos.X >= Pos.Next.LeftX && mousePos.X <= Pos.Next.RightX
					&& mousePos.Y >= Pos.Next.UpY && mousePos.Y <= Pos.Next.DownY)
				{
					SetColor(Black, Red);
					PrintNext(Pos.Next, Sym.ForCell);
					Sleep(75);
					SetColor(Black, LightGray);
					PrintNext(Pos.Next, Sym.ForCell);

					for (int i = 0; i < 10; i++)
						for (int j = 0; j < 20; j++)
							Arr.M.YouArr[i][j] = 0;
					Col.B.CountBoatYou1 = 4;
					Col.B.CountBoatYou2 = 3;
					Col.B.CountBoatYou3 = 2;
					Col.B.CountBoatYou4 = 1;

					AutoStateShipsUser(Arr, Col);
					SetColor(LightCyan, Blue);
					PrintArrYou(Arr, Pos.You);
				}

				if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
					mousePos.X >= Pos.Ok.LeftX && mousePos.X <= Pos.Ok.RightX
					&& mousePos.Y >= Pos.Ok.UpY && mousePos.Y <= Pos.Ok.DownY)
				{
					SetColor(Black, Red);
					PrintOk(Pos.Ok, Sym.ForCell);
					Sleep(75);
					SetColor(Black, LightGray);
					PrintOk(Pos.Ok, Sym.ForCell);

					for (int i = 0; i < 10; i++)
						for (int j = 0; j < 20; j++)
							Arr.M.PcArr[i][j] = 0;

					Col.B.CountBoatPc4 = 1;
					Col.B.CountBoatPc3 = 2;
					Col.B.CountBoatPc2 = 3;
					Col.B.CountBoatPc1 = 4;

					AutoStateShipsPc(Arr, Col);

					int count1 = 0;
					int count2 = 0;

					for (int i = 0; i < 10; i++)
						for (int j = 0; j < 20; j++)
						{
							if (Arr.M.YouArr[i][j] == Arr.M.Active || Arr.M.YouArr[i][j] == Arr.M.Sank)
								count1++;
							if (Arr.M.PcArr[i][j] == Arr.M.Active || Arr.M.PcArr[i][j] == Arr.M.Sank)
								count2++;
						}
					if (count1 == 40 && count2 == 40)
					{
						T.Victory = false;
						Col.B.CountGlobShipsPc = 10;
						Col.B.CountGlobShipsYour = 10;
						return true;
					}
					else
						return false;
				}

				if (mouseButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
					mousePos.X >= Pos.XX.LeftX && mousePos.X <= Pos.XX.RightX
					&& mousePos.Y >= Pos.XX.UpY && mousePos.Y <= Pos.XX.DownY)
				{
					SetColor(Black, Red);
					PrintXX(Pos.XX, Sym.ForCell);
					Sleep(75);
					SetColor(Black, LightGray);
					PrintXX(Pos.XX, Sym.ForCell);

					int count3 = 0;
					int count4 = 0;

					for (int i = 0; i < 10; i++)
						for (int j = 0; j < 20; j++)
						{
							Arr.M.YouArr[i][j] = tempArrYou[i][j];
							Arr.M.PcArr[i][j] = tempArrPc[i][j];

							if (Arr.M.YouArr[i][j] == Arr.M.Active || Arr.M.YouArr[i][j] == Arr.M.Sank)
								count3++;
							if (Arr.M.PcArr[i][j] == Arr.M.Active || Arr.M.PcArr[i][j] == Arr.M.Sank)
								count4++;
						}
					Col.B.CountBoatPc1 = tempPc1;
					Col.B.CountBoatPc2 = tempPc2;
					Col.B.CountBoatPc3 = tempPc3;
					Col.B.CountBoatPc4 = tempPc4;
					Col.B.CountBoatYou1 = tempYou1;
					Col.B.CountBoatYou2 = tempYou2;
					Col.B.CountBoatYou3 = tempYou3;
					Col.B.CountBoatYou4 = tempYou4;
					T.Victory = tempVictory;
					Col.B.CountGlobShipsPc = tempCountGlobShipsPc;
					Col.B.CountGlobShipsYour = tempCountGlobShipsYour;

					if (count3 == 40 && count4 == 40)
						return true;
					else
						return false;
				}
			}
			}
		}
	}
}

bool ItsButton(Coor &Pos, COORD & mousePos, int &ClickButton, bool &SwPrintMainMenu, Turn &T)
{
	if (mousePos.X <= Pos.MainMenu.RightX && mousePos.Y < Pos.MainMenu.DownY && !T.ImpSet)
	{
		ClickButton = MainMenu;
		return true;
	}
	if (mousePos.X >= Pos.OkImport.LeftX && mousePos.X <= Pos.OkImport.RightX && mousePos.Y >= Pos.OkImport.UpY && mousePos.Y <= Pos.OkImport.DownY && T.ImpSet)
	{
		ClickButton = OkImport;
		return true;
	}
	if (mousePos.X >= Pos.NoImport.LeftX && mousePos.X <= Pos.NoImport.RightX && mousePos.Y >= Pos.NoImport.UpY && mousePos.Y <= Pos.NoImport.DownY && T.ImpSet)
	{
		ClickButton = NoImport;
		return true;
	}
	if (mousePos.X >= Pos.InstShBut.LeftX && mousePos.X <= Pos.InstShBut.RightX	&& mousePos.Y >= Pos.InstShBut.UpY && mousePos.Y <= Pos.InstShBut.DownY && SwPrintMainMenu)
	{
		ClickButton = InstallShips;
		return true;
	}
	if (mousePos.X >= Pos.Exit.LeftX && mousePos.X <= Pos.Exit.RightX && mousePos.Y >= Pos.Exit.UpY && mousePos.Y <= Pos.Exit.DownY && SwPrintMainMenu)
	{
		ClickButton = Exit;
		return true;
	}
	if (mousePos.X >= Pos.Manual.LeftX && mousePos.X <= Pos.Manual.RightX && mousePos.Y >= Pos.Manual.UpY && mousePos.Y <= Pos.Manual.DownY && SwPrintMainMenu)
	{
		ClickButton = Manual;
		return true;
	}
	if (mousePos.X >= Pos.Auto.LeftX && mousePos.X <= Pos.Auto.RightX && mousePos.Y >= Pos.Auto.UpY && mousePos.Y <= Pos.Auto.DownY && SwPrintMainMenu)
	{
		ClickButton = Auto;
		return true;
	}
	if (mousePos.X >= Pos.XX.LeftX && mousePos.X <= Pos.XX.RightX && mousePos.Y >= Pos.XX.UpY && mousePos.Y <= Pos.XX.DownY && SwPrintMainMenu)
	{
		ClickButton = XX;
		return true;
	}
	if (mousePos.X >= Pos.Ok.LeftX && mousePos.X <= Pos.Ok.RightX && mousePos.Y >= Pos.Ok.UpY && mousePos.Y <= Pos.Ok.DownY && SwPrintMainMenu)
	{
		ClickButton = OK;
		return true;
	}
	if (mousePos.X >= Pos.GameMode.LeftX && mousePos.X <= Pos.GameMode.RightX && mousePos.Y > Pos.GameMode.UpY && mousePos.Y < Pos.GameMode.DownY && T.SwGameModeAll && T.SwYourShot && !T.Victory)
	{
		ClickButton = GameMode;
		return true;
	}
	else
		return false;
}

bool ItsAClick(clock_t &t1, clock_t &t2, double t)
{
	return abs((double)(t2 - t1) / CLOCKS_PER_SEC) > t;
}

bool ItSClickOk(Cell &Ok, COORD &mP)
{
	if (mP.X <= Ok.RightX && mP.X >= Ok.LeftX && mP.Y >= Ok.UpY && mP.Y <= Ok.DownY)
		return true;
	else
		return false;
}

bool ItSClickXX(Cell &XX, COORD &mP)
{
	if (mP.X <= XX.RightX && mP.X >= XX.LeftX && mP.Y >= XX.UpY && mP.Y <= XX.DownY)
		return true;
	else
		return false;
}

bool ItsADeckTrue(COORD &mousePos, D &S)
{
	if (mousePos.X >= S.Sh1.LeftX && mousePos.X <= S.Sh1.RightX && mousePos.Y == S.Sh1.UpY
		|| mousePos.X >= S.Sh2H.LeftX && mousePos.X <= S.Sh2H.RightX && mousePos.Y >= S.Sh2H.UpY && mousePos.Y <= S.Sh2H.DownY
		|| mousePos.X >= S.Sh3H.LeftX && mousePos.X <= S.Sh3H.RightX && mousePos.Y >= S.Sh3H.UpY && mousePos.Y <= S.Sh3H.DownY
		|| mousePos.X >= S.Sh4H.LeftX && mousePos.X <= S.Sh4H.RightX && mousePos.Y >= S.Sh4H.UpY && mousePos.Y <= S.Sh4H.DownY)
		return true;
	else
		return false;
}

bool ItsCountBoatYou(CountBoat &Col)
{
	if (Col.B.CountBoatYou1 >= 0 && Col.B.CountBoatYou1 < 4 || Col.B.CountBoatYou2 >= 0 && Col.B.CountBoatYou2 < 3
		|| Col.B.CountBoatYou3 >= 0 && Col.B.CountBoatYou3 < 2 || Col.B.CountBoatYou4 >= 0 && Col.B.CountBoatYou4 < 1)
		return true;
	else
		return false;
}