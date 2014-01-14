#pragma once

#include "cocos2d.h"
USING_NS_CC;

namespace ytools {

	class YFile
	{
	public:
		YFile();
		~YFile();

		static bool HasFileInWritablePath(const char * file);
		static void CopyFileToWritablePath(const char * file);
		static void DeleteFileInWritablePath(const char * file);
	private:

	};

}