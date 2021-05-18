#pragma once
#include <iostream>
#include "ConsoleLib.h"

struct GlobPar 
{
	int SizeCol;
	int SizeLine;
	int HightPole;
	int LenPole;
};

struct Arr
{
	const int YArr = 10; 
	const int XArr = 20; 
	const int YD1A = 1; 
	const int XD1A = 2; 
	const int YD2AV = 2;
	const int YD3AV = 3;
	const int YD4AV = 4;
	const int XD2AH = 4;
	const int XD3AH = 6;
	const int XD4AH = 8;
	int YouArr[10][20];
	int PcArr[10][20];
	int D1A[1][2] = { {219, 219} };											
	int D2AV[2][2] = { {219, 219}, {219, 219} };							
	int D3AV[3][2] = { {219, 219}, {219, 219}, {219, 219} };				
	int D4AV[4][2] = { {219, 219}, {219, 219}, {219, 219}, {219, 219} };	
	int D2AH[1][4] = { 219, 219, 219, 219 };								
	int D3AH[1][6] = { 219, 219, 219, 219, 219, 219 };						
	int D4AH[1][8] = { 219, 219, 219, 219, 219, 219, 219, 219 };			
	const int Active = 219;
	const int Sank = 178;
	const int Missed = 177;

};

struct Mas
{
	Arr M;
};

struct Pole
{
	int LeftX;
	int RightX;
	int UpY;
	int DownY;
	int Len;
	int Hight;
};

struct SymChars
{
	char TopLeft;
	char TopRight;
	char MidLeft;
	char MidRight;
	char DownLeft;
	char DownRight;
	char VertCh;
	char HorCh;
	char Pusto;
};

struct Cell 
{
	int LeftX;
	int RightX;
	int UpY;
	int DownY;
	int WidthCell;
	int HeightCell;
};

struct Coor
{
	Cell MainMenu = { 0,19,0,3,19,3 };		// LeftX RightX UpY DownY WidthCell HeightCell
	Cell Info = { 84,88,1,3,4,3 };	
	Cell InstShBut = { 0,19,3,5,19,3 };		
	Cell Exit = { 0,19,6,8,19,3 };		
	Cell Ok = { 82,87,16,18,4,3 };			
	Cell OkImport = { 46,51,11,13,4,3 };
	Cell NoImport = { 59,64,11,13,4,3 };
	Cell XX = { 21,25,1,3,4,3 };			
	Cell Manual = { 20,39,3,5,19,3 };		
	Cell Auto = { 20,39,6,8,19,3 };			
	Cell Next = { 80,87,1,3,7,3 };
	Cell GameMode = { 61,80,5,16,20,12 };
	Pole You;
	Pole Pc;
	Pole ForInstShips;
	Pole ForChoice = { 67,78,7,14,11,8 };
	Pole Import = { 20,89,0,20,69,19 };
};

struct Symbol
{
	SymChars ForPole;
	SymChars ForCell;
};

struct Ships
{
	int LeftX;
	int RightX;
	int UpY;
	int DownY;
	int Hei;
	int Len;
	int Width;
	int CountDeck;
};

enum Boat
{
	Boat1 = 1,
	BoatV2 = 2,
	BoatV3 = 3,
	BoatV4 = 4,
	BoatH2 = 5,
	BoatH3 = 6,
	BoatH4 = 7
};

enum ButtonEnum
{
	MainMenu = 1,
	Menu = 2,
	File = 3,
	InstallShips = 4,
	Settings = 5,
	Exit = 0,
	OkImport = 6,
	NoImport = 7,
	Manual = 8,
	Auto = 9,
	XX = 10,
	OK = 11,
	GameMode = 12
};

struct D
{
	Ships Sh1; 
	Ships Sh2H;
	Ships Sh3H;
	Ships Sh4H;
	Boat BoatAll;
};

struct Warship
{
	int Deck1;
	int DeckVert2;
	int DeckVert3;
	int DeckVert4;
	int DeckHor2;
	int DeckHor3;
	int DeckHor4;
};

struct Turn
{
	bool SwGameModeAll;
	bool SwYourShot;
	bool SwForTurn2;
	bool SwForTurn3;
	bool SwForTurn4;
	bool Victory;
	bool ImpSet = false;
	ButtonEnum ButtonAll;
};

struct MyMousePos
{
	int LeftX;
	int RightX;
	int UpY;
	int DownY;
};

struct Count
{
	int CountBoatYou1 = 4;
	int CountBoatYou2 = 3;
	int CountBoatYou3 = 2;
	int CountBoatYou4 = 1;
	int CountBoatPc1 = 4;
	int CountBoatPc2 = 3;
	int CountBoatPc3 = 2;
	int CountBoatPc4 = 1;
	int CountGlobShipsPc;
	int CountGlobShipsYour;
};

struct CountBoat
{
	Count B;
};

struct ForShot
{
	int X = 100;
	int Y = 100;
};

struct Shot
{
	ForShot First;
	ForShot Second;
	ForShot Third;
	ForShot Fourth;
	bool Hit = false;
	int CountShotPc = 0;
};


