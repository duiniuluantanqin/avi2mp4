
// avi2mp4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "avi2mp4.h"
#include "avi2mp4Dlg.h"
#include <stdio.h>
#include "Vfw.h"


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


// Cavi2mp4Dlg 对话框




Cavi2mp4Dlg::Cavi2mp4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cavi2mp4Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cavi2mp4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_ListBox2);
}

BEGIN_MESSAGE_MAP(Cavi2mp4Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &Cavi2mp4Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Cavi2mp4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(ID_LIST, &Cavi2mp4Dlg::OnBnClickedList)
END_MESSAGE_MAP()


// Cavi2mp4Dlg 消息处理程序

BOOL Cavi2mp4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cavi2mp4Dlg::OnPaint()
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
HCURSOR Cavi2mp4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cavi2mp4Dlg::OnBnClickedOk()
{
	char* filename = "D:\\Youku Files\\transcode\\test101_baofeng_003.mp4";
	char* newfilename = "D:\\Youku Files\\transcode\\new.mp4";
	
	quicktime_t* file = quicktime_open(filename, 1, 0, 0);
	quicktime_t* newfile = quicktime_open(newfilename, 0, 1, 0);
	if (NULL == file || NULL == newfile)
	{
		return;
	}

    long time_scale = quicktime_get_time_scale(file);
    quicktime_set_time_scale(newfile, time_scale);
    //char* session_sdp = quicktime_get_session_sdp(file);
    //quicktime_set_session_sdp(newfile, session_sdp);
	
	int track_count = quicktime_video_tracks(file);  
	for (int index = 0; index < track_count; ++index)
	{			
		int frame_height = quicktime_video_height(file, index);
		int frame_weight = quicktime_video_width(file, index);
		int frame_depth =  quicktime_video_depth(file, index);
		long frame_length = quicktime_video_length(file, index);
		float frame_rate =   quicktime_video_frame_rate(file, index);
		int time_scale =   quicktime_video_time_scale(file, index);
		char* compressor = quicktime_video_compressor(file, index);
        //long duration = file->vtracks->track->mdia.minf.stbl.stts.table->sample_duration;
        long duration = quicktime_sample_duration(file->moov.trak[index]);
		
		quicktime_set_framerate(newfile, frame_rate);
		quicktime_set_depth(newfile, frame_depth, index);
		quicktime_set_video(newfile, track_count, frame_weight, frame_height, frame_rate, time_scale, compressor);
        
        u_char* ppBuf[1024];
        int pBufSize;
        quicktime_get_mp4_video_decoder_config(file, index, ppBuf, &pBufSize);
        quicktime_set_mp4_video_decoder_config(newfile, index, *ppBuf, pBufSize);

        u_char* header[1024];
        int header_size = 0;
        quicktime_get_avcc_header(&(file->moov.trak[index]->mdia.minf.stbl.stsd.table->avcc), header, &header_size);
        quicktime_set_avcc_header(&(newfile->moov.trak[index]->mdia.minf.stbl.stsd.table->avcc), *header, header_size);
   

        int profile_id = quicktime_get_iod_video_profile_level(file);
        quicktime_set_iod_video_profile_level(newfile, profile_id);


        //quicktime_seek_start(newfile);        
        unsigned char video_buffer[0x40000];
        int num = 0;
        while(num++ < quicktime_track_samples(file, file->vtracks[index].track))
        { 
            memset(video_buffer, 0, 0x40000);   
            long bytes = quicktime_read_frame(file, video_buffer, index);
            if (bytes <= 0)
            {
                break;
            } 
            if(bytes >= 4)
            {
                //unsigned char* p = &video_buffer[0];
                //*p = htonl(bytes - 4);//大端,去掉头部四个字节
            }
            quicktime_write_video_frame(newfile, video_buffer, bytes, index, 0, duration, 0);                     
        }       
	}

  	track_count = quicktime_audio_tracks(file);  
    for (int index = 0; index < track_count; ++index)
    {			
        long length = quicktime_audio_length(file, index);
        int channels = quicktime_track_channels(file, index);
        char* compressor = quicktime_audio_compressor(file, index);
        int time_scale = quicktime_audio_time_scale(file, index);

        float sample_rate = file->atracks->track->mdia.minf.stbl.stsd.table->sample_rate;
        int bits = file->atracks->track->mdia.minf.stbl.stsd.table->sample_size;
        int sample_size = file->atracks->track->mdia.minf.stbl.stsz.sample_size;
        int sample_duration = file->atracks->track->mdia.minf.stbl.stts.table->sample_duration;
        quicktime_set_audio(newfile, channels, sample_rate, bits, sample_size, time_scale, sample_duration, compressor);

        u_char* ppBuf[1024];
        int pBufSize;
        quicktime_get_mp4_audio_decoder_config(file, index, ppBuf, &pBufSize);
        quicktime_set_mp4_audio_decoder_config(newfile, index, *ppBuf, pBufSize);

        int profile_id = quicktime_get_iod_video_profile_level(file);
        quicktime_set_iod_video_profile_level(newfile, profile_id);

        unsigned char audio_buffer[0x40000];
        int num = 0;
        while(num++ < quicktime_track_samples(file, file->atracks[index].track))
        {
            memset(audio_buffer, 0, 0x40000); 
            int bytes = quicktime_read_audio_frame(file, audio_buffer, 10000, index);
            if (bytes <= 0)
            {
                break;
            }
            quicktime_write_audio_frame(newfile, audio_buffer, bytes, index);
        }
    }	

	quicktime_close(newfile);
	quicktime_close(file);
    AfxMessageBox("Conversion OK！");
}

void Cavi2mp4Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Cavi2mp4Dlg::OnBnClickedList()
{
//     CString strAVIFileName;
//     strAVIFileName = "D:\\Youku Files\\transcode\\test_baofeng.avi";
//     char* newfilename = "D:\\Youku Files\\transcode\\avi2mp4.mp4";
// 
//     quicktime_t* newfile = quicktime_open(newfilename, 0, 1, 0);
//     if (newfile == NULL)
//     {
//         return;
//     }
// 
//     AVIFileInit();
//     PAVIFILE avi;
//     int res=AVIFileOpen(&avi, strAVIFileName, OF_READ, NULL);
//     int n = GetLastError();
//     if (res!=AVIERR_OK)
//     {
//         //an error occures
//         if (avi!=NULL)
//             AVIFileRelease(avi);
//         return ;
//     }
//     AVIFILEINFO avi_info;
//     AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
// 
//     quicktime_set_time_scale(newfile, avi_info.dwScale);
//     quicktime_set_framerate(newfile, avi_info.dwRate);
//     //quicktime_set_depth(newfile, avi_info., 0);
//     quicktime_set_video(newfile, 1, avi_info.dwWidth, avi_info.dwHeight, avi_info.dwRate, avi_info.dwScale, "mp4v");
// 
//     PAVISTREAM pStream;
//      res=AVIFileGetStream(avi, &pStream, streamtypeVIDEO /*video stream*/,0 /*first stream*/);
//     if (res!=AVIERR_OK)
//     {
//         if (pStream!=NULL)
//             AVIStreamRelease(pStream);
//         AVIFileExit();
//         return ;
//     }
// 
//     //do some task with the stream
//     int iNumFrames;
//     int iFirstFrame;
//     iFirstFrame=AVIStreamStart(pStream);
//     if (iFirstFrame==-1)
//     {
//         //Error getteing the frame inside the stream
//         if (pStream!=NULL)
//             AVIStreamRelease(pStream);
//         AVIFileExit();
//         return ;
//     }
//     iNumFrames=AVIStreamLength(pStream);
//     if (iNumFrames==-1)
//     {
//         //Error getteing the number of frames inside the stream
//         if (pStream!=NULL)
//             AVIStreamRelease(pStream);
//         AVIFileExit();
//         return ;
//     }
// 
//     //getting bitmap from frame
//     BITMAPINFOHEADER bih;
//     ZeroMemory(&bih, sizeof(BITMAPINFOHEADER));
// 
//     bih.biBitCount=24; //24 bit per pixel
//     bih.biClrImportant=0;
//     bih.biClrUsed = 0;
//     bih.biCompression = BI_RGB;
//     bih.biPlanes = 1;
//     bih.biSize = 40;
//     bih.biXPelsPerMeter = 0;
//     bih.biYPelsPerMeter = 0;
//     //calculate total size of RGBQUAD scanlines (DWORD aligned)
//     bih.biSizeImage = (((bih.biWidth * 3) + 3) & 0xFFFC) * bih.biHeight ;
// 
//     PGETFRAME pFrame;
//     pFrame=AVIStreamGetFrameOpen(pStream, NULL );
// 
//     AVISTREAMINFO streaminfo;
//     AVIStreamInfo(pStream,&streaminfo,sizeof(AVISTREAMINFO));
// 
//     //Get the first frame
//     BITMAPINFOHEADER bih2;
//     long lsize = sizeof(bih2);
//     int index=0;
//     for (int i=iFirstFrame; i<iNumFrames; i++)
//     {
//         index= i-iFirstFrame;
//         BYTE* pDIB = (BYTE*) AVIStreamGetFrame(pFrame, index); //
//         AVIStreamReadFormat(pStream,index,&bih2,&lsize);
//         BITMAPFILEHEADER stFileHdr;
// 
//         BYTE* Bits=new BYTE[bih2.biSizeImage];
//         AVIStreamRead(pStream,index,1,Bits,bih2.biSizeImage,NULL,NULL);
//         //RtlMoveMemory(Bits, pDIB + sizeof(BITMAPINFOHEADER), bih2.biSizeImage);
// 
//         bih2.biClrUsed =0;
//         stFileHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
//         stFileHdr.bfSize=sizeof(BITMAPFILEHEADER);
//         stFileHdr.bfType=0x4d42;
// 
//         
//         /////
//         delete Bits;
//         //CreateFromPackedDIBPointer(pDIB, index);
//     }
// 
//     AVIStreamGetFrameClose(pFrame);
// 
//     //close the stream after finishing the task
//     if (pStream!=NULL)
//         AVIStreamRelease(pStream);
//     AVIFileExit();
//     quicktime_close(newfile);
}
