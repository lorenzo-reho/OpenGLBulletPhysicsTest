#pragma once
#include "Common.h"
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;
namespace FileSystem {

	void ExtractModels(string path);
	inline vector<string> _modelsPath;

}