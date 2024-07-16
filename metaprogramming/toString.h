#pragma once
#include <string>
#include <sstream>
#include <vector>

template<typename T>
constexpr std::string to_string_(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

std::vector<std::string> to_string()
{
	return {};
}

template<typename P1,typename ... Param>
std::vector<std::string> to_string(const P1& p1, const Param& ... param)
{
	std::cout << "first aproach;\n";  
	std::vector<std::string> s;  
	s.push_back(to_string_(p1));  
	const auto remainder = to_string(param...);	  
	s.insert(s.end(), remainder.begin(), remainder.end());
	return s;
}

template<typename Tchar,typename Param>
std::basic_string<Tchar> to_String(const Param& param)
{
	std::cout << "Second aproach ;\n";
	
	std::basic_stringstream<Tchar> sstr;

	sstr << param;
	
	return sstr.str();
}

template<typename Tchar, typename...Param>
std::vector<std::basic_string<Tchar>> to_String(const Param& ...param) {

	return { to_String<Tchar>(param)... };

}