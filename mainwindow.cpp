#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"
#include "general_object.h"

#include <fstream>
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->layers->InitHeadCount(1);

    Parser parser;

    std::cout << "GeneralObject: " << sizeof(GeneralObject) << std::endl;
    std::ifstream in("C:/Users/Robot/Documents/Sample/xmas_dragon_long.gcode", std::ios::in | std::ios::binary);
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    in.seekg(0, std::ios::beg);

    std::vector<char> data(size);
    in.read(data.data(), data.size());

    ParserDispatch dispatch;
    parser.ReadFromMemory({data.data(), data.size()}, dispatch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

