/*******************************************************************************
 *   Filename:       setmodel.h
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    ȡ�ͳ����ݼ�¼

 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	OIL_RECORD_H
#define	OIL_RECORD_H

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
#include "includes.h"

/*******************************************************************************
* MACROS
*/
//ODBC ����Դ(32 λ),DSN
#define		ODBC_DNS	"MySql32"


/*******************************************************************************************
/�ṹ��																				 
*******************************************************************************************/

typedef  struct _stcFlshRec   	//�����ͳ߼�¼���ݽṹ
{
	uint32	StoreCnt;         	//�洢��ˮ��    		4   ׷�ټ�¼��

	uint8	RecTypCod;       	//��¼����          	1   �������ͣ��������ϰ࿨���°࿨�����ݼ�¼��
	uint8	RelSpeed[3];      	//ʵ��              	3   D9~D0��ʵ�٣�D19~D10��Ԥ��

	uint32	Time;          	    //��/��/ʱ/��/��      	4   D5~D0:��,D11~D6:��,D16~D12:ʱD21~D17���գ�
	                               	//                      	D25~D22���� ;D26~D31:��
	uint8	LocoTyp;          	//�����ͺ�          	1   
	uint8	E_LocoTyp;        	//�����ͺ���չ�ֽ�  	1   �����ͺ������ֽ�,������LKJ2000��ʽ��ͬ
	uint16 	LocoNum;       	    //������            	2	

	uint32 	TrainTyp;     	    //��������          	4   ��������,���α����·���(����[2005]72���ļ�)
	                             	//                      	�ĳ��������ʶ��,������LKJ2000��ʽ��ͬ
	                             	
	uint8	TrainNum[3];     	//�������ֲ���      	3   ���α����·���(����[2005]72����)�ĳ������ݲ���
	uint8 	Car_Truck;       	//��/������/��       	1   D0��0/1 �� ��/��   D1��0/1 �� ��/��   
	 
	uint8 	VoitureCnt;       	//����              	1	
	uint8 	KmMark[3];   		//�����            	3   ��λ����

	uint16 	Weight;       	    //����              	2
	uint16 	PlanLen;       	    //�Ƴ�              	2   ��λ��0.1   

	uint16 	MstDriverNum;  	    //˾����            	2	
	uint8 	E_MstDriverNum; 	//˾������չ�ֽ�    	1   
	uint8 	E_SlvDriverNum;   	//��˾������չ�ֽ�  	1   

	uint16 	SlvDriverNum;  	    //��˾����          	2   
	uint16	DriverUnitNum;  	//˾����λ���      	2   //����Ψһȷ��˾��

	uint8 	RoadNum;          	//���κ�(��·��)     	1	
	uint8  	RelRoadNum;     	//ʵ�ʽ�·��         	1   �����ʽ��LKJ2000��ͬ   
	uint8  	StationNum;     	//��վ��            	1
	uint8  	E_StationNum;   	//��վ����չ�ֽ�    	1   ��վ����չ�ֽ�

	uint8 	SignalTyp;        	//�źŻ�����        	1   B2-B0 :2-��վ,3-��վ,4-ͨ��,5-Ԥ��,6-����
	uint8 	LocoSign;        	//�����ź�          	1   B4 = 0/1  ����/���;   B3~B0 0-�޵�,1-��,2-��, 
	                            	//                      	3-˫��,4-���,5-��,6-��,7-�̻�,8-��
	uint8 	LocoWorkState;    	//��������          	1   b0-��λ,B1-���,B2-��ǰ,B3-�ƶ�,B4-ǣ��
	uint8 	LocoState;      	//װ��״̬          	1   B0 = 1/0 - ����/���; B2 = 1/0 - ����/�ǵ���

//	uint8 	SignalNum[2];      	//�źŻ����        	2   
//	uint8 	LocoPipePress[2]; 	//�г���ѹ          	2   B9-B0:��ѹ(��λ:1kPa)

	uint16	Myspeed1;			//�Բ��ٶ�1				2
	uint16	Myspeed2;			//�Բ��ٶ�2				2	
	  
	uint32 	MstDip;           	//��������          	4   ���ͳ�����(���ӻ�����ʱΪ��������,����Ϊ����������)

//	uint32 	SlvDip;           	//�ӻ�����          	4   ���ͳ�����(���ӻ�����ʱΪ�ӻ�����,���������ֵΪ��)
	uint32	MyKileMeter;		//�����				4
		
	int32 	MyMstLocoPower;     //������������       	4   ��������豸����

//	int32 	SlvLocoPower;     	//�ӻ���������       	4   �ӻ�����豸����
	uint32	MyPower;			//�ۼƵ���				4	
	//090901
 	//uint16	MstDip1Prs;        	//ѹǿ            		2   �����ͳ�1ѹǿֵ
	//uint16	MstDip2Prs;        	//ѹǿ            		2   �����ͳ�2ѹǿֵ
	int16		Myhig1;				//Һλ�߶�1				2	
	int16		Myhig2;				//Һλ�߶�2				2							

	uint16	SlvDip1Prs;       	//ѹǿ            		2   �ӻ��ͳ�1ѹǿֵ
	uint16 	SlvDip2Prs;       	//ѹǿ            		2   �ӻ��ͳ�2ѹǿֵ
	
	uint8  	MyYear;           	//��      				1   װ��ʱ�����
	uint8 	MyMonth;         	//��      				1   װ��ʱ�����
	uint8 	MyData;          	//��      				1   װ��ʱ�����
	uint8 	MyHour;           	//ʱ      				1   װ��ʱ���ʱ
	
	uint8 	MyMinute;     		//��      				1   װ��ʱ��ķ�
	uint8 	MySecond;       	//��       				1   װ��ʱ�����
	uint16	MstDensity;			//�ܶ�							2	����ȼ���ܶ�
	
//	uint16	SlvDensity;			//�ܶ�						2	�ӻ�ȼ���ܶ�
//	uint16	GpsHeight;			//�߶�						2	�����߶�
	int16	MyAddspeed;			//�Բ���ٶ�					2
	uint16	MyDip;				//�Բ�����							2
		
	int32	GpsLongitude;		//����					4	��������
	int32	GpsLatitude;		//γ��					4	����γ��
		
	int16	MstEngRotSpd;		//�������ͻ�ת��		2	�������ͻ�ת��
//	int16	SlvEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��
	int16	MyEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��

	//�������� 
	//���Լ�ʱ��оƬ���׵�������
	uint16 	JcRealType;			//�����ͺ�				2   �ⲿ���õĻ����ͺ�
	uint16 	JcRealNo;			//�������				2   �ⲿ���õĻ������
	
//	uint16 	MstPotPress;		//������ѹ				2	Ԥ���Ӽ��	
//	uint16 	SlvPotPress;		//�ӻ���ѹ				2	Ԥ���Ӽ��	
	uint16	MyDip1Tmp;	  		//�ͳ�1�¶�
	uint16	MyDip2Tmp;			//�ͳ�2�¶�
		
//	uint16 	MstPot1;			//��������1				2	Ԥ���Ӽ��	
//	uint16 	MstPot2;			//��������2				2	Ԥ���Ӽ��
	uint16	MyDip1Den;
	uint16	MyDip2Den;	

	
	
//	uint16 	SlvPot1;			//�ӻ�����1				2	Ԥ���Ӽ��		
//	uint16 	SlvPot2;			//�ӻ�����2				2	Ԥ���Ӽ��
	uint16	MyDip1Err;
	uint16	MyDip2Err;
	
	uint16 	MaxSpeed;			//����					2	Ԥ���Ӽ��	
//	uint16 	MstOcurrent;		//����ԭ�ߵ���   		2	Ԥ���Ӽ��
	uint16	ErrNum;				//���й�������			2	
	
	
	uint8	ErrorCode;			//���ϴ���				1   0~255
//	uint8 	DipValChgState;  	//�����仯״̬   		1   �����仯����֣����ͳ�����/��С���仯ƽ�ȡ���΢���������Ҳ���
	uint8	MyLocoWorkState;	//�Բ����״̬			1
	//090901
	uint8	MstDipTemp;			//�¶�					1	�����¶�
	uint8	OilBoxModel;		//����ģ��				1	�����������
	
	uint8	SoftVes;        	//�����汾          	1   
	uint8	Reserve1;        	//Ԥ��          		1  	
//	uint16	Reserve0;        	//Ԥ��          		2   
	uint16 	CrcCheck;         	//�洢��У���    		2   Flash��¼�洢CRCУ��
}stcFlshRec;



typedef  struct _stcFlshRecSql   	//�����ͳ߼�¼���ݽṹ_���ݿ����
{
	uint32	StoreCnt;         	//�洢��ˮ��    		4   ׷�ټ�¼��

	uint32	RecTypCod;       	//��¼����          	1   �������ͣ��������ϰ࿨���°࿨�����ݼ�¼��
	uint32	RelSpeed;      		//ʵ��              	3   D9~D0��ʵ�٣�D19~D10��Ԥ��

	uint32	Time;          	    //��/��/ʱ/��/��      	4   D5~D0:��,D11~D6:��,D16~D12:ʱD21~D17���գ�
	                          	//                      	D25~D22���� ;D26~D31:��
	uint32	LocoTyp;          	//�����ͺ�          	1   
	uint32	E_LocoTyp;        	//�����ͺ���չ�ֽ�  	1   �����ͺ������ֽ�,������LKJ2000��ʽ��ͬ
	uint32 	LocoNum;       	    //������            	2	

	uint8 	TrainTyp[4];     	//��������          	4   ��������,���α����·���(����[2005]72���ļ�)
	                            //                      	�ĳ��������ʶ��,������LKJ2000��ʽ��ͬ
	uint32	TrainNum;     		//�������ֲ���      	3   ���α����·���(����[2005]72����)�ĳ������ݲ���
	uint8 	Car_Truck[4];       //��/������/��       	1   D0��0/1 �� ��/��   D1��0/1 �� ��/��   
	 
	uint32 	VoitureCnt;       	//����              	1	
	uint32 	KmMark;   		//�����            	3   ��λ����

	uint32 	Weight;       	    //����              	2
	uint32 	PlanLen;       	    //�Ƴ�              	2   ��λ��0.1   

	uint32 	MstDriverNum;  	    //˾����            	2	
	uint32 	E_MstDriverNum; 	//˾������չ�ֽ�    	1   
	uint32 	E_SlvDriverNum;   	//��˾������չ�ֽ�  	1   

	uint32 	SlvDriverNum;  	    //��˾����          	2   
	uint32	DriverUnitNum;  	//˾����λ���      	2   //����Ψһȷ��˾��

	uint32 	RoadNum;          	//���κ�(��·��)     	1	
	uint32  RelRoadNum;     	//ʵ�ʽ�·��         	1   �����ʽ��LKJ2000��ͬ   
	uint32 	StationNum;     	//��վ��            	1
	uint32 	E_StationNum;   	//��վ����չ�ֽ�    	1   ��վ����չ�ֽ�

	uint8 	SignalTyp[4];       //�źŻ�����        	1   B2-B0 :2-��վ,3-��վ,4-ͨ��,5-Ԥ��,6-����
	uint8 	LocoSign[4];        //�����ź�          	1   B4 = 0/1  ����/���;   B3~B0 0-�޵�,1-��,2-��, 
	                            	//                      	3-˫��,4-���,5-��,6-��,7-�̻�,8-��
	uint32 	LocoWorkState;    	//��������          	1   b0-��λ,B1-���,B2-��ǰ,B3-�ƶ�,B4-ǣ��
	uint32 	LocoState;      	//װ��״̬          	1   B0 = 1/0 - ����/���; B2 = 1/0 - ����/�ǵ���

//	uint8 	SignalNum[2];      	//�źŻ����        	2   
//	uint8 	LocoPipePress[2]; 	//�г���ѹ          	2   B9-B0:��ѹ(��λ:1kPa)

	uint32	Myspeed1;			//�Բ��ٶ�1				2
	uint32	Myspeed2;			//�Բ��ٶ�2				2	
	  
	uint32 	MstDip;           	//��������          	4   ���ͳ�����(���ӻ�����ʱΪ��������,����Ϊ����������)

//	uint32 	SlvDip;           	//�ӻ�����          	4   ���ͳ�����(���ӻ�����ʱΪ�ӻ�����,���������ֵΪ��)
	uint32	MyKileMeter;		//�����				4
		
	int32 	MyMstLocoPower;     //������������       	4   ��������豸����

//	int32 	SlvLocoPower;     	//�ӻ���������       	4   �ӻ�����豸����
	uint32	MyPower;			//�ۼƵ���				4	
	//090901
 	//uint16	MstDip1Prs;        	//ѹǿ            		2   �����ͳ�1ѹǿֵ
	//uint16	MstDip2Prs;        	//ѹǿ            		2   �����ͳ�2ѹǿֵ
	int32		Myhig1;				//Һλ�߶�1				2	
	int32		Myhig2;				//Һλ�߶�2				2							

	uint32	SlvDip1Prs;       	//ѹǿ            		2   �ӻ��ͳ�1ѹǿֵ
	uint32 	SlvDip2Prs;       	//ѹǿ            		2   �ӻ��ͳ�2ѹǿֵ
	
	uint32  	MyYear;           	//��      				1   װ��ʱ�����
	uint32 	MyMonth;         	//��      				1   װ��ʱ�����
	uint32 	MyData;          	//��      				1   װ��ʱ�����
	uint32 	MyHour;           	//ʱ      				1   װ��ʱ���ʱ
	
	uint32 	MyMinute;     		//��      				1   װ��ʱ��ķ�
	uint32 	MySecond;       	//��       				1   װ��ʱ�����
	uint32	MstDensity;			//�ܶ�							2	����ȼ���ܶ�
	
//	uint16	SlvDensity;			//�ܶ�						2	�ӻ�ȼ���ܶ�
//	uint16	GpsHeight;			//�߶�						2	�����߶�
	int32	MyAddspeed;			//�Բ���ٶ�					2
	uint32	MyDip;				//�Բ�����							2
		
	int32	GpsLongitude;		//����					4	��������
	int32	GpsLatitude;		//γ��					4	����γ��
		
	int32	MstEngRotSpd;		//�������ͻ�ת��		2	�������ͻ�ת��
//	int16	SlvEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��
	int32	MyEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��

	//�������� 
	//���Լ�ʱ��оƬ���׵�������
	uint32 	JcRealType;			//�����ͺ�				2   �ⲿ���õĻ����ͺ�
	uint32 	JcRealNo;			//�������				2   �ⲿ���õĻ������
	
//	uint16 	MstPotPress;		//������ѹ				2	Ԥ���Ӽ��	
//	uint16 	SlvPotPress;		//�ӻ���ѹ				2	Ԥ���Ӽ��	
	uint32	MyDip1Tmp;	  		//�ͳ�1�¶�
	uint32	MyDip2Tmp;			//�ͳ�2�¶�
		
//	uint16 	MstPot1;			//��������1				2	Ԥ���Ӽ��	
//	uint16 	MstPot2;			//��������2				2	Ԥ���Ӽ��
	uint32	MyDip1Den;
	uint32	MyDip2Den;	

	
	
//	uint16 	SlvPot1;			//�ӻ�����1				2	Ԥ���Ӽ��		
//	uint16 	SlvPot2;			//�ӻ�����2				2	Ԥ���Ӽ��
	uint32	MyDip1Err;
	uint32	MyDip2Err;
	
	uint32 	MaxSpeed;			//����					2	Ԥ���Ӽ��	
//	uint16 	MstOcurrent;		//����ԭ�ߵ���   		2	Ԥ���Ӽ��
	uint32	ErrNum;				//���й�������			2	
	
	
	uint32	ErrorCode;			//���ϴ���				1   0~255
//	uint8 	DipValChgState;  	//�����仯״̬   		1   �����仯����֣����ͳ�����/��С���仯ƽ�ȡ���΢���������Ҳ���
	uint32	MyLocoWorkState;	//�Բ����״̬			1
	//090901
	uint32	MstDipTemp;			//�¶�					1	�����¶�
	uint32	OilBoxModel;		//����ģ��				1	�����������
	
	uint32	SoftVes;        	//�����汾          	1   
	uint32	Reserve1;        	//Ԥ��          		1  	
//	uint16	Reserve0;        	//Ԥ��          		2   
	uint32 	CrcCheck;         	//�洢��У���    		2   Flash��¼�洢CRCУ��
}stcFlshRecSql;


typedef  struct _stcRecoilRecordCtrl   	//�����ͳ߼�¼���ݽṹ_���ݿ����
{
	uint8	recnum;			//	
	uint8	storeflg;		
	uint8   ICflg;
	uint8	enableflg;		//
	uint32	currecnum;		//��ǰ��¼��
	uint32	ICreadnum;		//��ʼ��¼��
	uint8	ICstorefile[128];//IC���ļ���������
}stcRecOilRecordCtrl;

typedef struct _stcTinyRec{  
    uint8   Addr;
    uint8   ModelNum;
    uint16  Oil;
    uint32  CurRecNum;
    uint16  Speed1;
    uint16  Speed2;
    uint16  Speedcs;
    int16   Hig1;
    int16   Hig2;
    uint8   LocoWorkSta;
}stcTinyRec;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
extern	int 				cvi_hdbc_mysql_handle;		//���ݿ����Ӿ��
extern	int 				globalvalue;
extern	int 				db_panelHandle;
extern	stcFlshRec			gsFlshRec;
extern	stcRecOilRecordCtrl	gsRecvOilRecordCtrl;

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
int  InsertoilRecToDB (char *tabelname,stcFlshRec *sFlshRec);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif