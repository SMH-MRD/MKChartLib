#include <stdexcept>

#include "stdafx.h"
#include "CMKChart.h"

namespace MKChart {

	CMKChart::CMKChart() {}
	CMKChart::~CMKChart() {}

	WCHAR CMKChart::szInipath[_MAX_PATH], CMKChart::szDrive[_MAX_DRIVE], CMKChart::szPath[_MAX_PATH], CMKChart::szFName[_MAX_FNAME], CMKChart::szExt[_MAX_EXT];
	WCHAR CMKChart::szLogfolder1[_MAX_PATH];
	std::wstring  CMKChart::log_path;
	ST_CHART_SET CMKChart::mkchartset[MK_CHART_WND_MAX];
	HINSTANCE CMKChart::hInst;
	HPEN hpen[MK_MAX_GRAPH_PER_CHART];

	static double dummy_d = 0.0;
	static int dummy_i = 0;
	static bool dummy_b = false;



	//########################################################################
	int CMKChart::init_chartfunc() {

		for (int i = 0; i < MK_CHART_WND_MAX; i++) {
			for (int j = 0; j < MK_CHART_MAX_PER_WND; j++) {
				for (int k = 0; k < MK_MAX_GRAPH_PER_CHART; k++) {
					mkchartset[i].data_type[0][j][k] = MK_DATA_TYPE_NULL;
					mkchartset[i].data_type[1][j][k] = MK_DATA_TYPE_NULL;

					mkchartset[i].pdata[0].pd[j][k] = &dummy_d;
					mkchartset[i].pdata[1].pd[j][k] = &dummy_d;
					mkchartset[i].pdata[0].pi[j][k] = &dummy_i;
					mkchartset[i].pdata[1].pi[j][k] = &dummy_i;
					for (int l = 0; l < MK_MAX_BOOL_PER_CHART; l++) {
						mkchartset[i].pdata[0].pb[j][k][l] = &dummy_b;
						mkchartset[i].pdata[1].pb[j][k][l] = &dummy_b;
					}
				}
			}
		}

		hInst = GetModuleHandle(0);

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
		str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_W_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_w = _wtoi(buf_t);
		str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_H_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_h = _wtoi(buf_t);
		str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_PLOT_MS_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].plot_interval_ms = _wtoi(buf_t);
		str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_TYPE_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_type = _wtoi(buf_t);

		return 0;
	};
	//########################################################################
	HWND CMKChart::open_chart(int chartID, HWND hwnd_parent) {

		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);

		if (mkchartset[chartID].chart_type == CHART_SCATTER) {
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = ChartWndProc_A;// !CALLBACKでreturnを返していないとWindowClassの登録に失敗する
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = hInst;
			wc.hIcon = NULL;
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = TEXT("MKChart_A");
			wc.hIconSm = NULL;
			ATOM fb = RegisterClassExW(&wc);

			mkchartset[chartID].hwnd_chart = CreateWindow(TEXT("MKChart_A"),
				TEXT("MK CHART"),
				WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION,
				CHART_WND_X, CHART_WND_Y, CHART_WND_W, CHART_WND_H,
				hwnd_parent,
				0,
				hInst,
				NULL);
		}
		else {
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = ChartWndProc_A;// !CALLBACKでreturnを返していないとWindowClassの登録に失敗する
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = hInst;
			wc.hIcon = NULL;
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = TEXT("MKChart_B");
			wc.hIconSm = NULL;
			ATOM fb = RegisterClassExW(&wc);

			mkchartset[chartID].hwnd_chart = CreateWindow(TEXT("MKChart_B"),
				TEXT("MK CHART"),
				WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION,
				CHART_WND_X, CHART_WND_Y, CHART_WND_W, CHART_WND_H,
				hwnd_parent,
				0,
				hInst,
				NULL);
		}

		SendMessage(mkchartset[chartID].hwnd_chart, WM_MKCHART_INIT, chartID, 0L);

		ShowWindow(mkchartset[chartID].hwnd_chart, SW_SHOW);
		UpdateWindow(mkchartset[chartID].hwnd_chart);
		return mkchartset[chartID].hwnd_chart;
	};
	//########################################################################	
	LRESULT CMKChart::ChartWndProc_A(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

		HDC hdc;

		switch (msg) {
		case WM_DESTROY: {

			int chartID_work = get_chartID(hwnd);

			DeleteObject(mkchartset[chartID_work].hBmap_mem0);
			DeleteDC(mkchartset[chartID_work].hdc_mem0);

			DeleteObject(mkchartset[chartID_work].hBmap_bg);
			DeleteDC(mkchartset[chartID_work].hdc_mem_bg);

			DeleteObject(mkchartset[chartID_work].hBmap_graph);
			DeleteDC(mkchartset[chartID_work].hdc_mem_graph);

			close_chart(get_chartID(hwnd));

			PostQuitMessage(0);
		}return 0;
		case WM_TIMER: {
			int chartID_work = get_chartID(hwnd);
	
			set_graph(chartID_work);//プロットデータ記録

			//SelectObject(mkchartset[chartID_work].hdc_mem_bg, GetStockObject(BLACK_PEN));
			SelectObject(mkchartset[chartID_work].hdc_mem_graph, GetStockObject(DC_PEN));
			SetDCPenColor(mkchartset[chartID_work].hdc_mem_graph, RGB(0, 0, 255));

			if (mkchartset[chartID_work].chart_type == MK_CHART_TYPE_SCATTER) {

				for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) {
					if (mkchartset[chartID_work].graph_count[i]) {
						for (int j = 0; j < MK_MAX_GRAPH_PER_CHART; j++) {
							if (mkchartset[chartID_work].graph_count[i] < j) {
								MoveToEx(mkchartset[chartID_work].hdc_mem_graph, 
									mkchartset[chartID_work].plot_p[i][j][0].x, 
									mkchartset[chartID_work].plot_p[i][j][0].y,
									NULL);
								//				LineTo(mkchartset[chartID_work].hdc_mem_graph, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y);
								//				//MoveToEx(mkchartset[chartID_work].hdc_mem_graph, mkchartset[chartID_work].g_origin[i].x+test_count, mkchartset[chartID_work].g_origin[i].y + test_count, NULL);
								//				//LineTo(mkchartset[chartID_work].hdc_mem_graph, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y);
							}
							else break;
						}
					}
					else continue;
				}
			}
			else {
				int retio100 = MK_RANGE_100PERCENT / GRAPH_CHART_100;
				bool b_refresh = true;
				for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) {
					if (mkchartset[chartID_work].graph_count[i]) {
						for (int j = 0; j < MK_MAX_GRAPH_PER_CHART; j++) {
							if (mkchartset[chartID_work].graph_count[i] > j) {
								SelectObject(mkchartset[chartID_work].hdc_mem_graph, mkchartset[chartID_work].hpen[j]);
								MoveToEx(mkchartset[chartID_work].hdc_mem_graph,
									mkchartset[chartID_work].plot_p[i][j][0].x,
									mkchartset[chartID_work].plot_p[i][j][0].y,
									NULL
								);

								LONG old_x = mkchartset[chartID_work].plot_p[i][j][0].x;
								mkchartset[chartID_work].plot_p[i][j][0].x = mkchartset[chartID_work].g_origin[i].x
									+ (mkchartset[chartID_work].plot_data[i][j][mkchartset[chartID_work].plot_buf_index].x * mkchartset[chartID_work].spd_dot_per_sec / 100)% GRAPH_CHART_DOT_W;
					
								mkchartset[chartID_work].plot_p[i][j][0].y = mkchartset[chartID_work].g_origin[i].y 
										+ mkchartset[chartID_work].plot_data[i][j][mkchartset[chartID_work].plot_buf_index].y.i_data/ retio100;

								if (old_x > mkchartset[chartID_work].plot_p[i][j][0].x) {
									if (b_refresh == true) {
										PatBlt(mkchartset[chartID_work].hdc_mem_graph, 0, 0, CHART_WND_W, CHART_WND_H, WHITENESS);
										PatBlt(mkchartset[chartID_work].hdc_mem0, 0, 0, CHART_WND_W, CHART_WND_H, WHITENESS);
										b_refresh = false;
									}
								}
								else {
									LineTo(mkchartset[chartID_work].hdc_mem_graph,
										mkchartset[chartID_work].plot_p[i][j][0].x,
										mkchartset[chartID_work].plot_p[i][j][0].y
									);
								}
							}
							else break;
						}
					}
					else continue;
				}
			}


			InvalidateRect(hwnd, NULL, TRUE);

			//					hdc = GetDC(hwnd);
			//					TextOut(hdc, 0, test_count%100, L"Test\0", sizeof("Test\0"));
		}return 0;
		case WM_MKCHART_INIT: {
			int chartID_work = wp;
			//ボタン作成
			mkchartset[chartID_work].hwnd_chart_startPB = CreateWindow(
				L"BUTTON", L"Start",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				CHART_WND_W - 100, CHART_WND_H - 70, 38, 25, hwnd, (HMENU)IDC_CHART_START_PB, hInst, NULL);
			mkchartset[chartID_work].hwnd_chart_sopPB = CreateWindow(
				L"BUTTON", L"Stop",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				CHART_WND_W - 58, CHART_WND_H - 70, 38, 25, hwnd, (HMENU)IDC_CHART_STOP_PB, hInst, NULL);
			mkchartset[chartID_work].hwnd_chart_opt1_radio = CreateWindow(
				L"BUTTON", L"Option1",
				WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
				CHART_WND_W - 175, 5, 70, 25, hwnd, (HMENU)IDC_CHART_RADIO_OPT1, hInst, NULL);
			mkchartset[chartID_work].hwnd_chart_opt2_radio = CreateWindow(
				L"BUTTON", L"Option2",
				WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
				CHART_WND_W - 95, 5, 70, 25, hwnd, (HMENU)IDC_CHART_RADIO_OPT2, hInst, NULL);


			init_chart(chartID_work);
			hdc = GetDC(hwnd);

			if (mkchartset[chartID_work].chart_type == MK_CHART_TYPE_SCATTER) {
				mkchartset[chartID_work].hBmap_mem0 = CreateCompatibleBitmap(hdc, CHART_WND_W, CHART_WND_H);
				mkchartset[chartID_work].hdc_mem0 = CreateCompatibleDC(hdc);
				SelectObject(mkchartset[chartID_work].hdc_mem0, mkchartset[chartID_work].hBmap_mem0);

				mkchartset[chartID_work].hBmap_bg = CreateCompatibleBitmap(hdc, CHART_WND_W, CHART_WND_H);
				mkchartset[chartID_work].hdc_mem_bg = CreateCompatibleDC(hdc);
				SelectObject(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].hBmap_bg);

				mkchartset[chartID_work].hBmap_graph = CreateCompatibleBitmap(hdc, CHART_WND_W, CHART_WND_H);
				mkchartset[chartID_work].hdc_mem_graph = CreateCompatibleDC(hdc);
				SelectObject(mkchartset[chartID_work].hdc_mem_graph, mkchartset[chartID_work].hBmap_graph);

				PatBlt(mkchartset[chartID_work].hdc_mem0, 0, 0, CHART_WND_W, CHART_WND_H, WHITENESS);
				PatBlt(mkchartset[chartID_work].hdc_mem_bg, 0, 0, CHART_WND_W, CHART_WND_H, WHITENESS);
				PatBlt(mkchartset[chartID_work].hdc_mem_graph, 0, 0, CHART_WND_W, CHART_WND_H, WHITENESS);

				ReleaseDC(hwnd, hdc);

				SelectObject(mkchartset[chartID_work].hdc_mem_bg, GetStockObject(DC_PEN));
				SetDCPenColor(mkchartset[chartID_work].hdc_mem_bg, RGB(128, 128, 128));

				for (int i = 0; i < CHART_NUM; i++) {
					MoveToEx(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x - SCAT_CHART_DOT_W / 2, mkchartset[chartID_work].g_origin[i].y, NULL);
					LineTo(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x + SCAT_CHART_DOT_W / 2, mkchartset[chartID_work].g_origin[i].y);

					MoveToEx(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y - SCAT_CHART_DOT_H / 2, NULL);
					LineTo(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y + SCAT_CHART_DOT_H / 2);

				}
			}
			else {
				mkchartset[chartID_work].hBmap_mem0 = CreateCompatibleBitmap(hdc, CHART_WND_W * 4, CHART_WND_H);
				mkchartset[chartID_work].hdc_mem0 = CreateCompatibleDC(hdc);
				SelectObject(mkchartset[chartID_work].hdc_mem0, mkchartset[chartID_work].hBmap_mem0);

				mkchartset[chartID_work].hBmap_bg = CreateCompatibleBitmap(hdc, CHART_WND_W, CHART_WND_H);
				mkchartset[chartID_work].hdc_mem_bg = CreateCompatibleDC(hdc);
				SelectObject(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].hBmap_bg);

				mkchartset[chartID_work].hBmap_graph = CreateCompatibleBitmap(hdc, mkchartset[chartID_work].graph_field_w, mkchartset[chartID_work].graph_field_h);
				mkchartset[chartID_work].hdc_mem_graph = CreateCompatibleDC(hdc);
				SelectObject(mkchartset[chartID_work].hdc_mem_graph, mkchartset[chartID_work].hBmap_graph);

				PatBlt(mkchartset[chartID_work].hdc_mem0, 0, 0, CHART_WND_W * 4, CHART_WND_H, WHITENESS);
				PatBlt(mkchartset[chartID_work].hdc_mem_bg, 0, 0, CHART_WND_W, CHART_WND_H, WHITENESS);
				PatBlt(mkchartset[chartID_work].hdc_mem_graph, 0, 0, CHART_WND_W * 4, CHART_WND_H, WHITENESS);

				ReleaseDC(hwnd, hdc);

				SelectObject(mkchartset[chartID_work].hdc_mem_bg, GetStockObject(DC_PEN));
				SetDCPenColor(mkchartset[chartID_work].hdc_mem_bg, RGB(128, 128, 128));

				for (int i = 0; i < CHART_NUM; i++) {
					MoveToEx(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y, NULL);
					LineTo(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x + GRAPH_CHART_DOT_W, mkchartset[chartID_work].g_origin[i].y);

					MoveToEx(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y + GRAPH_CHART_DOT_H / 2 - 5, NULL);
					LineTo(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y - GRAPH_CHART_DOT_H / 2 + 5);

				}
			}

			DeleteObject(SelectObject(mkchartset[chartID_work].hdc_mem0, GetStockObject(WHITE_BRUSH)));
			DeleteObject(SelectObject(mkchartset[chartID_work].hdc_mem_bg, GetStockObject(WHITE_BRUSH)));

			//タイマー起動
			mkchartset[chartID_work].timerID = SetTimer(hwnd, ID_CHART_TIMER + chartID_work, mkchartset[chartID_work].plot_interval_ms, NULL);

			return 0;
		}
		case WM_CREATE: {
			;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);

			int chartID_work = get_chartID(hwnd);
			TransparentBlt(mkchartset[chartID_work].hdc_mem0, 0, 0, mkchartset[chartID_work].chart_w, mkchartset[chartID_work].chart_h, mkchartset[chartID_work].hdc_mem_bg, 0, 0, mkchartset[chartID_work].chart_w, mkchartset[chartID_work].chart_h, RGB(255, 255, 255));
			TransparentBlt(mkchartset[chartID_work].hdc_mem0, 0, 0, mkchartset[chartID_work].chart_w, mkchartset[chartID_work].chart_h, mkchartset[chartID_work].hdc_mem_graph, 0, 0, mkchartset[chartID_work].chart_w, mkchartset[chartID_work].chart_h, RGB(255, 255, 255));
			BitBlt(hdc, 0, 0, CHART_WND_W, CHART_WND_H, mkchartset[chartID_work].hdc_mem0, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);

			break;
		}

					   return 0;
		}
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	//########################################################################	
	LRESULT CMKChart::ChartWndProc_B(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

		HDC hdc;

		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_TIMER:
			hdc = GetDC(hwnd);
			TextOut(hdc, 0, 0, L"Test\0", sizeof("Test\0"));
			return 0;
		case WM_CREATE: {
			break;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			break;
		}
					   return 0;
		}
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	//########################################################################
	int CMKChart::init_chart(int chartID) {

		int nFramX = GetSystemMetrics(SM_CXSIZEFRAME);		//ウィンドウ周囲の幅
		int nFramY = GetSystemMetrics(SM_CYSIZEFRAME);		//ウィンドウ周囲の高さ
		int nCaption = GetSystemMetrics(SM_CYCAPTION);		//タイトルバーの高さ
		int scrw = GetSystemMetrics(SM_CXSCREEN);			//プライマモニタの幅
		int scrh = GetSystemMetrics(SM_CYSCREEN);			//プライマモニタの高さ

		//表示フォント
		mkchartset[chartID].hfont_inftext = CreateFont(
			12,						//int cHeight
			0,						//int cWidth
			0,						//int cEscapement
			0,						//int cOrientation
			0,						//int cWeight
			FALSE,					//DWORD bItalic
			FALSE,					//DWORD bUnderline
			FALSE,					//DWORD bStrikeOut
			SHIFTJIS_CHARSET,		//DWORD iCharSet
			OUT_DEFAULT_PRECIS,		//DWORD iOutPrecision
			CLIP_DEFAULT_PRECIS,	//DWORD iClipPrecision
			PROOF_QUALITY,			//DWORD iQuality
			FIXED_PITCH | FF_MODERN,//DWORD iPitchAndFamily
			TEXT("Arial")			//LPCWSTR pszFaceName
		);

		mkchartset[chartID].hpen[0] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		mkchartset[chartID].hpen[1] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mkchartset[chartID].hpen[2] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mkchartset[chartID].hpen[3] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));


		//SAMPLE Radio button 表示
		if (mkchartset[chartID].chart_type == CHART_GRAPH) SendMessage(mkchartset[chartID].hwnd_chart_opt1_radio, BM_SETCHECK, BST_CHECKED, 0L);
		if (mkchartset[chartID].chart_type == CHART_SCATTER)  SendMessage(mkchartset[chartID].hwnd_chart_opt2_radio, BM_SETCHECK, BST_CHECKED, 0L);

		if (mkchartset[chartID].chart_type == CHART_SCATTER) {
			//SAMPLE Radio button 表示
			SendMessage(mkchartset[chartID].hwnd_chart_opt2_radio, BM_SETCHECK, BST_CHECKED, 0L);
			//CHART原点
			mkchartset[chartID].g_origin[0].x = PHASE_MARGIN_X + SCAT_CHART_DOT_W / 2;
			mkchartset[chartID].g_origin[0].y = SCAT_CHART_DOT_H / 2;
			mkchartset[chartID].g_origin[1].x = PHASE_MARGIN_X + PHASE_MARGIN_X + SCAT_CHART_DOT_W + SCAT_CHART_DOT_W / 2;
			mkchartset[chartID].g_origin[1].y = SCAT_CHART_DOT_H / 2;
			mkchartset[chartID].g_origin[2].x = PHASE_MARGIN_X + SCAT_CHART_DOT_W / 2;
			mkchartset[chartID].g_origin[2].y = PHASE_MARGIN_Y + SCAT_CHART_DOT_H + SCAT_CHART_DOT_H / 2;
			mkchartset[chartID].g_origin[3].x = PHASE_MARGIN_X + PHASE_MARGIN_X + SCAT_CHART_DOT_W + SCAT_CHART_DOT_W / 2;
			mkchartset[chartID].g_origin[3].y = PHASE_MARGIN_Y + SCAT_CHART_DOT_H + SCAT_CHART_DOT_H / 2;
			//描画表示時間
			mkchartset[chartID].refresh_interval_ms = PHASE_DURATION_DEF;
			mkchartset[chartID].g_ms_per_dot = 0;//散布図は未使用

			mkchartset[chartID].graph_field_w = CHART_WND_W;
			mkchartset[chartID].graph_field_h = CHART_WND_H;

			mkchartset[chartID].dot100percent_x = SCAT_CHART_100;
			mkchartset[chartID].dot100percent_y = SCAT_CHART_100;

			for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) {
				for (int j = 0; j < MK_CHART_MAX_PER_WND; j++) {
					mkchartset[chartID].plot_p[i][j][0].x = mkchartset[chartID].g_origin[i].x;
					mkchartset[chartID].plot_p[i][j][0].y = mkchartset[chartID].g_origin[i].y;
				}
			}
		}
		else {
			SendMessage(mkchartset[chartID].hwnd_chart_opt1_radio, BM_SETCHECK, BST_CHECKED, 0L);
			for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) {
				mkchartset[chartID].g_origin[i].x = CHART_MARGIN_X;
				mkchartset[chartID].g_origin[i].y = GRAPH_CHART_DOT_H / 2 + GRAPH_CHART_DOT_H * i + 25;

				for (int j = 0; j < MK_CHART_MAX_PER_WND; j++) {
					for (int k = 0; k < MK_MAX_BOOL_PER_CHART; k++) {
						mkchartset[chartID].plot_p[i][j][k].x = mkchartset[chartID].g_origin[i].x;
						mkchartset[chartID].plot_p[i][j][k].y = mkchartset[chartID].g_origin[i].y + GRAPH_CHART_DOT_H / 8 * k;
					}
				}
			}
			mkchartset[chartID].refresh_interval_ms = CHART_SPEED_DEF;//時間グラフは未使用

			mkchartset[chartID].g_ms_per_dot = CHART_SPEED_DEF / GRAPH_CHART_DOT_W;

			mkchartset[chartID].graph_field_w = CHART_WND_W + CHART_MARGIN_X;
			mkchartset[chartID].graph_field_h = CHART_WND_H;

			mkchartset[chartID].bPrimaryDisp = true;//初期値は第１画面表示

			mkchartset[chartID].dot100percent_x = GRAPH_CHART_DOT_W;
			mkchartset[chartID].dot100percent_y = GRAPH_CHART_100;

		}

		mkchartset[chartID].plot_buf_index = 0;		//チャートデータバッファのindex
		mkchartset[chartID].plot_x = 0;				//データプロットBITMAP上のX位置
		mkchartset[chartID].start_time_ms = GetTickCount();
		set_chart_spd(chartID, CHART_SPEED_DEF);

		for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) mkchartset[chartID].graph_count[i] = 0;

		for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) {
			mkchartset[chartID].graph_count[i] = 0;
			for (int k = 0; k < MK_MAX_GRAPH_PER_CHART; k++) {
				if (mkchartset[chartID].data_type[MK_DATA_CODE_Y][i][k] > 0) {
					mkchartset[chartID].graph_count[i]++;	//各チャートに表示するグラフ数カウント
					set_graph(chartID);				//開始点セット
				}
				else break;
			}
		}
		return 0;
	}
	//########################################################################
	int CMKChart::close_chart(int chartID) {

		//タイマー解放
		KillTimer(NULL, mkchartset[chartID].timerID);

		for (int i=0; i < MK_MAX_GRAPH_PER_CHART; i++) DeleteObject(mkchartset[chartID].hpen[i]);

		//描画用デバイスコンテキスト解放
		DeleteDC(mkchartset[chartID].hdc_mem0);			//ベース画面
		DeleteDC(mkchartset[chartID].hdc_mem_bg);		//背景画面
		DeleteDC(mkchartset[chartID].hdc_mem_graph);	//プロット画面
		DestroyWindow(mkchartset[chartID].hwnd_chart);  //ウィンドウ破棄
		return 0;
	}
	//########################################################################
	int CMKChart::set_double_data(double* pd, int chart_WND_ID, int i_chart, int i_item, double d_100, bool is_x) {
		if ((chart_WND_ID < 0) || (i_chart >= MK_CHART_WND_MAX))return -1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;


		if (mkchartset[chart_WND_ID].chart_type == MK_CHART_TYPE_SCATTER) {
			if (is_x) {
				mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_X].pd[i_chart][i_item] = pd;
				mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i_chart][i_item] = MK_DATA_TYPE_DOUBLE;
				mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].d100[i_chart][i_item] = d_100;
			}
			else {
				mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pd[i_chart][i_item] = pd;
				mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i_chart][i_item] = MK_DATA_TYPE_DOUBLE;
				mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].d100[i_chart][i_item] = d_100;
			}
		}
		else {
			mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].i100[i_chart][i_item] = 100000;		//X軸は時間 intでセット
			mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i_chart][i_item] = MK_DATA_TYPE_TIME;//X軸は時間

			mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pd[i_chart][i_item] = pd;
			mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i_chart][i_item] = MK_DATA_TYPE_DOUBLE;
			mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].d100[i_chart][i_item] = d_100;
		}
		return 0;
	};
	//########################################################################
	int CMKChart::set_int_data(int* pi, int chart_WND_ID, int i_chart, int i_item, int i_100, bool is_x) {
		if ((chart_WND_ID < 0) || (i_chart >= MK_CHART_MAX_PER_WND))return -1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;

		if (mkchartset[chart_WND_ID].chart_type == MK_CHART_TYPE_SCATTER) {
			if (is_x) {
				mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_X].pi[i_chart][i_item] = pi;
				mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i_chart][i_item] = MK_DATA_TYPE_INT;
				mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].i100[i_chart][i_item] = i_100;
			}
			else {
				mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pi[i_chart][i_item] = pi;
				mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i_chart][i_item] = MK_DATA_TYPE_INT;
				mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].i100[i_chart][i_item] = i_100;
			}
		}
		else {
			mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].i100[i_chart][i_item] = 100000;		//X軸は時間 intでセット
			mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i_chart][i_item] = MK_DATA_TYPE_TIME;//X軸は時間

			mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pi[i_chart][i_item] = pi;
			mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i_chart][i_item] = MK_DATA_TYPE_INT;
			mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].i100[i_chart][i_item] = i_100;
		}
		return 0;
	};
	//########################################################################
	int CMKChart::set_bool_data(bool* pb, int chart_WND_ID, int i_chart, int i_item, int i_bool) {
		if ((chart_WND_ID < 0) || (i_chart >= MK_CHART_MAX_PER_WND))return -1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;
		if ((i_bool < 0) || (i_bool >= MK_MAX_BOOL_PER_CHART))return -1;

		mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].i100[i_chart][i_item] = 100000;//BOOLのX軸は時間のみ intでセット
		mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i_chart][i_item] = MK_DATA_TYPE_TIME;//BOOLのX軸は時間のみ

		mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pb[i_chart][i_item][i_bool] = pb;
		mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].i100[i_chart][i_item] = 1;
		mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i_chart][i_item] = MK_DATA_TYPE_BOOL;

		return 0;
	};
	//########################################################################
	int  CMKChart::chart_start(int chartID, HWND hwnd_parent) {
		if (mkchartset[chartID].chart_status < MK_CHART_STANDBY) {//初期化未完
			if (open_chart(chartID, hwnd_parent) != NULL) init_chart(chartID);
		}
		return 0;
	};
	//########################################################################
	int CMKChart::set_graph(int chart_WND_ID) {

		//チャートバッファのindex更新
		if (mkchartset[chart_WND_ID].plot_buf_index >= MK_CHART_BUF_MAX) mkchartset[chart_WND_ID].plot_buf_index = 0;
		else mkchartset[chart_WND_ID].plot_buf_index++;

		if (mkchartset[chart_WND_ID].plot_buf_index >= MK_CHART_BUF_MAX) return -1;

		int time_10ms = int((GetTickCount() - mkchartset[chart_WND_ID].start_time_ms)/10);
		
		for (int i = 0; i < MK_CHART_MAX_PER_WND; i++) {
			for (int j = 0; j < MK_CHART_MAX_PER_WND; j++) {
				if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i][j] < MK_DATA_TYPE_TIME)break;
				else if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i][j] == MK_DATA_TYPE_DOUBLE) {
					mkchartset[chart_WND_ID].plot_data[i][j][mkchartset[chart_WND_ID].plot_buf_index].y.i_data
						= (int)(MK_RANGE_100PERCENT * (*mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pd[i][j]) / mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].d100[i][j]);
				}
				else if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i][j] == MK_DATA_TYPE_INT) {
					mkchartset[chart_WND_ID].plot_data[i][j][mkchartset[chart_WND_ID].plot_buf_index].y.i_data
						= (int)(MK_RANGE_100PERCENT * (*mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pi[i][j]) / mkchartset[chart_WND_ID].value100[MK_DATA_CODE_Y].i100[i][j]);
				}
				else if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i][j] == MK_DATA_TYPE_BOOL) {
					for (int k = 0; k < MK_MAX_BOOL_PER_CHART; k++) {
						mkchartset[chart_WND_ID].plot_data[i][j][mkchartset[chart_WND_ID].plot_buf_index].y.b_data[k]
							= *mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_Y].pb[i][j][k];
					};
				}
				else break;

				if (mkchartset[chart_WND_ID].chart_type == MK_CHART_TYPE_SCATTER) {
					if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_Y][i][j] < MK_DATA_TYPE_TIME)break;
					else if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i][j] == MK_DATA_TYPE_DOUBLE) {
						mkchartset[chart_WND_ID].plot_data[i][j][mkchartset[chart_WND_ID].plot_buf_index].x
							= (int)(MK_RANGE_100PERCENT * (*mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_X].pd[i][j]) / mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].d100[i][j]);
					}
					else if (mkchartset[chart_WND_ID].data_type[MK_DATA_CODE_X][i][j] == MK_DATA_TYPE_INT) {
						mkchartset[chart_WND_ID].plot_data[i][j][mkchartset[chart_WND_ID].plot_buf_index].x
							= (int)(MK_RANGE_100PERCENT * (*mkchartset[chart_WND_ID].pdata[MK_DATA_CODE_X].pi[i][j]) / mkchartset[chart_WND_ID].value100[MK_DATA_CODE_X].i100[i][j]);
					}
					else break;
				}
				else {
					mkchartset[chart_WND_ID].plot_data[i][j][mkchartset[chart_WND_ID].plot_buf_index].x = time_10ms;
				}
			}
		}
	}
	//########################################################################
	int CMKChart::set_chart_spd(int chart_WND_ID, int speed_ms) {
		int temp_s = speed_ms / 1000;
		if (temp_s < 1) mkchartset[chart_WND_ID].spd_dot_per_sec = GRAPH_CHART_DOT_W;
		else 	mkchartset[chart_WND_ID].spd_dot_per_sec = GRAPH_CHART_DOT_W / temp_s;
		return 0;
	}
}