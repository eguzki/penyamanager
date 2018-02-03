#ifndef INACTIVITYEVENTFILTER_H
#define INACTIVITYEVENTFILTER_H

#include <QObject>
#include <QTimer>

namespace PenyaManager {
    //
    class InactivityEventFilter : public QObject
    {
        Q_OBJECT

        public:
            //
            explicit InactivityEventFilter(QTimer *pInactivityTimer);
            //
            ~InactivityEventFilter();

		protected:
			//
  			bool eventFilter(QObject *obj, QEvent *ev);

        private:
            //
            QTimer              *m_pInactivityTimer;
    };
}

#endif // INACTIVITYEVENTFILTER_H
