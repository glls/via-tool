// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GraphicEx.pas' rev: 6.00

#ifndef GraphicExHPP
#define GraphicExHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <GraphicColor.hpp>	// Pascal unit
#include <GraphicStrings.hpp>	// Pascal unit
#include <GraphicCompression.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Graphicex
{
//-- type declarations -------------------------------------------------------
typedef DynamicArray<unsigned >  TCardinalArray;

typedef DynamicArray<Byte >  TByteArray;

typedef DynamicArray<float >  TFloatArray;

#pragma option push -b-
enum GraphicEx__1 { ioTiled, ioBigEndian, ioMinIsWhite, ioReversed, ioUseGamma };
#pragma option pop

typedef Set<GraphicEx__1, ioTiled, ioUseGamma>  TImageOptions;

#pragma option push -b-
enum TCompressionType { ctUnknown, ctNone, ctRLE, ctPackedBits, ctLZW, ctFax3, ctFaxRLE, ctFax4, ctFaxRLEW, ctLZ77, ctJPEG, ctOJPEG, ctThunderscan, ctNext, ctIT8CTPAD, ctIT8LW, ctIT8MP, ctIT8BL, ctPixarFilm, ctPixarLog, ctDCS, ctJBIG, ctPCDHuffmann };
#pragma option pop

struct TImageProperties;
typedef TImageProperties *PImageProperties;

#pragma pack(push, 4)
struct TImageProperties
{
	unsigned Version;
	TImageOptions Options;
	unsigned Width;
	unsigned Height;
	Graphiccolor::TColorScheme ColorScheme;
	Byte BitsPerSample;
	Byte SamplesPerPixel;
	Byte BitsPerPixel;
	TCompressionType Compression;
	float FileGamma;
	float XResolution;
	float YResolution;
	bool Interlaced;
	bool HasAlpha;
	unsigned FirstIFD;
	unsigned PlanarConfig;
	unsigned CurrentRow;
	unsigned TileWidth;
	unsigned TileLength;
	unsigned BytesPerLine;
	DynamicArray<unsigned >  RowsPerStrip;
	DynamicArray<Byte >  YCbCrSubSampling;
	DynamicArray<Byte >  JPEGTables;
	unsigned JPEGColorMode;
	unsigned JPEGTablesMode;
	int CurrentStrip;
	int StripCount;
	int Predictor;
	bool Overview;
	Byte Rotate;
	Word ImageCount;
	bool LocalColorTable;
	bool BottomUp;
	Byte Channels;
	Byte FilterMode;
} ;
#pragma pack(pop)

class DELPHICLASS TGraphicExGraphic;
class PASCALIMPLEMENTATION TGraphicExGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
private:
	Graphiccolor::TColorManager* FColorManager;
	TImageProperties FImageProperties;
	unsigned FBasePosition;
	Classes::TStream* FStream;
	#pragma pack(push, 1)
	Types::TRect FProgressRect;
	#pragma pack(pop)
	
	
public:
	__fastcall virtual TGraphicExGraphic(void);
	__fastcall virtual ~TGraphicExGraphic(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, const AnsiString FileName)/* overload */;
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	HIDESBASE void __fastcall LoadFromResourceName(unsigned Instance, const AnsiString ResName);
	HIDESBASE void __fastcall LoadFromResourceID(unsigned Instance, int ResID);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
	__property Graphiccolor::TColorManager* ColorManager = {read=FColorManager};
	__property TImageProperties ImageProperties = {read=FImageProperties, write=FImageProperties};
};


typedef TMetaClass*TGraphicExGraphicClass;

class DELPHICLASS TSGIGraphic;
class PASCALIMPLEMENTATION TSGIGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
private:
	DynamicArray<unsigned >  FRowStart;
	DynamicArray<unsigned >  FRowSize;
	Graphiccompression::TDecoder* FDecoder;
	void __fastcall ReadAndDecode(void * Red, void * Green, void * Blue, void * Alpha, unsigned Row, unsigned BPC);
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TSGIGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TSGIGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TAutodeskGraphic;
class PASCALIMPLEMENTATION TAutodeskGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TAutodeskGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TAutodeskGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


#pragma pack(push, 1)
struct TIFDEntry
{
	Word Tag;
	Word DataType;
	unsigned DataLength;
	unsigned Offset;
} ;
#pragma pack(pop)

typedef Word TTIFFPalette[788];

typedef DynamicArray<TIFDEntry >  GraphicEx__6;

class DELPHICLASS TTIFFGraphic;
class PASCALIMPLEMENTATION TTIFFGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
private:
	DynamicArray<TIFDEntry >  FIFD;
	Word FPalette[788];
	unsigned FYCbCrPositioning;
	DynamicArray<float >  FYCbCrCoefficients;
	bool __fastcall FindTag(unsigned Tag, unsigned &Index);
	void __fastcall GetValueList(Classes::TStream* Stream, unsigned Tag, TByteArray &Values)/* overload */;
	void __fastcall GetValueList(Classes::TStream* Stream, unsigned Tag, TCardinalArray &Values)/* overload */;
	void __fastcall GetValueList(Classes::TStream* Stream, unsigned Tag, TFloatArray &Values)/* overload */;
	float __fastcall GetValue(Classes::TStream* Stream, unsigned Tag, float Default = 0.000000E+00)/* overload */;
	unsigned __fastcall GetValue(unsigned Tag, unsigned Default = (unsigned)(0x0))/* overload */;
	unsigned __fastcall GetValue(unsigned Tag, unsigned &Size, unsigned Default = (unsigned)(0x0))/* overload */;
	void __fastcall SortIFD(void);
	void __fastcall SwapIFD(void);
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TTIFFGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TTIFFGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TEPSGraphic;
class PASCALIMPLEMENTATION TEPSGraphic : public TTIFFGraphic 
{
	typedef TTIFFGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TEPSGraphic(void) : TTIFFGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TEPSGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TTargaGraphic;
class PASCALIMPLEMENTATION TTargaGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream)/* overload */;
	HIDESBASE void __fastcall SaveToStream(Classes::TStream* Stream, bool Compressed)/* overload */;
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TTargaGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TTargaGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TPCXGraphic;
class PASCALIMPLEMENTATION TPCXGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TPCXGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TPCXGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TPCDGraphic;
class PASCALIMPLEMENTATION TPCDGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TPCDGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TPCDGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TPPMGraphic;
class PASCALIMPLEMENTATION TPPMGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
private:
	char FBuffer[4096];
	int FIndex;
	char __fastcall CurrentChar(void);
	char __fastcall GetChar(void);
	unsigned __fastcall GetNumber(void);
	AnsiString __fastcall ReadLine();
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TPPMGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TPPMGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TCUTGraphic;
class PASCALIMPLEMENTATION TCUTGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
private:
	AnsiString FPaletteFile;
	
protected:
	void __fastcall LoadPalette(void);
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromFile(const AnsiString FileName);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
	__property AnsiString PaletteFile = {read=FPaletteFile, write=FPaletteFile};
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TCUTGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TCUTGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TRLAGraphic;
class PASCALIMPLEMENTATION TRLAGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
private:
	void __fastcall SwapHeader(void *Header);
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TRLAGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TRLAGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TPSDGraphic;
class PASCALIMPLEMENTATION TPSDGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TPSDGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TPSDGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


class DELPHICLASS TPSPGraphic;
class PASCALIMPLEMENTATION TPSPGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TPSPGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TPSPGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


typedef char TChunkType[4];

#pragma pack(push, 1)
struct TPNGChunkHeader
{
	unsigned Length;
	char ChunkType[4];
} ;
#pragma pack(pop)

class DELPHICLASS TPNGGraphic;
class PASCALIMPLEMENTATION TPNGGraphic : public TGraphicExGraphic 
{
	typedef TGraphicExGraphic inherited;
	
private:
	Graphiccompression::TLZ77Decoder* FDecoder;
	int FIDATSize;
	void *FRawBuffer;
	void *FCurrentSource;
	#pragma pack(push, 1)
	TPNGChunkHeader FHeader;
	#pragma pack(pop)
	
	unsigned FCurrentCRC;
	int FSourceBPP;
	HPALETTE FPalette;
	DynamicArray<Byte >  FTransparency;
	Graphics::TColor FTransparentColor;
	Graphics::TColor FBackgroundColor;
	void __fastcall ApplyFilter(Byte Filter, System::PByte Line, System::PByte PrevLine, System::PByte Target, int BPP, int BytesPerRow);
	bool __fastcall IsChunk(const char * ChunkType);
	unsigned __fastcall LoadAndSwapHeader(void);
	void __fastcall LoadBackgroundColor(const void *Description);
	void __fastcall LoadIDAT(const void *Description);
	void __fastcall LoadTransparency(const void *Description);
	void __fastcall ReadDataAndCheckCRC(void);
	void __fastcall ReadRow(void * RowBuffer, int BytesPerRow);
	int __fastcall SetupColorDepth(int ColorType, int BitDepth);
	
public:
	/* virtual class method */ virtual bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
	__property Graphics::TColor BackgroundColor = {read=FBackgroundColor, nodefault};
	__property TByteArray Transparency = {read=FTransparency};
public:
	#pragma option push -w-inl
	/* TGraphicExGraphic.Create */ inline __fastcall virtual TPNGGraphic(void) : TGraphicExGraphic() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicExGraphic.Destroy */ inline __fastcall virtual ~TPNGGraphic(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  CanLoad(TMetaClass* vmt, const AnsiString FileName){ return TGraphicExGraphic::CanLoad(FileName); }
	
};


#pragma option push -b-
enum TFormatType { ftAnimation, ftLayered, ftMultiImage, ftRaster, ftVector };
#pragma option pop

typedef Set<TFormatType, ftAnimation, ftVector>  TFormatTypes;

#pragma option push -b-
enum TFilterSortType { fstNone, fstBoth, fstDescription, fstExtension };
#pragma option pop

#pragma option push -b-
enum TFilterOption { foCompact, foIncludeAll, foIncludeExtension };
#pragma option pop

typedef Set<TFilterOption, foCompact, foIncludeExtension>  TFilterOptions;

class DELPHICLASS TFileFormatList;
class PASCALIMPLEMENTATION TFileFormatList : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FClassList;
	Classes::TList* FExtensionList;
	
protected:
	int __fastcall FindExtension(const AnsiString Extension);
	int __fastcall FindGraphicClass(TMetaClass* GraphicClass);
	
public:
	__fastcall TFileFormatList(void);
	__fastcall virtual ~TFileFormatList(void);
	void __fastcall Clear(void);
	AnsiString __fastcall GetDescription(TMetaClass* Graphic);
	void __fastcall GetExtensionList(Classes::TStrings* List);
	AnsiString __fastcall GetGraphicFilter(TFormatTypes Formats, TFilterSortType SortType, TFilterOptions Options, TMetaClass* GraphicClass);
	TMetaClass* __fastcall GraphicFromExtension(AnsiString S);
	TMetaClass* __fastcall GraphicFromContent(const AnsiString FileName)/* overload */;
	TMetaClass* __fastcall GraphicFromContent(Classes::TStream* Stream)/* overload */;
	void __fastcall RegisterFileFormat(const AnsiString Extension, const AnsiString Common, const AnsiString Individual, TFormatTypes FormatTypes, bool Replace, bool RegisterDefault, TMetaClass* GraphicClass);
	void __fastcall UnregisterFileFormat(const AnsiString Extension, TMetaClass* GraphicClass);
};


#pragma option push -b-
enum TResamplingFilter { sfBox, sfTriangle, sfHermite, sfBell, sfSpline, sfLanczos3, sfMitchell };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFileFormatList* FileFormatList;
extern PACKAGE void __fastcall Stretch(unsigned NewWidth, unsigned NewHeight, TResamplingFilter Filter, float Radius, Graphics::TBitmap* Source, Graphics::TBitmap* Target)/* overload */;
extern PACKAGE void __fastcall Stretch(unsigned NewWidth, unsigned NewHeight, TResamplingFilter Filter, float Radius, Graphics::TBitmap* Source)/* overload */;

}	/* namespace Graphicex */
using namespace Graphicex;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GraphicEx
