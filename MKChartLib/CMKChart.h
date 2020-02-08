#pragma once



namespace MKChart
{
#include "CMKChart_ini.h"
#include <Windows.h>
//#include <windowsx.h>
#include <commctrl.h>
#include <time.h>

#define MK_CHART_MAX			4		//�\���\�`���[�g��
#define MK_CHART_TYPE_BASIC		0		//X:���ԁ@Y:DATA
#define MK_CHART_TYPE_SCATTER	1		//�U�z�}
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
		int num_of_plot;//�v���b�g��
		int chart_x, chart_y, chart_w, chart_h;	//�`���[�g��ʂ̈ʒu�@���A����
		int plot_interval_ms;					//�\���Ԋumsec
		int refresh_interval_ms;				//�O���t�\���N���A�Ԋumsec
		DWORD	start_time_ms;					//�`���[�g�J�n����
		DWORD	latast_plot_time_ms;			//�Ō�Ƀv���b�g��������
		INT32	plot_data[MK_MAX_GRAPH_PER_CHART][MK_CHART_BUF_MAX];//�`���[�g�v���b�g�o�b�t�@100%=100000
		ST_RANGE_SET	value100[MK_MAX_GRAPH_PER_CHART];//�v���b�g�f�[�^100%�̒l�@���Ԃ́A100�b=100%�Ƃ���
		POINT g_origin[MK_MAX_GRAPH_PER_CHART];		//�O���t�̌��_
		int dot100percent_x, dot100percent_y;//100%�Ɋ��蓖�Ă�dot��


		HDC hdc_mem0;					//������ʃ������f�o�C�X�R���e�L�X�g
		HDC hdc_mem_bg;					//�w�i��ʃ������f�o�C�X�R���e�L�X�g
		HDC hdc_mem_graph;				//�O���t��ʃ������f�o�C�X�R���e�L�X�g
		HDC hdc_mem_inf;				//������ʃ������f�o�C�X�R���e�L�X�g
		HFONT hfont_inftext;			//�e�L�X�g�p�t�H���g
		BLENDFUNCTION bf;				//�����ߐݒ�\����

		int g_write_line;				//�`���[�g�������C��

		bool bPrimalyFirst;				//����ʕ\��


		int g_ms_per_dot;				//1dot�������msec


	}ST_CHART_SET, *LPST_CHART_SET;

	
	class CMKChart
	{
	public:
		CMKChart();
		~CMKChart();

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//ini�t�@�C���p�X�擾�p
		static	WCHAR szLogfolder1[_MAX_PATH];
		static  std::wstring log_path;

		static	ST_CHART_SET mkchartset[MK_CHART_MAX];

		static	int init_chartfunc();
		static	int chart_start(int chart_id);
		static	int chart_stop(int chart_id);
		

	};
}
