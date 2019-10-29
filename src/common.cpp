#include <common.hpp>

bool file_exists(const string &file_path){
	fstream file(file_path);
	return file.is_open();
}
