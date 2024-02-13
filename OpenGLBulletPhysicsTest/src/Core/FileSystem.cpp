#include "FileSystem.h"


void FileSystem::ExtractModels(string directory) {

	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		string path = entry.path().u8string();
		string filename = path.substr(path.find_last_of("/\\") + 1);
		string extension = path.substr(path.find_last_of("."));
		if (extension != ".obj") continue;
		_modelsPath.push_back(filename);
	}

}
