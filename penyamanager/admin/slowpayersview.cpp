//
#include <QFileDialog>
#include <QTextStream>

#include <objs/Member.h>
#include <commons/utils.h>
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
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
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
        // open file dialog
        // start in home dir
        Singletons::m_pDialogManager->getOpenFileName(this, tr("Open File..."), QDir::homePath(),
                tr("CSV Files (*.csv)"), QFileDialog::AnyFile,
                std::bind(&SlowPayersView::onCsvFileSelected, this, _1)
                );
        // nothing should be added here
    }
    //
    void SlowPayersView::onCsvFileSelected(const QString &fn)
    {
        if (fn.isNull()){
            return;
        }

        QString filename = Utils::addSuffix(fn, "csv");

        // fetch data
        MemberListResultPtr pMemberListResultPtr = Singletons::m_pDAO->getSlowPayersList();
        if (pMemberListResultPtr->m_error) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        QFile f(filename);
        if (!f.open( QIODevice::WriteOnly )) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Error opening %1").arg(filename), [](){});
            return;
        }
        QTextStream out(&f);
        out.setCodec("UTF-8");
        // print header
        out << tr("Name") << "," << tr("Balance") << Qt::endl;

        for (MemberList::iterator iter = pMemberListResultPtr->m_list->begin(); iter != pMemberListResultPtr->m_list->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            out << pMemberPtr->m_name << " " << pMemberPtr->m_surname1 << " " << pMemberPtr->m_surname2 << ", " << QString("%1 €").arg(pMemberPtr->m_balance, 0, 'f', 2) << Qt::endl;
        }
        f.close();
        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Successfully exported. Filename: %1").arg(filename), [](){});
        // nothing should be added here
    }
    //
    void SlowPayersView::on_resetAccountsPushButton_clicked()
    {
        // assume slow payers list is not empty (button would be disabled)
        Singletons::m_pDialogManager->questionMessageBoxTitled(this, tr("Reset accounts. Are you sure?"),
                std::bind(&SlowPayersView::onResetAccountAccepted, this, _1)
                );
    }
    //
    void SlowPayersView::onResetAccountAccepted(QMessageBox::StandardButton answerButton)
    {
        if (answerButton != QMessageBox::Yes) {
            return;
        }
        // reset accounts balance
        bool ok = Singletons::m_pServices->resetSlowPayersBalance();
        if (!ok) {
            Singletons::m_pDialogManager->criticalMessageBoxTitled(this, tr("Database error. Contact administrator"), [](){});
            return;
        }

        Singletons::m_pDialogManager->infoMessageBoxTitled(this, tr("Operation done"),
                std::bind(&SlowPayersView::onResetAccountDone, this)
                );
        // nothing should be added here
    }
    //
    void SlowPayersView::onResetAccountDone()
    {
        init();
    }
}


