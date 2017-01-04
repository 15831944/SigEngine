// secdesc.h:
//
// Wrapper classes for the Win32 low-level security APIs.
// (C) 1999 Peter Kenyon
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SID_H__1CF2BF36_9316_11D3_B0B8_0040054C5E60__INCLUDED_)
#define AFX_SID_H__1CF2BF36_9316_11D3_B0B8_0040054C5E60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <winnt.h>
#include <aclapi.h>
#include <accctrl.h>

// Calculates the size needed for an ACL, given an array of
// SIDs and the size of an ACE type.
int GetLengthAcl(int nAceCount, PSID pAceSid[], size_t sizeAce);

class CSecurityAttributes : public SECURITY_ATTRIBUTES
{
public:
	CSecurityAttributes() {}
	CSecurityAttributes(PSECURITY_DESCRIPTOR pSD, BOOL bCanInheritHandle=FALSE)
	{
		lpSecurityDescriptor = (LPVOID)pSD;
		bInheritHandle = bCanInheritHandle;
	}
	operator LPSECURITY_ATTRIBUTES() { return this; }
};

class CSid  
{
public:
	enum WELLKNOWN_SID_TYPE 
	{
		WST_NULL	= 0,
		WST_EVERYONE,
		WST_CREATOROWNER,
		WST_CREATORGROUP,
		WST_INTERACTIVE,
		WST_LOCALUSERS,
		WST_LOCALADMINS,
		WST_LOCALGUESTS,
		WST_LOCALPOWERUSERS
	};

	CSid();
	CSid(WELLKNOWN_SID_TYPE);
	virtual ~CSid();

	BOOL CreateNullSid();
	BOOL CreateEveryoneSid();
	BOOL CreateCreatorOwnerSid();
	BOOL CreateCreatorGroupSid();
	BOOL CreateInteractiveUserSid();
	BOOL CreateLocalUserSid();
	BOOL CreateLocalAdminSid();
	BOOL CreateLocalGuestSid();
	BOOL CreateLocalPowerUserSid();
	void AllocateSid(DWORD dwSize);
	void FreeSid();
	void FromSid(PSID pSid);
	
	BOOL LookupAccountName(LPCTSTR lpSystemName, LPCTSTR lpAccountName, LPTSTR lpReferencedDomainName, LPDWORD cbReferencedDomainName, PSID_NAME_USE peUse);
	inline BOOL AllocateAndInitializeSid(
		PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
		BYTE nSubAuthorityCount,
		DWORD nSubAuthority0,
		DWORD nSubAuthority1,
		DWORD nSubAuthority2,
		DWORD nSubAuthority3,
		DWORD nSubAuthority4,
		DWORD nSubAuthority5,
		DWORD nSubAuthority6,
		DWORD nSubAuthority7)
	{
		FreeSid();
		if(::AllocateAndInitializeSid(
			pIdentifierAuthority,
			nSubAuthorityCount,
			nSubAuthority0,
			nSubAuthority1,
			nSubAuthority2,
			nSubAuthority3,
			nSubAuthority4,
			nSubAuthority5,
			nSubAuthority6,
			nSubAuthority7,
			&m_pSid))
		{
			m_bSystemAllocated = TRUE;
			return TRUE;
		}
		else
			return FALSE;
	}

	inline DWORD GetLengthSid() { return ::GetLengthSid(m_pSid); }
	inline PDWORD GetSidSubAuthority(DWORD dwSubAuthority) { return ::GetSidSubAuthority(m_pSid, dwSubAuthority); }
	inline PUCHAR GetSidSubAuthorityCount() { return ::GetSidSubAuthorityCount(m_pSid); }
	inline BOOL IsValidSid() { return ::IsValidSid(m_pSid); }

	inline operator PSID () { return m_pSid; } 
	inline BOOL operator == (CSid sid) { return ::EqualSid(sid.m_pSid, m_pSid); }
	
protected:

	BOOL  m_bSystemAllocated;
	DWORD m_dwSidSize;
	PSID m_pSid;

};


class CSecurityDescriptor  
{
public:
	CSecurityDescriptor();
	CSecurityDescriptor(PSECURITY_DESCRIPTOR);
	virtual ~CSecurityDescriptor();

	inline BOOL IsValidSecurityDescriptor() { return ::IsValidSecurityDescriptor(m_pSD); }
	inline BOOL SetSecurityDescriptorGroup(PSID pGroup, BOOL bGroupDefaulted) { return ::SetSecurityDescriptorGroup(m_pSD, pGroup, bGroupDefaulted); }
	inline BOOL SetSecurityDescriptorOwner(PSID pOwner, BOOL bOwnerDefaulted) { return ::SetSecurityDescriptorOwner(m_pSD, pOwner, bOwnerDefaulted); }
	inline BOOL SetSecurityDescriptorSacl(BOOL bSaclPresent, PACL pSacl, BOOL bSaclDefaulted)
		{ return ::SetSecurityDescriptorSacl(m_pSD, bSaclPresent, pSacl, bSaclDefaulted); }
	inline BOOL SetSecurityDescriptorDacl(BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted)
		{ return ::SetSecurityDescriptorDacl(m_pSD, bDaclPresent, pDacl, bDaclDefaulted); }
	inline BOOL GetSecurityDescriptorGroup(PSID* pGroup, LPBOOL lpGroupDefaulted) { return ::GetSecurityDescriptorGroup(m_pSD, pGroup, lpGroupDefaulted); }
	inline BOOL GetSecurityDescriptorOwner(PSID* pOwner, LPBOOL lpOwnerDefaulted) { return ::GetSecurityDescriptorGroup(m_pSD, pOwner, lpOwnerDefaulted); }
	inline BOOL GetSecurityDescriptorSacl(LPBOOL lpbSaclPresent, PACL* pSacl, LPBOOL lpbSaclDefaulted)
		{ return ::GetSecurityDescriptorSacl(m_pSD, lpbSaclPresent, pSacl, lpbSaclDefaulted); }
	inline BOOL GetSecurityDescriptorDacl(LPBOOL lpbDaclPresent, PACL* pDacl, LPBOOL lpbDaclDefaulted)
		{ return ::GetSecurityDescriptorSacl(m_pSD, lpbDaclPresent, pDacl, lpbDaclDefaulted); }

	inline operator PSECURITY_DESCRIPTOR () { return m_pSD; }

protected:
	PSECURITY_DESCRIPTOR m_pSD;

};


class CAcl  
{
public:
	CAcl();
	virtual ~CAcl();
	BOOL InitializeAcl(DWORD nAclLength);
	DWORD SetEntriesInAcl(ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS pListOfExplicitEntries);

	inline BOOL IsValidAcl() { return ::IsValidAcl(m_pACL); }
	inline BOOL AddAce(DWORD dwStartingAceIndex, LPVOID pAceList, DWORD nAceListLength)
		{ return ::AddAce(m_pACL, ACL_REVISION, dwStartingAceIndex, pAceList, nAceListLength);  }
	inline BOOL AddAccessAllowedAce(DWORD dwAccessMask, PSID pSID)
		{ return ::AddAccessAllowedAce(m_pACL, ACL_REVISION, dwAccessMask, pSID); }
	inline BOOL AddAccessDeniedAce(DWORD dwAccessMask, PSID pSID)
		{ return ::AddAccessDeniedAce(m_pACL, ACL_REVISION, dwAccessMask, pSID); }
	inline BOOL AddAuditAccessAce(DWORD dwAccessMask, PSID pSid, BOOL bAuditSuccess, BOOL bAuditFailure)
		{ return ::AddAuditAccessAce(m_pACL, ACL_REVISION, dwAccessMask, pSid, bAuditSuccess, bAuditFailure) ; }
	inline BOOL DeleteAce(DWORD dwAceIndex) { return ::DeleteAce(m_pACL, dwAceIndex); }
	inline BOOL FindFirstFreeAce(LPVOID * pAce) { return ::FindFirstFreeAce(m_pACL, pAce); }
	inline BOOL GetAce(DWORD dwAceIndex, LPVOID* pAce) { return ::GetAce(m_pACL, dwAceIndex, pAce); }

	inline operator PACL () { return m_pACL; }

protected:
	PACL m_pACL;

};

class CExplicitAccess : public EXPLICIT_ACCESS
{
public:
	CExplicitAccess() {}
	CExplicitAccess(DWORD dwAccessPermissions, ACCESS_MODE am, DWORD dwInheritance, TRUSTEE trAppliesTo)
	{
		grfAccessPermissions	= dwAccessPermissions;
		grfAccessMode			= am;
		grfInheritance			= dwInheritance;
		Trustee					= trAppliesTo;
	}
};

class CTrustee : public TRUSTEE
{
public:
	CTrustee() 
	{ 
		pMultipleTrustee = NULL; 
		MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE; 
	}
	CTrustee(TRUSTEE_TYPE type, LPCTSTR pszTrustee)
	{
		pMultipleTrustee = NULL; 
		MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE; 

		TrusteeForm = TRUSTEE_IS_NAME;
		ptstrName = (LPTSTR)pszTrustee;
	}
	CTrustee(TRUSTEE_TYPE type, PSID pSid)
	{
		pMultipleTrustee = NULL; 
		MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE; 

		TrusteeForm = TRUSTEE_IS_SID;
		ptstrName = (LPTSTR)pSid;
	}
};

#endif // !defined(AFX_SID_H__1CF2BF36_9316_11D3_B0B8_0040054C5E60__INCLUDED_)
