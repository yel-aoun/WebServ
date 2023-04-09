#include "delete.hpp"
#include "../server/client.hpp"
#include "../server/server.hpp"
#include "../headers_cpp.hpp"


Delete::Delete()
{
    
}

int deleteFolder(const char* folderPath) {
    int status = 0;

    // Open the folder
    DIR* dir = opendir(folderPath);
    if (dir == NULL) {
        std::cerr << "Error opening folder: " << folderPath << std::endl;
        return -1;
    }

    // Iterate over the contents of the folder
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the path to the entry
        char entryPath[PATH_MAX];
        snprintf(entryPath, PATH_MAX, "%s/%s", folderPath, entry->d_name);

        // Recursively delete subdirectories
        if (entry->d_type == DT_DIR) {
            int subStatus = deleteFolder(entryPath);
            if (subStatus != 0) {
                status = subStatus;
            }
        }
        // Delete files and symbolic links
        else {
            int subStatus = unlink(entryPath);
            if (subStatus != 0) {
                status = subStatus;
            }
        }
    }

    // Close the folder
    closedir(dir);

    // Delete the empty folder
    if (status == 0) {
        int subStatus = rmdir(folderPath);
        if (subStatus != 0) {
            std::cerr << "Error deleting folder: " << folderPath << std::endl;
            return subStatus;
        }
    }

    return status;
}

void Delete::delete_directory(Client *ctl, Server &serv)
{
    if (!deleteFolder(ctl->loc_path.c_str()))
    {
        ctl->status_code = 204;
        ctl->status = "No Content";
        ctl->loc_path = "./default_error_pages/204.html";
        return ;
    }
    else
    {
        if (access(ctl->loc_path.c_str(), W_OK) == 0)
        {
            ctl->status_code = 500;
            ctl->status = "Internal Server Error";
            ctl->loc_path = "./default_error_pages/500.html";
            return ;
        }
        else
        {
            ctl->status_code = 403;
            ctl->status = "Forbidden";
            ctl->loc_path = "./default_error_pages/403.html";
            return ;
        }
    }
}

void Delete::Treat_directory(Client *ctl, Server &serv)
{
    this->delete_directory(ctl, serv);
}

void Delete::Treat_File(Client *ctl, Server &serv)
{
    remove(ctl->loc_path.c_str());
}

void Delete::erase(Client *ctl, Server &serv)
{
    DIR* dir = opendir(ctl->loc_path.c_str());
    if (dir != NULL)
    {
        // std::cout << "The client requested a directory" << std::endl;
        this->Treat_directory(ctl, serv);
    }
    else if (fopen(ctl->loc_path.c_str(), "r") != NULL)
    {
        // std::cout << "The client requested a file" << std::endl;
        this->Treat_File(ctl, serv);
    } 
    else
    {
        ctl->status_code = 404;
        ctl->status = "No Found";
        ctl->loc_path = "./default_error_pages/404.html";
        return ;
    }
}
Delete::~Delete()
{

}
