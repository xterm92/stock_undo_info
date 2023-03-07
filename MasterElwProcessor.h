// MasterElwProcessor.h: interface for the MasterElwProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASTERELWPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_)
#define AFX_MASTERELWPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MasterProcessor.h"
#include "ExturePlusInternetElw.h"

class MasterElwProcessor: public MasterProcessor
{
    public:
        MasterElwProcessor(int serial);
        virtual ~MasterElwProcessor();

#if(1)
		int masterGroupCProc(const ACE_CString &packet);
#endif

        ACE_CString getKospi50(const ACE_CString& raw);
        ACE_CString getKospi100(const ACE_CString& raw);
        ACE_CString getSymbolSubtype(const ACE_CString& raw);
        ACE_CString getManufacturingType(const ACE_CString& raw);
        ACE_CString getManagementType(const ACE_CString& raw);
        ACE_CString getSuspensionType(const ACE_CString& raw);
        ACE_CString getEx(const ACE_CString& rawEx);
        ACE_CString getSplitMerge(const ACE_CString& rawEx);
        ACE_CString getTotalMarketPriceType(const ACE_CString& raw);
        ACE_CString getKogiType(const ACE_CString& raw);
        ACE_CString getIndustryClassCode(const ACE_CString& index2, const ACE_CString& index3);
        ACE_CString getTradeUnit(const ACE_CString& raw);
        ACE_CString getInvestmentWarningType(const ACE_CString& rawAlarm);
        ACE_CString getStockGroupID(const ACE_CString& raw);
        ACE_CString getIsDividendIndexStock(const ACE_CString& raw);
        ACE_CString getEpsSign(const ACE_CString& raw);
        ACE_CString getETFType(const ACE_CString& raw);
        ACE_CString getReValuationReason(const ACE_CString& raw);
        ACE_CString getParPriceInteger(const ACE_CString& rawParPrice);
        ACE_CString getParPriceRealNumber(const ACE_CString& rawParPrice);
        ACE_CString getMasterIncreaseType(const ACE_CString& raw);
        ACE_CString getStockType(const ACE_CString& raw);
        ACE_CString getIsOpenPriceBecomeStdPrice(const ACE_CString& raw);
        ACE_CString getExchange(const ACE_CString& raw);

#if(1)
	    ACE_CString getSymbolUpCode(const ACE_CString& raw);
#endif


    protected:
        BYTE MasterElwProcessor::getExchange();
};

#endif // !defined(AFX_MASTERELWPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_)
