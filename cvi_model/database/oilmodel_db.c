/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    2017-10-14
 *   Notes:
 *     				 E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "oilmodel_db.h"
#include "cvi_db.h"

#include "modeltable.h"
#include "oilmath.h"

/*******************************************************************************
* LOCAL VARIABLES
*/

/********************************************************************************************/
// local Prototypes																		
/********************************************************************************************/
int		gdb_panelHandle;
int		gdb_ChildpanelHandle;

int		gmodeltime = 0;  				//��ʱ�����¸�ֵ

/*******************************************************************************
* LOCAL fun
*/
void	InitOilPara(void);


/********************************************************************************************/
/*��oilmodel���																            */
/********************************************************************************************/
int CVICALLBACK OpenOilModelCallback (int panel, int control, int event,
								  	  void *callbackData, int eventData1, int eventData2)
{
	char	tmp;
	switch (event)
	{
		case EVENT_COMMIT:

			if ((gdb_panelHandle 		= LoadPanel (0, "oilmodel_db.uir", SETM_PANEL)) < 0)
				return -1;	
			
			if ((gdb_ChildpanelHandle 	= LoadPanel (gdb_panelHandle, "oilmodel_db.uir", CHILD)) < 0)
				return -1;	
		
			ConnectDB();	//�������ݿ�
	
			DisplayPanel (gdb_panelHandle);
			
			InitModelTableCtrl();						//��ʼ���ṹ��
			InitOilPara();								//
			CreateModelToTableMap(&gsSetModelTable);	//�������ݿ�ӳ��
			
			refreshmodlecallback(panel,SETM_PANEL_MODEL_NUM,EVENT_COMMIT,&tmp,0,0); 
			
			break;
	}
	
	return 0;
}

/********************************************************************************************/
/*ģ�������ʾ															            		*/
/********************************************************************************************/
void 	ModelDistoPanle(void)
{
	stcCalcModel 	*psModel;
	char			tmpbuf[128];
	tmpbuf[127] = '\0';
	
	if(gsSetModelTable.Operate.rdEndFlg == 1 ||gsSetModelTable.Operate.ModefyModelFlg == 1)   						//�Ѿ�����ģ��
	{
		gsSetModelTable.Operate.rdEndFlg = 0;						//
		gsSetModelTable.Operate.ModefyModelFlg = 0;
		
		psModel = &gsSetModelTable.Operate.rdModel;
		//ɾ������еı��ؼ�������
		DeleteTableRows (gdb_panelHandle, SETM_PANEL_TABLE, 1, -1);
		
		//���������ݱ��м�¼����ͬ������
		InsertTableRows (gdb_panelHandle, SETM_PANEL_TABLE, 1, psModel->PotNum, VAL_USE_MASTER_CELL_TYPE);
		
		if (psModel->ModelNum > 0)
		{
			//��������ָ������д�������ؼ���
			for(char i = 1;i < psModel->PotNum +1;i++)
			{
				SetTableCellVal (gdb_panelHandle, SETM_PANEL_TABLE, MakePoint(1,i), psModel->sModPot[i-1].HigVal);
				SetTableCellVal (gdb_panelHandle, SETM_PANEL_TABLE, MakePoint(2,i), psModel->sModPot[i-1].DipVal);
			}
		}
		
		//����������ʾֵ
		sprintf(tmpbuf,"ģ�ͱ��:%02d,ģ�͵���:%02d"
																,psModel->ModelNum
																,psModel->PotNum
			   													);
		SetCtrlVal(gdb_panelHandle, SETM_PANEL_TEXTMSG,tmpbuf);
	
	}
}

//��ʾ����������ʾ��    
void	DisplayModelTabl(int panel)
{
	char 	modelnum;
	GetCtrlVal(gdb_panelHandle,SETM_PANEL_MODEL_NUM, &modelnum);  //ȡҪ���õ�ģ�ͱ��
	
	gsSetModelTable.Operate.rdRecNum 	= modelnum;
	gsSetModelTable.Operate.rdStartFlg 	= 1;					  //��ʼ������
	
	//ReadModelFromTable(modelnum);  							  //��ȡ���ݱ��е����� 
	
	return;
}

//��ȡ���ݣ���ˢ������
int CVICALLBACK refreshmodlecallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
 			DisplayModelTabl(panel);						//��ʼ��

			gsOilPara.cvi_calcOilflg = 1;					//������������

			break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.														*/
/********************************************************************************************/
int CVICALLBACK oilmodelPB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

		    HidePanel(gdb_panelHandle);								//�˳�����
			gdb_panelHandle = 0;
			break;
	}
	return 0;
}

/*******************************************************************************
 * ��    �ܣ�       ȡ�����������.
 * ��ڲ�����       ��
 * ���ڲ����� 	    ��
 * ���� ���ߣ� 	    redmornigcn
 * �������ڣ� 	    2017-05-16
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void    GetModelPanelVal(int panel)
{
	GetCtrlVal(panel,SETM_PANEL_SLOPE, &gsOilPara.Slope);  		//ȡҪ���õ�ȡ�߶�ֵ   
	GetCtrlVal(panel,SETM_PANEL_START, &gsSetModelTable.Operate.rdModel.StartOil);  		
																//ȡҪ���õ�ȡ�߶�ֵ   
	GetCtrlVal(panel,SETM_PANEL_OIL,   &gsOilPara.cvi_oilval);  
	GetCtrlVal(panel,SETM_PANEL_HIGHT, &gsOilPara.cvi_higval);  
}

/********************************************************************************************/
//���㲢��ʾ
/********************************************************************************************/
void	MathAndSetPanel(int panel)
{
	if(gsOilPara.cvi_calcOilflg)
	{
		gsOilPara.cvi_calcOilflg = 0;							//CVI��ʼ��������
		
		gsOilPara.cvi_oilval = GetMathOilVal(gsOilPara.cvi_higval);
		
		SetCtrlVal(panel,SETM_PANEL_OIL,		gsOilPara.cvi_oilval);	//�����ʾ����
		SetCtrlVal(panel,SETM_PANEL_OIL_CHART,	gsOilPara.cvi_oilval);	//�����ʾ����
	}
	
	if(gsOilPara.cvi_calchigflg)
	{
		gsOilPara.cvi_calchigflg = 0;								//cvi��ʼ����߶�
		
		gsOilPara.cvi_higval = GetMathHigVal(gsOilPara.cvi_oilval); 
		SetCtrlVal(panel,SETM_PANEL_HIGHT,gsOilPara.cvi_higval);	//���߶����¸�ֵ
	}
}

/*******************************************************************************
* ��    �ܣ� ���в�����
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
void	InitOilPara(void)
{
	gsOilPara.cvi_calchigflg = 0;
	gsOilPara.cvi_calcOilflg = 0;
}


/********************************************************************************************/
//��ʱ������
/********************************************************************************************/
int CVICALLBACK ModelTimerCallBack (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

////////////////////////////////////////////////////////////������ݱ���ʾ				
			ModelDistoPanle();					
			
			GetModelPanelVal(panel);			//ȡ������
			
			if(sCtrl.PC.sCom->sConfig.open == 1)	//���ڴ���
				MathAndSetPanel(panel);				//������岢��ʾ����ֵ�����ȵ���GetModelPanelVal��
			
			break;
	}
	return 0;
}


/********************************************************************************************/
//�߶�ת��Ϊ����
/********************************************************************************************/
int CVICALLBACK hightToOilCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calcOilflg = 1;		//��������
			break;
	}
	return 0;
}

int CVICALLBACK OilToHightCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{

	
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calchigflg = 1;  		//����߶�
			break;
	}
	return 0;
}


int CVICALLBACK sclopeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calcOilflg = 1;		//��������

			break;
	}
	return 0;
}

int CVICALLBACK modefyHigCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			gsOilPara.cvi_calcOilflg = 1;		//��������

			break;
	}
	return 0;
}

int CVICALLBACK modefyCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			InstallPopup(gdb_ChildpanelHandle);			//�����������
			 
			break;
	}
	return 0;
}

int CVICALLBACK SetModelCallBack (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			l_eqiupmentcode = RUN_MODEL_PARA;  		  //�·�����ģ������
			break;
	}
	return 0;
}

int CVICALLBACK ConfigOkCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	char	modelnum,potnum;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,CHILD_MODELNUM,&modelnum);
			GetCtrlVal(panel,CHILD_POTNUM,&potnum);
			
			if(modelnum && potnum>2 && modelnum<64 && potnum < 100)  //������Ч���ж�
			{
				gsSetModelTable.Operate.ModefyModelFlg = 1;		//
		
				gsSetModelTable.Operate.rdModel.ModelNum = modelnum;
				gsSetModelTable.Operate.rdModel.PotNum   = potnum;	
			}
			else
			{
				MessagePopup("������ʾ","����������ȷ�ϣ�");
			}
			
			RemovePopup(gdb_ChildpanelHandle);		 //�ر��������
			
			break;
	}
	return 0;
}

int CVICALLBACK ModefyModelTableCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point colrow;
	switch (event)
	{
		//��������еı��ؼ���˫��ʱ���������²���
		case EVENT_LEFT_DOUBLE_CLICK:
		
		case EVENT_COMMIT:

			
			//��û���ǰ��������
			GetActiveTableCell (gdb_ChildpanelHandle, CHILD_TABLE, &colrow);
		
			//���ñ��Ϊ���޸�״̬
			SetCtrlAttribute (gdb_ChildpanelHandle, CHILD_TABLE, ATTR_CTRL_MODE, VAL_HOT);
			//��ñ���һ�������ݵ�ID��
			//GetTableCellVal (gdb_ChildpanelHandle, CHILD_TABLE, MakePoint(1, colrow.y), &value);
		
			//��ID����Ϊȫ�ֱ�������
			//globalvalue = value;	
			break;
	}
	return 0;
}

int CVICALLBACK PotNumCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	char	potnum;	
	switch (event)
	{
		case EVENT_COMMIT:
					//���������ݱ��м�¼����ͬ������
			GetCtrlVal(panel,CHILD_POTNUM,&potnum);
			
			DeleteTableRows (gdb_ChildpanelHandle, CHILD_TABLE, 1, -1);
			InsertTableRows (gdb_ChildpanelHandle, CHILD_TABLE, 1, potnum, VAL_USE_MASTER_CELL_TYPE);
		
			break;
	}
	return 0;
}
