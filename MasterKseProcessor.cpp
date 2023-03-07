// MasterKseProcessor.cpp: implementation of the MasterKseProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "MasterKseProcessor.h"
#include "PaxfeedPacket.h"
#include "PaxfeedPacketDefine.h"
#include "PaxfeedStringUtil.h"
#include "PaxfeedMasterDefine.h"
#include "ExturePlusInternetKse.h"

#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace paxfeed;

#if(1)
MasterKseProcessor::MasterKseProcessor(const ACE_CString &frameId, const ACE_CString &packet, int serial)
        : MasterProcessor(serial)
{
    isValidPacket_ = false;

	char tmp[1024];

    if ( EXTURE_PLUS_KSE_MASTER_SIZE != static_cast<int>(packet.length()) )
    {
        isValidPacket_ = false;
    }
    else
    {
        ExturePlusKseMaster kse;
        ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

        ACE_CString dataClass(kse.dataClass, sizeof kse.dataClass);
        ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
        ACE_CString abbrStockCode(kse.abbrStockCode + 1, sizeof ( kse.abbrStockCode ) - 1);
        ACE_CString abbrStockNameKor(kse.abbrStockNameKor, sizeof ( kse.abbrStockNameKor ));
        ACE_CString abbrStockNameEng(kse.abbrStockNameEng, sizeof ( kse.abbrStockNameEng ));
        ACE_CString ydayClosePrice(kse.ydayClosePrice, sizeof ( kse.ydayClosePrice ));
        ACE_CString upLimitPrice(kse.upLimitPrice, sizeof ( kse.upLimitPrice ));
        ACE_CString downLimitPrice(kse.downLimitPrice, sizeof ( kse.downLimitPrice ));
        ACE_CString standardPrice(kse.standardPrice, sizeof ( kse.standardPrice ));
        ACE_CString isManagementStock(kse.isManagementStock, sizeof ( kse.isManagementStock ));
        ACE_CString isTradeStop(kse.isTradeStop, sizeof ( kse.isTradeStop ));
        ACE_CString exClassCode(kse.exClassCode, sizeof ( kse.exClassCode ));
        ACE_CString faceValueChangeClassCode(kse.faceValueChangeClassCode, sizeof ( kse.faceValueChangeClassCode ));
        ACE_CString ydayAccmVolume(kse.ydayAccmVolume, sizeof ( kse.ydayAccmVolume ));
        ACE_CString ydayAccmAmount(kse.ydayAccmAmount, sizeof ( kse.ydayAccmAmount ));
        ACE_CString listingSize(kse.listingSize, sizeof ( kse.listingSize ));
        ACE_CString substitutePrice(kse.substitutePrice, sizeof ( kse.substitutePrice ));
        ACE_CString faceValue(kse.faceValue, sizeof ( kse.faceValue ) - 2);  // 뒤의 소수점 2자리는 무시
        ACE_CString lowestQuotePrice(kse.lowestQuotePrice, sizeof ( kse.lowestQuotePrice ));
        ACE_CString highestQuotePrice(kse.highestQuotePrice, sizeof ( kse.highestQuotePrice ));
        ACE_CString isInsincerityPublicNewsAppoint(kse.isInsincerityPublicNewsAppoint, sizeof ( kse.isInsincerityPublicNewsAppoint ));
        ACE_CString REITsClassCode(kse.REITsClassCode, sizeof ( kse.REITsClassCode ));
        ACE_CString capital(kse.capital, sizeof ( kse.capital ) - 3);  // 뒤의 소수점 3자리는 무시
        ACE_CString issuePrice(kse.issuePrice, sizeof ( kse.issuePrice ));
        ACE_CString isCorporateGovernanceFine(kse.isCorporateGovernanceFine, sizeof ( kse.isCorporateGovernanceFine ));
        ACE_CString marketAlarmClassCode(kse.marketAlarmClassCode, sizeof kse.marketAlarmClassCode);
        ACE_CString listingDate(kse.listingDate, sizeof kse.listingDate);
        ACE_CString ETFFollowingEarningRateMultiple(kse.ETFFollowingEarningRateMultiple, sizeof ( kse.ETFFollowingEarningRateMultiple ));
        ACE_CString ETFReplicationMethodTypeCode(kse.ETFReplicationMethodTypeCode, ( sizeof kse.ETFReplicationMethodTypeCode ));
        ACE_CString shortTermFeverishInstrumentTypeCode(kse.shortTermFeverishInstrumentTypeCode, sizeof ( kse.shortTermFeverishInstrumentTypeCode ));
        ACE_CString isClearanceTrade(kse.isClearanceTrade, ( sizeof kse.isClearanceTrade ));
        ACE_CString expirationDate(kse.expirationDate, sizeof ( kse.expirationDate ));
        ACE_CString distributeTypeCode(kse.distributeTypeCode, sizeof ( kse.distributeTypeCode ));
        ACE_CString expirationRedemptionPriceDecisionStartDate(kse.expirationRedemptionPriceDecisionStartDate, sizeof ( kse.expirationRedemptionPriceDecisionStartDate ));
        ACE_CString expirationRedemptionPriceDecisionEndDate(kse.expirationRedemptionPriceDecisionEndDate, sizeof ( kse.expirationRedemptionPriceDecisionEndDate ));
        ACE_CString isShortStockSellingPossibility(kse.isShortStockSellingPossibility, sizeof ( kse.isShortStockSellingPossibility ));
        ACE_CString lowLiquidity(kse.lowLiquidity, sizeof ( kse.lowLiquidity ));
        ACE_CString abnormalRise(kse.abnormalRise, sizeof ( kse.abnormalRise ));
        ACE_CString isOpenPriceBecomeStdPrice(kse.isOpenPriceBecomeStdPrice, sizeof ( kse.isOpenPriceBecomeStdPrice ));

        symbol_ = stockCode;

        ACE_CString preferredStockClassCode(kse.preferredStockClassCode, sizeof ( kse.preferredStockClassCode ));
        ACE_CString stockType = getStockType(preferredStockClassCode);

        /*
         *
         * 18   임의종료발동조건코드  X   1   139 "단일가세선에서 임의종료의 발동조건.조건부발동(2)인경우 임의종료규칙에서 정의하는 가격요건을 충족하는지 판단 후 발동을 결정함.
         ##코드값## 0:미발동 1:발동 2:조건부발동(가격요건판단)"
         *
         * 일단 출력만 해본다.
         */
        ACE_CString randomEndTriggerConditionCode(kse.randomEndTriggerConditionCode, sizeof ( kse.randomEndTriggerConditionCode ));
        ACE_CString isInvestmentPrecautionIssue(kse.isInvestmentPrecautionIssue, sizeof ( kse.isInvestmentPrecautionIssue ));

        /*
         * 2021.03.15 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */
        ACE_CString indexCalculationInstitution_code(kse.indexCalculationInstitution_code, sizeof ( kse.indexCalculationInstitution_code ));

        /*
         * 2021.07.19 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */

        /*
         * 2021.11.29 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */
        ACE_CString isSPAC_merger(kse.isSPAC_merger, sizeof ( kse.isSPAC_merger ));

        try
        {
            CheckSize(packet.length(), EXTURE_PLUS_KSE_MASTER_SIZE);

            // log frame count status
            LogFrameCount(frameId);

            ExturePlusKseMaster kse;
            ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

            ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
            if ( stockCode == "999999999999" )
            {
                return;
            }

            bind(MASTER_SYMBOL, stockCode);
            bind(MASTER_EXCHANGE, EXCHANGE_KSE_STRING);
            bind(MASTER_SYMBOL_TYPE, SYMBOL_STOCK_STRING);

            char tempBuf[1024];
            ::memset(&tempBuf, 0, sizeof ( tempBuf ));
            ::sprintf(tempBuf, "%d", DECIMAL_0);
            bind(MASTER_DECIMAL_POINT, tempBuf);

            bind(MASTER_ABBR_SYMBOL, trim(ACE_CString(kse.abbrStockCode + 1, sizeof ( kse.abbrStockCode ) - 1)));
            bind(MASTER_NAME, trim(ACE_CString(kse.abbrStockNameKor, sizeof ( kse.abbrStockNameKor ))));

#if(0)
			ACE_CString stockseq(kse.stockSeq, sizeof ( kse.stockSeq ));
			int stockseq_index = atoi( stockseq.c_str() );

			if(stockseq_index > 9990)
			{
				ACE_DEBUG( ( LM_DEBUG , "[%s] [MasterKseProcessor::MasterKseProcessor],stockseq_index[%d],[%d],[%d]\n" , getCurrentTimestamp().c_str() , stockseq_index,
					EXTURE_PLUS_KSE_MASTER_SIZE,
					(int)(packet.length())
					));
			}
			else
			{
				KseMasterName[stockseq_index] = trim(ACE_CString(kse.abbrStockNameKor, sizeof ( kse.abbrStockNameKor )));
			}
#endif

            bind(MASTER_ENG_NAME, trim(ACE_CString(kse.abbrStockNameEng, sizeof ( kse.abbrStockNameEng ))));

            ACE_CString symbolSubtype(kse.stockGroupID, sizeof ( kse.stockGroupID ));
            bind(MASTER_SYMBOL_SUBTYPE, getSymbolSubtype(symbolSubtype));

            bind(MASTER_YDAY_CLOSE, ACE_CString(kse.ydayClosePrice, sizeof ( kse.ydayClosePrice )));
            bind(MASTER_UP_LIMIT, ACE_CString(kse.upLimitPrice, sizeof ( kse.upLimitPrice )));
            bind(MASTER_DOWN_LIMIT, ACE_CString(kse.downLimitPrice, sizeof ( kse.downLimitPrice )));
            bind(MASTER_STD_PRICE, ACE_CString(kse.standardPrice, sizeof ( kse.standardPrice )));
            bind(MASTER_MANAGEMENT, getManagementType(ACE_CString(kse.isManagementStock, sizeof ( kse.isManagementStock ))));
            bind(MASTER_IS_MANAGEMENT, ACE_CString(kse.isManagementStock, sizeof ( kse.isManagementStock )));
            bind(MASTER_SUSPENSION, getSuspensionType(ACE_CString(kse.isTradeStop, sizeof ( kse.isTradeStop ))));
            bind(MASTER_IS_SUSPENSION, ACE_CString(kse.isTradeStop, sizeof ( kse.isTradeStop )));
            bind(MASTER_EX, getEx(ACE_CString(kse.exClassCode, sizeof ( kse.exClassCode ))));
            bind(MASTER_SPLITMERGE, getSplitMerge(ACE_CString(kse.faceValueChangeClassCode, sizeof ( kse.faceValueChangeClassCode ))));
            bind(MASTER_YDAY_VOLUME, ACE_CString(kse.ydayAccmVolume, sizeof ( kse.ydayAccmVolume )));

#if(1)
			ACE_CString ydayaccmamount(kse.ydayAccmAmount, sizeof ( kse.ydayAccmAmount ));
			memset(tmp,0x00,sizeof(tmp));
			sprintf(tmp,"%ld", atol(ydayaccmamount.c_str()));
            bind(MASTER_YDAY_AMOUNT, tmp);
#endif
            bind(MASTER_LISTING_VOLUME, ACE_CString(kse.listingSize, sizeof ( kse.listingSize )));
            bind(MASTER_SUBSTITUE_PRICE, ACE_CString(kse.substitutePrice, sizeof ( kse.substitutePrice )));

            // bind(MASTER_PAR_PRICE, ACE_CString(kse.faceValue, sizeof(kse.faceValue)-3 )) ;  // 뒤의 소수점 3자리는 무시

            ACE_CString faceValue(kse.faceValue, sizeof ( kse.faceValue ));
            bind(MASTER_PAR_PRICE, getParPriceInteger(faceValue));  // 뒤의 소수점 3자리는 무시
            bind(MASTER_PAR_PRICE_REAL_NUMBER, getParPriceRealNumber(faceValue));

            ACE_CString evaluatePrice(kse.evaluatePrice, sizeof ( kse.evaluatePrice ));
            bind(MASTER_EVALUATION_PRICE, evaluatePrice);
            bind(MASTER_LOWEST_QUOTE_PRICE, lowestQuotePrice);
            bind(MASTER_HIGHEST_QUOTE_PRICE, highestQuotePrice);


            bind(MASTER_IS_INSINCERITY_DISCLOSURE, ACE_CString(kse.isInsincerityPublicNewsAppoint, sizeof ( kse.isInsincerityPublicNewsAppoint )));
            bind(MASTER_REITS, ACE_CString(kse.REITsClassCode, sizeof ( kse.REITsClassCode )));

            // 9차스펙 1 : 1주단위, 10 : 10주단위, 100 : 100주단위, 1000 : 1000주단위 getTradeUnit() 확인 필요.
            // 구스펙 : 매매수량단위.
            // 신스펙의 정규장매매수량단위와 시간외매매수량단위가 같은 값을 가진다.
            // 따라서 실제로 나누는 의미가 없을것이다.

#if(1)
			ACE_CString capital(kse.capital, sizeof ( kse.capital ));
			memset(tmp,0x00,sizeof(tmp));
			sprintf(tmp,"%ld", atol(capital.c_str()));
            bind(MASTER_CAPITAL, tmp);
#endif
			bind(MASTER_KOGI_TYPE, getKogiType(ACE_CString(kse.isCorporateGovernanceIndexStock, sizeof kse.isCorporateGovernanceIndexStock)));
            bind(MASTER_PREEMPTIVE_RIGHT_PRICE, ACE_CString(kse.issuePrice, sizeof ( kse.issuePrice )));

            // (유가) 배당지수종목여부(KODI)

            // (유가)지배구조지수종목여부(KOGI)
            // bind(MASTER_KOGI_TYPE, getKogiType(ACE_CString(kse.isCorporateGovernanceIndexStock, sizeof(kse.isCorporateGovernanceIndexStock)))) ;

            // kse.isCorporateGovernanceIndexStock (지배구조지수조목여부는 filler 처리됨)
            // isKRXSRIGovernance 로 대체함 2012.09.14 시행

            bind(MASTER_CAUTION_TYPE, getInvestmentWarningType(ACE_CString(kse.marketAlarmClassCode, sizeof kse.marketAlarmClassCode)));

			ACE_CString listingdate(kse.listingDate, sizeof(kse.listingDate));
            bind(MASTER_REGISTER_DATE, ACE_CString(kse.listingDate, sizeof(kse.listingDate)));

#if(1)
ACE_DEBUG( ( LM_DEBUG , "[%s] [MasterKseProcessor::MasterKseProcessor],STOCKCODE[%s],REGISTER_DATE[%s]\n" , getCurrentTimestamp().c_str() , stockCode.c_str(), listingdate.c_str()	));
#endif

            //// 상폐일자 => 신주 인수권 증서만 해당 된다.
            //ACE_CString delistingDate(kse.delistingDate, sizeof(kse.delistingDate));

            // 2013.02.26 정리매매여부 추가
            bind(MASTER_CLEAR_OFF_ALLOWANCE_TRADING, ACE_CString(kse.isClearanceTrade, sizeof(kse.isClearanceTrade )));
            bind(MASTER_IS_CLEAR_OFF_ALLOWANCE_TRADING, ACE_CString(kse.isClearanceTrade, sizeof(kse.isClearanceTrade )));

            // 2014.11.28 모의투자시스템을 위해 추가함
            // 단축코드(앞뒤 구분자를 포함한)
            bind(MASTER_ABBR_SYMBOL_FULL, trim(ACE_CString(kse.abbrStockCode, sizeof ( kse.abbrStockCode ))));

            // 재평가사유코드 모의투자지원을 위해 추가함(2014.12.12)
            ACE_CString reEvaluationReasonCode(kse.isRevaluationStockReason, sizeof(kse.isRevaluationStockReason ));
            ACE_CString reEvaluationReason = getReValuationReason(reEvaluationReasonCode);
            bind(MASTER_RE_EVALUATION_REASON, reEvaluationReason);

            // 증자구분코드
            ACE_CString capitalIncreaseClassCode(kse.capitalIncreaseClassCode, sizeof ( kse.capitalIncreaseClassCode ));
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

#if(1)
			ACE_CString upperLimitQuantity(kse.upperLimitQuantity, sizeof ( kse.upperLimitQuantity ));
			memset(tmp,0x00,sizeof(tmp));
			sprintf(tmp,"%ld",atol(upperLimitQuantity.c_str()));
            bind(MASTER_UPPER_LIMIT_QUANTITY, tmp);
#endif

            bind(MASTER_IS_INVESTMENT_PRECAUTION_ISSUE, ACE_CString(kse.isInvestmentPrecautionIssue, ( sizeof kse.isInvestmentPrecautionIssue )));

#if(0)
bind(MASTER_BPS,"");
bind(MASTER_DIVIDEND_PER_SHARE,"");
bind(MASTER_DIVIDENED_PROFIT_RATE,"");
bind(MASTER_EPS,"");
bind(MASTER_INDEX,"");
bind(MASTER_IS_CREDIT_ORDER_POSSIBILITY,"");
bind(MASTER_IS_LOSS,"");
bind(MASTER_IS_OVERTIME_MARKET_TRADING_POSSIBILITY,"");
bind(MASTER_IS_PREFERRED_STOCKS_WITH_LESSER_SHARES,"");
bind(MASTER_KODI_TYPE,"");
bind(MASTER_KOSPI100,"");
bind(MASTER_KOSPI200,"");
bind(MASTER_KOSPI50,"");
bind(MASTER_MANUFACTURING,"");
bind(MASTER_PBR,"");
bind(MASTER_PER,"");
bind(MASTER_TOTAL_MARKET_PRICE_TYPE,"");
bind(MASTER_TRADE_UNIT,"");
bind(MASTER_UNI_INDEX,"");
#endif

            isValidPacket_ = true;
        }
        catch ( std::exception& e )
        {
            isValidPacket_ = false;
        }
    }
}
#endif

#if(1)
MasterKseProcessor::MasterKseProcessor(const ACE_CString &frameId, const ACE_CString &packet, int serial, ExturePlusKseMaster kseUsage)
        : MasterProcessor(serial)
{
	ACE_CString dataType(packet.substr(0, 5));

	char tmp[1024];

    isValidPacket_ = false;
    if ( EXTURE_PLUS_KSE_JISU_MASTER_SIZE != static_cast<int>(packet.length()) )
    {
        isValidPacket_ = false;
    }
    else
    {
        ExturePlusKseJisuMaster kse;
        ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

        ACE_CString dataClass(kse.dataClass, sizeof(kse.dataClass));
        ACE_CString stockCode(kse.stockCode, sizeof(kse.stockCode));
        ACE_CString isManufactureIndustry(kse.isManufactureIndustry, sizeof ( kse.isManufactureIndustry ));
        ACE_CString businessTypeKOSPI200(kse.businessTypeKOSPI200, sizeof ( kse.businessTypeKOSPI200 ));
        ACE_CString isKOSPI100(kse.isKOSPI100, sizeof ( kse.isKOSPI100 ));
        ACE_CString isKOSPI50(kse.isKOSPI50, sizeof ( kse.isKOSPI50 ));
        ACE_CString listPriceSizeCode(kse.listPriceSizeCode, sizeof ( kse.listPriceSizeCode ));
        ACE_CString isKRX100Stock(kse.isKRX100Stock, sizeof ( kse.isKRX100Stock ));
        ACE_CString dividendEarningRate(kse.dividendEarningRate, sizeof ( kse.dividendEarningRate ) - 1);  // 소수점 1 자리 제외
        ACE_CString isloss(kse.isloss, sizeof ( kse.isloss ));

        symbol_ = stockCode;

        ACE_CString kosdaq150IndexIssue(kse.kosdaq150IndexIssue, sizeof ( kse.kosdaq150IndexIssue ));
        ACE_CString krx300(kse.krx300, sizeof ( kse.krx300 ));

		ACE_CString bpsSign;
		ACE_CString pbrSign;
		ACE_CString perSign;
		ACE_CString epsSign;

#if(1)
		if(kse.BPS[0]=='0') bpsSign="+";

        ACE_CString rawBPS(kse.BPS, sizeof ( kse.BPS ));

        ACE_CString BPS(getSignSymbol(bpsSign) + rawBPS);

		if(kse.PBR[0]=='0') pbrSign="+";

        ACE_CString rawPBR(kse.PBR, sizeof ( kse.PBR ));
        ACE_CString PBR(getSignSymbol(pbrSign) + rawPBR);

		if(kse.PER[0]=='0') perSign="+";

        ACE_CString rawPER(kse.PER, sizeof ( kse.PER ));
        ACE_CString PER(getSignSymbol(perSign) + rawPER);
#endif

        ACE_CString isKRX_BBIG_K_NewDealIndex(kse.isKRX_BBIG_K_NewDealIndex, sizeof ( kse.isKRX_BBIG_K_NewDealIndex ));
        ACE_CString isKRX_secondaryBattery_K_NewDealIndex(kse.isKRX_secondaryBattery_K_NewDealIndex, sizeof ( kse.isKRX_secondaryBattery_K_NewDealIndex ));
        ACE_CString isKRX_bio_K_NewDealIndex(kse.isKRX_bio_K_NewDealIndex, sizeof ( kse.isKRX_bio_K_NewDealIndex ));

        /*
         * 2021.11.29 스펙변경
         * 미사용 데이터이며, 정상 파싱여부 확인을 위해 출력만 한다.
         */

#if(1)
ACE_CString abbrStockCode(kseUsage.abbrStockCode + 1, sizeof ( kseUsage.abbrStockCode ) - 1);
ACE_CString abbrStockNameKor(kseUsage.abbrStockNameKor, sizeof ( kseUsage.abbrStockNameKor ));
ACE_CString abbrStockNameEng(kseUsage.abbrStockNameEng, sizeof ( kseUsage.abbrStockNameEng ));
ACE_CString ydayClosePrice(kseUsage.ydayClosePrice, sizeof ( kseUsage.ydayClosePrice ));
ACE_CString upLimitPrice(kseUsage.upLimitPrice, sizeof ( kseUsage.upLimitPrice ));
ACE_CString downLimitPrice(kseUsage.downLimitPrice, sizeof ( kseUsage.downLimitPrice ));
ACE_CString standardPrice(kseUsage.standardPrice, sizeof ( kseUsage.standardPrice ));
ACE_CString isManagementStock(kseUsage.isManagementStock, sizeof ( kseUsage.isManagementStock ));
ACE_CString isTradeStop(kseUsage.isTradeStop, sizeof ( kseUsage.isTradeStop ));
ACE_CString exClassCode(kseUsage.exClassCode, sizeof ( kseUsage.exClassCode ));
ACE_CString faceValueChangeClassCode(kseUsage.faceValueChangeClassCode, sizeof ( kseUsage.faceValueChangeClassCode ));
ACE_CString ydayAccmVolume(kseUsage.ydayAccmVolume, sizeof ( kseUsage.ydayAccmVolume ));
ACE_CString ydayAccmAmount(kseUsage.ydayAccmAmount, sizeof ( kseUsage.ydayAccmAmount ));
ACE_CString listingSize(kseUsage.listingSize, sizeof ( kseUsage.listingSize ));
ACE_CString substitutePrice(kseUsage.substitutePrice, sizeof ( kseUsage.substitutePrice ));
ACE_CString faceValue(kseUsage.faceValue, sizeof ( kseUsage.faceValue ) - 2);  // 뒤의 소수점 2자리는 무시
ACE_CString lowestQuotePrice(kseUsage.lowestQuotePrice, sizeof ( kseUsage.lowestQuotePrice ));
ACE_CString highestQuotePrice(kseUsage.highestQuotePrice, sizeof ( kseUsage.highestQuotePrice ));
ACE_CString isInsincerityPublicNewsAppoint(kseUsage.isInsincerityPublicNewsAppoint, sizeof ( kseUsage.isInsincerityPublicNewsAppoint ));
ACE_CString REITsClassCode(kseUsage.REITsClassCode, sizeof ( kseUsage.REITsClassCode ));
ACE_CString capital(kseUsage.capital, sizeof ( kseUsage.capital ) - 3);  // 뒤의 소수점 3자리는 무시
ACE_CString issuePrice(kseUsage.issuePrice, sizeof ( kseUsage.issuePrice ));
ACE_CString isCorporateGovernanceFine(kseUsage.isCorporateGovernanceFine, sizeof ( kseUsage.isCorporateGovernanceFine ));
ACE_CString marketAlarmClassCode(kseUsage.marketAlarmClassCode, sizeof kseUsage.marketAlarmClassCode);
ACE_CString listingDate(kseUsage.listingDate, sizeof kseUsage.listingDate);
ACE_CString ETFFollowingEarningRateMultiple(kseUsage.ETFFollowingEarningRateMultiple, sizeof ( kseUsage.ETFFollowingEarningRateMultiple ));
ACE_CString ETFReplicationMethodTypeCode(kseUsage.ETFReplicationMethodTypeCode, ( sizeof kseUsage.ETFReplicationMethodTypeCode ));
ACE_CString shortTermFeverishInstrumentTypeCode(kseUsage.shortTermFeverishInstrumentTypeCode, sizeof ( kseUsage.shortTermFeverishInstrumentTypeCode ));
ACE_CString isClearanceTrade(kseUsage.isClearanceTrade, ( sizeof kseUsage.isClearanceTrade ));
ACE_CString expirationDate(kseUsage.expirationDate, sizeof ( kseUsage.expirationDate ));
ACE_CString distributeTypeCode(kseUsage.distributeTypeCode, sizeof ( kseUsage.distributeTypeCode ));
ACE_CString expirationRedemptionPriceDecisionStartDate(kseUsage.expirationRedemptionPriceDecisionStartDate, sizeof ( kseUsage.expirationRedemptionPriceDecisionStartDate ));
ACE_CString expirationRedemptionPriceDecisionEndDate(kseUsage.expirationRedemptionPriceDecisionEndDate, sizeof ( kseUsage.expirationRedemptionPriceDecisionEndDate ));
ACE_CString isShortStockSellingPossibility(kseUsage.isShortStockSellingPossibility, sizeof ( kseUsage.isShortStockSellingPossibility ));
ACE_CString lowLiquidity(kseUsage.lowLiquidity, sizeof ( kseUsage.lowLiquidity ));
ACE_CString abnormalRise(kseUsage.abnormalRise, sizeof ( kseUsage.abnormalRise ));
ACE_CString isOpenPriceBecomeStdPrice(kseUsage.isOpenPriceBecomeStdPrice, sizeof ( kseUsage.isOpenPriceBecomeStdPrice ));
ACE_CString preferredStockClassCode(kseUsage.preferredStockClassCode, sizeof ( kseUsage.preferredStockClassCode ));
ACE_CString stockType = getStockType(preferredStockClassCode);
ACE_CString randomEndTriggerConditionCode(kseUsage.randomEndTriggerConditionCode, sizeof ( kseUsage.randomEndTriggerConditionCode ));
ACE_CString isInvestmentPrecautionIssue(kseUsage.isInvestmentPrecautionIssue, sizeof ( kseUsage.isInvestmentPrecautionIssue ));
ACE_CString indexCalculationInstitution_code(kseUsage.indexCalculationInstitution_code, sizeof ( kseUsage.indexCalculationInstitution_code ));
ACE_CString isSPAC_merger(kseUsage.isSPAC_merger, sizeof ( kseUsage.isSPAC_merger ));
#endif

        try
        {
            CheckSize(packet.length(), EXTURE_PLUS_KSE_JISU_MASTER_SIZE);

            // log frame count status
            LogFrameCount(frameId);

            ExturePlusKseJisuMaster kse;
            ACE_OS::memcpy(&kse, packet.c_str(), packet.length());

            ACE_CString stockCode(kse.stockCode, sizeof kse.stockCode);
            if ( stockCode == "999999999999" )
            {
                return;
            }

            bind(MASTER_SYMBOL, stockCode);

            ACE_CString symbolSubtype(kse.stockGroupID, sizeof ( kse.stockGroupID ));
            bind(MASTER_SYMBOL_SUBTYPE, getSymbolSubtype(symbolSubtype));
            bind(MASTER_MANUFACTURING, getManufacturingType(ACE_CString(kse.isManufactureIndustry, sizeof ( kse.isManufactureIndustry ))));

            ACE_CString index2(kse.indexBusinessTypeMedium, sizeof ( kse.indexBusinessTypeMedium ));  //지수업종 중
            ACE_CString index3(kse.indexBusinessTypeSmall, sizeof ( kse.indexBusinessTypeSmall ));    //지수업종 소

			ACE_DEBUG( ( LM_DEBUG , "[%s]1. [MasterKseProcessor::MasterKseProcessor]symbol:[%s],index[%s],[%s]\n" , 
				getCurrentTimestamp().c_str() , 
				stockCode.c_str(),
				index2.c_str(), index3.c_str()));

			index2=getSymbolUpCode(index2);
			index3=getSymbolUpCode(index3);

			ACE_DEBUG( ( LM_DEBUG , "[%s]1. [MasterKseProcessor::MasterKseProcessor]symbol:[%s],index[%s],[%s]\n" , 
				getCurrentTimestamp().c_str() , 
				stockCode.c_str(),
				index2.c_str(), index3.c_str()));
		    
            std::string stockGroupID(kse.stockGroupID, sizeof ( kse.stockGroupID ));
            boost::trim(stockGroupID);
            ACE_CString industryClassCode;
            if ( stockGroupID == "DR" )  // DR:주식예탁증서
            {
                industryClassCode = getIndustryClassCode("451", "000");
            }
            else if ( stockGroupID == "EW" ) // EW:ELW
            {
                industryClassCode = getIndustryClassCode("452", "000");
            }
            else if ( stockGroupID == "EF" ) // EF:ETF
            {
                industryClassCode = getIndustryClassCode("453", "000");
            }
            else if ( stockGroupID == "SW" ) // SW:신주인수권증권
            {
                industryClassCode = getIndustryClassCode("454", "000");
            }
            else if ( stockGroupID == "SR" ) // SR:신주인수권증서
            {
                industryClassCode = getIndustryClassCode("455", "000");
            }
            else if ( stockGroupID == "BC" ) // BC:수익증권
            {
                industryClassCode = getIndustryClassCode("456", "000");
            }
            else if ( stockGroupID == "FE" ) // FE:해외ETF
            {
                industryClassCode = getIndustryClassCode("457", "000");
            }
            else if ( stockGroupID == "FS" ) // FS:외국주권
            {
                industryClassCode = getIndustryClassCode("458", "000");
            }
            else if ( stockGroupID == "EN" ) // EN:ETN
            {
                industryClassCode = getIndustryClassCode("459", "000");
            }
            else
            {
                industryClassCode = getIndustryClassCode(index2, index3);
            }

            if ( industryClassCode.length() > 12 )
            {
                industryClassCode = industryClassCode.substr(0, 12);
            }

            bind(MASTER_INDEX, industryClassCode);
            bind(MASTER_KOSPI200, ACE_CString(kse.businessTypeKOSPI200, sizeof ( kse.businessTypeKOSPI200 )));
            bind(MASTER_KOSPI100, getKospi100(ACE_CString(kse.isKOSPI100, sizeof ( kse.isKOSPI100 ))));
            bind(MASTER_KOSPI50, getKospi50(ACE_CString(kse.isKOSPI50, sizeof ( kse.isKOSPI50 ))));

            // 9차스펙 1 : 1주단위, 10 : 10주단위, 100 : 100주단위, 1000 : 1000주단위 getTradeUnit() 확인 필요.
            // 구스펙 : 매매수량단위.
            // 신스펙의 정규장매매수량단위와 시간외매매수량단위가 같은 값을 가진다.
            // 따라서 실제로 나누는 의미가 없을것이다.
            bind(MASTER_TOTAL_MARKET_PRICE_TYPE, getTotalMarketPriceType(ACE_CString(kse.listPriceSizeCode, sizeof ( kse.listPriceSizeCode ))));

            bind(MASTER_UNI_INDEX, ACE_CString(kse.isKRX100Stock, sizeof ( kse.isKRX100Stock )));

#if(1)
bind(MASTER_EXCHANGE, EXCHANGE_KSE_STRING);
bind(MASTER_SYMBOL_TYPE, SYMBOL_STOCK_STRING);
#endif

#if(1)
			ACE_CString dividendearningrate(kse.dividendEarningRate, sizeof ( kse.dividendEarningRate ));

		    double dividendearningrate_1 = ::atof(dividendearningrate.c_str());
			int dividendearningrate_2 = (int) ( dividendearningrate_1 );
			memset(tmp, 0x00, sizeof ( tmp ));
		    sprintf(tmp, "%d", dividendearningrate_2);

			bind(MASTER_DIVIDENED_PROFIT_RATE, tmp);
#endif

#if(1)
            // 주당배당금액
            ACE_CString strDividendPriceRaw(kse.dividendPrice, sizeof ( kse.dividendPrice ));
			memset(tmp,0x00,sizeof(tmp));
			sprintf(tmp, "%ld", atol(strDividendPriceRaw.c_str()));
            bind(MASTER_DIVIDEND_PER_SHARE, tmp);

			memset(tmp,0x00,sizeof(tmp));
			sprintf(tmp, "%ld", atol(BPS.c_str()));
            bind(MASTER_BPS, tmp);

			if(kse.EPS[0]=='0') epsSign="+";

	        ACE_CString rawEPS(kse.EPS, sizeof ( kse.EPS ));
		    ACE_CString EPS(getSignSymbol(epsSign) + rawEPS);

			memset(tmp,0x00,sizeof(tmp));
			sprintf(tmp, "%ld", atol(EPS.c_str()));
            bind(MASTER_EPS, tmp);

            bind(MASTER_PBR, getCommonPriceDoubleInteger(trim(PBR)));
			bind(MASTER_PER, getCommonPriceDoubleInteger(PER));
#endif
            bind(MASTER_IS_LOSS, trim(isloss));








#if(1)
bind(MASTER_SYMBOL, stockCode);
bind(MASTER_EXCHANGE, EXCHANGE_KSE_STRING);
bind(MASTER_SYMBOL_TYPE, SYMBOL_STOCK_STRING);

char tempBuf[1024];
::memset(&tempBuf, 0, sizeof ( tempBuf ));
::sprintf(tempBuf, "%d", DECIMAL_0);
bind(MASTER_DECIMAL_POINT, tempBuf);

bind(MASTER_ABBR_SYMBOL, trim(ACE_CString(kseUsage.abbrStockCode + 1, sizeof ( kseUsage.abbrStockCode ) - 1)));
bind(MASTER_NAME, trim(ACE_CString(kseUsage.abbrStockNameKor, sizeof ( kseUsage.abbrStockNameKor ))));

bind(MASTER_ENG_NAME, trim(ACE_CString(kseUsage.abbrStockNameEng, sizeof ( kseUsage.abbrStockNameEng ))));
bind(MASTER_YDAY_CLOSE, ACE_CString(kseUsage.ydayClosePrice, sizeof ( kseUsage.ydayClosePrice )));
bind(MASTER_UP_LIMIT, ACE_CString(kseUsage.upLimitPrice, sizeof ( kseUsage.upLimitPrice )));
bind(MASTER_DOWN_LIMIT, ACE_CString(kseUsage.downLimitPrice, sizeof ( kseUsage.downLimitPrice )));
bind(MASTER_STD_PRICE, ACE_CString(kseUsage.standardPrice, sizeof ( kseUsage.standardPrice )));
bind(MASTER_MANAGEMENT, getManagementType(ACE_CString(kseUsage.isManagementStock, sizeof ( kseUsage.isManagementStock ))));
bind(MASTER_IS_MANAGEMENT, ACE_CString(kseUsage.isManagementStock, sizeof ( kseUsage.isManagementStock )));
bind(MASTER_SUSPENSION, getSuspensionType(ACE_CString(kseUsage.isTradeStop, sizeof ( kseUsage.isTradeStop ))));
bind(MASTER_IS_SUSPENSION, ACE_CString(kseUsage.isTradeStop, sizeof ( kseUsage.isTradeStop )));
bind(MASTER_EX, getEx(ACE_CString(kseUsage.exClassCode, sizeof ( kseUsage.exClassCode ))));
bind(MASTER_SPLITMERGE, getSplitMerge(ACE_CString(kseUsage.faceValueChangeClassCode, sizeof ( kseUsage.faceValueChangeClassCode ))));
bind(MASTER_YDAY_VOLUME, ACE_CString(kseUsage.ydayAccmVolume, sizeof ( kseUsage.ydayAccmVolume )));

#if(1)
ACE_CString ydayaccmamount(kseUsage.ydayAccmAmount, sizeof ( kseUsage.ydayAccmAmount ));
memset(tmp,0x00,sizeof(tmp));
sprintf(tmp,"%ld", atol(ydayaccmamount.c_str()));
bind(MASTER_YDAY_AMOUNT, tmp);
#endif
bind(MASTER_LISTING_VOLUME, ACE_CString(kseUsage.listingSize, sizeof ( kseUsage.listingSize )));
bind(MASTER_SUBSTITUE_PRICE, ACE_CString(kseUsage.substitutePrice, sizeof ( kseUsage.substitutePrice )));

// bind(MASTER_PAR_PRICE, ACE_CString(kseUsage.faceValue, sizeof(kseUsage.faceValue)-3 )) ;  // 뒤의 소수점 3자리는 무시

ACE_CString faceValue(kseUsage.faceValue, sizeof ( kseUsage.faceValue ));
bind(MASTER_PAR_PRICE, getParPriceInteger(faceValue));  // 뒤의 소수점 3자리는 무시
bind(MASTER_PAR_PRICE_REAL_NUMBER, getParPriceRealNumber(faceValue));

ACE_CString evaluatePrice(kseUsage.evaluatePrice, sizeof ( kseUsage.evaluatePrice ));
bind(MASTER_EVALUATION_PRICE, evaluatePrice);
bind(MASTER_LOWEST_QUOTE_PRICE, lowestQuotePrice);
bind(MASTER_HIGHEST_QUOTE_PRICE, highestQuotePrice);


bind(MASTER_IS_INSINCERITY_DISCLOSURE, ACE_CString(kseUsage.isInsincerityPublicNewsAppoint, sizeof ( kseUsage.isInsincerityPublicNewsAppoint )));
bind(MASTER_REITS, ACE_CString(kseUsage.REITsClassCode, sizeof ( kseUsage.REITsClassCode )));

#if(1)
ACE_CString capital(kseUsage.capital, sizeof ( kseUsage.capital ));
memset(tmp,0x00,sizeof(tmp));
sprintf(tmp,"%ld", atol(capital.c_str()));
bind(MASTER_CAPITAL, tmp);
#endif
bind(MASTER_KOGI_TYPE, getKogiType(ACE_CString(kseUsage.isCorporateGovernanceIndexStock, sizeof kseUsage.isCorporateGovernanceIndexStock)));
bind(MASTER_PREEMPTIVE_RIGHT_PRICE, ACE_CString(kseUsage.issuePrice, sizeof ( kseUsage.issuePrice )));

bind(MASTER_CAUTION_TYPE, getInvestmentWarningType(ACE_CString(kseUsage.marketAlarmClassCode, sizeof kseUsage.marketAlarmClassCode)));

ACE_CString listingdate(kseUsage.listingDate, sizeof(kseUsage.listingDate));
bind(MASTER_REGISTER_DATE, ACE_CString(kseUsage.listingDate, sizeof(kseUsage.listingDate)));
bind(MASTER_CLEAR_OFF_ALLOWANCE_TRADING, ACE_CString(kseUsage.isClearanceTrade, sizeof(kseUsage.isClearanceTrade )));
bind(MASTER_IS_CLEAR_OFF_ALLOWANCE_TRADING, ACE_CString(kseUsage.isClearanceTrade, sizeof(kseUsage.isClearanceTrade )));
bind(MASTER_ABBR_SYMBOL_FULL, trim(ACE_CString(kseUsage.abbrStockCode, sizeof ( kseUsage.abbrStockCode ))));
ACE_CString reEvaluationReasonCode(kseUsage.isRevaluationStockReason, sizeof(kseUsage.isRevaluationStockReason ));
ACE_CString reEvaluationReason = getReValuationReason(reEvaluationReasonCode);
bind(MASTER_RE_EVALUATION_REASON, reEvaluationReason);

ACE_CString capitalIncreaseClassCode(kseUsage.capitalIncreaseClassCode, sizeof ( kseUsage.capitalIncreaseClassCode ));
ACE_CString capitalIncreaseType = getMasterIncreaseType(capitalIncreaseClassCode);
bind(MASTER_CAPITAL_INCREASE_TYPE, capitalIncreaseType);
bind(MASTER_STOCK_TYPE, stockType);
bind(MASTER_IS_OPEN_PRICE_BECOME_STD_PRICE, getIsOpenPriceBecomeStdPrice(isOpenPriceBecomeStdPrice));
bind(MASTER_IS_SHORT_STOCK_SELLING_POSSIBILITY, trim(isShortStockSellingPossibility));
bind(MASTER_IS_LOW_LIQUIDITY, trim(lowLiquidity));
bind(MASTER_IS_ABNORMAL_RISE, trim(abnormalRise));

#if(1)
ACE_CString upperLimitQuantity(kseUsage.upperLimitQuantity, sizeof ( kseUsage.upperLimitQuantity ));
memset(tmp,0x00,sizeof(tmp));
sprintf(tmp,"%ld",atol(upperLimitQuantity.c_str()));
bind(MASTER_UPPER_LIMIT_QUANTITY, tmp);
#endif

bind(MASTER_IS_INVESTMENT_PRECAUTION_ISSUE, ACE_CString(kseUsage.isInvestmentPrecautionIssue, ( sizeof kseUsage.isInvestmentPrecautionIssue )));
#endif

            isValidPacket_ = true;
        }
        catch ( std::exception& e )
        {
            isValidPacket_ = false;
        }
    }
}
#endif

bool MasterKseProcessor::isValidPacket()
{
    return isValidPacket_;
}

ACE_CString MasterKseProcessor::getSymbol()
{
    return symbol_;
}

ACE_CString MasterKseProcessor::getKospi50(const ACE_CString& raw)
{
    char result;
    if ( raw == "Y" )  // KOSPI 50
    {
        result = MEMBER_OF_INDEX_YES;
    }
    else
    {
        result = MEMBER_OF_INDEX_NO;
    }
    return result;
}

ACE_CString MasterKseProcessor::getKospi100(const ACE_CString& raw)
{
    char result;
    if ( raw == "Y" )
    {
        result = MEMBER_OF_INDEX_YES;
    }
    else
    {
        result = MEMBER_OF_INDEX_NO;
    }
    return result;
}

MasterKseProcessor::~MasterKseProcessor()
{
}

BYTE MasterKseProcessor::getExchange()
{
    return EXCHANGE_KSE;
}

ACE_CString MasterKseProcessor::getSymbolSubtype(const ACE_CString& raw)
{
    ACE_CString result;

    if ( raw == "ST" )
    {
        result = SYMBOL_SUBTYPE_STRING_ST;
    }
    else if ( raw == "MF" )
    {
        result = SYMBOL_SUBTYPE_STRING_MF;
    }
    else if ( raw == "RT" )
    {
        result = SYMBOL_SUBTYPE_STRING_RT;
    }
    else if ( raw == "SC" )
    {
        result = SYMBOL_SUBTYPE_STRING_SC;
    }
    else if ( raw == "IF" )
    {
        result = SYMBOL_SUBTYPE_STRING_IF;
    }
    else if ( raw == "DR" )
    {
        result = SYMBOL_SUBTYPE_STRING_DR;
    }
    else if ( raw == "EW" )
    {
        result = SYMBOL_SUBTYPE_STRING_EW;
    }
    else if ( raw == "EF" )
    {
        result = SYMBOL_SUBTYPE_STRING_EF;
    }
    else if ( raw == "SW" )
    {
        result = SYMBOL_SUBTYPE_STRING_SW;
    }
    else if ( raw == "SR" )
    {
        result = SYMBOL_SUBTYPE_STRING_SR;
    }
    else if ( raw == "BC" )
    {
        result = SYMBOL_SUBTYPE_STRING_BC;
    }
    else if ( raw == "FE" )
    {
        result = SYMBOL_SUBTYPE_STRING_FE;
    }
    else if ( raw == "FS" )
    {
        result = SYMBOL_SUBTYPE_STRING_FS;
    }
    else if ( raw == "EN" )
    {
        result = SYMBOL_SUBTYPE_STRING_EN;
    }
    return result;
}

ACE_CString MasterKseProcessor::getManufacturingType(const ACE_CString& raw)
{
    ACE_CString result;

    if ( raw == "Y" )
    {
        result = "제조업";
    }
    else
    {
        result = "비제조업";
    }
    return result;
}

ACE_CString MasterKseProcessor::getManagementType(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "Y" )
    {
        result = MASTER_MANAGEMENT_VALUE_MAN;
    }
    else if ( raw == "N" )
    {
        result = MASTER_MANAGEMENT_VALUE_NORMAL;
    }
    else
    {
        result = MASTER_MANAGEMENT_VALUE_NORMAL;
    }
    return result;
}

ACE_CString MasterKseProcessor::getSuspensionType(const ACE_CString& raw)
{
    ACE_CString result;

    //거래정지
    if ( raw == "Y" )
    {
        result = MASTER_SUSPENSION_VALUE_SUSPENDED;
    }
    // 정상
    else
    {
        result = MASTER_SUSPENSION_VALUE_NORMAL;
    }
    return result;
}

ACE_CString MasterKseProcessor::getEx(const ACE_CString& rawEx)
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
        result = "중간(분기)배당락";
    }
    else if ( rawEx == "06" )
    {
        result = "권리중간배당락";
    }
    else if ( rawEx == "07" )
    {
        result = "권리분기배당락";
    }
    else if ( rawEx == "99" )
    {
        result = "기타";
    }
    else
    {
        result = "정상";
    }
    //ACE_DEBUG((LM_ERROR, "[%s] [MasterKseProcessor::getEx] [%s]\n", getCurrentTimestamp().c_str(), result.c_str() ));
    return result;
}

ACE_CString MasterKseProcessor::getSplitMerge(const ACE_CString& rawEx)
{
    /*
     * 00:해당없음(액면가변경이 취해질 수 있는 종목군에 대해 변경

     없음을 의미) 01:액면분할 02:액면병합 03:주식분할 04:주식병합 99:기타

     (2012.08.27)
     *
     */
    ACE_CString result = "정상";
    if ( rawEx == "00" )
    {
        result = "정상";  // 00:해당없음(액면가변경이 취해질 수 있는 종목군에 대해 변경없음을 의미)
    }
    else if ( rawEx == "01" )
    {
        result = "액면분할";
    }
    else if ( rawEx == "02" )
    {
        result = "액면병합";
    }
    else if ( rawEx == "03" )
    {
        result = "주식분할";
    }
    else if ( rawEx == "04" )
    {
        result = "주식병합";
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

ACE_CString MasterKseProcessor::getTotalMarketPriceType(const ACE_CString& raw)
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
    else if ( raw == "0" )
    {
        result = "제외";
    }
    return result;
}

ACE_CString MasterKseProcessor::getKogiType(const ACE_CString& raw)
{
    ACE_CString result("일반");

    if ( raw == "Y" )
    {
        result = "우량";
    }
    else if ( raw == "N" )
    {
        result = "일반";
    }
    return result;
}

#if(0)
// 종목이 소분류(index3)에 직접 속해있을 경우에는 소분류 코드를 사용,
// 소분류에 속하지 않고(index3 == "000"), 직접 중분류에 속해 있을 경우에는
// 중분류 코드를 사용
ACE_CString MasterKseProcessor::getIndustryClassCode(const ACE_CString& index2, const ACE_CString& index3)
{
    std::ostringstream os;
    os << "KRI" << ( index3 == "000" ? index2 : index3 ).c_str() << "000000";
    return os.str().c_str();
}
#endif

ACE_CString MasterKseProcessor::getTradeUnit(const ACE_CString& raw)
{
    int tradeUnitNum = atoi(raw.c_str());
    if ( tradeUnitNum == 0 )
    {
        tradeUnitNum = 1;
    }
    char tradeUnitChar[6];
    ::memset(&tradeUnitChar, 0, sizeof ( tradeUnitChar ));
    ::sprintf(tradeUnitChar, "%d", tradeUnitNum);
    ACE_CString result(tradeUnitChar);
    return result;
}

ACE_CString MasterKseProcessor::getInvestmentWarningType(const ACE_CString& rawAlarm)
{
    ACE_CString result(MASTER_CAUTION_TYPE_VALUE_NORMAL);
    if ( rawAlarm == "00" )
    {
        result = MASTER_CAUTION_TYPE_VALUE_NORMAL;
    }
    else if ( rawAlarm == "01" )
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

#if(0)
ACE_CString MasterKseProcessor::getStockMainBatchGroupID(const ACE_CString& raw)
{
    ExturePlusKseMaster kse;
    ACE_OS::memcpy(&kse, raw.c_str(), raw.length());
    ACE_CString symbolSubtype(kse.stockGroupID, sizeof ( kse.stockGroupID ));
    return symbolSubtype;
}
ACE_CString MasterKseProcessor::getStockJisuBatchGroupID(const ACE_CString& raw)
{
    ExturePlusKseJisuMaster kse;
    ACE_OS::memcpy(&kse, raw.c_str(), raw.length());
    ACE_CString symbolSubtype(kse.stockGroupID, sizeof ( kse.stockGroupID ));
    return symbolSubtype;
}
#endif

ACE_CString MasterKseProcessor::getIsDividendIndexStock(const ACE_CString& raw)
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

ACE_CString MasterKseProcessor::getEpsSign(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "-" )
    {
        result = "-";
    }
    return result;
}

ACE_CString MasterKseProcessor::getETFType(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "0" )
    {
        result = "해당없음";
    }
    else if ( raw == "1" )
    {
        result = "투자회사형";
    }
    else if ( raw == "2" )
    {
        result = "수익증권형";
    }
    else
    {
        result = "해당없음";
    }
    return result;
}

ACE_CString MasterKseProcessor::getReValuationReason(const ACE_CString& raw)
{
    // 2020.09.07 스펙변경 대응
    // 00:해당없음
    // 01:회사분할
    // 02:자본감소
    // 03:장기간정지
    // 04:초과분배
    // 05:대규모배당
    // 06:회사분할합병
    // 07:ETN증권병합,분할
    // 99:기타
    ACE_CString result;
    if ( raw == "00" )
    {
        result = "해당없음";
    }
    else if ( raw == "01" )
    {
        result = "회사분할";
    }
    else if ( raw == "02" )
    {
        result = "자본감소";
    }
    else if ( raw == "03" )
    {
        result = "장기간정지";
    }
    else if ( raw == "04" )
    {
        result = "초과분배";
    }
    else if ( raw == "05" )
    {
        result = "대규모배당";
    }
    else if ( raw == "06" )
    {
        result = "회사분할합병";
    }
    else if ( raw == "07" )
    {
        result = "ETN증권병합,분할";
    }
    else if ( raw == "99" )
    {
        result = "기타";
    }
    else
    {
        result = "해당없음";
    }
    return result;
}

ACE_CString MasterKseProcessor::getParPriceInteger(const ACE_CString& rawParPrice)
{
    // 9(9)V9(3)
    double parPrice = ::atof(rawParPrice.c_str());
    parPrice = parPrice / 1;
    int parPriceInt = (int) ( parPrice );
    char strBuf[1024];
    ::memset(&strBuf, 0, sizeof ( strBuf ));
    ::sprintf(strBuf, "%d", parPriceInt);
    std::string strParPriceInt(strBuf);
    boost::trim(strParPriceInt);
    ACE_CString aceStrParPriceInt(strParPriceInt.c_str());
    return aceStrParPriceInt;
}

ACE_CString MasterKseProcessor::getParPriceRealNumber(const ACE_CString& rawParPrice)
{
    // 9(9)V9(3)
    double parPrice = ::atof(rawParPrice.c_str());
    parPrice = parPrice / 1;
    char strBuf[1024];
    ::memset(&strBuf, 0, sizeof ( strBuf ));
    ::sprintf(strBuf, "%f", parPrice);
    std::string strParPrice(strBuf);
    boost::trim(strParPrice);
    ACE_CString aceStrParPrice(strParPrice.c_str());
    return aceStrParPrice;
}

ACE_CString MasterKseProcessor::getMasterIncreaseType(const ACE_CString& raw)
{
    // 00:해당없음 01:유상증자 02:무상증자 03:유무상증자 99:기타
    ACE_CString result;
    if ( raw == "00" )
    {
        result = "해당없음";
    }
    else if ( raw == "01" )
    {
        result = "유상증자";
    }
    else if ( raw == "02" )
    {
        result = "무상증자";
    }
    else if ( raw == "03" )
    {
        result = "유무상증자";
    }
    else if ( raw == "99" )
    {
        result = "기타";
    }
    else
    {
        result = "해당없음";
    }
    return result;
}

ACE_CString MasterKseProcessor::getStockType(const ACE_CString& raw)
{
//    93  종류주권구분코드    X   1   458 "0:해당없음(보통주) 1:구형우선주 2:신형우선주 9:종류주권(2014.03.03)
//
//    ※증권그룹ID ST에만 해당
//    ※구명칭:우선주구분코드"

    ACE_CString result;
    if ( raw == "0" )
    {
        result = "보통주";
    }
    else if ( raw == "1" )
    {
        result = "구형우선주";
    }
    else if ( raw == "2" )
    {
        result = "신형우선주";
    }
    else if ( raw == "9" )
    {
        result = "종류증권";
    }
    else
    {
        result = "미정의";
    }
    return ( result );
}

ACE_CString MasterKseProcessor::getIsOpenPriceBecomeStdPrice(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "Y" )
    {
        result = "Y";
    }
    else if ( raw == "N" )
    {
        result = "N";
    }
    else
    {
        result = "N";
    }
    return ( result );

}

ACE_CString MasterKseProcessor::getSignSymbol(const ACE_CString& raw)
{
    ACE_CString result;
    if ( raw == "-" )
    {
        result = "-";
    }
    return result;
}

#if(1)
ACE_CString MasterKseProcessor::getCommonPriceDoubleInteger(const ACE_CString& rawParPrice)
{
    // 9(9)V9(3)
    double parPrice = ::atof(rawParPrice.c_str());
    parPrice = parPrice * 100;
    int parPriceInt = (int) ( parPrice );
    char strBuf[1024];
    ::memset(&strBuf, 0, sizeof ( strBuf ));
    ::sprintf(strBuf, "%d", parPriceInt);
    std::string strParPriceInt(strBuf);
    boost::trim(strParPriceInt);
    ACE_CString aceStrParPriceInt(strParPriceInt.c_str());
    return aceStrParPriceInt;
}
#endif

ACE_CString MasterKseProcessor::getIndustryClassCode(const ACE_CString& index2, const ACE_CString& index3)
{
    std::ostringstream os;
    os << "KRI" << ( index3 == "000" ? index2 : index3 ).c_str() << "000000";
    return os.str().c_str();
}

#if(0)
	ACE_CString indexConstMstKseMap1[599] = {"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P","110043","110046","110043","110004","110007","110012","110014","110020","110021","110023","110037","110038","110039","110040","110041","110042","110044","110045","110049","110051","110052","110053","110056","110057","110058","110059","110060","110061","110062","110065","110066","110067","110068","110069","110070","110071","110072","110073","110074","110077","110078","110079","110080","110081","110082","110083","110084","110086","110087","110088","110089","110090","110091","110092","110093","110094","110095","110096","110097","110098","110099","110100","110101","110102","110103","110104","110105","110106","110107","110108","110109","110110","110111","110112","2P8802","2P8803","2P9259","2P9269","2P9258","2P9284","2P9206","2P9271","2P9234","2P9272","2P9263","2P9256","2P9239","2P9246","2P9247","2P9248","2P9260","2P9255","2P9265","2P9267","2P9266","2P9276","2P9277","2P9278","2P9279","2P9280","2P9281","2P9282","2P9283","2P9231","2P9235","2P9240","2P9275","2P9211","2P9242","2P9243","2P9274","2P9245","2P9262","2P9236","2P9251","2P9238","2P9264","2P9268","2P9229","2P9252","2P9233","2P9253","2P9221","2P9244","2P9222","2P9257","2P9241","2P9273","2P9207","2P9250","2P9237","2P9249","2P9210","2P9232","2P9254","2PB003","2PB101","2PB201","2PB211","2PB221","2PB226","2PB231","2PB232","2PB237","2PB238","2PB239","2PB241","2PB242","2PB243","2PB305","2PB306","2PB307","2PC007","2PC006","2PM128","2PM126","2PM127","2PM119","2PM121","2PM102","2PM104","2PM107","2PM109","2PM112","2PM114","2PM115","2PM116","2PM117","2PM118","2PM122","2PM123","2PM131","2PM124","2PM132","2PM125","2PM120","2PM129","2PM130","2PM134","2PM133","2PM001","2PR001","2PR101","120001","120002","120003","120004","120005","2PW006","120007","120008","120009","120010","120011","120012","120013","120014","120015","120016","120017","120018","120019","120020","120021","120901"};
	ACE_CString indexConstMstKseMap2[599] = {"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","187","188","165","132","133","134","142","136","141","411","412","413","414","415","351","352","353","354","355","356","357","358","105","600","167","203","212","213","214","215","216","217","218","331","204","175","176","169","174","301","302","303","304","801","802","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","004","013","707","731","708","821","312","313","009","010","005","006","007","008","717","003","709","011","012","304","306","307","308","305","822","732","051","052","100","101","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","050","053","054","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","055","056","057","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445","601","602","601","004","007","012","014","020","021","023","037","038","039","040","041","042","044","045","049","051","052","053","056","057","058","059","060","061","062","065","066","067","068","069","070","071","072","073","074","077","078","079","080","081","082","083","084","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","802","803","259","269","258","284","206","271","234","272","263","256","239","246","247","248","260","255","265","267","266","276","277","278","279","280","281","282","283","231","235","240","275","211","242","243","274","245","262","236","251","238","264","268","229","252","233","253","221","244","222","257","241","273","207","250","237","249","210","232","254","003","101","201","211","221","226","231","232","237","238","239","241","242","243","305","306","307","007","006","128","126","127","119","121","102","104","107","109","112","114","115","116","117","118","122","123","131","124","132","125","120","129","130","134","133","001","001","101","001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","901"};
	ACE_CString indexConstMstKseMap3[599] = {"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3","2","2","2","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","8","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","C","C","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","M","R","R","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"};
#endif

#if(1)
#define MASTERJISUTOTCNT 394
#endif

#if(0)
{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P"};
{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","187","188","165","132","133","134","142","136","141","411","412","413","414","415","351","352","353","354","355","356","357","358","105","600","167","203","212","213","214","215","216","217","218","331","204","175","176","169","174","301","302","303","304","801","802","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","004","013","707","731","708","821","312","313","009","010","005","006","007","008","717","003","709","011","012","304","306","307","308","305","822","732","051","052","100","101","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","050","053","054","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","055","056","057","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445"};
{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3"};
#endif

#if(1)
	ACE_CString indexConstMstKseMap1[MASTERJISUTOTCNT] = 
	{"KGG01P","KGZ01P","KGZ02P","KGZ03P","KGS01P","KGS02P","KGS03P","KGS04P","KGS05P","KGS06P","KGS07P","KGS08P","KGS09P","KGS19P","KGS10P","KGS11P","KGS20P","KGS12P","KGS13P","KGS21P","KGS14P","KGS15P","KGS16P","KGS17P","KGS22P","KGS18P","K2G14P","K2G01P","K2G02P","K2G03P","K2S11P","K2S02P","K2S08P","K2S09P","K2S05P","K2S07P","K2S03P","K2S10P","K2S06P","K2S04P","K2S01P","K2W01P","K2W02P","K2W03P","XGW01P","XGG01P","X3G01P","XGS01P","XGS02P","XGS03P","XGS04P","XGS05P","XGS06P","XGS07P","XGS08P","XGS09P","XGS10P","XGS11P","XGS12P","XGS13P","XGS14P","XGS15P","XGS16P","XGS17P","X3E01P","XGE05P","QGG01P","QGZ01P","QGZ02P","QGZ03P","QGS35P","QGS36P","QGS37P","QGS38P","QGS39P","QGS01P","QGS32P","QGS42P","QGS02P","QGS03P","QGS04P","QGS31P","QGS05P","QGS49P","QGS34P","QGS06P","QGS07P","QGS08P","QGS09P","QGS10P","QGS11P","QGS12P","QGS13P","QGS33P","QGS14P","QGS15P","QGS16P","QGS17P","QGS18P","QGS19P","QGS20P","QGS65P","QGS66P","QGS68P","QGS75P","QGS81P","QGS87P","QGS21P","QGS22P","QGS23P","QGS24P","QGS25P","QGS26P","QGS27P","QGS28P","QGS29P","QGS30P","QGG03P","QGG04P","QGG05P","QGG06P","NGG01P","K2B01P","KGD02P","KGD03P","K2B03P","K2T01P","K2E01P","K2E02P","K2W04P","KGD04P","K2G05P","K2G04P","K2G06P","K2G08P","K2G10P","K2D01P","K2D02P","K2D01T","K2D02T","KGD01P","XGE01P","XGE03P","XGE02P","XGB05P","XGE04P","XGG03P","XGT01P","XGT02P","XGT03P","XGT04P","XGT05P","X3S05P","X3S04P","X3S02P","X3S01P","X3S03P","X3S08P","X3S06P","X3S07P","CGD01P","XGG02P","K2Z01P","Q5G01P","Q5S05P","Q5S06P","Q5S07P","Q5S08P","Q5S02P","Q5S03P","Q5S04P","Q5E01P","Q5W01P","K2G01T","K2G01N","K2G07N","K2G07T","FTG01P","FTX01P","FTG02P","FTX07P","FRG01P","FRX01P","FRX02P","K2X01P","F2G01P","F2X02P","O2901P","O2902P","O2905P","K2V01P","K2V02P","K2V03P","K2V04P","MGA07P","MGA02P","MGA01P","MGA03P","MGA04P","GGG01P","GGG02P","MGA10P","MGA11P","F2X03P","F2X04P","FRX03P","FRX04P","FRG03P","FRX09P","FRX10P","FRX11P","FRX12P","FRG02P","FRX05P","FRX06P","FRX07P","FRX08P","Q5X01P","Q5X02P","K2X02P","K2X03P","K2X05P","K2X06P","K2X07P","K2X08P","K2X09P","XGX01P","MGA08P","MGA09P","F5G01P","F5X01T","F5X02T","F5X03T","F5X04T","F2X01P","FT901P","FTX02P","FTX03P","FTX04P","FT904P","FTX05P","F2G02P","F2X07P","F2X08P","F2X09P","TGG01P","TGG02P","OG903P","OG904P","O2903P","F2X06P","O2X01P","MGA12P","FTX06P","FTX08P","OG901P","OG902P","OG907P","OG908P","OG910P","OG911P","F2V01P","GGS01P","O2904P","OG905P","OG906P","F3G01P","F3X01P","F3X02P","F3X03P","X3X01P","MGA13P","F2V02P","O2909P","O2908P","O2906P","O2907P","F2S01P","F2S02P","F2S03P","F2S04P","F2S05P","F2S06P","F2S07P","F2S08P","F2S09P","F2S10P","F2X10P","F2X11P","F2X12P","F2X13P","F2X14P","F2X15P","F2X16P","F2X17P","F2X18P","F2X19P","F2X20P","F2X21P","F2X22P","F2X23P","F2X24P","F2X25P","F2X26P","F2X27P","F2X28P","F2X29P","F2X30P","F2X31P","F2X32P","F2X33P","F2X34P","F2X35P","F2X36P","F2X37P","F2X38P","F2X39P","MGA14P","O2910P","O2911P","O2912P","KGG01T","QGG01T","X3G01T","Q5G01T","KGD02T","KGD03T","K2S07T","K2S03T","K2S06T","K2S05T","K2S10T","K2S02T","K2S08T","K2S09T","K2S04T","K2S01T","K2S11T","K2G06T","K2G06N","K2G08T","K2G08N","K2G10T","K2G10N","O2913P","O2914P","O2915P","FTA01P","FTA02P","FTX10P","FTX11P","XG901P","XG902P","XG903P","XGX02P","FGA03P","FGA04P","FGA05P","FGA06P","FGA07P","FRG01T","OG909P","OG912P","GGE01P","XGV01P","XGV02P","MGA05P","MGA06P","XGX03P","XGX04P","K2D03N","K2X11P","F2901P","F2X05P","F5901P","F5X05P","GGT01P","GGT02P","GGT03P","XGT06T","XGT08T","XGT10T","XGT06P","XGT08P","XGT10P","XGT07P","XGT09P","XGT11P","KGT01P","KGX01P","XGT12P","XGT13P","XGT14P","XGT15P"};
	ACE_CString indexConstMstKseMap2[MASTERJISUTOTCNT] = 
	{"001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","024","025","026","027","028","029","035","036","150","151","152","153","154","155","156","157","158","159","160","401","402","403","441","043","300","044","045","046","047","049","050","052","053","055","056","057","058","061","062","063","064","065","418","419","001","002","003","004","007","008","009","010","011","012","015","017","024","026","027","029","031","033","037","041","042","043","056","058","062","063","065","066","067","068","070","072","074","075","077","081","082","084","092","099","106","151","152","153","154","155","156","157","158","159","160","181","182","183","184","001","161","163","164","166","168","180","283","894","243","182","244","224","227","232","185","186","187","188","165","132","133","134","142","136","141","411","412","413","414","415","351","352","353","354","355","356","357","358","105","600","167","203","212","213","214","215","216","217","218","331","204","175","176","169","174","301","302","303","304","801","802","003","901","701","702","601","703","704","711","712","713","714","815","812","811","813","814","001","002","817","818","705","706","004","005","008","009","010","011","012","013","014","015","016","017","205","210","170","171","172","173","177","178","179","601","819","820","206","207","208","209","231","716","308","309","310","311","896","897","721","722","723","724","001","002","004","013","707","731","708","821","312","313","009","010","005","006","007","008","717","003","709","011","012","304","306","307","308","305","822","732","051","052","100","101","751","752","753","754","755","756","757","758","759","760","761","762","763","764","765","766","767","768","769","770","771","772","773","774","775","776","777","778","779","780","781","782","783","784","785","786","787","788","789","790","827","050","053","054","195","196","198","197","241","242","196","197","198","199","200","201","202","203","204","205","206","225","226","228","230","233","235","055","056","057","321","322","323","324","501","502","503","504","823","824","825","826","841","018","001","002","004","416","417","892","893","916","917","282","895","284","285","420","421","429","430","431","432","433","434","420","421","422","426","427","428","918","919","442","443","444","445"};
	ACE_CString indexConstMstKseMap3[MASTERJISUTOTCNT] = 
	{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","5","5","5","5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","6","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","1","2","2","2","2","2","2","2","2","2","2","1","1","1","1","B","B","B","B","C","C","C","1","1","1","1","1","1","D","D","D","D","D","D","D","D","D","G","G","D","D","1","1","C","C","C","C","C","C","C","C","C","C","C","C","2","2","1","1","1","1","1","1","1","3","D","D","2","2","2","2","2","1","D","D","D","D","B","B","1","1","1","1","C","C","E","E","1","1","1","D","D","D","E","E","E","E","E","E","D","G","1","E","E","3","3","3","3","3","D","1","E","E","E","E","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","D","E","E","E","1","2","3","2","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","E","E","E","D","D","B","B","3","3","3","3","D","D","D","D","D","C","E","E","G","3","3","D","D","3","3","1","1","1","1","2","2","3","3","3","3","3","3","3","3","3","3","3","3","1","1","3","3","3","3"};
#endif

#if(1)
ACE_CString MasterKseProcessor::getSymbolUpCode(const ACE_CString& raw)
{
	int kk=0,ii=0,ff=0;

	for(kk=0; kk<MASTERJISUTOTCNT; kk++)
	{
		if(raw == indexConstMstKseMap1[kk])
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
		return(indexConstMstKseMap2[ii]);
	}
}
#endif





