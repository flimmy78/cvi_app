/*******************************************************************************
 *   Filename:       main.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:
					 1�������ļ�
/////////////////////////////////////////////////////////////////////////////
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

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "asynctmr.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>

#include <cvi_ansytimer.h>		 									//��ʱ������

stcAnsyTimerMgr   TimeTmp[10];
char	var[10];
int		timeout[10];
/*---------------------------------------------------------------------------*/
/* This is the Async. timer callback routine.                                */
//	�����ļ���   ��redmorningcn 2017-09-23��
/*---------------------------------------------------------------------------*/
void	TestAnsyTimer(void)
{
	int		i;
	int		times = 0;

	for(i = 0; i< CVI_ANSYTIME_VAR_MAX_NUM;i++)
	{
		 
		 TimeTmp[i].flg 		= 0 ;
		 TimeTmp[i].Settime 	= (short)(100*(i+1));
		 TimeTmp[i].poverFlg 	= &var[i];
		 TimeTmp[i].ptimeout 	= &timeout[i];
		 timeout[i] = 0;
		 TimeTmp[i].startflg 	= 1;	//���Ͽ�ʼ
	}


	cvi_InitAnsyTimer();

	times = 0;
	
	AddTimeOutVarToAnsyTimer(TimeTmp[0]);
	timeout[0] = 0;			//����
	
	printf("start test;systime = %d\r\n",g_AnsyTime);
	while(1)
	{
		for(i =0 ;i < CVI_ANSYTIME_VAR_MAX_NUM; i++)
		{
			if(var[i] == 1 ) 				//��Ч
			{
				times++;
				var[i] = 0;
				printf("time[%d] Time over;systime = %d\r\n",i,g_AnsyTime);
				if(times == 4)
					AddTimeOutVarToAnsyTimer(TimeTmp[1]);

				if(times == 10)
					AddTimeOutVarToAnsyTimer(TimeTmp[2]);

				if(times == 20)
					AddTimeOutVarToAnsyTimer(TimeTmp[3]);

				timeout[i] = 0;

			}
		}
	}
}

/********************************************************************************************/
/* Application entry point.																	*/
/********************************************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)					/* Initialize CVI libraries */
		return -1;	/* out of memory */

	TestAnsyTimer();
	RunUserInterface ();								//����

	return 0;
}
