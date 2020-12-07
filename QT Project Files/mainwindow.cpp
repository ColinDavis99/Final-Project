#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string_search_I.h"

//Driver Code & Test Cases

// Making an object:
// [Rabin_Karp/Boyer_Moore] [Object Name](input file or string, what you want to search for, is it a file input?, is it case sensitive?)
// Example: Rabin_Karp Rabin_Karp1("AbCdEfG", "AbCdEfG", false, false);
// Operation: Will search for "ABC" in "AbCdEfG", it is not a file, it will not worry about capial letters
// Result: It will be found 1 time
// -----------------------
// Running a Search:
// [Object Name].search(do you want to supress the output to the terminal?)
// Example Rabin_Karp1.search(true);
// Operation: Will not spam the terminal with count and indexes. (useful when calculating average runtime)

void getAverageRunTime(Boyer_Moore Boyer_Moore_Obj, int numTrials);

void getAverageRunTime(Boyer_Moore Boyer_Moore_Obj, int numTrials) {

    double mean = 0;
    int i = 0;
    Boyer_Moore_Obj.search(true); // get outliers out of the way first
    Boyer_Moore_Obj.search(true);
    Boyer_Moore_Obj.search(true);
    while (i != numTrials) {
        Boyer_Moore_Obj.search(true);
        mean += Boyer_Moore_Obj.getRunTime();
        i++;

    }

    mean /= (double)numTrials;

    std::cout << "The mean runtime for " << Boyer_Moore_Obj.getTag() << " is " << mean << " microseconds" << std::endl;
}

void getAverageRunTime(Rabin_Karp Rabin_Karp_Obj, int numTrials);

void getAverageRunTime(Rabin_Karp Rabin_Karp_Obj, int numTrials) {

    double mean = 0;
    int i = 0;
    Rabin_Karp_Obj.search(true); // get outliers out of the way first
    Rabin_Karp_Obj.search(true);
    Rabin_Karp_Obj.search(true);
    while (i != numTrials) {
        Rabin_Karp_Obj.search(true);
        mean += Rabin_Karp_Obj.getRunTime();
        i++;

    }

    mean /= (double)numTrials;

    std::cout << "The mean runtime for " << Rabin_Karp_Obj.getTag() << " is " << mean << " microseconds" << std::endl;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // set to the main page by default

    //Rabin_Karp Rabin_Karp1("WELCOMETOONLINECOLLEGE", "COLLEGE", false, true);
        //Rabin_Karp1.search(false);

        //Boyer_Moore Boyer_Moore1("WELCOMETOONLINECOLLEGE", "COLLEGE", false, true); // makes a boyer_moore object
        //Boyer_Moore1.search(false); // runs the boyer_moore search algorith on the object



        //Boyer_Moore Boyer_Moore2("testing123", "123", false, false);
        //getAverageRunTime(Boyer_Moore2, 10);

        //Rabin_Karp Rabin_Karp2("blackhat2014.txt", "the", true, false);
        //Rabin_Karp2.search(true);s

        //EXAMPLE: Calculates mean runtime for Boyer_Moore 2
        //getAverageRunTime(Boyer_Moore2, 10);

        // EXAMPLE: Calculates mean runtime for Rabin_Karp2
        //int mean2 = 0;
        //for (int i = 0; i < 10; i++) {
            //Rabin_Karp2.search(true);
            //mean2 += Rabin_Karp2.getRunTime();
        //}
        //mean2 /= 10;
        //std::cout << "The mean runtime for Rabin_Karp2 was " << mean2 << " microseconds" << std::endl;

}

//GRAPHING

QVector <double> RKsizes, BMsizes, RKruntimes, BMruntimes;
int timesRun = 0;

void MainWindow::makePlot() {

    timesRun++;

    if (timesRun > 0) {
       ui->customPlot->removeGraph(0);
       ui->customPlot->removeGraph(1);
    }

    // add two new graphs and set their look:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::darkGreen)); // line color blue for first graph
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::darkGreen, Qt::darkGreen, 7));
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::red, 7));
    ui->customPlot->xAxis->setLabel("Number of characters searched");
    ui->customPlot->yAxis->setLabel("Runtime in microseconds");
    //set names of graphs
    ui->customPlot->graph(0)->setName("Rabin-Karp");
    ui->customPlot->graph(1)->setName("Boyer-Moore");

    QFont pfont("Newyork",14);
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(14);

    ui->customPlot->xAxis->setLabelFont(pfont);
    ui->customPlot->yAxis->setLabelFont(pfont);

    if (timesRun > 0) {
        // adding legend display
        ui->customPlot->legend->setVisible(true);
        QFont legendFont = font();  // start out with MainWindow's font..
        legendFont.setPointSize(9); // and make a bit smaller for legend
        ui->customPlot->legend->setFont(legendFont);
        ui->customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
        ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    }

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(RKsizes, RKruntimes);
    ui->customPlot->graph(1)->setData(BMsizes, BMruntimes);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->customPlot->graph(0)->rescaleAxes();

    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->customPlot->graph(1)->rescaleAxes(true);

    // Note: we could have also just called ui->customPlot->rescaleAxes(); instead

    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->customPlot->replot();

}


// FORMATTING:


bool caseSensitive = false;
bool isRabinKarp = true;
bool isBoyerMoore = false;
bool usingFile = false;
bool supressOutput = false;
bool isFileReady = false;
std::string fileString;

MainWindow::~MainWindow() {
    delete ui;

}


void MainWindow::on_pushButton_clicked() { // run search button
    std::string getSearch = ui->lineEdit->text().toStdString(); // gets search from textbox
    std::string getSource; // gets source (what you are searching through) from textbox
    if (usingFile) {
       getSource = fileString;
    } else {
       getSource = ui->lineEdit_2->text().toStdString(); // gets source (what you are searching through) from textbox
    }

    if (getSearch.compare("") == 0) { // if no input to search
        QMessageBox::about(this, "Input Error", "Please enter something to search");
        return;
    }

    if (getSource.compare("") == 0 && !usingFile) { // if no input to search in (source)
        if (!usingFile) {
            QMessageBox::about(this, "Input Error", "Please enter something to search through");
        } else {
            if (!isFileReady) {
                QMessageBox::about(this, "File is not ready", "File is still processing, you selected a large one didn't you?");
            }
        }
        return;
    }

    Boyer_Moore* Boyer_Moore1;
    Rabin_Karp* Rabin_Karp1;

    if (isBoyerMoore) {
            Boyer_Moore1 = new Boyer_Moore(getSource, getSearch, false, caseSensitive);
            Boyer_Moore1->search(supressOutput);
    } else {
            Rabin_Karp1 = new Rabin_Karp(getSource, getSearch, false, caseSensitive);
            Rabin_Karp1->search(supressOutput);
    }


    // Setting Labels with results & formatting
    QString occurencesLabel = "The string '";
    occurencesLabel += QString::fromStdString(getSearch);
    occurencesLabel += "' was found ";
    std::string runtimeLabel = "This search took ";
    std::string runtime;

    if (isBoyerMoore) {
        occurencesLabel += QString::number(Boyer_Moore1->getOccurrences());
        if (Boyer_Moore1->getOccurrences() == 1) {
            occurencesLabel += " time";
        } else {
            occurencesLabel += " times";
        }
        ui->label_7->setText(occurencesLabel);

        std::string runtime = std::to_string(Boyer_Moore1->getRunTime());
        runtime.erase(runtime.find_last_not_of('0') + 1, std::string::npos); // removes trailing zeros from result after to_string formatting
        if (runtime[runtime.length()-1] == '.') { // special case where it is an integer. Ex: 19.00000 would become 19. so we make it 19.0
            runtime += '0';
        }
        runtimeLabel += runtime;
        runtimeLabel += " microseconds";
        ui->label_8->setText(QString::fromStdString(runtimeLabel)); // set runtime label

        ui->label_9->setText(QString::fromStdString(Boyer_Moore1->getBadCharTableHTML())); // set HTMl table

        BMsizes.push_back((double)getSource.length()); // push size of source (num of character) to sizes vector for plotting x axis
        BMruntimes.push_back(Boyer_Moore1->getRunTime());

    } else {
        occurencesLabel += QString::number(Rabin_Karp1->getOccurrences());
        if (Rabin_Karp1->getOccurrences() == 1) {
            occurencesLabel += " time";
        } else {
            occurencesLabel += " times";
        }
        ui->label_7->setText(occurencesLabel);

        std::string runtime = std::to_string(Rabin_Karp1->getRunTime());
        runtime.erase(runtime.find_last_not_of('0') + 1, std::string::npos); // removes trailing zeros from result after to_string formatting
        if (runtime[runtime.length()-1] == '.') { // special case where it is an integer. Ex: 19.00000 would become 19. so we make it 19.0
            runtime += '0';
        }
        runtimeLabel += runtime;
        runtimeLabel += " microseconds";
        ui->label_8->setText(QString::fromStdString(runtimeLabel));

        QString searchHash = "The hash of ";
        searchHash += ui->lineEdit->text();
        searchHash += " is: ";
        searchHash += QString::fromStdString(Rabin_Karp1->getHash());
        ui->label_9->setText(searchHash); // set search string hash for Rabin-Karp

        RKsizes.push_back((double)getSource.length()); // push size of source (num of character) to sizes vector for plotting x axis
        RKruntimes.push_back(Rabin_Karp1->getRunTime());
    }

    MainWindow::makePlot(); // graph results

}

void MainWindow::on_checkBox_stateChanged(int arg1) {
    if (arg1 == 0) {
        caseSensitive = false;
    } else {
        caseSensitive = true;
    }
}

void MainWindow::on_radioButton_clicked() { // Rabin-Karp selector
    isRabinKarp = true;
    isBoyerMoore = false;
}




void MainWindow::on_radioButton_2_clicked() { // Boyer-Moore selector
    isBoyerMoore = true;
    isRabinKarp = false;
}

QString file_name = "default";
void MainWindow::on_pushButton_2_clicked() { // Choose file button
    if (file_name.compare("default") == 0) { // if theres no file selected yet
        file_name = QFileDialog::getOpenFileName(this, "Choose a file", "C://");\
        QFile file(file_name);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::about(this, "Error with file", "File was not open");
        }
        usingFile = true;
        ui->label_6->setText(file_name); // set file name label
        QTextStream in(&file);
        QString contents = in.readAll();
        file.close();
        fileString = contents.toStdString(); //QString to std::string
        isFileReady = true;
        ui->pushButton_2->setText("Remove File");
    } else {
        usingFile = false;
        ui->pushButton_2->setText("Choose File");
        ui->label_6->setText("Ex: file.txt");
        file_name = "default";
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1) { // supress log output
    if (arg1 == 0) {
        supressOutput = false;
    } else {
        supressOutput = true;
    }
}

void MainWindow::on_pushButton_3_clicked() { // Graph results button
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked() { // go back to main window from graphing window
    ui->stackedWidget->setCurrentIndex(0);
}
