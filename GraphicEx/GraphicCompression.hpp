// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GraphicCompression.pas' rev: 6.00

#ifndef GraphicCompressionHPP
#define GraphicCompressionHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <MZLib.hpp>	// Pascal unit
#include <JPG.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Graphiccompression
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDecoder;
class PASCALIMPLEMENTATION TDecoder : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize) = 0 ;
	virtual void __fastcall DecodeEnd(void);
	virtual void __fastcall DecodeInit(void);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored) = 0 ;
	virtual void __fastcall EncodeInit(void);
	virtual void __fastcall EncodeEnd(void);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TDecoder(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTargaRLEDecoder;
class PASCALIMPLEMENTATION TTargaRLEDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	unsigned FColorDepth;
	
public:
	__fastcall TTargaRLEDecoder(unsigned ColorDepth);
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TTargaRLEDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPackbitsRLEDecoder;
class PASCALIMPLEMENTATION TPackbitsRLEDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPackbitsRLEDecoder(void) : TDecoder() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TPackbitsRLEDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPCXRLEDecoder;
class PASCALIMPLEMENTATION TPCXRLEDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPCXRLEDecoder(void) : TDecoder() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TPCXRLEDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSGIRLEDecoder;
class PASCALIMPLEMENTATION TSGIRLEDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	Byte FSampleSize;
	
public:
	__fastcall TSGIRLEDecoder(Byte SampleSize);
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TSGIRLEDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCUTRLEDecoder;
class PASCALIMPLEMENTATION TCUTRLEDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TCUTRLEDecoder(void) : TDecoder() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCUTRLEDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPSPRLEDecoder;
class PASCALIMPLEMENTATION TPSPRLEDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPSPRLEDecoder(void) : TDecoder() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TPSPRLEDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TRLADecoder;
class PASCALIMPLEMENTATION TRLADecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TRLADecoder(void) : TDecoder() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TRLADecoder(void) { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TStateEntry
{
	unsigned NewState[2];
	int RunLength;
} ;
#pragma pack(pop)

typedef DynamicArray<TStateEntry >  TStateArray;

class DELPHICLASS TCCITTDecoder;
class PASCALIMPLEMENTATION TCCITTDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	int FOptions;
	bool FIsWhite;
	bool FSwapBits;
	DynamicArray<TStateEntry >  FWhiteStates;
	DynamicArray<TStateEntry >  FBlackStates;
	unsigned FWidth;
	Byte FBitsLeft;
	Byte FMask;
	Byte FBits;
	unsigned FPackedSize;
	unsigned FRestWidth;
	Byte *FSource;
	Byte *FTarget;
	Byte FFreeTargetBits;
	bool FWordAligned;
	void __fastcall MakeStates(void);
	
protected:
	bool __fastcall FillRun(unsigned RunLength);
	int __fastcall FindBlackCode(void);
	int __fastcall FindWhiteCode(void);
	bool __fastcall NextBit(void);
	
public:
	__fastcall TCCITTDecoder(int Options, bool SwapBits, bool WordAligned, unsigned Width);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCCITTDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCCITTFax3Decoder;
class PASCALIMPLEMENTATION TCCITTFax3Decoder : public TCCITTDecoder 
{
	typedef TCCITTDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TCCITTDecoder.Create */ inline __fastcall TCCITTFax3Decoder(int Options, bool SwapBits, bool WordAligned, unsigned Width) : TCCITTDecoder(Options, SwapBits, WordAligned, Width) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCCITTFax3Decoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCCITTMHDecoder;
class PASCALIMPLEMENTATION TCCITTMHDecoder : public TCCITTDecoder 
{
	typedef TCCITTDecoder inherited;
	
public:
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TCCITTDecoder.Create */ inline __fastcall TCCITTMHDecoder(int Options, bool SwapBits, bool WordAligned, unsigned Width) : TCCITTDecoder(Options, SwapBits, WordAligned, Width) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCCITTMHDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TLZ77Decoder;
class PASCALIMPLEMENTATION TLZ77Decoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	Mzlib::TZState FStream;
	int FZLibResult;
	int FFlushMode;
	bool FAutoReset;
	int __fastcall GetAvailableInput(void);
	int __fastcall GetAvailableOutput(void);
	
public:
	__fastcall TLZ77Decoder(int FlushMode, bool AutoReset);
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall DecodeEnd(void);
	virtual void __fastcall DecodeInit(void);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
	__property int AvailableInput = {read=GetAvailableInput, nodefault};
	__property int AvailableOutput = {read=GetAvailableOutput, nodefault};
	__property int ZLibResult = {read=FZLibResult, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TLZ77Decoder(void) { }
	#pragma option pop
	
};


#pragma pack(push, 1)
struct TJPEGGeneral
{
	
	union
	{
		struct 
		{
			Jpg::jpeg_compress_struct c;
			
		};
		struct 
		{
			Jpg::jpeg_decompress_struct d;
			
		};
		struct 
		{
			Jpg::jpeg_common_struct common;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TJPEGState;
typedef TJPEGState *PJPEGState;

#pragma pack(push, 4)
struct TJPEGState
{
	TJPEGGeneral General;
	Jpg::jpeg_error_mgr Error;
	Jpg::jpeg_destination_mgr DestinationManager;
	Jpg::jpeg_source_mgr SourceManager;
	Word HSampling;
	Word VSampling;
	unsigned BytesPerLine;
	void *RawBuffer;
	unsigned RawBufferSize;
	Jpg::JSAMPROW *DownSampleBuffer[10];
	int ScanCount;
	int SamplesPerClump;
	void *JPEGTables;
	unsigned JTLength;
	int JPEGQuality;
	int JPEGTablesMode;
} ;
#pragma pack(pop)

class DELPHICLASS TTIFFJPEGDecoder;
class PASCALIMPLEMENTATION TTIFFJPEGDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	TJPEGState FState;
	void *FImageProperties;
	
public:
	__fastcall TTIFFJPEGDecoder(void * Properties);
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall DecodeInit(void);
	virtual void __fastcall DecodeEnd(void);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TTIFFJPEGDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TThunderDecoder;
class PASCALIMPLEMENTATION TThunderDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	unsigned FWidth;
	
public:
	__fastcall TThunderDecoder(unsigned Width);
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TThunderDecoder(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPCDDecoder;
class PASCALIMPLEMENTATION TPCDDecoder : public TDecoder 
{
	typedef TDecoder inherited;
	
private:
	Classes::TStream* FStream;
	
public:
	__fastcall TPCDDecoder(Classes::TStream* Stream);
	virtual void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	virtual void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TPCDDecoder(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Graphiccompression */
using namespace Graphiccompression;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GraphicCompression
