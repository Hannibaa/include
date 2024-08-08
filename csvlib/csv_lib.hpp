#pragma once
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <include/string/stringfunctionhelper.h>
#include <include/concepts/my_concepts.h>


#define   _end                               '\n'
#define   TITLES                             "Titles"
#define   NEW_LINE                           std::cout << _end
#define   WAIT                               std::cin.get()

/* Character values */
#define CSV_TAB    0x09
#define CSV_SPACE  0x20
#define CSV_CR     0x0d
#define CSV_LF     0x0a
#define CSV_COMMA  0x2c
#define CSV_QUOTE  0x22

#define DONT_STOP  -1

namespace csv {

	template<typename K , typename T>
	using csv_mapVec       =std::map<K,std::vector<T>>;

	using  csv_map       = std::map<std::string, std::vector<std::string>>;
	using  csv_vecString = std::vector<std::string>;

	/* csv main data structure *************************************************************/
	struct csv_data {
		csv_vecString									  field_names;
		csv_map											  data;
		int                                               nfield;
		int                                               ndata;
	};

	/* csv main data structure with maping integer field of columns ************************/
	struct CSV_DATA {
		csv_vecString                                  column_names;
		std::vector<std::vector<std::string>>          data;
		int                                            column_count;
		int                                            raw_count;
	};

	struct csv_option {
		size_t  max_line_load;
		char    delimiter_line;
		char    delimiter_value;
	};

	csv_option csv_all_option{
		-1,
		CSV_LF,
		CSV_COMMA
	};

	csv_option csv_space_all_option{
		-1,
		CSV_LF,
		CSV_SPACE
	};


	template<typename T>
	class CSV {
	public:

		CSV() = default;
		CSV(const std::string& file_name_csv);

	private:
		csv_data        _data;
	};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Helper functions  
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	void insert_to(std::vector<T>& vec, const std::vector<T>& in_vec) {
		vec.insert(vec.end(), in_vec.begin(), in_vec.end());
	}

	// counting char in string
	int count_char_in_string(const std::string& str, char c) {
		int count{};

		for (char ch : str) {
			if (ch == c) ++count;
		}

		return count;
	}

	// save char position in vector
	std::vector<size_t> get_char_position_in_file(const fs::path& file_name, char c, size_t npos = -1) {

		std::ifstream ifs(file_name, std::ios::in | std::ios::binary);

		if (!ifs.is_open()) {
			std::runtime_error("Error in opening file " + file_name.string());
		}

		size_t pos{};
		char ch;

		std::vector<size_t>  vpos;

		while (ifs.get(ch)) {
			if (ch == c) vpos.push_back(pos);

			++pos;
			if (pos > npos) break;
		}

		ifs.close();
		return vpos;
	}

	//  loading entire file in to string
	std::string load_file_to_string(const fs::path& file_name) {

		std::ifstream ifs(file_name, std::ios::in | std::ios::binary);

		if (!ifs.is_open()) {
			std::runtime_error("Error in opening file " + file_name.string());
			return {};
		}

		size_t file_size = fs::file_size(file_name);

		std::string buffer(file_size, '\0');
		ifs.read(&buffer[0], file_size);
		ifs.close();

		buffer.resize(ifs.gcount());

		return buffer;
	}

	// laoding partial file in to string
	std::string load_file_to_string(const fs::path& file_name, size_t size) {
		std::ifstream ifs{ file_name };

		if (!ifs.is_open()) {
			throw std::runtime_error("could not open file : " + file_name.string());
		}

		std::string buffer(size, '\0');
		ifs.read(&buffer[0], size * sizeof(char));
		buffer.resize(ifs.gcount());

		ifs.close();
		return buffer;
	}

	// laoding part of csv file to string starting from position 'position' with size 'size'
	std::string load_csv_file_to_string(const fs::path file_name, size_t position, size_t size)
	{
		std::ifstream  ifs(file_name, std::ios::in | std::ios::binary);

		if (!ifs.is_open()) {
			throw std::runtime_error("Error in opening file : " + file_name.string());
		}

		std::string first_line;
		std::getline(ifs, first_line);

		size_t fl_size = first_line.size();

		ifs.seekg(position);

		if (!ifs) {
			throw std::runtime_error("Failure to seek to the specifique position");
		}

		std::string buffer(size, '\0'); 


		ifs.read(&buffer[0], size); 
		buffer.resize(ifs.gcount());

		//check first if its complete line
		size_t first_crfl = buffer.find(CSV_LF);
		size_t last_crfl = buffer.rfind(CSV_LF);
		auto new_buf = first_line + buffer.substr(first_crfl, last_crfl - first_crfl - 1);

		return new_buf;//.substr(buffer.find('\n'));
	}

	// splite string into another string according to space
	std::vector<std::string> TextToWords(const std::string& text) {

		std::vector<std::string> vec_words;
		std::istringstream  istr_stream(text);

		for (std::string buf; istr_stream >> buf;) vec_words.push_back(buf);

		return vec_words;
	}

	int count_char_in_file(const fs::path& file_name, char Char) {

		std::ifstream ifs(file_name, std::ios::in | std::ios::binary);

		if (ifs.is_open()) {
			std::runtime_error("Error in opening file" + file_name.string());
		}

		int count{};
		char ch;

		while (ifs.get(ch)) {
			if (ch == Char) ++count;
		}

		return count;
	}

	void save_string_to_file(const std::string& str, const fs::path& file_name) {

		std::ofstream  ofs(file_name, std::ios::out | std::ios::binary);

		if (!ofs.is_open()) {
			std::runtime_error("Error in creating file " + file_name.string());
		}

		ofs.write(str.c_str(), str.size());

		if (ofs.fail()) {
			std::runtime_error("Failed to write to file " + file_name.string());
		}

		ofs.close();
	}

	void trait_string_remove_char(std::string& str, const std::string_view chars)
	{

	}

	void string_remove_crlf(std::string& str) {

		while (true) {
			if (*(str.end() - 1) == CSV_CR || *(str.end() - 1) == CSV_LF)
				str.pop_back();
			else
				break;
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    function that read lines and put is in vector of string.
	//    Loading the line by line of data:
	//    splite_string_in_vector()
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// If we need to read strings with delimiter space
	csv_vecString splite_string_in_vecstr(const std::string& str) {
		return TextToWords(str);
	}

	csv_vecString splite_string_in_vecstr(const std::string& str, char delimiter) {

		if (delimiter == ' ') {
			return splite_string_in_vecstr(str);
		}

		csv_vecString            tokens;
		std::stringstream		 ss(str);
		std::string				 token;

		while (std::getline(ss, token, delimiter)) {

			// check this token should not contain any CR or LF
			string_remove_crlf(token);

			tokens.push_back(token);
		}

		return tokens;
	}

	
	// inversing function of above vector of string put it in one string
	std::string put_vecstr_in_string(const vecString& vecstr, char delimiter) {
		
		std::stringstream ss;

		for (const auto& s : vecstr) {
			ss << s << delimiter;
		}
		auto str = ss.str();
		str.pop_back();
		return str;
	}

	// Push the value in a vector of parameter:
	// extract the value by using map :
    // value["Depth(ft)"] = 200.434 ;(float or double) 
    // value["Time"] = "01/27/2023 12:51:54" ; (as string) but should be convert to time_point
    // value["Time"] = time_point("01/27/2023 12:51:54"); std::chrono::time_point
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Load csv file in data structure csv_data
	//    This function load only what we have in string buffer
	//    
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	// get first line 
	// columns names in vector string. 
	csv_vecString  get_csv_columns_names(const fs::path& file_name, char delimiter) {

		std::ifstream ifs(file_name, std::ios::in | std::ios::binary);

		if (!ifs.is_open()) {
			std::runtime_error("Error in opening file " + file_name.string());
		}

		// get first line :
		std::string buffer;
		if (std::getline(ifs, buffer)) {
			ifs.close();
			return  splite_string_in_vecstr(buffer, delimiter);
		}
		else {
			throw std::runtime_error("Failed to read the first line from file");
		}
	}

	// get raws and columns number
	int get_csv_raw_number(const fs::path& file_name, char delimiter_line = '\n') {
		return count_char_in_file(file_name, delimiter_line) - 1;
	}

	// Load csv data from string.
	csv_data  load_csv_data(
		const std::string& text,
		char  delemiter_value = ',',
		char  delemiter_line = '\n'
	) {

		// 1. Extract all the lines in a vector of string
		auto vlines = splite_string_in_vecstr(text, delemiter_line);

		if (vlines.empty()) {
			std::cerr << "No Data!!";
			return{};
		}

		// 1.1 Extract columns names
		csv_vecString para_names = splite_string_in_vecstr(vlines[0], delemiter_value);
		int columns_count = para_names.size();

		// check last column to have some number of 
		if (splite_string_in_vecstr(vlines[vlines.size() - 1], delemiter_value).size() != columns_count) {
			vlines.pop_back();
		}

		// 2. define a map
		csv_map    values;

		// 3. Extract the value to a map
		for (int i = 1; i < vlines.size(); ++i) {
			auto v = splite_string_in_vecstr(vlines[i], delemiter_value);

			// put value in a vectors
			int j = 0;
			for (auto& e : v) {
				values[para_names[j]].push_back(e);
				++j;
			}

		}

		for (int k = 0; k < values[para_names[0]].size(); ++k)
			values["index"].push_back(std::to_string(k));

		csv_data   _csv_data;
		_csv_data.field_names = para_names;
		_csv_data.field_names.insert(_csv_data.field_names.begin(), "index");
		_csv_data.nfield = columns_count + 1;
		_csv_data.data = values;
		_csv_data.ndata = values[para_names[1]].size();

		if (_csv_data.data[para_names[0]].size() != _csv_data.data[para_names[1]].size())
		{
			_csv_data.data[para_names[0]].pop_back();
		}

		std::cout << "function success\n";
		return _csv_data;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////// 
	//   load csv data from string using option structure												//
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	CSV_DATA load_csv_data_op(
		const std::string& text,
		const csv_option& _option = csv_all_option
	) 
	{
		// 1. Extract all the lines in a vector of string
		auto vlines = splite_string_in_vecstr(text, _option.delimiter_line);

		if (vlines.empty()) {
			std::cerr << "No Data!!";
			return{};
		}

		CSV_DATA   csv;

		// 1.1 Extract parameter names
		csv.column_names = splite_string_in_vecstr(vlines[0], _option.delimiter_value);
		csv.column_count = csv.column_names.size();
		csv.data.resize(csv.column_count);

		// 3. Extract the value to a map
		for (int i = 1; i < vlines.size(); ++i) {
			auto v = splite_string_in_vecstr(vlines[i], _option.delimiter_value);

			// put value in a vectors
			int j = 0;
			for (auto& e : v) {
			    csv.data[j].push_back(e);
				++j;
			}

			if (i > _option.max_line_load) break;
		}
		
		csv.raw_count = csv.data[1].size();

		if (csv.data[0].size() != csv.data[1].size())
		{
			csv.data[0].pop_back();
		}

		std::cout << "function success\n";
		return csv;
	}

	void set_csv_option(csv_option& _option, char delimiter_line, char delimiter_value, size_t max_lines) {
		_option.delimiter_line = delimiter_line;
		_option.delimiter_value = delimiter_value;
		_option.max_line_load = max_lines;
	}

	// saving csv file into string after into file
	void save_csv_to_string(std::string& str_csv, const csv_data& csv) {

	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Printing functions 
	//    name space print
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace print {

		template<typename ...STR>
		void _print_impl(const STR& ...str) {
			// condition if there no parameter
			if (sizeof...(str) == 0) return;
			// expansion of cout function
			((std::cout << "|" << std::setw(str.size() > 8 ? str.size() : 8) << std::left << str), ...);
		}

		template<typename T1, typename T2>
		void _print(const T1& str1, int l1, const T2& str2, int l2) {
			std::cout << "[" << std::setw(l1) << std::left << str1 << "|"
				<< std::setw(1) << " "
				<< std::setw(l2) << str2 << "]";
		}


		template<typename ...Tint>
			requires my_metaprogramming::are_same_v<int, Tint...>
		void print_selected_fields(csv_data& map, int number_line, Tint... indexes) {
			csv_vecString  names = map.field_names;

			if (((indexes > map.nfield - 1) || ...)) {
				std::cerr << "Error in indexeing of field";
				return;
			}

			// print the titles that selected 
			(_print_impl(names[indexes]), ...);
			NEW_LINE;

			//_print_impl(map[names[2]][0], map[names[1]][0]);
			int i{ 0 };
			for (const auto& e : map.data[names[1]]) {
				(_print_impl(map.data[names[indexes]][i]), ...);
				++i;
				NEW_LINE;
				if (i % number_line == 0) {
					WAIT;
					// print the titles that selected 
					(_print_impl(names[indexes]), ...);
					NEW_LINE;

				}
			}
		}

		template<typename ...Tint>
			requires meta::are_same_v<int, Tint...>
		void print_selected_fields(CSV_DATA& csv, int number_line, Tint...indexes)
		{
			if (((indexes > csv.column_count - 1) || ...)) {
				std::cerr << "index over script vector";
				return;
			}

			(_print_impl(csv.column_names[indexes]), ...);
			NEW_LINE;

			int i{};
			for (const auto& e : csv.data[0]) {
				(_print_impl(csv.data[indexes][i]), ...);
				++i;
				NEW_LINE;
				if (number_line != DONT_STOP)
					if (i % number_line == 0) {
						WAIT;
						(_print_impl(csv.column_names[indexes]), ...);
						NEW_LINE;
					}
			}

		}

		template<typename T>
		void print_vector(const std::vector<T>& v, const std::string& param_name = "", int number = 10, int stop_line = 30) {
			int i{};
			int length = param_name.size();

			length = length > 0 ? length : 12;

			for (auto& e : v) {
				_print(i, 6, e, length);

				++i;
				if (i % number == 0) std::cout << '\n';
				if (i % stop_line == 0) {
					std::cin.get();
					std::cout << _end;
				}
			}
			std::cout << "\n";
		}

	}



    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Conversion functions   
	//    name space convertion
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace convertion {

		template<typename U, typename T>
		std::vector<U>  convert_vec_to(const std::vector<T>& vec, U(*f)(const T&)) {

			std::vector<U> vec2(vec.size(), U{});

			for (size_t i = 0; i < vec.size(); ++i) {
				vec2[i] = f(vec[i]);
			}

			return vec2;
		}

		template<typename U, typename T, typename Func_Conv>
		std::vector<U> convert_vec_to(const std::vector<T>& vec, Func_Conv f) {

			std::vector<U> vec2(vec.size(), U{});

			for (size_t i = 0; i < vec.size(); ++i) {
				vec2[i] = f(vec[i]);
			}

			return vec2;
		}
		
		float string_to_float(const std::string& str) {

			try {
				float x = std::stof(str);
				return x;
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Invalid Argument : " << e.what() << _end;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Out of range : " << e.what() << _end;
			}
		}


		std::chrono::system_clock::time_point 
			string_to_time_point(const std::string& str, const std::string& format)
		{
			std::istringstream iss(str);
			std::tm dt{};

			iss >> std::get_time(&dt, format.c_str());

			if (iss.fail()) {
				throw std::runtime_error("Failed to parse time string");
			}

			std::time_t time_tt = std::mktime(&dt);
			return std::chrono::system_clock::from_time_t(time_tt);
		}

		const char* format_time = "%m/%d/%Y %H:%M:%S";

		std::chrono::system_clock::time_point
			string_to_time_point1(const std::string& str) {
			return string_to_time_point(str, format_time);
		}
	}
} 