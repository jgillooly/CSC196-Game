#include "FileIO.h"

namespace antares {
	std::string getFilePath() {
		return std::filesystem::current_path().string();
	}
}
