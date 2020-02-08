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

#define MK_MAX_GRAPH_PER_CHART	4
#define MK_CHART_BUF_MAX		600
#define MK_RANGE_100PERCENT		100000

	typedef struct _stRANGE_SET
	{
		double value_x;
		double value_y;
	}ST_RANGE_SET, *LPST_RANGE_SET;

	typedef struct _stCHART_SET
	{
		int chart_type;
		int num_of_plot;//プロット数
		int chart_x, chart_y, chart_w, chart_h;	//チャート画面の位置　幅、高さ
		int plot_interval_ms;					//表示間隔msec
		int refresh_interval_ms;				//グラフ表示クリア間隔msec
		DWORD	start_time_ms;					//チャート開始時間
		DWORD	latast_plot_time_ms;			//最後にプロットした時間
		INT32	plot_data[MK_MAX_GRAPH_PER_CHART][MK_CHART_BUF_MAX];//チャートプロットバッファ100%=100000
		ST_RANGE_SET	value100[MK_MAX_GRAPH_PER_CHART];//プロットデータ100%の値　時間は、100秒=100%とする
		POINT g_origin[MK_MAX_GRAPH_PER_CHART];		//グラフの原点
		int dot100percent_x, dot100percent_y;//100%に割り当てるdot数


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

		static	int init_chartfunc();
		static	int chart_start(int chart_id);
		static	int chart_stop(int chart_id);
		

	};
}
