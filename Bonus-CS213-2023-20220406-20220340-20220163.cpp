// Assignment 1 Bonus.

/* This assignment is done by Students:

Yussuf Mohammad Taha, ID:20220406

Moaz Gehad, ID: 20220340

Shaher Saeed, ID: 20220163

Last modification: 16 / 10 / 2023

*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.h"
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];

void loadImage();

void saveImage();

void flipImage();

void black_and_white();

void mirrorImage();

void menu();

void cropImage();

void detectEdges();

int main() {
    cout << "Ahlan ya user ya habibi\n";
    cout << "Please enter file name of the image to process: ";
    loadImage();
    menu();
    return 0;
}

//_________________________________________
void loadImage() {
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

//_________________________________________
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//_________________________________________
void flipImage() {
    cout << "Flip (h)orizontally or (v)ertically ?";
    char s;
    cin >> s;
    if (s == 'h')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(image[i][j], image[i][255 - j]);
            }
        }
    else
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[255 - i][j]);
            }
        }
}

void black_and_white() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                int avg = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3;
                if (avg > 127)
                    image[i][j][k] = 255;
                else
                    image[i][j][k] = 0;
            }
        }
    }
}

void mirrorImage() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    char c;
    cin >> c;
    //down
    if (c == 'd')
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[255 - i][j][k];
                }
            }
            //upper
        }
    else if (c == 'u')
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[255 - i][j][k] = image[i][j][k];
                }
            }
            //left
        }
    else if (c == 'l')
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[i][255 - j][k];
                }
            }
        }
        //right
    else if (c == 'r')
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][255 - j][k] = image[i][j][k];
                }
            }
        }
}

void cropImage() {
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
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                if ((i < startl || i > endl) || j < startw || j > endw)
                    image[i][j][0] = image[i][j][1] = image[i][j][2] = 255;
            }
        }
    }
}

void detectEdges() {
    black_and_white();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k) {
                if(image[i][j][k] != image[i][j][k + 1] || image[i][j][k] != image[i + 1][j][k] || image[i][j][k] != image[i][j + 1][k])
                    image[i][j][k] = 0;
                else
                    image[i][j][k] = 255;
            }
        }
    }
}

void menu() {
    char action;
    cout << "Please select a filter to apply or 0 to exit:\n"
            "1-Black & White Filter          9-Shrink Image\n"
            "2-Invert Filter                 a-Mirror 1/2 Image\n"
            "3-Merge Filter                  b-Shuffle Image\n"
            "4-Flip Image                    c-Blur Image\n"
            "5-Darken and Lighten Image      d-Crop Image\n"
            "6-Rotate Image                  e-Skew Image Right  \n"
            "7-Detect Image Edges            f-Skew Image Up\n"
            "8-Enlarge Image                 s-Save the image to a file\n"
            "9-Shrink Image                  0-Exit\n";
    cin >> action;
    if (action == '0')
        return;
    switch (action) {
        case '1': //black and white
            black_and_white();
            break;
        case '2': //invert
            break;
        case '3': // merger
            break;
        case '4': //flip
            flipImage();
            break;
        case '5': //darken and lighten
            break;
        case '6': //rotate
            break;
        case '7': //detect edges
            detectEdges();
            break;
        case '8': //enlarge
            break;
        case '9': //shrink
            break;
        case 'a': //mirrorImage
            mirrorImage();
            break;
        case 'b': //shuffle
            break;
        case 'c': //blur
            break;
        case 'd': //crop
            cropImage();
            break;
        case 'e': //skew right
            break;
        case 'f': //skew up
            break;
        case 's': // save
            saveImage();
            break;
    }
    menu();
}
