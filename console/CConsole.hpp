#pragma once
#pragma comment(lib, "winmm.lib")

#ifndef UNICODE 
#error  Please enable UNICODE for your compiler! VS: Project Properties -> General -> Advanced\
Character Set -> Use Unicode. Thanks! - Javidx9
#endif
/*
                   Color Console Windows
        Author : KADDA Aoues
        Date   : 13 / 03 / 2024

        typedef struct _CHAR_INFO {
            union {
                 WCHAR UnicodeChar;
                 CHAR  AsciiChar;
            } Char;
            WORD Attributes;
        } CHAR_INFO, *PCHAR_INFO;
*/

#include <Windows.h>
#include <include/console/win_utility.h>
#include <conio.h>
#include <thread>
#include <string>
#include <string_view>



namespace console {

    // Colour type 
    enum COLOUR
    {
        FG_BLACK = 0x0000,
        FG_DARK_BLUE = 0x0001,
        FG_DARK_GREEN = 0x0002,
        FG_DARK_CYAN = 0x0003,
        FG_DARK_RED = 0x0004,
        FG_DARK_MAGENTA = 0x0005,
        FG_DARK_YELLOW = 0x0006,
        FG_GREY = 0x0007, // Thanks MS :-/
        FG_DARK_GREY = 0x0008,
        FG_BLUE = 0x0009,
        FG_GREEN = 0x000A,
        FG_CYAN = 0x000B,
        FG_RED = 0x000C,
        FG_MAGENTA = 0x000D,
        FG_YELLOW = 0x000E,
        FG_WHITE = 0x000F,
        BG_BLACK = 0x0000,
        BG_DARK_BLUE = 0x0010,
        BG_DARK_GREEN = 0x0020,
        BG_DARK_CYAN = 0x0030,
        BG_DARK_RED = 0x0040,
        BG_DARK_MAGENTA = 0x0050,
        BG_DARK_YELLOW = 0x0060,
        BG_GREY = 0x0070,
        BG_DARK_GREY = 0x0080,
        BG_BLUE = 0x0090,
        BG_GREEN = 0x00A0,
        BG_CYAN = 0x00B0,
        BG_RED = 0x00C0,
        BG_MAGENTA = 0x00D0,
        BG_YELLOW = 0x00E0,
        BG_WHITE = 0x00F0,
    };

    // solid box
    enum PIXEL_TYPE
    {
        SOLID = 0x2588,
        THREEQUARTERS = 0x2593,
        HALF = 0x2592,
        QUARTER = 0x2591,
    };

    enum GLYPH_SOLID
    {
        SLD0 = 0x2580,
        SLD1 ,
        SLD2 ,
        SLD3 ,
        SLD4 ,
        SLD5 ,
        SLD6 ,
        SLD7 ,
        SLD8 ,
        SLD9 ,
        SLDA ,
        SLDB ,
        SLDC ,
        SLDD ,
        SLDE ,
        SLDF ,
    };


    // Pricipale Class Colored Console
    class Console {

    public:

        Console()
            :hConsole{GetStdHandle(STD_OUTPUT_HANDLE)}
            ,hConsoleIn{GetStdHandle(STD_INPUT_HANDLE)}
        {
        }

        int construct_console(int width, int hight, int fontw, int fonth) {

            // 1. Check valid handle to output standard console
            if (hConsole == INVALID_HANDLE_VALUE) {
                return Error(L"Bad Handle");
            }

            m_lx = width;
            m_ly = hight;

            // 2. set as small possible the size of windows before resize windows buffer 
            m_rectWindow = { 0,0,1,1 };
            SetConsoleWindowInfo(hConsole, TRUE, &m_rectWindow);

            // 3. set the size of screen buffer
            COORD  coord = { short(m_lx), short(m_ly) };
            if (!SetConsoleScreenBufferSize(hConsole, coord)) {
                return Error(L"SetConsoleScreenBufferSize");
            }


            // 4. Assign screen buffer to the console
            if (!SetConsoleActiveScreenBuffer(hConsole)) {
                Error(L"SetConsoleActiveScreenBuffer");
            }

            // 5. Set font size of screen buffer
            CONSOLE_FONT_INFOEX  cfi;
            cfi.cbSize = sizeof(cfi);
            cfi.nFont = 0;
            cfi.dwFontSize.X = fontw;
            cfi.dwFontSize.Y = fonth;
            cfi.FontFamily = FF_DONTCARE;
            cfi.FontWeight = FW_NORMAL;
            wcscpy_s(cfi.FaceName, L"Consolas");

            if (!SetCurrentConsoleFontEx(hConsole, false, &cfi)) {
                return Error(L"SetCurrentConsoleFontEx");
            }

            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
               return Error(L"GetConsoleScreenBufferInfo");
            }
            if (m_ly > csbi.dwMaximumWindowSize.Y)
                return Error(L"Screen Height / Font Height Too Big");
            if (m_lx > csbi.dwMaximumWindowSize.X)
                return Error(L"Screen Width / Font Width Too Big");

            // 6. Set physical Console Window Size
            m_rectWindow = { 0,0, (short)m_lx - 1, (short)m_ly - 1 };
            if (!SetConsoleWindowInfo(hConsole, TRUE, &m_rectWindow))
                return Error(L"SetConsoleWindowInfo");

            // Set flags to allow mouse input
            if (!SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
                return Error(L"SetConsoleMode");

            // 7. Allocate memory for screen buffer
            screen = new CHAR_INFO[m_lx * m_ly];
            memset(screen, 0, sizeof(CHAR_INFO) * m_lx * m_ly);

            // Hide Cursor
            setCursorVisibility(0);
            return 1;
        }

        void display() const {
            WriteConsoleOutput(hConsole, screen, { (short)m_lx, (short)m_ly }, { 0,0 },
                (SMALL_RECT*)&m_rectWindow);
        }

        void clear() {
            memset(screen, 0, sizeof(CHAR_INFO) * m_lx * m_ly);
        }

        void clear(COLOUR  bg_color) {
			for (int i = 0; i < m_lx; ++i)
				for (int j = 0; j < m_ly; ++j)
					draw(i, j, L' ', bg_color);

        }

        virtual void draw(int x, int y, short c = 0x2588, short color = 0x000F ) {

            if (x >= 0 && x < m_lx && y >= 0 && y < m_ly) {
                screen[y * m_lx + x].Char.UnicodeChar = c;
                screen[y * m_lx + x].Attributes = color;
            }
        }

        void text_at(int x, int y, std::wstring_view text, short color = 0x000F) {

            for (int i = 0; i < text.size(); ++i)
                draw(x + i, y, text[i], color);
        }

        ~Console() {
            delete[] screen;
            CloseHandle(hConsole);
            CloseHandle(hConsoleIn);
        }

        void setCursorVisibility(char visible) {
            CONSOLE_CURSOR_INFO      structCursorInfo;
            GetConsoleCursorInfo(hConsole, &structCursorInfo);  // Get current cursor size
            structCursorInfo.bVisible = (visible ? TRUE : FALSE);
            SetConsoleCursorInfo(hConsole, &structCursorInfo);
        }

        constexpr std::pair<int, int> get_size() {
            return std::pair<int, int>{m_lx, m_ly};
        }

    protected:

        void clip(int& x, int& y) {

            if (x < 0) x = 0;
            if (x >= m_lx) x = m_lx;
            if (y < 0) y = 0;
            if (y >= m_ly) y = m_ly;

        }

        int Error(const wchar_t* msg)
        {
            wchar_t buf[256];
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
            SetConsoleActiveScreenBuffer(hOriginalConsole);
            wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
            return 0;
        }

    private:
        int                m_lx;
        int                m_ly;

        SMALL_RECT         m_rectWindow;

        HANDLE             hConsole;
        HANDLE             hOriginalConsole;
        HANDLE             hConsoleIn;

        CHAR_INFO*         screen;

    };

}

using COLOR = console::COLOUR;
using GLYPH = console::GLYPH_SOLID;
