/*
								Colored Console Utility 
								Author : Aoues Kadda
								Date   : 26 / 06 / 2024



*/

#pragma once
#include <include/console/CConsole.hpp>
#include <include/maths/Geometry.h>

#define CAT(x,n)    x##n

// Making object console 
// after in application we will constructed
console::Console     _console;


namespace console {


	// We will make also globle variable Need it for game programming
	// 
	float				 fps{ 1.f };		 // frame per seconds = 1.f / elaps
	float				 elaps{};			 // elapsed time
	float				 Dt60{ 1.5f };       // dalta time in 60 seconds
	float				 Dtime{};            // Dt = Dt60 * 60.f / fps;
	wchar_t				 title[256]{};       // buffer for title 

	// Drawing methode defined here
	void draw_box(int x, int y, int lx, int ly, int _color)
	{
		_console.draw(100, 10);

		for (int i = x; i < x + lx + 1; ++i) {
			_console.draw(i, y, 0x2588, _color);
			_console.draw(i, y + ly, 0x2588, _color);
		}

		for (int j = y + 1; j < y + ly + 1; ++j) {
			_console.draw(x, j, 0x2588, _color);
			_console.draw(x + lx, j, 0x2588, _color);
		}
	}

	void draw_box(const geom2d::iRect& rect, int _color) {
		draw_box(rect.x, rect.y, rect.dx, rect.dy, _color);
	}

	template<typename TRect, typename T>
	requires std::is_arithmetic_v<T> || std::is_enum_v<T> && 
	         std::is_arithmetic_v<typename TRect::value_type>
	void draw_box(const TRect& rect,T _color) {
		draw_box(
			static_cast<int>(rect.x),
			static_cast<int>(rect.y),
			static_cast<int>(rect.dx),
			static_cast<int>(rect.dy), static_cast<int>(_color));
	}

	void draw_box(const geom2d::iPoint2d& p1, const geom2d::iPoint2d& p2, int _color) {
		draw_box(geom2d::iRect{ p1,p2 }, _color);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    Functions related to console programming in windows
// 	   typedef
//      struct
//      	_
//      	CONSOLE_SCREEN_BUFFER_INFO
//      {
//      	COORD dwSize;
//      	COORD dwCursorPosition;
//      	WORD wAttributes;
//      	SMALL_RECT srWindow;
//      	COORD dwMaximumWindowSize;
//      } CONSOLE_SCREEN_BUFFER_INFO;
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::pair<COORD, SMALL_RECT> get_console_size() {
		int      size[4];
		CONSOLE_SCREEN_BUFFER_INFO		csbi{};
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
			return std::make_pair(csbi.dwSize, csbi.srWindow);
		}
		else {
			std::cerr << "Error : GetConsoleScreenBufferInfo \n";
			return {};
		}

	}


}

