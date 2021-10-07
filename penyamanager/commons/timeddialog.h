#ifndef TIMEDDIALOG_H
#define TIMEDDIALOG_H

#include <QDialog>
#include <QTimer>

namespace PenyaManager {
    //
    class TimedDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit TimedDialog(QWidget *parent, QTimer *pInactivityTimer);
    };
}

#endif // TIMEDDIALOG_H
