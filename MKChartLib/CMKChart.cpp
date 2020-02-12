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
				str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_W_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_w = _wtoi(buf_t);
				str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_H_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].chart_h = _wtoi(buf_t);
				str_num = GetPrivateProfileString(SET1_SECT_OF_INIFILE, SET_CHART_PLOT_MS_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 4) mkchartset[MK_CHART1].plot_interval_ms = _wtoi(buf_t);

	return 0;
	};
	//########################################################################
	int CMKChart::open_chart(int chartID, HWND hwnd_parent) {
		HWND hwnd;
	

		WNDCLASSEX wc;

		HINSTANCE hInstance = GetModuleHandle(0);

		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = ChartWndProc;// !CALLBACKでreturnを返していないとWindowClassの登録に失敗する
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = TEXT("myChart");
		wc.hIconSm = NULL;
		ATOM fb = RegisterClassExW(&wc);

		mkchartset[chartID].hwnd_chart = CreateWindow(TEXT("myChart"),
			TEXT("MY CHART"),
			WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION,
			CHART_WND_X,
			CHART_WND_Y,
			CHART_WND_W,
			CHART_WND_H,
			hwnd_parent,
			0,
			hInstance,
			NULL);

		ShowWindow(mkchartset[chartID].hwnd_chart, SW_SHOW);
		UpdateWindow(mkchartset[chartID].hwnd_chart);
		return 0;
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
	LRESULT CMKChart::ChartWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
		HDC hdc;

		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_TIMER:
			hdc = GetDC(hwnd);
			TextOut(hdc, 0, 0, L"Test\0", sizeof("Test\0"));
			return 0;
		case WM_CREATE:

			return 0;
		}
		return DefWindowProc(hwnd, msg, wp, lp);
	}


	//########################################################################
	int CMKChart::set_double_data(double* pd, int chartID, int i_item, bool is_x, double d_100) {
		if ((chartID < 0) || (chartID >= MK_CHART_MAX))return - 1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;

		if (is_x) {
			mkchartset[chartID].pdata[i_item][MK_DATA_CODE_X][MK_ADDRESS_DOUBLE] = pd;
			mkchartset[chartID].value100->d100_x = d_100;
			mkchartset[chartID].data_type[i_item][MK_DATA_CODE_X] = MK_DATA_TYPE_DOUBLE;
		}
		else {
			mkchartset[chartID].pdata[i_item][MK_DATA_CODE_Y][MK_ADDRESS_DOUBLE] = pd;
			mkchartset[chartID].value100->d100_y = d_100;
			mkchartset[chartID].data_type[i_item][MK_DATA_CODE_Y] = MK_DATA_TYPE_DOUBLE;
		}
		return 0;
	};
	//########################################################################
	int CMKChart::set_int_data(int* pi, int chartID, int i_item, bool is_x, int i_100) {
		if ((chartID < 0) || (chartID >= MK_CHART_MAX))return -1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;

		if (is_x) {
			mkchartset[chartID].pdata[i_item][MK_DATA_CODE_X][MK_ADDRESS_INT] = pi;
			mkchartset[chartID].value100->i100_x = i_100;
			mkchartset[chartID].data_type[i_item][MK_DATA_CODE_X] = MK_DATA_TYPE_INT;
		}
		else {
			mkchartset[chartID].pdata[i_item][MK_DATA_CODE_Y][MK_ADDRESS_INT] = pi;
			mkchartset[chartID].value100->i100_y = i_100;
			mkchartset[chartID].data_type[i_item][MK_DATA_CODE_Y] = MK_DATA_TYPE_INT;
		}
		if ((chartID < 0) || (chartID >= MK_CHART_MAX))return -1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;
		return 0;
	};
	//########################################################################
	int CMKChart::set_bool_data(bool* pb, int chartID, int i_item, int i_bool) {
		if ((chartID < 0) || (chartID >= MK_CHART_MAX))return -1;
		if ((i_item < 0) || (i_item >= MK_MAX_GRAPH_PER_CHART))return -1;
		if ((i_bool < 0) || (i_item >= MK_ADDRESS_BOOL_MAX))return -1;

		mkchartset[chartID].pdata[i_item][MK_DATA_CODE_X][i_bool] = nullptr; //BOOLのX軸は時間のみ
		mkchartset[chartID].value100->i100_x = 100000;
		mkchartset[chartID].data_type[i_item][MK_DATA_CODE_X] = MK_DATA_TYPE_TIME;

		mkchartset[chartID].pdata[i_item][MK_DATA_CODE_Y][i_bool] = pb;
		mkchartset[chartID].value100->i100_y = 1;
		mkchartset[chartID].data_type[i_item][MK_DATA_CODE_Y] = MK_DATA_TYPE_BOOL;

		return 0;
	};
	//########################################################################
}