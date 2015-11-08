/*
 *  64 DWORD
 */
#ifndef VFAPI_H
#define VFAPI_H

#define	VF_STREAM_VIDEO 0x00000001
#define	VF_STREAM_AUDIO 0x00000002
#define	VF_OK           0x00000000
#define	VF_ERROR        0x80004005

typedef	struct {
	DWORD	dwSize;
	DWORD	dwAPIVersion;        /* Video File API */
	DWORD	dwVersion;
	DWORD	dwSupportStreamType;
	                             /* AVF_STREAM_VIDEO or VF_STREAM_AUDIO */
    char	cPluginInfo[256];    /* AVI ver 1.0 */
	char	cFileType[256];      /* AVI (*.avi)|*.avi */
} VF_PluginInfo,*LPVF_PluginInfo;

typedef	DWORD	VF_FileHandle,*LPVF_FileHandle;

typedef	struct {
	DWORD	dwSize;
	DWORD	dwHasStreams;
                            /* AVF_STREAM_VIDEO or VF_STREAM_AUDIO */
} VF_FileInfo,*LPVF_FileInfo;

typedef	struct {
	DWORD	dwSize;              
	DWORD	dwLengthL;
	DWORD	dwLengthH;
	DWORD	dwRate;              /*dwRate/dwScale */
	DWORD	dwScale;             
	DWORD	dwWidth;
	DWORD	dwHeight;           
	DWORD	dwBitCount;          /*(24) */
} VF_StreamInfo_Video,*LPVF_StreamInfo_Video;

typedef	struct {
	DWORD	dwSize;              
	DWORD	dwLengthL;           
	DWORD	dwLengthH;           
	DWORD	dwRate;
	DWORD	dwScale;             
	DWORD	dwChannels;          
	DWORD	dwBitsPerSample;     
	DWORD	dwBlockAlign;
} VF_StreamInfo_Audio,*LPVF_StreamInfo_Audio;

typedef	struct {
	DWORD	dwSize;             
	DWORD	dwFrameNumberL;     
	DWORD	dwFrameNumberH;     
	void	*lpData;            //(lpData + lPitch*Y)
	long	lPitch;
} VF_ReadData_Video,*LPVF_ReadData_Video;

typedef	struct {
	DWORD	dwSize;             
	DWORD	dwSamplePosL;       
	DWORD	dwSamplePosH;       
	DWORD	dwSampleCount;      
	DWORD	dwReadedSampleCount;
	DWORD	dwBufSize;          
	void	*lpBuf;
} VF_ReadData_Audio,*LPVF_ReadData_Audio;

typedef	struct {
	DWORD	dwSize;
	HRESULT (_stdcall *OpenFile)( char *lpFileName,LPVF_FileHandle lpFileHandle);
	HRESULT (_stdcall *CloseFile)( VF_FileHandle hFileHandle);
	HRESULT (_stdcall *GetFileInfo)( VF_FileHandle hFileHandle,LPVF_FileInfo lpFileInfo );
	HRESULT (_stdcall *GetStreamInfo)( VF_FileHandle hFileHandle,DWORD dwStream,void *lpStreamInfo );
	HRESULT (_stdcall *ReadData)( VF_FileHandle hFileHandle,DWORD dwStream,void *lpData ); 
} VF_PluginFunc,*LPVF_PluginFunc;

/*
HRESULT _stdcall vfGetPluginInfo( LPVF_PluginInfo lpPluginInfo );
HRESULT _stdcall vfGetPluginFunc( LPVF_PluginFunc lpPluginFunc );
*/

#endif /* VFAPI_H */