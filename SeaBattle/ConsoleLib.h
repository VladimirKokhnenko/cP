#pragma once
/*********************************************************************/
/*                                                                   */
/*    ConsoleLib [Release 2.1.1]                                     */
/*    Библиотека функций-оберток для работы с консолью               */
/*                                                                   */
/*    Copyright (с) 2006-2016, Дмитрий Барабаш                       */
/*                                                                   */
/*    E-mail:   dmitry@barabash.com                                  */
/*    Web:      http://itstep.barabash.com                           */
/*                                                                   */
/*********************************************************************/

#include <windows.h>

// Хендлы консоли
extern HANDLE hStdOut;
extern HANDLE hStdIn;

// Цвета
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

// Показываем/прячем текстовый курсор
void ShowCursor(bool visible);

// Устанавливает цвет символов и фона
void SetColor(ConsoleColor text, ConsoleColor background);

// Перемещает курсор в заданную позицию
void GotoXY(int X, int Y);

// Выводит заданную строку в заданную позицию
void WriteStr(int X, int Y, const char *Str);

// Выводит заданный символ начиная с заданной позиции
void WriteChar(int X, int Y, char Ch);
void WriteInt(int X, int Y, int Ch);
// Выводит указанное количество заданных символов начиная с заданной позиции
void WriteChars(int X, int Y, char Ch, unsigned Len);

// Меняет текстовые атрибуты, начиная с заданной позиции
void ChangeTextAttr(int X, int Y, ConsoleColor text, ConsoleColor background, unsigned Len);
