// InvestorCodeConverter.h: interface for the InvestorCodeConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INVESTORCODECONVERTER_H__A48CD9BE_8D9A_431A_A2D6_74A573DCEA8C__INCLUDED_)
#define AFX_INVESTORCODECONVERTER_H__A48CD9BE_8D9A_431A_A2D6_74A573DCEA8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ace/SStringfwd.h"
#include "ace/String_Base.h"
#include "ace/Null_Mutex.h"
#include "ace/Hash_Map_Manager_T.h"

class InvestorCodeConverter : public ACE_Hash_Map_Manager<ACE_CString, ACE_CString, ACE_Null_Mutex>
{
public:
  typedef ACE_Hash_Map_Manager<ACE_CString, ACE_CString, ACE_Null_Mutex> BaseClass;
public:
  InvestorCodeConverter();  // throw(ESource)
  ~InvestorCodeConverter();
  const ACE_CString& getInvestor(const ACE_CString& raw);  // throw(ESource)
};

#endif // !defined(AFX_INVESTORCODECONVERTER_H__A48CD9BE_8D9A_431A_A2D6_74A573DCEA8C__INCLUDED_)
