#pragma once
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <chrono>
#include <cctype>

#define end '\n'
#define wait std::cin.get()
#define print std::cout

using Byte = unsigned char;

/*
       READ TYPE DATA THAT IS POD OF LENGTH SIZEOF(T) 
       COMPARED TO OR CALCULATED HOW MUCH WE HAVE IN FILE


*/

// PERSE LINE BY LINE 
// CHECK THE LENGTH
// 

size_t sizeofFile(const std::string& filename) {

    return std::filesystem::file_size(filename);
}

// check byte or char in file light one

size_t checkByteInFile(const std::string& filename, char ch) {

    std::ifstream ifs{ filename, std::ios::binary };
    if (!ifs.is_open()) {
        print << "Error, check path file or... " << filename << end;
        return -1;
    }

    size_t count{};

    while (true) {
        char c{};
        ifs.get(c);
        // check end of file every time we access to file
        if (ifs.eof()) {
            print << "End of file reached " << ifs.tellg() << end;
            break;
        }
        // comparaison condition
        if (ch == c) {
            ++count;
            print << "get one at " << ifs.tellg() << " times : " << count << end;
        }


    }


    ifs.close();
    return count;
}

// Prototype of function very heavy one

std::vector<int> checkByteInFile1(const std::string& filename, char c) {
    
    std::ifstream ifs{ filename, std::ios::binary };

    if (!ifs.is_open()) {
        print << "Error in opening file " << filename << end;
        return std::vector<int>{};
    }

    std::vector<int> vPosition;

    int count{};

    while (true) {
        char ch{};
        int pos = ifs.tellg();
        ifs.get(ch);
        // check end of file every time we access to file
        if (ifs.eof()) {
            print << "End of file reached " << pos << end;
            break;
        }
        // comparaison condition
        if (ch == c) {
            ++count;
            vPosition.push_back(ifs.tellg());
            print << "get one at " << ifs.tellg() << " times : " << count << end;
        }
    }

    ifs.close();
    return vPosition;
}

// check a range of charactere

std::map<char,int> checkRangeCharInFile(const std::string& filename, char from = 'a', char to = 'z')
{
    std::ifstream ifs{ filename, std::ios::binary };
    if (!ifs.is_open()) {
        print << "Error, check path file or... " << filename << end;
        return std::map<char,int>{};
    }

    std::map<char, int> count;
   // std::vector<std::pair<size_t, char>> charcount;

    while (true) {
        char c{};
        ifs.get(c);
        // check end of file every time we access to file
        if (ifs.eof()) {
            print << "End of file reached " << ifs.tellg() << end;
            break;
        }
        // comparaison condition
        for (char ch = from; ch < to + 1; ch++)
        {
            if (ch == c) {
                count[ch]++;
                print << "get one at " << ifs.tellg() << " times : " << count[ch] << end;
                break;
            }
        }
    }
    
    ifs.close();
    return count;
}

// extract some section from fille of size sz and from position offset;
// and saved in other file name with specific extension extsec
// position start from 0;

void extractFromFile(const std::string& filename, size_t position, size_t size) {

    // check timing for any call of these function
    auto tp = std::chrono::steady_clock::now();

    size_t sz = std::filesystem::file_size(filename);

    if (sz == -1) {
        print << "error in file " << filename << end;
        return;
    }
    else if (sz < position) {
        print << "error in position value, greater than size of file \n";
        return;
    }
    else if (sz < size) {
        print << "error in size to be extracted, greater than size of file\n";
        return;
    }

    std::ifstream ifs{ filename, std::ios::binary };
    // check is open
    if (!ifs.is_open()) {
        print << "Error in opening file ...\n";
        return;
    }

    std::string tofile = filename + ".bin";
    
    std::ofstream ofs{ tofile, std::ios::binary };

    if (!ofs.is_open()) {
        print << "error in opening or creating " << tofile << end;
        ifs.close();
        return;
    }

    ifs.seekg(position);
    // iterate all size of input file
    for (size_t t = 0; t < size; t++) {
        char c{};
        ifs.get(c);
        if (ifs.eof()) {
            print << "file finished \n";
            break;
        }

        ofs.put(c);
    }

    print << "process is finished\n";


    ofs.close();
    ifs.close();

    auto d = std::chrono::duration<float>{ std::chrono::steady_clock::now() - tp };
    print << "duration is seconds : " << d.count() << end;
}

void ExtractAlphanumFromFile(const std::string& filename, const std::string& outputfile) {

    auto tp = std::chrono::steady_clock::now();

    std::ifstream ifs{ filename, std::ios::binary };

    if (!ifs.is_open()) {
        print << "error in opening file ... " << filename << end;
        return;
    }

    std::ofstream ofs{ outputfile, std::ios::binary };

    if (!ofs.is_open()) {
        print << "error in opening file ... " << outputfile << end;
        ifs.close();
        return;
    } 

    while (true) {
        char c{};
        ifs.get(c);

        if (ifs.eof()) {
            print << "end of file ..." << ifs.tellg() << end;
            break;
        }

        if ( std::isalnum(c) )
        ofs.put(c);
    }
    
    auto d = std::chrono::duration<float>{ std::chrono::steady_clock::now() - tp };

    print << "size fo output file : " << ofs.tellp() << end;
    print << "process finished take " << d.count() << " second \n";

    ifs.close();
    ofs.close();
    
}
