#include "SystemManager.h"
#include "sqlite_header.h"

SystemManager * SystemManager::s_SystemManager = NULL;

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
}

bool SystemManager::init() {
	m_chosedCellCode = kNull;
	return true;
}

SystemManager * SystemManager::GetInstance() {
	if (s_SystemManager == NULL) {
		s_SystemManager = new SystemManager();
		CCAssert(s_SystemManager -> init(), "SystemManager::init failed");
	}
	return s_SystemManager;
}