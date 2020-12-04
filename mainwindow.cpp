#include <iostream>
#include <string>
#include <QMainWindow>
#include <QMessageBox>
#include <vector>

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

// FORMATTING:


bool caseSensitive = false;
bool isRabinKarp = true;
bool isBoyerMoore = false;

MainWindow::~MainWindow() {
    delete ui;

}


void MainWindow::on_pushButton_clicked() { // run search button
    std::string getSearch = ui->lineEdit->text().toStdString(); // gets string from textbox

    if (getSearch.compare("") == 0) { // if no input to search
        QMessageBox::about(this, "Input Error", "Please enter something to search");
    }

    if (caseSensitive) {
        if (isBoyerMoore) {
            Boyer_Moore* Boyer_Moore1 = new Boyer_Moore("testing", getSearch, false, true);
            Boyer_Moore1->search(false);
        } else {
            Rabin_Karp* Rabin_Karp1 = new Rabin_Karp("testing", getSearch, false, true);
            Rabin_Karp1->search(false);
        }
    } else {
        if (isBoyerMoore) {
            Boyer_Moore* Boyer_Moore1 = new Boyer_Moore("testing", getSearch, false, false);
            Boyer_Moore1->search(false);
        } else {
            Rabin_Karp* Rabin_Karp1 = new Rabin_Karp("testing", getSearch, false, false);
            Rabin_Karp1->search(false);
        }
    }
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
