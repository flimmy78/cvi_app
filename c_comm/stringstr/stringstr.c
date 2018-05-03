#include <ansi_c.h>
#include    "includes.h"              



//������ת��Ϊָ����ʽ�����ݡ�
short	wordtodata(char *word,char 	format)
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
				if(  ( (word[i]>('a'-1))&& (word[i]<('f'+1)))  
				  || ((word[i]>('A'-1))&& (word[i]<('F'+1))) 
				  || ( (word[i]>('0'-1))&& (word[i]<('9'+1)))  
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
		if(*p != ',' && *p != ' ' && (i +1) < strlen(string) )	//����ת��
		{
			if(wordlen < 16)
			{
				word[wordlen++] = *p;
			}
			p++;  

		}
		else
		{
			if((i +1) == strlen(string))	//��β����
				word[wordlen++] = *p;		
			
			word[wordlen++] = '\0';
			
			buf[buflen++] = (short)wordtodata(word,format);
			
			wordlen = 0;
			p++;  
		}
	}
	return	buflen;
}










