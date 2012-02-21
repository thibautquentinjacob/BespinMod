#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>

class Dialog : public QDialog {
   Q_OBJECT
public:
   Dialog() : QDialog(0, Qt::Window){}
public slots:
   void setLayoutDirection(bool rtl) {
      QDialog::setLayoutDirection(rtl ? Qt::RightToLeft : Qt::LeftToRight);
   }
};

#endif // DIALOG_H
