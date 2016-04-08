#ifndef DIRSEARCHER
#define DIRSEARCHER
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace format_tool
{
/*
 * ToDo
 * dirent.h (dir searcher, windows and unix)
 */
class FileSearcher
{
	private:
	FileSearcher(const FileSearcher& rhs);
	FileSearcher& operator=(const FileSearcher& rhs);
	vector<string> fileLocations;
public:	
	void getFiles(string location = "test", const ...) {
		std::cout << arg << " ";
	}
	FileSearcher();
	~FileSearcher();

};
}

#endif // DIRSEARCHER
