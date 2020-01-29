#ifndef QUICK_MESSAGE_BOX_H
#define QUICK_MESSAGE_BOX_H

#include <QMessageBox>

class quick_message_box {
    public:
        QMessageBox mb;
        quick_message_box(const char * title, const char * text){
            mb.setWindowTitle(title);
            mb.setText(text);
            mb.setStandardButtons(QMessageBox::Ok);
        }
};

#endif // QUICK_MESSAGE_BOX_H
