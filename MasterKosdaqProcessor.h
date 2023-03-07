// MasterKosdaqProcessor.h: interface for the MasterKosdaqProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASTERKOSDAQPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_)
#define AFX_MASTERKOSDAQPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MasterProcessor.h"
#include "ExturePlusInternetKosdaq.h"

class MasterKosdaqProcessor: public MasterProcessor
{
    public:
        MasterKosdaqProcessor(const ACE_CString &frameId, const ACE_CString &packet, int serial);
		MasterKosdaqProcessor(const ACE_CString &frameId, const ACE_CString &packet, int serial, ExturePlusKosdaqMaster kosdaqUsage);
        ~MasterKosdaqProcessor();

    protected:
        BYTE getExchange();

    protected:
        ACE_CString getSymbolSubtype(const ACE_CString& raw);
        ACE_CString getManufacturingType(const ACE_CString& raw);
        ACE_CString getSuspensionType(const ACE_CString& raw);

        ACE_CString getEx(const ACE_CString& raw);
        ACE_CString getSplitMerge(const ACE_CString& rawEx);

        ACE_CString getTotalMarketPriceType(const ACE_CString& raw);
        ACE_CString getKogiType(const ACE_CString& raw);
        ACE_CString getIndustryClassCode(const ACE_CString& industryClassMid, const ACE_CString& industryClassSmall);
        ACE_CString getTradeUnit(const ACE_CString& raw);
        ACE_CString getIsDividendIndexStock(const ACE_CString& raw);

        ACE_CString getKospi50(const ACE_CString& raw);
        ACE_CString getKospi100(const ACE_CString& raw);
        ACE_CString getEpsSign(const ACE_CString& raw);
        ACE_CString getInvestmentWarningType(const ACE_CString& rawCaution);
        ACE_CString getManagementType(const ACE_CString& raw);
        ACE_CString getETFType(const ACE_CString& raw);

        ACE_CString getReValuationReason(const ACE_CString& raw);
        ACE_CString getParPriceInteger(const ACE_CString& rawParPrice);
        ACE_CString getParPriceRealNumber(const ACE_CString& rawParPrice);

        ACE_CString getMasterIncreaseType(const ACE_CString& raw);

        ACE_CString getStockType(const ACE_CString& raw);

        ACE_CString getIsOpenPriceBecomeStdPrice(const ACE_CString& raw);
        bool isUnclassifiedIndexBusinessType(const ACE_CString& indexBusinessTypeLarge, const ACE_CString& indexBusinessTypeMedium, const ACE_CString& indexBusinessTypeSmall);

        ACE_CString getSignSymbol(const ACE_CString& raw);

#if(1)
		ACE_CString getCommonPriceDoubleInteger(const ACE_CString& rawParPrice);
		ACE_CString getSymbolUpCode(const ACE_CString& raw);
#endif

    public:
        bool isValidPacket();
        ACE_CString getSymbol();

#if(0)
		ACE_CString MasterKosdaqProcessor::getStockMainBatchGroupID(const ACE_CString& raw);
		ACE_CString MasterKosdaqProcessor::getStockJisuBatchGroupID(const ACE_CString& raw);
#endif

        ACE_CString getVenture(const ACE_CString& raw);
        ACE_CString getCautionType(const ACE_CString& rawAlarm);

    private:
        bool isValidPacket_;
        ACE_CString symbol_;
        ExturePlusKosdaqMaster kse_;

};

#endif // !defined(AFX_MASTERKOSDAQPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_)
