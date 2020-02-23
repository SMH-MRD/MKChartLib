#include <stdexcept>

#include "stdafx.h"
#include "CMKChart.h"

namespace MKChart {

	CMKChart::CMKChart(){}
	CMKChart::~CMKChart(){}

	WCHAR CMKChart::szInipath[_MAX_PATH], CMKChart::szDrive[_MAX_DRIVE], CMKChart::szPath[_MAX_PATH], CMKChart::szFName[_MAX_FNAME], CMKChart::szExt[_MAX_EXT];
	WCHAR CMKChart::szLogfolder1[_MAX_PATH];
	std::wstring  CMKChart::log_path;
	ST_CHART_SET CMKChart::mkchartset[MK_CHART_WND_MAX];
	HINSTANCE CMKChart::hInst;

	//########################################################################
	static double dummy_d = 0.0;
	static int dummy_i = 0;
	static bool dummy_b = false;
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
		HWND hwnd;
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
#if 0
	LRESULT CMKChart::ChartWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

		BITMAP bmp_info;
		static HWND hinfchk;
		int nFramX, nFramY, nCaption, scrw, scrh, winw, winh, winx, winy, mob_speed = 4;
		HDC hdc;
		TCHAR szBuf[128];
		HMENU hsubmenu, hpopmenu;
		HWND tmpwnd;


		switch (msg) {
		case WM_CREATE: {

			nFramX = GetSystemMetrics(SM_CXSIZEFRAME);		//ウィンドウ周囲の幅
			nFramY = GetSystemMetrics(SM_CYSIZEFRAME);		//ウィンドウ周囲の高さ
			nCaption = GetSystemMetrics(SM_CYCAPTION);		//タイトルバーの高さ
			scrw = GetSystemMetrics(SM_CXSCREEN);			//プライマモニタの幅
			scrh = GetSystemMetrics(SM_CYSCREEN);			//プライマモニタの高さ
/*
			hwnd_startPB = CreateWindow(
				L"BUTTON", L"Start",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				CHART_WND_W - 100, CHART_WND_H - 70, 38, 25, hWnd, (HMENU)IDC_CHART_START_PB, Chart::hInst, NULL);
			hwnd_stopPB = CreateWindow(
				L"BUTTON", L"Stop",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				CHART_WND_W - 58, CHART_WND_H - 70, 38, 25, hWnd, (HMENU)IDC_CHART_STOP_PB, Chart::hInst, NULL);
			hwnd_radio_g = CreateWindow(
				L"BUTTON", L"graph",
				WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
				CHART_WND_W - 150, 5, 60, 25, hWnd, (HMENU)IDC_CHART_RADIO_GRAPH, Chart::hInst, NULL);
			hwnd_radio_p = CreateWindow(
				L"BUTTON", L"phase",
				WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
				CHART_WND_W - 80, 5, 60, 25, hWnd, (HMENU)IDC_CHART_RADIO_PHASE, Chart::hInst, NULL);



			init_chart();

			hdc = GetDC(hWnd);
			HBITMAP hDummy = CreateCompatibleBitmap(hdc, st_disp.chart_w, st_disp.chart_h);
			SelectObject(st_disp.hdc_mem0, hDummy);		//合成画像（背景＋グラフ）
			hDummy = CreateCompatibleBitmap(hdc, st_disp.chart_w, st_disp.chart_h);
			SelectObject(st_disp.hdc_mem_bg, hDummy);	//背景画像
			hDummy = CreateCompatibleBitmap(hdc, st_disp.chart_w, st_disp.chart_h);
			SelectObject(st_disp.hdc_mem_graph, hDummy);//グラフ画像

			PatBlt(st_disp.hdc_mem0, 0, 0, st_disp.chart_w, st_disp.chart_h, WHITENESS);//HDC hdc, int x,int y, int w, int h,DWORD rop
			PatBlt(st_disp.hdc_mem_bg, 0, 0, st_disp.chart_w, st_disp.chart_h, WHITENESS);//HDC hdc, int x,int y, int w, int h,DWORD rop
			PatBlt(st_disp.hdc_mem_graph, 0, 0, st_disp.chart_w, st_disp.chart_h, WHITENESS);//HDC hdc, int x,int y, int w, int h,DWORD rop

			ReleaseDC(hWnd, hdc);
			DeleteObject(hDummy);

			//SelectObject(st_disp.hdc_mem_bg, GetStockObject(BLACK_PEN));

			POINT linkpt[2];
			POINT toPT;

			SelectObject(st_disp.hdc_mem_bg, GetStockObject(DC_PEN));
			SetDCPenColor(st_disp.hdc_mem_bg, RGB(128, 128, 128));
			for (int i = 0; i < CHART_NUM; i++) {
				MoveToEx(st_disp.hdc_mem_bg, st_disp.g_origin[i].x, st_disp.g_origin[i].y, NULL);
				LineTo(st_disp.hdc_mem_bg, st_disp.g_origin[i].x + CHART_DOT_W, st_disp.g_origin[i].y);

				MoveToEx(st_disp.hdc_mem_bg, st_disp.g_origin[i].x, st_disp.g_origin[i].y + CHART_DOT_H / 2 - 5, NULL);
				LineTo(st_disp.hdc_mem_bg, st_disp.g_origin[i].x, st_disp.g_origin[i].y - CHART_DOT_H / 2 + 5);

			}

			//TransparentBlt(st_disp.hdc_mem0, 0, 0, st_disp.chart_w, st_disp.chart_h, st_disp.hdc_mem_graph, 0, 0, st_disp.chart_w, st_disp.chart_h, RGB(255, 255, 255));
			//BitBlt(st_disp.hdc_mem0, 0, 0, st_disp.chart_w, st_disp.chart_h, st_disp.hdc_mem_bg, 0, 0, SRCCOPY);
*/

		}break;

		case WM_TIMER: {
			std::wcout << "Timer Triggerred from Lib";
/*
			if (st_disp.disp_type == CHART_GRAPH) {

				st_disp.g_write_line += st_disp.g_ms_per_dot * st_disp.plot_interval_ms;
				if (st_disp.g_write_line >= CHART_WND_W * 2) {
					st_disp.g_write_line -= CHART_WND_W * 2;
				}
				int iline = 1;
				double tem_d = 0.1;
				plot_graph(iline, &tem_d);
			}
			else if (st_disp.disp_type == CHART_PHASE) {
				;
			}
			else;
			InvalidateRect(Chart::hwnd_chart, NULL, FALSE);
		}break;
		case WM_COMMAND:
			switch (LOWORD(wp)) {
			case IDC_CHART_START_PB:
				SetTimer(hwnd_chart, ID_CHART_TIMER, Chart::chart_interval_ms, NULL);
				break;
			case IDC_CHART_STOP_PB:
				KillTimer(hwnd_chart, ID_CHART_TIMER);
				break;
			case IDC_CHART_RADIO_GRAPH:
				st_disp.disp_type = CHART_GRAPH;
				SendMessage(hwnd_radio_g, BM_SETCHECK, BST_CHECKED, 0L);
				SendMessage(hwnd_radio_p, BM_SETCHECK, BST_UNCHECKED, 0L);
				break;
			case IDC_CHART_RADIO_PHASE:
				st_disp.disp_type = CHART_PHASE;
				SendMessage(hwnd_radio_p, BM_SETCHECK, BST_CHECKED, 0L);
				SendMessage(hwnd_radio_g, BM_SETCHECK, BST_UNCHECKED, 0L);
				break;

				*/
			}break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
/*
			hdc = BeginPaint(hWnd, &ps);
			TransparentBlt(st_disp.hdc_mem0, 0, 0, st_disp.chart_w, st_disp.chart_h, st_disp.hdc_mem_bg, 0, 0, st_disp.chart_w, st_disp.chart_h, RGB(255, 255, 255));
			TransparentBlt(st_disp.hdc_mem0, 0, 0, st_disp.chart_w, st_disp.chart_h, st_disp.hdc_mem_graph, 0, 0, st_disp.chart_w, st_disp.chart_h, RGB(255, 255, 255));

			BitBlt(
				hdc,				//HDC hdc
				0,					//int x
				0,					//int y
				st_disp.chart_w,	//int cx
				st_disp.chart_h,	//int c
				st_disp.hdc_mem0,	//HDC hdcSrc
				0,					//int x1
				0,					//int y1
				SRCCOPY//DWORD rop
			);
			EndPaint(hWnd, &ps);
*/
			break;
		}
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_KEYDOWN:
			if (wp == 'Q') {
				DestroyWindow(hWnd);
			}
			break;
		default:
			return DefWindowProc(hWnd, msg, wp, lp);
		}
		return 0;
	}
#endif


	//########################################################################	
	static int test_count;

	LRESULT CMKChart::ChartWndProc_A(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

		BITMAP bmp_info;
		static HWND hinfchk;
		int winw, winh, winx, winy;
		HDC hdc;
		TCHAR szBuf[128];
		HMENU hsubmenu, hpopmenu;
		HWND tmpwnd;

		switch (msg) {
		case WM_DESTROY:
			close_chart(get_chartID(hwnd));
			PostQuitMessage(0);
			return 0;
		case WM_TIMER:
			test_count++;
//			hdc = GetDC(hwnd);
//			TextOut(hdc, 0, test_count%100, L"Test\0", sizeof("Test\0"));
			return 0;
		case WM_MKCHART_INIT:{
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
			
			//描画用デバイスコンテキスト確保
			mkchartset[chartID_work].hdc_mem0 = CreateCompatibleDC(NULL);		//ベース画面
			mkchartset[chartID_work].hdc_mem_bg = CreateCompatibleDC(NULL);		//背景画面
			mkchartset[chartID_work].hdc_mem_graph = CreateCompatibleDC(NULL);	//プロット画面


			HDC hdc = GetDC(hwnd);
			HBITMAP hDummy = CreateCompatibleBitmap(hdc, mkchartset[chartID_work].chart_field_w, mkchartset[chartID_work].chart_field_h);
			SelectObject(mkchartset[chartID_work].hdc_mem0, hDummy);		//合成画像（背景＋グラフ）
			hDummy = CreateCompatibleBitmap(hdc, mkchartset[chartID_work].chart_field_w, mkchartset[chartID_work].chart_field_h);
			SelectObject(mkchartset[chartID_work].hdc_mem_bg, hDummy);	//背景画像
			hDummy = CreateCompatibleBitmap(hdc, mkchartset[chartID_work].chart_field_w, mkchartset[chartID_work].chart_field_h);
			SelectObject(mkchartset[chartID_work].hdc_mem_graph, hDummy);//グラフ画像

			PatBlt(mkchartset[chartID_work].hdc_mem0, 0, 0, mkchartset[chartID_work].chart_field_w, mkchartset[chartID_work].chart_field_h, WHITENESS);//HDC hdc, int x,int y, int w, int h,DWORD rop
			PatBlt(mkchartset[chartID_work].hdc_mem_bg, 0, 0, mkchartset[chartID_work].chart_field_w, mkchartset[chartID_work].chart_field_h, WHITENESS);//HDC hdc, int x,int y, int w, int h,DWORD rop
			PatBlt(mkchartset[chartID_work].hdc_mem_graph, 0, 0, mkchartset[chartID_work].chart_field_w, mkchartset[chartID_work].chart_field_h, WHITENESS);//HDC hdc, int x,int y, int w, int h,DWORD rop

			ReleaseDC(hwnd, hdc);
			DeleteObject(hDummy);



			POINT linkpt[2];
			POINT toPT;
			//SelectObject(mkchartset[chartID_work].hdc_mem_bg, GetStockObject(BLACK_PEN));
			SelectObject(mkchartset[chartID_work].hdc_mem_bg, GetStockObject(DC_PEN));
			SetDCPenColor(mkchartset[chartID_work].hdc_mem_bg, RGB(128, 128, 128));

			for (int i = 0; i < CHART_NUM; i++) {
				MoveToEx(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y, NULL);
				LineTo(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x + GRAPH_CHART_DOT_W, mkchartset[chartID_work].g_origin[i].y);

				MoveToEx(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y + GRAPH_CHART_DOT_H / 2 - 5, NULL);
				LineTo(mkchartset[chartID_work].hdc_mem_bg, mkchartset[chartID_work].g_origin[i].x, mkchartset[chartID_work].g_origin[i].y - GRAPH_CHART_DOT_H / 2 + 5);

			}

			//タイマー起動
			mkchartset[chartID_work].timerID = SetTimer(hwnd, ID_CHART_TIMER+ chartID_work, mkchartset[chartID_work].plot_interval_ms, NULL);

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
			BitBlt(
					hdc,				//HDC hdc
					0,0, mkchartset[chartID_work].chart_w, mkchartset[chartID_work].chart_h, //int x int y int cx int cy
					mkchartset[chartID_work].hdc_mem0,	//HDC hdcSrc
					0,	0,				//int x1 int y1
					SRCCOPY//DWORD rop
			);

			EndPaint(hwnd, &ps);

			break;
		}

			return 0;
		}
		return DefWindowProc(hwnd, msg, wp, lp);
	}

	//########################################################################	
	LRESULT CMKChart::ChartWndProc_B(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

		BITMAP bmp_info;
		static HWND hinfchk;
		int winw, winh, winx, winy;
		HDC hdc;
		TCHAR szBuf[128];
		HMENU hsubmenu, hpopmenu;
		HWND tmpwnd;

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

		//SAMPLE Radio button 表示
		if (mkchartset[chartID].chart_type == CHART_GRAPH) SendMessage(mkchartset[chartID].hwnd_chart_opt1_radio, BM_SETCHECK, BST_CHECKED, 0L);
		if (mkchartset[chartID].chart_type == CHART_SCATTER)  SendMessage(mkchartset[chartID].hwnd_chart_opt2_radio, BM_SETCHECK, BST_CHECKED, 0L);

		if (mkchartset[chartID].chart_type == CHART_SCATTER) {
			//SAMPLE Radio button 表示
			SendMessage(mkchartset[chartID].hwnd_chart_opt2_radio, BM_SETCHECK, BST_CHECKED, 0L);
			//CHART原点
			for (int i = 0; i < PHASE_NUM; i++) {
				mkchartset[chartID].g_origin[i].x = (PHASE_MARGIN_X + PHASE_DOT_W)*i + PHASE_DOT_W / 2;
				mkchartset[chartID].g_origin[i].y = PHASE_MARGIN_Y + PHASE_DOT_H / 2;
			}
			//描画表示時間
			mkchartset[chartID].refresh_interval_ms = PHASE_DURATION_DEF;
			mkchartset[chartID].g_ms_per_dot = 0;//散布図は未使用

			mkchartset[chartID].chart_field_w = CHART_WND_W;
			mkchartset[chartID].chart_field_h = CHART_WND_H;

			mkchartset[chartID].dot100percent_x = SCAT_CHART_100;
			mkchartset[chartID].dot100percent_y = SCAT_CHART_100;

		}
		else {
			for (int i = 0; i < CHART_NUM; i++) {
				mkchartset[chartID].g_origin[i].x = CHART_MARGIN_X;
				mkchartset[chartID].g_origin[i].y = GRAPH_CHART_DOT_H / 2 + GRAPH_CHART_DOT_H * i + 25;
			}
			mkchartset[chartID].refresh_interval_ms = CHART_DURATION_DEF;//時間グラフは未使用
			
			mkchartset[chartID].g_ms_per_dot = CHART_DURATION_DEF / GRAPH_CHART_DOT_W;
			
			mkchartset[chartID].chart_field_w = GRAPH_CHART_DOT_W * 4;
			mkchartset[chartID].chart_field_h = GRAPH_CHART_DOT_H * CHART_NUM;
			
			mkchartset[chartID].bPrimaryDisp = true;//初期値は第１画面表示

			mkchartset[chartID].dot100percent_x = CHART_DURATION_DEF;
			mkchartset[chartID].dot100percent_y = GRAPH_CHART_100;

		}

		mkchartset[chartID].plot_buf_index = 0;

		return 0;
	}
	//########################################################################
	int CMKChart::close_chart(int chartID) {

		//タイマー解放
		KillTimer(NULL, mkchartset[chartID].timerID);

		//描画用デバイスコンテキスト解放
		DeleteDC(mkchartset[chartID].hdc_mem0);			//ベース画面
		DeleteDC(mkchartset[chartID].hdc_mem_bg);		//背景画面
		DeleteDC(mkchartset[chartID].hdc_mem_graph);	//プロット画面
		DestroyWindow(mkchartset[chartID].hwnd_chart);  //ウィンドウ破棄
		return 0;
	}
	//########################################################################
	int CMKChart::set_double_data(double* pd, int chart_WND_ID, int i_chart, int i_item, double d_100, bool is_x) {
		if ((chart_WND_ID < 0) || (i_chart >= MK_CHART_WND_MAX))return - 1;
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
		if(mkchartset[chartID].chart_status<MK_CHART_STANDBY){//初期化未完
			if (open_chart(chartID, hwnd_parent) != NULL) init_chart(chartID);
		}
		return 0;
	};
	//########################################################################
}