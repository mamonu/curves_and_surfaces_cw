#pragma once

#include <iostream>
using namespace std;

class RGBTriple;

class Bitmap {
private:

	class BitmapInfoHeader {
	public:
		unsigned long _Size;
		long _Width;
		long _Height;
		unsigned short _Planes;
		unsigned short _BitCount;
		unsigned long _Compression;
		unsigned long _SizeImage;
		long _XPelsPerMeter;
		long _YPelsPerMeter;
		unsigned long _ClrUsed;
		unsigned long _ClrImportant;

		BitmapInfoHeader() {}
		BitmapInfoHeader(int Width, int Height, int BitCount);
		ostream &Write(ostream &out) const;
		istream &Read(istream &in);
	};

	class BitmapFileHeader {
	public:
		unsigned short _Type;
		unsigned long _Size;
		unsigned short _Reserved1;
		unsigned short _Reserved2;
		unsigned long _OffBits;

		BitmapFileHeader() {}
		BitmapFileHeader(const BitmapInfoHeader& Info);
		ostream &Write(ostream &out) const;
		istream &Read(istream &in);
	};

	BitmapFileHeader _FileHeader;
	BitmapInfoHeader _InfoHeader;
	RGBTriple *_pPalette;
	void *_pPixels;
	bool _OwnsData;

	void WriteLong(ostream &out, const char * Buffer, unsigned long Size) const;

public:
	Bitmap();
	Bitmap(int Width, int Height, int BitCount, void *pPixel, RGBTriple *pPalette=0, bool OwnsData=false);
	~Bitmap();
	ostream &Write(ostream &out) const;
	istream &Read(istream &in);
	void invertColors();

	const void *Bits() const { return _pPixels; }
	int Width() const { return _InfoHeader._Width; }
	int Height() const { return _InfoHeader._Height; }
};
