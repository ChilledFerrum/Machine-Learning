#include <iostream>
#include "headers/ClassifierHeader.h"
#include <iomanip>

int main()
{    
    bool useGaussian = true;
    double totalTrainSet = 0.96;
    int numberofDatasetRows = 150;
    BayesianClassifier d = BayesianClassifier();
    
    d.readData(totalTrainSet, numberofDatasetRows);
    
    std::cout << d.ShowDataset();
    if(useGaussian){
        d.GaussianNBTrain();
        d.printGaussianTrainResult();
        d.printFrequencyLabels();
    }else{
        d.HistogramNBTrain();
        d.printHistogramFrequencyTable();
        d.printFrequencyLabels();
    }
    

    std::cout << "\u001b[32mPress Enter to See Test Results...\033[0m" << std::endl;
    if(getchar() == 10){
        if(useGaussian)
            d.GaussianNBProbabilityResults();
        else{
            d.HistogramNBProbabilityResults();
        }
    } 
}