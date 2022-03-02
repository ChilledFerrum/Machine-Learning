class Petal{
    private:
        // Length total 5
        int countLengthRange1to2;
        int countLengthRange3to4;
        int countLengthRange4to5;
        int countLengthRange5to6;
        int countLengthRange6to7;

        // Width total 3
        int countWidthRange0to1;
        int countWidthRange1to2;
        int countWidthRange2to3;

    public:
        // Simple Init 
        Petal():countLengthRange1to2(0), countLengthRange3to4(0),countLengthRange4to5(0), countLengthRange5to6(0), countLengthRange6to7(0), 
                countWidthRange0to1(0), countWidthRange1to2(0), countWidthRange2to3(0){}

        void Length(int Range1to2, int Range3to4, int Range4to5, int Range5to6, int Range6to7){
            countLengthRange1to2 = Range1to2;
            countLengthRange3to4 = Range3to4;
            countLengthRange4to5 = Range4to5;
            countLengthRange5to6 = Range5to6;
            countLengthRange6to7 = Range6to7;
        }

        void Width(int Range0to1, int Range1to2, int Range2to3){
            countWidthRange0to1 = Range0to1;
            countWidthRange1to2 = Range1to2;
            countWidthRange2to3 = Range2to3;
        }

        int getLengthRange1to2(){return countLengthRange1to2;}
        void setLengthRange1to2(int R12){countLengthRange1to2 = R12;}

        int getLengthRange3to4(){return countLengthRange3to4;}
        void setLengthRange3to4(int R34){countLengthRange3to4 = R34;}

        int getLengthRange4to5(){return countLengthRange4to5;}
        void setLengthRange4to5(int R45){ countLengthRange4to5 = R45;}

        int getLengthRange5to6(){return countLengthRange5to6;}
        void setLengthRange5to6(int R56){countLengthRange5to6 = R56;}

        int getLengthRange6to7(){return countLengthRange6to7;}
        void setLengthRange6to7(int R67){countLengthRange6to7 = R67;}



        int getWidthRange0to1(){return countWidthRange0to1;}
        void setWidthRange0to1(int R01){countWidthRange0to1 = R01;}

        int getWidthRange1to2(){return countWidthRange1to2;}
        void setWidthRange1to2(int R12){countWidthRange1to2 = R12;}

        int getWidthRange2to3(){return countWidthRange2to3;}
        void setWidthRange2to3(int R23){countWidthRange2to3 = R23;}
};