#include "YFile.h"

using namespace ytools;

YFile::YFile() {}

YFile::~YFile() {}

bool YFile::HasFileInWritablePath(const char * file) {
	std::string full_path = CCFileUtils::sharedFileUtils()->getWritablePath();
	full_path += file;
	FILE * pFp = fopen(full_path.c_str(), "r");
	bool result = false;
	if (pFp != NULL) {
		result = true;
		fclose(pFp);
	}
	return result;
}


void YFile::CopyFileToWritablePath(const char * file) {
	std::string strFile = file;
	std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strFile.c_str());
	unsigned long len = 0;
	unsigned char* data = NULL;
	data = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(),"r",&len);

	std::string destPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	destPath += strFile;

	FILE *pFp = fopen(destPath.c_str(),"w+");
	size_t result = fwrite(data,sizeof(char), len, pFp);
	CCLOGINFO("write file - res: %d\n%s", result, destPath.c_str());

	fclose(pFp);
	delete [] data;
	data = NULL;
}

void YFile::DeleteFileInWritablePath(const char * file) {
	std::string full_path = CCFileUtils::sharedFileUtils()->getWritablePath();
	full_path += file;
	int result = remove(full_path.c_str());
	if (result == 0) {
		CCLOGINFO("delete file - SUCCESS!\n%s", full_path.c_str());
	} else {
		CCLOGINFO("delete file - FAILED! %d\n%s", result, full_path.c_str());
	}
}