#pragma once



namespace MKChart
{
#include "CMKChart_ini.h"
#include <Windows.h>
//#include <windowsx.h>
#include <commctrl.h>
#include <time.h>

#define MK_CHART_WND_MAX		4		//�\���\�`���[�g�E�B���h�E��
#define MK_CHART_MAX_PER_WND	4		//1�E�B���h�E������\���\�`���[�g��
#define MK_MAX_GRAPH_PER_CHART	4		//1�̃`���[�g�ɏd�˂ĕ\���\�ȃO���t��
#define MK_MAX_BOOL_PER_CHART	4		//�P�̃O���t�ɏd�˂ĕ\���\��ON/OFF�f�[�^��

#define MK_CHART_TYPE_BASIC		0		//X:���ԁ@Y:DATA
#define MK_CHART_TYPE_SCATTER	1		//�U�z�}

#define MK_CHART1				0
#define MK_CHART2				1
#define MK_CHART3				2
#define MK_CHART4				3

#define MK_DATA_TYPE_NULL		0
#define MK_DATA_TYPE_TIME		1
#define MK_DATA_TYPE_DOUBLE		2
#define MK_DATA_TYPE_INT		3
#define MK_DATA_TYPE_BOOL		4

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

//����{�^��ID
#define IDC_CHART_START_PB		10601
#define IDC_CHART_STOP_PB		10602
#define IDC_CHART_RADIO_OPT1	10603
#define IDC_CHART_RADIO_OPT2	10604

//�N���^�C�}�[ID
#define ID_CHART_TIMER			100

//���b�Z�[�WID
#define WM_MKCHART_INIT			0x0400



	union MK_plot {				//�`���[�g�Ƀv���b�g����f�[�^�@ON/OFF��4�_
		INT32 i_data;
		bool b_data[4];
	};
	typedef struct _stMK_plot {
		INT32 x;
		MK_plot y;
	}ST_PLOT_ELEMENT, *LPST_PLOT_ELEMENT;

	typedef struct _stPLOT_BUF{
		double* pd[MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART];
		int*    pi[MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART];
		bool*	pb[MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART][MK_MAX_BOOL_PER_CHART];
	}ST_PLOT_BUF, *LPST_PLOT_BUF;
	typedef struct _stRANGE_SET //100%�̒l���Z�b�g
	{
		double d100[MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART];
		int    i100[MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART];
	}ST_RANGE_SET, *LPST_RANGE_SET;



#define MK_CHART_DEACTIVE	0
#define MK_CHART_STANDBY	1
#define MK_CHART_ACTIVE		2
#define MK_CHART_PAUSE		3

	
	typedef struct _stCHART_SET
	{
		int chart_status;
		int chart_type;
		int num_of_plot;//�v���b�g��
		int chart_x, chart_y, chart_w, chart_h;	//�`���[�g��ʂ̈ʒu�@���A����
		int chart_field_w, chart_field_h;//GRAPH�`���[�g�̃T�C�Y
		int plot_interval_ms;					//�\���Ԋumsec
		int refresh_interval_ms;				//�O���t�\���N���A�Ԋumsec
		DWORD	start_time_ms;					//�`���[�g�J�n����
		DWORD	latast_plot_time_ms;			//�Ō�Ƀv���b�g��������

	//Window
		HWND hwnd_chart;				//�`���[�g�E�B���h�E�̃n���h��
		HWND hwnd_chart_startPB;		//�`���[�g�X�^�[�gPB�̃n���h��
		HWND hwnd_chart_sopPB;			//�`���[�g�X�g�b�vPB�̃n���h��
		HWND hwnd_chart_opt1_radio;		//�`���[�gOption1PB�̃n���h��
		HWND hwnd_chart_opt2_radio;		//�`���[�gOption2PB�̃n���h��
		HBITMAP hBmap_mem0;
		HBITMAP hBmap_bg;
		HBITMAP hBmap_graph;
		HDC hdc_mem0;					//������ʃ������f�o�C�X�R���e�L�X�g
		HDC hdc_mem_bg;					//�w�i��ʃ������f�o�C�X�R���e�L�X�g
		HDC hdc_mem_graph;				//�O���t��ʃ������f�o�C�X�R���e�L�X�g
		HDC hdc_mem_inf;				//������ʃ������f�o�C�X�R���e�L�X�g
		HFONT hfont_inftext;			//�e�L�X�g�p�t�H���g
		BLENDFUNCTION bf;				//�����ߐݒ�\����

		int g_ms_per_dot;							//1dot�������msec
		int dot100percent_x, dot100percent_y;		//100%�Ɋ��蓖�Ă�dot��
		POINT g_origin[MK_MAX_GRAPH_PER_CHART];		//�O���t�̌��_

		bool bPrimaryDisp;							//���ԃ`���[�g��2�摜�؂�ւ�

		ST_PLOT_BUF pdata[2];											//�v���b�g�f�[�^�̃A�h���X�@x����y��
		ST_RANGE_SET value100[2];										//�v���b�g�f�[�^100%�̒l�@���Ԃ́A100�b=100%�Ƃ���
		int	data_type[2][MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART];	//�v���b�g�f�[�^�̌^



		ST_PLOT_ELEMENT	plot_data[MK_CHART_MAX_PER_WND][MK_MAX_GRAPH_PER_CHART][MK_CHART_BUF_MAX];//�`���[�g�v���b�g�o�b�t�@ ���O�L�^�p
		int plot_buf_index;				//plot_data�̏�������index
		int plot_x;						//plot����x���W

		UINT_PTR timerID;//�v���b�g�^�C�}�[ID

	}ST_CHART_SET, *LPST_CHART_SET;

	
	class CMKChart
	{
	public:
		CMKChart();
		~CMKChart();

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//ini�t�@�C���p�X�擾�p
		static	WCHAR szLogfolder1[_MAX_PATH];
		static  std::wstring log_path;
		static	ST_CHART_SET mkchartset[MK_CHART_WND_MAX];
		static HINSTANCE hInst;


		static	int init_chartfunc();
		static	int init_chart(int chartID);
		static	int close_chart(int chartID);
		static	int set_double_data(double* pd, int chart_WND_ID, int i_chart, int i_item, double d_100, bool is_x);
		static	int set_int_data(int* pi, int chart_WND_ID, int i_chart, int i_item, int i_100, bool is_x);
		static	int set_bool_data(bool* pb, int chart_WND_ID, int i_chart, int i_item, int i_bool);

		static HWND open_chart(int chartID, HWND hwnd_parent);
		static LRESULT CALLBACK ChartWndProc_A(HWND, UINT, WPARAM, LPARAM);//Time-Data Graph
		static LRESULT CALLBACK ChartWndProc_B(HWND, UINT, WPARAM, LPARAM);//Data-Data Graph
		
		static	int chart_start(int chartID, HWND hwnd_parent);
		static	int chart_plot(int chartID);
		static	int chart_stop(int chartID);

		static int get_chartID(HWND hWnd) { for (int i = 0; i < MK_CHART_WND_MAX; i++) { if (hWnd == mkchartset[i].hwnd_chart) return i; } return 3; }

	
	};
}
