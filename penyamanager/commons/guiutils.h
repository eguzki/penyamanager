#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QPixmap>
#include <QMessageBox>

#include <objs/Transaction.h>
#include <objs/Member.h>
#include "DataTypes.h"

namespace PenyaManager {
    //
    class GuiUtils
    {
        public:
            // get image
            static QPixmap getImage(const QString& filename);
            //
            static void printInvoice(QVariantHash &invoiceData, Int32 memberId, Int32 invoiceId);
            //
            static void printText(const QString& html);
            //
            static void printPostalMembers(const MemberListPtr pMemberListPtr);
            //
            static void infoMessageBox(QWidget *parent, const QString &message);
            //
            static void criticalMessageBox(QWidget *parent, const QString &message);
            //
            static QMessageBox::StandardButton questionMessageBox(QWidget *parent, const QString &message);
            //
            static QString invoiceAccountDescription(const Int32 invoiceId);
            //
            static QString depositFixDescription(const Int32 depositId);
            //
            static QString depositDescription(const Int32 depositId);
            //
            static QString getTransactionDescr(const QString& descr, TransactionType type);
            //
            static QString getInvoiceDescr(const QString& descr);
            //
            static QString getDepositFixDescr(const QString& descr);

        private:
            //
            GuiUtils() {}
            //
            ~GuiUtils() {}
    };
}

#endif // GUIUTILS_H
