#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlighter.h"
#include <QLabel>
#include "build_constants.h"
#include <QListWidget>
#include <QHBoxLayout>
#include "cpu.h"
#include "view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:

        //void on_Step_Button_released();

        void on_Assemble_Button_released();

        void on_Reset_Button_released();


        void on_Step_Button_clicked();

        void on_File_Open_Source_Code_triggered();

        void on_actionSave_Source_Code_triggered();

    private:
        view * memory_view;
        view * stack_view;
        void display_data();
        QListWidgetItem * memory_list_items[g_MEM_SIZE];
        QLabel * reg_labels[g_TOTAL_REG_COUNT];
        highlighter * syntax_highlighter;
        CPU cpu = CPU();
        Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
