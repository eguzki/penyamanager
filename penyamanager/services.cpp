//

#include "singletons.h"
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
    void Services::createDeposit(const MemberPtr &pMemberPtr, Float amount)
    {
        // create account register info
        // currently simple description. Maybe let user set some subject?
        QString description("deposit");
        this->createAccountTransaction(pMemberPtr->m_id, amount, description, TransactionType::Deposit);
    }
    //
    void Services::closeInvoice(const MemberPtr &pMemberPtr, Int32 invoiceId, PaymentType payment)
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
        // payment
        pInvoicePtr->m_payment = payment;

        // update invoice data
        Singletons::m_pDAO->updateInvoice(pInvoicePtr);

        if (payment == PaymentType::Account)
        {
            // create account register info
            QString description = QString("invoice ref %1").arg(invoiceId);
            // account transaction has totalInvoice as negative amount
            this->createAccountTransaction(pMemberPtr->m_id, -totalInvoice, description, TransactionType::Invoice);
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
}
