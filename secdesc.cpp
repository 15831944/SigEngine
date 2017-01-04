// secdesc.cpp
//
// Wrapper classes for the Win32 low-level security APIs.
// (C) 1999 Peter Kenyon <Peter@bizinf.co.nz>
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "secdesc.h"

// CAcl
CAcl::CAcl()
{
	m_pACL = NULL;
}

// Allocates and initializes an empty ACL.
// Use the helper function GetLengthAcl to calculate the size needed
// eg:		GetLengthAcl(3, pSids, sizeof(ACCESS_DENIED_ACE));
BOOL CAcl::InitializeAcl(DWORD nAclLength)
{ 
	if(m_pACL)
		::LocalFree(m_pACL);

	m_pACL = (PACL) LocalAlloc(LMEM_FIXED, nAclLength);

	if(!m_pACL)
		return FALSE;

	return ::InitializeAcl(m_pACL, nAclLength, ACL_REVISION); 
}

CAcl::~CAcl()
{
	::LocalFree(m_pACL);
}

// Re-allocates an ACL and merges it with an array of EXPLICIT_ACCESS entries
DWORD CAcl::SetEntriesInAcl(ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS pListOfExplicitEntries)
{
	PACL paclNew;
	DWORD dwRes = ::SetEntriesInAcl(cCountOfExplicitEntries, pListOfExplicitEntries, m_pACL, &paclNew);

	if(dwRes == ERROR_SUCCESS)
	{
		::LocalFree(m_pACL);
		m_pACL = paclNew;
	}

	return dwRes;
}

// CSid
CSid::CSid()
{
	m_pSid = NULL;
	m_dwSidSize = 0;
	m_bSystemAllocated = FALSE;
}

CSid::CSid(WELLKNOWN_SID_TYPE type)
{
	m_pSid = NULL;
	m_dwSidSize = 0;
	m_bSystemAllocated = FALSE;

	switch(type)
	{
	case WST_NULL:
		CreateNullSid();
		break;

	case WST_EVERYONE:
		CreateEveryoneSid();
		break;
		
	case WST_CREATOROWNER:
		CreateCreatorOwnerSid();
		break;

	case WST_CREATORGROUP:
		CreateCreatorGroupSid();
		break;

	case WST_INTERACTIVE:
		CreateInteractiveUserSid();
		break;

	case WST_LOCALUSERS:
		CreateLocalUserSid();
		break;

	case WST_LOCALADMINS:
		CreateLocalAdminSid();
		break;

	case WST_LOCALGUESTS:
		CreateLocalGuestSid();
		break;

	case WST_LOCALPOWERUSERS:
		CreateLocalPowerUserSid();
		break;

	}
}

CSid::~CSid()
{
	FreeSid();
}

BOOL CSid::LookupAccountName(
							 LPCTSTR lpSystemName, 
							 LPCTSTR lpAccountName, 
							 LPTSTR lpReferencedDomainName, 
							 LPDWORD cbReferencedDomainName, 
							 PSID_NAME_USE peUse)
{
	// Retrieves the SID for the specified account name.

	return ::LookupAccountName(
			lpSystemName,
			lpAccountName,
			m_pSid,
			&m_dwSidSize,
			lpReferencedDomainName,
			cbReferencedDomainName,
			peUse);
}


void CSid::FromSid(PSID pSid)
{
	FreeSid();

	m_pSid = pSid;
}

void CSid::FreeSid()
{
	if(m_pSid)
	{
		if(m_bSystemAllocated)
			::FreeSid(m_pSid);
		else
			delete m_pSid;
	}
}

// Allocates a SID but does not initialize it.
void CSid::AllocateSid(DWORD dwSize)
{
	FreeSid();

	char * pNewBuffer = new char[dwSize];
	
	if(pNewBuffer)
	{
		m_pSid = (PSID)pNewBuffer;
		m_dwSidSize = dwSize;
	}
	else
		m_dwSidSize = 0;

	m_bSystemAllocated = FALSE;
	
}

// Creates a SID representing anybody who is a member of the built-in
// Administrators group on the local computer.
BOOL CSid::CreateLocalAdminSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0);
}

// Creates a SID representing all users on the local machine
BOOL CSid::CreateLocalUserSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_USERS,
        0, 0, 0, 0, 0, 0);
}

// Creates a SID representing all users everywhere.
BOOL CSid::CreateEveryoneSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_WORLD_SID_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		1,
        SECURITY_WORLD_RID,
        0, 0, 0, 0, 0, 0, 0);
}

// Creates a SID with no members
BOOL CSid::CreateNullSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NULL_SID_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		1,
        SECURITY_NULL_RID,
        0, 0, 0, 0, 0, 0, 0);
}

// Creates a SID representing the user who created an object
BOOL CSid::CreateCreatorOwnerSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_CREATOR_SID_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		1,
        SECURITY_CREATOR_OWNER_RID,
        0, 0, 0, 0, 0, 0, 0);
}

// Creates a SID representing the group the user who who created an 
// object belongs to.
BOOL CSid::CreateCreatorGroupSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_CREATOR_SID_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		1,
        SECURITY_CREATOR_GROUP_RID,
        0, 0, 0, 0, 0, 0, 0);
}

// Creates a SID representing the built-in Guests group.
BOOL CSid::CreateLocalGuestSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_GUESTS,
        0, 0, 0, 0, 0, 0);
}

// A Power User is a user who "expects to treat a system as if it 	
// were their personal computer rather than as a workstation for 
// multiple users" - Platform SDK
BOOL CSid::CreateLocalPowerUserSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_POWER_USERS,
        0, 0, 0, 0, 0, 0);
}

// This SID represents any user physically logged into the current workstation.
// Can be used to grant access to logged-on users as opposed to users
// accessing data across the network.
BOOL CSid::CreateInteractiveUserSid()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid(
		&sidAuth,
		1,
        SECURITY_INTERACTIVE_RID,
        0, 0, 0, 0, 0, 0, 0);
}

// CSecurityDescriptor
CSecurityDescriptor::CSecurityDescriptor()
{
	m_pSD = (PSECURITY_DESCRIPTOR) new char[SECURITY_DESCRIPTOR_MIN_LENGTH];
	
	if(m_pSD)
		::InitializeSecurityDescriptor(m_pSD, SECURITY_DESCRIPTOR_REVISION);
}

CSecurityDescriptor::CSecurityDescriptor(PSECURITY_DESCRIPTOR pSD)
{
	m_pSD = pSD;
}

CSecurityDescriptor::~CSecurityDescriptor()
{
	delete m_pSD;
}

// Calculates the size needed for an ACL, given
// an array of SIDs and the size of an ACE type.
int GetLengthAcl(int nAceCount, PSID pAceSid[], size_t sizeAce)
{
	int cbAcl = sizeof (ACL);
	for (int i = 0 ; i < nAceCount ; i++) 
	{
		// subtract ACE.SidStart from the size
		int cbAce = sizeAce - sizeof(DWORD);
		// add this ACE's SID length
		cbAce += ::GetLengthSid(pAceSid[i]);
		// add the length of each ACE to the total ACL length
		cbAcl += cbAce;
	}

	return cbAcl;
}
