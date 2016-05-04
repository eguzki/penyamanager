//

#include <QCryptographicHash>
#include <QFileInfo>
#include <QDateTime>
#include <string>
#include <simplecrypt.h>

#include "constants.h"
#include "utils.h"

namespace PenyaManager {
    // file name
    QString Utils::newImageName(const QString& prefix, const QString& filename)
    {
        QFileInfo imageInfo(filename);
        // Copy file to destination
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString nameTemplate("%1-%2.%3");
        return nameTemplate.arg(prefix).arg(QString::number(currentDateTime.toMSecsSinceEpoch()/1000)).arg(imageInfo.suffix());
    }
    //
    QString Utils::hashSHA256asHex(const QString& plainText)
    {
        QCryptographicHash hash(QCryptographicHash::Algorithm::Sha256);
        std::string plainTextStr = plainText.toStdString();
        hash.addData(plainTextStr.c_str(), plainTextStr.length());
        // to Hex
        return QString(hash.result().toHex());
    }
    //
    // Simple encryption with SimpleCrypt
    // Simple and easy to integrate in the project
    // Weak cryptography
    // For strong cryptography use AES simmetric encryption. Implementations:
    // * http://delta.affinix.com/qca/
    // * Openssl
    QString Utils::encryptToString(const QString& plainText)
    {
        SimpleCrypt crypto(Constants::kCryptKey);
        return crypto.encryptToString(plainText);
    }
    //
    // Simple encryption with SimpleCrypt
    // Simple and easy to integrate in the project
    // Weak cryptography
    // For strong cryptography use AES simmetric encryption. Implementations:
    // * http://delta.affinix.com/qca/
    // * Openssl
    QString Utils::decryptToString(const QString& plainText)
    {
        SimpleCrypt crypto(Constants::kCryptKey);
        return crypto.decryptToString(plainText);
    }
    //
    // valid log level strings:
    // debug
    // info
    // warn
    // error
    QsLogging::Level Utils::getLogLevel(const QString& plainText)
    {
        // if plainText is unknown => info
        QsLogging::Level level(QsLogging::InfoLevel);
        if (plainText == "debug") {
            level = QsLogging::DebugLevel;
        } else if (plainText == "info"){
            level = QsLogging::InfoLevel;
        } else if (plainText == "warn"){
            level = QsLogging::WarnLevel;
        } else if (plainText == "error"){
            level = QsLogging::ErrorLevel;
        }
        return level;
    }
}
