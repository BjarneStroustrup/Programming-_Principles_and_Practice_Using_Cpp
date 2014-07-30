//
// "$Id: Fl_XPM_Image.cxx 9325 2012-04-05 05:12:30Z fabien $"
//
// Fl_XPM_Image routines.
//
// Copyright 1997-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//
// Contents:
//
//

//
// Include necessary header files...
//

#include <FL/Fl.H>
#include <FL/Fl_XPM_Image.H>
#include <stdio.h>
#include <stdlib.h>
#include <FL/fl_utf8.h>
#include "flstring.h"


//
// 'hexdigit()' - Convert a hex digit to an integer.
//

static int hexdigit(int x) {	// I - Hex digit...
  if (isdigit(x)) return x-'0';
  if (isupper(x)) return x-'A'+10;
  if (islower(x)) return x-'a'+10;
  return 20;
}

#define MAXSIZE 2048
#define INITIALLINES 256
/**
  The constructor loads the XPM image from the name filename.
  <P>The destructor free all memory and server resources that are used by
  the image.
*/
Fl_XPM_Image::Fl_XPM_Image(const char *name) : Fl_Pixmap((char *const*)0) {
  FILE *f;

  if ((f = fl_fopen(name, "rb")) == NULL) return;

  // read all the c-strings out of the file:
  char** new_data = new char *[INITIALLINES];
  char** temp_data;
  int malloc_size = INITIALLINES;
  char buffer[MAXSIZE+20];
  int i = 0;
  while (fgets(buffer,MAXSIZE+20,f)) {
    if (buffer[0] != '\"') continue;
    char *myp = buffer;
    char *q = buffer+1;
    while (*q != '\"' && myp < buffer+MAXSIZE) {
      if (*q == '\\') switch (*++q) {
      case '\r':
      case '\n':
	if (!fgets(q,(int) (buffer+MAXSIZE+20-q),f)) { /* no problem if we hit EOF */ } break;
      case 0:
	break;
      case 'x': {
	q++;
	int n = 0;
	for (int x = 0; x < 3; x++) {
	  int xd = hexdigit(*q);
	  if (xd > 15) break;
	  n = (n<<4)+xd;
	  q++;
	}
	*myp++ = n;
      } break;
      default: {
	int c = *q++;
	if (c>='0' && c<='7') {
	  c -= '0';
	  for (int x=0; x<2; x++) {
	    int xd = hexdigit(*q);
	    if (xd>7) break;
	    c = (c<<3)+xd;
	    q++;
	  }
	}
	*myp++ = c;
      } break;
      } else {
	*myp++ = *q++;
      }
    }
    *myp++ = 0;
    if (i >= malloc_size) {
      temp_data = new char *[malloc_size + INITIALLINES];
      memcpy(temp_data, new_data, sizeof(char *) * malloc_size);
      delete[] new_data;
      new_data = temp_data;
      malloc_size += INITIALLINES;
    }
    new_data[i] = new char[myp-buffer+1];
    memcpy(new_data[i], buffer,myp-buffer);
    new_data[i][myp-buffer] = 0;
    i++;
  }

  fclose(f);

  data((const char **)new_data, i);
  alloc_data = 1;

  measure();
}


//
// End of "$Id: Fl_XPM_Image.cxx 9325 2012-04-05 05:12:30Z fabien $".
//
