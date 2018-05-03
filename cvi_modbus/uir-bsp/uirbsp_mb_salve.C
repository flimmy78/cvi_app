#include <ansi_c.h>
#include <userint.h>
#include "modbus_poll.h"
#include "mb_salve.h"
#include "uirbsp_mb_salve.h"
#include "includes.h"
#include "stringstr.h"



//�����������
#define		UIR_SLAVE_NAME	"mb_salve.uir"

//ȫ�ֱ���
int	    	gSlavePanelHandle = 0;
extern	 	int panelHandle;						//��

//����ӻ������֡�
strMBSlave	gsMBSlave;								//�ӻ�������

//��salve��壬�ر�����塣
int CVICALLBACK OpenSlaveCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				gSlavePanelHandle	= LoadPanel (0,UIR_SLAVE_NAME, MB_SLAVE);
				DisplayPanel (gSlavePanelHandle);						//��ʾ�ӻ����	
				HidePanel (panelHandle);								//�����������			
		break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.�ر�salve��壬��ʾ����塣						    */
/********************************************************************************************/
int CVICALLBACK mb_SlavePanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			HidePanel(gSlavePanelHandle);								//�˳�����
			gSlavePanelHandle = 0;										//
			
			DisplayPanel(panelHandle);

			break;
		}
	return 0;
}


//��ʱ��ص������е��ã����г��������ѯ��ִ�д�����
void CVI_MBSlavePanelHandle(int panel)
{
	char	string[512];
	int		buflen;
	
	if(gSlavePanelHandle == 0)												//����״̬�£���ִ�к�������
		return;
	
	if(gsMBSlave.writeflg == 0)
	{
		GetCtrlVal(panel,MB_SLAVE_ID,		&gsMBSlave.node) ;				//ȡ�豸ID
		GetCtrlVal(panel,MB_SLAVE_ADDR,		&gsMBSlave.addr) ;				//ȡ���ݵ�ַ
		GetCtrlVal(panel,MB_SLAVE_FORMAT,	&gsMBSlave.format) ;			//ȡ���ݵ�ַ
	
		GetCtrlVal(panel,MB_SLAVE_BUF,string);								//ȡ������
		buflen = stringtobuf(string,&gsMBSlave.buf[gsMBSlave.addr],gsMBSlave.format);//���ַ�����Ϊ����	
	}
	
	if(gsMBSlave.writeflg )													//���ݽ��յ���״̬���и�ֵ
	{
		int	i;
		char	word[16];
		gsMBSlave.writeflg  = 0;
		
		gsMBSlave.len  = (char)(MB_ChTbl[0].RxFrameData[5]+MB_ChTbl[0].RxFrameData[4]*256);		//
		gsMBSlave.addr = (char)(MB_ChTbl[0].RxFrameData[3]+MB_ChTbl[0].RxFrameData[2]*256); 
		
		SetCtrlVal(panel,MB_SLAVE_ADDR,gsMBSlave.addr);
		SetCtrlVal(panel,MB_SLAVE_LEN,gsMBSlave.len);
		
		string[0] = '\0'; 
		for(i = 0; i<gsMBSlave.len;i++ )
		{
			word[0] = '\0';
			switch(gsMBSlave.format)
			{
				case 0:
					sprintf(word,"%d,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;
				case 1:
					sprintf(word,"%x,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;		
				case 2:
					sprintf(word,"%0,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;
				case 3:
					sprintf(word,"%b,",gsMBSlave.buf[gsMBSlave.addr+i]);
					break;						
				default:
					sprintf(word,"%d,",gsMBSlave.buf[gsMBSlave.addr+i]);
			}
			strcat(string,word);
		}
		if(strlen(string))
		{
			string[strlen(string) - 1]  =  '\0' ;
			ResetTextBox(panel, MB_SLAVE_BUF,"");
			SetCtrlVal (panel, MB_SLAVE_BUF,  string);					//���յ������ݴ�ӡ����
		}
	}
}



//slave ���ʱ�ӻص�����
int CVICALLBACK MBSlaveTimerCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			CVI_MBSlavePanelHandle(panel); 
			break;
	}
	return 0;
}