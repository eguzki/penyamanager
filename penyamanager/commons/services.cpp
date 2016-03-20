//

#include <QsLog.h>

#include "singletons.h"
#include "objs/Invoice.h"
#include "objs/Deposit.h"
#include "services.h"

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
    DepositPtr Services::createDeposit(const MemberPtr &pMemberPtr, Float amount)
    {
        // create deposit register info as unconfirmed
        DepositPtr pDepositPtr(new Deposit);
        pDepositPtr->m_memberId = pMemberPtr->m_id;
        // create unconfirmed deposit. Admin has to validate and process.
        pDepositPtr->m_state = DepositState::Unchecked;
        pDepositPtr->m_date = QDateTime::currentDateTime();
        pDepositPtr->m_total = amount;
        // currently simple description. Maybe let user set some subject?
        pDepositPtr->m_descr = QString("deposit");

        // store in ddbb
        return Singletons::m_pDAO->createDeposit(pDepositPtr);
    }
    //
    void Services::closeInvoice(const MemberPtr &pMemberPtr, Int32 invoiceId)
    {
        InvoicePtr pInvoicePtr(new Invoice());
        // id
        pInvoicePtr->m_id = invoiceId;
        // memberId
        pInvoicePtr->m_memberId = pMemberPtr->m_id;
        // invoice date: now
        pInvoicePtr->m_date = QDateTime::currentDateTime();
        // state: closed
        pInvoicePtr->m_state = InvoiceState::Closed;
        // total
        InvoiceProductItemListPtr pInvoiceProductItemListPtr = Singletons::m_pDAO->getInvoiceProductItems(pInvoicePtr->m_id);
        Float totalInvoice = 0.0;
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            Float totalPrice = pInvoiceProductItemPtr->m_priceperunit * pInvoiceProductItemPtr->m_count;
            totalInvoice += totalPrice;
        }
        pInvoicePtr->m_total = totalInvoice;
        // invoice lastModified date: now
        pInvoicePtr->m_lastModified = QDateTime::currentDateTime();

        // update invoice data
        Singletons::m_pDAO->updateInvoice(pInvoicePtr);

        // create account register info
        QString description = QString("invoice ref %1").arg(invoiceId);
        // account transaction has totalInvoice as negative amount
        this->createAccountTransaction(pMemberPtr->m_id, -totalInvoice, description, TransactionType::Invoice);
        // Update stock
        for (InvoiceProductItemList::iterator iter = pInvoiceProductItemListPtr->begin(); iter != pInvoiceProductItemListPtr->end(); ++iter)
        {
            InvoiceProductItemPtr pInvoiceProductItemPtr = *iter;
            // count as negative addition
            Singletons::m_pDAO->updateStock(pInvoiceProductItemPtr->m_productId,-pInvoiceProductItemPtr->m_count);
        }
    }
    //
    void Services::createAccountTransaction(Int32 memberId, Float amount, const QString &description, TransactionType type)
    {
        // get member last balance information and add new transaction
        TransactionPtr pLastAccountInfo = Singletons::m_pDAO->getLastAccountInfo(memberId);

        // in case there is not previous account info
        Float lastBalance = 0.0;
        if (pLastAccountInfo) {
            lastBalance = pLastAccountInfo->m_balance;
        }

        TransactionPtr pNewTransaction(new Transaction);
        pNewTransaction->m_type = type;
        pNewTransaction->m_memberId = memberId;
        pNewTransaction->m_amount = amount;
        pNewTransaction->m_date = QDateTime::currentDateTime();
        pNewTransaction->m_balance = lastBalance + amount;
        pNewTransaction->m_descr = description;
        // update account balance info
        Singletons::m_pDAO->insertTransaction(pNewTransaction);
    }
    //
    void Services::resetSlowPayersBalance()
    {
        // fetch data
        MemberListPtr pMemberListPtr = Singletons::m_pDAO->getSlowPayersList();
        for (MemberList::iterator iter = pMemberListPtr->begin(); iter != pMemberListPtr->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            createAccountTransaction(pMemberPtr->m_id, -pMemberPtr->m_balance, "reset account", TransactionType::AccountPayment);
            QLOG_INFO() << QString("[ResetSlowPayer] member ID %1 amount %2€").arg(pMemberPtr->m_id).arg(-pMemberPtr->m_balance, 0, 'f', 2);
        }
    }
    //
    TransactionListStatsPtr Services::getAccountListStats(const QDate &fromDate, const QDate &toDate)
    {
        TransactionListStatsPtr pTransactionListStatsPtr(new TransactionListStats);
        // query to get total num of transactions
        pTransactionListStatsPtr->m_totalNumTransactions = Singletons::m_pDAO->getAccountListCount(fromDate, toDate);
        // query to get sum of invoices
        pTransactionListStatsPtr->m_totalInvoices = Singletons::m_pDAO->getAccountListInvoicesSum(fromDate, toDate);
        // query to get sum of deposits
        pTransactionListStatsPtr->m_totalDeposits = Singletons::m_pDAO->getAccountListDepositsSum(fromDate, toDate);
        // query to get sum of bank charges
        pTransactionListStatsPtr->m_totalBankCharges = Singletons::m_pDAO->getAccountListBankChargesSum(fromDate, toDate);
        return pTransactionListStatsPtr;
    }
    //
    TransactionListStatsPtr Services::getAccountListByMemberIdStats(Int32 memberId, const QDate &fromDate, const QDate &toDate)
    {
        TransactionListStatsPtr pTransactionListStatsPtr(new TransactionListStats);
        // query to get total num of transactions
        pTransactionListStatsPtr->m_totalNumTransactions = Singletons::m_pDAO->getAccountListByMemberIdCount(memberId, fromDate, toDate);
        // query to get sum of invoices
        pTransactionListStatsPtr->m_totalInvoices = Singletons::m_pDAO->getAccountListByMemberIdInvoicesSum(memberId, fromDate, toDate);
        // query to get sum of deposits
        pTransactionListStatsPtr->m_totalDeposits = Singletons::m_pDAO->getAccountListByMemberIdDepositsSum(memberId, fromDate, toDate);
        // query to get sum of bank charges
        pTransactionListStatsPtr->m_totalBankCharges = Singletons::m_pDAO->getAccountListByMemberIdBankChargesSum(memberId, fromDate, toDate);
        return pTransactionListStatsPtr;
    }
    //
    void Services::updateInvoiceInfo(Int32 invoiceId, Int32 productId, Uint32 count)
    {
        // update product invoice and invoice's last modification date
        Singletons::m_pDAO->updateProductInvoice(invoiceId, productId, count);
        Singletons::m_pDAO->updateInvoiceLastModDate(invoiceId, QDateTime::currentDateTime());
    }
    //
    void Services::removeInvoiceProductId(Int32 invoiceId, Int32 productId)
    {
        // update product invoice and invoice's last modification date
        Singletons::m_pDAO->removeProductInvoice(invoiceId, productId);
        // check if there are more products
        Uint32 numProducts = Singletons::m_pDAO->countInvoiceProductItems(invoiceId);
        if (numProducts) {
            Singletons::m_pDAO->updateInvoiceLastModDate(invoiceId, QDateTime::currentDateTime());
        } else {
            // no products left, remove invoice
            Singletons::m_pDAO->deleteInvoice(invoiceId);
        }
    }
    //
    void Services::increaseProductInvoice(Int32 invoiceId, Int32 productId, Int32 count)
    {
        Uint32 numRowsAffected = Singletons::m_pDAO->increaseProductInvoice(invoiceId, productId, count);
        if (numRowsAffected <= 0) {
            // product item does not exit, create it on invoice
            Singletons::m_pDAO->updateProductInvoice(invoiceId, productId, count);
        }
        Singletons::m_pDAO->updateInvoiceLastModDate(invoiceId, QDateTime::currentDateTime());
    }
}
