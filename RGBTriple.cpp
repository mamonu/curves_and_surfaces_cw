#include "StdAfx.h"
#include "RGBTriple.h"

void RGBTriple::write(ostream &out) const {
        out << "(" << int(_red) << ", " << int(_green) << ", " << int(_blue) << ")";
}

void RGBTriple::read(istream &in) {
        char ch;
        int red, green, blue;
        in >> ch >> red >> ch >> green >> ch >> blue >> ch;
        *this = RGBTriple(red, green, blue);
}


