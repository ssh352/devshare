#ifndef CTP_QUOTE_H_
#define CTP_QUOTE_H_
#include "ThostFtdcMdApi.h"
#include "trader.h"
#include "CtpQuoter.h"
#include <string>
using namespace std;
class CtpQuoteApi:public CThostFtdcMdApi
{
	/*
public:
	///创建MdApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	///modify for udp marketdata
	//static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false, const bool bIsMulticast=false);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release();
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init();
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join();
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	//virtual const char *GetTradingDay();
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress);
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress);
	
	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo);
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CThostFtdcMdSpi *pSpi);
	
	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount);

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

	///用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID);
	

	///登出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);
protected:
	~CtpQuoteApi();	
	*/
};


class CtpQuoteSpi:public CThostFtdcMdSpi
{
	public:
	int login_status;
	int requestId;
	CtpQuoter* ctpquoter;

	//Quoter *quoter;
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	CtpQuoteSpi(CThostFtdcMdApi* api, CtpQuoter *ctpquoter):api(api){this->ctpquoter=ctpquoter;};


	virtual void OnFrontConnected();
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);
	int  ReqUserLogin(TThostFtdcBrokerIDType	vAppId,
	        TThostFtdcUserIDType	vUserId,	TThostFtdcPasswordType	vPasswd);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) ;
private:
	CThostFtdcMdApi *api;
};



class CtpQuote
{
public:
	CThostFtdcMdApi *api;
	//CtpQuoteApi *api;
	CtpQuoteSpi *spi;
	CtpQuote(string username,string password, string quote_addr);
};
#endif