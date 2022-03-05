#include <iostream>
#include <fstream>
#include <sstream>
#include "headers/ClassifierHeader.h"
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>

std::string format(std::string str){
    int index = 0;
    std::string output = "";
    for (int i = str.length() -1; i >= 0 ; i--) {
        if(str.at(i) == '0'){
            index = i;
            }
        else
            {
                for(int j = index; j > 0; j--){
                    output += str.at(index - j);

                }
                if (index == 0)
                    output = str;
                break;
            }
    }

    index = str.find('.');
    if(index == output.length() - 1){
        output.erase(index);
    }
    return output;
}
std::string 
tolower(std::string str){
    int n = str.length();
    std::for_each(str.begin(), str.end(), [](char & c){
        c = ::tolower(c);
    });
    return str;
}

void BayesianClassifier::readData(double trainset, int n_rows){
    std::string label;
    int trainSet = std::round(trainset * n_rows);
    
    int testSet = n_rows - trainSet;

    if((trainSet % 3 != 0) || (testSet % 3 != 0)){
        std::cout << "train Set or test Set must be equally distributed to all the features!" << 
                     "\nTry the following [0.8, 0.6, 0.5, 0.4]" << std::endl;
        return;
    }
    int trainSetCNT = trainSet / 3;
    int testSetCNT = testSet / 3;
    trainSetFeatureCNT = trainSetCNT;
    testSetFeatureCNT = testSetCNT;
    std::string line, word;
    int index = 0;
    int column = 0;
    numInstances = 0;
    std::fstream file ("../data/iris.csv", std::ios::in);
    if(file.is_open()){
        bool begin = false;
        while(getline(file, line)){
            std::stringstream str(line);
            
            if(index < trainSetCNT)
                ++numInstances;

            // Getting Labels
            if(!begin){
                while(getline(str, word, ',')){
                }
                begin = true;
            }
            
            column = 0;
            while(getline(str, word, ',')){
                if(index < trainSetCNT){
                    switch(column){
                        case 0:
                            sepal_length.push_back(toDouble(word));
                            break;
                        case 1:
                            sepal_width.push_back(toDouble(word));
                            break;
                        case 2:
                            petal_length.push_back(toDouble(word));
                            break;
                        case 3:
                            petal_width.push_back(toDouble(word));
                            break;
                        case 4:
                            labels.push_back(word);
                            break;
                        
                    }
                }
                else if(index >= trainSetCNT && index <= trainSetCNT + testSetCNT){
                    switch(column){
                        case 0:
                            test_sepal_length.push_back(toDouble(word));
                            break;
                        case 1:
                            test_sepal_width.push_back(toDouble(word));
                            break;
                        case 2:
                            test_petal_length.push_back(toDouble(word));
                            break;
                        case 3:
                            test_petal_width.push_back(toDouble(word));
                            break;
                        case 4:
                            test_labels.push_back(word);
                            break;
                    }
                }
                ++column;
            }
            ++index;
            if(index == trainSetCNT + testSetCNT)
                index = 0;
        }
        file.close();
        --numInstances;
    }else{
        std::cout << "Warning: Check Dataset File Path.";
        std::cout << std::endl << "Must belong to \"ProjectPath\"/data/iris.csv" << std::endl;
    }
}

void BayesianClassifier::readData(){
    std::string label;
    std::string line, word;
    int index = 0;
    int column = 0;
    std::fstream file ("../data/iris.csv", std::ios::in);
    if(file.is_open()){
        bool begin = false;
        while(getline(file, line)){
            std::stringstream str(line);
            
            // Getting Labels
            if(!begin){
                while(getline(str, word, ',')){
                }
                begin = true;
            }

            column = 0;
            while(getline(str, word, ',')){
                if(index < 40){
                    ++numInstances;
                    switch(column){
                        case 0:
                            sepal_length.push_back(toDouble(word));
                            break;
                        case 1:
                            sepal_width.push_back(toDouble(word));
                            break;
                        case 2:
                            petal_length.push_back(toDouble(word));
                            break;
                        case 3:
                            petal_width.push_back(toDouble(word));
                            break;
                        case 4:
                            labels.push_back(word);
                            break;
                        
                    }
                }
                else if(index >= 40 && index <= 50){
                    switch(column){
                        case 0:
                            test_sepal_length.push_back(toDouble(word));
                            break;
                        case 1:
                            test_sepal_width.push_back(toDouble(word));
                            break;
                        case 2:
                            test_petal_length.push_back(toDouble(word));
                            break;
                        case 3:
                            test_petal_width.push_back(toDouble(word));
                            break;
                        case 4:
                            test_labels.push_back(word);
                            break;
                    }
                }
                ++column;
            }
            ++index;
            if(index == 50)
                index = 0;
        }
        file.close();
    }else{
        std::cout << "Warning: Check Dataset File Path.";
        std::cout << std::endl << "Must belong to \"ProjectPath\"/data/iris.csv" << std::endl;
    }
}

std::string BayesianClassifier::ShowDataset(){
    std::string str_output = "";
    for(unsigned i = 0; i < sepal_length.size(); i++)
        str_output += 
        format(std::to_string(sepal_length[i])) + "\t| " 
        + format(std::to_string(sepal_width[i])) + "\t| "
        + format(std::to_string(petal_length[i])) + "\t| "
        + format(std::to_string(petal_width[i])) + "\t| "
        + labels[i] + "\n";

    return str_output;
}

double BayesianClassifier::getSetosa_SepalLengthND(double data){ 
    double NormalDistribution = (1. / (sqrt(2. * 3.14) * stDevSetosaSL)) * 
                                exp(- pow(data - Setosa_SepalLengthMean, 2.) / (2. * stDevSetosaSL*stDevSetosaSL) );

    return NormalDistribution;
}

double BayesianClassifier::getSetosa_SepalWidthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevSetosaSW)) * exp(-pow(data - Setosa_SepalWidthMean, 2.) / (2. * pow(stDevSetosaSW, 2.)) );

    return NormalDistribution;
}

double BayesianClassifier::getSetosa_PetalLengthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevSetosaPL)) * exp(-pow(data - Setosa_PetalLengthMean, 2.) / (2. * pow(stDevSetosaPW, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getSetosa_PetalWidthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevSetosaPW)) * exp(-pow(data - Setosa_PetalWidthMean, 2.) / (2. * pow(stDevSetosaPW, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVersicolor_SepalLengthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVersicolorSL)) * exp(-pow(data - Versicolor_SepalLengthMean, 2.) / (2. * pow(stDevVersicolorSL, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVersicolor_SepalWidthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVersicolorSW)) * exp(-pow(data - Versicolor_SepalWidthMean, 2.) / (2. * pow(stDevVersicolorSW, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVersicolor_PetalLengthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVersicolorPL)) * exp(-pow(data - Versicolor_PetalLengthMean, 2.) / (2. * pow(stDevVersicolorPL, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVersicolor_PetalWidthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVersicolorPW)) * exp(-pow(data - Versicolor_PetalWidthMean, 2.) / (2. * pow(stDevVersicolorPW, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVirginica_SepalLengthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVirginicaSL)) * exp(-pow(data - Virginica_SepalLengthMean, 2.) / (2. * pow(stDevVirginicaSL, 2.)) );
   
    return NormalDistribution;
}

double BayesianClassifier::getVirginica_SepalWidthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVirginicaSW)) * exp(-pow(data - Virginica_SepalWidthMean, 2.) / (2. * pow(stDevVirginicaSW, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVirginica_PetalLengthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVirginicaPL)) * exp(-pow(data - Virginica_PetalLengthMean, 2.) / (2. * pow(stDevVirginicaPL, 2.)) );
    
    return NormalDistribution;
}

double BayesianClassifier::getVirginica_PetalWidthND(double data){
    double NormalDistribution = (1. / (sqrt(2. * PI) * stDevVirginicaPW)) * exp(-pow(data - Virginica_PetalWidthMean, 2.) / (2. * pow(stDevVirginicaPW, 2.)) );
    
    return NormalDistribution;
}


void BayesianClassifier::GaussianNBTrain(){
    // Init count Labels;
    Labels l = Labels();
    int countl = 0;
    std::vector<std::string>::iterator itstr, prevstr;
    for(itstr = labels.begin(), prevstr=labels.begin(); itstr != labels.end(); prevstr=itstr, ++itstr){ 
        if (*prevstr == *itstr){
            ++countl;
        }else{
            if(*prevstr == "Iris-setosa"){
                l.setSetosa(countl);

            }
            if(*prevstr == "Iris-versicolor"){
                countl++;
                l.setVersicolor(countl);
            }
            countl = 0;
        }
    }
    if(*prevstr == "Iris-virginica"){
        countl++;
        l.setVirginica(countl);
    }
    frequencyLabel = l;

    double cnt = 0;
    double sumSL = 0, sumSW = 0, sumPL = 0, sumPW = 0;
    // Calculating Setosa Means
    for(unsigned int i = 0; i < frequencyLabel.getSetosa(); ++i){
        sumSL += sepal_length[i];
        sumSW += sepal_width[i];
        sumPL += petal_length[i];
        sumPW += petal_width[i];
        cnt++;
    }

    Setosa_SepalLengthMean = (double)sumSL / (double)cnt;
    Setosa_SepalWidthMean = (double)sumSW / (double)cnt;
    Setosa_PetalLengthMean = (double)sumPL / (double)cnt;
    Setosa_PetalWidthMean = (double)sumPW / (double)cnt;

    // Calculating Setosa Standard Deviation...
    double stDevsumSetosaSL = 0, stDevsumSetosaSW = 0, stDevsumSetosaPL = 0, stDevsumSetosaPW = 0;
    for(unsigned int i = 0; i < frequencyLabel.getSetosa(); ++i){
        stDevsumSetosaSL += pow(sepal_length[i] - Setosa_SepalLengthMean, 2.);
        stDevsumSetosaSW += pow(sepal_width[i] - Setosa_SepalWidthMean, 2.);
        stDevsumSetosaPL += pow(petal_length[i] - Setosa_PetalLengthMean, 2.);
        stDevsumSetosaPW += pow(petal_width[i] - Setosa_PetalWidthMean, 2.);
    }
    stDevSetosaSL = pow( (1. /((double)numInstances - 1.) * stDevsumSetosaSL), 0.5);
    stDevSetosaSW = pow( (1. /((double)numInstances - 1.) * stDevsumSetosaSW), 0.5);
    stDevSetosaPL = pow( (1. /((double)numInstances - 1.) * stDevsumSetosaPL), 0.5);
    stDevSetosaPW = pow( (1. /((double)numInstances - 1.) * stDevsumSetosaPW), 0.5);

    cnt = 0;
    sumSL = 0;
    sumSW = 0;
    sumPL = 0;
    sumPW = 0;

    // Calculating Versicolor Means...
    for(unsigned int i = frequencyLabel.getVersicolor(); i < frequencyLabel.getSetosa() + frequencyLabel.getVersicolor(); ++i){
        sumSL += sepal_length[i];
        sumSW += sepal_width[i];
        sumPL += petal_length[i];
        sumPW += petal_width[i];
        cnt++;
    }
    Versicolor_SepalLengthMean = sumSL / cnt;
    Versicolor_SepalWidthMean = sumSW / cnt;
    Versicolor_PetalLengthMean = sumPL / cnt;
    Versicolor_PetalWidthMean = sumPW / cnt;

    // Calculating Versicolor Standard Deviation...
    double stDevsumVersicolorSL = 0, stDevsumVersicolorSW = 0, stDevsumVersicolorPL = 0, stDevsumVersicolorPW = 0;
    for(unsigned int i = frequencyLabel.getVersicolor(); i < frequencyLabel.getSetosa() + frequencyLabel.getVersicolor(); ++i){
        stDevsumVersicolorSL += pow(sepal_length[i] - Versicolor_SepalLengthMean, 2.);
        stDevsumVersicolorSW += pow(sepal_width[i] - Versicolor_SepalWidthMean, 2.);
        stDevsumVersicolorPL += pow(petal_length[i] - Versicolor_PetalLengthMean, 2.);
        stDevsumVersicolorPW += pow(petal_width[i] - Versicolor_PetalWidthMean, 2.);
    }
    stDevVersicolorSL = pow( (1. / ((double)numInstances - 1.) * Versicolor_SepalLengthMean), 0.5);
    stDevVersicolorSW = pow( (1. / ((double)numInstances - 1.) * Versicolor_SepalWidthMean), 0.5);
    stDevVersicolorPL = pow( (1. / ((double)numInstances - 1.) * Versicolor_PetalLengthMean), 0.5);
    stDevVersicolorPW = pow( (1. / ((double)numInstances - 1.) * Versicolor_PetalWidthMean), 0.5);


    // Calculating Virginica mean...
    cnt = 0;
    sumSL = 0;
    sumSW = 0;
    sumPL = 0;
    sumPW = 0;
    for(unsigned int i = frequencyLabel.getVirginica() + frequencyLabel.getVersicolor(); i < frequencyLabel.getSetosa() + frequencyLabel.getVersicolor() + frequencyLabel.getVirginica(); ++i){
        sumSL += sepal_length[i];
        sumSW += sepal_width[i];
        sumPL += petal_length[i];
        sumPW += petal_width[i];
        cnt++;
    }
    Virginica_SepalLengthMean = sumSL / cnt;
    Virginica_SepalWidthMean = sumSW / cnt;
    Virginica_PetalLengthMean = sumPL / cnt;
    Virginica_PetalWidthMean = sumPW / cnt;
    
    // Calculating Virginica Standard Deviation...
    double stDevsumVirginicaSL = 0, stDevsumVirginicaSW = 0, stDevsumVirginicaPL = 0, stDevsumVirginicaPW = 0;
    for(unsigned int i = frequencyLabel.getVirginica() + frequencyLabel.getVersicolor(); i < frequencyLabel.getSetosa() + frequencyLabel.getVersicolor() + frequencyLabel.getVirginica(); ++i){
        stDevsumVirginicaSL += pow(sepal_length[i] - Virginica_SepalLengthMean, 2.);
        stDevsumVirginicaSW += pow(sepal_width[i] - Virginica_SepalWidthMean, 2.);
        stDevsumVirginicaPL += pow(petal_length[i] - Virginica_PetalLengthMean, 2.);
        stDevsumVirginicaPW += pow(petal_width[i] - Virginica_PetalWidthMean, 2.);
    }

    stDevVirginicaSL = pow( (1. / ((double)numInstances - 1.) * Virginica_SepalLengthMean), 0.5);
    stDevVirginicaSW = pow( (1. / ((double)numInstances - 1.) * Virginica_SepalWidthMean), 0.5);
    stDevVirginicaPL = pow( (1. / ((double)numInstances - 1.) * Virginica_PetalLengthMean), 0.5);
    stDevVirginicaPW = pow( (1. / ((double)numInstances - 1.) * Virginica_PetalWidthMean), 0.5);
}


void BayesianClassifier::HistogramNBTrain(){
    // Creating Labels Frequency Table
    
    // Init count Labels;
    Labels l = Labels();
    int countl = 0;
    std::vector<std::string>::iterator itstr, prevstr;
    for(itstr = labels.begin(), prevstr=labels.begin(); itstr != labels.end(); prevstr=itstr, ++itstr){ 
        if (*prevstr == *itstr){
            ++countl;
        }else{
            if(*prevstr == "Iris-setosa"){
                l.setSetosa(countl);

            }
            if(*prevstr == "Iris-versicolor"){
                countl++;
                l.setVersicolor(countl);
            }
            countl = 0;
        }
    }
    if(*prevstr == "Iris-virginica"){
        countl++;
        l.setVirginica(countl);
    }

    frequencyLabel = l;

    // Init count fields
    Sepal s = Sepal();
    int countR45set=0, countR56set=0, countR67set=0, countR78set = 0;
    int countR45ver=0, countR56ver=0, countR67ver=0, countR78ver = 0;
    int countR45vir=0, countR56vir=0, countR67vir=0, countR78vir = 0;
    
    // Define Count Sepal Length Fields
    for(unsigned int i = 0; i < sepal_length.size(); ++i){
        if(labels[i] == "Iris-setosa"){
            if((sepal_length[i] >= 4) && (sepal_length[i] < 5))
                ++countR45set;
            else if((sepal_length[i] >= 5) && (sepal_length[i] < 6))
                ++countR56set;
            else if((sepal_length[i] >= 6) && (sepal_length[i] < 7))
                ++countR67set;
            else if((sepal_length[i] >= 7) && (sepal_length[i] <= 8))
                ++countR78set;
        }
        else if(labels[i] == "Iris-versicolor"){
            if((sepal_length[i] >= 4) && (sepal_length[i] < 5))
                ++countR45ver;
            else if((sepal_length[i] >= 5) && (sepal_length[i] < 6))
                ++countR56ver;
            else if((sepal_length[i] >= 6) && (sepal_length[i] < 7))
                ++countR67ver;
            else if((sepal_length[i] >= 7) && (sepal_length[i] <= 8))
                ++countR78ver;

        }
        else if(labels[i] == "Iris-virginica"){
            if((sepal_length[i] >= 4) && (sepal_length[i] < 5))
                ++countR45vir;
            else if((sepal_length[i] >= 5) && (sepal_length[i] < 6))
                ++countR56vir;
            else if((sepal_length[i] >= 6) && (sepal_length[i] < 7))
                ++countR67vir;
            else if((sepal_length[i] >= 7) && (sepal_length[i] <= 8))
                ++countR78vir;
        }
    }
    

    // Set Count Sepal Length Fields to Objects
    Sepalfrequencies_setosa.setLengthRange4to5(countR45set);
    Sepalfrequencies_setosa.setLengthRange5to6(countR56set);
    Sepalfrequencies_setosa.setLengthRange6to7(countR67set);
    Sepalfrequencies_setosa.setLengthRange7to8(countR78set);

    Sepalfrequencies_versicolor.setLengthRange4to5(countR45ver);
    Sepalfrequencies_versicolor.setLengthRange5to6(countR56ver);
    Sepalfrequencies_versicolor.setLengthRange6to7(countR67ver);
    Sepalfrequencies_versicolor.setLengthRange7to8(countR78ver);

    Sepalfrequencies_virginica.setLengthRange4to5(countR45vir);
    Sepalfrequencies_virginica.setLengthRange5to6(countR56vir);
    Sepalfrequencies_virginica.setLengthRange6to7(countR67vir);
    Sepalfrequencies_virginica.setLengthRange7to8(countR78vir);


    // Initialize Count Sepal Width Fields
    int countR23set=0, countR34set=0; countR45set=0;
    int countR23ver=0, countR34ver=0; countR45ver=0;
    int countR23vir=0, countR34vir=0; countR45vir=0;

    //  Initialize Count Sepal Width Fields
    for(unsigned int i = 0; i < sepal_width.size(); i++){
        if(labels[i] == "Iris-setosa"){
            if((sepal_width[i] >= 2) && (sepal_width[i] < 3))
                ++countR23set;
            else if((sepal_width[i] >= 3) && (sepal_width[i] < 4))
                ++countR34set;
            else if((sepal_width[i] >= 4) && (sepal_width[i] <= 5))
                ++countR45set;
        }
        else if(labels[i] == "Iris-versicolor"){
            if((sepal_width[i] >= 2) && (sepal_width[i] < 3))
                ++countR23ver;
            else if((sepal_width[i] >= 3) && (sepal_width[i] < 4))
                ++countR34ver;
            else if((sepal_width[i] >= 4) && (sepal_width[i] <= 5))
                ++countR45ver;
        }
        else if(labels[i] == "Iris-virginica"){
            if((sepal_width[i] >= 2) && (sepal_width[i] < 3))
                ++countR23vir;
            else if((sepal_width[i] >= 3) && (sepal_width[i] < 4))
                ++countR34vir;
            else if((sepal_width[i] >= 4) && (sepal_width[i] <= 5))
                ++countR45vir;
        }
    }

    // Set Count Sepal Width to Objects
    Sepalfrequencies_setosa.setWidthRange2to3(countR23set);
    Sepalfrequencies_setosa.setWidthRange3to4(countR34set);
    Sepalfrequencies_setosa.setWidthRange4to5(countR45set);

    Sepalfrequencies_versicolor.setWidthRange2to3(countR23ver);
    Sepalfrequencies_versicolor.setWidthRange3to4(countR34ver);
    Sepalfrequencies_versicolor.setWidthRange4to5(countR45ver);

    Sepalfrequencies_virginica.setWidthRange2to3(countR23vir);
    Sepalfrequencies_virginica.setWidthRange3to4(countR34vir);
    Sepalfrequencies_virginica.setWidthRange4to5(countR45vir);


    // Initialize Count Petal Length Fields
    Petal p = Petal();
    int countR12set=0; countR34set=0; countR45set=0; countR56set=0; countR67set=0;
    int countR12ver=0; countR34ver=0; countR45ver=0; countR56ver=0; countR67ver=0;
    int countR12vir=0; countR34vir=0; countR45vir=0; countR56vir=0; countR67vir=0;

    // Define Count Petal Length Fields
    for(unsigned int i = 0; i < petal_length.size(); ++i){
        if(labels[i] == "Iris-setosa"){
            if((petal_length[i] >= 1) && (petal_length[i] <= 2))
                ++countR12set;
            else if((petal_length[i] >= 3) && (petal_length[i] < 4))
                ++countR34set;
            else if((petal_length[i] >= 4) && (petal_length[i] < 5))
                ++countR45set;
            else if((petal_length[i] >= 5) && (petal_length[i] < 6))
                ++countR56set;
            else if((petal_length[i] >= 6) && (petal_length[i] <= 7))
                ++countR67set;
        }
        else if(labels[i] == "Iris-versicolor"){
            if((petal_length[i] >= 1) && (petal_length[i] <= 2))
                ++countR12ver;
            else if((petal_length[i] >= 3) && (petal_length[i] < 4))
                ++countR34ver;
            else if((petal_length[i] >= 4) && (petal_length[i] < 5))
                ++countR45ver;
            else if((petal_length[i] >= 5) && (petal_length[i] < 6))
                ++countR56ver;
            else if((petal_length[i] >= 6) && (petal_length[i] <= 7))
                ++countR67ver;
        }
        else if(labels[i] == "Iris-virginica"){
            if((petal_length[i] >= 1) && (petal_length[i] < 2))
                ++countR12vir;
            else if((petal_length[i] >= 3) && (petal_length[i] < 4))
                ++countR34vir;
            else if((petal_length[i] >= 4) && (petal_length[i] < 5))
                ++countR45vir;
            else if((petal_length[i] >= 5) && (petal_length[i] < 6))
                ++countR56vir;
            else if((petal_length[i] >= 6) && (petal_length[i] <= 7))
                ++countR67vir;
        }
    }


    // Set Count Petal Length Fields to Objects
    Petalfrequencies_setosa.setLengthRange1to2(countR12set);
    Petalfrequencies_setosa.setLengthRange3to4(countR34set);
    Petalfrequencies_setosa.setLengthRange4to5(countR45set);
    Petalfrequencies_setosa.setLengthRange5to6(countR56set);
    Petalfrequencies_setosa.setLengthRange6to7(countR67set);

    Petalfrequencies_versicolor.setLengthRange1to2(countR12ver);
    Petalfrequencies_versicolor.setLengthRange3to4(countR34ver);
    Petalfrequencies_versicolor.setLengthRange4to5(countR45ver);
    Petalfrequencies_versicolor.setLengthRange5to6(countR56ver);
    Petalfrequencies_versicolor.setLengthRange6to7(countR67ver);

    Petalfrequencies_virginica.setLengthRange1to2(countR12vir);
    Petalfrequencies_virginica.setLengthRange3to4(countR34vir);
    Petalfrequencies_virginica.setLengthRange4to5(countR45vir);
    Petalfrequencies_virginica.setLengthRange5to6(countR56vir);
    Petalfrequencies_virginica.setLengthRange6to7(countR67vir);


    // Initialize Count Petal Width Fields
    int countR01set=0; countR12set=0; countR23set=0;
    int countR01ver=0; countR12ver=0; countR23ver=0;
    int countR01vir=0; countR12vir=0; countR23vir=0;

    // Define Count Petal Width Fields
    for(unsigned int i = 0; i < petal_width.size(); ++i){
        if(labels[i] == "Iris-setosa"){
            if((petal_width[i] >= 0) && (petal_width[i] < 1))
                ++countR01set;
            else if((petal_width[i] >= 1) && (petal_width[i] < 2))
                ++countR12set;
            else if((petal_width[i] >= 2) && (petal_width[i] < 3))
                ++countR23set;
        }
        else if(labels[i] == "Iris-versicolor"){
            if((petal_width[i] >= 0) && (petal_width[i] < 1))
                ++countR01ver;
            else if((petal_width[i] >= 1) && (petal_width[i] < 2))
                ++countR12ver;
            else if((petal_width[i] >= 2) && (petal_width[i] < 3))
                ++countR23ver;
        }
        else if(labels[i] == "Iris-virginica"){
            if((petal_width[i] >= 0) && (petal_width[i] < 1))
                ++countR01vir;
            else if((petal_width[i] >= 1) && (petal_width[i] < 2))
                ++countR12vir;
            else if((petal_width[i] >= 2) && (petal_width[i] < 3))
                ++countR23vir;
        }
    }

    // Set Count Petal Width Fields to Objects
    Petalfrequencies_setosa.setWidthRange0to1(countR01set);
    Petalfrequencies_setosa.setWidthRange1to2(countR12set);
    Petalfrequencies_setosa.setWidthRange2to3(countR23set);

    Petalfrequencies_versicolor.setWidthRange0to1(countR01ver);
    Petalfrequencies_versicolor.setWidthRange1to2(countR12ver);
    Petalfrequencies_versicolor.setWidthRange2to3(countR23ver);

    Petalfrequencies_virginica.setWidthRange0to1(countR01vir);
    Petalfrequencies_virginica.setWidthRange1to2(countR12vir);
    Petalfrequencies_virginica.setWidthRange2to3(countR23vir);
}

void BayesianClassifier::HistogramNBProbabilityResults(){
    double setosaLikelihood, versicolorLikelihood, virginicaLikelihood; // Likelihood
    double setosaProbability, versicolorProbability, virginicaProbability;  // Real Probability
    double sepal_lengthCNT, sepal_widthCNT, petal_lengthCNT, petal_widthCNT;
    bool setosaHas0 = false, versicolorHas0 = false, virginicaHas0 = false;
    for(unsigned int j = 0; j < test_labels.size(); ++j){
                std::cout << "\u001b[32mExample " << j + 1 << ":\033[0m"
                          << "\n\nCalculating probabilities for [" + test_labels[j] + "]\n"
                          << "\tSepal Length: " << test_sepal_length[j] << "\n"
                          << "\tSepal Width: " << test_sepal_width[j] << "\n"
                          << "\tPetal Length: " << test_petal_length[j] << "\n"
                          << "\tPetal Width: " << test_petal_width[j] << "\n";
        for(int i = 0 ; i < 3; i++){
            if(test_sepal_length[j] >= 4 && test_sepal_length[j] < 5){
                switch(i){
                    case 0:
                        sepal_lengthCNT = Sepalfrequencies_setosa.getLengthRange4to5();
                        break;
                    case 1:
                        sepal_lengthCNT = Sepalfrequencies_versicolor.getLengthRange4to5();
                        break;
                    case 2:
                        sepal_lengthCNT = Sepalfrequencies_virginica.getLengthRange4to5();
                        break;
                }
            }else if(test_sepal_length[j] >= 5 && test_sepal_length[j] < 6){
                switch(i){
                    case 0:
                        sepal_lengthCNT = Sepalfrequencies_setosa.getLengthRange5to6();
                        break;
                    case 1:
                        sepal_lengthCNT = Sepalfrequencies_versicolor.getLengthRange5to6();
                        break;
                    case 2:
                        sepal_lengthCNT = Sepalfrequencies_virginica.getLengthRange5to6();
                        break;
                }
            }else if(test_sepal_length[j] >= 6 && test_sepal_length[j] < 7){
                switch(i){
                    case 0:
                        sepal_lengthCNT = Sepalfrequencies_setosa.getLengthRange6to7();
                        break;
                    case 1:
                        sepal_lengthCNT = Sepalfrequencies_versicolor.getLengthRange6to7();
                        break;
                    case 2:
                        sepal_lengthCNT = Sepalfrequencies_virginica.getLengthRange6to7();
                        break;
                }
            }else if(test_sepal_length[j] >= 7 && test_sepal_length[j] <= 8){
                switch(i){
                    case 0:
                        sepal_lengthCNT = Sepalfrequencies_setosa.getLengthRange7to8();
                        break;
                    case 1:
                        sepal_lengthCNT = Sepalfrequencies_versicolor.getLengthRange7to8();
                        break;
                    case 2:
                        sepal_lengthCNT = Sepalfrequencies_virginica.getLengthRange7to8();
                        break;
                }
            }

            if(test_sepal_width[j] >= 2 && test_sepal_width[j] < 3){
                switch(i){
                    case 0:
                        sepal_widthCNT = Sepalfrequencies_setosa.getWidthRange2to3();
                        break;
                    case 1:
                        sepal_widthCNT = Sepalfrequencies_versicolor.getWidthRange2to3();
                        break;
                    case 2:
                        sepal_widthCNT = Sepalfrequencies_virginica.getWidthRange2to3();
                        break;
                }
            }else if(test_sepal_width[j] >= 3 && test_sepal_width[j] < 4){
                switch(i){
                    case 0:
                        sepal_widthCNT = Sepalfrequencies_setosa.getWidthRange3to4();
                        break;
                    case 1:
                        sepal_widthCNT = Sepalfrequencies_versicolor.getWidthRange3to4();
                        break;
                    case 2:
                        sepal_widthCNT = Sepalfrequencies_virginica.getWidthRange3to4();
                        break;
                }
            }else if(test_sepal_width[j] >= 4 && test_sepal_width[j] <= 5){
                switch(i){
                    case 0:
                        sepal_widthCNT = Sepalfrequencies_setosa.getWidthRange4to5();
                        break;
                    case 1:
                        sepal_widthCNT = Sepalfrequencies_versicolor.getWidthRange4to5();
                        break;
                    case 2:
                        sepal_widthCNT = Sepalfrequencies_virginica.getWidthRange4to5();
                        break;
                }
            }

            if(test_petal_length[j] >= 1 && test_petal_length[j] < 2){
                switch(i){
                    case 0:
                        petal_lengthCNT = Petalfrequencies_setosa.getLengthRange1to2();
                        break;
                    case 1:
                        petal_lengthCNT = Petalfrequencies_versicolor.getLengthRange1to2();
                        break;
                    case 2:
                        petal_lengthCNT = Petalfrequencies_virginica.getLengthRange1to2();
                        break;
                }
            }else if(test_petal_length[j] >= 3 && test_petal_length[j] < 4){
                switch(i){
                    case 0:
                        petal_lengthCNT = Petalfrequencies_setosa.getLengthRange3to4();
                        break;
                    case 1:
                        petal_lengthCNT = Petalfrequencies_versicolor.getLengthRange3to4();
                        break;
                    case 2:
                        petal_lengthCNT = Petalfrequencies_virginica.getLengthRange3to4();
                        break;
                }
            }else if(test_petal_length[j] >= 4 && test_petal_length[j] < 5){
                switch(i){
                    case 0:
                        petal_lengthCNT = Petalfrequencies_setosa.getLengthRange4to5();
                        break;
                    case 1:
                        petal_lengthCNT = Petalfrequencies_versicolor.getLengthRange4to5();
                        break;
                    case 2:
                        petal_lengthCNT = Petalfrequencies_virginica.getLengthRange4to5();
                        break;
                }
            }else if(test_petal_length[i] >= 5 && test_petal_length[i] < 6){
                switch(i){
                    case 0:
                        petal_lengthCNT = Petalfrequencies_setosa.getLengthRange5to6();
                        break;
                    case 1:
                        petal_lengthCNT = Petalfrequencies_versicolor.getLengthRange5to6();
                        break;
                    case 2:
                        petal_lengthCNT = Petalfrequencies_virginica.getLengthRange5to6();
                        break;
                }
            }else if(test_petal_length[j] >= 6 && test_petal_length[j] < 7){
                switch(i){
                    case 0:
                        petal_lengthCNT = Petalfrequencies_setosa.getLengthRange6to7();
                        break;
                    case 1:
                        petal_lengthCNT = Petalfrequencies_versicolor.getLengthRange6to7();
                        break;
                    case 2:
                        petal_lengthCNT = Petalfrequencies_virginica.getLengthRange6to7();
                        break;
                }
            }

            if(test_petal_width[j] >= 0 && test_petal_width[j] < 1){
                switch(i){
                    case 0:
                        petal_widthCNT = Petalfrequencies_setosa.getWidthRange0to1();
                        break;
                    case 1:
                        petal_widthCNT = Petalfrequencies_versicolor.getWidthRange0to1();
                        break;
                    case 2:
                        petal_widthCNT = Petalfrequencies_virginica.getWidthRange0to1();
                        break;
                }
            }else if(test_petal_width[j] >= 1 && test_petal_width[j] < 2){
                switch(i){
                    case 0:
                        petal_widthCNT = Petalfrequencies_setosa.getWidthRange1to2();
                        break;
                    case 1:
                        petal_widthCNT = Petalfrequencies_versicolor.getWidthRange1to2();
                        break;
                    case 2:
                        petal_widthCNT = Petalfrequencies_virginica.getWidthRange1to2();
                        break;
                }
            }else if(test_petal_width[j] >= 2 && test_petal_width[j] <= 3){
                switch(i){
                    case 0:
                        petal_widthCNT = Petalfrequencies_setosa.getWidthRange2to3();
                        break;
                    case 1:
                        petal_widthCNT = Petalfrequencies_versicolor.getWidthRange2to3();
                        break;
                    case 2:
                        petal_widthCNT = Petalfrequencies_virginica.getWidthRange2to3();
                        break;
                }
            }

            if(sepal_lengthCNT == 0 || sepal_widthCNT == 0 || petal_lengthCNT == 0 || petal_widthCNT == 0){
                switch(i){
                    case 0:
                        setosaLikelihood = ( (sepal_lengthCNT + 3/3) / (frequencyLabel.getSetosa() + 3) )* 
                                        ( (sepal_widthCNT + 3/3) / (frequencyLabel.getSetosa() + 3) )* 
                                        ( (petal_lengthCNT + 3/3) / (frequencyLabel.getSetosa() + 3) )* 
                                        ( (petal_widthCNT + 3/3) / (frequencyLabel.getSetosa() + 3) )*
                                        1./3.;

                        break;
                    case 1:
                        versicolorLikelihood = ( (sepal_lengthCNT + 1.) / (frequencyLabel.getVersicolor() + 3) )* 
                                        ( (sepal_widthCNT + 3/3) / (frequencyLabel.getVersicolor() + 3) )* 
                                        ( (petal_lengthCNT + 3/3) / (frequencyLabel.getVersicolor() + 3) )* 
                                        ( (petal_widthCNT + 3/3) / (frequencyLabel.getVersicolor() + 3) )* 
                                        (1./3.);
                        break;
                    case 2:
                        virginicaLikelihood = ( (double)(sepal_lengthCNT + 3/3) / (frequencyLabel.getVirginica() + 3) )* 
                                        ( (double)(sepal_widthCNT + 3/3) / (frequencyLabel.getVirginica() + 3) )* 
                                        ( (double)(petal_lengthCNT + 3/3) / (frequencyLabel.getVirginica() + 3) )*
                                        ( (double)(petal_widthCNT + 3/3) / (frequencyLabel.getVirginica() + 3) )* 
                                        (1./3.);
                        break;
                }
            }else{
                switch(i){
                    case 0:
                        setosaLikelihood = ((double)sepal_lengthCNT / frequencyLabel.getSetosa())* 
                                        ((double)sepal_widthCNT / frequencyLabel.getSetosa()) * 
                                        ((double)petal_lengthCNT / frequencyLabel.getSetosa()) * 
                                        ((double)petal_widthCNT / frequencyLabel.getSetosa()) * 
                                        (1./3.);

                        break;
                    case 1:
                        versicolorLikelihood = ((double)sepal_lengthCNT / frequencyLabel.getVersicolor())* 
                                        ((double)sepal_widthCNT / frequencyLabel.getVersicolor()) * 
                                        ((double)sepal_lengthCNT / frequencyLabel.getVersicolor()) * 
                                        ((double)petal_widthCNT / frequencyLabel.getVersicolor()) * 
                                        (1./3.);
                        break;
                    case 2:
                        virginicaLikelihood = ((double)sepal_lengthCNT / frequencyLabel.getVirginica())* 
                                        ((double)sepal_widthCNT / frequencyLabel.getVirginica()) * 
                                        ((double)petal_lengthCNT / frequencyLabel.getVirginica()) * 
                                        ((double)petal_widthCNT / frequencyLabel.getVirginica()) * 
                                        (1./3.);
                        break;
                }
            }
        }
        setosaProbability =     setosaLikelihood     / (setosaLikelihood + versicolorLikelihood + virginicaLikelihood);
        versicolorProbability = versicolorLikelihood / (setosaLikelihood + versicolorLikelihood + virginicaLikelihood);
        virginicaProbability =  virginicaLikelihood  / (setosaLikelihood + versicolorLikelihood + virginicaLikelihood);
        std::cout << "\nLikelihoods for each class: \n";
        std::cout << "\tLikelihood of Setosa: " << setosaLikelihood << "\n";
        std::cout << "\tLikelihood of Versicolor: " << versicolorLikelihood << "\n";
        std::cout << "\tLikelihood of Virginica: " << virginicaLikelihood << "\n";

        std::cout << "\nProbabilities for each class: \n";
        std::cout << "\tProbability of Setosa: " << setosaProbability * 100 << "%\n";
        std::cout << "\tProbability of Versicolor: " << versicolorProbability * 100 << "%\n";
        std::cout << "\tProbability of Virginica: " << virginicaProbability * 100 << "%\n";

        std::cout << "\nTotal probability: " << setosaProbability + versicolorProbability + virginicaProbability << "\n";
    }
}


void BayesianClassifier::GaussianNBProbabilityResults(){
    double setosaLikelihood, versicolorLikelihood, virginicaLikelihood; // Likelihood
    double setosaProbability, versicolorProbability, virginicaProbability;  // Real Probability

    for(unsigned int j = 0; j < test_labels.size(); ++j){
        std::cout << "\u001b[32mExample " << j + 1 << ":\033[0m"
                    << "\n\nCalculating probabilities for [" + test_labels[j] + "]\n"
                    << "\tSepal Length: " << test_sepal_length[j] << "\n"
                    << "\tSepal Width: " << test_sepal_width[j] << "\n"
                    << "\tPetal Length: " << test_petal_length[j] << "\n"
                    << "\tPetal Width: " << test_petal_width[j] << "\n";
        for(int i = 0 ; i < 3; i++){
            switch(i){
                case 0:
                    setosaLikelihood = getSetosa_SepalLengthND(test_sepal_length[j])* 
                                    getSetosa_SepalWidthND(test_sepal_width[j]) * 
                                    getSetosa_PetalLengthND(test_petal_length[j]) * 
                                    getSetosa_PetalWidthND(test_petal_width[j]) * 
                                    (1./3.);

                    break;
                case 1:
                    versicolorLikelihood = getVersicolor_SepalLengthND(test_sepal_length[j])* 
                                    getVersicolor_SepalWidthND(test_sepal_width[j]) * 
                                    getVersicolor_PetalLengthND(test_petal_length[j]) * 
                                    getVersicolor_PetalWidthND(test_petal_width[j]) * 
                                    (1./3.);
                    break;
                case 2:
                    virginicaLikelihood = getVirginica_SepalLengthND(test_sepal_length[j])* 
                                    getVirginica_SepalWidthND(test_sepal_width[j]) * 
                                    getVirginica_PetalLengthND(test_petal_length[j]) * 
                                    getVirginica_PetalWidthND(test_petal_width[j]) * 
                                    (1./3.);
                    
                    break;
            }
        }
        setosaProbability =     setosaLikelihood     / (setosaLikelihood + versicolorLikelihood + virginicaLikelihood);
        versicolorProbability = versicolorLikelihood / (setosaLikelihood + versicolorLikelihood + virginicaLikelihood);
        virginicaProbability =  virginicaLikelihood  / (setosaLikelihood + versicolorLikelihood + virginicaLikelihood);

        std::cout << "\nLikelihoods for each class: \n";
        std::cout << "\tLikelihood of Setosa: " << setosaLikelihood << "\n";
        std::cout << "\tLikelihood of Versicolor: " << versicolorLikelihood << "\n";
        std::cout << "\tLikelihood of Virginica: " << virginicaLikelihood << "\n";

        std::cout << "\nProbabilities for each class: \n";
        std::cout << "\tProbability of Setosa: " << setosaProbability * 100 << " %\n";
        std::cout << "\tProbability of Versicolor: " << versicolorProbability * 100 << " %\n";
        std::cout << "\tProbability of Virginica: " << virginicaProbability * 100 << " %\n";

        std::cout << "\nTotal probability: " << setosaProbability + versicolorProbability + virginicaProbability << "\n";
    }
}

void BayesianClassifier::printFrequencyLabels(){
    std::cout << "The dataset is equally distributed, " 
              << "which results to a final distributed chance of: 1/3 33%\n";
    
    std::cout << "Train Set Feature Count:\n";
    std::cout << "Setosa Count: " << frequencyLabel.getSetosa() << "\n";
    std::cout << "Versicolor Count: " << frequencyLabel.getVersicolor() << "\n";
    std::cout << "Virginica Count: " << frequencyLabel.getVirginica() << "\n";

    std::cout << "\nTest Set:\n";
    std::cout << "Setosa Count: " << testSetFeatureCNT << "\n";
    std::cout << "Versicolor Count: " << testSetFeatureCNT << "\n";
    std::cout << "Virginica Count:" << testSetFeatureCNT << "\n" << std::endl;
}

void BayesianClassifier::printHistogramFrequencyTable(){
    printSepalLengthFrequencyTable();
    printInstanceChanceSepalLengthTable();
    std::cout << "\u001b[32m=========================================================\033[0m\n";

    printSepalWidthFrequencyTable();
    printInstanceChanceSepalWidthTable();
    std::cout << "\u001b[32m=========================================================\033[0m\n";
    
    printPetalLengthFrequencyTable();
    printInstanceChancePetalLengthTable();
    std::cout << "\u001b[32m=========================================================\033[0m\n";

    printPetalWidthFrequencyTable();
    printInstanceChancePetalWidthTable();
    std::cout << "\u001b[32m=========================================================\033[0m\n";
}

void BayesianClassifier::printGaussianTrainResult(){
    printGaussianSepalLengthTable();
    std::cout << "\u001b[32m=======================================================================\n\033[0m\n\n";
    printGaussianSepalWidthTable();
    std::cout << "\u001b[32m=======================================================================\n\033[0m\n\n";
    printGaussianPetalLengthTable();
    std::cout << "\u001b[32m=======================================================================\n\033[0m\n\n";
    printGaussianPetalWidthTable();
    std::cout << "\u001b[32m=======================================================================\n\033[0m\n\n";
}

void BayesianClassifier::printGaussianSepalLengthTable(){
    std::string output = "\u001b[31m=======================================================================\n||\u001b[32m\t\tSepal Length Gaussian Table\t\t\t\u001b[31m     ||\n=======================================================================\033[0m\n\n";

    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Means:\t\t\t  " + std::to_string(Setosa_SepalLengthMean) + "\t  " + std::to_string(Versicolor_SepalLengthMean) + "\t  " + std::to_string(Virginica_SepalLengthMean) + "\n";
    output += "Standard Deviation:\t  " + std::to_string(stDevSetosaSL) + "\t  " + std::to_string(stDevVersicolorSL) + "\t  " + std::to_string(stDevVirginicaSL) + "\n";
    std::cout << output;

}
void BayesianClassifier::printGaussianSepalWidthTable(){
    std::string output = "\u001b[31m=======================================================================\n||\u001b[32m\t\tSepal Width Gaussian Table\t\t\t\u001b[31m     ||\n=======================================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Means:\t\t\t  " + std::to_string(Setosa_SepalWidthMean) + "\t  " + std::to_string(Versicolor_SepalWidthMean) + "\t  " + std::to_string(Virginica_SepalWidthMean) + "\n";
    output += "Standard Deviation:\t  " + std::to_string(stDevSetosaSW) + "\t  " + std::to_string(stDevVersicolorSW) + "\t  " + std::to_string(stDevVirginicaSW) + "\n";
    std::cout << output;
}

void BayesianClassifier::printGaussianPetalLengthTable(){
    std::string output = "\u001b[31m=======================================================================\n||\u001b[32m\t\tPetal Length Gaussian Table\t\t\t\u001b[31m     ||\n=======================================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Means:\t\t\t  " + std::to_string(Setosa_PetalLengthMean) + "\t  " + std::to_string(Versicolor_PetalLengthMean) + "\t  " + std::to_string(Virginica_PetalLengthMean) + "\n";
    output += "Standard Deviation:\t  " + std::to_string(stDevSetosaPL) + "\t  " + std::to_string(stDevVersicolorPL) + "\t  " + std::to_string(stDevVirginicaPL) + "\n";
    std::cout << output;

}

void BayesianClassifier::printGaussianPetalWidthTable(){
    std::string output = "\u001b[31m=======================================================================\n||\u001b[32m\t\tPetal Length Gaussian Table\t\t\t\u001b[31m     ||\n=======================================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Means:\t\t\t  " + std::to_string(Setosa_PetalWidthMean) + "\t  " + std::to_string(Versicolor_PetalWidthMean) + "\t  " + std::to_string(Virginica_PetalWidthMean) + "\n";
    output += "Standard Deviation:\t  " + std::to_string(stDevSetosaPW) + "\t  " + std::to_string(stDevVersicolorPW) + "\t  " + std::to_string(stDevVirginicaPW) + "\n";
    std::cout << output;
}


void BayesianClassifier::printSepalLengthFrequencyTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tSepal Length Occurrence Table\u001b[31m\n=========================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Length Range 4 - 4.9:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange4to5()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getLengthRange4to5()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getLengthRange4to5()) + "\n";
    output += "Length Range 5 - 5.9:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange5to6()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getLengthRange5to6()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getLengthRange5to6()) + "\n";
    output += "Length Range 6 - 6.9:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange6to7()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getLengthRange6to7()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getLengthRange6to7()) + "\n";
    output += "Length Range 7 - 8:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange7to8()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getLengthRange7to8()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getLengthRange7to8()) + "\n";

    std::cout << output;
}

void BayesianClassifier::printInstanceChanceSepalLengthTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tSepal Length Chance Table\u001b[31m\n=========================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Length Range 4 - 4.9:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange4to5())      + "/"  + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                            + std::to_string(Sepalfrequencies_versicolor.getLengthRange4to5())  + "/"  + std::to_string(frequencyLabel.getVersicolor()) +  "\t    " 
                                            + std::to_string(Sepalfrequencies_virginica.getLengthRange4to5())   + "/"  + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Length Range 5 - 5.9:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange5to6())      + "/" + std::to_string(frequencyLabel.getSetosa())      + "\t    " 
                                            + std::to_string(Sepalfrequencies_versicolor.getLengthRange5to6())  + "/" + std::to_string(frequencyLabel.getVersicolor())  +  "\t    " 
                                            + std::to_string(Sepalfrequencies_virginica.getLengthRange5to6())   + "/" + std::to_string(frequencyLabel.getVirginica())   + "\n";

    output += "Length Range 6 - 6.9:\t    " + std::to_string(Sepalfrequencies_setosa.getLengthRange6to7())      + "/" + std::to_string(frequencyLabel.getSetosa())      + "\t    " 
                                            + std::to_string(Sepalfrequencies_versicolor.getLengthRange6to7())  + "/" + std::to_string(frequencyLabel.getVersicolor())  +  "\t    " 
                                            + std::to_string(Sepalfrequencies_virginica.getLengthRange6to7())   + "/" + std::to_string(frequencyLabel.getVirginica())   + "\n";

    output += "Length Range 7 - 8:\t    "   + std::to_string(Sepalfrequencies_setosa.getLengthRange7to8())      + "/" + std::to_string(frequencyLabel.getSetosa())      + "\t    " 
                                            + std::to_string(Sepalfrequencies_versicolor.getLengthRange7to8())  + "/" + std::to_string(frequencyLabel.getVersicolor())  +  "\t    " 
                                            + std::to_string(Sepalfrequencies_virginica.getLengthRange7to8())   + "/" + std::to_string(frequencyLabel.getVirginica())   + "\n";
    
    std::cout << output;
}



void BayesianClassifier::printSepalWidthFrequencyTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tSepal Width Occurrence Table\u001b[31m\n=========================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Width Range 2 - 2.9:\t    " + std::to_string(Sepalfrequencies_setosa.getWidthRange2to3()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getWidthRange2to3()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getWidthRange2to3()) + "\n";
    output += "Width Range 3 - 3.9:\t    " + std::to_string(Sepalfrequencies_setosa.getWidthRange3to4()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getWidthRange3to4()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getWidthRange3to4()) + "\n";
    output += "Width Range 4 - 5:\t    "  + std::to_string(Sepalfrequencies_setosa.getWidthRange4to5()) + "\t\t    " + std::to_string(Sepalfrequencies_versicolor.getWidthRange4to5()) + "\t\t    " + std::to_string(Sepalfrequencies_virginica.getWidthRange4to5()) + "\n";
    
    std::cout << output; 
}

void BayesianClassifier::printInstanceChanceSepalWidthTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tSepal Width Chance Table\u001b[31m\n=========================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Width Range 2 - 2.9:\t    "      + std::to_string(Sepalfrequencies_setosa.getWidthRange2to3())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                                + std::to_string(Sepalfrequencies_versicolor.getWidthRange2to3()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                                + std::to_string(Sepalfrequencies_virginica.getWidthRange2to3())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Width Range 3 - 3.9:\t    "      + std::to_string(Sepalfrequencies_setosa.getWidthRange3to4())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                                + std::to_string(Sepalfrequencies_versicolor.getWidthRange3to4()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                                + std::to_string(Sepalfrequencies_virginica.getWidthRange3to4()) + "/" + std::to_string(frequencyLabel.getVirginica())   + "\n";

    output += "Width Range 4 - 5:\t    "        + std::to_string(Sepalfrequencies_setosa.getWidthRange4to5())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                                + std::to_string(Sepalfrequencies_versicolor.getWidthRange4to5()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                                + std::to_string(Sepalfrequencies_virginica.getWidthRange4to5())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";
    
    std::cout << output;
}



void BayesianClassifier::printPetalLengthFrequencyTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tPetal Length Occurrence Table\u001b[31m\n=========================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Length Range 1 - 1.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange1to2()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getLengthRange1to2()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getLengthRange1to2()) + "\n";
    output += "Length Range 3 - 3.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange3to4()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getLengthRange3to4()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getLengthRange3to4()) + "\n";
    output += "Length Range 4 - 4.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange4to5()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getLengthRange4to5()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getLengthRange4to5()) + "\n";
    output += "Length Range 5 - 5.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange5to6()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getLengthRange5to6()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getLengthRange5to6()) + "\n";
    output += "Length Range 6 - 7:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange6to7())   + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getLengthRange6to7()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getLengthRange6to7()) + "\n";

    std::cout << output;
}

void BayesianClassifier::printInstanceChancePetalLengthTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tPetal Length Chance Table\u001b[31m\n=========================================================\033[0m\n\n";
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Length Range 1 - 1.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange1to2())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                            + std::to_string(Petalfrequencies_versicolor.getLengthRange1to2()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                            + std::to_string(Petalfrequencies_virginica.getLengthRange1to2())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Length Range 3 - 3.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange3to4())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                            + std::to_string(Petalfrequencies_versicolor.getLengthRange3to4()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                            + std::to_string(Petalfrequencies_virginica.getLengthRange3to4())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Length Range 4 - 4.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange4to5())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                            + std::to_string(Petalfrequencies_versicolor.getLengthRange4to5()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                            + std::to_string(Petalfrequencies_virginica.getLengthRange4to5())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Length Range 5 - 5.9:\t    " + std::to_string(Petalfrequencies_setosa.getLengthRange5to6())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                            + std::to_string(Petalfrequencies_versicolor.getLengthRange5to6()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                            + std::to_string(Petalfrequencies_virginica.getLengthRange5to6())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Length Range 6 - 7:\t    "   + std::to_string(Petalfrequencies_setosa.getLengthRange6to7())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                            + std::to_string(Petalfrequencies_versicolor.getLengthRange6to7()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                            + std::to_string(Petalfrequencies_virginica.getLengthRange6to7())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    std::cout << output;
}



void BayesianClassifier::printPetalWidthFrequencyTable(){
    std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tPetal Width Occurrence Table\u001b[31m\n=========================================================\033[0m\n\n"; 
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Width Range 0 - 0.9:\t    " + std::to_string(Petalfrequencies_setosa.getWidthRange0to1()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getWidthRange0to1()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getWidthRange0to1()) + "\n";
    output += "Width Range 1 - 1.9:\t    " + std::to_string(Petalfrequencies_setosa.getWidthRange1to2()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getWidthRange1to2()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getWidthRange1to2()) + "\n";
    output += "Width Range 2 - 3:\t    "  + std::to_string(Petalfrequencies_setosa.getWidthRange2to3()) + "\t\t    " + std::to_string(Petalfrequencies_versicolor.getWidthRange2to3()) + "\t\t    " + std::to_string(Petalfrequencies_virginica.getWidthRange2to3()) + "\n";
    
    std::cout << output;
}

void BayesianClassifier::printInstanceChancePetalWidthTable(){
        std::string output = "\u001b[31m=========================================================\u001b[32m\n\t\tPetal Width Chance Table\u001b[31m\n=========================================================\033[0m\n\n"; 
    output += "\t\t\tIris-setosa\tIris-versicolor\tIris-virginica\n";
    output += "Width Range 0 - 0.9:\t    " + std::to_string(Petalfrequencies_setosa.getWidthRange0to1())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                           + std::to_string(Petalfrequencies_versicolor.getWidthRange0to1()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                           + std::to_string(Petalfrequencies_virginica.getWidthRange0to1())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Width Range 1 - 1.9:\t    " + std::to_string(Petalfrequencies_setosa.getWidthRange1to2())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                           + std::to_string(Petalfrequencies_versicolor.getWidthRange1to2()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                           + std::to_string(Petalfrequencies_virginica.getWidthRange1to2())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";

    output += "Width Range 2 - 3:\t    "   + std::to_string(Petalfrequencies_setosa.getWidthRange2to3())     + "/" + std::to_string(frequencyLabel.getSetosa())     + "\t    " 
                                           + std::to_string(Petalfrequencies_versicolor.getWidthRange2to3()) + "/" + std::to_string(frequencyLabel.getVersicolor()) + "\t    " 
                                           + std::to_string(Petalfrequencies_virginica.getWidthRange2to3())  + "/" + std::to_string(frequencyLabel.getVirginica())  + "\n";
    
    std::cout << output;
}

double BayesianClassifier::toDouble(std::string str){
    try{
        double num = std::stod(str);

        return num;
    }catch(const std::exception &err){
        std::cout << "Error: Attempted to Read Incorrect value within the Dataset." << std::endl << std::endl << "Possible Solutions: " 
        << std::endl;
        std::cout << "Check if the correct dataset is being read." << std::endl;
        std::cout << "Check if the values are numbers (double/float) instead of any characters." << std::endl << std::endl;
        std::cout << "Root Cause: " << std::endl << err.what() << std::endl;
    }
    return 0;
}

BayesianClassifier::BayesianClassifier(){
    numInstances = 0;
}

BayesianClassifier::~BayesianClassifier(){
    // kill me
}
