#ifndef  _uirbsp_mb_poll_h_
#define  _uirbsp_mb_poll_h_

/********************************************************************************************/
/* �������ýṹ��																				    */
/********************************************************************************************/
typedef struct	_strMBPoll_
{
	char	node;			//�˿�
	char	addr;			//��ַ 
	char	format;			//��ʾ��ʽ
	char	len;
	
	int		readflg:1;		//���Ĵ�����ʶ
	int 	writeflg:1;		//д�Ĵ�����ʶ
	int		autoflg:1;		//�Զ�����
	int  	tmpflg:6;		//
	
	short	buf[512];		//����
}strMBPoll;					//�������ýṹ��

#endif