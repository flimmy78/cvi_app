/*******************************************************************************
 *   Filename:       setmodel.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    
					 
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#include "oilmodel_db.h"
#include <ansi_c.h>
#include <utility.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>

 /********************************************************************************************/
/* ��ʱ����������ṹ��																				    */
/********************************************************************************************/
typedef struct	_stcTableCtrl_
{
	int		hdbc_handel;	//���ݿ���������
	int		hmap;			//��ʱֵ

	char	*dnsname;		//���ݿ�DNS��name	
	char	*tablename;		//��ʱ��
	int		* poverFlg;		//��ʱ��ʶ
}stcTableCtrl;				//���ݿ�����



/*******************************************************************************
* CONSTANTS
*/

int cvi_hdbc_mysql_handle;			//���ݿ����Ӿ��
int globalvalue;
int db_panelHandle;

/*******************************************************************************
* GLOBAL VARIABLES
*/
void	ConnectDB(void);
void	CloseDB(void);
void	ChangeRecordValue(void);


/********************************************************************************************/
/*�����ݿ����																	            */
/********************************************************************************************/
int CVICALLBACK OpenOilModelCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			if ((db_panelHandle = LoadPanel (0, "oilmodel_db.uir", SETM_PANEL)) < 0)
				return -1;	
	
			//ConnectDB();	//�������ݿ�
	
			DisplayPanel (db_panelHandle);

			break;
	}
	
	return 0;
}



/*******************************************************************************
* ��    �ƣ� ConnectDB
* ��    �ܣ� �������ݿ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �����ݿ⽨�����ӡ�ODBC ����Դ(32 λ)֧�֣��ṩDNS
*******************************************************************************/
void	ConnectDB(void)
{
	//�������ݿ����ӣ���������Ӿ��
	char	dsnbuf[64];
	sprintf(dsnbuf,"DSN=%s",ODBC_DNS);
	cvi_hdbc_mysql_handle = DBConnect (dsnbuf);
}

/*******************************************************************************
* ��    �ƣ� CloseDB
* ��    �ܣ� �������ݿ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
void	CloseDB(void)
{
	//���˳�Ӧ�ó���ʱ���ر����ݿ�����
	DBDisconnect (cvi_hdbc_mysql_handle); 	
}


/*******************************************************************************
* ��    �ƣ� CreateDBTableMap
* ��    �ܣ� �������ݱ�ӳ��
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
int	CreateDBTableMap(int * hmap,stcCalcModel *sCalcModel)
{
	long	tmp64;
	int		i,j=0;
	char	tmpbuf[32];
	int 	resultcode;

	DBMapColumnToShort (*hmap, "MODEL_NUM",&sCalcModel->ModelNum,&tmp64);	//����ģ�ͱ��
	DBMapColumnToShort (*hmap, "POT_NUM", &sCalcModel->PotNum,&tmp64);		//ģ�͵���
	DBMapColumnToShort (*hmap, "SET_OIL", &sCalcModel->StartOil, &tmp64);	//ģ�ͳ�ʼֵ
	
	for(i = 0;i < 100;i++)						   
	{
		sprintf(tmpbuf,"HIG%02d",i);
		resultcode = DBMapColumnToShort (*hmap, tmpbuf, &sCalcModel->sModPot[i].HigVal, &tmp64);	//�߶�
		
		sprintf(tmpbuf,"OIL%02d",i);
		resultcode = DBMapColumnToShort (*hmap, tmpbuf, &sCalcModel->sModPot[i].DipVal, &tmp64);	//����
	}	
	
	return 1;
}

/*******************************************************************************
* ��    �ƣ� CreateDBBindColCalcModel
* ��    �ܣ� �������ݱ��
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-06
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
int	CreateDBBindColCalcModel(int * hstat,stcCalcModel *sCalcModel)
{
	long	tmp64;
	int		i,j=1;

	j=1;
	
	DBBindColShort (*hstat, j++, &sCalcModel->ModelNum,&tmp64);  				//����ģ�ͱ�� 
	DBBindColShort (*hstat, j++, &sCalcModel->PotNum,&tmp64);					//ģ�͵���  
	DBBindColShort (*hstat, j++, &sCalcModel->StartOil, &tmp64);				//ģ�ͳ�ʼֵ   
	
	for(i = 0;i < 100;i++)						   
	{
		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].HigVal, &tmp64);	//�߶�
		
		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].DipVal, &tmp64);	//����
	}	

	return 1;
}

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
int	CreateDBTable(char *tabelname)
{
	int 	resultcode;
	int 	hmap;	
 
	hmap = DBBeginMap (cvi_hdbc_mysql_handle); 				//����һ�����ݿ�ӳ��

	CreateDBTableMap(&hmap,&gsCalcModel);					//����һ�����ݱ�ӳ��

	resultcode = DBCreateTableFromMap (hmap, tabelname);	//�ɴ�ӳ�䴴��һ�����ݱ�

	DBDeactivateMap (hmap); 								//����ӳ�� 

	return 1;
}

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
int	ReadRecFromDB(char *tabelname,int	keyval)
{
	int 	resultcode;
	long 	idstatus;
	int 	idvalue;
	int 	hstat;
	int 	total = 0;
	int 	i = 1;
	char	tmpbuf[64];

	DisableBreakOnLibraryErrors ();
			
	//����SQL��ѯ
	
	sprintf(tmpbuf,"SELECT * FROM %s WHERE MODEL_NUM = %d",tabelname,keyval);	//����ָ����ֵ����
	hstat = DBActivateSQL (cvi_hdbc_mysql_handle, tmpbuf);

	CreateDBBindColCalcModel(&hstat,&gsCalcModel);  							//�󶨼�¼����ؼ�¼�����ݽṹ�� 
	
	total = DBNumberOfRecords (hstat); 											//��ü�¼������

	if (total > 0)
	{
		//ȡ���ݼ�¼������ӡ
		//while (DBFetchNext(hstat) != DB_EOF)
		if (DBFetchNext(hstat) != DB_EOF)    
		{
			//ɾ������еı��ؼ�������
			DeleteTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, -1);
			
			//���������ݱ��м�¼����ͬ������
			InsertTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, gsCalcModel.PotNum, VAL_USE_MASTER_CELL_TYPE);
			
			if (gsCalcModel.ModelNum > 0)
			{
				//��������ָ������д�������ؼ���
				for(i = 1;i < gsCalcModel.PotNum +1;i++)
				{
					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(1,i), gsCalcModel.sModPot[i-1].HigVal);
					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(2,i), gsCalcModel.sModPot[i-1].DipVal);
				}
			}			
			
			//����������ʾֵ
			sprintf(tmpbuf,"ģ����Ϣ����ģ�ͱ�ţ�%2d;ģ�͵�����%2d;��ʼ������%2d��"
																	,gsCalcModel.ModelNum
																	,gsCalcModel.PotNum
																	,gsCalcModel.StartOil
				   													);
			SetCtrlVal(db_panelHandle, SETM_PANEL_TEXTMSG,tmpbuf);
	
			gsCalcModel.CrcCheck = GetCrc16Check((uint8 *)&gsCalcModel,sizeof(gsCalcModel)-2);	//����У��	
			
			l_eqiupmentcode = RUN_MODEL_PARA;								//����Ϊ����ģ�Ϳ�
		}
	}
	
	//����رղ�ѯ
	DBDeactivateSQL (hstat);
	
	return 1;
}

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
int CVICALLBACK InsertRecToDB (char *tabelname,stcCalcModel *sCalcModel)
{
	int 	resultcode;
	int 	hstat;
	int 	numberofrecords;
	int 	hmap;	
	
	hmap = DBBeginMap (cvi_hdbc_mysql_handle);  //����һ�����ݿ�ӳ���ϵ
	
	CreateDBTableMap(&hmap,sCalcModel);			//����һ�����ݱ�ӳ��

	hstat = DBActivateMap (hmap, tabelname); 	//����ӳ��
	
	ChangeRecordValue();	  					//�޸ļ�¼ֵ 
	
	DBCreateRecord(hstat);  					//������¼  

	resultcode = DBPutRecord (hstat);			//�������ݿ�  
			
	resultcode = DBDeactivateMap (hmap);		//�ͷű�����ľ�� 

	return 0;
}

/*******************************************************************************
* ��    �ƣ� ChangeRecordValue
* ��    �ܣ� �������ݼ�¼
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �������ݿ�������ֽ���ӳ�䣬�ڸ�ֵ��д���ݣ���������⡣ 
*******************************************************************************/
void	ChangeRecordValue(void)
{
	gsCalcModel.ModelNum++;
	gsCalcModel.PotNum = 3;
	
	gsCalcModel.sModPot[0].HigVal = 0;
	gsCalcModel.sModPot[0].DipVal = 1200;
	
	gsCalcModel.sModPot[1].HigVal = 1558;
	gsCalcModel.sModPot[1].DipVal = 3400;
	
	gsCalcModel.sModPot[2].HigVal = 7529;
	gsCalcModel.sModPot[2].DipVal = 9000;
	
	for(int i = 3;i<100;i++)
	{
		gsCalcModel.sModPot[i].HigVal = 7529;
		gsCalcModel.sModPot[i].DipVal = 9000;
	}
}
