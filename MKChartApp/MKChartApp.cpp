// MKChartApp.cpp : アプリケーションのエントリ ポイントを定義します。
//



#include "stdafx.h"

#include "CMKChart.h"

using namespace MKChart;

int main()

{

	CMKChart *pchartobj = new CMKChart;
	pchartobj->init_chartfunc();
    return 0;
}

