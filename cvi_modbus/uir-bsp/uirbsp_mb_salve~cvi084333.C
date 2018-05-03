#include <ansi_c.h>
#include <userint.h>
#include "modbus_poll.h"
#include "mb_salve.h"
#include "uirbsp_mb_salve.h"
#include "includes.h"


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
				DisplayPanel (gSlavePanelHandle);						//��ʾ�������	
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

//������ת��Ϊָ����ʽ�����ݡ�
int	wordtodata(char *word,char 	format)
{
	char	wordlen;
	char	multy;			//ϵ����׼	
	int		tmp;
	int		data;
	int		i;
	
	switch(format)
	{
		case 0:
			multy =10;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '9'){
					//MessagePopup ("ERR MEssage", "�д���9��С0���ַ�");
					
					return 0;
				}
			break;
		case 1:
			multy = 16;
			
			for(i = 0;i < strlen(word);i++)
				if(  ( (word[i]>('a'-1))&& (word[i]>('f'+1)))  
				  || ((word[i]>('A'-1))&& (word[i]>('F'+1))) 
				  || ( (word[i]>('0'-1))&& (word[i]>('9'+1)))  
				  == 0
				 ){
					//MessagePopup ("ERR MEssage", "�з�16�����ַ�");
					
					return 0;
				}
			break;
		case 2:
			multy = 8;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '7'){
					//MessagePopup ("ERR MEssage", "�д���7��С0���ַ�");
					
					return 0;
				}			
			break;
		case 3:
			multy = 2;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '1'){
					//MessagePopup ("ERR MEssage", "�д���1��С0���ַ�");
					
					return 0;
				}			
			break;
		default:
			multy = 10;
			
			for(i = 0;i < strlen(word);i++)
				if(word[i]< '0'||word[i] > '9'){
					//MessagePopup ("ERR MEssage", "�д���9��С0���ַ�");
					
					return 0;
				}
	}

	tmp 	= 1;
	data 	= 0;
	wordlen	= (char)strlen(word);

	while(wordlen)
	{
		data += tmp * (word[--wordlen]-'0');
		tmp  *= multy;
	}
	
	return	data;
}
 
//��ָ����ʽ���ַ���ת��Ϊ���飨�ѿո��,�ֶΣ�
int	stringtobuf(char *string,short *buf,char 	format)				//��ָ����ʽ��ת�����ݡ�
{
	char	word[16];
	char	wordlen;
	int		buflen;
	int		i = 0;
	char	*p = string;
	
	wordlen 	= 0;
	buflen 		= 0;
	
	for(i = 0;i < strlen(string);i++)
	{
		if(*p == ',' || *p == ' ' )	//����ת��
		{
			word[wordlen++] = '\0';
			
			buf[buflen++] = (short)wordtodata(word,format);
			
			wordlen = 0;
			p++;  
		}
		else
		{
			if(wordlen < 16)
			{
				word[wordlen++] = *p;
			}
			p++;  
		}
	}
	return	buflen;
}

//��ʾ���ֵ
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
	
	if(gsMBSlave.writeflg )
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