//

#include <QCoreApplication>
#include <QDir>

#include "translationmanager.h"

namespace PenyaManager {
    //
    const QString   TranslationManager::kBasqueLangLabel        = "EUS";
    //
    const QString   TranslationManager::kEspLangLabel           = "ES";
    //
    TranslationManager::TranslationManager()
        :
            m_currentLangIndex(0), // initial index -> eu
            m_pLanguagesPrefixArray{"eu", "es"},
            m_locale(QLocale::Basque),
            m_translationLanguageFile(QString("penyamanager_%1").arg(m_pLanguagesPrefixArray[m_currentLangIndex])),
            m_adminTranslationLanguageFile(QString("penyamanageradmin_%1").arg(m_pLanguagesPrefixArray[m_currentLangIndex])),
            m_translationFilePath(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + "translations"))
    {
    }
    //
    TranslationManager::~TranslationManager()
    {
    }
    //
    void TranslationManager::switchLanguage()
    {
        m_currentLangIndex = (m_currentLangIndex + 1)%m_numLangs;
        m_translationLanguageFile = QString("penyamanager_%1").arg(m_pLanguagesPrefixArray[m_currentLangIndex]);
        m_adminTranslationLanguageFile = QString("penyamanageradmin_%1").arg(m_pLanguagesPrefixArray[m_currentLangIndex]);
        if (m_pLanguagesPrefixArray[m_currentLangIndex] == "eu") {
            // lang and country
            m_locale = QLocale(QLocale::Basque, QLocale::Spain);
        } else if (m_pLanguagesPrefixArray[m_currentLangIndex] == "es") {
            // lang and country
            m_locale = QLocale(QLocale::Spanish, QLocale::Spain);
        }
    }
    //
    QString TranslationManager::getTranslationFile()
    {
        return QDir(m_translationFilePath).filePath(m_translationLanguageFile);
    }
    //
    QString TranslationManager::getAdminTranslationFile()
    {
        return QDir(m_translationFilePath).filePath(m_adminTranslationLanguageFile);
    }
    //
    QLocale TranslationManager::getLocale()
    {
        return m_locale;
    }
    //
    QString TranslationManager::getLanguageLabel()
    {
        QString langLabel(kBasqueLangLabel);
        if (m_pLanguagesPrefixArray[m_currentLangIndex] == "es") {
            langLabel = kEspLangLabel;
        }
        return langLabel;
    }
    //
    QString TranslationManager::getStringTranslation(const QString &basqueStr, const QString &espStr)
    {
        if (m_pLanguagesPrefixArray[m_currentLangIndex] == "es") {
            return QString(espStr);
        }
        return QString(basqueStr);
    }
}
