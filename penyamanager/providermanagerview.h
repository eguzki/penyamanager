#ifndef PROVIDERMANAGERVIEW_H
#define PROVIDERMANAGERVIEW_H

#include <QWidget>

namespace Ui {
class ProviderManagerView;
}

class ProviderManagerView : public QWidget
{
    Q_OBJECT

public:
    explicit ProviderManagerView(QWidget *parent = 0);
    ~ProviderManagerView();

private:
    Ui::ProviderManagerView *ui;
};

#endif // PROVIDERMANAGERVIEW_H
