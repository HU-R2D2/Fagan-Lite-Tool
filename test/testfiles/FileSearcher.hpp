#ifndef DIRSEARCHER
#define DIRSEARCHER
#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <unistd.h>

//! @author 	Ferdi Stoeltie 1665045
//! @date		19-20-2016
//! @version	0.8
//! @brief		This class is used for file searching within a directory and it's subdirectories.
//!				It does so by calling the constructor with the base directory as a string.
//!				When this is done, the method get_files can be called, to return the legal files.
//! @warning 	As of yet, only cpp, hpp and h files are supported as legal files,
//!				the rest are discarded and ignored.
class FileSearcher
{
public:
	//! @brief The constructor for FileSearcher. When it is called,
	//!			It will start looking for legal files within the given directory
	//!			and it's subdirectories.
	//! @param base_dir the base directory to start searching for files and folders.
	FileSearcher(std::string base_dir);
	//! @brief Default destructor
	~FileSearcher();
	//! @brief Returns a vector containing legal files.
	//!			It is populated by calling the ctor of the filesearcher.
	//!	@return A vector containing legal files as strings.
	//! @warning Call the ctor first, this will ensure correct population of the return vector!
	std::vector<std::string> get_files();
private:
	// The base_dir string that contains the base directory
	std::string base_dir;

	// The vector, containing all legal files
	std::vector<std::string> files;

	// Will read folder data and called recursively
	void read_folder_data(std::string base_dir);
	// Validates the string for being a legal file or not,
	// and if it is, will add filepath to the vector)
	bool validate_and_add(std::string total_path);
	// Validates whether the extension of the file total_path is of type string s
	bool is_of_type(std::string total_path, std::string s);

};


#endif // DIRSEARCHER
