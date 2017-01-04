// Memory.h: interface for the CMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORY_H__EEEBB9FB_894C_4EC5_855E_2270B8DC415F__INCLUDED_)
#define AFX_MEMORY_H__EEEBB9FB_894C_4EC5_855E_2270B8DC415F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Pre baseclass declaration includes
// Includes needed headers for baseclass declaration
#include "SigUtils.h" // for ClassUtils

#define MEM_ALIGN 3 // 2^3 or 1<<3 = 8 bytes
#define ALIGN(x) ((x+(1<<MEM_ALIGN)-1)&(0-1<<MEM_ALIGN))

class EXPSIGENGINE CMemory : public ClassUtils
{
  public:
    CMemory();
    virtual ~CMemory();
};

#define FAVOR_REDBLACK

// Post baseclass declaration includes
// Allows to include only the baseclass header
#include "MemoryContainer.h"       // Base class
#include "MemoryPool.h"            // Minimal implementation
#include "MemoryArray.h"           // Changed methods
#include "MemoryTree.h"            // Complex management
#include "MemoryTreeRedBlack.h"    // Complex management
#include "MemoryTreeAvl.h"         // Complex management
#include "MemoryTreeSplay.h"       // Complex management

#include "MemoryStringContainer.h" // Base class
#include "MemoryStringPool.h"      // Minimal implementation
#include "MemoryStringArray.h"     // Changed methods
#include "MemoryStringTree.h"      // Complex management

#include "MemoryString.h"

#endif // !defined(AFX_MEMORY_H__EEEBB9FB_894C_4EC5_855E_2270B8DC415F__INCLUDED_)
