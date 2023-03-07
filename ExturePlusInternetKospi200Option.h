#ifndef __EXTURE_PLUS_KOSPI_200_OPTION_H__
#define __EXTURE_PLUS_KOSPI_200_OPTION_H__

/*
 12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

#pragma pack(1)

#if(1)
// KOSPI200지수옵션_실시간_UDP(8M)_20140901_2014072501.xls
// 19   K200옵션_Polling 데이터  I2034   모든 포트 확인용으로 송신 1분간격으로 제공    20  1분간격    코스피200지수옵션체결호가정보
class ExturePlusKoscomLineLKInfo_KOSPI200_OPTION
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA 구분
        char informationCategory[2];                            // 002 정보구분
        char marketCategory[1];                                 // 003 시장구분
        char time[4];                                           // 004 시간
        char mainBackupType[2];                                 // 005 MainBackup 구분
        char filler[8];                                         // 006 Filler
        char endOfText[1];                                      // 007 FF
        char recvAddr[32];                                      // 수신주소정보(전문에는 없는 것)
};
const int EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSPI200_OPTION_SIZE = sizeof(ExturePlusKoscomLineLKInfo_KOSPI200_OPTION);
#endif

#if(1)
//KOSPI200지수선물 종목정보 데이터//파생 종목정보
//파생 종목정보//파생 종목정보
//파생 종목정보 전송 완료 후 타 배치정보 전송
//(파생A) DRV : A001F, A003F
class ExturePlusKospi200OptionStockInfoRecord
{
    public:
	char dataClass[2];               //데이터구분값
	char infoMarketClass[3];               //정보구분값
	char distributeStockIndex[8];               //정보분배일련번호
	char stockCount[6];               //정보구분총종목수
	char hireDate[8];               //영업일자
	char stockCode[12];               //종목코드
	char stockSeq[6];               //정보분배종목인덱스
	char futureOptionCode[1];               //선물옵션구분코드
	char productId[11];               //상품ID
	char abbrStockCode[9];               //종목단축코드
	char stockNameKor[80];               //종목명
	char abbrStockNameKor[40];               //종목약명
	char stockNameEng[80];               //종목영문명
	char abbrStockNameEng[40];               //종목영문약명
	char productGroupID[3];               //장운영상품그룹ID
	char listingDate[8];               //상장일자
	char discontinueListingDate[8];               //상장폐지일자
	char stockClassCodeBasedSpread[1];               //스프레드기준종목구분코드
	char finalSettlementTypeCode[1];               //최종결제방법코드
	char price_limit_expansion_direction_code[1];               //가격제한확대적용방향코드
	char price_limit_final_step[3];               //가격제한최종단계
	char price_limit_1st_upper_limit_price[11];               //가격제한1단계상한가
	char price_limit_2nd_upper_limit_price[11];               //가격제한2단계상한가
	char price_limit_3rd_upper_limit_price[11];               //가격제한3단계상한가
	char price_limit_1st_lower_limit_price[11];               //가격제한1단계하한가
	char price_limit_2nd_lower_limit_price[11];               //가격제한2단계하한가
	char price_limit_3rd_lower_limit_price[11];               //가격제한3단계하한가
	char standardPrice[11];               //기준가격
	char baseAssetId[3];               //기초자산ID
	char exerciseTypeCode[1];               //권리행사유형코드
	char spreadTypeCode[2];               //스프레드구성코드
	char spreadNdmStockCode[12];               //스프레드구성종목코드1
	char spreadFdmStockCode[12];               //스프레드구성종목코드2
	char lastTradeDate[8];               //최종거래일자
	char lastSettlementDate[8];               //최종결제일자
	char monthProductClassCode[3];               //결제월일련번호
	char expireDate[8];               //만기일자
	char exercisePrice[18];               //행사가격
	char adjustmentClassCode[1];               //조정구분코드
	char tradeUnit[22];               //거래단위
	char tradeMultiplier[22];               //거래승수
	char marketCreationClassCode[1];               //시장조성구분코드
	char listingTypeCode[1];               //상장유형코드
	char atTheMoney[11];               //등가격
	char adjustmentReasonCode[2];               //조정사유코드
	char baseAssetStockCode[12];               //기초자산종목코드
	char baseAssetClosePrice[11];               //기초자산종가
	char remainDateCount[8];               //잔존일수
	char adjustedStandardPrice[18];               //조정기준가격
	char standardPriceClassCode[2];               //기준가격구분코드
	char standardPriceClassCodeForTrade[1];               //매매용기준가격구분코드
	char ydayClosePriceAdjusted[18];               //전일조정종가
	char isConsultBulkTradeProduct[1];               //협의대량매매대상여부
	char ydayWarrentMoneyStandardPrice[23];               //전일증거금기준가격
	char ydayWarrentMoneyStandardPriceClassCode[2];               //증거금기준가격구분코드
	char theoreticalPriceSettlement[16];               //정산이론가격
	char theoreticalPriceStandard[16];               //기준이론가격
	char ydaySettlementPrice[18];               //전일정산가격
	char isTradeStop[1];               //거래정지여부
	char upLimitPriceForOptionCircuitBreakers[11];               //선물CIRCUIT_BREAKERS상한가
	char downLimitPriceForOptionCircuitBreakers[11];               //선물CIRCUIT_BREAKERS하한가
	char exercisePriceForIncuiry[18];               //조회용행사가격
	char ATMClassCode[1];               //ATM구분코드
	char isLastTradeDate[1];               //최종거래일여부
	char divValueForSettlementPrice[16];               //배당락후배당가치
	char ydayClosePrice[11];               //전일종가
	char ydayClosePriceClassCode[1];               //전일종가구분코드
	char ydayOpenPrice[11];               //이전일자시가
	char ydayHighPrice[11];               //이전일자고가
	char ydayLowPrice[11];               //이전일자저가
	char firstTradeDate[8];               //최초거래일자
	char ydayLastTradeTime[9];               //최종체결시각
	char ydaySettlementPriceClassCode[2];               //정산가격구분코드
	char exactTheoryPriceSeparationRate[13];               //정산가격이론가격괴리율
	char ydayOpenInterest[12];               //전일미결제약정수량
	char ydayAskPriceQuotePriority1[11];               //전일매도우선호가가격
	char ydayBidPriceQuotePriority1[11];               //전일매수우선호가가격
	char intrinsicVolatility[11];               //내재변동성
	char highestPriceWithinListing[11];               //상장중최고가
	char lowestPriceWithinListing[11];               //상장중최저가
	char highestPriceWithinYear[11];               //연중최고가
	char lowestPriceWithinYear[11];               //연중최저가
	char highestPriceDateWithinListing[8];               //상장중최고가일자
	char lowestPriceDateWithinListing[8];               //상장중최저가일자
	char highestPriceDateWithinYear[8];               //연중최고가일자
	char lowestPriceDateWithinYear[8];               //연중최저가일자
	char standardDayCountYear[8];               //연간기준일수
	char standardTradeDayCountMonth[8];               //월간거래일수
	char standardTradeDayCountYear[8];               //연간거래일수
	char ydayTradeCount[15];               //전일체결건수
	char ydayTradeVolume[12];               //전일누적거래량
	char ydayTradeAmount[22];               //전일누적거래대금
	char ydayConsultBulkTradeVolume[15];               //전일총누적거래량
	char ydayConsultBulkTradeAmount[22];               //전일총누적거래대금
	char cdRate[11];               //CD금리
	char unsettledLimitContractCount[15];               //주식선물미결제한도수량
	char productGroup[4];               //기초자산상품군ID
	char productGroupOffsetRate[11];               //증거금OFFSET비율
	char limitPriceQuoteConditionClassCode[5];               //지정가호가취소조건코드
	char marketPriceQuotePriceConditionClassCode[5];               //시장가호가취소조건코드
	char conditionalLimitPriceQuotePriceConditionClassCode[5];               //조건부지정가호가취소조건코드
	char advantageousLimitPriceQuotePriceConditionClassCode[5];               //최유리지정가호가취소조건코드
	char EFPTradingItem[1];               //EFP거래대상여부
	char FLEXTradingItem[1];               //FLEX거래대상여부
	char previousDayEFPTradingVolume[12];               //EFP체결수량
	char previousDayEFPTradingPrice[22];               //EFP거래대금
	char isHoliday[1];               //휴장여부
	char isRealTimePriceLimit[1];               //동적가격제한여부
	char realTimeUpperLimitPriceRange[11];               //동적상한가간격
	char realTimeLowerLimitPriceRange[11];               //동적하한가간격
	char underlyingAssetMarketID[3];               //기초자산시장ID
	char upperLimitQuantity[23];               //상한수량
	char lowerLimitQuantity[23];               //하한수량
	char upperLimitQuantityForBlockTrade[23];               //협의대량매매상한수량
	char lowerLimitQuantityForBlockTrade[23];               //협의대량매매하한수량
	char standardProductID[11];            //기준상품ID
	char subProductID[11];                 //부상품ID  
	char standardProductStockCount[6];     //부상품ID
	char subProductStockCount[6];          //부상품종목수
	char tradeDefineWeek[2];               //결제주
	char isSuspendedStocks[1];               //휴면여부
	char designationDateForSuspendedStocks[8];               //휴면지정일자
	char endOfText[1];               //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INFO_RECORD_SIZE = sizeof(ExturePlusKospi200OptionStockInfoRecord);
#endif

#if(1)
//파생 체결//F1보드 : 누적거래량만 공개 (가격, 거래대금 등 제외)//(A301F)
//파생 체결//파생 체결
//F1보드 : 누적거래량만 공개 (가격, 거래대금 등 제외)
//(파생A) DRV : A301F, A303F
class ExturePlusKospi200OptionTradeRecord
{
    public:
	char dataClass[2];            //데이터구분값
	char infoMarketClass[3];            //정보구분값
	char distributeStockIndex[8];            //정보분배일련번호
	char boardID[2];            //보드ID
	char sessionID[2];            //세션ID
	char stockCode[12];            //종목코드
	char stockSeq[6];            //정보분배종목인덱스
	char tradeTime[12];            //매매처리시각
	char currentPrice[9];            //체결가격
	char tradeVolume[9];            //거래량
	char ndmInterestPrice[9];            //근월물체결가격
	char fdmInterestPrice[9];            //원월물체결가격
	char openPrice[9];            //시가
	char highPrice[9];            //고가
	char lowPrice[9];            //저가
	char lastPrice[9];            //직전가격
	char accmTradeVolume[12];            //누적거래량
	char accmTradeAmount[22];            //누적거래대금
	char lastQuoteTypeAskBid[1];            //최종매도매수구분코드
	char realTimeUpperLimitPrice[9];            //동적상한가
	char realTimeLowerLimitPrice[9];            //동적하한가
	char endOfText[1];            //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_TRADE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionTradeRecord);
#endif

#if(1)
//KOSPI200지수선물시세Recovery 데이터//파생 시세 Snapshot(우선호가 5단계)
//파생 시세 Snapshot (우선호가 5단계)
//파생 시세 Snapshot (우선호가 5단계)
//(파생A) DRV : B201F, B203F
class ExturePlusKospi200OptionRecoveryQuoteRecord
{
    public:
	char askPrice[9];             //매도 우선호가가격
	char bidPrice[9];             //매수 우선호가가격
	char askVolume[9];            //매도 우선호가잔량
	char bidVolume[9];            //매수 우선호가잔량
	char askCount[5];             //매도 우선호가주문건수
	char bidCount[5];             //매수 우선호가주문건수
};
const int EXTURE_PLUS_KOSPI_200_OPTION_RECOVERY_QUOTE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionRecoveryQuoteRecord);

class ExturePlusKospi200OptionRecoveryRecord
{
    public:
	char dataClass[2];           //데이터구분값
	char infoMarketClass[3];           //정보구분값
	char boardID[2];           //보드ID
	char sessionID[2];           //세션ID
	char stockCode[12];           //종목코드
	char stockSeq[6];           //정보분배종목인덱스
	char realTimeUpperLimitPrice[9];           //상한가
	char realTimeLowerLimitPrice[9];           //하한가
	char currentPrice[9];           //체결가격
	char ndmInterestPrice[9];           //근월물체결가격
	char fdmInterestPrice[9];           //원월물체결가격
	char openPrice[9];           //시가
	char highPrice[9];           //고가
	char lowPrice[9];           //저가
	char openInterestVolume[10];           //미결제약정수량
	char accmTradeVolume[12];           //누적거래량
	char accmTradeAmount[22];           //누적거래대금
	char lastQuoteTypeAskBid[1];           //최종매도매수구분코드
	ExturePlusKospi200OptionRecoveryQuoteRecord quoteRecord[5];
	char askTotalVolume[9];            //매도호가총잔량
	char bidTotalVolume[9];            //매수호가총잔량
	char askCountValidQuote[5];            //매도호가유효건수
	char bidCountValidQuote[5];            //매수호가유효건수
	char estimatedTradingPrice[9];            //예상체결가
	char endOfText[1];            //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_RECOVERY_RECORD_SIZE = sizeof(ExturePlusKospi200OptionRecoveryRecord);
#endif

#if(1)
//KOSPI200지수선물 우선호가//파생 우선호가 (우선호가 5단계)(B601F)
//파생 우선호가 (우선호가 5단계)//파생 우선호가 (우선호가 5단계)
//(파생A) DRV : B601F, B603F
class ExturePlusKospi200OptionPriorityQuoteRecord
{
    public:
	char dataClass[2];        //데이터구분값
	char infoMarketClass[3];        //정보구분값
	char distributeStockIndex[8];        //정보분배일련번호
	char boardID[2];        //보드ID
	char sessionID[2];        //세션ID
	char stockCode[12];        //종목코드
	char stockSeq[6];        //정보분배종목인덱스
	char quoteAcceptTime[12];        //매매처리시각
	char askPricePriority1[9];        //매도1단계우선호가가격
	char bidPricePriority1[9];        //매수1단계우선호가가격
	char askVolumePriority1[9];        //매도1단계우선호가잔량
	char bidVolumePriority1[9];        //매수1단계우선호가잔량
	char askCountQuotePriority1[5];        //매도1단계우선호가주문건수
	char bidCountQuotePriority1[5];        //매수1단계우선호가주문건수
	char askPricePriority2[9];        //매도2단계우선호가가격
	char bidPricePriority2[9];        //매수2단계우선호가가격
	char askVolumePriority2[9];        //매도2단계우선호가잔량
	char bidVolumePriority2[9];        //매수2단계우선호가잔량
	char askCountQuotePriority2[5];        //매도2단계우선호가주문건수
	char bidCountQuotePriority2[5];        //매수2단계우선호가주문건수
	char askPricePriority3[9];        //매도3단계우선호가가격
	char bidPricePriority3[9];        //매수3단계우선호가가격
	char askVolumePriority3[9];        //매도3단계우선호가잔량
	char bidVolumePriority3[9];        //매수3단계우선호가잔량
	char askCountQuotePriority3[5];        //매도3단계우선호가주문건수
	char bidCountQuotePriority3[5];        //매수3단계우선호가주문건수
	char askPricePriority4[9];        //매도4단계우선호가가격
	char bidPricePriority4[9];        //매수4단계우선호가가격
	char askVolumePriority4[9];        //매도4단계우선호가잔량
	char bidVolumePriority4[9];        //매수4단계우선호가잔량
	char askCountQuotePriority4[5];        //매도4단계우선호가주문건수
	char bidCountQuotePriority4[5];        //매수4단계우선호가주문건수
	char askPricePriority5[9];        //매도5단계우선호가가격
	char bidPricePriority5[9];        //매수5단계우선호가가격
	char askVolumePriority5[9];        //매도5단계우선호가잔량
	char bidVolumePriority5[9];        //매수5단계우선호가잔량
	char askCountQuotePriority5[5];        //매도5단계우선호가주문건수
	char bidCountQuotePriority5[5];        //매수5단계우선호가주문건수
	char askTotalQuoteVolume[9];        //매도호가총잔량
	char bidTotalQuoteVolume[9];        //매수호가총잔량
	char askCountValidQuote[5];        //매도호가유효건수
	char bidCountValidQuote[5];        //매수호가유효건수
	char estimatedTradingPrice[9];        //예상체결가
	char endOfText[1];        //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_PRIORITY_QUOTE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionPriorityQuoteRecord);
#endif

#if(1)
//KOSPI200지수선물 체결_우선호가	G7014
//파생 체결 + 우선호가 (우선호가 5단계)
//파생 체결 + 우선호가(우선호가 5단계)
//(파생A) DRV : G701F, G703F
class ExturePlusKospi200OptionTradePriorityQuoteRecord
{
    public:
	char dataClass[2];            //데이터구분값
	char infoMarketClass[3];            //정보구분값
	char distributeStockIndex[8];            //정보분배일련번호
	char boardID[2];            //보드ID
	char sessionID[2];            //세션ID
	char stockCode[12];            //종목코드
	char stockSeq[6];            //정보분배종목인덱스
	char tradeTime[12];            //매매처리시각
	char currentPrice[9];            //체결가격
	char tradeVolume[9];            //거래량
	char ndmInterestPrice[9];            //근월물체결가격
	char fdmInterestPrice[9];            //원월물체결가격
	char openPrice[9];            //시가
	char highPrice[9];            //고가
	char lowPrice[9];            //저가
	char lastPrice[9];            //직전가격
	char accmTradeVolume[12];            //누적거래량
	char accmTradeAmount[22];            //누적거래대금
	char lastQuoteTypeAskBid[1];            //최종매도매수구분코드
	char realTimeUpperLimitPrice[9];            //동적상한가
	char realTimeLowerLimitPrice[9];            //동적하한가
	char askPricePriority1[9];            //매도1단계우선호가가격
	char bidPricePriority1[9];            //매수1단계우선호가가격
	char askVolumePriority1[9];            //매도1단계우선호가잔량
	char bidVolumePriority1[9];            //매수1단계우선호가잔량
	char askCountQuotePriority1[5];            //매도1단계우선호가주문건수
	char bidCountQuotePriority1[5];            //매수1단계우선호가주문건수
	char askPricePriority2[9];            //매도2단계우선호가가격
	char bidPricePriority2[9];            //매수2단계우선호가가격
	char askVolumePriority2[9];            //매도2단계우선호가잔량
	char bidVolumePriority2[9];            //매수2단계우선호가잔량
	char askCountQuotePriority2[5];            //매도2단계우선호가주문건수
	char bidCountQuotePriority2[5];            //매수2단계우선호가주문건수
	char askPricePriority3[9];            //매도3단계우선호가가격
	char bidPricePriority3[9];            //매수3단계우선호가가격
	char askVolumePriority3[9];            //매도3단계우선호가잔량
	char bidVolumePriority3[9];            //매수3단계우선호가잔량
	char askCountQuotePriority3[5];            //매도3단계우선호가주문건수
	char bidCountQuotePriority3[5];            //매수3단계우선호가주문건수
	char askPricePriority4[9];            //매도4단계우선호가가격
	char bidPricePriority4[9];            //매수4단계우선호가가격
	char askVolumePriority4[9];            //매도4단계우선호가잔량
	char bidVolumePriority4[9];            //매수4단계우선호가잔량
	char askCountQuotePriority4[5];            //매도4단계우선호가주문건수
	char bidCountQuotePriority4[5];            //매수4단계우선호가주문건수
	char askPricePriority5[9];            //매도5단계우선호가가격
	char bidPricePriority5[9];            //매수5단계우선호가가격
	char askVolumePriority5[9];            //매도5단계우선호가잔량
	char bidVolumePriority5[9];            //매수5단계우선호가잔량
	char askCountQuotePriority5[5];            //매도5단계우선호가주문건수
	char bidCountQuotePriority5[5];            //매수5단계우선호가주문건수
	char askTotalQuoteVolume[9];            //매도호가총잔량
	char bidTotalQuoteVolume[9];            //매수호가총잔량
	char askCountValidQuote[5];            //매도호가유효건수
	char bidCountValidQuote[5];            //매수호가유효건수
	char endOfText[1];            //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_TRADE_PRIORITY_QUOTE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionTradePriorityQuoteRecord);
#endif

#if(1)
//KOSPI200지수선물 투자자 데이터//파생 상품별 투자자별 통계
//파생 상품별 투자자별 통계//파생 상품별 투자자별 통계
//(장중 공개 보드만 포함)
//(파생A) DRV : H101F, H103F
class ExturePlusKospi200OptionInvestorRecord
{
    public:
	char dataClass[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char createDate[8];                       //생성일자
	char createTime[6];                       //통계산출시각
	char dataType[2];                       //투자자거래현황송신데이터구분코드
	char productId[11];                       //상품ID
	char optionClass[1];                            //옵션구분
	char investorType[4];                       //투자자구분코드
	char bidAgreementVolume[10];                       //매수거래량
	char askAgreementVolume[10];                       //매도거래량
	char bidAgreementAmount[22];                       //매수거래대금
	char askAgreementAmount[22];                       //매도거래대금
	char bidAgreementVolumeBySpread[10];                       //스프레드매수거래량
	char askAgreementVolumeBySpread[10];                       //스프레드매도거래량
	char bidAgreementAmountBySpread[22];                       //스프레드매수거래대금
	char askAgreementAmountBySpread[22];                       //스프레드매도거래대금
	char endOfText[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_INVESTOR_RECORD_SIZE = sizeof(ExturePlusKospi200OptionInvestorRecord);
#endif

#if(1)
//KOSPI200지수선물 미결제약정수량 데이터//파생종목 미결제약정수량 데이터
//파생종목 미결제약정수량 데이터
//파생종목 미결제약정수량 데이터
//전일확정치 : 장개시전
//장중 : 10초주기
//당일확정치 : 장종료후
//(파생A) DRV : H201F, H203F
class ExturePlusKospi200OptionOpenInterestVolumeRecord
{
    public:
	char dataClass[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char stockCode[12];                       //종목코드
	char stockSeq[6];                       //정보분배종목인덱스
	char openInterestClass[2];                       //미결제약정송신데이터구분코드
	char tradeDate[8];                       //거래일자
	char openInterestVolume[10];                       //미결제약정수량
	char endOfText[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_OPEN_INTEREST_VOLUME_RECORD_SIZE = sizeof(ExturePlusKospi200OptionOpenInterestVolumeRecord);
#endif

#if(1)
//KOSPI200지수선물 정산가격 데이터//선물종목 정산가격 데이터
//선물종목 정산가격 데이터	선물종목
//정산가격 데이터	
//장종료후
//(파생A) DRV : H301F, H304F
class ExturePlusKospi200OptionAdjustedPriceRecord
{
    public:
	char dataClass[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char stockCode[12];                       //종목코드
	char stockSeq[6];                       //정보분배종목인덱스
	char adjustedPrice[18];                       //정산가격
	char adjustedPriceClass[2];                       //정산가격구분코드
	char lastSettlementPrice[18];                       //최종결제가격
	char lastSettlementPriceClass[1];                       //최종결제가격구분코드
	char endOfText[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_ADJUSTED_PRICE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionAdjustedPriceRecord);
#endif

#if(1)
//옵션종목 매매증거금 기준가 데이터
//옵션종목 매매증거금 기준가 데이터
//장종료후
//(파생A) DRV : ID03F, ID05F, ID07F, ID12F, ID15F, ID16F
class ExturePlusKospi200OptionTradeMarginStandardPriceRecord
{
    public:

        char dataClass[2];                              //1 	데이터구분값	0	String	2                  
        char infoMarketClass[3];                        //2 	정보구분값	0	String	3                      
        char stockCode[12];                             //3 	종목코드	0	String	12                     
        char stockSeq[4];                               //4 	정보분배종목인덱스	0	Int	6                  
        char marginStdPrice[18];                        //5 	증거금기준가격	8	FLOAT128	18             
        char marginStdPriceClass[2];                    //6 	증거금기준가격구분코드	0	String	2          
        char optionExercisePrice[18];                   //7 	옵션권리행사결제가격	8	FLOAT128	18     
        char optionExercisePriceClass[1];               //8 	옵션권리행사결제가격구분코드	0	String	1  
        char endOfText[1];                              //9 	정보분배메세지종료키워드	0	String	1      
};
const int EXTURE_PLUS_KOSPI_200_OPTION_TRADE_MARGIN_STANDARD_PRICE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionTradeMarginStandardPriceRecord);
#endif

#if(1)
//KOSPI200지수선물 장운영스케줄공개//장운영스케줄공개
//장운영스케줄공개//장운영스케줄 이벤트 공개 발생시 제공
//실시간
//(증권A) STK : M401S
//(증권C) STK : M402S, M403S, M404S
//(증권B) KSQ : M401Q
//(증권B) KNX : M401X
//(채권A) BND : M401B
//(채권A) SMB : M401M
//(채권A) KTS : M401K
//(채권A) RPO : M401R
//(파생A) DRV : M401F, M403F
class ExturePlusKospi200OptionMarketOperationScheduleDisclosureRecord
{
    public:
	char data_type[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char market_operation_product_group_id[3];                       //장운영상품그룹ID
	char board_id[2];                       //보드ID
	char board_event_id[3];                       //보드이벤트ID
	char board_event_start_time[9];                       //보드이벤트시작시각
	char board_event_group_code[5];                       //보드이벤트적용군코드
	char session_start_end_code[2];                       //세션개시종료코드
	char session_id[2];                       //세션ID
	char issue_code[12];                       //종목코드
	char listedCompanyStockCode [12];                       //상장사종목코드
	char derivatives_id[11];                       //상품ID
	char uspensionTransactionReasonCode [3];                       //거래정지사유코드
	char uspensionTransactionOccurCode [1];                       //거래정지발생유형코드
	char step_applied[2];                       //적용단계
	char price_expansion_trigger_code_for_base_issue[1];                       //기준종목가격제한확대발생코드
	char price_expansion_expected_time[9];                       //가격제한확대예정시각
	char end_of_text[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_SCHEDULE_DISCLOSURE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionMarketOperationScheduleDisclosureRecord);
#endif

#if(1)
//KOSPI200지수선물 배분정보	KOSPI200지수선물 배분정보//배분정보
//배분정보
//단일가체결이 상/하한가로 결정되는 경우 상/하한가 매수, 매도주문에 대해 일정량의 수량을 순차적으로 배분하여 체결시키는 경우
//실시간
//(증권A) STK : O601S
//(증권C) STK : O602S, O603S, O604S
//(증권B) KSQ : O601Q
//(증권B) KNX : O601X
//(파생A) DRV : O601F, O603F
class ExturePlusKospi200OptionQuantityAllocationRecord
{
    public:
	char dataType[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char distributeStockIndex[8];                       //정보분배일련번호
	char boardID[2];                       //보드ID
	char issueCode[12];                       //종목코드
	char issueSeqence[6];                       //정보분배종목인덱스
	char allocationStartEnd[1];                       //배분적용구분코드
	char allocationTypeCode[1];                       //배분처리구분코드
	char timeForAllocationEnd[9];                       //배분해제시각
	char endOfText[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_QUANTITY_ALLOCATION_RECORD_SIZE = sizeof(ExturePlusKospi200OptionQuantityAllocationRecord);
#endif

#if(1)
//K200선물_실시간상하한가 적용및해제//파생 동적상하한가 적용 및 해제(Q201F)
//파생 동적상하한가 적용 및 해제
//파생 동적상하한가 적용 및 해제
//실시간
//(파생A) DRV : Q201F, Q203F
class ExturePlusKospi200OptionRealTimeUpperLowerLimitPriceRecord
{
    public:
	char dataType[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char distributeStockIndex[8];                       //정보분배일련번호
	char boardID[2];                       //보드ID
	char issueCode[12];                       //종목코드
	char issueSeqence[6];                       //정보분배종목인덱스
	char processingTime[12];                       //매매처리시각
	char realTimePriceLimit[1];                       //동적가격제한설정코드
	char realTimeUpperLimitPrice[9];                       //동적상한가
	char realTimeLowerLimitPrice[9];                       //동적하한가
	char endOfText[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_REAL_TIME_UPPER_LOWER_LIMIT_PRICE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionRealTimeUpperLowerLimitPriceRecord);
#endif

#if(1)
//K200선물_가격제한폭확대발동//파생 가격제한폭확대발동
//파생 가격제한폭확대발동//가격제한폭확대 발동시 제공
//(파생A) DRV : V101F, V103F
class ExturePlusKospi200OptionPriceLimitRangeExpansionTriggerRecord
{
    public:
	char data_type[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char distributeStockIndex[8];                       //정보분배일련번호
	char board_id[2];                       //보드ID
	char issue_code[12];                       //종목코드
	char issue_seq[6];                       //정보분배종목인덱스
	char price_expansion_time[9];                       //가격확대시각
	char the_upper_step_of_price_limit_expansion[2];                       //가격제한확대상한단계
	char the_lower_step_of_price_limit_expansion[2];                       //가격제한확대하한단계
	char upper_limit_price[9];                       //상한가
	char lower_limit_price[9];                       //하한가
	char end_of_text[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI200_OPTION_PRICE_LIMIT_RANGE_EXPANSION_TRIGGER_RECORD_SIZE = sizeof(ExturePlusKospi200OptionPriceLimitRangeExpansionTriggerRecord);
#endif

#if(1)
// (파생A) DRV : A601F, A602F, A603F, A604F, A605F, A606F, A607F, A608F, A609F, A610F, A611F, A612F, A613F, A615F, A616F
// 파생 종목마감
class ExturePlusKospi200OptionStockCloseRecord
{
    public:
        char dataClass[2];                              // 데이터구분값
        char infoMarketClass[3];                        // 정보구분값
		char distributeStockIndex[8];                   // 정보분배일련번호
		char boardID[2];                                // 보드ID
        char stockCode[12];                             // 종목코드		
		char stockSeq[6];					// 정보분배종목인덱스
		char closePrice[9];                             // 종목마감종가
		char closePriceTypeCode[1];                     // 종가구분코드
        char accmTradeVolume[12];                       // 누적거래량
        char accmTradeAmount[22];                       // 누적거래대금
		char endOfText[1];                              // 정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_STOCK_CLOSE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionStockCloseRecord);
#endif

#if(1)
//옵션종목 민감도 데이터
//옵션종목 민감도 데이터
//장중 : 10초주기
//(파생A) DRV : N703F, N705F, N707F, N712F, N715F, N716F
class ExturePlusKospi200OptionSensitivityRecord
{
	public:
	char  dataType[2];                        //데이터구분값
	char  infoMarketClass[3];                        //정보구분값
	char  issueCode[12];                        //종목코드
	char  seq[6];                        //정보분배종목인덱스
	char  producedDate[8];                        //산출일자
	char  producedTime[9];                        //산출시각
	char  dataCategory[1];                        //내재변동성산출구분코드
	char  underlyingAssetId[3];                        //기초자산ID
	char  sensitivityDelta[20];                        //민감도델타
	char  sensitivityTheta[20];                        //민감도쎄타
	char  sensitivityVega[20];                        //민감도베가
	char  sensitivityGamma[20];                        //민감도감마
	char  sensitivityRho[20];                        //민감도로
	char  endOfText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_SENSITIVITY_RECORD_SIZE = sizeof(ExturePlusKospi200OptionSensitivityRecord);
#endif

#if(1)
//K200선물_장개시전협의거래//Eurex연계 장개시전 협의거래
//Eurex연계 장개시전 협의거래
//Eurex연계 장개시전 협의거래
//09:00 1회	
//(파생A) DRV : M701F, M703F
class ExturePlusKospi200OptionPreMarketNegotiatedTradeRecord
{
    public:
	char data_type[2];                       //데이터구분값
	char infoMarketClass[3];                       //정보구분값
	char stockCode[12];                       //종목코드
	char stockSeq[6];                       //정보분배종목인덱스
	char tradePrice[9];                       //체결가격
	char tradeVolume[9];                       //거래량
	char end_of_text[1];                       //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_PRE_MARKET_NEGOTIATED_TRADE_RECORD_SIZE = sizeof(ExturePlusKospi200OptionPreMarketNegotiatedTradeRecord);
#endif

#if(1)
//장운영TS
//장운영 Trading Session 이벤트 발생시 종목별 제공
//실시간
//(증권A) STK : A701S
//(증권C) STK : A702S, A703S, A704S
//(증권B) KSQ : A701Q
//(증권B) KNX : A701X
//(파생A) DRV : A701F, A703F
class ExturePlusKospi200OptionMarketOperationRecord
{
    public:
	char dataCategory[2];                           //데이터구분값
	char infoMarketClass[3];                        //정보구분값
	char distributeStockIndex[8];                   //정보분배일련번호
	char boardID[2];                                //보드ID
	char sessionID[2];                              //세션ID
	char stockCode[12];                             //종목코드
	char stockSeq[6];                               //정보분배종목인덱스
	char tradeProcessTime[12];                      //매매처리시각
	char boardEventID[3];                           //보드이벤트ID
	char boardEventBeginTime[9];                    //보드이벤트시작시각
	char boardEventApplyCode[5];                    //보드이벤트적용군코드
	char tradingHaltReasonCode[3];                  //거래정지사유코드
	char endOfText[1];                              //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSPI_200_OPTION_MARKET_OPERATION_RECORD_SIZE = sizeof(ExturePlusKospi200OptionMarketOperationRecord);
#endif

#pragma pack()

#endif // __EXTURE_PLUS_KOSPI_200_OPTION_H__
