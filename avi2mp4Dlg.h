
// avi2mp4Dlg.h : ͷ�ļ�
//

#pragma once
#include "quicktime.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <stdio.h>


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
	CListBox m_ListBox;
	afx_msg void OnBnClickedButton1();
	CListBox m_ListBox2;
	afx_msg void OnBnClickedList();
};
