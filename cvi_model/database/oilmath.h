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

#ifndef	OILMATH_H
#define	OILMATH_H
/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "oilmodel_db.h"
#include "modeltable.h"


/*******************************************************************************
 * ��    �ƣ�       GetMathOilVal
 * ��    �ܣ�       �������������ݸ߶�ֵ�������ݻ���������ϵ���ȼ�������.
 * ��ڲ�����       ��
 * ���ڲ����� 	    ��
 * ���� ���ߣ� 	    redmornigcn
 * �������ڣ� 	    2017-05-16
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint16    GetMathOilVal(int16   hig);

/*******************************************************************************
 * ��    �ܣ�       ����߶�ֵ�����������������ݻ���������ϵ���ȼ�������.
 * ��ڲ�����       ��
 * ���ڲ����� 	    ��
 * ���� ���ߣ� 	    redmornigcn
 * �������ڣ� 	    2017-10-16
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint16    GetMathHigVal(int16   oil);

#endif