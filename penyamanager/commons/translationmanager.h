#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QLocale>

#include "DataTypes.h"

namespace PenyaManager {
    //
    class TranslationManager
    {
        public:
            // Basque lang label
            static const QString    kBasqueLangLabel;
            // Esp lang label
            static const QString    kEspLangLabel;
            //
            TranslationManager();
            //
            ~TranslationManager();
            //
            void switchLanguage();
            //
            QString getTranslationFile();
            //
            QString getAdminTranslationFile();
            //
            QLocale getLocale();
            //
            QString getLanguageLabel();
            //
            QString getStringTranslation(const QString &basqueStr, const QString &espStr);

        private:
            //
            static const Uint16     m_numLangs = 2;
            //
            Uint16                  m_currentLangIndex;
            //
            QString                 m_pLanguagesPrefixArray[m_numLangs];
            //
            QLocale                 m_locale;
            //
            QString                 m_translationLanguageFile;
            //
            QString                 m_adminTranslationLanguageFile;
            //
            QString                 m_translationFilePath;
    };
}

#endif // TRANSLATIONMANAGER_H
