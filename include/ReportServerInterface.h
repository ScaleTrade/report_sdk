#pragma once

#include <ctime>
#include <rapidjson/document.h>
#include <string>
#include <vector>

#include "Structures.h"
#include "structures/AccountStructures.hpp"
#include "structures/CandleStructures.hpp"
#include "structures/TradeStructures.hpp"
#include "structures/SymbolStructures.hpp"
#include "structures/GroupStructures.hpp"
#include "structures/LogStructures.hpp"

class Core;

inline int REPORT_SERVER_API = 1;

class ReportServerInterface {
public:
    ReportServerInterface(Core* st, const std::string& name);
    ~ReportServerInterface();

    static int GetApiVersion() { return REPORT_SERVER_API; }

    virtual int GetLogs(time_t from, time_t to, const std::string& type, const std::string& filter, std::vector<ServerLog>* logs);

    virtual int GetAccountsByGroup(const std::string& group, std::vector<AccountRecord>* accounts);
    virtual int GetAccountByLogin(int login, AccountRecord* account);
    virtual int GetAccountBalanceByLogin(int login, MarginLevel* margin);
    virtual int GetMarginLevelByGroup(const std::string& group, std::vector<MarginLevel>* margins);
    virtual int GetAccountsEquitiesByGroup(time_t from, time_t to, const std::string& group_filter, std::vector<EquityRecord>* equities);
    virtual int GetAccountsEquitiesByLogin(time_t from, time_t to, int login, std::vector<EquityRecord>* equities);

    virtual int GetOpenTradesByLogin(int login, std::vector<TradeRecord>* trades);
    virtual int GetPendingTradesByLogin(int login, std::vector<TradeRecord>* trades);
    virtual int GetOpenTradesByMagic(int magic, std::vector<TradeRecord>* trades);
    virtual int GetOpenTradeByOrder(int order, TradeRecord* trade);
    virtual int GetOpenTradeByGwUUID(const std::string& gw_uuid, TradeRecord* trade);
    virtual int GetCloseTradeByGwUUID(const std::string& gw_uuid, TradeRecord* trade);
    virtual int GetOpenTradeByGwOrder(int gw_order, TradeRecord* trade);
    virtual int GetCloseTradeByGwOrder(int gw_order, TradeRecord* trade);
    virtual int GetCloseTradesByLogin(int login, std::vector<TradeRecord>* trades);
    virtual int GetCloseTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetPendingTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetOpenTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetAllOpenTrades(std::vector<TradeRecord>* trades);
    virtual int GetTransactionsByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetTransactionsByLogin(int login, time_t from, time_t to, std::vector<TradeRecord>* trades);

    virtual int CalculateCommission(const TradeRecord& trade, double* calculated_commission);
    virtual int CalculateSwap(const TradeRecord& trade, double* calculated_swap);
    virtual int CalculateProfit(const TradeRecord& trade, double* calculated_profit);
    virtual int CalculateMargin(const TradeRecord& trade, double* calculated_margin);
    virtual int CalculateConvertRateByCurrency(const std::string& from_cur, const std::string& to_cur, int cmd, double* multiplier);

    virtual int GetSymbol(const std::string& symbol, SymbolRecord* cs);
    virtual int GetGroup(const std::string& group_name, GroupRecord* group);
    virtual int GetAllGroups(std::vector<GroupRecord>* groups);

    virtual int GetCandles(const std::string& symbol, const std::string& frame, time_t from, time_t to, std::vector<CandleRecord>* candles);

private:
    Core* St;
    std::string report_name;
};
