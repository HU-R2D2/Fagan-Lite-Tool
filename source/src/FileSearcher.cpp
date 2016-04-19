#include "../include/FileSearcher.hpp"
using namespace std;
FileSearcher::FileSearcher(string base_dir) : base_dir{base_dir}{
    read_folder_data(base_dir);
}

FileSearcher::~FileSearcher()
{
}
void FileSearcher::read_folder_data(string base_dir)	{
    DIR           *d;
    struct dirent *dir;
    d = opendir(base_dir.c_str());
    if (d)
    {
        cout << "directory: " << base_dir << endl;
        while ((dir = readdir(d)) != NULL)	{
            string new_path = "/" + string(dir->d_name);
            string total_path = base_dir;
            total_path.append(new_path);
            if ((total_path.find(".") == std::string::npos) || total_path.find_last_of(".") < base_dir.length())	{
                cout << "Reading folder..." << total_path << endl;
                read_folder_data(total_path);
            }
            else	{
                validate_and_add(total_path);
            }
        }
    }
}

bool FileSearcher::validate_and_add(string total_path)	{
    if (is_of_type(total_path, ".hpp") 	||
        is_of_type(total_path, ".h") 	||
        is_of_type(total_path, ".cpp"))	{
        files.push_back(total_path);
        return true;
    }
    return false;
}
bool FileSearcher::is_of_type(string total_path, string s)	{
    std::size_t eofn;
    if ((eofn = total_path.find(s)) != std::string::npos &&
        total_path.length() == eofn + s.length())	{
        files.push_back(total_path);
        return true;
    }
    return false;
}

vector<string> FileSearcher::get_files()  {
    return files;
}
