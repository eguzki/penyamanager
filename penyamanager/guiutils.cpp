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
        printer.setOutputFileName("deposit.pdf");
        printer.setPaperSize(QPrinter::A6);
        //printer.setPageSize(QPrinter::A6);
        if (!printer.isValid()) {
            QLOG_ERROR() << QString("[PrintFailed] pdf printer not valid");
            return;
        }
        // nedeed to keep printer from printing page number
        QSizeF paperSize;
        paperSize.setWidth(printer.pageRect(QPrinter::Millimeter).width());
        paperSize.setHeight(printer.pageRect(QPrinter::Millimeter).height());
        QTextDocument textDocument;
        // supported attributes
        // http://doc.qt.io/qt-5/richtext-html-subset.html
        // Use tables for layout
        textDocument.setPageSize(paperSize); // the document needs a valid PageSize
        textDocument.setHtml(html);
        textDocument.print(&printer);

    }
}
