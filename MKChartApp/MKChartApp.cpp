// MKChartApp.cpp : アプリケーションのエントリ ポイントを定義します。
//



#include "stdafx.h"

#include "CMKChart.h"

using namespace MKChart;

static double	double_data[8];
static int		int_data[8];
static bool		bool_data[8];
static UINT IDtimer, IDtimer2;


VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int main()

{
	HWND hwnd;
	WNDCLASS winc;

	HINSTANCE hInstance = GetModuleHandle(NULL);



	// 標準出力にユニコードを表示できるようにする
	setlocale(LC_ALL, "Japanese");

	WCHAR cBuff[256] = L"";
	GetConsoleTitle(cBuff, 256);
	HWND hWnd = FindWindow(NULL, cBuff);
	CMKChart *pchartobj = new CMKChart;
	pchartobj->init_chartfunc();
	pchartobj->set_double_data(&double_data[1], MK_CHART1, 0, 0, 1.0, false);
	pchartobj->chart_start(MK_CHART1,hWnd);
	//コンソールアプリ用Window	作成
#if 0
	{
		winc.style = CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc = WndProc;
		winc.cbClsExtra = winc.cbWndExtra = 0;
		winc.hInstance = hInstance;
		winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		winc.hCursor = LoadCursor(NULL, IDC_ARROW);
		winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		winc.lpszMenuName = NULL;
		winc.lpszClassName = TEXT("KITTY");

		if (!RegisterClass(&winc)) return -1;
		hwnd = CreateWindow(TEXT("KITTY"), TEXT("CLOSE THIS WINDOW FOR QUIT APPLI!!"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 300, 400, 400, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) return -1;
	}
#endif	
	
	IDtimer = SetTimer(NULL, NULL, 100, TimerProc);
	//IDtimer2 = SetTimer(hwnd, 1, 1000, NULL);




	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(100));

	MSG msg;

	// メイン メッセージ ループ:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	char inputc = '0';
	while (inputc != 'q') cin >> inputc;

	KillTimer(NULL, IDtimer);
	delete pchartobj;

	return 0;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {


	double_data[0] += 0.1; if (double_data[0]>6.28)double_data[0] = 0.0;
	double_data[1] = double_data[0] * sin(double_data[0]);
	double_data[2] = double_data[0] * cos(double_data[0]);


	int_data[0] += 1; if (int_data[0] > 100)int_data[0] = 0;
	if (int_data[0] % 10<5)bool_data[0] = true; else bool_data[0] = false;

	if (idEvent == IDtimer) {
		wcout << "From TimerProc  int " << int_data[0] << "   double " << double_data[0] << endl;
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		wcout << "TIMER EVENT TRIGGERRED from AppliWin" << endl;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, int_data[0], L"Test\0", sizeof("Test\0"));
		return 0;
	case WM_CREATE:

		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

