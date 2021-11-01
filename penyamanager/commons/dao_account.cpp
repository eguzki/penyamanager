//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
    //
    FloatBoolPairResultPtr DAO::getAccountBalance(Int32 memberId)
    {
        FloatBoolPairResultPtr pResult(new FloatBoolPairResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member account balance
            queryPtr->prepare(
                    "SELECT balance FROM account "
                    "WHERE idmember=:memberid "
                    "ORDER BY date DESC LIMIT 1"
                    );
            // member and balance
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountBalance member %1").arg(memberId));
            pResult->m_error = 1;
        } else if (queryResponse.query->next())
        {
            pResult->m_pair.b = true;
            pResult->m_pair.f = queryResponse.query->value(0).toFloat();
        }
        return pResult;
    }
    //
    TransactionResultPtr DAO::getLastAccountInfo(Int32 memberId)
    {
        TransactionResultPtr pLastAccountInfoResultPtr(new TransactionResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // member's last account transaction
            queryPtr->prepare(
                    "SELECT member.username, account.amount, account.date, account.balance, account.description, account.type "
                    "FROM account "
                    "INNER JOIN member ON member.idmember = account.idmember "
                    "WHERE account.idmember=:memberid "
                    "ORDER BY account.date DESC "
                    "LIMIT 1"
                    );
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getLastAccountInfo memberId %1").arg(memberId));
            pLastAccountInfoResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            Uint32 column = 0;
            TransactionPtr pLastAccountInfoPtr(new Transaction);
            pLastAccountInfoPtr->m_memberId = memberId;
            pLastAccountInfoPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
            pLastAccountInfoPtr->m_amount = queryResponse.query->value(column++).toFloat();
            pLastAccountInfoPtr->m_date = queryResponse.query->value(column++).toDateTime();
            pLastAccountInfoPtr->m_date.setTimeSpec(Qt::UTC);
            pLastAccountInfoPtr->m_balance = queryResponse.query->value(column++).toFloat();
            pLastAccountInfoPtr->m_descr = queryResponse.query->value(column++).toString();
            pLastAccountInfoPtr->m_type = static_cast<TransactionType>(queryResponse.query->value(column++).toUInt());
            pLastAccountInfoResultPtr->m_transaction = pLastAccountInfoPtr;
        }
        return pLastAccountInfoResultPtr;
    }
    //
    bool DAO::insertTransaction(const TransactionPtr &pTransactionPtr)
    {
        auto createQuery = [pTransactionPtr](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert transaction
            queryPtr->prepare(
                    "INSERT INTO account "
                    "(idmember, amount, date, balance, description, type) "
                    "VALUES (:memberid, :amount, :date, :balance, :description, :type)"
                    );
            queryPtr->bindValue(":memberid", pTransactionPtr->m_memberId);
            queryPtr->bindValue(":amount", pTransactionPtr->m_amount);
            queryPtr->bindValue(":date", pTransactionPtr->m_date);
            queryPtr->bindValue(":balance", pTransactionPtr->m_balance);
            queryPtr->bindValue(":description", pTransactionPtr->m_descr);
            queryPtr->bindValue(":type", static_cast<Int32>(pTransactionPtr->m_type));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("insertTransaction memberId %1").arg(pTransactionPtr->m_memberId));
        }
        return !queryResponse.error;
    }
    //
    TransactionListResultPtr DAO::getAccountList(const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        TransactionListResultPtr pTransactionListResultPtr(new TransactionListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // member's account transaction list
            queryPtr->prepare(
                    "SELECT account.idmember, member.username, account.amount, account.date, account.description, account.balance, account.type "
                    "FROM account "
                    "INNER JOIN member ON member.idmember = account.idmember "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "ORDER BY date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // bind value
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountList fromDate %1 toDate %2 page %3 count %4").arg(fromDateLocalized).arg(toDateLocalized).arg(page).arg(count));
            pTransactionListResultPtr->m_error = 1;
        } else {
            pTransactionListResultPtr->m_list = TransactionListPtr(new TransactionList);
            while (queryResponse.query->next()) {
                Uint32 value = 0;
                TransactionPtr pTransactionPtr(new Transaction());
                pTransactionPtr->m_memberId = queryResponse.query->value(value++).toInt();
                pTransactionPtr->m_memberUsername = queryResponse.query->value(value++).toInt();
                pTransactionPtr->m_amount = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_date = queryResponse.query->value(value++).toDateTime();
                pTransactionPtr->m_date.setTimeSpec(Qt::UTC);
                pTransactionPtr->m_descr = queryResponse.query->value(value++).toString();
                pTransactionPtr->m_balance = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_type = static_cast<TransactionType>(queryResponse.query->value(value++).toUInt());
                pTransactionListResultPtr->m_list->push_back(pTransactionPtr);
            }
        }

        return pTransactionListResultPtr;
    }
    //
    Int32 DAO::getAccountListCount(const QDate &fromDate, const QDate &toDate)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // num transactions from account
            queryPtr->prepare(
                    "SELECT COUNT(*) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        Int32 count = 0.0;
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListCount fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            count = -1;
        } else if (queryResponse.query->next()) {
            count = queryResponse.query->value(0).toUInt();
        }
        return count;
    }
    //
    FloatResult DAO::getAccountListInvoicesSum(const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of invoices from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "AND type=1"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListInvoicesSum fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListDepositsSum(const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of deposits from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "AND type IN (2, 4)"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListDepositsSum fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListBankChargesSum(const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of bank charges from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE date BETWEEN :fromDate AND :toDate "
                    "AND type=3"
                    );
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListBankChargesSum fromDate %1 toDate %2").arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    Int32 DAO::getAccountListByMemberIdCount(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        Uint32 count = 0.0;
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // num transactions by memberid from account
            queryPtr->prepare(
                    "SELECT COUNT(*) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdCount memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            count = -1;
        } else if (queryResponse.query->next()) {
            count = queryResponse.query->value(0).toUInt();
        }
        return count;
    }
    //
    FloatResult DAO::getAccountListByMemberIdInvoicesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of invoices by memberid from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "AND type=1"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdInvoicesSum memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListByMemberIdDepositsSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of deposits by memberid from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "AND type IN (2, 4)"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdDepositsSum memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    FloatResult DAO::getAccountListByMemberIdBankChargesSum(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        FloatResult floatResult({0, 0.0});
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // sum of bank charger by memberid from account
            queryPtr->prepare(
                    "SELECT SUM(amount) FROM account "
                    "WHERE idmember=:memberid "
                    "AND date BETWEEN :fromDate AND :toDate "
                    "AND type=3"
                    );
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberIdBankChargesSum memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            floatResult.error = 1;
        } else if (queryResponse.query->next()) {
            floatResult.result = queryResponse.query->value(0).toFloat();
        }
        return floatResult;
    }
    //
    TransactionListResultPtr DAO::getAccountListByMemberId(Int32 memberId, const QDate &fromDate, const QDate &toDate, Uint32 page, Uint32 count)
    {
        TransactionListResultPtr pTransactionListResultPtr(new TransactionListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // member's account transaction list
            queryPtr->prepare(
                    "SELECT member.username, account.amount, account.date, account.description, account.balance, account.type "
                    "FROM account "
                    "INNER JOIN member ON member.idmember = account.idmember "
                    "WHERE account.idmember=:memberid "
                    "AND account.date BETWEEN :fromDate AND :toDate "
                    "ORDER BY account.date DESC "
                    "LIMIT :limit OFFSET :offset"
                    );
            // bind value
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":fromDate", fromDate);
            queryPtr->bindValue(":toDate", toDate);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString fromDateLocalized = locale.toString(fromDate, QLocale::NarrowFormat);
            QString toDateLocalized = locale.toString(toDate, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAccountListByMemberId memberId %1 fromDate %2 toDate %3").arg(memberId).arg(fromDateLocalized).arg(toDateLocalized));
            pTransactionListResultPtr->m_error = 1;
        } else {
            pTransactionListResultPtr->m_list = TransactionListPtr(new TransactionList);
            while (queryResponse.query->next()) {
                Uint32 value = 0;
                TransactionPtr pTransactionPtr(new Transaction());
                pTransactionPtr->m_memberId = memberId;
                pTransactionPtr->m_memberUsername = queryResponse.query->value(value++).toInt();
                pTransactionPtr->m_amount = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_date = queryResponse.query->value(value++).toDateTime();
                pTransactionPtr->m_date.setTimeSpec(Qt::UTC);
                pTransactionPtr->m_descr = queryResponse.query->value(value++).toString();
                pTransactionPtr->m_balance = queryResponse.query->value(value++).toFloat();
                pTransactionPtr->m_type = static_cast<TransactionType>(queryResponse.query->value(value++).toUInt());
                pTransactionListResultPtr->m_list->push_back(pTransactionPtr);
            }
        }
        return pTransactionListResultPtr;
    }
    //
    MemberListResultPtr DAO::getSlowPayersList()
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // slow payers
            // SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember
            // returns list of distinct idmembers and their last account date
            // First INNER JOIN on the same table (account) gets balance for the row with last (newest) account date
            // Second INNER JOIN on members table get member information
            queryPtr->prepare(
                    "SELECT ac.idmember, member.username, member.name, member.surname1, member.surname2, member.image, ac.balance, member.lastmodified, member.reg_date "
                    "FROM account ac "
                    "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                    "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                    "INNER JOIN member ON member.idmember=ac.idmember "
                    "WHERE ac.balance<0 AND member.active=:activemember"
                    );
            queryPtr->bindValue(":activemember", Member::ACTIVE);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getSlowPayersList"));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_username =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname1 =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath =  queryResponse.query->value(column++).toString();
                pMemberPtr->m_balance =  queryResponse.query->value(column++).toFloat();
                pMemberPtr->m_lastModified =  queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate =  queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        return pMemberListResultPtr;
    }
}
