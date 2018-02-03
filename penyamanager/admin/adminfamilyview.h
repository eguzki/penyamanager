#ifndef ADMINFAMILYVIEW_H
#define ADMINFAMILYVIEW_H

#include <QWidget>
#include <commons/IPartner.h>

namespace Ui {
    //
    class AdminFamilyView;
}


namespace PenyaManager {
    //
    class AdminFamilyView : public IPartner
    {
        Q_OBJECT

        public:
            //
            explicit AdminFamilyView(QWidget *parent, const CentralWidgetCallback &callback);
            //
            ~AdminFamilyView();
            //
            void init();
            //
            void retranslate();

        private:
            //
            void fillFamilyInfo(Int32 familyId);
            //
            void initialize();
            //
            void onFamilyImageSelected(const QString &fn);
            //
            void onFamilyUpdated();

        private slots:
            //
            void on_savePushButton_clicked();
            //
            void on_imagePushButton_clicked();

        private:
            //
            Ui::AdminFamilyView *ui;
            //
            CentralWidgetCallback       m_switchCentralWidgetCallback;
            //
            QString                     m_familyImageFilename;
    };

}

#endif // ADMINFAMILYVIEW_H
