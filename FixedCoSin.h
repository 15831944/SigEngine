// FixedCoSin.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXEDCOSIN_H__8E6A11E7_1F6A_4382_98F0_2A2AE4C26515__INCLUDED_)
#define AFX_FIXEDCOSIN_H__8E6A11E7_1F6A_4382_98F0_2A2AE4C26515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"

// ====

#define FIXED_SHORT
//#define FIXED_LONG

// ====

#ifdef FIXED_SHORT
#ifdef FIXED_LONG
#error "Cannot define FIXED_SHORT and FIXED_LONG together !"
#endif // FIXED_LONG
#endif // FIXED_SHORT

#ifdef FIXED_SHORT
#define FIXED_TYPE short
#define FIXED_SIZE 16
#define FIXED_MASK 0x2000
#else
#define FIXED_TYPE int
#define FIXED_SIZE 32
#define FIXED_MASK 0x20000000
#endif // FIXED_SHORT

#define FIXED_QUADR 256  // 1024 / 4
#define FIXED_BIAIS 1024
#define FIXED_ARRAY 1536 // 1024 + 512
#define FIXED_2PI   6.28318530717958647692528

#include "FixedCoSin.hpp"

/*
//FIXED_TYPE g_panCOSIN[1536];
class CFixedCoSin  
{
  public:
    CFixedCoSin(){}
    virtual ~CFixedCoSin(){}

    //

    inline void CreateFixedArray(void)
    {
      double      l_nPi;
      int         l_nLoop;
      int         l_nSize;
      int         l_nPoint;
      int         l_nBiais;

      FIXED_TYPE* l_pnCosin;
      FIXED_TYPE* l_pnCos;

      FIXED_TYPE  l_anCosinCadrant[FIXED_ARRAY];

      //
  
      l_nPi     = FIXED_2PI; // 2PI
      l_nSize   = FIXED_SIZE>>3; // /8
      l_nPoint  = FIXED_MASK; // 1<<(FIXED_SIZE-2);
      l_nBiais  = FIXED_BIAIS;
      l_pnCosin = l_anCosinCadrant;

      for
      ( l_nLoop = 0
      ; l_nLoop < l_nBiais
      ; l_nLoop += 1
      )
      {
        *l_pnCosin
        = (FIXED_TYPE)
        (
            sin
            ( (l_nPi * l_nLoop)
            / l_nBiais
            )
          * l_nPoint
        )
        ;

        l_pnCosin += 1;
      }

      l_pnCos = l_anCosinCadrant;
      l_nBiais /= 2;

      for
      ( l_nLoop = 0
      ; l_nLoop < l_nBiais
      ; l_nLoop += 1
      )
      {
        *l_pnCosin = *l_pnCos;
        l_pnCosin += 1;
        l_pnCos   += 1;
      }

      // Ecriture du fichier

      FILE*          l_sFileHandle;
      unsigned char* l_panDataCosin;
      unsigned char  l_nBufferHi;
      unsigned char  l_nBufferLo;

      l_nBiais  = FIXED_BIAIS;

      l_sFileHandle = fopen("C:\\FixedCoSin.hpp", "wt"); // Change the path here
      if(l_sFileHandle != NULL)
      {
        l_nBiais = FIXED_ARRAY;
        fprintf(l_sFileHandle, "FIXED_TYPE g_panCOSIN[%d] =\n{\n ", l_nBiais);

        l_panDataCosin = (unsigned char*) l_anCosinCadrant + l_nSize; // LITTLE ENDIAN
        l_pnCosin      = l_anCosinCadrant;

        for
        ( l_nLoop = 0
        ; l_nLoop < l_nBiais
        ; l_nLoop += 1
        )
        {
          if(*l_pnCosin < 0)
          {
            fputs(" -0x", l_sFileHandle);
            *l_pnCosin = 0 - *l_pnCosin; // On inverse
          }
          else
          {
            fputs("  0x", l_sFileHandle);
          }

          for
          ( l_nPoint = 0
          ; l_nPoint < l_nSize
          ; l_nPoint += 1
          )
          {
            l_panDataCosin -= 1; // LITTLE ENDIAN

            l_nBufferHi = *l_panDataCosin;
            l_nBufferLo = l_nBufferHi;

            l_nBufferHi >>= 4;
            l_nBufferLo  &= 0x0F;

            if(l_nBufferHi < 10)
            {
              l_nBufferHi += '0';
            }
            else
            {
              l_nBufferHi += 'A' - 10;
            }

            if(l_nBufferLo < 10)
            {
              l_nBufferLo += '0';
            }
            else
            {
              l_nBufferLo += 'A' - 10;
            }

            fputc(l_nBufferHi, l_sFileHandle);
            fputc(l_nBufferLo, l_sFileHandle);
          }

          l_panDataCosin += l_nSize; // LITTLE ENDIAN
          l_panDataCosin += l_nSize; // LITTLE ENDIAN
          l_pnCosin      += 1;

          // FIXED_TYPE suivant
          fputs(",", l_sFileHandle);

          l_nPoint = 16 / l_nSize;
          if((l_nLoop % l_nPoint) == (l_nPoint - 1))
          { // 16 bytes per line
            if(((l_nLoop - 16) % FIXED_QUADR) == 0)
            {
              switch((l_nLoop - 16) / FIXED_QUADR)
              {
                case 0 :
                  fputs(" //          SIN(  0)", l_sFileHandle);
                  break;
                case 1 :
                  fputs(" // COS(  0) SIN( 90)", l_sFileHandle);
                  break;
                case 2 :
                  fputs(" // COS( 90) SIN(180)", l_sFileHandle);
                  break;
                case 3 :
                  fputs(" // COS(180) SIN(270)", l_sFileHandle);
                  break;
                case 4 :
                  fputs(" // COS(270) SIN(360)", l_sFileHandle);
                  break;
                case 5 :
                  fputs(" // COS(360)", l_sFileHandle);
                  break;
                default :
              }
            }else{}

            fputs("\n ", l_sFileHandle);
          }else{}
        }
        fputs("};\n", l_sFileHandle);

        fclose(l_sFileHandle);
      }else{}
    }
};
*/

/* BIAIS    */ inline FIXED_TYPE fcossin(unsigned int i_nPointer) { return g_panCOSIN[i_nPointer%FIXED_ARRAY]; }

/* COS 360  */ inline double fcosdeg(double i_nAngleDeg) { return (double) fcossin((unsigned int) (i_nAngleDeg * 2.8444444444444444444444444444444) + FIXED_QUADR) / FIXED_MASK; }
/* COS 2PI  */ inline double fcosrad(double i_nAngleRad) { return (double) fcossin((unsigned int) (i_nAngleRad * 162.97466172610082382733714920597) + FIXED_QUADR) / FIXED_MASK; }
/* COS ONE  */ inline double fcosone(double i_nAngleOne) { return (double) fcossin((unsigned int) (i_nAngleOne * 1024.0000000000000000000000000000) + FIXED_QUADR) / FIXED_MASK; }
/* COS 1024 */ inline double fcosbia(double i_nAngleBia) { return (double) fcossin((unsigned int) (i_nAngleBia                                    ) + FIXED_QUADR) / FIXED_MASK; }
/* COS 100  */ inline double fcospct(double i_nAnglePct) { return (double) fcossin((unsigned int) (i_nAnglePct * 10.240000000000000000000000000000) + FIXED_QUADR) / FIXED_MASK; }

/* SIN 360  */ inline double fsindeg(double i_nAngleDeg) { return (double) fcossin((unsigned int) (i_nAngleDeg * 2.8444444444444444444444444444444)              ) / FIXED_MASK; }
/* SIN 2PI  */ inline double fsinrad(double i_nAngleRad) { return (double) fcossin((unsigned int) (i_nAngleRad * 162.97466172610082382733714920597)              ) / FIXED_MASK; }
/* SIN ONE  */ inline double fsinone(double i_nAngleOne) { return (double) fcossin((unsigned int) (i_nAngleOne * 1024.0000000000000000000000000000)              ) / FIXED_MASK; }
/* SIN 1024 */ inline double fsinbia(double i_nAngleBia) { return (double) fcossin((unsigned int) (i_nAngleBia                                    )              ) / FIXED_MASK; }
/* SIN 100  */ inline double fsinpct(double i_nAnglePct) { return (double) fcossin((unsigned int) (i_nAnglePct * 10.240000000000000000000000000000)              ) / FIXED_MASK; }

/* BIAIS    */ // inline FIXED_TYPE fcossin(int i_nPointer, bool i_bCos = true) { int l_nShift = (i_bCos==true)?FIXED_QUADR:0; return g_panCOSIN[(((i_nPointer%FIXED_BIAIS)+FIXED_BIAIS)%FIXED_BIAIS)+l_nShift]; }

/* COS 360  */ // inline double fcosdeg(double i_nAngleDeg) { return ((double) fcossin((int) ((i_nAngleDeg * FIXED_BIAIS) / 360.0)    ,  true)) / FIXED_MASK; }
/* COS 2PI  */ // inline double fcosrad(double i_nAngleRad) { return ((double) fcossin((int) ((i_nAngleRad * FIXED_BIAIS) / FIXED_2PI),  true)) / FIXED_MASK; }
/* COS ONE  */ // inline double fcosone(double i_nAngleOne) { return ((double) fcossin((int) ((i_nAngleOne * FIXED_BIAIS))            ,  true)) / FIXED_MASK; }
/* COS 1024 */ // inline double fcosbia(double i_nAngleBia) { return ((double) fcossin((int) ((i_nAngleBia))                          ,  true)) / FIXED_MASK; }
/* COS 100  */ // inline double fcospct(double i_nAnglePct) { return ((double) fcossin((int) ((i_nAnglePct * FIXED_BIAIS) / 100.0)    ,  true)) / FIXED_MASK; }

/* SIN 360  */ // inline double fsindeg(double i_nAngleDeg) { return ((double) fcossin((int) ((i_nAngleDeg * FIXED_BIAIS) / 360.0)    , false)) / FIXED_MASK; }
/* SIN 2PI  */ // inline double fsinrad(double i_nAngleRad) { return ((double) fcossin((int) ((i_nAngleRad * FIXED_BIAIS) / FIXED_2PI), false)) / FIXED_MASK; }
/* SIN ONE  */ // inline double fsinone(double i_nAngleOne) { return ((double) fcossin((int) ((i_nAngleOne * FIXED_BIAIS))            , false)) / FIXED_MASK; }
/* SIN 1024 */ // inline double fsinbia(double i_nAngleBia) { return ((double) fcossin((int) ((i_nAngleBia))                          , false)) / FIXED_MASK; }
/* SIN 100  */ // inline double fsinpct(double i_nAnglePct) { return ((double) fcossin((int) ((i_nAnglePct * FIXED_BIAIS) / 100.0)    , false)) / FIXED_MASK; }

#endif // !defined(AFX_FIXEDCOSIN_H__8E6A11E7_1F6A_4382_98F0_2A2AE4C26515__INCLUDED_)
