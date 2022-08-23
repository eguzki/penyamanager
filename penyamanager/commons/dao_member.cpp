//

#include "singletons.h"
#include "dao.h"

namespace PenyaManager {
    //
    MemberResultPtr DAO::fetchMemberById(Int32 memberId)
    {
        MemberResultPtr pMemberResultPtr(new MemberResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member by id
            queryPtr->prepare(
                    "SELECT member.name, member.username, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                    "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                    "member.notes, member.pwd, member.lastlogin, member.id_card, member.card, member.type, member.inactive_start_date, member.inactive_modification_date "
                    "FROM member "
                    "WHERE member.idmember=:memberid AND member.active != :droppedmember AND member.active != :deadmember"
                    );
            // member and balance
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":droppedmember", Member::DROPPED);
            queryPtr->bindValue(":deadmember", Member::DEAD);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);

        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("fetchMemberById memberId %1").arg(memberId));
            pMemberResultPtr->m_error = 1;
        } else if (queryResponse.query->next())
        {
            MemberPtr pMemberPtr(new Member);
            Uint32 column = 0;
            pMemberPtr->m_id = memberId;
            pMemberPtr->m_name = queryResponse.query->value(column++).toString();
            pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
            pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
            pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
            pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
            pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
            pMemberPtr->m_address = queryResponse.query->value(column++).toString();
            pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
            pMemberPtr->m_town = queryResponse.query->value(column++).toString();
            pMemberPtr->m_state = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_email = queryResponse.query->value(column++).toString();
            pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
            pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
            pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
            pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
            pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
            pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
            pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
            pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
            pMemberResultPtr->m_member = pMemberPtr;
        }
        return pMemberResultPtr;
    }
    //
    MemberResultPtr DAO::fetchMemberByUsername(Int32 username)
    {
        MemberResultPtr pMemberResultPtr(new MemberResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member by username
            queryPtr->prepare(
                    "SELECT member.idmember, member.name, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                    "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, "
                    "member.notes, member.pwd, member.lastlogin, member.id_card, member.card, member.type, member.inactive_start_date, member.inactive_modification_date "
                    "FROM member "
                    "WHERE member.username=:username AND member.active != :droppedmember AND member.active != :deadmember "
                    );
            // member and balance
            queryPtr->bindValue(":username", username);
            queryPtr->bindValue(":droppedmember", Member::DROPPED);
            queryPtr->bindValue(":deadmember", Member::DEAD);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("fetchMemberByUsername member %1").arg(username));
            pMemberResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            MemberPtr pMemberPtr(new Member);
            Uint32 column = 0;
            pMemberPtr->m_id = queryResponse.query->value(column++).toInt();
            pMemberPtr->m_name = queryResponse.query->value(column++).toString();
            pMemberPtr->m_username = username;
            pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
            pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
            pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
            pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
            pMemberPtr->m_address = queryResponse.query->value(column++).toString();
            pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
            pMemberPtr->m_town = queryResponse.query->value(column++).toString();
            pMemberPtr->m_state = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
            pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
            pMemberPtr->m_email = queryResponse.query->value(column++).toString();
            pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
            pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
            pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
            pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
            pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
            pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
            pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
            pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
            pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
            pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
            pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
            pMemberResultPtr->m_member = pMemberPtr;
        }
        return pMemberResultPtr;
    }
    //
    MemberListStatsResultPtr DAO::getMemberListStats(bool onlyPostalSend)
    {
        MemberListStatsResultPtr pMemberListStatsResultPtr(new MemberListStatsResult);
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            if (onlyPostalSend) {
                // member list filtered stats
                queryPtr->prepare(
                        "SELECT COUNT(*) FROM member "
                        "WHERE postal_send = 1"
                        );
            } else {
                // member list stats
                queryPtr->prepare(
                        "SELECT COUNT(*) FROM member"
                        );
            }
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getMemberListStats postalSend %1").arg(onlyPostalSend));
            pMemberListStatsResultPtr->m_error = 1;
        } else if (queryResponse.query->next()) {
            pMemberListStatsResultPtr->m_stats = MemberListStatsPtr(new MemberListStats);
            pMemberListStatsResultPtr->m_stats->m_totalMembers = queryResponse.query->value(0).toUInt();
        } else {
            pMemberListStatsResultPtr->m_stats = MemberListStatsPtr(new MemberListStats(0));
        }
        return pMemberListStatsResultPtr;
    }
    //
    bool DAO::updateMember(const MemberPtr &pMemberPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update  member
            queryPtr->prepare(
                    "UPDATE member "
                    "SET username=:username, name=:name, surname1=:surname1, surname2=:surname2, image=:image, lastmodified=:lastmodified, active=:active, isAdmin=:isadmin, birth=:birth, "
                    "address=:address, zip_code=:zip_code, town=:town, state=:state, tel=:tel, tel2=:tel2, email=:email, bank_account=:bank_account, postal_send=:postal_send, "
                    "notes=:notes, id_card=:id_card, card=:card, type=:type, reg_date=:reg_date, "
                    "inactive_start_date=:inactive_start_date, inactive_modification_date=:inactive_modification_date "
                    "WHERE idmember = :memberid"
                    );
            // obligatory
            queryPtr->bindValue(":memberid", pMemberPtr->m_id);
            queryPtr->bindValue(":username", pMemberPtr->m_username);
            queryPtr->bindValue(":name", pMemberPtr->m_name);
            queryPtr->bindValue(":surname1", pMemberPtr->m_surname1);
            queryPtr->bindValue(":surname2", pMemberPtr->m_surname2);
            queryPtr->bindValue(":lastmodified", pMemberPtr->m_lastModified);
            queryPtr->bindValue(":active", pMemberPtr->m_active);
            queryPtr->bindValue(":isadmin", pMemberPtr->m_isAdmin?1:0);
            queryPtr->bindValue(":bank_account", pMemberPtr->m_bank_account);
            queryPtr->bindValue(":postal_send", pMemberPtr->m_postalSend?1:0);
            queryPtr->bindValue(":type", pMemberPtr->m_memberType);
            queryPtr->bindValue(":reg_date", pMemberPtr->m_regDate);
            // optional
            if (pMemberPtr->m_imagePath.isEmpty()) {
                queryPtr->bindValue(":image", QVariant());
            } else {
                queryPtr->bindValue(":image", pMemberPtr->m_imagePath);
            }
            if (pMemberPtr->m_birthdate.isValid()) {
                queryPtr->bindValue(":birth", pMemberPtr->m_birthdate);
            } else {
                queryPtr->bindValue(":birth", QVariant());
            }
            if (pMemberPtr->m_address.isEmpty()) {
                queryPtr->bindValue(":address", QVariant());
            } else {
                queryPtr->bindValue(":address", pMemberPtr->m_address);
            }
            if (pMemberPtr->m_zipCode.isEmpty()) {
                queryPtr->bindValue(":zip_code", QVariant());
            } else {
                queryPtr->bindValue(":zip_code", pMemberPtr->m_zipCode);
            }
            if (pMemberPtr->m_town.isEmpty()) {
                queryPtr->bindValue(":town", QVariant());
            } else {
                queryPtr->bindValue(":town", pMemberPtr->m_town);
            }
            if (pMemberPtr->m_state.isEmpty()) {
                queryPtr->bindValue(":state", QVariant());
            } else {
                queryPtr->bindValue(":state", pMemberPtr->m_state);
            }
            if (pMemberPtr->m_phone.isEmpty()) {
                queryPtr->bindValue(":tel", QVariant());
            } else {
                queryPtr->bindValue(":tel", pMemberPtr->m_phone);
            }
            if (pMemberPtr->m_phone2.isEmpty()) {
                queryPtr->bindValue(":tel2", QVariant());
            } else {
                queryPtr->bindValue(":tel2", pMemberPtr->m_phone2);
            }
            if (pMemberPtr->m_email.isEmpty()) {
                queryPtr->bindValue(":email", QVariant());
            } else {
                queryPtr->bindValue(":email", pMemberPtr->m_email);
            }
            if (pMemberPtr->m_notes.isEmpty()) {
                queryPtr->bindValue(":notes", QVariant());
            } else {
                queryPtr->bindValue(":notes", pMemberPtr->m_notes);
            }
            if (pMemberPtr->m_idCard.isEmpty()) {
                queryPtr->bindValue(":id_card", QVariant());
            } else {
                queryPtr->bindValue(":id_card", pMemberPtr->m_idCard);
            }
            if (pMemberPtr->m_cardNumber.isEmpty()) {
                queryPtr->bindValue(":card", QVariant());
            } else {
                queryPtr->bindValue(":card", pMemberPtr->m_cardNumber);
            }
            if (pMemberPtr->m_inactiveStartDate.isValid()) {
                queryPtr->bindValue(":inactive_start_date", pMemberPtr->m_inactiveStartDate);
            } else {
                queryPtr->bindValue(":inactive_start_date", QVariant());
            }
            if (pMemberPtr->m_inactiveModificationDate.isValid()) {
                queryPtr->bindValue(":inactive_modification_date", pMemberPtr->m_inactiveModificationDate);
            } else {
                queryPtr->bindValue(":inactive_modification_date", QVariant());
            }
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("updateMember memberId %1").arg(pMemberPtr->m_id));
        }
        return !queryResponse.error;
    }
    //
    Int32 DAO::createMember(const MemberPtr &pMemberPtr)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // create member
            queryPtr->prepare(
                    "INSERT INTO member "
                    "(username, name, surname1, surname2, image, lastmodified, reg_date, active, isAdmin, birth, "
                    "address, zip_code, town, state, tel, tel2, email, bank_account, postal_send, "
                    "notes, pwd, lastlogin, id_card, card, type) "
                    "VALUES (:username, :name, :surname1, :surname2, :image, :lastmodified, :reg_date, :active, :isadmin, :birth, "
                    ":address, :zip_code, :town, :state, :tel, :tel2, :email, :bank_account, :postal_send, "
                    ":notes, :pwd, :lastlogin, :id_card, :card, :type)"
                    );
            // obligatory
            queryPtr->bindValue(":username", pMemberPtr->m_username);
            queryPtr->bindValue(":name", pMemberPtr->m_name);
            queryPtr->bindValue(":surname1", pMemberPtr->m_surname1);
            queryPtr->bindValue(":surname2", pMemberPtr->m_surname2);
            queryPtr->bindValue(":lastmodified", pMemberPtr->m_lastModified);
            queryPtr->bindValue(":reg_date", pMemberPtr->m_regDate);
            queryPtr->bindValue(":active", pMemberPtr->m_active);
            queryPtr->bindValue(":isadmin", pMemberPtr->m_isAdmin?1:0);
            queryPtr->bindValue(":bank_account", pMemberPtr->m_bank_account);
            queryPtr->bindValue(":postal_send", pMemberPtr->m_postalSend?1:0);
            queryPtr->bindValue(":pwd", pMemberPtr->m_pwd);
            queryPtr->bindValue(":lastlogin", pMemberPtr->m_lastLogin);
            queryPtr->bindValue(":type", pMemberPtr->m_memberType);
            // optional
            if (pMemberPtr->m_imagePath.isEmpty()) {
                queryPtr->bindValue(":image", QVariant());
            } else {
                queryPtr->bindValue(":image", pMemberPtr->m_imagePath);
            }
            if (pMemberPtr->m_birthdate.isValid()) {
                queryPtr->bindValue(":birth", pMemberPtr->m_birthdate);
            } else {
                queryPtr->bindValue(":birth", QVariant());
            }
            if (pMemberPtr->m_address.isEmpty()) {
                queryPtr->bindValue(":address", QVariant());
            } else {
                queryPtr->bindValue(":address", pMemberPtr->m_address);
            }
            if (pMemberPtr->m_zipCode.isEmpty()) {
                queryPtr->bindValue(":zip_code", QVariant());
            } else {
                queryPtr->bindValue(":zip_code", pMemberPtr->m_zipCode);
            }
            if (pMemberPtr->m_town.isEmpty()) {
                queryPtr->bindValue(":town", QVariant());
            } else {
                queryPtr->bindValue(":town", pMemberPtr->m_town);
            }
            if (pMemberPtr->m_state.isEmpty()) {
                queryPtr->bindValue(":state", QVariant());
            } else {
                queryPtr->bindValue(":state", pMemberPtr->m_state);
            }
            if (pMemberPtr->m_phone.isEmpty()) {
                queryPtr->bindValue(":tel", QVariant());
            } else {
                queryPtr->bindValue(":tel", pMemberPtr->m_phone);
            }
            if (pMemberPtr->m_phone2.isEmpty()) {
                queryPtr->bindValue(":tel2", QVariant());
            } else {
                queryPtr->bindValue(":tel2", pMemberPtr->m_phone2);
            }
            if (pMemberPtr->m_email.isEmpty()) {
                queryPtr->bindValue(":email", QVariant());
            } else {
                queryPtr->bindValue(":email", pMemberPtr->m_email);
            }
            if (pMemberPtr->m_notes.isEmpty()) {
                queryPtr->bindValue(":notes", QVariant());
            } else {
                queryPtr->bindValue(":notes", pMemberPtr->m_notes);
            }
            if (pMemberPtr->m_idCard.isEmpty()) {
                queryPtr->bindValue(":id_card", QVariant());
            } else {
                queryPtr->bindValue(":id_card", pMemberPtr->m_idCard);
            }
            if (pMemberPtr->m_cardNumber.isEmpty()) {
                queryPtr->bindValue(":card", QVariant());
            } else {
                queryPtr->bindValue(":card", pMemberPtr->m_cardNumber);
            }
            return queryPtr;
        };

        Int32 memberId = -1;
        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("createMember memberUsername %1").arg(pMemberPtr->m_username));
        } else {
            auto lastQuery = [](){
                return QueryPtr(new QSqlQuery(kLastQueryId));
            };

            // For LAST_INSERT_ID(), the most recently generated ID is maintained in the server on a per-connection basis
            QueryResponse lastQueryResponse = exec(lastQuery);
            if (lastQueryResponse.error) {
                Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                        QString("createMember could not get last ID created in DB"));
            } else if (lastQueryResponse.query->next()) {
                memberId = lastQueryResponse.query->value(0).toUInt();
            }
        }
        return memberId;
    }
    //
    bool DAO::changeMemberPassword(Int32 memberId, const QString &pwdHash, const QDateTime &lastmodified)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update member password
            queryPtr->prepare(
                    "UPDATE member "
                    "SET pwd=:pwd, lastmodified=:lastmodified "
                    "WHERE idmember = :memberid"
                    );
            queryPtr->bindValue(":pwd", pwdHash);
            queryPtr->bindValue(":lastmodified", lastmodified);
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("changeMemberPassword memberId %1").arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    bool DAO::changeMemberLastLogin(Int32 memberId, const QDateTime &lastlogin)
    {
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // update member lastlogin date
            queryPtr->prepare(
                    "UPDATE member "
                    "SET lastlogin=:lastlogin "
                    "WHERE idmember = :memberid"
                    );
            queryPtr->bindValue(":lastlogin", lastlogin);
            queryPtr->bindValue(":memberid", memberId);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("changeMemberLastLogin memberId %1").arg(memberId));
        }
        return !queryResponse.error;
    }
    //
    BoolResult DAO::checkUsername(Int32 username)
    {
        BoolResult boolResult({0, false});

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // check username
            queryPtr->prepare(
                    "SELECT COUNT(*) "
                    "FROM member "
                    "WHERE username = :username"
                    );
            queryPtr->bindValue(":username", username);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("checkUsername username %1").arg(username));
            boolResult.error = 1;
        } else if (queryResponse.query->next()) {
            boolResult.result = queryResponse.query->value(0).toInt() != 0;
        } else {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("checkUsername username %1. Query does not return any result and should.").arg(username));
        }
        return boolResult;
    }
    //
    Int32 DAO::getLastUsername()
    {
        Uint32 lastUsername = -1;
        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Get last invoice (closed or open)
            queryPtr->prepare(
                    "SELECT username "
                    "FROM member "
                    "ORDER BY username DESC "
                    "LIMIT 1"
                    );
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb, QString("getLastUsername"));
        } else if (queryResponse.query->next())
        {
            lastUsername = queryResponse.query->value(0).toInt();;
        }
        return lastUsername;
    }
    //
    bool DAO::renewInactiveMember(Int32 memberId, const QDate &modificationDate)
    {
        auto query = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // Member by id
            queryPtr->prepare(
                    "UPDATE member "
                    "SET inactive_modification_date=:inactive_modification_date "
                    "WHERE idmember = :memberid"
                    );
            // bind value
            queryPtr->bindValue(":memberid", memberId);
            queryPtr->bindValue(":inactive_modification_date", modificationDate);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(query);

        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("renewInactiveMember memberId %1").arg(memberId));
        }

        return !queryResponse.error;
    }
    //
    MemberListResultPtr DAO::getOldInactiveMembers(Uint32 intervalInMonths)
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto query = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // old inactive members
            queryPtr->prepare(
                    "SELECT idmember, name, username, surname1, surname2, image, lastmodified, reg_date, active, "
                    "isAdmin, birth, address, zip_code, town, state, tel, tel2, email, "
                    "bank_account, postal_send, notes, pwd, lastlogin, id_card, card, type, "
                    "inactive_start_date, inactive_modification_date "
                    "FROM member "
                    "WHERE active=:inactivemember AND DATE_ADD(inactive_modification_date, INTERVAL :intervalInMonths MONTH) < now()"
                    );
            //
            queryPtr->bindValue(":inactivemember", Member::INACTIVE);
            queryPtr->bindValue(":intervalInMonths", intervalInMonths);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(query);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getOldInactiveMembers"));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name = queryResponse.query->value(column++).toString();
                pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_address = queryResponse.query->value(column++).toString();
                pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
                pMemberPtr->m_town = queryResponse.query->value(column++).toString();
                pMemberPtr->m_state = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_email = queryResponse.query->value(column++).toString();
                pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
                pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
                pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
                pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
                pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
                pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
                pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        return pMemberListResultPtr;
    }
    //
    MemberListResultPtr DAO::getOldDroppedMembers(Uint32 intervalInYears)
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto query = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // old dropped members
            queryPtr->prepare(
                    "SELECT idmember, name, username, surname1, surname2, image, lastmodified, reg_date, active, "
                    "isAdmin, birth, address, zip_code, town, state, tel, tel2, email, "
                    "bank_account, postal_send, notes, pwd, lastlogin, id_card, card, type, "
                    "inactive_start_date, inactive_modification_date "
                    "FROM member "
                    "WHERE active=:droppedmember AND DATE_ADD(lastmodified, INTERVAL :intervalInYears YEAR) < now()"
                    );
            //
            queryPtr->bindValue(":droppedmember", Member::DROPPED);
            queryPtr->bindValue(":intervalInYears", intervalInYears);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(query);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getOldDroppedMembers"));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name = queryResponse.query->value(column++).toString();
                pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_address = queryResponse.query->value(column++).toString();
                pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
                pMemberPtr->m_town = queryResponse.query->value(column++).toString();
                pMemberPtr->m_state = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_email = queryResponse.query->value(column++).toString();
                pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
                pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
                pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
                pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
                pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
                pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
                pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        return pMemberListResultPtr;
    }
    //
    MemberListResultPtr DAO::getMemberList(bool onlyPostalSend, Uint32 page, Uint32 count)
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto createQuery = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            if (onlyPostalSend) {
                // member filtered list
                queryPtr->prepare(
                        "SELECT member.idmember, member.username, member.name, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                        "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, member.id_card, member.card, member.type, "
                        "member.notes, member.inactive_start_date, member.inactive_modification_date, ac.balance "
                        "FROM account ac "
                        "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                        "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                        "INNER JOIN member ON member.idmember=ac.idmember "
                        "WHERE member.postal_send = 1 AND member.active != :droppedmember AND member.active != :deadmember "
                        "ORDER BY member.surname1 ASC "
                        "LIMIT :limit OFFSET :offset"
                        );
            } else {
                // member list
                queryPtr->prepare(
                        "SELECT member.idmember, member.username, member.name, member.surname1, member.surname2, member.image, member.lastmodified, member.reg_date, member.active, member.isAdmin, member.birth, "
                        "member.address, member.zip_code, member.town, member.state, member.tel, member.tel2, member.email, member.bank_account, member.postal_send, member.id_card, member.card, member.type, "
                        "member.notes, member.inactive_start_date, member.inactive_modification_date, ac.balance "
                        "FROM account ac "
                        "INNER JOIN (SELECT account.idmember, MAX(account.date) AS MaxDate FROM account GROUP BY account.idmember) groupedAccount "
                        "ON ac.idmember = groupedAccount.idmember AND ac.date=groupedAccount.MaxDate "
                        "INNER JOIN member ON member.idmember=ac.idmember "
                        "WHERE member.active != :droppedmember AND member.active != :deadmember "
                        "ORDER BY member.surname1 ASC "
                        "LIMIT :limit OFFSET :offset"
                        );
            }
            queryPtr->bindValue(":droppedmember", Member::DROPPED);
            queryPtr->bindValue(":deadmember", Member::DEAD);
            queryPtr->bindValue(":limit", count);
            queryPtr->bindValue(":offset", page * count);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(createQuery);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getMemberList postalSend %1 page %2 count %3").arg(onlyPostalSend).arg(page).arg(count));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                Uint32 column = 0;
                MemberPtr pMemberPtr(new Member);
                pMemberPtr->m_id = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_address = queryResponse.query->value(column++).toString();
                pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
                pMemberPtr->m_town = queryResponse.query->value(column++).toString();
                pMemberPtr->m_state = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_email = queryResponse.query->value(column++).toString();
                pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
                pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
                pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
                pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
                pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
                pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_balance = queryResponse.query->value(column++).toFloat();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }

        return pMemberListResultPtr;
    }
    //
    MemberListResultPtr DAO::getYoungMembersOlderThan(Uint32 minYearsOld)
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto query = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // old dropped members
            queryPtr->prepare(
                    "SELECT idmember, name, username, surname1, surname2, image, lastmodified, reg_date, active, "
                    "isAdmin, birth, address, zip_code, town, state, tel, tel2, email, "
                    "bank_account, postal_send, notes, pwd, lastlogin, id_card, card, type, "
                    "inactive_start_date, inactive_modification_date "
                    "FROM member "
                    "WHERE member.active!=:droppedmember AND member.active!=:deadmember "
                    "AND type=:youngtype "
                    "AND DATE_ADD(birth, INTERVAL :minYearsOld YEAR) < now()"
                    );
            //
            queryPtr->bindValue(":droppedmember", Member::DROPPED);
            queryPtr->bindValue(":deadmember", Member::DEAD);
            queryPtr->bindValue(":youngtype", Member::YOUNG);
            queryPtr->bindValue(":minYearsOld", minYearsOld);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(query);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getYoungMembersOlderThan"));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name = queryResponse.query->value(column++).toString();
                pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_address = queryResponse.query->value(column++).toString();
                pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
                pMemberPtr->m_town = queryResponse.query->value(column++).toString();
                pMemberPtr->m_state = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_email = queryResponse.query->value(column++).toString();
                pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
                pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
                pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
                pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
                pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
                pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
                pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        return pMemberListResultPtr;
    }
    //
    MemberListResultPtr DAO::getKidMembersOlderThan(Uint32 minYearsOld)
    {
        MemberListResultPtr pMemberListResultPtr(new MemberListResult);

        auto query = [=](){
            QueryPtr queryPtr(new QSqlQuery);
            // old dropped members
            queryPtr->prepare(
                    "SELECT idmember, name, username, surname1, surname2, image, lastmodified, reg_date, active, "
                    "isAdmin, birth, address, zip_code, town, state, tel, tel2, email, "
                    "bank_account, postal_send, notes, pwd, lastlogin, id_card, card, type, "
                    "inactive_start_date, inactive_modification_date "
                    "FROM member "
                    "WHERE member.active!=:droppedmember AND member.active!=:deadmember "
                    "AND type=:kidtype "
                    "AND DATE_ADD(birth, INTERVAL :minYearsOld YEAR) < now()"
                    );
            //
            queryPtr->bindValue(":droppedmember", Member::DROPPED);
            queryPtr->bindValue(":deadmember", Member::DEAD);
            queryPtr->bindValue(":kidtype", Member::KID);
            queryPtr->bindValue(":minYearsOld", minYearsOld);
            return queryPtr;
        };

        // run query
        QueryResponse queryResponse = exec(query);
        if (queryResponse.error) {
            Singletons::m_pLogger->Error(Constants::kNoUserId, PenyaManager::LogAction::kDb,
                    QString("getYoungMembersOlderThan"));
            pMemberListResultPtr->m_error = 1;
        } else {
            pMemberListResultPtr->m_list = MemberListPtr(new MemberList);
            while (queryResponse.query->next()) {
                MemberPtr pMemberPtr(new Member);
                Uint32 column = 0;
                pMemberPtr->m_id =  queryResponse.query->value(column++).toInt();
                pMemberPtr->m_name = queryResponse.query->value(column++).toString();
                pMemberPtr->m_username = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_surname1 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_surname2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_imagePath = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastModified = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastModified.setTimeSpec(Qt::UTC);
                pMemberPtr->m_regDate = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_regDate.setTimeSpec(Qt::UTC);
                pMemberPtr->m_active = queryResponse.query->value(column++).toInt();
                pMemberPtr->m_isAdmin = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_birthdate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_address = queryResponse.query->value(column++).toString();
                pMemberPtr->m_zipCode = queryResponse.query->value(column++).toString();
                pMemberPtr->m_town = queryResponse.query->value(column++).toString();
                pMemberPtr->m_state = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone = queryResponse.query->value(column++).toString();
                pMemberPtr->m_phone2 = queryResponse.query->value(column++).toString();
                pMemberPtr->m_email = queryResponse.query->value(column++).toString();
                pMemberPtr->m_bank_account = queryResponse.query->value(column++).toString();
                pMemberPtr->m_postalSend = queryResponse.query->value(column++).toInt() == 1;
                pMemberPtr->m_notes = queryResponse.query->value(column++).toString();
                pMemberPtr->m_pwd = queryResponse.query->value(column++).toString();
                pMemberPtr->m_lastLogin = queryResponse.query->value(column++).toDateTime();
                pMemberPtr->m_lastLogin.setTimeSpec(Qt::UTC);
                pMemberPtr->m_idCard = queryResponse.query->value(column++).toString();
                pMemberPtr->m_cardNumber = queryResponse.query->value(column++).toString();
                pMemberPtr->m_memberType = queryResponse.query->value(column++).toUInt();
                pMemberPtr->m_inactiveStartDate = queryResponse.query->value(column++).toDate();
                pMemberPtr->m_inactiveModificationDate = queryResponse.query->value(column++).toDate();
                pMemberListResultPtr->m_list->push_back(pMemberPtr);
            }
        }
        return pMemberListResultPtr;
    }
}
