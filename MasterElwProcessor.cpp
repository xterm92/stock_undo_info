// MasterElwProcessor.cpp: implementation of the MasterElwProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include <sstream>
#include <vector>
#include "PaxfeedPacket.h"
#include "PaxfeedPacketELW.h"
#include "PaxfeedPacketDefine.h"
#include "PaxfeedStringUtil.h"
#include "PaxfeedMasterDefine.h"
#include "PaxfeedMasterELWDefine.h"
#include "ExturePlusInternetElw.h"
#include "SimpleStringUtil.h"
#include "MasterElwProcessor.h"

#include <boost/algorithm/string.hpp>

using namespace paxfeed;

MasterElwProcessor::MasterElwProcessor(int serial) :
	MasterProcessor(serial) {

}

MasterElwProcessor::~MasterElwProcessor() {

}

#if(1)
int MasterElwProcessor::masterGroupCProc(const ACE_CString &packet) {
	ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::masterGroupCProc] BEGIN\n", getCurrentTimestamp().c_str()));

	bool isValidPacket = false;
	int result = 0;

    if ( EXTURE_PLUS_ELW_MASTER_SIZE != static_cast<int>(packet.length()) )
    {
        isValidPacket = false;
    }
    else
    {
        ExturePlusElwMaster elwData;
        ACE_OS::memcpy(&elwData, packet.c_str(), packet.length());

        ACE_CString dataClass(elwData.dataClass, sizeof elwData.dataClass);
        ACE_CString stockCode(elwData.stockCode, sizeof elwData.stockCode);
        ACE_CString abbrStockCode(elwData.abbrStockCode + 1, sizeof ( elwData.abbrStockCode ) - 1);
        ACE_CString abbrStockNameKor(elwData.abbrStockNameKor, sizeof ( elwData.abbrStockNameKor ));
        ACE_CString abbrStockNameEng(elwData.abbrStockNameEng, sizeof ( elwData.abbrStockNameEng ));
        ACE_CString ydayClosePrice(elwData.ydayClosePrice, sizeof ( elwData.ydayClosePrice ));
        ACE_CString upLimitPrice(elwData.upLimitPrice, sizeof ( elwData.upLimitPrice ));
        ACE_CString downLimitPrice(elwData.downLimitPrice, sizeof ( elwData.downLimitPrice ));
        ACE_CString standardPrice(elwData.standardPrice, sizeof ( elwData.standardPrice ));
        ACE_CString isManagementStock(elwData.isManagementStock, sizeof ( elwData.isManagementStock ));
        ACE_CString isTradeStop(elwData.isTradeStop, sizeof ( elwData.isTradeStop ));
        ACE_CString exClassCode(elwData.exClassCode, sizeof ( elwData.exClassCode ));
        ACE_CString faceValueChangeClassCode(elwData.faceValueChangeClassCode, sizeof ( elwData.faceValueChangeClassCode ));
        ACE_CString ydayAccmVolume(elwData.ydayAccmVolume, sizeof ( elwData.ydayAccmVolume ));
        ACE_CString ydayAccmAmount(elwData.ydayAccmAmount, sizeof ( elwData.ydayAccmAmount ));
        ACE_CString listingSize(elwData.listingSize, sizeof ( elwData.listingSize ));
        ACE_CString substitutePrice(elwData.substitutePrice, sizeof ( elwData.substitutePrice ));
        ACE_CString faceValue(elwData.faceValue, sizeof ( elwData.faceValue ) - 2);  // 뒤의 소수점 2자리는 무시
        ACE_CString lowestQuotePrice(elwData.lowestQuotePrice, sizeof ( elwData.lowestQuotePrice ));
        ACE_CString highestQuotePrice(elwData.highestQuotePrice, sizeof ( elwData.highestQuotePrice ));
        ACE_CString isInsincerityPublicNewsAppoint(elwData.isInsincerityPublicNewsAppoint, sizeof ( elwData.isInsincerityPublicNewsAppoint ));
        ACE_CString REITsClassCode(elwData.REITsClassCode, sizeof ( elwData.REITsClassCode ));
        ACE_CString capital(elwData.capital, sizeof ( elwData.capital ) - 3);  // 뒤의 소수점 3자리는 무시
        ACE_CString issuePrice(elwData.issuePrice, sizeof ( elwData.issuePrice ));
        ACE_CString isCorporateGovernanceFine(elwData.isCorporateGovernanceFine, sizeof ( elwData.isCorporateGovernanceFine ));
        ACE_CString marketAlarmClassCode(elwData.marketAlarmClassCode, sizeof elwData.marketAlarmClassCode);
        ACE_CString listingDate(elwData.listingDate, sizeof elwData.listingDate);
        ACE_CString ETFFollowingEarningRateMultiple(elwData.ETFFollowingEarningRateMultiple, sizeof ( elwData.ETFFollowingEarningRateMultiple ));
        ACE_CString ETFReplicationMethodTypeCode(elwData.ETFReplicationMethodTypeCode, ( sizeof elwData.ETFReplicationMethodTypeCode ));
        ACE_CString shortTermFeverishInstrumentTypeCode(elwData.shortTermFeverishInstrumentTypeCode, sizeof ( elwData.shortTermFeverishInstrumentTypeCode ));
        ACE_CString isClearanceTrade(elwData.isClearanceTrade, ( sizeof elwData.isClearanceTrade ));
        ACE_CString expirationDate(elwData.expirationDate, sizeof ( elwData.expirationDate ));
        ACE_CString distributeTypeCode(elwData.distributeTypeCode, sizeof ( elwData.distributeTypeCode ));
        ACE_CString expirationRedemptionPriceDecisionStartDate(elwData.expirationRedemptionPriceDecisionStartDate, sizeof ( elwData.expirationRedemptionPriceDecisionStartDate ));
        ACE_CString expirationRedemptionPriceDecisionEndDate(elwData.expirationRedemptionPriceDecisionEndDate, sizeof ( elwData.expirationRedemptionPriceDecisionEndDate ));
        ACE_CString isShortStockSellingPossibility(elwData.isShortStockSellingPossibility, sizeof ( elwData.isShortStockSellingPossibility ));
        ACE_CString lowLiquidity(elwData.lowLiquidity, sizeof ( elwData.lowLiquidity ));
        ACE_CString abnormalRise(elwData.abnormalRise, sizeof ( elwData.abnormalRise ));
        ACE_CString isOpenPriceBecomeStdPrice(elwData.isOpenPriceBecomeStdPrice, sizeof ( elwData.isOpenPriceBecomeStdPrice ));

        ACE_CString preferredStockClassCode(elwData.preferredStockClassCode, sizeof ( elwData.preferredStockClassCode ));
        ACE_CString stockType = getStockType(preferredStockClassCode);

        /*
         *
         * 18   임의종료발동조건코드  X   1   139 "단일가세선에서 임의종료의 발동조건.조건부발동(2)인경우 임의종료규칙에서 정의하는 가격요건을 충족하는지 판단 후 발동을 결정함.
         ##코드값## 0:미발동 1:발동 2:조건부발동(가격요건판단)"
         *
         * 일단 출력만 해본다.
         */
        ACE_CString randomEndTriggerConditionCode(elwData.randomEndTriggerConditionCode, sizeof ( elwData.randomEndTriggerConditionCode ));
        ACE_CString upperLimitQuantity(elwData.upperLimitQuantity, sizeof ( elwData.upperLimitQuantity ));
        ACE_CString isInvestmentPrecautionIssue(elwData.isInvestmentPrecautionIssue, sizeof ( elwData.isInvestmentPrecautionIssue ));

        /*
         * 2021.03.15 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */
        ACE_CString indexCalculationInstitution_code(elwData.indexCalculationInstitution_code, sizeof ( elwData.indexCalculationInstitution_code ));

        /*
         * 2021.07.19 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */

        /*
         * 2021.11.29 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */
        ACE_CString isSPAC_merger(elwData.isSPAC_merger, sizeof ( elwData.isSPAC_merger ));
		ACE_CString frameID = dataClass;

        try
        {
            CheckSize(packet.length(), EXTURE_PLUS_ELW_MASTER_SIZE);

            // log frame count status
            LogFrameCount(frameID);

            ExturePlusElwMaster elwData;
            ACE_OS::memcpy(&elwData, packet.c_str(), packet.length());

            ACE_CString stockCode(elwData.stockCode, sizeof elwData.stockCode);
            if ( stockCode == "999999999999" )
            {
                return(0);
            }

            bind(MASTER_SYMBOL, stockCode);
            bind(MASTER_EXCHANGE, EXCHANGE_KSE_STRING);
            bind(MASTER_SYMBOL_TYPE, SYMBOL_STOCK_STRING);

            char tempBuf[1024];
            ::memset(&tempBuf, 0, sizeof ( tempBuf ));
            ::sprintf(tempBuf, "%d", DECIMAL_0);
            bind(MASTER_DECIMAL_POINT, tempBuf);

            bind(MASTER_ABBR_SYMBOL, trim(ACE_CString(elwData.abbrStockCode + 1, sizeof ( elwData.abbrStockCode ) - 1)));
            bind(MASTER_NAME, trim(ACE_CString(elwData.abbrStockNameKor, sizeof ( elwData.abbrStockNameKor ))));

            bind(MASTER_ENG_NAME, trim(ACE_CString(elwData.abbrStockNameEng, sizeof ( elwData.abbrStockNameEng ))));

            ACE_CString symbolSubtype(elwData.stockGroupID, sizeof ( elwData.stockGroupID ));
            bind(MASTER_SYMBOL_SUBTYPE, getSymbolSubtype(symbolSubtype));

            bind(MASTER_YDAY_CLOSE, ACE_CString(elwData.ydayClosePrice, sizeof ( elwData.ydayClosePrice )));
            bind(MASTER_UP_LIMIT, ACE_CString(elwData.upLimitPrice, sizeof ( elwData.upLimitPrice )));
            bind(MASTER_DOWN_LIMIT, ACE_CString(elwData.downLimitPrice, sizeof ( elwData.downLimitPrice )));
            bind(MASTER_STD_PRICE, ACE_CString(elwData.standardPrice, sizeof ( elwData.standardPrice )));
            bind(MASTER_MANAGEMENT, getManagementType(ACE_CString(elwData.isManagementStock, sizeof ( elwData.isManagementStock ))));
            bind(MASTER_IS_MANAGEMENT, ACE_CString(elwData.isManagementStock, sizeof ( elwData.isManagementStock )));
            bind(MASTER_SUSPENSION, getSuspensionType(ACE_CString(elwData.isTradeStop, sizeof ( elwData.isTradeStop ))));
            bind(MASTER_IS_SUSPENSION, ACE_CString(elwData.isTradeStop, sizeof ( elwData.isTradeStop )));
            bind(MASTER_EX, getEx(ACE_CString(elwData.exClassCode, sizeof ( elwData.exClassCode ))));
            bind(MASTER_SPLITMERGE, getSplitMerge(ACE_CString(elwData.faceValueChangeClassCode, sizeof ( elwData.faceValueChangeClassCode ))));
            bind(MASTER_YDAY_VOLUME, ACE_CString(elwData.ydayAccmVolume, sizeof ( elwData.ydayAccmVolume )));
            bind(MASTER_YDAY_AMOUNT, ACE_CString(elwData.ydayAccmAmount, sizeof ( elwData.ydayAccmAmount )));
            bind(MASTER_LISTING_VOLUME, ACE_CString(elwData.listingSize, sizeof ( elwData.listingSize )));
            bind(MASTER_SUBSTITUE_PRICE, ACE_CString(elwData.substitutePrice, sizeof ( elwData.substitutePrice )));

            // bind(MASTER_PAR_PRICE, ACE_CString(elwData.faceValue, sizeof(elwData.faceValue)-3 )) ;  // 뒤의 소수점 3자리는 무시

            ACE_CString faceValue(elwData.faceValue, sizeof ( elwData.faceValue ));
            bind(MASTER_PAR_PRICE, getParPriceInteger(faceValue));  // 뒤의 소수점 3자리는 무시
            bind(MASTER_PAR_PRICE_REAL_NUMBER, getParPriceRealNumber(faceValue));

            ACE_CString evaluatePrice(elwData.evaluatePrice, sizeof ( elwData.evaluatePrice ));
            bind(MASTER_EVALUATION_PRICE, evaluatePrice);
            bind(MASTER_LOWEST_QUOTE_PRICE, lowestQuotePrice);
            bind(MASTER_HIGHEST_QUOTE_PRICE, highestQuotePrice);


            bind(MASTER_IS_INSINCERITY_DISCLOSURE, ACE_CString(elwData.isInsincerityPublicNewsAppoint, sizeof ( elwData.isInsincerityPublicNewsAppoint )));
            bind(MASTER_REITS, ACE_CString(elwData.REITsClassCode, sizeof ( elwData.REITsClassCode )));

            // 9차스펙 1 : 1주단위, 10 : 10주단위, 100 : 100주단위, 1000 : 1000주단위 getTradeUnit() 확인 필요.
            // 구스펙 : 매매수량단위.
            // 신스펙의 정규장매매수량단위와 시간외매매수량단위가 같은 값을 가진다.
            // 따라서 실제로 나누는 의미가 없을것이다.
            bind(MASTER_CAPITAL, ACE_CString(elwData.capital, sizeof ( elwData.capital ) - 3));            // 뒤의 소수점 3자리는 무시
			bind(MASTER_KOGI_TYPE, getKogiType(ACE_CString(elwData.isCorporateGovernanceIndexStock, sizeof elwData.isCorporateGovernanceIndexStock)));
            bind(MASTER_PREEMPTIVE_RIGHT_PRICE, ACE_CString(elwData.issuePrice, sizeof ( elwData.issuePrice )));

            // (유가) 배당지수종목여부(KODI)

            // (유가)지배구조지수종목여부(KOGI)
            // bind(MASTER_KOGI_TYPE, getKogiType(ACE_CString(elwData.isCorporateGovernanceIndexStock, sizeof(elwData.isCorporateGovernanceIndexStock)))) ;

            // elwData.isCorporateGovernanceIndexStock (지배구조지수조목여부는 filler 처리됨)
            // isKRXSRIGovernance 로 대체함 2012.09.14 시행

            bind(MASTER_CAUTION_TYPE, getInvestmentWarningType(ACE_CString(elwData.marketAlarmClassCode, sizeof elwData.marketAlarmClassCode)));
            bind(MASTER_REGISTER_DATE, ACE_CString(elwData.listingDate, sizeof elwData.listingDate));

            //// 상폐일자 => 신주 인수권 증서만 해당 된다.
            //ACE_CString delistingDate(elwData.delistingDate, sizeof(elwData.delistingDate));

            // 2013.02.26 정리매매여부 추가
            bind(MASTER_CLEAR_OFF_ALLOWANCE_TRADING, ACE_CString(elwData.isClearanceTrade, ( sizeof elwData.isClearanceTrade )));
            bind(MASTER_IS_CLEAR_OFF_ALLOWANCE_TRADING, ACE_CString(elwData.isClearanceTrade, ( sizeof elwData.isClearanceTrade )));

            // 2014.11.28 모의투자시스템을 위해 추가함
            // 단축코드(앞뒤 구분자를 포함한)
            bind(MASTER_ABBR_SYMBOL_FULL, trim(ACE_CString(elwData.abbrStockCode, sizeof ( elwData.abbrStockCode ))));

            // 재평가사유코드 모의투자지원을 위해 추가함(2014.12.12)
            ACE_CString reEvaluationReasonCode(elwData.isRevaluationStockReason, ( sizeof elwData.isRevaluationStockReason ));
            ACE_CString reEvaluationReason = getReValuationReason(reEvaluationReasonCode);
            bind(MASTER_RE_EVALUATION_REASON, reEvaluationReason);

            // 증자구분코드
            ACE_CString capitalIncreaseClassCode(elwData.capitalIncreaseClassCode, sizeof ( elwData.capitalIncreaseClassCode ));
            ACE_CString capitalIncreaseType = getMasterIncreaseType(capitalIncreaseClassCode);
            bind(MASTER_CAPITAL_INCREASE_TYPE, capitalIncreaseType);

            // 종류주권구분코드
            bind(MASTER_STOCK_TYPE, stockType);

            // 시가기준가종목여부(Y, N)
            bind(MASTER_IS_OPEN_PRICE_BECOME_STD_PRICE, getIsOpenPriceBecomeStdPrice(isOpenPriceBecomeStdPrice));

            // 공매도 가능여부
            bind(MASTER_IS_SHORT_STOCK_SELLING_POSSIBILITY, trim(isShortStockSellingPossibility));
            // 저유동성 여부
            bind(MASTER_IS_LOW_LIQUIDITY, trim(lowLiquidity));
            // 이상급등여부
            bind(MASTER_IS_ABNORMAL_RISE, trim(abnormalRise));

            // 상한수량(2018.09.17)
            /*
             * [KRX 문의사항]
             * 주문할때 낼 수 있는 최대 수량으로서,
             * 전에도 있었지만, KRX/KOSCOM 에서 별도로 공지하지 않았음
             * KRX 매매체결 시스템에서 내부적으로만 사용했음
             * 향후 주문수량 통제를 위해 공개함
             */
            bind(MASTER_UPPER_LIMIT_QUANTITY, trim(upperLimitQuantity));

            // 투자주의종목 여부(2020.11.12)
            bind(MASTER_IS_INVESTMENT_PRECAUTION_ISSUE, ACE_CString(elwData.isInvestmentPrecautionIssue, ( sizeof elwData.isInvestmentPrecautionIssue )));
            // 상장주식수부족종목 여부(2020.11.12)

            isValidPacket = true;
        }
        catch ( std::exception& e )
        {
            isValidPacket = false;
			ACE_DEBUG((LM_ERROR, "[%s] [MasterElwProcessor::masterGroupCProc] error occur e.what:[%s]\n", getCurrentTimestamp().c_str(), e.what()));
        }
		if (isValidPacket == true) {

#if(0)
			setPacketType (PACKET_ELW_ELW_BATCH_DATA);
#endif
			result = sendPacket();
		}
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::masterGroupCProc] isValidPacket:[%d]\tissue_code:[%s]\tresult:[%d]\n", 
		getCurrentTimestamp().c_str(), isValidPacket, stockCode.c_str(), result));
    }
	return (0);
}
#endif

ACE_CString MasterElwProcessor::getExchange(const ACE_CString& raw) {
	ACE_CString result;
	if (raw == "1")  // 유가증권
		{
		result = EXCHANGE_KSE_STRING;
	} else if (raw == "2")  // 코스닥
		{
		result = EXCHANGE_KOSDAQ_STRING;
	} else {
		result = EXCHANGE_KSE_STRING;
	}
	return (result);
}

BYTE MasterElwProcessor::getExchange() {
	return (EXCHANGE_KSE);
}

ACE_CString MasterElwProcessor::getKospi50(const ACE_CString& raw) {
	char result;
	if (raw == "Y")  // KOSPI 50
		{
		result = MEMBER_OF_INDEX_YES;
	} else {
		result = MEMBER_OF_INDEX_NO;
	}
	return (result);
}

ACE_CString MasterElwProcessor::getKospi100(const ACE_CString& raw) {
	char result;
	if (raw == "Y") {
		result = MEMBER_OF_INDEX_YES;
	} else {
		result = MEMBER_OF_INDEX_NO;
	}
	return (result);
}

ACE_CString MasterElwProcessor::getSymbolSubtype(const ACE_CString& raw) {
	ACE_CString result;

	if (raw == "ST") {
		result = SYMBOL_SUBTYPE_STRING_ST;
	} else if (raw == "MF") {
		result = SYMBOL_SUBTYPE_STRING_MF;
	} else if (raw == "RT") {
		result = SYMBOL_SUBTYPE_STRING_RT;
	} else if (raw == "SC") {
		result = SYMBOL_SUBTYPE_STRING_SC;
	} else if (raw == "IF") {
		result = SYMBOL_SUBTYPE_STRING_IF;
	} else if (raw == "DR") {
		result = SYMBOL_SUBTYPE_STRING_DR;
	} else if (raw == "EW") {
		result = SYMBOL_SUBTYPE_STRING_EW;
	} else if (raw == "EF") {
		result = SYMBOL_SUBTYPE_STRING_EF;
	} else if (raw == "SW") {
		result = SYMBOL_SUBTYPE_STRING_SW;
	} else if (raw == "SR") {
		result = SYMBOL_SUBTYPE_STRING_SR;
	} else if (raw == "BC") {
		result = SYMBOL_SUBTYPE_STRING_BC;
	} else if (raw == "FE") {
		result = SYMBOL_SUBTYPE_STRING_FE;
	} else if (raw == "FS") {
		result = SYMBOL_SUBTYPE_STRING_FS;
	} else if (raw == "EN") {
		result = SYMBOL_SUBTYPE_STRING_EN;
	}
	return (result);
}

ACE_CString MasterElwProcessor::getManufacturingType(const ACE_CString& raw) {
	ACE_CString result;

	if (raw == "Y") {
		result = "제조업";
	} else {
		result = "비제조업";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getManagementType(const ACE_CString& raw) {
	ACE_CString result;
	if (raw == "Y") {
		result = MASTER_MANAGEMENT_VALUE_MAN;
	} else if (raw == "N") {
		result = MASTER_MANAGEMENT_VALUE_NORMAL;
	} else {
		result = MASTER_MANAGEMENT_VALUE_NORMAL;
	}
	return (result);
}

ACE_CString MasterElwProcessor::getSuspensionType(const ACE_CString& raw) {
	ACE_CString result;

	//거래정지
	if (raw == "Y") {
		result = MASTER_SUSPENSION_VALUE_SUSPENDED;
	}
	// 정상
	else {
		result = MASTER_SUSPENSION_VALUE_NORMAL;
	}
	return (result);
}

ACE_CString MasterElwProcessor::getEx(const ACE_CString& rawEx) {
	ACE_CString result = "정상";
	if (rawEx == "00") {
		result = "정상";  // 00:해당사항없음(락이 발생안한 경우)
	} else if (rawEx == "01") {
		result = "권리락";
	} else if (rawEx == "02") {
		result = "배당락";
	} else if (rawEx == "03") {
		result = "분배락";
	} else if (rawEx == "04") {
		result = "권배락";
	} else if (rawEx == "05") {
		result = "중간배당락";
	} else if (rawEx == "06") {
		result = "권리중간배당락";
	} else if (rawEx == "99") {
		result = "기타";
	} else {
		result = "정상";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getSplitMerge(const ACE_CString& rawEx) {
	/*
	 * 00:해당없음(액면가변경이 취해질 수 있는 종목군에 대해 변경

	 없음을 의미) 01:액면분할 02:액면병합 03:주식분할 04:주식병합 99:기타

	 (2012.08.27)
	 *
	 */
	ACE_CString result = "정상";
	if (rawEx == "00") {
		result = "정상";  // 00:해당없음(액면가변경이 취해질 수 있는 종목군에 대해 변경없음을 의미)
	} else if (rawEx == "01") {
		result = "액면분할";
	} else if (rawEx == "02") {
		result = "액면병합";
	} else if (rawEx == "03") {
		result = "주식분할";
	} else if (rawEx == "04") {
		result = "주식병합";
	} else if (rawEx == "99") {
		result = "기타";
	} else {
		result = "정상";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getTotalMarketPriceType(const ACE_CString& raw) {
	ACE_CString result("제외");
	if (raw == "1") {
		result = "대형";
	} else if (raw == "2") {
		result = "중형";
	} else if (raw == "3") {
		result = "소형";
	} else if (raw == "0") {
		result = "제외";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getKogiType(const ACE_CString& raw) {
	ACE_CString result("일반");

	if (raw == "Y") {
		result = "우량";
	} else if (raw == "N") {
		result = "일반";
	}
	return (result);
}

// 종목이 소분류(index3)에 직접 속해있을 경우에는 소분류 코드를 사용,
// 소분류에 속하지 않고(index3 == "000"), 직접 중분류에 속해 있을 경우에는
// 중분류 코드를 사용
ACE_CString MasterElwProcessor::getIndustryClassCode(const ACE_CString& index2, const ACE_CString& index3) {
	std::ostringstream os;
	os << "KRI" << (index3 == "000" ? index2 : index3).c_str() << "000000";
	return (os.str().c_str());
}

ACE_CString MasterElwProcessor::getTradeUnit(const ACE_CString& raw) {
	int tradeUnitNum = atoi(raw.c_str());
	if (tradeUnitNum == 0) {
		tradeUnitNum = 1;
	}
	char tradeUnitChar[6];
	::memset(&tradeUnitChar, 0, sizeof(tradeUnitChar));
	::sprintf(tradeUnitChar, "%d", tradeUnitNum);
	ACE_CString result(tradeUnitChar);
	return (result);
}

ACE_CString MasterElwProcessor::getInvestmentWarningType(const ACE_CString& rawAlarm) {
	ACE_CString result(MASTER_CAUTION_TYPE_VALUE_NORMAL);
	if (rawAlarm == "00") {
		result = MASTER_CAUTION_TYPE_VALUE_NORMAL;
	} else if (rawAlarm == "01") {
		result = "투자주의";
	} else if (rawAlarm == "02") {
		result = "투자경고";
	} else if (rawAlarm == "03") {
		result = "투자위험";
	} else {
		result = MASTER_CAUTION_TYPE_VALUE_NORMAL;
	}
	return (result);
}

ACE_CString MasterElwProcessor::getIsDividendIndexStock(const ACE_CString& raw) {
	ACE_CString result = "00";
	if (raw == "Y") {
		result = "01"; // 배당지수
	} else if (raw == "N") {
		result = "00"; // X
	}
	return (result);
}

ACE_CString MasterElwProcessor::getEpsSign(const ACE_CString& raw) {
	ACE_CString result;
	if (raw == "-") {
		result = "-";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getETFType(const ACE_CString& raw) {
	ACE_CString result;
	if (raw == "0") {
		result = "해당없음";
	} else if (raw == "1") {
		result = "투자회사형";
	} else if (raw == "2") {
		result = "수익증권형";
	} else {
		result = "해당없음";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getReValuationReason(const ACE_CString& raw) {
	//00:해당없음,
	//01:기업분할,
	//02:자본감소,
	//03:장기간정지,
	//04:초과분배,
	//05:대규모배당
	//99:기타
	ACE_CString result;
	if (raw == "00") {
		result = "해당없음";
	} else if (raw == "01") {
		result = "기업분할";
	} else if (raw == "02") {
		result = "자본감소";
	} else if (raw == "03") {
		result = "장기간정지";
	} else if (raw == "04") {
		result = "초과분배";
	} else if (raw == "05") {
		result = "대규모배당";
	} else if (raw == "99") {
		result = "기타";
	} else {
		result = "해당없음";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getParPriceInteger(const ACE_CString& rawParPrice) {
	// 9(9)V9(3)
	double parPrice = ::atof(rawParPrice.c_str());
	parPrice = parPrice / 1000;
	int parPriceInt = (int) (parPrice);
	char strBuf[1024];
	::memset(&strBuf, 0, sizeof(strBuf));
	::sprintf(strBuf, "%d", parPriceInt);
	std::string strParPriceInt(strBuf);
	boost::trim(strParPriceInt);
	ACE_CString aceStrParPriceInt(strParPriceInt.c_str());
	return (aceStrParPriceInt);
}

ACE_CString MasterElwProcessor::getParPriceRealNumber(const ACE_CString& rawParPrice) {
	// 9(9)V9(3)
	double parPrice = ::atof(rawParPrice.c_str());
	parPrice = parPrice / 1000;
	char strBuf[1024];
	::memset(&strBuf, 0, sizeof(strBuf));
	::sprintf(strBuf, "%f", parPrice);
	std::string strParPrice(strBuf);
	boost::trim(strParPrice);
	ACE_CString aceStrParPrice(strParPrice.c_str());
	return (aceStrParPrice);
}

ACE_CString MasterElwProcessor::getMasterIncreaseType(const ACE_CString& raw) {
	// 00:해당없음 01:유상증자 02:무상증자 03:유무상증자 99:기타
	ACE_CString result;
	if (raw == "00") {
		result = "해당없음";
	} else if (raw == "01") {
		result = "유상증자";
	} else if (raw == "02") {
		result = "무상증자";
	} else if (raw == "03") {
		result = "유무상증자";
	} else if (raw == "99") {
		result = "기타";
	} else {
		result = "해당없음";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getStockType(const ACE_CString& raw) {
//    93  종류주권구분코드    X   1   458 "0:해당없음(보통주) 1:구형우선주 2:신형우선주 9:종류주권(2014.03.03)
//
//    ※증권그룹ID ST에만 해당
//    ※구명칭:우선주구분코드"

	ACE_CString result;
	if (raw == "0") {
		result = "보통주";
	} else if (raw == "1") {
		result = "구형우선주";
	} else if (raw == "2") {
		result = "신형우선주";
	} else if (raw == "9") {
		result = "종류증권";
	} else {
		result = "미정의";
	}
	return (result);
}

ACE_CString MasterElwProcessor::getIsOpenPriceBecomeStdPrice(const ACE_CString& raw) {
	ACE_CString result;
	if (raw == "Y") {
		result = "Y";
	} else if (raw == "N") {
		result = "N";
	} else {
		result = "N";
	}
	return (result);

}

#if(0)
	ACE_CString MstElwJisuProcessConstIdMap1[599] = {"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","110043","110046","110043","110004","110007","110012","110014","110020","110021","110023","110037","110038","110039","110040","110041","110042","110044","110045","110049","110051","110052","110053","110056","110057","110058","110059","110060","110061","110062","110065","110066","110067","110068","110069","110070","110071","110072","110073","110074","110077","110078","110079","110080","110081","110082","110083","110084","110086","110087","110088","110089","110090","110091","110092","110093","110094","110095","110096","110097","110098","110099","110100","110101","110102","110103","110104","110105","110106","110107","110108","110109","110110","110111","110112","2P8802","2P8803","2P9259","2P9269","2P9258","2P9284","2P9206","2P9271","2P9234","2P9272","2P9263","2P9256","2P9239","2P9246","2P9247","2P9248","2P9260","2P9255","2P9265","2P9267","2P9266","2P9276","2P9277","2P9278","2P9279","2P9280","2P9281","2P9282","2P9283","2P9231","2P9235","2P9240","2P9275","2P9211","2P9242","2P9243","2P9274","2P9245","2P9262","2P9236","2P9251","2P9238","2P9264","2P9268","2P9229","2P9252","2P9233","2P9253","2P9221","2P9244","2P9222","2P9257","2P9241","2P9273","2P9207","2P9250","2P9237","2P9249","2P9210","2P9232","2P9254","2PB003","2PB101","2PB201","2PB211","2PB221","2PB226","2PB231","2PB232","2PB237","2PB238","2PB239","2PB241","2PB242","2PB243","2PB305","2PB306","2PB307","2PC007","2PC006","2PM128","2PM126","2PM127","2PM119","2PM121","2PM102","2PM104","2PM107","2PM109","2PM112","2PM114","2PM115","2PM116","2PM117","2PM118","2PM122","2PM123","2PM131","2PM124","2PM132","2PM125","2PM120","2PM129","2PM130","2PM134","2PM133","2PM001","2PR001","2PR101","120001","120002","120003","120004","120005","2PW006","120007","120008","120009","120010","120011","120012","120013","120014","120015","120016","120017","120018","120019","120020","120021","120901"};
	ACE_CString MstElwJisuProcessConstIdMap3[599] = {"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3","2","2","2","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","C","C","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","R","R","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"};
#endif
#if(0)
	ACE_CString MstElwJisuProcessConstIdMap2[599] = {"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","187","188","165","132","133","134","142","136","141","411","412","413","414","415","351","352","353","354","355","356","357","358","105","600","167","203","212","213","214","215","216","217","218","331","204","175","176","169","174","301","302","303","304","801","802","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","004","013","707","731","708","821","312","313","009","010","005","006","007","008","717","003","709","011","012","304","306","307","308","305","822","732","051","052","100","101","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","050","053","054","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","055","056","057","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","601","602","601","004","007","012","014","020","021","023","037","038","039","040","041","042","044","045","049","051","052","053","056","057","058","059","060","061","062","065","066","067","068","069","070","071","072","073","074","077","078","079","080","081","082","083","084","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","802","803","259","269","258","284","206","271","234","272","263","256","239","246","247","248","260","255","265","267","266","276","277","278","279","280","281","282","283","231","235","240","275","211","242","243","274","245","262","236","251","238","264","268","229","252","233","253","221","244","222","257","241","273","207","250","237","249","210","232","254","003","101","201","211","221","226","231","232","237","238","239","241","242","243","305","306","307","007","006","128","126","127","119","121","102","104","107","109","112","114","115","116","117","118","122","123","131","124","132","125","120","129","130","134","133","001","001","101","001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","901"};
#endif

#if(1)
#define MASTERJISUTOTCNT 394
#endif

#if(1)
	ACE_CString MstElwJisuProcessConstIdMap1[MASTERJISUTOTCNT] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P"};
	ACE_CString MstElwJisuProcessConstIdMap3[MASTERJISUTOTCNT] = 
	{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3"};
#endif

#if(1)
ACE_CString MasterElwProcessor::getSymbolUpCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<MASTERJISUTOTCNT; kk++)
	{
		if(raw == MstElwJisuProcessConstIdMap1[kk])
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
		return(MstElwJisuProcessConstIdMap3[ii]);
	}
}
#endif











































































#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif

#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif

#if(0)
/*CHANGE-------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------*/
#endif

#if(0)
int MasterElwProcessor::processPacket_KRX_A102S(const ACE_CString &packet) {
	ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] BEGIN\n", getCurrentTimestamp().c_str()));

	bool isValidPacket = false;
	int result = 0;
	if (EXTURE_PLUS_ELW_ELW_BATCH_DATA_SIZE != static_cast<int>(packet.length())) {
		ACE_DEBUG((LM_ERROR, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] Skip : %s,%d : EXTURE_PLUS_ELW_ELW_BATCH_DATA_SIZE:[%d] != packet.length():[%d] packet:[%s]\n", getCurrentTimestamp().c_str(), __FILE__, __LINE__, EXTURE_PLUS_ELW_ELW_BATCH_DATA_SIZE, packet.length(), packet.c_str()));
	} else {
		ExturePlusElwELWBatchData rawData;
		::memset(&rawData, 0, sizeof(ExturePlusElwELWBatchData));
		::memcpy(&rawData, packet.c_str(), packet.length());
		ACE_CString data_category(rawData.data_category, sizeof(rawData.data_category));
		data_category = trim_ACE(data_category);

		ACE_CString issue_code(rawData.issue_code, sizeof(rawData.issue_code));
		issue_code = trim_ACE(issue_code);

		ACE_CString data_seq_number(rawData.data_seq_number, sizeof(rawData.data_seq_number));
		data_seq_number = trim_ACE(data_seq_number);

		ACE_CString elw_issue_market_candidate_korean_name(rawData.elw_issue_market_candidate_korean_name, sizeof(rawData.elw_issue_market_candidate_korean_name));
		elw_issue_market_candidate_korean_name = trim_ACE(elw_issue_market_candidate_korean_name);

		ACE_CString elw_issue_market_candidate_english_name(rawData.elw_issue_market_candidate_english_name, sizeof(rawData.elw_issue_market_candidate_english_name));
		elw_issue_market_candidate_english_name = trim_ACE(elw_issue_market_candidate_english_name);

		ACE_CString elw_issue_market_candidate_number(rawData.elw_issue_market_candidate_number, sizeof(rawData.elw_issue_market_candidate_number));
		elw_issue_market_candidate_number = trim_ACE(elw_issue_market_candidate_number);

		ACE_CString elw_composition_issue_market_id_1(rawData.elw_composition_issue_market_id_1, sizeof(rawData.elw_composition_issue_market_id_1));
		elw_composition_issue_market_id_1 = trim_ACE(elw_composition_issue_market_id_1);

		ACE_CString elw_composition_issue_market_id_2(rawData.elw_composition_issue_market_id_2, sizeof(rawData.elw_composition_issue_market_id_2));
		elw_composition_issue_market_id_2 = trim_ACE(elw_composition_issue_market_id_2);

		ACE_CString elw_composition_issue_market_id_3(rawData.elw_composition_issue_market_id_3, sizeof(rawData.elw_composition_issue_market_id_3));
		elw_composition_issue_market_id_3 = trim_ACE(elw_composition_issue_market_id_3);

		ACE_CString elw_composition_issue_market_id_4(rawData.elw_composition_issue_market_id_4, sizeof(rawData.elw_composition_issue_market_id_4));
		elw_composition_issue_market_id_4 = trim_ACE(elw_composition_issue_market_id_4);

		ACE_CString elw_composition_issue_market_id_5(rawData.elw_composition_issue_market_id_5, sizeof(rawData.elw_composition_issue_market_id_5));
		elw_composition_issue_market_id_5 = trim_ACE(elw_composition_issue_market_id_5);

		ACE_CString elw_underlying_asset_1(rawData.elw_underlying_asset_1, sizeof(rawData.elw_underlying_asset_1));
		elw_underlying_asset_1 = trim_ACE(elw_underlying_asset_1);

		ACE_CString elw_underlying_asset_2(rawData.elw_underlying_asset_2, sizeof(rawData.elw_underlying_asset_2));
		elw_underlying_asset_2 = trim_ACE(elw_underlying_asset_2);

		ACE_CString elw_underlying_asset_3(rawData.elw_underlying_asset_3, sizeof(rawData.elw_underlying_asset_3));
		elw_underlying_asset_3 = trim_ACE(elw_underlying_asset_3);

		ACE_CString elw_underlying_asset_4(rawData.elw_underlying_asset_4, sizeof(rawData.elw_underlying_asset_4));
		elw_underlying_asset_4 = trim_ACE(elw_underlying_asset_4);

		ACE_CString elw_underlying_asset_5(rawData.elw_underlying_asset_5, sizeof(rawData.elw_underlying_asset_5));
		elw_underlying_asset_5 = trim_ACE(elw_underlying_asset_5);

		ACE_CString elw_underlying_asset_composite_rate_1(rawData.elw_underlying_asset_composite_rate_1, sizeof(rawData.elw_underlying_asset_composite_rate_1));
		elw_underlying_asset_composite_rate_1 = trim_ACE(elw_underlying_asset_composite_rate_1);

		ACE_CString elw_underlying_asset_composite_rate_2(rawData.elw_underlying_asset_composite_rate_2, sizeof(rawData.elw_underlying_asset_composite_rate_2));
		elw_underlying_asset_composite_rate_2 = trim_ACE(elw_underlying_asset_composite_rate_2);

		ACE_CString elw_underlying_asset_composite_rate_3(rawData.elw_underlying_asset_composite_rate_3, sizeof(rawData.elw_underlying_asset_composite_rate_3));
		elw_underlying_asset_composite_rate_3 = trim_ACE(elw_underlying_asset_composite_rate_3);

		ACE_CString elw_underlying_asset_composite_rate_4(rawData.elw_underlying_asset_composite_rate_4, sizeof(rawData.elw_underlying_asset_composite_rate_4));
		elw_underlying_asset_composite_rate_4 = trim_ACE(elw_underlying_asset_composite_rate_4);

		ACE_CString elw_underlying_asset_composite_rate_5(rawData.elw_underlying_asset_composite_rate_5, sizeof(rawData.elw_underlying_asset_composite_rate_5));
		elw_underlying_asset_composite_rate_5 = trim_ACE(elw_underlying_asset_composite_rate_5);

#if(0)
		elw_underlying_asset_composite_rate_1 = getDoubleString(elw_underlying_asset_composite_rate_1, 1000000, 0);
		elw_underlying_asset_composite_rate_2 = getDoubleString(elw_underlying_asset_composite_rate_2, 1000000, 0);
		elw_underlying_asset_composite_rate_3 = getDoubleString(elw_underlying_asset_composite_rate_3, 1000000, 0);
		elw_underlying_asset_composite_rate_4 = getDoubleString(elw_underlying_asset_composite_rate_4, 1000000, 0);
		elw_underlying_asset_composite_rate_5 = getDoubleString(elw_underlying_asset_composite_rate_5, 1000000, 0);
#endif

#if(0)
		elw_underlying_asset_composite_rate_1 = getDoubleString(elw_underlying_asset_composite_rate_1, 1, 0);
		elw_underlying_asset_composite_rate_2 = getDoubleString(elw_underlying_asset_composite_rate_2, 1, 0);
		elw_underlying_asset_composite_rate_3 = getDoubleString(elw_underlying_asset_composite_rate_3, 1, 0);
		elw_underlying_asset_composite_rate_4 = getDoubleString(elw_underlying_asset_composite_rate_4, 1, 0);
		elw_underlying_asset_composite_rate_5 = getDoubleString(elw_underlying_asset_composite_rate_5, 1, 0);
#endif

		ACE_CString index_associated_market_type_code(rawData.elw_index_industry_code, sizeof(rawData.elw_index_industry_code));
		//index_associated_market_type_code = trim_ACE(index_associated_market_type_code);
		index_associated_market_type_code = getSymbolUpCode(index_associated_market_type_code);

		ACE_CString elw_index_industry_code(rawData.elw_index_industry_code, sizeof(rawData.elw_index_industry_code));
		elw_index_industry_code = trim_ACE(elw_index_industry_code);

		ACE_CString elw_rights_type_0(rawData.elw_rights_type_0, sizeof(rawData.elw_rights_type_0));
		elw_rights_type_0 = trim_ACE(elw_rights_type_0);

		ACE_CString elw_rights_execution_type(rawData.elw_rights_execution_type, sizeof(rawData.elw_rights_execution_type));
		elw_rights_execution_type = trim_ACE(elw_rights_execution_type);

		ACE_CString elw_payment_method(rawData.elw_payment_method, sizeof(rawData.elw_payment_method));
		elw_payment_method = trim_ACE(elw_payment_method);

		ACE_CString elw_last_traded_date(rawData.elw_last_traded_date, sizeof(rawData.elw_last_traded_date));
		elw_last_traded_date = trim_ACE(elw_last_traded_date);

		ACE_CString elw_payment_date(rawData.elw_payment_date, sizeof(rawData.elw_payment_date));
		elw_payment_date = trim_ACE(elw_payment_date);

		ACE_CString base_price_of_elw_underlying_asset(rawData.base_price_of_elw_underlying_asset, sizeof(rawData.base_price_of_elw_underlying_asset));
		base_price_of_elw_underlying_asset = trim_ACE(base_price_of_elw_underlying_asset);

#if(0)
		base_price_of_elw_underlying_asset = getDoubleString(base_price_of_elw_underlying_asset, 1000, 0);
#endif

#if(1)
		base_price_of_elw_underlying_asset = getDoubleString(base_price_of_elw_underlying_asset, 1, 0);
#endif

		ACE_CString elw_rights_content(rawData.elw_rights_content, sizeof(rawData.elw_rights_content));
		elw_rights_content = trim_ACE(elw_rights_content);

		ACE_CString elw_conversion_rate(rawData.elw_conversion_rate, sizeof(rawData.elw_conversion_rate));
		elw_conversion_rate = trim_ACE(elw_conversion_rate);

#if(0)
		elw_conversion_rate = getDoubleString(elw_conversion_rate, 1000000, 0);
#endif

#if(1)
		elw_conversion_rate = getDoubleString(elw_conversion_rate, 1, 0);
#endif

		ACE_CString elw_price_rise_participation_rate(rawData.elw_price_rise_participation_rate, sizeof(rawData.elw_price_rise_participation_rate));
		elw_price_rise_participation_rate = trim_ACE(elw_price_rise_participation_rate);

#if(0)
		elw_price_rise_participation_rate = getDoubleString(elw_price_rise_participation_rate, 100, 0);
#endif

#if(1)
		elw_price_rise_participation_rate = getDoubleString(elw_price_rise_participation_rate, 1, 0);
#endif

		ACE_CString elw_minimum_compensation_rate(rawData.elw_minimum_compensation_rate, sizeof(rawData.elw_minimum_compensation_rate));
		elw_minimum_compensation_rate = trim_ACE(elw_minimum_compensation_rate);

#if(0)
		elw_minimum_compensation_rate = getDoubleString(elw_minimum_compensation_rate, 100, 0);
#endif

#if(1)
		elw_minimum_compensation_rate = getDoubleString(elw_minimum_compensation_rate, 1, 0);
#endif

		ACE_CString elw_fixed_payment(rawData.elw_fixed_payment, sizeof(rawData.elw_fixed_payment));
		elw_fixed_payment = trim_ACE(elw_fixed_payment);
		elw_fixed_payment = getDoubleString(elw_fixed_payment, 1000, 0);

		ACE_CString elw_payment_agent(rawData.elw_payment_agent, sizeof(rawData.elw_payment_agent));
		elw_payment_agent = trim_ACE(elw_payment_agent);

		ACE_CString price_evaluation_method_use_at_elw_maturity(rawData.price_evaluation_method_use_at_elw_maturity, sizeof(rawData.price_evaluation_method_use_at_elw_maturity));
		price_evaluation_method_use_at_elw_maturity = trim_ACE(price_evaluation_method_use_at_elw_maturity);

		ACE_CString elw_rights_type_1(rawData.elw_rights_type_1, sizeof(rawData.elw_rights_type_1));
		elw_rights_type_1 = trim_ACE(elw_rights_type_1);

		ACE_CString elw_lp_holding_quantity(rawData.elw_lp_holding_quantity, sizeof(rawData.elw_lp_holding_quantity));
		elw_lp_holding_quantity = trim_ACE(elw_lp_holding_quantity);

		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] data_category                                   :[%s]\n", getCurrentTimestamp().c_str(), data_category.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] issue_code                                      :[%s]\n", getCurrentTimestamp().c_str(), issue_code.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] data_seq_number                                 :[%s]\n", getCurrentTimestamp().c_str(), data_seq_number.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_issue_market_candidate_korean_name          :[%s]\n", getCurrentTimestamp().c_str(), elw_issue_market_candidate_korean_name.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_issue_market_candidate_english_name         :[%s]\n", getCurrentTimestamp().c_str(), elw_issue_market_candidate_english_name.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_issue_market_candidate_number               :[%s]\n", getCurrentTimestamp().c_str(), elw_issue_market_candidate_number.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_composition_issue_market_id_1               :[%s]\n", getCurrentTimestamp().c_str(), elw_composition_issue_market_id_1.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_composition_issue_market_id_2               :[%s]\n", getCurrentTimestamp().c_str(), elw_composition_issue_market_id_2.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_composition_issue_market_id_3               :[%s]\n", getCurrentTimestamp().c_str(), elw_composition_issue_market_id_3.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_composition_issue_market_id_4               :[%s]\n", getCurrentTimestamp().c_str(), elw_composition_issue_market_id_4.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_composition_issue_market_id_5               :[%s]\n", getCurrentTimestamp().c_str(), elw_composition_issue_market_id_5.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_1                          :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_1.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_2                          :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_2.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_3                          :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_3.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_4                          :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_4.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_5                          :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_5.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_composite_rate_1           :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_composite_rate_1.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_composite_rate_2           :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_composite_rate_2.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_composite_rate_3           :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_composite_rate_3.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_composite_rate_4           :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_composite_rate_4.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_underlying_asset_composite_rate_5           :[%s]\n", getCurrentTimestamp().c_str(), elw_underlying_asset_composite_rate_5.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] index_associated_market_type_code               :[%s]\n", getCurrentTimestamp().c_str(), index_associated_market_type_code.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_index_industry_code                         :[%s]\n", getCurrentTimestamp().c_str(), elw_index_industry_code.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_rights_type_0                               :[%s]\n", getCurrentTimestamp().c_str(), elw_rights_type_0.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_rights_execution_type                       :[%s]\n", getCurrentTimestamp().c_str(), elw_rights_execution_type.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_payment_method                              :[%s]\n", getCurrentTimestamp().c_str(), elw_payment_method.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_last_traded_date                            :[%s]\n", getCurrentTimestamp().c_str(), elw_last_traded_date.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_payment_date                                :[%s]\n", getCurrentTimestamp().c_str(), elw_payment_date.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] base_price_of_elw_underlying_asset              :[%s]\n", getCurrentTimestamp().c_str(), base_price_of_elw_underlying_asset.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_rights_content                              :[%s]\n", getCurrentTimestamp().c_str(), elw_rights_content.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_conversion_rate                             :[%s]\n", getCurrentTimestamp().c_str(), elw_conversion_rate.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_price_rise_participation_rate               :[%s]\n", getCurrentTimestamp().c_str(), elw_price_rise_participation_rate.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_minimum_compensation_rate                   :[%s]\n", getCurrentTimestamp().c_str(), elw_minimum_compensation_rate.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_fixed_payment                               :[%s]\n", getCurrentTimestamp().c_str(), elw_fixed_payment.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_payment_agent                               :[%s]\n", getCurrentTimestamp().c_str(), elw_payment_agent.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] price_evaluation_method_use_at_elw_maturity     :[%s]\n", getCurrentTimestamp().c_str(), price_evaluation_method_use_at_elw_maturity.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_rights_type_1                               :[%s]\n", getCurrentTimestamp().c_str(), elw_rights_type_1.c_str()));
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] elw_lp_holding_quantity                         :[%s]\n", getCurrentTimestamp().c_str(), elw_lp_holding_quantity.c_str()));

		/*
		 * MASTER_MAP 은 "KEY = VALUE |" 형태로 전송된다.
		 * 숫자의 경우 NULL 과 0 은 같다고 해야 하는가?
		 *
		 * 빈문자열을 그대로 SEND 해야 하는가?
		 *
		 * KOSCOM 스펙 그대로 보낸다. 소수점을 찍어 보낼 필요가 있는가? -> 이건 있다.
		 */
		try {
			CheckSize(packet.length(), EXTURE_PLUS_ELW_ELW_BATCH_DATA_SIZE);

			// log frame count status
			LogFrameCount(data_category);

			if (issue_code == "999999999999") {
				ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] issue_code:[%s] Skip dummy master data\n", getCurrentTimestamp().c_str(), issue_code.c_str()));
				return (0);
			}

			bind(MASTER_ELW_ELW_SYMBOL, issue_code);
			bind(MASTER_EXCHANGE, EXCHANGE_KSE_STRING);
			bind(MASTER_SYMBOL_TYPE, SYMBOL_ELW_STRING);

			char tempBuf[1024];
			::memset(&tempBuf, 0, sizeof(tempBuf));
			::sprintf(tempBuf, "%d", DECIMAL_0);
			bind(MASTER_DECIMAL_POINT, tempBuf);

			bind(MASTER_ELW_ELW_ISSUE_MARKET_CANDIDATE_KOREAN_NAME, elw_issue_market_candidate_korean_name);
			bind(MASTER_ELW_ELW_ISSUE_MARKET_CANDIDATE_ENGLISH_NAME, elw_issue_market_candidate_english_name);
			bind(MASTER_ELW_ELW_ISSUE_MARKET_CANDIDATE_NUMBER, elw_issue_market_candidate_number);

			bind(MASTER_ELW_ELW_COMPOSITION_ISSUE_MARKET_ID_1, elw_composition_issue_market_id_1);
			bind(MASTER_ELW_ELW_COMPOSITION_ISSUE_MARKET_ID_2, elw_composition_issue_market_id_2);
			bind(MASTER_ELW_ELW_COMPOSITION_ISSUE_MARKET_ID_3, elw_composition_issue_market_id_3);
			bind(MASTER_ELW_ELW_COMPOSITION_ISSUE_MARKET_ID_4, elw_composition_issue_market_id_4);
			bind(MASTER_ELW_ELW_COMPOSITION_ISSUE_MARKET_ID_5, elw_composition_issue_market_id_5);

			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_SYMBOL_1, elw_underlying_asset_1);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_SYMBOL_2, elw_underlying_asset_2);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_SYMBOL_3, elw_underlying_asset_3);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_SYMBOL_4, elw_underlying_asset_4);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_SYMBOL_5, elw_underlying_asset_5);

			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_COMPOSITE_RATE_1, elw_underlying_asset_composite_rate_1);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_COMPOSITE_RATE_2, elw_underlying_asset_composite_rate_2);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_COMPOSITE_RATE_3, elw_underlying_asset_composite_rate_3);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_COMPOSITE_RATE_4, elw_underlying_asset_composite_rate_4);
			bind(MASTER_ELW_ELW_UNDERLYING_ASSET_COMPOSITE_RATE_5, elw_underlying_asset_composite_rate_5);

			bind(MASTER_ELW_INDEX_ASSOCIATED_MARKET_TYPE_CODE, index_associated_market_type_code);

			bind(MASTER_ELW_ELW_INDEX_INDUSTRY_CODE, elw_index_industry_code);
			bind(MASTER_ELW_ELW_RIGHTS_TYPE_0, elw_rights_type_0);
			bind(MASTER_ELW_ELW_RIGHTS_EXECUTION_TYPE, elw_rights_execution_type);
			bind(MASTER_ELW_ELW_PAYMENT_METHOD, elw_payment_method);
			bind(MASTER_ELW_ELW_LAST_TRADED_DATE, elw_last_traded_date);

			bind(MASTER_ELW_ELW_PAYMENT_DATE, elw_payment_date);
			bind(MASTER_ELW_BASE_PRICE_OF_ELW_UNDERLYING_ASSET, base_price_of_elw_underlying_asset);
			bind(MASTER_ELW_ELW_RIGHTS_CONTENT, elw_rights_content);
			bind(MASTER_ELW_ELW_CONVERSION_RATE, elw_conversion_rate);
			bind(MASTER_ELW_ELW_PRICE_RISE_PARTICIPATION_RATE, elw_price_rise_participation_rate);
			bind(MASTER_ELW_ELW_MINIMUM_COMPENSATION_RATE, elw_minimum_compensation_rate);

			bind(MASTER_ELW_ELW_FIXED_PAYMENT, elw_fixed_payment);

			bind(MASTER_ELW_ELW_PAYMENT_AGENT, elw_payment_agent);
			bind(MASTER_ELW_PRICE_EVALUATION_METHOD_USE_AT_ELW_MATURITY, price_evaluation_method_use_at_elw_maturity);
			bind(MASTER_ELW_ELW_RIGHTS_TYPE_1, elw_rights_type_1);
			bind(MASTER_ELW_ELW_LP_HOLDING_QUANTITY, elw_lp_holding_quantity);
			isValidPacket = true;
		} catch (std::exception e) {
			isValidPacket = false;
			ACE_DEBUG((LM_ERROR, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] error occur e.what:[%s]\n", getCurrentTimestamp().c_str(), e.what()));
		}
		if (isValidPacket == true) 
		{
#if(0)
			setPacketType (PACKET_ELW_ELW_BATCH_DATA);
#endif
			result = sendPacket();
		}
		ACE_DEBUG((LM_DEBUG, "[%s] [MasterElwProcessor::processPacket_KRX_A102S] isValidPacket:[%d]\tissue_code:[%s]\tresult:[%d]\n", getCurrentTimestamp().c_str(), isValidPacket, issue_code.c_str(), result));
	}
	return (0);
}
#endif



