#ifndef CTPTRADER_H_
#define CTPTRADER_H_
#include "CtpQuote.h"
#include "CtpTrade.h"
class CtpTrader{
public:
	CtpTradeSpi *trade_spi;
	//CtpTradeApi *api;
	CThostFtdcTraderApi* trade_api;

	CtpQuoteApi *quote_spi;
    CThostFtdcMdApi *quote_api;

	//int status;
	CtpTrader(Trader *trader);
};

#endif