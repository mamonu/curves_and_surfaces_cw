#include "StdAfx.h"
#include "Bitmap.h"
#include "RGBTriple.h"

Bitmap::BitmapFileHeader::BitmapFileHeader(const BitmapInfoHeader& Info) {
	_Type = 0x4d42;
	_Reserved1 = 0;
	_Reserved2 = 0;
	_OffBits = 14 + Info._Size + Info._ClrUsed * 3;
	_Size = _OffBits + Info._SizeImage;
}

ostream &Bitmap::BitmapFileHeader::Write(ostream &out) const {
	out.write((const char*)&_Type, sizeof(_Type));
	out.write((const char*)&_Size, sizeof(_Size));
	out.write((const char*)&_Reserved1, sizeof(_Reserved1));
	out.write((const char*)&_Reserved2, sizeof(_Reserved2));
	out.write((const char*)&_OffBits, sizeof(_OffBits));
	return out;
}

istream &Bitmap::BitmapFileHeader::Read(istream &in) {
	in.read((char*)&_Type, sizeof(_Type));
	in.read((char*)&_Size, sizeof(_Size));
	in.read((char*)&_Reserved1, sizeof(_Reserved1));
	in.read((char*)&_Reserved2, sizeof(_Reserved2));
	in.read((char*)&_OffBits, sizeof(_OffBits));
	return in;
}

// class Bitmap::BitmapInfoHeader

Bitmap::BitmapInfoHeader::BitmapInfoHeader(int Width, int Height, int BitCount) {
	_Size=40;
	_Width=Width;
	_Height=Height;
	_Planes=1;
	_BitCount=BitCount;
	_Compression=0L; // No compression
	_SizeImage=(long)Width*(long)Height*(BitCount>8 ? 3L : 1L);
	_XPelsPerMeter=0;
	_YPelsPerMeter=0;
	_ClrUsed=(BitCount>8 ? 0L : 1L<<BitCount);
	_ClrImportant=_ClrUsed;
}

ostream &Bitmap::BitmapInfoHeader::Write(ostream &out) const {
	out.write((const char*)&_Size, sizeof(_Size));
	out.write((const char*)&_Width, sizeof(_Width));
	out.write((const char*)&_Height, sizeof(_Height));
	out.write((const char*)&_Planes, sizeof(_Planes));
	out.write((const char*)&_BitCount, sizeof(_BitCount));
	out.write((const char*)&_Compression, sizeof(_Compression));
	out.write((const char*)&_SizeImage, sizeof(_SizeImage));
	out.write((const char*)&_XPelsPerMeter, sizeof(_XPelsPerMeter));
	out.write((const char*)&_YPelsPerMeter, sizeof(_YPelsPerMeter));
	out.write((const char*)&_ClrUsed, sizeof(_ClrUsed));
	out.write((const char*)&_ClrImportant, sizeof(_ClrImportant));
	return out;
}

istream &Bitmap::BitmapInfoHeader::Read(istream &in) {
	in.read((char*)&_Size, sizeof(_Size));
	in.read((char*)&_Width, sizeof(_Width));
	in.read((char*)&_Height, sizeof(_Height));
	in.read((char*)&_Planes, sizeof(_Planes));
	in.read((char*)&_BitCount, sizeof(_BitCount));
	in.read((char*)&_Compression, sizeof(_Compression));
	in.read((char*)&_SizeImage, sizeof(_SizeImage));
	in.read((char*)&_XPelsPerMeter, sizeof(_XPelsPerMeter));
	in.read((char*)&_YPelsPerMeter, sizeof(_YPelsPerMeter));
	in.read((char*)&_ClrUsed, sizeof(_ClrUsed));
	in.read((char*)&_ClrImportant, sizeof(_ClrImportant));
	return in;
}

// class Bitmap

Bitmap::Bitmap(int Width, int Height, int BitCount, void *pPixels, RGBTriple *pPalette, bool OwnsData)
: _InfoHeader(Width, Height, BitCount), _pPixels(pPixels), _pPalette(pPalette), _OwnsData(OwnsData) {
	_FileHeader = BitmapFileHeader(_InfoHeader);
}

Bitmap::Bitmap()
: _InfoHeader(0, 0, 8),	_pPixels(0), _pPalette(0), _OwnsData(true) {
	_FileHeader = BitmapFileHeader(_InfoHeader);
}

Bitmap::~Bitmap()
{
	if (_OwnsData) {
		delete[] _pPixels;
		delete[] _pPalette;
	}
}

// Some older streaming classes use a short to specify the size of the data (BC++Builder5 uses a long)
void Bitmap::WriteLong(ostream &out, const char * Buffer, unsigned long Size) const {
	if (Size>0)
		out.write((const char*)Buffer, Size);
}

ostream &Bitmap::Write(ostream &out) const {
	_FileHeader.Write(out);
	_InfoHeader.Write(out);
	WriteLong(out, (const char*)_pPalette, _InfoHeader._ClrUsed*3);
	WriteLong(out, (const char*)_pPixels, _InfoHeader._SizeImage);
	return out;
}

istream &Bitmap::Read(istream &in) {
	_FileHeader.Read(in);
	_InfoHeader.Read(in);

	// Read palette
	if (_InfoHeader._BitCount==8) {
		if (_OwnsData)
			delete[] _pPalette;
		_pPalette=new RGBTriple [_InfoHeader._ClrUsed];
		in.read((char*)_pPalette, 3*_InfoHeader._ClrUsed);
	}

	// Calculate the length of the line and the filler.
	long ImageLength = _InfoHeader._Width*_InfoHeader._Height*(_InfoHeader._BitCount>8 ? 3L : 1L);;
	long LineLength = _InfoHeader._Width*(_InfoHeader._BitCount>8 ? 3L : 1L);
	long FillerLength = LineLength % 4;
	FillerLength = (FillerLength ? 4 - FillerLength : 0 );
	long Filler = 0;

	//  Allocate space for bitmap
	if (_OwnsData)
		delete[] _pPixels;

	_pPixels=new unsigned char [ImageLength];
	unsigned char *pPixels = (unsigned char *)_pPixels;
	for (int i=0; i<_InfoHeader._Height; i++, pPixels+=LineLength){
		in.read((char*)pPixels, LineLength);
		if (FillerLength)
			in.read((char*)&Filler, FillerLength);
	}

	_OwnsData = true;
	return in;
}

void Bitmap::invertColors() {
	if (_InfoHeader._BitCount==8) {
		RGBTriple *colour = _pPalette;
		for (unsigned int i=0; i<_InfoHeader._ClrUsed; i++)
			colour[i].invert(); 
	} else {
		RGBTriple *colour = (RGBTriple*)_pPixels;
		for (int i=0; i<_InfoHeader._Height*_InfoHeader._Width; i++)
			colour[i].invert(); 
	}
}