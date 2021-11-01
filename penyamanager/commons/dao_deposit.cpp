//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
    //
    DepositResultPtr DAO::createDeposit(const DepositPtr &pDepositPtr)
    {
        DepositResultPtr pNewDepositResultPtr(new DepositResult);

        auto createQuery = [pDepositPtr](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert new deposit
            queryPtr->prepare(
                    "INSERT INTO deposit "
                    "(idmember, state, date, total) "
                    "VALUES (:memberid, :state, :date, :total)"
                    );
            queryPtr->bindValue(":memberid", pDepositPtr->m_memberId);
            queryPtr->bindValue(":state", static_cast<Int32>(pDepositPtr->m_state));
            queryPtr->bindValue(":date", pDepositPtr->m_date);
            queryPtr->bindValue(":total", pDepositPtr->m_total);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createDeposit memberId %1").arg(pDepositPtr->m_memberId));
            pNewDepositResultPtr->m_error = 1;
            return pNewDepositResultPtr;
        }

        auto lastQuery = [](){
            return QueryPtr(new QSqlQuery(kLastQueryId));
        };

        // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
        QueryResponse lastQueryResponse = exec(lastQuery);
        if (lastQueryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createDeposit could not get last ID created in db"));
            pNewDepositResultPtr->m_error = 1;
        } else if (lastQueryResponse.query->next()) {
            pNewDepositResultPtr->m_deposit = pDepositPtr;
            pNewDepositResultPtr->m_deposit->m_id = lastQueryResponse.query->value(0).toUInt();
        }
        return pNewDepositResultPtr;
    }
    //
    DepositListResultPtr DAO::getUncheckedDeposits()
    {
        DepositListResultPtr pDepositListResultPtr(new DepositListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // unchecked deposit list
            queryPtr->prepare(
                    "SELECT member.username, deposit.iddeposit, deposit.date, deposit.total, deposit.idmember "
                    "FROM deposit "
                    "INNER JOIN member ON member.idmember = deposit.idmember "
                    "WHERE deposit.state = 0"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getUncheckedDeposits"));
            pDepositListResultPtr->m_error = 1;
        } else {
            pDepositListResultPtr->m_list = DepositListPtr(new DepositList);
            while (queryResponse.query->next()) {
                Uint32 column = 0;
                DepositPtr pDepositPtr(new Deposit);
                pDepositPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pDepositPtr->m_id = queryResponse.query->value(column++).toInt();
                pDepositPtr->m_date = queryResponse.query->value(column++).toDateTime();
                pDepositPtr->m_date.setTimeSpec(Qt::UTC);
                pDepositPtr->m_total = queryResponse.query->value(column++).toFloat();
                pDepositPtr->m_memberId = queryResponse.query->value(column++).toInt();
                pDepositListResultPtr->m_list->push_back(pDepositPtr);
            }
        }

        return pDepositListResultPtr;
    }
    //
    bool DAO::closeDeposit(Int32 depositId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // close deposit
            queryPtr->prepare(
                    "UPDATE deposit "
                    "SET state=1 "
                    "WHERE iddeposit=:depositid"
                    );
            queryPtr->bindValue(":depositid", depositId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("closeDeposit depositId %1").arg(depositId));
        }
        return !queryResponse.error;
    }
}
