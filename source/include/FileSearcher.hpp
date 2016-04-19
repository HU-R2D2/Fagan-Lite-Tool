#ifndef DIRSEARCHER
#define DIRSEARCHER
#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <unistd.h>

using namespace std;

/*
 * ToDo
 * dirent.h (dir searcher, windows and unix)
 */
class FileSearcher
{
public:
	FileSearcher(string base_dir);
	~FileSearcher();
	vector<string> get_files();
private:

	string base_dir;
	vector<string> files;

	void read_folder_data(string base_dir);
	bool validate_and_add(string total_path);
	bool is_of_type(string total_path, string s);

};


#endif // DIRSEARCHER
