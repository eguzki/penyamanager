//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
    //
    ReservationListResultPtr DAO::getTableReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // table reservation list for a given moment (date and reservationtype)
            queryPtr->prepare(
                    "SELECT tablereservation.idreservation, tablereservation.idtable, member.username, member.name, member.surname1, member.surname2, tablereservation.idmember, tablereservation.guestnum, tablereservation.isadmin "
                    "FROM tablereservation "
                    "INNER JOIN member ON tablereservation.idmember=member.idmember "
                    "WHERE date=:dateid "
                    "AND reservationtype=:reservationtypeid"
                    );
            // bind value
            queryPtr->bindValue(":reservationtypeid", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":dateid", now);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString nowDateLocalized = locale.toString(now, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getTableReservation reservationType %1 now %2").arg(static_cast<Uint16>(reservationType)).arg(nowDateLocalized));
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list =  ReservationListPtr(new ReservationList);
            while (queryResponse.query->next()) {
                ReservationPtr pReservationPtr(new Reservation);
                Uint32 column = 0;
                pReservationPtr->m_reservationId = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_idItem = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberUsername = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_memberName = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname1 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_memberSurname2 = queryResponse.query->value(column++).toString();
                pReservationPtr->m_idMember = queryResponse.query->value(column++).toInt();
                pReservationPtr->m_guestNum = queryResponse.query->value(column++).toUInt();
                pReservationPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }

        return pReservationListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getLunchTableList(Uint32 page, Uint32 count)
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // lunch tables list
            queryPtr->prepare(
                    "SELECT idtable, name, guestnum "
                    "FROM lunchtables "
                    "LIMIT :limit OFFSET :offset"
                    );
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getLunchTableList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::LunchTableType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = queryResponse.query->value(2).toUInt();
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getAllLunchTableList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // lunch tables list
            queryPtr->prepare(
                    "SELECT idtable, name, guestnum "
                    "FROM lunchtables"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAllLunchTableList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::LunchTableType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = queryResponse.query->value(2).toUInt();
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListStatsPtr DAO::getLunchTableListStats()
    {
        ReservationItemListStatsPtr pReservationItemListStatsPtr(new ReservationItemListStats);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // lunchtable list
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM lunchtables"
                    );
            return queryPtr;
        };
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getLunchTableListStats"));
            pReservationItemListStatsPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats);
            pReservationItemListStatsPtr->m_listStats->m_totalNum = queryResponse.query->value(0).toUInt();
        } else {
            pReservationItemListStatsPtr->m_listStats = ReservationListStatsPtr(new ReservationListStats(0));
        }
        return pReservationItemListStatsPtr;
    }
    //
    bool DAO::makeTableReservation(const QDate &date, ReservationType reservationType, Uint16 guestNum, Int32 memberId, Int32 idTable, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert table reservation
            queryPtr->prepare(
                    "INSERT INTO tablereservation "
                    "(date, reservationtype, guestnum, idmember, idtable, isadmin) "
                    "VALUES (:date, :reservationtype, :guestnum, :idmember, :idtable, :isadmin)"
                    );
            queryPtr->bindValue(":date", date);
            queryPtr->bindValue(":reservationtype", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":guestnum", guestNum);
            queryPtr->bindValue(":idmember", memberId);
            queryPtr->bindValue(":idtable", idTable);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString dateLocalized = locale.toString(date, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("makeTableReservation reservationType %1 date %2 memberId %3").arg(static_cast<Uint16>(reservationType)).arg(dateLocalized).arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::updateTableReservation(Int32 reservationId, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update table reservation
            queryPtr->prepare(
                    "UPDATE tablereservation "
                    "SET isadmin = :isadmin "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("updateTableReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::cancelTableReservation(Int32 reservationId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // cancel table reservation
            queryPtr->prepare(
                    "DELETE FROM tablereservation "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("cancelTableReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
}
