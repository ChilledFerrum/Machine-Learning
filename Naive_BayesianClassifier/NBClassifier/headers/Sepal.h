class Sepal{
    private:
        // Length total 4
        int countLengthRange4to5;
        int countLengthRange5to6;
        int countLengthRange6to7;
        int countLengthRange7to8;

        // Width total 3
        int countWidthRange2to3;
        int countWidthRange3to4;
        int countWidthRange4to5;

    public:
        // Simple Init 
        Sepal():countLengthRange4to5(0), countLengthRange5to6(0), countLengthRange6to7(0), countLengthRange7to8(0),
                countWidthRange2to3(0), countWidthRange3to4(0), countWidthRange4to5(0){}

        void Length(int Range4to5, int Range5to6, int Range6to7){
            countLengthRange4to5 = Range4to5;
            countLengthRange5to6 = Range5to6;
            countLengthRange6to7 = Range6to7;
        }

        void Width(int Range2to3, int Range3to4, int Range4to5){
            countWidthRange2to3 = Range2to3;
            countWidthRange3to4 = Range3to4;
            countWidthRange4to5 = Range4to5;
        }

        // Setters & Getters Length
        int getLengthRange4to5(){ return countLengthRange4to5;}
        void setLengthRange4to5(int R45){countLengthRange4to5 = R45;}
        
        int getLengthRange5to6(){ return countLengthRange5to6;}
        void setLengthRange5to6(int R56){countLengthRange5to6 = R56;}
        
        int getLengthRange6to7(){ return countLengthRange6to7;}
        void setLengthRange6to7(int R67){countLengthRange6to7 = R67;}
        
        int getLengthRange7to8(){ return countLengthRange7to8;}
        void setLengthRange7to8(int R78){countLengthRange7to8 = R78;}


        // Setters & Getters Width
        int getWidthRange2to3(){ return countWidthRange2to3;}
        void setWidthRange2to3(int R23){countWidthRange2to3 = R23;}

        int getWidthRange3to4(){ return countWidthRange3to4;}
        void setWidthRange3to4(int R34){countWidthRange3to4 = R34;}

        int getWidthRange4to5(){ return countWidthRange4to5;}
        void setWidthRange4to5(int R45){countWidthRange4to5 = R45;}

};