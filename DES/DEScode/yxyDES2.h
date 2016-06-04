/*----------------------------------------------------------------
            // Copyright (C) 2008 ��ѧԨ
            // ��Ȩ���С�
            //
            // �ļ�����yxyDES2.h
            // �ļ�����������DES2������ ͷ�ļ�
            //
            //
            // �����ˣ���ѧԨ
            //
            // �޸��ˣ�
            // �޸�������
            //
            // �޸��ˣ�
            // �޸�������
//----------------------------------------------------------------*/
//---------------------------------------------------------------------------

#ifndef yxyDESH
#define yxyDESH

#include <string>

class yxyDES2
{
public:
		//�๹�캯��
         yxyDES2(); 

		 //����������
        ~yxyDES2(); 

        //����:����16��28λ��key
        //����:Դ8λ���ַ���(key),���key�����0-1
        //���:����������private CreateSubKey���������char SubKeys[keyN][16][48]
        void InitializeKey(char* srcBytes,unsigned int keyN);

        //����:����8λ�ַ���
        //����:8λ�ַ���,ʹ��Key�����0-1
        //���:���������ܺ��������private szCiphertext[16]
        //      �û�ͨ������Ciphertext�õ�
        void EncryptData(char* _srcBytes,unsigned int keyN);

        //����:����16λʮ�������ַ���
        //����:16λʮ�������ַ���,ʹ��Key�����0-1
        //���:���������ܺ��������private szPlaintext[8]
        //      �û�ͨ������Plaintext�õ�
        void DecryptData(char* _srcBytes,unsigned int keyN);

        //����:�������ⳤ���ַ���
        //����:���ⳤ���ַ���,����,ʹ��Key�����0-1
        //���:���������ܺ��������private szFCiphertextAnyLength[8192]
        //      �û�ͨ������CiphertextAnyLength�õ�
        void EncryptAnyLength(char* _srcBytes,unsigned int _bytesLength,unsigned int keyN);

        //����:�������ⳤ��ʮ�������ַ���
        //����:���ⳤ���ַ���,����,ʹ��Key�����0-1
        //���:���������ܺ��������private szFPlaintextAnyLength[8192]
        //      �û�ͨ������PlaintextAnyLength�õ�
        void DecryptAnyLength(char* _srcBytes,unsigned int _bytesLength, unsigned int keyN);

		//����:Bytes��Bits��ת��,
        //����:���任�ַ���,���������Ż�����ָ��,Bits��������С
		void Bytes2Bits(char *srcBytes, char* dstBits, unsigned int sizeBits);

		//����:Bits��Bytes��ת��,
        //����:���任�ַ���,���������Ż�����ָ��,Bits��������С
		void Bits2Bytes(char *dstBytes, char* srcBits, unsigned int sizeBits);

		//����:Int��Bits��ת��,
        //����:���任�ַ���,���������Ż�����ָ��
		void Int2Bits(unsigned int srcByte, char* dstBits);
		
		//����:Bits��Hex��ת��
        //����:���任�ַ���,���������Ż�����ָ��,Bits��������С
		void Bits2Hex(char *dstHex, char* srcBits, unsigned int sizeBits);
		
		//����:Bits��Hex��ת��
        //����:���任�ַ���,���������Ż�����ָ��,Bits��������С
		void Hex2Bits(char *srcHex, char* dstBits, unsigned int sizeBits);

		//szCiphertextInBinary��get����
        char* GetCiphertextInBinary();

		//szCiphertextInHex��get����
		char* GetCiphertextInHex();

        //Ciphertext��get����
		char* GetCiphertextInBytes();

		//Plaintext��get����
        char* GetPlaintext();

        //CiphertextAnyLength��get����
		char* GetCiphertextAnyLength();

		//PlaintextAnyLength��get����
        char* GetPlaintextAnyLength();

private:
        char szSubKeys[2][16][48];//����2��16��48λ��Կ,��2������3DES
		char szCiphertextRaw[64]; //�������������(64��Bits) int 0,1
		char szPlaintextRaw[64]; //�������������(64��Bits) int 0,1
		char szCiphertextInBytes[8];//����8λ����
        char szPlaintextInBytes[8];//����8λ�����ַ���

		char szCiphertextInBinary[65]; //�������������(64��Bits) char '0','1',���һλ��'\0'
		char szCiphertextInHex[17]; //����ʮ����������,���һλ��'\0'
		char szPlaintext[9];//����8λ�����ַ���,���һλ��'\0'

        char szFCiphertextAnyLength[8192];//���ⳤ������
        char szFPlaintextAnyLength[8192];//���ⳤ�������ַ���

		//����:��������Կ
        //����:����PC1�任��56λ�������ַ���,���ɵ�szSubKeys���0-1
        //���:��������char szSubKeys[16][48]
        void CreateSubKey(char* sz_56key,unsigned int keyN);

		//����:DES�е�F����,
        //����:��32λ,��32λ,key���(0-15),ʹ�õ�szSubKeys���0-1
        //���:���ڱ任����32λ
        void FunctionF(char* sz_Li,char* sz_Ri,unsigned int iKey,unsigned int keyN);

		//����:IP�任
        //����:�������ַ���,����������ָ��
        //���:�����ı�ڶ�������������
        void InitialPermuteData(char* _src,char* _dst);

		//����:����32λ������չλ48λ,
        //����:ԭ32λ�ַ���,��չ�������ָ��
        //���:�����ı�ڶ�������������
        void ExpansionR(char* _src,char* _dst);

		//����:�����,
        //����:�����Ĳ����ַ���1,�ַ���2,����������,����������ָ��
        //���: �����ı���ĸ�����������
        void XOR(char* szParam1,char* szParam2, unsigned int uiParamLength, char* szReturnValueBuffer);

		//����:S-BOX , ����ѹ��,
        //����:48λ�������ַ���,
        //���:���ؽ��:32λ�ַ���
        void CompressFuncS(char* _src48, char* _dst32);

		//����:IP��任,
        //����:���任�ַ���,����������ָ��
        //���:�����ı�ڶ�������������
        void PermutationP(char* _src,char* _dst);

};

#endif
 