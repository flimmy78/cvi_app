/*******************************************************************************
 *   Filename:       SetPara.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *					 ��������Ӧ�ã�����ƷͨѶЭ�顣 20180423
 *   Description:    
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "setpara.h"

#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include <formatio.h> 
/********************************************************************************************/
/* Constants																				*/
/********************************************************************************************/

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
int				l_eqiupmentcode = 0;	//װ�������룬����������
stcProductInfo  gstrProductInfo;		//��Ʒ����
stcOilPara		gsOilPara;				//��������
stcRunPara		gsRunPara;				//���в���   

/********************************************************************************************/
/* local Prototypes																			*/
/********************************************************************************************/


/********************************************************************************************/
//��ϵͳʱ�䣬ת��ΪstcTime�ṹ
/********************************************************************************************/
void     ReadTime(stcTime * sTime)
{
	struct tm *ptr;
    time_t lt; 
	
    lt=time(NULL);
    ptr=localtime((time_t*)&lt);				//��ϵͳʱ��
	
	sTime->Sec 		= (unsigned char)ptr->tm_sec;
	sTime->Min 		= (unsigned char)ptr->tm_min;
	sTime->Hour 	= (unsigned char)ptr->tm_hour;	
	sTime->Date 	= (unsigned char)ptr->tm_mday;	  	
	sTime->Month 	= (unsigned char)ptr->tm_mon+1;
	sTime->Year 	= (unsigned char)ptr->tm_year-100;	
//	printf("%d-%d-%d %d:%d:%d\r\n",sTime->Year ,sTime->Month,sTime->Date,sTime->Hour,sTime->Min,sTime->Sec);
}


stcCalcModel	gsCalcModel;	//����ģ�ͣ������ã�
extern	int   g_com1systictimes;
/********************************************************************************************/
/* �������ò���      																		*/
//ͨ��l_eqiupmentcode�����������ù��̡�
//�˺�����Ҫѭ��ִ�У������ⲿ���� l_eqiupmentcode
/********************************************************************************************/
void Com_SetParaTask(void)		
{
	unsigned char  buf[256];
	//unsigned char  txdatabuf[256];
	unsigned int   datalen = 0;
	static   int   modelsendnum = 0;			//�������
	unsigned char  clearcode = 1;
	int  	i;
	uint8	*p;
	if(l_eqiupmentcode != 0)					//������ָ��
	{
		datalen = 0;
		
		memcpy(&buf[datalen],(unsigned char *)&l_eqiupmentcode,sizeof(l_eqiupmentcode));
		datalen += sizeof(l_eqiupmentcode);
		
		switch (l_eqiupmentcode)				//����ָ����������ͳ��ģ��ͨѶЭ��
		{
			short  			density; 
			stcTime			sTime;  
			short   		hig; 
			char			modelnum;
			unsigned short 	locotype,loconum;
			//unsigned short	crc;
			unsigned int	calcpara;
			//unsigned int 	recnum;  
			
			case DATA_CARD_DIS:  
							  break; 
			case DATA_CARD_FIN:  
							  break; 
			case DATA_CARD:  
							  break;    
			case DENSITY_CARD: 
							  density = gsOilPara.Density;			//ȡ�ܶ�ֵ

							  memcpy(&buf[datalen],(unsigned char *)&density,sizeof(density));
							  datalen += sizeof(density);
						
							  break;   
			case CALC_PARA: 
							  calcpara = gsOilPara.Slope;			//б��  ��/10000��

							  memcpy(&buf[datalen],(unsigned char *)&calcpara,sizeof(calcpara));
							  datalen += sizeof(calcpara);
							  
							  hig = gsOilPara.Hig;					//�߶�
							  memcpy(&buf[datalen],(unsigned char *)&hig,sizeof(hig));
							  datalen += sizeof(hig);
						
							  break;    							  
			case MODEL_CARD:  
							 
							  break;   
			case TIME_CARD:   
	 						  ReadTime((stcTime *)&sTime);											// ����??   
							  memcpy(&buf[datalen],(unsigned char *)&sTime,sizeof(sTime));
							  datalen += sizeof(sTime);

							  break; 
			case HIGHT_CARD:  
							  hig = gsOilPara.Hig;				//�߶�
							  memcpy(&buf[datalen],(unsigned char *)&hig,sizeof(hig));
							  datalen += sizeof(hig);

							  break; 
			case COPY_CARD:  	
							  
						      break; 
			case MODEL_SELECT_CARD:
							  modelnum = gsOilPara.ModelNum;	//ѡģ
							  
							  memcpy(&buf[datalen],(unsigned char *)&modelnum,sizeof(modelnum));
							  datalen += sizeof(modelnum);

							  break; 
			case FIX_CARD:  
							  locotype = gstrProductInfo.sLocoId.Type;	//����
							  loconum  = gstrProductInfo.sLocoId.Num;	//���

							  memcpy(&buf[datalen],(unsigned char *)&locotype,sizeof(locotype));
							  datalen += sizeof(locotype);
							 
							  memcpy(&buf[datalen],(unsigned char *)&loconum,sizeof(loconum));
							  datalen += sizeof(loconum);							  
							  
				     		  break; 
			case COPY_FRAM_CARD:  
							  break; 
			case EXPAND_CARD:  	
							  break; 
			case SYS_RUN_PARA:  
							  memcpy(&buf[datalen],(unsigned char *)&gsRunPara,sizeof(gsRunPara));
							  datalen += sizeof(gsRunPara);						  
							  break; 	
			case CLEAR_ALL:  	
							  break;		
			case RUN_MODEL_PARA:						//���õ��������õ�����ģ��
					
					clearcode = 0;						//������װ�ñ�ʾ��һ��ֱ������

					if(modelsendnum < 1 + (sizeof(gsCalcModel) / 128))
					{
						p = (uint8 *)&gsCalcModel;
						memcpy(&buf[datalen],(unsigned char *)&modelsendnum,sizeof(modelsendnum));		//�������
						datalen += sizeof(modelsendnum);

						if(sizeof(gsCalcModel) - 128*modelsendnum > 128 )
						{
							memcpy(&buf[datalen],(unsigned char *)(p + 128*modelsendnum),128);
							datalen += 128; 
						}else
						{
							memcpy(&buf[datalen],(unsigned char *)(p + 128*modelsendnum),
								   				 sizeof(gsCalcModel) - 128*modelsendnum );
							
							datalen += sizeof(gsCalcModel) - 128 * modelsendnum ; 
						}
						modelsendnum++;
						
						//i = g_com1systictimes;				  			//��ʱ
						//while(g_com1systictimes - i  < 1000);
					} 

					if(modelsendnum >= 1 + (sizeof(gsCalcModel) / 128)) //���ݷ������
					{
						modelsendnum = 0;
						clearcode = 1;									//�����ʾ�����ý���
						break;						
					}
					
					//i = GetAnsySysTime();
					//while(GetAnsySysTime() - i < 5000 );//
					i  = 100000000;					//��ʱ����
					while(i--);
					break; 							  
							  
			default:
				break;
		}

		memcpy(sCtrl.PC.wr,buf,datalen);			//���ݿ����������ַ�		
		sCtrl.PC.ConnCtrl.sendlen 		= datalen;	//��������������

		sCtrl.PC.ConnCtrl.sourceaddr	= 0xC2;		//Դ��ַ
		sCtrl.PC.ConnCtrl.DestAddr		= 0x82; 	//Ŀ�ĵ�ַ
		sCtrl.PC.ConnCtrl.SendFramNum 	= 0x00; 	//���
		sCtrl.PC.ConnCtrl.FrameCode		= 0x00;		//֡������	
	 
		sCtrl.PC.ConnCtrl.SendFlg 		= 1;		//�������� ��CVI_bsComm,���̣߳�
		
		if( clearcode )
			l_eqiupmentcode = 0;					//���������������
	}
}


