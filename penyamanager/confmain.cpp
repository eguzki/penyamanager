//

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <QtSql>
#include <stdio.h>

#include <commons/utils.h>
#include <commons/constants.h>

bool testDB(const QString& hostname, const QString& databaseName,
            const QString& username, const QString& pass)
{
    QSqlDatabase db(QSqlDatabase::addDatabase("QMYSQL"));
    // configure db connection
    db.setHostName(hostname);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(pass);

    // open ddbb connection
    bool success(db.open());

    if (!success) {
        fprintf(stderr, "Error: %s\n", db.lastError().text().toStdString().c_str());
    }

    return success;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setApplicationName("penyamanagerconf");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("penyamanager configuration application");
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();

    // An option value with multiples names (-r, --path)
    const QCommandLineOption resourcePathOption(
            QStringList() << "r" << "path",
            "Resource path",
            "resourcepath");
    parser.addOption(resourcePathOption);

    // An option value (--host)
    const QCommandLineOption dbHostOption(
            "host",
            "Database host. IP or hostname",
            "host");
    parser.addOption(dbHostOption);

    // An option value with multiples names (-n, --name)
    const QCommandLineOption dbNameOption(
            QStringList() << "n" << "name",
            "Database name",
            "name");
    parser.addOption(dbNameOption);

    // An option value with multiples names (-u, --user)
    const QCommandLineOption dbUserOption(
            QStringList() << "u" << "user",
            "Database username",
            "user");
    parser.addOption(dbUserOption);

    // An option value with multiples names (-p, --password)
    const QCommandLineOption dbPassOption(
            QStringList() << "p" << "password",
            "Database password",
            "password");
    parser.addOption(dbPassOption);

    // An option value (--syslog). Optional.
    const QCommandLineOption sysLogServerOption(
            "syslog",
            "Syslog Server host. IP or hostname. Default database host.",
            "syslog");
    parser.addOption(sysLogServerOption);

    // An option value (--debug). Optional.
    const QCommandLineOption debugOption(
            "debug",
            "Debug mode");
    parser.addOption(debugOption);

    // An option value (--force). Optional.
    const QCommandLineOption forceOption(
            "force",
            "Disable parameter checks");
    parser.addOption(forceOption);

    // An option value (--creditlimit). Optional.
    const QCommandLineOption creditLimitOption(
            "creditlimit",
            QString("Credit Limit. Default: %1 €").arg(PenyaManager::Constants::kDefaultCreditLimit, 0, 'f', 2),
            "creditlimit");
    parser.addOption(creditLimitOption);

    if (!parser.parse(QCoreApplication::arguments())) {
        fputs(qPrintable(parser.errorText()), stderr);
        fputs("\n\n", stderr);
        fputs(qPrintable(parser.helpText()), stderr);
        return 1;
    }

    if (parser.isSet(versionOption)) {
        printf("%s %s\n", qPrintable(QCoreApplication::applicationName()),
                qPrintable(QCoreApplication::applicationVersion()));
        return 0;
    }

    if (parser.isSet(helpOption)) {
        parser.showHelp();
        return 0;
    }

    QString resourcePath = parser.value(resourcePathOption);
    QString dbHost = parser.value(dbHostOption);
    QString dbName = parser.value(dbNameOption);
    QString dbUser = parser.value(dbUserOption);
    QString dbPass = parser.value(dbPassOption);

    if (resourcePath.isEmpty() ||
            dbHost.isEmpty() ||
            dbName.isEmpty() ||
            dbUser.isEmpty() ||
            dbPass.isEmpty()
            ) {
        fputs(qPrintable(parser.helpText()), stderr);
        return 1;
    }

    if (!parser.isSet(forceOption) && !testDB(dbHost, dbName, dbUser, dbPass)) {
        fprintf(stderr, "DB address: %s\n", dbHost.toStdString().c_str());
        fprintf(stderr, "DB name: %s\n", dbName.toStdString().c_str());
        fprintf(stderr, "DB username: %s\n", dbUser.toStdString().c_str());
        fputs("Check connection params, you fool user!\n", stderr);
        return 1;
    }

    Float creditLimit(PenyaManager::Constants::kDefaultCreditLimit);
    if (parser.isSet(creditLimitOption)) {
        bool ok;
        Float tmpCreditLimit = parser.value(creditLimitOption).toFloat(&ok);
        if (!ok) {
            fputs("Check credit limit param. Not a valid float. You fool user\n", stderr);
            return 1;
        }
        creditLimit = tmpCreditLimit;
    }

    QSettings settings(PenyaManager::Constants::kOrganizationName, PenyaManager::Constants::kApplicationName);
    // resource path
    settings.setValue(PenyaManager::Constants::kResourcePathKey, resourcePath);
    // syslog server host (optional)
    if (parser.isSet(sysLogServerOption)) {
        settings.setValue(PenyaManager::Constants::kSyslogServer, parser.value(sysLogServerOption));
    } else {
        settings.setValue(PenyaManager::Constants::kSyslogServer, dbHost);
    }
    // debug (optional)
    if (parser.isSet(debugOption)){
        settings.setValue(PenyaManager::Constants::kDebugConfig, 1);
    } else {
        settings.setValue(PenyaManager::Constants::kDebugConfig, 0);
    }

    // Credit Limit
    settings.setValue(PenyaManager::Constants::kCreditLimitSettingsKey, QString("%1").arg(creditLimit, 0, 'f', 2));

    // db settings
    settings.beginGroup(PenyaManager::Constants::kDatabaseGroupName);
    settings.setValue(PenyaManager::Constants::kDatabaseHost, dbHost);
    settings.setValue(PenyaManager::Constants::kDatabaseName, dbName);
    settings.setValue(PenyaManager::Constants::kDatabaseUser, dbUser);
    // Encrypt pass
    QString cryptedPass = PenyaManager::Utils::encryptToString(dbPass);
    settings.setValue(PenyaManager::Constants::kDatabasePass, cryptedPass);
    settings.endGroup();

    fputs("Successful\n", stdout);
    return 0;
}

