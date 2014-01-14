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

	m_db_full_path = writable_path + "game_data.sqlite";

	//TStage t_stage;
	//insert_stage(t_stage);
	select_stage();

	return true;
}

SystemManager * SystemManager::GetInstance() {
	if (s_SystemManager == NULL) {
		s_SystemManager = new SystemManager();
		CCAssert(s_SystemManager -> init(), "SystemManager::init failed");
	}
	return s_SystemManager;
}

void SystemManager::insert_stage(const TStage& t_stage) {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("INSERT INTO stage (cell_height, cell_width, map_grid_height, map_grid_width, stage_id, stage_name) VALUES(@cell_height, @cell_width, @map_grid_height, @map_grid_width, @stage_id, @stage_name)");

		pStmt -> BindInt(1, 40);
		pStmt -> BindInt(2, 40);
		pStmt -> BindInt(3, 20);
		pStmt -> BindInt(4, 32);
		pStmt -> BindInt(5, 102);
		pStmt -> BindString(6, "中文关卡名");

		pStmt -> ExecuteAndFree();

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}

void SystemManager::select_stage() {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("SELECT * FROM stage");
		
		while (pStmt -> FetchRow()) {
			int stage_id = pStmt -> GetColumnInt("stage_id");
			string stage_name = pStmt -> GetColumnString("stage_name");
			CCLOG("(%d,%s)", stage_id, stage_name.c_str());
		}

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}
