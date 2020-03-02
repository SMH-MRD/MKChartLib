#pragma once

#define NAME_OF_INIFILE		L"mkchart"	//iniファイル名
#define EXT_OF_INIFILE		L"ini"		//iniファイル拡張子

#define SET1_SECT_OF_INIFILE					L"SET1"			//CHART1 機能パラメータセクション
#define SET2_SECT_OF_INIFILE					L"SET2"			//CHART2 機能パラメータセクション
#define SET3_SECT_OF_INIFILE					L"SET3"			//CHART3 機能パラメータセクション
#define SET4_SECT_OF_INIFILE					L"SET4"			//CHART4 機能パラメータセクション

#define SET_CHART_TYPE_KEY_OF_INIFILE			L"CHART_TYPE"
#define SET_CHART_X_KEY_OF_INIFILE				L"CHART_WND_X"
#define SET_CHART_Y_KEY_OF_INIFILE				L"CHART_WND_Y"
#define SET_CHART_W_KEY_OF_INIFILE				L"CHART_WND_W"
#define SET_CHART_H_KEY_OF_INIFILE				L"CHART_WND_H"
#define SET_CHART_PLOT_MS_KEY_OF_INIFILE		L"PLOT_MS"


#define CHART_NUM		4
#define PLOT_ITEM_NUM	4
#define CHART_WND_X		600
#define CHART_WND_Y		100
#define CHART_WND_W		800
#define CHART_WND_H		650

#define CHART_GRAPH		0
#define CHART_SCATTER	1

#define GRAPH_CHART_100				50	//100%ドット数
#define GRAPH_CHART_DOT_H			140	//１つのチャートの高さ
#define GRAPH_CHART_DOT_W			720	//１つのチャートの幅
#define SCAT_CHART_100				100	//100%ドット数
#define SCAT_CHART_DOT_H			300	//１つのチャートの高さ
#define SCAT_CHART_DOT_W			300	//１つのチャートの幅
#define CHART_MARGIN_X				50	//チャート書き出しポイント
#define CHART_SPEED_DEF				10000	//チャート表示範囲デフォルトmsec

#define PHASE_NUM			3
#define PHASE_DURATION_DEF	10000	//位相表示時間msec
#define PHASE_INTERVAL		100	//位相表示間隔
#define PHASE_MARGIN_X		25	//位相チャート書き出しポイント
#define PHASE_MARGIN_Y		10	//位相チャート書き出しポイント
#define PHASE_MAX_DEGREE	20	//位相チャート表示最大角度