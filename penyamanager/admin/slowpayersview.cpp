//

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <objs/Member.h>
#include <commons/singletons.h>
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
        headers.append(tr("Username"));
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
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getSlowPayersList();

        if (pMemberListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        if (pMemberListResultPtr->m_list->size() > 0) {
            this->ui->csvPushButton->setEnabled(true);
            this->ui->resetAccountsPushButton->setEnabled(true);
        } else {
            this->ui->csvPushButton->setEnabled(false);
            this->ui->resetAccountsPushButton->setEnabled(false);
        }

        // table
        this->ui->slowPayersTableWidget->setRowCount(pMemberListResultPtr->m_list->size());

        // invoice table reset
        this->ui->slowPayersTableWidget->clearContents();

        // fill data
        Uint32 rowCount = 0;
        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            this->ui->slowPayersTableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(pMemberPtr->m_username)));
            this->ui->slowPayersTableWidget->setItem(rowCount, 1, new QTableWidgetItem(pMemberPtr->m_name + " " + pMemberPtr->m_surname1 + " " + pMemberPtr->m_surname2));
            this->ui->slowPayersTableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString("%1 €").arg(pMemberPtr->m_balance, 0, 'f', 2)));
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

        // fetch data
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getSlowPayersList();
        if (pMemberListResultPtr->m_error) {
            QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            QMessageBox::warning(this, tr("Unable to save file"), tr("Error opening %1").arg(filename));
            return;
        }
        QTextStream out(&f);
        // print header
        out << tr("Name") << "," << tr("Balance") << endl;

        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            out << pMemberPtr->m_name << " " << pMemberPtr->m_surname1 << " " << pMemberPtr->m_surname2 << ", " << QString("%1 €").arg(pMemberPtr->m_balance, 0, 'f', 2) << endl;
        }
        f.close();
        QMessageBox::information(this, tr("CSV export"), tr("Successfully exported. Filename: %1").arg(filename));
    }
    //
    void SlowPayersView::on_resetAccountsPushButton_clicked()
    {
        // assume slow payers list is not empty (button would be disabled)
        QMessageBox::StandardButton answerButton = QMessageBox::question(this, tr("reset accounts"), tr("Are you sure?"));
        if (answerButton == QMessageBox::Yes) {
            // reset accounts balance
            bool ok = Singletons::m_pServices->resetSlowPayersBalance();
            if (ok) {
                QMessageBox::information(this, tr("reset accounts"), tr("Operation done"));
            } else {
                QMessageBox::critical(this, tr("Database error"), tr("Contact administrator"));
            }
        } else {
            QMessageBox::information(this, tr("reset accounts"), tr("Operation cancelled"));
        }
        init();
    }
}


