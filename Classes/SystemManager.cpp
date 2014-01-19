#include "SystemManager.h"
#include "sqlite_header.h"
#include "YFile.h"
#include "Stage.h"

SystemManager * SystemManager::s_SystemManager = NULL;

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
}

bool SystemManager::init() {
	m_chosedCellCode = kNull;
	m_chosedCellPollCode = emcpcNull;
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


	//select_stage();

	return true;
}

SystemManager * SystemManager::GetInstance() {
	if (s_SystemManager == NULL) {
		s_SystemManager = new SystemManager();
		CCAssert(s_SystemManager -> init(), "SystemManager::init failed");
	}
	return s_SystemManager;
}

void SystemManager::do_load_map() {
	int stage_id = Stage::GetInstance() -> m_stage_id;
	Stage::GetInstance() -> clearMap();
	select_stage(stage_id);
	select_stage_code_map(stage_id);
	Stage::GetInstance() -> refleshMapShow();
	Stage::GetInstance() -> refleshCellShow_adv();
}

void SystemManager::do_save_map() {
	int stage_id = Stage::GetInstance() -> m_stage_id;
	string stage_name = Stage::GetInstance() -> m_stage_name;
	CCSize cell_size = Stage::GetInstance() -> getCellSize();
	CCSize map_grid_size = Stage::GetInstance() -> getMapGridSize();

	TStage t_stage;
	t_stage.cell_height = cell_size.height;
	t_stage.cell_width = cell_size.width;
	t_stage.map_grid_height = map_grid_size.height;
	t_stage.map_grid_width = map_grid_size.width;
	t_stage.stage_id = stage_id;
	t_stage.stage_name = stage_name;

	delete_stage(stage_id);
	insert_stage(t_stage);
	delete_stage_code_map(stage_id);
	insert_stage_code_map(stage_id);
}

void SystemManager::insert_stage(const TStage& t_stage) {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("INSERT INTO stage (cell_height, cell_width, map_grid_height, map_grid_width, stage_id, stage_name) VALUES(@cell_height, @cell_width, @map_grid_height, @map_grid_width, @stage_id, @stage_name)");

		pStmt -> BindInt(1, t_stage.cell_height);
		pStmt -> BindInt(2, t_stage.cell_width);
		pStmt -> BindInt(3, t_stage.map_grid_height);
		pStmt -> BindInt(4, t_stage.map_grid_width);
		pStmt -> BindInt(5, t_stage.stage_id);
		pStmt -> BindString(6, t_stage.stage_name);

		pStmt -> ExecuteAndFree();

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}

void SystemManager::delete_stage(int stage_id) {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("DELETE FROM stage WHERE stage_id=@stage_id");
		pStmt -> BindInt(1, stage_id);
		pStmt -> ExecuteAndFree();

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}

void SystemManager::insert_stage_code_map(int stage_id) {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("INSERT INTO stage_code_map (cell_code, cell_idx, stage_id) VALUES(@cell_code, @cell_idx, @stage_id)");

		vector<MapCell>& v_map = Stage::GetInstance() -> m_Map;
		for (int idx = 0; idx < v_map.size(); idx++) {
			pStmt -> Reset();
			pStmt -> BindInt(1, v_map[idx].code);
			pStmt -> BindInt(2, idx);
			pStmt -> BindInt(3, stage_id);
			pStmt -> Execute();
		}

		pStmt -> FreeQuery();

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}

void SystemManager::delete_stage_code_map(int stage_id) {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("DELETE FROM stage_code_map WHERE stage_id=@stage_id");
		pStmt -> BindInt(1, stage_id);
		pStmt -> ExecuteAndFree();

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}

void SystemManager::select_stage(int stage_id) {
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("SELECT * FROM stage WHERE stage_id = @stage_id");
		pStmt -> BindInt(1, stage_id);

		while (pStmt -> FetchRow()) {
			Stage::GetInstance() -> m_CellSize.height = pStmt -> GetColumnInt("cell_height");
			Stage::GetInstance() -> m_CellSize.width = pStmt -> GetColumnInt("cell_width");
			Stage::GetInstance() -> m_MapGridSize.height = pStmt -> GetColumnInt("map_grid_height");
			Stage::GetInstance() -> m_MapGridSize.width = pStmt -> GetColumnInt("map_grid_width");
			Stage::GetInstance() -> m_stage_id = pStmt -> GetColumnInt("stage_id");
			Stage::GetInstance() -> m_stage_name = pStmt -> GetColumnString("stage_name");
		}

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}

void SystemManager::select_stage_code_map(int stage_id) {
	vector<MapCell>& map = Stage::GetInstance() -> m_Map;
	map.clear();
	try {
		Kompex::SQLiteDatabase *pDatabase = new Kompex::SQLiteDatabase(m_db_full_path.c_str(), SQLITE_OPEN_READWRITE, 0);
		Kompex::SQLiteStatement *pStmt = new Kompex::SQLiteStatement(pDatabase);

		pStmt -> Sql("SELECT * FROM stage_code_map WHERE stage_id = @stage_id");
		pStmt -> BindInt(1, stage_id);

		while (pStmt -> FetchRow()) {
			MapCell mc;
			CCPoint loc = Stage::GetInstance() -> idx2loc(pStmt -> GetColumnInt("cell_idx"));
			mc.setMapCell(loc, (enumMapCellCode)(pStmt -> GetColumnInt("cell_code")));
			map.push_back(mc);
		}

		delete pStmt;
		delete pDatabase;

	} catch(Kompex::SQLiteException &exception) {
		//std::cerr << "\nException Occured" << std::endl;
		CCLOGERROR("\nException Occured: \n%s", exception.GetString().c_str());
		exception.Show();
	}
}