#include "utils/fileutils.hpp"


namespace caze { namespace utils {

	std::string read_file(const char* filepath)
	{
	    std::ifstream inFile;
	    inFile.open(filepath); //open the input file

	    std::stringstream strStream;
	    strStream << inFile.rdbuf(); //read the file
	    std::string str = strStream.str();

	    return str;
	}

} }