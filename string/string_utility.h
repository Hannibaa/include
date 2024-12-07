/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                        String  function  Library                          *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 * Under namespace : sfl                                                     *
 * URL :                                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/

/*
     namesspaces :
          conv : convertion between strings type, types ...
          splite : put string in some order, splite it ...
          type   : types defined for string


*/


#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>
#include <array>
#include <memory>
#include <filesystem>
#include <fstream>
#include <random>
#include <map>


namespace fs = std::filesystem;

// MACROS

#ifndef CHAR_DEFINITION
#define CHAR_DEFINITION

#define _END             '\n'
#define _BELL            '\a'
#define _TAB             '\t'
#define _VTAB            '\v'
#define _BACKSPACE       '\b'
#define _NEWPAGE         '\f'
#define _CR              '\r'
#define _LF				 '\n'
#define _ESCAPE          '\x1b'
#define _DELETE          '\x7F'
#define _CTRL_C          (char(3))

#endif // !CHAR_DEFINITION

#ifdef END
#undef END
#endif // END


namespace sfl {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////// 
	/////////////////    TYPES AND CONSTANT PREDIFINED IN STRING LIBRARY
	///////////////// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline namespace type {
        
        template<typename Char = char>
        using vecString = std::vector<std::basic_string<Char>>;
        
        using vecPath   = std::vector<fs::path>;
        
        using uchar = unsigned char;
        using byte = unsigned char;
        using uint = unsigned int;
        using ushort = unsigned short;

		// enum define just from where we can applay 
		enum FROM {
			BEGINING,
			END,
			BEGINING_AND_END,
			ANY
		};

		// Templated functions :
		enum class CONV_OPTION {
			IGNOR_HI_CHAR,
			ADD_SIGNEFICANT_CHAR,
			ADD_ALL_CHAR
		};


    } // namespace type


	namespace var {

		constexpr size_t npos = std::string::npos;

		const char* alphabet = "";
		const char* numbers = "0123456789";
		const char* alphanum = "";

	}




    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////// 
    /////////////////    CONVERTION FUNCTION   
    ///////////////// 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    namespace conv {

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 
		//    Convert String element to vector element
		// 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		// function that take string<Char> and converted to vector<Char> :
		// using std::copy function
		template<typename TChar>
		std::vector<TChar>  to_vector(const std::basic_string<TChar>& String) {

			std::vector<TChar> vec(String.size());
			std::copy(String.begin(), String.end(), vec.begin());
			return vec;
		}

		// function that take string<Char> and converted to vector<Char> :
		// using memcpy function
		template<typename TChar>
		std::vector<TChar>  to_vector_memcpy(const std::basic_string<TChar>& String) {

			std::vector<TChar> vec(String.size());
			std::memcpy(vec.data(), String.data(), String.size() * sizeof(TChar));
			return vec;
		}

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 
        //    CONVERTION BETWEEN CHAR TO WCHAR AND WCHAR TO CHAR FUNCTIONS    
        // 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

		auto wchart_to_char(wchar_t wch) {

			std::array<char, 2> ch;

			ch[0] = static_cast<char>(wch & 0x00ff);
			ch[1] = static_cast<char>((wch & 0xff00) >> 8);

			return ch;
		}

		bool is_wchart_fit_char(wchar_t wch) {
			return (wch & 0xff00) == 0;
		}

		// this function return true if inverse convertible between char and wchar.
		bool is_wstr_convertible_str(const std::wstring& wstr) {

			for (const auto& w : wstr)
			{
				if (!is_wchart_fit_char(w)) {
					return false;
				}
			}

			return true;
		}

		// this here will ignore hi char in wchar_t. 
		std::string wstr_to_str(const std::wstring& wstr) {

			std::string str(wstr.size(), '\0');

			for (int i = 0; i < wstr.size(); ++i) {
				str[i] = static_cast<char>(wstr[i] & 0x00ff);
			}
			return str;
		}

		std::string wstr_to_str2(const std::wstring& wstr) {
			return std::string(wstr.begin(), wstr.end());
		}

		// string to wstring
		std::wstring str_to_wstr(const std::string& str) {
			std::wstring wstr(str.size(), L'\0');

			for (int i = 0; i < str.size(); ++i) {
				wstr[i] = static_cast<wchar_t>(str[i]);
			}
			return wstr;
		}

		std::string wstr_to_str3(const std::wstring& wstr) {
			std::string str;
			str.reserve(wstr.size() * sizeof(std::wstring::value_type));

			for (const auto& e : wstr) {
				str.push_back(static_cast<char>(e & 0x00ff));

				if ((e & 0xff00) != 0x0000)
					str.push_back(static_cast<char>((e & 0xff00) >> 8));
			}

			return str;
		}

		std::string wstr_to_str4(const std::wstring& wstr) {
			std::string str;
			str.reserve(wstr.size() * sizeof(std::wstring::value_type));

			for (const auto& e : wstr) {
				str.push_back(static_cast<char>(e & 0x00ff));
				str.push_back(static_cast<char>((e & 0xff00) >> 8));
			}
			return str;
		}


		template<CONV_OPTION Version>
		constexpr std::string wstr_to_str(const std::wstring& wstr) {
			std::string str;
			if constexpr (Version == CONV_OPTION::IGNOR_HI_CHAR)
				str = wstr_to_str(wstr);
			else if constexpr (Version == CONV_OPTION::ADD_SIGNEFICANT_CHAR)
				str = wstr_to_str2(wstr);
			else if constexpr (Version == CONV_OPTION::ADD_ALL_CHAR)
				str = wstr_to_str3(wstr);
			else {
				std::cerr << "Error of version";
				return {};
			}

			return str;
		}


		// conversion of vector of Tchar to basic_string<Tchar>
		template<typename Tchar>
		std::basic_string<Tchar> vector2string(const std::vector<Tchar>& buffer)
		{
			return std::basic_string<Tchar>(buffer.begin(), buffer.end());
		}

	}// namespace conv : conversion




	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////// 
	/////////////////       FUNCTIONS OF STRING TRAITMENTS
	///////////////// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace trait {

		// general function
		template<typename Char, FROM from_where>
		void remove_char(std::basic_string<Char>& str, int (*is_function)(int))
		{
			if (str.empty()) return;
			int i{};

			if constexpr (from_where == FROM::BEGINING)
			{
				while (is_function(str[i])) {
					++i;
					if (i > str.size()) break;
				}
				str = str.substr(i);
			}
			else
				if constexpr (from_where == FROM::END)
				{
					while (is_function(str[str.size() - 1])) {
						str.pop_back();
						if (str.empty()) return;
					}
				}
				else
					if constexpr (from_where == FROM::BEGINING_AND_END) 
					{
						remove_char<Char, FROM::BEGINING>(str, is_function);
						remove_char<Char, FROM::END>(str, is_function);
					}
					else
						if constexpr (from_where == FROM::ANY)
						{
							std::basic_string<Char> tempstr = str;
							str.clear(); str.reserve(tempstr.size());
							for (auto& e : tempstr) {
								if (!is_function(e)) str.push_back(e);
							}
							str.shrink_to_fit();
						}


		}

		// returning a string 
		template<typename Char, FROM from_where>
		constexpr std::basic_string<Char> remove_char2(std::basic_string<Char> str, int (*is_function)(int))
		{
			if (str.empty()) return {};
			int i{};

			if constexpr (from_where == FROM::BEGINING)
			{
				while (is_function(str[i])) {
					++i;
					if (i > str.size()) break;
				}
				str = str.substr(i);
			}
			else
				if constexpr (from_where == FROM::END)
				{
					while (is_function(str[str.size() - 1])) {
						str.pop_back();
						if (str.empty()) return;
					}
				}
				else
					if constexpr (from_where == FROM::BEGINING_AND_END)
					{
						remove_char<Char, FROM::BEGINING>(str, is_function);
						remove_char<Char, FROM::END>(str, is_function);
					}
					else
						if constexpr (from_where == FROM::ANY)
						{
							std::basic_string<Char> tempstr = str;
							str.clear(); str.reserve(tempstr.size());
							for (auto& e : tempstr) {
								if (!is_function(e)) str.push_back(e);
							}
							str.shrink_to_fit();
						}

			return str;
		}


		// remove char from string 
		void remove_char_any(std::string& str, char c = ' ') {
			std::string tempstr = str;

			str.clear(); str.reserve(tempstr.size());

			for (auto& e : str) {
				if (e == c) str.push_back(e);
			}

			str.shrink_to_fit();
		}

		void remove_char_any(std::string& str, int(*is_function)(int)) {
			std::string tempstr = str;

			str.clear(); str.reserve(tempstr.size());

			for (auto& e : str) {
				if (is_function(e)) str.push_back(e);
			}

			str.shrink_to_fit();

		}

		// romove successive char(blank) from end of string
		void remove_char_end(std::string& str, char Nchar = ' ') {
			if (str.empty()) return;

			while (str[str.size() - 1] == Nchar) {
				str.pop_back();
				if (str.empty()) return;
			}
		}

		void remove_char_end(std::string& str, int(*is_function)(int))
		{
			if (str.empty()) return;

			while ( is_function(str[str.size() - 1]) ) {
				str.pop_back();
				if (str.empty()) return;
			}
		}

		// remove successive char(blank) from the begining of string
		void remove_char_beg(std::string& str, char Nchar = ' ') {
			int i = 0;

			while (str[i] == Nchar) {
				++i;
				if (i > str.size()) break;
			}

			str = str.substr(i);
		}

		void remove_char_beg(std::string& str, int (*is_function)(int))
		{
			int i = 0;

			while ( is_function(str[i]) ) {
				++i;
				if (i > str.size()) break;
			}

			str = str.substr(i);
		}

		// remove sccessive char(blank) from end and begining of string
		void remove_char_eb(std::string& str, char Nchar = ' ') {
			remove_char_beg(str,Nchar);
			remove_char_end(str,Nchar);
		}

		void remove_char_eb(std::string& str, int(*is_function)(int))
		{
			remove_char_beg(str, is_function);
			remove_char_end(str, is_function);
		}

		// general function that remove all blank like CR LF Space Tab 

		template<FROM where> 
		void remove_space(std::string& str) {

			if constexpr (where == FROM::BEGINING) {
				remove_char_beg(str, std::isspace);
			}
			else
				if constexpr (where == FROM::END) {
					remove_char_end(str, std::isspace);
				}
				else
					if constexpr (where == FROM::BEGINING_AND_END) {
						remove_char_eb(str, std::isspace);
					}
					else
						if constexpr (where == FROM::ANY) {
							remove_char_any(str, std::isspace);
						}

		}


		// remove blank from begining and end of strings

		void remove_blank_eb(std::string& str) {
			remove_char_eb(str, std::isblank);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//                   REVERSE STRING AND RANDOM ARRANGEMENT OF STRING
		//
		///////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename Tchar>
		std::basic_string<Tchar> reverse_string(std::basic_string<Tchar> str) {
			int l = str.size();
			for (int i = 0; i < l / 2; i++) {
				std::swap(str[i], str[l - i - 1]);
			}

			return str;
		}


	} // namespace trait

	// TODO : string transformation and input and outpu
	template<typename STRING, typename STRINGS>
	void get_lines(const STRING&, STRINGS&) {

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////// 
	/////////////////    LOGIC AND BINARY RELATION  
	///////////////// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace check {

		template<char ...ch>
		constexpr int is_one_of(int c) {
			return ((c == ch) || ...);
		}
		
		template<typename Char, Char...ch>
		constexpr int is_one_of(int c) {
			return ((c == static_cast<int>(ch)) || ...);
		}


	} // namespace check : checking of string 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////// 
    /////////////////    COMPARAISON 
    ///////////////// 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace comp {



	} // namespace comp : comparaison

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////// 
    /////////////////    STRING GENERATOR  
    ///////////////// 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace generator {



		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 
		//    RANDOM GENERATOR
		// 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		namespace rand {


		} // namespace rand : random


	} // namespace generator
    
}// namespace stl : string function library