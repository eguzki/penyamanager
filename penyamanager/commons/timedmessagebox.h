#ifndef TIMEDMESSAGEBOX_H
#define TIMEDMESSAGEBOX_H

#include <QTimer>
#include <QAbstractButton>
#include <QMessageBox>

namespace PenyaManager {
    //
    typedef std::function<void(QAbstractButton *p)> MessageBoxCallback;
    //
    typedef std::function<void()> InfoMessageBoxCallback;
    //
    typedef std::function<void(QMessageBox::StandardButton answerButton)> QuestionMessageBoxCallback;

    // This class implements a MessageBox with a timeout.
    // Receives one callback that will be called on user action.
    // On timer timeout, no callback is called
    class TimedMessageBox: public QMessageBox
    {
        Q_OBJECT

        public:
            //
            explicit TimedMessageBox(QTimer *pInactivityTimer, const MessageBoxCallback &callback,
                    QMessageBox::Icon icon, const QString &title, const QString &text,
                    QMessageBox::StandardButtons buttons = QMessageBox::NoButton,
                    QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            //
            static void infoMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            static void infoMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            static void criticalMessageBox(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            static void criticalMessageBoxTitled(QWidget *parent, const QString &message, const InfoMessageBoxCallback &callback);
            //
            static void questionMessageBoxTitled(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback);
            //
            static void questionMessageBox(QWidget *parent, const QString &message, const QuestionMessageBoxCallback &callback);
            //
            static MessageBoxCallback convertInfoMessageBox(const InfoMessageBoxCallback &callback);
            //
            static MessageBoxCallback convertQuestionMessageBox(const QuestionMessageBoxCallback &callback);

        public slots:
            //
            void OnButtonClicked(QAbstractButton *pButton);
            //
            void OnTimeout();

        private:
            //
            void finish();

        private:
            //
            QTimer                          *m_pInactivityTimer;
            //
            MessageBoxCallback              m_callback;

    };
}

#endif // TIMEDMESSAGEBOX_H
