#include <vector>
#include <utility>
#include <algorithm>
#include "Labels.h"
#include "Petal.h"
#include "Sepal.h"

# define PI 3.14159265358979323846

class BayesianClassifier{
    public:
        BayesianClassifier();

        virtual ~BayesianClassifier();
        
        void readData();
        void readData(double trainSet, int n_rows);
        std::string ShowDataset();
        
        // Creates a frequency Table using Histogram based data
        void HistogramNBTrain();
        // Prints the frequency Table
        void printHistogramFrequencyTable();

        void HistogramNBProbabilityResults();


        // Trains the Model using the Gaussian method
        void GaussianNBTrain();
        void printGaussianTrainResult();
        void GaussianNBProbabilityResults();
        
        


        
        void printFrequencyLabels();
    private:
        // 2D matrix for Dataset
        std::vector<std::vector<std::string>> dataset;
        
        // Data Train Vectors
        std::vector<double> sepal_length;
        std::vector<double> sepal_width;
        std::vector<double> petal_length;
        std::vector<double> petal_width;
        std::vector<std::string> labels;
        
        // Data Test Vectors
        std::vector<double> test_sepal_length;
        std::vector<double> test_sepal_width;
        std::vector<double> test_petal_length;
        std::vector<double> test_petal_width;
        std::vector<std::string> test_labels;

        // NB Model Objects
        Petal Petalfrequencies_setosa;
        Petal Petalfrequencies_versicolor;
        Petal Petalfrequencies_virginica;

        Sepal Sepalfrequencies_setosa;
        Sepal Sepalfrequencies_versicolor;
        Sepal Sepalfrequencies_virginica;

        Labels frequencyLabel; // Number of instances
        int numInstances;
        int trainSetFeatureCNT;
        int testSetFeatureCNT;
        double Setosa_SepalLengthMean, Setosa_SepalWidthMean, Setosa_PetalLengthMean, Setosa_PetalWidthMean;
        double Versicolor_SepalLengthMean, Versicolor_SepalWidthMean, Versicolor_PetalLengthMean, Versicolor_PetalWidthMean;
        double Virginica_SepalLengthMean, Virginica_SepalWidthMean, Virginica_PetalLengthMean, Virginica_PetalWidthMean;

        double stDevSetosaSL, stDevSetosaSW, stDevSetosaPL, stDevSetosaPW;
        double stDevVersicolorSL, stDevVersicolorSW, stDevVersicolorPL, stDevVersicolorPW;
        double stDevVirginicaSL, stDevVirginicaSW, stDevVirginicaPL, stDevVirginicaPW;

        double NormDistSetosaSL, NormDistSetosaSW, NormDistSetosaPL, NormDistSetosaPW;
        double NormDistVersicolorSL, NormDistVersicolorSW, NormDistVersicolorPL, NormDistVersicolorPW;
        double NormDistVirginicaSL, NormDistVirginicaSW, NormDistVirginicaPL, NormDistVirginicaPW;
        
        // Functions
        double toDouble(std::string str);

        double getSetosa_SepalLengthND(double data);
        double getSetosa_SepalWidthND(double data);
        double getSetosa_PetalLengthND(double data);
        double getSetosa_PetalWidthND(double data);

        double getVersicolor_SepalLengthND(double data);
        double getVersicolor_SepalWidthND(double data);
        double getVersicolor_PetalLengthND(double data);
        double getVersicolor_PetalWidthND(double data);

        double getVirginica_SepalLengthND(double data);
        double getVirginica_SepalWidthND(double data);
        double getVirginica_PetalLengthND(double data);
        double getVirginica_PetalWidthND(double data);

        void printSepalLengthFrequencyTable();
        void printInstanceChanceSepalLengthTable();

        void printSepalWidthFrequencyTable();
        void printInstanceChanceSepalWidthTable();

        
        void printPetalLengthFrequencyTable();
        void printInstanceChancePetalLengthTable();

        void printPetalWidthFrequencyTable();
        void printInstanceChancePetalWidthTable();

        void printGaussianSepalLengthTable();
        void printGaussianSepalWidthTable();
        void printGaussianPetalLengthTable();
        void printGaussianPetalWidthTable();

};