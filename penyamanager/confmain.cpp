//

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <QDebug>
#include <stdio.h>

#include "constants.h"

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
    const QCommandLineOption ddbbHostOption(
            "host",
            "Database host. IP or hostname",
            "host");
    parser.addOption(ddbbHostOption);

    // An option value with multiples names (-n, --name)
    const QCommandLineOption ddbbNameOption(
            QStringList() << "n" << "name",
            "Database name",
            "name");
    parser.addOption(ddbbNameOption);

    // An option value with multiples names (-u, --user)
    const QCommandLineOption ddbbUserOption(
            QStringList() << "u" << "user",
            "Database username",
            "host");
    parser.addOption(ddbbUserOption);

    // An option value with multiples names (-p, --password)
    const QCommandLineOption ddbbPassOption(
            QStringList() << "p" << "password",
            "Database password",
            "password");
    parser.addOption(ddbbPassOption);

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
    QString ddbbHost = parser.value(ddbbHostOption);
    QString ddbbName = parser.value(ddbbNameOption);
    QString ddbbUser = parser.value(ddbbUserOption);
    QString ddbbPass = parser.value(ddbbPassOption);

    if (resourcePath.isEmpty() ||
            ddbbHost.isEmpty() ||
            ddbbName.isEmpty() ||
            ddbbUser.isEmpty() ||
            ddbbPass.isEmpty()
            ) {
        fputs(qPrintable(parser.helpText()), stderr);
        return 1;
    }

    QSettings settings(PenyaManager::Constants::kOrganizationName, PenyaManager::Constants::kApplicationName);
    // resource path
    settings.setValue(PenyaManager::Constants::kResourcePathKey, resourcePath);

    // ddbb settings
    settings.beginGroup(PenyaManager::Constants::kDatabaseGroupName);
    settings.setValue(PenyaManager::Constants::kDatabaseHost, ddbbHost);
    settings.setValue(PenyaManager::Constants::kDatabaseName, ddbbName);
    settings.setValue(PenyaManager::Constants::kDatabaseUser, ddbbUser);
    settings.setValue(PenyaManager::Constants::kDatabasePass, ddbbPass);
    settings.endGroup();

    fputs("Successful\n", stdout);
    return 0;
}

