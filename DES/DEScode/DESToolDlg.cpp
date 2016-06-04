// DES ToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DESTool.h"
#include "DESToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDESToolDlg 对话框




CDESToolDlg::CDESToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDESToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE_KEY1, edtFileKey1);
	DDX_Control(pDX, IDC_EDIT_FILEPATH_SRC, edtFileSrc);
	DDX_Control(pDX, IDC_EDIT_FILEPATH_DST, edtFileDst);
	DDX_Control(pDX, IDC_CHECK_FILE_TDES, chbFileTDES);
	DDX_Control(pDX, IDC_EDIT_FILE_KEY2, edtFileKey2);
	DDX_Control(pDX, IDC_STATIC_FILETDES, lblFileTDES);
	DDX_Control(pDX, IDC_PROGRESS_FILE, prcsbar);
}

BEGIN_MESSAGE_MAP(CDESToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, &CDESToolDlg::OnBnClickedButtonEncrypt)
	ON_BN_CLICKED(IDC_CHECK_TDES, &CDESToolDlg::OnBnClickedCheckTdes)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CDESToolDlg::OnBnClickedButtonDecrypt)
	ON_BN_CLICKED(IDC_RADIO_HEX, &CDESToolDlg::OnBnClickedRadioHex)
	ON_BN_CLICKED(IDC_RADIO_BIN, &CDESToolDlg::OnBnClickedRadioBin)
	ON_BN_CLICKED(IDC_RADIO_RAW, &CDESToolDlg::OnBnClickedRadioRaw)
	ON_BN_CLICKED(IDC_BUTTON_CLEARPLAINTEXT, &CDESToolDlg::OnBnClickedButtonClearplaintext)
	ON_BN_CLICKED(IDC_BUTTON_CLEARCIPHERTEXT, &CDESToolDlg::OnBnClickedButtonClearciphertext)
	ON_BN_CLICKED(IDC_BUTTON_CLEARALL, &CDESToolDlg::OnBnClickedButtonClearall)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ABOUT, &CDESToolDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_SRC, &CDESToolDlg::OnBnClickedButtonBrowseSrc)
	ON_BN_CLICKED(IDC_CHECK_FILE_TDES, &CDESToolDlg::OnBnClickedCheckFileTdes)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_DST, &CDESToolDlg::OnBnClickedButtonBrowseDst)
	ON_BN_CLICKED(IDC_BUTTON_FILE_GO_E, &CDESToolDlg::OnBnClickedButtonFileGoE)
	ON_BN_CLICKED(IDC_BUTTON_GO_D, &CDESToolDlg::OnBnClickedButtonGoD)
END_MESSAGE_MAP()


// CDESToolDlg 消息处理程序

BOOL CDESToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_brush.CreateSolidBrush(RGB(255,255,255));   //生成一绿色刷子
	myDES = new yxyDES2();
	bIs3DES = false;
	memset(szPlaintextData,0,8192);
	memset(bitsCiphertextAnyLength,0,32768);
	memset(hexCiphertextAnyLength,0,16384);
	memset(szCiphertextData,0,8192);
	memset(szSourceKey1,0,8);
	memset(szSourceKey2,0,8);
	CButton *rdbHex = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	rdbHex->SetCheck(true);
	SetBitmap(IDB_BITMAP1,IDC_STATIC_PIC);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDESToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDESToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDESToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDESToolDlg::OnBnClickedButtonEncrypt()
{
	yxyDES2 *myDES = new yxyDES2();
	CEdit *edtKey = (CEdit*)GetDlgItem(IDC_EDIT_KEY);
	CEdit *edtKeyTDES = (CEdit*)GetDlgItem(IDC_EDIT_KEYTDES);
	CEdit *edtPlaintext = (CEdit*)GetDlgItem(IDC_EDIT_PLAINTEXT);
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);
	CButton *rdbHex = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	CButton *rdbBin = (CButton*)GetDlgItem(IDC_RADIO_BIN);
	CButton *rdbRaw = (CButton*)GetDlgItem(IDC_RADIO_RAW);
	CString strKey,strKeyTDES,strPlaintext,strCiphertext;

	edtKey->GetWindowText(strKey);
	edtPlaintext->GetWindowText(strPlaintext);
	edtCiphertext->GetWindowText(strCiphertext);
	edtKeyTDES->GetWindowText(strKeyTDES);

	memset(szSourceKey1,0,8);
	memset(szSourceKey2,0,8);
	memset(szPlaintextData,0,8192);
	memcpy(szSourceKey1,strKey.GetBuffer(),strKey.GetLength() < 8 ? strKey.GetLength() : 8);
	memcpy(szSourceKey2,strKeyTDES.GetBuffer(),strKeyTDES.GetLength() < 8 ? strKeyTDES.GetLength() : 8);

	myDES->InitializeKey(szSourceKey1,0);
	//Clear the old text
	edtCiphertext->SetWindowText("");
	//myDES->EncryptAnyLength((char*)(LPCTSTR)strPlaintext,strPlaintext.GetLength());
	memcpy(szPlaintextData,strPlaintext.GetBuffer(),strPlaintext.GetLength());

	if(bIs3DES)
	{
		myDES->InitializeKey(szSourceKey2,1); //use key2
		//E(key0)-D(key1)-E(key0)
		myDES->EncryptAnyLength(szPlaintextData,strlen(szPlaintextData),0);
		myDES->DecryptAnyLength(myDES->GetCiphertextAnyLength(),strlen(myDES->GetCiphertextAnyLength()),1);
		myDES->EncryptAnyLength(myDES->GetPlaintextAnyLength(),strlen(myDES->GetPlaintextAnyLength()),0);
	}
	else
	{
		myDES->EncryptAnyLength(szPlaintextData,strlen(szPlaintextData),0);
	}
	ConvertCiphertext2OtherFormat(strlen(szPlaintextData) % 8 == 0 ? strlen(szPlaintextData) << 3 : ((strlen(szPlaintextData)>>3) + 1) << 6,myDES->GetCiphertextAnyLength());
	if(rdbHex->GetCheck())
	{
		edtCiphertext->SetWindowText(hexCiphertextAnyLength);
	}
	else if(rdbBin->GetCheck())
	{
		edtCiphertext->SetWindowText(bitsCiphertextAnyLength);
	}
	else
	{
		edtCiphertext->SetWindowText(myDES->GetCiphertextAnyLength());
	}
}

void CDESToolDlg::OnBnClickedCheckTdes()
{
	CButton *chbIsTDES = (CButton*)GetDlgItem(IDC_CHECK_TDES);
	CEdit *edtKeyTDES = (CEdit*)GetDlgItem(IDC_EDIT_KEYTDES);
	CStatic *lblTDES = (CStatic*)GetDlgItem(IDC_STATIC_TDES);

	if(chbIsTDES->GetCheck() == BST_CHECKED)
	{
		bIs3DES = true;
		edtKeyTDES->EnableWindow(true);
		edtKeyTDES->ShowWindow(SW_NORMAL);
		lblTDES->ShowWindow(SW_NORMAL);

	}
	else
	{
		bIs3DES = false;
		edtKeyTDES->SetWindowText("");
		edtKeyTDES->EnableWindow(false);
		edtKeyTDES->ShowWindow(SW_HIDE);
		lblTDES->ShowWindow(SW_HIDE);
	}
}

void CDESToolDlg::OnBnClickedButtonDecrypt()
{
	CEdit *edtKey = (CEdit*)GetDlgItem(IDC_EDIT_KEY);
	CEdit *edtKeyTDES = (CEdit*)GetDlgItem(IDC_EDIT_KEYTDES);
	CEdit *edtPlaintext = (CEdit*)GetDlgItem(IDC_EDIT_PLAINTEXT);
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);
	CButton *rdbRaw = (CButton*)GetDlgItem(IDC_RADIO_RAW);
	CString strKey,strKeyTDES,strPlaintext,strCiphertext;

	if(rdbRaw->GetCheck())
	{
		MessageBox("原始密文有不可显示字符,解密将不能得到正确结果.","警告",MB_OK);
		return;
	}

	edtKey->GetWindowText(strKey);
	edtPlaintext->GetWindowText(strPlaintext);
	edtCiphertext->GetWindowText(strCiphertext);
	edtKeyTDES->GetWindowText(strKeyTDES);

	memset(szSourceKey1,0,8);
	memset(szSourceKey2,0,8);
	memset(szCiphertextData,0,8192);
	memcpy(szSourceKey1,strKey.GetBuffer(),strKey.GetLength() < 8 ? strKey.GetLength() : 8);
	memcpy(szSourceKey2,strKeyTDES.GetBuffer(),strKeyTDES.GetLength() < 8 ? strKeyTDES.GetLength() : 8);

	myDES->InitializeKey(szSourceKey1,0);
	//Clear the old text
	edtPlaintext->SetWindowText("");
	if(bIs3DES)
	{
		myDES->InitializeKey(szSourceKey2,1); //key2
		//D(key0)-E(key1)-D(key0)
		myDES->DecryptAnyLength(szCiphertextData,ConvertOtherFormat2Ciphertext(strCiphertext.GetBuffer()),0);
		myDES->EncryptAnyLength(myDES->GetPlaintextAnyLength(),strlen(myDES->GetPlaintextAnyLength()),1);
		myDES->DecryptAnyLength(myDES->GetCiphertextAnyLength(),strlen(myDES->GetCiphertextAnyLength()),0);
	}
	else
	{
		//Decrypt		
		myDES->DecryptAnyLength(szCiphertextData,ConvertOtherFormat2Ciphertext(strCiphertext.GetBuffer()),0);
	}
	edtPlaintext->SetWindowText((LPCTSTR)myDES->GetPlaintextAnyLength());
}

void CDESToolDlg::ConvertCiphertext2OtherFormat(int iBitsLen,char *szCipherInBytes)
{
	memset(hexCiphertextAnyLength,0,16384);
	memset(bitsCiphertextAnyLength,0,32768);
	myDES->Bytes2Bits(szCipherInBytes,bitsCiphertextAnyLength,iBitsLen);
	myDES->Bits2Hex(hexCiphertextAnyLength,bitsCiphertextAnyLength,iBitsLen);
	for(int i=0;i<iBitsLen;i++)
	{
		bitsCiphertextAnyLength[i] += 48;
	}
}

int CDESToolDlg::ConvertOtherFormat2Ciphertext(char *szCipher)
{
	CButton *rdbHex = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	CButton *rdbBin = (CButton*)GetDlgItem(IDC_RADIO_BIN);
	CButton *rdbRaw = (CButton*)GetDlgItem(IDC_RADIO_RAW);

	int iLen = 0;
	memset(szCiphertextData,0,8192);
	if(rdbHex->GetCheck())
	{
		iLen = ((strlen(szCipher)>>2) + (strlen(szCipher) % 4 == 0 ? 0 : 1))<<4;
		memset(hexCiphertextAnyLength,0,16384);
		memcpy(hexCiphertextAnyLength,szCipher,strlen(szCipher));
		myDES->Hex2Bits(hexCiphertextAnyLength,bitsCiphertextAnyLength,iLen);
		myDES->Bits2Bytes(szCiphertextData,bitsCiphertextAnyLength,iLen);
	}
	else if(rdbBin->GetCheck())
	{
		iLen = strlen(szCipher);
		memset(bitsCiphertextAnyLength,0,32768);
		memcpy(bitsCiphertextAnyLength,szCipher,iLen);
		for(long i=0;i< iLen;i++)
		{
			bitsCiphertextAnyLength[i]-= 48;
		}
		myDES->Bits2Bytes(szCiphertextData,bitsCiphertextAnyLength,iLen);
	}
	return iLen>>3;
}
void CDESToolDlg::OnBnClickedRadioHex()
{
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);
	if(hexCiphertextAnyLength[0] < 48)
	{
		for(unsigned i=0;i < strlen(bitsCiphertextAnyLength) >> 2;i++)
		{
			hexCiphertextAnyLength[i] += hexCiphertextAnyLength[i] > 9 ? 55 : 48; //convert to char '0'-'F'
		}
	}
	edtCiphertext->SetWindowText(hexCiphertextAnyLength);
}

void CDESToolDlg::OnBnClickedRadioBin()
{
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);
	if(bitsCiphertextAnyLength[0] < 48)
	{
		for(unsigned i=0;i < strlen(hexCiphertextAnyLength) << 2 ;i++)
		{
			bitsCiphertextAnyLength[i] += 48;  //0 to '0'
		}
	}
	edtCiphertext->SetWindowText(bitsCiphertextAnyLength);
}

void CDESToolDlg::OnBnClickedRadioRaw()
{
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);
	edtCiphertext->SetWindowText(szCiphertextData);
}

void CDESToolDlg::OnBnClickedButtonClearplaintext()
{
	CEdit *edtPlaintext = (CEdit*)GetDlgItem(IDC_EDIT_PLAINTEXT);
	edtPlaintext->SetWindowText("");
}

void CDESToolDlg::OnBnClickedButtonClearciphertext()
{
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);
	edtCiphertext->SetWindowText("");
}

void CDESToolDlg::OnBnClickedButtonClearall()
{
	CEdit *edtKey = (CEdit*)GetDlgItem(IDC_EDIT_KEY);
	CEdit *edtKeyTDES = (CEdit*)GetDlgItem(IDC_EDIT_KEYTDES);
	CEdit *edtPlaintext = (CEdit*)GetDlgItem(IDC_EDIT_PLAINTEXT);
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_EDIT_CIPHERTEXT);

	edtKey->SetWindowText("");
	edtKeyTDES->SetWindowText("");
	edtPlaintext->SetWindowText("");
	edtCiphertext->SetWindowText("");
}

void CDESToolDlg::SetBitmap(UINT uBmpResource,UINT uCtrlResource)     
{   
	HBITMAP hBitmap;   
	CStatic *pStatic = (CStatic*)GetDlgItem(uCtrlResource);   
	hBitmap = (HBITMAP)LoadImage(
		AfxGetInstanceHandle(),     
		MAKEINTRESOURCE(uBmpResource),     
		IMAGE_BITMAP,     
		0,     
        0,     
        LR_LOADMAP3DCOLORS);   
	pStatic->ModifyStyle(0xF,SS_BITMAP);   
	pStatic->SetBitmap(hBitmap);

}
HBRUSH CDESToolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    //if(nCtlColor==CTLCOLOR_DLG || nCtlColor==CTLCOLOR_STATIC)   
	return  m_brush;       //返加自定义白色刷子   
    //else
	    //return hbr; 
}

void CDESToolDlg::OnBnClickedAbout()
{
	CAboutDlg* my_about = new CAboutDlg();
	my_about->DoModal();
}

void CDESToolDlg::OnBnClickedButtonBrowseSrc()
{
	CFileDialog *open_file = new CFileDialog(TRUE,"*.*",NULL,NULL,"All Files(*.*)|*.*|",NULL,0,0);
	if(open_file->DoModal() == IDOK)
	{
		edtFileSrc.SetWindowText(open_file->GetPathName());
	}
}

void CDESToolDlg::OnBnClickedCheckFileTdes()
{
	if(chbFileTDES.GetCheck())
	{
		lblFileTDES.ShowWindow(SW_SHOW);
		edtFileKey2.ShowWindow(SW_SHOW);
	}
	else
	{
		lblFileTDES.ShowWindow(SW_HIDE);
		edtFileKey2.ShowWindow(SW_HIDE);
	}
}

void CDESToolDlg::OnBnClickedButtonBrowseDst()
{
	CFileDialog *save_file = new CFileDialog(FALSE,"*.*",NULL,OFN_OVERWRITEPROMPT,"All Files(*.*)|*.*|",NULL,0,0);
	if(save_file->DoModal() == IDOK)
	{
		edtFileDst.SetWindowText(save_file->GetPathName());
	}
}

void CDESToolDlg::OnBnClickedButtonFileGoE()
{
	FILE *fpSrc,*fpDst;
	CString szSrcPath,szDstPath,szKey1,szKey2;
	char buff[8] = {0};
	long fileSize = 0, hasDone = 0;

	edtFileSrc.GetWindowText(szSrcPath);
	edtFileDst.GetWindowText(szDstPath);
	edtFileKey1.GetWindowText(szKey1);
	edtFileKey2.GetWindowText(szKey2);

	if((fpSrc = fopen(szSrcPath.GetBuffer(),"rb")) == NULL)
	{
		MessageBox("打不开源文件!","错误",MB_OK | MB_ICONERROR);
		return;
	}
	if((fpDst = fopen(szDstPath.GetBuffer(),"wb")) == NULL)
	{
		MessageBox("打不开目的文件!","错误",MB_OK | MB_ICONERROR);
		return;
	}
	
	fseek(fpSrc,0,SEEK_SET);
	fseek(fpSrc,0,SEEK_END);
	fileSize = ftell(fpSrc);
	rewind(fpSrc);
	prcsbar.SetRange(0,100);
	prcsbar.ShowWindow(SW_SHOW);
	myDES->InitializeKey(szKey1.GetBuffer(),0);

	if(chbFileTDES.GetCheck())
	{
		myDES->InitializeKey(szKey2.GetBuffer(),1);
		while(!feof(fpSrc))
		{
			memset(buff,0,8);
			fread(buff,sizeof(char),8,fpSrc);
			//E(key0)-D(key1)-E(key0)
			myDES->EncryptData(buff, 0);
			myDES->DecryptData(myDES->GetCiphertextInBytes(), 1);
			myDES->EncryptData(myDES->GetPlaintext(), 0);
			fwrite(myDES->GetCiphertextInBytes(),sizeof(char),8,fpDst);
			hasDone += 8;
			prcsbar.SetPos((int)(hasDone  * 100 / fileSize));
		}
	}
	else
	{
		while(!feof(fpSrc))
		{
			memset(buff,0,8);
			fread(buff,sizeof(char),8,fpSrc);
			myDES->EncryptData(buff,0);
			fwrite(myDES->GetCiphertextInBytes(),sizeof(char),8,fpDst);
			hasDone += 8;
			prcsbar.SetPos((int)(hasDone  * 100 / fileSize));
		}
	}
	fclose(fpSrc);
	fclose(fpDst);
	prcsbar.SetPos(100);
	MessageBox("加密完成!","提示",MB_OK | MB_ICONINFORMATION);
	prcsbar.ShowWindow(SW_HIDE);
}

void CDESToolDlg::OnBnClickedButtonGoD()
{
	FILE *fpSrc,*fpDst;
	CString szSrcPath,szDstPath,szKey1,szKey2;
	char buff[8] = {0};
	long fileSize = 0,hasDone = 0;

	edtFileSrc.GetWindowText(szSrcPath);
	edtFileDst.GetWindowText(szDstPath);
	edtFileKey1.GetWindowText(szKey1);
	edtFileKey2.GetWindowText(szKey2);

	if((fpSrc = fopen(szSrcPath.GetBuffer(),"rb")) == NULL)
	{
		MessageBox("打不开源文件!","错误",MB_OK | MB_ICONERROR);
		return;
	}
	if((fpDst = fopen(szDstPath.GetBuffer(),"wb")) == NULL)
	{
		MessageBox("打不开目的文件!","错误",MB_OK | MB_ICONERROR);
		return;
	}
	
	fseek(fpSrc,0,SEEK_SET);
	fseek(fpSrc,0,SEEK_END);
	fileSize = ftell(fpSrc);
	rewind(fpSrc);
	prcsbar.SetRange(0,100);
	prcsbar.ShowWindow(SW_SHOW);
	myDES->InitializeKey(szKey1.GetBuffer(),0);

	if(chbFileTDES.GetCheck())
	{
		myDES->InitializeKey(szKey2.GetBuffer(),1);
		while(!feof(fpSrc))
		{
			memset(buff,0,8);
			fread(buff,sizeof(char),8,fpSrc);
			//D(key0)-E(key1)-D(key0)
			myDES->DecryptData(buff, 0);
			myDES->EncryptData(myDES->GetPlaintext(), 1);
			myDES->DecryptData(myDES->GetCiphertextInBytes(), 0);
			fwrite(myDES->GetPlaintext(),sizeof(char),8,fpDst);
			hasDone += 8;
			prcsbar.SetPos((int)(hasDone  * 100 / fileSize));
		}
	}
	else
	{
		while(!feof(fpSrc))
		{
			memset(buff,0,8);
			fread(buff,sizeof(char),8,fpSrc);
			myDES->DecryptData(buff,0);
			fwrite(myDES->GetPlaintext(),sizeof(char),8,fpDst);
			hasDone += 8;
			prcsbar.SetPos((int)(hasDone  * 100 / fileSize));
		}
	}
	fclose(fpSrc);
	fclose(fpDst);
	prcsbar.SetPos(100);
	MessageBox("解密完成!","提示",MB_OK | MB_ICONINFORMATION);
	prcsbar.ShowWindow(SW_HIDE);
}
