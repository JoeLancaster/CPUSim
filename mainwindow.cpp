#include "mainwindow.h"
#include "assembler.h"
#include "ui_mainwindow.h"
#include "runtime_exception.h"
#include "quick_message_box.h"
#include <QLabel>
#include <QLayout>
#include <QSizeGrip>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <iomanip>
#include <algorithm>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    for(unsigned short i = 0; i < g_TOTAL_REG_COUNT; i++){
        reg_labels[i] = new QLabel(this);
        reg_labels[i]->setText((assembler_strings::regs[i] + ": ").c_str());
        ui->Regs_Layout->addWidget(reg_labels[i]);
    }
    memory_view = new view(*(ui->Memory_Scroll_Area));
    stack_view = new view(*(ui->Stack_Scroll_Area));
    syntax_highlighter = new highlighter(ui->TextEditor->document());
    for(unsigned short i = 0; i < g_MEM_SIZE; i++){
        std::stringstream hex_num_stream;
        hex_num_stream << std::setfill('0') << std::setw(2) << std::hex << i << ":   "; //nicely formatted hex numbers
        std::string hex_num_string = hex_num_stream.str();
        std::transform(hex_num_string.begin(), hex_num_string.end(), hex_num_string.begin(), ::toupper);
        memory_list_items[i] = new QListWidgetItem(hex_num_string.c_str(), memory_view->list);
    }
    return;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::display_data(){
    for(unsigned short i = 0; i < g_TOTAL_REG_COUNT; i++){
        std::string temp_reg_value = std::to_string(cpu.get_regs()[i]);
        reg_labels[i]->setText((assembler_strings::regs[i] + ": " + temp_reg_value).c_str());
    }
    for(unsigned short i = 0; i < g_MEM_SIZE; i++){
        std::string temp = memory_list_items[i]->text().toStdString();
        temp = temp.erase(4, 2); //deletes the last two characters in the string and eventually replaces them with the updated value
        std::stringstream temp_stream;
        temp_stream << temp << std::hex << (unsigned short)cpu.get_mem()[i];
        temp = temp_stream.str();
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper); //sets the string to uppercase
        memory_list_items[i]->setText(temp.c_str());
    }
    stack_view->list->clear();
    for(unsigned short i = 0; i < cpu.get_stack()->size(); i++){
        std::stringstream temp_stream;
        temp_stream << std::hex << std::setfill('0') << std::setw(2) << i << ": " << (unsigned short)cpu.get_stack()->at(i); //nicely formatted hex numbers again
        std::string temp = temp_stream.str();
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        stack_view->list->addItem(temp.c_str());
    }
}

void MainWindow::on_Assemble_Button_released(){
    ui->Assemble_Button->setEnabled(false); //this is required so the user can't interrupt the assembly process
    QStringList lines = ui -> TextEditor->toPlainText().split(QRegExp("[\r\n]"), QString::SkipEmptyParts); //creates a list of strings that are equal to the lines in the text editor
    if(lines.length() == 0){
        QMessageBox mb;
        mb.setText("That file is empty!");
        mb.setWindowTitle("Error!");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }
    if(lines.length() > 128){
        QMessageBox mb;
        mb.setText("The assembly code is too large!");
        mb.setWindowTitle("Error!");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }
    if(Assembler::clean(lines.last().toStdString()).find("HLT") == std::string::npos){ //looks for the string "HLT" in the final line
        QMessageBox mb;
        mb.setText("The last line of this program does not contain a halt statement");
        mb.setWindowTitle("Warning!");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec(); //will still assemble because it could be desired behaviour
    }
    std::ofstream program_file;
    program_file.open("assembleroutput.bin", std::ios::binary | std::ios::out);
    foreach(QString line, lines){
        static opcode op;
        std::string clean_line = Assembler::clean(line.toStdString());
        try{
            op = Assembler::assemble_line(clean_line);
        }
        catch(std::exception & e){
            QMessageBox mb;
            mb.setWindowTitle("Erorr assembling");
            mb.setText(e.what());
            mb.setStandardButtons(QMessageBox::Ok);
            mb.exec();
            ui->Assemble_Button->setEnabled(true);
            return;
        }
        program_file << op.code << op.target;
    }
    program_file.close();
    this -> cpu.load("assembleroutput.bin");
    display_data();
    ui->Assemble_Button->setEnabled(true);
}

void MainWindow::on_Reset_Button_released(){
    cpu.reset();
    cpu.load("assembleroutput.bin");
    display_data();
}


void MainWindow::on_Step_Button_clicked(){
    ui->Step_Button->setEnabled(false);
    if(cpu.abort){
        QMessageBox mb;
        mb.setText("The program has halted.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.setWindowTitle("Aborted");
        mb.exec();
        ui->Step_Button->setEnabled(true);
        return;
    }
    try{
        this->cpu.tick();
        this->display_data();
        ui->Step_Button->setEnabled(true);
        return;
    }
    catch(runtime_exception & e){
        QMessageBox mb;
        mb.setText(e.what());
        mb.setStandardButtons(QMessageBox::Ok);
        mb.setWindowTitle("The cpu stopped unexpectedly");
        mb.exec();
        ui->Step_Button->setEnabled(true);
        return;
    }
}

void MainWindow::on_File_Open_Source_Code_triggered(){
    QString source_code_file_name = QFileDialog::getOpenFileName(this, "Open Source Code File", QDir::currentPath(), "All files (*.*);;Assembly Source Code (*.8asm)");
    if(!source_code_file_name.endsWith(".8asm", Qt::CaseInsensitive)){
        QMessageBox mb;
        mb.setText("That file format is not supported.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.setWindowTitle("Error");
        mb.exec();
        return;
    }
    std::ifstream source_code_file(source_code_file_name.toStdString());
    if(source_code_file.is_open() == false){
        QMessageBox mb;
        mb.setText("Unable to open file");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.setWindowTitle("Error");
        mb.exec();
        return;
    }
    else{
        std::string line;
        while(getline(source_code_file, line)){
            ui->TextEditor->append(QString::fromStdString(line));
        }
    }
}

void MainWindow::on_actionSave_Source_Code_triggered(){
    bool status;
    QString file_name = QFileDialog::getSaveFileName(this, "Save", QDir::currentPath(), "All files (*.*);;Assembly Source Code (*.8asm)");
    std::ofstream file(file_name.toStdString());
    if(!file.is_open()){
        QMessageBox mb;
        mb.setText("Failed to save file");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.setWindowTitle("Error");
        mb.exec();
        return;
    }
    foreach(QString line, ui->TextEditor->toPlainText().split(QRegExp("[\r\n]"))){
        file << line.toStdString() << std::endl;
    }
}
