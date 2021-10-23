#ifndef TIMEDFILEDIALOG_H
#define TIMEDFILEDIALOG_H

#include <QFileDialog>
#include <QTimer>

namespace PenyaManager {
    //
    typedef std::function<void(const QString &filename)> FileDialogCallback;
    //
    class TimedFileDialog : public QFileDialog
    {
        Q_OBJECT

        public:
            //
            TimedFileDialog(QTimer *pInactivityTimer,
                    QWidget *parent, const QString &caption, const QString &directory,
                    const QString &filter, QFileDialog::AcceptMode acceptMode,
                    const FileDialogCallback &callback);
            //
            static void fileDialog(QWidget *parent,
                    const QString &caption, const QString &directory,
                    const QString &filter, QFileDialog::AcceptMode acceptMode, const FileDialogCallback &callback);

        private slots:
            //
            void onFilesSelected(const QStringList &selected);
            //
            void onRejected();
            //
            void onTimeout();

        private:
            //
            void finish();

        private:
            //
            QTimer                          *m_pInactivityTimer;
            //
            FileDialogCallback              m_callback;
    };
}

#endif // TIMEDFILEDIALOG_H
