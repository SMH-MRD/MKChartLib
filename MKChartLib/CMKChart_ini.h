#pragma once

#define NAME_OF_INIFILE		L"mkchart"	//iniファイル名
#define EXT_OF_INIFILE		L"ini"		//iniファイル拡張子

#define SET1_SECT_OF_INIFILE					L"SET1"			//CHART1 機能パラメータセクション
#define SET2_SECT_OF_INIFILE					L"SET2"			//CHART2 機能パラメータセクション
#define SET3_SECT_OF_INIFILE					L"SET3"			//CHART3 機能パラメータセクション
#define SET4_SECT_OF_INIFILE					L"SET4"			//CHART4 機能パラメータセクション

#define SET_CHART_X_KEY_OF_INIFILE				L"CHART_WND_X"
#define SET_CHART_Y_KEY_OF_INIFILE				L"CHART_WND_Y"
#define SET_CHART_W_KEY_OF_INIFILE				L"CHART_WND_W"
#define SET_CHART_H_KEY_OF_INIFILE				L"CHART_WND_H"
#define SET_CHART_PLOT_MS_KEY_OF_INIFILE		L"PLOT_MS"


#define IDC_CHART_START_PB		10601
#define IDC_CHART_STOP_PB		10602
#define IDC_CHART_RADIO_GRAPH	10603
#define IDC_CHART_RADIO_PHASE	10604


#define ID_CHART_TIMER	1


#define CHART_NUM		4
#define PLOT_ITEM_NUM	4
#define CHART_WND_X		0
#define CHART_WND_Y		0
#define CHART_WND_W		800
#define CHART_WND_H		650

#define CHART_GRAPH		0
#define CHART_PHASE		1

#define CHART_100			50	//100%ドット数
#define CHART_DOT_H			140	//１つのチャートの高さ
#define CHART_DOT_W			720	//１つのチャートの幅
#define CHART_MARGIN_X		50	//チャート書き出しポイント
#define CHART_DURATION_DEF	10000	//チャート表示範囲デフォルトmsec

#define PHASE_NUM			3
#define PHASE_DOT_H			200	//１つの位相チャートの高さ
#define PHASE_DOT_W			200	//１つの位相チャートの幅
#define PHASE_DURATION_DEF	10000	//位相表示時間msec
#define PHASE_INTERVAL		100	//位相表示間隔
#define PHASE_MARGIN_X		50	//位相チャート書き出しポイント
#define PHASE_MARGIN_Y		50	//位相チャート書き出しポイント
#define PHASE_MAX_DEGREE	20	//位相チャート表示最大角度