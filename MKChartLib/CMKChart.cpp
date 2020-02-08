#include <stdexcept>

#include "stdafx.h"
#include "CMKChart.h"

namespace MKChart {

	CMKChart::CMKChart(){}
	CMKChart::~CMKChart(){}

	WCHAR CMKChart::szInipath[_MAX_PATH], CMKChart::szDrive[_MAX_DRIVE], CMKChart::szPath[_MAX_PATH], CMKChart::szFName[_MAX_FNAME], CMKChart::szExt[_MAX_EXT];
	WCHAR CMKChart::szLogfolder1[_MAX_PATH];
	std::wstring  CMKChart::log_path;
	ST_CHART_SET CMKChart::mkchartset[MK_CHART_MAX];

	//########################################################################
	int CMKChart::init_chartfunc() {

		//iniファイルPATH取得
		GetModuleFileName(NULL, szInipath, (sizeof(TCHAR) * _MAX_PATH));// exe fileのパス取り込み
		_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
		log_path.clear(); log_path += szPath;
		_wmakepath_s(szInipath, sizeof(szInipath), szDrive, szPath, NAME_OF_INIFILE, EXT_OF_INIFILE); // ini fileのパスセット

		//iniファイル設定値読み込み
		TCHAR buf_t[128];
		//CHART 1
		DWORD	str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_X_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_x = _wtoi(buf_t);
				str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_Y_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_y = _wtoi(buf_t);
#if 0
		//LOG01
		if (nlogs > 0) {
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME1_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].fname, sizeof(mklogset[MK_LOGSET_1].fname), szInipath);
			_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
																																		//	_wmakepath_s(mklogset[MK_LOGSET_1].fname, sizeof(mklogset[MK_LOGSET_1].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE1_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].szType, sizeof(mklogset[MK_LOGSET_1].szType), szInipath);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].ms_period = stoi(buf_t);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_1].n_item = stoi(buf_t);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_TIMESET1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_1].timeset = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE01_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[0] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE02_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[1] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE03_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[2] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE04_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[3] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE05_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[4] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE06_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[5] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE07_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[6] = stoi(buf_t);
			str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE08_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[7] = stoi(buf_t);

			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL01_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[0], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL02_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[1], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL03_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[2], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL04_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[3], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL05_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[4], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL06_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[5], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL07_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[6], LABEL_LEN_MAX, szInipath);
			str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL08_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].labes[7], LABEL_LEN_MAX, szInipath);

		}
#endif	
	return 0;
	};



}