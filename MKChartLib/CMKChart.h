#pragma once



namespace MKChart
{
#include "CMKChart_ini.h"
#include <Windows.h>
//#include <windowsx.h>
#include <commctrl.h>
#include <time.h>

#define MK_CHART_MAX			4		//表示可能チャート数
#define MK_CHART_TYPE_BASIC		0		//X:時間　Y:DATA
#define MK_CHART_TYPE_SCATTER	1		//散布図
#define MK_CHART1				0
#define MK_CHART2				1
#define MK_CHART3				2
#define MK_CHART4				3

#define MK_DATA_TYPE_TIME		0
#define MK_DATA_TYPE_DOUBLE		1
#define MK_DATA_TYPE_INT		2
#define MK_DATA_TYPE_BOOL		3

#define MK_MAX_GRAPH_PER_CHART	4
#define MK_CHART_BUF_MAX		600
#define MK_RANGE_100PERCENT		100000

#define MK_DATA_CODE_X			0
#define MK_DATA_CODE_Y			1
#define MK_ADDRESS_INT			0
#define MK_ADDRESS_DOUBLE		0
#define MK_ADDRESS_BOOL_MAX		4
#define MK_ADDRESS_BOOL1		0
#define MK_ADDRESS_BOOL2		1
#define MK_ADDRESS_BOOL3		2
#define MK_ADDRESS_BOOL4		3




	typedef struct _stRANGE_SET
	{
		double d100_x;
		double d100_y;
		int i100_x;
		int i100_y;
	}ST_RANGE_SET, *LPST_RANGE_SET;
	union MK_plot {
		INT32 i_data;
		bool b_data[4];
	};

	typedef struct _stCHART_SET
	{
		int chart_type;
		int num_of_plot;//プロット数
		int chart_x, chart_y, chart_w, chart_h;	//チャート画面の位置　幅、高さ
		int plot_interval_ms;					//表示間隔msec
		int refresh_interval_ms;				//グラフ表示クリア間隔msec
		DWORD	start_time_ms;					//チャート開始時間
		DWORD	latast_plot_time_ms;			//最後にプロットした時間
		MK_plot	plot_data[MK_MAX_GRAPH_PER_CHART][MK_CHART_BUF_MAX];//チャートプロットバッファ100%=100000
		ST_RANGE_SET	value100[MK_MAX_GRAPH_PER_CHART];//プロットデータ100%の値　時間は、100秒=100%とする

		POINT g_origin[MK_MAX_GRAPH_PER_CHART];		//グラフの原点
		int dot100percent_x, dot100percent_y;//100%に割り当てるdot数

		void* pdata[MK_MAX_GRAPH_PER_CHART][2][4];		//プロットデータのアドレス　NULL->時間
		int	data_type[MK_MAX_GRAPH_PER_CHART][2];	//プロットデータの型

		HWND hwnd_chart;				//チャートウィンドウのハンドル
		HDC hdc_mem0;					//合成画面メモリデバイスコンテキスト
		HDC hdc_mem_bg;					//背景画面メモリデバイスコンテキスト
		HDC hdc_mem_graph;				//グラフ画面メモリデバイスコンテキスト
		HDC hdc_mem_inf;				//文字画面メモリデバイスコンテキスト
		HFONT hfont_inftext;			//テキスト用フォント
		BLENDFUNCTION bf;				//半透過設定構造体

		int g_write_line;				//チャート書込ライン

		bool bPrimalyFirst;				//第一画面表示


		int g_ms_per_dot;				//1dotあたりのmsec


	}ST_CHART_SET, *LPST_CHART_SET;

	
	class CMKChart
	{
	public:
		CMKChart();
		~CMKChart();

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//iniファイルパス取得用
		static	WCHAR szLogfolder1[_MAX_PATH];
		static  std::wstring log_path;
		static	ST_CHART_SET mkchartset[MK_CHART_MAX];
	//	static HINSTANCE hInst;


		static	int init_chartfunc();
		static	int set_double_data(double* pd, int chartID, int i_item,bool is_x, double d_100);
		static	int set_int_data(int* pi, int chartID, int i_item, bool is_x, int i_100);
		static	int set_bool_data(bool* pb, int chartID, int i_item, int i_bool);

		static int open_chart(int chartID, HWND hwnd_parent);
		static LRESULT CALLBACK ChartWndProc(HWND, UINT, WPARAM, LPARAM);
		
		static	int chart_start(int chartID, int chart_id);
		static	int chart_stop(int chartID, int chart_id);

	};
}
