// DES ToolDlg.h : 头文件
//

#pragma once
#include "yxyDES2.h"

// CDESToolDlg 对话框
class CDESToolDlg : public CDialog
{
// 构造
public:
	CDESToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DESTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
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
	// 生成的消息映射函数
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
