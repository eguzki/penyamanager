//

#include <functional>
using namespace std::placeholders;

#include "numitemdialog.h"
#include "ui_numitemdialog.h"

namespace PenyaManager {

    //
    NumItemDialog::NumItemDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NumItemDialog)
    {
        ui->setupUi(this);
        this->connect(this->ui->toolButton_0, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 0));
        this->connect(this->ui->toolButton_1, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 1));
        this->connect(this->ui->toolButton_2, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 2));
        this->connect(this->ui->toolButton_3, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 3));
        this->connect(this->ui->toolButton_4, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 4));
        this->connect(this->ui->toolButton_5, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 5));
        this->connect(this->ui->toolButton_6, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 6));
        this->connect(this->ui->toolButton_7, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 7));
        this->connect(this->ui->toolButton_8, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 8));
        this->connect(this->ui->toolButton_9, &QToolButton::clicked, std::bind(&NumItemDialog::onButtonClick, this, 9));

        this->ui->numDisplayLabel->setText("");
    }

    //
    NumItemDialog::~NumItemDialog()
    {
        delete ui;
    }

    //
    void NumItemDialog::onButtonClick(Uint32 num)
    {
        // Check number is not too high
        if (this->ui->numDisplayLabel->text().length() > 4)
        {
            // do not allow "big" numbers
            return;
        }
        QString newCountText(this->ui->numDisplayLabel->text().append(QString::number(num)));
        this->ui->numDisplayLabel->setText(newCountText);
    }
    //
    void NumItemDialog::on_toolButton_C_clicked()
    {
        this->ui->numDisplayLabel->setText("");
    }
    //
    void NumItemDialog::on_toolButton_Done_clicked()
    {
        Uint32 count = 0;

        if (this->ui->numDisplayLabel->text().length() > 0)
        {
            count = this->ui->numDisplayLabel->text().toUInt();
        }

        done(count);
    }
}
