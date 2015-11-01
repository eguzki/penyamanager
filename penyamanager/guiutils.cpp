//

#include <QPrinter>
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
        QPrinterInfo defaultPrinter = QPrinterInfo::defaultPrinter();
        if (defaultPrinter.isNull()) {
            QLOG_INFO() << QString("[PrintFailed] default printer is null");
            return;
        }
        QPrinter printer( defaultPrinter);

        /*
         * PDF
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("/home/eguzki/printer.pdf");
        */

        QSizeF paperSize(80, 297);
        printer.setPaperSize(paperSize, QPrinter::Millimeter);
        if (!printer.isValid()) {
            QLOG_ERROR() << QString("[PrintFailed] pdf printer not valid");
            return;
        }

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
}
