/*******************************************************************************
 *   Filename:       cvi_file.h
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    

 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

#ifndef	CVI_FILE_H
#define	CVI_FILE_H

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/


/********************************************************************************************/
/* Constants																					*/
/********************************************************************************************/



/*******************************************************************************************
/�ṹ��																				 
*******************************************************************************************/
typedef	struct	_stcfileinfo_
{
	int	handle;				//�ļ��ؼ����
	int	size;				//�ļ���С
	int	deallen;			//�Ѵ�������
}stcFileInfo;

/********************************************************************************************/
/* Globals																					*/
/********************************************************************************************/
//���ڽṹ�弰ͨѶ
extern	int	g_sysIaptime;
extern	int	gBinFilePanelHandle;

/********************************************************************************************/
/* �����ļ������ٷֱ�						                								*/
/********************************************************************************************/
char	SetFileDealPer(void);

/********************************************************************************************/
/* ��bin�ļ���ȡ����						                								*/
/********************************************************************************************/
int		ReadFileData(int	addr,char *buf,int	reclen);

/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/

#endif