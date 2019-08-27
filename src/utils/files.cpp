#include "files.hpp"

#ifdef _WIN32
#include "dirent.hpp"
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#include <dirent.h>
#include <cstdio>
#include <string.h>
#include <sys/types.h>
#endif
#include <filesystem>
#include <iostream>
//#endif

namespace gamelib3 {

// -----------------------------------------------------------------------------
//  getWorkingDirectory
// -----------------------------------------------------------------------------
std::string Files::getWorkingDirectory() {
  char buff[FILENAME_MAX];
  auto ret = GetCurrentDir(static_cast<char *>(buff), FILENAME_MAX);
  std::string current_working_dir(static_cast<char *>(buff));
  return current_working_dir;
}

// -----------------------------------------------------------------------------
// getFilesInFolder
// -----------------------------------------------------------------------------
std::set<std::string> Files::getFilesInFolder(std::string folder) {
  std::set<std::string> out;

  //#ifdef __APPLE__
  //#include "TargetConditionals.h"
  //#ifdef TARGET_OS_MAC

  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(folder.c_str())) != nullptr) {
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != nullptr) {
      if (strncmp(ent->d_name, ".", sizeof(ent->d_name)) == 0 ||
          strncmp(ent->d_name, "..", sizeof(ent->d_name)) == 0)
        continue;
      std::cout << folder + "/" + ent->d_name << std::endl;
      out.insert(folder + "/" + ent->d_name);
    }
    closedir(dir);
  } else {
    /* could not open directory */
    perror("");
    return out;
  }
  //#enndif
  //#else

  //  for (auto p : std::filesystem::directory_iterator(folder)) {
  //    std::cout << p.path() << std::endl;
  //    out.insert(p.path().string());
  //  }

  // sort alphabetically by default
  //#endif

  return out;
}
}  // namespace gamelib3
