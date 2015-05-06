//

#include "utils.h"
#include "singletons.h"
#include "accountview.h"
#include "ui_accountview.h"

namespace PenyaManager {
    //
    AccountView::AccountView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AccountView)
    {
        ui->setupUi(this);
    }
    //
    AccountView::~AccountView()
    {
        delete ui;
    }
    //
    void AccountView::init()
    {
        //
        // Loading User profile
        //

        MemberPtr pCurrMemberPtr = Singletons::m_pCurrMember;
        fillMemberProfile(pCurrMemberPtr);

        //
        // Show
        //

        show();
    }
    //
    void AccountView::fillMemberProfile(const MemberPtr &pMemberPtr)
    {
        QString imagePath = QDir(Constants::kImageRootPath).filePath(pMemberPtr->m_imagePath);
        QPixmap memberPixmap = Utils::getImage(imagePath);
        this->ui->memberImage->setPixmap(memberPixmap);
        this->ui->memberImage->setFixedWidth(Constants::kMemberImageWidth);
        this->ui->memberImage->setFixedHeight(Constants::kMemberImageHeigth);
        this->ui->memberImage->setScaledContents(true);
        this->ui->memberNameLabel->setText(pMemberPtr->m_name + " " + pMemberPtr->m_surname);
        this->ui->memberIdInfo->setText(QString::number(pMemberPtr->m_id));
        this->ui->memberBalanceInfo->setText(QString::number(pMemberPtr->m_balance, 'f', 2));
    }
    //
    void AccountView::on_fromCalendarWidget_clicked(const QDate &date)
    {

    }
    //
    void AccountView::on_toCalendarWidget_clicked(const QDate &date)
    {

    }
    //
    void AccountView::on_backPushButton_clicked()
    {
        this->hide();
        // call main window
        IPartner* pMainWindow = Singletons::m_pParnetFinder->getPartner(Constants::kMainWindowKey);
        pMainWindow->init();
    }
}
