#include <global.h>
#include <aes.h>

#if MB_AES_EN == DEF_ENABLED
static INT8U       mbszIvec[] = {0X12, 0x34, 0x56, 0x78,0X87, 0x65, 0x56, 0x78,
                                 0x87, 0x65, 0x43, 0x21,0x12, 0x34, 0x43, 0x21};
static AES_KEY     mbaesKey;
static INT8U       mbuserIvec[16];
#endif
/*******************************************************************************
 * ��    �ƣ� MB_AESCbcDecrypt()
 * ��    �ܣ� �������ݼ�����
 * ��ڲ����� buf ������ջ�����,len ����Ҫ���ܵĻ���������
 * ���ڲ����� ���ܺ�ĳ���
 * ���� ���ߣ� ������
 * �������ڣ� 2014-03-28
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
INT16U MB_AESCbcDecrypt(INT8U *buf, INT16U len)
{
#if MB_AES_EN == DEF_ENABLED    
    memset(mbaesKey.rd_key, 0, sizeof(mbaesKey.rd_key));// ������չ��Կ
    AES_SetDecryptKey(  "scw->ll->zs->scw",         // ��Կ
                        128, 		                // 128λ��ʽ������192��256λ��ʽ
                       &mbaesKey);			        // ��չ��Կ
    /***********************************************
    * ������ ������Կ����
    */
    memcpy((INT8U*)mbuserIvec,(INT8U*)&mbszIvec[0], 16);// ����
    /***********************************************
    * ������ ������Կ������Ϊ���Ӱ�ȫ�ԣ���ʹ�����Զ��뷢�Ͷ˽���ͬ����
    *
    if (++mbszIvec[6] > 10)
      mbszIvec[6]  = 0;
    *//***********************************************
    * ������ ������ݳ����Ƿ�Ϊ16��������
    */
    if ( (len & 0x0f) != 0  )
      return (DEF_FALSE);
    
    AES_CbcEnOrDecrypt((INT8U*)buf,                 // �����ܻ�����
                       (INT8U*)buf,                 // ���ܺ�Ļ�����
                        len,				        // ����������
                       (AES_KEY*)&mbaesKey, 		// ��չ��Կ
                       (INT8U*)mbuserIvec, 		    // ����
                        AES_DECRYPT);		        // ����
    /***********************************************
    * ������ ������һ���ֽ��Ƿ�Ϊ1��Ϊ1���ʾ���λ�ֽ���Ϊ1
    */
    if ( buf[len-1] == 1) {                         // �������ֽ�Ϊ1
      len--;                                        // ��Ч������-1
    /***********************************************
    * ������ ���>1������ֽ���
    */
    } else if ( buf[len-1] < 16 && buf[len-1] > 1) {
      INT8U i   = buf[len-1];                       // ��ȡ���ֵ
      INT8U *p  = &buf[len-i];                      // ָ��ʼ�����ֽڵ�ַ
      for (i-=1;i > 0;i--,p++) {
        if ( *p != *(p+1) )                         // ������������ֽڵ�ֵ�����
          break;                                    // ˵���������ֵ��ֱ������
      }
      if (i==0)                                     // �������ɣ�˵��������ֽ�
        len -= buf[len-1];                          // ��ȡ��Ч����֡�ֽ���
    }
#endif
    return      len;                                // ���¸�ֵ�����ռ�����
}
/*******************************************************************************
 * ��    �ƣ� MB_AESCbcEncrypt()
 * ��    �ܣ� �������ݼ�����
 * ��ڲ����� buf ���뷢�ͻ�����,len ����Ҫ���ܵĻ���������
 * ���ڲ����� ���ܺ�ĳ���
 * ���� ���ߣ� ������
 * �������ڣ� 2014-03-28
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
INT16U MB_AESCbcEncrypt(INT8U *buf, INT16U len)
{
#if MB_AES_EN == DEF_ENABLED
    INT8U       temp;
    
    memset(mbaesKey.rd_key, 0, sizeof(mbaesKey.rd_key));// ������չ��Կ
    AES_SetEncryptKey(  "scw->ll->zs->scw",         // ��Կ
                        128, 		                // 128λ��ʽ������192��256λ��ʽ
                       &mbaesKey);			        // ��չ��Կ
    /***********************************************
    * ������ ������Կ����
    */
    memcpy((INT8U*)mbuserIvec,(INT8U*)&mbszIvec[0], 16);// ����
    temp    = len & 0x0f;
    if ( temp != 0) {
      temp    = 16 - temp;
      memset((INT8U*)&buf[len],temp,temp);
      len = len + temp;
    }
    AES_CbcEnOrDecrypt((INT8U*)&buf[0],             // �����ܻ�����
                       (INT8U*)&buf[0],             // ���ܺ�Ļ�����
                        len,	                    // ����������
                       (AES_KEY*)&mbaesKey, 		// ��չ��Կ
                       (INT8U*)mbuserIvec, 		    // ����
                        AES_ENCRYPT);		        // ����
#endif
    return len;
}