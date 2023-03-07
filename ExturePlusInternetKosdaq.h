#ifndef __EXTURE_PLUS_KOSDAQ_H__
#define __EXTURE_PLUS_KOSDAQ_H__

/*
 12345678901234567890123456789012345678901234567890123456789012345678901234567890
 */

#pragma pack(1)

#if(1)
//증권 종목정보
//(증권A) STK : A001S
//(증권C) STK :  A002S, A003S, A004S
//(증권B) KSQ : A001Q
//(증권B) KNX : A001X
//(주식파생) STK : A001S
//(주식파생) KSQ : A001Q
class ExturePlusKosdaqMaster
{
    public:
	char dataClass[2];                  //정보분배 데이터를 식별하는 구분 코드값
	char infoMarketClass[3];            //정보분배에서 분배하는 정보의 구분 코드값
	char distributeStockIndex[8];		//정보분배에서 부여하는 일련번호
										//시세 : 종목별 보드별 부여 (※ 대용량 서비스에서 제공)
										//종목정보 :  정보구분값별 부여
										//기타 : 데이터구분값별 부여
	char distributeTotalStockIndex[6];         //정보분배총종목인덱스
	char sendDate[8];         //영업일자
	char stockCode[12];         //종목코드
	char stockSeq[6];         //정보분배종목인덱스
	char abbrStockCode[9];         //종목단축코드
	char abbrStockNameKor[40];         //종목약명
	char abbrStockNameEng[40];         //종목영문약명
	char infoDivisionGroupNo[5];         //정보분배그룹번호
	char MarketProductGroupID[3];         //장운영상품그룹ID
	char stockGroupID[2];         //증권그룹ID
	char isUnitTrade[1];         //단위매매체결여부
	char exClassCode[2];         //락구분코드
	char faceValueChangeClassCode[2];         //액면가변경구분코드
	char isOpenPriceBecomeStdPrice[1];         //시가기준가격종목여부
	char isRevaluationStockReason[2];         //재평가종목사유코드
	char isStandardPriceChangeStock[1];         //기준가격변경종목여부
	char randomEndTriggerConditionCode[1];         //임의종료발동조건코드
	char isMarketAlarmDangerNotice[1];         //시장경보위험예고여부
	char marketAlarmClassCode[2];         //시장경보구분코드
	char isCorporateGovernanceFine[1];         //지배구조우량여부
	char isManagementStock[1];         //관리종목여부
	char isInsincerityPublicNewsAppoint[1];         //불성실공시여부
	char isBackDoorListing[1];         //우회상장여부
	char isTradeStop[1];         //거래정지여부
	char standardIndustryCode[10];         //업종ID
	char SmallMediumEnterprisesIs[1];         //중소기업여부
	char isCorporateGovernanceIndexStock[1];         //소속부구분코드
	char investOrganClassCode[1];         //투자기구구분코드
	char standardPrice[11];         //기준가격
	char ydayClosePriceClassCode[1];         //전일종가구분코드
	char ydayClosePrice[11];         //전일종가
	char ydayAccmVolume[12];         //전일누적거래량
	char ydayAccmAmount[22];         //전일누적거래대금
	char upLimitPrice[11];         //상한가
	char downLimitPrice[11];         //하한가
	char substitutePrice[11];         //대용가격
	char faceValue[11];         //액면가
	char issuePrice[11];         //발행가격
	char listingDate[8];         //상장일자
	char listingSize[16];         //상장주식수
	char isClearanceTrade[1];         //정리매매여부
	char listingStartDate[8];         //존립개시일자
	char listingEndDAte[8];         //존립종료일자
	char excercisePeriodBeginDate[8];         //행사기간개시일자
	char excercisePeriodEndDate[8];         //권리행사기간만료일자
	char ELWBWExcercisePrice[13];         //ELW신주인수권증권행사가격
	char capital[22];         //자본금
	char CreditOrderPossibleIs[1];         //신용주문가능여부
	char LimitQuotePriceConditionClassCode[5];         //지정가호가취소조건코드
	char MarketQuotePriceConditionClassCode[5];         //시장가호가취소조건코드
	char ConditionalLimitQuotePriceConditionClassCode[5];         //조건부지정가호가취소조건코드
	char BestLimitQuotePriceConditionClassCode[5];         //최유리지정가호가취소조건코드
	char topPriorityQuotePriceConditionClassCode[5];         //최우선지정가호가취소조건코드
	char capitalIncreaseClassCode[2];         //증자구분코드
	char preferredStockClassCode[1];         //종류주권구분코드
	char isNationalStock[1];         //국민주여부
	char evaluatePrice[11];         //평가가격
	char lowestQuotePrice[11];         //최저호가가격
	char highestQuotePrice[11];         //최고호가가격
	char MainBaordVolumeUnit[11];         //메인보드수량단위
	char JangAfterOvertimeVolumeUnit[11];         //장종료후시간외수량단위
	char REITsClassCode[1];         //리츠종류코드
	char objectSovereign[12];         //목적주권종목코드
	char CurrencyISOCode[3];         //통화ISO코드
	char NationalCode[3];         //국가코드
	char BelfastPossibleIs[1];         //시장조성가능여부
	char OvertimeTradePossibleIs[1];         //시간외매매가능여부
	char isBeforeMarketOvertimeMarketClosePrice[1];         //장개시전시간외종가가능여부
	char isBeforeMarketOvertimeMarketBlockTradingPossibility[1];         //장개시전시간외대량매매가능여부
	char isBeforeMarketOvertimeMarketBasketPossibility[1];         //장개시전시간외바스켓가능여부
	char isEstimatedTradePriceOpen[1];         //예상체결가공개여부
	char isShortStockSellingPossibility[1];         //공매도가능여부
	char ETFFollowingEarningRateMultiple[13];         //추적수익률배수
	char REGSIS[1];         //REGS여부
	char SPACIS[1];         //SPAC여부
	char taxImportedTypeCode[1];         //과세유형코드
	char rateSubstitutePriceCalcurated[13];         //대용가격사정비율
	char isStockInvestmentWarningAttention[1];         //투자주의환기종목여부
	char delistingDate[8];         //상장폐지일자
	char shortTermFeverishInstrumentTypeCode[1];         //단기과열종목구분코드
	char ETFReplicationMethodTypeCode[1];         //ETF복제방법구분코드
	char expirationDate[8];         //만기일자
	char distributeTypeCode[2];         //분배금형태코드
	char expirationRedemptionPriceDecisionStartDate[8];         //만기상환가격결정시작일자
	char expirationRedemptionPriceDecisionEndDate[8];         //만기상환가격결정종료일자
	char etpProductTypeCode[1];         //ETP상품구분코드
	char indexCalculationInstitution_code[2];         //지수산출기관코드
	char indexMarket_classification_id[6];         //지수시장분류ID
	char indexSeqNumber[3];         //지수일련번호
	char trackingIndexLeverageInverseTypeCode[2];         //추적지수레버리지인버스구분코드
	char referenceIndexLeverageInverseTypeCode[2];         //참고지수레버리지인버스구분코드
	char indexAssetClassificationId1[6];         //지수자산분류ID1
	char indexAssetClassificationId2[6];         //지수자산분류ID2
	char RecommendTestimonialNo[5];         //상장주선사회원번호
	char lpOrderPossibility[1];         //LP주문가능여부
	char lowLiquidity[1];         //저유동성여부
	char abnormalRise[1];         //이상급등여부
	char upperLimitQuantity[23];         //상한수량
	char isInvestmentPrecautionIssue[1];         //투자유의종목여부
	char TradingVolumeInsufficientIs[1];         //상장주식수부족종목여부
	char isSPAC_merger[1];         //SPAC소멸합병여부
	char segment_code[1];         //세그먼트구분코드
	char endOfText[1];         //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_MASTER_SIZE = sizeof(ExturePlusKosdaqMaster);

//증권 지수 및 투자지표
//(증권A) STK : CA01S
//(증권B) KSQ : CA01Q
//(주식파생) STK : CA01S
//(주식파생) KSQ : CA01Q
class ExturePlusKosdaqJisuMaster
{
    public:
	char dataClass[2];                  //정보분배 데이터를 식별하는 구분 코드값
	char infoMarketClass[3];            //정보분배에서 분배하는 정보의 구분 코드값
	char distributeStockIndex[8];		//정보분배에서 부여하는 일련번호
										//시세 : 종목별 보드별 부여 (※ 대용량 서비스에서 제공)
										//종목정보 :  정보구분값별 부여
										//기타 : 데이터구분값별 부여
	char stockCode[12];         //종목코드
	char stockSeq[6];         //일련번호
	char stockGroupID[2];         //증권그룹ID
	char isEPSCalcExclusion[1];         //주당순이익산출제외여부
	char EPS[22];         //주당순이익
	char isloss[1];         //결손여부
	char PER[13];         //주가수익율
	char isBPSCalcExclusion[1];         //주당순자산가치산출제외여부
	char BPS[22];         //주당순자산가치
	char PBR[13];         //주당순자산비율
	char isDividendPriceExclusion[1];         //주당배당금산출제외여부
	char dividendPrice[22];         //주당배당금액
	char dividendEarningRate[13];         //배당수익율
	char listPriceSizeCode[1];         //시가총액규모코드
	char isManufactureIndustry[1];         //제조업여부
	char indexBusinessTypeLarge[6];         //지수업종대분류코드
	char indexBusinessTypeMedium[6];         //지수업종중분류코드
	char indexBusinessTypeSmall[6];         //지수업종소분류코드
	char businessTypeKOSPI200[1];         //KOSPI200섹터업종
	char businessTypeKOSPI200_2[1];         //KOSPI200커뮤니케이션서비스섹터 중복여부
	char isKOSPI[1];         //KOSPI지수종목여부
	char investOrganClassCode[1];         //KOSDAQ지수종목여부
	char isKOSPI100[1];         //KOSPI100여부
	char isKOSPI50[1];         //KOSPI50여부
	char kosdaq150IndexIssue[1];         //KOSDAQ150지수종목여부
	char isKRX100Stock[1];         //KRX100종목여부
	char krx300[1];         //KRX300지수여부
	char KOSPI200LowVolatilityHighDividendIndex[1];         //KOSPI200고배당지수여부
	char isKRX_BBIG_K_NewDealIndex[1];         //KRXBBIGK뉴딜지수여부
	char isKRX_secondaryBattery_K_NewDealIndex[1];         //KRX2차전지K뉴딜지수여부
	char isKRX_bio_K_NewDealIndex[1];         //KRX바이오K뉴딜지수여부
	char filler[9];         //
	char endOfText[1];         //
};
const int EXTURE_PLUS_KOSDAQ_JISU_MASTER_SIZE = sizeof(ExturePlusKosdaqJisuMaster);
#endif

#if(1)
//코스피 종가 RECOVERY	B1011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//코스피 시세 RECOVERY	B2011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//코스피 시간외단일가 최종	B3011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//코스피 시간외단일가 RECOVERY	B4011→ 증권 Snapshot (MM/LP호가 제외) 로 통합
//증권 Snapshot (MM/LP호가 제외)	종목별 보드별 snapshot 및 최종상태를 일정간격으로 제공 (MM/LP호가 제외)	
//실시간[건당 0.2초/전종목 전송후 30초 sleep]
//주기변경 가능
//(증권A) STK : B201S
//(증권B) KSQ : B201Q
//(증권B) KNX : B201X
class ExturePlusKosdaqRecoveryTotalTradeRecord
{
	public:
	char askQuote[11];				// 매도n단계우선호가가격
	char bidQuote[11];				// 매수n단계우선호가가격
	char askQuoteVolume[12];		// 매도n단계우선호가잔량
	char bidQuoteVolume[12];		// 매수n단계우선호가잔량
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TOTAL_TRADE_RECORD_SIZE = sizeof(ExturePlusKosdaqRecoveryTotalTradeRecord);

class ExturePlusKosdaqRecoveryTotalTrade
{
	public:
	char dataClass[2];								// 데이터구분값 
	char infoMarketClass[3];						// 정보구분값 
	char boardID[2];								// 보드ID
	char sessionID[2];								// 세션ID
	char stockCode[12];								// 종목코드
	char stockSeq[6];								// 정보분배종목인덱스
	char upDown[1];             					// 전일대비구분코드
	char gap[11];							        // 전일대비가격
	char upLimitPrice[11];      					// 상한가
	char downLimitPrice[11];    					// 하한가 
	char closePrice[11];							// 현재가
    char openPrice[11];         					// 시가  
    char highPrice[11];         					// 고가  
    char lowPrice[11];          					// 저가  
    char accmTradeVolume[12];   					// 누적거래량   
    char accmTradeAmount[22];   					// 누적거래대금  
    char lastAskBidClassCode[1];					// 최종매도매수구분코드 
	ExturePlusKosdaqRecoveryTotalTradeRecord rec[10];  // 매도(수) n단계 우선호가 정보
	char totalRemainingAskPrice[12];     			// 매도호가공개단계잔량합계    
	char totalRemainingBidPrice[12];     			// 매수호가공개단계잔량합계 
	char estimatedTradePrice[11];   				// 예상체결가   
    char estimatedTradeVolume[12];  				// 예상체결수량
	char realRateQuotationClass[1];    				// 전일종가구분코드
													// 1:실세
													// 2:기세
													// 3:거래무
													// 4:시가기준가종목의 기세
	char isTradeStop[1];            				// 거래정지여부
    char endText[1];     							// 정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TOTAL_TRADE_SIZE = sizeof(ExturePlusKosdaqRecoveryTotalTrade);
#endif

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

#if(1)
//종목별투자자정보/배치/FTP
//종목별투자자정보/배치/FTP
class ExturePlusKosdaqInvestorStock
{
    public:
        char dataClass[2];            // 001 DATA구분 DT
        char infoClass[2];            // 002 정보구분 00
        char marketClass[1];          // 003 시장구분 0
        char exchange[2];             // 시장구분
        char date[8];                 // 일자
        char symbol[12];              // 종목코드
        char investor[4];             // 투자자구분
                                      // 1000:기관계 9000:외국인계
        char sellVolume[12];          // 매도거래량 // 단위:주
        char sellAmount[18];          // 매도거래대금 // 단위:원
        char buyVolume[12];           // 매수거래량 // 단위:주
        char buyAmount[18];           // 매수거래대금 // 단위:원
        char filler[14];              // FILLER 14
        char endOfText[1];
};
const int EXTURE_PLUS_KOSDAQ_INVESTOR_STOCK_SIZE = sizeof(ExturePlusKosdaqInvestorStock);
#endif

#if(1)
//장운영스케줄공개
//(증권A) STK : M401S
//(증권C) STK : M402S, M403S, M404S
//(증권B) KSQ : M401Q
//(증권B) KNX : M401X
//(채권A) BND : M401B
//(채권A) SMB : M401M
//(채권A) KTS : M401K
//(채권A) RPO : M401R
//(파생A) DRV : M401F, M402F, M403F, M404F, M405F, M406F, M407F, M408F, M409F, M410F, M411F, M412F, M413F, M415F, M416F
//(파생B) DRV : M414F
//(일반A) CMD : M401G
//(일반A) ETS : M401E
//장운영스케줄 이벤트 공개 발생시 제공
class ExturePlusKosdaqMarketOperationScheduleDisclosure
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char marketCategory[3];                                     //장운영상품그룹ID
	char boardID[2];                                     //보드ID
	char boardEventID[3];                                     //보드이벤트ID
	char boardEventBeginTime[9];                                     //보드이벤트시작시각
	char boardEventApplyCode[5];                                     //보드이벤트적용군코드
	char sessionBeginEndCode[2];                                     //세션개시종료코드
	char sessionID[2];                                     //세션ID
	char issueCode[12];                                     //종목코드
	char listedIssueCode[12];                                     //상장사종목코드
	char productID[11];                                     //상품ID
	char tradingHaltReasonCode[3];                                     //거래정지사유코드
	char tradingHaltOccurenceTypeCode[1];                                     //거래정지발생유형코드
	char stepApplied[2];                                     //적용단계
	char stepAppliedOccuredCode[1];                                     //기준종목가격제한확대발생코드
	char stepAppliedScheduleTime[9];                                     //가격제한확대예정시각
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_SCHEDULE_DISCLOSURE_SIZE = sizeof(ExturePlusKosdaqMarketOperationScheduleDisclosure);
#endif

#if(1)
//협의거래 결과(TO-BE)//코스피대량체결(C4011)(AS-IS)
//협의거래 결과//종목별 보드별 협의거래 공개(누적거래량만)
//장종료 후 2회	
//(증권A) STK : C401S
//(증권C) STK : C402S, C403S, C404S
//(증권B) KSQ : C401Q
//(증권B) KNX : C401X
class ExturePlusKosdaqTotalBulkTrade
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char boardID[2];                                     //보드ID
	char stockCode[12];                                     //종목코드
	char stockSeq[6];                                     //정보분배종목인덱스
	char accumlatedVolume[12];                                     //누적거래량
	char endText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_TOTAL_BULK_TRADE_SIZE = sizeof(ExturePlusKosdaqTotalBulkTrade);
#endif

#if(1)
//지수전문 통합
//IA000(정규장지수)
//IB000(예상지수)
class ExturePlusTotalKosdaqIndex
{
    public:
	char dataClass[2];              //데이터구분값
	char infoMarketClass[3];        //정보구분값
	char dataID[6];                 //지수ID
	char standardCode[12];          //표준코드
	char time[6];                   //지수산출시각
	char index[9];                  //지수
	char sign[1];                   //전일대비지수부호
	char gap[9];                    //전일대비지수
	char tradeVolume[12];           //누적거래량
	char tradeAmount[12];           //누적거래대금
	char filler[4];                 //필러값
	char endText[1];                //정보분배메세지종료키워드
};
const int EXTURE_PLUS_TOTAL_KOSDAQ_INDEX_SIZE = sizeof(ExturePlusTotalKosdaqIndex);

//14  KOSDAQ지수    변경없음    E4012   KOSDAQ지수    50  -   실시간
//15  KOSDAQ예상지수  변경없음    E5012   KOSDAQ예상지수  50  -   실시간
//16  KOSTAR지수    변경없음    E6012   KOSTAR지수    50  -   실시간
//17  KOSTAR예상지수  변경없음    E7012   KOSTAR예상지수  50  -   실시간
//18  "KOSDAQ프리미어지수" 변경없음    L2012   KOSDAQ프리미어지수    50  -   실시간
//19  "KOSDAQ프리미어예상지수"   변경없음    L3012   KOSDAQ프리미어예상지수  50  -   실시간
class ExturePlusKosdaqIndex
{
    public:
        char dataClass[2];                                            // 001 DATA구분
        char infoClass[2];                                            // 001 정보구분
        char marketClass[1];                                          // 001 시장구분
        char businessTypeCode[3];                                     // 002 업종코드
        char time[6];                                                 // 003 시간
        char index[9];                                                // 004 지수
        char sign[1];                                                 // 005 부호
        char gap[9];                                                  // 006 대비
        char tradeVolume[12];                                          // 007 체결수량
        char tradeAmount[12];                                          // 008 거래대금
};
const int EXTURE_PLUS_KOSDAQ_INDEX_SIZE = sizeof(ExturePlusKosdaqIndex);
#endif

#if(1)
//코스피_종목상태정보(VI)
//VI 발동/해제 정보
//(증권A) STK : R801S
//(증권C) STK : R803S, R804S
//(증권B) KSQ : R801Q
//VI (Volatility Interruption) 발동/해제 정보
class ExturePlusKosdaqKOSDAQVolatilityInterruptionPerInstrument
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char boardID[2];                                     //보드ID
	char issueCode[12];                                     //종목코드
	char issueSeqNo[6];                                     //정보분배종목인덱스
	char tradeExecutionProcessingTime[12];                                     //매매처리시각
	char removalTimeOfVI[9];                                     //VI해제시각
	char VIApplicationCategoryCode[1];                                     //VI적용구분코드
	char VITypeCode[1];                                     //VI종류코드
	char basePriceToTriggerStaticVI[11];                                     //정적VI발동기준가격
	char basePriceToTriggerDynamicVI[11];                                     //동적VI발동기준가격
	char VITriggeringPrice[11];                                     //VI발동가격
	char disparateRatioStaticVI[13];                                     //정적VI발동가격괴리율
	char disparateRatioDynamicVI[13];                                     //동적VI발동가격괴리율
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_KOSDAQ_VOLATILITY_INTERRUPTION_PER_INSTRUMENT_SIZE = sizeof(ExturePlusKosdaqKOSDAQVolatilityInterruptionPerInstrument);
#endif

#if(1)
//배분정보	
//(증권A) STK : O601S
//(증권C) STK : O602S, O603S, O604S
//(증권B) KSQ : O601Q
//(증권B) KNX : O601X
//(파생A) DRV : O601F, O603F
//단일가체결이 상/하한가로 결정되는 경우 상/하한가 매수, 매도주문에 대해 일정량의 수량을 순차적으로 배분하여 체결시키는 경우
class ExturePlusKosdaqQuantityAllocation
{
    public:

	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char boardID[2];                                     //보드ID
	char issueCode[12];                                     //종목코드
	char serialNo[6];                                     //정보분배종목인덱스
	char allocationStartEnd[1];                                     //배분적용구분코드
	char allocationTypeCode[1];                                     //배분처리구분코드
	char timeForAllocationEnd[9];                                     //배분해제시각
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_QUANTITY_ALLOCATION_SIZE = sizeof(ExturePlusKosdaqQuantityAllocation);
#endif

#if(1)
//종목이벤트 정보
//(증권A) STK : I601S
//(증권C) STK : I602S, I603S, I604S
//(증권B) KSQ : I601Q
//(증권B) KNX : I601X
//주식/채권 종목의 거래정지, 관리종목, 정리매매 등의 이벤트 정보
//선물회선은 (STK, KSQ) 종목 중 기초자산 해당종목만 필터링 "
class ExturePlusKosdaqKOSDAQIssueEventInformation
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char distributeStockIndex[8];                                     //정보분배일련번호
	char issueCode[12];                                     //종목코드
	char eventTypeCode[2];                                     //이벤트종류코드
	char eventOccurrenceCauseCode[4];                                     //이벤트발생사유코드
	char startDate[8];                                     //이벤트개시일자
	char expirationDate[8];                                     //이벤트종료일자
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_KOSDAQ_ISSUE_EVENT_INFORMATION_SIZE = sizeof(ExturePlusKosdaqKOSDAQIssueEventInformation);
#endif

#if(1)
//프로그램매매 호가//프로그램매매 종목별집계
//(증권A) STK : C301S
//(증권B) KSQ : C301Q
//프로그램매매 종목별집계
//차익종목 : 종합지수 대상종목
//비차익종목 : K200 or Q150 or KRX300 대상종목
class ExturePlusKosdaqProgramTrade
{
    public:

	char dataClass[2];                        //데이터구분값
	char infoMarketClass[3];                        //정보구분값
	char stockCode[12];                        //종목코드
	char serialNo[6];                        //정보분배종목인덱스
	char indexMarginalProfitAskQuoteRemainder[15];                        //매도차익거래잔량
	char indexMarginalProfitBidQuoteRemainder[15];                        //매수차익거래잔량
	char indexNotMarginalProfitAskQuoteRemainder[15];                        //매도비차익잔량
	char indexNotMarginalProfitBidQuoteRemainder[15];                        //매수비차익잔량
	char indexMarginalProfitAskQuoteVolume[15];                        //매도차익수량
	char indexMarginalProfitBidQuoteVolume[15];                        //매수차익수량
	char indexNotMarginalProfitAskQuoteVolume[15];                        //매도비차익수량
	char indexNotMarginalProfitBidQuoteVolume[15];                        //매수비차익수량
	char indexMarginalProfitAskConsignmentTradeVolume[10];                        //위탁매도차익체결수량
	char indexMarginalProfitAskFloorTradeVolume[10];                        //자기매도차익체결수량
	char indexMarginalProfitBidConsignmentTradeVolume[10];                        //위탁매수차익체결수량
	char indexMarginalProfitBidFloorTradeVolume[10];                        //자기매수차익체결수량
	char indexNotMarginalProfitAskConsignmentTradeVolume[10];                        //위탁매도비차익체결수량
	char indexNotMarginalProfitAskFloorTradeVolume[10];                        //자기매도비차익체결수량
	char indexNotMarginalProfitBidConsignmentTradeVolume[10];                        //위탁매수비차익체결수량
	char indexNotMarginalProfitBidFloorTradeVolume[10];                        //자기매수비차익체결수량
	char indexMarginalProfitAskConsignmentTradeAmount[22];                        //위탁매도차익거래대금
	char indexMarginalProfitAskFloorTradeAmount[22];                        //자기매도차익거래대금
	char indexMarginalProfitBidConsignmentTradeAmount[22];                        //위탁매수차익거래대금
	char indexMarginalProfitBidFloorTradeAmount[22];                        //자기매수차익거래대금
	char indexNotMarginalProfitAskConsignmentTradeAmount[22];                        //위탁매도비차익거래대금
	char indexNotMarginalProfitAskFloorTradeAmount[22];                        //자기매도비차익거래대금
	char indexNotMarginalProfitBidConsignmentTradeAmount[22];                        //위탁매수비차익거래대금
	char indexNotMarginalProfitBidFloorTradeAmount[22];                        //자기매수비차익거래대금
	char endOfText[1];                        //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_SIZE = sizeof(ExturePlusKosdaqProgramTrade);
#endif

#if(1)
//프로그램매매 전체집계
//(증권A) STK : J001S
//(증권B) KSQ : J001Q
//프로그램매매 전체집계
//차익종목 : 종합지수 대상종목
//비차익종목 : K200 or Q150 or KRX300 대상종목"
class ExturePlusKosdaqProgramTradeTotal
{
    public:
	char dataClass[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char indexMarginalProfitAskQuoteRemainder[15];                                     //매도차익거래잔량
	char indexMarginalProfitBidQuoteRemainder[15];                                     //매수차익거래잔량
	char indexNotMarginalProfitAskQuoteRemainder[15];                                     //매도비차익잔량
	char indexNotMarginalProfitBidQuoteRemainder[15];                                     //매수비차익잔량
	char indexMarginalProfitAskQuoteVolume[15];                                     //매도차익수량
	char indexMarginalProfitBidQuoteVolume[15];                                     //매수차익수량
	char indexNotMarginalProfitAskQuoteVolume[15];                                     //매도비차익수량
	char indexNotMarginalProfitBidQuoteVolume[15];                                     //매수비차익수량
	char indexMarginalProfitAskConsignmentTradeVolume[10];                                     //위탁매도차익체결수량
	char indexMarginalProfitAskFloorTradeVolume[10];                                     //자기매도차익체결수량
	char indexMarginalProfitBidConsignmentTradeVolume[10];                                     //위탁매수차익체결수량
	char indexMarginalProfitBidFloorTradeVolume[10];                                     //자기매수차익체결수량
	char indexNotMarginalProfitAskConsignmentTradeVolume[10];                                     //위탁매도비차익체결수량
	char indexNotMarginalProfitAskFloorTradeVolume[10];                                     //자기매도비차익체결수량
	char indexNotMarginalProfitBidConsignmentTradeVolume[10];                                     //위탁매수비차익체결수량
	char indexNotMarginalProfitBidFloorTradeVolume[10];                                     //자기매수비차익체결수량
	char indexMarginalProfitAskConsignmentTradeAmount[22];                                     //위탁매도차익거래대금
	char indexMarginalProfitAskFloorTradeAmount[22];                                     //자기매도차익거래대금
	char indexMarginalProfitBidConsignmentTradeAmount[22];                                     //위탁매수차익거래대금
	char indexMarginalProfitBidFloorTradeAmount[22];                                     //자기매수차익거래대금
	char indexNotMarginalProfitAskConsignmentTradeAmount[22];                                     //위탁매도비차익거래대금
	char indexNotMarginalProfitAskFloorTradeAmount[22];                                     //자기매도비차익거래대금
	char indexNotMarginalProfitBidConsignmentTradeAmount[22];                                     //위탁매수비차익거래대금
	char indexNotMarginalProfitBidFloorTradeAmount[22];                                     //자기매수비차익거래대금
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_TOTAL_SIZE = sizeof(ExturePlusKosdaqProgramTradeTotal);
#endif

#if(1)
//코스피 거래원//거래상위 5개 회원 통계(B901S)
//(증권A) STK : B901S
//(증권C) STK : B902S, B903S, B904S
//(증권B) KSQ : B901Q
//(증권B) KNX : B901X
class ExturePlusKosdaqSecuritiesTradeRecord
{
    public:
        char askSecuritiesTradeNumber[5];                             // 006-1 매도거래원번호
        char askTradeVolume[12];                                      // 006-2 매도체결수량
        char askTradeAmount[22];                                      // 006-3 매도거래대금
        char bidSecuritiesTradeNumber[5];                             // 006-4 매수거래원번호
        char bidTradeVolume[12];                                      // 006-5 매수체결수량
        char bidTradeAmount[22];                                      // 006-6 매수거래대금
};
const int EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_RECORD_SIZE = sizeof(ExturePlusKosdaqSecuritiesTradeRecord);

class ExturePlusKosdaqSecuritiesTrade
{
    public:
        char dataClass[2];                                            //데이터구분값
        char infoMarketClass[3];                                            //정보구분값
        char stockCode[12];                                           //종목코드
		char serialNo[6];                                             //정보분배종목인덱스
        ExturePlusKosdaqSecuritiesTradeRecord rec[5];                   //거래원정보 OCCURS 5
        char endOfText[1];                                               //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_SECURITIES_TRADE_SIZE = sizeof(ExturePlusKosdaqSecuritiesTrade);
#endif

#if(1)
// 증권 우선호가 (MM/LP호가 제외)
// (증권A) STK : B601S
// (증권B) KSQ : B601Q
// (증권B) KNX : B601X
class ExturePlusKosdaqQuoteRecord
{
    public:
	char askQuote[11];	                // 매도n단계우선호가가격
	char bidQuote[11];                  // 매수n단계우선호가가격
	char askQuoteVolume[12];            // 매도n단계우선호가잔량
	char bidQuoteVolume[12];            // 매수n단계우선호가잔량
};
const int EXTURE_PLUS_KOSDAQ_QUOTE_RECORD_SIZE = sizeof(ExturePlusKosdaqQuoteRecord);

class ExturePlusKosdaqQuote10
{
    public:
     char dataClass[2];       //       데이터구분값  
     char infoMarketClass[3];     //       정보구분값   
     char distributeStockIndex[8];                    //       정보분배일련번호    
     char boardID[2];     //       보드ID    
     char sessionID[2];   //       세션ID    
     char stockCode[12];      //       종목코드    
     char stockSeq[6];    //       정보분배종목인덱스   
     char tradingProcessingTime[12];  //       매매처리시각 
     ExturePlusKosdaqQuoteRecord rec[10];			// 매도(수) n단계 우선호가 정보 
     char totalAskQuoteRemainder[12];     //       매도호가공개단계잔량합계    
     char totalBidQuoteRemainder[12];     //       매수호가공개단계잔량합계    
     char estimatedTradePrice[11];    //       예상체결가   
      char estimatedTradeVolume[12];      //       예상체결수량  
     char endText[1];     //       정보분배메세지종료키워드    
};
const int EXTURE_PLUS_KOSDAQ_QUOTE10_SIZE = sizeof(ExturePlusKosdaqQuote10);
#endif

#if(1)
// 현재등락
//(증권A) STK : B501S
//(증권B) KSQ : B501Q
//(증권B) KNX : B501X 
class ExturePlusKosdaqUpDown
{
    public:
	 char data_category[2];           //       데이터구분값  
	 char infoMarketClass[3];               //       정보구분값   
	 char totalStockSize[5];          //       등락대상종목수
	 char tradeFormationStockSize[5]; //       등락거래형성수    
	 char upLimitStockSize[5];        //       등락상한수 
	 char upStockSize[5];             //       등락상승수  
	 char sattionaryStockSize[5];     //       등락보합수
	 char downLimitStockSize[5];      //       등락하한수
	 char downStockSize[5];           //       등락하락수  
	 char quotationStockSize[5];      //       등락기세수
	 char quotationUpStockSize[5];    //       등락기세상승수
	 char quotationDownStockSize[5];  //       등락기세하락수
	 char endText[1];                 //       정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_UPDOWN_SIZE = sizeof(ExturePlusKosdaqUpDown);
#endif

#if(1)
//주식종목정보변경
//(증권A) STK : A801S
//(증권C) STK : A802S, A803S, A804S
//(증권B) KSQ : A801Q
//(증권B) KNX : A801X
class ExturePlusKosdaqIssueInformationDisclosure
{
	public:
	char data_category[2];                                          //  데이터구분값  
	char infoMarketClass[3];                                   //  정보구분값   
	char board_id[2];                                               //  보드ID    
	char issue_code[12];                                            //  종목코드    
	char issue_seq_no[6];    										 //  정보분배종목인덱스   
	char disclosure_data_type_code[3];                              //  공개정보구분코드값   
	char basis_price[11];                                           //  기준가격    
	char upper_limit_price[11];                                     //  상한가 
	char lower_limit_price[11];                                     //  하한가 
	char evaluation_price[11];                                      //  평가가격    
	char highest_order_price[11];                                   //  최고호가가격  
	char lowest_order_price[11];                                    //  최저호가가격  
	char opening_price_becomes_basis_price_type[1];                 //  시가기준가격여부    
	char back_door_listing[2];                                      //  락구분코드   
	char par_value_change_type_code[2];                             //  액면가변경구분코드   
	char lot_size[11];                                              //  수량단위    
	char number_of_listed_stocks[16];                               //  상장주식수   
	char designation[1];                                            //  지정여부    
	char closing_price_possibility_in_pre_off_hours_session[1];     //  장개시전시간외종가가능여부   
	char endText[1];     										     //  정보분배메세지종료키워드    
};
const int EXTURE_PLUS_KOSDAQ_ISSUE_INFORMATION_DISCLOSURE_SIZE = sizeof(ExturePlusKosdaqIssueInformationDisclosure);
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
class ExturePlusKosdaqMarketOperationTS
{
    public:
	char dataCategory[2];                                //데이터구분값
	char infoMarketClass[3];                                //정보구분값
	char distributeStockIndex[8];                                //정보분배일련번호
	char boardID[2];                                //보드ID
	char sessionID[2];                                //세션ID
	char issueCode[12];                                //종목코드
	char serialNo[6];                                //정보분배종목인덱스
	char tradeProcessTime[12];                                //매매처리시각
	char boardEventID[3];                                //보드이벤트ID
	char boardEventBeginTime[9];                                //보드이벤트시작시각
	char boardEventApplyCode[5];                                //보드이벤트적용군코드
	char tradingHaltReasonCode[3];                                //거래정지사유코드
	char endOfText[1];                                //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_MARKET_OPERATION_TS_SIZE = sizeof(ExturePlusKosdaqMarketOperationTS);
#endif

#if(1)
//기준가결정
//(증권A) STK : A401S
//(증권C) STK : A402S, A403S, A404S
//(증권B) KSQ : A401Q
//(증권B) KNX : A401X
//평가가격 대상 종목의 기준가결정시 제공
class ExturePlusKosdaqKOSDAQDeterminedBasePrice
{
	public:
	char dataCategory[2];                      // 데이터구분값
	char infoMarketClass[3];               // 정보구분값
	char distributeStockIndex[8];                        // 정보분배일련번호
	char boardID[2];                           // 보드ID
	char issueCode[12];                        // 종목코드
	char stockSeq[6];                          // 정보분배종목인덱스
	char basisPrice[11];                       // 기준가격
	char upperLimitPriceOfBasisPrice[11];      // 기준가격상한가
	char lowerLimitPriceOfBasisPrice[11];      // 기준가격하한가
	char endText[1];                           // 정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_KOSDAQ_DETERMINED_BASE_PRICE_SIZE = sizeof(ExturePlusKosdaqKOSDAQDeterminedBasePrice);
#endif

#if(1)
// 증권 체결
// (증권A) STK : A301S
// (증권C) STK : A302S, A303S, A304S
// (증권B) KSQ : A301Q
// (증권B) KNX : A301X
class ExturePlusKosdaqTrade
{
    public:
     char dataClass[2];                        //       데이터구분값  
     char infoMarketClass[3];                        //       정보구분값   
     char distributeStockIndex[8];                         //       정보분배일련번호    
     char boardID[2];                          //       보드ID    
     char sessionID[2];                        //       세션ID    
     char stockCode[12];                       //       종목코드    
     char stockSeq[6];                         //       정보분배종목인덱스   
     char transactionProcessingTime[12];   	   //       매매처리시각  
     char upDown[1];                           //       전일대비구분코드    
     char gap[11];                              //       전일대비가격  
     char tradePrice[11];                       //       체결가격    
     char tradeVolume[10];                     //       거래량 
     char openPrice[11];                        //       시가  
     char highPrice[11];                        //       고가  
     char lowPrice[11];                         //       저가  
     char accmTradeVolume[12];                 //       누적거래량   
     char accmTradeAmount[22];                 //       누적거래대금  
     char lastAskBidClassCode[1];              //       최종매도매수구분코드  
     char LPHoldingVolume[15];                 //       LP보유수량  
     char askOneQuote[11];                      //       매도최우선호가가격   
     char bidOneQuote[11];                      //       매수최우선호가가격   
     char endText[1];                          //       정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_TRADE_SIZE = sizeof(ExturePlusKosdaqTrade);
#endif

#if(1)
//공매도정보
//(증권A) STK : I801S
//(증권C) STK : I802S, I803S, I804S
//(증권B) KSQ : I801Q
//(증권B) KNX : I801X
class ExturePlusKosdaqShortSellingInformation
{
    public:
	char dataCategory[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char issueCode[12];                                     //종목코드
	char shortSellingDebtSecuritiesAskTradingVolume[12];                                     //차입공매도체결수량
	char shortSellingDebtSecuritiesAskTradingValue[22];                                     //차입공매도거래대금
	char upTickRuleAppliedCoveredShortSellingTradingVolume[12];                                     //업틱룰적용거래량
	char upTickRuleAppliedCoveredShortSellingTradingValue[22];                                     //업틱룰적용거래대금
	char upTickRuleUnappliedCoveredShortSellingTradingVolume[12];                                     //업틱룰예외거래량
	char upTickRuleUnappliedCoveredShortSellingTradingValue[22];                                     //업틱룰예외거래대금
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_SHORT_SELLING_INFORMATION_SIZE = sizeof(ExturePlusKosdaqShortSellingInformation);
#endif

#if(1)
class ExturePlusKosdaqProgramTradePublic
{
    public:
        char dataClass[2];                                             // 001 데이터구분
        char infoClass[2];                                             // 002 정보구분
        char marketClass[1];                                           // 003 시장구분
        char stockCode[12];                                            // 004 종목코드
        char serialNo[8];                                              // 005 일련번호
        char askPublicAheadPublicPrevRemainder[12];                    // 006 사전공시신규호가매도수량(항목명변경:매도공시사전수량->사전공시신규호가매도수량)
        char bidPublicAheadPublicPrevRemainder[12];                    // 007 사전공시신규호가매수수량(항목명변경:매수공시사전수량->사전공시신규호가매수수량)
        char askPublicAheadPublicPrevCorrectingRemainder[12];          // 008 사전공시기제출호가매도수량(항목명변경:매도공시사전정정수량->사전공시기제출호가매도수량)
        char bidPublicAheadPublicPrevCorrectingRemainder[12];          // 009 사전공시기제출호가매수수량(항목명변경:매수공시사전정정수량->사전공시기제출호가매수수량)
        char postDisclosedProgramTradingSellOrderVolume[12];           // 010 사후공시매도수량(단위 : 주,  신규                2011.05.30)
        char postDisclosedProgramTradingBuyOrderVolume[12];            // 011 사후공시매수수량(단위 : 주,  신규                2011.05.30)
        char filler[2];                                                // 012 FILLER
        char ff[1];                                                    // 013 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_PUBLIC_SIZE = sizeof(ExturePlusKosdaqProgramTradePublic);
#endif

#if(1)
class ExturePlusKosdaqProgramTradeBatch
{
    public:
        char dataClass[2];                                            // 001 data구분
        char infoClass[2];                                            // 002 정보구분
        char marketClass[1];                                          // 003 시장구분
        char serialNo[8];                                             // 004 일련번호
        char ptFirstMonthClassCode[1];                                // 005 PT월물구분코드
        char consignmentFloorTradingClassCode[2];                     // 006 위탁자기구분코드
        char memberNo[5];                                             // 007 회원번호
        char tradeDate[8];                                            // 008 매매일자
        char stockAskVolume[12];                                      // 009 주식매도수량
        char stockAskAmount[22];                                      // 010 주식매도금액
        char stockBidVolume[12];                                      // 011 주식매수수량
        char stockBidAmount[22];                                      // 012 주식매수금액
        char futureAskVolume[12];                                     // 013 선물매도수량
        char futureAskAmount[22];                                     // 014 선물매도금액
        char futureBidVolume[12];                                     // 015 선물매수수량
        char futureBidAmount[22];                                     // 016 선물매수금액
        char callAskVolume[12];                                       // 017 콜매도수량
        char callAskAmount[22];                                       // 018 콜매도금액
        char callBidVolume[12];                                       // 019 콜매수수량
        char callBidAmount[22];                                       // 020 콜매수금액
        char putAskVolume[12];                                        // 021 풋매도수량
        char putAskAmount[22];                                        // 022 풋매도금액
        char putBidVolume[12];                                        // 023 풋매수수량
        char putBidAmount[22];                                        // 024 풋매수금액
        char stockErrorVolume[12];                                    // 025 주식오차수량
        char stockErrorCause[60];                                     // 026 주식오차사유
        char filler[6];                                               // 027 FILLER
        char ff[1];                                                   // 028 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_PROGRAM_TRADE_BATCH_SIZE = sizeof(ExturePlusKosdaqProgramTradeBatch);
#endif

#if(1)
//전자공시
//(증권A) STK  : F000S, E900S
//(증권A) KSQ  : F000Q, E900Q
//(증권A) KNX  : F000X, E900X
//(증권A) OTHERS : F0909, E9909
//전자공시 (온라인)    : F0
//전일 전자공시 (배치) : E9
class ExturePlusKosdaqPublicNews
{
    public:
	char dataClass[2];                                     //데이터구분값
	char infoMarketClass[3];                                     //정보구분값
	char stockCode[12];                                     //종목코드
	char publicNewsSerialNumber[6];                                     //공시연단위일련번호
	char perPublicNewsTotalPageSize[5];                                     //공시문서총페이지번호
	char perPulbicNewsPageSerialNumber[5];                                     //공시문서페이지번호
	char publicNewsDate[8];                                     //공시일자
	char sendDate[8];                                     //전송일자
	char publicNewsMarketClass[1];                                     //공시시장구분코드
	char stockName[40];                                     //종목약명
	char processClass[1];                                     //공시문서처리구분값
	char reason[5];                                     //공시사유구분코드값
	char koreanEnglishClass[1];                                     //공시언어구분값
	char publicNewsTitle[264];                                     //공시문서제목
	char publicNewsContents[1000];                                     //공시문서내용
	char isStockExistence[1];                                     //공시문서종목코드포함여부
	char isPulbicNewsContentsStockCode[1];                                     //공시페이지종목코드여부
	char stockCodeCount[2];                                     //공시페이지종목개수
	char endOfText[1];                                     //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE = sizeof(ExturePlusKosdaqPublicNews);
#endif

#if(0)
class ExturePlusKosdaqPublicNews
{
    public:
        char dataClass[2];                                              // 001 DATA구분
        char infoClass[2];                                              // 002 정보구분
        char marketClass[1];                                            // 003 시장구분
        char stockCode[12];                                             // 004 종목코드
        char publicNewsSerialNumber[6];                                 // 005 공시일련번호
        char perPublicNewsTotalPageSize[5];                             // 006 공시건당 총 페이지 수
        char perPulbicNewsPageSerialNumber[5];                          // 007 공시건당 페이지 일련번호
        char publicNewsDate[8];                                         // 008 공시일자
        char sendDate[8];                                               // 009 전송일자
        char publicNewsMarketClass[1];                                  // 010 공시용시장구분
        char stockName[40];                                             // 011 종목명
        char processClass[1];                                           // 012 처리구분
        char reason[5];                                                 // 013 사유
        char koreanEnglishClass[1];                                     // 014 국문영문구분
        char publicNewsTitle[264];                                      // 015 공시제목
        char publicNewsContents[1000];                                  // 016 공시내용.
        char isStockExistence[1];                                       // 017 종목존재여부.
        char isPulbicNewsContentsStockCode[1];                          // 018 공시내용 종목코드여부
        char stockCodeCount[2];                                         // 019 종목코드갯수
        char filler[8];                                                 // 020 FILLER
        char ff[1];                                                     // 021 END OF TEXT
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_PUBLIC_NEWS_SIZE = sizeof(ExturePlusKosdaqPublicNews);
#endif

#if(0)
// 유가증권_UDP_코스콤정보분배_20140203_1차안내.xlsb
// 23   ETF PDF 변경없음    F8011   ETF PDF 160 -   일일 06:10, 06:50 총 2회 전송
class ExturePlusKosdaqETF_PDF
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA 구분
        char informationCategory[2];                            // 002 정보구분
        char marketCategory[1];                                 // 003 시장구분
        char etfCode[12];                                       // 004 ETF코드
        char dataSeqNumber[8];                                  // 005 데이터 일련번호
        char date[8];                                           // 006 일자
        char transferAgentNumber[3];                            // 007 사무수탁회사번호
        char compositionIssueNumber[4];                         // 008 구성종목수
        char compositionIssueCode[12];                          // 009 구성종목코드
        char oneCUUnitShare[18];                                // 010 "1CU단위증권수/계약수/원화현금/USD현금/원화평가액"
        char compositionIssueMarketType[1];                     // 011 구성종목시장구분
        char compositionIssueName[40];                          // 012 구성종목명
        char parValueAmount[18];                                // 013 "액면금액/설정현금액/원화평가금액"
        char profitDistributionBasisDate[8];                    // 014 이익분배기준일
        char appraisedValue[18];                                // 015 평가금액
        char filler[4];                                         // 016 FILLER
        char endOfText[1];                                      // 017 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE = sizeof(ExturePlusKosdaqETF_PDF);
#endif

#if(1)
//코스콤 정보,ETP정보,ETF PDF,F803S
class ExturePlusKosdaqETF_PDF
{
	public:
	char dataCategory[2];                            //데이터구분값
	char infoMarketClass[3];                         //정보구분값
	char etfCode[12];                                //종목코드
	char dataSeqNumber[8];                           //데이터 일련번호
	char date[8];                                    //일자
	char transferAgentNumber[3];                     //사무수탁회사번호
	char compositionIssueNumber[4];                  //구성종목수
	char compositionIssueCode[12];                   //구성종목코드
	char oneCUUnitShare[18];                         //1CU단위증권수/계약수/원화현금
	char compositionIssueMarketType[1];              //구성종목시장구분
	char compositionIssueName[40];                   //구성종목명
	char parValueAmount[18];                         //액면금액/설정현금액
	char profitDistributionBasisDate[8];             //이익분배기준일
	char appraisedValue[18];                         //평가금액
	char filler[4];                                  //FILLER
	char endOfText[1];                               //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_ETF_PDF_SIZE = sizeof(ExturePlusKosdaqETF_PDF);
#endif

#if(1)
class ExturePlusKosdaqRecoveryTrade
{
    public:
        char dataClass[2];                                          // 001 DATA구분
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드(표준코드)
        char serialNo[5];                                           // 005 종목일련번호
        char upDown[1];                                             // 006 등락구분
        char gap[9];                                                // 007 전일대비
        char closePrice[11];                                        // 008 현재가
        char openPrice[11];                                         // 009 시가
        char highPrice[11];                                         // 010 고가
        char lowPrice[11];                                          // 011 저가
        char askQuote[11];                                          // 012 매도호가
        char bidQuote[11];                                          // 013 매수호가
        char accmTradeVolume[12];                                   // 014 누적체결수량
        char accmTradeAmount[22];                                   // 015 누적거래대금
        char realRateQuotationClass[1];                             // 016 실세/기세구분
        char boardEventID[3];                                       // 017 보드이벤트ID
        char boardID[2];                                            // 018 보드ID
        char isTradeStop[1];                                        // 019 거래정지여부

        char beforeMarketOverTimeClosePriceTradeVolume[12];         // 020 장개시전시간외종가체결수량
        char beforeMarketOverTimeClosePriceTradeAmount[22];         // 021 장개시전시간외종가거래대금

        char regularMarketTradeVolume[12];                          // 022 정규장체결수량
        char regularMarketTradeAmount[22];                          // 023 정규장거래대금

        char afterMarketOvertimeClosePriceTradeVolume[12];          // 024 장종료후시간외종가체결수량
        char afterMarketOvertimeClosePriceTradeAmount[22];          // 025 장종료후시간외종가거래대금

		char overTimeMarketFixedAccmVolume[12];          //단일가체결수량
        char overTimeMarketFixedAccmAmount[22];          //단일가거래대금

		char manyBulkTradeVolume[12];          //대량체결수량
        char manyBulkTradeAmount[22];          //대량거래대금

        char earlyClosedELWStatus[1];                               // 026 ELW 조기종료여부
        char earlyClosedELWTime[6];                                 // 027 ELW 조기종료시간

        char aBlox[1];                                              // 028 경쟁대량 방향구분
        char regularBuyInTradingVolume[12];                         // 029 일반 Buy-In 체결수량
        char regularBuyInTradingValue[22];                          // 030 일반 Buy-In 거래대금
        char sameDayBuyInTradingVolume[12];                         // 031 당일 Buy-In 체결수량
        char sameDayBuyInTradingValue[22];                          // 032 당일 Buy-In 거래대금
        char filler[8];                                             // 033 FILLER
        char ff[1];                                                 // 034 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_SIZE = sizeof(ExturePlusKosdaqRecoveryTrade);
#endif


#if(1)
// 유가증권_UDP_정보분배_20140203_4차안내.xlsb
//18  코스피_시간외단일가_최종   코스피_시간외단일가_최종   B3011   코스피_시간외단일가_최종   170 170 실시간
//19  코스피_시간외단일가_시세   코스피_시간외단일가_시세   B4011   코스피_시간외단일가_시세   170 170 실시간
class ExturePlusKosdaqRecoveryTradeFixed
{
    public:
        char dataClass[2];                                          // 001 DATA구분
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드
        char serialNo[5];                                           // 005 종목일련번호
        char upDown[1];                                             // 006 시간외단일가등락구분
        char gap[9];                                                // 007 시간외단일가대비
        char overTimeMarketFixedUpLimitPrice[11];                    // 008 시간외단일가상한가
        char overTimeMarketFixedDownLimitPrice[11];                  // 009 시간외단일가하한가
        char overTimeMarketFixedCurrClosePrice[11];                  // 010 시간외단일가현재가
        char overTimeMarketFixedOpenPrice[11];                       // 011 시간외단일가시가
        char overTimeMarketFixedHighPrice[11];                       // 012 시간외단일가고가
        char overTimeMarketFixedLowPrice[11];                        // 013 시간외단일가저가
        char overTimeMarketFixedAskQuote[11];                        // 014 시간외단일매도호가
        char overTimeMarketFixedBikQuote[11];                        // 015 시간외단일매수호가
        char overTimeMarketFixedAccmVolume[12];                     // 016 시간외단일가누적체결수량
        char overTimeMarketFixedAccmAmount[22];                     // 017 시간외단일가누적거래대금
        char totalAccmVolume[12];                                   // 018 전체 총 누적체결수량
        char totlaAccmAmount[22];                                   // 019 전체 총 누적거래대금
        char overTimeMarketFixedMarketClass[1];                     // 020 시간외단일가장구분
        char isTradeStop[1];                                        // 021 거래정지여부
        char realRateQuotationClass[1];                             // 022 실세/기세 구분
        char filler[2];                                             // 023 FILLER
        char ff[1];                                                 // 024 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_RECOVERY_TRADE_FIXED_SIZE = sizeof(ExturePlusKosdaqRecoveryTradeFixed);
#endif

#if(1)
//업종별 투자자별 통계//업종별 투자자별 통계
//09:00~18:00 [90초 주기]
//(증권A) STK : C001S
//(증권B) KSQ : C001Q
//(증권B) KNX : C001X
class ExturePlusKosdaqTotalInvestorIndex
{
    public:
	char dataClass[2];              //데이터구분값
	char infoMarketClass[3];              //정보구분값
	char calculationTime[6];              //통계산출시각
	char investorCode[4];              //투자자구분코드
	char jisuIdentifiation[6];              //지수ID
	char jisuStandardCode[12];              //표준코드
	char askTradeVolume[12];              //누적매도체결수량
	char askTradeAmount[22];              //누적매도거래대금
	char bidTradeVolume[12];              //누적매수체결수량
	char bidTradeAmount[22];              //누적매수거래대금
	char filler[3];              //필러값3
	char endText[1];              //정보분배메세지종료키워드
};
const int EXTURE_PLUS_KOSDAQ_TOTAL_INVESTOR_INDEX_SIZE = sizeof(ExturePlusKosdaqTotalInvestorIndex);
#endif

#if(1)
class ExturePlusKosdaqInvestorIndex
{
    public:
        char dataClass[2];                                            // 001 DATA구분
        char infoClass[2];                                            // 002 정보구분
        char marketClass[1];                                          // 003 시장구분
        char calculationTime[6];                                      // 004 산출시각
        char investorCode[4];                                         // 005 투자자코드
        char businessType[3];                                         // 006 업종코드
        char askTradeVolume[12];                                      // 007 매도체결수량
        char askTradeAmount[22];                                      // 008 매도거래대금
        char bidTradeVolume[12];                                      // 009 매수체결수량
        char bidTradeAmount[22];                                      // 010 매수거래대금
        char filler[7];
        char ff[1];
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_INVESTOR_INDEX_SIZE = sizeof(ExturePlusKosdaqInvestorIndex);
#endif

#if(1)
class ExturePlusKoscomLineLKInfo_KOSDAQ
{
    public:
        // 001 ~ 010
        char dataCategory[2];                                   // 001 DATA 구분
        char informationCategory[2];                            // 002 정보구분
        char marketCategory[1];                                 // 003 시장구분
        char time[4];                                           // 004 시간
        char ff[1];                                             // 005 FF
        char recvAddr[32];                                      // 수신주소정보(전문에는 없는 것)
};
const int EXTURE_PLUS_KOSCOM_LINE_LK_INFO_KOSDAQ_SIZE = sizeof(ExturePlusKoscomLineLKInfo_KOSDAQ);
#endif

#if(1)
// 지수 리커버리용 내부 레코드
// 체결 포맷을 빌려서 채운다.
// DATA 구분은 ZZ 로 임시로 설정함
class PaxfeedKosdaqCustomIndexRecoveryRec
{
    public:
        char dataClass[2];                                          // 001 DATA구분(ZZ)
        char infoClass[2];                                          // 002 정보구분
        char marketClass[1];                                        // 003 시장구분
        char stockCode[12];                                         // 004 종목코드
        char serialNo[5];                                           // 005 종목일련번호(A0001 의 serialNo 와 같은 값이며, 사이즈가 다르지만 실제 유효한 값이 5자리를 안넘으므로 동일한 값임. 일련번호는 매일매일 다를 수 있음)
        char boardID[2];                                            // 006 보드 ID
        char upDown[1];                                             // 007 전일대비(기준가대비)구분
        char gap[9];                                                // 008 전일대비
        char tradePrice[9];                                         // 009 체결가격
        char tradeVolume[10];                                       // 010 체결수량
        char sessionID[2];                                          // 011 세션ID
        char openPrice[9];                                          // 012 시가
        char highPrice[9];                                          // 013 고가
        char lowPrice[9];                                           // 014 저가
        char accmTradeVolume[12];                                   // 015 누적체결수량
        char accmTradeAmount[18];                                   // 016 누적거래대금
        char lastAskBidClassCode[1];                                // 017 최종매도매수구분코드
        char isTradePriceQuotePrice1Equal[1];                       // 018 체결가와1호가일치여부
        char tradeTime[6];                                          // 019 체결시각
        char LPHoldingVolume[15];                                   // 020 LP보유수량
        char askOneQuote[9];                                        // 021 매도1호가
        char bidOneQuote[9];                                        // 022 매수1호가
        char filler[6];                                             // 023 FILLER(2)
        char ff[1];                                                 // 024 FF
        char cr[1];
        char lf[1];
};
const int PAXFEED_KOSDAQ_CUSTOM_INDEX_RECOVERY_REC = sizeof(PaxfeedKosdaqCustomIndexRecoveryRec);
#endif

#if(1)
class ExturePlusKosdaqBulkTrade
{
    public:
        char dataCategory[2];                                          // 001 DATA구분
        char informationCategory[2];                                   // 002 정보구분
        char marketCategory[1];                                        // 003 시장구분
        char issueCode[12];                                            // 004 종목코드
        char serialNo[5];                                              // 005 종목일련번호
        char seqNumber[8];                                             // 006 일련번호
        char kBloxVolumeInPreMarketTradingHoursSession[12];             // 007 장개시전 시간외 상대대량 체결수량
        char basketTradingVolumeInPreMarketTradingHoursSession[12];     // 008 장개시전 시간외 바스켓 체결수량
        char aBloxVolumeInPreMarketTradingHoursSession[12];             // 009 장개시전 시간외 경쟁대량체결수량
        char kBloxVolumeInRegularTradingHoursSession[12];               // 010 장중상대대량체결수량
        char basketTradingVolumeInRegularTradingHoursSession[12];       // 011 장중바스켓체결수량
        char aBloxVolumeInRegularTradingHoursSession[12];               // 012 장중경쟁대량체결수량
        char kBloxVolumeInPostMarketTradingHoursSession[12];            // 013 장종료후 시간외 상대대량체결수량
        char basketTradingVolumeInPostMarketTradingHoursSession[12];    // 014 장종료후 시간외 바스켓 체결수량
        char filler[7];                                                // 015 FILLER
        char ff[1];                                                    // 016 FF
        char cr[1];
        char lf[1];
};
const int EXTURE_PLUS_KOSDAQ_BULK_TRADE_SIZE = sizeof(ExturePlusKosdaqBulkTrade);
#endif

#pragma pack()

#endif // __EXTURE_PLUS_KOSDAQ_H__
