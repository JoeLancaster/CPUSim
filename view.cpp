#include "view.h"

view::view(QScrollArea & scroll_area){
    this->list = new QListWidget();
    this->layout = new QHBoxLayout();
    this->grip = new QSizeGrip(list);
    scroll_area.setWidget(list);
    scroll_area.setAlignment(Qt::AlignLeft);
}
