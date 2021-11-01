//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
    //
    ReservationListResultPtr DAO::getFireplaceReservation(ReservationType reservationType, const QDate &now)
    {
        ReservationListResultPtr pReservationListResultPtr(new ReservationListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace reservation list for a given moment (date and reservationtype)
            queryPtr->prepare(
                    "SELECT fireplacereservation.idreservation, fireplacereservation.idfireplace, member.username, member.name, member.surname1, member.surname2, fireplacereservation.idmember, fireplacereservation.isadmin "
                    "FROM fireplacereservation "
                    "INNER JOIN member ON fireplacereservation.idmember=member.idmember "
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
                    QString("getFireplaceReservation reservationType %1 now %2").arg(static_cast<Uint16>(reservationType)).arg(nowDateLocalized));
            pReservationListResultPtr->m_error = -1;
        } else {
            pReservationListResultPtr->m_list = ReservationListPtr(new ReservationList);
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
                pReservationPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pReservationPtr->m_guestNum = 0;
                pReservationListResultPtr->m_list->push_back(pReservationPtr);
            }
        }
        return pReservationListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getFireplaceList(Uint32 page, Uint32 count)
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT idfireplace, name "
                    "FROM fireplaces "
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
                    QString("getFireplaceList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::FireplaceType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListResultPtr DAO::getAllFireplaceList()
    {
        ReservationItemListResultPtr pReservationItemListResultPtr(new ReservationItemListResult);

        auto createQuery = [](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT idfireplace, name "
                    "FROM fireplaces"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getAllFireplaceList"));
            pReservationItemListResultPtr->m_error = 1;
        } else {
            pReservationItemListResultPtr->m_list = ReservationItemListPtr(new ReservationItemList);
            while (queryResponse.query->next()) {
                ReservationItemPtr pReservationItemPtr(new ReservationItem);
                pReservationItemPtr->m_itemType = ReservationItemType::FireplaceType;
                pReservationItemPtr->m_idItem = queryResponse.query->value(0).toInt();
                pReservationItemPtr->m_itemName = queryResponse.query->value(1).toString();
                pReservationItemPtr->m_guestNum = 0;
                pReservationItemListResultPtr->m_list->push_back(pReservationItemPtr);
            }
        }
        return pReservationItemListResultPtr;
    }
    //
    ReservationItemListStatsPtr DAO::getFireplaceListStats()
    {
        ReservationItemListStatsPtr pReservationItemListStatsPtr(new ReservationItemListStats);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // fireplace list
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM fireplaces"
                    );
            return queryPtr;
        };
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getFireplaceListStats"));
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
    bool DAO::updateFireplaceReservation(Int32 reservationId, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update fireplace reservation
            queryPtr->prepare(
                    "UPDATE fireplacereservation "
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
                    QString("updateFireplaceReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::makeFireplaceReservation(const QDate &date, ReservationType reservationType, Int32 memberId, Int32 idFireplace, bool isAdmin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // insert fireplace reservation
            queryPtr->prepare(
                    "INSERT INTO fireplacereservation "
                    "(date, reservationtype, idmember, idfireplace, isadmin) "
                    "VALUES (:date, :reservationtype, :idmember, :idfireplace, :isadmin)"
                    );
            queryPtr->bindValue(":date", date);
            queryPtr->bindValue(":reservationtype", static_cast<Uint16>(reservationType));
            queryPtr->bindValue(":idmember", memberId);
            queryPtr->bindValue(":idfireplace", idFireplace);
            queryPtr->bindValue(":isadmin", (isAdmin)?(1):(0));
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            QLocale locale;
            QString dateLocalized = locale.toString(date, QLocale::NarrowFormat);
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("makeFireplaceReservation reservationType %1 date %2 memberId %3").arg(static_cast<Uint16>(reservationType)).arg(dateLocalized).arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::cancelFireplaceReservation(Int32 reservationId)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // cancel fireplace reservation
            queryPtr->prepare(
                    "DELETE FROM fireplacereservation "
                    "WHERE idreservation = :idreservation"
                    );
            queryPtr->bindValue(":idreservation", reservationId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("cancelFireplaceReservation reservationId %1").arg(reservationId));
        }
        return !queryResponse.error;
    }
}
