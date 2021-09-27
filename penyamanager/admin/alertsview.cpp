//
#include <QFileDialog>
#include <QTextStream>

#include <objs/Member.h>
#include <commons/utils.h>
#include <commons/singletons.h>
#include "alertsview.h"
#include "ui_alertsview.h"

namespace PenyaManager {
    //
    AlertsView::AlertsView(QWidget *parent) :
        IPartner(parent),
        ui(new Ui::AlertsView)
    {
        ui->setupUi(this);
    }
    //
    AlertsView::~AlertsView()
    {
        delete ui;
    }
    //
    void AlertsView::init()
    {
    }
    //
    void AlertsView::retranslate()
    {
        this->ui->retranslateUi(this);
    }
}
