// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GraphicColor.pas' rev: 6.00

#ifndef GraphicColorHPP
#define GraphicColorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <GraphicStrings.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Graphiccolor
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TColorScheme { csUnknown, csIndexed, csG, csGA, csRGB, csRGBA, csBGR, csBGRA, csCMY, csCMYK, csCIELab, csYCbCr, csPhotoYCC };
#pragma option pop

#pragma option push -b-
enum GraphicColor__1 { coAlpha, coApplyGamma, coNeedByteSwap, coLabByteRange, coLabChromaOffset };
#pragma option pop

typedef Set<GraphicColor__1, coAlpha, coLabChromaOffset>  TConvertOptions;

#pragma option push -b-
enum TRawPaletteFormat { pfInterlaced8Triple, pfInterlaced8Quad, pfPlane8Triple, pfPlane8Quad, pfInterlaced16Triple, pfInterlaced16Quad, pfPlane16Triple, pfPlane16Quad };
#pragma option pop

typedef void __fastcall (__closure *TConversionMethod)(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);

typedef DynamicArray<int >  GraphicColor__3;

class DELPHICLASS TColorManager;
class PASCALIMPLEMENTATION TColorManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	bool FChanged;
	Byte FSourceBPS;
	Byte FTargetBPS;
	Byte FSourceSPP;
	Byte FTargetSPP;
	float FMainGamma;
	float FDisplayGamma;
	Byte FGammaTable[256];
	float FYCbCrCoefficients[3];
	Byte FHSubsampling;
	Byte FVSubSampling;
	DynamicArray<int >  FCrToRedTable;
	DynamicArray<int >  FCbToBlueTable;
	DynamicArray<int >  FCrToGreenTable;
	DynamicArray<int >  FCbToGreenTable;
	TColorScheme FSourceScheme;
	TColorScheme FTargetScheme;
	TConversionMethod FRowConversion;
	TConvertOptions FSourceOptions;
	TConvertOptions FTargetOptions;
	
protected:
	Byte __fastcall ComponentGammaConvert(Byte Value);
	Word __fastcall ComponentNoConvert16(Word Value);
	Byte __fastcall ComponentNoConvert8(Byte Value);
	Byte __fastcall ComponentScaleConvert(Word Value);
	Byte __fastcall ComponentScaleGammaConvert(Word Value);
	Byte __fastcall ComponentSwapScaleGammaConvert(Word Value);
	Byte __fastcall ComponentSwapScaleConvert(Word Value);
	Word __fastcall ComponentSwapConvert(Word Value);
	void __fastcall RowConvertBGR2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertBGR2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCIELAB2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCIELAB2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCMYK2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCMYK2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertGray(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexed8(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexedBoth16(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexedSource16(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexedTarget16(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertRGB2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertRGB2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertPhotoYCC2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertPhotoYCC2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertYCbCr2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertYCbCr2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall CreateYCbCrLookup(void);
	Graphics::TPixelFormat __fastcall GetPixelFormat(int Index);
	void __fastcall PrepareConversion(void);
	void __fastcall SetSourceBitsPerSample(const Byte Value);
	void __fastcall SetSourceColorScheme(const TColorScheme Value);
	void __fastcall SetSourceSamplesPerPixel(const Byte Value);
	void __fastcall SetTargetBitsPerSample(const Byte Value);
	void __fastcall SetTargetColorScheme(const TColorScheme Value);
	void __fastcall SetTargetSamplesPerPixel(const Byte Value);
	
public:
	__fastcall TColorManager(void);
	void __fastcall ConvertRow(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	HPALETTE __fastcall CreateColorPalette(const void * const * Data, const int Data_Size, TRawPaletteFormat DataFormat, unsigned ColorCount, bool RGB);
	HPALETTE __fastcall CreateGrayscalePalette(bool MinimumIsWhite);
	void __fastcall Error(const AnsiString Msg);
	void __fastcall SetGamma(float MainGamma, float DisplayGamma = 2.200000E+00);
	void __fastcall SetYCbCrParameters(const float * Values, const int Values_Size, Byte HSubSampling, Byte VSubSampling);
	__property Byte SourceBitsPerSample = {read=FSourceBPS, write=SetSourceBitsPerSample, nodefault};
	__property TColorScheme SourceColorScheme = {read=FSourceScheme, write=SetSourceColorScheme, nodefault};
	__property TConvertOptions SourceOptions = {read=FSourceOptions, write=FSourceOptions, nodefault};
	__property Graphics::TPixelFormat SourcePixelFormat = {read=GetPixelFormat, index=0, nodefault};
	__property Byte SourceSamplesPerPixel = {read=FSourceSPP, write=SetSourceSamplesPerPixel, nodefault};
	__property Byte TargetBitsPerSample = {read=FTargetBPS, write=SetTargetBitsPerSample, nodefault};
	__property TColorScheme TargetColorScheme = {read=FTargetScheme, write=SetTargetColorScheme, nodefault};
	__property TConvertOptions TargetOptions = {read=FTargetOptions, write=FTargetOptions, nodefault};
	__property Graphics::TPixelFormat TargetPixelFormat = {read=GetPixelFormat, index=1, nodefault};
	__property Byte TargetSamplesPerPixel = {read=FTargetSPP, write=SetTargetSamplesPerPixel, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TColorManager(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define DefaultDisplayGamma  (2.200000E+00)
extern PACKAGE Byte __fastcall ClampByte(int Value);
extern PACKAGE Word __fastcall MulDiv16(Word Number, Word Numerator, Word Denominator);

}	/* namespace Graphiccolor */
using namespace Graphiccolor;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GraphicColor
