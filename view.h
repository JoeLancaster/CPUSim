#ifndef VIEW_H
#define VIEW_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QScrollArea>

class view{
        public:
            view(QScrollArea &);
            QListWidget * list;
            QHBoxLayout * layout;
            QSizeGrip * grip;

};

#endif // VIEW_H
