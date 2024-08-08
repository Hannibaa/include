#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <array>
#include <conio.h>
#include <include/console/escape_code.h>
#include <include/csvlib/csv_lib.hpp>





namespace csv_display {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    TOOLS
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace tools {

		// simple clamp function
		template<typename T>
			requires std::is_arithmetic_v<T>
		void clamp(T& x, const T& _max, const T& _min) {
			if (x < _min) x = _min;
			if (x > _max) x = _max;
		}


		// simple function to fix vector of string
		void fit_all_same(csv::csv_vecString& vec) {

			// get maximum length string
			auto max_size = (*std::max_element(vec.begin(), vec.end(),
				[](std::string str1, std::string str2) {
					return str1.size() < str2.size();
				})).size();

				for (auto& e : vec) e.resize(max_size, ' ');
		}

		// title for console
		void title(const wchar_t* text) {

			SetConsoleTitle(text);

		}


		// check if i in one of part of number
		template<size_t N>
		bool check(int i, const std::array<int, N>& _arr) {
			bool _check{ false };
			for (const auto& e : _arr)
				_check = _check || (i == e);

			return _check;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    END TOOLS
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


		// diplay vector of string as menu of chose 
	void display_vec(std::ostream& out,           // string stream
		const std::vector<std::string>& vec,			// vector of string or items
		int                             items_line, 	// number of items by line
		int                             select_item, 	// item in vector to be colored
		int                             _color, 		// color of bg selected item
		int							 fg_color = color::White)      // color of selected text
	{
		int i{};
		for (const auto& e : vec) {
			if (i != select_item)
				out << i << "|" << e << '\t';
			else
				out << _COLOR_BG256(_color)
				<< i << "|"
				<< _COLOR_FG256(fg_color) << e << RESETMODE << '\t';

			++i;
			if (i % items_line == 0) {
				out << END;
			}
		}
	}


	// templated and best one 
	template<size_t N>
	void display_columns(std::ostream& out,					   // string stream
		const std::vector<std::string>& vec,					   // vector of string
		int							  items_by_line,		   // number of items by line
		int							  select,				   // dynamic selection
		const std::array<int, N>& vselected,			   // static selections
		int							  bg_sel_color,			   // background of selected color
		int							  bg_color,				   // background color
		int							  fg_color = color::White) // foreground color
	{
		int i{};

		for (const auto& e : vec) {
			if (i == select)
				out << _COLOR_BG256(bg_sel_color)
				<< i << "|"
				<< _COLOR_FG256(fg_color) << e << RESETMODE << '\t';
			else
				if (tools::check(i, vselected)) {
					out << _COLOR_BG256(bg_color)
						<< i << "|"
						<< _COLOR_FG256(fg_color) << e << RESETMODE << '\t';
				}
				else {
					out << i << "|" << e << '\t';
				}

			++i;
			if (i % items_by_line == 0) {
				out << END;
			}
		}
	}



	// display vector of string horizontally with one high lighted
	void display_menu(const csv::csv_vecString& items,				// items of menu
		std::string_view          name,				// name of menu
		int                       selected,			// selected items with highlighted
		int						name_color,			// color of background name
		int						menu_color,			// color of all menu
		int						select_color,       // color for selected highlighted
		int                       x,					// coordinate x
		int                       y)					// coordinate y
	{
		int i{};

		std::cout << MOVETO(x, y - 1) << _COLOR_BG256(name_color) << name << RESETMODE;

		for (const auto& e : items) {

			if (i == selected)
				std::cout << MOVETO(x, y + i) << _COLOR_BG256(select_color) << e << RESETMODE;
			else
				std::cout << MOVETO(x, y + i) << _COLOR_BG256(menu_color) << e << RESETMODE;

			++i;
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//  SELECTION MENU   
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void select_field(const csv::CSV_DATA& csv, int(&n)[2]) {
		int j{};
		int k = 0;
		n[0] = 0;
		n[1] = 1;

		for (;;) {
			esc::cls();
			Print_(color::Red, "Names columns : ") << END;

			// selected field:
			//  
			Print_(color::Green, csv.column_names[n[0]]) << END;
			Print_(color::Green, csv.column_names[n[1]]) << END;

			display_vec(std::cout, csv.column_names, 4, j, color::Green);

			char  ch = _getch();
			if (ch == UP) {
				--j;
				tools::clamp(j, csv.column_count - 1, 0);
				ch = 0;
			}

			if (ch == DW) {
				++j;
				tools::clamp(j, csv.column_count - 1, 0);
				ch = 0;
			}

			if (ch == BSPACE) {
				n[k % 2] = j;
				++k;
			}

			if (ch == ESCAPE) break;
		}

	}

	template<size_t N>
	void select_columns(const csv::CSV_DATA& csv, std::array<int, N>& n,
		int sel_color, int elem_color, int fg_color)
	{
		int j{};
		int k{};

		for (;;) {
			esc::cls();

			display_columns(std::cout, csv.column_names, 4, j, n,
				sel_color, elem_color, fg_color);

			char ch = _getch();
			if (ch == UP) {
				--j;
				tools::clamp(j, csv.column_count - 1, 0);
				ch = 0;
			}

			if (ch == DW) {
				++j;
				tools::clamp(j, csv.column_count - 1, 0);
				ch = 0;
			}

			if (ch == BSPACE) {
				n[k % N] = j;
				++k;
			}

			if (ch == ESCAPE) break;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   OPTION MENU    
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void menu(const csv::csv_vecString& items,
		std::string_view        name_menu,
		int& selected,           // OUT Value.
		int                     name_color,
		int                     menu_color,
		int                     select_color,
		int x, int y) {

		int i{};
		for (;;) {
			display_menu(items, name_menu, i, name_color, menu_color, select_color, x, y);

			char ch = _getch();

			if (ch == CR) {
				selected = i;
				break;
			}

			if (ch == UP) --i;
			if (ch == DW) ++i;

			tools::clamp(i, int(items.size() - 1), 0);
		}

	}
}

namespace csv_d = csv_display;