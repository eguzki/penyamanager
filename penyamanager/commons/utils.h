#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QsLog.h>

namespace PenyaManager {
    //
    class Utils
    {
        public:
            // file name
            static QString newImageName(const QString& prefix, const QString& filename);
            //
            static QString hashSHA256asHex(const QString& plainText);
            //
            static QString encryptToString(const QString& plainText);
            //
            static QString decryptToString(const QString& plainText);
            //
            static QsLogging::Level getLogLevel(const QString& plainText);

        private:
            //
            Utils() {}
            //
            ~Utils() {}
    };
}

#endif // UTILS_H
