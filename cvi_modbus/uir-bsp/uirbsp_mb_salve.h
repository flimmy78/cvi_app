#ifndef  _uirbsp_mb_slave_h_
#define  _uirbsp_mb_slave_h_

/********************************************************************************************/
/* �������ýṹ��																				    */
/********************************************************************************************/
typedef struct	_strMBSlave_
{
	char	node;			//�˿�
	char	addr;			//��ַ 
	char	format;			//��ʾ��ʽ
	char	len;
	
	int		readflg:1;		//���Ĵ�����ʶ
	int 	writeflg:1;		//д�Ĵ�����ʶ
	int  	tmpflg:6;		//
	
	short	buf[512];		//����
}strMBSlave;				//�������ýṹ��


#endif
