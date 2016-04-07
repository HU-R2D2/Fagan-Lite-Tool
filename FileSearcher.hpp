#ifndef DIRSEARCHER
#define DIRSEARCHER
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace format_tool
{
class FileSearcher
{
	private:

	FileSearcher(const FileSearcher& rhs);
	FileSearcher& operator=(const FileSearcher& rhs);
	vector<string> fileLocations;
public:	
	void getFiles();
	template<typename base_location, typename ... Strings>
	void getFiles(base_location arg, const Strings&... rest) {
		std::cout << arg <<" ";
		Output(rest...);
	}
	FileSearcher();
	~FileSearcher();

};
}

#endif // DIRSEARCHER
