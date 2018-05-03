/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    2017-10-15
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/
#include  	"modeltable.h"


/*******************************************************************************
* CONSTANTS
*/

int 				cvi_hdbc_mysql_handle;				//���ݿ����Ӿ��
int 				db_panelHandle;
stcThreadModel		gsThreadModel;		//����ģ���߳� ��191017��

extern	stcCalcModel	gsCalcModel;	//����ģ�ͣ������ã�


/*******************************************************************************
* GLOBAL VARIABLES
*/

stcModelTableCtrl	gsSetModelTable;	//ģ�Ͳ�����
stcOilPara			gsOilPara;			//�����������	

stcThreadModel		gsThreadModel;		//����ģ���߳� ��191017��

/*******************************************************************************
* ��    �ܣ� ��ʼ��ģ�ͱ���Ʊ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
void	InitModelTableCtrl(void)
{
	gsSetModelTable.phdbc = &g_cvihdbc_handel;
	gsSetModelTable.map   = 0;
	gsSetModelTable.sql   = 0;
	strcpy((char *)gsSetModelTable.tablename,MODEL_TABLE_NAME);
	
	gsSetModelTable.Operate.rdEndFlg 	= 0;
	gsSetModelTable.Operate.rdStartFlg 	= 0;
	gsSetModelTable.Operate.wrEndFlg 	= 0;
	gsSetModelTable.Operate.wrStartFlg 	= 0;	
}

/*******************************************************************************
* ��    �ܣ� �������ݱ�ӳ��
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-05
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� 
*******************************************************************************/
int	CreateModelToTableMap(stcModelTableCtrl * stable)
{
	long	tmp64;
	int		i;
	char	tmpbuf[32];
	int 	resultcode;

	stable->map = DBBeginMap(*stable->phdbc);																//����ӳ�䣬��ʼ��ֵ
	
	DBMapColumnToShort (stable->map, "MODEL_NUM",(short *)&stable->sMode.ModelNum,	&tmp64);						//����ģ�ͱ��
	DBMapColumnToShort (stable->map, "POT_NUM",  (short *)&stable->sMode.PotNum,		&tmp64);						//ģ�͵���
	DBMapColumnToShort (stable->map, "SET_OIL",  (short *)&stable->sMode.StartOil, 	&tmp64);						//ģ�ͳ�ʼֵ
	
	for(i = 0;i < 100;i++)						   
	{
		sprintf(tmpbuf,"HIG%02d",i);
		resultcode = DBMapColumnToShort (stable->map, tmpbuf, (short *)&stable->sMode.sModPot[i].HigVal, &tmp64);	//�߶�
		
		sprintf(tmpbuf,"OIL%02d",i);
		resultcode = DBMapColumnToShort (stable->map, tmpbuf, (short *)&stable->sMode.sModPot[i].DipVal, &tmp64);	//����
	}	
	
	return 1;
}


/*******************************************************************************
* ��    �ܣ� ��ȡָ��ֵ�����ݱ�
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ�redmorningcn.
* �������ڣ� 2017-09-06
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �����ݿ��ж�ȡָ�������ݣ������� 
*******************************************************************************/
int	ReadModelFromTable(int	keyval)
{
	int 	total = 0;
//	char	tmpbuf[64];

	DisableBreakOnLibraryErrors ();
			
	gsSetModelTable.sql = DBActivateMap(gsSetModelTable.map,gsSetModelTable.tablename);			//����ӳ��
	total = DBNumberOfRecords (gsSetModelTable.sql); 											//��ü�¼������

	if (total > 0)
	{
		//ȡ���ݼ�¼������ӡ
		while (DBFetchNext(gsSetModelTable.sql) != DB_EOF)    									//���ݱȽϴ󣬽���������ѯ���������ݹ���
		{
			if(gsSetModelTable.sMode.ModelNum == keyval)
			{
				memcpy((char *)&gsSetModelTable.Operate.rdModel,
					   (char *)&gsSetModelTable.sMode,
					   sizeof(stcCalcModel));													//�������ݣ���ֹ�쳣��д
				
				gsSetModelTable.Operate.rdEndFlg = 1;											//����ʶΪ1�����ݶ�ȡ��� 
				break;
				//return 1;
			}
		}
	}
	
	//����رղ�ѯ
	DBDeactivateSQL (gsSetModelTable.sql);
	return 0;
}


//----------------------------------------------------------------------------
// ��    �ܣ� ���ڵ��ա�������.ͨ����ʶλ���̣߳����Ƴ����շ�Э��
// ��    ����
// ��    �ߣ� redmornigcn 20170927
//----------------------------------------------------------------------------
static int CVICALLBACK Thread_DB (void *functionData)
{
	
	while (!gsThreadModel.ThreadExit)							//�̲߳��˳�
	{
//////////////////////////////////////////////////////////////////���ݿ�д����
		if(gsSetModelTable.Operate.rdStartFlg)					//��ȡ��ʼ��ȡ����
		{
			gsSetModelTable.Operate.rdStartFlg = 0;
			ReadModelFromTable(gsSetModelTable.Operate.rdRecNum);//��ȡ���ݼ�¼	
			
			memcpy((uint8 *)&gsCalcModel,
				   (uint8 *)&gsSetModelTable.sMode,
				   sizeof(gsCalcModel));						//�����ͳ�ģ���ļ�����
		}
	}

	return 0;
}

//----------------------------------------------------------------------------
// ��    �ܣ� ��ʼ��ģ�ͱ����ݿ�����̡߳�Ϊʵ�����ݿ�������뿪�����߳�
// ��    ����
// ��    �ߣ� redmornigcn 20171027
//----------------------------------------------------------------------------
int	cvi_InitBspDB(stcThreadModel * T_Ctrl)
{
	if(T_Ctrl->ThreadID == 0)				//��ʼ���շ������߳�
	{
		//T_Ctrl->sCom = &gsCom1Contrl;		//����1��������
		T_Ctrl->ThreadExit = 0;				//�̲߳��ͷ�

		//cvi_OpenCom(T_Ctrl->sCom);			//�򿪸ø��̶߳�Ӧ�Ĵ���
		
		CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,
									   Thread_DB,		//���̴߳�����
									   NULL,
							   		   &T_Ctrl->ThreadID);
	}
	
	return	T_Ctrl->ThreadID;				//�����߳�ID
}


///*******************************************************************************
//* ��    �ƣ� CreateDBBindColCalcModel
//* ��    �ܣ� �������ݱ��
//* ��ڲ����� ��
//* ���ڲ����� ��
//* ���� ���ߣ�redmorningcn.
//* �������ڣ� 2017-09-06
//* ��    �ģ�
//* �޸����ڣ�
//* ��    ע�� 
//*******************************************************************************/
//int	CreateDBBindColCalcModel(int * hstat,stcCalcModel *sCalcModel)
//{
//	long	tmp64;
//	int		i,j=1;

//	j=1;
//	
//	DBBindColShort (*hstat, j++, &sCalcModel->ModelNum,&tmp64);  				//����ģ�ͱ�� 
//	DBBindColShort (*hstat, j++, &sCalcModel->PotNum,&tmp64);					//ģ�͵���  
//	DBBindColShort (*hstat, j++, &sCalcModel->StartOil, &tmp64);				//ģ�ͳ�ʼֵ   
//	
//	for(i = 0;i < 100;i++)						   
//	{
//		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].HigVal, &tmp64);	//�߶�
//		
//		DBBindColShort (*hstat, j++, &sCalcModel->sModPot[i].DipVal, &tmp64);	//����
//	}	

//	return 1;
//}

///*******************************************************************************
//* ��    �ƣ� CreateDBTable
//* ��    �ܣ� �������ݱ�
//* ��ڲ����� ��
//* ���ڲ����� ��
//* ���� ���ߣ�redmorningcn.
//* �������ڣ� 2017-09-05
//* ��    �ģ�
//* �޸����ڣ�
//* ��    ע��DBBindColInt 
//*******************************************************************************/
//int	CreateDBTable(char *tabelname)
//{
//	int 	resultcode;
//	int 	hmap;	
// 
//	hmap = DBBeginMap (cvi_hdbc_mysql_handle); 				//����һ�����ݿ�ӳ��

//	CreateDBTableMap(&hmap,&gsCalcModel);					//����һ�����ݱ�ӳ��

//	resultcode = DBCreateTableFromMap (hmap, tabelname);	//�ɴ�ӳ�䴴��һ�����ݱ�

//	DBDeactivateMap (hmap); 								//����ӳ�� 

//	return 1;
//}

///*******************************************************************************
//* ��    �ƣ� ReadRecFromDB
//* ��    �ܣ� �����ݿ���У���ȡ���ݼ�¼
//* ��ڲ����� ��
//* ���ڲ����� ��
//* ���� ���ߣ�redmorningcn.
//* �������ڣ� 2017-09-06
//* ��    �ģ�
//* �޸����ڣ�
//* ��    ע�� �����ݿ��ж�ȡָ�������ݣ������� 
//*******************************************************************************/
//int	ReadRecFromDB(char *tabelname,int	keyval)
//{
//	int 	resultcode;
//	long 	idstatus;
//	int 	idvalue;
//	int 	hstat;
//	int 	total = 0;
//	int 	i = 1;
//	char	tmpbuf[64];

//	DisableBreakOnLibraryErrors ();
//			
//	//����SQL��ѯ
//	
//	sprintf(tmpbuf,"SELECT * FROM %s WHERE MODEL_NUM = %d",tabelname,keyval);	//����ָ����ֵ����
//	hstat = DBActivateSQL (cvi_hdbc_mysql_handle, tmpbuf);

//	CreateDBBindColCalcModel(&hstat,&gsCalcModel);  							//�󶨼�¼����ؼ�¼�����ݽṹ�� 
//	
//	total = DBNumberOfRecords (hstat); 											//��ü�¼������

//	if (total > 0)
//	{
//		//ȡ���ݼ�¼������ӡ
//		//while (DBFetchNext(hstat) != DB_EOF)
//		if (DBFetchNext(hstat) != DB_EOF)    
//		{
//			//ɾ������еı��ؼ�������
//			DeleteTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, -1);
//			
//			//���������ݱ��м�¼����ͬ������
//			InsertTableRows (db_panelHandle, SETM_PANEL_TABLE, 1, gsCalcModel.PotNum, VAL_USE_MASTER_CELL_TYPE);
//			
//			if (gsCalcModel.ModelNum > 0)
//			{
//				//��������ָ������д�������ؼ���
//				for(i = 1;i < gsCalcModel.PotNum +1;i++)
//				{
//					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(1,i), gsCalcModel.sModPot[i-1].HigVal);
//					SetTableCellVal (db_panelHandle, SETM_PANEL_TABLE, MakePoint(2,i), gsCalcModel.sModPot[i-1].DipVal);
//				}
//			}			
//			
//			//����������ʾֵ
//			sprintf(tmpbuf,"ģ����Ϣ����ģ�ͱ�ţ�%2d;ģ�͵�����%2d;��ʼ������%2d��"
//																	,gsCalcModel.ModelNum
//																	,gsCalcModel.PotNum
//																	,gsCalcModel.StartOil
//				   													);
//			SetCtrlVal(db_panelHandle, SETM_PANEL_TEXTMSG,tmpbuf);
//	
//			gsCalcModel.CrcCheck = GetCrc16Check((uint8 *)&gsCalcModel,sizeof(gsCalcModel)-2);	//����У��	
//			
//			l_eqiupmentcode = RUN_MODEL_PARA;								//����Ϊ����ģ�Ϳ�
//		}
//	}
//	
//	//����رղ�ѯ
//	DBDeactivateSQL (hstat);
//	
//	return 1;
//}

///*******************************************************************************
//* ��    �ƣ� InsertRecToDB
//* ��    �ܣ� �������ݼ�¼
//* ��ڲ����� ��
//* ���ڲ����� ��
//* ���� ���ߣ�redmorningcn.
//* �������ڣ� 2017-09-05
//* ��    �ģ�
//* �޸����ڣ�
//* ��    ע�� �������ݿ�������ֽ���ӳ�䣬�ڸ�ֵ��д���ݣ���������⡣ 
//*******************************************************************************/
//int CVICALLBACK InsertRecToDB (char *tabelname,stcCalcModel *sCalcModel)
//{
//	int 	resultcode;
//	int 	hstat;
//	int 	numberofrecords;
//	int 	hmap;	
//	
//	hmap = DBBeginMap (cvi_hdbc_mysql_handle);  //����һ�����ݿ�ӳ���ϵ
//	
//	CreateDBTableMap(&hmap,sCalcModel);			//����һ�����ݱ�ӳ��

//	hstat = DBActivateMap (hmap, tabelname); 	//����ӳ��
//	
//	ChangeRecordValue();	  					//�޸ļ�¼ֵ 
//	
//	DBCreateRecord(hstat);  					//������¼  

//	resultcode = DBPutRecord (hstat);			//�������ݿ�  
//			
//	resultcode = DBDeactivateMap (hmap);		//�ͷű�����ľ�� 

//	return 0;
//}

///*******************************************************************************
//* ��    �ƣ� ChangeRecordValue
//* ��    �ܣ� �������ݼ�¼
//* ��ڲ����� ��
//* ���ڲ����� ��
//* ���� ���ߣ�redmorningcn.
//* �������ڣ� 2017-09-05
//* ��    �ģ�
//* �޸����ڣ�
//* ��    ע�� �������ݿ�������ֽ���ӳ�䣬�ڸ�ֵ��д���ݣ���������⡣ 
//*******************************************************************************/
//void	ChangeRecordValue(void)
//{
//	gsCalcModel.ModelNum++;
//	gsCalcModel.PotNum = 3;
//	
//	gsCalcModel.sModPot[0].HigVal = 0;
//	gsCalcModel.sModPot[0].DipVal = 1200;
//	
//	gsCalcModel.sModPot[1].HigVal = 1558;
//	gsCalcModel.sModPot[1].DipVal = 3400;
//	
//	gsCalcModel.sModPot[2].HigVal = 7529;
//	gsCalcModel.sModPot[2].DipVal = 9000;
//	
//	for(int i = 3;i<100;i++)
//	{
//		gsCalcModel.sModPot[i].HigVal = 7529;
//		gsCalcModel.sModPot[i].DipVal = 9000;
//	}
//}

