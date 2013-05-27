
// avi2mp4Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "avi2mp4.h"
#include "avi2mp4Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    // ʵ��
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


// Cavi2mp4Dlg �Ի���




Cavi2mp4Dlg::Cavi2mp4Dlg(CWnd* pParent /*=NULL*/)
: CDialog(Cavi2mp4Dlg::IDD, pParent)
, m_FilePathName(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cavi2mp4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_FilePathName);
}

BEGIN_MESSAGE_MAP(Cavi2mp4Dlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &Cavi2mp4Dlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON1, &Cavi2mp4Dlg::OnBnClickedButton1)
    ON_BN_CLICKED(ID_LIST, &Cavi2mp4Dlg::OnBnClickedList)
    ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &Cavi2mp4Dlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


// Cavi2mp4Dlg ��Ϣ�������

BOOL Cavi2mp4Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cavi2mp4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cavi2mp4Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cavi2mp4Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void Cavi2mp4Dlg::OnBnClickedOk()
{
    UpdateData(TRUE);
    if (m_FilePathName.IsEmpty())
    {
        AfxMessageBox(_T("��ѡ���ļ���"));
        return;
    }

    CStringA tempPathNameA = m_FilePathName;
    CStringA tempPathA = m_FilePath + "\\new.mp4";

    char *oldfilename =  tempPathNameA.GetBuffer(tempPathNameA.GetLength()); 
    char *newfilename =  tempPathA.GetBuffer(tempPathA.GetLength());

    quicktime_t *oldfile = quicktime_open(oldfilename, 1, 0, 0);
    quicktime_t *newfile = quicktime_open(newfilename, 0, 1, 0);
    if (NULL == oldfile || NULL == newfile)
    {
        AfxMessageBox(_T("���ļ�ʧ��"));
        return;
    }

    long time_scale = quicktime_get_time_scale(oldfile);
    quicktime_set_time_scale(newfile, time_scale);
    //char* session_sdp = quicktime_get_session_sdp(file);
    //quicktime_set_session_sdp(newfile, session_sdp);

    int video_track_count = quicktime_video_tracks(oldfile);  
    for (int index = 0; index < video_track_count; ++index)
    {
        long length      = quicktime_video_length(oldfile, index);
        int frame_height = quicktime_video_height(oldfile, index);
        int frame_weight = quicktime_video_width(oldfile, index);
        int frame_depth  = quicktime_video_depth(oldfile, index);		
        float frame_rate = quicktime_video_frame_rate(oldfile, index);
        int time_scale   = quicktime_video_time_scale(oldfile, index);
        char *compressor = quicktime_video_compressor(oldfile, index);
        
        quicktime_set_framerate(newfile, frame_rate);
        quicktime_set_depth(newfile, frame_depth, index);
        quicktime_set_video(newfile, video_track_count, frame_weight, frame_height, frame_rate, time_scale, compressor);

        u_char *ppBuf[BUFSIZE] = {0};
        int pBufSize;
        quicktime_get_mp4_video_decoder_config(oldfile, index, ppBuf, &pBufSize);
        if (pBufSize > 0)
        {
            quicktime_set_mp4_video_decoder_config(newfile, index, *ppBuf, pBufSize);
        }
        
        u_char header[BUFSIZE] = {0};
        int header_size = 0;
        quicktime_get_avcc_header(&(oldfile->moov.trak[index]->mdia.minf.stbl.stsd.table->avcc), header, &header_size);
        if (header_size > 0)
        {
            quicktime_set_avcc_header(&(newfile->moov.trak[index]->mdia.minf.stbl.stsd.table->avcc), header, header_size);
        }

        int profile_id = quicktime_get_iod_video_profile_level(oldfile);
        quicktime_set_iod_video_profile_level(newfile, profile_id);

        u_char video_buffer[MAX_BYTES_PER_FRAME];
        for (int num = 0; num < length; ++num)
        { 
            memset(video_buffer, 0, MAX_BYTES_PER_FRAME);   
            long bytes = quicktime_read_frame(oldfile, video_buffer, index);
            long duration = quicktime_sample_duration(oldfile->moov.trak[index]);
            if (bytes <= 0)
            {
                break;
            } 
            u_char key_frame = 0;
            if (quicktime_has_keyframes(oldfile, index))
            {
                for (int i = 0; i < oldfile->vtracks->track[index].mdia.minf.stbl.stss.total_entries; ++i)
                {
                    if (oldfile->vtracks->current_position == oldfile->vtracks->track[index].mdia.minf.stbl.stss.table[i].sample)
                    {
                        key_frame = 1;
                        break;
                    }
                }
            }
            //quicktime_h264_is_key(video_buffer, bytes, compressor);
            quicktime_write_video_frame(newfile, video_buffer, bytes, index, key_frame, duration, 0);                     
        }       
    }

    int audio_track_count = quicktime_audio_tracks(oldfile);  
    for (int index = 0; index < audio_track_count; ++index)
    {
        long length         = quicktime_audio_length(oldfile, index);
        int channels        = quicktime_track_channels(oldfile, index);
        char *compressor    = quicktime_audio_compressor(oldfile, index);
        int time_scale      = quicktime_audio_time_scale(oldfile, index);
        long sample_rate    = quicktime_audio_sample_rate(oldfile, index);
        int bits            = quicktime_audio_bits(oldfile, index);
        int sample_duration = quicktime_audio_sample_duration(oldfile, index);

        quicktime_set_audio(newfile, channels, sample_rate, bits, 0/*size == 0, use table*/, time_scale, sample_duration, compressor);

        u_char *ppBuf[BUFSIZE] = {0};
        int pBufSize = 0;
        quicktime_get_mp4_audio_decoder_config(oldfile, index, ppBuf, &pBufSize);
        quicktime_set_mp4_audio_decoder_config(newfile, index, *ppBuf, pBufSize);

        int profile_id = quicktime_get_iod_video_profile_level(oldfile);
        quicktime_set_iod_video_profile_level(newfile, profile_id);

        u_char audio_buffer[MAX_BYTES_PER_FRAME];
        for (int num = 0; num < length; ++num)
        {
            memset(audio_buffer, 0, MAX_BYTES_PER_FRAME); 
            int bytes = quicktime_read_audio_frame(oldfile, audio_buffer, MAX_BYTES_PER_FRAME, index);
            if (bytes <= 0)
            {
                break;
            }
            quicktime_write_audio_frame(newfile, audio_buffer, bytes, index);
        }
    }

    quicktime_close(newfile);
    quicktime_close(oldfile);

    tempPathNameA.ReleaseBuffer();
    tempPathA.ReleaseBuffer();
    AfxMessageBox(_T("ת����ɣ���������ͬĿ¼new.mp4"));
}

void Cavi2mp4Dlg::OnBnClickedButton1()
{
    CFileDialog dlg(TRUE,
                    NULL, 
                    NULL,
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                    (LPCTSTR)_TEXT("����ý���ļ� (*.mp4;*.avi)|*.mp4;*.avi|�����ļ� (*.*)|*.*||"),
                    NULL);

    if (IDOK == dlg.DoModal())
    {
        m_FilePathName = dlg.GetPathName();
        m_FilePath     = dlg.GetFolderPath();
    }
    UpdateData(FALSE);
}

void Cavi2mp4Dlg::OnBnClickedList()
{
    OnCancel();
}

void Cavi2mp4Dlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{   
    ShellExecuteW(NULL, L"open", m_FilePath, NULL, NULL, SW_SHOWNORMAL);          
    *pResult = 0;  
}
