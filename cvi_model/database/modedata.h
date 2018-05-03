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

#ifndef	MODEL_DATA_H
#define	MODEL_DATA_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <formatio.h> 
#include "includes.h"   


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

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif
