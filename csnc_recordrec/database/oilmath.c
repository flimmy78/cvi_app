/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    2017-10-16
 *   Notes:
 *     				 E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "oilmodel_db.h"
#include "databaseoperate.h"
#include "modeltable.h"

/*******************************************************************************
* LOCAL VARIABLES
*/

/*******************************************************************************
 * ��    �ƣ�       GetMathOilVal
 * ��    �ܣ�       �������������ݸ߶�ֵ�������ݻ�������ϵ���ȼ�������.
 * ��ڲ�����       ��
 * ���ڲ����� 	    ��
 * ���� ���ߣ� 	    redmornigcn
 * �������ڣ� 	    2017-05-16
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint16    GetMathOilVal(int16   hig)
{
  	float 		DipVal = 0;                  		
  	float 		Hight;                  			
	float		MinHig,MaxHig;	
	float		MinDip,MaxDip;					
    
	uint8		ModelPotNum;
	uint8		i;
    
	//ģ����Ч�Ŵ���
	if(		gsSetModelTable.Operate.rdModel.PotNum  == 0
	|| 		gsSetModelTable.Operate.rdModel.ModelNum== 0)
	{
		return 0;
	}
	
	ModelPotNum = gsSetModelTable.Operate.rdModel.PotNum;           	//ģ�͵���

	Hight = hig;                                        				//�߶�ֵ

	Hight += ((float)gsOilPara.Hig );              						//���벹���߶�	
  	
  	for(i = 1; i <  ModelPotNum; i++)                   				//�����ĸ���
  	{
		MinHig 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].HigVal; 	//��1����ĸ߶�ֵ
		MaxHig 	= gsSetModelTable.Operate.rdModel.sModPot[i].HigVal;   	//��2����ĸ߶�ֵ

		MinDip 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].DipVal; 	//��1���������ֵ
		MaxDip 	= gsSetModelTable.Operate.rdModel.sModPot[i].DipVal;   	//��2���������ֵ
						
		if(MinHig == MaxHig  || MinDip == MaxDip)       				//����ģ���г���������ͬ��
		{
			//DisplaySet(60,1,"E-OL");                    				//��ʾ����ֵ
			return	0;                                  				//����ģ�ʹ�����ʾ0
		}

		if(MinHig <= Hight && Hight < MaxHig)		    				//��������,��ģ��ֵ�У�������ֵ����
		{	
			DipVal = MinDip + ((Hight - MinHig)  * (MaxDip - MinDip)) / (MaxHig - MinHig);

			break;
		}
	
		if(i == 1)														//С����С�߶ȣ�����͵�б��
		{			
			if(Hight < MinHig)
			{
				DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				
				break;
			}
		}
		
		if(i == (ModelPotNum - 1))										//�߶�ֵ�������һ�㣬���������
		{
			
			if(Hight >= MaxHig)
			{
				DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
			}
		}
	}
        
    DipVal *= gsOilPara.Slope;                 					//��������б��
    DipVal /= 10000;
	DipVal += gsSetModelTable.Operate.rdModel.StartOil;        	//����ֵ �� ģ����ʼ����ֵ
    
    return  (uint16)DipVal;
}


/*******************************************************************************
 * ��    �ܣ�       ����߶�ֵ�����������������ݻ�������ϵ���ȼ�������.
 * ��ڲ�����       ��
 * ���ڲ����� 	    ��
 * ���� ���ߣ� 	    redmornigcn
 * �������ڣ� 	    2017-10-16
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint16    GetMathHigVal(int16   oil)
{
  	float 		DipVal = 0;    
  	float 		Hight  = 0;                  			
	float		MinHig,MaxHig;	
	float		MinDip,MaxDip;					
    
	uint8		ModelPotNum;
	uint8		i;
	
	//ģ����Ч�Ŵ���  
	if(		gsSetModelTable.Operate.rdModel.PotNum  == 0
		|| 	gsSetModelTable.Operate.rdModel.ModelNum== 0)
	{
		return 0;
	}
	
	DipVal = oil;
			 
    DipVal -= gsSetModelTable.Operate.rdModel.StartOil;        	//����ֵ �� ģ����ʼ����ֵ 
    
	DipVal *=10000;
	DipVal /= gsOilPara.Slope;                 					//��������б��
	
	ModelPotNum = gsSetModelTable.Operate.rdModel.PotNum;              //ģ�͵���
  	
  	for(i = 1; i <  ModelPotNum; i++)                   //�����ĸ���
  	{
		MinHig 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].HigVal; //��1����ĸ߶�ֵ
		MaxHig 	= gsSetModelTable.Operate.rdModel.sModPot[i].HigVal;   //��2����ĸ߶�ֵ

		MinDip 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].DipVal; //��1���������ֵ
		MaxDip 	= gsSetModelTable.Operate.rdModel.sModPot[i].DipVal;   //��2���������ֵ
						
		if(MinHig == MaxHig  || MinDip == MaxDip)       				//����ģ���г���������ͬ��
		{
			//DisplaySet(60,1,"E-OL");                    				//��ʾ����ֵ
			return	0;                                  				//����ģ�ʹ�����ʾ0
		}

		if(MinDip <= DipVal && DipVal < MaxDip)		    				//��������,��ģ��ֵ�У�������ֵ����
		{	
			//DipVal = MinDip + ((Hight - MinHig)  * (MaxDip - MinDip)) / (MaxHig - MinHig);
			Hight = MinHig + ( ((DipVal - MinDip)  * (MaxHig - MinHig)) / (MaxDip - MinDip));
			break;
		}
	
		if(i == 1)														//С����С�߶ȣ�����͵�б��
		{			
			if(DipVal < MinDip)
			{
				//DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				Hight = MinHig + ( ((DipVal - MinDip)  * (MaxHig - MinHig)) / (MaxDip - MinDip)); 
				break;
			}
		}
		
		if(i == (ModelPotNum - 1))										//�߶�ֵ�������һ�㣬���������
		{
			if(DipVal >= MaxDip)
			{
				//DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				Hight = MinHig + ( ((DipVal - MinDip)  * (MaxHig - MinHig)) / (MaxDip - MinDip)); 
			}
		}
	}
        
	Hight -= ((float)gsOilPara.Hig );              					//�����߶�	
    
    return  (uint16)Hight;
}

