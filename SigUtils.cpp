// SigUtils.cpp: implementation of the SigUtils classes.
//
// 051012
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SigUtils.h"

#include "CPathSplit.h"

#include "math.h"
#include "FixedCoSin.h"

int IPOW(int x, int n)          {return (!n)?1:(n&1)?x*IPOW(x,n-1):IPOW(x*x,n>>1);}
int SQRT(int n)                 {int r=0,b,t; b=(n>=0x10000)?1<<30:1<<14; do{t=r+b; if(n>=t){n-=t; r=t+b;} r>>=1; b>>=2;}while(b); return r;}
int SHASH(const char* c, int s) {return (*c!=0)?SHASH(c+1,s+1)+(((*c|0x20)-'a'+1)*IPOW(26,s)): 0; }

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int ANGLE
( int i_nXd // Point 1
, int i_nYd
, int i_nXf // Point 2
, int i_nYf
)
{
  int   l_nDifX = (i_nXf - i_nXd) << 4;
  int   l_nDifY = (i_nYf - i_nYd) << 4;
  int   l_nNorm = SQRT(IPOW(l_nDifX, 2) + IPOW(l_nDifY, 2));
  short l_nSinA = (l_nDifY << 13) / l_nNorm;
  short l_nCosA = (l_nDifX << 13) / l_nNorm;

  short l_nMin;
  short l_nMed;
  short l_nMax;

  //

  l_nSinA -= (l_nCosA < 0)? 1 : 0; // Make sure Sin is negative even at 180 degrees

  l_nMin   = 1; // Start at quadrant 1
  l_nMin  += ((l_nSinA * l_nCosA) < 0)? 1 : 0; // Even quadrant (quadrant 2/4)
  l_nMin  += ( l_nSinA            < 0)? 2 : 0; // If more than 180 degrees, switch to quadrants 3-4
  l_nMin <<= 8;
  l_nMax   = l_nMin + 256 + 1; // LE +1 QUI FAIT LA DIFFERENCE : SANS CA, PAS DE BRAS, PAS DE CHOCOLAT !

  if(l_nSinA < 0)
  { // INC
    while(l_nMax > (l_nMin + 1))
    { // Enfin une routine dicho qui marche :)
      l_nMed = (l_nMin + l_nMax) / 2;

      if(g_panCOSIN[l_nMed] > l_nCosA)
      {
        l_nMax = l_nMed;
      }
      else
      {
        l_nMin = l_nMed;
      }
    }
  }
  else
  { // DEC
    while(l_nMax > (l_nMin + 1))
    { // Enfin une routine dicho qui marche :)
      l_nMed = (l_nMin + l_nMax) / 2;

      if(g_panCOSIN[l_nMed] < l_nCosA)
      {
        l_nMax = l_nMed;
      }
      else
      {
        l_nMin = l_nMed;
      }
    }
  }

  return (((l_nMax - 256) * 360) >> 10) % 360; // Use l_nMax (l_nMin + 1)
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
//#pragma float_control(except, off, push)
//#pragma float_control(precise, off)
double ATOD
( const char* i_poNumber
, double      i_nDefaultReturn // = 0.0
, BOOL        i_bStopOnError   // = FALSE
)
{
  double l_nInt = 0.0;
  double l_nRea = 1.0; // Divisor
  double l_nExp = 0.0;
  BOOL   l_bIntNeg = FALSE;
  BOOL   l_bExpNeg = FALSE;

  //

//  _controlfp(_PC_64, _MCW_PC);

  // +0123.456e-0789.0
  // A B  CD  EF G  HI

  if(i_poNumber != NULL)
  {
    if(*i_poNumber != 0)
    {
      while
      ( // Search ABCE
           (*i_poNumber != 0)
        && (*i_poNumber != '+') // A
        && (*i_poNumber != '-') // A
        && ((*i_poNumber < '1') || (*i_poNumber > '9')) // B : '1' avoid heading '0'
        && (*i_poNumber != '.') // C
        && ((*i_poNumber|0x20) != 'e') // E
      )
      { // Skip things such spaces and heading '0'
        i_poNumber += 1;
      }

      if(*i_poNumber == '-')
      { // Îf A : +(0123.456e-0789.0)
        l_bIntNeg = TRUE;
        i_poNumber += 1;
      }
      else{}

      while
      ( // Search BCE
           (*i_poNumber != 0)
        && ((*i_poNumber  < '1') || (*i_poNumber  > '9')) // B : '1' avoid heading '0'
        && (*i_poNumber != '.') // C
        && ((*i_poNumber|0x20) != 'e') // E
      )
      { // Should only skip heading '0'
        i_poNumber += 1;
      }

      while
      ( // While B : 123(.456e-0789.0)
           (*i_poNumber != 0)
        && (*i_poNumber >= '0') // Includes '0'
        && (*i_poNumber <= '9')
      )
      {
        l_nInt *= 10.0;
        l_nInt += (*i_poNumber - '0');
        i_poNumber += 1;
      }

      if(*i_poNumber == '.')
      { // If C : .(456e-0789.0)
        i_poNumber += 1;

        while
        ( // While D : 456(e-0789.0)
             (*i_poNumber != 0)
          && (*i_poNumber >= '0') // Includes '0'
          && (*i_poNumber <= '9')
        )
        {
          l_nRea /= 10.0;
          l_nInt += ((*i_poNumber - '0') * l_nRea);
          i_poNumber += 1;
        }
      }
      else{}

      if((*i_poNumber|0x20) == 'e')
      { // Îf E : e(-0789.0)
        i_poNumber += 1; // Skip E

        if(*i_poNumber == '-')
        { // Îf F : -(0789.0)
          l_bExpNeg = TRUE;
          i_poNumber += 1;
        }
        else{}

        while
        ( // Search GH
             (*i_poNumber != 0)
          && ((*i_poNumber  < '1') || (*i_poNumber  > '9')) // G : '1' avoid heading '0'
          && (*i_poNumber != '.') // H
        )
        { // Should only skip heading '0'
          i_poNumber += 1;
        }

        while
        ( // While G : 789(.0)
             (*i_poNumber != 0)
          && (*i_poNumber >= '0') // Includes '0'
          && (*i_poNumber <= '9')
        )
        {
          l_nExp *= 10.0;
          l_nExp += (*i_poNumber - '0');
          i_poNumber += 1;
        }

        if(*i_poNumber == '.')
        { // Îf H : .(0)
          l_nRea = 1.0; // Reset divisor
          i_poNumber += 1;
        }
        else{}

        while
        ( // While I : 0
             (*i_poNumber != 0)
          && (*i_poNumber >= '0') // Includes '0'
          && (*i_poNumber <= '9')
        )
        {
          l_nRea /= 10.0;
          l_nExp += ((*i_poNumber - '0') * l_nRea);
          i_poNumber += 1;
        }
      }
      else{}
    }
    else{}

    if
    ( 
         (i_bStopOnError == TRUE) 
      && (*i_poNumber    != 0)
    )
    {
      return 0.0; // Gonna sleeping
    }
    else
    { // If string finished, then it is valid ;)
//      _controlfp(_RC_DOWN, _MCW_PC);

      return
      (
          l_nInt // Number
        * (l_bIntNeg ? (-1.0) : (+1.0)) // Sign
        * ((l_nExp == 0.0)
        ? 1.0 // Avoid pow usage when not necessary
        : pow    // Exponent
          ( 10.0
          ,   l_nExp
            * (l_bExpNeg ? (-1.0) : (+1.0))
          ))
      );
    }
  }
  else
  {
    return i_nDefaultReturn;
  }
}
//#pragma float_control(precise, off, pop)

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int ATOL
( const char* i_poNumber
, int         i_nDefaultReturn // = 0
, BOOL        i_bStopOnError   // = FALSE
)
{
  int  l_nInt    = 0;
  int  l_nRea    = 0;
  int  l_nExp    = 0;
  int  l_nRdn    = 1; // Multiplicator
  BOOL l_bIntNeg = FALSE;
  BOOL l_bExpNeg = FALSE;

  //

  // +0123.456e-0789.0
  // A B  CD  EF G  HI

  if(i_poNumber != NULL)
  {
    if(*i_poNumber != 0)
    {
      while
      ( // Search ABCE
           (*i_poNumber != 0)
        && (*i_poNumber != '+') // A
        && (*i_poNumber != '-') // A
        && ((*i_poNumber < '1') || (*i_poNumber > '9')) // B : '1' avoid heading '0'
        && (*i_poNumber != '.') // C
        && ((*i_poNumber|0x20) != 'e') // E
      )
      { // Skip things such spaces and heading '0'
        i_poNumber += 1;
      }

      if(*i_poNumber == '-')
      { // Îf A : +(0123.456e-0789.0)
        l_bIntNeg = TRUE;
        i_poNumber += 1;
      }
      else{}

      while
      ( // Search BCE
           (*i_poNumber != 0)
        && ((*i_poNumber  < '1') || (*i_poNumber  > '9')) // B : '1' avoid heading '0'
        && (*i_poNumber != '.') // C
        && ((*i_poNumber|0x20) != 'e') // E
      )
      { // Should only skip heading '0'
        i_poNumber += 1;
      }

      while
      ( // While B : 123(.456e-0789.0)
           (*i_poNumber != 0)
        && (*i_poNumber >= '0') // Includes '0'
        && (*i_poNumber <= '9')
      )
      {
        l_nInt *= 10;
        l_nInt += (*i_poNumber - '0');
        i_poNumber += 1;
      }

      if(*i_poNumber == '.')
      { // If C : .(456e-0789.0)
        i_poNumber += 1;

        while
        ( // While D : 456(e-0789.0)
             (*i_poNumber != 0)
          && (*i_poNumber >= '0') // Includes '0'
          && (*i_poNumber <= '9')
        )
        {
          l_nRea *= 10;
          l_nRea += (*i_poNumber - '0');
          l_nRdn *= 10;
          i_poNumber += 1;
        }
      }
      else{}

      if((*i_poNumber|0x20) == 'e')
      { // Îf E : e(-0789.0)
        i_poNumber += 1; // Skip E

        if(*i_poNumber == '-')
        { // Îf F : -(0789.0)
          l_bExpNeg = TRUE;
          i_poNumber += 1;
        }
        else{}

        while
        ( // Search GH
             (*i_poNumber != 0)
          && ((*i_poNumber  < '1') || (*i_poNumber  > '9')) // G : '1' avoid heading '0'
          && (*i_poNumber != '.') // H
        )
        { // Should only skip heading '0'
          i_poNumber += 1;
        }

        while
        ( // While G : 789(.0)
             (*i_poNumber != 0)
          && (*i_poNumber >= '0') // Includes '0'
          && (*i_poNumber <= '9')
        )
        {
          l_nExp *= 10;
          l_nExp += (*i_poNumber - '0');
          i_poNumber += 1;
        }
      }
      else{}
    }
    else{}

    if
    ( 
         (i_bStopOnError == TRUE) 
      && (*i_poNumber    != 0)
    )
    {
      return 0; // Gonna sleeping
    }
    else
    { // If string finished, then it is valid ;)
      int l_nReturn
      = l_nInt // Number
      * l_nRdn
      + l_nRea
      ;

      if(l_bExpNeg == TRUE)
      {
        while(l_nExp > 0)
        {
          l_nReturn /= 10;
          l_nExp -= 1;
        }
      }
      else
      {
        while(l_nExp > 0)
        {
          l_nReturn *= 10;
          l_nExp -= 1;
        }
      }

      return (int) (l_nReturn / l_nRdn) * ((l_bIntNeg ? (-1) : (+1)));
    }
  }
  else
  {
    return i_nDefaultReturn;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int ATOI
( const char* i_poNumber
, int         i_nDefaultReturn // = 0
, BOOL        i_bStopOnError   // = FALSE
)
{
  int  l_nInt    = 0;
  BOOL l_bIntNeg = FALSE;

  const char* l_panTruc = i_poNumber;

  //

  // +0123
  // A B

  if(i_poNumber != NULL)
  {
    if(*i_poNumber != 0)
    {
      while
      ( // Search AB
           (*i_poNumber != 0)
        && (*i_poNumber != '+') // A
        && (*i_poNumber != '-') // A
        && ((*i_poNumber < '1') || (*i_poNumber > '9')) // B : '1' avoid heading '0'
      )
      { // Skip things such spaces and heading '0'
        i_poNumber += 1;
      }

      if(*i_poNumber == '-')
      { // Îf A : +(0123)
        l_bIntNeg = TRUE;
        i_poNumber += 1;
      }
      else{}

      while
      ( // Search B
           (*i_poNumber != 0)
        && ((*i_poNumber  < '1') || (*i_poNumber  > '9')) // B : '1' avoid heading '0'
      )
      { // Should only skip heading '0'
        i_poNumber += 1;
      }

      while
      ( // Îf B : 123()
           (*i_poNumber != 0)
        && (*i_poNumber >= '0') // Includes '0'
        && (*i_poNumber <= '9')
      )
      {
        l_nInt *= 10;
        l_nInt += (*i_poNumber - '0');
        i_poNumber += 1;
      }
    }
    else{}

    if
    ( 
         (i_bStopOnError == TRUE) 
      && (*i_poNumber    != 0)
    )
    {
      return 0; // Gonna sleeping
    }
    else
    { // If string finished, then it is valid ;)
      return (int)
      (
          l_nInt // Number
      ) * (l_bIntNeg ? (-1) : (+1)); // Sign
    }
  }
  else
  {
    return i_nDefaultReturn;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int ATOH
( const char* i_poNumber
, int         i_nDefaultReturn // = 0
, BOOL        i_bStopOnError   // = FALSE
)
{
  int  l_nInt    = 0;
  BOOL l_bIntNeg = FALSE;
  BOOL l_bIntDec = FALSE;
  BOOL l_bIntHex = FALSE;

  const char* l_panTruc = i_poNumber;

  //

  // +0123ABC
  // A B

  if(i_poNumber != NULL)
  {
    if(*i_poNumber != 0)
    {
      while
      ( // Search AB
           (*i_poNumber != 0)
        && (*i_poNumber != '+') // A
        && (*i_poNumber != '-') // A
        && ((*i_poNumber        < '1') || (*i_poNumber        > '9')) // B : '1' avoid heading '0'
        && (((*i_poNumber|0x20) < 'a') || ((*i_poNumber|0x20) > 'f')) // B : hexadecimal digits
      )
      { // Skip things such spaces and heading '0'
        i_poNumber += 1;
      }

      if(*i_poNumber == '-')
      { // Îf A : +(0123ABC)
        l_bIntNeg = TRUE;
        i_poNumber += 1;
      }
      else{}

      while
      ( // Search B
           (*i_poNumber != 0)
        && ((*i_poNumber        < '1') || (*i_poNumber        > '9')) // B : '1' avoid heading '0'
        && (((*i_poNumber|0x20) < 'a') || ((*i_poNumber|0x20) > 'f')) // B : hexadecimal digits
      )
      { // Should only skip heading '0'
        i_poNumber += 1;
      }

      while
      ( // Îf B : 123ABC()
           (*i_poNumber != 0)
        && ((l_bIntDec = ((*i_poNumber        >= '0') && (*i_poNumber        <= '9'))) == TRUE)
        || ((l_bIntHex = (((*i_poNumber|0x20) >= 'a') && ((*i_poNumber|0x20) <= 'f'))) == TRUE)
      )
      {
        l_nInt <<= 4;

        if(l_bIntDec == TRUE)
        { // Decimal
          l_nInt += (*i_poNumber - '0');
        }
        else
        { // Hexadecimal
          l_nInt += ((*i_poNumber | 0x20) - 'a' + 10);
        }

        i_poNumber += 1;
      }
    }
    else{}

    if
    ( 
         (i_bStopOnError == TRUE) 
      && (*i_poNumber    != 0)
    )
    {
      return 0; // Gonna sleeping
    }
    else
    { // If string finished, then it is valid ;)
      return (int)
      (
          l_nInt // Number
      ) * (l_bIntNeg ? (-1) : (+1)); // Sign
    }
  }
  else
  {
    return i_nDefaultReturn;
  }
}

//#define dRACC_DICHO
//#define dRACC_LOOKUP

#if defined(dRACC_DICHO) && defined(dRACC_LOOKUP)
char g_anAccent[] = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
#endif // (dRACC_DICHO && dRACC_LOOKUP)
char g_anNormal[] = "AAAAAAACEEEEIIIIDNOOOOOXOUUUUYPBaaaaaaaceeeeiiiidnoooooxouuuuypy";

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
#ifdef dRACC_DICHO
char DICHO
( char  i_nMin
, char  i_nMax
, char  i_nTst
#ifdef dRACC_LOOKUP
, char* i_panTable
#endif // dRACC_LOOKUP
)
{
  register char l_nMin;
  register char l_nMed;
  register char l_nMax;

  //

  l_nMin = i_nMin;
  l_nMax = i_nMax + 1; // LE +1 QUI FAIT LA DIFFERENCE : SANS CA, PAS DE BRAS, PAS DE CHOCOLAT !

  while(l_nMax > (l_nMin + 1))
  { // Enfin une routine dicho qui marche :)
    l_nMed = (l_nMin + l_nMax) >> 1;
#ifdef dRACC_LOOKUP
    if(i_panTable[l_nMed - i_nMin] > i_nTst) // Look-up table, un peu lent mais nécessaire sur les plages non contigus
#else
    if(l_nMed > i_nTst) // Les caractères sont contigus, l_nMed représente déjà le caractère de référence
#endif // dRACC_LOOKUP
    {
      l_nMax = l_nMed;
    }
    else
    {
      l_nMin = l_nMed;
    }
  }

  return l_nMin;
}
#endif // dRACC_DICHO

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
char* RACC(char* io_panString, BOOL i_bLower)
{ // Enlève les accents (et passe en minuscule) : ATTENTION - TRES RAPIDE !
  register char l_nChr = *io_panString;

  char* l_panString = io_panString;

  while(l_nChr != 0)
  {
    if
    (
         (l_nChr >= 'À') // -64 / 192
      && (l_nChr <= 'ÿ') // -1  / 255
    )
    { // Si c'est dans la plage internationale
#ifdef dRACC_DICHO
      *io_panString
      = g_anNormal
        [ DICHO
          ( 'À'
          , 'ÿ'
          , *io_panString
#ifdef dRACC_LOOKUP
          , g_anAccent
#endif // dRACC_LOOKUP
          )
        - 'À'
        ]
      ;
#else
      // On récupère direct dans la table, vu qu'elle est contigue :)
      *io_panString = g_anNormal[*io_panString - 'À'];
#endif // dRACC_DICHO

      if(i_bLower == TRUE)
      { // On retourne le caractère non accentué
        *io_panString |= 0x20;
      }
      else{}
    }
    else
    {
      if
      (
           (i_bLower == TRUE)
        && (l_nChr >= 'A')
        && (l_nChr <= 'Z')
      )
      { // Si c'est une lettre majuscule et que l'on passe en minuscule
        l_nChr        |= 0x20;
        *io_panString  = l_nChr;
      }
      else{}
    }

    io_panString += 1; // Caractère suivant
    l_nChr        = *io_panString;
  }

  return l_panString;
}

// === COMPARAISON DE CHAINE ==========================================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
char SCMP
( const char* i_panString
, const char* i_panCompare
#ifdef EXTENDCMP
, BOOL  i_bLower  // = FALSE
, BOOL  i_bAccent // = FALSE
#endif // EXTENDCMP
, int   i_nCharToCompare // = 0
)
{
#ifdef EXTENDCMP
  register char l_nString  = 0;
  register char l_nCompare = 0;
#endif // EXTENDCMP

  while
  (
       (i_nCharToCompare > 0)
//    && (*i_panString  != 0)
//    && (*i_panCompare != 0)
  )
  {
#ifdef EXTENDCMP
    l_nString  = *i_panString;
    l_nCompare = *i_panCompare;

    if(i_bAccent == TRUE)
    {
      if
      (
           (l_nString >= 'À') // -64 / 192
        && (l_nString <= 'ÿ') // -1  / 255
      )
      {
#ifdef dRACC_DICHO
        l_nString
        = g_anNormal
          [ DICHO
            ( 'À'
            , 'ÿ'
            , l_nString
#ifdef dRACC_LOOKUP
            , g_anAccent
#endif // dRACC_LOOKUP
            )
          - 'À'
          ]
        ;
#else
        // On récupère direct dans la table, vu qu'elle est contigue :)
        l_nString = g_anNormal[l_nString - 'À'];
#endif // dRACC_DICHO
      }
      else{}

      if
      (
           (l_nCompare >= 'À') // -64 / 192
        && (l_nCompare <= 'ÿ') // -1  / 255
      )
      {
#ifdef dRACC_DICHO
        l_nCompare
        = g_anNormal
          [ DICHO
            ( 'À'
            , 'ÿ'
            , l_nCompare
#ifdef dRACC_LOOKUP
            , g_anAccent
#endif // dRACC_LOOKUP
            )
          - 'À'
          ]
        ;
#else
        // On récupère direct dans la table, vu qu'elle est contigue :)
        l_nCompare = g_anNormal[l_nCompare - 'À'];
#endif // dRACC_DICHO
      }
      else{}
    }
    else{}

    if(i_bLower == TRUE)
    {
      if
      (
           (l_nString >= 'A')
        && (l_nString <= 'Z')
      )
      {
        l_nString |= 0x20;
      }
      else{}

      if
      (
           (l_nCompare >= 'A')
        && (l_nCompare <= 'Z')
      )
      {
        l_nCompare |= 0x20;
      }
      else{}
    }
    else{}

    if(l_nString != l_nCompare)
#else
    if(*i_panString != *i_panCompare)
#endif // EXTENDCMP
    { // Different, quit testing any further
      break;
    }
    else{}

    i_panString      += 1;
    i_panCompare     += 1;
    i_nCharToCompare -= 1;
  }

#ifdef EXTENDCMP
  return l_nString - l_nCompare;
#else
  return (*i_panString - *i_panCompare);
#endif // EXTENDCMP
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL WCMP
( char* i_panWild
, char* i_panString
#ifdef EXTENDCMP
, BOOL i_bLower  // = FALSE
, BOOL i_bAccent // = FALSE
#endif // EXTENDCMP
)
{ // 3750 ms pour : for(int x = 0; x < 9999999; x += 1) WCMP("*t?st?n*this*t*", "testing this shit");
  char* l_pnWild;
  char* l_pnString;
  
#ifdef EXTENDCMP
  register char l_nWild;
  register char l_nString;
#endif // EXTENDCMP

  while
  (
       (*i_panString != 0)
    && (*i_panWild   != '*')
  )
  {
#ifdef EXTENDCMP
    l_nWild   = *i_panWild;
    l_nString = *i_panString;

    if(i_bAccent == TRUE)
    {
      if
      (
           (l_nWild >= 'À') // -64 / 192
        && (l_nWild <= 'ÿ') // -1  / 255
      )
      {
#ifdef dRACC_DICHO
        l_nWild
        = g_anNormal
          [ DICHO
            ( 'À'
            , 'ÿ'
            , l_nWild
#ifdef dRACC_LOOKUP
            , g_anAccent
#endif // dRACC_LOOKUP
            )
          - 'À'
          ]
        ;
#else
        // On récupère direct dans la table, vu qu'elle est contigue :)
        l_nWild = g_anNormal[l_nWild - 'À'];
#endif // dRACC_DICHO
      }
      else{}

      if
      (
           (l_nString >= 'À') // -64 / 192
        && (l_nString <= 'ÿ') // -1  / 255
      )
      {
#ifdef dRACC_DICHO
        l_nString
        = g_anNormal
          [ DICHO
            ( 'À'
            , 'ÿ'
            , l_nString
#ifdef dRACC_LOOKUP
            , g_anAccent
#endif // dRACC_LOOKUP
            )
          - 'À'
          ]
        ;
#else
        // On récupère direct dans la table, vu qu'elle est contigue :)
        l_nString = g_anNormal[l_nString - 'À'];
#endif // dRACC_DICHO
      }
      else{}
    }
    else{}

    if(i_bLower == TRUE)
    {
      if
      (
           (l_nWild >= 'A')
        && (l_nWild <= 'Z')
      )
      {
        l_nWild |= 0x20;
      }
      else{}

      if
      (
           (l_nString >= 'A')
        && (l_nString <= 'Z')
      )
      {
        l_nString |= 0x20;
      }
      else{}
    }
    else{}

    if
    (
         (l_nWild != l_nString)
      && (l_nWild != '?')
    )
#else
    if
    (
         (*i_panWild != *i_panString)
      && (*i_panWild != '?')
    )
#endif // EXTENDCMP
    {
      return FALSE;
    }
    else
    {
      i_panWild   += 1;
      i_panString += 1;
    }
  }

  while(*i_panString != 0)
  {
    if(*i_panWild == '*')
    {
      i_panWild += 1;

      if(*i_panWild == 0)
      {
        return TRUE;
      }
      else
      {
        l_pnWild   = i_panWild;
        l_pnString = i_panString + 1;
      }
    }
    else
    {
#ifdef EXTENDCMP
      l_nWild   = *i_panWild;
      l_nString = *i_panString;

      if(i_bAccent == TRUE)
      {
        if
        (
             (l_nWild >= 'À') // -64 / 192
          && (l_nWild <= 'ÿ') // -1  / 255
        )
        {
#ifdef dRACC_DICHO
          l_nWild
          = g_anNormal
            [ DICHO
              ( 'À'
              , 'ÿ'
              , l_nWild
#ifdef dRACC_LOOKUP
              , g_anAccent
#endif // dRACC_LOOKUP
              )
            - 'À'
            ]
          ;
#else
          // On récupère direct dans la table, vu qu'elle est contigue :)
          l_nWild = g_anNormal[l_nWild - 'À'];
#endif // dRACC_DICHO
        }
        else{}

        if
        (
             (l_nString >= 'À') // -64 / 192
          && (l_nString <= 'ÿ') // -1  / 255
        )
        {
#ifdef dRACC_DICHO
          l_nString
          = g_anNormal
            [ DICHO
              ( 'À'
              , 'ÿ'
              , l_nString
#ifdef dRACC_LOOKUP
              , g_anAccent
#endif // dRACC_LOOKUP
              )
            - 'À'
            ]
          ;
#else
          // On récupère direct dans la table, vu qu'elle est contigue :)
          l_nString = g_anNormal[l_nString - 'À'];
#endif // dRACC_DICHO
        }
        else{}
      }
      else{}

      if(i_bLower == TRUE)
      {
        if
        (
             (l_nWild >= 'A')
          && (l_nWild <= 'Z')
        )
        {
          l_nWild |= 0x20;
        }
        else{}

        if
        (
             (l_nString >= 'A')
          && (l_nString <= 'Z')
        )
        {
          l_nString |= 0x20;
        }
        else{}
      }
      else{}

      if
      (
           (l_nWild == l_nString)
        || (l_nWild == '?')
      )
#else
      if
      (
           (*i_panWild == *i_panString)
        || (*i_panWild == '?')
      )
#endif // EXTENDCMP
      {
        i_panWild   += 1;
        i_panString += 1;
      }
      else
      {
        i_panWild   = l_pnWild;
        i_panString = l_pnString;

        l_pnString += 1;
      }
    }
  }

  while(*i_panWild == '*')
  {
    i_panWild += 1;
  }

  return (*i_panWild == 0);
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
// Fonction récursive qui fait le même travail que WCMP, mais 'juste' 2.74 fois plus lentement !
BOOL WRCMP
( const char* i_panWild
, const char* i_panString
#ifdef EXTENDCMP
, BOOL i_bLower  // = FALSE
, BOOL i_bAccent // = FALSE
#endif // EXTENDCMP
)
{ // 10281 ms pour : for(int y = 0; y < 9999999; y += 1) WRCMP("*t?st?n*this*t*", "testing this shit");
#ifdef EXTENDCMP
  register char l_nWild;
  register char l_nString;

  l_nWild   = *i_panWild;
  l_nString = *i_panString;

  if(i_bAccent == TRUE)
  {
    if
    (
         (l_nWild >= 'À') // -64 / 192
      && (l_nWild <= 'ÿ') // -1  / 255
    )
    {
#ifdef dRACC_DICHO
      l_nWild
      = g_anNormal
        [ DICHO
          ( 'À'
          , 'ÿ'
          , l_nWild
#ifdef dRACC_LOOKUP
          , g_anAccent
#endif // dRACC_LOOKUP
          )
        - 'À'
        ]
      ;
#else
      // On récupère direct dans la table, vu qu'elle est contigue :)
      l_nWild = g_anNormal[l_nWild - 'À'];
#endif // dRACC_DICHO
    }
    else{}

    if
    (
         (l_nString >= 'À') // -64 / 192
      && (l_nString <= 'ÿ') // -1  / 255
    )
    {
#ifdef dRACC_DICHO
      l_nString
      = g_anNormal
        [ DICHO
          ( 'À'
          , 'ÿ'
          , l_nString
#ifdef dRACC_LOOKUP
          , g_anAccent
#endif // dRACC_LOOKUP
          )
        - 'À'
        ]
      ;
#else
      // On récupère direct dans la table, vu qu'elle est contigue :)
      l_nString = g_anNormal[l_nString - 'À'];
#endif // dRACC_DICHO
    }
    else{}
  }
  else{}

  if(i_bLower == TRUE)
  {
    if
    (
         (l_nWild >= 'A')
      && (l_nWild <= 'Z')
    )
    {
      l_nWild |= 0x20;
    }
    else{}

    if
    (
         (l_nString >= 'A')
      && (l_nString <= 'Z')
    )
    {
      l_nString |= 0x20;
    }
    else{}
  }
  else{}

  if(l_nWild == l_nString)
#else
  if(*i_panWild == *i_panString)
#endif // EXTENDCMP
  {
    i_panWild   += 1;
    i_panString += 1;

    return ((*i_panString == 0) || (WRCMP(i_panWild, i_panString)));
  }
  else
  {
    if(*i_panString == 0)
    {
      i_panWild += 1;

      return ((*i_panWild == '*') && (WRCMP(i_panWild, i_panString)));
    }
    else
    {
      switch(*i_panWild)
      {
        case '?':
          i_panWild   += 1;
          i_panString += 1;

          return WRCMP(i_panWild, i_panString);
          break; // NEVER USED DUE TO THE PREVIOUS RETURN
        case '*':
          i_panWild += 1;

          if(*i_panWild == 0)
          {
            return TRUE;
          }
          else{}
    
          while(*i_panString != 0)
          {
            if(WRCMP(i_panWild, i_panString) == TRUE)
            {
              return TRUE;
            }
            else{}

            i_panString += 1;
          }
    
        default:
          return FALSE;
      }
    }
  }
}

// === COPIE DE MEMOIRE ===============================================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void MEMCPY
( void* o_panBufferOut
, void* i_panBufferIn
, int   i_nBufferSize
, BOOL  i_bCopyForward // = TRUE
)
{
  char* l_panBufferOut = (char*) o_panBufferOut;
  char* l_panBufferIn  = (char*) i_panBufferIn;
  int   l_nSrc;
  int   l_nDst;
  int   l_nLoop;

  //

  if
  (
       (l_panBufferOut != l_panBufferIn)
    && (i_nBufferSize > 0)
  )
  { // Makes sure there is something to do (most case)
#ifdef DEBUGSTUFF // SigUtils.h
    if(i_nBufferSize <= 4)
    { // Put a breakpoint here to test size LE 4
      i_nBufferSize = i_nBufferSize;
    }
    else{}
#endif // DEBUGSTUFF

    if(i_bCopyForward == TRUE)
    { // FORWARD COPY
      l_nSrc = (int) l_panBufferIn  & 0x07;
      l_nDst = (int) l_panBufferOut & 0x07;

      switch(l_nSrc)
      { // PRE COPY ODD - try to switch on an EVEN boundary
        case 1 : // ODD  : CHAR
        case 3 : // ODD  : CHAR
        case 5 : // ODD  : CHAR
        case 7 : // ODD  : CHAR
          switch(l_nDst)
          {
            case 1 : // ODD  : CHAR
            case 3 : // ODD  : CHAR
            case 5 : // ODD  : CHAR
            case 7 : // ODD  : CHAR
              if(i_nBufferSize >= 1)
              {
                *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                i_nBufferSize -= 1;
              }
              else{}

              l_nSrc = (int) l_panBufferIn  & 0x07;
              l_nDst = (int) l_panBufferOut & 0x07;
          }
      }

      if(i_nBufferSize > 0)
      {
        switch(l_nSrc)
        { // PRE COPY EVEN - try to switch on an INT boundary
          case 2 : // EVEN : SHORT
          case 6 : // EVEN : SHORT
            switch(l_nDst)
            {
              case 2 : // EVEN : SHORT
              case 6 : // EVEN : SHORT
                if(i_nBufferSize >= 2)
                {
                  *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                  i_nBufferSize -= 2;
                }
                else{}

                l_nSrc = (int) l_panBufferIn  & 0x07;
                l_nDst = (int) l_panBufferOut & 0x07;
            }
        }

        if(i_nBufferSize > 0)
        {
          switch(l_nSrc)
          { // PRE COPY EVEN - try to switch on an HYPER boundary
            case 4 : // EVEN : INT
              switch(l_nDst)
              {
                case 0 : // EVEN : INT
                case 4 : // EVEN : INT
                  if(i_nBufferSize >= 4)
                  {
                    *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                    i_nBufferSize -= 4;
                  }
                  else{}

                  l_nSrc = (int) l_panBufferIn  & 0x07;
                  l_nDst = (int) l_panBufferOut & 0x07;
              }
          }

          if(i_nBufferSize > 0)
          {
            switch(l_nSrc)
            { // POST COPY
              case 0 : // EVEN : HYPER
                switch(l_nDst)
                {
                  case 0 : // EVEN : HYPER
                    l_nLoop = i_nBufferSize >> 6; // / 64
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 6); // * 64
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      { // AVOID CACHE MISS
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                      }
                    }
                    else{}

                    l_nLoop = i_nBufferSize >> 3; // / 8
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 3); // * 8
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      {
                        *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn); l_panBufferOut += 8; l_panBufferIn += 8;
                      }
                    }
                    else{}

                    l_nSrc = (int) l_panBufferIn  & 0x07;
                    l_nDst = (int) l_panBufferOut & 0x07;
                }
              case 4 : // EVEN : INT
                switch(l_nDst)
                {
                  case 0 : // EVEN : HYPER
                  case 4 : // EVEN : INT
                    l_nLoop = i_nBufferSize >> 5; // / 32
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 5); // * 32
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      { // AVOID CACHE MISS
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                      }
                    }
                    else{}

                    l_nLoop = i_nBufferSize >> 2; // / 4
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 2); // * 4
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      {
                        *((int*) l_panBufferOut) = *((int*) l_panBufferIn); l_panBufferOut += 4; l_panBufferIn += 4;
                      }
                    }
                    else{}

                    l_nSrc = (int) l_panBufferIn  & 0x07;
                    l_nDst = (int) l_panBufferOut & 0x07;
                }
              case 2 : // EVEN : SHORT
              case 6 : // EVEN : SHORT
                switch(l_nDst)
                {
                  case 0 : // EVEN : HYPER
                  case 2 : // EVEN : SHORT
                  case 4 : // EVEN : INT
                  case 6 : // EVEN : SHORT
                    l_nLoop = i_nBufferSize >> 4; // / 16
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 4); // * 16
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      { // AVOID CACHE MISS
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                      }
                    }
                    else{}

                    l_nLoop = i_nBufferSize >> 1; // / 2
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 1); // * 2
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      {
                        *((short*) l_panBufferOut) = *((short*) l_panBufferIn); l_panBufferOut += 2; l_panBufferIn += 2;
                      }
                    }
                    else{}

                    l_nSrc = (int) l_panBufferIn  & 0x07;
                    l_nDst = (int) l_panBufferOut & 0x07;
                }
              case 1 : // ODD  : CHAR
              case 3 : // ODD  : CHAR
              case 5 : // ODD  : CHAR
              case 7 : // ODD  : CHAR
              default :
                l_nLoop = i_nBufferSize >> 3; // / 8
                if(l_nLoop > 0)
                {
                  i_nBufferSize -= (l_nLoop << 3); // * 8
                  for
                  ( // INIT JUST ABOVE
                  ; l_nLoop  > 0
                  ; l_nLoop -= 1
                  )
                  { // AVOID CACHE MISS
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                    *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                  }
                }
                else{}

                while(i_nBufferSize > 0)
                { // LAST DROPS OF BYTE
                  *((char*) l_panBufferOut) = *((char*) l_panBufferIn); l_panBufferOut += 1; l_panBufferIn += 1;
                  i_nBufferSize  -= 1;
                }
            }
          }
        }
      }
    }
    else
    { // BACKWARD COPY
      l_panBufferOut += i_nBufferSize; // Start from the tail
      l_panBufferIn  += i_nBufferSize;

      l_nSrc = (int) l_panBufferIn  & 0x07;
      l_nDst = (int) l_panBufferOut & 0x07;

      switch(l_nSrc)
      { // PRE COPY ODD - try to switch on a EVEN boundary
        case 1 : // ODD  : CHAR
        case 3 : // ODD  : CHAR
        case 5 : // ODD  : CHAR
        case 7 : // ODD  : CHAR
          switch(l_nDst)
          {
            case 1 : // ODD  : CHAR
            case 3 : // ODD  : CHAR
            case 5 : // ODD  : CHAR
            case 7 : // ODD  : CHAR
              if(i_nBufferSize >= 1)
              {
                l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                i_nBufferSize  -= 1;
              }
              else{}

              l_nSrc = (int) l_panBufferIn  & 0x07;
              l_nDst = (int) l_panBufferOut & 0x07;
          }
      }

      if(i_nBufferSize > 0)
      {
        switch(l_nSrc)
        { // PRE COPY EVEN - try to switch on a INT boundary
          case 2 : // EVEN : SHORT
          case 6 : // EVEN : SHORT
            switch(l_nDst)
            {
              case 2 : // EVEN : SHORT
              case 6 : // EVEN : SHORT
                if(i_nBufferSize >= 2)
                {
                  l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                  i_nBufferSize  -= 2;
                }
                else{}

                l_nSrc = (int) l_panBufferIn  & 0x07;
                l_nDst = (int) l_panBufferOut & 0x07;
            }
        }

        if(i_nBufferSize > 0)
        {
          switch(l_nSrc)
          { // PRE COPY EVEN - try to switch on a HYPER boundary
            case 4 : // EVEN : INT
              switch(l_nDst)
              {
                case 0 : // EVEN : INT
                case 4 : // EVEN : INT
                  if(i_nBufferSize >= 4)
                  {
                    l_panBufferOut -= 4; l_panBufferIn -= 4; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                    i_nBufferSize  -= 4;
                  }
                  else{}

                  l_nSrc = (int) l_panBufferIn  & 0x07;
                  l_nDst = (int) l_panBufferOut & 0x07;
              }
          }

          if(i_nBufferSize > 0)
          {
            switch(l_nSrc)
            { // POST COPY
              case 0 : // EVEN : HYPER
                switch(l_nDst)
                {
                  case 0 : // EVEN : HYPER
                    l_nLoop = i_nBufferSize >> 6; // / 64
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 6); // * 64
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      { // AVOID CACHE MISS
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                      }
                    }
                    else{}

                    l_nLoop = i_nBufferSize >> 3; // / 8
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 3); // * 8
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      {
                        l_panBufferOut -= 8; l_panBufferIn -= 8; *((hyper*) l_panBufferOut) = *((hyper*) l_panBufferIn);
                      }
                    }
                    else{}

                    l_nSrc = (int) l_panBufferIn  & 0x07;
                    l_nDst = (int) l_panBufferOut & 0x07;
                }
              case 4 : // EVEN : INT
                switch(l_nDst)
                {
                  case 0 : // EVEN : HYPER
                  case 4 : // EVEN : INT
                    l_nLoop = i_nBufferSize >> 5; // / 32
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 5); // * 32
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      { // AVOID CACHE MISS
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                      }
                    }
                    else{}

                    l_nLoop = i_nBufferSize >> 2; // / 4
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 2); // * 4
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      {
                        l_panBufferOut -= 4; l_panBufferIn -= 4; *((int*) l_panBufferOut) = *((int*) l_panBufferIn);
                      }
                    }
                    else{}

                    l_nSrc = (int) l_panBufferIn  & 0x07;
                    l_nDst = (int) l_panBufferOut & 0x07;
                }
              case 2 : // EVEN : SHORT
              case 6 : // EVEN : SHORT
                switch(l_nDst)
                {
                  case 0 : // EVEN : HYPER
                  case 2 : // EVEN : SHORT
                  case 4 : // EVEN : INT
                  case 6 : // EVEN : SHORT
                    l_nLoop = i_nBufferSize >> 4; // / 16
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 4); // * 16
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      { // AVOID CACHE MISS
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                      }
                    }
                    else{}

                    l_nLoop = i_nBufferSize >> 1; // / 2
                    if(l_nLoop > 0)
                    {
                      i_nBufferSize -= (l_nLoop << 1); // * 2
                      for
                      ( // INIT JUST ABOVE
                      ; l_nLoop  > 0
                      ; l_nLoop -= 1
                      )
                      {
                        l_panBufferOut -= 2; l_panBufferIn -= 2; *((short*) l_panBufferOut) = *((short*) l_panBufferIn);
                      }
                    }
                    else{}

                    l_nSrc = (int) l_panBufferIn  & 0x07;
                    l_nDst = (int) l_panBufferOut & 0x07;
                }
              case 1 : // ODD  : CHAR
              case 3 : // ODD  : CHAR
              case 5 : // ODD  : CHAR
              case 7 : // ODD  : CHAR
              default :
                l_nLoop = i_nBufferSize >> 3; // / 8
                if(l_nLoop > 0)
                {
                  i_nBufferSize -= (l_nLoop << 3); // * 8
                  for
                  ( // INIT JUST ABOVE
                  ; l_nLoop  > 0
                  ; l_nLoop -= 1
                  )
                  { // AVOID CACHE MISS
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                    l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                  }
                }
                else{}

                while(i_nBufferSize > 0)
                { // LAST DROPS OF BYTE
                  l_panBufferOut -= 1; l_panBufferIn  -= 1; *((char*) l_panBufferOut) = *((char*) l_panBufferIn);
                  i_nBufferSize  -= 1;
                }
            }
          }
        }
      }
    } // FORWARD vs BACKWARD
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void MEMMOVE
( void* o_panBufferOut
, void* i_panBufferIn
, int   i_nBufferSize
)
{
  MEMCPY
  ( o_panBufferOut
  , i_panBufferIn
  , i_nBufferSize
  , (o_panBufferOut < i_panBufferIn) // Forward copy if destination BEFORE source
  );
}

// ============================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CRC32::CRC32()
{
  ULONG l_nPolynomial = 0x04C11DB7;
  int   l_nLoopX;
  int   l_nLoopY;

  for
  ( l_nLoopY  = 0
  ; l_nLoopY <  256
  ; l_nLoopY += 1
  )
  {
    mp_panCrcTable[l_nLoopY] = _Reflect(l_nLoopY, 8) << 24;

    for
    ( l_nLoopX  = 0
    ; l_nLoopX <  8
    ; l_nLoopX += 1
    )
    {
      mp_panCrcTable[l_nLoopY]
      = (mp_panCrcTable[l_nLoopY] << 1)
      ^ ( mp_panCrcTable[l_nLoopY] & (1 << 31)
        ? l_nPolynomial
        : 0
        )
      ;
    }

    mp_panCrcTable[l_nLoopY] = _Reflect(mp_panCrcTable[l_nLoopY], 32);
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
ULONG CRC32::_Reflect(ULONG i_nRef, char i_nChar)
{
  ULONG l_nValue = 0;
  int   l_nLoop;

  for
  ( l_nLoop  = 1
  ; l_nLoop <  (i_nChar + 1)
  ; l_nLoop += 1
  )
  {
    if(i_nRef & 1)
    {
      l_nValue |= 1 << (i_nChar - l_nLoop);
    }
    else{}

    i_nRef >>= 1;
  }

  return l_nValue;
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CRC32::_Calc(const LPBYTE i_panBuffer, UINT i_nSize, ULONG &io_rnCRC)
{
  LPBYTE l_panByte = i_panBuffer;

  while(i_nSize--)
  {
    io_rnCRC
    = (io_rnCRC >> 8)
    ^ mp_panCrcTable[(io_rnCRC & 0xFF) ^ *l_panByte++]
    ;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
DWORD CRC32::CalcCRC(LPVOID i_panBuffer, UINT i_nSize)
{
  if
  (
       (i_panBuffer == NULL)
    || (i_nSize     == 0)
  )
  {
    return 0;
  }
  else
  {
    DWORD l_nCRC = 0xFFFFFFFF;

    _Calc((LPBYTE) i_panBuffer, i_nSize, l_nCRC);

    return l_nCRC ^ 0xFFFFFFFF;
  }
}

// ============================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
LPSTR TrimLeftRight
( LPSTR i_panString
, LPSTR i_panRemove
)
{
  int l_nIndexStart = 0;
  int l_nIndexEnd   = strlen(i_panString) - 1;
  int l_nIndexCopy = 0;
  int l_nIndexSkip = 0;

  if
  (
       (i_panString    == NULL)
    || (i_panString[0] == '\0')
  )
  {
    return i_panString;
  }
  else
  {
    while
    (
         (l_nIndexEnd > l_nIndexStart)
      && (
              i_panString[l_nIndexEnd] == ' '
           || i_panString[l_nIndexEnd] == '\t'
           || i_panString[l_nIndexEnd] == '\r'
           || i_panString[l_nIndexEnd] == '\n'
         )
    )
    { // Remove trailing characters
      l_nIndexEnd -= 1;
    }

    for
    ( l_nIndexSkip = 0
    ;    (l_nIndexEnd > l_nIndexStart)
      && (i_panRemove[l_nIndexSkip] != 0)
    ;
    )
    { // Remove trailing characters
      if(i_panString[l_nIndexEnd] == i_panRemove[l_nIndexSkip])
      { // Found a character to skip
        l_nIndexEnd -= 1; // Remove it from the end
        l_nIndexSkip = 0; // Restart the scan
      }
      else
      { // Not found, try the next characher
        l_nIndexSkip += 1;
      }
    }

    while
    (
         (l_nIndexStart <= l_nIndexEnd)
      && (
              i_panString[l_nIndexStart] == ' '
           || i_panString[l_nIndexStart] == '\t'
           || i_panString[l_nIndexStart] == '\r'
           || i_panString[l_nIndexStart] == '\n'
         )
    )
    { // Remove leading characters
      l_nIndexStart += 1;
    }

    for
    ( l_nIndexSkip = 0
    ;    (l_nIndexStart <= l_nIndexEnd)
      && (i_panRemove[l_nIndexSkip] != 0)
    ;
    )
    { // Remove leading characters
      if(i_panString[l_nIndexStart] == i_panRemove[l_nIndexSkip])
      { // Found a character to skip
        l_nIndexStart += 1; // Remove it from the start
        l_nIndexSkip   = 0; // Restart the scan
      }
      else
      { // Not found, try the next characher
        l_nIndexSkip += 1;
      }
    }

    if(l_nIndexStart != 0)
    { // If start has changed, relocate the string
      while(l_nIndexStart <= l_nIndexEnd)
      {
        i_panString[l_nIndexCopy] = i_panString[l_nIndexStart];
        l_nIndexCopy  += 1;
        l_nIndexStart += 1;
      }

      // Place the new end
      i_panString[l_nIndexCopy] = '\0';
    }
    else
    { // Place the new end
      i_panString[l_nIndexEnd + 1] = '\0';
    }
   
    return i_panString;
  }
}

// ============================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void ClassUtils::SetClassName
( const char* i_panStrName
)
{
  mp_oStrObjectName = i_panStrName;
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void ClassUtils::_SetClassType
( const char* i_panStrClass // = "BaseClass"
)
{
  mp_oStrObjectClass = i_panStrClass;
}

// ============================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
MultiStringBuffer::MultiStringBuffer()
{
  m_panFullString = NULL;
  m_nBufferLen    = 0;
  mp_panPrevSep   = NULL;

  ErasePointers();
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
MultiStringBuffer::~MultiStringBuffer()
{
  if(m_panFullString != NULL)
  {
    delete m_panFullString;
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
MultiStringBuffer::Extract
( XString& rString
, LPCTSTR  lpszFullString
, int      iSubString
, TCHAR    chSep // = '\n'
, bool     bTrim // = false
, bool     bForce  // = false
)
{
  TCHAR l_anChar[2] = {chSep, 0};

  return Extract
  ( rString
  , lpszFullString
  , iSubString
  , l_anChar
  , bTrim
  , bForce
  );
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
MultiStringBuffer::Extract
( XString& rString
, LPCTSTR  lpszFullString
, int      iSubString
, LPCTSTR  lpszSep // = "(,)\n"
, bool     bTrim   // = false
, bool     bForce  // = false
)
{
  if
  (
       (iSubString == 0) // Si premier élément, donc à prioris nouvelle chaine
    || (mp_panPrevSep != lpszSep) // Ou changement de séparateur (ne devrait théoriquement pas arriver)
    || (bForce == true)
//    || (m_strPrevSep.compare(lpszSep) != 0)
  )
  { // Si premiere fois, on efface le buffer et les pointeurs
    int    l_nStart = 0;
    int    l_nTrim  = 0;
    int    l_nEnd   = 0;
    TCHAR* l_panChar;
    bool   l_bTrim  = false;
// MODIF_KOCH 070326
// DK 070326 (QUOTE PARSE) : Gestion des guillemets
    bool   l_bQuote = false; // Ouverture/fermeture des guillemets
// MODIF_KOCH 070326

    ErasePointers(lpszFullString);
    m_strPrevSep  = lpszSep;
    mp_panPrevSep = lpszSep;

    if(m_panFullString != NULL)
    { // Si y'a du boulot, on parse
      l_panChar = m_panFullString;

      while(*l_panChar != '\0')
      {
// MODIF_KOCH 070326
// DK 070326 (QUOTE PARSE) : Gestion des guillemets
        if(*l_panChar == '"')
        {
          l_bQuote = !l_bQuote;
        }
        else if(l_bQuote == false)
        {
// MODIF_KOCH 070326
          if
          (
               (m_strPrevSep.find(*l_panChar) != std::string::npos)
            && ( // Nettoyage des espaces contigus si compte comme caractère de séparation
                    (bTrim == false) // On s'en fout du trim
                 || ( // On a déjà trimé
                         (l_bTrim == true)
                      && (bTrim   == true)
                    )
               )
          )
          { // Séparateur trouvé
            m_anSubStrFirst.push_back(l_nStart);

            l_nTrim = l_nEnd;

            if(bTrim == true)
            { // Si on trim, on repart en arrière
              do
              {
                l_nTrim   -= 1;
                l_panChar -= 1;
              }
              while
              (
                   (*l_panChar == ' ')
                || (*l_panChar == '\t')
                || (*l_panChar == '\r')
                || (*l_panChar == '\n')
              );

              l_nTrim   += 1;
              l_panChar += 1;

              l_bTrim = false;
            }
            else{}

            *l_panChar = '\0'; // pour le strcpy d'en dessous

            m_anSubStrCount.push_back(l_nTrim - l_nStart);
            l_nStart   = l_nEnd + 1;
            l_panChar += l_nEnd - l_nTrim;
          }
          else
          {
            if
            (
                 (l_bTrim == false)
              && (bTrim   == true)
            )
            { // Si pas déjà trimé
              if
              (
                   (*l_panChar == ' ')
                || (*l_panChar == '\t')
                || (*l_panChar == '\r')
                || (*l_panChar == '\n')
              )
              { // Si on trim, on déplace le début
                l_nStart += 1;
              }
              else
              {
                l_bTrim = true;
              }
            }
            else{}
          }
// MODIF_KOCH 070326
// DK 070326 (QUOTE PARSE) : Gestion des guillemets
        }
        else{} // Tant que l'on est dans un 'quote', on passe
// MODIF_KOCH 070326

        l_nEnd    += 1;
        l_panChar += 1;
      } // endwhile

      m_anSubStrFirst.push_back(l_nStart);
      m_anSubStrCount.push_back(l_nEnd - l_nStart);
    }
    else{}
  }
  else{}

  if(iSubString < m_anSubStrFirst.size())
  {
    // Maintenant on retourne la chaine qui va bien ;)
    strcpy
    ( rString.GetBuffer(m_anSubStrCount[iSubString]+1) // Destination
    , &m_panFullString[m_anSubStrFirst[iSubString]] // Source
    );

    rString.ReleaseBuffer();

    return TRUE; // Extraction OK
  }
  else
  {
    rString.Empty();

    return FALSE; // Index pas trouvé
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL MultiStringBuffer::Parse
( LPCTSTR lpszFullString
, TCHAR   chSep // = '\n'
, bool    bTrim // = true
)
{
  XString l_oStrTempo;

  return Extract
  ( l_oStrTempo
  , lpszFullString
  , 0
  , chSep
  , bTrim
  );
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL MultiStringBuffer::Parse
( LPCTSTR lpszFullString
, LPCTSTR lpszSep // = "(,)\n"
, bool    bTrim   // = true
)
{
  XString l_oStrTempo;

  return Extract
  ( l_oStrTempo
  , lpszFullString
  , 0
  , lpszSep
  , bTrim
  );
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
LPCTSTR MultiStringBuffer::GetStringAdr
( int iSubString
)
{
  if(m_panFullString != NULL)
  {
    return &m_panFullString[m_anSubStrFirst[iSubString]];
  }
  else
  {
    return NULL;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
XString MultiStringBuffer::GetStringObj
( int iSubString
)
{
  if(m_panFullString != NULL)
  {
    return &m_panFullString[m_anSubStrFirst[iSubString]];
  }
  else
  {
    return "";
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
std::string MultiStringBuffer::GetStringStd
( int iSubString
)
{
  if(m_panFullString != NULL)
  {
    return &m_panFullString[m_anSubStrFirst[iSubString]];
  }
  else
  {
    return "";
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void MultiStringBuffer::ErasePointers
( LPCTSTR lpszFullString
)
{
  m_anSubStrFirst.resize(0);
  m_anSubStrCount.resize(0);

  if(lpszFullString != NULL)
  {
    int l_nStringLen = strlen(lpszFullString) + 1;
    
    if(l_nStringLen > m_nBufferLen)
    {
      if(m_panFullString != NULL)
      {
        delete m_panFullString;
        m_panFullString = NULL;
      }
      else{}

      m_nBufferLen = l_nStringLen;
    }
    else{}

    if(m_panFullString == NULL)
    {
      m_panFullString = new char[m_nBufferLen];
    }
    else{}
    
    strcpy(m_panFullString, lpszFullString);
  }
  else
  {
    if(m_panFullString != NULL)
    {
      m_panFullString[0] = '\0';
    }
    else{}
  }
}

// === CLASSE DE BASE : FICHIER =======================================================================================

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CFileIO::CFileIO
(
)
{
  _Init();
  _InitSecurity();
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CFileIO::CFileIO
( char* i_panFilePathNameExt
)
{
  _Init();
  _InitSecurity();

  FileOpen(i_panFilePathNameExt);
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
CFileIO::~CFileIO
(
)
{
#ifdef DEBUGSTUFF // SigUtils.h
  TRACE
  ( "%s::~CFileIO(%s) read %d byte%s\n"
  , (CString) mp_oStrObjectName
  , mp_oStrFile
  , mp_nPos + mp_nFileRead
  , (mp_nFileRead > 1)?"s":""
  );
#endif // DEBUGSTUFF

  if(m_poSidEveryone        != NULL) delete m_poSidEveryone;
  if(m_poTrusteeEveryone    != NULL) delete m_poTrusteeEveryone;
  if(m_poSecurityAttributes != NULL) delete m_poSecurityAttributes;

  FileClose();
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CFileIO::_Init
(
)
{
  mp_nFileSize = 0;
  mp_nFileLeft = 0;
  mp_nFileRead = 0;
  mp_nPointer  = 0;
  mp_nPos      = 0;

  mp_panBuffer = NULL;
  mp_poFile    = NULL;
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CFileIO::_InitSecurity
(
)
{
  m_poSidEveryone        = new CSid(CSid::WST_EVERYONE);
  m_poTrusteeEveryone    = new CTrustee(TRUSTEE_IS_WELL_KNOWN_GROUP, *m_poSidEveryone);
  m_poSecurityAttributes = new CSecurityAttributes(m_oSecurityDescriptor, FALSE);

  m_sEA
  = CExplicitAccess
    ( KEY_ALL_ACCESS
    , SET_ACCESS
    , SUB_CONTAINERS_AND_OBJECTS_INHERIT
    , *m_poTrusteeEveryone
    )
  ;

  if(m_oAcl.SetEntriesInAcl(1,&m_sEA)!=ERROR_SUCCESS)
  {
    TRACE("Erreur de descripteur de sécurité (1)");
  }
  else{}

  if(!m_oSecurityDescriptor.SetSecurityDescriptorDacl(TRUE,m_oAcl,FALSE))
  {
    TRACE("Erreur de descripteur de sécurité (2)");
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CFileIO::_Load
(
)
{
  if
  (
       (mp_nFileRead == 0) // Pas de buffer lu
    || (mp_nFileRead == mp_nPointer) // Fin de buffer atteinte
  )
  { // Lecture d'un nouveau buffer
    mp_nPos += mp_nFileRead; // Position précédente
    mp_nPointer = 0;

    mp_nFileRead  = (UINT) mp_poFile->Read(mp_panBuffer, cBUFFER_SIZE); // On remplit le buffer
    mp_nFileLeft -= mp_nFileRead;

#ifdef XDEBUGSTUFF // SigUtils.h
    if(mp_nFileRead > 0)
    {
      int   l_nColumn;
      int   l_nStart;
      int   l_nLoop;
      int   l_nEnd;
      char  l_panBuffer[2][18];
      char* l_panStuff;

      // Null character        NUL     0           \0 
      // Alert                 BEL     7           \a 
      // Backspace             BS      8           \b 
      // Horizontal tab        HT      9           \t 
      // Newline               NL (LF) 10 or 0x0a  \n 
      // Vertical tab          VT      11 or 0x0b  \v 
      // Formfeed              FF      12 or 0x0c  \f 
      // Carriage return       CR      13 or 0x0d  \r 
      // Double quotation mark "       34 or 0x22  \" 
      // Single quotation mark '       39 or 0x27  \' 
      // Question mark         ?       63 or 0x3f  \? 
      // Backslash             \       92 or 0x5c  \\ 
      // Octal number          ooo     --          \ooo 
      // Hexadecimal number    hhh     --          \xhhh 

      for
      ( l_nColumn = 0
      ; l_nColumn < 2
      ; l_nColumn += 1
      )
      {
        switch(l_nColumn)
        {
          case 0:
            l_nStart = 0;
            l_nEnd   = 8;
            break;
          case 1:
            l_nStart = (mp_nFileRead - 8);
            l_nEnd   = mp_nFileRead;
            break;
        }

        l_panStuff = &l_panBuffer[l_nColumn][0];

        for
        ( l_nLoop = l_nStart
        ; l_nLoop < l_nEnd
        ; l_nLoop += 1
        )
        {
          switch(mp_panBuffer[l_nLoop])
          {
            case '\0':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = '0';
              break;
            case '\a':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 'a';
              break;
            case '\b':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 'b';
              break;
            case '\t':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 't';
              break;
            case '\n':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 'n';
              break;
            case '\v':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 'v';
              break;
            case '\f':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 'f';
              break;
            case '\r':
              *l_panStuff = '\\';
              l_panStuff  += 1;
              *l_panStuff = 'r';
              break;
//            case '\"':
//              *l_panStuff = '\\';
//              l_panStuff  += 1;
//              *l_panStuff = '\"';
//              break;
//            case '\'':
//              *l_panStuff = '\\';
//              l_panStuff  += 1;
//              *l_panStuff = '\'';
//              break;
//            case '\?':
//              *l_panStuff = '\\';
//              l_panStuff  += 1;
//              *l_panStuff = '\?';
//              break;
//            case '\\':
//              *l_panStuff = '\\';
//              l_panStuff  += 1;
//              *l_panStuff = '\\';
//              break;
            default:
              *l_panStuff = mp_panBuffer[l_nLoop]; // On copie le caractère
          }

          l_panStuff  += 1;
        }

        *l_panStuff = '\0';
      }

      TRACE
      ( "%s::_Load(%s) loaded %d byte%s : 0x%08X [%s[ - [%s[ 0x%08X\n"
      , (CString) mp_oStrObjectName
      , (CString) mp_oStrFile
      , mp_nFileRead
      , (mp_nFileRead > 1)?"s":""
      , mp_nPos
      , &l_panBuffer[0][0]
      , &l_panBuffer[1][0]
      , mp_nPos + mp_nFileRead
      );
    }
    else
    {
      TRACE
      ( "%s::LoadNextLine(%s) >>> EOF !\n"
      , (CString) mp_oStrObjectName
      , (CString) mp_oStrFile // mp_poFile->GetFilePath()
      );
    }
#endif // DEBUGSTUFF
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL CFileIO::FileOpen
( char* i_panFilePathNameExt
)
{
  FileClose();
  
  mp_poFile
  = new 
  CFile
  ( i_panFilePathNameExt
  , CFile::modeRead
  | CFile::shareDenyWrite
  | CFile::typeBinary
  )
  ;

  mp_oStrFile = i_panFilePathNameExt;

  if(mp_poFile != NULL)
  {
    mp_nFileSize = (int) mp_poFile->GetLength();
    mp_nFileLeft = mp_nFileSize;
    mp_panBuffer = new char[cBUFFER_SIZE + 2];

    if(mp_panBuffer != NULL)
    {
      mp_panBuffer[cBUFFER_SIZE]   = 0; // UNICODE
      mp_panBuffer[cBUFFER_SIZE+1] = 0; // UNICODE

      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL CFileIO::FileCreate
( char* i_panFilePathNameExt
)
{
  FileClose();

/*
  CString l_oStrPath = i_panFilePathNameExt;

  CPathSplit l_oTest0(i_panFilePathNameExt);
  CPathSplit l_oTest1(l_oStrPath.Left(l_oStrPath.ReverseFind('\\')));

  CreateDirectory
  ( l_oTest1.GetFolder()
  , m_poSecurityAttributes // Attributs de sécurités par défaut
  );

  CreateDirectory
  ( l_oTest0.GetFolder()
  , m_poSecurityAttributes // Attributs de sécurités par défaut
  );
*/

  mp_poFile
  = new 
  CFile
  ( i_panFilePathNameExt
  , CFile::shareExclusive
  | CFile::modeCreate
  | CFile::modeWrite
  | CFile::typeBinary
  )
  ;

  mp_oStrFile = i_panFilePathNameExt;

  if(mp_poFile != NULL)
  {
    mp_nFileSize = (int) mp_poFile->GetLength();
    mp_nFileLeft = mp_nFileSize;
    mp_panBuffer = new char[cBUFFER_SIZE + 2];

    if(mp_panBuffer != NULL)
    {
      mp_panBuffer[cBUFFER_SIZE]   = 0; // UNICODE
      mp_panBuffer[cBUFFER_SIZE+1] = 0; // UNICODE

      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CFileIO::FileFlush
(
)
{
  if(mp_poFile != NULL)
  {
    mp_poFile->Flush();
  }
  else{}
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
void CFileIO::FileClose
(
)
{
  if(mp_panBuffer != NULL)
  {
    delete [] mp_panBuffer;
  }
  else{}

  if(mp_poFile != NULL)
  {
//    mp_poFile->Flush();
    mp_poFile->Close();
    delete mp_poFile;
  }
  else{}

  _Init();
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL CFileIO::LoadNextLine
( XString &o_poStrLine
, BOOL     i_bAllowEmptyLine
)
{
  char*   l_panCopy;
  XString l_oStrTempo;

  int     l_nBegin;
  int     l_nTempo;

  BOOL    l_bCr = FALSE;
  BOOL    l_bLf = FALSE;

  BOOL    l_bStringFound = FALSE;

  //

  if((mp_nPos + mp_nPointer) < mp_nFileSize)
  { // Si on n'a pas encore atteind la fin
    o_poStrLine.Empty();

    //

    do
    {
      _Load();

#ifdef DEBUGSTUFF // SigUtils.h
      if
      (
           ((mp_nPos + mp_nPointer) >= 0x003FFFE0)
        && ((mp_nPos + mp_nPointer) <  0x00400000)
      )
      { // Placer un breakpoint ici pour stopper le debug à un endroit précis dans le fichier
        mp_nPos = mp_nPos;
      }
#endif // DEBUGSTUFF

/*
      if(i_bAllowEmptyLine == TRUE)
      {
        l_bCr = FALSE;
        l_bLf = FALSE;
      }
      else{}
*/

      if(l_bStringFound == FALSE)
      { // Si on n'a pas encore trouvé de chaine
        while
        ( // On passe les CRLF
             ( // Cherche une seule ligne seulent
                  (
                       (mp_panBuffer[mp_nPointer] == '\r')
                    && (l_bCr == FALSE)
                  )
               || (
                       (mp_panBuffer[mp_nPointer] == '\n')
                    && (l_bLf == FALSE)
                  )
             )
          && (mp_nPointer < mp_nFileRead)
        )
        {
          if(i_bAllowEmptyLine == TRUE)
          {
            if(mp_panBuffer[mp_nPointer] == '\r')
            {
              l_bCr = TRUE;
            }
            else{}

            if(mp_panBuffer[mp_nPointer] == '\n')
            {
              l_bLf = TRUE;
            }
            else{}
          }
          else{}

          mp_nPointer += 1;
        }
      }
      else{}

      // Début de chaine
      l_nBegin = mp_nPointer;

      // On cherche la fin de chaine
      while
      (
           (mp_panBuffer[mp_nPointer] != '\r')
        && (mp_panBuffer[mp_nPointer] != '\n')
        && (mp_nPointer < mp_nFileRead)
      )
      {
        mp_nPointer += 1;
      }

      // On ajoute déjà ce que l'on vient de trouver
      l_nTempo = mp_nPointer - l_nBegin;
      if(l_nTempo > 0)
      {
        l_bStringFound = TRUE;
        l_panCopy = l_oStrTempo.GetBuffer(l_nTempo);

        while(l_nBegin < mp_nPointer)
        {
          *l_panCopy = mp_panBuffer[l_nBegin]; // On copie le caractère
          l_panCopy  += 1;
          l_nBegin   += 1;
        }

        l_oStrTempo.ReleaseBuffer(l_nTempo);    

        o_poStrLine += l_oStrTempo;
      }
      else{}
    }
    while
    ( // Tant qu'il reste quelque chose à lire et que l'on n'est pas sur une fin de ligne
         ((mp_nPos + mp_nPointer) < mp_nFileSize) // Fin de fichier pas atteinte
      && (
              (mp_nPointer >= mp_nFileRead) // Fin de buffer atteinte
           || ( // Pas de fin de chaine trouvée
                   (mp_panBuffer[mp_nPointer] != '\r')
                && (mp_panBuffer[mp_nPointer] != '\n')
                && (mp_panBuffer[mp_nPointer] != '\0')
              )
           || ( // Pas de chaine vide autorisée
                   (o_poStrLine.IsEmpty() == TRUE)
                && (i_bAllowEmptyLine     == FALSE)
              )
/*
           || (
                   (o_poStrLine.IsEmpty() == FALSE)
                && (i_bAllowEmptyLine     == FALSE)
              )
*/
         )
    );

    return (i_bAllowEmptyLine == TRUE) || (o_poStrLine.IsEmpty() == FALSE);
  }
  else
  { // Fin déjà atteinte, là c'est clair, c'est mort
    return FALSE;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL CFileIO::LoadNextBuff
( char *o_panBuffer
, int  &io_rnSize
)
{
  if
  (
       (o_panBuffer != NULL)
    && (io_rnSize   != 0)
    && ((mp_nPos + mp_nPointer) < mp_nFileSize)
  )
  { // Si on n'a pas encore atteind la fin
    int l_nSize = io_rnSize;
    int l_nRead;

    //

    do
    {
      _Load();
    
      l_nRead
      = min
      ( mp_nFileRead - mp_nPointer
      , l_nSize
      );

#ifdef USEMEMCPY
      MEMCPY
#else
      memcpy
#endif // USEMEMCPY
      ( o_panBuffer // Output buffer
      , &mp_panBuffer[mp_nPointer]
      , l_nRead
      );

      l_nSize     -= l_nRead; // Reste à lire
      mp_nPointer += l_nRead; // On a lu jusqu'à
      o_panBuffer += l_nRead; // Pour la suite
    }
    while
    ( // Tant qu'il reste quelque chose à lire
         ((mp_nPos + mp_nPointer) < mp_nFileSize)
      && (l_nSize > 0)
    );

    io_rnSize -= l_nSize;

    return (io_rnSize != 0);
  }
  else
  {
    return FALSE;
  }
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
BOOL CFileIO::WriteLine
( const char* i_panBuffer
)
{
  int l_nSize = strlen(i_panBuffer);

  if(mp_poFile != NULL)
  {
    mp_poFile->Write
    ( i_panBuffer
    , l_nSize
    );
  }
  else{}

  return (mp_poFile != NULL) && (i_panBuffer != NULL) && (l_nSize > 0);
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CFileIO::GetSize
(
)
{
  return mp_nFileSize;
}

/*--- START FUNCTION HEADER --------------------------------------------------*/
/* Name          :                                                            */
/* Role          :                                                            */
/* Type          : public                                                     */
/* Interface     : RETURN (direct value)                                      */
/*                   None                                                     */
/*                 OUTPUT (pointer to value)                                  */
/*                   None                                                     */
/*                 INPUT  (pointer to value, direct/default value)            */
/*                   None                                                     */
/* Pre-condition : None                                                       */
/* Constraints   : Sets the default values to                                 */
/* Behavior      :                                                            */
/*----------------------------------------------------------------------------*/
/* PROC                                                                       */
/*                                                                            */
/* A.....                                                                     */
/*----------------------------------------------------------------------------*/
/*--- END FUNCTION HEADER ----------------------------------------------------*/
int CFileIO::GetPos
(
)
{
  return mp_nPos + mp_nPointer;
}
