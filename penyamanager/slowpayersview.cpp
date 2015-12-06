//

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "objs/Member.h"
#include "singletons.h"
#include "slowpayersview.h"
#include "ui_slowpayersview.h"

namespace PenyaManager {
    //
    SlowPayersView::SlowPayersView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::SlowPayersView)
    {
        ui->setupUi(this);
        initializeTable();
    }
    //
    SlowPayersView::~SlowPayersView()
    {
        delete ui;
    }
    //
    void SlowPayersView::init()
    {
        fillSlowPayersData();

        //
        // Show
        //

        show();
    }
    //
    void SlowPayersView::initializeTable()
    {
        // table Header
        this->ui->slowPayersTableWidget->setColumnCount(3);
        translateTable();
        this->ui->slowPayersTableWidget->setColumnWidth(0, 100);
        this->ui->slowPayersTableWidget->setColumnWidth(1, 400);
        this->ui->slowPayersTableWidget->setColumnWidth(2, 200);
    }
    //
    void SlowPayersView::translateTable()
    {
        // table reservation table Header
        QStringList headers;
        headers.append(tr("Member Id"));
        headers.append(tr("Name"));
        headers.append(tr("Balance"));
        this->ui->slowPayersTableWidget->setHorizontalHeaderLabels(headers);
    }
    //
    void SlowPayersView::retranslate()
    {
        this->ui->retranslateUi(this);
        translateTable();
    }
    //
    void SlowPayersView::fillSlowPayersData()
    {
        // fetch data
        MemberListPtr pMemberListPtr = Singletons::m_pDAO->getSlowPayersList();
        if (pMemberListPtr->size() > 0) {
            this->ui->csvPushButton->setEnabled(true);
            this->ui->printPushButton->setEnabled(true);
            this->ui->resetAccountsPushButton->setEnabled(true);
        } else {
            this->ui->csvPushButton->setEnabled(false);
            this->ui->printPushButton->setEnabled(false);
            this->ui->resetAccountsPushButton->setEnabled(false);
        }

        // table
        this->ui->slowPayersTableWidget->setRowCount(pMemberListPtr->size());

        // invoice table reset
        this->ui->slowPayersTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (MemberList::iterator iter = pMemberListPtr->begin(); iter != pMemberListPtr->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            this->ui->slowPayersTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pMemberPtr->m_id)));
            this->ui->slowPayersTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pMemberPtr->m_name + " " + pMemberPtr->m_surname));
            this->ui->slowPayersTableWidget->setItem(rowCount, 2, new QTableWidgetItem(tr("%1 €").arg(pMemberPtr->m_balance)));
            rowCount++;
        }
    }
    //
    void SlowPayersView::on_csvPushButton_clicked()
    {
        // Assume slow payers list is not empty (buttons should be disabled)
        QString filename = QFileDialog::getSaveFileName(this, tr("Export CSV"));

        if (filename.isNull()){
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            QMessageBox::warning(this, "Unable to save file", "Error opening " + filename);
            return;
        }
        QTextStream out(&f);
        // print header
        out << tr("Name") << "," << tr("Balance") << "\n";

        // fetch data
        MemberListPtr pMemberListPtr = Singletons::m_pDAO->getSlowPayersList();
        for (MemberList::iterator iter = pMemberListPtr->begin(); iter != pMemberListPtr->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            out << pMemberPtr->m_name << " " << pMemberPtr->m_surname << ", " << tr("%1 €").arg(pMemberPtr->m_balance) << "\n";
        }
        f.close();
    }
    //
    void SlowPayersView::on_printPushButton_clicked()
    {
        // TODO

    }
    //
    void SlowPayersView::on_resetAccountsPushButton_clicked()
    {
        // assume slow payers list is not empty (button would be disabled)
        QMessageBox::StandardButton answerButton = QMessageBox::question(this, "reset accounts", "Are you sure?");
        if (answerButton == QMessageBox::Yes) {
            // reset accounts balance
            Singletons::m_pServices->resetSlowPayersBalance();
            QMessageBox::information(this, "reset accounts", "Operation done");
        } else {
            QMessageBox::information(this, "reset accounts", "Operation cancelled");
        }
        fillSlowPayersData();
    }
}


