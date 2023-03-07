// InvestorCodeConverter.cpp: implementation of the InvestorCodeConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "PaxfeedInvestorCode.h"
#include "InvestorCodeConverter.h"

#include "ESource.h"

#include <sstream>

using namespace paxfeed;

InvestorCodeConverter::InvestorCodeConverter()  // throw(ESource)
{
  if (-1 == bind("1000", IC_BROKER))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("2000", IC_INSURANCE))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("3000", IC_INVEST))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("3100", IC_PRIVATE_EQUITY_FUND))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("4000", IC_BANK))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("5000", IC_MERCHANT_BANK))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("6000", IC_FUND))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("7000", IC_ETC_ORGAN))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("7100", IC_ETC))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("8000", IC_INDIVIDUAL))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("9000", IC_FOREIGNER_WITH_ID))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("9001", IC_FOREIGNER_WITHOUT_ID))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
  if (-1 == bind("9999", IC_WHOLE))
    throw ESource("cannot bind investor code", __FILE__, __LINE__);
}

InvestorCodeConverter::~InvestorCodeConverter()
{

}

const ACE_CString& InvestorCodeConverter::getInvestor(const ACE_CString& raw)  // throw(ESource)
{
  BaseClass::ENTRY* entry = 0;
  if (0 == find(raw, entry))
    return entry->int_id_;
  else {
    std::ostringstream os;
    os << "cannot find investor code(" << raw.c_str() << ")";
    throw ESource(os.str(), __FILE__, __LINE__);
  }
}

