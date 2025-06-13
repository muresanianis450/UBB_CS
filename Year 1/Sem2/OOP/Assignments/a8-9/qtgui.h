//
// Created by mures on 5/22/2025.
//

#ifndef QTGUI_H
#define QTGUI_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class QTGUI; }
QT_END_NAMESPACE

class QTGUI : public QWidget {
Q_OBJECT

public:
    explicit QTGUI(QWidget *parent = nullptr);
    ~QTGUI() override;
    void connect_push_buttons();
    void function();

private:
    Ui::QTGUI *ui;
};


#endif //QTGUI_H
