#include <sstream>
#include <utility>

#include "InvestorCodeConverter.h"
#include "InternetKseChannelProcessor.h"

#include "PaxfeedDefine.h"
#include "PaxfeedPacket.h"
#include "ace/Log_Msg.h"
#include "MMapAllocator.h"
#include "PaxfeedStatus.h"
#include "PaxfeedStringUtil.h"
#include "TickFilter.h"
#include "MasterKseProcessor.h"
#include <exception>
#include "SimpleStringUtil.h"
#include <boost/algorithm/string.hpp>

using namespace paxfeed;

InternetKseChannelProcessor::InternetKseChannelProcessor(const ACE_CString &channelName)
        : InternetChannelProcessor(channelName)
{
    initTradeTypeList();
}

InternetKseChannelProcessor::~InternetKseChannelProcessor()
{

}

int InternetKseChannelProcessor::reset()
{
    InternetChannelProcessor::reset();
    return 0;
}

#if(1)
int InternetKseChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString frameID(packet.substr(0, 2));
    ACE_CString informationCategoryAndMarketCategory(packet.substr(2, 3));
    ACE_CString trID(packet.substr(0, 5));
	ACE_CString dataType(packet.substr(0, 5));
    ACE_CString marketClass(packet.substr(4, 1));

	int hasValue;
	ExturePlusKseMaster kseUsage;

	if(dataType=="A001S")
	{
		MasterKseProcessor masterProc(frameID, packet, getSerial());
		if ( masterProc.isValidPacket() == true )
        {
            int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));

			memcpy(&kseUsage, packet.c_str(), packet.length());
			ACE_CString stockCode1(kseUsage.stockCode, sizeof(kseUsage.stockCode));

			hasValue = masterMapKse_->find(stockCode1, kseUsage, ALLOCATOR::instance());

			if ( hasValue == -1 )
			{
				masterMapKse_->bind(ACE_CString(stockCode1.c_str(), ALLOCATOR::instance()), kseUsage, ALLOCATOR::instance());
			}
        }
	}
	else if(dataType=="CA01S")
	{
		ExturePlusKseJisuMaster ksejisu;
        memcpy(&ksejisu, packet.c_str(), packet.length());

		ACE_CString stockCode2(ksejisu.stockCode, sizeof(ksejisu.stockCode));
		hasValue = masterMapKse_->find(stockCode2, kseUsage, ALLOCATOR::instance());

		if ( hasValue == -1 )
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::masterMapKse_->find] Error symbol:[%s] hasValue:[%d]\n" , getCurrentTimestamp().c_str() , stockCode2.c_str() , hasValue ));

			return(0);
		}
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.dataClass),kseUsage.dataClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.infoMarketClass),kseUsage.infoMarketClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.distributeStockIndex),kseUsage.distributeStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.distributeTotalStockIndex),kseUsage.distributeTotalStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.sendDate),kseUsage.sendDate));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.stockCode),kseUsage.stockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.stockSeq),kseUsage.stockSeq));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.abbrStockCode),kseUsage.abbrStockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.abbrStockNameKor),kseUsage.abbrStockNameKor));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.abbrStockNameEng),kseUsage.abbrStockNameEng));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.infoDivisionGroupNo),kseUsage.infoDivisionGroupNo));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.MarketProductGroupID),kseUsage.MarketProductGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.stockGroupID),kseUsage.stockGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isUnitTrade),kseUsage.isUnitTrade));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.exClassCode),kseUsage.exClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.faceValueChangeClassCode),kseUsage.faceValueChangeClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isOpenPriceBecomeStdPrice),kseUsage.isOpenPriceBecomeStdPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isRevaluationStockReason),kseUsage.isRevaluationStockReason));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isStandardPriceChangeStock),kseUsage.isStandardPriceChangeStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.randomEndTriggerConditionCode),kseUsage.randomEndTriggerConditionCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isMarketAlarmDangerNotice),kseUsage.isMarketAlarmDangerNotice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.marketAlarmClassCode),kseUsage.marketAlarmClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isCorporateGovernanceFine),kseUsage.isCorporateGovernanceFine));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isManagementStock),kseUsage.isManagementStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isInsincerityPublicNewsAppoint),kseUsage.isInsincerityPublicNewsAppoint));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isBackDoorListing),kseUsage.isBackDoorListing));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isTradeStop),kseUsage.isTradeStop));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.standardIndustryCode),kseUsage.standardIndustryCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.SmallMediumEnterprisesIs),kseUsage.SmallMediumEnterprisesIs));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isCorporateGovernanceIndexStock),kseUsage.isCorporateGovernanceIndexStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.investOrganClassCode),kseUsage.investOrganClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.standardPrice),kseUsage.standardPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayClosePriceClassCode),kseUsage.ydayClosePriceClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayClosePrice),kseUsage.ydayClosePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayAccmVolume),kseUsage.ydayAccmVolume));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayAccmAmount),kseUsage.ydayAccmAmount));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.upLimitPrice),kseUsage.upLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.downLimitPrice),kseUsage.downLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.substitutePrice),kseUsage.substitutePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.faceValue),kseUsage.faceValue));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.issuePrice),kseUsage.issuePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.listingDate),kseUsage.listingDate));

		MasterKseProcessor masterProc(frameID, packet, getSerial(), kseUsage);
		if ( masterProc.isValidPacket() == true )
        {
			int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , 
				getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));
        }
	}
	else if(dataType=="C401S")
	{
		handleBulkTrade(packet);
	}
	else if(dataType=="A301S")
	{
		handleTrade(packet);
	}
	else if(dataType=="A401S")
    {
        handleDeterminedBasePrice(packet);
    }
	else if(dataType=="B601S")
    {
        handleQuote10(packet);
    }
	else if(dataType=="B901S")
    {
        handleSecuritiesTrade(packet);
    }
	else if(dataType=="A801S")
    {
        handleIssueInformationDisclosure(packet);
    }
	else if(dataType=="J001S")
    {
        handleProgramTradeTotal(packet);
    }
	else if(dataType=="C301S")
    {
        handleProgramTrade(packet);
    }
	else if(dataType=="O601S")
    {
        handleQuantityAllocation(packet);
    }
	else if(dataType=="B201S")
	{
		handleRecoveryTotalTrade(packet);
	}
	else if(dataType=="B501S")
	{
		handleUpDown(packet);
	}
	else if(dataType=="B501S")
	{
		handleUpDown(packet);
	}
	else if(dataType=="F000S")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="E900S")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="F000Q")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="E900Q")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="F000X")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="E900X")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="I601S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if(dataType=="I801S")
	{
		handleShortSellingInfo(packet);
	}
	else if(dataType=="M401S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
	else if(dataType=="R801S")
	{
		handleKOSPIVolatilityInterruptionPerInstrument(packet);
	}
#if(0)
//코스콤 정보,ETN 사무수탁정보             ,S104S
//코스콤 정보,ETP정보,ETN 기초지수 구성종목,S204S
//코스콤 정보,ETP정보,ETN IIV              ,S304S
//코스콤 정보,ETP정보,ETF 사무수탁배치     ,N803S
//코스콤 정보,ETP정보,ETF PDF              ,F803S
#endif
	else if(dataType=="S104S")
	{
		handleETNTransferAgentBatchData(packet);
	}
	else if(dataType=="S204S")
	{
		handleETNIndexCompositionConstituents(packet);
	}
	else if(dataType=="S304S")
	{
		handleETN_IIV(packet);
	}
	else if(dataType=="N803S")
	{
		handleETFWorkEntrustmentBatch(packet);
	}
	else if(dataType=="F803S")
	{
		handleETF_PDF(packet);
	}
#if(0)
//코스콤 정보,외국인 투자정보	코스피 외국인 종목별투자정보(확정치),F101S
//코스콤 정보,외국인 투자정보	코스닥 외국인 종목별투자정보(확정치),F101Q
//코스콤 정보,외국인 투자정보	코스피 외국인 확정치데이터재전송,F401S
//코스콤 정보,외국인 투자정보	코스닥 외국인 확정치데이터재전송,F401Q
#endif
	else if(dataType=="F101S")
	{
		handleForeignerMaster(packet);
	}
	else if(dataType=="F101Q")
	{
		handleForeignerMaster(packet);
	}
	else if(dataType=="F401S")
	{
		handleForeignerMasterUpdate(packet);
	}
	else if(dataType=="F401Q")
	{
		handleForeignerMasterUpdate(packet);
	}
	else if(dataType=="B801S")
	{
		handleQuoteBefore(packet);
	}
	else if(dataType=="C001S")
	{
		handleInvestorIndex(packet);
	}
	else if(dataType=="A701S")
	{
		handleMarketOperationTS(packet);
	}
#if(1)
	else if(dataType=="IA000")
	{
		ExturePlusTotalKseIndex totalkse;
		ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

		ACE_CString jisuFrameId(totalkse.dataID, sizeof ( totalkse.dataID ));
		jisuFrameId = getSymbolFrameId(jisuFrameId);

		ACE_DEBUG( ( LM_DEBUG , "[%s][%.*s][%.*s] [InternetKseChannelProcessor::processPacket] jisuFrameId Data:[%s]\n" , 
			getCurrentTimestamp().c_str() , 
			sizeof(totalkse.dataClass),totalkse.dataClass,
			sizeof(totalkse.dataID),totalkse.dataID,
			jisuFrameId.c_str() ));

		if ( jisuFrameId == "C8")	    //KRX100지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D0")	//KOSPI지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D1")	//KOSPI예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "D2")	//KOSPI200지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D4")	//KOSPI100/50지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T7")	//KTOP30지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T8")	//KTOP30예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "N9")	//동일가중지수	
		{
			handleEquallyWeightedIndex(packet);
		}
		else if ( jisuFrameId == "O1")	//동일가중예상지수	
		{
			handleEquallyWeightedIndexForecast(packet);
		}
	}
	else if(dataType=="IB000")
	{
		ExturePlusTotalKseIndex totalkse;
		ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

		ACE_CString jisuFrameId(totalkse.dataID, sizeof ( totalkse.dataID ));
		jisuFrameId = getSymbolFrameId(jisuFrameId);

		ACE_DEBUG( ( LM_DEBUG , "[%s][%.*s][%.*s] [InternetKseChannelProcessor::processPacket] jisuFrameId Data:[%s]\n" , 
			getCurrentTimestamp().c_str() , 
			sizeof(totalkse.dataClass),totalkse.dataClass,
			sizeof(totalkse.dataID),totalkse.dataID,
			jisuFrameId.c_str() ));

		if ( jisuFrameId == "C8")	    //KRX100지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D0")	//KOSPI지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D1")	//KOSPI예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "D2")	//KOSPI200지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D4")	//KOSPI100/50지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T7")	//KTOP30지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T8")	//KTOP30예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "N9")	//동일가중지수	
		{
			handleEquallyWeightedIndex(packet);
		}
		else if ( jisuFrameId == "O1")	//동일가중예상지수	
		{
			handleEquallyWeightedIndexForecast(packet);
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
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] polling Data:[%s]\n" , getCurrentTimestamp().c_str() , packet.c_str() ));
		}
		else if ( frameID == "ZZ" )
		{
			// 지수 리커버리(내부)
			handleCustomIndexRecovery(packet);
		}
		else
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] trID:[%s]\n" , getCurrentTimestamp().c_str() , trID.c_str() ));
		}
	}
    return 0;
}
#endif

bool InternetKseChannelProcessor::isValidSymbol(const ACE_CString& symbol)
{
    ACE_CString isNormalstockCode(symbol.substr(0, 3));

    return true;
}

int InternetKseChannelProcessor::handleBulkTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_TOTAL_BULK_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleBulkTrade] Skip : %s,%d : EXTURE_PLUS_KSE_BULK_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_BULK_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // 일단 대량체결 처리는 정책확정시까지 보류한다.
	ExturePlusKseTotalBulkTrade priorkse;
	ACE_OS::memcpy(&priorkse, packet.c_str(), packet.length());

	ExturePlusKseBulkTrade kse;
    ::memset(&kse, 0x20, sizeof(ExturePlusKseBulkTrade));//0x20(SPACE) INIT

	ACE_CString boardID(priorkse.boardID, sizeof ( priorkse.boardID ));
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
	if(boardID=="B2") ::memcpy(kse.kBloxVolumeInPreMarketTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.kBloxVolumeInPreMarketTradingHoursSession));
	if(boardID=="K2") ::memcpy(kse.basketTradingVolumeInPreMarketTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.basketTradingVolumeInPreMarketTradingHoursSession));
	if(boardID=="I2") ::memcpy(kse.aBloxVolumeInPreMarketTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.aBloxVolumeInPreMarketTradingHoursSession));
	if(boardID=="B1") ::memcpy(kse.kBloxVolumeInRegularTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.kBloxVolumeInRegularTradingHoursSession));
	if(boardID=="K1") ::memcpy(kse.basketTradingVolumeInRegularTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.basketTradingVolumeInRegularTradingHoursSession));
	if(boardID=="I1") ::memcpy(kse.aBloxVolumeInRegularTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.aBloxVolumeInRegularTradingHoursSession));
	if(boardID=="B3") ::memcpy(kse.kBloxVolumeInPostMarketTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.kBloxVolumeInPostMarketTradingHoursSession));
	if(boardID=="K3") ::memcpy(kse.basketTradingVolumeInPostMarketTradingHoursSession, priorkse.accumlatedVolume, sizeof(kse.basketTradingVolumeInPostMarketTradingHoursSession));

	::memcpy(kse.issueCode, priorkse.stockCode, sizeof(kse.issueCode));

	ACE_CString symbol(kse.issueCode, sizeof ( kse.issueCode ));
	ACE_CString issueCode(kse.issueCode, sizeof ( kse.issueCode ));

    const ACE_CString BOARD_ID_PRE_OFF_HOURS_SESSION_B2("B2");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_PRE_OFF_HOURS_SESSION_K2("K2");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_PRE_OFF_HOURS_SESSION_I2("I2");	//KOSPI/KOSDAQ
    const ACE_CString BOARD_ID_REGULAR_SESSION_B1("B1");	//KOSPI/KOSDAQ
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
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleBulkTrade] symbol:[%s]\tskip dummy packet\n" , getCurrentTimestamp().c_str() , symbol.c_str() ));
        return 0;
    }

    int recvTime = (int) ( ::time(0) );


#if(0)
    double kBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kse.kBloxVolumeInPreMarketTradingHoursSession, sizeof ( kse.kBloxVolumeInPreMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kse.basketTradingVolumeInPreMarketTradingHoursSession, sizeof ( kse.basketTradingVolumeInPreMarketTradingHoursSession )).c_str());
    double aBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kse.aBloxVolumeInPreMarketTradingHoursSession, sizeof ( kse.aBloxVolumeInPreMarketTradingHoursSession )).c_str());

    double kBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kse.kBloxVolumeInRegularTradingHoursSession, sizeof ( kse.kBloxVolumeInRegularTradingHoursSession )).c_str());
    double basketTradingVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kse.basketTradingVolumeInRegularTradingHoursSession, sizeof ( kse.basketTradingVolumeInRegularTradingHoursSession )).c_str());
    double aBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kse.aBloxVolumeInRegularTradingHoursSession, sizeof ( kse.aBloxVolumeInRegularTradingHoursSession )).c_str());

    double kBloxVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kse.kBloxVolumeInPostMarketTradingHoursSession, sizeof ( kse.kBloxVolumeInPostMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kse.basketTradingVolumeInPostMarketTradingHoursSession, sizeof ( kse.basketTradingVolumeInPostMarketTradingHoursSession )).c_str());

    double tradeVolumePreMarket = kBloxVolumeInPreMarketTradingHoursSession + basketTradingVolumeInPreMarketTradingHoursSession + aBloxVolumeInPreMarketTradingHoursSession;
    double tradeVolumeRegularMarket = kBloxVolumeInRegularTradingHoursSession + basketTradingVolumeInRegularTradingHoursSession + aBloxVolumeInRegularTradingHoursSession;
    double tradeVolumePostMarket = kBloxVolumeInPostMarketTradingHoursSession + basketTradingVolumeInPostMarketTradingHoursSession;
#endif

#if(1)
    double kBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kse.kBloxVolumeInPreMarketTradingHoursSession, sizeof ( kse.kBloxVolumeInPreMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kse.basketTradingVolumeInPreMarketTradingHoursSession, sizeof ( kse.basketTradingVolumeInPreMarketTradingHoursSession )).c_str());
    double aBloxVolumeInPreMarketTradingHoursSession = ::atof(ACE_CString(kse.aBloxVolumeInPreMarketTradingHoursSession, sizeof ( kse.aBloxVolumeInPreMarketTradingHoursSession )).c_str());

	if(kBloxVolumeInPreMarketTradingHoursSession == 0) kBloxVolumeInPreMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_B2);
	if(basketTradingVolumeInPreMarketTradingHoursSession == 0) basketTradingVolumeInPreMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_K2);
	if(aBloxVolumeInPreMarketTradingHoursSession == 0) aBloxVolumeInPreMarketTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_I2);

    double kBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kse.kBloxVolumeInRegularTradingHoursSession, sizeof ( kse.kBloxVolumeInRegularTradingHoursSession )).c_str());
    double basketTradingVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kse.basketTradingVolumeInRegularTradingHoursSession, sizeof ( kse.basketTradingVolumeInRegularTradingHoursSession )).c_str());
    double aBloxVolumeInRegularTradingHoursSession = ::atof(ACE_CString(kse.aBloxVolumeInRegularTradingHoursSession, sizeof ( kse.aBloxVolumeInRegularTradingHoursSession )).c_str());

	if(kBloxVolumeInRegularTradingHoursSession == 0) kBloxVolumeInRegularTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_B1);
	if(basketTradingVolumeInRegularTradingHoursSession == 0) basketTradingVolumeInRegularTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_K1);
	if(aBloxVolumeInRegularTradingHoursSession == 0) aBloxVolumeInRegularTradingHoursSession = getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_I1);

    double kBloxVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kse.kBloxVolumeInPostMarketTradingHoursSession, sizeof ( kse.kBloxVolumeInPostMarketTradingHoursSession )).c_str());
    double basketTradingVolumeInPostMarketTradingHoursSession = ::atof(ACE_CString(kse.basketTradingVolumeInPostMarketTradingHoursSession, sizeof ( kse.basketTradingVolumeInPostMarketTradingHoursSession )).c_str());

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

#if(1)
printPacketBlockTrade(blockRec);
#endif

    char buf[BLOCK_TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &blockRec, BLOCK_TRADE_SIZE);

    int result = sendPacket(ACE_CString(buf, BLOCK_TRADE_SIZE), PACKET_BLOCK_TRADE, EXCHANGE_KSE);
    return result;
}

int InternetKseChannelProcessor::handleETFWorkEntrustmentBatch(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_ETF_WORK_ENTRUSTMENT_BATCH_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleETFWorkEntrustmentBatch] Skip : %s,%d : EXTURE_PLUS_KSE_ETF_WORK_ENTRUSTMENT_BATCH_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_ETF_WORK_ENTRUSTMENT_BATCH_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseETFWorkEntrustmentBatch batchRec;
    ACE_OS::memcpy(&batchRec, packet.c_str(), packet.length());

    ACE_CString stockCode(batchRec.stockCode, sizeof ( batchRec.stockCode ));

    if ( stockCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_INFO , "[%s] [InternetKseChannelProcessor::handleETFWorkEntrustmentBatch] - Skip dummy data(%s)\n" , getCurrentTimestamp().c_str() , stockCode.c_str() ));
    }
    else
    {
		//
    }
    int result = 0;
    return result;
}

int InternetKseChannelProcessor::handleTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleTrade] Skip : %s,%d : EXTURE_PLUS_KSE_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());
	ACE_CString dataType(packet.substr(0, 5));

    ACE_CString frameId = "A3";

    ExturePlusKseTrade kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());
    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
    ACE_CString isNormalstockCode(kse.stockCode, ( sizeof kse.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.


	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] stockCode  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.stockCode),kse.stockCode ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] boardID    :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.boardID),kse.boardID ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] sessionID  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.sessionID),kse.sessionID ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] transactionProcessingTime:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.transactionProcessingTime),kse.transactionProcessingTime ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] upDown     :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.upDown),kse.upDown ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] gap        :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.gap),kse.gap ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] tradePrice :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.tradePrice),kse.tradePrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] tradeVolume:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.tradeVolume),kse.tradeVolume ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] openPrice  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.openPrice),kse.openPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] highPrice  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.highPrice),kse.highPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] lowPrice   :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.lowPrice),kse.lowPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] accmTradeVolume:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.accmTradeVolume),kse.accmTradeVolume ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTrade] accmTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.accmTradeAmount),kse.accmTradeAmount ));

    if ( isValidSymbol(stockCode) == false )
    {
        //ACE_DEBUG((LM_DEBUG, "[%s] [InternetKseChannelProcessor::handleTrade] skip stockCode( %s )\n", getCurrentTimestamp().c_str(), stockCode.c_str()));
        return 0;
    }

    ACE_CString boardID(kse.boardID, sizeof ( kse.boardID ));
    ACE_CString sessionID(kse.sessionID, sizeof ( kse.sessionID ));

    /*
     * 정규시간외구분코드가 7(일반바이인), 8(당일바이인) 인 경우 skip 한다.
     * 코드값모음집(20131010)
     * ==> 일반 바이인(G7)
     * ==> 당일 바이인(G8)
     */

    if ( ( boardID == "G7" ) || ( boardID == "G8" ) )
    {
        return 0;
    }
    // 체결유형코드가 25(바이인)인 경우 skip 한다.
    // 세션 ID ==> 25
    if ( sessionID == "25" )
    {
        return 0;
    }

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));
    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());


#if(0)
    // 정규시간외구분코드 : 장종료후시간외단일가(4) , 체결유형코드 : 시간외단일가(70)
    // 4    장종료후시간외단일가  G4  유가/코스닥
    if ( ( boardID == "G4" ) || ( sessionID == "70" ) )
    {
        return handleTradeFixed(kse); //시간외단일가
    }
#endif
#if(1)
    // 정규시간외구분코드 : 장종료후시간외단일가(4) , 체결유형코드 : 시간외단일가(70)
    // 4    장종료후시간외단일가  G4  유가/코스닥
    if ( ( boardID == "G4" ) )
    {
        return handleTradeFixed(kse); //시간외단일가
    }
#endif

    ACE_CString upDown(kse.upDown, sizeof kse.upDown);
    trade.market = getMarketInTrade(boardID);
    trade.upDown = getUpDownInTrade(upDown);

    // 장개시전시간외거래인 경우 시가, 고가, 저가는 0으로 셋팅하고 종가는 체결가로 셋팅한다.
    if ( ( boardID == "G2" ) || ( sessionID == "50" ) )
    {
        trade.open = 0;
        trade.high = 0;
        trade.low = 0;
        trade.close = atoi(ACE_CString(kse.tradePrice, sizeof kse.tradePrice).c_str());
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
        trade.open = atoi(ACE_CString(kse.openPrice, sizeof kse.openPrice).c_str());
        trade.high = atoi(ACE_CString(kse.highPrice, sizeof kse.highPrice).c_str());
        trade.low = atoi(ACE_CString(kse.lowPrice, sizeof kse.lowPrice).c_str());
        trade.close = atoi(ACE_CString(kse.tradePrice, sizeof kse.tradePrice).c_str());
    }

    ACE_CString tradePrice(kse.tradePrice, sizeof ( kse.tradePrice ));
    ACE_CString openPrice(kse.openPrice, sizeof ( kse.openPrice ));
    ACE_CString highPrice(kse.highPrice, sizeof ( kse.highPrice ));
    ACE_CString lowPrice(kse.lowPrice, sizeof ( kse.lowPrice ));

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(kse.accmTradeVolume, sizeof kse.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kse.accmTradeAmount, sizeof kse.accmTradeAmount).c_str());

	//차세대 시스템(체결가격이 존재하므로 값을 직접 입력)
    trade.tradeVolume = ::atof(ACE_CString(kse.tradeVolume, sizeof kse.tradeVolume).c_str());

    if ( trade.tradeVolume < 0 )
    {
        /*
         * APP 재기동후 간혹 오류가 나는 경우가 있다.
         * 해당 boardID 의 accmVolume 을 현재것으로 처리하고 다음 리커버리를 기다린다.
         */
        setAccmVolume(stockCode, accmVolume, boardID);
        setAccmAmount(stockCode, accmAmount, boardID);
        trade.tradeVolume = 0;
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleTrade] Skip : %s,%d : net volume error stockCode:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , trade.tradeVolume ), -1);
    }

    setAccmVolume(stockCode, accmVolume, boardID);
    setAccmAmount(stockCode, accmAmount, boardID);

    trade.accmVolume = getTotalAccmVolume(stockCode);

    if ( trade.accmVolume == -1 )
    {
        trade.accmVolume = 0;   //accmVolume ;
    }

    int tradeTime = getTickTime(ACE_CString(kse.transactionProcessingTime, sizeof kse.transactionProcessingTime), frameId);

    trade.amount = getTotalAccmAmount(stockCode);
    if ( trade.amount == -1 )
    {
        trade.amount = 0;   //amount ;
    }

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = getModTime(tradeTime);
        memcpy(&trade.symbol, &kse.stockCode, sizeof kse.stockCode);

        trade.openMin = trade.close;
        trade.highMin = trade.close;
        trade.lowMin = trade.close;
        trade.volumeMin = trade.tradeVolume;

        tradeMap_->bind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, ALLOCATOR::instance());
    }
    else
    {
        int previousTime = trade.tradeTime;
        trade.tradeTime = getModTime(tradeTime);
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

#if(1)
printPacketTrade(trade);
#endif

    char buf[TRADE_SIZE];
    ::memset(buf, 0, sizeof ( buf ));
    memcpy(buf, &trade, TRADE_SIZE);
    sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

    return 0;
}


#if(1)
int InternetKseChannelProcessor::handleElwRecoveryTotalTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] Skip : %s,%d : EXTURE_PLUS_ELW_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , 
			EXTURE_PLUS_ELW_RECOVERY_TOTAL_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }
	int other_else=0;

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

   	ExturePlusElwRecoveryTotalTrade totalrawPacket;
	ACE_OS::memcpy(&totalrawPacket, packet.c_str(), packet.length());

    ExturePlusElwRecoveryTrade rawPacket;
	::memset(&rawPacket, 0x30, sizeof(rawPacket));

	memcpy(rawPacket.stockCode,totalrawPacket.stockCode,sizeof(rawPacket.stockCode));
	memcpy(rawPacket.boardID,totalrawPacket.boardID,sizeof(rawPacket.boardID));
	memcpy(rawPacket.upDown,totalrawPacket.upDown,sizeof(rawPacket.upDown));
	memcpy(rawPacket.gap,totalrawPacket.gap,sizeof(rawPacket.gap));
	memcpy(rawPacket.closePrice,totalrawPacket.closePrice,sizeof(rawPacket.closePrice));
	memcpy(rawPacket.openPrice,totalrawPacket.openPrice,sizeof(rawPacket.openPrice));
	memcpy(rawPacket.highPrice,totalrawPacket.highPrice,sizeof(rawPacket.highPrice));
	memcpy(rawPacket.lowPrice,totalrawPacket.lowPrice,sizeof(rawPacket.lowPrice));
	memcpy(rawPacket.realRateQuotationClass,totalrawPacket.realRateQuotationClass,sizeof(rawPacket.realRateQuotationClass));

	ACE_CString boardID(totalrawPacket.boardID, sizeof(totalrawPacket.boardID ));
    ACE_CString sessionID(totalrawPacket.sessionID, sizeof ( totalrawPacket.sessionID ));

	ACE_CString stockCode(rawPacket.stockCode, sizeof rawPacket.stockCode);
    ACE_CString isNormalstockCode(rawPacket.stockCode, ( sizeof rawPacket.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

	/*
	G2	장개시전종가	40
	G2	장개시전종가	40
	*/
	if(boardID == "G2")
	{
		memcpy(rawPacket.beforeMarketOverTimeClosePriceTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.beforeMarketOverTimeClosePriceTradeVolume));
		memcpy(rawPacket.beforeMarketOverTimeClosePriceTradeAmount,totalrawPacket.accmTradeAmount,sizeof(rawPacket.beforeMarketOverTimeClosePriceTradeAmount));

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
		memcpy(rawPacket.regularMarketTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.regularMarketTradeVolume));
		memcpy(rawPacket.regularMarketTradeAmount,totalrawPacket.accmTradeAmount,sizeof(rawPacket.regularMarketTradeAmount));

		other_else=100;
	}
	/*
	G3	장종료후종가	60
	G3	장종료후종가	40
	*/
	if(boardID == "G3")
	{
		memcpy(rawPacket.afterMarketOvertimeClosePriceTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.afterMarketOvertimeClosePriceTradeVolume));
		memcpy(rawPacket.afterMarketOvertimeClosePriceTradeAmount,totalrawPacket.accmTradeAmount,sizeof(rawPacket.afterMarketOvertimeClosePriceTradeAmount));

		other_else=100;
	}

	//G7	일반Buy-In	20	단일가	일반 Buy-In 체결수량       
	//G7	일반Buy-In	20	단일가	일반 Buy-In 거래대금       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 체결수량       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 거래대금  

	if(boardID == "G7")
	{
		memcpy(rawPacket.regularBuyInTradingVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.regularBuyInTradingVolume));
		memcpy(rawPacket.regularBuyInTradingValue,totalrawPacket.accmTradeAmount,sizeof(rawPacket.regularBuyInTradingValue));

		other_else=100;
	}
	if(boardID == "G8")
	{
		memcpy(rawPacket.sameDayBuyInTradingVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.sameDayBuyInTradingVolume));
		memcpy(rawPacket.sameDayBuyInTradingValue,totalrawPacket.accmTradeAmount,sizeof(rawPacket.sameDayBuyInTradingValue));

		other_else=100;
	}

    //G4 시간외단일가누적 체결수량/시간외단일가누적 거래대금
	if(boardID=="G4")
	{
		memcpy(rawPacket.overTimeMarketFixedAccmVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.overTimeMarketFixedAccmVolume));
		memcpy(rawPacket.overTimeMarketFixedAccmAmount,totalrawPacket.accmTradeVolume,sizeof(rawPacket.overTimeMarketFixedAccmAmount));

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
		memcpy(rawPacket.manyBulkTradeVolume,totalrawPacket.accmTradeVolume,sizeof(rawPacket.manyBulkTradeVolume));
		memcpy(rawPacket.manyBulkTradeAmount,totalrawPacket.accmTradeVolume,sizeof(rawPacket.manyBulkTradeAmount));

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetElwChannelProcessor::handleRecoveryTotalTrade] stockCode:[%s],boardID:[%s],sessionID:[%s],manyBulkTradeVolume:[%.*s],manyBulkTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , stockCode.c_str() , boardID.c_str(), sessionID.c_str(), sizeof(rawPacket.manyBulkTradeVolume), rawPacket.manyBulkTradeVolume, sizeof(rawPacket.manyBulkTradeAmount), rawPacket.manyBulkTradeAmount));
	}

	Trade trade;
    ::memset(&trade, 0, sizeof(Trade));

    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(rawPacket.upDown, sizeof rawPacket.upDown);
	ACE_CString boardEventID(rawPacket.boardEventID, sizeof ( rawPacket.boardEventID ));

    trade.market = getMarketInRecoveryTrade(boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(rawPacket.openPrice, sizeof rawPacket.openPrice).c_str());
    trade.high = atoi(ACE_CString(rawPacket.highPrice, sizeof rawPacket.highPrice).c_str());
    trade.low = atoi(ACE_CString(rawPacket.lowPrice, sizeof rawPacket.lowPrice).c_str());
    trade.close = atoi(ACE_CString(rawPacket.closePrice, sizeof rawPacket.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(rawPacket.gap, sizeof rawPacket.gap).c_str());
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


	double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(rawPacket.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( rawPacket.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(rawPacket.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( rawPacket.beforeMarketOverTimeClosePriceTradeAmount )).c_str());

    if(beforeMarketOverTimeClosePriceTradeVolume == 0) beforeMarketOverTimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);
    if(beforeMarketOverTimeClosePriceTradeAmount == 0) beforeMarketOverTimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);

    double regularMarketTradeVolume = ::atof(ACE_CString(rawPacket.regularMarketTradeVolume, sizeof ( rawPacket.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(rawPacket.regularMarketTradeAmount, sizeof ( rawPacket.regularMarketTradeAmount )).c_str());

    if(regularMarketTradeVolume == 0) regularMarketTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_IN);
    if(regularMarketTradeAmount == 0) regularMarketTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_IN);

    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(rawPacket.afterMarketOvertimeClosePriceTradeVolume, sizeof ( rawPacket.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(rawPacket.afterMarketOvertimeClosePriceTradeAmount, sizeof ( rawPacket.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    if(afterMarketOvertimeClosePriceTradeVolume == 0) afterMarketOvertimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE);
    if(afterMarketOvertimeClosePriceTradeAmount == 0) afterMarketOvertimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE);

	double regularBuyInTradingVolume = ::atof(ACE_CString(rawPacket.regularBuyInTradingVolume, sizeof ( rawPacket.regularBuyInTradingVolume )).c_str());
	double regularBuyInTradingValue = ::atof(ACE_CString(rawPacket.regularBuyInTradingValue, sizeof ( rawPacket.regularBuyInTradingValue )).c_str());

	if(regularBuyInTradingVolume == 0) regularBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    if(regularBuyInTradingValue == 0) regularBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);

	double sameDayBuyInTradingVolume = ::atof(ACE_CString(rawPacket.sameDayBuyInTradingVolume, sizeof ( rawPacket.sameDayBuyInTradingVolume )).c_str());
	double sameDayBuyInTradingValue = ::atof(ACE_CString(rawPacket.sameDayBuyInTradingValue, sizeof ( rawPacket.sameDayBuyInTradingValue )).c_str());

	if(sameDayBuyInTradingVolume == 0) sameDayBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    if(sameDayBuyInTradingValue == 0) sameDayBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);

	double overTimeMarketFixedAccmVolume = ::atof(ACE_CString(rawPacket.overTimeMarketFixedAccmAmount, sizeof ( rawPacket.overTimeMarketFixedAccmAmount )).c_str());
	double overTimeMarketFixedAccmAmount = ::atof(ACE_CString(rawPacket.overTimeMarketFixedAccmAmount, sizeof ( rawPacket.overTimeMarketFixedAccmAmount )).c_str());

	if(overTimeMarketFixedAccmVolume == 0) overTimeMarketFixedAccmVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE);
    if(overTimeMarketFixedAccmAmount == 0) overTimeMarketFixedAccmAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE);

	double manyBulkTradeVolume = ::atof(ACE_CString(rawPacket.manyBulkTradeVolume, sizeof ( rawPacket.manyBulkTradeVolume )).c_str());
	double manyBulkTradeAmount = ::atof(ACE_CString(rawPacket.manyBulkTradeAmount, sizeof ( rawPacket.manyBulkTradeAmount )).c_str());

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

	double gettotalaccmvolume = getTotalAccmVolume(stockCode);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] Check>> accmVolume:[%f],getTotalAccmVolume():[%f]\n" ,getCurrentTimestamp().c_str() , accmVolume, gettotalaccmvolume));

    //if ( accmVolume < getTotalAccmVolume(stockCode) )
	if ( accmVolume < gettotalaccmvolume )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
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

    ACE_CString quotation(rawPacket.realRateQuotationClass, sizeof rawPacket.realRateQuotationClass);

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
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = time(0);
        ACE_OS::memcpy(&trade.symbol, &rawPacket.stockCode, sizeof rawPacket.stockCode);

        trade.openMin = 0;
        trade.highMin = 0;
        trade.lowMin = 0;
        trade.volumeMin = 0;
    }

    trade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    Trade oldVal;
    tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());

#if(1)
printPacketTrade(trade);
#endif

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

    return result;
}
#endif

#if(1)
int InternetKseChannelProcessor::handleRecoveryTotalTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }
	int other_else=0;

    ACE_CString frameId(packet.substr(0, 2));
	ACE_CString dataType(packet.substr(0, 5));

    // log frame count status
    LogFrameCount(frameId);

   	ExturePlusKseRecoveryTotalTrade totalkse;
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseRecoveryTrade kse;
	::memset(&kse, 0x30, sizeof(kse));

	memcpy(kse.stockCode,totalkse.stockCode,sizeof(kse.stockCode));
	memcpy(kse.boardID,totalkse.boardID,sizeof(kse.boardID));
	memcpy(kse.upDown,totalkse.upDown,sizeof(kse.upDown));
	memcpy(kse.gap,totalkse.gap,sizeof(kse.gap));
	memcpy(kse.closePrice,totalkse.closePrice,sizeof(kse.closePrice));
	memcpy(kse.openPrice,totalkse.openPrice,sizeof(kse.openPrice));
	memcpy(kse.highPrice,totalkse.highPrice,sizeof(kse.highPrice));
	memcpy(kse.lowPrice,totalkse.lowPrice,sizeof(kse.lowPrice));
	memcpy(kse.realRateQuotationClass,totalkse.realRateQuotationClass,sizeof(kse.realRateQuotationClass));

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] stockCode:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.stockCode),kse.stockCode ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] boardID  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.boardID),kse.boardID ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] upDown   :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.upDown),kse.upDown ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] gap      :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.gap),kse.gap ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] closePrice:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.closePrice),kse.closePrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] openPrice :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.openPrice),kse.openPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] highPrice :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.highPrice),kse.highPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] lowPrice  :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.lowPrice),kse.lowPrice ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] realRateQuotationClass:[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(kse.realRateQuotationClass),kse.realRateQuotationClass ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] accmTradeVolume       :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(totalkse.accmTradeVolume),totalkse.accmTradeVolume ));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] accmTradeAmount       :[%.*s]\n" ,getCurrentTimestamp().c_str() , sizeof(totalkse.accmTradeAmount),totalkse.accmTradeAmount ));

	ACE_CString boardID(totalkse.boardID, sizeof(totalkse.boardID ));
    ACE_CString sessionID(totalkse.sessionID, sizeof ( totalkse.sessionID ));

	ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
    ACE_CString isNormalstockCode(kse.stockCode, ( sizeof kse.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

	/*
	G2	장개시전종가
	*/
	if(boardID == "G2")
	{
		memcpy(kse.beforeMarketOverTimeClosePriceTradeVolume,totalkse.accmTradeVolume,sizeof(kse.beforeMarketOverTimeClosePriceTradeVolume));
		memcpy(kse.beforeMarketOverTimeClosePriceTradeAmount,totalkse.accmTradeAmount,sizeof(kse.beforeMarketOverTimeClosePriceTradeAmount));

		other_else=100;
	}
	/*
	G1	정규장
	*/
	if(boardID == "G1")
	{
		memcpy(kse.regularMarketTradeVolume,totalkse.accmTradeVolume,sizeof(kse.regularMarketTradeVolume));
		memcpy(kse.regularMarketTradeAmount,totalkse.accmTradeAmount,sizeof(kse.regularMarketTradeAmount));

		other_else=100;
	}
	/*
	G3	장종료후종가
	*/
	if(boardID == "G3")
	{
		memcpy(kse.afterMarketOvertimeClosePriceTradeVolume,totalkse.accmTradeVolume,sizeof(kse.afterMarketOvertimeClosePriceTradeVolume));
		memcpy(kse.afterMarketOvertimeClosePriceTradeAmount,totalkse.accmTradeAmount,sizeof(kse.afterMarketOvertimeClosePriceTradeAmount));

		other_else=100;
	}

	//G7	일반Buy-In	20	단일가	일반 Buy-In 체결수량       
	//G7	일반Buy-In	20	단일가	일반 Buy-In 거래대금       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 체결수량       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 거래대금  

	if(boardID == "G7")
	{
		memcpy(kse.regularBuyInTradingVolume,totalkse.accmTradeVolume,sizeof(kse.regularBuyInTradingVolume));
		memcpy(kse.regularBuyInTradingValue,totalkse.accmTradeAmount,sizeof(kse.regularBuyInTradingValue));

		other_else=100;
	}
	if(boardID == "G8")
	{
		memcpy(kse.sameDayBuyInTradingVolume,totalkse.accmTradeVolume,sizeof(kse.sameDayBuyInTradingVolume));
		memcpy(kse.sameDayBuyInTradingValue,totalkse.accmTradeAmount,sizeof(kse.sameDayBuyInTradingValue));

		other_else=100;
	}

    //G4 시간외단일가누적 체결수량/시간외단일가누적 거래대금(DANIL)
	if(boardID=="G4")
	{
		memcpy(kse.overTimeMarketFixedAccmVolume,totalkse.accmTradeVolume,sizeof(kse.overTimeMarketFixedAccmVolume));
		memcpy(kse.overTimeMarketFixedAccmAmount,totalkse.accmTradeVolume,sizeof(kse.overTimeMarketFixedAccmAmount));

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
		memcpy(kse.manyBulkTradeVolume,totalkse.accmTradeVolume,sizeof(kse.manyBulkTradeVolume));
		memcpy(kse.manyBulkTradeAmount,totalkse.accmTradeVolume,sizeof(kse.manyBulkTradeAmount));

		ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] stockCode:[%s],boardID:[%s],sessionID:[%s],manyBulkTradeVolume:[%.*s],manyBulkTradeAmount:[%.*s]\n" ,getCurrentTimestamp().c_str() , stockCode.c_str() , boardID.c_str(), sessionID.c_str(), sizeof(kse.manyBulkTradeVolume), kse.manyBulkTradeVolume, sizeof(kse.manyBulkTradeAmount), kse.manyBulkTradeAmount));
	}

    if ( isValidSymbol(stockCode) == false )
    {
        //ACE_DEBUG((LM_DEBUG, "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] skip stockCode( %s )\n", getCurrentTimestamp().c_str(), stockCode.c_str()));
        return 0;
    }

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));

    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(kse.upDown, sizeof kse.upDown);
	ACE_CString boardEventID(kse.boardEventID, sizeof ( kse.boardEventID ));

    trade.market = getMarketInRecoveryTrade(boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kse.openPrice, sizeof kse.openPrice).c_str());
    trade.high = atoi(ACE_CString(kse.highPrice, sizeof kse.highPrice).c_str());
    trade.low = atoi(ACE_CString(kse.lowPrice, sizeof kse.lowPrice).c_str());
    trade.close = atoi(ACE_CString(kse.closePrice, sizeof kse.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str());
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


	double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(kse.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( kse.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(kse.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( kse.beforeMarketOverTimeClosePriceTradeAmount )).c_str());

    if(beforeMarketOverTimeClosePriceTradeVolume == 0) beforeMarketOverTimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);
    if(beforeMarketOverTimeClosePriceTradeAmount == 0) beforeMarketOverTimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);

    double regularMarketTradeVolume = ::atof(ACE_CString(kse.regularMarketTradeVolume, sizeof ( kse.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(kse.regularMarketTradeAmount, sizeof ( kse.regularMarketTradeAmount )).c_str());

    if(regularMarketTradeVolume == 0) regularMarketTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_IN);
    if(regularMarketTradeAmount == 0) regularMarketTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_IN);

    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(kse.afterMarketOvertimeClosePriceTradeVolume, sizeof ( kse.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(kse.afterMarketOvertimeClosePriceTradeAmount, sizeof ( kse.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    if(afterMarketOvertimeClosePriceTradeVolume == 0) afterMarketOvertimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE);
    if(afterMarketOvertimeClosePriceTradeAmount == 0) afterMarketOvertimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE);

	double regularBuyInTradingVolume = ::atof(ACE_CString(kse.regularBuyInTradingVolume, sizeof ( kse.regularBuyInTradingVolume )).c_str());
	double regularBuyInTradingValue = ::atof(ACE_CString(kse.regularBuyInTradingValue, sizeof ( kse.regularBuyInTradingValue )).c_str());

	if(regularBuyInTradingVolume == 0) regularBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    if(regularBuyInTradingValue == 0) regularBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);

	double sameDayBuyInTradingVolume = ::atof(ACE_CString(kse.sameDayBuyInTradingVolume, sizeof ( kse.sameDayBuyInTradingVolume )).c_str());
	double sameDayBuyInTradingValue = ::atof(ACE_CString(kse.sameDayBuyInTradingValue, sizeof ( kse.sameDayBuyInTradingValue )).c_str());

	if(sameDayBuyInTradingVolume == 0) sameDayBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    if(sameDayBuyInTradingValue == 0) sameDayBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);

	double overTimeMarketFixedAccmVolume = ::atof(ACE_CString(kse.overTimeMarketFixedAccmAmount, sizeof ( kse.overTimeMarketFixedAccmAmount )).c_str());
	double overTimeMarketFixedAccmAmount = ::atof(ACE_CString(kse.overTimeMarketFixedAccmAmount, sizeof ( kse.overTimeMarketFixedAccmAmount )).c_str());

	if(overTimeMarketFixedAccmVolume == 0) overTimeMarketFixedAccmVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_DANIL_TRADE);
    if(overTimeMarketFixedAccmAmount == 0) overTimeMarketFixedAccmAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_DANIL_TRADE);

	double manyBulkTradeVolume = ::atof(ACE_CString(kse.manyBulkTradeVolume, sizeof ( kse.manyBulkTradeVolume )).c_str());
	double manyBulkTradeAmount = ::atof(ACE_CString(kse.manyBulkTradeAmount, sizeof ( kse.manyBulkTradeAmount )).c_str());

	if(manyBulkTradeVolume == 0) manyBulkTradeVolume = getAccmVolume(stockCode, BOARD_ID_BULK_TRADE_TODAY);
    if(manyBulkTradeAmount == 0) manyBulkTradeAmount = getAccmAmount(stockCode, BOARD_ID_BULK_TRADE_TODAY);


	//1.장개시전시간외종가 체결수량 : beforeMarketOverTimeClosePriceTradeVolume
    //2.정규장체결수량              : regularMarketTradeVolume
    //3.장종료후시간외종가 체결수량 : afterMarketOvertimeClosePriceTradeVolume
    //4.일반 Buy-in 체결수량        : regularBuyInTradingVolume
    //5.당일 Buy-in 체결수량        : sameDayBuyInTradingVolume
    //6.시간외단일가누적 체결수량   : overTimeMarketFixedAccmVolume
	//7.대량 체결수량               : manyBulkTradeVolume
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 1.(G2)장개시전시간외종가 체결수량:[%f]\n" ,getCurrentTimestamp().c_str() , beforeMarketOverTimeClosePriceTradeVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 2.(G1)정규장체결수량             :[%f]\n" ,getCurrentTimestamp().c_str() , regularMarketTradeVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 3.(G3)장종료후시간외종가 체결수량:[%f]\n" ,getCurrentTimestamp().c_str() , afterMarketOvertimeClosePriceTradeVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 4.(G7)일반 Buy-in 체결수량       :[%f]\n" ,getCurrentTimestamp().c_str() , regularBuyInTradingVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 5.(G8)당일 Buy-in 체결수량       :[%f]\n" ,getCurrentTimestamp().c_str() , sameDayBuyInTradingVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 6.(G4)시간외단일가누적 체결수량  :[%f]\n" ,getCurrentTimestamp().c_str() , overTimeMarketFixedAccmVolume));
	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] 7.(B2)(K2)(I2)(B1)(K1)(I1)(B3)(K3)대량 체결수량:[%f]\n" ,getCurrentTimestamp().c_str() , manyBulkTradeVolume));

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

	double gettotalaccmvolume = getTotalAccmVolume(stockCode);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] Check>> accmVolume:[%f],getTotalAccmVolume():[%f]\n" ,getCurrentTimestamp().c_str() , accmVolume, gettotalaccmvolume));

    //if ( accmVolume < getTotalAccmVolume(stockCode) )
	if ( accmVolume < gettotalaccmvolume )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTotalTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
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

    ACE_CString quotation(kse.realRateQuotationClass, sizeof kse.realRateQuotationClass);

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
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = time(0);
        ACE_OS::memcpy(&trade.symbol, &kse.stockCode, sizeof kse.stockCode);

        trade.openMin = 0;
        trade.highMin = 0;
        trade.lowMin = 0;
        trade.volumeMin = 0;
    }

    trade.market = getMarketBasedCurrentTime();

    ACE_CString oldKey;
    Trade oldVal;
    tradeMap_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), trade, oldKey, oldVal, ALLOCATOR::instance());

#if(1)
printPacketTrade(trade);
#endif

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

    return result;
}
#endif

int InternetKseChannelProcessor::handleRecoveryTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] Skip : %s,%d : EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_RECOVERY_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

   	ExturePlusKseRecoveryTotalTrade totalkse;
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseRecoveryTrade kse;
	::memset(&kse, 0x30, sizeof(kse));

	memcpy(kse.stockCode,totalkse.stockCode,sizeof(kse.stockCode));
	memcpy(kse.boardID,totalkse.boardID,sizeof(kse.boardID));
	memcpy(kse.upDown,totalkse.upDown,sizeof(kse.upDown));
	memcpy(kse.gap,totalkse.gap,sizeof(kse.gap));
	memcpy(kse.closePrice,totalkse.closePrice,sizeof(kse.closePrice));
	memcpy(kse.openPrice,totalkse.openPrice,sizeof(kse.openPrice));
	memcpy(kse.highPrice,totalkse.highPrice,sizeof(kse.highPrice));
	memcpy(kse.lowPrice,totalkse.lowPrice,sizeof(kse.lowPrice));
	memcpy(kse.realRateQuotationClass,totalkse.realRateQuotationClass,sizeof(kse.realRateQuotationClass));

	ACE_CString boardID(totalkse.boardID, sizeof(totalkse.boardID ));
    ACE_CString sessionID(totalkse.sessionID, sizeof ( totalkse.sessionID ));

	/*
	G2	장개시전종가	40
	G2	장개시전종가	40
	*/
	if(boardID == "G2" && sessionID == "40")
	{
		memcpy(kse.beforeMarketOverTimeClosePriceTradeVolume,totalkse.accmTradeVolume,sizeof(kse.beforeMarketOverTimeClosePriceTradeVolume));
		memcpy(kse.beforeMarketOverTimeClosePriceTradeAmount,totalkse.accmTradeAmount,sizeof(kse.beforeMarketOverTimeClosePriceTradeAmount));
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
	int ff=0;
	if(boardID == "G1" && sessionID == "10") ff=100;
	if(boardID == "G1" && sessionID == "52") ff=100;
	if(boardID == "G1" && sessionID == "11") ff=100;
	if(boardID == "G1" && sessionID == "53") ff=100;
	if(boardID == "G1" && sessionID == "20") ff=100;
	if(boardID == "G1" && sessionID == "21") ff=100;
	if(boardID == "G1" && sessionID == "30") ff=100;
	if(boardID == "G1" && sessionID == "54") ff=100;
	if(boardID == "G1" && sessionID == "40") ff=100;
	if(boardID == "G1" && sessionID == "50") ff=100;
	if(boardID == "G1" && sessionID == "51") ff=100;
	if(boardID == "G1" && sessionID == "80") ff=100;

	if(ff==100)
	{
		memcpy(kse.regularMarketTradeVolume,totalkse.accmTradeVolume,sizeof(kse.regularMarketTradeVolume));
		memcpy(kse.regularMarketTradeAmount,totalkse.accmTradeAmount,sizeof(kse.regularMarketTradeAmount));
	}
	/*
	G3	장종료후종가	60
	G3	장종료후종가	40
	*/
	ff=0;
	if(boardID == "G3" && sessionID == "60") ff=100;
	if(boardID == "G3" && sessionID == "40") ff=100;

	if(ff==100)
	{
		memcpy(kse.afterMarketOvertimeClosePriceTradeVolume,totalkse.accmTradeVolume,sizeof(kse.afterMarketOvertimeClosePriceTradeVolume));
		memcpy(kse.afterMarketOvertimeClosePriceTradeAmount,totalkse.accmTradeAmount,sizeof(kse.afterMarketOvertimeClosePriceTradeAmount));
	}

	//G7	일반Buy-In	20	단일가	일반 Buy-In 체결수량       
	//G7	일반Buy-In	20	단일가	일반 Buy-In 거래대금       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 체결수량       
	//G8	당일Buy-In	20	단일가	당일 Buy-In 거래대금  
	
    //char regularBuyInTradingVolume[12];                         // 029 일반 Buy-In 체결수량
    //char regularBuyInTradingValue[22];                          // 030 일반 Buy-In 거래대금
    //char sameDayBuyInTradingVolume[12];                         // 031 당일 Buy-In 체결수량
    //char sameDayBuyInTradingValue[22];                          // 032 당일 Buy-In 거래대금

	if(boardID == "G7" && sessionID == "20")
	{
		memcpy(kse.regularBuyInTradingVolume,totalkse.accmTradeVolume,sizeof(kse.regularBuyInTradingVolume));
		memcpy(kse.regularBuyInTradingValue,totalkse.accmTradeAmount,sizeof(kse.regularBuyInTradingValue));
	}

	if(boardID == "G8" && sessionID == "20")
	{
		memcpy(kse.sameDayBuyInTradingVolume,totalkse.accmTradeVolume,sizeof(kse.sameDayBuyInTradingVolume));
		memcpy(kse.sameDayBuyInTradingValue,totalkse.accmTradeAmount,sizeof(kse.sameDayBuyInTradingValue));
	}


    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
    ACE_CString isNormalstockCode(kse.stockCode, ( sizeof kse.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    // 종목코드가 KRA로 시작한다면 ELW 거래원 데이터 + 신주인수권증서 + 신주인수권증권
    // 종목코드가 KR5로 시작한다면 수익증권 거래원 데이터
    // 종목코드가 KR7로 시작한다면 일반주식 + REIT + 선박투자 등등등.
//    if ( ( isNormalstockCode != "KR7" ) && ( isNormalstockCode != "KYG" ) && ( isNormalstockCode != "KR8" ) && ( isNormalstockCode != "HK0" ) && ( isNormalstockCode != "USU" ) && ( isNormalstockCode != "KRG" ) )
//    {
//        // ACE_DEBUG((LM_DEBUG, "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] skip stockCode( %s )\n", getCurrentTimestamp().c_str(), stockCode.c_str()));
//        return 0;
//    }

    if ( isValidSymbol(stockCode) == false )
    {
        //ACE_DEBUG((LM_DEBUG, "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] skip stockCode( %s )\n", getCurrentTimestamp().c_str(), stockCode.c_str()));
        return 0;
    }

    // 구스펙 장구분코드
    // 신스펙 정규시간외구분코드
    //ACE_CString boardID(kse.boardID, sizeof ( kse.boardID ));
    ACE_CString boardEventID(kse.boardEventID, sizeof ( kse.boardEventID ));

    Trade trade;
    ::memset(&trade, 0, sizeof(Trade));

    TickFilter filter;

    int hasValue = tradeMap_->find(stockCode, trade, ALLOCATOR::instance());

    ACE_CString upDown(kse.upDown, sizeof kse.upDown);
    trade.market = getMarketInRecoveryTrade(boardID, boardEventID);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kse.openPrice, sizeof kse.openPrice).c_str());
    trade.high = atoi(ACE_CString(kse.highPrice, sizeof kse.highPrice).c_str());
    trade.low = atoi(ACE_CString(kse.lowPrice, sizeof kse.lowPrice).c_str());
    trade.close = atoi(ACE_CString(kse.closePrice, sizeof kse.closePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str());
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
	const ACE_CString BOARD_ID_BULK_TRADE_TODAY("ZZ");

	const ACE_CString BOARD_ID_MARKET_REGULARBUYIN_TRADE("G7");
	const ACE_CString BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE("G8");


	double beforeMarketOverTimeClosePriceTradeVolume = ::atof(ACE_CString(kse.beforeMarketOverTimeClosePriceTradeVolume, sizeof ( kse.beforeMarketOverTimeClosePriceTradeVolume )).c_str());
    double beforeMarketOverTimeClosePriceTradeAmount = ::atof(ACE_CString(kse.beforeMarketOverTimeClosePriceTradeAmount, sizeof ( kse.beforeMarketOverTimeClosePriceTradeAmount )).c_str());

    if(beforeMarketOverTimeClosePriceTradeVolume == 0) beforeMarketOverTimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);
    if(beforeMarketOverTimeClosePriceTradeAmount == 0) beforeMarketOverTimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_BEFORE_TRADE);

    double regularMarketTradeVolume = ::atof(ACE_CString(kse.regularMarketTradeVolume, sizeof ( kse.regularMarketTradeVolume )).c_str());
    double regularMarketTradeAmount = ::atof(ACE_CString(kse.regularMarketTradeAmount, sizeof ( kse.regularMarketTradeAmount )).c_str());

    if(regularMarketTradeVolume == 0) regularMarketTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_IN);
    if(regularMarketTradeAmount == 0) regularMarketTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_IN);

    double afterMarketOvertimeClosePriceTradeVolume = ::atof(ACE_CString(kse.afterMarketOvertimeClosePriceTradeVolume, sizeof ( kse.afterMarketOvertimeClosePriceTradeVolume )).c_str());
    double afterMarketOvertimeClosePriceTradeAmount = ::atof(ACE_CString(kse.afterMarketOvertimeClosePriceTradeAmount, sizeof ( kse.afterMarketOvertimeClosePriceTradeAmount )).c_str());

    if(afterMarketOvertimeClosePriceTradeVolume == 0) afterMarketOvertimeClosePriceTradeVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_AFTER_TRADE);
    if(afterMarketOvertimeClosePriceTradeAmount == 0) afterMarketOvertimeClosePriceTradeAmount = getAccmAmount(stockCode, BOARD_ID_MARKET_AFTER_TRADE);

	double regularBuyInTradingVolume = ::atof(ACE_CString(kse.regularBuyInTradingVolume, sizeof ( kse.regularBuyInTradingVolume )).c_str());
	double regularBuyInTradingValue = ::atof(ACE_CString(kse.regularBuyInTradingValue, sizeof ( kse.regularBuyInTradingValue )).c_str());

	if(regularBuyInTradingVolume == 0) regularBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);
    if(regularBuyInTradingValue == 0) regularBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_REGULARBUYIN_TRADE);

	double sameDayBuyInTradingVolume = ::atof(ACE_CString(kse.sameDayBuyInTradingVolume, sizeof ( kse.sameDayBuyInTradingVolume )).c_str());
	double sameDayBuyInTradingValue = ::atof(ACE_CString(kse.sameDayBuyInTradingValue, sizeof ( kse.sameDayBuyInTradingValue )).c_str());

	if(sameDayBuyInTradingVolume == 0) sameDayBuyInTradingVolume = getAccmVolume(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);
    if(sameDayBuyInTradingValue == 0) sameDayBuyInTradingValue = getAccmAmount(stockCode, BOARD_ID_MARKET_SAMEDAYBUYIN_TRADE);

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

#if(0)
    double accmVolume = ::atof(ACE_CString(kse.accmTradeVolume, sizeof kse.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kse.accmTradeAmount, sizeof kse.accmTradeAmount).c_str());

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

    ExturePlusKseRecoveryTradeFixed rawTradeFixed;
    ::memset(&rawTradeFixed, 0, sizeof(ExturePlusKseRecoveryTradeFixed));
    int hasValueTradeFixed = tradeFixedMapKse_->find(stockCode, rawTradeFixed, ALLOCATOR::instance());
    if ( hasValueTradeFixed == -1 )
    {
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] stockCode:[%s]\thasValueTradeFixed:[%d] == -1 \n" , getCurrentTimestamp().c_str() , stockCode.c_str() , hasValueTradeFixed ));
    }
    else
    {
        ACE_CString strTotalAccmVolume(rawTradeFixed.totalAccmVolume, sizeof ( rawTradeFixed.totalAccmVolume ));
        double totalAccmVolume = parseDouble(strTotalAccmVolume, 0);
        ACE_CString strTotalAccmAmount(rawTradeFixed.totlaAccmAmount, sizeof ( rawTradeFixed.totlaAccmAmount ));
        double totalAccmAmount = parseDouble(strTotalAccmAmount, 0);

        double etcAccmVolume = totalAccmVolume - accmVolume;
        double etcAccmAmount = totalAccmAmount - accmAmount;

        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] stockCode:[%s]\tetcAccmVolume:[%f]\taccmVolume:[%f]\ttotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , etcAccmVolume , accmVolume , totalAccmVolume ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] stockCode:[%s]\tetcAccmAmount:[%f]\ttotalAccmAmount:[%f]\taccmAmount:[%f]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , etcAccmAmount , accmAmount , totalAccmAmount ));

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
#endif

#if(1)
	//1.장개시전시간외종가 체결수량 : beforeMarketOverTimeClosePriceTradeVolume
    //2.정규장체결수량              : regularMarketTradeVolume
    //3.장종료후시간외종가 체결수량 : afterMarketOvertimeClosePriceTradeVolume
    //4.일반 Buy-in 체결수량        : regularBuyInTradingVolume
    //5.당일 Buy-in 체결수량        : sameDayBuyInTradingVolume
    //6.시간외단일가누적 체결수량   : rawTradeFixed.overTimeMarketFixedAccmVolume

    //7.B2	장개시전대량	kBloxVolumeInPreMarketTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_B2);
    //7.K2	장개시전대량바스켓	basketTradingVolumeInPreMarketTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_K2);
    //7.I2	장개시전경쟁대량	aBloxVolumeInPreMarketTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_PRE_OFF_HOURS_SESSION_I2);
    //7.B1	장중대량	kBloxVolumeInRegularTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_B1);
    //7.K1	장중대량바스켓	basketTradingVolumeInRegularTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_K1);
    //7.I1	장중경쟁대량	aBloxVolumeInRegularTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_REGULAR_SESSION_I1);
    //7.B3	장종료후대량	kBloxVolumeInPostMarketTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_POST_OFF_HOURS_SESSION_B3);
    //7.K3	장종료후대량바스켓	basketTradingVolumeInPostMarketTradingHoursSession	getAccmVolume(issueCode, BOARD_ID_POST_OFF_HOURS_SESSION_K3);

    //1.장개시전시간외종가 거래대금 : beforeMarketOverTimeClosePriceTradeAmount
    //2.정규장거래대금              : regularMarketTradeAmount
    //3.장종료후시간외종가 거래대금 : afterMarketOvertimeClosePriceTradeAmount
    //4.일반 Buy-in 거래대금        : regularBuyInTradingValue
    //5.당일 Buy-in 거래대금        : sameDayBuyInTradingValue
    //6.시간외단일가누적 거래대금   : rawTradeFixed.overTimeMarketFixedAccmAmount

    double accmVolume = 0;
    double accmAmount = 0;

	accmVolume = accmVolume + beforeMarketOverTimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularMarketTradeVolume;
	accmVolume = accmVolume + afterMarketOvertimeClosePriceTradeVolume;
	accmVolume = accmVolume + regularBuyInTradingVolume;
	accmVolume = accmVolume + sameDayBuyInTradingVolume;

	accmAmount = accmAmount + beforeMarketOverTimeClosePriceTradeAmount;
	accmAmount = accmAmount + regularMarketTradeAmount;
	accmAmount = accmAmount + regularBuyInTradingValue;
	accmAmount = accmAmount + sameDayBuyInTradingValue;

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

    ExturePlusKseRecoveryTradeFixed rawTradeFixed;
    ::memset(&rawTradeFixed, 0, sizeof(ExturePlusKseRecoveryTradeFixed));
    int hasValueTradeFixed = tradeFixedMapKse_->find(stockCode, rawTradeFixed, ALLOCATOR::instance());

    if ( hasValueTradeFixed == -1 )
    {
		//
    }
    else
    {
        ACE_CString overTimeMarketFixedAccmVolume(rawTradeFixed.overTimeMarketFixedAccmVolume, sizeof ( rawTradeFixed.overTimeMarketFixedAccmVolume ));
		accmVolume = accmVolume + parseDouble(overTimeMarketFixedAccmVolume, 0);
        ACE_CString overTimeMarketFixedAccmAmount(rawTradeFixed.overTimeMarketFixedAccmAmount, sizeof ( rawTradeFixed.overTimeMarketFixedAccmAmount ));
		accmAmount = accmAmount + parseDouble(overTimeMarketFixedAccmAmount, 0);
    }
#endif

    if ( accmVolume < getTotalAccmVolume(stockCode) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTrade] Skip : %s,%d : net volume error stockCode:[%s] accmVolume:[%f] getTotalAccmVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , stockCode.c_str() , accmVolume , getTotalAccmVolume(stockCode) ), -1);
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

    ACE_CString quotation(kse.realRateQuotationClass, sizeof kse.realRateQuotationClass);

    if ( frameId == "B1" )
    {
        trade.subtype = TRADESUBTYPE_CLOSE;
    }
    else if ( quotation == "2" )
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
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_STOCK;
        trade.decimalPoint = DECIMAL_0;
        trade.tradeTime = time(0);
        ACE_OS::memcpy(&trade.symbol, &kse.stockCode, sizeof kse.stockCode);

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
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

    return result;
}

int InternetKseChannelProcessor::handleUpDown(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_UPDOWN_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleUpDown] Skip : %s,%d : EXTURE_PLUS_KSE_UPDOWN_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_UPDOWN_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseUpDown kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    UpDown upDown;
    upDown.exchange = EXCHANGE_KSE;
    upDown.symbolType = SYMBOL_STOCK;

    ACE_CString stockCode = getIndexSymbol(1);
    ACE_OS::memcpy(&upDown.symbol, stockCode.c_str(), stockCode.length());

    upDown.totalCount = atoi(ACE_CString(kse.totalStockSize, sizeof kse.totalStockSize).c_str());
    upDown.tradeCount = atoi(ACE_CString(kse.tradeFormationStockSize, sizeof kse.tradeFormationStockSize).c_str());
    upDown.upCount = atoi(ACE_CString(kse.upStockSize, sizeof kse.upStockSize).c_str());
    upDown.upLimitCount = atoi(ACE_CString(kse.upLimitStockSize, sizeof kse.upLimitStockSize).c_str());

    upDown.downCount = atoi(ACE_CString(kse.downStockSize, sizeof kse.downStockSize).c_str());
    upDown.downLimitCount = atoi(ACE_CString(kse.downLimitStockSize, sizeof kse.downLimitStockSize).c_str());
    upDown.stationaryCount = atoi(ACE_CString(kse.sattionaryStockSize, sizeof kse.sattionaryStockSize).c_str());

    upDown.quotationCount = atoi(ACE_CString(kse.quotationStockSize, sizeof kse.quotationStockSize).c_str());
    upDown.quotationUpCount = atoi(ACE_CString(kse.quotationUpStockSize, sizeof kse.quotationUpStockSize).c_str());
    upDown.quotationDownCount = atoi(ACE_CString(kse.quotationDownStockSize, sizeof kse.quotationDownStockSize).c_str());

    // 구스펙 : 총거래량, 총거래대금
    // 신스펙 : X
    // DBWriter ShmWriter 사용하지 않음. 임시값으로 대치한다.
    upDown.accmVolume = 0.0;
    upDown.accmAmount = 0.0;
    upDown.registerDt = getRegisterDt();
    upDown.market = MARKET_IN;

    char buf[UPDOWN_SIZE];
    memcpy(buf, &upDown, UPDOWN_SIZE);
    int result = sendPacket(ACE_CString(buf, UPDOWN_SIZE), PACKET_UPDOWN, EXCHANGE_KSE);

#if(0)
printPacketUpDown(upDown);
#endif

    return result;
}

int InternetKseChannelProcessor::getRegisterDt()
{
    time_t registerDt = ::time(0);
    struct tm tmRegisterDt = *::localtime(&registerDt);
    registerDt = ::mktime(&tmRegisterDt);
    return registerDt;
}

int InternetKseChannelProcessor::getRegisterDt(const ACE_CString &imsiTime)
{
    time_t registerDt = ::time(0);
    struct tm tmRegisterDt = *::localtime(&registerDt);

    if ( ( imsiTime == "DKAM" ) || ( imsiTime == "DKTM" ) )
    {
        tmRegisterDt.tm_hour = 18;
        tmRegisterDt.tm_min = 0;
        tmRegisterDt.tm_sec = 0;
    }
    else
    {
        // 오늘날짜 해당시간 
        tmRegisterDt.tm_hour = atoi(imsiTime.substr(0, 2).c_str());
        tmRegisterDt.tm_min = atoi(imsiTime.substr(2, 4).c_str());
        tmRegisterDt.tm_sec = 0;
    }
    registerDt = ::mktime(&tmRegisterDt);
    return registerDt;
}

int InternetKseChannelProcessor::handleIndexForecast(const ACE_CString &packet)
{
	if ( EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE != static_cast<int>(packet.length()) )
	{
		ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleIndexForecast] Skip : %s, %d : EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
	}

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusTotalKseIndex totalkse;
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseIndex kse;

	::memcpy(kse.time, totalkse.time, sizeof(kse.time));
	::memcpy(kse.index, totalkse.index, sizeof(kse.index));
	::memcpy(kse.sign, totalkse.sign, sizeof(kse.sign));
	::memcpy(kse.gap, totalkse.gap, sizeof(kse.gap));
	::memcpy(kse.tradeVolume, totalkse.tradeVolume, sizeof(kse.tradeVolume));
	::memcpy(kse.tradeAmount, totalkse.tradeAmount, sizeof(kse.tradeAmount));

	ACE_DEBUG( ( LM_DEBUG , "[%s]//EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d],[%d]\n" , getCurrentTimestamp().c_str(),
		EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE,
		packet.length()
		));
	ACE_DEBUG( ( LM_DEBUG , "[%s]//[%.*s],[%.*s],[%.*s],[%.*s],[%.*s],[%.*s]\n" , getCurrentTimestamp().c_str(),
		sizeof(kse.time),kse.time,
		sizeof(kse.index),kse.index,
		sizeof(kse.sign),kse.sign,
		sizeof(kse.gap),kse.gap,
		sizeof(kse.tradeVolume),kse.tradeVolume,
		sizeof(kse.tradeAmount),kse.tradeAmount
		));

#if(0)
	Trade trade;
    ACE_CString frameId = packet.substr(0, 2);

    int index = atoi(ACE_CString(kse.businessTypeCode, sizeof kse.businessTypeCode).c_str());
#endif
#if(1)
	Trade trade;

	ACE_CString businesstypecode(totalkse.dataID, sizeof ( totalkse.dataID ));
	ACE_CString frameId(totalkse.dataID, sizeof ( totalkse.dataID ));

    int index = atoi(getSymbolUpCode(businesstypecode).c_str());
	frameId = getSymbolFrameId(frameId);
#endif

    ACE_CString symbol = getIndexSymbol(index, frameId);
    int hasValue = tradeMap_->find(symbol, trade, ALLOCATOR::instance());

    // common
    ACE_CString upDown(kse.sign, 1);
    ACE_CString volume(kse.tradeVolume, sizeof ( kse.tradeVolume ));
    trade.market = getMarketStepInIndex(ACE_CString(kse.time, sizeof ( kse.time )));
    trade.upDown = getUpDownInIndex(upDown);
    trade.accmVolume = atof(volume.c_str());
    trade.amount = atof(ACE_CString(kse.tradeAmount, sizeof kse.tradeAmount).c_str());

#if(1)
    trade.close = atoi(ACE_CString(kse.index, sizeof kse.index).c_str()) * 100;
    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str()) * 100;
#endif

    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }
    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    // 예상지수에서는 상황에 따라 체결이 빠지는 경우도 있으므로, 단위 체결량을 산출할 수 없다.
    // 따라서, 누적체결량을 단위체결량으로 강제 할당 한다. 
    trade.tradeVolume = trade.accmVolume;
    int tickTime = getTickTime(ACE_CString(kse.time, sizeof kse.time), frameId);

    if ( trade.tradeVolume == -1 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleIndexForecast] Skip : %s,%d : net volume error symbol:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , symbol.c_str() , trade.tradeVolume ), -1);
    }

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_INDEX;
        trade.decimalPoint = DECIMAL_2;
        trade.tradeTime = tickTime;

        memcpy(&trade.symbol, symbol.c_str(), sizeof trade.symbol);

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

        if ( ( tickTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
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
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIndexForecast] dataClass:[%.*s],infoMarketClass:[%.*s],dataID:[%.*s],standardCode:[%.*s],symbol:[%s]\tresult:[%d]\n" , 
		getCurrentTimestamp().c_str(), 
		sizeof(totalkse.dataClass),totalkse.dataClass, 
		sizeof(totalkse.infoMarketClass),totalkse.infoMarketClass, 
		sizeof(totalkse.dataID),totalkse.dataID, 
		sizeof(totalkse.standardCode),totalkse.standardCode, 
		symbol.c_str() , 
		result ));

#if(1)
printPacketTrade(trade);
#endif

    return result;
}

#if(1)
int InternetKseChannelProcessor::handleCustomIndexRecovery(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleCustomIndexRecovery] packet.length()[%d],packet:[%s]\n" , getCurrentTimestamp().c_str() , packet.length(), packet.c_str() ));
    return 0;
}
#endif

int InternetKseChannelProcessor::handleIndex(const ACE_CString &packet)
{
	if ( EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE != static_cast<int>(packet.length()) )
	{
		ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleIndexForecast] Skip : %s, %d : EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
	}
    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

	ExturePlusTotalKseIndex totalkse;
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseIndex kse;

	::memcpy(kse.time, totalkse.time, sizeof(kse.time));
	::memcpy(kse.index, totalkse.index, sizeof(kse.index));
	::memcpy(kse.sign, totalkse.sign, sizeof(kse.sign));
	::memcpy(kse.gap, totalkse.gap, sizeof(kse.gap));
	::memcpy(kse.tradeVolume, totalkse.tradeVolume, sizeof(kse.tradeVolume));
	::memcpy(kse.tradeAmount, totalkse.tradeAmount, sizeof(kse.tradeAmount));

	ACE_DEBUG( ( LM_DEBUG , "[%s]//EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d],[%d]\n" , getCurrentTimestamp().c_str(),
		EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE,
		packet.length()
		));
	ACE_DEBUG( ( LM_DEBUG , "[%s]//[%.*s],[%.*s],[%.*s],[%.*s],[%.*s],[%.*s]\n" , getCurrentTimestamp().c_str(),
		sizeof(kse.time),kse.time,
		sizeof(kse.index),kse.index,
		sizeof(kse.sign),kse.sign,
		sizeof(kse.gap),kse.gap,
		sizeof(kse.tradeVolume),kse.tradeVolume,
		sizeof(kse.tradeAmount),kse.tradeAmount
		));

#if(0)
	Trade trade;
    ACE_CString frameId = packet.substr(0, 2);

    int index = atoi(ACE_CString(kse.businessTypeCode, sizeof kse.businessTypeCode).c_str());
#endif
#if(1)
	Trade trade;

	ACE_CString businesstypecode(totalkse.dataID, sizeof ( totalkse.dataID ));
	ACE_CString frameId(totalkse.dataID, sizeof ( totalkse.dataID ));

    int index = atoi(getSymbolUpCode(businesstypecode).c_str());
	frameId = getSymbolFrameId(frameId);
#endif




    ACE_CString symbol = getIndexSymbol(index, frameId);

    int hasValue = tradeMap_->find(symbol, trade, ALLOCATOR::instance());

    // common
    ACE_CString upDown(kse.sign, 1);
    ACE_CString volume(kse.tradeVolume, sizeof ( kse.tradeVolume ));
    trade.market = getMarketStepInIndex(ACE_CString(kse.time, sizeof ( kse.time )));
    trade.upDown = getUpDownInIndex(upDown);
    trade.accmVolume = atof(volume.c_str());
    trade.amount = atof(ACE_CString(kse.tradeAmount, sizeof kse.tradeAmount).c_str());

#if(1)
    trade.close = atoi(ACE_CString(kse.index, sizeof kse.index).c_str()) * 100;
    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str()) * 100;
#endif

    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;
    trade.tradeVolume = trade.accmVolume - getTotalAccmVolume(symbol);

    int tickTime = getTickTime(ACE_CString(kse.time, sizeof kse.time), frameId);

    if ( trade.tradeVolume == -1 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleIndex] Skip : %s,%d : net volume error symbol:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , symbol.c_str() , trade.tradeVolume ), -1);
    }

    setTotalAccmVolume(symbol, trade.accmVolume);
    setTotalAccmAmount(symbol, trade.amount);

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_INDEX;
        trade.decimalPoint = DECIMAL_2;
        trade.tradeTime = tickTime;

        memcpy(&trade.symbol, symbol.c_str(), sizeof trade.symbol);

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

        if ( ( tickTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
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
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIndex] dataClass:[%.*s],infoMarketClass:[%.*s],dataID:[%.*s],standardCode:[%.*s],symbol:[%s]\tresult:[%d]\n" , 
		getCurrentTimestamp().c_str(), 
		sizeof(totalkse.dataClass),totalkse.dataClass, 
		sizeof(totalkse.infoMarketClass),totalkse.infoMarketClass, 
		sizeof(totalkse.dataID),totalkse.dataID, 
		sizeof(totalkse.standardCode),totalkse.standardCode, 
		symbol.c_str() , 
		result ));

#if(1)
printPacketTrade(trade);
#endif

    return result;
}

int InternetKseChannelProcessor::handleEquallyWeightedIndex(const ACE_CString &packet)
{
	if ( EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE != static_cast<int>(packet.length()) )
	{
		ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleEquallyWeightedIndex] Skip : %s, %d : EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
	}
    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

	ExturePlusTotalKseIndex totalkse;
	::memset(&totalkse, 0, sizeof(ExturePlusTotalKseIndex));
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseIndex rawData;
    ::memset(&rawData, 0, sizeof(ExturePlusKseIndex));

	::memcpy(rawData.time, totalkse.time, sizeof(rawData.time));
	::memcpy(rawData.index, totalkse.index, sizeof(rawData.index));
	::memcpy(rawData.sign, totalkse.sign, sizeof(rawData.sign));
	::memcpy(rawData.gap, totalkse.gap, sizeof(rawData.gap));
	::memcpy(rawData.tradeVolume, totalkse.tradeVolume, sizeof(rawData.tradeVolume));
	::memcpy(rawData.tradeAmount, totalkse.tradeAmount, sizeof(rawData.tradeAmount));

    return 0;
}

int InternetKseChannelProcessor::handleEquallyWeightedIndexForecast(const ACE_CString &packet)
{
	if ( EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE != static_cast<int>(packet.length()) )
	{
		ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleEquallyWeightedIndexForecast] Skip : %s, %d : EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
	}

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusTotalKseIndex totalkse;
	::memset(&totalkse, 0, sizeof(ExturePlusTotalKseIndex));
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseIndex rawData;
    ::memset(&rawData, 0, sizeof(ExturePlusKseIndex));

	::memcpy(rawData.time, totalkse.time, sizeof(rawData.time));
	::memcpy(rawData.index, totalkse.index, sizeof(rawData.index));
	::memcpy(rawData.sign, totalkse.sign, sizeof(rawData.sign));
	::memcpy(rawData.gap, totalkse.gap, sizeof(rawData.gap));
	::memcpy(rawData.tradeVolume, totalkse.tradeVolume, sizeof(rawData.tradeVolume));
	::memcpy(rawData.tradeAmount, totalkse.tradeAmount, sizeof(rawData.tradeAmount));

    return 0;
}

int InternetKseChannelProcessor::handleForeignerMaster(const ACE_CString &packet)
{
    // for debug
    time_t timeEnter = ::time(0);
    struct tm tmEnter = *::localtime(&timeEnter);

    if ( EXTURE_PLUS_KSE_FOREIGNER_MASTER_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleForeignerMaster] Skip : %s, %d : EXTURE_PLUS_KSE_FOREIGNER_MASTER_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_FOREIGNER_MASTER_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseForeignerMaster kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    ForeignerMaster master;
    ::memset(&master, 0, sizeof(ForeignerMaster));

    master.exchange = getExchange(kse.infoMarketClass[2]);
    master.symbolType = getSymbolType(kse.infoMarketClass[2]);

    if ( master.symbolType == 255 )
    {
        return 0;
    }

    // 마지막 레코드 스킵.
    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
    if ( ( stockCode == "999999999999" ) || ( stockCode == "000000000000" ) )
    {
        return 0;
    }

    std::string stockCodeTrimed(stockCode.c_str());
    boost::trim(stockCodeTrimed);
    if ( stockCodeTrimed == std::string("") )
    {
        return 0;
    }

    ACE_OS::memcpy(&master.symbol, &kse.stockCode, sizeof kse.stockCode);
    master.serial = atoi(ACE_CString(kse.serialNo, sizeof kse.serialNo).c_str());
    master.symbolLimitRate = atoi(ACE_CString(kse.stockLimitRate, sizeof kse.stockLimitRate).c_str());
    master.individualLimitRate = atoi(ACE_CString(kse.individualLimitRate, sizeof kse.individualLimitRate).c_str());

    // 한도수량 = 상장주식수 *  종목한도비율 / 10000 (10000으로 나눠진 이유는 종목한도비율값을 백분율값으로 나타내기 위해서 10000으로 나눠준다.)
    // master.limitVolume = atof(ACE_CString(kse.listingStockSize,sizeof kse.listingStockSize).c_str()) * atof(ACE_CString(kse.stockLimitRate,sizeof kse.stockLimitRate).c_str()) / (float)10000;
    // 위의 구문을 아래와 같이 변경함
    double listingStockSize = atof(ACE_CString(kse.listingStockSize, sizeof kse.listingStockSize).c_str());
    double stockLimitRate = atof(ACE_CString(kse.stockLimitRate, sizeof kse.stockLimitRate).c_str());
    double limitVolume = listingStockSize * stockLimitRate / 10000.0;
    master.limitVolume = limitVolume;

    master.exhaust = getExhaustInForeigner(ACE_CString(kse.limitExhaustClass, sizeof kse.limitExhaustClass));

    // 구스펙 : 주문가능 수량 부호
    // 신스펙 : X
    // DBWriter 확인 결과 사용하지 않음. 우선 플러스 기호로 처리한다.
    // master.orderLimitSign = getSign(ACE_CString(kse.orderPossibilityVolumeSign,sizeof kse.orderPossibilityVolumeSign)) ;
    master.orderLimitSign = SIGN_PLUS;

    master.orderLimitVolume = atof(ACE_CString(kse.orderPossibilityVolume, sizeof kse.orderPossibilityVolume).c_str());
    master.listSize = atof(ACE_CString(kse.listingStockSize, sizeof ( kse.listingStockSize )).c_str());

    char buf[FOREIGNER_MASTER_SIZE];
    memcpy(buf, &master, FOREIGNER_MASTER_SIZE);
    int result = sendPacket(ACE_CString(buf, FOREIGNER_MASTER_SIZE), PACKET_FOREIGNER_MASTER, getExchange(kse.infoMarketClass[2]));

#if(1)
printPacketForeignerMaster(master);
#endif

    return result;
}

int InternetKseChannelProcessor::handleForeignerMasterUpdate(const ACE_CString &packet)
{
    // for debug
    time_t timeEnter = ::time(0);
    struct tm tmEnter = *::localtime(&timeEnter);
    if ( EXTURE_PLUS_KSE_FOREIGNER_MASTER_UPDATE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleForeignerMasterUpdate] Skip : %s, %d : EXTURE_PLUS_KSE_FOREIGNER_MASTER_UPDATE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_FOREIGNER_MASTER_UPDATE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseForeignerMasterUpdate kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    ForeignerMaster master;
    ::memset(&master, 0, sizeof(ForeignerMaster));

    master.exchange = getExchange(kse.infoMarketClass[2]);
    master.symbolType = getSymbolType(kse.infoMarketClass[2]);

    if ( master.symbolType == 255 )
    {
        return 0;
    }

    ACE_OS::memcpy(&master.symbol, &kse.stockCode, sizeof kse.stockCode);
    master.serial = 1;
    master.symbolLimitRate = atoi(ACE_CString(kse.stockLimitRate, sizeof kse.stockLimitRate).c_str());
    master.individualLimitRate = atoi(ACE_CString(kse.individualLimitRate, sizeof kse.individualLimitRate).c_str());
    master.exhaust = getExhaustInForeigner(ACE_CString(kse.limitExhaustClass, sizeof kse.limitExhaustClass));
    master.orderLimitSign = SIGN_PLUS;
    master.orderLimitVolume = atof(ACE_CString(kse.orderPossibilityVolume, sizeof kse.orderPossibilityVolume).c_str());
    master.listSize = atof(ACE_CString(kse.listingStockSize, sizeof ( kse.listingStockSize )).c_str());
    master.limitVolume = master.listSize * master.symbolLimitRate / 10000;

    char buf[FOREIGNER_MASTER_SIZE];
    memcpy(buf, &master, FOREIGNER_MASTER_SIZE);
    int result = sendPacket(ACE_CString(buf, FOREIGNER_MASTER_SIZE), PACKET_FOREIGNER_MASTER, getExchange(kse.infoMarketClass[2]));

    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);

#if(0)
printPacketForeignerMaster(master);
#endif

    return result;
}

int InternetKseChannelProcessor::handleForeigner(const ACE_CString &packet)
{
    // for debug
    time_t timeEnter = ::time(0);
    struct tm tmEnter = *::localtime(&timeEnter);

    if ( EXTURE_PLUS_KSE_FOREIGNER_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleForeigner] Skip : %s, %d : EXTURE_PLUS_KSE_FOREIGNER_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_FOREIGNER_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseForeigner kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    ACE_CString marketClass(kse.marketClass, sizeof kse.marketClass);
    if ( ( marketClass != "1" ) && ( marketClass != "2" ) )
    {
        return 0;
    }

    Foreigner foreigner;
    ::memset(&foreigner, 0, sizeof(Foreigner));

    foreigner.subtype = SYMBOL_STOCK;
    foreigner.decimalPoint = DECIMAL_0;
    ACE_OS::memcpy(&foreigner.symbol, &kse.stockCode, sizeof kse.stockCode);

    // 신스펙은 양수만 존재 하므로 SIGN_PLUS 값으로 대치한다. 
    foreigner.orderLimitSign = SIGN_PLUS;
    foreigner.orderLimitVolume = atof(ACE_CString(kse.orderPossibilityVolume, sizeof kse.orderPossibilityVolume).c_str());

    char buf[FOREIGNER_SIZE];
    memcpy(buf, &foreigner, FOREIGNER_SIZE);
    int result = sendPacket(ACE_CString(buf, FOREIGNER_SIZE), PACKET_FOREIGNER, getExchange(kse.marketClass[0]));
    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);

#if(0)
printPacketForeigner(foreigner);
#endif

    return result;
}

int InternetKseChannelProcessor::handleQuote10(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_QUOTE10_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleQuote10] Skip : %s, %d : EXTURE_PLUS_KSE_QUOTE10_SIZE[%d] != packet.length()[%d] packet:[%s] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_QUOTE10_SIZE , packet.length() , packet.c_str() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseQuote10 kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
    ACE_CString isNormalstockCode(kse.stockCode, ( sizeof kse.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    if ( isValidSymbol(stockCode) == false )
    {
        //ACE_DEBUG((LM_DEBUG, "[%s] [InternetKseChannelProcessor::handleQuote10] skip stockCode( %s )\n", getCurrentTimestamp().c_str(), stockCode.c_str()));
        return 0;
    }

    ACE_CString boardID(kse.boardID, sizeof kse.boardID);
    ACE_CString sessionID(kse.sessionID, sizeof kse.sessionID);

    /*
     * 정규시간외구분코드가 7(일반바이인), 8(당일바이인) 인 경우 skip 한다.
     * 코드값모음집(20131010)
     * ==> 일반 바이인(G7)
     * ==> 당일 바이인(G8)
     */

    if ( ( boardID == "G7" ) || ( boardID == "G8" ) )
    {
        return 0;
    }
    // 바이인 세션 ID ==> 25
    if ( sessionID == "25" )
    {
        return 0;
    }

#if(0)
    // 세션ID / 70:시간외단일가
    // 보드ID / 장종료후시간외단일가(G4)
    if ( ( sessionID == "70" ) || ( boardID == "G4" ) )
    {
        return handleQuote10Fixed(packet);
    }
#endif
#if(1)
    // 보드ID / 장종료후시간외단일가(G4)
    if ( ( boardID == "G4" ) )
    {
        return handleQuote10Fixed(packet);
    }
#endif

    Quote10 quote;
    quote.exchange = EXCHANGE_KSE;
    quote.symbolType = SYMBOL_STOCK;
    quote.decimalPoint = 0;

    ACE_OS::memcpy(&quote.symbol, stockCode.c_str(), sizeof quote.symbol);

    quote.concurrent = getConcurrent(boardID, sessionID);

    // 구스펙 장종료후시간외 값을 처리하기 위해 getMarketInQuote10 함수 매개변수 갯수 변경.
    quote.market = getMarketInQuote10(boardID, sessionID);

    quote.quoteTime = time(0);

    quote.totalAskVolume = atof(ACE_CString(kse.totalAskQuoteRemainder, sizeof kse.totalAskQuoteRemainder).c_str());
    quote.totalBidVolume = atof(ACE_CString(kse.totalBidQuoteRemainder, sizeof kse.totalBidQuoteRemainder).c_str());

    quote.expectedPrice = atoi(ACE_CString(kse.estimatedTradePrice, sizeof kse.estimatedTradePrice).c_str());
    quote.expectedVolume = atof(ACE_CString(kse.estimatedTradeVolume, sizeof kse.estimatedTradeVolume).c_str());

    for ( int i = 0 ; i < 10 ; ++i )
    {
        quote.rec[i].ask = atoi(ACE_CString(kse.rec[i].askQuote, sizeof kse.rec[i].askQuote).c_str());
        quote.rec[i].askVolume = atoi(ACE_CString(kse.rec[i].askQuoteVolume, sizeof kse.rec[i].askQuoteVolume).c_str());
        quote.rec[i].bid = atoi(ACE_CString(kse.rec[i].bidQuote, sizeof kse.rec[i].bidQuote).c_str());
        quote.rec[i].bidVolume = atoi(ACE_CString(kse.rec[i].bidQuoteVolume, sizeof kse.rec[i].bidQuoteVolume).c_str());
    }

    sendQuote10(quote);
    return 0;
}

int InternetKseChannelProcessor::handleQuote10Fixed(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_QUOTE10_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleQuote10Fixed] Skip : %s, %d : EXTURE_PLUS_KSE_QUOTE10_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_QUOTE10_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseQuote10 kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    // 구스펙 : 시간외단일가장구분
    // 신스펙 : 장상태구분코드로 대치(70 : 시간외단일가), 정규시간외구분코드(4 : 장종료후시간외단일가)
    ACE_CString boardID(kse.boardID, sizeof kse.boardID);
    ACE_CString sessionID(kse.sessionID, sizeof ( kse.sessionID ));

    Quote10 quote;
    quote.exchange = EXCHANGE_KSE;
    quote.symbolType = SYMBOL_STOCK;
    quote.decimalPoint = 0;

    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
    ACE_OS::memcpy(&quote.symbol, stockCode.c_str(), sizeof quote.symbol);

    // 구스펙 : 동시구분(0:접속, 1:동시, 2:동시연장)
    // 신스펙 : X
    quote.concurrent = getConcurrent(boardID, sessionID);
    quote.market = getMarketInQuote10(boardID, sessionID);
    quote.quoteTime = time(0);

    quote.totalAskVolume = atof(ACE_CString(kse.totalAskQuoteRemainder, sizeof kse.totalAskQuoteRemainder).c_str());
    quote.totalBidVolume = atof(ACE_CString(kse.totalBidQuoteRemainder, sizeof kse.totalBidQuoteRemainder).c_str());

    quote.expectedPrice = atoi(ACE_CString(kse.estimatedTradePrice, sizeof kse.estimatedTradePrice).c_str());
    quote.expectedVolume = atof(ACE_CString(kse.estimatedTradeVolume, sizeof kse.estimatedTradeVolume).c_str());

    for ( int i = 0 ; i < 10 ; ++i )
    {
        quote.rec[i].ask = atoi(ACE_CString(kse.rec[i].askQuote, sizeof kse.rec[i].askQuote).c_str());
        quote.rec[i].askVolume = atoi(ACE_CString(kse.rec[i].askQuoteVolume, sizeof kse.rec[i].askQuoteVolume).c_str());
        quote.rec[i].bid = atoi(ACE_CString(kse.rec[i].bidQuote, sizeof kse.rec[i].bidQuote).c_str());
        quote.rec[i].bidVolume = atoi(ACE_CString(kse.rec[i].bidQuoteVolume, sizeof kse.rec[i].bidQuoteVolume).c_str());
    }
    char buf[QUOTE10_SIZE];
    memcpy(buf, &quote, QUOTE10_SIZE);
    int result = sendPacket(ACE_CString(buf, QUOTE10_SIZE), PACKET_QUOTE10_FIXED, EXCHANGE_KSE);

#if(0)
printPacketQuote10(quote);
#endif

    return result;
}

int InternetKseChannelProcessor::handleQuoteBefore(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_QUOTE_BEFORE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleQuoteBefore] Skip : %s, %d : EXTURE_PLUS_KSE_QUOTE_BEFORE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_QUOTE_BEFORE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseQuoteBefore kse;
    ACE_OS::memcpy(&kse, packet.c_str(), EXTURE_PLUS_KSE_QUOTE_BEFORE_SIZE);

    QuoteVolume quote;
    quote.exchange = EXCHANGE_KSE;
    quote.symbolType = SYMBOL_STOCK;
    ACE_CString stockCode = ACE_CString(kse.stockCode, sizeof kse.stockCode);
    memcpy(&quote.symbol, stockCode.c_str(), sizeof quote.symbol);
    quote.market = MARKET_BEFORE_TRADE;
    quote.quoteTime = time(0);

    quote.totalAskVolume = atof(ACE_CString(kse.totalAskQouteVolume, sizeof kse.totalAskQouteVolume).c_str());
    quote.totalBidVolume = atof(ACE_CString(kse.totalBidQuoteVolume, sizeof kse.totalBidQuoteVolume).c_str());

    char buf[QUOTE_PRICE_SIZE];
    memcpy(buf, &quote, QUOTE_VOLUME_SIZE);
    int result = sendPacket(ACE_CString(buf, QUOTE_VOLUME_SIZE), PACKET_QUOTE_VOLUME, EXCHANGE_KSE);

//printPacketQuoteVolume(quote);

    return result;
}

int InternetKseChannelProcessor::handleSecuritiesTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_SECURITIES_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleSecuritiesTrade] Skip : %s, %d : EXTURE_PLUS_KSE_SECURITIES_TRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_SECURITIES_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKseSecuritiesTrade kse;
    ACE_OS::memcpy(&kse, packet.c_str(), EXTURE_PLUS_KSE_SECURITIES_TRADE_SIZE);

    SecuritiesTrade2 sec;
    ::memset(&sec, 0, sizeof(SecuritiesTrade2));
    sec.subtype = SECURITIESTRADESUBTYPE_TRADE;
    sec.exchange = EXCHANGE_KSE;
    sec.symbolType = SYMBOL_STOCK;
    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);

    memcpy(sec.symbol, stockCode.c_str(), sizeof kse.stockCode);
    ACE_OS::memcpy(sec.rec1.seller, kse.rec[0].askSecuritiesTradeNumber + 2, ( sizeof kse.rec[0].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec1.buyer, kse.rec[0].bidSecuritiesTradeNumber + 2, ( sizeof kse.rec[0].bidSecuritiesTradeNumber ) - 2);
    sec.rec1.askVolume = atof(ACE_CString(kse.rec[0].askTradeVolume, sizeof kse.rec[0].askTradeVolume).c_str());
    sec.rec1.bidVolume = atof(ACE_CString(kse.rec[0].bidTradeVolume, sizeof kse.rec[0].bidTradeVolume).c_str());
    sec.rec1.askAmount = atof(ACE_CString(kse.rec[0].askTradeAmount, sizeof kse.rec[0].askTradeAmount).c_str());
    sec.rec1.bidAmount = atof(ACE_CString(kse.rec[0].bidTradeAmount, sizeof kse.rec[0].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec2.seller, kse.rec[1].askSecuritiesTradeNumber + 2, ( sizeof kse.rec[1].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec2.buyer, kse.rec[1].bidSecuritiesTradeNumber + 2, ( sizeof kse.rec[1].bidSecuritiesTradeNumber ) - 2);
    sec.rec2.askVolume = atof(ACE_CString(kse.rec[1].askTradeVolume, sizeof kse.rec[1].askTradeVolume).c_str());
    sec.rec2.bidVolume = atof(ACE_CString(kse.rec[1].bidTradeVolume, sizeof kse.rec[1].bidTradeVolume).c_str());
    sec.rec2.askAmount = atof(ACE_CString(kse.rec[1].askTradeAmount, sizeof kse.rec[1].askTradeAmount).c_str());
    sec.rec2.bidAmount = atof(ACE_CString(kse.rec[1].bidTradeAmount, sizeof kse.rec[1].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec3.seller, kse.rec[2].askSecuritiesTradeNumber + 2, ( sizeof kse.rec[2].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec3.buyer, kse.rec[2].bidSecuritiesTradeNumber + 2, ( sizeof kse.rec[2].bidSecuritiesTradeNumber ) - 2);
    sec.rec3.askVolume = atof(ACE_CString(kse.rec[2].askTradeVolume, sizeof kse.rec[2].askTradeVolume).c_str());
    sec.rec3.bidVolume = atof(ACE_CString(kse.rec[2].bidTradeVolume, sizeof kse.rec[2].bidTradeVolume).c_str());
    sec.rec3.askAmount = atof(ACE_CString(kse.rec[2].askTradeAmount, sizeof kse.rec[2].askTradeAmount).c_str());
    sec.rec3.bidAmount = atof(ACE_CString(kse.rec[2].bidTradeAmount, sizeof kse.rec[2].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec4.seller, kse.rec[3].askSecuritiesTradeNumber + 2, ( sizeof kse.rec[3].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec4.buyer, kse.rec[3].bidSecuritiesTradeNumber + 2, ( sizeof kse.rec[3].bidSecuritiesTradeNumber ) - 2);
    sec.rec4.askVolume = atof(ACE_CString(kse.rec[3].askTradeVolume, sizeof kse.rec[3].askTradeVolume).c_str());
    sec.rec4.bidVolume = atof(ACE_CString(kse.rec[3].bidTradeVolume, sizeof kse.rec[3].bidTradeVolume).c_str());
    sec.rec4.askAmount = atof(ACE_CString(kse.rec[3].askTradeAmount, sizeof kse.rec[3].askTradeAmount).c_str());
    sec.rec4.bidAmount = atof(ACE_CString(kse.rec[3].bidTradeAmount, sizeof kse.rec[3].bidTradeAmount).c_str());

    ACE_OS::memcpy(sec.rec5.seller, kse.rec[4].askSecuritiesTradeNumber + 2, ( sizeof kse.rec[4].askSecuritiesTradeNumber ) - 2);
    ACE_OS::memcpy(sec.rec5.buyer, kse.rec[4].bidSecuritiesTradeNumber + 2, ( sizeof kse.rec[4].bidSecuritiesTradeNumber ) - 2);
    sec.rec5.askVolume = atof(ACE_CString(kse.rec[4].askTradeVolume, sizeof kse.rec[4].askTradeVolume).c_str());
    sec.rec5.bidVolume = atof(ACE_CString(kse.rec[4].bidTradeVolume, sizeof kse.rec[4].bidTradeVolume).c_str());
    sec.rec5.askAmount = atof(ACE_CString(kse.rec[4].askTradeAmount, sizeof kse.rec[4].askTradeAmount).c_str());
    sec.rec5.bidAmount = atof(ACE_CString(kse.rec[4].bidTradeAmount, sizeof kse.rec[4].bidTradeAmount).c_str());

    char buf[SECURITIES_TRADE2_SIZE];
    memcpy(buf, &sec, SECURITIES_TRADE2_SIZE);

    ACE_CString isNormalstockCode(kse.stockCode, ( sizeof kse.stockCode ) - 9); //종목코드(표준코드) 12자리에서 앞의 3자리만 뽑아온다.

    int result = 0;

    if ( isValidSymbol(stockCode) == true )
    {
        result = sendPacket(ACE_CString(buf, SECURITIES_TRADE2_SIZE), PACKET_SECURITIES_TRADE, EXCHANGE_KSE);
    }
    else
    {
        if ( isNormalstockCode == "KRA" )
        {
            result = sendPacket(ACE_CString(buf, SECURITIES_TRADE2_SIZE), PACKET_SECURITIES_TRADE_ELW, EXCHANGE_KSE);
        }
    }

#if(0)
printPacketSecuritiesTrade2(sec);
#endif

    return result;
}

int InternetKseChannelProcessor::handleInvestorIndex(const ACE_CString &packet)
{
    int result = 0;

    try
    {
        if ( EXTURE_PLUS_KSE_TOTAL_INVESTOR_INDEX_SIZE != static_cast<int>(packet.length()) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex] Skip : %s, %d : EXTURE_PLUS_KSE_INVESTOR_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_INVESTOR_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
        }

        // log frame count status
        LogFrameCount(packet.substr(0, 2).c_str());

		ExturePlusKseTotalInvestorIndex totalkse;
		ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

        ExturePlusKseInvestorIndex kse;

		::memcpy(kse.calculationTime,totalkse.calculationTime,sizeof(kse.calculationTime));
		::memcpy(kse.investorCode,totalkse.investorCode,sizeof(kse.investorCode));
		::memcpy(kse.askTradeVolume,totalkse.askTradeVolume,sizeof(kse.askTradeVolume));
		::memcpy(kse.askTradeAmount,totalkse.askTradeAmount,sizeof(kse.askTradeAmount));
		::memcpy(kse.bidTradeVolume,totalkse.bidTradeVolume,sizeof(kse.bidTradeVolume));
		::memcpy(kse.bidTradeAmount,totalkse.bidTradeAmount,sizeof(kse.bidTradeAmount));


        // 2020.11.26
        ACE_CString packetPrefix(packet.substr(0, 5).c_str());
        if ( packetPrefix != "C001S" )
        {
            ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex|DEBUG] skip......\tpacketPrefix:[%s]\n" , getCurrentTimestamp().c_str() , packetPrefix.c_str() ));
            return ( 0 );
        }

        Investor investor;
        ::memset(&investor, 0, sizeof(Investor));
        investor.subtype = SYMBOL_STOCK;
        investor.exchange = EXCHANGE_KSE;
        investor.symbolType = SYMBOL_INDEX;

        // 구스펙 : 투자자코드
        // 신스펙 : 투자자코드
        ACE_CString rawInvestorCode(kse.investorCode, sizeof ( kse.investorCode ));
        const ACE_CString& investorCode = invConv_.getInvestor(ACE_CString(kse.investorCode, sizeof ( kse.investorCode )));
        ::memcpy(& ( investor.investor ), investorCode.c_str(), 4);

#if(0)
        int code = atoi(ACE_CString(kse.businessType, sizeof kse.businessType).c_str());
#endif
#if(1)
	    ACE_CString businesstype(totalkse.jisuIdentifiation, sizeof ( totalkse.jisuIdentifiation ));
        int code = atoi(getSymbolUpCode(businesstype).c_str());

		ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex|DEBUG] code:[%d],businesstype:[%s],jisuIdentifiation[%.*s]\n" , getCurrentTimestamp().c_str() , code , businesstype.c_str() , sizeof ( totalkse.jisuIdentifiation ), totalkse.jisuIdentifiation ));
#endif

        // KOSPI 200 
        if ( code == 29 )
        {
            code = TICKERPLANT_BASECODE_KOSPI200 + 1;
        }
        else if ( code >= 30 )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex] Skip : %s,%d : unknow code [%d]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , code ), -1);
        }
        ACE_CString stockCode = getIndexSymbol(code);

        /*
         * KRX100 은 투자자 데이터를 보내지 않는다.
         * 일단 return 시키고
         * 어느 업종 코드가 KRI000000000 으로 매핑되는지 찾는다.
         */
        if ( stockCode == "KRI000000000" )
        {
            ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex|DEBUG] code:[%d]\tstockCode:[%s]\tpacket:[%s]\n" , getCurrentTimestamp().c_str() , code , stockCode.c_str() , packet.c_str() ));
            return ( 0 );
        }
		else
		{
			ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex|DEBUG] code:[%d]\tstockCode:[%s]\tpacket:[%s]\n" , getCurrentTimestamp().c_str() , code , stockCode.c_str() , packet.c_str() ));
		}

        ACE_OS::memcpy(&investor.symbol, stockCode.c_str(), sizeof investor.symbol);
        //investor.sendTime = time(0) ;
        investor.askVolume = atof(ACE_CString(kse.askTradeVolume, sizeof kse.askTradeVolume).c_str()) / (float) 1000;
        investor.askAmount = atof(ACE_CString(kse.askTradeAmount, sizeof kse.askTradeAmount).c_str()) / (float) 1000000;
        investor.bidVolume = atof(ACE_CString(kse.bidTradeVolume, sizeof kse.bidTradeVolume).c_str()) / (float) 1000;
        investor.bidAmount = atof(ACE_CString(kse.bidTradeAmount, sizeof kse.bidTradeAmount).c_str()) / (float) 1000000;

        char buf[INVESTOR_SIZE];
        memcpy(buf, &investor, INVESTOR_SIZE);
        result = sendPacket(ACE_CString(buf, INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KSE);
    }
    catch ( std::exception& e )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex] error occur e,what[%s]\n" , getCurrentTimestamp().c_str() , e.what() ));
        result = -1;
    }
    catch ( ... )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorIndex] unknown error occur\n" , getCurrentTimestamp().c_str() ));
        result = -1;
    }
    return result;
}

int InternetKseChannelProcessor::handleProgramTrade(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_PROGRAM_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleProgramTrade] Skip : %s, %d : KSE_KOSDAQ_PROGRAMTRADE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_PROGRAM_TRADE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // copy raw data
    ExturePlusKseProgramTrade kseProgTrd;
    ACE_OS::memcpy(&kseProgTrd, packet.c_str(), packet.length());

    // set basic info
    ProgramTrade paxProgTrd;
    paxProgTrd.exchange = EXCHANGE_KSE;
    paxProgTrd.symbolType = SYMBOL_STOCK;

    // set datas
    ACE_OS::memcpy(paxProgTrd.symbol, kseProgTrd.stockCode, std::min(sizeof ( paxProgTrd.symbol ), sizeof ( kseProgTrd.stockCode )));

    paxProgTrd.mpSellQuoteRemainder = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskQuoteRemainder, sizeof ( kseProgTrd.indexMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrd.mpBuyQuoteRemainder = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidQuoteRemainder, sizeof ( kseProgTrd.indexMarginalProfitBidQuoteRemainder )).c_str());
    paxProgTrd.nmpSellQuoteRemainder = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskQuoteRemainder, sizeof ( kseProgTrd.indexNotMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrd.nmpBuyQuoteRemainder = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidQuoteRemainder, sizeof ( kseProgTrd.indexNotMarginalProfitBidQuoteRemainder )).c_str());
    paxProgTrd.mpSellQuoteVolume = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskQuoteVolume, sizeof ( kseProgTrd.indexMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrd.mpBuyQuoteVolume = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidQuoteVolume, sizeof ( kseProgTrd.indexMarginalProfitBidQuoteVolume )).c_str());
    paxProgTrd.nmpSellQuoteVolume = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskQuoteVolume, sizeof ( kseProgTrd.indexNotMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrd.nmpBuyQuoteVolume = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidQuoteVolume, sizeof ( kseProgTrd.indexNotMarginalProfitBidQuoteVolume )).c_str());

    // 매도위탁체결수량
    // 아래 코드를 변경함
    // paxProgTrd.sellCommitTradeVolume = 
    //   ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskConsignmentTradeVolume, sizeof(kseProgTrd.indexMarginalProfitAskConsignmentTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume, sizeof(kseProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume)).c_str());
    double indexMarginalProfitAskConsignmentTradeVolume = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskConsignmentTradeVolume, sizeof ( kseProgTrd.indexMarginalProfitAskConsignmentTradeVolume )).c_str());
    double indexNotMarginalProfitAskConsignmentTradeVolume = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume, sizeof ( kseProgTrd.indexNotMarginalProfitAskConsignmentTradeVolume )).c_str());
    paxProgTrd.sellCommitTradeVolume = indexMarginalProfitAskConsignmentTradeVolume + indexNotMarginalProfitAskConsignmentTradeVolume;

    // 매도자기체결수량
    // 아래 코드를 변경함
    // paxProgTrd.sellSelfTradeVolume =
    //   ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskFloorTradeVolume, sizeof(kseProgTrd.indexMarginalProfitAskFloorTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskFloorTradeVolume, sizeof(kseProgTrd.indexNotMarginalProfitAskFloorTradeVolume)).c_str());
    double indexMarginalProfitAskFloorTradeVolume = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskFloorTradeVolume, sizeof ( kseProgTrd.indexMarginalProfitAskFloorTradeVolume )).c_str());
    double indexNotMarginalProfitAskFloorTradeVolume = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskFloorTradeVolume, sizeof ( kseProgTrd.indexNotMarginalProfitAskFloorTradeVolume )).c_str());
    paxProgTrd.sellSelfTradeVolume = indexMarginalProfitAskFloorTradeVolume + indexNotMarginalProfitAskFloorTradeVolume;

    // 매수위탁체결수량
    // 아래코드를 변경함
    // paxProgTrd.buyCommitTradeVolume =
    //   ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidConsignmentTradeVolume, sizeof(kseProgTrd.indexMarginalProfitBidConsignmentTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume, sizeof(kseProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume)).c_str());
    double indexMarginalProfitBidConsignmentTradeVolume = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidConsignmentTradeVolume, sizeof ( kseProgTrd.indexMarginalProfitBidConsignmentTradeVolume )).c_str());
    double indexNotMarginalProfitBidConsignmentTradeVolume = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume, sizeof ( kseProgTrd.indexNotMarginalProfitBidConsignmentTradeVolume )).c_str());
    paxProgTrd.buyCommitTradeVolume = indexMarginalProfitBidConsignmentTradeVolume + indexNotMarginalProfitBidConsignmentTradeVolume;

    // 매수자기체결수량
    // 아래코드를 변경함
    // paxProgTrd.buySelfTradeVolume =
    //   ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidFloorTradeVolume, sizeof(kseProgTrd.indexMarginalProfitBidFloorTradeVolume)).c_str())
    //+ ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidFloorTradeVolume, sizeof(kseProgTrd.indexNotMarginalProfitBidFloorTradeVolume)).c_str());
    double indexMarginalProfitBidFloorTradeVolume = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidFloorTradeVolume, sizeof ( kseProgTrd.indexMarginalProfitBidFloorTradeVolume )).c_str());
    double indexNotMarginalProfitBidFloorTradeVolume = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidFloorTradeVolume, sizeof ( kseProgTrd.indexNotMarginalProfitBidFloorTradeVolume )).c_str());
    paxProgTrd.buySelfTradeVolume = indexMarginalProfitBidFloorTradeVolume + indexNotMarginalProfitBidFloorTradeVolume;

    // 구스펙 : 매도위탁체결금액 
    // 신스펙 : (지수)차익매도위탁체결금액 + (지수)비차익매도위탁체결금
    //paxProgTrd.sellCommitTradeAmount = 
    //  ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskConsignmentTradeAmount, sizeof(kseProgTrd.indexMarginalProfitAskConsignmentTradeAmount)).c_str())
    //  + ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount, sizeof(kseProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount)).c_str());
    double indexMarginalProfitAskConsignmentTradeAmount = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskConsignmentTradeAmount, sizeof ( kseProgTrd.indexMarginalProfitAskConsignmentTradeAmount )).c_str());
    double indexNotMarginalProfitAskConsignmentTradeAmount = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount, sizeof ( kseProgTrd.indexNotMarginalProfitAskConsignmentTradeAmount )).c_str());
    paxProgTrd.sellCommitTradeAmount = indexMarginalProfitAskConsignmentTradeAmount + indexNotMarginalProfitAskConsignmentTradeAmount;

    // 아래코드를 변경함
    //paxProgTrd.sellSelfTradeAmount =
    //  ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskFloorTradeAmount, sizeof(kseProgTrd.indexMarginalProfitAskFloorTradeAmount)).c_str())
    //  + ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskFloorTradeAmount, sizeof(kseProgTrd.indexNotMarginalProfitAskFloorTradeAmount)).c_str());
    double indexMarginalProfitAskFloorTradeAmount = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitAskFloorTradeAmount, sizeof ( kseProgTrd.indexMarginalProfitAskFloorTradeAmount )).c_str());
    double indexNotMarginalProfitAskFloorTradeAmount = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitAskFloorTradeAmount, sizeof ( kseProgTrd.indexNotMarginalProfitAskFloorTradeAmount )).c_str());
    paxProgTrd.sellSelfTradeAmount = indexMarginalProfitAskFloorTradeAmount + indexNotMarginalProfitAskFloorTradeAmount;

    // 아래코드를 변경함
    //paxProgTrd.buyCommitTradeAmount = 
    //  ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidConsignmentTradeAmount, sizeof(kseProgTrd.indexMarginalProfitBidConsignmentTradeAmount)).c_str())
    //  + ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount, sizeof(kseProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount)).c_str());
    double indexMarginalProfitBidConsignmentTradeAmount = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidConsignmentTradeAmount, sizeof ( kseProgTrd.indexMarginalProfitBidConsignmentTradeAmount )).c_str());
    double indexNotMarginalProfitBidConsignmentTradeAmount = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount, sizeof ( kseProgTrd.indexNotMarginalProfitBidConsignmentTradeAmount )).c_str());
    paxProgTrd.buyCommitTradeAmount = indexMarginalProfitBidConsignmentTradeAmount + indexNotMarginalProfitBidConsignmentTradeAmount;

    // 아래코드를 변경함
    //paxProgTrd.buySelfTradeAmount =
    //  ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidFloorTradeAmount, sizeof(kseProgTrd.indexMarginalProfitBidFloorTradeAmount)).c_str());
    //  + ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidFloorTradeAmount, sizeof(kseProgTrd.indexNotMarginalProfitBidFloorTradeAmount)).c_str());
    double indexMarginalProfitBidFloorTradeAmount = ::atof(ACE_CString(kseProgTrd.indexMarginalProfitBidFloorTradeAmount, sizeof ( kseProgTrd.indexMarginalProfitBidFloorTradeAmount )).c_str());
    double indexNotMarginalProfitBidFloorTradeAmount = ::atof(ACE_CString(kseProgTrd.indexNotMarginalProfitBidFloorTradeAmount, sizeof ( kseProgTrd.indexNotMarginalProfitBidFloorTradeAmount )).c_str());
    paxProgTrd.buySelfTradeAmount = indexMarginalProfitBidFloorTradeAmount + indexNotMarginalProfitBidFloorTradeAmount;

    //프로그램매도사전공시수량, 프로그램매수공시수량 -> 스펙 분리 C5
    ACE_CString stockCode(kseProgTrd.stockCode, sizeof kseProgTrd.stockCode);
    ExturePlusKseProgramTradePublic kseProgTrdPublic;

    int hasValue = programTradeMapKse_->find(stockCode, kseProgTrdPublic, ALLOCATOR::instance());

    if ( hasValue == -1 )
    {
        paxProgTrd.paSellVolume = 0.0f;
        paxProgTrd.paBuyVolume = 0.0f;
    }
    else
    {
        paxProgTrd.paSellVolume = ::atof(ACE_CString(kseProgTrdPublic.askPublicAheadPublicPrevRemainder, sizeof ( kseProgTrdPublic.askPublicAheadPublicPrevRemainder )).c_str());
        paxProgTrd.paBuyVolume = ::atof(ACE_CString(kseProgTrdPublic.bidPublicAheadPublicPrevRemainder, sizeof ( kseProgTrdPublic.bidPublicAheadPublicPrevRemainder )).c_str());
    }
    int result = sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrd), sizeof(ProgramTrade)), PACKET_PROGRAM, EXCHANGE_KSE);

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleProgramTrade] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));
//    printPacketProgramTrade(paxProgTrd);
    return result;
}

int InternetKseChannelProcessor::handleProgramTradePublic(const ACE_CString &packet)
{
    int result = 0;
    try
    {
        if ( EXTURE_PLUS_KSE_PROGRAM_TRADE_PUBLIC_SIZE != static_cast<int>(packet.length()) )
        {
            ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::hanldeProgramTradePublic] Skip : %s, %d : EXTURE_PLUS_KSE_PROGRAM_TRADE_PUBLIC_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_PROGRAM_TRADE_PUBLIC_SIZE , packet.length() , packet.c_str() ), -1);
        }

        // log frame count status
        LogFrameCount(packet.substr(0, 2).c_str());

        ExturePlusKseProgramTradePublic kseProgTrdPublic;
        ACE_OS::memcpy(&kseProgTrdPublic, packet.c_str(), packet.length());

        ACE_CString stockCode(kseProgTrdPublic.stockCode, sizeof kseProgTrdPublic.stockCode);
        ACE_CString dataClass(kseProgTrdPublic.dataClass, sizeof kseProgTrdPublic.dataClass);
        ACE_CString infoClass(kseProgTrdPublic.infoClass, sizeof kseProgTrdPublic.infoClass);
        ACE_CString marketClass(kseProgTrdPublic.marketClass, sizeof kseProgTrdPublic.marketClass);
        ACE_CString askPublicAheadPublicPrevRemainder(kseProgTrdPublic.askPublicAheadPublicPrevRemainder, sizeof kseProgTrdPublic.askPublicAheadPublicPrevRemainder);
        ACE_CString bidPublicAheadPublicPrevRemainder(kseProgTrdPublic.bidPublicAheadPublicPrevRemainder, sizeof kseProgTrdPublic.bidPublicAheadPublicPrevRemainder);
        ACE_CString askPublicAheadPublicPrevCorrectingRemainder(kseProgTrdPublic.askPublicAheadPublicPrevCorrectingRemainder, sizeof kseProgTrdPublic.askPublicAheadPublicPrevCorrectingRemainder);
        ACE_CString bidPublicAheadPublicPrevCorrectingRemainder(kseProgTrdPublic.bidPublicAheadPublicPrevCorrectingRemainder, sizeof kseProgTrdPublic.bidPublicAheadPublicPrevCorrectingRemainder);
        ACE_CString postDisclosedProgramTradingSellOrderVolume(kseProgTrdPublic.postDisclosedProgramTradingSellOrderVolume, sizeof kseProgTrdPublic.postDisclosedProgramTradingSellOrderVolume);
        ACE_CString postDisclosedProgramTradingBuyOrderVolume(kseProgTrdPublic.postDisclosedProgramTradingBuyOrderVolume, sizeof kseProgTrdPublic.postDisclosedProgramTradingBuyOrderVolume);

        int hasValue = programTradeMapKse_->find(stockCode, kseProgTrdPublic, ALLOCATOR::instance());
        if ( hasValue == -1 )
        {
            programTradeMapKse_->bind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kseProgTrdPublic, ALLOCATOR::instance());
        }
        else
        {
            ACE_CString oldKey;
            ExturePlusKseProgramTradePublic oldVal;
            programTradeMapKse_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kseProgTrdPublic, oldKey, oldVal, ALLOCATOR::instance());
        }
    }
    catch ( std::exception& e )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleProgramTradePublic] error occur e.what[%s]\n" , getCurrentTimestamp().c_str() , e.what() ));
        result = -1;
    }
    return result;
}

int InternetKseChannelProcessor::handleProgramTradeTotal(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_PROGRAM_TRADE_TOTAL_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleProgramTradeTotal] Skip : %s, %d : EXTURE_PLUS_KSE_PROGRAM_TRADE_TOTAL_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_PROGRAM_TRADE_TOTAL_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // copy raw data
    ExturePlusKseProgramTradeTotal kseProgTrdTot;
    ACE_OS::memcpy(&kseProgTrdTot, packet.c_str(), packet.length());

    // set basic info
    ProgramTradeTotal paxProgTrdTot;
    paxProgTrdTot.exchange = EXCHANGE_KSE;

    // set datas
    paxProgTrdTot.mpSellQuoteRemainder = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitAskQuoteRemainder, sizeof ( kseProgTrdTot.indexMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrdTot.mpBuyQuoteRemainder = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitBidQuoteRemainder, sizeof ( kseProgTrdTot.indexMarginalProfitBidQuoteRemainder )).c_str());
    paxProgTrdTot.nmpSellQuoteRemainder = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitAskQuoteRemainder, sizeof ( kseProgTrdTot.indexNotMarginalProfitAskQuoteRemainder )).c_str());
    paxProgTrdTot.nmpBuyQuoteRemainder = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitBidQuoteRemainder, sizeof ( kseProgTrdTot.indexNotMarginalProfitBidQuoteRemainder )).c_str());

    paxProgTrdTot.mpSellQuoteVolume = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitAskQuoteVolume, sizeof ( kseProgTrdTot.indexMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrdTot.mpBuyQuoteVolume = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitBidQuoteVolume, sizeof ( kseProgTrdTot.indexMarginalProfitBidQuoteVolume )).c_str());
    paxProgTrdTot.nmpSellQuoteVolume = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitAskQuoteVolume, sizeof ( kseProgTrdTot.indexNotMarginalProfitAskQuoteVolume )).c_str());
    paxProgTrdTot.nmpBuyQuoteVolume = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitBidQuoteVolume, sizeof ( kseProgTrdTot.indexNotMarginalProfitBidQuoteVolume )).c_str());

    paxProgTrdTot.mpSellCommitTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitAskConsignmentTradeVolume, sizeof ( kseProgTrdTot.indexMarginalProfitAskConsignmentTradeVolume )).c_str());
    paxProgTrdTot.mpSellSelfTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitAskFloorTradeVolume, sizeof ( kseProgTrdTot.indexMarginalProfitAskFloorTradeVolume )).c_str());
    paxProgTrdTot.mpBuyCommitTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitBidConsignmentTradeVolume, sizeof ( kseProgTrdTot.indexMarginalProfitBidConsignmentTradeVolume )).c_str());
    paxProgTrdTot.mpBuySelfTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitBidFloorTradeVolume, sizeof ( kseProgTrdTot.indexMarginalProfitBidFloorTradeVolume )).c_str());

    paxProgTrdTot.nmpSellCommitTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitAskConsignmentTradeVolume, sizeof ( kseProgTrdTot.indexNotMarginalProfitAskConsignmentTradeVolume )).c_str());
    paxProgTrdTot.nmpSellSelfTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitAskFloorTradeVolume, sizeof ( kseProgTrdTot.indexNotMarginalProfitAskFloorTradeVolume )).c_str());
    paxProgTrdTot.nmpBuyCommitTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitBidConsignmentTradeVolume, sizeof ( kseProgTrdTot.indexNotMarginalProfitBidConsignmentTradeVolume )).c_str());
    paxProgTrdTot.nmpBuySelfTradeVolume = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitBidFloorTradeVolume, sizeof ( kseProgTrdTot.indexNotMarginalProfitBidFloorTradeVolume )).c_str());

    paxProgTrdTot.mpSellCommitTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitAskConsignmentTradeAmount, sizeof ( kseProgTrdTot.indexMarginalProfitAskConsignmentTradeAmount )).c_str());
    paxProgTrdTot.mpSellSelfTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitAskFloorTradeAmount, sizeof ( kseProgTrdTot.indexMarginalProfitAskFloorTradeAmount )).c_str());
    paxProgTrdTot.mpBuyCommitTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitBidConsignmentTradeAmount, sizeof ( kseProgTrdTot.indexMarginalProfitBidConsignmentTradeAmount )).c_str());
    paxProgTrdTot.mpBuySelfTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexMarginalProfitBidFloorTradeAmount, sizeof ( kseProgTrdTot.indexMarginalProfitBidFloorTradeAmount )).c_str());

    paxProgTrdTot.nmpSellCommitTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitAskConsignmentTradeAmount, sizeof ( kseProgTrdTot.indexNotMarginalProfitAskConsignmentTradeAmount )).c_str());
    paxProgTrdTot.nmpSellSelfTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitAskFloorTradeAmount, sizeof ( kseProgTrdTot.indexNotMarginalProfitAskFloorTradeAmount )).c_str());
    paxProgTrdTot.nmpBuyCommitTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitBidConsignmentTradeAmount, sizeof ( kseProgTrdTot.indexNotMarginalProfitBidConsignmentTradeAmount )).c_str());
    paxProgTrdTot.nmpBuySelfTradeAmount = ::atof(ACE_CString(kseProgTrdTot.indexNotMarginalProfitBidFloorTradeAmount, sizeof ( kseProgTrdTot.indexNotMarginalProfitBidFloorTradeAmount )).c_str());

    // transfer
    int result = sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdTot), sizeof(ProgramTradeTotal)), PACKET_PROGRAM_TOTAL, EXCHANGE_KSE);

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleProgramTrade] exchange:[%d]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , paxProgTrdTot.exchange , result ));
//    printPacketProgramTradeTotal(paxProgTrdTot);

    return result;
}

// 신스펙 에서는 매수/매도구분코드가 없다. 매수정보와 매도정보가 함께 제공된다.
// 현재 시스템에 영향을 최소화하기 위해서 매수값 정보와 매도값 정보를 분리하여 각각 패킷을 전송한다.
int InternetKseChannelProcessor::handleProgramTradeBatch(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_PROGRAM_TRADE_BATCH_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleProgramTradeBatch] Skip : %s, %d : EXTURE_PLUS_KSE_PROGRAM_TRADE_BATCH_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_PROGRAM_TRADE_BATCH_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    // copy raw data
    ExturePlusKseProgramTradeBatch kseProgTrdBatch;
    ACE_OS::memcpy(&kseProgTrdBatch, packet.c_str(), packet.length());

    // last record
    ACE_CString memberNo(kseProgTrdBatch.memberNo, sizeof kseProgTrdBatch.memberNo);
    if ( memberNo == "99999" )
    {
        return 0;
    }

    // set basic info
    ProgramTradeBatch paxProgTrdBatch;
    paxProgTrdBatch.exchange = EXCHANGE_KSE;

    //매도
    paxProgTrdBatch.serial = ACE_OS::atoi(ACE_CString(kseProgTrdBatch.serialNo, sizeof ( kseProgTrdBatch.serialNo )).c_str());
    paxProgTrdBatch.registerTime = getTime(ACE_CString(kseProgTrdBatch.tradeDate, sizeof ( kseProgTrdBatch.tradeDate )));

    ACE_OS::memcpy(paxProgTrdBatch.securities, kseProgTrdBatch.memberNo + 2, std::min(sizeof ( paxProgTrdBatch.securities ), sizeof ( kseProgTrdBatch.memberNo ) - 2));

    paxProgTrdBatch.commitType = getCommitType(ACE_CString(kseProgTrdBatch.consignmentFloorTradingClassCode, sizeof ( kseProgTrdBatch.consignmentFloorTradingClassCode )));

    paxProgTrdBatch.stockType = 1; //매도 
    paxProgTrdBatch.stockVolume = ::atof(ACE_CString(kseProgTrdBatch.stockAskVolume, sizeof ( kseProgTrdBatch.stockAskVolume )).c_str());
    paxProgTrdBatch.stockAmounte = ::atof(ACE_CString(kseProgTrdBatch.stockAskAmount, sizeof ( kseProgTrdBatch.stockAskAmount )).c_str());
    paxProgTrdBatch.futureVolume = ::atof(ACE_CString(kseProgTrdBatch.futureAskVolume, sizeof ( kseProgTrdBatch.futureAskVolume )).c_str());
    paxProgTrdBatch.futuAmount = ::atof(ACE_CString(kseProgTrdBatch.futureAskAmount, sizeof ( kseProgTrdBatch.futureAskAmount )).c_str());

    paxProgTrdBatch.nearSymbolType = getNearSymbolType(ACE_CString(kseProgTrdBatch.ptFirstMonthClassCode, sizeof ( kseProgTrdBatch.ptFirstMonthClassCode )).c_str());
    paxProgTrdBatch.callOptionVolume = ::atof(ACE_CString(kseProgTrdBatch.callAskVolume, sizeof ( kseProgTrdBatch.callAskVolume )).c_str());
    paxProgTrdBatch.callOptionAmount = ::atof(ACE_CString(kseProgTrdBatch.callAskAmount, sizeof ( kseProgTrdBatch.callAskAmount )).c_str());
    paxProgTrdBatch.putOptionVolume = ::atof(ACE_CString(kseProgTrdBatch.putAskVolume, sizeof ( kseProgTrdBatch.putAskVolume )).c_str());
    paxProgTrdBatch.putOptionAmount = ::atof(ACE_CString(kseProgTrdBatch.putAskAmount, sizeof ( kseProgTrdBatch.putAskAmount )).c_str());

    sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdBatch), sizeof(ProgramTradeBatch)), PACKET_PROGRAM_BATCH, EXCHANGE_KSE);

    //매수
    paxProgTrdBatch.stockType = 2; //매수 
    paxProgTrdBatch.stockVolume = ::atof(ACE_CString(kseProgTrdBatch.stockBidVolume, sizeof ( kseProgTrdBatch.stockBidVolume )).c_str());
    paxProgTrdBatch.stockAmounte = ::atof(ACE_CString(kseProgTrdBatch.stockBidAmount, sizeof ( kseProgTrdBatch.stockBidAmount )).c_str());
    paxProgTrdBatch.futureVolume = ::atof(ACE_CString(kseProgTrdBatch.futureBidVolume, sizeof ( kseProgTrdBatch.futureBidVolume )).c_str());
    paxProgTrdBatch.futuAmount = ::atof(ACE_CString(kseProgTrdBatch.futureBidAmount, sizeof ( kseProgTrdBatch.futureBidAmount )).c_str());

    paxProgTrdBatch.callOptionVolume = ::atof(ACE_CString(kseProgTrdBatch.callBidVolume, sizeof ( kseProgTrdBatch.callBidVolume )).c_str());
    paxProgTrdBatch.callOptionAmount = ::atof(ACE_CString(kseProgTrdBatch.callBidAmount, sizeof ( kseProgTrdBatch.callBidAmount )).c_str());
    paxProgTrdBatch.putOptionVolume = ::atof(ACE_CString(kseProgTrdBatch.putBidVolume, sizeof ( kseProgTrdBatch.putBidVolume )).c_str());
    paxProgTrdBatch.putOptionAmount = ::atof(ACE_CString(kseProgTrdBatch.putBidAmount, sizeof ( kseProgTrdBatch.putBidAmount )).c_str());

    sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdBatch), sizeof(ProgramTradeBatch)), PACKET_PROGRAM_BATCH, EXCHANGE_KSE);
//    int result = sendPacket(ACE_CString(reinterpret_cast<char*>(&paxProgTrdBatch), sizeof(ProgramTradeBatch)), PACKET_PROGRAM_BATCH, EXCHANGE_KSE);

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleProgramTradeBatch] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
//    printPacketProgramTradeBatch(paxProgTrdBatch);

    return 0;
}

int InternetKseChannelProcessor::handlePublicNews(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_PUBLIC_NEWS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handlePublicNews] Skip : %s, %d : EXTURE_PLUS_KSE_PUBLIC_NEWS_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_PUBLIC_NEWS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusKsePublicNews kse;
    ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

    int result = sendPacket(packet, PACKET_PUBLIC_NEWS, EXCHANGE_KSE);
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handlePublicNews] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
    return result;
}

int InternetKseChannelProcessor::handleRecoveryTradeFixed(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_RECOVERY_TOTAL_TRADE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleRecoveryTradeFixed] Skip : %s, %d : EXTURE_PLUS_KSE_RECOVERY_TRADE_FIXED_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_RECOVERY_TRADE_FIXED_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ACE_CString frameId(packet.substr(0, 2));

    // log frame count status
    LogFrameCount(frameId);

    ExturePlusKseRecoveryTotalTrade totalkse;
    ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseRecoveryTradeFixed kse;
    memset(&kse, 0x30, sizeof(kse));

    ACE_CString boardID(totalkse.boardID, sizeof ( totalkse.boardID ));
    ACE_CString sessionID(totalkse.sessionID, sizeof ( totalkse.sessionID ));

    memcpy(kse.stockCode, totalkse.stockCode, sizeof(kse.stockCode));
    memcpy(kse.upDown, totalkse.upDown, sizeof(kse.upDown));
    memcpy(kse.overTimeMarketFixedOpenPrice, totalkse.openPrice, sizeof(kse.overTimeMarketFixedOpenPrice));
    memcpy(kse.overTimeMarketFixedHighPrice, totalkse.highPrice, sizeof(kse.overTimeMarketFixedHighPrice));
    memcpy(kse.overTimeMarketFixedLowPrice, totalkse.lowPrice, sizeof(kse.overTimeMarketFixedLowPrice));
    memcpy(kse.overTimeMarketFixedCurrClosePrice, totalkse.closePrice, sizeof(kse.overTimeMarketFixedCurrClosePrice));
    memcpy(kse.gap, totalkse.gap, sizeof(kse.gap));
    memcpy(kse.realRateQuotationClass, totalkse.realRateQuotationClass, sizeof(kse.realRateQuotationClass));
    memcpy(kse.overTimeMarketFixedAccmVolume, totalkse.accmTradeVolume, sizeof(kse.overTimeMarketFixedAccmVolume));
    memcpy(kse.overTimeMarketFixedAccmAmount, totalkse.accmTradeAmount, sizeof(kse.overTimeMarketFixedAccmAmount));


    Trade trade;
    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);

    TickFilter filter;

    //ACE_CString overTimeMarketFixedMarketClass(kse.overTimeMarketFixedMarketClass, sizeof kse.overTimeMarketFixedMarketClass);
    ACE_CString overTimeMarketFixedMarketClass;
    /*
    G4	장종료후단일가	20	단일가	0
    G4	장종료후단일가	50	장중VI단일가	2
    */
    if(boardID=="G4" && sessionID=="20") overTimeMarketFixedMarketClass="0";
    if(boardID=="G4" && sessionID=="50") overTimeMarketFixedMarketClass="2";

    ACE_CString upDown(kse.upDown, sizeof kse.upDown);
    trade.market = getMarketInTradeFixed(overTimeMarketFixedMarketClass);
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kse.overTimeMarketFixedOpenPrice, sizeof kse.overTimeMarketFixedOpenPrice).c_str());
    trade.high = atoi(ACE_CString(kse.overTimeMarketFixedHighPrice, sizeof kse.overTimeMarketFixedHighPrice).c_str());
    trade.low = atoi(ACE_CString(kse.overTimeMarketFixedLowPrice, sizeof kse.overTimeMarketFixedLowPrice).c_str());
    trade.close = atoi(ACE_CString(kse.overTimeMarketFixedCurrClosePrice, sizeof kse.overTimeMarketFixedCurrClosePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(kse.overTimeMarketFixedAccmVolume, sizeof kse.overTimeMarketFixedAccmVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kse.overTimeMarketFixedAccmAmount, sizeof kse.overTimeMarketFixedAccmAmount).c_str());
    trade.accmVolume = accmVolume;
    trade.amount = accmAmount;

    ACE_CString quotation(kse.realRateQuotationClass, sizeof kse.realRateQuotationClass);

    if ( frameId == "B3" )
    {
        trade.subtype = TRADESUBTYPE_CLOSE;
    }
    else if ( quotation == "2" )
    {
        trade.subtype = TRADESUBTYPE_QUOTATION;
    }
    else
    {
        trade.subtype = TRADESUBTYPE_RECOVERY;
    }

    trade.tradeVolume = 0;

    trade.exchange = EXCHANGE_KSE;
    trade.symbolType = SYMBOL_STOCK;
    trade.decimalPoint = DECIMAL_0;
    trade.tradeTime = time(0);
    ACE_OS::memcpy(&trade.symbol, &kse.stockCode, sizeof kse.stockCode);

    trade.openMin = 0;
    trade.highMin = 0;
    trade.lowMin = 0;
    trade.volumeMin = 0;

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE_FIXED, EXCHANGE_KSE);

#if(0)
    if ( frameId == "B3" )
    {
        ACE_CString oldKey;
        ExturePlusKseRecoveryTradeFixed oldValue;
        ::memset(&oldValue, 0, sizeof(ExturePlusKseRecoveryTradeFixed));
        int rebindResult = tradeFixedMapKse_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kse, oldKey, oldValue, ALLOCATOR::instance());
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTradeFixed] frameId:[%s]\tstockCode:[%s]\trebindResult:[%d]\n" , getCurrentTimestamp().c_str() , frameId.c_str() , stockCode.c_str() , rebindResult ));
    }
#endif

#if(1)
    ACE_CString oldKey;
    ExturePlusKseRecoveryTradeFixed oldValue;
    ::memset(&oldValue, 0, sizeof(ExturePlusKseRecoveryTradeFixed));
    int rebindResult = tradeFixedMapKse_->rebind(ACE_CString(stockCode.c_str(), ALLOCATOR::instance()), kse, oldKey, oldValue, ALLOCATOR::instance());
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleRecoveryTradeFixed] frameId:[%s]\tstockCode:[%s]\trebindResult:[%d]\n" , getCurrentTimestamp().c_str() , frameId.c_str() , stockCode.c_str() , rebindResult ));
#endif

    return result;
}

int InternetKseChannelProcessor::handleTradeFixed(const ExturePlusKseTrade &kse)
{
    Trade trade;
    ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);

    TickFilter filter;

    ACE_CString upDown(kse.upDown, sizeof kse.upDown);

    trade.market = MARKET_IN;
    trade.upDown = getUpDownInTrade(upDown);

    trade.open = atoi(ACE_CString(kse.openPrice, sizeof kse.openPrice).c_str());
    trade.high = atoi(ACE_CString(kse.highPrice, sizeof kse.highPrice).c_str());
    trade.low = atoi(ACE_CString(kse.lowPrice, sizeof kse.lowPrice).c_str());
    trade.close = atoi(ACE_CString(kse.tradePrice, sizeof kse.tradePrice).c_str());

    if ( filter.mustFilterByCurrPrice(trade.close) )
    {
        return -1;
    }

    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str());
    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;

    double accmVolume = ::atof(ACE_CString(kse.accmTradeVolume, sizeof kse.accmTradeVolume).c_str());
    double accmAmount = ::atof(ACE_CString(kse.accmTradeAmount, sizeof kse.accmTradeAmount).c_str());
    trade.accmVolume = accmVolume;
    trade.amount = accmAmount;

    trade.subtype = TRADESUBTYPE_TRADE;
    trade.tradeVolume = 0;
    trade.exchange = EXCHANGE_KSE;
    trade.symbolType = SYMBOL_STOCK;
    trade.decimalPoint = DECIMAL_0;
    trade.tradeTime = time(0);
    ACE_OS::memcpy(&trade.symbol, &kse.stockCode, sizeof kse.stockCode);

    trade.openMin = 0;
    trade.highMin = 0;
    trade.lowMin = 0;
    trade.volumeMin = 0;

    char buf[TRADE_SIZE];
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE_FIXED, EXCHANGE_KSE);

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleTradeFixed] stockCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , result ));
    printPacketTrade(trade);

    return result;
}

int InternetKseChannelProcessor::handleInvestorStock(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_INVESTOR_STOCK_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorStock] Skip : %s, %d : EXTURE_PLUS_KSE_INVESTOR_STOCK_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_INVESTOR_STOCK_SIZE , packet.length() , packet.c_str() ), -1);
    }
    int result = 0;
    try
    {
        // log frame count status   
        LogFrameCount(packet.substr(0, 2).c_str());

        ExturePlusKseInvestorStock raw;
        ACE_OS::memcpy(&raw, packet.c_str(), std::min(sizeof ( raw ), packet.length()));

#if(1)
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]dataClass  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.dataClass),raw.dataClass));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]infoClass  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.infoClass),raw.infoClass));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]marketClass:[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.marketClass),raw.marketClass));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]exchange   :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.exchange),raw.exchange));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]date       :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.date),raw.date));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]symbol     :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.symbol),raw.symbol));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]investor   :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.investor),raw.investor));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]sellVolume :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.sellVolume),raw.sellVolume));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]sellAmount :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.sellAmount),raw.sellAmount));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]buyVolume  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.buyVolume),raw.buyVolume));
ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock]buyAmount  :[%.*s]\n" , getCurrentTimestamp().c_str() ,sizeof(raw.buyAmount),raw.buyAmount));
#endif

        Investor investor;
        investor.subtype = SYMBOL_STOCK;
        investor.exchange = EXCHANGE_KSE;
        investor.symbolType = SYMBOL_STOCK;

        ACE_OS::memset(investor.symbol, 0, sizeof ( investor.symbol ));
        ACE_OS::memcpy(&investor.symbol, raw.symbol, std::min(sizeof ( investor.symbol ), sizeof ( raw.symbol )));
        std::string investorCode(raw.investor, raw.investor + sizeof ( raw.investor ));
        ACE_OS::memcpy(&investor.investor, investorCode.c_str(), std::min(sizeof investor.investor, investorCode.length()));

        investor.askVolume = atof(std::string(raw.sellVolume, sizeof raw.sellVolume).c_str());
        investor.askAmount = atof(std::string(raw.sellAmount, sizeof raw.sellAmount).c_str());
        investor.bidVolume = atof(std::string(raw.buyVolume, sizeof raw.buyVolume).c_str());
        investor.bidAmount = atof(std::string(raw.buyAmount, sizeof raw.buyAmount).c_str());

        result = sendPacket(ACE_CString(reinterpret_cast<char*>(&investor), INVESTOR_SIZE), PACKET_INVESTOR, EXCHANGE_KSE);

        ACE_CString stockCode(investor.symbol, sizeof ( investor.symbol ));
//        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleInvestorStock] stockCode:[%s]\tinvestorCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , stockCode.c_str() , investorCode.c_str() , result ));
//        printPacketInvestor(investor);
    }
    catch ( std::exception& e )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorStock] error occur e.what[%s])\n" , getCurrentTimestamp().c_str() , e.what() ));
        result = -1;
    }
    catch ( ... )
    {
        ACE_DEBUG( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleInvestorStock] unknown error occur\n" , getCurrentTimestamp().c_str() ));
        result = -1;
    }
    return result;
}

#if(1)
int InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] BEGIN\n" , getCurrentTimestamp().c_str() ));
    if ( EXTURE_PLUS_KSE_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] Skip : %s, %d : EXTURE_PLUS_KSE_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExturePlusKseMarketOperationScheduleDisclosure rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKseMarketOperationScheduleDisclosure));
    ::memcpy(&rawRec, packet.c_str(), sizeof(ExturePlusKseMarketOperationScheduleDisclosure));

    {
        ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
        ACE_CString marketCategory(rawRec.marketCategory, sizeof ( rawRec.marketCategory ));
        ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
        ACE_CString boardID(rawRec.boardID, sizeof ( rawRec.boardID ));
        ACE_CString boardEventID(rawRec.boardEventID, sizeof ( rawRec.boardEventID ));
        ACE_CString boardEventBeginTime(rawRec.boardEventBeginTime, sizeof ( rawRec.boardEventBeginTime ));
        ACE_CString boardEventApplyCode(rawRec.boardEventApplyCode, sizeof ( rawRec.boardEventApplyCode ));
        ACE_CString sessionBeginEndCode(rawRec.sessionBeginEndCode, sizeof ( rawRec.sessionBeginEndCode ));
        ACE_CString sessionID(rawRec.sessionID, sizeof ( rawRec.sessionID ));
        ACE_CString listedIssueCode(rawRec.listedIssueCode, sizeof ( rawRec.listedIssueCode ));
        ACE_CString tradingHaltReasonCode(rawRec.tradingHaltReasonCode, sizeof ( rawRec.tradingHaltReasonCode ));
        ACE_CString tradingHaltOccurenceTypeCode(rawRec.tradingHaltOccurenceTypeCode, sizeof ( rawRec.tradingHaltOccurenceTypeCode ));
        ACE_CString stepApplied(rawRec.stepApplied, sizeof ( rawRec.stepApplied ));

        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] dataCategory                  :[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] marketCategory                :[%s]\n" , getCurrentTimestamp().c_str() , marketCategory.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] issueCode                     :[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] boardID                       :[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] boardEventID                  :[%s]\n" , getCurrentTimestamp().c_str() , boardEventID.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] boardEventBeginTime           :[%s]\n" , getCurrentTimestamp().c_str() , boardEventBeginTime.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] boardEventApplyCode           :[%s]\n" , getCurrentTimestamp().c_str() , boardEventApplyCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] sessionBeginEndCode           :[%s]\n" , getCurrentTimestamp().c_str() , sessionBeginEndCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] sessionID                     :[%s]\n" , getCurrentTimestamp().c_str() , sessionID.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] listedIssueCode               :[%s]\n" , getCurrentTimestamp().c_str() , listedIssueCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] tradingHaltReasonCode         :[%s]\n" , getCurrentTimestamp().c_str() , tradingHaltReasonCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] tradingHaltOccurenceTypeCode  :[%s]\n" , getCurrentTimestamp().c_str() , tradingHaltOccurenceTypeCode.c_str() ));
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] stepApplied                   :[%s]\n" , getCurrentTimestamp().c_str() , stepApplied.c_str() ));
    }

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    std::string issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    boost::trim(issueCode);

    std::string listedIssueCode(rawRec.listedIssueCode, sizeof ( rawRec.listedIssueCode ));
    boost::trim(listedIssueCode);

    ACE_CString symbol;

    if ( ( issueCode == std::string("") ) || ( listedIssueCode == std::string("") ) )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] issueCode:[%s][%d]\tlistedIssueCode:[%s][%d]\t\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , issueCode.length() , listedIssueCode.c_str() , listedIssueCode.length() ));

        // 종목코드없을 경우 시장공통으로 설정
        symbol = "KRI001000000";
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
    int result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationScheduleDisclosure] END\n" , getCurrentTimestamp().c_str() ));
    return result;
}
#endif

int InternetKseChannelProcessor::handleMarketOperationTS(const ACE_CString &packet)
{
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationTS] BEGIN\n" , getCurrentTimestamp().c_str() ));
    if ( EXTURE_PLUS_KSE_MARKET_OPERATION_TS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleMarketOperationTS] Skip : %s, %d : EXTURE_PLUS_KSE_MARKET_OPERATION_TS_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_MARKET_OPERATION_TS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    ExturePlusKseMarketOperationTS rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKseMarketOperationTS));
    ::memcpy(&rawRec, packet.c_str(), sizeof(ExturePlusKseMarketOperationTS));

    MarketOperation marketRec;
    ::memset(&marketRec, 0, sizeof(MarketOperation));

    std::string issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    boost::trim(issueCode);

    if ( issueCode == std::string("") )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationTS] invalid issueCode:[%s][%d] skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , issueCode.length() ));
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
    int result = sendPacket(ACE_CString(buf, MARKET_OPERATION_SIZE), PACKET_MARKET_OPERATION, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationTS] result:[%d]\n" , getCurrentTimestamp().c_str() , result ));
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleMarketOperationTS] END\n" , getCurrentTimestamp().c_str() ));
    return result;
}

#if(1)
int InternetKseChannelProcessor::handleShortSellingInfo(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_SHORT_SELLING_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] Skip : %s, %d : EXTURE_PLUS_KSE_SHORT_SELLING_INFORMATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_SHORT_SELLING_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseShortSellingInformation shortSellingInfoRec;
    ACE_OS::memcpy(&shortSellingInfoRec, packet.c_str(), packet.length());

    ACE_CString issueCode(shortSellingInfoRec.issueCode, sizeof ( shortSellingInfoRec.issueCode ));
    ACE_CString shortSellingDebtSecuritiesAskTradingVolume(shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingVolume, sizeof ( shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingVolume ));
    ACE_CString shortSellingDebtSecuritiesAskTradingValue(shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingValue, sizeof ( shortSellingInfoRec.shortSellingDebtSecuritiesAskTradingValue ));
    ACE_CString upTickRuleAppliedCoveredShortSellingTradingVolume(shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingVolume, sizeof ( shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingVolume ));
    ACE_CString upTickRuleAppliedCoveredShortSellingTradingValue(shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingValue, sizeof ( shortSellingInfoRec.upTickRuleAppliedCoveredShortSellingTradingValue ));
    ACE_CString upTickRuleUnappliedCoveredShortSellingTradingVolume(shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingVolume, sizeof ( shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingVolume ));
    ACE_CString upTickRuleUnappliedCoveredShortSellingTradingValue(shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingValue, sizeof ( shortSellingInfoRec.upTickRuleUnappliedCoveredShortSellingTradingValue ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tshortSellingDebtSecuritiesAskTradingVolume:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), shortSellingDebtSecuritiesAskTradingVolume.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tshortSellingDebtSecuritiesAskTradingValue:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), shortSellingDebtSecuritiesAskTradingValue.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleAppliedCoveredShortSellingTradingVolume:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleAppliedCoveredShortSellingTradingVolume.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleAppliedCoveredShortSellingTradingValue:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleAppliedCoveredShortSellingTradingValue.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleUnappliedCoveredShortSellingTradingVolume:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleUnappliedCoveredShortSellingTradingVolume.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tupTickRuleUnappliedCoveredShortSellingTradingValue:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str(), upTickRuleUnappliedCoveredShortSellingTradingValue.c_str() ));

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
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
    int result = sendPacket(ACE_CString(buf, SHORT_SELLING_INFO_SIZE), PACKET_SHORT_SELLING_INFO, EXCHANGE_KSE);

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleShortSellingInfo] issueCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , result ));
    printPacketShortSellingInfo(recShortSelling);
    return ( result );
}
#endif

int InternetKseChannelProcessor::handleQuantityAllocation(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_QUANTITY_ALLOCATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] Skip : %s, %d : EXTURE_PLUS_KSE_QUANTITY_ALLOCATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_QUANTITY_ALLOCATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseQuantityAllocation allocationRec;
    ACE_OS::memcpy(&allocationRec, packet.c_str(), packet.length());

    //2012.05.31
    //배분정보 전문
    //- 시가등이 상/하한가로 결정이 되어 상하한가 매수/매도 주문에 대해 일정량의 수량을 순차적으로 배분하여 체결시키는 경우 제공
    //- 거래중지후 최초가격이 상/하한가로 결정되는 경우 제공

    //[영향도]
    //- 시가가 상/하한가 일때 체결이 분산되어 체결될때 제공되는 것으로서 전문데이터를 통한 별도의 서비스 가능성은 현재 없음
    //    - 데이터가 배분개시, 배분 종료 정보라서 별도 필요성은 현재 없는 것으로 판단
    //- 추후 서비스 가능성에 대비하여, 데이터 수신 및 파싱 처리만 구현(Tickerplant) 

    ACE_CString dataCategory(allocationRec.dataCategory, sizeof ( allocationRec.dataCategory ));
    ACE_CString issueCode(allocationRec.issueCode, sizeof ( allocationRec.issueCode ));
    ACE_CString serialNo(allocationRec.serialNo, sizeof ( allocationRec.serialNo ));
    ACE_CString boardID(allocationRec.boardID, sizeof ( allocationRec.boardID ));
    ACE_CString allocationStartEnd(allocationRec.allocationStartEnd, sizeof ( allocationRec.allocationStartEnd ));
    ACE_CString allocationTypeCode(allocationRec.allocationTypeCode, sizeof ( allocationRec.allocationTypeCode ));
    ACE_CString timeForAllocationEnd(allocationRec.timeForAllocationEnd, sizeof ( allocationRec.timeForAllocationEnd ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] serialNo:[%s]\n" , getCurrentTimestamp().c_str() , serialNo.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] boardID:[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] allocationStartEnd:[%s]\n" , getCurrentTimestamp().c_str() , allocationStartEnd.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] allocationTypeCode:[%s]\n" , getCurrentTimestamp().c_str() , allocationTypeCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleQuantityAllocation] timeForAllocationEnd:[%s]\n" , getCurrentTimestamp().c_str() , timeForAllocationEnd.c_str() ));

    int result = 0;
    return result;
}

int InternetKseChannelProcessor::handleETF_PDF(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_ETF_PDF_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleETF_PDF] Skip : %s, %d : EXTURE_PLUS_KSE_ETF_PDF_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_ETF_PDF_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseETF_PDF pdfRec;
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

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleETF_PDF] dataCategory:[%s]\tetfCode[%s]\tdataSeqNumber:[%s]\tdate:[%s]\ttransferAgentNumber:[%s]\tcompositionIssueNumber:[%s]\tcompositionIssueCode:[%s]\toneCUUnitShare[%s]\tcompositionIssueMarketType:[%s]\tcompositionIssueName:[%s]\tparValueAmount:[%s]\tprofitDistributionBasisDate:[%s]\tappraisedValue:[%s]\n" , 
		getCurrentTimestamp().c_str() , 
		dataCategory.c_str() , 
		etfCode.c_str() , 
		dataSeqNumber.c_str() , 
		date.c_str() , 
		transferAgentNumber.c_str() , 
		compositionIssueNumber.c_str() , 
		compositionIssueCode.c_str() , 
		oneCUUnitShare.c_str() , 
		compositionIssueMarketType.c_str() , 
		compositionIssueName.c_str() , 
		parValueAmount.c_str() , 
		profitDistributionBasisDate.c_str() , 
		appraisedValue.c_str() ));

    int result = 0;
    return result;
}

int InternetKseChannelProcessor::handleKospi200FutureIndex(const ACE_CString &packet)
{
#if(1)
	if ( EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE != static_cast<int>(packet.length()) )
	{
		ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleKospi200FutureIndex] Skip : %s, %d : EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_TOTAL_KSE_INDEX_SIZE , packet.length() , packet.c_str() ), -1);
	}
#endif

    // log frame count status
    LogFrameCount(packet.substr(0, 2).c_str());

    ExturePlusTotalKseIndex totalkse;
	ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

    ExturePlusKseIndex kse;

	::memcpy(kse.time, totalkse.time, sizeof(kse.time));
	::memcpy(kse.index, totalkse.index, sizeof(kse.index));
	::memcpy(kse.sign, totalkse.sign, sizeof(kse.sign));
	::memcpy(kse.gap, totalkse.gap, sizeof(kse.gap));
	::memcpy(kse.tradeVolume, totalkse.tradeVolume, sizeof(kse.tradeVolume));
	::memcpy(kse.tradeAmount, totalkse.tradeAmount, sizeof(kse.tradeAmount));

    Trade trade;
    ACE_CString symbol = "KRF001000000";

    int hasValue = tradeMap_->find(symbol, trade, ALLOCATOR::instance());

    // common
    ACE_CString upDown(kse.sign, 1);
    ACE_CString volume(kse.tradeVolume, sizeof ( kse.tradeVolume ));
    trade.market = getMarketStepInIndex(ACE_CString(kse.time, sizeof ( kse.time )));
    trade.upDown = getUpDownInIndex(upDown);
    trade.accmVolume = atof(volume.c_str());
    trade.amount = atof(ACE_CString(kse.tradeAmount, sizeof kse.tradeAmount).c_str());

#if(1)
    trade.close = atoi(ACE_CString(kse.index, sizeof kse.index).c_str()) * 100;
    int gap = atoi(ACE_CString(kse.gap, sizeof kse.gap).c_str()) * 100;
#endif

    if ( ( trade.upDown == UPDOWN_DOWN ) || ( trade.upDown == UPDOWN_DOWN_LIMIT ) )
    {
        gap = -gap;
    }

    trade.ydayClose = trade.close - gap;
    trade.openInterest = 0;
    trade.tradeVolume = trade.accmVolume - getTotalAccmVolume(symbol);

    ACE_CString frameId = packet.substr(0, 2);

    int tickTime = getTickTime(ACE_CString(kse.time, sizeof kse.time), frameId);

    if ( trade.tradeVolume == -1 )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleIndex] Skip : %s,%d : net volume error symbol:[%s] trade.tradeVolume:[%f]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , symbol.c_str() , trade.tradeVolume ), -1);
    }

    setTotalAccmVolume(symbol, trade.accmVolume);
    setTotalAccmAmount(symbol, trade.amount);

    if ( hasValue == -1 )
    {
        trade.subtype = TRADESUBTYPE_TRADE;
        trade.exchange = EXCHANGE_KSE;
        trade.symbolType = SYMBOL_INDEX;
        trade.decimalPoint = DECIMAL_2;
        trade.tradeTime = tickTime;

        memcpy(&trade.symbol, symbol.c_str(), sizeof trade.symbol);

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

        if ( ( tickTime / 60 == previousTime / 60 ) && ( trade.volumeMin != 0 ) )
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
    memcpy(buf, &trade, TRADE_SIZE);
    int result = sendPacket(ACE_CString(buf, TRADE_SIZE), PACKET_TRADE, EXCHANGE_KSE);

	ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKospi200FutureIndex] dataClass:[%.*s],infoMarketClass:[%.*s],dataID:[%.*s],standardCode:[%.*s],symbol:[%s]\tresult:[%d]\n" , 
		getCurrentTimestamp().c_str(), 
		sizeof(totalkse.dataClass),totalkse.dataClass, 
		sizeof(totalkse.infoMarketClass),totalkse.infoMarketClass, 
		sizeof(totalkse.dataID),totalkse.dataID, 
		sizeof(totalkse.standardCode),totalkse.standardCode, 
		symbol.c_str() , 
		result ));

    printPacketTrade(trade);

    return result;

}

#if(1)
int InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_KOSPI_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] Skip : %s, %d : EXTURE_PLUS_KSE_KOSPI_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_KOSPI_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseKOSPIVolatilityInterruptionPerInstrument rawVIRec;
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

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] issueSeqNo:[%s]\n" , getCurrentTimestamp().c_str() , issueSeqNo.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] boardID:[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] tradeExecutionProcessingTime:[%s]\n" , getCurrentTimestamp().c_str() , tradeExecutionProcessingTime.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] removalTimeOfVI:[%s]\n" , getCurrentTimestamp().c_str() , removalTimeOfVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] VIApplicationCategoryCode:[%s]\n" , getCurrentTimestamp().c_str() , VIApplicationCategoryCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] VITypeCode:[%s]\n" , getCurrentTimestamp().c_str() , VITypeCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] basePriceToTriggerStaticVI:[%s]\n" , getCurrentTimestamp().c_str() , basePriceToTriggerStaticVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] basePriceToTriggerDynamicVI:[%s]\n" , getCurrentTimestamp().c_str() , basePriceToTriggerDynamicVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] VITriggeringPrice:[%s]\n" , getCurrentTimestamp().c_str() , VITriggeringPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] disparateRatioStaticVI:[%s]\n" , getCurrentTimestamp().c_str() , disparateRatioStaticVI.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] disparateRatioDynamicVI:[%s]\n" , getCurrentTimestamp().c_str() , disparateRatioDynamicVI.c_str() ));

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

//    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] viRec.VIApplicationCategoryCode:[%c]\n" , getCurrentTimestamp().c_str() , viRec.VIApplicationCategoryCode ));

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
    int resultVIRec = sendPacket(ACE_CString(buf, VOLATILITY_INTERRUPTION_PER_INSTRUMENT2_SIZE), PACKET_VOLATILITY_INTERRUPTION_PER_INSTRUMENT2, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIVolatilityInterruptionPerInstrument] issueCode:[%s]\tresultVIRec:[%d]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , resultVIRec ));
    return resultVIRec;
}
#endif

int InternetKseChannelProcessor::handleKoscomLineLKInfo(const ACE_CString &packet)
{

    if ( EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KSE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleKoscomLineLKInfo] Skip : %s,%d : EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KSE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KSE_SIZE , packet.length() , packet.c_str() ), -1);
        return 0;
    }

    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKoscomLineLKInfo] packet:[%s][%d]\n" , getCurrentTimestamp().c_str() , packet.c_str() , packet.length() ));

    ExturePlusKoscomLineLKInfo_KSE rawRec;
    ::memset(&rawRec, 0, sizeof(ExturePlusKoscomLineLKInfo_KSE));
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
    int result = sendPacket(ACE_CString(bufSendPacket, KOSCOM_LINE_LK_INFO_SIZE), PACKET_KOSCOM_LINE_LK_INFO, EXCHANGE_KSE);

    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKoscomLineLKInfo] result:[%d]\thostname:[%s]\trecvAddr:[%s]\tcommType:[%d]\trecvTime:[%d]\tlkMsgRaw:[%s]\n" , getCurrentTimestamp().c_str() , result , ACE_CString(lkRec.hostname_, sizeof ( lkRec.hostname_ )).c_str() , ACE_CString(lkRec.addrInfo_, sizeof ( lkRec.addrInfo_ )).c_str() , lkRec.commType_ , lkRec.recvTime_ , ACE_CString(lkRec.msgRaw_, sizeof ( lkRec.msgRaw_ )).c_str() ));
    return result;
}

int InternetKseChannelProcessor::handleETNTransferAgentBatchData(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_ETN_TRANSFER_AGENT_BATCH_DATA_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleETNTransferAgentBatchData] Skip : %s, %d : EXTURE_PLUS_KSE_ETN_TRANSFER_AGENT_BATCH_DATA_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_ETN_TRANSFER_AGENT_BATCH_DATA_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseETNTransferAgentBatchData rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString seqNumber(rawRec.seqNumber, sizeof ( rawRec.seqNumber ));
    ACE_CString finalIndexValue(rawRec.finalIndexValue, sizeof ( rawRec.finalIndexValue ));
    ACE_CString indexValueInSumOfMoney(rawRec.indexValueInSumOfMoney, sizeof ( rawRec.indexValueInSumOfMoney ));
    ACE_CString previousDayTaxableBasicPrice(rawRec.previousDayTaxableBasicPrice, sizeof ( rawRec.previousDayTaxableBasicPrice ));
    ACE_CString previousDayTaxableBasicPriceBeforeDividend(rawRec.previousDayTaxableBasicPriceBeforeDividend, sizeof ( rawRec.previousDayTaxableBasicPriceBeforeDividend ));
    ACE_CString previousDayCashDividendPrice(rawRec.previousDayCashDividendPrice, sizeof ( rawRec.previousDayCashDividendPrice ));
    ACE_CString aDayBeforePreviousDayTaxableBasicPrice(rawRec.aDayBeforePreviousDayTaxableBasicPrice, sizeof ( rawRec.aDayBeforePreviousDayTaxableBasicPrice ));
    ACE_CString volatilityFuturesType(rawRec.volatilityFuturesType, sizeof ( rawRec.volatilityFuturesType ));
    ACE_CString minimumQuantityOfCall(rawRec.minimumQuantityOfCall, sizeof ( rawRec.minimumQuantityOfCall ));
    ACE_CString interestRateOfCall(rawRec.interestRateOfCall, sizeof ( rawRec.interestRateOfCall ));
    ACE_CString expenses(rawRec.expenses, sizeof ( rawRec.expenses ));

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleETNTransferAgentBatchData] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
        return 0;
    }

    ETNTransferAgentBatchData batchData;
    ::memset(&batchData, 0, sizeof(ETNTransferAgentBatchData));

    int recvTime = (int) ( ::time(0) );

    ::memcpy(& ( batchData.symbol ), issueCode.c_str(), issueCode.length());
    batchData.registerDt = recvTime;
    batchData.finalIndexValue = ::atof(finalIndexValue.c_str());
    if ( batchData.finalIndexValue != 0 )
    {
        batchData.finalIndexValue = batchData.finalIndexValue / 100.0;
    }

    batchData.indexValueInSumOfMoney = ::atof(indexValueInSumOfMoney.c_str());

    batchData.previousDayTaxableBasicPrice = ::atof(previousDayTaxableBasicPrice.c_str());
    if ( batchData.previousDayTaxableBasicPrice != 0 )
    {
        batchData.previousDayTaxableBasicPrice = batchData.previousDayTaxableBasicPrice / 100.0;
    }

    batchData.previousDayTaxableBasicPriceBeforeDividend = ::atof(previousDayTaxableBasicPriceBeforeDividend.c_str());
    if ( batchData.previousDayTaxableBasicPriceBeforeDividend != 0 )
    {
        batchData.previousDayTaxableBasicPriceBeforeDividend = batchData.previousDayTaxableBasicPriceBeforeDividend / 100.0;
    }

    batchData.previousDayCashDividendPrice = ::atof(previousDayCashDividendPrice.c_str());
    if ( batchData.previousDayCashDividendPrice != 0 )
    {
        batchData.previousDayCashDividendPrice = batchData.previousDayCashDividendPrice / 100.0;
    }

    batchData.aDayBeforePreviousDayTaxableBasicPrice = ::atof(aDayBeforePreviousDayTaxableBasicPrice.c_str());
    if ( batchData.aDayBeforePreviousDayTaxableBasicPrice != 0 )
    {
        batchData.aDayBeforePreviousDayTaxableBasicPrice = batchData.aDayBeforePreviousDayTaxableBasicPrice / 100.0;
    }

    batchData.volatilityFuturesType = ::atoi(volatilityFuturesType.c_str());
    batchData.minimumQuantityOfCall = ::atoi(minimumQuantityOfCall.c_str());

    batchData.interestRateOfCall = ::atof(interestRateOfCall.c_str());
    if ( batchData.interestRateOfCall != 0 )
    {
        batchData.interestRateOfCall = batchData.interestRateOfCall / 100000000.0;
    }

    batchData.expenses = ::atof(expenses.c_str());
    if ( batchData.expenses != 0 )
    {
        batchData.expenses = batchData.expenses / 100.0;
    }

    printPacketETNTransferAgentBatchData(batchData);

    char buf[ETN_TRANSFER_AGENT_BATCH_DATA_SIZE];
    ::memset(&buf, 0, ETN_TRANSFER_AGENT_BATCH_DATA_SIZE);
    ::memcpy(&buf, &batchData, ETN_TRANSFER_AGENT_BATCH_DATA_SIZE);
    int resultBatchData = sendPacket(ACE_CString(buf, ETN_TRANSFER_AGENT_BATCH_DATA_SIZE), PACKET_ETN_TRANSFER_AGENT_BATCH_DATA, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleETNTransferAgentBatchData] issueCode:[%s]\tresultBatchData:[%d]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , resultBatchData ));

    return resultBatchData;
}

int InternetKseChannelProcessor::handleETNIndexCompositionConstituents(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleETNIndexCompositionConstituents] Skip : %s, %d : EXTURE_PLUS_KSE_ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseETNIndexCompositionConstituents rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString ETNIssueCode(rawRec.ETNIssueCode, sizeof ( rawRec.ETNIssueCode ));
    ACE_CString dataSeqNumber(rawRec.dataSeqNumber, sizeof ( rawRec.dataSeqNumber ));
    ACE_CString date(rawRec.date, sizeof ( rawRec.date ));

    ACE_CString officeConsignmentCompanyRegistrationNumber(rawRec.officeConsignmentCompanyRegistrationNumber, sizeof ( rawRec.officeConsignmentCompanyRegistrationNumber ));
    ACE_CString numberOfCompositionConstituents(rawRec.numberOfCompositionConstituents, sizeof ( rawRec.numberOfCompositionConstituents ));
    ACE_CString compositionConstituentsCode(rawRec.compositionConstituentsCode, sizeof ( rawRec.compositionConstituentsCode ));
    ACE_CString nameOfCompositionConstituents(rawRec.nameOfCompositionConstituents, sizeof ( rawRec.nameOfCompositionConstituents ));
    ACE_CString compositionRate(rawRec.compositionRate, sizeof ( rawRec.compositionRate ));

    if ( ETNIssueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleETNIndexCompositionConstituents] ETNIssueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , ETNIssueCode.c_str() ));
        return 0;
    }

    ETNIndexCompositionConstituents constituent;
    ::memset(&constituent, 0, sizeof(ETNIndexCompositionConstituents));

    ::memcpy(& ( constituent.symbol ), ETNIssueCode.c_str(), ETNIssueCode.length());
    constituent.registerDt = (int) ( ::time(0) );
    ::memcpy(& ( constituent.date ), date.c_str(), date.length());
    ::memcpy(& ( constituent.officeConsignmentCompanyRegistrationNumber ), officeConsignmentCompanyRegistrationNumber.c_str(), officeConsignmentCompanyRegistrationNumber.length());
    constituent.numberOfCompositionConstituents = ::atoi(numberOfCompositionConstituents.c_str());
    ::memcpy(& ( constituent.compositionConstituentsCode ), compositionConstituentsCode.c_str(), compositionConstituentsCode.length());
    ::memcpy(& ( constituent.nameOfCompositionConstituents ), nameOfCompositionConstituents.c_str(), nameOfCompositionConstituents.length());
    constituent.compositionRate = ::atof(compositionRate.c_str());
    if ( constituent.compositionRate != 0 )
    {
        constituent.compositionRate = constituent.compositionRate / 100.0;
    }

    printPacketETNIndexCompositionConstituents(constituent);

    char buf[ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE];
    ::memset(&buf, 0, ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE);
    ::memcpy(&buf, &constituent, ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE);
    int resultConstituent = sendPacket(ACE_CString(buf, ETN_INDEX_COMPOSITION_CONSTITUENTS_SIZE), PACKET_ETN_INDEX_COMPOSITION_CONSTITUENTS, EXCHANGE_KSE);

    return resultConstituent;
}

int InternetKseChannelProcessor::handleETN_IIV(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_ETN_IIV_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleETN_IIV] Skip : %s, %d : EXTURE_PLUS_KSE_ETN_IIV_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_ETN_IIV_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseETN_IIV rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString ETNIssueCode(rawRec.ETNIssueCode, sizeof ( rawRec.ETNIssueCode ));
    ACE_CString hours(rawRec.hours, sizeof ( rawRec.hours ));
    ACE_CString previousDayIV(rawRec.previousDayIV, sizeof ( rawRec.previousDayIV ));
    ACE_CString duringMarketHoursFinalIV(rawRec.duringMarketHoursFinalIV, sizeof ( rawRec.duringMarketHoursFinalIV ));

    if ( ETNIssueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleETN_IIV] ETNIssueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , ETNIssueCode.c_str() ));
        return 0;
    }

    ETN_IIV iiv;
    ::memset(&iiv, 0, sizeof(ETN_IIV));

    ::memcpy(& ( iiv.symbol ), ETNIssueCode.c_str(), ETNIssueCode.length());
    iiv.registerDt = getTickTime(hours, "S3");
    iiv.previousDayIV = ::atof(previousDayIV.c_str());
    if ( iiv.previousDayIV != 0 )
    {
        iiv.previousDayIV = iiv.previousDayIV / 100.0;
    }

    iiv.duringMarketHoursFinalIV = ::atof(duringMarketHoursFinalIV.c_str());
    if ( iiv.duringMarketHoursFinalIV != 0 )
    {
        iiv.duringMarketHoursFinalIV = iiv.duringMarketHoursFinalIV / 100.0;
    }

    printPacketETN_IIV(iiv);

    char buf[ETN_IIV_SIZE];
    ::memset(&buf, 0, ETN_IIV_SIZE);
    ::memcpy(&buf, &iiv, ETN_IIV_SIZE);
    int resultIIV = sendPacket(ACE_CString(buf, ETN_IIV_SIZE), PACKET_ETN_IIV, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleETN_IIV] ETNIssueCode:[%s]\tresultIIV:[%d]\n" , getCurrentTimestamp().c_str() , ETNIssueCode.c_str() , resultIIV ));

    return resultIIV;
}

#if(1)
int InternetKseChannelProcessor::handleKOSPIIssueEventInformation(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_KOSPI_ISSUE_EVENT_INFORMATION_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleKOSPIIssueEventInformation] Skip : %s, %d : EXTURE_PLUS_KSE_KOSPI_ISSUE_EVENT_INFORMATION_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_KOSPI_ISSUE_EVENT_INFORMATION_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseKOSPIIssueEventInformation rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString eventTypeCode(rawRec.eventTypeCode, sizeof ( rawRec.eventTypeCode ));
    ACE_CString eventOccurrenceCauseCode(rawRec.eventOccurrenceCauseCode, sizeof ( rawRec.eventOccurrenceCauseCode ));
    ACE_CString startDate(rawRec.startDate, sizeof ( rawRec.startDate ));
    ACE_CString expirationDate(rawRec.expirationDate, sizeof ( rawRec.expirationDate ));

    if ( issueCode == "999999999999" )
    {
        ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIIssueEventInformation] issueCode:[%s] dummy data skip......\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
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

    int result = sendPacket(ACE_CString(buf, KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE), PACKET_KOSPI_KOSDAQ_ISSUE_EVENT_INFORMATION, EXCHANGE_KSE);
    //ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleKOSPIIssueEventInformation] issueCode:[%s]\tresult:[%d]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() , result ));
    return result;
}
#endif

int InternetKseChannelProcessor::handleDeterminedBasePrice(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_KOSPI_DETERMINED_BASE_PRICE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] Skip : %s, %d : EXTURE_PLUS_KSE_KOSPI_DETERMINED_BASE_PRICE_SIZE[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_KOSPI_DETERMINED_BASE_PRICE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);
    /*
     * 규정에는 위와같이 표현되어 있으며 공통점은 상하한가가 없는 종목들임
     ※ 중복데이터 : 중복처리 무방
     */
    ExturePlusKseKOSPIDeterminedBasePrice rawRec;
    ACE_OS::memcpy(&rawRec, packet.c_str(), packet.length());

    ACE_CString dataCategory(rawRec.dataCategory, sizeof ( rawRec.dataCategory ));
    ACE_CString issueCode(rawRec.issueCode, sizeof ( rawRec.issueCode ));
    ACE_CString boardID(rawRec.boardID, sizeof ( rawRec.boardID ));
    ACE_CString basisPrice(rawRec.basisPrice, sizeof ( rawRec.basisPrice ));
    ACE_CString upperLimitPriceOfBasisPrice(rawRec.upperLimitPriceOfBasisPrice, sizeof ( rawRec.upperLimitPriceOfBasisPrice ));
    ACE_CString lowerLimitPriceOfBasisPrice(rawRec.lowerLimitPriceOfBasisPrice, sizeof ( rawRec.lowerLimitPriceOfBasisPrice ));

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] dataCategory:[%s]\n" , getCurrentTimestamp().c_str() , dataCategory.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] issueCode:[%s]\n" , getCurrentTimestamp().c_str() , issueCode.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] boardID:[%s]\n" , getCurrentTimestamp().c_str() , boardID.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] basisPrice:[%s]\n" , getCurrentTimestamp().c_str() , basisPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] upperLimitPriceOfBasisPrice:[%s]\n" , getCurrentTimestamp().c_str() , upperLimitPriceOfBasisPrice.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleDeterminedBasePrice] lowerLimitPriceOfBasisPrice:[%s]\n" , getCurrentTimestamp().c_str() , lowerLimitPriceOfBasisPrice.c_str() ));

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

    int result = sendPacket(ACE_CString(buf, DETERMINED_BASIC_PRICE_SIZE), PACKET_DETERMINED_BASIS_PRICE, EXCHANGE_KSE);
    return ( result );
}

int InternetKseChannelProcessor::handleIssueInformationDisclosure(const ACE_CString &packet)
{
    if ( EXTURE_PLUS_KSE_ISSUE_INFORMATION_DISCLOSURE_SIZE != static_cast<int>(packet.length()) )
    {
        ACE_ERROR_RETURN( ( LM_ERROR , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] Skip : %s, %d : EXTURE_PLUS_KSE_ISSUE_INFORMATION_DISCLOSURE_SIZE:[%d] != packet.length()[%d] packet:[%s]\n" , getCurrentTimestamp().c_str() , __FILE__ , __LINE__ , EXTURE_PLUS_KSE_ISSUE_INFORMATION_DISCLOSURE_SIZE , packet.length() , packet.c_str() ), -1);
    }

    // log frame count status
    ACE_CString frameId(packet.substr(0, 2));
    LogFrameCount(frameId);

    ExturePlusKseIssueInformationDisclosure rawRec;
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

    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] data_category:[%s]\n" , getCurrentTimestamp().c_str() , data_category.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] issue_code:[%s]\n" , getCurrentTimestamp().c_str() , issue_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] issue_seq_no:[%s]\n" , getCurrentTimestamp().c_str() , issue_seq_no.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] disclosure_data_type_code:[%s]\n" , getCurrentTimestamp().c_str() , disclosure_data_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] board_id:[%s]\n" , getCurrentTimestamp().c_str() , board_id.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] basis_price:[%s]\n" , getCurrentTimestamp().c_str() , basis_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] upper_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , upper_limit_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] lower_limit_price:[%s]\n" , getCurrentTimestamp().c_str() , lower_limit_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] evaluation_price:[%s]\n" , getCurrentTimestamp().c_str() , evaluation_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] highest_order_price:[%s]\n" , getCurrentTimestamp().c_str() , highest_order_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] lowest_order_price:[%s]\n" , getCurrentTimestamp().c_str() , lowest_order_price.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] opening_price_becomes_basis_price_type:[%s]\n" , getCurrentTimestamp().c_str() , opening_price_becomes_basis_price_type.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] back_door_listing:[%s]\n" , getCurrentTimestamp().c_str() , back_door_listing.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] par_value_change_type_code:[%s]\n" , getCurrentTimestamp().c_str() , par_value_change_type_code.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] lot_size:[%s]\n" , getCurrentTimestamp().c_str() , lot_size.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] number_of_listed_stocks:[%s]\n" , getCurrentTimestamp().c_str() , number_of_listed_stocks.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] designation:[%s]\n" , getCurrentTimestamp().c_str() , designation.c_str() ));
    ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::handleIssueInformationDisclosure] closing_price_possibility_in_pre_off_hours_session:[%s]\n" , getCurrentTimestamp().c_str() , closing_price_possibility_in_pre_off_hours_session.c_str() ));

    int result = 0;
    return ( result );
}

#if(0)
int InternetKseChannelProcessor::processPacket(const ACE_CString &packet)
{
    ACE_CString frameID(packet.substr(0, 2));
    ACE_CString informationCategoryAndMarketCategory(packet.substr(2, 3));
    ACE_CString trID(packet.substr(0, 5));
	ACE_CString dataType(packet.substr(0, 5));
    ACE_CString marketClass(packet.substr(4, 1));

	int hasValue;
	ExturePlusKseMaster kseUsage;

	if(dataType=="A001S")
	{
		MasterKseProcessor masterProc(frameID, packet, getSerial());
		if ( masterProc.isValidPacket() == true )
        {
            int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));

			memcpy(&kseUsage, packet.c_str(), packet.length());
			ACE_CString stockCode1(kseUsage.stockCode, sizeof(kseUsage.stockCode));

			hasValue = masterMapKse_->find(stockCode1, kseUsage, ALLOCATOR::instance());

			if ( hasValue == -1 )
			{
				masterMapKse_->bind(ACE_CString(stockCode1.c_str(), ALLOCATOR::instance()), kseUsage, ALLOCATOR::instance());
			}
        }
	}
	else if(dataType=="CA01S")
	{
		ExturePlusKseJisuMaster ksejisu;
        memcpy(&ksejisu, packet.c_str(), packet.length());

		ACE_CString stockCode2(ksejisu.stockCode, sizeof(ksejisu.stockCode));
		hasValue = masterMapKse_->find(stockCode2, kseUsage, ALLOCATOR::instance());

		if ( hasValue == -1 )
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::masterMapKse_->find] Error symbol:[%s] hasValue:[%d]\n" , getCurrentTimestamp().c_str() , stockCode2.c_str() , hasValue ));

			return(0);
		}
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.dataClass),kseUsage.dataClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.infoMarketClass),kseUsage.infoMarketClass));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.distributeStockIndex),kseUsage.distributeStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.distributeTotalStockIndex),kseUsage.distributeTotalStockIndex));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.sendDate),kseUsage.sendDate));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.stockCode),kseUsage.stockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.stockSeq),kseUsage.stockSeq));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.abbrStockCode),kseUsage.abbrStockCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.abbrStockNameKor),kseUsage.abbrStockNameKor));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.abbrStockNameEng),kseUsage.abbrStockNameEng));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.infoDivisionGroupNo),kseUsage.infoDivisionGroupNo));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.MarketProductGroupID),kseUsage.MarketProductGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.stockGroupID),kseUsage.stockGroupID));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isUnitTrade),kseUsage.isUnitTrade));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.exClassCode),kseUsage.exClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.faceValueChangeClassCode),kseUsage.faceValueChangeClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isOpenPriceBecomeStdPrice),kseUsage.isOpenPriceBecomeStdPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isRevaluationStockReason),kseUsage.isRevaluationStockReason));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isStandardPriceChangeStock),kseUsage.isStandardPriceChangeStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.randomEndTriggerConditionCode),kseUsage.randomEndTriggerConditionCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isMarketAlarmDangerNotice),kseUsage.isMarketAlarmDangerNotice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.marketAlarmClassCode),kseUsage.marketAlarmClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isCorporateGovernanceFine),kseUsage.isCorporateGovernanceFine));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isManagementStock),kseUsage.isManagementStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isInsincerityPublicNewsAppoint),kseUsage.isInsincerityPublicNewsAppoint));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isBackDoorListing),kseUsage.isBackDoorListing));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isTradeStop),kseUsage.isTradeStop));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.standardIndustryCode),kseUsage.standardIndustryCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.SmallMediumEnterprisesIs),kseUsage.SmallMediumEnterprisesIs));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.isCorporateGovernanceIndexStock),kseUsage.isCorporateGovernanceIndexStock));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.investOrganClassCode),kseUsage.investOrganClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.standardPrice),kseUsage.standardPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayClosePriceClassCode),kseUsage.ydayClosePriceClassCode));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayClosePrice),kseUsage.ydayClosePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayAccmVolume),kseUsage.ydayAccmVolume));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.ydayAccmAmount),kseUsage.ydayAccmAmount));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.upLimitPrice),kseUsage.upLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.downLimitPrice),kseUsage.downLimitPrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.substitutePrice),kseUsage.substitutePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.faceValue),kseUsage.faceValue));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.issuePrice),kseUsage.issuePrice));
		ACE_DEBUG( ( LM_DEBUG , "[InternetKseChannelProcessor::masterMapKse_->find][%.*s]\n", sizeof(kseUsage.listingDate),kseUsage.listingDate));

		MasterKseProcessor masterProc(frameID, packet, getSerial(), kseUsage);
		if ( masterProc.isValidPacket() == true )
        {
			int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , 
				getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));
        }
	}
#if(1)
	else if(dataType=="A003S")
	{
		MasterKseProcessor masterProc(frameID, packet, getSerial());
		if ( masterProc.isValidPacket() == true )
        {
            int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));

			memcpy(&kseUsage, packet.c_str(), packet.length());
			ACE_CString stockCode1(kseUsage.stockCode, sizeof(kseUsage.stockCode));

			hasValue = masterMapKse_->find(stockCode1, kseUsage, ALLOCATOR::instance());

			if ( hasValue == -1 )
			{
				masterMapKse_->bind(ACE_CString(stockCode1.c_str(), ALLOCATOR::instance()), kseUsage, ALLOCATOR::instance());
			}
        }
	}
	else if(dataType=="A004S")
	{
		MasterKseProcessor masterProc(frameID, packet, getSerial());
		if ( masterProc.isValidPacket() == true )
        {
            int result = masterProc.sendPacket();
            ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] masterProc.sendPacket() symbol:[%s] result:[%d]\n" , getCurrentTimestamp().c_str() , masterProc.getSymbol().c_str() , result ));

			memcpy(&kseUsage, packet.c_str(), packet.length());
			ACE_CString stockCode1(kseUsage.stockCode, sizeof(kseUsage.stockCode));

			hasValue = masterMapKse_->find(stockCode1, kseUsage, ALLOCATOR::instance());

			if ( hasValue == -1 )
			{
				masterMapKse_->bind(ACE_CString(stockCode1.c_str(), ALLOCATOR::instance()), kseUsage, ALLOCATOR::instance());
			}
        }
	}
#endif
#if(1)
	else if(dataType=="A703S")
	{
		handleMarketOperationTS(packet);
	}
	else if(dataType=="A704S")
	{
		handleMarketOperationTS(packet);
	}
#endif
#if(1)
	else if(dataType=="A303S")
	{
		handleTrade(packet);
	}
	else if(dataType=="A304S")
	{
		handleTrade(packet);
	}
#endif
#if(1)
	else if(dataType=="B903S")
    {
        handleSecuritiesTrade(packet);
    }
	else if(dataType=="B904S")
    {
        handleSecuritiesTrade(packet);
    }
#endif
#if(1)
	else if(dataType=="M403S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
	else if(dataType=="M404S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
#endif
#if(1)
	else if(dataType=="I603S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if(dataType=="I604S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
#endif
#if(1)
	else if ( dataType == "B703S" ) //(증권C) STK : B702S, B703S, B704S
    {
        //NONE
    }
	else if ( dataType == "B704S" ) //(증권C) STK : B702S, B703S, B704S
    {
        //NONE
    }
#endif
#if(1)
	else if ( dataType == "B203S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleElwRecoveryTotalTrade(packet);
    }
	else if ( dataType == "B204S" ) //(증권C) STK : B202S, B203S, B204S
    {
        handleElwRecoveryTotalTrade(packet);
    }
#endif
	else if(dataType=="C401S")
	{
		handleBulkTrade(packet);
	}
	else if(dataType=="A301S")
	{
		handleTrade(packet);
	}
	else if(dataType=="A401S")
    {
        handleDeterminedBasePrice(packet);
    }
	else if(dataType=="B601S")
    {
        handleQuote10(packet);
    }
	else if(dataType=="B901S")
    {
        handleSecuritiesTrade(packet);
    }
	else if(dataType=="A801S")
    {
        handleIssueInformationDisclosure(packet);
    }
	else if(dataType=="J001S")
    {
        handleProgramTradeTotal(packet);
    }
	else if(dataType=="C301S")
    {
        handleProgramTrade(packet);
    }
	else if(dataType=="O601S")
    {
        handleQuantityAllocation(packet);
    }
	else if(dataType=="B201S")
	{
		handleRecoveryTotalTrade(packet);
	}
	else if(dataType=="B501S")
	{
		handleUpDown(packet);
	}
	else if(dataType=="B501S")
	{
		handleUpDown(packet);
	}
	else if(dataType=="F000S")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="E900S")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="F000Q")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="E900Q")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="F000X")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="E900X")
	{
		handlePublicNews(packet);
	}
	else if(dataType=="I601S")
	{
		handleKOSPIIssueEventInformation(packet);
	}
	else if(dataType=="I801S")
	{
		handleShortSellingInfo(packet);
	}
	else if(dataType=="M401S")
	{
		handleMarketOperationScheduleDisclosure(packet);
	}
	else if(dataType=="R801S")
	{
		handleKOSPIVolatilityInterruptionPerInstrument(packet);
	}
#if(0)
//코스콤 정보,ETN 사무수탁정보             ,S104S
//코스콤 정보,ETP정보,ETN 기초지수 구성종목,S204S
//코스콤 정보,ETP정보,ETN IIV              ,S304S
//코스콤 정보,ETP정보,ETF 사무수탁배치     ,N803S
//코스콤 정보,ETP정보,ETF PDF              ,F803S
#endif
	else if(dataType=="S104S")
	{
		handleETNTransferAgentBatchData(packet);
	}
	else if(dataType=="S204S")
	{
		handleETNIndexCompositionConstituents(packet);
	}
	else if(dataType=="S304S")
	{
		handleETN_IIV(packet);
	}
	else if(dataType=="N803S")
	{
		handleETFWorkEntrustmentBatch(packet);
	}
	else if(dataType=="F803S")
	{
		handleETF_PDF(packet);
	}
#if(0)
//코스콤 정보,외국인 투자정보	코스피 외국인 종목별투자정보(확정치),F101S
//코스콤 정보,외국인 투자정보	코스닥 외국인 종목별투자정보(확정치),F101Q
//코스콤 정보,외국인 투자정보	코스피 외국인 확정치데이터재전송,F401S
//코스콤 정보,외국인 투자정보	코스닥 외국인 확정치데이터재전송,F401Q
#endif
	else if(dataType=="F101S")
	{
		handleForeignerMaster(packet);
	}
	else if(dataType=="F101Q")
	{
		handleForeignerMaster(packet);
	}
	else if(dataType=="F401S")
	{
		handleForeignerMasterUpdate(packet);
	}
	else if(dataType=="F401Q")
	{
		handleForeignerMasterUpdate(packet);
	}
	else if(dataType=="B801S")
	{
		handleQuoteBefore(packet);
	}
	else if(dataType=="C001S")
	{
		handleInvestorIndex(packet);
	}
	else if(dataType=="A701S")
	{
		handleMarketOperationTS(packet);
	}
#if(1)
	else if(dataType=="IA000")
	{
		ExturePlusTotalKseIndex totalkse;
		ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

		ACE_CString jisuFrameId(totalkse.dataID, sizeof ( totalkse.dataID ));
		jisuFrameId = getSymbolFrameId(jisuFrameId);

		ACE_DEBUG( ( LM_DEBUG , "[%s][%.*s][%.*s] [InternetKseChannelProcessor::processPacket] jisuFrameId Data:[%s]\n" , 
			getCurrentTimestamp().c_str() , 
			sizeof(totalkse.dataClass),totalkse.dataClass,
			sizeof(totalkse.dataID),totalkse.dataID,
			jisuFrameId.c_str() ));

		if ( jisuFrameId == "C8")	    //KRX100지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D0")	//KOSPI지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D1")	//KOSPI예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "D2")	//KOSPI200지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D4")	//KOSPI100/50지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T7")	//KTOP30지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T8")	//KTOP30예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "N9")	//동일가중지수	
		{
			handleEquallyWeightedIndex(packet);
		}
		else if ( jisuFrameId == "O1")	//동일가중예상지수	
		{
			handleEquallyWeightedIndexForecast(packet);
		}
	}
	else if(dataType=="IB000")
	{
		ExturePlusTotalKseIndex totalkse;
		ACE_OS::memcpy(&totalkse, packet.c_str(), packet.length());

		ACE_CString jisuFrameId(totalkse.dataID, sizeof ( totalkse.dataID ));
		jisuFrameId = getSymbolFrameId(jisuFrameId);

		ACE_DEBUG( ( LM_DEBUG , "[%s][%.*s][%.*s] [InternetKseChannelProcessor::processPacket] jisuFrameId Data:[%s]\n" , 
			getCurrentTimestamp().c_str() , 
			sizeof(totalkse.dataClass),totalkse.dataClass,
			sizeof(totalkse.dataID),totalkse.dataID,
			jisuFrameId.c_str() ));

		if ( jisuFrameId == "C8")	    //KRX100지수
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D0")	//KOSPI지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D1")	//KOSPI예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "D2")	//KOSPI200지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "D4")	//KOSPI100/50지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T7")	//KTOP30지수	
		{
			handleIndex(packet);
		}
		else if ( jisuFrameId == "T8")	//KTOP30예상지수	
		{
			handleIndexForecast(packet);
		}
		else if ( jisuFrameId == "N9")	//동일가중지수	
		{
			handleEquallyWeightedIndex(packet);
		}
		else if ( jisuFrameId == "O1")	//동일가중예상지수	
		{
			handleEquallyWeightedIndexForecast(packet);
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
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] polling Data:[%s]\n" , getCurrentTimestamp().c_str() , packet.c_str() ));
		}
		else if ( frameID == "ZZ" )
		{
			// 지수 리커버리(내부)
			handleCustomIndexRecovery(packet);
		}
		else
		{
			ACE_DEBUG( ( LM_DEBUG , "[%s] [InternetKseChannelProcessor::processPacket] trID:[%s]\n" , getCurrentTimestamp().c_str() , trID.c_str() ));
		}
	}
    return 0;
}
#endif

ACE_CString InternetKseChannelProcessor::getIndexSymbol(int code, const ACE_CString &frameId)
{
    // 예상지수 처리를 위해 프레임 ID 별로 코드값을 따로 간다.
    // KRIXXX000000  // 일반지수
    // KRYXXX000000  // 예상지수

    int index = code;        // default
    char buf[13];
    ::memset(buf, 0, sizeof ( buf ));

    // KOSPI 예상지수
    if ( frameId == "D1" )        //KOSPI 예상지수 구스펙(Y1) 신스펙(D1)
    {
        sprintf(buf, "KRY%03d000000", index); // 001
    }
    else if ( frameId == "D2" )
    {
        index = index - 28;
        index = TICKERPLANT_BASECODE_KOSPI200 + index; //TICKERPLANT_BASECODE_KOSPI200 = 200
        sprintf(buf, "KRI%03d000000", index);
    }
    else if ( frameId == "D4" )
    {
        if ( code == 35 )
        {
            index = TICKERPLANT_BASECODE_KOSPI100; //TICKERPLANT_BASECODE_KOSPI100 = 100
        }
        else if ( code == 36 )
        {
            index = TICKERPLANT_BASECODE_KOSPI50; //TICKERPLANT_BASECODE_KOSPI50 = 50
        }
        sprintf(buf, "KRI%03d000000", index);
    }
    else if ( frameId == "D6" )
    {
        index = TICKERPLANT_BASECODE_KODI;
        sprintf(buf, "KRI%03d000000", index);
    }
    else if ( frameId == "D8" )
    {
        index = TICKERPLANT_BASECODE_KOGI;
        sprintf(buf, "KRI%03d000000", index);
    }
    else if ( frameId == "C8" ) // KRX 100지수 구스펙(I0) 신스펙(C8)
    {
        index = 0;
        sprintf(buf, "KRI%03d000000", index);
    }
    else if ( frameId == "T7" ) // 48   KTOP30지수
    {
        index = TICKERPLANT_BASECODE_KTOP30;
        sprintf(buf, "KRI%03d000000", index);
    }
    else if ( frameId == "T8" ) // 49   KTOP30예상지수
    {
        index = TICKERPLANT_BASECODE_KTOP30;
        sprintf(buf, "KRY%03d000000", index);
    }
    else
    {
        sprintf(buf, "KRI%03d000000", index);
    }
    ACE_CString symbol = ACE_CString(buf);
    return ( symbol );
}

BYTE InternetKseChannelProcessor::getMarketInTrade(const ACE_CString& raw)
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

BYTE InternetKseChannelProcessor::getMarketStepInIndex(const ACE_CString& time)
{
    BYTE result = MARKET_IN;
    if ( ( time == "JUNJJJ" ) || ( time == "EXTJJJ" ) )
    {
        result = MARKET_END;
    }
    return result;
}

BYTE InternetKseChannelProcessor::getUpDownInTrade(const ACE_CString& raw)
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

BYTE InternetKseChannelProcessor::getUpDownInIndex(const ACE_CString& raw)
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

BYTE InternetKseChannelProcessor::getMarketStatusInMarket(const ACE_CString& raw)
{
    BYTE result = static_cast<BYTE>(atoi(raw.c_str()));
    return result;
}

BYTE InternetKseChannelProcessor::getMarketInRecoveryTrade(const ACE_CString& boardID, const ACE_CString& boardEventID)
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
    // ACE_DEBUG((LM_DEBUG, "[%s] [InternetKseChannelProcessor::getMarketInRecoveryTrade] stockMarketOperationCode:[%s]\tregularOvertimeClassCode:[%s]\tresult:[%d]\n", getCurrentTimestamp().c_str(), stockMarketOperationCode.c_str(), regularOvertimeClassCode.c_str(), result));

    return result;
}

BYTE InternetKseChannelProcessor::getExhaustInForeigner(const ACE_CString& raw)
{
    BYTE result = static_cast<BYTE>(atoi(raw.c_str()));
    return result;
}

BYTE InternetKseChannelProcessor::getSign(const ACE_CString& raw)
{
    BYTE result = SIGN_NONE;
    if ( raw == "+" )
    {
        result = SIGN_PLUS;
    }
    else if ( raw == " " )
    {
        result = SIGN_MINUS;
    }
    return result;
}

BYTE InternetKseChannelProcessor::getMarketInQuote10(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = MARKET_IN;
    // marketStatusClassCode 60: 장종료시간외접수
    /*
     * 60:장종료후시간외접수
     65:장종료후시간외
     */
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

ACE_CString InternetKseChannelProcessor::getKospi200Type(const ACE_CString& raw)
{
    ACE_CString result;

    if ( raw == "2" )
    {
        result = "제조업";
    }
    else if ( raw == "3" )
    {
        result = "전기통신";
    }
    else if ( raw == "4" )
    {
        result = "건설";
    }
    else if ( raw == "5" )
    {
        result = "유통";
    }
    else if ( raw == "6" )
    {
        result = "금융";
    }
    else if ( raw == "" )
    {
        result = "";
    }

    return result;
}

int InternetKseChannelProcessor::getTickTime(const ACE_CString &timeStr, const ACE_CString &frameId)
{
    int hour = 0;
    int minute = 0;
    int second = 0;

    if ( timeStr.substr(3, 3) == "JJJ" )
    {
        // 장전 예상지수인 경우 09:00 을 끝으로 한다. by dong in 2008.02.01
        if ( frameId == "D1" )
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

BYTE InternetKseChannelProcessor::getStockType(const ACE_CString& raw)
{
    return ACE_OS::atoi(raw.c_str());
}

BYTE InternetKseChannelProcessor::getCommitType(const ACE_CString& raw)
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

BYTE InternetKseChannelProcessor::getNearSymbolType(const ACE_CString& raw)
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
BYTE InternetKseChannelProcessor::getSymbolType(char rawSymbolType)
{
    BYTE symbolType;

    switch ( rawSymbolType )
    {
        case '1' :
        case '2' :
            symbolType = SYMBOL_STOCK;
            break;
        default :
            symbolType = 255;
    }
    return symbolType;
}
#endif

#if(1)
BYTE InternetKseChannelProcessor::getSymbolType(char rawSymbolType)
{
    BYTE symbolType;

    switch ( rawSymbolType )
    {
        case 'S' :
		case 'X' :
        case 'Q' :
            symbolType = SYMBOL_STOCK;
            break;
        default :
            symbolType = 255;
    }
    return symbolType;
}
#endif

BYTE InternetKseChannelProcessor::getExchange(char rawSymbolType)
{
    return rawSymbolType == 'Q' ? EXCHANGE_KOSDAQ : EXCHANGE_KSE;
}

time_t InternetKseChannelProcessor::getModTime(time_t tradeTime)
{
    return tradeTime;
}

const std::vector<ACE_CString>& InternetKseChannelProcessor::getTradeTypeList()
{
    return tradeTypeList_;
}

void InternetKseChannelProcessor::initTradeTypeList()
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

BYTE InternetKseChannelProcessor::getMarketInTradeFixed(const ACE_CString& raw)
{
    // 1 : 시간외단일가개시
    BYTE result = MARKET_IN;
    // 0 : 초기값
    if ( raw == "0" )
    {
        result = MARKET_BEFORE;
    }
    // 2 : 시간외단일가마감
    else if ( raw == "2" )
    {
        result = MARKET_END;
    }
    return result;
}

BYTE InternetKseChannelProcessor::getConcurrent(const ACE_CString& boardID, const ACE_CString& sessionID)
{
    BYTE result = CONCURRENT_OFF;
    if ( boardID == "G1" ) //정규시간외구분코드가 1인경우(동시,접속 둘다 가능) 1 정규장 G1  유가/코스닥/파생/코넥스   개별경쟁거래
    {
        if ( sessionID == "10" ) //시가단일가는 ~09:00 까지. (10:시가단일가)
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

#if(0)
	ACE_CString indexConstKseMap1[498] = 
	{"KGG01P","KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G01P","K2G01P","K2G02P","K2G03P","K2S11P","K2S11P","K2S02P","K2S02P","K2S08P","K2S08P","K2S09P","K2S09P","K2S05P","K2S05P","K2S07P","K2S07P","K2S03P","K2S03P","K2S10P","K2S10P","K2S06P","K2S06P","K2S04P","K2S04P","K2S01P","K2S01P","K2W01P","K2W01P","K2W02P","K2W02P","K2W03P","K2W03P","XGW01P","XGW01P","XGG01P","XGG01P","X3G01P","X3G01P","XGS01P","XGS01P","XGS02P","XGS02P","XGS03P","XGS03P","XGS04P","XGS04P","XGS05P","XGS05P","XGS06P","XGS06P","XGS07P","XGS07P","XGS08P","XGS08P","XGS09P","XGS09P","XGS10P","XGS10P","XGS11P","XGS11P","XGS12P","XGS12P","XGS13P","XGS13P","XGS14P","XGS14P","XGS15P","XGS15P","XGS16P","XGS16P","XGS17P","XGS17P","X3E01P","X3E01P","XGE05P","XGE05P","QGG01P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS01P","QGS32P","QGS32P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG03P","QGG04P","QGG04P","QGG05P","QGG05P","QGG06P","QGG06P","NGG01P","NGG01P","K2B01P","KGD02P","KGD02P","KGD03P","KGD03P","K2B03P","K2T01P","K2E01P","K2E01P","K2E02P","K2E02P","K2W04P","K2W04P","KGD04P","KGD04P","K2G05P","K2G05P","K2G04P","K2G04P","K2G06P","K2G06P","K2G08P","K2G08P","K2G10P","K2G10P","K2D01P","K2D01P","K2D02P","K2D02P","KGD01P","KGD01P","XGE01P","XGE01P","XGE03P","XGE03P","XGE02P","XGE02P","XGB05P","XGE04P","XGE04P","XGT01P","XGT01P","XGT02P","XGT02P","XGT03P","XGT03P","XGT04P","XGT04P","XGT05P","XGT05P","X3S05P","X3S05P","X3S04P","X3S04P","X3S02P","X3S02P","X3S01P","X3S01P","X3S03P","X3S03P","X3S08P","X3S08P","X3S06P","X3S06P","X3S07P","X3S07P","XGG02P","XGG02P","K2Z01P","Q5G01P","Q5G01P","Q5S05P","Q5S05P","Q5S06P","Q5S06P","Q5S07P","Q5S07P","Q5S08P","Q5S08P","Q5S02P","Q5S02P","Q5S03P","Q5S03P","Q5S04P","Q5S04P","Q5E01P","Q5E01P","Q5W01P","K2G01T","K2G01T","K2G01N","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG01P","TGG02P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","KGG01T","QGG01T","QGG01T","X3G01T","X3G01T","Q5G01T","Q5G01T","KGD02T","KGD02T","KGD03T","KGD03T","K2S07T","K2S07T","K2S03T","K2S03T","K2S06T","K2S06T","K2S05T","K2S05T","K2S10T","K2S10T","K2S02T","K2S02T","K2S08T","K2S08T","K2S09T","K2S09T","K2S04T","K2S04T","K2S01T","K2S01T","K2S11T","K2S11T","K2G06T","K2G06T","K2G06N","K2G06N","K2G08T","K2G08T","K2G08N","K2G08N","K2G10T","K2G10T","K2G10N","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT06T","XGT08T","XGT08T","XGT10T","XGT10T","XGT06P","XGT06P","XGT08P","XGT08P","XGT10P","XGT10P","XGT07P","XGT07P","XGT09P","XGT09P","XGT11P","XGT11P","KGT01P","KGT01P","KGX01P"};
	ACE_CString indexConstKseMap2[498] = 
	{"KRD020020008","KRD020020008","KRD020020081","KRD020020099","KRD020020107","KRD020020115","KRD020020123","KRD020020131","KRD020020149","KRD020020156","KRD020020164","KRD020020172","KRD020020180","KRD020020198","KRD020020206","KRD020020214","KRD020020222","KRD020020230","KRD020020248","KRD020020255","KRD020020263","KRD020020271","KRD020020289","KRD020020297","KRD020020305","KRD020020313","KRD020020321","KRD020020016","KRD020020016","KRD020020024","KRD020020032","KRD020022327","KRD020022327","KRD020020339","KRD020020339","KRD020020347","KRD020020347","KRD020020354","KRD020020354","KRD020020362","KRD020020362","KRD020020370","KRD020020370","KRD020020388","KRD020020388","KRD020020396","KRD020020396","KRD020020404","KRD020020404","KRD020021386","KRD020021386","KRD020021394","KRD020021394","KRD020021048","KRD020021048","KRD020021055","KRD020021055","KRD020021063","KRD020021063","KRD020021071","KRD020021071","KRD020020073","KRD020020073","KRD020022087","KRD020022087","KRD020020842","KRD020020842","KRD020020859","KRD020020859","KRD020020867","KRD020020867","KRD020020875","KRD020020875","KRD020020891","KRD020020891","KRD020020909","KRD020020909","KRD020020925","KRD020020925","KRD020020933","KRD020020933","KRD020020958","KRD020020958","KRD020020966","KRD020020966","KRD020020974","KRD020020974","KRD020020982","KRD020020982","KRD020021741","KRD020021741","KRD020021758","KRD020021758","KRD020021766","KRD020021766","KRD020021774","KRD020021774","KRD020021782","KRD020021782","KRD020029330","KRD020029330","KRD020029348","KRD020029348","KRD020040006","KRD020040006","KRD020020438","KRD020020446","KRD020020453","KRD020020461","KRD020040022","KRD020040022","KRD020020479","KRD020020487","KRD020020495","KRD020020503","KRD020020511","KRD020020529","KRD020020537","KRD020020545","KRD020020552","KRD020020560","KRD020020578","KRD020020586","KRD020020594","KRD020020602","KRD020020610","KRD020020628","KRD020020636","KRD020020644","KRD020020651","KRD020020669","KRD020020677","KRD020020685","KRD020020693","KRD020020701","KRD020020719","KRD020020727","KRD020020735","KRD020020743","KRD020020750","KRD020020768","KRD020020776","KRD020020784","KRD020020792","KRD020020792","KRD020020800","KRD020020800","KRD020020818","KRD020020818","KRD020020826","KRD020020826","KRD020021089","KRD020021089","KRD020020412","KRD020021329","KRD020021329","KRD020021311","KRD020021311","KRD020021352","KRD020021402","KRD020022459","KRD020022459","KRD020029322","KRD020029322","KRD020029280","KRD020029280","KRD020022723","KRD020022723","KRD020022368","KRD020022368","KRD020022806","KRD020022806","KRD020022947","KRD020022947","KRD020022970","KRD020022970","KRD020023028","KRD020023028","KRD020022004","KRD020022004","KRD020022012","KRD020022012","KRD020021345","KRD020021345","KRD020021444","KRD020021444","KRD020021451","KRD020021451","KRD020021469","KRD020021469","KRD020021824","KRD020022061","KRD020022061","KRD020023085","KRD020023085","KRD020023127","KRD020023127","KRD020023119","KRD020023119","KRD020023101","KRD020023101","KRD020023093","KRD020023093","KRD020022228","KRD020022228","KRD020022236","KRD020022236","KRD020022244","KRD020022244","KRD020022251","KRD020022251","KRD020022269","KRD020022269","KRD020022475","KRD020022475","KRD020022483","KRD020022483","KRD020022491","KRD020022491","KRD020021360","KRD020021360","KRD020021410","KRD020021378","KRD020021378","KRD020021642","KRD020021642","KRD020021659","KRD020021659","KRD020021667","KRD020021667","KRD020021675","KRD020021675","KRD020021683","KRD020021683","KRD020021691","KRD020021691","KRD020021709","KRD020021709","KRD020022731","KRD020022731","KRD020021436","KRD020021477","KRD020021477","KRD020021485","KRD020021485","KRD020021113","KRD020021170","KRD020021121","KRD020021188","KRD020021105","KRD020021162","KRD020021303","KRD020021147","KRD020021097","KRD020021154","KRD020021139","KRD020021196","KRD020021204","KRD020021220","KRD020021238","KRD020021246","KRD020021253","KRD020021295","KRD020021261","KRD020021212","KRD020021279","KRD020021287","KRD020023713","KRD020020G06","KRD020020G22","KRD020020G48","KRD020023721","KRD020020G71","KRD020020G97","KRD020020GB1","KRD020023697","KRD020023705","KRD020023242","KRD020023259","KRD020023564","KRD020023572","KRD020023226","KRD020023622","KRD020023630","KRD020024117","KRD020023648","KRD020023218","KRD020023580","KRD020023598","KRD020023606","KRD020023614","KRD020023168","KRD020023176","KRD020023135","KRD020023143","KRD020023150","KRD020024083","KRD020021618","KRD020021626","KRD020021600","KRD020023184","KRD020023671","KRD020023689","KRD020023200","KRD020023531","KRD020023549","KRD020023556","KRD020021840","KRD020023234","KRD020021568","KRD020021576","KRD020021584","KRD020021592","KRD020029306","KRD020029314","KRD020023192","KRD020023267","KRD020023275","KRD020023283","KRD020021790","KRD020021790","KRD020021808","KRD020021808","KRD020021816","KRD020022715","KRD020021832","KRD020021899","KRD020021907","KRD020021972","KRD020021980","KRD020021998","KRD020021915","KRD020021923","KRD020021931","KRD020021949","KRD020021956","KRD020021964","KRD020022046","KRD020022053","KRD020022095","KRD020022707","KRD020022103","KRD020022111","KRD020022129","KRD020022137","KRD020022145","KRD020022277","KRD020022285","KRD020022293","KRD020022301","KRD020022319","KRD020022467","KRD020022509","KRD020022517","KRD020022525","KRD020022533","KRD020022541","KRD020022558","KRD020022566","KRD020022574","KRD020022582","KRD020022590","KRD020024026","KRD020023291","KRD020023309","KRD020024091","KRD020023317","KRD020023325","KRD020023333","KRD020023341","KRD020023358","KRD020023366","KRD020023374","KRD020023382","KRD020023390","KRD020024109","KRD020023408","KRD020023416","KRD020023424","KRD020023432","KRD020023440","KRD020023457","KRD020024034","KRD020023465","KRD020023473","KRD020024042","KRD020023481","KRD020023499","KRD020023507","KRD020024059","KRD020023515","KRD020023523","KRD020022350","KRD020022335","KRD020022343","KRD020022376","KRD020022384","KRD020022384","KRD020022392","KRD020022392","KRD020022418","KRD020022418","KRD020022400","KRD020022400","KRD020022434","KRD020022434","KRD020022442","KRD020022442","KRD020022814","KRD020022814","KRD020022822","KRD020022822","KRD020022830","KRD020022830","KRD020022848","KRD020022848","KRD020022855","KRD020022855","KRD020022863","KRD020022863","KRD020022871","KRD020022871","KRD020022889","KRD020022889","KRD020022897","KRD020022897","KRD020022905","KRD020022905","KRD020022913","KRD020022913","KRD020022954","KRD020022954","KRD020022962","KRD020022962","KRD020022988","KRD020022988","KRD020023002","KRD020023002","KRD020023036","KRD020023036","KRD020023051","KRD020023051","KRD020022608","KRD020022616","KRD020022624","KRD020022632","KRD020022657","KRD020022640","KRD020022665","KRD020022673","KRD020022681","KRD020022699","KRD020022798","KRD020022749","KRD020022756","KRD020022764","KRD020022772","KRD020022780","KRD020023077","KRD020023655","KRD020023663","KRD020024760","KRD020026047","KRD020026054","KRD020029264","KRD020029272","KRD020029249","KRD020029256","KRD020029231","KRD020029298","KRD020029355","KRD020029363","KRD020029371","KRD020029389","KRD020020CV8","KRD020020CW6","KRD020020CX4","KRD020020CN5","KRD020020CN5","KRD020020CP0","KRD020020CP0","KRD020020CQ8","KRD020020CQ8","KRD0200200F2","KRD0200200F2","KRD0200200H8","KRD0200200H8","KRD0200200K2","KRD0200200K2","KRD0200200G0","KRD0200200G0","KRD0200200J4","KRD0200200J4","KRD0200200L0","KRD0200200L0","KRD020020FR9","KRD020020FR9","KRD020020FS7"};
	ACE_CString indexConstKseMap3[498] = 
	{"IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","Z5000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000"};
	ACE_CString indexConstKseMap4[498] = 
	{"D0011","D1011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D2011","D3011","D4011","D4011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N9011","O1011","N9011","O1011","N9011","O1011","N9011","O1011","C8011","C9011","AA011","AB011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E5012","E4012","E5012","E4012","E5012","P9018","R7018","Q8011","S4011","V0011","S6011","V2011","T2011","U1011","BK011","BL011","BK011","BL011","BK011","BL011","BK011","BL011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","Z0011","Z1011","Z0011","Z1011","S7011","V4011","U2011","U5011","U2011","U5011","U2011","U5011","Y0011","Z8011","Z9011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","T7011","T8011","U0011","T9012","U4012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W8012","W9012","U8012","Z2011","Z3011","Z2011","Z3011","O2016","O2016","O3016","O3016","L4016","L4016","R6016","K2011","K9014","K9014","J3034","N0034","N0034","O8011","O8011","O8011","O8011","R0011","P5011","O7011","P8011","P8011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","S9014","S9014","T4014","T4014","T5016","T5016","U6016","U6016","U6016","U6016","U6016","U7016","U7016","U7016","U7016","U7016","U9012","U9012","V7011","V7011","V7011","V7011","V7011","V7011","V7011","V8011","V9011","V9011","W1024","W1024","W1024","W1024","W1024","W0014","X0016","X0016","X0016","X0016","X0016","X0016","X2124","X2124","X2124","X2124","X6019","X7019","X6019","X7019","X9034","BQ034","Y1034","Y2014","Y5034","Y6011","Y7016","Y7016","Y8034","Y8034","Y9011","Y9011","Y9011","Y9011","Z6011","Z7034","AD034","AD034","AE164","AE164","AE164","AE164","AK011","AI011","AN011","AO034","AO034","AP034","AP034","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AS016","AQ034","AR034","AV034","AW011","AX011","AY012","AZ012","BC011","BD011","BA012","BB012","BG011","BH011","BI011","BJ011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BO034","BO034","BO034","X0016","X0016","X0016","X0016","Y6011","Y6011","Y6011","Y6011","AI011","AI011","AI011","AI011","AI011","T5016","T1014","T1014","Z5011","Y6011","Y6011","AI011","AI011","AK011","AK011","AN011","V7011","AJ104","AJ104","W1024","W1024","Y6011","Y6011","Y6011","BE011","BF011","BE011","BF011","BE011","BF011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","BK011","BL011","V7011"};
	ACE_CString indexConstKseMap5[498] = 
	{"D0","D1","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D2","D3","D4","D4","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N9","O1","N9","O1","N9","O1","N9","O1","C8","C9","AA","AB","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E4","E5","E4","E4","E4","E4","E4","E5","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E5","E4","E5","E4","E5","E4","E5","P9","R7","Q8","S4","V0","S6","V2","T2","U1","BK","BL","BK","BL","BK","BL","BK","BL","AT","AU","AT","AU","AT","AU","AT","AU","AT","AU","Z0","Z1","Z0","Z1","S7","V4","U2","U5","U2","U5","U2","U5","Y0","Z8","Z9","AG","AH","AG","AH","AG","AH","AG","AH","AG","AH","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","T7","T8","U0","T9","U4","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W8","W9","U8","Z2","Z3","Z2","Z3","O2","O2","O3","O3","L4","L4","R6","K2","K9","K9","J3","N0","N0","O8","O8","O8","O8","R0","P5","O7","P8","P8","J2","J2","J2","J2","J2","J2","J2","J2","S9","S9","T4","T4","T5","T5","U6","U6","U6","U6","U6","U7","U7","U7","U7","U7","U9","U9","V7","V7","V7","V7","V7","V7","V7","V8","V9","V9","W1","W1","W1","W1","W1","W0","X0","X0","X0","X0","X0","X0","X2","X2","X2","X2","X6","X7","X6","X7","X9","BQ","Y1","Y2","Y5","Y6","Y7","Y7","Y8","Y8","Y9","Y9","Y9","Y9","Z6","Z7","AD","AD","AE","AE","AE","AE","AK","AI","AN","AO","AO","AP","AP","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AS","AQ","AR","AV","AW","AX","AY","AZ","BC","BD","BA","BB","BG","BH","BI","BJ","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BO","BO","BO","X0","X0","X0","X0","Y6","Y6","Y6","Y6","AI","AI","AI","AI","AI","T5","T1","T1","Z5","Y6","Y6","AI","AI","AK","AK","AN","V7","AJ","AJ","W1","W1","Y6","Y6","Y6","BE","BF","BE","BF","BE","BF","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","BK","BL","V7"};
#endif

#if(0)
	ACE_CString indexConstKseMap1[TOTALJISUCNT] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","XGD02P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","O2903P","F2X06P","O2X01P","MGA12P","FTX06T","FTX08T","GGS01P","O2904P","F3G01P","F3X01T","F3X02P","F3X03T","X3X01P","MGA13T","F2V02P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03T","FGA04T","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05T","F5901P","F5X05T","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","TGX01P","G2T01P","F2X40T","F2X41T","F5X06T","F5X07T","QGG11P","110043","110046","110043","110004","110007","110012","110014","110020","110021","110023","110037","110038","110039","110040","110041","110042","110044","110045","110049","110051","110052","110053","110056","110057","110058","110059","110060","110061","110062","110065","110066","110067","110068","110069","110070","110071","110072","110073","110074","110077","110078","110079","110080","110081","110082","110083","110084","110086","110087","110088","110089","110090","110091","110092","110093","110094","110095","110096","110097","110098","110099","110100","110101","110102","110103","110104","110105","110106","110107","110108","110109","110110","110111","110112","2P8802","2P8803","2P9259","2P9269","2P9258","2P9284","2P9206","2P9271","2P9234","2P9272","2P9263","2P9256","2P9239","2P9246","2P9247","2P9248","2P9260","2P9255","2P9265","2P9267","2P9266","2P9276","2P9277","2P9278","2P9279","2P9280","2P9281","2P9282","2P9283","2P9231","2P9235","2P9240","2P9275","2P9211","2P9242","2P9243","2P9274","2P9245","2P9262","2P9236","2P9251","2P9238","2P9264","2P9268","2P9229","2P9252","2P9233","2P9253","2P9221","2P9244","2P9222","2P9257","2P9241","2P9273","2P9207","2P9250","2P9237","2P9249","2P9210","2P9232","2P9254","2PB003","2PB101","2PB201","2PB211","2PB221","2PB226","2PB231","2PB232","2PB237","2PB238","2PB239","2PB241","2PB242","2PB243","2PB305","2PB306","2PB307","2PC007","2PC006","2PM128","2PM126","2PM127","2PM119","2PM121","2PM102","2PM104","2PM107","2PM109","2PM112","2PM114","2PM115","2PM116","2PM117","2PM118","2PM122","2PM123","2PM131","2PM124","2PM132","2PM125","2PM120","2PM129","2PM130","2PM134","2PM133","2PM001","2PR001","2PR101","120001","120002","120003","120004","120005","2PW006","120007","120008","120009","120010","120011","120012","120013","120014","120015","120016","120017","120018","120019","120020","120021","120901"};
	ACE_CString indexConstKseMap6[TOTALJISUCNT] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","165","132","133","134","142","136","411","412","413","414","415","351","352","353","354","355","356","357","358","600","167","203","212","213","214","215","216","217","218","331","204","175","176","301","302","303","304","001","002","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","001","001","001","002","002","002","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","707","731","708","821","312","313","003","709","304","306","307","308","305","822","732","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","003","005","286","287","422","423","189","601","602","601","004","007","012","014","020","021","023","037","038","039","040","041","042","044","045","049","051","052","053","056","057","058","059","060","061","062","065","066","067","068","069","070","071","072","073","074","077","078","079","080","081","082","083","084","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","802","803","259","269","258","284","206","271","234","272","263","256","239","246","247","248","260","255","265","267","266","276","277","278","279","280","281","282","283","231","235","240","275","211","242","243","274","245","262","236","251","238","264","268","229","252","233","253","221","244","222","257","241","273","207","250","237","249","210","232","254","003","101","201","211","221","226","231","232","237","238","239","241","242","243","305","306","307","007","006","128","126","127","119","121","102","104","107","109","112","114","115","116","117","118","122","123","131","124","132","125","120","129","130","134","133","001","001","101","001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","901"};
#endif


#define TOTALJISUCNT 379
#define ANOTHERJISUCNT 498

#if(1)
	ACE_CString indexConstKseMap0[ANOTHERJISUCNT] = 
    {"KGG01P","KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G01P","K2G01P","K2G02P","K2G03P","K2S11P","K2S11P","K2S02P","K2S02P","K2S08P","K2S08P","K2S09P","K2S09P","K2S05P","K2S05P","K2S07P","K2S07P","K2S03P","K2S03P","K2S10P","K2S10P","K2S06P","K2S06P","K2S04P","K2S04P","K2S01P","K2S01P","K2W01P","K2W01P","K2W02P","K2W02P","K2W03P","K2W03P","XGW01P","XGW01P","XGG01P","XGG01P","X3G01P","X3G01P","XGS01P","XGS01P","XGS02P","XGS02P","XGS03P","XGS03P","XGS04P","XGS04P","XGS05P","XGS05P","XGS06P","XGS06P","XGS07P","XGS07P","XGS08P","XGS08P","XGS09P","XGS09P","XGS10P","XGS10P","XGS11P","XGS11P","XGS12P","XGS12P","XGS13P","XGS13P","XGS14P","XGS14P","XGS15P","XGS15P","XGS16P","XGS16P","XGS17P","XGS17P","X3E01P","X3E01P","XGE05P","XGE05P","QGG01P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS01P","QGS32P","QGS32P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG03P","QGG04P","QGG04P","QGG05P","QGG05P","QGG06P","QGG06P","NGG01P","NGG01P","K2B01P","KGD02P","KGD02P","KGD03P","KGD03P","K2B03P","K2T01P","K2E01P","K2E01P","K2E02P","K2E02P","K2W04P","K2W04P","KGD04P","KGD04P","K2G05P","K2G05P","K2G04P","K2G04P","K2G06P","K2G06P","K2G08P","K2G08P","K2G10P","K2G10P","K2D01P","K2D01P","K2D02P","K2D02P","KGD01P","KGD01P","XGE01P","XGE01P","XGE03P","XGE03P","XGE02P","XGE02P","XGB05P","XGE04P","XGE04P","XGT01P","XGT01P","XGT02P","XGT02P","XGT03P","XGT03P","XGT04P","XGT04P","XGT05P","XGT05P","X3S05P","X3S05P","X3S04P","X3S04P","X3S02P","X3S02P","X3S01P","X3S01P","X3S03P","X3S03P","X3S08P","X3S08P","X3S06P","X3S06P","X3S07P","X3S07P","XGG02P","XGG02P","K2Z01P","Q5G01P","Q5G01P","Q5S05P","Q5S05P","Q5S06P","Q5S06P","Q5S07P","Q5S07P","Q5S08P","Q5S08P","Q5S02P","Q5S02P","Q5S03P","Q5S03P","Q5S04P","Q5S04P","Q5E01P","Q5E01P","Q5W01P","K2G01T","K2G01T","K2G01N","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG01P","TGG02P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","KGG01T","QGG01T","QGG01T","X3G01T","X3G01T","Q5G01T","Q5G01T","KGD02T","KGD02T","KGD03T","KGD03T","K2S07T","K2S07T","K2S03T","K2S03T","K2S06T","K2S06T","K2S05T","K2S05T","K2S10T","K2S10T","K2S02T","K2S02T","K2S08T","K2S08T","K2S09T","K2S09T","K2S04T","K2S04T","K2S01T","K2S01T","K2S11T","K2S11T","K2G06T","K2G06T","K2G06N","K2G06N","K2G08T","K2G08T","K2G08N","K2G08N","K2G10T","K2G10T","K2G10N","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT06T","XGT08T","XGT08T","XGT10T","XGT10T","XGT06P","XGT06P","XGT08P","XGT08P","XGT10P","XGT10P","XGT07P","XGT07P","XGT09P","XGT09P","XGT11P","XGT11P","KGT01P","KGT01P","KGX01P"};
	ACE_CString indexConstKseMap2[ANOTHERJISUCNT] = 
	{"KRD020020008","KRD020020008","KRD020020081","KRD020020099","KRD020020107","KRD020020115","KRD020020123","KRD020020131","KRD020020149","KRD020020156","KRD020020164","KRD020020172","KRD020020180","KRD020020198","KRD020020206","KRD020020214","KRD020020222","KRD020020230","KRD020020248","KRD020020255","KRD020020263","KRD020020271","KRD020020289","KRD020020297","KRD020020305","KRD020020313","KRD020020321","KRD020020016","KRD020020016","KRD020020024","KRD020020032","KRD020022327","KRD020022327","KRD020020339","KRD020020339","KRD020020347","KRD020020347","KRD020020354","KRD020020354","KRD020020362","KRD020020362","KRD020020370","KRD020020370","KRD020020388","KRD020020388","KRD020020396","KRD020020396","KRD020020404","KRD020020404","KRD020021386","KRD020021386","KRD020021394","KRD020021394","KRD020021048","KRD020021048","KRD020021055","KRD020021055","KRD020021063","KRD020021063","KRD020021071","KRD020021071","KRD020020073","KRD020020073","KRD020022087","KRD020022087","KRD020020842","KRD020020842","KRD020020859","KRD020020859","KRD020020867","KRD020020867","KRD020020875","KRD020020875","KRD020020891","KRD020020891","KRD020020909","KRD020020909","KRD020020925","KRD020020925","KRD020020933","KRD020020933","KRD020020958","KRD020020958","KRD020020966","KRD020020966","KRD020020974","KRD020020974","KRD020020982","KRD020020982","KRD020021741","KRD020021741","KRD020021758","KRD020021758","KRD020021766","KRD020021766","KRD020021774","KRD020021774","KRD020021782","KRD020021782","KRD020029330","KRD020029330","KRD020029348","KRD020029348","KRD020040006","KRD020040006","KRD020020438","KRD020020446","KRD020020453","KRD020020461","KRD020040022","KRD020040022","KRD020020479","KRD020020487","KRD020020495","KRD020020503","KRD020020511","KRD020020529","KRD020020537","KRD020020545","KRD020020552","KRD020020560","KRD020020578","KRD020020586","KRD020020594","KRD020020602","KRD020020610","KRD020020628","KRD020020636","KRD020020644","KRD020020651","KRD020020669","KRD020020677","KRD020020685","KRD020020693","KRD020020701","KRD020020719","KRD020020727","KRD020020735","KRD020020743","KRD020020750","KRD020020768","KRD020020776","KRD020020784","KRD020020792","KRD020020792","KRD020020800","KRD020020800","KRD020020818","KRD020020818","KRD020020826","KRD020020826","KRD020021089","KRD020021089","KRD020020412","KRD020021329","KRD020021329","KRD020021311","KRD020021311","KRD020021352","KRD020021402","KRD020022459","KRD020022459","KRD020029322","KRD020029322","KRD020029280","KRD020029280","KRD020022723","KRD020022723","KRD020022368","KRD020022368","KRD020022806","KRD020022806","KRD020022947","KRD020022947","KRD020022970","KRD020022970","KRD020023028","KRD020023028","KRD020022004","KRD020022004","KRD020022012","KRD020022012","KRD020021345","KRD020021345","KRD020021444","KRD020021444","KRD020021451","KRD020021451","KRD020021469","KRD020021469","KRD020021824","KRD020022061","KRD020022061","KRD020023085","KRD020023085","KRD020023127","KRD020023127","KRD020023119","KRD020023119","KRD020023101","KRD020023101","KRD020023093","KRD020023093","KRD020022228","KRD020022228","KRD020022236","KRD020022236","KRD020022244","KRD020022244","KRD020022251","KRD020022251","KRD020022269","KRD020022269","KRD020022475","KRD020022475","KRD020022483","KRD020022483","KRD020022491","KRD020022491","KRD020021360","KRD020021360","KRD020021410","KRD020021378","KRD020021378","KRD020021642","KRD020021642","KRD020021659","KRD020021659","KRD020021667","KRD020021667","KRD020021675","KRD020021675","KRD020021683","KRD020021683","KRD020021691","KRD020021691","KRD020021709","KRD020021709","KRD020022731","KRD020022731","KRD020021436","KRD020021477","KRD020021477","KRD020021485","KRD020021485","KRD020021113","KRD020021170","KRD020021121","KRD020021188","KRD020021105","KRD020021162","KRD020021303","KRD020021147","KRD020021097","KRD020021154","KRD020021139","KRD020021196","KRD020021204","KRD020021220","KRD020021238","KRD020021246","KRD020021253","KRD020021295","KRD020021261","KRD020021212","KRD020021279","KRD020021287","KRD020023713","KRD020020G06","KRD020020G22","KRD020020G48","KRD020023721","KRD020020G71","KRD020020G97","KRD020020GB1","KRD020023697","KRD020023705","KRD020023242","KRD020023259","KRD020023564","KRD020023572","KRD020023226","KRD020023622","KRD020023630","KRD020024117","KRD020023648","KRD020023218","KRD020023580","KRD020023598","KRD020023606","KRD020023614","KRD020023168","KRD020023176","KRD020023135","KRD020023143","KRD020023150","KRD020024083","KRD020021618","KRD020021626","KRD020021600","KRD020023184","KRD020023671","KRD020023689","KRD020023200","KRD020023531","KRD020023549","KRD020023556","KRD020021840","KRD020023234","KRD020021568","KRD020021576","KRD020021584","KRD020021592","KRD020029306","KRD020029314","KRD020023192","KRD020023267","KRD020023275","KRD020023283","KRD020021790","KRD020021790","KRD020021808","KRD020021808","KRD020021816","KRD020022715","KRD020021832","KRD020021899","KRD020021907","KRD020021972","KRD020021980","KRD020021998","KRD020021915","KRD020021923","KRD020021931","KRD020021949","KRD020021956","KRD020021964","KRD020022046","KRD020022053","KRD020022095","KRD020022707","KRD020022103","KRD020022111","KRD020022129","KRD020022137","KRD020022145","KRD020022277","KRD020022285","KRD020022293","KRD020022301","KRD020022319","KRD020022467","KRD020022509","KRD020022517","KRD020022525","KRD020022533","KRD020022541","KRD020022558","KRD020022566","KRD020022574","KRD020022582","KRD020022590","KRD020024026","KRD020023291","KRD020023309","KRD020024091","KRD020023317","KRD020023325","KRD020023333","KRD020023341","KRD020023358","KRD020023366","KRD020023374","KRD020023382","KRD020023390","KRD020024109","KRD020023408","KRD020023416","KRD020023424","KRD020023432","KRD020023440","KRD020023457","KRD020024034","KRD020023465","KRD020023473","KRD020024042","KRD020023481","KRD020023499","KRD020023507","KRD020024059","KRD020023515","KRD020023523","KRD020022350","KRD020022335","KRD020022343","KRD020022376","KRD020022384","KRD020022384","KRD020022392","KRD020022392","KRD020022418","KRD020022418","KRD020022400","KRD020022400","KRD020022434","KRD020022434","KRD020022442","KRD020022442","KRD020022814","KRD020022814","KRD020022822","KRD020022822","KRD020022830","KRD020022830","KRD020022848","KRD020022848","KRD020022855","KRD020022855","KRD020022863","KRD020022863","KRD020022871","KRD020022871","KRD020022889","KRD020022889","KRD020022897","KRD020022897","KRD020022905","KRD020022905","KRD020022913","KRD020022913","KRD020022954","KRD020022954","KRD020022962","KRD020022962","KRD020022988","KRD020022988","KRD020023002","KRD020023002","KRD020023036","KRD020023036","KRD020023051","KRD020023051","KRD020022608","KRD020022616","KRD020022624","KRD020022632","KRD020022657","KRD020022640","KRD020022665","KRD020022673","KRD020022681","KRD020022699","KRD020022798","KRD020022749","KRD020022756","KRD020022764","KRD020022772","KRD020022780","KRD020023077","KRD020023655","KRD020023663","KRD020024760","KRD020026047","KRD020026054","KRD020029264","KRD020029272","KRD020029249","KRD020029256","KRD020029231","KRD020029298","KRD020029355","KRD020029363","KRD020029371","KRD020029389","KRD020020CV8","KRD020020CW6","KRD020020CX4","KRD020020CN5","KRD020020CN5","KRD020020CP0","KRD020020CP0","KRD020020CQ8","KRD020020CQ8","KRD0200200F2","KRD0200200F2","KRD0200200H8","KRD0200200H8","KRD0200200K2","KRD0200200K2","KRD0200200G0","KRD0200200G0","KRD0200200J4","KRD0200200J4","KRD0200200L0","KRD0200200L0","KRD020020FR9","KRD020020FR9","KRD020020FS7"};
	ACE_CString indexConstKseMap3[ANOTHERJISUCNT] = 
	{"IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","J2000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","Z5000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000","IB000","IA000"};
	ACE_CString indexConstKseMap4[ANOTHERJISUCNT] = 
	{"D0011","D1011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D0011","D2011","D3011","D4011","D4011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N5011","N6011","N9011","O1011","N9011","O1011","N9011","O1011","N9011","O1011","C8011","C9011","AA011","AB011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E4012","E5012","E4012","E5012","E4012","E5012","E4012","E5012","P9018","R7018","Q8011","S4011","V0011","S6011","V2011","T2011","U1011","BK011","BL011","BK011","BL011","BK011","BL011","BK011","BL011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","AT011","AU011","Z0011","Z1011","Z0011","Z1011","S7011","V4011","U2011","U5011","U2011","U5011","U2011","U5011","Y0011","Z8011","Z9011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AG011","AH011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","AL011","AM011","T7011","T8011","U0011","T9012","U4012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W6012","W7012","W8012","W9012","U8012","Z2011","Z3011","Z2011","Z3011","O2016","O2016","O3016","O3016","L4016","L4016","R6016","K2011","K9014","K9014","J3034","N0034","N0034","O8011","O8011","O8011","O8011","R0011","P5011","O7011","P8011","P8011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","J2011","S9014","S9014","T4014","T4014","T5016","T5016","U6016","U6016","U6016","U6016","U6016","U7016","U7016","U7016","U7016","U7016","U9012","U9012","V7011","V7011","V7011","V7011","V7011","V7011","V7011","V8011","V9011","V9011","W1024","W1024","W1024","W1024","W1024","W0014","X0016","X0016","X0016","X0016","X0016","X0016","X2124","X2124","X2124","X2124","X6019","X7019","X6019","X7019","X9034","BQ034","Y1034","Y2014","Y5034","Y6011","Y7016","Y7016","Y8034","Y8034","Y9011","Y9011","Y9011","Y9011","Z6011","Z7034","AD034","AD034","AE164","AE164","AE164","AE164","AK011","AI011","AN011","AO034","AO034","AP034","AP034","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AJ104","AS016","AQ034","AR034","AV034","AW011","AX011","AY012","AZ012","BC011","BD011","BA012","BB012","BG011","BH011","BI011","BJ011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BG011","BH011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BI011","BJ011","BO034","BO034","BO034","X0016","X0016","X0016","X0016","Y6011","Y6011","Y6011","Y6011","AI011","AI011","AI011","AI011","AI011","T5016","T1014","T1014","Z5011","Y6011","Y6011","AI011","AI011","AK011","AK011","AN011","V7011","AJ104","AJ104","W1024","W1024","Y6011","Y6011","Y6011","BE011","BF011","BE011","BF011","BE011","BF011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","E0011","E1011","BK011","BL011","V7011"};
	ACE_CString indexConstKseMap5[ANOTHERJISUCNT] = 
	{"D0","D1","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D0","D2","D3","D4","D4","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N5","N6","N9","O1","N9","O1","N9","O1","N9","O1","C8","C9","AA","AB","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E4","E5","E4","E4","E4","E4","E4","E5","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E4","E5","E4","E5","E4","E5","E4","E5","P9","R7","Q8","S4","V0","S6","V2","T2","U1","BK","BL","BK","BL","BK","BL","BK","BL","AT","AU","AT","AU","AT","AU","AT","AU","AT","AU","Z0","Z1","Z0","Z1","S7","V4","U2","U5","U2","U5","U2","U5","Y0","Z8","Z9","AG","AH","AG","AH","AG","AH","AG","AH","AG","AH","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","AL","AM","T7","T8","U0","T9","U4","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W6","W7","W8","W9","U8","Z2","Z3","Z2","Z3","O2","O2","O3","O3","L4","L4","R6","K2","K9","K9","J3","N0","N0","O8","O8","O8","O8","R0","P5","O7","P8","P8","J2","J2","J2","J2","J2","J2","J2","J2","S9","S9","T4","T4","T5","T5","U6","U6","U6","U6","U6","U7","U7","U7","U7","U7","U9","U9","V7","V7","V7","V7","V7","V7","V7","V8","V9","V9","W1","W1","W1","W1","W1","W0","X0","X0","X0","X0","X0","X0","X2","X2","X2","X2","X6","X7","X6","X7","X9","BQ","Y1","Y2","Y5","Y6","Y7","Y7","Y8","Y8","Y9","Y9","Y9","Y9","Z6","Z7","AD","AD","AE","AE","AE","AE","AK","AI","AN","AO","AO","AP","AP","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AJ","AS","AQ","AR","AV","AW","AX","AY","AZ","BC","BD","BA","BB","BG","BH","BI","BJ","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BG","BH","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BI","BJ","BO","BO","BO","X0","X0","X0","X0","Y6","Y6","Y6","Y6","AI","AI","AI","AI","AI","T5","T1","T1","Z5","Y6","Y6","AI","AI","AK","AK","AN","V7","AJ","AJ","W1","W1","Y6","Y6","Y6","BE","BF","BE","BF","BE","BF","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","E0","E1","BK","BL","V7"};
#endif

#if(1)
	ACE_CString indexConstKseMap1[TOTALJISUCNT] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","XGD02P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG03P","GGG04P","GGG05P","GGG02P","GGG06P","GGG07P","GGG08P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","O2903P","F2X06P","O2X01P","MGA12P","FTX06T","FTX08T","GGS01P","O2904P","F3G01P","F3X01T","F3X02P","F3X03T","X3X01P","MGA13T","F2V02P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03T","FGA04T","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05T","F5901P","F5X05T","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","TGX01P","G2T01P","F2X40T","F2X41T","F5X06T","F5X07T","QGG11P"};
	ACE_CString indexConstKseMap6[TOTALJISUCNT] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","165","132","133","134","142","136","411","412","413","414","415","351","352","353","354","355","356","357","358","600","167","203","212","213","214","215","216","217","218","331","204","175","176","301","302","303","304","001","002","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","001","001","001","002","002","002","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","707","731","708","821","312","313","003","709","304","306","307","308","305","822","732","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","003","005","286","287","422","423","189"};
#endif

#if(1)
ACE_CString InternetKseChannelProcessor::getSymbolUpCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<TOTALJISUCNT; kk++)
	{
		if(raw == indexConstKseMap1[kk])
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
		return(indexConstKseMap6[ii]);
	}
}

ACE_CString InternetKseChannelProcessor::getSymbolFrameId(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<ANOTHERJISUCNT; kk++)
	{
		if(raw == indexConstKseMap0[kk])
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
		return(indexConstKseMap5[ii]);
	}
}
#endif






