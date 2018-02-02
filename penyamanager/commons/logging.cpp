//
#include <QsLogDest.h>
#include <QsLog.h>
#include <QDir>
#include <QString>
#include <QDateTime>
#include <QTcpSocket>

#include "constants.h"
#include "logging.h"

namespace PenyaManager {

    //
    QString LogActionToString(LogAction logAction)
    {
        switch(logAction){
            case LogAction::kMain:
                return "main";
            case LogAction::kLogin:
                return "login";
            case LogAction::kInvoice:
                return "invoice";
            case LogAction::kDb:
                return "db";
            case LogAction::kDashboard:
                return "dashboard";
            case LogAction::kService:
                return "service";
            case LogAction::kDeposit:
                return "deposit";
            case LogAction::kReservation:
                return "reservation";
            case LogAction::kPrint:
                return "print";
            case LogAction::kProvider:
                return "provider";
            case LogAction::kProduct:
                return "product";
            case LogAction::kFamily:
                return "family";
            case LogAction::kMember:
                return "member";
        }
        return "Unknown";
    }
    //
    PenyaManagerLoggerPtr NewLoggerInstance(QSettings *pSettings, QString program)
    {
        // if debug => FileLogger
        // otherwise => SysLogLogger
        QString debugOption = pSettings->value(PenyaManager::Constants::kDebugConfig, "0").toString();
        PenyaManagerLoggerPtr penyaManagerLoggerPtr;
        if (debugOption == "1") {
            penyaManagerLoggerPtr = PenyaManagerLoggerPtr(new FileLogger(program));
        } else {
            penyaManagerLoggerPtr = PenyaManagerLoggerPtr(new SysLogLogger(pSettings, program));
        }
        return penyaManagerLoggerPtr;
    }
    //
    PenyaManagerLogger::PenyaManagerLogger()
    {
    }
    //
    FileLogger::FileLogger(QString program) :
        PenyaManagerLogger(),
        m_messageTemplate("[user %1] [action %2] %3")
    {
        // init the logging mechanism
        QsLogging::Logger& logger = QsLogging::Logger::instance();
        // set log level and file name
        logger.setLoggingLevel(QsLogging::DebugLevel);
        const QString sLogPath(QDir(QDir::currentPath()).filePath(QString("%1.log").arg(program)));

        // Create log destinations
        QsLogging::DestinationPtr fileDestination( QsLogging::DestinationFactory::MakeFileDestination(
                    sLogPath,
                    QsLogging::LogRotationOption::EnableLogRotation,
                    QsLogging::MaxSizeBytes(Constants::kLogMaxSizeBytes)
                    ));
        // set log destinations on the logger
        logger.addDestination(fileDestination);
    }
    //
    FileLogger::~FileLogger()
    {
    }
    //
    void FileLogger::Error(Uint32 userId, LogAction logAction, const QString &message)
    {
        QLOG_ERROR() << m_messageTemplate.arg(QString::number(userId)).arg(LogActionToString(logAction)).arg(message);
    }
    //
    void FileLogger::Warn(Uint32 userId, LogAction logAction, const QString &message)
    {
        QLOG_WARN() << m_messageTemplate.arg(QString::number(userId)).arg(LogActionToString(logAction)).arg(message);
    }
    //
    void FileLogger::Info(Uint32 userId, LogAction logAction, const QString &message)
    {
        QLOG_INFO() << m_messageTemplate.arg(QString::number(userId)).arg(LogActionToString(logAction)).arg(message);
    }
    //
    void FileLogger::Debug(Uint32 userId, LogAction logAction, const QString &message)
    {
        QLOG_DEBUG() << m_messageTemplate.arg(QString::number(userId)).arg(LogActionToString(logAction)).arg(message);
    }
    //
    SysLogLogger::SysLogLogger(QSettings *pSettings, QString program) :
        PenyaManagerLogger(),
        m_messageTemplate("[user %1] [action %2] %3"),
        m_pUdpSocket(new QUdpSocket(NULL)),
        m_qHostAddress(),
        m_datagramTemplate("<%1>%2 %3 %4: %5"),
        m_program(program),
        m_localAddress()
    {
        pSettings->beginGroup(PenyaManager::Constants::kDatabaseGroupName);
        // get syslog server from conf. Default value: db host
        QString defaultSyslogServer = pSettings->value(Constants::kDatabaseHost).toString();
        m_localAddress = getLocalAddress(pSettings->value(Constants::kDatabaseHost).toString());
        pSettings->endGroup();
        QString syslogServer = pSettings->value(PenyaManager::Constants::kSyslogServer, defaultSyslogServer).toString();
        m_qHostAddress = QHostAddress(syslogServer);
    }
    //
    SysLogLogger::~SysLogLogger()
    {
    }

    // Get IP address required to reach db host
    QString SysLogLogger::getLocalAddress(QString dbHost)
    {
        QString localAddress = "UnknownAddress";
        QTcpSocket socket;
        socket.connectToHost(dbHost, 3306); // db host:port
        if (socket.waitForConnected()) {
            localAddress = socket.localAddress().toString();
        }
        return localAddress;
    }
    //
    QString SysLogLogger::computeDatagram(Uint16 severity, Uint32 userId, LogAction logAction, const QString &message)
    {
        // Datagram format
        // https://tools.ietf.org/html/rfc3164#section-4.1.1
        // Example: "<132>Nov 17 22:14:15 myHostName penya: syslog client at 10.0.0.6 started."
        Uint16 facility = 16; // local0
        Uint32 pri = facility * 8 + severity;
        QString datagramMessage = m_messageTemplate.arg(QString::number(userId)).arg(LogActionToString(logAction)).arg(message);
        // date must be localized in timezone, but remote syslog requires english
        QLocale syslogLocale(QLocale::English);
        QDateTime now = QDateTime::currentDateTime();
        return m_datagramTemplate.arg(QString::number(pri)).arg(syslogLocale.toString(now, "MMM d hh:mm:ss")).arg(m_localAddress).arg(m_program).arg(datagramMessage);
    }
    //
    void SysLogLogger::Error(Uint32 userId, LogAction logAction, const QString &message)
    {
        Uint16 severity = 3; // Error
        QByteArray datagram;
        datagram.append(computeDatagram(severity, userId, logAction, message));
        m_pUdpSocket->writeDatagram(datagram.data(), datagram.size(), m_qHostAddress, 514);
    }
    //
    void SysLogLogger::Warn(Uint32 userId, LogAction logAction, const QString &message)
    {
        Uint16 severity = 4; // Warning
        QByteArray datagram;
        datagram.append(computeDatagram(severity, userId, logAction, message));
        m_pUdpSocket->writeDatagram(datagram.data(), datagram.size(), m_qHostAddress, 514);
    }
    //
    void SysLogLogger::Info(Uint32 userId, LogAction logAction, const QString &message)
    {
        Uint16 severity = 6; // Informational
        QByteArray datagram;
        datagram.append(computeDatagram(severity, userId, logAction, message));
        m_pUdpSocket->writeDatagram(datagram.data(), datagram.size(), m_qHostAddress, 514);
    }
    //
    void SysLogLogger::Debug(Uint32 userId, LogAction logAction, const QString &message)
    {
        Uint16 severity = 7; // Debug
        QByteArray datagram;
        datagram.append(computeDatagram(severity, userId, logAction, message));
        m_pUdpSocket->writeDatagram(datagram.data(), datagram.size(), m_qHostAddress, 514);
    }
}

