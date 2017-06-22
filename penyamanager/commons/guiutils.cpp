//

#include <QPrinter>
#include <QVariant>
#include <QPrinterInfo>
#include <QTextDocument>
#include <QFile>
#include <mustache.h>
#include <QsLog.h>

#include "guiutils.h"

namespace PenyaManager {
    // get image
    QPixmap GuiUtils::getImage(const QString& filename)
    {
        QPixmap image(filename);
        if (image.isNull()) {
            image = QPixmap(":images/no-image.gif");
        }
        return image;
    }
    //
    void GuiUtils::printText(const QString& html)
    {
        QLOG_INFO() << QString("[Print] print ini");
        QPrinterInfo defaultPrinter = QPrinterInfo::defaultPrinter();
        if (defaultPrinter.isNull()) {
            QLOG_ERROR() << QString("[PrintFailed] default printer is null");
            return;
        }
        QPrinter printer( defaultPrinter);

        /*
         * PDF
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("/home/eguzki/printer.pdf");

        if (!printer.isValid()) {
            QLOG_ERROR() << QString("[PrintFailed] pdf printer not valid");
            return;
        }
        */

        // nedeed to keep printer from printing page number
        QSizeF pageSize;
        pageSize.setWidth(printer.pageRect(QPrinter::Millimeter).width());
        pageSize.setHeight(printer.pageRect(QPrinter::Millimeter).height());
        QTextDocument textDocument;
        // supported attributes
        // http://doc.qt.io/qt-5/richtext-html-subset.html
        // Use tables for layout
        textDocument.setPageSize(pageSize); // the document needs a valid PageSize
        textDocument.setHtml(html);
        QLOG_INFO() << QString("[Print] print");
        textDocument.print(&printer);
    }
    //
    void GuiUtils::printInvoice(QVariantHash &invoiceData, Int32 memberId, Int32 invoiceId)
    {
        QFile invoiceTemplateFile(":resources/invoice.html");
        if (!invoiceTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QLOG_ERROR() << QString("[Invoice] invoice.html not found");
            return;
        }
        QTextStream invoiceTemplateStream(&invoiceTemplateFile);
        invoiceTemplateStream.setCodec("UTF-8");
        QString invoiceTemplate = invoiceTemplateStream.readAll();
        QString invoiceHtml = Mustache::renderTemplate(invoiceTemplate, invoiceData);
        GuiUtils::printText(invoiceHtml);
        QLOG_INFO() << QString("[Print] print invoice user %1 invoice %2").arg(memberId).arg(invoiceId);
    }
    //
    void GuiUtils::printPostalMembers(const MemberListPtr pMemberListPtr)
    {
        QFile membersTemplateFile(":resources/members.html");
        if (!membersTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QLOG_ERROR() << QString("[Members] members.html not found");
            return;
        }
        QTextStream membersTemplateStream(&membersTemplateFile);
        membersTemplateStream.setCodec("UTF-8");
        QString memberTemplate = membersTemplateStream.readAll();

        QFile singleMembersTemplateFile(":resources/singlemember.html");
        if (!singleMembersTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QLOG_ERROR() << QString("[Members] singlemember.html not found");
            return;
        }
        QTextStream singleMembersTemplateStream(&singleMembersTemplateFile);
        singleMembersTemplateStream.setCodec("UTF-8");
        QString singleMembersTemplate = singleMembersTemplateStream.readAll();

        QFile doubleMembersTemplateFile(":resources/doublemember.html");
        if (!doubleMembersTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QLOG_ERROR() << QString("[Members] doublemember.html not found");
            return;
        }
        QTextStream doubleMembersTemplateStream(&doubleMembersTemplateFile);
        doubleMembersTemplateStream.setCodec("UTF-8");
        QString doubleMembersTemplate = doubleMembersTemplateStream.readAll();

        QString membersHtml;
        for (MemberList::iterator iter = pMemberListPtr->begin(); iter != pMemberListPtr->end(); ++iter)
        {
            MemberPtr pMemberPtr = *iter;
            QString membersPart;
            if ((iter+1) == pMemberListPtr->end()) {
                // last one
                QVariantHash memberData;
                memberData["name"] = QString("%1 %2").arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname);
                memberData["address"] = pMemberPtr->m_address;
                memberData["zip"] = pMemberPtr->m_zipCode;
                memberData["town"] = pMemberPtr->m_town;
                membersPart = Mustache::renderTemplate(singleMembersTemplate, memberData);
            } else {
                QVariantHash memberData;
                memberData["name_1"] = QString("%1 %2").arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname);
                memberData["address_1"] = pMemberPtr->m_address;
                memberData["zip_1"] = pMemberPtr->m_zipCode;
                memberData["town_1"] = pMemberPtr->m_town;
                // increment iterator to read next member
                ++iter;
                pMemberPtr = *iter;
                memberData["name_2"] = QString("%1 %2").arg(pMemberPtr->m_name).arg(pMemberPtr->m_surname);
                memberData["address_2"] = pMemberPtr->m_address;
                memberData["zip_2"] = pMemberPtr->m_zipCode;
                memberData["town_2"] = pMemberPtr->m_town;
                // print two members
                membersPart = Mustache::renderTemplate(doubleMembersTemplate, memberData);
            }
            membersHtml.append(membersPart);
        }
        QVariantHash htmlVariant;
        htmlVariant["members"] = membersHtml;
        QString html = Mustache::renderTemplate(memberTemplate, htmlVariant);
        QLOG_DEBUG() << html;
        GuiUtils::printText(html);
        QLOG_INFO() << QString("[Print] print member list");

    }
}
