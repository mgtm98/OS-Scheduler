#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    topLayout = new QHBoxLayout;
    rightLayout = new QVBoxLayout;
    leftLayout = new QVBoxLayout;
    topLeftLayout = new QHBoxLayout;
    botLeftLayout = new QHBoxLayout;

    unitTimeSlider = new QSlider(Qt::Horizontal);
    unitTimelbl = new QLabel("Time unit (ms) ");
    schedularType = new QComboBox();
    processesTable = new QTableWidget;
    newBtn = new QPushButton("New");
    runBtn = new QPushButton("Run");
    clearBtn = new QPushButton("Clear");

    progressBarScrollArea = new QScrollArea();
    progressLayout = new QFormLayout();

    infoLayout = new QFormLayout;

    ganttChart = new GanttChart;

    simulationTimer = new QTimer();

    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainLayout);
    mainLayout->addLayout(topLayout);
    topLayout->addLayout(leftLayout);
    topLayout->addLayout(rightLayout);
    leftLayout->addLayout(topLeftLayout);
    mainLayout->addWidget(ganttChart);

    topLeftLayout->addWidget(unitTimelbl);
    topLeftLayout->addWidget(unitTimeSlider);
    topLeftLayout->addWidget(schedularType);
    leftLayout->addWidget(processesTable);
    leftLayout->addLayout(botLeftLayout);
    botLeftLayout->addWidget(newBtn);
    botLeftLayout->addWidget(clearBtn);
    botLeftLayout->addWidget(runBtn);

    rightLayout->addWidget(progressBarScrollArea);
    progressBarScrollArea->setLayout(progressLayout);
    progressLayout->setSpacing(10);

    rightLayout->addLayout(infoLayout);
    infoLayout->addRow("PID : ", new QLabel(""));
    infoLayout->addRow("Process Name : ", new QLabel(""));
    infoLayout->addRow("Exe time : ", new QLabel(""));

    schedularType->setMinimumWidth(200);

    processesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    initSchedularTable(WITHOUT_PRIORITY);

    schedularType->addItems({"Round Robin", "First Come First Server (FCFS)",
                             "Shortest Job First (SJF)", "Priority"});

    ganttChart->setMaximumHeight(200);

    simulationTimer->start(1000);

    connect(newBtn, &QPushButton::clicked, this, &MainWindow::addNewProcess);
    connect(processesTable, &QTableWidget::itemChanged, this, &MainWindow::processesTableItemChanged);
    connect(clearBtn,  &QPushButton::clicked, this, &MainWindow::clearProcess);
    connect(unitTimeSlider, &QSlider::valueChanged, this, &MainWindow::unitTimeSliderValueChanged);
    connect(simulationTimer, &QTimer::timeout, this, &MainWindow::callback);
}

void MainWindow::initSchedularTable(SchedularTable type){
    if(type == SchedularTable::PRIORITY){
        processesTable->setColumnCount(4);
        processesTable->setHorizontalHeaderLabels({"PID", "Arrival Time", "Burst Time", "Priority"});
    }else{
        processesTable->setColumnCount(3);
        processesTable->setHorizontalHeaderLabels({"PID", "Arrival Time", "Burst Time"});
    }
}

void MainWindow::addNewProcess(){
    processesTable->insertRow(processesTable->rowCount());
}

void MainWindow::processesTableItemChanged(QTableWidgetItem *item){
    if(item->column() == 0){
        if(item->text().compare("")){
            QProgressBar *bar = new QProgressBar();
            bar->setValue(100);
            QString pid = item->text() + " : ";
            QLabel *pidLabel = new QLabel(pid);
            progressLayout->addRow(pidLabel, bar);
            progressBarMap.insert(item->row(), QPair<QLabel*, QProgressBar*>(pidLabel, bar));
        }
    }
}

void MainWindow::clearProcess(){
    int activeRow = processesTable->selectedItems()[0]->row();
    progressLayout->takeRow(progressBarMap[activeRow].second);
    delete progressBarMap[activeRow].second;
    delete progressBarMap[activeRow].first;
    progressBarMap.remove(activeRow);
    processesTable->removeRow(activeRow);
}

void MainWindow::unitTimeSliderValueChanged(int value){
    unitTimelbl->setText("Time uint (ms) " + QString::number(value * 50) + " : ");
}

void MainWindow::callback(){
}

MainWindow::~MainWindow(){
}