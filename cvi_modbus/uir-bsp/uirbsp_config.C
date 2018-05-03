#include <userint.h>
#include <rs232.h>
#include <ansi_c.h>

#include <comconfig.h>
#include <modbus_poll.h>
#include <MB_BSP.h>


extern	stcUartConfig		mb_com1config;
extern	int					gCom1PanelHandle;
#define		UIR_COM1CONFIG_NAME		"comconfig.uir"


/********************************************************************************************/
/* PanelCB ():  Quits panel.														*/
/********************************************************************************************/
void	QuitCom1Panel(int	panel)
{
	GetCtrlVal (panel, COM1_PANEL_PORT, 	&mb_com1config.port);	//ȡ�˿�
	GetCtrlVal (panel, COM1_PANEL_BAUT, 	&mb_com1config.baut);	//ȡ������
	GetCtrlVal (panel, COM1_PANEL_BITS, 	&mb_com1config.bits);	//ȡ���ݳ���
	GetCtrlVal (panel, COM1_PANEL_PARITY, 	&mb_com1config.parity);	//ȡУ��
	GetCtrlVal (panel, COM1_PANEL_STOPS, 	&mb_com1config.stops);	//ȡֹͣλ

	mb_com1config.config = 1;										//���ø���
	
	WriteMbComConfigToFile(&mb_com1config);							//��������Ϣд���ļ�

	
	//if( mb_com1config.open == 0)									//δ�򿪣�ֱ�Ӵ�
	{
		if(mb_com1config.stops == 0)
			mb_com1config.stops = 1;
		
		int	status = OpenComConfig (	mb_com1config.port,		//�򿪴���
								   	"",
									mb_com1config.baut,
									mb_com1config.parity,
									mb_com1config.bits,
									mb_com1config.stops,
									256,
									256
					  			);

		char	buf[128];
		if(status < 0 )										//�˿ڴ򿪴���
		{
			sprintf(buf,"���ڲ��ܴ򿪣���ȷ��!��״̬��Ϊ%d",status);
			MessagePopup ("���ô�����Ϣ", buf);

			return ;
		}

		/* 	Make sure Serial buffers are empty */
		FlushInQ  (mb_com1config.port);
		FlushOutQ (mb_com1config.port);
		
		mb_com1config.open = 1;						//�򿪴��ڳɹ���ʶ��λ
	}
	
	HidePanel(gCom1PanelHandle);											//�˳�����
}

int CVICALLBACK OpenCom1Callback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2);
/********************************************************************************************/
/* PanelCB ():  Quits panel.														*/
/********************************************************************************************/
void	ConfigMbComWithFile(void)
{

	mb_com1config.config = 1;										//���ø���
	
	ReadMbComConfigFromFile(&mb_com1config);							//���ļ���ȡ��������Ϣ

	//if( mb_com1config.open == 0)									//δ�򿪣�ֱ�Ӵ�
	{
		if(mb_com1config.stops == 0)
			mb_com1config.stops = 1;
		
		int	status = OpenComConfig (	mb_com1config.port,		//�򿪴���
								   	"",
									mb_com1config.baut,
									mb_com1config.parity,
									mb_com1config.bits,
									mb_com1config.stops,
									255,
									255
					  			);

		char	buf[128];
		if(status < 0 )										//�˿ڴ򿪴���
		{
			sprintf(buf,"���ڲ��ܴ򿪣���ȷ��!��״̬��Ϊ%d",status);
			MessagePopup ("���ô�����Ϣ", buf);

			int	data;
			//���ʻص�����
			OpenCom1Callback(MAIN,MAIN_COMCONFIG,EVENT_COMMIT,&data,data,data);
			
			return ;
		}

		/* 	Make sure Serial buffers are empty */
		FlushInQ  (mb_com1config.port);
		FlushOutQ (mb_com1config.port);
		
		mb_com1config.open = 1;						//�򿪴��ڳɹ���ʶ��λ
	}
}

/********************************************************************************************/
/* PanelCB ():  ����1����													             	*/
/********************************************************************************************/
int CVICALLBACK Com1ConfigOkCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	//int status;
	switch (event)
	{
		case EVENT_COMMIT:

			QuitCom1Panel(panel);

			break;
	}
	return 0;
}

/********************************************************************************************/
/* PanelCB ():  Quits this application.														*/
/********************************************************************************************/
int CVICALLBACK Com1PanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_CLOSE:

			QuitCom1Panel(panel);

			break;
		}
	return 0;
}

int		gCom1PanelHandle;
/********************************************************************************************/
/* ��com1_panel�������ʾ������Ϣ*/
/********************************************************************************************/
void	SetCviCtrlMbComConfig(stcUartConfig * sUartConfig)
{
	 if( gCom1PanelHandle )
	 {
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_PORT, sUartConfig->port);			//ȡ�˿�
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_BAUT, sUartConfig->baut);			//ȡ������
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_BITS, sUartConfig->bits);			//ȡ���ݳ���
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_PARITY,sUartConfig->parity);		//ȡУ��
		 SetCtrlVal (gCom1PanelHandle, COM1_PANEL_STOPS, sUartConfig->stops);		//ȡֹͣλ
	 }
}

int CVICALLBACK OpenCom1Callback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(mb_com1config.open  == 0)
			{
				gCom1PanelHandle	= LoadPanel (0,UIR_COM1CONFIG_NAME, COM1_PANEL);
				DisplayPanel (gCom1PanelHandle);								//��ʾ�������

				ReadMbComConfigFromFile(&mb_com1config);							//���ļ���ȡ��������Ϣ
				
				SetCviCtrlMbComConfig(&mb_com1config);								//����ֵ�����ʾ
			}else{
				if( mb_com1config.open )											//����Ϊ��״̬���رմ���
				{
					mb_com1config.open = 0;										//�ùرձ�ʶ
					CloseCom (mb_com1config.port);								//�رմ���
				}			
			}
			break;	
	}
	return 0;
}