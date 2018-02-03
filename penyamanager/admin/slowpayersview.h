#ifndef SLOWPAYERSVIEW_H
#define SLOWPAYERSVIEW_H

#include <QWidget>
#include <QMessageBox>

#include <commons/IPartner.h>

namespace Ui {
class SlowPayersView;
}

namespace PenyaManager {
    //
    class SlowPayersView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit SlowPayersView(QWidget *parent = 0);
            //
            ~SlowPayersView();
            //
            void init();
            //
            void retranslate();

        private slots:
            //
            void on_csvPushButton_clicked();
            //
            void on_resetAccountsPushButton_clicked();

        private:
            //
            void translateTable();
            //
            void fillSlowPayersData();
            //
            void initializeTable();
            //
            void onResetAccountAccepted(QMessageBox::StandardButton answerButton);
            //
            void onResetAccountDone();
            //
            void onCsvFileSelected(const QString &fn);

        private:
            //
            Ui::SlowPayersView *ui;
    };
}

#endif // SLOWPAYERSVIEW_H
