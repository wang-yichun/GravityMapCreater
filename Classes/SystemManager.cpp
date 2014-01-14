#include "SystemManager.h"
#include "sqlite_header.h"
#include "YFile.h"

SystemManager * SystemManager::s_SystemManager = NULL;

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
}

bool SystemManager::init() {
	m_chosedCellCode = kNull;

	// db init
	stringstream ss_info;

	string resource_path = CCFileUtils::sharedFileUtils()->fullPathForFilename("game_data.sqlite");
	ss_info << "ResourcePath=" << resource_path << endl;
	string writable_path = CCFileUtils::sharedFileUtils()->getWritablePath();
	ss_info << "WritablePath=" << writable_path << endl;
	CCLOG("%s", ss_info.str().c_str());
	ss_info.str("");

	if (ytools::YFile::HasFileInWritablePath("game_data.sqlite")) {
		CCLOG("game_data.sqlite is already exists.");
	} else {
		ytools::YFile::CopyFileToWritablePath("game_data.sqlite");	
		CCLOG("game_data.sqlite has been copied.");
	}

	return true;
}

SystemManager * SystemManager::GetInstance() {
	if (s_SystemManager == NULL) {
		s_SystemManager = new SystemManager();
		CCAssert(s_SystemManager -> init(), "SystemManager::init failed");
	}
	return s_SystemManager;
}