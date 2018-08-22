//

#include "singletons.h"
#include "objs/Invoice.h"
#include "objs/Deposit.h"
#include "services.h"
#include "guiutils.h"

namespace PenyaManager {

    //
    Services::Services()
    {
    }
    //
    Services::~Services()
    {
    }
    //
    DepositResultPtr Services::createDeposit(const MemberPtr &pMemberPtr, Float amount)
    {
        // create deposit register info as unconfirmed
        DepositPtr pDepositPtr(new Deposit);
        pDepositPtr->m_memberId = pMemberPtr->m_id;
        // create unconfirmed deposit. Admin has to validate and process.
        pDepositPtr->m_state = DepositState::Unchecked;
        pDepositPtr->m_date = QDateTime::currentDateTimeUtc();
        pDepositPtr->m_total = amount;
        // store in ddbb
        return Singletons::m_pDAO->createDeposit(pDepositPtr);
    }
    //
    // Steps
    // Update invoice data
    // Create transaction
    // Update stock
    bool Services::closeInvoice(const InvoicePtr &pOpenInvoicePtr)
    {
        InvoicePtr pInvoicePtr(new Invoice());
        // id
        pInvoicePtr->m_id = pOpenInvoicePtr->m_id;
        // date
        pInvoicePtr->m_date = pOpenInvoicePtr->m_date;
        // memberId
        pInvoicePtr->m_memberId = pOpenInvoicePtr->m_memberId;
        // state: closed
        pInvoicePtr->m_state = InvoiceState::Closed;
        // total
        InvoiceProductItemListResultPtr pInvoiceProductItemListResultPtr = Singletons::m_pDAO->getAllInvoiceProductItems(pInvoicePtr->m_id);
        if (pInvoiceProductItemListResultPtr->m_error) {
            return false;
        }
        // total invoice could be calculated using ddbb query with
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            // use current product price
            Float totalPrice = pInvoiceProductItemPtr->m_currentPricePerUnit * pInvoiceProductItemPtr->m_count;
            totalInvoice += totalPrice;
            // close invoice product price
            bool ok = Singletons::m_pDAO->updateProductInvoice(pInvoicePtr->m_id, pInvoiceProductItemPtr->m_productId, pInvoiceProductItemPtr->m_count, pInvoiceProductItemPtr->m_currentPricePerUnit);
            if (!ok) {
                return false;
            }
        }
        pInvoicePtr->m_total = totalInvoice;
        // invoice lastModified date: now
        pInvoicePtr->m_lastModified = QDateTime::currentDateTimeUtc();

        // close invoice reg in db
        bool ok = Singletons::m_pDAO->updateInvoice(pInvoicePtr);
        if (!ok) {
            return false;
        }

        // create account register info
        QString description = GuiUtils::invoiceAccountDescription(pInvoicePtr->m_id);
        // account transaction has totalInvoice as negative amount
        ok = this->createAccountTransaction(pInvoicePtr->m_memberId, -totalInvoice, description, TransactionType::Invoice);
        if (!ok) {
            return false;
        }
        // Update stock
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListResultPtr->m_list->begin(); iter != pInvoiceProductItemListResultPtr->m_list->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            // count as negative addition
            ok = Singletons::m_pDAO->updateStock(pInvoiceProductItemPtr->m_productId,-pInvoiceProductItemPtr->m_count);
            if (!ok) {
                return false;
            }
        }
        return true;
    }
    //
    bool Services::createAccountTransaction(Int32 memberId, Float amount, const QString &description, TransactionType type)
    {
        // get member last balance information and add new transaction
        TransactionResultPtr pLastAccountInfoResultPtr = Singletons::m_pDAO->getLastAccountInfo(memberId);
        if (pLastAccountInfoResultPtr->m_error) {
            return false;
        }

        // in case there is not previous account info
        Float lastBalance = 0.0;
        if (pLastAccountInfoResultPtr->m_transaction) {
            lastBalance = pLastAccountInfoResultPtr->m_transaction->m_balance;
        }

        TransactionPtr pNewTransaction(new Transaction);
        pNewTransaction->m_type = type;
        pNewTransaction->m_memberId = memberId;
        pNewTransaction->m_amount = amount;
        pNewTransaction->m_date = QDateTime::currentDateTimeUtc();
        pNewTransaction->m_balance = lastBalance + amount;
        pNewTransaction->m_descr = description;
        // update account balance info
        return Singletons::m_pDAO->insertTransaction(pNewTransaction);
    }
    //
    bool Services::resetSlowPayersBalance()
    {
        // fetch data
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getSlowPayersList();
        if (pMemberListResultPtr->m_error) {
            return false;
        }
        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            bool ok = createAccountTransaction(pMemberPtr->m_id, -pMemberPtr->m_balance, QString(""), TransactionType::AccountPayment);
            if (!ok) {
                return false;
            }
            Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kService,
                    QString("ResetSlowPayer member ID %1 amount %2€").arg(pMemberPtr->m_id).arg(-pMemberPtr->m_balance, 0, 'f', 2));
        }
        return true;
    }
    //
    TransactionListStatsResultPtr Services::getAccountListStats(const QDate &fromDate, const QDate &toDate)
    {
        TransactionListStatsResultPtr pTransactionListStatsResultPtr(new TransactionListStatsResult);
        // query to get total num of transactions
        Int32 totalNumTransactions = Singletons::m_pDAO->getAccountListCount(fromDate, toDate);
        if (totalNumTransactions < 0) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        // query to get sum of invoices
        FloatResult totalInvoices = Singletons::m_pDAO->getAccountListInvoicesSum(fromDate, toDate);
        if (totalInvoices.error) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        // query to get sum of deposits
        FloatResult totalDeposits = Singletons::m_pDAO->getAccountListDepositsSum(fromDate, toDate);
        if (totalDeposits.error) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        // query to get sum of bank charges
        FloatResult totalBankCharges = Singletons::m_pDAO->getAccountListBankChargesSum(fromDate, toDate);
        if (totalBankCharges.error) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        pTransactionListStatsResultPtr->m_listStats = TransactionListStatsPtr(new TransactionListStats);
        pTransactionListStatsResultPtr->m_listStats->m_totalBankCharges = totalBankCharges.result;
        pTransactionListStatsResultPtr->m_listStats->m_totalNumTransactions = totalNumTransactions;
        pTransactionListStatsResultPtr->m_listStats->m_totalInvoices = totalInvoices.result;
        pTransactionListStatsResultPtr->m_listStats->m_totalDeposits = totalDeposits.result;
        return pTransactionListStatsResultPtr;
    }
    //
    TransactionListStatsResultPtr Services::getAccountListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        TransactionListStatsResultPtr pTransactionListStatsResultPtr(new TransactionListStatsResult);
        // query to get total num of transactions
        Int32 totalNumTransactions = Singletons::m_pDAO->getAccountListByMemberIdCount(memberId, fromDate, toDate);
        if (totalNumTransactions < 0) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        // query to get sum of invoices
        FloatResult totalInvoices = Singletons::m_pDAO->getAccountListByMemberIdInvoicesSum(memberId, fromDate, toDate);
        if (totalInvoices.error) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        // query to get sum of deposits
        FloatResult totalDeposits = Singletons::m_pDAO->getAccountListByMemberIdDepositsSum(memberId, fromDate, toDate);
        if (totalDeposits.error) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }
        // query to get sum of bank charges
        FloatResult totalBankCharges = Singletons::m_pDAO->getAccountListByMemberIdBankChargesSum(memberId, fromDate, toDate);
        if (totalBankCharges.error) {
            pTransactionListStatsResultPtr->m_error = 1;
            return pTransactionListStatsResultPtr;
        }

        pTransactionListStatsResultPtr->m_listStats = TransactionListStatsPtr(new TransactionListStats);
        pTransactionListStatsResultPtr->m_listStats->m_totalNumTransactions = totalNumTransactions;
        pTransactionListStatsResultPtr->m_listStats->m_totalInvoices = totalInvoices.result;
        pTransactionListStatsResultPtr->m_listStats->m_totalDeposits = totalDeposits.result;
        pTransactionListStatsResultPtr->m_listStats->m_totalBankCharges = totalBankCharges.result;
        return pTransactionListStatsResultPtr;
    }
    //
    bool Services::updateInvoiceInfo(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        // update product invoice and invoice's last modification date
        // invoice is open, price will be 0
        bool ok = Singletons::m_pDAO->updateProductInvoice(invoiceId, productId, count, 0.0);
        if (!ok) {
            return false;
        }
        return Singletons::m_pDAO->updateInvoiceLastModDate(invoiceId, QDateTime::currentDateTimeUtc());
    }
    //
    bool Services::removeInvoiceProductId(Int32 invoiceId, Int32 productId)
    {
        // update product invoice and invoice's last modification date
        bool ok = Singletons::m_pDAO->removeProductInvoice(invoiceId, productId);
        if (!ok) {
            return false;
        }
        // check if there are more products
        InvoiceProductItemStatsResultPtr invoiceProductItemStatsResultPtr = Singletons::m_pDAO->getInvoiceProductItemsStats(invoiceId);
        if (invoiceProductItemStatsResultPtr->m_error) {
            return false;
        } else if (invoiceProductItemStatsResultPtr->m_stats->m_totalProducts > 0) {
            ok = Singletons::m_pDAO->updateInvoiceLastModDate(invoiceId, QDateTime::currentDateTimeUtc());
        } else {
            // no products left, remove invoice
            ok = Singletons::m_pDAO->deleteInvoice(invoiceId);
        }
        return ok;
    }
    // Returns boolean with database operation error and numRowsAffected
    // it is assumed invoice is open
    BoolResult Services::increaseProductInvoice(Int32 invoiceId, Int32 productId, Int32 count)
    {
        BoolResult boolResult({0, false});
        Int32 numRowsAffected = Singletons::m_pDAO->increaseProductInvoice(invoiceId, productId, count);
        boolResult.result = numRowsAffected;
        if (numRowsAffected < 0) {
            return boolResult;
        } else if (numRowsAffected == 0) {
            // product item does not exit, create it on invoice
            // invoice is open, price will be 0
            boolResult.error = !Singletons::m_pDAO->updateProductInvoice(invoiceId, productId, count, 0.0);
            if (boolResult.error) {
                return boolResult;
            }
        }
        boolResult.error = !Singletons::m_pDAO->updateInvoiceLastModDate(invoiceId, QDateTime::currentDateTimeUtc());
        return boolResult;
    }
    //
    bool Services::cleanOutdatedInvoices()
    {
        InvoiceListResultPtr pActiveInvoiceList = Singletons::m_pDAO->getActiveInvoiceList();
        if (pActiveInvoiceList->m_error) {
            return false;
        }

        QDateTime now = QDateTime::currentDateTimeUtc();
        for (InvoiceList::iterator iter = pActiveInvoiceList->m_list->begin(); iter != pActiveInvoiceList->m_list->end(); ++iter) {
            InvoicePtr pInvoicePtr = *iter;
            // check modified
            if (pInvoicePtr->m_lastModified.secsTo(now) > 60*60 * Constants::kOpenInvoiceTimeoutH) {
                // invoice timed out
                // close it
                bool ok = closeInvoice(pInvoicePtr);
                if (!ok) {
                    return false;
                }
                Singletons::m_pLogger->Info(Constants::kSystemUserId, PenyaManager::LogAction::kService,
                        QString("[Invoice][OUTDATED] User %1 Invoice ID %2").arg(pInvoicePtr->m_memberId).arg(pInvoicePtr->m_id));
                // leave returnInvoicePtr empty
            }
        }
        return !pActiveInvoiceList->m_error;
    }
    //
    MemberResultPtr Services::getMemberById(Int32 memberId)
    {
        MemberResultPtr pResult = Singletons::m_pDAO->fetchMemberById(memberId);
        if (pResult->m_error) {
            return pResult;
        }
        if (pResult->m_member) {
            FloatBoolPairResultPtr pair = Singletons::m_pDAO->getAccountBalance(memberId);
            if (pair->m_error) {
                pResult->m_error = 1;
                return pResult;
            }

            if (pair->m_pair.b) {
                // exists
                pResult->m_member->m_balance = pair->m_pair.f;
            }
        }

        return pResult;
    }
    //
    MemberResultPtr Services::getMemberByUsername(Int32 username)
    {
        MemberResultPtr pResult = Singletons::m_pDAO->fetchMemberByUsername(username);
        if (pResult->m_error) {
            return pResult;
        }

        if (pResult->m_member) {
            FloatBoolPairResultPtr pair = Singletons::m_pDAO->getAccountBalance(pResult->m_member->m_id);
            if (pair->m_error) {
                pResult->m_error = 1;
                return pResult;
            }

            if (pair->m_pair.b) {
                // exists
                pResult->m_member->m_balance = pair->m_pair.f;
            }
        }
        return pResult;
    }
}

