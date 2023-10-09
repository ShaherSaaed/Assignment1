// Assignment 1.

/* This assignment is done by Students:

Yussuf Mohammad Taha, ID:20220406

Moaz Gehad, ID: 20220340

Shaher Saeed, ID: 20220163

*/
#include <iostream>
#include "bmplib.cpp"
#include "bmplib.h"
#include <fstream>

using namespace std;
unsigned char inputImage[SIZE][SIZE];
unsigned char mergeImage[SIZE][SIZE];
unsigned char resultImage[SIZE][SIZE];
char imageName[100];
char mergeFile[100];

void loadImage();

void saveImage();

void blur();

void invertImage();

void rotateImage();

void shrink();

void merge();

void darken_and_lighten();

void BW();

void FLIP();

void MIRROR();

void CROP();

int main()
{
    cout << "Ahlan ya user ya habibi\n";
    cout << "Please enter file name of the image to process: ";
    loadImage();
    char action;
    while (true) {
        cout << "Please select a filter to apply or 0 to exit:\n"
                "1-Black & White Filter\n"
                "2-Invert Filter\n"
                "3-Merge Filter \n"
                "4-Flip Image\n"
                "5-Darken and Lighten Image \n"
                "6-Rotate Image\n"
                "7-Detect Image Edges \n"
                "8-Enlarge Image\n"
                "9-Shrink Image\n"
                "a-Mirror 1/2 Image\n"
                "b-Shuffle Image\n"
                "c-Blur Image\n"
                "d-Crop Image\n"
                "e-Skew Image Right  \n"
                "f-Skew Image Up  \n"
                "s-Save the inputImage to a file\n"
                "0-Exit\n";
        cin >> action;
        if(action == '0')
            break;
        switch (action) {
            case '1': //black and white
                BW();
                break;
            case '2': //invert
                invertImage();
                break;
            case '3': // merger
                merge();
                break;
            case '4': //flip
                FLIP();
                break;
            case '5': //darken and lighten
                darken_and_lighten();
                break;
            case '6': //rotate
                rotateImage();
                break;
            case '7': //detect edges
                break;
            case '8': //enlarge

                break;
            case '9': //shrink
                shrink();
                break;
            case 'a': //mirror
                MIRROR();
                break;
            case 'b': //shuffle

                break;
            case 'c': //blur
                blur();
                break;
            case 'd': //crop
                CROP();
                break;
            case 'e': //skew right

                break;
            case 'f': //skew up

                break;
            case 's': // save
                saveImage();
                break;
        }
    }
    return 0;
}

void loadImage () {
    cin >> imageName;
    cout << "\n";
    strcat (imageName, ".bmp");
    readGSBMP(imageName, inputImage);
    readGSBMP(imageName, resultImage);
}

void saveImage () {
    char savedImage[100];
    cout << "Enter the target Image file name: ";
    cin >> savedImage;
    strcat (savedImage, ".bmp");
    writeGSBMP(savedImage, resultImage);
}

void merge() {
    char secondImage[100];
    cout << "Please enter name of inputImage file to merge with: ";
    cin >> secondImage;
    strcat(secondImage, ".bmp");
    readGSBMP(secondImage, mergeImage);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            resultImage[i][j] = (inputImage[i][j] + mergeImage[i][j]) / 2;
        }
    }
}

void darken_and_lighten(){
    cout << "Do you want to (d)arken or (l)ighten the inputImage: ";
    string brightness; cin >> brightness;
    if(brightness[0] == 'd') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (inputImage[i][j] != 0) {
                    resultImage[i][j] = inputImage[i][j] - (inputImage[i][j] / 2);
                }
            }
        }
    }
    else{
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(inputImage[i][j] < 170){
                    resultImage[i][j] = inputImage[i][j] + (inputImage[i][j] / 2);
                }
                else{
                    resultImage[i][j] = 255;
                }
            }
        }
    }
}

void blur(){
    for(int i = 1; i < SIZE - 1; i++){
        for(int j = 1; j < SIZE - 1; j++){
            resultImage[i][j] = (inputImage[i][j - 1] + inputImage[i - 1][j] + inputImage[i + 1][j - 1] + inputImage[i - 1][j + 1] + inputImage[i][j] + inputImage[i + 1][j + 1] +
                                 inputImage[i][j + 1] + inputImage[i + 1][j] + inputImage[i - 1][j - 1]) / 9;
        }
    }
}

void shrink(){
    cout << "Enter the value to shrink: ";
    string shrink_ratio;
    cin >> shrink_ratio;
    cout << '\n';
    int shrink = (shrink_ratio.back() - '0');
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            resultImage[i][j] = 255;
        }
    }
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            resultImage[int(i / shrink)][int(j / shrink)] = inputImage[i][j];
        }
    }
}

void BW() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int avg = (inputImage[i][j] + 127) / 2;
            if (avg > 127)
                resultImage[i][j] = 255;
            else
                resultImage[i][j] = 0;
        }
    }
}

void FLIP() {
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    char HorV;
    cin >> HorV;
    if (HorV == 'h') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(resultImage[i][j], resultImage[i][255 - j]);
            }
        }
    } else {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE / 2; i++) {
                swap(resultImage[i][j], resultImage[255 - i][j]);
            }
        }
    }
}

void MIRROR() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    char mir;
    cin >> mir;
    if (mir == 'r')
        //right side
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {

                resultImage[i][j] = resultImage[i][255 - j];
            }
        }
        //left side
    else if (mir = 'l')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                resultImage[i][255 - j] = resultImage[i][j];
            }
        }
        //upper
    else if (mir = 'u')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                resultImage[255 - i][j] = resultImage[i][j];
            }
        }
        //down
    else if (mir = 'd')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                resultImage[i][j] = resultImage[255 - i][j];
            }
        }
}

void CROP() {
    cout << "Please enter x y:\n";
    int x, y;
    cin >> x >> y;
    cout << "Please enter L W:\n";
    int l, w, startl, endl, startw, endw;
    cin >> l >> w;
    startl = x - l / 2;
    endl = x + l / 2;
    startw = y - w / 2;
    endw = y + w / 2;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            if ((i < startl || i > endl) || (j < startw || j > endw))
                resultImage[i][j] = 255;
    }
}

void invertImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            resultImage[i][j] = 255 - inputImage[i][j];
        }
    }
}

void rotateImage() {
    int degree;
    cout << "Rotate (90) / (180) or (270) degree clockwise ? ";
    cin >> degree ;
    if (degree==270){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[255 - j][i];
            }
        }

    }
    else if (degree==90){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[j][255 - i];
            }
        }
    }
    else if (degree==180){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[255 - i][255 - j];
            }
        }
    }
}
