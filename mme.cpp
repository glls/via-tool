//---------------------------------------------------------------------------
//	taken from the project : MARUMO MPEG-2 EDITOR
//---------------------------------------------------------------------------
#pragma hdrstop

#include <limits.h>
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>

#include "m2v_vfapi.h"
#include "mme_project.h"
#include "query_frame.h"
#include "message.h"

//---------------------------------------------------------------------------
//   type definition
//---------------------------------------------------------------------------
typedef struct {
	HINSTANCE        instance;
	HWND             main_hwnd;
	HWND             callback_dlg;
	HWND             slide_bar;
	HACCEL           accel_tbl;
	M2V_VFAPI        vfapi;
	MME_PROJECT      project;
	HANDLE           clipboard;
	int              lang;
	char             openpath[MAX_PATH];
	char             savepath[MAX_PATH];
} MME_APP;


//---------------------------------------------------------------------------
// file local functions
//---------------------------------------------------------------------------
static void create_goplist(M2V_VFAPI *vfapi, char *path);

//---------------------------------------------------------------------------
/*
static void on_file_benchmark()
{
	__int64 i;
	int msec;
	int start;
	__int64 fps;
	char buffer[1024];

	EnableWindow(mme_app.main_hwnd, FALSE);

	start = GetTickCount();

	for(i=mme_app.project.in_point;i<mme_app.project.out_point+1;i++){
		set_frame_index_mme_project(&(mme_app.project), i);

		SetWindowText(mme_app.main_hwnd, get_status_str_mme_project(&(mme_app.project)));
		InvalidateRgn(mme_app.main_hwnd, NULL, FALSE);
		msg_pump();
	}

	i = mme_app.project.out_point - mme_app.project.in_point;
	msec = GetTickCount() - start;
	fps = i * 1000 * 1000 / msec;
	sprintf(buffer, "frame %I64d, time %d msec, fps %d.%03d", i, msec, (int)fps/1000, (int)fps%1000);
	MessageBox(mme_app.main_hwnd, buffer, "INFO", MB_ICONINFORMATION|MB_OK);

	EnableWindow(mme_app.main_hwnd, TRUE);

	return;
}

//---------------------------------------------------------------------------
static void on_file_goplist()
{
	OPENFILENAME of;
	char path[32768];
	char work[1024];
	char *head;
	int  n;

	DWORD gl_mode;

	// initialize
	memset(&of, 0, sizeof(OPENFILENAME));
	memset(path, 0, sizeof(path));
	of.lStructSize = sizeof(OPENFILENAME);
	of.hwndOwner = mme_app.main_hwnd;
	of.lpstrFile = path;
	of.nMaxFile = sizeof(path);
	of.lpstrFilter = mme_app.vfapi.info.cFileType;
	of.lpstrInitialDir = mme_app.openpath;
	of.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetOpenFileName(&of) == 0){
		return;
	}

	put_openpath(of.lpstrFile);

	gl_mode = get_goplist_mode();
	put_goplist_mode(2); // NEVER_USE_TIMECODE + SAVE_GL_FILE

	head = path + of.nFileOffset;
	while( head[0] != '\0' ){
		memcpy(work, path, of.nFileOffset);
		n = strlen(head) + 1;
		if(work[of.nFileOffset-1] == '\0'){
			work[of.nFileOffset-1] = '\\';
		}
		memcpy(work+of.nFileOffset, head, n);
		head += n;
		create_goplist(&(mme_app.vfapi), work);
	}

	//put_goplist_mode(gl_mode);

	return;
}
*/

//---------------------------------------------------------------------------
/*static void on_move_timecode()
{
	__int64 index;

	FRAME_BY_TIMECODE prm;

	prm.current = get_frame_index_mme_project(&(mme_app.project));
	prm.max = get_frame_count_mme_project(&(mme_app.project))-1;
	prm.lang = mme_app.lang;
	prm.rate = mme_app.project.video_info.dwRate;
	prm.scale = mme_app.project.video_info.dwScale;

	index = query_frame_by_timecode(mme_app.instance, mme_app.main_hwnd, &prm);

	if(index != set_frame_index_mme_project(&(mme_app.project), index)){
		MessageBox(mme_app.main_hwnd, get_error_msg_mme_project(&(mme_app.project)), "INFO", MB_OK|MB_ICONINFORMATION);
	}


	SetWindowText(mme_app.main_hwnd, get_status_str_mme_project(&(mme_app.project)));
	InvalidateRgn(mme_app.main_hwnd, NULL, FALSE);

	return;
}

//---------------------------------------------------------------------------
static void on_dropfiles(HANDLE hdrop)
{
	int n;
	char *path;

	n = DragQueryFile(hdrop, 0, NULL, 0) + 4;
	path = malloc(n);
	n = DragQueryFile(hdrop, 0, path, n);
	DragFinish(hdrop);
	open_file(path);
	free(path);
}
//---------------------------------------------------------------------------

static void resize(int client_width, int client_height)
{
	RECT rect;
	RECT client_rect;
	int h_diff;
	int v_diff;

	GetWindowRect(mme_app.main_hwnd, &rect);
	GetClientRect(mme_app.main_hwnd, &client_rect);

	h_diff = client_width - (client_rect.right - client_rect.left);
	v_diff = client_height - (client_rect.bottom - client_rect.top);

	rect.right += h_diff;
	rect.bottom += v_diff + 24;

	MoveWindow(mme_app.main_hwnd, rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top), TRUE);

	GetClientRect(mme_app.main_hwnd, &client_rect);

	h_diff = client_width - (client_rect.right - client_rect.left);
	v_diff = client_height - (client_rect.bottom - client_rect.top);

	rect.right += h_diff;
	rect.bottom += v_diff + 24;

	MoveWindow(mme_app.main_hwnd, rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top), TRUE);

	GetClientRect(mme_app.main_hwnd, &rect);

	MoveWindow(mme_app.slide_bar, rect.left, rect.bottom-24, (rect.right-rect.left), 24, TRUE);
}
*/

//---------------------------------------------------------------------------
static void create_goplist(M2V_VFAPI *vfapi, char *path)
{
	VF_FileHandle file;

	if(vfapi->func.OpenFile(path, &file) != VF_OK){
		return;
	}

	vfapi->func.CloseFile(file);
}
//---------------------------------------------------------------------------

