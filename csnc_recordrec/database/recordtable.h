/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    ͳ��ģ������ģ������
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	MODELTABLE_H
#define	MODELTABLE_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "databaseoperate.h"

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <formatio.h> 
#include "includes.h"   

/*******************************************************************************
* MACROS
*/
#define		MODEL_TABLE_NAME			"oilmodeltest"


/*******************************************************************************************
/�ṹ��																				 
*******************************************************************************************/
typedef struct _stcModPot_						//IC ��cd����
{
	unsigned short	HigVal;								//ѹ��ֵ
	unsigned short	DipVal;								//����ֵ
}stcModPot;

typedef struct _stcCalcModel_					
{
	stcModPot			sModPot[100];					// 4*100 	����
	unsigned short		PotNum;							// 2 		ģ����Ч���� 
	unsigned short		StartOil;                       // 2    	ģ�ͳ�ʼ����   	
	unsigned short		ModelNum;						// 1		ģ�ͱ��
//	uint8		valid;									// 1        ʹ��
	unsigned short		CrcCheck;						// 2 		CrcCheck;
}stcCalcModel;

typedef struct	_stcModelOperateCtrl_  
{
	stcCalcModel	wrModel;			//��ģ�ͻ���
	stcCalcModel	rdModel;			//дģ�ͻ���
	char			wrStartFlg;
	char			rdStartFlg;
	char			wrEndFlg;			//��д�ṹ���ʾ������ɣ�
	char			rdEndFlg;			//���ṹ���ʾ�������У� 
	
	int				rdRecNum;			//��ȡ���������
	char			ModefyModelFlg;
}stcModelOperateCtrl;

typedef struct	_stcTableCtrl_
{
	int					*phdbc;				//���ݿ���
	char				tablename[24];		//���ݱ�����
	int					map;				//���ݱ�ӳ��
	int					sql;				//���ӳ����Ч
	stcCalcModel		sMode;				//��Ҫӳ��Ľṹ��
	stcModelOperateCtrl Operate;
}stcModelTableCtrl;						//���ݿ�����

typedef struct _StrOilPara {
    uint8			ModelNum;			//ģ�ͱ��	0~64
    uint8			Rec8;				//����
    int16			Hig;				//�߶�  -500~500
    int16			Density;			//�ܶ�  800~900,     0.xxxx��/�������ף�10000����
    int16			Rec16;				//����
    uint32			Slope;				//����ϵ�� :����ֵ�ٳ�(slope/10000) 
    
	int16			cvi_oilval;			//������������ֵ
	int16			cvi_higval;			//���������߶�ֵ
	uint8			cvi_calcOilflg;		//cvi����������ʶ
	uint8			cvi_calchigflg;		//cvi����߶ȱ�ʶ
	
    uint8           tmp[18];
}StrOilPara;



//db����
typedef struct _stcThreadModel_
{
	//stcModelTableCtrl	*ModelCtrl;
	int					ThreadID;						//����ID
	int					ThreadExit;						//�����ͷű�ʶ
} stcThreadModel;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	stcModelTableCtrl	gsSetModelTable;	//ģ�ͱ�
extern	StrOilPara			gsOilPara;			//�����������	
stcThreadModel				gsThreadModel;		//����ģ���߳� ��191017��


/*******************************************************************************
* ��    �ܣ� ��ȡָ��ֵ�����ݱ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-06
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �����ݿ��ж�ȡָ�������ݣ������� 
*******************************************************************************/
int	ReadModelFromTable(int	keyval);

/*******************************************************************************
* ��    �ܣ� ��ʼ��ģ�ͱ���Ʊ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
void	InitModelTableCtrl(void);

/*******************************************************************************
* ��    �ܣ� �������ݱ�ӳ��
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
int	CreateModelToTableMap(stcModelTableCtrl * stable);

//----------------------------------------------------------------------------
// ��    �ܣ� ��ʼ��ģ�ͱ����ݿ�����̡߳�Ϊʵ�����ݿ�������뿪�����߳�
// ��    ����
// ��    �ߣ� redmornigcn 20171027
//----------------------------------------------------------------------------
int	cvi_InitBspDB(stcThreadModel * T_Ctrl);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
