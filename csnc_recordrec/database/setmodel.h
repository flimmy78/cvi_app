/*******************************************************************************
 *   Filename:       setmodel.h
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    ͳ��ģ������ģ������

					 ˫��ѡ�� otr �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Otr �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� OTR �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_COMM_PRIO     ��
 *                                            �� �����ջ�� APP_TASK_COMM_STK_SIZE ����С
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	SET_MODEL_H
#define	SET_MODEL_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "asynctmr.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <formatio.h> 
#include <comconfig.h>         
#include "pc_csnr.h"
#include "includes.h"

/*******************************************************************************
* MACROS
*/
//ODBC ����Դ(32 λ),DSN
#define		ODBC_DNS	"MySql32"


/*******************************************************************************************
/�ṹ��																				 
*******************************************************************************************/
typedef struct _stcModPot_						//IC ��cd����
{
	uint16_t	HigVal;								//ѹ��ֵ
	uint16_t	DipVal;								//����ֵ
}stcModPot;

//����ģ�͵㣬�߶ȣ�����
// 4 bytes
//typedef struct _stcModPot_					//
//{
//	uint16	Hig;								// 2 		�߶�
//	uint16	Oil;								// 2 		����
//}stcModPot;
//����������ģ��
//408 bytes
typedef struct _stcCalcModel_					
{
	stcModPot	sModPot[100];					// 4*100 	����
	uint16		PotNum;							// 2 		ģ����Ч���� 
	uint16		StartOil;                       // 2    	ģ�ͳ�ʼ����   	
	uint16		ModelNum;						// 1		ģ�ͱ��
//	uint8		valid;							// 1        ʹ��
	uint16		CrcCheck;						// 2 		CrcCheck;
}stcCalcModel;



/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	stcCalcModel	gsCalcModel;
extern	int cvi_hdbc_mysql_handle;			//���ݿ����Ӿ��
extern	int globalvalue;
extern	int db_panelHandle;

/*******************************************************************************
* ��    �ƣ� ReadRecFromDB
* ��    �ܣ� �����ݿ���У���ȡ���ݼ�¼
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-06
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �����ݿ��ж�ȡָ�������ݣ������� 
*******************************************************************************/
extern int	ReadRecFromDB(char *tabelname,int	keyval);

/*******************************************************************************
* ��    �ƣ� CreateDBTable
* ��    �ܣ� �������ݱ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע��DBBindColInt 
*******************************************************************************/
extern int	CreateDBTable(char *tabelname);

/*******************************************************************************
* ��    �ƣ� InsertRecToDB
* ��    �ܣ� �������ݼ�¼
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �������ݿ�������ֽ���ӳ�䣬�ڸ�ֵ��д���ݣ���������⡣ 
*******************************************************************************/
extern int CVICALLBACK InsertRecToDB (char *tabelname,stcCalcModel *sCalcModel);


/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
