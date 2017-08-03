#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> split_string(string&input_line);
string get_first_word(string&input_line);

string to_lower(string&str);

string get_file_fullpath(string&file_name);
string get_file_path(string&file_name);

bool check_file_ext(string file_name, string ext);
string set_file_ext(string file_name, string ext);
string swap_file_ext(string file_name, string ext_old, string ext_new);

#endif
