#include <algorithm>
#include <sstream>
#include <exception>
#include <iomanip>
#include "InvestorCodeConverter.h"
#include "InternetKosdaqChannelProcessor.h"
#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "ace/Log_Msg.h"
#include "MMapAllocator.h"
#include "PaxfeedStatus.h"
#include "PaxfeedStringUtil.h"
#include "MasterKosdaqProcessor.h"
#include "TickFilter.h"
#include "Tickerplant.h"
#include "SimpleStringUtil.h"

#include <boost/algorithm/string.hpp>

using namespace paxfeed;

InternetKosdaqChannelProcessor::InternetKosdaqChannelProcessor(const ACE_CString &channelName)
        : InternetChannelProcessor::InternetChannelProcessor(channelName)
{
    initTradeTypeList();
}

InternetKosdaqChannelProcessor::~InternetKosdaqChannelProcessor()
{
}

int InternetKosdaqChannelProcessor::reset()
{
    InternetChannelProcessor::reset();
    return 0;
}

int InternetKosdaqChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString frameID(packet.substr(0, 2));
    ACE_CString trID(packet.substr(0, 5));
	ACE_CString dataType(packet.substr(0, 5));
    ACE_CString exchangeID(packet.substr(4, 1));

	int hasValue;
	ExturePlusKosdaqMaster kosdaqUsage;

	if(dataType=="A001Q")
	{
		MasterKosdaqProcessor masterProc(frameID, packet, getSerial());
        if ( masterProc.isValidPacket() == true )
        {
			int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));

			memcpy(&kosdaqUsage, packet.c_str(), packet.length());
			ACE_CString stockCode1(kosdaqUsage.stockCode, sizeof(kosdaqUsage.stockCode));

			hasValue = masterMapKosdaq_->find(stockCode1, kosdaqUsage, ALLOCATOR::instance());

			if ( hasValue == -1 )
			{
				masterMapKosdaq_->bind(ACE_CString(stockCode1.c_str(), ALLOCATOR::instance()), kosdaqUsage, ALLOCATOR::instance());
			}
        }
	}
#if(0)
	else if(dataType=="A001X")
	{
		MasterKosdaqProcessor masterProc(frameID, packet, getSerial());
        if ( masterProc.isValidPacket() == true )
        {
			int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));

			memcpy(&kosdaqUsage, packet.c_str(), packet.length());
			ACE_CString stockCode1(kosdaqUsage.stockCode, sizeof(kosdaqUsage.stockCode));

			hasValue = masterMapKosdaq_->find(stockCode1, kosdaqUsage, ALLOCATOR::instance());

			if ( hasValue == -1 )
			{
				masterMapKosdaq_->bind(ACE_CString(stockCode1.c_str(), ALLOCATOR::instance()), kosdaqUsage, ALLOCATOR::instance());
			}
        }
	}
#endif
	else if(dataType=="CA01Q")
	{
		ExturePlusKosdaqJisuMaster kosdaqjisu;
        memcpy(&kosdaqjisu, packet.c_str(), packet.length());

		ACE_CString stockCode2(kosdaqjisu.stockCode, sizeof(kosdaqjisu.stockCode));
		hasValue = masterMapKosdaq_->find(stockCode2, kosdaqUsage, ALLOCATOR::instance());

		if ( hasValue == -1 )
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::masterMapKosdaq_->find] Error symbol:[%s] hasValue:[%d]\n" , getCurrentTimestamp().c_str() , stockCode2.c_str() , hasValue ));

			return(0);
		}
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.dataClass),kosdaqUsage.dataClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.infoMarketClass),kosdaqUsage.infoMarketClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.distributeStockIndex),kosdaqUsage.distributeStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.distributeTotalStockIndex),kosdaqUsage.distributeTotalStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.sendDate),kosdaqUsage.sendDate));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.stockCode),kosdaqUsage.stockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.stockSeq),kosdaqUsage.stockSeq));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.abbrStockCode),kosdaqUsage.abbrStockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.abbrStockNameKor),kosdaqUsage.abbrStockNameKor));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.abbrStockNameEng),kosdaqUsage.abbrStockNameEng));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.infoDivisionGroupNo),kosdaqUsage.infoDivisionGroupNo));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.MarketProductGroupID),kosdaqUsage.MarketProductGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.stockGroupID),kosdaqUsage.stockGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isUnitTrade),kosdaqUsage.isUnitTrade));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.exClassCode),kosdaqUsage.exClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.faceValueChangeClassCode),kosdaqUsage.faceValueChangeClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isOpenPriceBecomeStdPrice),kosdaqUsage.isOpenPriceBecomeStdPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isRevaluationStockReason),kosdaqUsage.isRevaluationStockReason));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isStandardPriceChangeStock),kosdaqUsage.isStandardPriceChangeStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.randomEndTriggerConditionCode),kosdaqUsage.randomEndTriggerConditionCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isMarketAlarmDangerNotice),kosdaqUsage.isMarketAlarmDangerNotice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.marketAlarmClassCode),kosdaqUsage.marketAlarmClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isCorporateGovernanceFine),kosdaqUsage.isCorporateGovernanceFine));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isManagementStock),kosdaqUsage.isManagementStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isInsincerityPublicNewsAppoint),kosdaqUsage.isInsincerityPublicNewsAppoint));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isBackDoorListing),kosdaqUsage.isBackDoorListing));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isTradeStop),kosdaqUsage.isTradeStop));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.standardIndustryCode),kosdaqUsage.standardIndustryCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.SmallMediumEnterprisesIs),kosdaqUsage.SmallMediumEnterprisesIs));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isCorporateGovernanceIndexStock),kosdaqUsage.isCorporateGovernanceIndexStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.investOrganClassCode),kosdaqUsage.investOrganClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.standardPrice),kosdaqUsage.standardPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayClosePriceClassCode),kosdaqUsage.ydayClosePriceClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayClosePrice),kosdaqUsage.ydayClosePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayAccmVolume),kosdaqUsage.ydayAccmVolume));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayAccmAmount),kosdaqUsage.ydayAccmAmount));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.upLimitPrice),kosdaqUsage.upLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.downLimitPrice),kosdaqUsage.downLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.substitutePrice),kosdaqUsage.substitutePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.faceValue),kosdaqUsage.faceValue));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.issuePrice),kosdaqUsage.issuePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.listingDate),kosdaqUsage.listingDate));

		MasterKosdaqProcessor masterProc(frameID, packet, getSerial(), kosdaqUsage);
		if ( masterProc.isValidPacket() == true )
        {
			int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , 
				getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));
        }
	}
#if(0)
	else if(dataType=="CA01X")
	{
		ExturePlusKosdaqJisuMaster kosdaqjisu;
        memcpy(&kosdaqjisu, packet.c_str(), packet.length());

		ACE_CString stockCode2(kosdaqjisu.stockCode, sizeof(kosdaqjisu.stockCode));
		hasValue = masterMapKosdaq_->find(stockCode2, kosdaqUsage, ALLOCATOR::instance());

		if ( hasValue == -1 )
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::masterMapKosdaq_->find] Error symbol:[%s] hasValue:[%d]\n" , getCurrentTimestamp().c_str() , stockCode2.c_str() , hasValue ));

			return(0);
		}
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.dataClass),kosdaqUsage.dataClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.infoMarketClass),kosdaqUsage.infoMarketClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.distributeStockIndex),kosdaqUsage.distributeStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.distributeTotalStockIndex),kosdaqUsage.distributeTotalStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.sendDate),kosdaqUsage.sendDate));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.stockCode),kosdaqUsage.stockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.stockSeq),kosdaqUsage.stockSeq));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.abbrStockCode),kosdaqUsage.abbrStockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.abbrStockNameKor),kosdaqUsage.abbrStockNameKor));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.abbrStockNameEng),kosdaqUsage.abbrStockNameEng));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.infoDivisionGroupNo),kosdaqUsage.infoDivisionGroupNo));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.MarketProductGroupID),kosdaqUsage.MarketProductGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.stockGroupID),kosdaqUsage.stockGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isUnitTrade),kosdaqUsage.isUnitTrade));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.exClassCode),kosdaqUsage.exClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.faceValueChangeClassCode),kosdaqUsage.faceValueChangeClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isOpenPriceBecomeStdPrice),kosdaqUsage.isOpenPriceBecomeStdPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isRevaluationStockReason),kosdaqUsage.isRevaluationStockReason));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isStandardPriceChangeStock),kosdaqUsage.isStandardPriceChangeStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.randomEndTriggerConditionCode),kosdaqUsage.randomEndTriggerConditionCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isMarketAlarmDangerNotice),kosdaqUsage.isMarketAlarmDangerNotice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.marketAlarmClassCode),kosdaqUsage.marketAlarmClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isCorporateGovernanceFine),kosdaqUsage.isCorporateGovernanceFine));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isManagementStock),kosdaqUsage.isManagementStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isInsincerityPublicNewsAppoint),kosdaqUsage.isInsincerityPublicNewsAppoint));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isBackDoorListing),kosdaqUsage.isBackDoorListing));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isTradeStop),kosdaqUsage.isTradeStop));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.standardIndustryCode),kosdaqUsage.standardIndustryCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.SmallMediumEnterprisesIs),kosdaqUsage.SmallMediumEnterprisesIs));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.isCorporateGovernanceIndexStock),kosdaqUsage.isCorporateGovernanceIndexStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.investOrganClassCode),kosdaqUsage.investOrganClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.standardPrice),kosdaqUsage.standardPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayClosePriceClassCode),kosdaqUsage.ydayClosePriceClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayClosePrice),kosdaqUsage.ydayClosePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayAccmVolume),kosdaqUsage.ydayAccmVolume));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.ydayAccmAmount),kosdaqUsage.ydayAccmAmount));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.upLimitPrice),kosdaqUsage.upLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.downLimitPrice),kosdaqUsage.downLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.substitutePrice),kosdaqUsage.substitutePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.faceValue),kosdaqUsage.faceValue));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.issuePrice),kosdaqUsage.issuePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKosdaqChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kosdaqUsage.listingDate),kosdaqUsage.listingDate));

		MasterKosdaqProcessor masterProc(frameID, packet, getSerial(), kosdaqUsage);
		if ( masterProc.isValidPacket() == true )
        {
			int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , 
				getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));
        }
	}
#endif
	else if(dataType=="B201Q")
	{	
		handleRecoveryTotalTrade(packet);
    }
	else if(dataType=="C401Q")
	{	
		handleBulkTrade(packet);
    }
	else if(dataType=="C001Q")
	{	
		handleInvestorIndex(packet);
    }
	else if(dataType=="A301Q")
	{	
		handleTrade(packet);
	}
	else if(dataType=="A401Q")
	{	
		handleDeterminedBasePrice(packet);
    }
	else if(dataType=="A701Q")
	{	
		handleMarketOperationTS(packet);
    }
	else if(dataType=="A801Q")
	{	
		handleIssueInformationDisclosure(packet);
    }
	else if(dataType=="B501Q")
	{	
		handleUpDown(packet);
    }
	else if(dataType=="B601Q")
	{	
		handleQuote10(packet);
    }
	else if(dataType=="B901Q")
	{	
		handleSecuritiesTrade(packet);
    }
	else if(dataType=="C301Q")
	{	
		handleProgramTrade(packet);
    }
	else if(dataType=="I601Q")
	{	
		handleKOSDAQIssueEventInformation(packet);
    }
	else if(dataType=="I801Q")
	{	
		handleShortSellingInfo(packet);
    }
	else if(dataType=="J001Q")
	{	
		handleProgramTradeTotal(packet);
    }
	else if(dataType=="M401Q")
	{	
		handleMarketOperationScheduleDisclosure(packet);
    }
	else if(dataType=="O601Q")
	{	
		handleQuantityAllocation(packet);
    }
	else if(dataType=="R801Q")
	{	
		handleKOSDAQVolatilityInterruptionPerInstrument(packet);
    }
#if(0)
	else if(dataType=="B201X")
	{	
		handleRecoveryTotalTrade(packet);
    }
	else if(dataType=="C401X")
	{	
		handleBulkTrade(packet);
    }
	else if(dataType=="C001X")
	{	
		handleInvestorIndex(packet);
    }
	else if(dataType=="A301X")
	{	
		handleTrade(packet);
	}
	else if(dataType=="A401X")
	{	
		handleDeterminedBasePrice(packet);
    }
	else if(dataType=="A701X")
	{	
		handleMarketOperationTS(packet);
    }
	else if(dataType=="A801X")
	{	
		handleIssueInformationDisclosure(packet);
    }
	else if(dataType=="B601X")
	{	
		handleQuote10(packet);
    }
	else if(dataType=="B901X")
	{	
		handleSecuritiesTrade(packet);
    }
	else if(dataType=="I601X")
	{	
		handleKOSDAQIssueEventInformation(packet);
    }
	else if(dataType=="M401X")
	{	
		handleMarketOperationScheduleDisclosure(packet);
    }
	else if(dataType=="O601X")
	{	
		handleQuantityAllocation(packet);
    }
#endif
#if(1)
	else if(dataType=="IA000")
	{
		ExturePlusTotalKseIndex totalkosdaq;
		ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

		ACE_CString jisuFrameId(totalkosdaq.dataID, sizeof ( totalkosdaq.dataID ));
		jisuFrameId = getSymbolFrameId(jisuFrameId);

		
		if ( jisuFrameId == "E4" )// KOSDAQ지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "E6" )// KOSTAR지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "E5" )// KOSDAQ예상지수
		{
			handleIndexForecast(packet);
		}
	}
	else if(dataType=="IB000")
	{
		ExturePlusTotalKseIndex totalkosdaq;
		ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

		ACE_CString jisuFrameId(totalkosdaq.dataID, sizeof ( totalkosdaq.dataID ));
		jisuFrameId = getSymbolFrameId(jisuFrameId);

		if ( jisuFrameId == "E4" )// KOSDAQ지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "E6" )// KOSTAR지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "E5" )// KOSDAQ예상지수
		{
			handleIndexForecast(packet);
		}
	}
#endif
	else
	{
		if ( frameID == "DT" )
		{
			handleInvestorStock(packet);
		}
		else if ( frameID == "I2" )
		{
			handleKoscomLineLKInfo(packet);
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::processPacket] polling Data:[%s]\n" , getCurrentTimestamp().c_str() , packet.c_str() ));
		}
		else if ( frameID == "ZZ" )
		{
			// 지수 리커버리(내부)
			handleCustomIndexRecovery(packet);
		}
		else
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::processPacket] trID:[%s]\n" , getCurrentTimestamp().c_str() , trID.c_str() ));
		}
	}

    return 0;
}

bool InternetKosdaqChannelProcessor::isValidSymbol(const ACE_CString& symbol)
{
    ACE_CString isNormalstockCode(symbol.substr(0, 3));

    return true;
}

int InternetKosdaqChannelProcessor::handleIndex(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_TOTAL_KOSDAQ_INDEX_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleIndex] Skip : %s, %d : EXTURE_PLUS_TOTAL_KOSDAQ_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , 
			getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_TOTAL_KOSDAQ_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

#if(1)
	ExturePlusTotalKosdaqIndex totalkosdaq;
	ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

    ExturePlusKosdaqIndex kosdaq;

	::memcpy(kosdaq.time, totalkosdaq.time, sizeof(kosdaq.time));
	::memcpy(kosdaq.index, totalkosdaq.index, sizeof(kosdaq.index));
	::memcpy(kosdaq.sign, totalkosdaq.sign, sizeof(kosdaq.sign));
	::memcpy(kosdaq.gap, totalkosdaq.gap, sizeof(kosdaq.gap));
	::memcpy(kosdaq.tradeVolume, totalkosdaq.tradeVolume, sizeof(kosdaq.tradeVolume));
	::memcpy(kosdaq.tradeAmount, totalkosdaq.tradeAmount, sizeof(kosdaq.tradeAmount));
#endif

    ACE_CString symbol;

#if(1)
	Trade trade;

	ACE_CString businesstypecode(totalkosdaq.dataID, sizeof ( totalkosdaq.dataID ));
	ACE_CString frameId(totalkosdaq.dataID, sizeof ( totalkosdaq.dataID ));

    int index = atoi(getSymbolUpCode(businesstypecode).c_str());
	frameId = getSymbolFrameId(frameId);
#endif

    symbol = getIndexSymbol(index, frameId);

    int hasValue = tradeMap_->find(symbol, trade, ALLOCATOR::instance());
    trade.market = getMarketStepInIndex(ACE_CString(kosdaq.time, sizeof ( kosdaq.time )));
    trade.upDown = getUpDownInIndex(ACE_CString(kosdaq.sign, sizeof kosdaq.sign));
    trade.accmVolume = atof(ACE_CString(kosdaq.tradeVolume, sizeof kosdaq.tradeVolume).c_str());
    trade.amount = atof(ACE_CString(kosdaq.tradeAmount, sizeof kosdaq.tradeAmount).c_str());

#if(1)
    trade.close = atoi(ACE_CString(kosdaq.index, sizeof kosdaq.index).c_str()) * 100;
    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str()) * 100;
#endif

    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;
    trade.tradeVolume = trade.accmVolume - getTotalAccmVolume(symbol);

    if ( trade.tradeVolume < 0 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleIndex] Skip : %s,%d : net volume error symbol:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , symbol.c_str() , trade.tradeVolume ), -1);
    }

    setTotalAccmVolume(symbol, trade.accmVolume);
    setTotalAccmAmount(symbol, trade.amount);

    int tickTime = getTickTime(ACE_CString(kosdaq.time, sizeof kosdaq.time), frameId);

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;

#if(1)
        trade.exchange = EXCHANGE_KOSDAQ;
#endif

        trade.symbolType = SYMBOL_INDEX;
        trade.decimalPoint = DECIMAL_2;
        trade.tradeTime = tickTime;
        memcpy(&trade.symbol, symbol.c_str(), std::min(sizeof trade.symbol, symbol.length()));

        trade.open = trade.close;
        trade.high = trade.close;
        trade.low = trade.close;

        trade.openMin = trade.close;
        trade.highMin = trade.close;
        trade.lowMin = trade.close;
        trade.volumeMin = trade.tradeVolume;
        tradeMap_->bind(ACE_CString(symbol.c_str(), ALLOCATOR::instance()), trade, ALLOCATOR::instance());
    }
    else
    {
        if ( trade.close > trade.high )
        {
            trade.high = trade.close;
        }

        if ( trade.close < trade.low )
        {
            trade.low = trade.close;
        }

        int previousTime = trade.tradeTime;
        trade.tradeTime = tickTime;

        if ( ( trade.tradeTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
        {
            trade.volumeMin += trade.tradeVolume;

            if ( trade.close > trade.highMin )
            {
                trade.highMin = trade.close;
            }
            if ( trade.close < trade.lowMin )
            {
                trade.lowMin = trade.close;
            }
        }
        else
        {
            trade.volumeMin = trade.tradeVolume;
            trade.openMin = trade.close;
            trade.highMin = trade.close;
            trade.lowMin = trade.close;
        }
        ACE_CString oldKey;
        Trade oldVal;
        tradeMap_->rebind(ACE_CString(symbol.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());
    }
    char buf[TRADE_SIZE];
    memcpy(buf, &trade, std::min(sizeof buf, sizeof trade));

#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KOSDAQ);
#endif

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIndex] dataClass:[%.*s],infoMarketClass:[%.*s],dataID:[%.*s],standardCode:[%.*s],symbol:[%s]\tresult:[%d]\n" , 
		getCurrentTimestamp().c_str(), 
		sizeof(totalkosdaq.dataClass),totalkosdaq.dataClass, 
		sizeof(totalkosdaq.infoMarketClass),totalkosdaq.infoMarketClass, 
		sizeof(totalkosdaq.dataID),totalkosdaq.dataID, 
		sizeof(totalkosdaq.standardCode),totalkosdaq.standardCode, 
		symbol.c_str() , 
		result ));

#if(1)
printPacketTrade(trade);
#endif

    return result;
}

#if(1)
int InternetKosdaqChannelProcessor::handleIndexForecast(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_TOTAL_KOSDAQ_INDEX_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleIndexForecast] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
    }

    LogFrameCount(packet.substr(0, 2).c_str());

#if(1)
    ExturePlusTotalKosdaqIndex totalkosdaq;
	ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

    ExturePlusKosdaqIndex kosdaq;

	::memcpy(kosdaq.time, totalkosdaq.time, sizeof(kosdaq.time));
	::memcpy(kosdaq.index, totalkosdaq.index, sizeof(kosdaq.index));
	::memcpy(kosdaq.sign, totalkosdaq.sign, sizeof(kosdaq.sign));
	::memcpy(kosdaq.gap, totalkosdaq.gap, sizeof(kosdaq.gap));
	::memcpy(kosdaq.tradeVolume, totalkosdaq.tradeVolume, sizeof(kosdaq.tradeVolume));
	::memcpy(kosdaq.tradeAmount, totalkosdaq.tradeAmount, sizeof(kosdaq.tradeAmount));
#endif

    ACE_CString symbol;

#if(1)
	Trade trade;

	ACE_CString businesstypecode(totalkosdaq.dataID, sizeof ( totalkosdaq.dataID ));
	ACE_CString frameId(totalkosdaq.dataID, sizeof ( totalkosdaq.dataID ));

    int index = atoi(getSymbolUpCode(businesstypecode).c_str());
	frameId = getSymbolFrameId(frameId);
#endif

    symbol = getIndexSymbol(index, frameId);
    int hasValue = tradeMap_->find(symbol, trade, ALLOCATOR::instance());

    trade.market = getMarketStepInIndex(ACE_CString(kosdaq.time, sizeof ( kosdaq.time )));
    trade.upDown = getUpDownInIndex(ACE_CString(kosdaq.sign, sizeof kosdaq.sign));
    trade.accmVolume = atof(ACE_CString(kosdaq.tradeVolume, sizeof kosdaq.tradeVolume).c_str());
    trade.amount = atof(ACE_CString(kosdaq.tradeAmount, sizeof kosdaq.tradeAmount).c_str());

#if(1)
    trade.close = atoi(ACE_CString(kosdaq.index, sizeof kosdaq.index).c_str()) * 100;
    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str()) * 100;
#endif
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    //예상지수에서는 상황에 따라 체결이 빠지는 경우도 있으므로, 단위 체결량을 산출할 수 없다.
    //따라서, 누적체결량을 단위체결량으로 강제 할당 한다. 

    trade.tradeVolume = trade.accmVolume;
    if ( trade.tradeVolume < 0 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleIndexForecast] Skip : %s,%d : net volume error symbol:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , symbol.c_str() , trade.tradeVolume ), -1);
    }

    int tickTime = getTickTime(ACE_CString(kosdaq.time, sizeof kosdaq.time), frameId);

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;

#if(1)
		trade.exchange = EXCHANGE_KOSDAQ;
#endif

        trade.symbolType = SYMBOL_INDEX;
        trade.decimalPoint = DECIMAL_2;
        trade.tradeTime = tickTime;
        memcpy(&trade.symbol, symbol.c_str(), std::min(sizeof trade.symbol, symbol.length()));
        trade.open = trade.close;
        trade.high = trade.close;
        trade.low = trade.close;
        trade.openMin = trade.close;
        trade.highMin = trade.close;
        trade.lowMin = trade.close;
        trade.volumeMin = trade.tradeVolume;
        tradeMap_->bind(ACE_CString(symbol.c_str(), ALLOCATOR::instance()), trade, ALLOCATOR::instance());
    }
    else
    {
        if ( trade.close > trade.high )
        {
            trade.high = trade.close;
        }

        if ( trade.close < trade.low )
        {
            trade.low = trade.close;
        }

        int previousTime = trade.tradeTime;
        trade.tradeTime = tickTime;

        if ( ( trade.tradeTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
        {
            trade.volumeMin += trade.tradeVolume;
            if ( trade.close > trade.highMin )
            {
                trade.highMin = trade.close;
            }
            if ( trade.close < trade.lowMin )
            {
                trade.lowMin = trade.close;
            }
        }
        else
        {
            trade.volumeMin = trade.tradeVolume;
            trade.openMin = trade.close;
            trade.highMin = trade.close;
            trade.lowMin = trade.close;
        }
        ACE_CString oldKey;
        Trade oldVal;
        tradeMap_->rebind(ACE_CString(symbol.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());
    }

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, std::min(sizeof buf, sizeof trade));


#if(1)
    int result = 0;

	result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KOSDAQ);
#endif

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIndexForecast] dataClass:[%.*s],infoMarketClass:[%.*s],dataID:[%.*s],standardCode:[%.*s],symbol:[%s]\tresult:[%d]\n" , 
		getCurrentTimestamp().c_str(), 
		sizeof(totalkosdaq.dataClass),totalkosdaq.dataClass, 
		sizeof(totalkosdaq.infoMarketClass),totalkosdaq.infoMarketClass, 
		sizeof(totalkosdaq.dataID),totalkosdaq.dataID, 
		sizeof(totalkosdaq.standardCode),totalkosdaq.standardCode, 
		symbol.c_str() , 
		result ));

    return result;
}
#endif

int InternetKosdaqChannelProcessor::handleInvestorIndex(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_TOTAL_INVESTOR_INDEX_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestor] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_INVESTOR_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_INVESTOR_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
    }

    int result = 0;
    ACE_CString stockCode;
    try
    {
        // log frame count status
        LogFrameCount(packet.substr(0, 2).c_str());

#if(1)
		ExturePlusKosdaqTotalInvestorIndex totalkosdaq;
		ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

        ExturePlusKosdaqInvestorIndex kosdaq;

		::memcpy(kosdaq.calculationTime,totalkosdaq.calculationTime,sizeof(kosdaq.calculationTime));
		::memcpy(kosdaq.investorCode,totalkosdaq.investorCode,sizeof(kosdaq.investorCode));
		::memcpy(kosdaq.askTradeVolume,totalkosdaq.askTradeVolume,sizeof(kosdaq.askTradeVolume));
		::memcpy(kosdaq.askTradeAmount,totalkosdaq.askTradeAmount,sizeof(kosdaq.askTradeAmount));
		::memcpy(kosdaq.bidTradeVolume,totalkosdaq.bidTradeVolume,sizeof(kosdaq.bidTradeVolume));
		::memcpy(kosdaq.bidTradeAmount,totalkosdaq.bidTradeAmount,sizeof(kosdaq.bidTradeAmount));
#endif

        // 2020.11.26
        ACE_CString packetPrefix(packet.substr(0, 5).c_str());
        if ( packetPrefix != "C001Q" )
        {
            ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorIndex|DEBUG] skip......\tpacketPrefix:[%s]\n" , getCurrentTimestamp().c_str() , packetPrefix.c_str() ));
            return ( 0 );
        }

        Investor investor;
        ::memset(&investor, 0, sizeof(Investor));
        investor.subtype = SYMBOL_STOCK;

#if(1)
        investor.exchange = EXCHANGE_KOSDAQ;
#endif

        investor.symbolType = SYMBOL_INDEX;

#if(1)
	    ACE_CString businesstype(totalkosdaq.jisuIdentifiation, sizeof ( totalkosdaq.jisuIdentifiation ));
        int code = atoi(getSymbolUpCode(businesstype).c_str());

		ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorIndex|DEBUG] code:[%d],businesstype:[%s],jisuIdentifiation[%.*s]\n" , getCurrentTimestamp().c_str() , code , businesstype.c_str() , sizeof ( totalkosdaq.jisuIdentifiation ), totalkosdaq.jisuIdentifiation ));
#endif
        stockCode = getIndexSymbol(code, "E4"); //E4 : 코스닥지수

        /*
         * KRX100 은 투자자 데이터를 보내지 않는다.
         * 일단 return 시키고
         * 어느 업종 코드가 KRI000000000 으로 매핑되는지 찾는다.
         */
        if ( stockCode == "KRI000000000" )
        {
            ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorIndex|DEBUG] code:[%d]\tstockCode:[%s]\tpacket:[%s]\n" , getCurrentTimestamp().c_str() , code , stockCode.c_str() , packet.c_str() ));
            return ( 0 );
        }
		else
		{
			ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorIndex|DEBUG] code:[%d]\tstockCode:[%s]\tpacket:[%s]\n" , getCurrentTimestamp().c_str() , code , stockCode.c_str() , packet.c_str() ));
		}

        ACE_OS::memcpy(&investor.symbol, stockCode.c_str(), std::min(sizeof investor.symbol, stockCode.length()));

        // 투자자코드 확인필요..

        ACE_CString rawInvestorCode(kosdaq.investorCode, sizeof ( kosdaq.investorCode ));
        const ACE_CString& investorCode = invConv_.getInvestor(rawInvestorCode);
        ::memcpy(& ( investor.investor ), investorCode.c_str(), 4);

        investor.askVolume = atof(ACE_CString(kosdaq.askTradeVolume, sizeof kosdaq.askTradeVolume).c_str()) / (float) 1000;
        investor.askAmount = atof(ACE_CString(kosdaq.askTradeAmount, sizeof kosdaq.askTradeAmount).c_str()) / (float) 1000000;
        investor.bidVolume = atof(ACE_CString(kosdaq.bidTradeVolume, sizeof kosdaq.bidTradeVolume).c_str()) / (float) 1000;
        investor.bidAmount = atof(ACE_CString(kosdaq.bidTradeAmount, sizeof kosdaq.bidTradeAmount).c_str()) / (float) 1000000;

        char buf[INVESTOR_SIZE];
        memcpy(buf, &investor, std::min(sizeof buf, sizeof investor));

#if(1)
		result = sendPacket(ACE_CString(buf, INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KOSDAQ);
#endif

    }
    catch ( std::exception& e )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestor] error occur e,what[%s]\n" , getCurrentTimestamp().c_str() , e.what() ));
        result = -1;
    }
    catch ( ... )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestor] unknown error occur\n" , getCurrentTimestamp().c_str() ));
        result = -1;
    }
    return result;
}

int InternetKosdaqChannelProcessor::handleBulkTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_TOTAL_BULK_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleBulkTrade] Skip : %s,%d : EXTURE_PLUS_KOSDAQ_BULK_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_BULK_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // 일단 대량체결 처리는 정책확정시까지 보류한다.
	ExturePlusKosdaqTotalBulkTrade totalkosdaq;
	ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

	ExturePlusKosdaqBulkTrade kosdaq;
    ::memset(&kosdaq, 0x20, sizeof(ExturePlusKosdaqBulkTrade));//0x20(SPACE) INIT

	ACE_CString boardID(totalkosdaq.boardID, sizeof ( totalkosdaq.boardID ));
	/*
	B2	장개시전대량	kBloxVolumeInPreMarketTradingHoursSession
	K2	장개시전대량바스켓	basketTradingVolumeInPreMarketTradingHoursSession
	I2	장개시전경쟁대량	aBloxVolumeInPreMarketTradingHoursSession
	B1	장중대량	kBloxVolumeInRegularTradingHoursSession
	K1	장중대량바스켓	basketTradingVolumeInRegularTradingHoursSession
	I1	장중경쟁대량	aBloxVolumeInRegularTradingHoursSession
	B3	장종료후대량	kBloxVolumeInPostMarketTradingHoursSession
	K3	장종료후대량바스켓	basketTradingVolumeInPostMarketTradingHoursSession
	*/
	if(boardID=="B2") ::memcpy(kosdaq.kBloxVolumeInPreMarketTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.kBloxVolumeInPreMarketTradingHoursSession));
	if(boardID=="K2") ::memcpy(kosdaq.basketTradingVolumeInPreMarketTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.basketTradingVolumeInPreMarketTradingHoursSession));
	if(boardID=="I2") ::memcpy(kosdaq.aBloxVolumeInPreMarketTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.aBloxVolumeInPreMarketTradingHoursSession));
	if(boardID=="B1") ::memcpy(kosdaq.kBloxVolumeInRegularTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.kBloxVolumeInRegularTradingHoursSession));
	if(boardID=="K1") ::memcpy(kosdaq.basketTradingVolumeInRegularTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.basketTradingVolumeInRegularTradingHoursSession));
	if(boardID=="I1") ::memcpy(kosdaq.aBloxVolumeInRegularTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.aBloxVolumeInRegularTradingHoursSession));
	if(boardID=="B3") ::memcpy(kosdaq.kBloxVolumeInPostMarketTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.kBloxVolumeInPostMarketTradingHoursSession));
	if(boardID=="K3") ::memcpy(kosdaq.basketTradingVolumeInPostMarketTradingHoursSession, totalkosdaq.accumlatedVolume, sizeof(kosdaq.basketTradingVolumeInPostMarketTradingHoursSession));

	::memcpy(kosdaq.issueCode, totalkosdaq.stockCode, sizeof(kosdaq.issueCode));

	ACE_CString symbol(kosdaq.issueCode, sizeof ( kosdaq.issueCode ));
	ACE_CString issueCode(kosdaq.issueCode, sizeof ( kosdaq.issueCode ));

    const ACE_CString BOARD_ID_PRE_OFF_HOURS_SESSION_B2("B2");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_PRE_OFF_HOURS_SESSION_K2("K2");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_PRE_OFF_HOURS_SESSION_I2("I2");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_REGULAR_SESSION_B1("B1");	//KOSPI/KOSDAQ/
    const ACE_CString BOARD_ID_REGULAR_SESSION_K1("K1");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_REGULAR_SESSION_I1("I1");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_POST_OFF_HOURS_SESSION_B3("B3");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_POST_OFF_HOURS_SESSION_K3("K3");	//KOSPI/KOSDAQ


    //    // 대량체결
    //    // 대량체결은 거래량만 제공되고, 거래대금은 제공되지 않는다. 따라서 대량체결시의 체결가를 알 수 없다.
    //    // 대량체결전문에는 당일의 누적거래량을 제공하지 않으므로, 대량체결 전문만으로 PACKET_TRADE 를 만들 수 없다 ======> 독립된 내부포맷을 정의한 이유
    //    // 대량체결은 KRX 의 정책에 따라 체결종류가 변경(가령 바스켓매매등)되어왔으며, 굳이 현 서비스에서 각 타입별 대량체결을 서비스하지 않는다.
    //    // 따라서, 장개시전 대량체결, 장중 대량체결, 장마감후 대량체결 값만 합산해서 보낸다. =====> 상세분류가 필요하면 나중에 추가
    //    // TRADE_REAL 의 ACCM_VOLUME 에는 대량체결값이 B1, B2 전문을 통해 추가되어 있다. 다시 합산하지 않도록 주의한다.
    //    // 대량체결 전문은 배치성으로 동일 전문이 2회 발송된다. 각 APP 들은 REPLACE 하도록 한다.
    //    // 2014.06.27
    //    class BlockTrade
    //    {
    //    public :
    //        char symbol[12];                    // 종목코드, 거래소 시장공통 장운영은 KRI001000000, 코스닥 시장공통 장운영은 KRI501000000 으로 고정
    //        int recvTime;                       // Tickerplant 수신시간
    //        double tradeVolumePreMarket;        // 장개시전 대량체결 수량(장개시전시간외 상대대량체결수량 + 장개시전시간외 바스켓체결수량 + 장개시전시간외 경쟁대량체결수량)
    //        double tradeVolumeRegularMarket;    // 장중 대량체결 수량(장중 상대대량체결수량 + 장중 바스켓체결수량 + 장중 경쟁대량체결수량)
    //        double tradeVolumePostMarket;       // 장종료후 대량체결 수량(장종료후시간외 상대대량체결수량 + 장종료후시간외 바스켓체결수량)
    //    };
    //    static const int BLOCK_TRADE_SIZE = sizeof(BlockTrade);
    //    } // namespace paxfeed

	if ( symbol == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleBulkTrade] symbol:[%s]\tskip dummy packet\n" , getCurrentTimestamp().c_str() , symbol.c_str() ));
        return 0;
    }

    int recvTime = (int) ( ::time(0) );


#if(0)
    double kBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.kBloxVolumeInPreMarketTradingHoursSession, sizeof ( kosdaq.kBloxVolumeInPreMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.basketTradingVolumeInPreMarketTradingHoursSession, sizeof ( kosdaq.basketTradingVolumeInPreMarketTradingHoursSession )).c_str());
    double aBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.aBloxVolumeInPreMarketTradingHoursSession, sizeof ( kosdaq.aBloxVolumeInPreMarketTradingHoursSession )).c_str());

    double kBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kosdaq.kBloxVolumeInRegularTradingHoursSession, sizeof ( kosdaq.kBloxVolumeInRegularTradingHoursSession )).c_str());
    double basketTradingVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kosdaq.basketTradingVolumeInRegularTradingHoursSession, sizeof ( kosdaq.basketTradingVolumeInRegularTradingHoursSession )).c_str());
    double aBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kosdaq.aBloxVolumeInRegularTradingHoursSession, sizeof ( kosdaq.aBloxVolumeInRegularTradingHoursSession )).c_str());

    double kBloxVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.kBloxVolumeInPostMarketTradingHoursSession, sizeof ( kosdaq.kBloxVolumeInPostMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.basketTradingVolumeInPostMarketTradingHoursSession, sizeof ( kosdaq.basketTradingVolumeInPostMarketTradingHoursSession )).c_str());

    double tradeVolumePreMarket = kBloxVolumeInPreMarketTradingHoursSession + basketTradingVolumeInPreMarketTradingHoursSession + aBloxVolumeInPreMarketTradingHoursSession;
    double tradeVolumeRegularMarket = kBloxVolumeInRegularTradingHoursSession + basketTradingVolumeInRegularTradingHoursSession + aBloxVolumeInRegularTradingHoursSession;
    double tradeVolumePostMarket = kBloxVolumeInPostMarketTradingHoursSession + basketTradingVolumeInPostMarketTradingHoursSession;
#endif

#if(1)
    double kBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.kBloxVolumeInPreMarketTradingHoursSession, sizeof ( kosdaq.kBloxVolumeInPreMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.basketTradingVolumeInPreMarketTradingHoursSession, sizeof ( kosdaq.basketTradingVolumeInPreMarketTradingHoursSession )).c_str());
    double aBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.aBloxVolumeInPreMarketTradingHoursSession, sizeof ( kosdaq.aBloxVolumeInPreMarketTradingHoursSession )).c_str());

	if(kBloxVolumeInPreMarketTradingHoursSession == 0) kBloxVolumeInPreMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_B2);
	if(basketTradingVolumeInPreMarketTradingHoursSession == 0) basketTradingVolumeInPreMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_K2);
	if(aBloxVolumeInPreMarketTradingHoursSession == 0) aBloxVolumeInPreMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_I2);

    double kBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kosdaq.kBloxVolumeInRegularTradingHoursSession, sizeof ( kosdaq.kBloxVolumeInRegularTradingHoursSession )).c_str());
    double basketTradingVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kosdaq.basketTradingVolumeInRegularTradingHoursSession, sizeof ( kosdaq.basketTradingVolumeInRegularTradingHoursSession )).c_str());
    double aBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kosdaq.aBloxVolumeInRegularTradingHoursSession, sizeof ( kosdaq.aBloxVolumeInRegularTradingHoursSession )).c_str());

	if(kBloxVolumeInRegularTradingHoursSession == 0) kBloxVolumeInRegularTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_B1);
	if(basketTradingVolumeInRegularTradingHoursSession == 0) basketTradingVolumeInRegularTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_K1);
	if(aBloxVolumeInRegularTradingHoursSession == 0) aBloxVolumeInRegularTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_I1);

    double kBloxVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.kBloxVolumeInPostMarketTradingHoursSession, sizeof ( kosdaq.kBloxVolumeInPostMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kosdaq.basketTradingVolumeInPostMarketTradingHoursSession, sizeof ( kosdaq.basketTradingVolumeInPostMarketTradingHoursSession )).c_str());

    if(kBloxVolumeInPostMarketTradingHoursSession == 0) kBloxVolumeInPostMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_POST_OFF_HOURS_SESSION_B3);
	if(basketTradingVolumeInPostMarketTradingHoursSession == 0) basketTradingVolumeInPostMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_POST_OFF_HOURS_SESSION_K3);
#endif

	/*
	B2	장개시전대량	kBloxVolumeInPreMarketTradingHoursSession
	K2	장개시전대량바스켓	basketTradingVolumeInPreMarketTradingHoursSession
	I2	장개시전경쟁대량	aBloxVolumeInPreMarketTradingHoursSession
	B1	장중대량	kBloxVolumeInRegularTradingHoursSession
	K1	장중대량바스켓	basketTradingVolumeInRegularTradingHoursSession
	I1	장중경쟁대량	aBloxVolumeInRegularTradingHoursSession
	B3	장종료후대량	kBloxVolumeInPostMarketTradingHoursSession
	K3	장종료후대량바스켓	basketTradingVolumeInPostMarketTradingHoursSession
	*/

#if(1)
	//B2	장개시전대량
    if ( getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_B2) < kBloxVolumeInPreMarketTradingHoursSession )
    {
        setAccmVolume(issueCode, kBloxVolumeInPreMarketTradingHoursSession, BOARD_ID_PRE_OFF_HOURS_SESSION_B2);
    }
	//K2	장개시전대량바스켓
    if ( getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_K2) < basketTradingVolumeInPreMarketTradingHoursSession )
    {
        setAccmVolume(issueCode, basketTradingVolumeInPreMarketTradingHoursSession, BOARD_ID_PRE_OFF_HOURS_SESSION_K2);
    }
	//I2	장개시전경쟁대량
    if ( getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_I2) < aBloxVolumeInPreMarketTradingHoursSession )
    {
        setAccmVolume(issueCode, aBloxVolumeInPreMarketTradingHoursSession, BOARD_ID_PRE_OFF_HOURS_SESSION_I2);
    }
	//B1	장중대량
    if ( getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_B1) < kBloxVolumeInRegularTradingHoursSession )
    {
        setAccmVolume(issueCode, kBloxVolumeInRegularTradingHoursSession, BOARD_ID_REGULAR_SESSION_B1);
    }
	//K1	장중대량바스켓
    if ( getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_K1) < basketTradingVolumeInRegularTradingHoursSession )
    {
        setAccmVolume(issueCode, basketTradingVolumeInRegularTradingHoursSession, BOARD_ID_REGULAR_SESSION_K1);
    }
	//I1	장중경쟁대량
    if ( getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_I1) < aBloxVolumeInRegularTradingHoursSession )
    {
        setAccmVolume(issueCode, aBloxVolumeInRegularTradingHoursSession, BOARD_ID_REGULAR_SESSION_I1);
    }
	//B3	장종료후대량
    if ( getAccmVolume(issueCode, BOARD_ID_POST_OFF_HOURS_SESSION_B3) < kBloxVolumeInPostMarketTradingHoursSession )
    {
        setAccmVolume(issueCode, kBloxVolumeInPostMarketTradingHoursSession, BOARD_ID_POST_OFF_HOURS_SESSION_B3);
    }
	//K3	장종료후대량바스켓
    if ( getAccmVolume(issueCode, BOARD_ID_POST_OFF_HOURS_SESSION_K3) < basketTradingVolumeInPostMarketTradingHoursSession )
    {
        setAccmVolume(issueCode, basketTradingVolumeInPostMarketTradingHoursSession, BOARD_ID_POST_OFF_HOURS_SESSION_K3);
    }
#endif

    double tradeVolumePreMarket = kBloxVolumeInPreMarketTradingHoursSession + basketTradingVolumeInPreMarketTradingHoursSession + aBloxVolumeInPreMarketTradingHoursSession;
    double tradeVolumeRegularMarket = kBloxVolumeInRegularTradingHoursSession + basketTradingVolumeInRegularTradingHoursSession + aBloxVolumeInRegularTradingHoursSession;
    double tradeVolumePostMarket = kBloxVolumeInPostMarketTradingHoursSession + basketTradingVolumeInPostMarketTradingHoursSession;


    BlockTrade blockRec;
    ::memset(&blockRec, 0, sizeof(BlockTrade));
    ::memcpy(&blockRec.symbol, symbol.c_str(), symbol.length());
    blockRec.recvTime = recvTime;
    blockRec.tradeVolumePreMarket = tradeVolumePreMarket;
    blockRec.tradeVolumeRegularMarket = tradeVolumeRegularMarket;
    blockRec.tradeVolumePostMarket = tradeVolumePostMarket;

    printPacketBlockTrade(blockRec);

    char buf[BLOCK_TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &blockRec, BLOCK_TRADE_SIZE);

#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, BLOCK_TRADE_SIZE), PACKET_BLOCK_TRADE, EXCHANGE_KOSDAQ);
#endif
    return result;
}

#if(1)
int InternetKosdaqChannelProcessor::handleRecoveryTotalTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

	int other_else=0;

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

   	ExturePlusKosdaqRecoveryTotalTrade totalkosdaq;
	ACE_OS::memcpy(&totalkosdaq, packet.c_str(), packet.length());

    ExturePlusKosdaqRecoveryTrade kosdaq;
	::memset(&kosdaq, 0x30, sizeof(kosdaq));

	memcpy(kosdaq.stockCode,totalkosdaq.stockCode,sizeof(kosdaq.stockCode));
	memcpy(kosdaq.boardID,totalkosdaq.boardID,sizeof(kosdaq.boardID));
	memcpy(kosdaq.upDown,totalkosdaq.upDown,sizeof(kosdaq.upDown));
	memcpy(kosdaq.gap,totalkosdaq.gap,sizeof(kosdaq.gap));
	memcpy(kosdaq.closePrice,totalkosdaq.closePrice,sizeof(kosdaq.closePrice));
	memcpy(kosdaq.openPrice,totalkosdaq.openPrice,sizeof(kosdaq.openPrice));
	memcpy(kosdaq.highPrice,totalkosdaq.highPrice,sizeof(kosdaq.highPrice));
	memcpy(kosdaq.lowPrice,totalkosdaq.lowPrice,sizeof(kosdaq.lowPrice));
	memcpy(kosdaq.realRateQuotationClass,totalkosdaq.realRateQuotationClass,sizeof(kosdaq.realRateQuotationClass));

	ACE_CString boardID(totalkosdaq.boardID, sizeof(totalkosdaq.boardID ));
    ACE_CString sessionID(totalkosdaq.sessionID, sizeof ( totalkosdaq.sessionID ));

	ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);
    ACE_CString isNormalstockCode(kosdaq.stockCode, ( sizeof kosdaq.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

	/*
	G2	장개시전종가	40
	G2	장개시전종가	40
	*/
	if(boardID == "G2")
	{
		memcpy(kosdaq.beforeMarketOverTimeClosePriceTradeVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.beforeMarketOverTimeClosePriceTradeVolume));
		memcpy(kosdaq.beforeMarketOverTimeClosePriceTradeAmount,totalkosdaq.accmTradeAmount,sizeof(kosdaq.beforeMarketOverTimeClosePriceTradeAmount));

		other_else=100;
	}
	/*
	G1	정규장	10
	G1	정규장	52
	G1	정규장	11
	G1	정규장	53
	G1	정규장	20
	G1	정규장	21
	G1	정규장	30
	G1	정규장	54
	G1	정규장	40
	G1	정규장	50
	G1	정규장	51
	G1	정규장	80
	*/
	if(boardID == "G1")
	{
		memcpy(kosdaq.regularMarketTradeVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.regularMarketTradeVolume));
		memcpy(kosdaq.regularMarketTradeAmount,totalkosdaq.accmTradeAmount,sizeof(kosdaq.regularMarketTradeAmount));

		other_else=100;
	}
	/*
	G3	장종료후종가	60
	G3	장종료후종가	40
	*/
	if(boardID == "G3")
	{
		memcpy(kosdaq.afterMarketOvertimeClosePriceTradeVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.afterMarketOvertimeClosePriceTradeVolume));
		memcpy(kosdaq.afterMarketOvertimeClosePriceTradeAmount,totalkosdaq.accmTradeAmount,sizeof(kosdaq.afterMarketOvertimeClosePriceTradeAmount));

		other_else=100;
	}

	//G7	일반Buy-In	20	단일가	일반 Buy-In 체결수량       
	//G7	일반Buy-In	20	단일가	일반 Buy-In 거래대금       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 체결수량       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 거래대금  

	if(boardID == "G7")
	{
		memcpy(kosdaq.regularBuyInTradingVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.regularBuyInTradingVolume));
		memcpy(kosdaq.regularBuyInTradingValue,totalkosdaq.accmTradeAmount,sizeof(kosdaq.regularBuyInTradingValue));

		other_else=100;
	}
	if(boardID == "G8")
	{
		memcpy(kosdaq.sameDayBuyInTradingVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.sameDayBuyInTradingVolume));
		memcpy(kosdaq.sameDayBuyInTradingValue,totalkosdaq.accmTradeAmount,sizeof(kosdaq.sameDayBuyInTradingValue));

		other_else=100;
	}

    //G4 시간외단일가누적 체결수량/시간외단일가누적 거래대금
	if(boardID=="G4")
	{
		memcpy(kosdaq.overTimeMarketFixedAccmVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.overTimeMarketFixedAccmVolume));
		memcpy(kosdaq.overTimeMarketFixedAccmAmount,totalkosdaq.accmTradeVolume,sizeof(kosdaq.overTimeMarketFixedAccmAmount));

		other_else=100;
	}

	//7.B2	장개시전대량 manyBulkTradeVolume/manyBulkTradeAmount/
    //7.K2	장개시전대량바스켓
    //7.I2	장개시전경쟁대량
    //7.B1	장중대량
    //7.K1	장중대량바스켓
    //7.I1	장중경쟁대량
    //7.B3	장종료후대량
    //7.K3	장종료후대량바스켓
	if(other_else==0)
	{
		memcpy(kosdaq.manyBulkTradeVolume,totalkosdaq.accmTradeVolume,sizeof(kosdaq.manyBulkTradeVolume));
		memcpy(kosdaq.manyBulkTradeAmount,totalkosdaq.accmTradeVolume,sizeof(kosdaq.manyBulkTradeAmount));

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTotalTrade] stockCode:[%s],boardID:[%s],sessionID:[%s],manyBulkTradeVolume:[%.*s],manyBulkTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , stockCode.c_str() , boardID.c_str(), sessionID.c_str(), sizeof(kosdaq.manyBulkTradeVolume), kosdaq.manyBulkTradeVolume, sizeof(kosdaq.manyBulkTradeAmount), kosdaq.manyBulkTradeAmount));
	}

    if ( isValidSymbol(stockCode) == false )
    {
        return 0;
    }

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));

    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(kosdaq.upDown, sizeof kosdaq.upDown);
	ACE_CString boardEventID(kosdaq.boardEventID, sizeof ( kosdaq.boardEventID ));

    trade.market = getMarketInRecoveryTrade(boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kosdaq.openPrice, sizeof kosdaq.openPrice).c_str());
    trade.high = atoi(ACE_CString(kosdaq.highPrice, sizeof kosdaq.highPrice).c_str());
    trade.low = atoi(ACE_CString(kosdaq.lowPrice, sizeof kosdaq.lowPrice).c_str());
    trade.close = atoi(ACE_CString(kosdaq.closePrice, sizeof kosdaq.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    /*
     * 버그 존재함
     * 정규장때 재기동을 한 경우 장개시전시간외 종가와 장개시후시간외 종가는 당일 거래량으로 포함되어야 하는데,
     * B2 의 누적거래량은 바이인을 제외한 전체 거래량을 담으므로, B2 처리시 전체 거래량은 맞게 되지만,
     * 다음 A3 전문 도착시에는 해당 보드 ID 만이 더해지고, 다른 보드 ID 값은 0 이므로, 거래량이 일부 빠지는 상황이 발생할 수 있다.
     *
     * ==> 로직변경
     * B2 수신시
     * 정규장 거래량을 G1 으로 해서 강제로 업데이트 한다.
     * 장개시전 시간외 거래량을 G2 로 해서 강제로 업데이트하고
     * 장개시후 시간외 거래량을 G3 로 해서 강제로 업데이트해야한다.
     */

    /*
     * 아래 값들을 강제로 세팅해야 한다.
     */

    const ACE_CString BOARD_ID_MARKET_IN("G1");
    const ACE_CString BOARD_ID_MARKET_BEFORE_TRADE("G2");
    const ACE_CString BOARD_ID_MARKET_AFTER_TRADE("G3");
	const ACE_CString BOARD_ID_MARKET_DANIL_TRADE("G4");
	const ACE_CString BOARD_ID_MARKET_REGULARBUYIN_TRADE("G7");
	const ACE_CString BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE("G8");
	const ACE_CString BOARD_ID_BULK_TRADE_TODAY("ZZ");


	double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(kosdaq.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( kosdaq.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(kosdaq.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( kosdaq.beforeMarketOverTimeClosePriceTradeAmount )).c_str());

    if(beforeMarketOverTimeClosePriceTradeVolume == 0) beforeMarketOverTimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);
    if(beforeMarketOverTimeClosePriceTradeAmount == 0) beforeMarketOverTimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);

    double regularMarketTradeVolume = ::atof(ACE_CString(kosdaq.regularMarketTradeVolume, sizeof ( kosdaq.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(kosdaq.regularMarketTradeAmount, sizeof ( kosdaq.regularMarketTradeAmount )).c_str());

    if(regularMarketTradeVolume == 0) regularMarketTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_IN);
    if(regularMarketTradeAmount == 0) regularMarketTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_IN);

    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(kosdaq.afterMarketOvertimeClosePriceTradeVolume, sizeof ( kosdaq.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(kosdaq.afterMarketOvertimeClosePriceTradeAmount, sizeof ( kosdaq.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    if(afterMarketOvertimeClosePriceTradeVolume == 0) afterMarketOvertimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE);
    if(afterMarketOvertimeClosePriceTradeAmount == 0) afterMarketOvertimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE);

	double regularBuyInTradingVolume = ::atof(ACE_CString(kosdaq.regularBuyInTradingVolume, sizeof ( kosdaq.regularBuyInTradingVolume )).c_str());
	double regularBuyInTradingValue = ::atof(ACE_CString(kosdaq.regularBuyInTradingValue, sizeof ( kosdaq.regularBuyInTradingValue )).c_str());

	if(regularBuyInTradingVolume == 0) regularBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    if(regularBuyInTradingValue == 0) regularBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);

	double sameDayBuyInTradingVolume = ::atof(ACE_CString(kosdaq.sameDayBuyInTradingVolume, sizeof ( kosdaq.sameDayBuyInTradingVolume )).c_str());
	double sameDayBuyInTradingValue = ::atof(ACE_CString(kosdaq.sameDayBuyInTradingValue, sizeof ( kosdaq.sameDayBuyInTradingValue )).c_str());

	if(sameDayBuyInTradingVolume == 0) sameDayBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    if(sameDayBuyInTradingValue == 0) sameDayBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);

	double overTimeMarketFixedAccmVolume = ::atof(ACE_CString(kosdaq.overTimeMarketFixedAccmAmount, sizeof ( kosdaq.overTimeMarketFixedAccmAmount )).c_str());
	double overTimeMarketFixedAccmAmount = ::atof(ACE_CString(kosdaq.overTimeMarketFixedAccmAmount, sizeof ( kosdaq.overTimeMarketFixedAccmAmount )).c_str());

	if(overTimeMarketFixedAccmVolume == 0) overTimeMarketFixedAccmVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE);
    if(overTimeMarketFixedAccmAmount == 0) overTimeMarketFixedAccmAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE);

	double manyBulkTradeVolume = ::atof(ACE_CString(kosdaq.manyBulkTradeVolume, sizeof ( kosdaq.manyBulkTradeVolume )).c_str());
	double manyBulkTradeAmount = ::atof(ACE_CString(kosdaq.manyBulkTradeAmount, sizeof ( kosdaq.manyBulkTradeAmount )).c_str());

	if(manyBulkTradeVolume == 0) manyBulkTradeVolume = getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY);
    if(manyBulkTradeAmount == 0) manyBulkTradeAmount = getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY);

    // 장개시전 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, beforeMarketOverTimeClosePriceTradeVolume, BOARD_ID_MARKET_BEFORE_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, beforeMarketOverTimeClosePriceTradeAmount, BOARD_ID_MARKET_BEFORE_TRADE);
    }

    // 정규장 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeVolume )
    {
        setAccmVolume(stockCode, regularMarketTradeVolume, BOARD_ID_MARKET_IN);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeAmount )
    {
        setAccmAmount(stockCode, regularMarketTradeAmount, BOARD_ID_MARKET_IN);
    }

    // 장마감후 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, afterMarketOvertimeClosePriceTradeVolume, BOARD_ID_MARKET_AFTER_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, afterMarketOvertimeClosePriceTradeAmount, BOARD_ID_MARKET_AFTER_TRADE);
    }

	// 일반 Buy-In
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE) < regularBuyInTradingVolume )
    {
        setAccmVolume(stockCode, regularBuyInTradingVolume, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE) < regularBuyInTradingValue )
    {
        setAccmAmount(stockCode, regularBuyInTradingValue, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    }

	// 당일 Buy-In
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE) < sameDayBuyInTradingVolume )
    {
        setAccmVolume(stockCode, sameDayBuyInTradingVolume, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE) < sameDayBuyInTradingValue )
    {
        setAccmAmount(stockCode, sameDayBuyInTradingValue, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    }

	// DANIL
	if ( getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE) < overTimeMarketFixedAccmVolume )
    {
        setAccmVolume(stockCode, overTimeMarketFixedAccmVolume, BOARD_ID_MARKET_DANIL_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE) < overTimeMarketFixedAccmAmount )
    {
        setAccmAmount(stockCode, overTimeMarketFixedAccmAmount, BOARD_ID_MARKET_DANIL_TRADE);
    }

	// MANY
	if ( getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY) < manyBulkTradeVolume )
    {
        setAccmVolume(stockCode, manyBulkTradeVolume, BOARD_ID_BULK_TRADE_TODAY);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY) < manyBulkTradeAmount )
    {
        setAccmAmount(stockCode, manyBulkTradeAmount, BOARD_ID_BULK_TRADE_TODAY);
    }

	//1.장개시전시간외종가 체결수량 : beforeMarketOverTimeClosePriceTradeVolume
    //2.정규장체결수량              : regularMarketTradeVolume
    //3.장종료후시간외종가 체결수량 : afterMarketOvertimeClosePriceTradeVolume
    //4.일반 Buy-in 체결수량        : regularBuyInTradingVolume
    //5.당일 Buy-in 체결수량        : sameDayBuyInTradingVolume
    //6.시간외단일가누적 체결수량   : overTimeMarketFixedAccmVolume
	//7.대량 체결수량               : manyBulkTradeVolume

    //1.장개시전시간외종가 거래대금 : beforeMarketOverTimeClosePriceTradeAmount
    //2.정규장거래대금              : regularMarketTradeAmount
    //3.장종료후시간외종가 거래대금 : afterMarketOvertimeClosePriceTradeAmount
    //4.일반 Buy-in 거래대금        : regularBuyInTradingValue
    //5.당일 Buy-in 거래대금        : sameDayBuyInTradingValue
    //6.시간외단일가누적 거래대금   : overTimeMarketFixedAccmAmount
	//7.대량 거래대금               : manyBulkTradeAmount

    //-------------------------------------------------------------
    //7.B2	장개시전대량
    //7.K2	장개시전대량바스켓
    //7.I2	장개시전경쟁대량
    //7.B1	장중대량
    //7.K1	장중대량바스켓
    //7.I1	장중경쟁대량
    //7.B3	장종료후대량
    //7.K3	장종료후대량바스켓
	//--------------------------------------------------------------

    double accmVolume = 0;
    double accmAmount = 0;

	accmVolume = accmVolume + beforeMarketOverTimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularMarketTradeVolume;
	accmVolume = accmVolume + afterMarketOvertimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularBuyInTradingVolume;
	accmVolume = accmVolume + sameDayBuyInTradingVolume;
	accmVolume = accmVolume + overTimeMarketFixedAccmVolume;
	accmVolume = accmVolume + manyBulkTradeVolume;

	accmAmount = accmAmount + beforeMarketOverTimeClosePriceTradeAmount;
	accmAmount = accmAmount + regularMarketTradeAmount;
	accmAmount = accmAmount + regularBuyInTradingValue;
	accmAmount = accmAmount + sameDayBuyInTradingValue;
	accmAmount = accmAmount + overTimeMarketFixedAccmAmount;
	accmAmount = accmAmount + manyBulkTradeAmount;

    if ( accmVolume < getTotalAccmVolume(stockCode) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
    }

    if ( accmVolume > 0 )
    {
        setTotalAccmVolume(stockCode, accmVolume);
    }
    trade.accmVolume = getTotalAccmVolume(stockCode);

    if ( accmAmount > 0 )
    {
        setTotalAccmAmount(stockCode, accmAmount);
    }
    trade.amount = getTotalAccmAmount(stockCode);

    ACE_CString quotation(kosdaq.realRateQuotationClass, sizeof kosdaq.realRateQuotationClass);

    if ( quotation == "2" )
    {
        trade.subtype = TRADESUBTYPE_QUOTATION;
    }
    else
    {
        trade.subtype = TRADESUBTYPE_RECOVERY;
    }

    trade.tradeVolume = 0;

    if ( hasValue == -1 )
    {

#if(1)
        trade.exchange = EXCHANGE_KOSDAQ;
#endif

        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = time(0);
        ACE_OS::memcpy(&trade.symbol, &kosdaq.stockCode, sizeof kosdaq.stockCode);

        trade.openMin = 0;
        trade.highMin = 0;
        trade.lowMin = 0;
        trade.volumeMin = 0;
    }

    trade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    Trade oldVal;
    tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());

	char buf[TRADE_SIZE];
    ::memset(buf, 0x00, sizeof ( buf ));
    memcpy(buf, &trade, TRADE_SIZE);


#if(1)

	int result = 0;

	result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KOSDAQ);
#endif

    return result;
}
#endif

int InternetKosdaqChannelProcessor::handleTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleTrade] Skip : %s,%d : EXTURE_PLUS_KOSDAQ_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

    ExturePlusKosdaqTrade kosdaq;
    ::memset(&kosdaq, 0, sizeof(ExturePlusKosdaqTrade));
    ACE_OS::memcpy(&kosdaq, packet.c_str(), std::min(sizeof kosdaq, packet.length()));

    ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);
    ACE_CString isNormalstockCode(kosdaq.stockCode, ( sizeof kosdaq.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    if ( isValidSymbol(stockCode) == false )
    {
        return 0;
    }

    ACE_CString boardID(kosdaq.boardID, sizeof ( kosdaq.boardID ));
    ACE_CString sessionID(kosdaq.sessionID, sizeof ( kosdaq.sessionID ));

	if ( ( boardID == "G7" ) || ( boardID == "G8" ) )
    {
        return 0;
    }
    if ( sessionID == "25" )
    {
        return 0;
    }

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));
    TickFilter filter;
    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(kosdaq.upDown, sizeof kosdaq.upDown);
    trade.subtype = TRADESUBTYPE_TRADE;

    // 정규시간외구분코드 : 장종료후시간외단일가(4) , 체결유형코드 : 시간외단일가(70)
    // 4    장종료후시간외단일가  G4  유가/코스닥

    if ( ( boardID == "G4" ) || ( sessionID == "70" ) )
    {
        return handleTradeFixed(kosdaq); //시간외단일가
    }

    trade.market = getMarketInTrade(boardID);
    trade.upDown = getUpDownInTrade(upDown);

    // 장개시전시간외거래인 경우 시가, 고가, 저가는 0으로 셋팅하고 종가는 체결가로 셋팅한다.
    if ( ( boardID == "G2" ) || ( sessionID == "50" ) )
    {
        trade.open = 0;
        trade.high = 0;
        trade.low = 0;
        trade.close = atoi(ACE_CString(kosdaq.tradePrice, sizeof kosdaq.tradePrice).c_str());
    }
    //장종료후시간외종가거래인 경우 시가, 고가, 저가, 종가는 그대로 두고, 체결량만 변경한다.
    else if ( boardID == "G3" || sessionID == "65" )  //
    {
        //가격을 셋팅하지 않는다.
        if ( hasValue == -1 )
        {
            return 0;
        }
    }
    else
    {
        trade.open = atoi(ACE_CString(kosdaq.openPrice, sizeof kosdaq.openPrice).c_str());
        trade.high = atoi(ACE_CString(kosdaq.highPrice, sizeof kosdaq.highPrice).c_str());
        trade.low = atoi(ACE_CString(kosdaq.lowPrice, sizeof kosdaq.lowPrice).c_str());
        trade.close = atoi(ACE_CString(kosdaq.tradePrice, sizeof kosdaq.tradePrice).c_str());
    }

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(kosdaq.accmTradeVolume, sizeof kosdaq.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kosdaq.accmTradeAmount, sizeof kosdaq.accmTradeAmount).c_str());
    double previousVolume = getAccmVolume(stockCode, boardID);

    trade.tradeVolume = accmVolume - previousVolume;

    if ( trade.tradeVolume < 0 )
    {
        /*
         * APP 재기동후 간혹 오류가 나는 경우가 있다.
         * 해당 boardID 의 accmVolume 을 현재것으로 처리하고 다음 리커버리를 기다린다.
         */
        setAccmVolume(stockCode, accmVolume, boardID);
        setAccmAmount(stockCode, accmAmount, boardID);
        trade.tradeVolume = 0;
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleTrade] Skip : %s,%d : net volume error stockCode:[%s] trade.tradeVolume:[%f] accmVolume:[%f] previousVolume:[%f] \n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , trade.tradeVolume , accmVolume , previousVolume ), -1);
    }

    setAccmVolume(stockCode, accmVolume, boardID);
    setAccmAmount(stockCode, accmAmount, boardID);

    trade.accmVolume = getTotalAccmVolume(stockCode);

    int tradeTime = getTickTime(ACE_CString(kosdaq.transactionProcessingTime, sizeof kosdaq.transactionProcessingTime), frameId);

    if ( trade.accmVolume == -1 )
    {
        trade.accmVolume = 0;   //accmVolume ;
    }

    trade.amount = getTotalAccmAmount(stockCode);
    if ( trade.amount == -1 )
    {
        trade.amount = 0;   //amount ;
    }

    if ( hasValue == -1 )
    {
        trade.tradeTime = tradeTime;

#if(1)
trade.exchange = EXCHANGE_KOSDAQ;
#endif

        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        memcpy(&trade.symbol, &kosdaq.stockCode, std::min(sizeof trade.symbol, sizeof kosdaq.stockCode));
        trade.openMin = trade.close;
        trade.highMin = trade.close;
        trade.lowMin = trade.close;
        trade.volumeMin = trade.tradeVolume;
        tradeMap_->bind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, ALLOCATOR::instance());
    }
    else
    {
        int previousTime = trade.tradeTime;
        trade.tradeTime = tradeTime;

        // 신규 1분바일 경우
        if ( ( trade.tradeTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
        {
            trade.volumeMin += trade.tradeVolume;
            if ( trade.close > trade.highMin )
            {
                trade.highMin = trade.close;
            }

            if ( trade.close < trade.lowMin )
            {
                trade.lowMin = trade.close;
            }
        }
        else
        {
            trade.volumeMin = trade.tradeVolume;
            trade.openMin = trade.close;
            trade.highMin = trade.close;
            trade.lowMin = trade.close;
        }

        ACE_CString oldKey;
        Trade oldVal;
        tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());
    }

    char buf[TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &trade, TRADE_SIZE);


#if(1)
sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KOSDAQ);
#endif

    return 0;
}

int InternetKosdaqChannelProcessor::handleRecoveryTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTrade] Skip : %s,%d : EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId.c_str());

    ExturePlusKosdaqRecoveryTrade kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), std::min(sizeof kosdaq, packet.length()));

    ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);
    ACE_CString isNormalstockCode(kosdaq.stockCode, ( sizeof kosdaq.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    if ( isValidSymbol(stockCode) == false )
    {
        return 0;
    }

    ACE_CString boardID(kosdaq.boardID, sizeof ( kosdaq.boardID ));
    ACE_CString boardEventID(kosdaq.boardEventID, sizeof ( kosdaq.boardEventID ));

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));

    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(kosdaq.upDown, sizeof kosdaq.upDown);

    trade.market = getMarketInRecoveryTrade(frameId, boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);
    trade.open = atoi(ACE_CString(kosdaq.openPrice, sizeof kosdaq.openPrice).c_str());
    trade.high = atoi(ACE_CString(kosdaq.highPrice, sizeof kosdaq.highPrice).c_str());
    trade.low = atoi(ACE_CString(kosdaq.lowPrice, sizeof kosdaq.lowPrice).c_str());
    trade.close = atoi(ACE_CString(kosdaq.closePrice, sizeof kosdaq.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    /*
     * 버그 존재함
     * 정규장때 재기동을 한 경우 장개시전시간외 종가와 장개시후시간외 종가는 당일 거래량으로 포함되어야 하는데,
     * B2 의 누적거래량은 바이인을 제외한 전체 거래량을 담으므로, B2 처리시 전체 거래량은 맞게 되지만,
     * 다음 A3 전문 도착시에는 해당 보드 ID 만이 더해지고, 다른 보드 ID 값은 0 이므로, 거래량이 일부 빠지는 상황이 발생할 수 있다.
     *
     * ==> 로직변경
     * B2 수신시
     * 정규장 거래량을 G1 으로 해서 강제로 업데이트 한다.
     * 장개시전 시간외 거래량을 G2 로 해서 강제로 업데이트하고
     * 장개시후 시간외 거래량을 G3 로 해서 강제로 업데이트해야한다.
     */

    /*
     *         char beforeMarketOverTimeClosePriceTradeVolume[12];         // 020 장개시전시간외종가체결수량
     char beforeMarketOverTimeClosePriceTradeAmount[18];         // 021 장개시전시간외종가거래대금
     char regularMarketTradeVolume[12];                          // 022 정규장체결수량
     char regularMarketTradeAmount[18];                          // 023 정규장거래대금
     char afterMarketOvertimeClosePriceTradeVolume[12];          // 024 장종료후시간외종가체결수량
     char afterMarketOvertimeClosePriceTradeAmount[18];          // 025 장종료후시간외종가거래대금
     char earlyClosedELWStatus[1];                               // 026 ELW 조기종료여부
     char earlyClosedELWTime[6];                                 // 027 ELW 조기종료시간
     char aBlox[1];                                              // 028 경쟁대량 방향구분
     char regularBuyInTradingVolume[12];                         // 029 일반 Buy-In 체결수량
     char regularBuyInTradingValue[18];                          // 030 일반 Buy-In 거래대금
     char sameDayBuyInTradingVolume[12];                         // 031 당일 Buy-In 체결수량
     char sameDayBuyInTradingValue[18];                          // 032 당일 Buy-In 거래대금
     */

    /*
     * 아래 값들을 강제로 세팅해야 한다.
     */

    double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(kosdaq.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( kosdaq.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(kosdaq.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( kosdaq.beforeMarketOverTimeClosePriceTradeAmount )).c_str());
    double regularMarketTradeVolume = ::atof(ACE_CString(kosdaq.regularMarketTradeVolume, sizeof ( kosdaq.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(kosdaq.regularMarketTradeAmount, sizeof ( kosdaq.regularMarketTradeAmount )).c_str());
    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(kosdaq.afterMarketOvertimeClosePriceTradeVolume, sizeof ( kosdaq.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(kosdaq.afterMarketOvertimeClosePriceTradeAmount, sizeof ( kosdaq.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    const ACE_CString BOARD_ID_MARKET_IN("G1");
    const ACE_CString BOARD_ID_MARKET_BEFORE_TRADE("G2");
    const ACE_CString BOARD_ID_MARKET_AFTER_TRADE("G3");
    const ACE_CString BOARD_ID_BULK_TRADE_TODAY("ZZ");

    // 장개시전 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, beforeMarketOverTimeClosePriceTradeVolume, BOARD_ID_MARKET_BEFORE_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE) < beforeMarketOverTimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, beforeMarketOverTimeClosePriceTradeAmount, BOARD_ID_MARKET_BEFORE_TRADE);
    }

    // 정규장 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeVolume )
    {
        setAccmVolume(stockCode, regularMarketTradeVolume, BOARD_ID_MARKET_IN);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_IN) < regularMarketTradeAmount )
    {
        setAccmAmount(stockCode, regularMarketTradeAmount, BOARD_ID_MARKET_IN);
    }

    // 장마감후 시간외 거래 값 업데이트
    if ( getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeVolume )
    {
        setAccmVolume(stockCode, afterMarketOvertimeClosePriceTradeVolume, BOARD_ID_MARKET_AFTER_TRADE);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE) < afterMarketOvertimeClosePriceTradeAmount )
    {
        setAccmAmount(stockCode, afterMarketOvertimeClosePriceTradeAmount, BOARD_ID_MARKET_AFTER_TRADE);
    }

    double accmVolume = ::atof(ACE_CString(kosdaq.accmTradeVolume, sizeof kosdaq.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kosdaq.accmTradeAmount, sizeof kosdaq.accmTradeAmount).c_str());

    // 대량체결거래량
    double bulkTradeVolumeEstimated = accmVolume - ( beforeMarketOverTimeClosePriceTradeVolume + regularMarketTradeVolume + afterMarketOvertimeClosePriceTradeVolume );
    // 대량체결거래대금
    double bulkTradeAmountEstimated = accmAmount - ( beforeMarketOverTimeClosePriceTradeAmount + regularMarketTradeAmount + afterMarketOvertimeClosePriceTradeAmount );

    if ( getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY) < bulkTradeVolumeEstimated )
    {
        setAccmVolume(stockCode, bulkTradeVolumeEstimated, BOARD_ID_BULK_TRADE_TODAY);
    }
    if ( getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY) < bulkTradeAmountEstimated )
    {
        setAccmAmount(stockCode, bulkTradeAmountEstimated, BOARD_ID_BULK_TRADE_TODAY);
    }

    ExturePlusKosdaqRecoveryTradeFixed rawTradeFixed;
    ::memset(&rawTradeFixed, 0, sizeof(ExturePlusKosdaqRecoveryTradeFixed));
    int hasValueTradeFixed = tradeFixedMapKosdaq_->find(stockCode, rawTradeFixed, ALLOCATOR::instance());
    if ( hasValueTradeFixed == -1 )
    {
	    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTrade] stockCode:[%s]\thasValueTradeFixed:[%d] == -1 \n" , getCurrentTimestamp().c_str() , stockCode.c_str() , hasValueTradeFixed ));
    }
    else
    {
        ACE_CString strTotalAccmVolume(rawTradeFixed.totalAccmVolume, sizeof ( rawTradeFixed.totalAccmVolume ));
        double totalAccmVolume = parseDouble(strTotalAccmVolume, 0);
        ACE_CString strTotalAccmAmount(rawTradeFixed.totlaAccmAmount, sizeof ( rawTradeFixed.totlaAccmAmount ));
        double totalAccmAmount = parseDouble(strTotalAccmAmount, 0);

        double etcAccmVolume = totalAccmVolume - accmVolume;
        double etcAccmAmount = totalAccmAmount - accmAmount;

        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTrade] stockCode:[%s]\tetcAccmVolume:[%f]\taccmVolume:[%f]\ttotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , etcAccmVolume , accmVolume , totalAccmVolume ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTrade] stockCode:[%s]\tetcAccmAmount:[%f]\ttotalAccmAmount:[%f]\taccmAmount:[%f]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , etcAccmAmount , accmAmount , totalAccmAmount ));

        const ACE_CString BOARD_ID_ETC("ZY");

        if ( etcAccmVolume > 0 )
        {
            setAccmVolume(stockCode, etcAccmVolume, BOARD_ID_ETC);
            accmVolume = totalAccmVolume;
        }
        if ( etcAccmAmount > 0 )
        {
            setAccmAmount(stockCode, etcAccmAmount, BOARD_ID_ETC);
            accmAmount = totalAccmAmount;
        }
    }

    if ( accmVolume < getTotalAccmVolume(stockCode) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
    }

    if ( accmVolume > 0 )
    {
        setTotalAccmVolume(stockCode, accmVolume);
    }
    trade.accmVolume = getTotalAccmVolume(stockCode);

    if ( accmAmount > 0 )
    {
        setTotalAccmAmount(stockCode, accmAmount);
    }
    trade.amount = getTotalAccmAmount(stockCode);

    trade.tradeVolume = 0;

    ACE_CString realRateQuotationClass(kosdaq.realRateQuotationClass, sizeof ( kosdaq.realRateQuotationClass ));

    trade.subtype = getSubType(frameId, realRateQuotationClass);

    time_t tradeTime = time(0);

    if ( hasValue == -1 )
    {
        trade.tradeTime = tradeTime;

#if(1)
        trade.exchange = EXCHANGE_KOSDAQ;
#endif

        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        ACE_OS::memcpy(&trade.symbol, &kosdaq.stockCode, std::min(sizeof trade.symbol, sizeof kosdaq.stockCode));

        trade.tradeVolume = 0.0;
        trade.openMin = 0;
        trade.highMin = 0;
        trade.lowMin = 0;
        trade.volumeMin = 0;
    }

    trade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    Trade oldVal;
    tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());

    char buf[TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &trade, TRADE_SIZE);

#if(1)

	sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KOSDAQ);

    int result = 0;
	result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KOSDAQ);
#endif

#if(0)
printPacketTrade(trade);
#endif

    return result;
}

#if(1)
int InternetKosdaqChannelProcessor::handleCustomIndexRecovery(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleCustomIndexRecovery] packet.length()[%d], packet:[%s]\n" , getCurrentTimestamp().c_str() , packet.length(), packet.c_str() ));

    return 0;
}
#endif

int InternetKosdaqChannelProcessor::handleQuote10(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleQuote10] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKosdaqQuote10 kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), std::min(sizeof kosdaq, packet.length()));

    Quote10 quote;

#if(1)
quote.exchange = EXCHANGE_KOSDAQ;
#endif

    quote.symbolType = SYMBOL_STOCK;
    quote.decimalPoint = 0;

    ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);
    ACE_CString isNormalstockCode(kosdaq.stockCode, ( sizeof kosdaq.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    if ( isValidSymbol(stockCode) == false )
    {
        return 0;
    }

    ACE_OS::memcpy(&quote.symbol, stockCode.c_str(), std::min(sizeof quote.symbol, stockCode.length()));

    ACE_CString boardID(kosdaq.boardID, sizeof kosdaq.boardID);
    ACE_CString sessionID(kosdaq.sessionID, sizeof ( kosdaq.sessionID ));

    if ( ( boardID == "G7" ) || ( boardID == "G8" ) )
    {
        return 0;
    }
    if ( sessionID == "25" )
    {
        return 0;
    }

    if ( ( sessionID == "70" ) || ( boardID == "G4" ) )
    {
        return handleQuote10Fixed(packet);
    }

    quote.concurrent = getConcurrent(boardID, sessionID);

    if ( ( sessionID == "70" ) || ( boardID == "G4" ) )
    {
        return handleQuote10Fixed(packet);
    }

    quote.market = getMarketInQuote10(boardID, sessionID);
    quote.quoteTime = time(0);

    quote.totalAskVolume = atof(ACE_CString(kosdaq.totalAskQuoteRemainder, sizeof kosdaq.totalAskQuoteRemainder).c_str());
    quote.totalBidVolume = atof(ACE_CString(kosdaq.totalBidQuoteRemainder, sizeof kosdaq.totalBidQuoteRemainder).c_str());

    quote.expectedPrice = atoi(ACE_CString(kosdaq.estimatedTradePrice, sizeof kosdaq.estimatedTradePrice).c_str());
    quote.expectedVolume = atof(ACE_CString(kosdaq.estimatedTradeVolume, sizeof kosdaq.estimatedTradeVolume).c_str());

    for ( int i = 0 ; i < int(ARRAYSIZE(kosdaq.rec)) ; ++i )
    {
        quote.rec[i].ask = atoi(ACE_CString(kosdaq.rec[i].askQuote, sizeof kosdaq.rec[i].askQuote).c_str());
        quote.rec[i].askVolume = atoi(ACE_CString(kosdaq.rec[i].askQuoteVolume, sizeof kosdaq.rec[i].askQuoteVolume).c_str());
        quote.rec[i].bid = atoi(ACE_CString(kosdaq.rec[i].bidQuote, sizeof kosdaq.rec[i].bidQuote).c_str());
        quote.rec[i].bidVolume = atoi(ACE_CString(kosdaq.rec[i].bidQuoteVolume, sizeof kosdaq.rec[i].bidQuoteVolume).c_str());
    }

    sendQuote10(quote);

    return 0;
}

int InternetKosdaqChannelProcessor::handleQuote10Fixed(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleQuote10Fixed] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKosdaqQuote10 kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), std::min(sizeof kosdaq, packet.length()));

    Quote10 quote;

#if(1)
quote.exchange = EXCHANGE_KOSDAQ;
#endif

    quote.symbolType = SYMBOL_STOCK;
    quote.decimalPoint = 0;

    ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);
    ACE_OS::memcpy(&quote.symbol, stockCode.c_str(), std::min(sizeof quote.symbol, stockCode.length()));

    ACE_CString boardID(kosdaq.boardID, sizeof kosdaq.boardID);
    ACE_CString sessionID(kosdaq.sessionID, sizeof kosdaq.sessionID);

    // 구스펙 : 동시구분
    // 신스펙 : X

    quote.concurrent = getConcurrent(boardID, sessionID);
    quote.market = getMarketInQuote10(boardID, sessionID);
    quote.quoteTime = time(0);
    quote.totalAskVolume = atof(ACE_CString(kosdaq.totalAskQuoteRemainder, sizeof kosdaq.totalAskQuoteRemainder).c_str());
    quote.totalBidVolume = atof(ACE_CString(kosdaq.totalBidQuoteRemainder, sizeof kosdaq.totalBidQuoteRemainder).c_str());
    quote.expectedPrice = atoi(ACE_CString(kosdaq.estimatedTradePrice, sizeof kosdaq.estimatedTradePrice).c_str());
    quote.expectedVolume = atof(ACE_CString(kosdaq.estimatedTradeVolume, sizeof kosdaq.estimatedTradeVolume).c_str());

    for ( int i = 0 ; i < int(ARRAYSIZE(kosdaq.rec)) ; ++i )
    {
        quote.rec[i].ask = atoi(ACE_CString(kosdaq.rec[i].askQuote, sizeof kosdaq.rec[i].askQuote).c_str());
        quote.rec[i].askVolume = atoi(ACE_CString(kosdaq.rec[i].askQuoteVolume, sizeof kosdaq.rec[i].askQuoteVolume).c_str());
        quote.rec[i].bid = atoi(ACE_CString(kosdaq.rec[i].bidQuote, sizeof kosdaq.rec[i].bidQuote).c_str());
        quote.rec[i].bidVolume = atoi(ACE_CString(kosdaq.rec[i].bidQuoteVolume, sizeof kosdaq.rec[i].bidQuoteVolume).c_str());
    }

    char buf[QUOTE10_SIZE];
    memcpy(buf, &quote, std::min(sizeof buf, sizeof quote));

#if(1)

	int result = 0;

	result = sendPacket(ACE_CString(buf, QUOTE10_SIZE), PACKET_QUOTE10_FIXED, EXCHANGE_KOSDAQ);
#endif

#if(0)
printPacketQuote10(quote);
#endif

    return result;
}

int InternetKosdaqChannelProcessor::handleSecuritiesTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleSecuritiesTrade] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKosdaqSecuritiesTrade kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_SIZE);

    SecuritiesTrade2 sec;
    ::memset(&sec, 0, sizeof(SecuritiesTrade2));
    sec.subtype = SECURITIESTRADESUBTYPE_TRADE;

#if(1)
sec.exchange = EXCHANGE_KOSDAQ;
#endif

    sec.symbolType = SYMBOL_STOCK;
    ACE_CString stockCode = ACE_CString(kosdaq.stockCode, sizeof kosdaq.stockCode);
    ACE_CString isNormalstockCode(kosdaq.stockCode, ( sizeof kosdaq.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    if ( isValidSymbol(stockCode) == false )
    {
        return 0;
    }

    memcpy(&sec.symbol, stockCode.c_str(), std::min(sizeof sec.symbol, stockCode.length()));

    ACE_OS::memcpy(&sec.rec1.seller, kosdaq.rec[0].askSecuritiesTradeNumber + 2, std::min(sizeof sec.rec1.seller, ( sizeof kosdaq.rec[0].askSecuritiesTradeNumber ) - 2));
    ACE_OS::memcpy(&sec.rec1.buyer, kosdaq.rec[0].bidSecuritiesTradeNumber + 2, std::min(sizeof sec.rec1.buyer, ( sizeof kosdaq.rec[0].bidSecuritiesTradeNumber ) - 2));
    sec.rec1.askVolume = atof(ACE_CString(kosdaq.rec[0].askTradeVolume, sizeof kosdaq.rec[0].askTradeVolume).c_str());
    sec.rec1.bidVolume = atof(ACE_CString(kosdaq.rec[0].bidTradeVolume, sizeof kosdaq.rec[0].bidTradeVolume).c_str());
    sec.rec1.askAmount = atof(ACE_CString(kosdaq.rec[0].askTradeAmount, sizeof kosdaq.rec[0].askTradeAmount).c_str());
    sec.rec1.bidAmount = atof(ACE_CString(kosdaq.rec[0].bidTradeAmount, sizeof kosdaq.rec[0].bidTradeAmount).c_str());

    ACE_OS::memcpy(&sec.rec2.seller, kosdaq.rec[1].askSecuritiesTradeNumber + 2, std::min(sizeof sec.rec2.seller, ( sizeof kosdaq.rec[1].askSecuritiesTradeNumber ) - 2));
    ACE_OS::memcpy(&sec.rec2.buyer, kosdaq.rec[1].bidSecuritiesTradeNumber + 2, std::min(sizeof sec.rec2.buyer, ( sizeof kosdaq.rec[1].bidSecuritiesTradeNumber ) - 2));
    sec.rec2.askVolume = atof(ACE_CString(kosdaq.rec[1].askTradeVolume, sizeof kosdaq.rec[1].askTradeVolume).c_str());
    sec.rec2.bidVolume = atof(ACE_CString(kosdaq.rec[1].bidTradeVolume, sizeof kosdaq.rec[1].bidTradeVolume).c_str());
    sec.rec2.askAmount = atof(ACE_CString(kosdaq.rec[1].askTradeAmount, sizeof kosdaq.rec[1].askTradeAmount).c_str());
    sec.rec2.bidAmount = atof(ACE_CString(kosdaq.rec[1].bidTradeAmount, sizeof kosdaq.rec[1].bidTradeAmount).c_str());

    ACE_OS::memcpy(&sec.rec3.seller, kosdaq.rec[2].askSecuritiesTradeNumber + 2, std::min(sizeof sec.rec3.seller, ( sizeof kosdaq.rec[2].askSecuritiesTradeNumber ) - 2));
    ACE_OS::memcpy(&sec.rec3.buyer, kosdaq.rec[2].bidSecuritiesTradeNumber + 2, std::min(sizeof sec.rec3.buyer, ( sizeof kosdaq.rec[2].bidSecuritiesTradeNumber ) - 2));
    sec.rec3.askVolume = atof(ACE_CString(kosdaq.rec[2].askTradeVolume, sizeof kosdaq.rec[2].askTradeVolume).c_str());
    sec.rec3.bidVolume = atof(ACE_CString(kosdaq.rec[2].bidTradeVolume, sizeof kosdaq.rec[2].bidTradeVolume).c_str());
    sec.rec3.askAmount = atof(ACE_CString(kosdaq.rec[2].askTradeAmount, sizeof kosdaq.rec[2].askTradeAmount).c_str());
    sec.rec3.bidAmount = atof(ACE_CString(kosdaq.rec[2].bidTradeAmount, sizeof kosdaq.rec[2].bidTradeAmount).c_str());

    ACE_OS::memcpy(&sec.rec4.seller, kosdaq.rec[3].askSecuritiesTradeNumber + 2, std::min(sizeof sec.rec4.seller, ( sizeof kosdaq.rec[3].askSecuritiesTradeNumber ) - 2));
    ACE_OS::memcpy(&sec.rec4.buyer, kosdaq.rec[3].bidSecuritiesTradeNumber + 2, std::min(sizeof sec.rec4.buyer, ( sizeof kosdaq.rec[3].bidSecuritiesTradeNumber ) - 2));
    sec.rec4.askVolume = atof(ACE_CString(kosdaq.rec[3].askTradeVolume, sizeof kosdaq.rec[3].askTradeVolume).c_str());
    sec.rec4.bidVolume = atof(ACE_CString(kosdaq.rec[3].bidTradeVolume, sizeof kosdaq.rec[3].bidTradeVolume).c_str());
    sec.rec4.askAmount = atof(ACE_CString(kosdaq.rec[3].askTradeAmount, sizeof kosdaq.rec[3].askTradeAmount).c_str());
    sec.rec4.bidAmount = atof(ACE_CString(kosdaq.rec[3].bidTradeAmount, sizeof kosdaq.rec[3].bidTradeAmount).c_str());

    ACE_OS::memcpy(&sec.rec5.seller, kosdaq.rec[4].askSecuritiesTradeNumber + 2, std::min(sizeof sec.rec5.seller, ( sizeof kosdaq.rec[4].askSecuritiesTradeNumber ) - 2));
    ACE_OS::memcpy(&sec.rec5.buyer, kosdaq.rec[4].bidSecuritiesTradeNumber + 2, std::min(sizeof sec.rec5.buyer, ( sizeof kosdaq.rec[4].bidSecuritiesTradeNumber ) - 2));
    sec.rec5.askVolume = atof(ACE_CString(kosdaq.rec[4].askTradeVolume, sizeof kosdaq.rec[4].askTradeVolume).c_str());
    sec.rec5.bidVolume = atof(ACE_CString(kosdaq.rec[4].bidTradeVolume, sizeof kosdaq.rec[4].bidTradeVolume).c_str());
    sec.rec5.askAmount = atof(ACE_CString(kosdaq.rec[4].askTradeAmount, sizeof kosdaq.rec[4].askTradeAmount).c_str());
    sec.rec5.bidAmount = atof(ACE_CString(kosdaq.rec[4].bidTradeAmount, sizeof kosdaq.rec[4].bidTradeAmount).c_str());

    char buf[SECURITIES_TRADE2_SIZE];
    memcpy(buf, &sec, std::min(sizeof buf, sizeof sec));

#if(1)

	int result = 0;

	result = sendPacket(ACE_CString(buf, SECURITIES_TRADE2_SIZE), PACKET_SECURITIES_TRADE, EXCHANGE_KOSDAQ);
#endif

#if(0)
printPacketSecuritiesTrade2(sec);
#endif

    return result;
}

int InternetKosdaqChannelProcessor::handleProgramTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleProgramTrade] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // copy raw data
    ExturePlusKosdaqProgramTrade kosdaqProgTrd;
    ACE_OS::memcpy(&kosdaqProgTrd, packet.c_str(), packet.length());

    // set basic info
    ProgramTrade paxProgTrd;

#if(1)
paxProgTrd.exchange = EXCHANGE_KOSDAQ;
#endif

    paxProgTrd.symbolType = SYMBOL_STOCK;

    // set datas
    ACE_OS::memcpy(paxProgTrd.symbol, kosdaqProgTrd.stockCode, std::min(sizeof ( paxProgTrd.symbol ), sizeof ( kosdaqProgTrd.stockCode )));

    paxProgTrd.mpSellQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskQuoteRemainder, sizeof ( kosdaqProgTrd.indexMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrd.mpBuyQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidQuoteRemainder, sizeof ( kosdaqProgTrd.indexMarginalProfitBidQuoteRemainder )).c_str());
    paxProgTrd.nmpSellQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskQuoteRemainder, sizeof ( kosdaqProgTrd.indexNotMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrd.nmpBuyQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidQuoteRemainder, sizeof ( kosdaqProgTrd.indexNotMarginalProfitBidQuoteRemainder )).c_str());
    paxProgTrd.mpSellQuoteVolume = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskQuoteVolume, sizeof ( kosdaqProgTrd.indexMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrd.mpBuyQuoteVolume = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidQuoteVolume, sizeof ( kosdaqProgTrd.indexMarginalProfitBidQuoteVolume )).c_str());
    paxProgTrd.nmpSellQuoteVolume = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskQuoteVolume, sizeof ( kosdaqProgTrd.indexNotMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrd.nmpBuyQuoteVolume = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidQuoteVolume, sizeof ( kosdaqProgTrd.indexNotMarginalProfitBidQuoteVolume )).c_str());

    // 매도위탁체결수량
    // 아래 코드를 변경함
    // paxProgTrd.sellCommitTradeVolume = 
    //   ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeVolume, sizeof(kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume, sizeof(kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume)).c_str());
    double indexMarginalProfitAskConsignmentTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeVolume, sizeof ( kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeVolume )).c_str());
    double indexNotMarginalProfitAskConsignmentTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume, sizeof ( kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume )).c_str());
    paxProgTrd.sellCommitTradeVolume = indexMarginalProfitAskConsignmentTradeVolume + indexNotMarginalProfitAskConsignmentTradeVolume;

    // 매도자기체결수량
    // 아래 코드를 변경함
    // paxProgTrd.sellSelfTradeVolume =
    //   ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskFloorTradeVolume, sizeof(kosdaqProgTrd.indexMarginalProfitAskFloorTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeVolume, sizeof(kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeVolume)).c_str());
    double indexMarginalProfitAskFloorTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskFloorTradeVolume, sizeof ( kosdaqProgTrd.indexMarginalProfitAskFloorTradeVolume )).c_str());
    double indexNotMarginalProfitAskFloorTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeVolume, sizeof ( kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeVolume )).c_str());
    paxProgTrd.sellSelfTradeVolume = indexMarginalProfitAskFloorTradeVolume + indexNotMarginalProfitAskFloorTradeVolume;

    // 매수위탁체결수량
    // 아래코드를 변경함
    // paxProgTrd.buyCommitTradeVolume =
    //   ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeVolume, sizeof(kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume, sizeof(kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume)).c_str());
    double indexMarginalProfitBidConsignmentTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeVolume, sizeof ( kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeVolume )).c_str());
    double indexNotMarginalProfitBidConsignmentTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume, sizeof ( kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume )).c_str());
    paxProgTrd.buyCommitTradeVolume = indexMarginalProfitBidConsignmentTradeVolume + indexNotMarginalProfitBidConsignmentTradeVolume;

    // 매수자기체결수량
    // 아래코드를 변경함
    // paxProgTrd.buySelfTradeVolume =
    //   ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidFloorTradeVolume, sizeof(kosdaqProgTrd.indexMarginalProfitBidFloorTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeVolume, sizeof(kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeVolume)).c_str());
    double indexMarginalProfitBidFloorTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidFloorTradeVolume, sizeof ( kosdaqProgTrd.indexMarginalProfitBidFloorTradeVolume )).c_str());
    double indexNotMarginalProfitBidFloorTradeVolume = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeVolume, sizeof ( kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeVolume )).c_str());
    paxProgTrd.buySelfTradeVolume = indexMarginalProfitBidFloorTradeVolume + indexNotMarginalProfitBidFloorTradeVolume;

    // 구스펙 : 매도위탁체결금액 
    // 신스펙 : (지수)차익매도위탁체결금액 + (지수)비차익매도위탁체결금
    //paxProgTrd.sellCommitTradeAmount = 
    //  ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeAmount, sizeof(kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeAmount)).c_str())
    //  + ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount, sizeof(kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount)).c_str());
    double indexMarginalProfitAskConsignmentTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeAmount, sizeof ( kosdaqProgTrd.indexMarginalProfitAskConsignmentTradeAmount )).c_str());
    double indexNotMarginalProfitAskConsignmentTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount, sizeof ( kosdaqProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount )).c_str());
    paxProgTrd.sellCommitTradeAmount = indexMarginalProfitAskConsignmentTradeAmount + indexNotMarginalProfitAskConsignmentTradeAmount;

    // 아래코드를 변경함
    //paxProgTrd.sellSelfTradeAmount =
    //  ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskFloorTradeAmount, sizeof(kosdaqProgTrd.indexMarginalProfitAskFloorTradeAmount)).c_str())
    //  + ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeAmount, sizeof(kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeAmount)).c_str());
    double indexMarginalProfitAskFloorTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitAskFloorTradeAmount, sizeof ( kosdaqProgTrd.indexMarginalProfitAskFloorTradeAmount )).c_str());
    double indexNotMarginalProfitAskFloorTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeAmount, sizeof ( kosdaqProgTrd.indexNotMarginalProfitAskFloorTradeAmount )).c_str());
    paxProgTrd.sellSelfTradeAmount = indexMarginalProfitAskFloorTradeAmount + indexNotMarginalProfitAskFloorTradeAmount;

    // 아래코드를 변경함
    //paxProgTrd.buyCommitTradeAmount = 
    //  ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeAmount, sizeof(kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeAmount)).c_str())
    //  + ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount, sizeof(kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount)).c_str());
    double indexMarginalProfitBidConsignmentTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeAmount, sizeof ( kosdaqProgTrd.indexMarginalProfitBidConsignmentTradeAmount )).c_str());
    double indexNotMarginalProfitBidConsignmentTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount, sizeof ( kosdaqProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount )).c_str());
    paxProgTrd.buyCommitTradeAmount = indexMarginalProfitBidConsignmentTradeAmount + indexNotMarginalProfitBidConsignmentTradeAmount;

    // 아래코드를 변경함
    //paxProgTrd.buySelfTradeAmount =
    //  ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidFloorTradeAmount, sizeof(kosdaqProgTrd.indexMarginalProfitBidFloorTradeAmount)).c_str());
    //  + ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeAmount, sizeof(kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeAmount)).c_str());
    double indexMarginalProfitBidFloorTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexMarginalProfitBidFloorTradeAmount, sizeof ( kosdaqProgTrd.indexMarginalProfitBidFloorTradeAmount )).c_str());
    double indexNotMarginalProfitBidFloorTradeAmount = ::atof(ACE_CString(kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeAmount, sizeof ( kosdaqProgTrd.indexNotMarginalProfitBidFloorTradeAmount )).c_str());
    paxProgTrd.buySelfTradeAmount = indexMarginalProfitBidFloorTradeAmount + indexNotMarginalProfitBidFloorTradeAmount;

    //프로그램매도사전공시수량, 프로그램매수공시수량 -> 스펙 분리 C5
    ACE_CString stockCode(kosdaqProgTrd.stockCode, sizeof kosdaqProgTrd.stockCode);
    ExturePlusKosdaqProgramTradePublic kosdaqProgTrdPublic;

    int hasValue = programTradeMapKosdaq_->find(stockCode, kosdaqProgTrdPublic, ALLOCATOR::instance());

    if ( hasValue == -1 )
    {
        paxProgTrd.paSellVolume = 0.0f;
        paxProgTrd.paBuyVolume = 0.0f;
    }
    else
    {
        paxProgTrd.paSellVolume = ::atof(ACE_CString(kosdaqProgTrdPublic.askPublicAheadPublicPrevRemainder, sizeof ( kosdaqProgTrdPublic.askPublicAheadPublicPrevRemainder )).c_str());
        paxProgTrd.paBuyVolume = ::atof(ACE_CString(kosdaqProgTrdPublic.bidPublicAheadPublicPrevRemainder, sizeof ( kosdaqProgTrdPublic.bidPublicAheadPublicPrevRemainder )).c_str());
    }

#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrd), sizeof(ProgramTrade)), PACKET_PROGRAM, EXCHANGE_KOSDAQ);
#endif

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleProgramTrade] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));
//    printPacketProgramTrade(paxProgTrd);
    return result;
}

int InternetKosdaqChannelProcessor::handleProgramTradePublic(const ACE_CString &packet)
{
    int result = 0;
    try
    {
        if ( EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_PUBLIC_SIZE != static_cast<int>(packet.length()) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::hanldeProgramTradePublic] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_PUBLIC_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_PUBLIC_SIZE , packet.length() , packet.c_str() ), -1);
        }

        // log frame count status
        LogFrameCount(packet.substr(0, 2).c_str());

        ExturePlusKosdaqProgramTradePublic kosdaqProgTrdPublic;
        ACE_OS::memcpy(&kosdaqProgTrdPublic, packet.c_str(), packet.length());

        ACE_CString stockCode(kosdaqProgTrdPublic.stockCode, sizeof kosdaqProgTrdPublic.stockCode);
        ACE_CString dataClass(kosdaqProgTrdPublic.dataClass, sizeof kosdaqProgTrdPublic.dataClass);
        ACE_CString infoClass(kosdaqProgTrdPublic.infoClass, sizeof kosdaqProgTrdPublic.infoClass);
        ACE_CString marketClass(kosdaqProgTrdPublic.marketClass, sizeof kosdaqProgTrdPublic.marketClass);
        ACE_CString askPublicAheadPublicPrevRemainder(kosdaqProgTrdPublic.askPublicAheadPublicPrevRemainder, sizeof kosdaqProgTrdPublic.askPublicAheadPublicPrevRemainder);
        ACE_CString bidPublicAheadPublicPrevRemainder(kosdaqProgTrdPublic.bidPublicAheadPublicPrevRemainder, sizeof kosdaqProgTrdPublic.bidPublicAheadPublicPrevRemainder);
        ACE_CString askPublicAheadPublicPrevCorrectingRemainder(kosdaqProgTrdPublic.askPublicAheadPublicPrevCorrectingRemainder, sizeof kosdaqProgTrdPublic.askPublicAheadPublicPrevCorrectingRemainder);
        ACE_CString bidPublicAheadPublicPrevCorrectingRemainder(kosdaqProgTrdPublic.bidPublicAheadPublicPrevCorrectingRemainder, sizeof kosdaqProgTrdPublic.bidPublicAheadPublicPrevCorrectingRemainder);
        ACE_CString postDisclosedProgramTradingSellOrderVolume(kosdaqProgTrdPublic.postDisclosedProgramTradingSellOrderVolume, sizeof kosdaqProgTrdPublic.postDisclosedProgramTradingSellOrderVolume);
        ACE_CString postDisclosedProgramTradingBuyOrderVolume(kosdaqProgTrdPublic.postDisclosedProgramTradingBuyOrderVolume, sizeof kosdaqProgTrdPublic.postDisclosedProgramTradingBuyOrderVolume);

        int hasValue = programTradeMapKosdaq_->find(stockCode, kosdaqProgTrdPublic, ALLOCATOR::instance());
        if ( hasValue == -1 )
        {
            programTradeMapKosdaq_->bind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kosdaqProgTrdPublic, ALLOCATOR::instance());
        }
        else
        {
            ACE_CString oldKey;
            ExturePlusKosdaqProgramTradePublic oldVal;
            programTradeMapKosdaq_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kosdaqProgTrdPublic, oldKey, oldVal, ALLOCATOR::instance());
        }
    }
    catch ( std::exception& e )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleProgramTradePublic] error occur e.what[%s]\n" , getCurrentTimestamp().c_str() , e.what() ));
        result = -1;
    }
    return result;
}

int InternetKosdaqChannelProcessor::handleProgramTradeTotal(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_TOTAL_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleProgramTradeTotal] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_TOTAL_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_TOTAL_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // copy raw data
    ExturePlusKosdaqProgramTradeTotal kosdaqProgTrdTot;
    ACE_OS::memcpy(&kosdaqProgTrdTot, packet.c_str(), packet.length());

    // set basic info
    ProgramTradeTotal paxProgTrdTot;

#if(1)
paxProgTrdTot.exchange = EXCHANGE_KOSDAQ;
#endif

    // set datas
    paxProgTrdTot.mpSellQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitAskQuoteRemainder, sizeof ( kosdaqProgTrdTot.indexMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrdTot.mpBuyQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitBidQuoteRemainder, sizeof ( kosdaqProgTrdTot.indexMarginalProfitBidQuoteRemainder )).c_str());
    paxProgTrdTot.nmpSellQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitAskQuoteRemainder, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrdTot.nmpBuyQuoteRemainder = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitBidQuoteRemainder, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitBidQuoteRemainder )).c_str());

    paxProgTrdTot.mpSellQuoteVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitAskQuoteVolume, sizeof ( kosdaqProgTrdTot.indexMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrdTot.mpBuyQuoteVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitBidQuoteVolume, sizeof ( kosdaqProgTrdTot.indexMarginalProfitBidQuoteVolume )).c_str());
    paxProgTrdTot.nmpSellQuoteVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitAskQuoteVolume, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrdTot.nmpBuyQuoteVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitBidQuoteVolume, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitBidQuoteVolume )).c_str());

    paxProgTrdTot.mpSellCommitTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitAskConsignmentTradeVolume, sizeof ( kosdaqProgTrdTot.indexMarginalProfitAskConsignmentTradeVolume )).c_str());
    paxProgTrdTot.mpSellSelfTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitAskFloorTradeVolume, sizeof ( kosdaqProgTrdTot.indexMarginalProfitAskFloorTradeVolume )).c_str());
    paxProgTrdTot.mpBuyCommitTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitBidConsignmentTradeVolume, sizeof ( kosdaqProgTrdTot.indexMarginalProfitBidConsignmentTradeVolume )).c_str());
    paxProgTrdTot.mpBuySelfTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitBidFloorTradeVolume, sizeof ( kosdaqProgTrdTot.indexMarginalProfitBidFloorTradeVolume )).c_str());

    paxProgTrdTot.nmpSellCommitTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitAskConsignmentTradeVolume, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitAskConsignmentTradeVolume )).c_str());
    paxProgTrdTot.nmpSellSelfTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitAskFloorTradeVolume, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitAskFloorTradeVolume )).c_str());
    paxProgTrdTot.nmpBuyCommitTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitBidConsignmentTradeVolume, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitBidConsignmentTradeVolume )).c_str());
    paxProgTrdTot.nmpBuySelfTradeVolume = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitBidFloorTradeVolume, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitBidFloorTradeVolume )).c_str());

    paxProgTrdTot.mpSellCommitTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitAskConsignmentTradeAmount, sizeof ( kosdaqProgTrdTot.indexMarginalProfitAskConsignmentTradeAmount )).c_str());
    paxProgTrdTot.mpSellSelfTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitAskFloorTradeAmount, sizeof ( kosdaqProgTrdTot.indexMarginalProfitAskFloorTradeAmount )).c_str());
    paxProgTrdTot.mpBuyCommitTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitBidConsignmentTradeAmount, sizeof ( kosdaqProgTrdTot.indexMarginalProfitBidConsignmentTradeAmount )).c_str());
    paxProgTrdTot.mpBuySelfTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexMarginalProfitBidFloorTradeAmount, sizeof ( kosdaqProgTrdTot.indexMarginalProfitBidFloorTradeAmount )).c_str());

    paxProgTrdTot.nmpSellCommitTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitAskConsignmentTradeAmount, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitAskConsignmentTradeAmount )).c_str());
    paxProgTrdTot.nmpSellSelfTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitAskFloorTradeAmount, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitAskFloorTradeAmount )).c_str());
    paxProgTrdTot.nmpBuyCommitTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitBidConsignmentTradeAmount, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitBidConsignmentTradeAmount )).c_str());
    paxProgTrdTot.nmpBuySelfTradeAmount = ::atof(ACE_CString(kosdaqProgTrdTot.indexNotMarginalProfitBidFloorTradeAmount, sizeof ( kosdaqProgTrdTot.indexNotMarginalProfitBidFloorTradeAmount )).c_str());


#if(1)
    // transfer
	int result = 0;

	result = sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdTot), sizeof(ProgramTradeTotal)), PACKET_PROGRAM_TOTAL, EXCHANGE_KOSDAQ);
#endif

#if(0)
printPacketProgramTradeTotal(paxProgTrdTot);
#endif

    return result;
}

int InternetKosdaqChannelProcessor::handleTradeFixed(const ExturePlusKosdaqTrade &kosdaq)
{
    time_t tradeTime = ::time(0);

    Trade trade;
    ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);

    ACE_CString upDown(kosdaq.upDown, sizeof kosdaq.upDown);
    trade.subtype = TRADESUBTYPE_TRADE;

    trade.market = MARKET_IN;
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kosdaq.openPrice, sizeof kosdaq.openPrice).c_str());
    trade.high = atoi(ACE_CString(kosdaq.highPrice, sizeof kosdaq.highPrice).c_str());
    trade.low = atoi(ACE_CString(kosdaq.lowPrice, sizeof kosdaq.lowPrice).c_str());
    trade.close = atoi(ACE_CString(kosdaq.tradePrice, sizeof kosdaq.tradePrice).c_str());

    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    trade.accmVolume = ::atof(ACE_CString(kosdaq.accmTradeVolume, sizeof kosdaq.accmTradeVolume).c_str());
    trade.amount = ::atof(ACE_CString(kosdaq.accmTradeAmount, sizeof kosdaq.accmTradeAmount).c_str());
    trade.tradeVolume = 0;
    trade.tradeTime = tradeTime;

#if(1)
trade.exchange = EXCHANGE_KOSDAQ;
#endif

    trade.symbolType = SYMBOL_STOCK;
    trade.decimalPoint = DECIMAL_0;
    memcpy(&trade.symbol, &kosdaq.stockCode, std::min(sizeof trade.symbol, sizeof kosdaq.stockCode));

    trade.openMin = 0;
    trade.highMin = 0;
    trade.lowMin = 0;
    trade.volumeMin = 0;

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, std::min(sizeof buf, sizeof trade));

#if(1)

	int result = 0;

	result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE_FIXED, EXCHANGE_KOSDAQ);
#endif

#if(0)
printPacketTrade(trade);
#endif

    return result;
}

int InternetKosdaqChannelProcessor::handleRecoveryTradeFixed(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_FIXED_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTradeFixed] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_FIXED_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_FIXED_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId.c_str());

    ExturePlusKosdaqRecoveryTradeFixed kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), std::min(sizeof kosdaq, packet.length()));

    Trade trade;
    ACE_CString stockCode(kosdaq.stockCode, sizeof kosdaq.stockCode);
    TickFilter filter;

    ACE_CString overTimeMarketFixedMarketClass(kosdaq.overTimeMarketFixedMarketClass, sizeof kosdaq.overTimeMarketFixedMarketClass);
    ACE_CString upDown(kosdaq.upDown, sizeof kosdaq.upDown);

    trade.market = getMarketInRecoveryTradeFixed(overTimeMarketFixedMarketClass);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kosdaq.overTimeMarketFixedOpenPrice, sizeof kosdaq.overTimeMarketFixedOpenPrice).c_str());
    trade.high = atoi(ACE_CString(kosdaq.overTimeMarketFixedHighPrice, sizeof kosdaq.overTimeMarketFixedHighPrice).c_str());
    trade.low = atoi(ACE_CString(kosdaq.overTimeMarketFixedLowPrice, sizeof kosdaq.overTimeMarketFixedLowPrice).c_str());
    trade.close = atoi(ACE_CString(kosdaq.overTimeMarketFixedCurrClosePrice, sizeof kosdaq.overTimeMarketFixedCurrClosePrice).c_str());

    int gap = atoi(ACE_CString(kosdaq.gap, sizeof kosdaq.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(kosdaq.overTimeMarketFixedAccmVolume, sizeof kosdaq.overTimeMarketFixedAccmVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kosdaq.overTimeMarketFixedAccmAmount, sizeof kosdaq.overTimeMarketFixedAccmAmount).c_str());

    trade.tradeVolume = 0;

    trade.accmVolume = accmVolume;
    trade.amount = accmAmount;

    ACE_CString realRateQuotationClass(kosdaq.realRateQuotationClass, sizeof ( kosdaq.realRateQuotationClass ));
    trade.subtype = getSubType(frameId, realRateQuotationClass);

    time_t tradeTime = time(0);

    trade.tradeTime = tradeTime;

#if(1)
    trade.exchange = EXCHANGE_KOSDAQ;
#endif

    trade.symbolType = SYMBOL_STOCK;
    trade.decimalPoint = DECIMAL_0;
    ACE_OS::memcpy(&trade.symbol, &kosdaq.stockCode, std::min(sizeof trade.symbol, sizeof kosdaq.stockCode));

    trade.tradeVolume = 0.0;
    trade.openMin = 0;
    trade.highMin = 0;
    trade.lowMin = 0;
    trade.volumeMin = 0;

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, std::min(sizeof buf, sizeof trade));

#if(1)
	int result = 0;
	result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE_FIXED, EXCHANGE_KOSDAQ);
#endif


#if(0)
printPacketTrade(trade);
#endif

    if ( frameId == "B3" )
    {
        ACE_CString oldKey;
        ExturePlusKosdaqRecoveryTradeFixed oldValue;
        ::memset(&oldValue, 0, sizeof(ExturePlusKosdaqRecoveryTradeFixed));
        int rebindResult = tradeFixedMapKosdaq_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kosdaq, oldKey, oldValue, ALLOCATOR::instance());
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleRecoveryTradeFixed] frameId:[%s]\tstockCode:[%s]\trebindResult:[%d]\n" , getCurrentTimestamp().c_str() , frameId.c_str() , stockCode.c_str() , rebindResult ));
    }

    return result;
}

int InternetKosdaqChannelProcessor::handleMarketOperationScheduleDisclosure(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleMarketOperationScheduleDisclosure] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , 
			getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExturePlusKosdaqMarketOperationScheduleDisclosure rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKosdaqMarketOperationScheduleDisclosure));
    ::memcpy(&rawRec, packet.c_str(), sizeof(ExturePlusKosdaqMarketOperationScheduleDisclosure));

	ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
	ACE_CString marketCategory(rawRec.marketCategory, sizeof ( rawRec.marketCategory ));

#if(0)
	ACE_CString issueCode(rawRec.issueCode, sizeof(rawRec.issueCode ));
	ACE_CString listedIssueCode(rawRec.listedIssueCode, sizeof ( rawRec.listedIssueCode ));
#endif

	ACE_CString boardID(rawRec.boardID, sizeof ( rawRec.boardID ));
	ACE_CString boardEventID(rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
	ACE_CString boardEventBeginTime(rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
	ACE_CString boardEventApplyCode(rawRec.boardEventApplyCode, sizeof ( rawRec.boardEventApplyCode ));
	ACE_CString sessionBeginEndCode(rawRec.sessionBeginEndCode, sizeof ( rawRec.sessionBeginEndCode ));
	ACE_CString sessionID(rawRec.sessionID, sizeof ( rawRec.sessionID ));
	ACE_CString tradingHaltReasonCode(rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));
	ACE_CString tradingHaltOccurenceTypeCode(rawRec.tradingHaltOccurenceTypeCode, sizeof ( rawRec.tradingHaltOccurenceTypeCode ));
	ACE_CString stepApplied(rawRec.stepApplied, sizeof ( rawRec.stepApplied ));

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

#if(1)
    std::string issueCode(rawRec.issueCode, sizeof(rawRec.issueCode));
    boost::trim(issueCode);
#endif

#if(1)
    std::string listedIssueCode(rawRec.listedIssueCode, sizeof ( rawRec.listedIssueCode ));
    boost::trim(listedIssueCode);
#endif

    ACE_CString symbol;

    if ( ( issueCode == std::string("") ) || ( listedIssueCode == std::string("") ) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleMarketOperationScheduleDisclosure] issueCode:[%s][%d]\tlistedIssueCode:[%s][%d]\t\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , issueCode.length() , listedIssueCode.c_str() , listedIssueCode.length() ));

        // 종목코드없을 경우 시장공통으로 설정
        symbol = "KRI501000000";
    }
    else
    {
        ACE_CString symbolTemp(issueCode.c_str());
        symbol = symbolTemp;
    }

    ::memcpy(&marketRec.symbol, symbol.c_str(), symbol.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(&marketRec.boardId, rawRec.boardID, sizeof ( rawRec.boardID ));
    ::memcpy(&marketRec.boardEventId, rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
    ::memcpy(&marketRec.beginTime, rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
    ::memcpy(&marketRec.tradingHaltReason, rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));

    printPacketMarketOperation(marketRec);

    char buf[MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(MarketOperation));


#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KOSDAQ);
#endif

    return result;
}

int InternetKosdaqChannelProcessor::handleMarketOperationTS(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_TS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleMarketOperationTS] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_TS_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_TS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExturePlusKosdaqMarketOperationTS rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKosdaqMarketOperationTS));
    ::memcpy(&rawRec, packet.c_str(), sizeof(ExturePlusKosdaqMarketOperationTS));

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    std::string issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    boost::trim(issueCode);

    if ( issueCode == std::string("") )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleMarketOperationTS] invalid issueCode:[%s][%d] skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , issueCode.length() ));
        return 0;
    }

    ACE_CString symbol(issueCode.c_str());

    ::memcpy(&marketRec.symbol, symbol.c_str(), symbol.length());
    marketRec.recvTime = (int) ( ::time(0) );
    ::memcpy(&marketRec.boardId, rawRec.boardID, sizeof ( rawRec.boardID ));
    ::memcpy(&marketRec.boardEventId, rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
    ::memcpy(&marketRec.beginTime, rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
    ::memcpy(&marketRec.tradingHaltReason, rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));

    printPacketMarketOperation(marketRec);

    char buf[MARKET_OPERATION_SIZE];
    ::memset(&buf, 0, sizeof ( buf ));
    ::memcpy(&buf, &marketRec, sizeof(MarketOperation));



#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KOSDAQ);
#endif

	return result;
}


int InternetKosdaqChannelProcessor::handleShortSellingInfo(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_SHORT_SELLING_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_SHORT_SELLING_INFORMATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_SHORT_SELLING_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKosdaqShortSellingInformation shortSellingInfoRec;
    ACE_OS::memcpy(&shortSellingInfoRec, packet.c_str(), packet.length());

    ACE_CString issueCode(shortSellingInfoRec.issueCode, sizeof ( shortSellingInfoRec.issueCode ));
    ACE_CString shortSellingDebtSecuritiesAskTradingVolume(shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingVolume, sizeof ( shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingVolume ));
    ACE_CString shortSellingDebtSecuritiesAskTradingValue(shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingValue, sizeof ( shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingValue ));
    ACE_CString upTickRuleAppliedCoveredShortSellingTradingVolume(shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingVolume, sizeof ( shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingVolume ));
    ACE_CString upTickRuleAppliedCoveredShortSellingTradingValue(shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingValue, sizeof ( shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingValue ));
    ACE_CString upTickRuleUnappliedCoveredShortSellingTradingVolume(shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingVolume, sizeof ( shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingVolume ));
    ACE_CString upTickRuleUnappliedCoveredShortSellingTradingValue(shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingValue, sizeof ( shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingValue ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tshortSellingDebtSecuritiesAskTradingVolume:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), shortSellingDebtSecuritiesAskTradingVolume.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tshortSellingDebtSecuritiesAskTradingValue:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), shortSellingDebtSecuritiesAskTradingValue.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleAppliedCoveredShortSellingTradingVolume:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleAppliedCoveredShortSellingTradingVolume.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleAppliedCoveredShortSellingTradingValue:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleAppliedCoveredShortSellingTradingValue.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleUnappliedCoveredShortSellingTradingVolume:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleUnappliedCoveredShortSellingTradingVolume.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleUnappliedCoveredShortSellingTradingValue:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleUnappliedCoveredShortSellingTradingValue.c_str() ));

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        return ( 0 );
    }

    // 코스콤 공매도 전문에는 발생일시 정보가 없으므로 전문수신시간을 발생일시로 처리한다.
    ShortSellingInfo recShortSelling;
    ::memset(&recShortSelling, 0, sizeof(ShortSellingInfo));
    ::memcpy(&recShortSelling.symbol, issueCode.c_str(), sizeof ( recShortSelling.symbol ));
    recShortSelling.registerTime = (int) ( time(0) );

    recShortSelling.shortSellingDebtSecuritiesAskTradingVolume = ::atof(shortSellingDebtSecuritiesAskTradingVolume.c_str());
    recShortSelling.shortSellingDebtSecuritiesAskTradingAmount = ::atof(shortSellingDebtSecuritiesAskTradingValue.c_str());

    recShortSelling.upTickRuleAppliedCoveredShortSellingTradingVolume = ::atof(upTickRuleAppliedCoveredShortSellingTradingVolume.c_str());
    recShortSelling.upTickRuleAppliedCoveredShortSellingTradingAmount = ::atof(upTickRuleAppliedCoveredShortSellingTradingValue.c_str());

    recShortSelling.upTickRuleUnappliedCoveredShortSellingTradingVolume = ::atof(upTickRuleUnappliedCoveredShortSellingTradingVolume.c_str());
    recShortSelling.upTickRuleUnappliedCoveredShortSellingTradingAmount = ::atof(upTickRuleUnappliedCoveredShortSellingTradingValue.c_str());

    char buf[SHORT_SELLING_INFO_SIZE];
    ::memset(&buf, 0, SHORT_SELLING_INFO_SIZE);
    ::memcpy(&buf, &recShortSelling, SHORT_SELLING_INFO_SIZE);


#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, SHORT_SELLING_INFO_SIZE), PACKET_SHORT_SELLING_INFO, EXCHANGE_KOSDAQ);
#endif

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , result ));
    printPacketShortSellingInfo(recShortSelling);
    return ( result );
}

int InternetKosdaqChannelProcessor::handleQuantityAllocation(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_QUANTITY_ALLOCATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_QUANTITY_ALLOCATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_QUANTITY_ALLOCATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKosdaqQuantityAllocation allocationRec;
    ACE_OS::memcpy(&allocationRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(allocationRec.dataCategory, sizeof ( allocationRec.dataCategory ));
    ACE_CString issueCode(allocationRec.issueCode, sizeof ( allocationRec.issueCode ));
    ACE_CString serialNo(allocationRec.serialNo, sizeof ( allocationRec.serialNo ));
    ACE_CString boardID(allocationRec.boardID, sizeof ( allocationRec.boardID ));
    ACE_CString allocationStartEnd(allocationRec.allocationStartEnd, sizeof ( allocationRec.allocationStartEnd ));
    ACE_CString allocationTypeCode(allocationRec.allocationTypeCode, sizeof ( allocationRec.allocationTypeCode ));
    ACE_CString timeForAllocationEnd(allocationRec.timeForAllocationEnd, sizeof ( allocationRec.timeForAllocationEnd ));


    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] serialNo:[%s]\n" , getCurrentTimestamp().c_str() , serialNo.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] boardID:[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] allocationStartEnd:[%s]\n" , getCurrentTimestamp().c_str() , allocationStartEnd.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] allocationTypeCode:[%s]\n" , getCurrentTimestamp().c_str() , allocationTypeCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleQuantityAllocation] timeForAllocationEnd:[%s]\n" , getCurrentTimestamp().c_str() , timeForAllocationEnd.c_str() ));

    int result = 0;
    return result;
}

int InternetKosdaqChannelProcessor::handleETF_PDF(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleETF_PDF] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , 
			getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKosdaqETF_PDF pdfRec;
    ACE_OS::memcpy(&pdfRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(pdfRec.dataCategory, sizeof ( pdfRec.dataCategory ));
    ACE_CString etfCode(pdfRec.etfCode, sizeof ( pdfRec.etfCode ));
    ACE_CString dataSeqNumber(pdfRec.dataSeqNumber, sizeof ( pdfRec.dataSeqNumber ));
    ACE_CString date(pdfRec.date, sizeof ( pdfRec.date ));
    ACE_CString transferAgentNumber(pdfRec.transferAgentNumber, sizeof ( pdfRec.transferAgentNumber ));
    ACE_CString compositionIssueNumber(pdfRec.compositionIssueNumber, sizeof ( pdfRec.compositionIssueNumber ));
    ACE_CString compositionIssueCode(pdfRec.compositionIssueCode, sizeof ( pdfRec.compositionIssueCode ));
    ACE_CString oneCUUnitShare(pdfRec.oneCUUnitShare, sizeof ( pdfRec.oneCUUnitShare ));
    ACE_CString compositionIssueMarketType(pdfRec.compositionIssueMarketType, sizeof ( pdfRec.compositionIssueMarketType ));
    ACE_CString compositionIssueName(pdfRec.compositionIssueName, sizeof ( pdfRec.compositionIssueName ));

    ACE_CString parValueAmount(pdfRec.parValueAmount, sizeof ( pdfRec.parValueAmount ));
    ACE_CString profitDistributionBasisDate(pdfRec.profitDistributionBasisDate, sizeof ( pdfRec.profitDistributionBasisDate ));
    ACE_CString appraisedValue(pdfRec.appraisedValue, sizeof ( pdfRec.appraisedValue ));

    int result = 0;
    return result;
}

int InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_KOSDAQ_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_KOSDAQ_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_KOSDAQ_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKosdaqKOSDAQVolatilityInterruptionPerInstrument rawVIRec;
    ACE_OS::memcpy(&rawVIRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawVIRec.dataCategory, sizeof ( rawVIRec.dataCategory ));
    ACE_CString issueCode(rawVIRec.issueCode, sizeof ( rawVIRec.issueCode ));
    ACE_CString issueSeqNo(rawVIRec.issueSeqNo, sizeof ( rawVIRec.issueSeqNo ));
    ACE_CString boardID(rawVIRec.boardID, sizeof ( rawVIRec.boardID ));
    ACE_CString tradeExecutionProcessingTime(rawVIRec.tradeExecutionProcessingTime, sizeof ( rawVIRec.tradeExecutionProcessingTime ));
    ACE_CString removalTimeOfVI(rawVIRec.removalTimeOfVI, sizeof ( rawVIRec.removalTimeOfVI ));
    ACE_CString VIApplicationCategoryCode(rawVIRec.VIApplicationCategoryCode, sizeof ( rawVIRec.VIApplicationCategoryCode ));
    ACE_CString VITypeCode(rawVIRec.VITypeCode, sizeof ( rawVIRec.VITypeCode ));
    ACE_CString basePriceToTriggerStaticVI(rawVIRec.basePriceToTriggerStaticVI, sizeof ( rawVIRec.basePriceToTriggerStaticVI ));
    ACE_CString basePriceToTriggerDynamicVI(rawVIRec.basePriceToTriggerDynamicVI, sizeof ( rawVIRec.basePriceToTriggerDynamicVI ));
    ACE_CString VITriggeringPrice(rawVIRec.VITriggeringPrice, sizeof ( rawVIRec.VITriggeringPrice ));
    ACE_CString disparateRatioStaticVI(rawVIRec.disparateRatioStaticVI, sizeof ( rawVIRec.disparateRatioStaticVI ));
    ACE_CString disparateRatioDynamicVI(rawVIRec.disparateRatioDynamicVI, sizeof ( rawVIRec.disparateRatioDynamicVI ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] issueSeqNo:[%s]\n" , getCurrentTimestamp().c_str() , issueSeqNo.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] boardID:[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] tradeExecutionProcessingTime:[%s]\n" , getCurrentTimestamp().c_str() , tradeExecutionProcessingTime.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] removalTimeOfVI:[%s]\n" , getCurrentTimestamp().c_str() , removalTimeOfVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] VIApplicationCategoryCode:[%s]\n" , getCurrentTimestamp().c_str() , VIApplicationCategoryCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] VITypeCode:[%s]\n" , getCurrentTimestamp().c_str() , VITypeCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] basePriceToTriggerStaticVI:[%s]\n" , getCurrentTimestamp().c_str() , basePriceToTriggerStaticVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] basePriceToTriggerDynamicVI:[%s]\n" , getCurrentTimestamp().c_str() , basePriceToTriggerDynamicVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] VITriggeringPrice:[%s]\n" , getCurrentTimestamp().c_str() , VITriggeringPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] disparateRatioStaticVI:[%s]\n" , getCurrentTimestamp().c_str() , disparateRatioStaticVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQVolatilityInterruptionPerInstrument] disparateRatioDynamicVI:[%s]\n" , getCurrentTimestamp().c_str() , disparateRatioDynamicVI.c_str() ));

    VolatilityInterruptionPerInstrument2 viRec;
    ::memset(&viRec, 0, sizeof(VolatilityInterruptionPerInstrument));

    ::memcpy(& ( viRec.symbol ), issueCode.c_str(), issueCode.length());
    viRec.registerDt = (int) ( ::time(0) );
    ::memcpy(& ( viRec.boardID ), boardID.c_str(), issueCode.length());

    // KOSCOM 전문은 ms 까지 있지만, 체결전문은 초단위고, TRADE_REAL 도 초단위 이므로, ms 는 절삭한다.
    ACE_CString tradeExecutionProcessingTimeSec(rawVIRec.tradeExecutionProcessingTime, 6);
    viRec.tradeExecutionProcessingTime = getTickTime(tradeExecutionProcessingTimeSec, dataCategory);
    ACE_CString removalTimeOfVISec(rawVIRec.removalTimeOfVI, 6);
    viRec.removalTimeOfVI = getTickTime(removalTimeOfVISec, dataCategory);
    ::memcpy(& ( viRec.VIApplicationCategoryCode ), VIApplicationCategoryCode.c_str(), VIApplicationCategoryCode.length());

    viRec.VITypeCode = parseInt(VITypeCode, 0);
    viRec.basePriceToTriggerStaticVI = parseInt(basePriceToTriggerStaticVI, 0);
    viRec.basePriceToTriggerDynamicVI = parseInt(basePriceToTriggerDynamicVI, 0);
    viRec.VITriggeringPrice = parseInt(VITriggeringPrice, 0);

    viRec.disparateRatioStaticVI = parseDouble(disparateRatioStaticVI, 0.0);
    viRec.disparateRatioDynamicVI = parseDouble(disparateRatioDynamicVI, 0.0);

    printPacketVolatilityInterruptionPerInstrument2(viRec);

    char buf[VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE];
    ::memset(&buf, 0, VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE);
    ::memcpy(&buf, &viRec, VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE);



#if(1)
	int resultVIRec;

	resultVIRec = sendPacket(ACE_CString(buf, VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE), PACKET_VOLATILITY_INTERRUPTION_PER_INSTRUMENT2, EXCHANGE_KOSDAQ);
#endif

    return resultVIRec;
}

int InternetKosdaqChannelProcessor::handleKoscomLineLKInfo(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSDAQ_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleKoscomLineLKInfo] Skip : %s,%d : EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSDAQ_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSDAQ_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    ExturePlusKoscomLineLKInfo_KOSDAQ rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKoscomLineLKInfo_KOSDAQ));
    ::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_INET_Addr addrLocalhost;
    ACE_CString hostname(addrLocalhost.get_host_name());
    ACE_CString recvAddr(rawRec.recvAddr, sizeof ( rawRec.recvAddr ));
    ACE_CString lkMsgRaw(packet.c_str(), 9);

    KoscomLineLKInfo lkRec;
    ::memset(&lkRec, 0, sizeof(KoscomLineLKInfo));
    ::memcpy(& ( lkRec.hostname_ ), hostname.c_str(), hostname.length());
    ::memcpy(& ( lkRec.addrInfo_ ), recvAddr.c_str(), recvAddr.length());
    lkRec.commType_ = COMM_TYPE_TCP;
    lkRec.recvTime_ = static_cast<int>(::time(0));
    ::memcpy(& ( lkRec.msgRaw_ ), lkMsgRaw.c_str(), lkMsgRaw.length());

    char bufSendPacket[KOSCOM_LINE_LK_INFO_SIZE];
    ::memset(&bufSendPacket, 0, sizeof ( bufSendPacket ));
    ::memcpy(&bufSendPacket, &lkRec, sizeof(KoscomLineLKInfo));

#if(1)
	int result = 0;
	result = sendPacket(ACE_CString(bufSendPacket, KOSCOM_LINE_LK_INFO_SIZE), PACKET_KOSCOM_LINE_LK_INFO, EXCHANGE_KOSDAQ);
#endif

    //   ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKoscomLineLKInfo] result:[%d]\thostname:[%s]\trecvAddr:[%s]\tcommType:[%d]\trecvTime:[%d]\tlkMsgRaw:[%s]\n" , getCurrentTimestamp().c_str() , result , ACE_CString(lkRec.hostname_, sizeof ( lkRec.hostname_ )).c_str() , ACE_CString(lkRec.addrInfo_, sizeof ( lkRec.addrInfo_ )).c_str() , lkRec.commType_ , lkRec.recvTime_ , ACE_CString(lkRec.msgRaw_, sizeof ( lkRec.msgRaw_ )).c_str() ));
    return result;
}

int InternetKosdaqChannelProcessor::handleKOSDAQIssueEventInformation(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQIssueEventInformation] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKosdaqKOSDAQIssueEventInformation rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString eventTypeCode(rawRec.eventTypeCode, sizeof ( rawRec.eventTypeCode ));
    ACE_CString eventOccurrenceCauseCode(rawRec.eventOccurrenceCauseCode, sizeof ( rawRec.eventOccurrenceCauseCode ));
    ACE_CString startDate(rawRec.startDate, sizeof ( rawRec.startDate ));
    ACE_CString expirationDate(rawRec.expirationDate, sizeof ( rawRec.expirationDate ));

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleKOSDAQIssueEventInformation] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        return 0;
    }

    KOSPI_KOSDAQ_IssueEventInformation infoRec;
    ::memset(&infoRec, 0, sizeof(KOSPI_KOSDAQ_IssueEventInformation));

    ::memcpy(&infoRec.symbol, issueCode.c_str(), issueCode.length());
    infoRec.registerDt = (int) ( ::time(0) );
    ::memcpy(&infoRec.eventTypeCode, eventTypeCode.c_str(), eventTypeCode.length());
    ::memcpy(&infoRec.eventOccurrenceCauseCode, eventOccurrenceCauseCode.c_str(), eventOccurrenceCauseCode.length());
    ::memcpy(&infoRec.startDate, startDate.c_str(), startDate.length());
    ::memcpy(&infoRec.expirationDate, expirationDate.c_str(), expirationDate.length());

    printPacketKOSPI_KOSDAQ_IssueEventInformation(infoRec);

    char buf[KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE];
    ::memset(&buf, 0, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);
    ::memcpy(&buf, &infoRec, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE);

#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE), PACKET_KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION, EXCHANGE_KOSDAQ);
#endif

    return result;
}

int InternetKosdaqChannelProcessor::handleDeterminedBasePrice(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_KOSDAQ_DETERMINED_BASE_PRICE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_KOSDAQ_DETERMINED_BASE_PRICE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_KOSDAQ_DETERMINED_BASE_PRICE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);
    /*
     * 규정에는 위와같이 표현되어 있으며 공통점은 상하한가가 없는 종목들임
     ※ 중복데이터 : 중복처리 무방
     */
    ExturePlusKosdaqKOSDAQDeterminedBasePrice rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString boardID(rawRec.boardID, sizeof ( rawRec.boardID ));
    ACE_CString basisPrice(rawRec.basisPrice, sizeof ( rawRec.basisPrice ));
    ACE_CString upperLimitPriceOfBasisPrice(rawRec.upperLimitPriceOfBasisPrice, sizeof ( rawRec.upperLimitPriceOfBasisPrice ));
    ACE_CString lowerLimitPriceOfBasisPrice(rawRec.lowerLimitPriceOfBasisPrice, sizeof ( rawRec.lowerLimitPriceOfBasisPrice ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] boardID:[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] basisPrice:[%s]\n" , getCurrentTimestamp().c_str() , basisPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] upperLimitPriceOfBasisPrice:[%s]\n" , getCurrentTimestamp().c_str() , upperLimitPriceOfBasisPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleDeterminedBasePrice] lowerLimitPriceOfBasisPrice:[%s]\n" , getCurrentTimestamp().c_str() , lowerLimitPriceOfBasisPrice.c_str() ));

    DeterminedBasisPrice priceRec;
    ::memset(&priceRec, 0, sizeof(DeterminedBasisPrice));

    ::memcpy(&priceRec.symbol, issueCode.c_str(), issueCode.length());
    priceRec.registerDt = (int) ( ::time(0) );
    ::memcpy(&priceRec.boardId, boardID.c_str(), boardID.length());
    priceRec.stdPrice = ::atoi(basisPrice.c_str());
    priceRec.upperLimitPrice = ::atoi(upperLimitPriceOfBasisPrice.c_str());
    priceRec.lowerLimitPrice = ::atoi(lowerLimitPriceOfBasisPrice.c_str());

    printPacketDeterminedBasisPrice(priceRec);

    char buf[DETERMINED_BASIC_PRICE_SIZE];
    ::memset(&buf, 0, DETERMINED_BASIC_PRICE_SIZE);
    ::memcpy(&buf, &priceRec, DETERMINED_BASIC_PRICE_SIZE);


#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, DETERMINED_BASIC_PRICE_SIZE), PACKET_DETERMINED_BASIS_PRICE, EXCHANGE_KOSDAQ);
#endif

    return ( result );
}

int InternetKosdaqChannelProcessor::handleIssueInformationDisclosure(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_ISSUE_INFORMATION_DISCLOSURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_ISSUE_INFORMATION_DISCLOSURE_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_ISSUE_INFORMATION_DISCLOSURE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKosdaqIssueInformationDisclosure rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString data_category(rawRec.data_category, sizeof ( rawRec.data_category ));
    ACE_CString issue_code(rawRec.issue_code, sizeof ( rawRec.issue_code ));
    ACE_CString issue_seq_no(rawRec.issue_seq_no, sizeof ( rawRec.issue_seq_no ));
    ACE_CString disclosure_data_type_code(rawRec.disclosure_data_type_code, sizeof ( rawRec.disclosure_data_type_code ));
    ACE_CString board_id(rawRec.board_id, sizeof ( rawRec.board_id ));
    ACE_CString basis_price(rawRec.basis_price, sizeof ( rawRec.basis_price ));
    ACE_CString upper_limit_price(rawRec.upper_limit_price, sizeof ( rawRec.upper_limit_price ));
    ACE_CString lower_limit_price(rawRec.lower_limit_price, sizeof ( rawRec.lower_limit_price ));
    ACE_CString evaluation_price(rawRec.evaluation_price, sizeof ( rawRec.evaluation_price ));
    ACE_CString highest_order_price(rawRec.highest_order_price, sizeof ( rawRec.highest_order_price ));
    ACE_CString lowest_order_price(rawRec.lowest_order_price, sizeof ( rawRec.lowest_order_price ));
    ACE_CString opening_price_becomes_basis_price_type(rawRec.opening_price_becomes_basis_price_type, sizeof ( rawRec.opening_price_becomes_basis_price_type ));
    ACE_CString back_door_listing(rawRec.back_door_listing, sizeof ( rawRec.back_door_listing ));
    ACE_CString par_value_change_type_code(rawRec.par_value_change_type_code, sizeof ( rawRec.par_value_change_type_code ));
    ACE_CString lot_size(rawRec.lot_size, sizeof ( rawRec.lot_size ));
    ACE_CString number_of_listed_stocks(rawRec.number_of_listed_stocks, sizeof ( rawRec.number_of_listed_stocks ));
    ACE_CString designation(rawRec.designation, sizeof ( rawRec.designation ));
    ACE_CString closing_price_possibility_in_pre_off_hours_session(rawRec.closing_price_possibility_in_pre_off_hours_session, sizeof ( rawRec.closing_price_possibility_in_pre_off_hours_session ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] issue_seq_no:[%s]\n" , getCurrentTimestamp().c_str() , issue_seq_no.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] disclosure_data_type_code:[%s]\n" , getCurrentTimestamp().c_str() , disclosure_data_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] board_id:[%s]\n" , getCurrentTimestamp().c_str() , board_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] basis_price:[%s]\n" , getCurrentTimestamp().c_str() , basis_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , upper_limit_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , lower_limit_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] evaluation_price:[%s]\n" , getCurrentTimestamp().c_str() , evaluation_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] highest_order_price:[%s]\n" , getCurrentTimestamp().c_str() , highest_order_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] lowest_order_price:[%s]\n" , getCurrentTimestamp().c_str() , lowest_order_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] opening_price_becomes_basis_price_type:[%s]\n" , getCurrentTimestamp().c_str() , opening_price_becomes_basis_price_type.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] back_door_listing:[%s]\n" , getCurrentTimestamp().c_str() , back_door_listing.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] par_value_change_type_code:[%s]\n" , getCurrentTimestamp().c_str() , par_value_change_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] lot_size:[%s]\n" , getCurrentTimestamp().c_str() , lot_size.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] number_of_listed_stocks:[%s]\n" , getCurrentTimestamp().c_str() , number_of_listed_stocks.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] designation:[%s]\n" , getCurrentTimestamp().c_str() , designation.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleIssueInformationDisclosure] closing_price_possibility_in_pre_off_hours_session:[%s]\n" , getCurrentTimestamp().c_str() , closing_price_possibility_in_pre_off_hours_session.c_str() ));

    int result = 0;
    return ( result );
}

ACE_CString InternetKosdaqChannelProcessor::getIndexSymbol(int code, const ACE_CString &frameId)
{
    int index = code; // default
    char buf[13];
    ::memset(buf, 0, sizeof ( buf ));

    if ( frameId == "E5" )
    {
        index = TICKERPLANT_BASECODE_KOSDAQ + index;  // 501
        sprintf(buf, "KRY%03d000000", index);
    }
    else
    {
        if ( frameId == "E4" )
        {
            index = TICKERPLANT_BASECODE_KOSDAQ + index; //TICKERPLANT_BASECODE_KOSDAQ = 500
        }
        if ( frameId == "E6" )
        {
            if ( index == 1 )
            {
                index = TICKERPLANT_BASECODE_KOSDAQ50; //750 ( 사용하지 않음으로 예상 )
            }
            else if ( index == 2 )
            {
                index = TICKERPLANT_BASECODE_KOSDAQIT50; //800 ( 사용하지 않음으로 예상 )
            }
            else if ( index == 201 )
            {
                index = TICKERPLANT_BASECODE_KOSTAR; //810
            }
        }
        sprintf(buf, "KRI%03d000000", index);
    }
    ACE_CString symbol = ACE_CString(buf);
    return symbol;
}

BYTE InternetKosdaqChannelProcessor::getMarketInTrade(const ACE_CString& raw)
{
    BYTE result = MARKET_IN;
    if ( raw == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( raw == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getMarketStepInIndex(const ACE_CString& time)
{
    BYTE result = MARKET_IN;
    if ( ( time == "JUNJJJ" ) || ( time == "EXTJJJ" ) )
    {
        result = MARKET_END;
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getUpDownInTrade(const ACE_CString& raw)
{
    BYTE result = UPDOWN_STATIONARY;
    if ( raw == "1" )
    {
        result = UPDOWN_UP_LIMIT;
    }
    else if ( raw == "2" )
    {
        result = UPDOWN_UP;
    }
    else if ( raw == "4" )
    {
        result = UPDOWN_DOWN_LIMIT;
    }
    else if ( raw == "5" )
    {
        result = UPDOWN_DOWN;
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getUpDownInIndex(const ACE_CString& raw)
{
    BYTE result;
    if ( raw == "+" )
    {
        result = UPDOWN_UP;
    }
    else if ( raw == "-" )
    {
        result = UPDOWN_DOWN;
    }
    else
    {
        result = UPDOWN_STATIONARY;
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID)
{
    BYTE result = MARKET_IN;

    if ( boardID == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( boardID == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    else if ( boardID == "G4" )
    {
        result = MARKET_END;
    }
    else
    {
        result = MARKET_IN;
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getMarketInRecoveryTrade(const ACE_CString& frameId, const ACE_CString& boardID, const ACE_CString& boardEventID)
{
    BYTE result = MARKET_IN;

    if ( boardID == "G2" )
    {
        result = MARKET_BEFORE_TRADE;
    }
    else if ( boardID == "G3" )
    {
        result = MARKET_AFTER_TRADE;
    }
    else if ( boardID == "G4" )
    {
        result = MARKET_END;
    }
    else
    {
        result = MARKET_IN;
    }
    return ( result );
}

BYTE InternetKosdaqChannelProcessor::getMarketInRecoveryTradeFixed(const ACE_CString& market)
{
    BYTE result = MARKET_IN;
    if ( market == "1" )
    {
        result = MARKET_END;
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = MARKET_IN;
    if ( ( boardID == "G3" ) || ( sessionID == "65" ) || ( sessionID == "60" ) )
    {
        result = MARKET_AFTER_TRADE;
    }
    else
    {
        result = MARKET_IN;
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getManagementType(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "N" )
    {
        result = MASTER_MANAGEMENT_VALUE_NORMAL;
    }
    else
    {
        result = MASTER_MANAGEMENT_VALUE_MAN;
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getSuspensionType(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "N" )
    {
        result = MASTER_SUSPENSION_VALUE_NORMAL;
    }
    else
    {
        result = MASTER_SUSPENSION_VALUE_SUSPENDED;
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getVenture(const ACE_CString& raw)
{
    ACE_CString result("일반기업");
    if ( raw == "1" )
    {
        result = "우량기업부";
    }
    else if ( raw == "2" )
    {
        result = "벤처기업부";
    }
    else if ( raw == "3" )
    {
        result = "중견기업부";
    }
    else if ( raw == "4" )
    {
        result = "신성장기업부";
    }
    else if ( raw == "A" )
    {
        result = "외국기업";
    }
    else if ( raw == "B" )
    {
        result = "투자회사";
    }
    else if ( raw == "C" )
    {
        result = "SPAC";
    }
    else if ( raw == "D" )
    {
        result = "ETF";
    }
    else if ( raw == "E" )
    {
        result = "관리종목";
    }
    else if ( raw == "F" )
    {
        result = "투자주의환기종목";
    }
    else if ( raw == "Z" )
    {
        result = "기타";
    }
    else
    {
        result = "일반기업";
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getEx(const ACE_CString& rawEx)
{
    ACE_CString result = "정상";
    if ( rawEx == "01" )
    {
        result = "권리락";
    }
    else if ( rawEx == "02" )
    {
        result = "배당락";
    }
    else if ( rawEx == "03" )
    {
        result = "분배락";
    }
    else if ( rawEx == "04" )
    {
        result = "권배락";
    }
    else if ( rawEx == "05" )
    {
        result = "중간배당락";
    }
    else if ( rawEx == "06" )
    {
        result = "권리중간배당락";
    }
    else if ( rawEx == "99" )
    {
        result = "기타";
    }
    else
    {
        result = "정상";
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getSplitMerge(const ACE_CString& rawEx)
{
    ACE_CString result = "정상";
    if ( rawEx == "01" )
    {
        result = "액면분할";
    }
    else if ( rawEx == "02" )
    {
        result = "액면병합";
    }
    else if ( rawEx == "03" )
    {
        result = "기타";
    }
    else
    {
        result = "정상";
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getCapitalReduction(const ACE_CString& rawEx)
{
    ACE_CString result = "정상";
    if ( rawEx == "6" )
    {
        result = "감자";
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getTotalMarketPriceType(const ACE_CString& raw)
{
    ACE_CString result("제외");
    if ( raw == "1" )
    {
        result = "대형";
    }
    else if ( raw == "2" )
    {
        result = "중형";
    }
    else if ( raw == "3" )
    {
        result = "소형";
    }
    else
    {
        result = "제외";
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getKogiType(const ACE_CString& raw)
{
    ACE_CString result("일반");
    if ( raw == "Y" )
    {
        result = "우량";
    }
    else
    {
        result = "일반";
    }
    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getCautionType(const ACE_CString& rawAlarm)
{
    ACE_CString result(MASTER_CAUTION_TYPE_VALUE_NORMAL);
    if ( rawAlarm == "01" )
    {
        result = "투자주의";
    }
    else if ( rawAlarm == "02" )
    {
        result = "투자경고";
    }
    else if ( rawAlarm == "03" )
    {
        result = "투자위험";
    }
    else
    {
        result = MASTER_CAUTION_TYPE_VALUE_NORMAL;
    }
    return result;
}

int InternetKosdaqChannelProcessor::getTickTime(const ACE_CString &timeStr, const ACE_CString &frameId)
{
    int hour = 0;
    int minute = 0;
    int second = 0;

    if ( timeStr.substr(3, 3) == "JJJ" )
    {
        // 장전 예상지수인 경우 09:00 을 끝으로 한다. by dong in 2008.02.01
        if ( frameId == "E5" )
        {
            hour = 9;
        }
        else
        {
            hour = 18;
        }
        minute = 0;
        second = 0;
    }
    else
    {
        hour = atoi(timeStr.substr(0, 2).c_str());
        minute = atoi(timeStr.substr(2, 2).c_str());
        second = atoi(timeStr.substr(4, 2).c_str());
    }
    int currentTime = ::time(0);
    int timezone = -9 * 3600;
    int dayBaseTime = ( currentTime - timezone ) - ( ( currentTime - timezone ) % ( 3600 * 24 ) ) + timezone;
    int tickTime = dayBaseTime + hour * 3600 + minute * 60 + second;
    return tickTime;
}

ACE_CString InternetKosdaqChannelProcessor::getIndustryClassCode(const ACE_CString& industryClassMid, const ACE_CString& industryClassSmall)
{
    ACE_CString code;

    int nindustryClassMid = ACE_OS::atoi(industryClassMid.c_str());
    int nindustryClassSmall = ACE_OS::atoi(industryClassSmall.c_str());

    if ( nindustryClassSmall != 0 )
    {
        std::ostringstream os;
        os << "KRI" << std::setw(3) << std::setfill('0') << nindustryClassSmall + TICKERPLANT_BASECODE_KOSDAQ << "000000";
        code = os.str().c_str();
    }
    else if ( nindustryClassMid != 0 )
    {
        std::ostringstream os;
        os << "KRI" << std::setw(3) << std::setfill('0') << nindustryClassMid + TICKERPLANT_BASECODE_KOSDAQ << "000000";
        code = os.str().c_str();
    }
    return code;
}

int InternetKosdaqChannelProcessor::handleProgramTradeBatch(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_BATCH_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleProgramTradeBatch] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_BATCH_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_BATCH_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // copy raw data
    ExturePlusKosdaqProgramTradeBatch kosdaqProgTrdBatch;
    ACE_OS::memcpy(&kosdaqProgTrdBatch, packet.c_str(), packet.length());

    // last record
    ACE_CString memberNo(kosdaqProgTrdBatch.memberNo, sizeof kosdaqProgTrdBatch.memberNo);
    if ( memberNo == "99999" )
    {
        return 0;
    }

    // set basic info
    ProgramTradeBatch paxProgTrdBatch;

#if(1)
    paxProgTrdBatch.exchange = EXCHANGE_KOSDAQ;
#endif

    //매도
    paxProgTrdBatch.serial = ACE_OS::atoi(ACE_CString(kosdaqProgTrdBatch.serialNo, sizeof ( kosdaqProgTrdBatch.serialNo )).c_str());
    paxProgTrdBatch.registerTime = getTime(ACE_CString(kosdaqProgTrdBatch.tradeDate, sizeof ( kosdaqProgTrdBatch.tradeDate )));

    ACE_OS::memcpy(paxProgTrdBatch.securities, kosdaqProgTrdBatch.memberNo + 2, std::min(sizeof ( paxProgTrdBatch.securities ), sizeof ( kosdaqProgTrdBatch.memberNo ) - 2));

    paxProgTrdBatch.commitType = getCommitType(ACE_CString(kosdaqProgTrdBatch.consignmentFloorTradingClassCode, sizeof ( kosdaqProgTrdBatch.consignmentFloorTradingClassCode )));

    paxProgTrdBatch.stockType = 1; //매도 
    paxProgTrdBatch.stockVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.stockAskVolume, sizeof ( kosdaqProgTrdBatch.stockAskVolume )).c_str());
    paxProgTrdBatch.stockAmounte = ::atof(ACE_CString(kosdaqProgTrdBatch.stockAskAmount, sizeof ( kosdaqProgTrdBatch.stockAskAmount )).c_str());
    paxProgTrdBatch.futureVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.futureAskVolume, sizeof ( kosdaqProgTrdBatch.futureAskVolume )).c_str());
    paxProgTrdBatch.futuAmount = ::atof(ACE_CString(kosdaqProgTrdBatch.futureAskAmount, sizeof ( kosdaqProgTrdBatch.futureAskAmount )).c_str());

    paxProgTrdBatch.nearSymbolType = getNearSymbolType(ACE_CString(kosdaqProgTrdBatch.ptFirstMonthClassCode, sizeof ( kosdaqProgTrdBatch.ptFirstMonthClassCode )).c_str());
    paxProgTrdBatch.callOptionVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.callAskVolume, sizeof ( kosdaqProgTrdBatch.callAskVolume )).c_str());
    paxProgTrdBatch.callOptionAmount = ::atof(ACE_CString(kosdaqProgTrdBatch.callAskAmount, sizeof ( kosdaqProgTrdBatch.callAskAmount )).c_str());
    paxProgTrdBatch.putOptionVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.putAskVolume, sizeof ( kosdaqProgTrdBatch.putAskVolume )).c_str());
    paxProgTrdBatch.putOptionAmount = ::atof(ACE_CString(kosdaqProgTrdBatch.putAskAmount, sizeof ( kosdaqProgTrdBatch.putAskAmount )).c_str());

#if(1)

	sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdBatch), sizeof(ProgramTradeBatch)), PACKET_PROGRAM_BATCH, EXCHANGE_KOSDAQ);
#endif

    //매수
    paxProgTrdBatch.stockType = 2; //매수 
    paxProgTrdBatch.stockVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.stockBidVolume, sizeof ( kosdaqProgTrdBatch.stockBidVolume )).c_str());
    paxProgTrdBatch.stockAmounte = ::atof(ACE_CString(kosdaqProgTrdBatch.stockBidAmount, sizeof ( kosdaqProgTrdBatch.stockBidAmount )).c_str());
    paxProgTrdBatch.futureVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.futureBidVolume, sizeof ( kosdaqProgTrdBatch.futureBidVolume )).c_str());
    paxProgTrdBatch.futuAmount = ::atof(ACE_CString(kosdaqProgTrdBatch.futureBidAmount, sizeof ( kosdaqProgTrdBatch.futureBidAmount )).c_str());

    paxProgTrdBatch.callOptionVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.callBidVolume, sizeof ( kosdaqProgTrdBatch.callBidVolume )).c_str());
    paxProgTrdBatch.callOptionAmount = ::atof(ACE_CString(kosdaqProgTrdBatch.callBidAmount, sizeof ( kosdaqProgTrdBatch.callBidAmount )).c_str());
    paxProgTrdBatch.putOptionVolume = ::atof(ACE_CString(kosdaqProgTrdBatch.putBidVolume, sizeof ( kosdaqProgTrdBatch.putBidVolume )).c_str());
    paxProgTrdBatch.putOptionAmount = ::atof(ACE_CString(kosdaqProgTrdBatch.putBidAmount, sizeof ( kosdaqProgTrdBatch.putBidAmount )).c_str());




#if(1)
	sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdBatch), sizeof(ProgramTradeBatch)), PACKET_PROGRAM_BATCH, EXCHANGE_KOSDAQ);
#endif

#if(0)
printPacketProgramTradeBatch(paxProgTrdBatch);
#endif

    return 0;
}

int InternetKosdaqChannelProcessor::handlePublicNews(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handlePublicNews] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKosdaqPublicNews kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), packet.length());


#if(1)
	int result = 0;

	result = sendPacket(packet, PACKET_PUBLIC_NEWS, EXCHANGE_KOSDAQ);
#endif
#if(0)
	int result = 0;
	result = sendPacket(packet, PACKET_PUBLIC_NEWS, EXCHANGE_KOSDAQ);
#endif

    return result;
}

ACE_CString InternetKosdaqChannelProcessor::getEpsSign(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "-" )
    {
        result = "-";
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getSubType(const ACE_CString& frameId, const ACE_CString& quotation)
{
    BYTE subtype;
    if ( ( frameId == "B1" ) || ( frameId == "B3" ) )
    {
        subtype = TRADESUBTYPE_CLOSE;
    }
    else if ( quotation == "2" )
    {
        subtype = TRADESUBTYPE_QUOTATION;
    }
    else
    {
        subtype = TRADESUBTYPE_RECOVERY;
    }
    return subtype;
}

BYTE InternetKosdaqChannelProcessor::getMarketStatusInMarket(const ACE_CString& raw)
{
    BYTE result = 0;
    if ( raw == "10" )
    {
        result = 6;
    }
    else if ( raw == "11" )
    {
        result = 7;
    }
    else if ( raw == "12" )
    {
        result = 11;
    }
    else if ( raw == "13" )
    {
        result = 2;
    }
    return result;
}

const std::vector<ACE_CString>& InternetKosdaqChannelProcessor::getTradeTypeList()
{
    return tradeTypeList_;
}

void InternetKosdaqChannelProcessor::initTradeTypeList()
{
    /*
     * mysql> SELECT DISTINCT BOARD_ID, BOARD_DESC FROM TBFC_KRX_CODE_BOARD_EVENT ORDER BY BOARD_ID ASC;
     +----------+------------------------+
     | BOARD_ID | BOARD_DESC             |
     +----------+------------------------+
     | B1       | 대량정규장             |
     | B2       | 대량장개시전시간외     |
     | B3       | 대량장종료후시간외     |
     | E1       | EFP                    |
     | F1       | FLEX정규장             |
     | F1       | 정규장 FLEX            |
     | G1       | 정규장                 |
     | G2       | 장개시전시간외종가     |
     | G3       | 장종료후시간외종가     |
     | G4       | 장종료후시간외단일가   |
     | G5       | 경매매장개시전시간외   |
     | G7       | 일반Buy-In             |
     | G8       | 당일Buy-In             |
     | I1       | 경쟁대량정규장         |
     | I2       | 경쟁대량장개시전시간외 |
     | K1       | 바스켓정규장           |
     | K2       | 바스켓장개시전시간외   |
     | K3       | 바스켓장종료후시간외   |
     | N1       | 협의대량정규장         |
     | R1       | RFQ                    |
     | S1       | 일반신고매매           |
     | SA       | 국채금융신고매매       |
     | SB       | 정부REPO신고매매       |
     | U2       | 장개시전협의거래       |
     +----------+------------------------+
     24 rows in set (0.00 sec)

     mysql>
     *
     */
    tradeTypeList_.clear();
    tradeTypeList_.push_back("B1");
    tradeTypeList_.push_back("B2");
    tradeTypeList_.push_back("B3");
    tradeTypeList_.push_back("E1");
    tradeTypeList_.push_back("F1");
    tradeTypeList_.push_back("G1");
    tradeTypeList_.push_back("G2");
    tradeTypeList_.push_back("G3");
    tradeTypeList_.push_back("G4");
    tradeTypeList_.push_back("G5");
    tradeTypeList_.push_back("G7");
    tradeTypeList_.push_back("G8");
    tradeTypeList_.push_back("I1");
    tradeTypeList_.push_back("I2");
    tradeTypeList_.push_back("K1");
    tradeTypeList_.push_back("K2");
    tradeTypeList_.push_back("K3");
    tradeTypeList_.push_back("N1");
    tradeTypeList_.push_back("R1");
    tradeTypeList_.push_back("S1");
    tradeTypeList_.push_back("SA");
    tradeTypeList_.push_back("SB");
    tradeTypeList_.push_back("U2");
    tradeTypeList_.push_back("ZZ");
    return;
}

ACE_CString InternetKosdaqChannelProcessor::getTradeUnit(const ACE_CString& raw)
{
    int tradeUnitNum = atoi(raw.c_str());
    if ( tradeUnitNum == 0 )
    {
        tradeUnitNum = 1;
    }
    char tradeUnitChar[6];
    sprintf(tradeUnitChar, "%d", tradeUnitNum);
    ACE_CString result(tradeUnitChar);
    return result;
}

BYTE InternetKosdaqChannelProcessor::getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = CONCURRENT_OFF;
    if ( boardID == "G1" ) //정규시간외구분코드가 1인경우(동시,접속 둘다 가능)
    {
        if ( sessionID == "10" ) //시가단일가는 ~09:00 까지.
        {
            result = CONCURRENT_ON;
        }
        else if ( ( sessionID == "40" ) || ( sessionID == "11" ) ) //시가단일가연장은 9시 이후까지 진행가능하므로.
        {
            result = CONCURRENT_OFF;
        }
        else //그 외의 경우 접속으로 가정
        {
            result = CONCURRENT_OFF;
        }
    }
    else
    {
        result = CONCURRENT_OFF;
    }
    return result;
}

int InternetKosdaqChannelProcessor::handleInvestorStock(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_INVESTOR_STOCK_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock] Skip : %s, %d : EXTURE_PLUS_KOSDAQ_INVESTOR_STOCK_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_INVESTOR_STOCK_SIZE , packet.length() , packet.c_str() ), -1);
    }

    int result = 0;
    try
    {
        // log frame count status   
        LogFrameCount(packet.substr(0, 2).c_str());
        ExturePlusKosdaqInvestorStock raw;
        ACE_OS::memcpy(&raw, packet.c_str(), std::min(sizeof ( raw ), packet.length()));

#if(1)
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]dataClass  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.dataClass),raw.dataClass));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]infoClass  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.infoClass),raw.infoClass));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]marketClass:[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.marketClass),raw.marketClass));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]exchange   :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.exchange),raw.exchange));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]date       :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.date),raw.date));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]symbol     :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.symbol),raw.symbol));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]investor   :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.investor),raw.investor));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]sellVolume :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.sellVolume),raw.sellVolume));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]sellAmount :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.sellAmount),raw.sellAmount));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]buyVolume  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.buyVolume),raw.buyVolume));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock]buyAmount  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.buyAmount),raw.buyAmount));
#endif

        Investor investor;
        investor.subtype = SYMBOL_STOCK;

#if(1)
        investor.exchange = EXCHANGE_KOSDAQ;
#endif

        investor.symbolType = SYMBOL_STOCK;

        ACE_OS::memset(investor.symbol, 0, sizeof ( investor.symbol ));
        ACE_OS::memcpy(&investor.symbol, raw.symbol, std::min(sizeof ( investor.symbol ), sizeof ( raw.symbol )));
        std::string investorCode(raw.investor, raw.investor + sizeof ( raw.investor ));
        ACE_OS::memcpy(&investor.investor, investorCode.c_str(), std::min(sizeof investor.investor, investorCode.length()));

        investor.askVolume = atof(std::string(raw.sellVolume, sizeof raw.sellVolume).c_str());
        investor.askAmount = atof(std::string(raw.sellAmount, sizeof raw.sellAmount).c_str());
        investor.bidVolume = atof(std::string(raw.buyVolume, sizeof raw.buyVolume).c_str());
        investor.bidAmount = atof(std::string(raw.buyAmount, sizeof raw.buyAmount).c_str());

#if(1)
		result = sendPacket(ACE_CString(reinterpret_cast<char*>(&investor), INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KOSDAQ);
#endif

        ACE_CString _investor(raw.investor, sizeof raw.investor);

        ACE_CString stockCode(investor.symbol, sizeof ( investor.symbol ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock] stockCode:[%s]\tinvestorCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , investorCode.c_str() , result ));
    }
    catch ( std::exception& e )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock] error occur e.what[%s])\n" , getCurrentTimestamp().c_str() , e.what() ));
        result = -1;
    }
    catch ( ... )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleInvestorStock] unknown error occur\n" , getCurrentTimestamp().c_str() ));
        result = -1;
    }
    return result;
}

int InternetKosdaqChannelProcessor::handleUpDown(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KOSDAQ_UPDOWN_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKosdaqChannelProcessor::handleUpDown] Skip : %s,%d : EXTURE_PLUS_KOSDAQ_UPDOWN_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSDAQ_UPDOWN_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKosdaqUpDown kosdaq;
    ACE_OS::memcpy(&kosdaq, packet.c_str(), packet.length());

    UpDown upDown;


#if(1)
upDown.exchange = EXCHANGE_KOSDAQ;
#endif

    upDown.symbolType = SYMBOL_STOCK;

    ACE_CString stockCode = getIndexSymbol(501);
    ACE_OS::memcpy(&upDown.symbol, stockCode.c_str(), stockCode.length());

    upDown.totalCount = atoi(ACE_CString(kosdaq.totalStockSize, sizeof kosdaq.totalStockSize).c_str());
    upDown.tradeCount = atoi(ACE_CString(kosdaq.tradeFormationStockSize, sizeof kosdaq.tradeFormationStockSize).c_str());
    upDown.upCount = atoi(ACE_CString(kosdaq.upStockSize, sizeof kosdaq.upStockSize).c_str());
    upDown.upLimitCount = atoi(ACE_CString(kosdaq.upLimitStockSize, sizeof kosdaq.upLimitStockSize).c_str());

    upDown.downCount = atoi(ACE_CString(kosdaq.downStockSize, sizeof kosdaq.downStockSize).c_str());
    upDown.downLimitCount = atoi(ACE_CString(kosdaq.downLimitStockSize, sizeof kosdaq.downLimitStockSize).c_str());
    upDown.stationaryCount = atoi(ACE_CString(kosdaq.sattionaryStockSize, sizeof kosdaq.sattionaryStockSize).c_str());

    upDown.quotationCount = atoi(ACE_CString(kosdaq.quotationStockSize, sizeof kosdaq.quotationStockSize).c_str());
    upDown.quotationUpCount = atoi(ACE_CString(kosdaq.quotationUpStockSize, sizeof kosdaq.quotationUpStockSize).c_str());
    upDown.quotationDownCount = atoi(ACE_CString(kosdaq.quotationDownStockSize, sizeof kosdaq.quotationDownStockSize).c_str());

    // 구스펙 : 총거래량, 총거래대금
    // 신스펙 : X
    // DBWriter ShmWriter 사용하지 않음. 임시값으로 대치한다.
    upDown.accmVolume = 0.0;
    upDown.accmAmount = 0.0;
    upDown.registerDt = getRegisterDt();
    upDown.market = MARKET_IN;

    char buf[UPDOWN_SIZE];
    memcpy(buf, &upDown, UPDOWN_SIZE);

#if(1)
	int result = 0;

	result = sendPacket(ACE_CString(buf, UPDOWN_SIZE), PACKET_UPDOWN, EXCHANGE_KOSDAQ);
#endif

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKosdaqChannelProcessor::handleUpDown] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));
//    printPacketUpDown(upDown);

    return result;
}

int InternetKosdaqChannelProcessor::getRegisterDt()
{
    time_t registerDt = ::time(0);
    struct tm tmRegisterDt = *::localtime(&registerDt);
    registerDt = ::mktime(&tmRegisterDt);
    return registerDt;
}

ACE_CString InternetKosdaqChannelProcessor::getIsDividendIndexStock(const ACE_CString& raw)
{
    ACE_CString result = "00";
    if ( raw == "Y" )
    {
        result = "01"; // 배당지수
    }
    else if ( raw == "N" )
    {
        result = "00"; // X
    }
    return result;
}

BYTE InternetKosdaqChannelProcessor::getCommitType(const ACE_CString& raw)
{
    //위탁
    int commitType = 0;
    if ( raw == "10" )
    {
        commitType = 1;
    }
    //자기 = 상품
    else if ( raw == "30" )
    {
        commitType = 2;
    }
    return commitType;
}

BYTE InternetKosdaqChannelProcessor::getNearSymbolType(const ACE_CString& raw)
{
    BYTE nearSymbolType = 0;
    if ( raw == "1" )
    {
        nearSymbolType = 1;
    }
    else if ( raw == "9" )
    {
        nearSymbolType = 2;
    }
    return nearSymbolType;
}

#if(0)
	ACE_CString indexConstKosdaqMap1[498] = 
	{"KGG01P","KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G01P","K2G01P","K2G02P","K2G03P","K2S11P","K2S11P","K2S02P","K2S02P","K2S08P","K2S08P","K2S09P","K2S09P","K2S05P","K2S05P","K2S07P","K2S07P","K2S03P","K2S03P","K2S10P","K2S10P","K2S06P","K2S06P","K2S04P","K2S04P","K2S01P","K2S01P","K2W01P","K2W01P","K2W02P","K2W02P","K2W03P","K2W03P","XGW01P","XGW01P","XGG01P","XGG01P","X3G01P","X3G01P","XGS01P","XGS01P","XGS02P","XGS02P","XGS03P","XGS03P","XGS04P","XGS04P","XGS05P","XGS05P","XGS06P","XGS06P","XGS07P","XGS07P","XGS08P","XGS08P","XGS09P","XGS09P","XGS10P","XGS10P","XGS11P","XGS11P","XGS12P","XGS12P","XGS13P","XGS13P","XGS14P","XGS14P","XGS15P","XGS15P","XGS16P","XGS16P","XGS17P","XGS17P","X3E01P","X3E01P","XGE05P","XGE05P","QGG01P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS01P","QGS32P","QGS32P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG03P","QGG04P","QGG04P","QGG05P","QGG05P","QGG06P","QGG06P","NGG01P","NGG01P","K2B01P","KGD02P","KGD02P","KGD03P","KGD03P","K2B03P","K2T01P","K2E01P","K2E01P","K2E02P","K2E02P","K2W04P","K2W04P","KGD04P","KGD04P","K2G05P","K2G05P","K2G04P","K2G04P","K2G06P","K2G06P","K2G08P","K2G08P","K2G10P","K2G10P","K2D01P","K2D01P","K2D02P","K2D02P","KGD01P","KGD01P","XGE01P","XGE01P","XGE03P","XGE03P","XGE02P","XGE02P","XGB05P","XGE04P","XGE04P","XGT01P","XGT01P","XGT02P","XGT02P","XGT03P","XGT03P","XGT04P","XGT04P","XGT05P","XGT05P","X3S05P","X3S05P","X3S04P","X3S04P","X3S02P","X3S02P","X3S01P","X3S01P","X3S03P","X3S03P","X3S08P","X3S08P","X3S06P","X3S06P","X3S07P","X3S07P","XGG02P","XGG02P","K2Z01P","Q5G01P","Q5G01P","Q5S05P","Q5S05P","Q5S06P","Q5S06P","Q5S07P","Q5S07P","Q5S08P","Q5S08P","Q5S02P","Q5S02P","Q5S03P","Q5S03P","Q5S04P","Q5S04P","Q5E01P","Q5E01P","Q5W01P","K2G01T","K2G01T","K2G01N","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG01P","TGG02P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","KGG01T","QGG01T","QGG01T","X3G01T","X3G01T","Q5G01T","Q5G01T","KGD02T","KGD02T","KGD03T","KGD03T","K2S07T","K2S07T","K2S03T","K2S03T","K2S06T","K2S06T","K2S05T","K2S05T","K2S10T","K2S10T","K2S02T","K2S02T","K2S08T","K2S08T","K2S09T","K2S09T","K2S04T","K2S04T","K2S01T","K2S01T","K2S11T","K2S11T","K2G06T","K2G06T","K2G06N","K2G06N","K2G08T","K2G08T","K2G08N","K2G08N","K2G10T","K2G10T","K2G10N","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT06T","XGT08T","XGT08T","XGT10T","XGT10T","XGT06P","XGT06P","XGT08P","XGT08P","XGT10P","XGT10P","XGT07P","XGT07P","XGT09P","XGT09P","XGT11P","XGT11P","KGT01P","KGT01P","KGX01P"};
	ACE_CString indexConstKosdaqMap2[498] = 
	{"KRD020020008","KRD020020008","KRD020020081","KRD020020099","KRD020020107","KRD020020115","KRD020020123","KRD020020131","KRD020020149","KRD020020156","KRD020020164","KRD020020172","KRD020020180","KRD020020198","KRD020020206","KRD020020214","KRD020020222","KRD020020230","KRD020020248","KRD020020255","KRD020020263","KRD020020271","KRD020020289","KRD020020297","KRD020020305","KRD020020313","KRD020020321","KRD020020016","KRD020020016","KRD020020024","KRD020020032","KRD020022327","KRD020022327","KRD020020339","KRD020020339","KRD020020347","KRD020020347","KRD020020354","KRD020020354","KRD020020362","KRD020020362","KRD020020370","KRD020020370","KRD020020388","KRD020020388","KRD020020396","KRD020020396","KRD020020404","KRD020020404","KRD020021386","KRD020021386","KRD020021394","KRD020021394","KRD020021048","KRD020021048","KRD020021055","KRD020021055","KRD020021063","KRD020021063","KRD020021071","KRD020021071","KRD020020073","KRD020020073","KRD020022087","KRD020022087","KRD020020842","KRD020020842","KRD020020859","KRD020020859","KRD020020867","KRD020020867","KRD020020875","KRD020020875","KRD020020891","KRD020020891","KRD020020909","KRD020020909","KRD020020925","KRD020020925","KRD020020933","KRD020020933","KRD020020958","KRD020020958","KRD020020966","KRD020020966","KRD020020974","KRD020020974","KRD020020982","KRD020020982","KRD020021741","KRD020021741","KRD020021758","KRD020021758","KRD020021766","KRD020021766","KRD020021774","KRD020021774","KRD020021782","KRD020021782","KRD020029330","KRD020029330","KRD020029348","KRD020029348","KRD020040006","KRD020040006","KRD020020438","KRD020020446","KRD020020453","KRD020020461","KRD020040022","KRD020040022","KRD020020479","KRD020020487","KRD020020495","KRD020020503","KRD020020511","KRD020020529","KRD020020537","KRD020020545","KRD020020552","KRD020020560","KRD020020578","KRD020020586","KRD020020594","KRD020020602","KRD020020610","KRD020020628","KRD020020636","KRD020020644","KRD020020651","KRD020020669","KRD020020677","KRD020020685","KRD020020693","KRD020020701","KRD020020719","KRD020020727","KRD020020735","KRD020020743","KRD020020750","KRD020020768","KRD020020776","KRD020020784","KRD020020792","KRD020020792","KRD020020800","KRD020020800","KRD020020818","KRD020020818","KRD020020826","KRD020020826","KRD020021089","KRD020021089","KRD020020412","KRD020021329","KRD020021329","KRD020021311","KRD020021311","KRD020021352","KRD020021402","KRD020022459","KRD020022459","KRD020029322","KRD020029322","KRD020029280","KRD020029280","KRD020022723","KRD020022723","KRD020022368","KRD020022368","KRD020022806","KRD020022806","KRD020022947","KRD020022947","KRD020022970","KRD020022970","KRD020023028","KRD020023028","KRD020022004","KRD020022004","KRD020022012","KRD020022012","KRD020021345","KRD020021345","KRD020021444","KRD020021444","KRD020021451","KRD020021451","KRD020021469","KRD020021469","KRD020021824","KRD020022061","KRD020022061","KRD020023085","KRD020023085","KRD020023127","KRD020023127","KRD020023119","KRD020023119","KRD020023101","KRD020023101","KRD020023093","KRD020023093","KRD020022228","KRD020022228","KRD020022236","KRD020022236","KRD020022244","KRD020022244","KRD020022251","KRD020022251","KRD020022269","KRD020022269","KRD020022475","KRD020022475","KRD020022483","KRD020022483","KRD020022491","KRD020022491","KRD020021360","KRD020021360","KRD020021410","KRD020021378","KRD020021378","KRD020021642","KRD020021642","KRD020021659","KRD020021659","KRD020021667","KRD020021667","KRD020021675","KRD020021675","KRD020021683","KRD020021683","KRD020021691","KRD020021691","KRD020021709","KRD020021709","KRD020022731","KRD020022731","KRD020021436","KRD020021477","KRD020021477","KRD020021485","KRD020021485","KRD020021113","KRD020021170","KRD020021121","KRD020021188","KRD020021105","KRD020021162","KRD020021303","KRD020021147","KRD020021097","KRD020021154","KRD020021139","KRD020021196","KRD020021204","KRD020021220","KRD020021238","KRD020021246","KRD020021253","KRD020021295","KRD020021261","KRD020021212","KRD020021279","KRD020021287","KRD020023713","KRD020020G06","KRD020020G22","KRD020020G48","KRD020023721","KRD020020G71","KRD020020G97","KRD020020GB1","KRD020023697","KRD020023705","KRD020023242","KRD020023259","KRD020023564","KRD020023572","KRD020023226","KRD020023622","KRD020023630","KRD020024117","KRD020023648","KRD020023218","KRD020023580","KRD020023598","KRD020023606","KRD020023614","KRD020023168","KRD020023176","KRD020023135","KRD020023143","KRD020023150","KRD020024083","KRD020021618","KRD020021626","KRD020021600","KRD020023184","KRD020023671","KRD020023689","KRD020023200","KRD020023531","KRD020023549","KRD020023556","KRD020021840","KRD020023234","KRD020021568","KRD020021576","KRD020021584","KRD020021592","KRD020029306","KRD020029314","KRD020023192","KRD020023267","KRD020023275","KRD020023283","KRD020021790","KRD020021790","KRD020021808","KRD020021808","KRD020021816","KRD020022715","KRD020021832","KRD020021899","KRD020021907","KRD020021972","KRD020021980","KRD020021998","KRD020021915","KRD020021923","KRD020021931","KRD020021949","KRD020021956","KRD020021964","KRD020022046","KRD020022053","KRD020022095","KRD020022707","KRD020022103","KRD020022111","KRD020022129","KRD020022137","KRD020022145","KRD020022277","KRD020022285","KRD020022293","KRD020022301","KRD020022319","KRD020022467","KRD020022509","KRD020022517","KRD020022525","KRD020022533","KRD020022541","KRD020022558","KRD020022566","KRD020022574","KRD020022582","KRD020022590","KRD020024026","KRD020023291","KRD020023309","KRD020024091","KRD020023317","KRD020023325","KRD020023333","KRD020023341","KRD020023358","KRD020023366","KRD020023374","KRD020023382","KRD020023390","KRD020024109","KRD020023408","KRD020023416","KRD020023424","KRD020023432","KRD020023440","KRD020023457","KRD020024034","KRD020023465","KRD020023473","KRD020024042","KRD020023481","KRD020023499","KRD020023507","KRD020024059","KRD020023515","KRD020023523","KRD020022350","KRD020022335","KRD020022343","KRD020022376","KRD020022384","KRD020022384","KRD020022392","KRD020022392","KRD020022418","KRD020022418","KRD020022400","KRD020022400","KRD020022434","KRD020022434","KRD020022442","KRD020022442","KRD020022814","KRD020022814","KRD020022822","KRD020022822","KRD020022830","KRD020022830","KRD020022848","KRD020022848","KRD020022855","KRD020022855","KRD020022863","KRD020022863","KRD020022871","KRD020022871","KRD020022889","KRD020022889","KRD020022897","KRD020022897","KRD020022905","KRD020022905","KRD020022913","KRD020022913","KRD020022954","KRD020022954","KRD020022962","KRD020022962","KRD020022988","KRD020022988","KRD020023002","KRD020023002","KRD020023036","KRD020023036","KRD020023051","KRD020023051","KRD020022608","KRD020022616","KRD020022624","KRD020022632","KRD020022657","KRD020022640","KRD020022665","KRD020022673","KRD020022681","KRD020022699","KRD020022798","KRD020022749","KRD020022756","KRD020022764","KRD020022772","KRD020022780","KRD020023077","KRD020023655","KRD020023663","KRD020024760","KRD020026047","KRD020026054","KRD020029264","KRD020029272","KRD020029249","KRD020029256","KRD020029231","KRD020029298","KRD020029355","KRD020029363","KRD020029371","KRD020029389","KRD020020CV8","KRD020020CW6","KRD020020CX4","KRD020020CN5","KRD020020CN5","KRD020020CP0","KRD020020CP0","KRD020020CQ8","KRD020020CQ8","KRD0200200F2","KRD0200200F2","KRD0200200H8","KRD0200200H8","KRD0200200K2","KRD0200200K2","KRD0200200G0","KRD0200200G0","KRD0200200J4","KRD0200200J4","KRD0200200L0","KRD0200200L0","KRD020020FR9","KRD020020FR9","KRD020020FS7"};
	ACE_CString indexConstKosdaqMap3[498] = 
	{"IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","Z5000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000"};
	ACE_CString indexConstKosdaqMap4[498] = 
	{"D0011","D1011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D2011","D3011","D4011","D4011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N9011","O1011","N9011","O1011","N9011","O1011","N9011","O1011","C8011","C9011","AA011","AB011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E5012","E4012","E5012","E4012","E5012","P9018","R7018","Q8011","S4011","V0011","S6011","V2011","T2011","U1011","BK011","BL011","BK011","BL011","BK011","BL011","BK011","BL011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","Z0011","Z1011","Z0011","Z1011","S7011","V4011","U2011","U5011","U2011","U5011","U2011","U5011","Y0011","Z8011","Z9011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","T7011","T8011","U0011","T9012","U4012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W8012","W9012","U8012","Z2011","Z3011","Z2011","Z3011","O2016","O2016","O3016","O3016","L4016","L4016","R6016","K2011","K9014","K9014","J3034","N0034","N0034","O8011","O8011","O8011","O8011","R0011","P5011","O7011","P8011","P8011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","S9014","S9014","T4014","T4014","T5016","T5016","U6016","U6016","U6016","U6016","U6016","U7016","U7016","U7016","U7016","U7016","U9012","U9012","V7011","V7011","V7011","V7011","V7011","V7011","V7011","V8011","V9011","V9011","W1024","W1024","W1024","W1024","W1024","W0014","X0016","X0016","X0016","X0016","X0016","X0016","X2124","X2124","X2124","X2124","X6019","X7019","X6019","X7019","X9034","BQ034","Y1034","Y2014","Y5034","Y6011","Y7016","Y7016","Y8034","Y8034","Y9011","Y9011","Y9011","Y9011","Z6011","Z7034","AD034","AD034","AE164","AE164","AE164","AE164","AK011","AI011","AN011","AO034","AO034","AP034","AP034","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AS016","AQ034","AR034","AV034","AW011","AX011","AY012","AZ012","BC011","BD011","BA012","BB012","BG011","BH011","BI011","BJ011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BO034","BO034","BO034","X0016","X0016","X0016","X0016","Y6011","Y6011","Y6011","Y6011","AI011","AI011","AI011","AI011","AI011","T5016","T1014","T1014","Z5011","Y6011","Y6011","AI011","AI011","AK011","AK011","AN011","V7011","AJ104","AJ104","W1024","W1024","Y6011","Y6011","Y6011","BE011","BF011","BE011","BF011","BE011","BF011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","BK011","BL011","V7011"};
	ACE_CString indexConstKosdaqMap5[498] = 
	{"D0","D1","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D2","D3","D4","D4","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N9","O1","N9","O1","N9","O1","N9","O1","C8","C9","AA","AB","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E4","E5","E4","E4","E4","E4","E4","E5","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E5","E4","E5","E4","E5","E4","E5","P9","R7","Q8","S4","V0","S6","V2","T2","U1","BK","BL","BK","BL","BK","BL","BK","BL","AT","AU","AT","AU","AT","AU","AT","AU","AT","AU","Z0","Z1","Z0","Z1","S7","V4","U2","U5","U2","U5","U2","U5","Y0","Z8","Z9","AG","AH","AG","AH","AG","AH","AG","AH","AG","AH","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","T7","T8","U0","T9","U4","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W8","W9","U8","Z2","Z3","Z2","Z3","O2","O2","O3","O3","L4","L4","R6","K2","K9","K9","J3","N0","N0","O8","O8","O8","O8","R0","P5","O7","P8","P8","J2","J2","J2","J2","J2","J2","J2","J2","S9","S9","T4","T4","T5","T5","U6","U6","U6","U6","U6","U7","U7","U7","U7","U7","U9","U9","V7","V7","V7","V7","V7","V7","V7","V8","V9","V9","W1","W1","W1","W1","W1","W0","X0","X0","X0","X0","X0","X0","X2","X2","X2","X2","X6","X7","X6","X7","X9","BQ","Y1","Y2","Y5","Y6","Y7","Y7","Y8","Y8","Y9","Y9","Y9","Y9","Z6","Z7","AD","AD","AE","AE","AE","AE","AK","AI","AN","AO","AO","AP","AP","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AS","AQ","AR","AV","AW","AX","AY","AZ","BC","BD","BA","BB","BG","BH","BI","BJ","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BO","BO","BO","X0","X0","X0","X0","Y6","Y6","Y6","Y6","AI","AI","AI","AI","AI","T5","T1","T1","Z5","Y6","Y6","AI","AI","AK","AK","AN","V7","AJ","AJ","W1","W1","Y6","Y6","Y6","BE","BF","BE","BF","BE","BF","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","BK","BL","V7"};
#endif
#if(0)
	ACE_CString indexConstKosdaqMap1[TOTALJISUCNT] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","XGD02P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","O2903P","F2X06P","O2X01P","MGA12P","FTX06T","FTX08T","GGS01P","O2904P","F3G01P","F3X01T","F3X02P","F3X03T","X3X01P","MGA13T","F2V02P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03T","FGA04T","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05T","F5901P","F5X05T","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","TGX01P","G2T01P","F2X40T","F2X41T","F5X06T","F5X07T","QGG11P","110043","110046","110043","110004","110007","110012","110014","110020","110021","110023","110037","110038","110039","110040","110041","110042","110044","110045","110049","110051","110052","110053","110056","110057","110058","110059","110060","110061","110062","110065","110066","110067","110068","110069","110070","110071","110072","110073","110074","110077","110078","110079","110080","110081","110082","110083","110084","110086","110087","110088","110089","110090","110091","110092","110093","110094","110095","110096","110097","110098","110099","110100","110101","110102","110103","110104","110105","110106","110107","110108","110109","110110","110111","110112","2P8802","2P8803","2P9259","2P9269","2P9258","2P9284","2P9206","2P9271","2P9234","2P9272","2P9263","2P9256","2P9239","2P9246","2P9247","2P9248","2P9260","2P9255","2P9265","2P9267","2P9266","2P9276","2P9277","2P9278","2P9279","2P9280","2P9281","2P9282","2P9283","2P9231","2P9235","2P9240","2P9275","2P9211","2P9242","2P9243","2P9274","2P9245","2P9262","2P9236","2P9251","2P9238","2P9264","2P9268","2P9229","2P9252","2P9233","2P9253","2P9221","2P9244","2P9222","2P9257","2P9241","2P9273","2P9207","2P9250","2P9237","2P9249","2P9210","2P9232","2P9254","2PB003","2PB101","2PB201","2PB211","2PB221","2PB226","2PB231","2PB232","2PB237","2PB238","2PB239","2PB241","2PB242","2PB243","2PB305","2PB306","2PB307","2PC007","2PC006","2PM128","2PM126","2PM127","2PM119","2PM121","2PM102","2PM104","2PM107","2PM109","2PM112","2PM114","2PM115","2PM116","2PM117","2PM118","2PM122","2PM123","2PM131","2PM124","2PM132","2PM125","2PM120","2PM129","2PM130","2PM134","2PM133","2PM001","2PR001","2PR101","120001","120002","120003","120004","120005","2PW006","120007","120008","120009","120010","120011","120012","120013","120014","120015","120016","120017","120018","120019","120020","120021","120901"};
	ACE_CString indexConstKosdaqMap6[TOTALJISUCNT] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","165","132","133","134","142","136","411","412","413","414","415","351","352","353","354","355","356","357","358","600","167","203","212","213","214","215","216","217","218","331","204","175","176","301","302","303","304","001","002","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","001","001","001","002","002","002","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","707","731","708","821","312","313","003","709","304","306","307","308","305","822","732","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","003","005","286","287","422","423","189","601","602","601","004","007","012","014","020","021","023","037","038","039","040","041","042","044","045","049","051","052","053","056","057","058","059","060","061","062","065","066","067","068","069","070","071","072","073","074","077","078","079","080","081","082","083","084","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","802","803","259","269","258","284","206","271","234","272","263","256","239","246","247","248","260","255","265","267","266","276","277","278","279","280","281","282","283","231","235","240","275","211","242","243","274","245","262","236","251","238","264","268","229","252","233","253","221","244","222","257","241","273","207","250","237","249","210","232","254","003","101","201","211","221","226","231","232","237","238","239","241","242","243","305","306","307","007","006","128","126","127","119","121","102","104","107","109","112","114","115","116","117","118","122","123","131","124","132","125","120","129","130","134","133","001","001","101","001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","901"};
#endif

#define TOTALJISUCNT 379
#define ANOTHERJISUCNT 498

#if(1)
	ACE_CString indexConstKosdaqMap0[ANOTHERJISUCNT] = 
    {"KGG01P","KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G01P","K2G01P","K2G02P","K2G03P","K2S11P","K2S11P","K2S02P","K2S02P","K2S08P","K2S08P","K2S09P","K2S09P","K2S05P","K2S05P","K2S07P","K2S07P","K2S03P","K2S03P","K2S10P","K2S10P","K2S06P","K2S06P","K2S04P","K2S04P","K2S01P","K2S01P","K2W01P","K2W01P","K2W02P","K2W02P","K2W03P","K2W03P","XGW01P","XGW01P","XGG01P","XGG01P","X3G01P","X3G01P","XGS01P","XGS01P","XGS02P","XGS02P","XGS03P","XGS03P","XGS04P","XGS04P","XGS05P","XGS05P","XGS06P","XGS06P","XGS07P","XGS07P","XGS08P","XGS08P","XGS09P","XGS09P","XGS10P","XGS10P","XGS11P","XGS11P","XGS12P","XGS12P","XGS13P","XGS13P","XGS14P","XGS14P","XGS15P","XGS15P","XGS16P","XGS16P","XGS17P","XGS17P","X3E01P","X3E01P","XGE05P","XGE05P","QGG01P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS01P","QGS32P","QGS32P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG03P","QGG04P","QGG04P","QGG05P","QGG05P","QGG06P","QGG06P","NGG01P","NGG01P","K2B01P","KGD02P","KGD02P","KGD03P","KGD03P","K2B03P","K2T01P","K2E01P","K2E01P","K2E02P","K2E02P","K2W04P","K2W04P","KGD04P","KGD04P","K2G05P","K2G05P","K2G04P","K2G04P","K2G06P","K2G06P","K2G08P","K2G08P","K2G10P","K2G10P","K2D01P","K2D01P","K2D02P","K2D02P","KGD01P","KGD01P","XGE01P","XGE01P","XGE03P","XGE03P","XGE02P","XGE02P","XGB05P","XGE04P","XGE04P","XGT01P","XGT01P","XGT02P","XGT02P","XGT03P","XGT03P","XGT04P","XGT04P","XGT05P","XGT05P","X3S05P","X3S05P","X3S04P","X3S04P","X3S02P","X3S02P","X3S01P","X3S01P","X3S03P","X3S03P","X3S08P","X3S08P","X3S06P","X3S06P","X3S07P","X3S07P","XGG02P","XGG02P","K2Z01P","Q5G01P","Q5G01P","Q5S05P","Q5S05P","Q5S06P","Q5S06P","Q5S07P","Q5S07P","Q5S08P","Q5S08P","Q5S02P","Q5S02P","Q5S03P","Q5S03P","Q5S04P","Q5S04P","Q5E01P","Q5E01P","Q5W01P","K2G01T","K2G01T","K2G01N","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG01P","TGG02P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","KGG01T","QGG01T","QGG01T","X3G01T","X3G01T","Q5G01T","Q5G01T","KGD02T","KGD02T","KGD03T","KGD03T","K2S07T","K2S07T","K2S03T","K2S03T","K2S06T","K2S06T","K2S05T","K2S05T","K2S10T","K2S10T","K2S02T","K2S02T","K2S08T","K2S08T","K2S09T","K2S09T","K2S04T","K2S04T","K2S01T","K2S01T","K2S11T","K2S11T","K2G06T","K2G06T","K2G06N","K2G06N","K2G08T","K2G08T","K2G08N","K2G08N","K2G10T","K2G10T","K2G10N","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT06T","XGT08T","XGT08T","XGT10T","XGT10T","XGT06P","XGT06P","XGT08P","XGT08P","XGT10P","XGT10P","XGT07P","XGT07P","XGT09P","XGT09P","XGT11P","XGT11P","KGT01P","KGT01P","KGX01P"};
	ACE_CString indexConstKosdaqMap2[ANOTHERJISUCNT] = 
	{"KRD020020008","KRD020020008","KRD020020081","KRD020020099","KRD020020107","KRD020020115","KRD020020123","KRD020020131","KRD020020149","KRD020020156","KRD020020164","KRD020020172","KRD020020180","KRD020020198","KRD020020206","KRD020020214","KRD020020222","KRD020020230","KRD020020248","KRD020020255","KRD020020263","KRD020020271","KRD020020289","KRD020020297","KRD020020305","KRD020020313","KRD020020321","KRD020020016","KRD020020016","KRD020020024","KRD020020032","KRD020022327","KRD020022327","KRD020020339","KRD020020339","KRD020020347","KRD020020347","KRD020020354","KRD020020354","KRD020020362","KRD020020362","KRD020020370","KRD020020370","KRD020020388","KRD020020388","KRD020020396","KRD020020396","KRD020020404","KRD020020404","KRD020021386","KRD020021386","KRD020021394","KRD020021394","KRD020021048","KRD020021048","KRD020021055","KRD020021055","KRD020021063","KRD020021063","KRD020021071","KRD020021071","KRD020020073","KRD020020073","KRD020022087","KRD020022087","KRD020020842","KRD020020842","KRD020020859","KRD020020859","KRD020020867","KRD020020867","KRD020020875","KRD020020875","KRD020020891","KRD020020891","KRD020020909","KRD020020909","KRD020020925","KRD020020925","KRD020020933","KRD020020933","KRD020020958","KRD020020958","KRD020020966","KRD020020966","KRD020020974","KRD020020974","KRD020020982","KRD020020982","KRD020021741","KRD020021741","KRD020021758","KRD020021758","KRD020021766","KRD020021766","KRD020021774","KRD020021774","KRD020021782","KRD020021782","KRD020029330","KRD020029330","KRD020029348","KRD020029348","KRD020040006","KRD020040006","KRD020020438","KRD020020446","KRD020020453","KRD020020461","KRD020040022","KRD020040022","KRD020020479","KRD020020487","KRD020020495","KRD020020503","KRD020020511","KRD020020529","KRD020020537","KRD020020545","KRD020020552","KRD020020560","KRD020020578","KRD020020586","KRD020020594","KRD020020602","KRD020020610","KRD020020628","KRD020020636","KRD020020644","KRD020020651","KRD020020669","KRD020020677","KRD020020685","KRD020020693","KRD020020701","KRD020020719","KRD020020727","KRD020020735","KRD020020743","KRD020020750","KRD020020768","KRD020020776","KRD020020784","KRD020020792","KRD020020792","KRD020020800","KRD020020800","KRD020020818","KRD020020818","KRD020020826","KRD020020826","KRD020021089","KRD020021089","KRD020020412","KRD020021329","KRD020021329","KRD020021311","KRD020021311","KRD020021352","KRD020021402","KRD020022459","KRD020022459","KRD020029322","KRD020029322","KRD020029280","KRD020029280","KRD020022723","KRD020022723","KRD020022368","KRD020022368","KRD020022806","KRD020022806","KRD020022947","KRD020022947","KRD020022970","KRD020022970","KRD020023028","KRD020023028","KRD020022004","KRD020022004","KRD020022012","KRD020022012","KRD020021345","KRD020021345","KRD020021444","KRD020021444","KRD020021451","KRD020021451","KRD020021469","KRD020021469","KRD020021824","KRD020022061","KRD020022061","KRD020023085","KRD020023085","KRD020023127","KRD020023127","KRD020023119","KRD020023119","KRD020023101","KRD020023101","KRD020023093","KRD020023093","KRD020022228","KRD020022228","KRD020022236","KRD020022236","KRD020022244","KRD020022244","KRD020022251","KRD020022251","KRD020022269","KRD020022269","KRD020022475","KRD020022475","KRD020022483","KRD020022483","KRD020022491","KRD020022491","KRD020021360","KRD020021360","KRD020021410","KRD020021378","KRD020021378","KRD020021642","KRD020021642","KRD020021659","KRD020021659","KRD020021667","KRD020021667","KRD020021675","KRD020021675","KRD020021683","KRD020021683","KRD020021691","KRD020021691","KRD020021709","KRD020021709","KRD020022731","KRD020022731","KRD020021436","KRD020021477","KRD020021477","KRD020021485","KRD020021485","KRD020021113","KRD020021170","KRD020021121","KRD020021188","KRD020021105","KRD020021162","KRD020021303","KRD020021147","KRD020021097","KRD020021154","KRD020021139","KRD020021196","KRD020021204","KRD020021220","KRD020021238","KRD020021246","KRD020021253","KRD020021295","KRD020021261","KRD020021212","KRD020021279","KRD020021287","KRD020023713","KRD020020G06","KRD020020G22","KRD020020G48","KRD020023721","KRD020020G71","KRD020020G97","KRD020020GB1","KRD020023697","KRD020023705","KRD020023242","KRD020023259","KRD020023564","KRD020023572","KRD020023226","KRD020023622","KRD020023630","KRD020024117","KRD020023648","KRD020023218","KRD020023580","KRD020023598","KRD020023606","KRD020023614","KRD020023168","KRD020023176","KRD020023135","KRD020023143","KRD020023150","KRD020024083","KRD020021618","KRD020021626","KRD020021600","KRD020023184","KRD020023671","KRD020023689","KRD020023200","KRD020023531","KRD020023549","KRD020023556","KRD020021840","KRD020023234","KRD020021568","KRD020021576","KRD020021584","KRD020021592","KRD020029306","KRD020029314","KRD020023192","KRD020023267","KRD020023275","KRD020023283","KRD020021790","KRD020021790","KRD020021808","KRD020021808","KRD020021816","KRD020022715","KRD020021832","KRD020021899","KRD020021907","KRD020021972","KRD020021980","KRD020021998","KRD020021915","KRD020021923","KRD020021931","KRD020021949","KRD020021956","KRD020021964","KRD020022046","KRD020022053","KRD020022095","KRD020022707","KRD020022103","KRD020022111","KRD020022129","KRD020022137","KRD020022145","KRD020022277","KRD020022285","KRD020022293","KRD020022301","KRD020022319","KRD020022467","KRD020022509","KRD020022517","KRD020022525","KRD020022533","KRD020022541","KRD020022558","KRD020022566","KRD020022574","KRD020022582","KRD020022590","KRD020024026","KRD020023291","KRD020023309","KRD020024091","KRD020023317","KRD020023325","KRD020023333","KRD020023341","KRD020023358","KRD020023366","KRD020023374","KRD020023382","KRD020023390","KRD020024109","KRD020023408","KRD020023416","KRD020023424","KRD020023432","KRD020023440","KRD020023457","KRD020024034","KRD020023465","KRD020023473","KRD020024042","KRD020023481","KRD020023499","KRD020023507","KRD020024059","KRD020023515","KRD020023523","KRD020022350","KRD020022335","KRD020022343","KRD020022376","KRD020022384","KRD020022384","KRD020022392","KRD020022392","KRD020022418","KRD020022418","KRD020022400","KRD020022400","KRD020022434","KRD020022434","KRD020022442","KRD020022442","KRD020022814","KRD020022814","KRD020022822","KRD020022822","KRD020022830","KRD020022830","KRD020022848","KRD020022848","KRD020022855","KRD020022855","KRD020022863","KRD020022863","KRD020022871","KRD020022871","KRD020022889","KRD020022889","KRD020022897","KRD020022897","KRD020022905","KRD020022905","KRD020022913","KRD020022913","KRD020022954","KRD020022954","KRD020022962","KRD020022962","KRD020022988","KRD020022988","KRD020023002","KRD020023002","KRD020023036","KRD020023036","KRD020023051","KRD020023051","KRD020022608","KRD020022616","KRD020022624","KRD020022632","KRD020022657","KRD020022640","KRD020022665","KRD020022673","KRD020022681","KRD020022699","KRD020022798","KRD020022749","KRD020022756","KRD020022764","KRD020022772","KRD020022780","KRD020023077","KRD020023655","KRD020023663","KRD020024760","KRD020026047","KRD020026054","KRD020029264","KRD020029272","KRD020029249","KRD020029256","KRD020029231","KRD020029298","KRD020029355","KRD020029363","KRD020029371","KRD020029389","KRD020020CV8","KRD020020CW6","KRD020020CX4","KRD020020CN5","KRD020020CN5","KRD020020CP0","KRD020020CP0","KRD020020CQ8","KRD020020CQ8","KRD0200200F2","KRD0200200F2","KRD0200200H8","KRD0200200H8","KRD0200200K2","KRD0200200K2","KRD0200200G0","KRD0200200G0","KRD0200200J4","KRD0200200J4","KRD0200200L0","KRD0200200L0","KRD020020FR9","KRD020020FR9","KRD020020FS7"};
	ACE_CString indexConstKosdaqMap3[ANOTHERJISUCNT] = 
	{"IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","Z5000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000"};
	ACE_CString indexConstKosdaqMap4[ANOTHERJISUCNT] = 
	{"D0011","D1011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D2011","D3011","D4011","D4011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N9011","O1011","N9011","O1011","N9011","O1011","N9011","O1011","C8011","C9011","AA011","AB011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E5012","E4012","E5012","E4012","E5012","P9018","R7018","Q8011","S4011","V0011","S6011","V2011","T2011","U1011","BK011","BL011","BK011","BL011","BK011","BL011","BK011","BL011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","Z0011","Z1011","Z0011","Z1011","S7011","V4011","U2011","U5011","U2011","U5011","U2011","U5011","Y0011","Z8011","Z9011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","T7011","T8011","U0011","T9012","U4012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W8012","W9012","U8012","Z2011","Z3011","Z2011","Z3011","O2016","O2016","O3016","O3016","L4016","L4016","R6016","K2011","K9014","K9014","J3034","N0034","N0034","O8011","O8011","O8011","O8011","R0011","P5011","O7011","P8011","P8011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","S9014","S9014","T4014","T4014","T5016","T5016","U6016","U6016","U6016","U6016","U6016","U7016","U7016","U7016","U7016","U7016","U9012","U9012","V7011","V7011","V7011","V7011","V7011","V7011","V7011","V8011","V9011","V9011","W1024","W1024","W1024","W1024","W1024","W0014","X0016","X0016","X0016","X0016","X0016","X0016","X2124","X2124","X2124","X2124","X6019","X7019","X6019","X7019","X9034","BQ034","Y1034","Y2014","Y5034","Y6011","Y7016","Y7016","Y8034","Y8034","Y9011","Y9011","Y9011","Y9011","Z6011","Z7034","AD034","AD034","AE164","AE164","AE164","AE164","AK011","AI011","AN011","AO034","AO034","AP034","AP034","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AS016","AQ034","AR034","AV034","AW011","AX011","AY012","AZ012","BC011","BD011","BA012","BB012","BG011","BH011","BI011","BJ011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BO034","BO034","BO034","X0016","X0016","X0016","X0016","Y6011","Y6011","Y6011","Y6011","AI011","AI011","AI011","AI011","AI011","T5016","T1014","T1014","Z5011","Y6011","Y6011","AI011","AI011","AK011","AK011","AN011","V7011","AJ104","AJ104","W1024","W1024","Y6011","Y6011","Y6011","BE011","BF011","BE011","BF011","BE011","BF011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","BK011","BL011","V7011"};
	ACE_CString indexConstKosdaqMap5[ANOTHERJISUCNT] = 
	{"D0","D1","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D2","D3","D4","D4","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N9","O1","N9","O1","N9","O1","N9","O1","C8","C9","AA","AB","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E4","E5","E4","E4","E4","E4","E4","E5","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E5","E4","E5","E4","E5","E4","E5","P9","R7","Q8","S4","V0","S6","V2","T2","U1","BK","BL","BK","BL","BK","BL","BK","BL","AT","AU","AT","AU","AT","AU","AT","AU","AT","AU","Z0","Z1","Z0","Z1","S7","V4","U2","U5","U2","U5","U2","U5","Y0","Z8","Z9","AG","AH","AG","AH","AG","AH","AG","AH","AG","AH","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","T7","T8","U0","T9","U4","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W8","W9","U8","Z2","Z3","Z2","Z3","O2","O2","O3","O3","L4","L4","R6","K2","K9","K9","J3","N0","N0","O8","O8","O8","O8","R0","P5","O7","P8","P8","J2","J2","J2","J2","J2","J2","J2","J2","S9","S9","T4","T4","T5","T5","U6","U6","U6","U6","U6","U7","U7","U7","U7","U7","U9","U9","V7","V7","V7","V7","V7","V7","V7","V8","V9","V9","W1","W1","W1","W1","W1","W0","X0","X0","X0","X0","X0","X0","X2","X2","X2","X2","X6","X7","X6","X7","X9","BQ","Y1","Y2","Y5","Y6","Y7","Y7","Y8","Y8","Y9","Y9","Y9","Y9","Z6","Z7","AD","AD","AE","AE","AE","AE","AK","AI","AN","AO","AO","AP","AP","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AS","AQ","AR","AV","AW","AX","AY","AZ","BC","BD","BA","BB","BG","BH","BI","BJ","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BO","BO","BO","X0","X0","X0","X0","Y6","Y6","Y6","Y6","AI","AI","AI","AI","AI","T5","T1","T1","Z5","Y6","Y6","AI","AI","AK","AK","AN","V7","AJ","AJ","W1","W1","Y6","Y6","Y6","BE","BF","BE","BF","BE","BF","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","BK","BL","V7"};
#endif

#if(1)
	ACE_CString indexConstKosdaqMap1[TOTALJISUCNT] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","XGD02P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","O2903P","F2X06P","O2X01P","MGA12P","FTX06T","FTX08T","GGS01P","O2904P","F3G01P","F3X01T","F3X02P","F3X03T","X3X01P","MGA13T","F2V02P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03T","FGA04T","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05T","F5901P","F5X05T","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","TGX01P","G2T01P","F2X40T","F2X41T","F5X06T","F5X07T","QGG11P"};
	ACE_CString indexConstKosdaqMap6[TOTALJISUCNT] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","165","132","133","134","142","136","411","412","413","414","415","351","352","353","354","355","356","357","358","600","167","203","212","213","214","215","216","217","218","331","204","175","176","301","302","303","304","001","002","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","001","001","001","002","002","002","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","707","731","708","821","312","313","003","709","304","306","307","308","305","822","732","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","003","005","286","287","422","423","189"};
#endif

#if(1)
ACE_CString InternetKosdaqChannelProcessor::getSymbolUpCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<TOTALJISUCNT; kk++)
	{
		if(raw == indexConstKosdaqMap1[kk])
		{
			ii=kk;
			ff=100;
			break;
		}
	}

	if(ff==0)
	{
		std::ostringstream os;
		os << "000";
		return os.str().c_str();
	}
	else
	{
		return(indexConstKosdaqMap6[ii]);
	}
}

ACE_CString InternetKosdaqChannelProcessor::getSymbolFrameId(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<ANOTHERJISUCNT; kk++)
	{
		if(raw == indexConstKosdaqMap0[kk])
		{
			ii=kk;
			ff=100;
			break;
		}
	}

	if(ff==0)
	{
		std::ostringstream os;
		os << "000";
		return os.str().c_str();
	}
	else
	{
		return(indexConstKosdaqMap5[ii]);
	}
}
#endif




