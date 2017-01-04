// SigEngine.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "SigEngine.h"

#include "TreeListResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE SigEngineDLL = { NULL, NULL };

extern "C" BOOL APIENTRY DllMain
( HINSTANCE hInstance
, DWORD     ul_reason_for_call
, LPVOID    lpReserved
)
{
  UNREFERENCED_PARAMETER(lpReserved);

  switch(ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
		  TRACE0("SigEngine.dll -> Initializing!\n");
		  // Extension DLL one-time initialization
      if(!AfxInitExtensionModule(SigEngineDLL, hInstance))
        return 0;
		  // Insert this DLL into the resource chain
		  // NOTE: If this Extension DLL is being implicitly linked to by
		  //  an MFC Regular DLL (such as an ActiveX Control)
		  //  instead of an MFC application, then you will want to
		  //  remove this line from DllMain and put it in a separate
		  //  function exported from this Extension DLL.  The Regular DLL
		  //  that uses this Extension DLL should then explicitly call that
		  //  function to initialize this Extension DLL.  Otherwise,
		  //  the CDynLinkLibrary object will not be attached to the
		  //  Regular DLL's resource chain, and serious problems will
		  //  result.
      new CDynLinkLibrary(SigEngineDLL);
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
		  TRACE0("SigEngine.dll -> Terminating!\n");
		  // Terminate the library before destructors are called
      AfxTermExtensionModule(SigEngineDLL);
      break;
  }

  return TRUE;
}

// Initialisation de CTreeListResource (inscription dans la chaine de ressources)

CTreeListResource::CTreeListResource()
{
  m_hOldInst = AfxGetResourceHandle();

  ASSERT(m_hOldInst != NULL);

  AfxSetResourceHandle(SigEngineDLL.hResource);
}

CTreeListResource::~CTreeListResource()
{
  AfxSetResourceHandle(m_hOldInst);
}
