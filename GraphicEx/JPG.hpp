// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'JPG.pas' rev: 6.00

#ifndef JPGHPP
#define JPGHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Jpg
{
//-- type declarations -------------------------------------------------------
#pragma option push -b
enum TJPGColorDepth { jpgAuto, jpgGray, jpg8Bit, jpg24Bit };
#pragma option pop

#pragma option push -b
enum TJPEGPixelFormat { jf24Bit, jf8Bit };
#pragma option pop

typedef Byte JSAMPLE;

typedef int GETJSAMPLE;

typedef int JCOEF;

typedef int *JCOEF_PTR;

typedef Byte UINT8;

typedef Word UINT16;

typedef unsigned UINT32;

typedef short INT16;

typedef int INT32;

typedef int *INT32PTR;

typedef unsigned JDIMENSION;

typedef Byte JOCTET;

typedef int jTOctet;

typedef Byte JOCTET_FIELD[2147483647];

typedef Byte *JOCTET_FIELD_PTR;

typedef Byte *JOCTETPTR;

typedef Byte *JSAMPLE_PTR;

typedef Byte JSAMPLE_ARRAY[2147483647];

typedef Byte *JSAMPROW;

typedef JSAMPROW *JSAMPROW_PTR;

typedef int jTSample;

typedef int jTRow;

typedef Byte *JSAMPROW_ARRAY[536870911];

typedef JSAMPROW *JSAMPARRAY;

typedef int jTArray;

typedef JSAMPROW *JSAMP_ARRAY[536870911];

typedef JSAMPARRAY *JSAMPIMAGE;

#pragma option push -b
enum J_COLOR_SPACE { JCS_UNKNOWN, JCS_GRAYSCALE, JCS_RGB, JCS_YCbCr, JCS_CMYK, JCS_YCCK };
#pragma option pop

#pragma option push -b
enum J_DCT_METHOD { JDCT_ISLOW, JDCT_IFAST, JDCT_FLOAT };
#pragma option pop

#pragma option push -b
enum J_DITHER_MODE { JDITHER_NONE, JDITHER_ORDERED, JDITHER_FS };
#pragma option pop

struct JQUANT_TBL;
typedef JQUANT_TBL *JQUANT_TBL_ptr;

#pragma pack(push, 4)
struct JQUANT_TBL
{
	Word quantval[64];
	BOOL sent_table;
} ;
#pragma pack(pop)

struct jpeg_component_info;
typedef jpeg_component_info *jpeg_component_info_ptr;

#pragma pack(push, 4)
struct jpeg_component_info
{
	int component_id;
	int component_index;
	int h_samp_factor;
	int v_samp_factor;
	int quant_tbl_no;
	int dc_tbl_no;
	int ac_tbl_no;
	unsigned width_in_blocks;
	unsigned height_in_blocks;
	int DCT_scaled_size;
	unsigned downsampled_width;
	unsigned downsampled_height;
	BOOL component_needed;
	int MCU_width;
	int MCU_height;
	int MCU_blocks;
	int MCU_sample_width;
	int last_col_width;
	int last_row_height;
	JQUANT_TBL *quant_table;
	void *dct_table;
} ;
#pragma pack(pop)

struct jpeg_error_mgr;
typedef jpeg_error_mgr *jpeg_error_mgr_ptr;

struct jpeg_progress_mgr;
typedef jpeg_progress_mgr *jpeg_progress_mgr_ptr;

struct jpeg_common_struct;
typedef jpeg_common_struct *j_common_ptr;

struct jpeg_decompress_struct;
typedef jpeg_decompress_struct *j_decompress_ptr;

typedef BOOL __fastcall (*jpeg_marker_parser_method)(j_decompress_ptr cinfo);

struct jpeg_marker_reader;
typedef jpeg_marker_reader *jpeg_marker_reader_ptr;

#pragma pack(push, 4)
struct jpeg_marker_reader
{
	void __fastcall (*reset_marker_reader)(j_decompress_ptr cinfo);
	int __fastcall (*read_markers)(j_decompress_ptr cinfo);
	jpeg_marker_parser_method read_restart_marker;
	jpeg_marker_parser_method process_COM;
	jpeg_marker_parser_method process_APPn[16];
	BOOL saw_SOI;
	BOOL saw_SOF;
	int next_restart_num;
	unsigned discarded_bytes;
} ;
#pragma pack(pop)

typedef int int8array[8];

#pragma pack(push, 4)
struct JPG__1
{
	
	union
	{
		struct 
		{
			System::SmallStringBase<80>  s;
			
		};
		struct 
		{
			int i[8];
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct jpeg_error_mgr
{
	void __fastcall (*error_exit)(j_common_ptr cinfo);
	void __fastcall (*emit_message)(j_common_ptr cinfo, int msg_level);
	void __fastcall (*output_message)(j_common_ptr cinfo);
	void __fastcall (*format_message)(j_common_ptr cinfo, char * buffer);
	void __fastcall (*reset_error_mgr)(j_common_ptr cinfo);
	int msg_code;
	JPG__1 msg_parm;
	int trace_level;
	int num_warnings;
} ;
#pragma pack(pop)

struct jpeg_source_mgr;
typedef jpeg_source_mgr *jpeg_source_mgr_ptr;

#pragma pack(push, 4)
struct jpeg_source_mgr
{
	Byte *next_input_byte;
	int bytes_in_buffer;
	void __fastcall (*init_source)(j_decompress_ptr cinfo);
	BOOL __fastcall (*fill_input_buffer)(j_decompress_ptr cinfo);
	void __fastcall (*skip_input_data)(j_decompress_ptr cinfo, int num_bytes);
	BOOL __fastcall (*resync_to_restart)(j_decompress_ptr cinfo, int desired);
	void __fastcall (*term_source)(j_decompress_ptr cinfo);
} ;
#pragma pack(pop)

struct jpeg_memory_mgr;
typedef jpeg_memory_mgr *jpeg_memory_mgr_ptr;

#pragma pack(push, 4)
struct jpeg_memory_mgr
{
	void * __fastcall (*alloc_small)(j_common_ptr cinfo, int pool_id, int sizeofobject);
	void * __fastcall (*alloc_large)(j_common_ptr cinfo, int pool_id, int sizeofobject);
	JSAMPARRAY __fastcall (*alloc_sarray)(j_common_ptr cinfo, int pool_id, unsigned samplesperrow, unsigned numrows);
	void *alloc_barray;
	void *request_virt_sarray;
	void *request_virt_barray;
	void *realize_virt_arrays;
	void *access_virt_sarray;
	void *access_virt_barray;
	void *free_pool;
	void *self_destruct;
	int max_memory_to_use;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct jpeg_common_struct
{
	jpeg_error_mgr *err;
	jpeg_memory_mgr *mem;
	jpeg_progress_mgr *progress;
	BOOL is_decompressor;
	int global_state;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct jpeg_progress_mgr
{
	void __fastcall (*progress_monitor)(const jpeg_common_struct &cinfo);
	int pass_counter;
	int pass_limit;
	int completed_passes;
	int total_passes;
	Classes::TPersistent* instance;
	int last_pass;
	int last_pct;
	int last_time;
	int last_scanline;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct jpeg_decompress_struct
{
	jpeg_common_struct common;
	jpeg_source_mgr *src;
	unsigned image_width;
	unsigned image_height;
	int num_components;
	J_COLOR_SPACE jpeg_color_space;
	J_COLOR_SPACE out_color_space;
	unsigned scale_num;
	unsigned scale_denom;
	double output_gamma;
	BOOL buffered_image;
	BOOL raw_data_out;
	J_DCT_METHOD dct_method;
	BOOL do_fancy_upsampling;
	BOOL do_block_smoothing;
	BOOL quantize_colors;
	J_DITHER_MODE dither_mode;
	BOOL two_pass_quantize;
	int desired_number_of_colors;
	BOOL enable_1pass_quant;
	BOOL enable_external_quant;
	BOOL enable_2pass_quant;
	unsigned output_width;
	unsigned output_height;
	int out_color_components;
	int output_components;
	int rec_outbuf_height;
	int actual_number_of_colors;
	JSAMPROW *colormap;
	unsigned output_scanline;
	int input_scan_number;
	unsigned input_iMCU_row;
	int output_scan_number;
	int output_iMCU_row;
	void *coef_bits;
	void *quant_tbl_ptrs[4];
	void *dc_huff_tbl_ptrs[4];
	void *ac_huff_tbl_ptrs[4];
	int data_precision;
	jpeg_component_info *comp_info;
	BOOL progressive_mode;
	BOOL arith_code;
	Byte arith_dc_L[16];
	Byte arith_dc_U[16];
	Byte arith_ac_K[16];
	unsigned restart_interval;
	BOOL saw_JFIF_marker;
	Byte density_unit;
	Word X_density;
	Word Y_density;
	BOOL saw_Adobe_marker;
	Byte Adobe_transform;
	BOOL CCIR601_sampling;
	int max_h_samp_factor;
	int max_v_samp_factor;
	int min_DCT_scaled_size;
	unsigned total_iMCU_rows;
	void *sample_range_limit;
	int comps_in_scan;
	void *cur_comp_info[4];
	unsigned MCUs_per_row;
	unsigned MCU_rows_in_scan;
	unsigned blocks_in_MCU;
	int MCU_membership[10];
	int Ss;
	int Se;
	int Ah;
	int Al;
	int unread_marker;
	void *master;
	void *main;
	void *coef;
	void *post;
	void *inputctl;
	void *marker;
	void *entropy;
	void *idct;
	void *upsample;
	void *cconvert;
	void *cquantize;
} ;
#pragma pack(pop)

struct jpeg_compress_struct;
typedef jpeg_compress_struct *j_compress_ptr;

struct jpeg_destination_mgr;
typedef jpeg_destination_mgr *jpeg_destination_mgr_ptr;

#pragma pack(push, 4)
struct jpeg_destination_mgr
{
	Byte *next_output_byte;
	int free_in_buffer;
	void __fastcall (*init_destination)(j_compress_ptr cinfo);
	BOOL __fastcall (*empty_output_buffer)(j_compress_ptr cinfo);
	void __fastcall (*term_destination)(j_compress_ptr cinfo);
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct jpeg_compress_struct
{
	jpeg_common_struct common;
	jpeg_destination_mgr *dest;
	unsigned image_width;
	unsigned image_height;
	int input_components;
	J_COLOR_SPACE in_color_space;
	double input_gamma;
	int data_precision;
	int num_components;
	J_COLOR_SPACE jpeg_color_space;
	jpeg_component_info *comp_info;
	void *quant_tbl_ptrs[4];
	void *dc_huff_tbl_ptrs[4];
	void *ac_huff_tbl_ptrs[4];
	Byte arith_dc_L[16];
	Byte arith_dc_U[16];
	Byte arith_ac_K[16];
	int num_scans;
	void *scan_info;
	BOOL raw_data_in;
	BOOL arith_code;
	BOOL optimize_coding;
	BOOL CCIR601_sampling;
	int smoothing_factor;
	J_DCT_METHOD dct_method;
	unsigned restart_interval;
	int restart_in_rows;
	BOOL write_JFIF_header;
	Byte density_unit;
	Word X_density;
	Word Y_density;
	BOOL write_Adobe_marker;
	unsigned next_scanline;
	BOOL progressive_mode;
	int max_h_samp_factor;
	int max_v_samp_factor;
	unsigned total_iMCU_rows;
	int comps_in_scan;
	void *cur_comp_info[4];
	unsigned MCUs_per_row;
	unsigned MCU_rows_in_scan;
	int blocks_in_MCU;
	int MCU_membership[10];
	int Ss;
	int Se;
	int Ah;
	int Al;
	void *master;
	void *main;
	void *prep;
	void *coef;
	void *marker;
	void *cconvert;
	void *downsample;
	void *fdct;
	void *entropy;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TJPEGContext
{
	jpeg_error_mgr err;
	jpeg_progress_mgr progress;
	J_DCT_METHOD FinalDCT;
	bool FinalTwoPassQuant;
	J_DITHER_MODE FinalDitherMode;
	union
	{
		struct 
		{
			jpeg_compress_struct c;
			
		};
		struct 
		{
			jpeg_decompress_struct d;
			
		};
		struct 
		{
			jpeg_common_struct common;
			
		};
		
	};
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Shortint JPEG_SUSPENDED = 0x0;
static const Shortint JPEG_HEADER_OK = 0x1;
static const Shortint JPEG_HEADER_TABLES_ONLY = 0x2;
static const Shortint JPEG_REACHED_SOS = 0x1;
static const Shortint JPEG_REACHED_EOI = 0x2;
static const Shortint JPEG_ROW_COMPLETED = 0x3;
static const Shortint JPEG_SCAN_COMPLETED = 0x4;
static const Shortint CSTATE_START = 0x64;
static const Shortint CSTATE_SCANNING = 0x65;
static const Shortint CSTATE_RAW_OK = 0x66;
static const Shortint CSTATE_WRCOEFS = 0x67;
static const Shortint JPEG_LIB_VERSION = 0x3d;
static const Byte JPEG_RST0 = 0xd0;
static const Byte JPEG_EOI = 0xd9;
static const Byte JPEG_APP0 = 0xe0;
static const Byte JPEG_COM = 0xfe;
static const Shortint DCTSIZE = 0x8;
static const Shortint DCTSIZE2 = 0x40;
static const Shortint NUM_QUANT_TBLS = 0x4;
static const Shortint NUM_HUFF_TBLS = 0x4;
static const Shortint NUM_ARITH_TBLS = 0x10;
static const Shortint MAX_COMPS_IN_SCAN = 0x4;
static const Shortint MAX_SAMP_FACTOR = 0x4;
static const Shortint C_MAX_BLOCKS_IN_MCU = 0xa;
static const Shortint D_MAX_BLOCKS_IN_MCU = 0xa;
static const Shortint MAX_COMPONENTS = 0xa;
static const Byte MAXJSAMPLE = 0xff;
static const Byte CENTERJSAMPLE = 0x80;
static const Byte DSTATE_START = 0xc8;
static const Byte DSTATE_INHEADER = 0xc9;
static const Byte DSTATE_READY = 0xca;
static const Byte DSTATE_PRELOAD = 0xcb;
static const Byte DSTATE_PRESCAN = 0xcc;
static const Byte DSTATE_SCANNING = 0xcd;
static const Byte DSTATE_RAW_OK = 0xce;
static const Byte DSTATE_BUFIMAGE = 0xcf;
static const Byte DSTATE_BUFPOST = 0xd0;
static const Byte DSTATE_RDCOEFS = 0xd1;
static const Byte DSTATE_STOPPING = 0xd2;
static const Byte JMSG_LENGTH_MAX = 0xc8;
static const Shortint JMSG_STR_PARM_MAX = 0x50;
static const Shortint JPOOL_PERMANENT = 0x0;
static const Shortint JPOOL_IMAGE = 0x1;
extern PACKAGE jpeg_error_mgr jpeg_std_error;
extern PACKAGE void __fastcall GetJPEGInfo(Classes::TStream* Stream, unsigned &Width, unsigned &Height)/* overload */;
extern PACKAGE void __fastcall GetJPEGInfo(AnsiString FileName, unsigned &Width, unsigned &Height)/* overload */;
extern PACKAGE void __fastcall jpeg_CreateDecompress(j_decompress_ptr cinfo, int version, int structsize);
extern PACKAGE void __fastcall jpeg_destroy_decompress(j_decompress_ptr cinfo);
extern PACKAGE int __fastcall jpeg_read_header(j_decompress_ptr cinfo, BOOL RequireImage);
extern PACKAGE int __fastcall jpeg_consume_input(j_decompress_ptr cinfo);
extern PACKAGE BOOL __fastcall jpeg_has_multiple_scans(j_decompress_ptr cinfo);
extern PACKAGE BOOL __fastcall jpeg_finish_decompress(j_decompress_ptr cinfo);
extern PACKAGE void __fastcall jpeg_stdio_src(j_decompress_ptr cinfo, Classes::TStream* input_file);
extern PACKAGE BOOL __fastcall jpeg_start_decompress(j_decompress_ptr cinfo);
extern PACKAGE unsigned __fastcall jpeg_read_scanlines(j_decompress_ptr cinfo, JSAMPARRAY scanlines, unsigned max_lines);
extern PACKAGE unsigned __fastcall jpeg_read_raw_data(j_decompress_ptr cinfo, JSAMPIMAGE data, unsigned max_lines);
extern PACKAGE BOOL __fastcall jpeg_start_output(j_decompress_ptr cinfo, int scan_number);
extern PACKAGE BOOL __fastcall jpeg_finish_output(j_decompress_ptr cinfo);
extern PACKAGE void __fastcall jpeg_calc_output_dimensions(j_decompress_ptr cinfo);
extern PACKAGE BOOL __fastcall jpeg_resync_to_restart(j_decompress_ptr cinfo, int desired);
extern PACKAGE void __fastcall jpeg_abort(j_decompress_ptr cinfo);
extern PACKAGE void __fastcall jpeg_destroy(j_decompress_ptr cinfo);
extern PACKAGE void __fastcall jpeg_stdio_dest(j_compress_ptr cinfo, Classes::TStream* output_file);
extern PACKAGE void __fastcall jpeg_set_quality(j_compress_ptr cinfo, int Quality, BOOL Baseline);
extern PACKAGE void __fastcall jpeg_set_defaults(j_compress_ptr cinfo);
extern PACKAGE void __fastcall jpeg_set_colorspace(j_compress_ptr cinfo, J_COLOR_SPACE colorspace);
extern PACKAGE void __fastcall jpeg_simple_progression(j_compress_ptr cinfo);
extern PACKAGE void __fastcall jpeg_start_compress(j_compress_ptr cinfo, BOOL WriteAllTables);
extern PACKAGE unsigned __fastcall jpeg_write_scanlines(j_compress_ptr cinfo, JSAMPARRAY scanlines, unsigned max_lines);
extern PACKAGE void __fastcall jpeg_CreateCompress(j_compress_ptr cinfo, int version, int structsize);
extern PACKAGE void __fastcall jpeg_finish_compress(j_compress_ptr cinfo);

}	/* namespace Jpg */
using namespace Jpg;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// JPG
