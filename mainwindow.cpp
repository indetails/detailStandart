#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deviceStruct.h"


ventilation_unit myVentilationUnit;
int totalPartNumber = 0 ;
int totalDigitalOutput = 0;
int totalDigitalInput = 0;
int totalAnalogInput = 0;
int totalAnalogOutput = 0;
int totalWidthRail1 = 0;
int totalWidthRail2 = 0;
int totalWidthRail3 = 0;
int totalDeviceType;
double totalAssembleTime = 0;
double totalEstimatedPrice = 0;
double totalProductionTime = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_Visuals();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup_Visuals()
{
    ui->swHeater->setCurrentIndex(0);
    ui->swHumidity->setCurrentIndex(0);
    ui->swPressure->setCurrentIndex(0);
    ui->swPanel->setCurrentIndex(0);
    ui->swCooler->setCurrentIndex(0);
    ui->swVentilation->setCurrentIndex(0);
}

void MainWindow::on_b_add_ventilation_clicked()
{
    ui->swVentilation->setCurrentIndex(1);
}

void MainWindow::on_bChooseVentilation_clicked()
{
    totalDeviceType =  totalDeviceType + 4;
    for (int i=0;i<ui->sbMotorQuantity->value();i++){
        myVentilationUnit.motor[i].id=i;
        if (ui->cbMotorRatedVoltage->currentIndex()==0){
            myVentilationUnit.motor[i].working_voltage = 220;
        }
        else if (ui->cbMotorRatedVoltage->currentIndex()==1) {
            myVentilationUnit.motor[i].working_voltage = 380;
        }
        if (ui->cbMotorRatedPower->currentIndex()==0){
            myVentilationUnit.motor[i].power = 250;
        }
        else if (ui->cbMotorRatedPower->currentIndex()==1) {
            myVentilationUnit.motor[i].power = 370;
        }

        myVentilationUnit.motor[i].current = myVentilationUnit.motor[i].power /
                                                    myVentilationUnit.motor[i].working_voltage;

        myVentilationUnit.motorProtector[i].current = myVentilationUnit.motor[i].current;
        myVentilationUnit.motorProtector[i]=addPart("motorProtector",myVentilationUnit.motorProtector[i]);
        myVentilationUnit.motorAuxContact[i]=addPart("motorAuxContact",myVentilationUnit.motorAuxContact[i]);
        myVentilationUnit.motorContactor[i].current = myVentilationUnit.motor[i].current;
        myVentilationUnit.motorContactor[i]=addPart("motorContactor",myVentilationUnit.motorContactor[i]);
        //  addConnection();
        //  addCable();
        //  addWork();

    }

    ui->leTotalPart->setText(QString::number(totalPartNumber));
    ui->leEstimatedPrice->setText(QString::number(totalEstimatedPrice));
    ui->leDigitalInput->setText(QString::number(totalDigitalInput));
    ui->leDigitalOutput->setText(QString::number(totalDigitalOutput));

    ui->swVentilation->setStyleSheet("QStackedWidget{\nbackground-color: rgba(33, 33, 33,75);\nfont: 11pt;\nborder-width :2px;\nborder-color: rgb(0, 85, 0);\nborder-radius : 8px;\nborder-style : solid;\n}");
}

device MainWindow::addPart(QString type, device part)
{
    if (type == "motorProtector")
    {

        if ((part.current >= 0.9) && (part.current < 1.25))
        {
            part.id = totalPartNumber + 1;
            part.manufacterer = "Siemens";
            part.order_number = "3RV2011-0KA10";
            part.estimated_price = 145;
            part.vendor = "Harmes";
            part.noOfDigOutput = 1;
            part.assemble_time = 30;

        }
        else if((part.current >= 1.25) && (part.current < 1.6))
        {

            part.id = totalPartNumber + 1;
            part.manufacterer = "Siemens";
            part.order_number = "3RV2011-0AA10";
            part.estimated_price = 155;
            part.vendor = "Harmes";
            part.noOfDigOutput = 1;
            part.assemble_time = 30;
        }
    }

    if(type == "motorAuxContact")
    {

        part.id = totalPartNumber + 1;
        part.manufacterer = "Siemens";
        part.order_number = "3RV3RV2901-1D";
        part.estimated_price = 145;
        part.vendor = "Harmes";
        part.noOfDigInput=1;

    }

    if(type == "motorContactor")
    {
        part.id = totalPartNumber + 1;
        part.manufacterer = "Siemens";
        part.order_number = "3RT2016-1BB41";
        part.estimated_price = 90;
        part.vendor = "Harmes";
        part.noOfDigOutput=1;
    }

    totalPartNumber++;
    totalDigitalInput = totalDigitalInput + part.noOfDigInput;
    totalDigitalOutput = totalDigitalOutput + part.noOfDigOutput;
    totalEstimatedPrice = totalEstimatedPrice + part.estimated_price;

    return part;
}

void MainWindow::on_btnGenerateBOM_clicked()
{
    QString filePath = "d:\\file.csv";
    QFile file(filePath);
    if (file.open(QFile::WriteOnly|QFile::Truncate))
    {
     for (int i=0;i<ui->sbMotorQuantity->value();i++)
     {
        QTextStream stream(&file);
        stream << myVentilationUnit.motorProtector[i].id << ";" <<myVentilationUnit.motorProtector[i].order_number << ";" <<myVentilationUnit.motorProtector[i].manufacterer<< ";" <<myVentilationUnit.motorProtector[i].estimated_price<< ";" << "\n";
     }
     file.close();
    }
    int partNo=0;
    QString filePath2 = "d:\\BOM.csv";
    QFile file2(filePath2);
    if (file2.open(QFile::WriteOnly|QFile::Truncate))
    {

        QTextStream stream(&file2);
        stream << ++partNo << ";" <<myVentilationUnit.motorProtector[0].order_number << ";" <<myVentilationUnit.motorProtector[0].manufacterer<< ";" <<myVentilationUnit.motorProtector[0].estimated_price<< ";" << "\n";
        stream << ++partNo << ";" <<myVentilationUnit.motorAuxContact[0].order_number << ";" <<myVentilationUnit.motorAuxContact[0].manufacterer<< ";" <<myVentilationUnit.motorAuxContact[0].estimated_price<< ";" << "\n";
        stream << ++partNo << ";" <<myVentilationUnit.motorContactor[0].order_number << ";" <<myVentilationUnit.motorContactor[0].manufacterer<< ";" <<myVentilationUnit.motorContactor[0].estimated_price<< ";" << "\n";
     file.close();
    }

}
