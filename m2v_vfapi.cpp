//---------------------------------------------------------------------------
//  m2v.vfp interface
//---------------------------------------------------------------------------
#pragma hdrstop

#include <windows.h>

#define M2V_VFAPI_C
#include "m2v_vfapi.h"

//---------------------------------------------------------------------------
//  global functions
//---------------------------------------------------------------------------
int open_m2v_vfapi(M2V_VFAPI *m2v);
void close_m2v_vfapi(M2V_VFAPI *m2v);

//---------------------------------------------------------------------------
//  file local functions
//---------------------------------------------------------------------------
static void get_plugin_path(char *path, int len);
static void replace_vertical_bar_to_null(char *string);

//---------------------------------------------------------------------------
int open_m2v_vfapi(M2V_VFAPI *m2v)
{
	typedef HRESULT (_stdcall *get_dll_func)(LPVF_PluginFunc);
	typedef HRESULT (_stdcall *get_dll_func_edit_ext)(LPVF_PluginFuncEditExt);
	typedef HRESULT (_stdcall *get_dll_info)(LPVF_PluginInfo);

	char path[MAX_PATH];
	get_dll_func get_func;
	get_dll_func_edit_ext get_func_edit_ext;
	get_dll_info get_info;

	memset(path, 0, sizeof(path));
	memset(m2v, 0, sizeof(M2V_VFAPI));

	get_plugin_path(path, sizeof(path));

	m2v->dll = LoadLibrary(path);
	if(m2v->dll == NULL){
		goto OPEN_M2V_VFAPI_ERROR;
	}

	get_info = (get_dll_info) GetProcAddress(m2v->dll, "vfGetPluginInfo");
	if(get_info == NULL){
		goto OPEN_M2V_VFAPI_ERROR;
	}
	
	m2v->info.dwSize = sizeof(VF_PluginInfo);
	if(get_info(&(m2v->info)) != VF_OK){
		goto OPEN_M2V_VFAPI_ERROR;
	}
	replace_vertical_bar_to_null(m2v->info.cFileType);
	
	get_func = (get_dll_func) GetProcAddress(m2v->dll, "vfGetPluginFunc");
	if(get_func == NULL){
		goto OPEN_M2V_VFAPI_ERROR;
	}

	m2v->func.dwSize = sizeof(VF_PluginFunc);
	if(get_func(&(m2v->func)) != VF_OK){
		goto OPEN_M2V_VFAPI_ERROR;
	}

	get_func_edit_ext = (get_dll_func_edit_ext) GetProcAddress(m2v->dll, "vfGetPluginFuncEditExt");
	if(get_func_edit_ext == NULL){
		goto OPEN_M2V_VFAPI_ERROR;
	}

	m2v->func_edit_ext.dwSize = sizeof(VF_PluginFuncEditExt);
	if(get_func_edit_ext(&(m2v->func_edit_ext)) != VF_OK){
		goto OPEN_M2V_VFAPI_ERROR;
	}
	
	return 1;

OPEN_M2V_VFAPI_ERROR:
	close_m2v_vfapi(m2v);
	return 0;
}

//---------------------------------------------------------------------------
void close_m2v_vfapi(M2V_VFAPI *m2v)
{
	if(m2v->dll){
		FreeLibrary(m2v->dll);
	}

	memset(m2v, 0, sizeof(M2V_VFAPI));
}

//---------------------------------------------------------------------------

void get_plugin_path(char *path, int len)
{
	const char filename[] = "m2v.vfp";

	strncpy(path, filename, len);
}
//---------------------------------------------------------------------------

static void replace_vertical_bar_to_null(char *str)
{
	while(*str){
		if(*str == '|'){
			*str = '\0';
			str += 1;
		}else{
			str = CharNext(str);
		}
	}
}
//---------------------------------------------------------------------------

