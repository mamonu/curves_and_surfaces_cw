#pragma once
#include <iostream>
using namespace std;

class RGBTriple {
private:
	unsigned char _blue;
	unsigned char _green;
	unsigned char _red;

	void write(ostream &out) const;
	void read(istream &in);

public:
	RGBTriple() {}
	RGBTriple(unsigned char red, unsigned char green, unsigned char blue) :
	_blue(blue), _green(green), _red(red) {}

	unsigned char red() const { return _red; }
	unsigned char green() const { return _green; }
	unsigned char blue() const { return _blue; }

	void invert() { unsigned char t = _blue; _blue = _red; _red = t; }

	friend ostream &operator<<(ostream &out, const RGBTriple &o) { o.write(out); return out; }
	friend istream &operator>>(istream &in, RGBTriple &o) { o.read(in); return in; }
};
