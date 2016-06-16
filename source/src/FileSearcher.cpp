#include "../include/FileSearcher.hpp"

FileSearcher::FileSearcher(std::string base_dir) : base_dir{base_dir} {
    read_folder_data(base_dir);
}

FileSearcher::~FileSearcher() {
}

void FileSearcher::read_folder_data(std::string base_dir) {
    DIR *d;
    struct dirent *dir;
    d = opendir(base_dir.c_str());
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            std::string new_path = "/" + std::string(dir->d_name);
            std::string total_path = base_dir;
            total_path.append(new_path);
            if ((total_path.find(".") == std::string::npos) ||
                total_path.find_last_of(".") < base_dir.length()) {
                read_folder_data(total_path);
            }   else {
                validate_and_add(total_path);
            }
        }
    }
}

bool FileSearcher::validate_and_add(std::string total_path) {
    if (is_of_type(total_path, ".hpp")  ||
        is_of_type(total_path, ".cpp")  ||

        is_of_type(total_path, ".h")    ||
        is_of_type(total_path, ".c")    ||

        is_of_type(total_path, ".cxx")  ||
        is_of_type(total_path, ".hxx")) {
        files.push_back(total_path);
        return true;
    }
    return false;
}

bool FileSearcher::is_of_type(std::string total_path, std::string s) {
    std::size_t eofn;
    if ((eofn = total_path.find(s)) != std::string::npos &&
        total_path.length() == eofn + s.length()) {
        return true;
    }
    return false;
}

std::vector<std::string> FileSearcher::get_files() {
    return files;
}
