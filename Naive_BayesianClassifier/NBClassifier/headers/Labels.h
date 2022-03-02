#include <string>

class Labels{
    private:
        int countsetosa;
        int countversicolor;
        int countvirginica;

    public:
        Labels():countsetosa(0), countversicolor(0), countvirginica(0){

        }
        Labels(int set, int vers, int virg):countsetosa(set), countversicolor(vers), countvirginica(virg){}

        void setSetosa(int countsetosa){ this->countsetosa = countsetosa;}
        int getSetosa(){ return countsetosa;}
        
        void setVersicolor(int countversicolor){ this->countversicolor = countversicolor; }
        int getVersicolor(){ return countversicolor;}

        void setVirginica(int countvirginica){ this->countvirginica = countvirginica;}
        int getVirginica(){ return countvirginica;}

        void printInfo(){
            std::string output = "========================================\n\t\tLabels\n========================================\n\n";
            output += "|| Iris-setosa || ";
                output += "Count: " + std::to_string(getSetosa()) + "\n";
            
            output += "|| Iris-versicolor ||";
                output += "Count: " + std::to_string(getVersicolor()) + "\n";
            
            output += "|| Iris-virginica ||";
                output += "Count: " + std::to_string(getVirginica()) + "\n";
            output += "========================================";

            std::cout << output;
        }
};