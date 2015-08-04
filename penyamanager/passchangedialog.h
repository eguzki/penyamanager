#ifndef PASSCHANGEDIALOG_H
#define PASSCHANGEDIALOG_H

#include <QDialog>

namespace Ui {
    //
    class PassChangeDialog;
}

namespace PenyaManager {
    //
    class PassChangeDialog : public QDialog
    {
        Q_OBJECT

        public:
            //
            explicit PassChangeDialog(QWidget *parent = 0);
            //
            ~PassChangeDialog();
            //
            QString getPassword();

        private slots:
            //
            void on_buttonBox_accepted();

        private:
            //
            Ui::PassChangeDialog *ui;
            //
            QString             m_pwd;
    };
}

#endif // PASSCHANGEDIALOG_H
