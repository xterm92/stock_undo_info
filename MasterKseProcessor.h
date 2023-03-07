// MasterKseProcessor.h: interface for the MasterKseProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASTERKSEPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_)
#define AFX_MASTERKSEPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MasterProcessor.h"
#include "ExturePlusInternetKse.h"

class MasterKseProcessor: public MasterProcessor
{
    public:
        MasterKseProcessor(const ACE_CString &frameId, const ACE_CString &packet, int serial);
		MasterKseProcessor(const ACE_CString &frameId, const ACE_CString &packet, int serial, ExturePlusKseMaster kseUsage);
        ~MasterKseProcessor();

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
        ACE_CString getIndustryClassCode(const ACE_CString& index2, const ACE_CString& index3);
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

        ACE_CString getSignSymbol(const ACE_CString& raw);

#if(1)
		ACE_CString getCommonPriceDoubleInteger(const ACE_CString& rawParPrice);
		ACE_CString getSymbolUpCode(const ACE_CString& raw);
#endif

    public:
        bool isValidPacket();
        ACE_CString getSymbol();
        void printPacket(const ExturePlusKseMaster kse);

#if(0)
		ACE_CString MasterKseProcessor::getStockMainBatchGroupID(const ACE_CString& raw);
		ACE_CString MasterKseProcessor::getStockJisuBatchGroupID(const ACE_CString& raw);
#endif

        ExturePlusKseMaster getExturePlusKseMaster() const;

    private:
        bool isValidPacket_;
        ACE_CString symbol_;
        ExturePlusKseMaster kse_;

};

#endif // !defined(AFX_MASTERKSEPROCESSOR_H__8C335928_7B77_41E3_AC5E_A6336148EE30__INCLUDED_)
