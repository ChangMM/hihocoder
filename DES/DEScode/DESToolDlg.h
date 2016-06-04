// DES ToolDlg.h : ͷ�ļ�
//

#pragma once
#include "yxyDES2.h"

// CDESToolDlg �Ի���
class CDESToolDlg : public CDialog
{
// ����
public:
	CDESToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DESTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	yxyDES2 *myDES;
	CBrush m_brush;
	char bitsCiphertextAnyLength[32768];
	char hexCiphertextAnyLength[16384];
	char szSourceKey1[8],szSourceKey2[8],szPlaintextData[8192],szCiphertextData[8192];
	bool bIs3DES;
	void ConvertCiphertext2OtherFormat(int iBitsLen,char *szCipherInBytes);
	int ConvertOtherFormat2Ciphertext(char *szCipherInBytes);
	void SetBitmap(UINT uBmpResource,UINT uCtrlResource);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEncrypt();
	afx_msg void OnBnClickedCheckTdes();
	afx_msg void OnBnClickedButtonDecrypt();
	afx_msg void OnBnClickedRadioHex();
	afx_msg void OnBnClickedRadioBin();
	afx_msg void OnBnClickedRadioRaw();
	afx_msg void OnBnClickedButtonClearplaintext();
	afx_msg void OnBnClickedButtonClearciphertext();
	afx_msg void OnBnClickedButtonClearall();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedButtonBrowseSrc();
	afx_msg void OnBnClickedCheckFileTdes();
	afx_msg void OnBnClickedButtonBrowseDst();
	afx_msg void OnBnClickedButtonFileGoE();
	afx_msg void OnBnClickedButtonGoD();
private:
	CEdit edtFileKey1;
	CEdit edtFileSrc;
	CEdit edtFileDst;
	CButton chbFileTDES;
	CEdit edtFileKey2;
    CStatic lblFileTDES;
	CProgressCtrl prcsbar;
};
