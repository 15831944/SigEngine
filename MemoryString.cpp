// MemoryString.cpp: implementation of the CMemoryString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemoryString::CMemoryString()
{

}

CMemoryString::~CMemoryString()
{

}

/*
#define HASHWORDBITS 32


int hash_string(const char *str_param)
{
  unsigned int hval = 0;
  unsigned int g;

  const char *str = str_param;

  while (*str != '\0')
  {
    hval <<= 4;
    hval += (unsigned long) *str++;

    g = hval & ((unsigned long) 0xf << (HASHWORDBITS - 4));
    
    if(g != 0)
    {
      hval ^= g >> (HASHWORDBITS - 8);
      hval ^= g;
    }
  }

  return hval;
}








*/