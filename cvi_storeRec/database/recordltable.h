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
#ifndef	RECORDTABLE_H
#define	RECORDTABLE_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include 	"databaseoperate.h"
#include 	"includes.h"   

#include 	<utility.h>
#include 	<ansi_c.h>
#include 	<cvirte.h>		
#include 	<userint.h>
#include 	<formatio.h> 
#include 	"modedata.h"   

#include 	"oilmodel_db.h"
#include	"cvi_config.h"   
#include	"setpara.h"   

/*******************************************************************************
* MACROS
*/
#define		MODEL_TABLE_NAME			"oilmodeltest"

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
extern	stcOilPara			gsOilPara;			//�����������	
extern	stcThreadModel		gsThreadModel;		//����ģ���߳� ��191017��


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
