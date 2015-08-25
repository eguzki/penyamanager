//

#include <QPrinter>
#include <QPrinterInfo>
#include <QTextDocument>

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
        /*
        QPrinterInfo defaultPrinter = QPrinterInfo::defaultPrinter();
        if (defaultPrinter.isNull()) {
            QLOG_INFO() << QString("[PrintFailed] default printer is null");
            return;
        }
        */
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("invoice.pdf");
        printer.setPaperSize(QPrinter::A6);
        if (!printer.isValid()) {
            QLOG_ERROR() << QString("[PrintFailed] pdf printer not valid");
            return;
        }
        QLOG_INFO() << QString("[Print] print");
        QTextDocument textDocument;
        // supported attributes
        // http://doc.qt.io/qt-5/richtext-html-subset.html
        // Use tables for layout
        textDocument.setHtml(html);
        textDocument.print(&printer);
    }
}
