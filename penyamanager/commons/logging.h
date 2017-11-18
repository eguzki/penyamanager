#ifndef LOGGING_H
#define LOGGING_H

#include <QString>
#include <QSettings>
#include <QUdpSocket>

#include "DataTypes.h"

namespace PenyaManager {
    //
    enum class LogAction {
            kMain, kLogin, kInvoice, kDb
    };
    //
    QString LogActionToString(LogAction logAction);
    //
    class PenyaManagerLogger
    {
        public:
            //
            PenyaManagerLogger();
            //
            virtual ~PenyaManagerLogger() {}
            //
            virtual void Error(Uint32 userId, LogAction logAction, const QString &message) = 0;
            //
            virtual void Warn(Uint32 userId, LogAction logAction, const QString &message) = 0;
            //
            virtual void Info(Uint32 userId, LogAction logAction, const QString &message) = 0;
    };
    //
    typedef QSharedPointer<PenyaManagerLogger> PenyaManagerLoggerPtr;
    // Factory
    PenyaManagerLoggerPtr NewLoggerInstance(QSettings *pSettings, QString program);

    //
    class FileLogger : public PenyaManagerLogger
    {
        public:
            //
            FileLogger(QString program);
            //
            ~FileLogger();
            //
            void Error(Uint32 userId, LogAction logAction, const QString &message);
            //
            void Warn(Uint32 userId, LogAction logAction, const QString &message);
            //
            void Info(Uint32 userId, LogAction logAction, const QString &message);
        private:
            //
            QString         m_messageTemplate;
    };

    //
    class SysLogLogger : public PenyaManagerLogger
    {
        public:
            //
            SysLogLogger(QSettings *pSettings, QString program);
            //
            ~SysLogLogger();
            //
            void Error(Uint32 userId, LogAction logAction, const QString &message);
            //
            void Warn(Uint32 userId, LogAction logAction, const QString &message);
            //
            void Info(Uint32 userId, LogAction logAction, const QString &message);

        private:
            //
            QString getLocalAddress(QString dbHost);
            //
            QString computeDatagram(Uint16 severity, Uint32 userId, LogAction logAction, const QString &message);

        private:
            //
            QString         m_messageTemplate;
            //
            QUdpSocket      *m_pUdpSocket;
            //
            QHostAddress    m_qHostAddress;
            //
            QString         m_datagramTemplate;
            //
            QString         m_program;
            //
            QString         m_localAddress;
    };
}

#endif // LOGGING_H
