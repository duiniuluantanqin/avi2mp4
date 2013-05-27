
// avi2mp4Dlg.h : ͷ�ļ�
//

#pragma once
#include "quicktime.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <stdio.h>

const int BUFSIZE = 2048;
const long MAX_BYTES_PER_FRAME = 100000;


// Cavi2mp4Dlg �Ի���
class Cavi2mp4Dlg : public CDialog
{
    // ����
public:
    Cavi2mp4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

    // �Ի�������
    enum { IDD = IDD_AVI2MP4_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


    // ʵ��
protected:
    HICON m_hIcon;

    // ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedList();
private:
    CString m_FilePath;
    CString m_FilePathName;
public:
    afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};
