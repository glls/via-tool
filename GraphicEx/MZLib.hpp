// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MZLib.pas' rev: 6.00

#ifndef MZLibHPP
#define MZLibHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Mzlib
{
//-- type declarations -------------------------------------------------------
typedef Word *PWord;

typedef int *PInteger;

typedef unsigned *PCardinal;

typedef Byte TByteArray[2147483647];

typedef Byte *PByteArray;

typedef Word TWordArray[1073741823];

typedef Word *PWordArray;

typedef int TIntegerArray[536870911];

typedef int *PIntegerArray;

typedef unsigned TCardinalArray[536870911];

typedef unsigned *PCardinalArray;

struct TInflateHuft;
typedef TInflateHuft *PInflateHuft;

#pragma pack(push, 4)
struct TInflateHuft
{
	Byte Exop;
	Byte Bits;
	unsigned Base;
} ;
#pragma pack(pop)

typedef TInflateHuft THuftField[268435455];

typedef TInflateHuft *PHuftField;

typedef PInflateHuft *PPInflateHuft;

#pragma option push -b-
enum TInflateCodesMode { icmStart, icmLen, icmLenNext, icmDistance, icmDistExt, icmCopy, icmLit, icmWash, icmZEnd, icmBadCode };
#pragma option pop

struct TInflateCodesState;
typedef TInflateCodesState *PInflateCodesState;

#pragma pack(push, 4)
struct MZLib__2
{
	TInflateHuft *Tree;
	unsigned need;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct MZLib__3
{
	unsigned get;
	unsigned Distance;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct MZLib__1
{
	
	union
	{
		struct 
		{
			MZLib__3 copy;
			
		};
		struct 
		{
			unsigned lit;
			
		};
		struct 
		{
			MZLib__2 Code;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TInflateCodesState
{
	TInflateCodesMode Mode;
	unsigned Len;
	MZLib__1 Sub;
	Byte LiteralTreeBits;
	Byte DistanceTreeBits;
	TInflateHuft *LiteralTree;
	TInflateHuft *DistanceTree;
} ;
#pragma pack(pop)

typedef unsigned __fastcall (*TCheckFunction)(unsigned Check, System::PByte Buffer, unsigned Len);

#pragma option push -b-
enum TInflateBlockMode { ibmZType, ibmLens, ibmStored, ibmTable, ibmBitTree, ibmDistTree, ibmCodes, ibmDry, ibmBlockDone, ibmBlockBad };
#pragma option pop

struct TInflateBlocksState;
typedef TInflateBlocksState *PInflateBlocksState;

#pragma pack(push, 4)
struct MZLib__5
{
	unsigned Table;
	unsigned Index;
	unsigned *blens;
	unsigned BB;
	TInflateHuft *TB;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct MZLib__6
{
	TInflateHuft *TL;
	TInflateHuft *TD;
	TInflateCodesState *codes;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct MZLib__4
{
	
	union
	{
		struct 
		{
			MZLib__6 decode;
			
		};
		struct 
		{
			MZLib__5 Trees;
			
		};
		struct 
		{
			unsigned left;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TInflateBlocksState
{
	TInflateBlockMode Mode;
	MZLib__4 Sub;
	bool Last;
	unsigned bitk;
	unsigned bitb;
	TInflateHuft *hufts;
	Byte *window;
	Byte *zend;
	Byte *read;
	Byte *write;
	TCheckFunction CheckFunction;
	unsigned Check;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TInflateMode { imMethod, imFlag, imDict4, imDict3, imDict2, imDict1, imDict0, imBlocks, imCheck4, imCheck3, imCheck2, imCheck1, imDone, imBad };
#pragma option pop

struct TInternalState;
typedef TInternalState *PInternalState;

#pragma pack(push, 4)
struct MZLib__8
{
	unsigned was;
	unsigned need;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct MZLib__7
{
	
	union
	{
		struct 
		{
			unsigned marker;
			
		};
		struct 
		{
			MZLib__8 Check;
			
		};
		struct 
		{
			unsigned imMethod;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TInternalState
{
	TInflateMode Mode;
	MZLib__7 Sub;
	bool nowrap;
	unsigned wbits;
	TInflateBlocksState *blocks;
} ;
#pragma pack(pop)

struct TZState;
typedef TZState *PZState;

#pragma pack(push, 4)
struct TZState
{
	Byte *NextInput;
	unsigned AvailableInput;
	unsigned TotalInput;
	Byte *NextOutput;
	unsigned AvailableOutput;
	unsigned TotalOutput;
	AnsiString Msg;
	TInternalState *State;
	int DataType;
	unsigned Adler;
} ;
#pragma pack(pop)

typedef AnsiString MZLib__9[10];

struct TTreeEntry;
typedef TTreeEntry *PTreeEntry;

#pragma pack(push, 2)
struct MZLib__01
{
	
	union
	{
		struct 
		{
			Word Code;
			
		};
		struct 
		{
			Word Frequency;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 2)
struct MZLib__11
{
	
	union
	{
		struct 
		{
			Word Len;
			
		};
		struct 
		{
			Word dad;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 2)
struct TTreeEntry
{
	MZLib__01 fc;
	MZLib__11 dl;
} ;
#pragma pack(pop)

typedef TTreeEntry TLiteralTree[573];

typedef TTreeEntry TDistanceTree[61];

typedef TTreeEntry THuffmanTree[39];

typedef TTreeEntry TTree[536870911];

typedef TTreeEntry *PTree;

struct TStaticTreeDescriptor;
typedef TStaticTreeDescriptor *PStaticTreeDescriptor;

#pragma pack(push, 4)
struct TStaticTreeDescriptor
{
	TTreeEntry *StaticTree;
	int *ExtraBits;
	int ExtraBase;
	int Elements;
	int MaxLength;
} ;
#pragma pack(pop)

struct TTreeDescriptor;
typedef TTreeDescriptor *PTreeDescriptor;

#pragma pack(push, 4)
struct TTreeDescriptor
{
	TTreeEntry *DynamicTree;
	int MaxCode;
	TStaticTreeDescriptor *StaticDescriptor;
} ;
#pragma pack(pop)

struct TDeflateState;
typedef TDeflateState *PDeflateState;

#pragma pack(push, 4)
struct TDeflateState
{
	TZState *ZState;
	int Status;
	Byte *PendingBuffer;
	int PendingBufferSize;
	Byte *PendingOutput;
	int Pending;
	int NoHeader;
	Byte DataType;
	Byte imMethod;
	int LastFlush;
	unsigned WindowSize;
	unsigned WindowBits;
	unsigned WindowMask;
	Byte *Window;
	int CurrentWindowSize;
	Word *Previous;
	Word *Head;
	unsigned InsertHash;
	unsigned HashSize;
	unsigned HashBits;
	unsigned HashMask;
	unsigned HashShift;
	int BlockStart;
	unsigned MatchLength;
	unsigned PreviousMatch;
	bool MatchAvailable;
	unsigned StringStart;
	unsigned MatchStart;
	unsigned Lookahead;
	unsigned PreviousLength;
	unsigned MaxChainLength;
	int Level;
	int Strategy;
	unsigned GoodMatch;
	unsigned NiceMatch;
	TTreeEntry LiteralTree[573];
	TTreeEntry DistanceTree[61];
	TTreeEntry BitLengthTree[39];
	TTreeDescriptor LiteralDescriptor;
	TTreeDescriptor DistanceDescriptor;
	TTreeDescriptor BitLengthDescriptor;
	Word BitLengthCounts[16];
	int Heap[573];
	int HeapLength;
	int HeapMaximum;
	Byte Depth[573];
	Byte *LiteralBuffer;
	unsigned LiteralBufferSize;
	unsigned LastLiteral;
	Word *DistanceBuffer;
	int OptimalLength;
	int StaticLength;
	int CompressedLength;
	unsigned Matches;
	int LastEOBLength;
	Word BitsBuffer;
	int ValidBits;
	union
	{
		struct 
		{
			unsigned MaxInsertLength;
			
		};
		struct 
		{
			unsigned MaxLazyMatch;
			
		};
		
	};
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::ResourceString _SNeedDict;
#define Mzlib_SNeedDict System::LoadResourceString(&Mzlib::_SNeedDict)
extern PACKAGE System::ResourceString _SStreamEnd;
#define Mzlib_SStreamEnd System::LoadResourceString(&Mzlib::_SStreamEnd)
extern PACKAGE System::ResourceString _SFileError;
#define Mzlib_SFileError System::LoadResourceString(&Mzlib::_SFileError)
extern PACKAGE System::ResourceString _SStreamError;
#define Mzlib_SStreamError System::LoadResourceString(&Mzlib::_SStreamError)
extern PACKAGE System::ResourceString _SDataError;
#define Mzlib_SDataError System::LoadResourceString(&Mzlib::_SDataError)
extern PACKAGE System::ResourceString _SInsufficientMemory;
#define Mzlib_SInsufficientMemory System::LoadResourceString(&Mzlib::_SInsufficientMemory)
extern PACKAGE System::ResourceString _SBufferError;
#define Mzlib_SBufferError System::LoadResourceString(&Mzlib::_SBufferError)
extern PACKAGE System::ResourceString _SIncompatibleVersion;
#define Mzlib_SIncompatibleVersion System::LoadResourceString(&Mzlib::_SIncompatibleVersion)
extern PACKAGE System::ResourceString _SInvalidDistanceCode;
#define Mzlib_SInvalidDistanceCode System::LoadResourceString(&Mzlib::_SInvalidDistanceCode)
extern PACKAGE System::ResourceString _SInvalidLengthCode;
#define Mzlib_SInvalidLengthCode System::LoadResourceString(&Mzlib::_SInvalidLengthCode)
extern PACKAGE System::ResourceString _SOversubscribedDBLTree;
#define Mzlib_SOversubscribedDBLTree System::LoadResourceString(&Mzlib::_SOversubscribedDBLTree)
extern PACKAGE System::ResourceString _SIncompleteDBLTree;
#define Mzlib_SIncompleteDBLTree System::LoadResourceString(&Mzlib::_SIncompleteDBLTree)
extern PACKAGE System::ResourceString _SOversubscribedLLTree;
#define Mzlib_SOversubscribedLLTree System::LoadResourceString(&Mzlib::_SOversubscribedLLTree)
extern PACKAGE System::ResourceString _SIncompleteLLTree;
#define Mzlib_SIncompleteLLTree System::LoadResourceString(&Mzlib::_SIncompleteLLTree)
extern PACKAGE System::ResourceString _SEmptyDistanceTree;
#define Mzlib_SEmptyDistanceTree System::LoadResourceString(&Mzlib::_SEmptyDistanceTree)
extern PACKAGE System::ResourceString _SInvalidBlockType;
#define Mzlib_SInvalidBlockType System::LoadResourceString(&Mzlib::_SInvalidBlockType)
extern PACKAGE System::ResourceString _SInvalidStoredBlockLengths;
#define Mzlib_SInvalidStoredBlockLengths System::LoadResourceString(&Mzlib::_SInvalidStoredBlockLengths)
extern PACKAGE System::ResourceString _STooManyLDSymbols;
#define Mzlib_STooManyLDSymbols System::LoadResourceString(&Mzlib::_STooManyLDSymbols)
extern PACKAGE System::ResourceString _SInvalidBitLengthRepeat;
#define Mzlib_SInvalidBitLengthRepeat System::LoadResourceString(&Mzlib::_SInvalidBitLengthRepeat)
extern PACKAGE System::ResourceString _SIncorrectDataCheck;
#define Mzlib_SIncorrectDataCheck System::LoadResourceString(&Mzlib::_SIncorrectDataCheck)
extern PACKAGE System::ResourceString _SUnknownCompression;
#define Mzlib_SUnknownCompression System::LoadResourceString(&Mzlib::_SUnknownCompression)
extern PACKAGE System::ResourceString _SInvalidWindowSize;
#define Mzlib_SInvalidWindowSize System::LoadResourceString(&Mzlib::_SInvalidWindowSize)
extern PACKAGE System::ResourceString _SIncorrectHeaderCheck;
#define Mzlib_SIncorrectHeaderCheck System::LoadResourceString(&Mzlib::_SIncorrectHeaderCheck)
extern PACKAGE System::ResourceString _SNeedDictionary;
#define Mzlib_SNeedDictionary System::LoadResourceString(&Mzlib::_SNeedDictionary)
static const Shortint MAX_MEM_LEVEL = 0x9;
static const Shortint DEF_MEM_LEVEL = 0x8;
static const Shortint MAX_WBITS = 0xf;
static const Shortint DEF_WBITS = 0xf;
static const Shortint Z_NO_FLUSH = 0x0;
static const Shortint Z_PARTIAL_FLUSH = 0x1;
static const Shortint Z_SYNC_FLUSH = 0x2;
static const Shortint Z_FULL_FLUSH = 0x3;
static const Shortint Z_FINISH = 0x4;
static const Shortint Z_OK = 0x0;
static const Shortint Z_STREAM_END = 0x1;
static const Shortint Z_NEED_DICT = 0x2;
static const Shortint Z_ERRNO = 0xffffffff;
static const Shortint Z_STREAM_ERROR = 0xfffffffe;
static const Shortint Z_DATA_ERROR = 0xfffffffd;
static const Shortint Z_MEM_ERROR = 0xfffffffc;
static const Shortint Z_BUF_ERROR = 0xfffffffb;
static const Shortint Z_VERSION_ERROR = 0xfffffffa;
static const Shortint Z_DEFAULT_COMPRESSION = 0xffffffff;
static const Shortint Z_NO_COMPRESSION = 0x0;
static const Shortint Z_BEST_SPEED = 0x1;
static const Shortint Z_BEST_COMPRESSION = 0x9;
static const Shortint Z_DEFAULT_STRATEGY = 0x0;
static const Shortint Z_FILTERED = 0x1;
static const Shortint Z_HUFFMAN_ONLY = 0x2;
static const Shortint Z_BINARY = 0x0;
static const Shortint Z_ASCII = 0x1;
static const Shortint Z_UNKNOWN = 0x2;
static const Shortint Z_DEFLATED = 0x8;
static const Shortint STORED_BLOCK = 0x0;
static const Shortint STATIC_TREES = 0x1;
static const Shortint DYN_TREES = 0x2;
static const Shortint MIN_MATCH = 0x3;
static const Word MAX_MATCH = 0x102;
static const Shortint PRESET_DICT = 0x20;
extern PACKAGE System::SmallString<10>  ZLIB_VERSION;
static const Shortint ERROR_BASE = 0x2;
extern PACKAGE AnsiString ErrorMessages[10];
static const Shortint LENGTH_CODES = 0x1d;
static const Word LITERALS = 0x100;
static const Word L_CODES = 0x11e;
static const Shortint D_CODES = 0x1e;
static const Shortint BL_CODES = 0x13;
static const Word HEAP_SIZE = 0x23d;
static const Shortint MAX_BITS = 0xf;
static const Shortint INIT_STATE = 0x2a;
static const Shortint BUSY_STATE = 0x71;
static const Word FINISH_STATE = 0x29a;
extern PACKAGE AnsiString __fastcall zError(int Error);
extern PACKAGE unsigned __fastcall CRC32(unsigned CRC, System::PByte Buffer, unsigned Len);
extern PACKAGE int __fastcall DeflateInit2(TZState &ZState, int Level, Byte Method, int AWindowBits, int MemLevel, int Strategy);
extern PACKAGE int __fastcall DeflateInit_(PZState ZState, int Level, const AnsiString Version, int StreamSize);
extern PACKAGE int __fastcall DeflateInit(TZState &ZState, int Level);
extern PACKAGE int __fastcall DeflateSetDictionary(TZState &ZState, System::PByte Dictionary, unsigned DictLength);
extern PACKAGE int __fastcall DeflateReset(TZState &ZState);
extern PACKAGE int __fastcall DeflateParams(TZState &ZState, int Level, int Strategy);
extern PACKAGE int __fastcall Deflate(TZState &ZState, int Flush);
extern PACKAGE int __fastcall DeflateEnd(TZState &ZState);
extern PACKAGE int __fastcall DeflateCopy(PZState Dest, PZState Source);
extern PACKAGE int __fastcall InflateReset(TZState &Z);
extern PACKAGE int __fastcall InflateEnd(TZState &Z);
extern PACKAGE int __fastcall InflateInit2_(TZState &Z, int W, const AnsiString Version, int StreamSize);
extern PACKAGE int __fastcall InflateInit2(TZState &Z, int AWindowBits);
extern PACKAGE int __fastcall InflateInit(TZState &Z);
extern PACKAGE int __fastcall InflateInit_(TZState &Z, const AnsiString Version, int StreamSize);
extern PACKAGE int __fastcall Inflate(TZState &Z, int F);
extern PACKAGE int __fastcall InflateSetDictionary(TZState &Z, System::PByte Dictionary, unsigned DictLength);
extern PACKAGE int __fastcall InflateSync(TZState &Z);
extern PACKAGE int __fastcall IsInflateSyncPoint(TZState &Z);

}	/* namespace Mzlib */
using namespace Mzlib;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MZLib
