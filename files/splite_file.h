#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

#define end '\n'
#define wait std::cin.get();

size_t sizeofFile(const char* filename) {
	std::ifstream ifs(filename, std::ios::ate | std::ios::binary);
	size_t sz = ifs.tellg();
	ifs.close();
	return sz;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//             SPLITE FILE IN MANY FILES WITH REDUCED SIZE
//             1. GENERATE FILES WITH EXT '.PART[N]'
//             2. NEED TO MAKE METAFILE FOR THESE GENERATED FILES
//                       NAMED 'metafiles.part0'
// 
///////////////////////////////////////////////////////////////////////////////////////////


void spliteFile(const std::string& filename, size_t size_parts ,const std::string& directory_name = "") {

	size_t sz = sizeofFile(filename.c_str());
	if (sz == -1) {
		std::cout << "Error when reading size fo file\n";
		return;
	}
	std::cout << "size of file " << filename << " is : " << sz << '\n';
	wait;
	// number of parts

	if (sz < size_parts) {
		std::cout << "size of partitioning is superior of size of file, please check file size\n";
		return;
	}

    size_t n = size_t(sz / size_parts) + size_t( !(sz % size_parts == 0) );

	std::cout << "number of files will be generated is " << n << '\n';
	if (n > 10) {
		std::cout << "number of file generated is more than 10, check output size\n";
		return;
	}
	wait;
	// Create directory name by default

	std::string dir_name{directory_name};
	if (dir_name == "") {
		dir_name = filename.substr(0, filename.find_first_of('.'));
	}

	if (!std::filesystem::create_directory(dir_name)) {
		std::cout << "is already created\n";
		//dir_name.clear();
	}
	else {
		std::cout << "succefull creation of directory " << dir_name << '\n';
	}

     dir_name = dir_name + "\\";
	// Start process file spliting

	std::ifstream ifs{ filename, std::ios::binary };

	if (!ifs.is_open()) {
		std::cout << "There error in opening file \n Filename : " << filename << '\n';
		return;
	}

	std::stringstream fileparts;  // should be add with dir_name \\

	for (int i = 0; i < n; i++)
	{
		fileparts << dir_name  << filename << ".part" << "[" << i + 1 << "]";
		std::cout << "process : " << fileparts.str() << '\n';
		
		std::ofstream ofs{ fileparts.str(), std::ios::binary };

		while (true) {
			char c{};
			ifs.get(c);
			if (ifs.eof()) break;
			ofs.put(c);
			if (ofs.tellp() == size_parts && i != n - 1) break;
		}

		ofs.close();
		std::cout << "file number[ " << i + 1 << "] [" << fileparts.str() << "]\n";
		fileparts.str(std::string{});
	}

	ifs.close();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//             ASSEMBLE FILES IN ONE FILE 
// 
///////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> getFilesDir(const std::string& directory) {

	// check if directory exist and is directory

	if (!std::filesystem::is_directory(directory)) {
		std::cout << directory << " is not directory " << end;
		return std::vector<std::string>{};
	}

	// making a list of every thing in directory

	std::vector<std::string> filenames;

	for (auto& dir : std::filesystem::directory_iterator{ directory })
	{
		std::cout << dir.path() << end;
		if (!std::filesystem::is_directory(dir))
		    filenames.push_back(dir.path().string());
	}

	return filenames;
}

std::vector<std::string> filterFiles(const std::vector<std::string>& vfiles, const string& ext) {
	// extension example '.exe' or '.part[*]'
}

void assembleFiles(const std::vector<std::string>& vFilenames) {

}

void assembleFiles(const std::string& directory) {

}