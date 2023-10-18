// Assignment 1 Bonus.

/* This assignment is done by Students:

Yussuf Mohammad Taha, ID:20220406

Moaz Gehad, ID: 20220340

Shaher Saeed, ID: 20220163

Last modification: 16 / 10 / 2023

*/

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.h"
#include "bmplib.cpp"

using namespace std;
unsigned char RGBinputImage[SIZE][SIZE][RGB];
unsigned char RGBresultImage[SIZE][SIZE][RGB];
unsigned char RGBmergeImage[SIZE][SIZE][RGB];
char mergeRGBFile[100];

void loadRGBImage();

void saveRGBImage();

void flipImage();

void RGB_black_and_white();

void mirrorImage();

void RGB_menu();

void cropImage();

void colored_detectEdges();

void colored_blur();

void colored_shrink();

void colored_darken_and_lighten();

void colored_merge();

void colored_skewVertical();

void colored_skewHorizontal();


int main() {
    cout << "Ahlan ya user ya habibi\n";
    cout << "Please enter file name of the Image to process:";
    loadRGBImage();
    RGB_menu();
    return 0;
}

void loadRGBImage() {
    char RGBimage[100];
    cin >> RGBimage;

    strcat(RGBimage, ".bmp");
    readRGBBMP(RGBimage, RGBinputImage);
    readRGBBMP(RGBimage, RGBresultImage);
}

void saveRGBImage() {
    char saveRGB[100];

    cout << "Enter the target Image file name: ";
    cin >> saveRGB;

    strcat(saveRGB, ".bmp");
    writeRGBBMP(saveRGB, RGBresultImage);
}

//_________________________________________
void flipImage() {
    cout << "Flip (h)orizontally or (v)ertically ?";
    char s;
    cin >> s;
    if (s == 'h')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(RGBresultImage[i][j], RGBresultImage[i][255 - j]);
            }
        }
    else
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(RGBresultImage[i][j], RGBresultImage[255 - i][j]);
            }
        }
}

void RGB_black_and_white() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                int avg = (RGBinputImage[i][j][0] + RGBinputImage[i][j][1] + RGBinputImage[i][j][2]) / 3;
                if (avg > 127)
                    RGBresultImage[i][j][k] = 255;
                else
                    RGBresultImage[i][j][k] = 0;
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
                    RGBresultImage[i][j][k] = RGBinputImage[255 - i][j][k];
                }
            }
            //upper
        }
    else if (c == 'u')
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    RGBresultImage[255 - i][j][k] = RGBinputImage[i][j][k];
                }
            }
            //left
        }
    else if (c == 'l')
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    RGBresultImage[i][j][k] = RGBinputImage[i][255 - j][k];
                }
            }
        }
        //right
    else if (c == 'r')
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    RGBresultImage[i][255 - j][k] = RGBinputImage[i][j][k];
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
                    RGBresultImage[i][j][0] = RGBresultImage[i][j][1] = RGBresultImage[i][j][2] = 255;
            }
        }
    }
}

void colored_detectEdges() {
    RGB_black_and_white();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k) {
                if(RGBresultImage[i][j][k] != RGBresultImage[i][j][k + 1] || RGBresultImage[i][j][k] != RGBresultImage[i + 1][j][k] || RGBresultImage[i][j][k] != RGBresultImage[i][j + 1][k])
                    RGBresultImage[i][j][k] = 0;
                else
                    RGBresultImage[i][j][k] = 255;
            }
        }
    }
}

void colored_darken_and_lighten(){
    cout << "Do you want to (d)arken or (l)ighten the Image:";
    string brightness; cin >> brightness;
    if(brightness[0] == 'd' || brightness[0] == 'D') {
        // For darkening the Image, we subtract the current value of the pixel by half its value.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k < RGB; k++) {
                    if (RGBinputImage[i][j][k] != 0) {
                        RGBresultImage[i][j][k] = RGBinputImage[i][j][k] - (RGBinputImage[i][j][k] / 2);
                    }
                }
            }
        }
    }
    else{
        // For lightening the Image, we add half the value of the current pixel to itself unless the value is greater than 170 we just make it 255.
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++) {
                    if (RGBinputImage[i][j][k] < 170) {
                        RGBresultImage[i][j][k] = RGBinputImage[i][j][k] + (RGBinputImage[i][j][k] / 2);
                    } else {
                        RGBresultImage[i][j][k] = 255;
                    }
                }
            }
        }
    }
}

void colored_blur(){
    // For blurring, I used box blur which takes the average of 9 pixels around the target pixel, including the pixel itself.
    for(int i = 1; i < SIZE - 1; i++){
        for(int j = 1; j < SIZE - 1; j++){
            for(int k = 0 ; k < RGB; k++) {
                RGBresultImage[i][j][k] = (RGBinputImage[i][j - 1][k] + RGBinputImage[i - 1][j][k] + RGBinputImage[i + 1][j - 1][k] +
                                           RGBinputImage[i - 1][j + 1][k] + RGBinputImage[i][j][k] + RGBinputImage[i + 1][j + 1][k] +
                                           RGBinputImage[i][j + 1][k] + RGBinputImage[i + 1][j][k] + RGBinputImage[i - 1][j - 1][k]) / 9;
            }
        }
    }
}

void colored_shrink(){
    cout << "Do you want to shrink to (1/2), (1/3), (1/4):";
    string shrink_ratio;
    cin >> shrink_ratio;
    cout << '\n';
    // Using the ".back()" method, we take the denominator of the ratio and subtract it by char(0) to get the integer value.
    int shrink = (shrink_ratio.back() - '0');
    // Whitening the Image.
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[i][j][k] = 255;
            }
        }
    }
    // Shrinking the Image by accessing the current pixel and putting it in the current index divided by the shrink ratio.
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[int(i / shrink)][int(j / shrink)][k] = RGBinputImage[i][j][k];
            }
        }
    }
}

void colored_skewVertical(){
    cout << "Enter the degree to skew up:";
    double angle; cin >> angle;
    double radian;
    radian = (22 * angle) / (7 * 180);
    // The length is used for compressing the Image and also skewing.
    int length = 256 - (256*(tan(radian)));
    // Whitening the Image.
    for(int i = 0 ; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[i][j][k] = 255;
            }
        }
    }
    // Compressing the Image.
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j <= length; j++){
            for(int k = 0; k < RGB; k++) {
                RGBinputImage[i][j][k] = RGBinputImage[i][(256 * j) / length][k];
            }
        }
    }
    // Using shearing, which is an algorithm used for skewing images using a 2x2 matrix.
    for(int i = 0 ; i < SIZE; i++){
        for(int j = 0; j <= length; j++){
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[i][j + (int) ((tan(radian)) * (255 - i))][k] = RGBinputImage[i][j][k];
            }
        }
    }
}

void colored_skewHorizontal(){
    cout << "Enter the degree to skew right:";
    double angle; cin >> angle;
    double radian;
    radian = (22 * angle) / (7 * 180);
    // The length is used for compressing the Image and also skewing.
    int length = 256 - (256*(tan(radian)));
    // Whitening the Image.
    for(int i = 0 ; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[i][j][k] = 255;
            }
        }
    }
    // Compressing the Image.
    for(int i = 0; i <= length; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++) {
                RGBinputImage[i][j][k] = RGBinputImage[(256 * i) / length][j][k];
            }
        }
    }
    // Using shearing, which is an algorithm used for skewing images using a 2x2 matrix.
    for(int i = 0 ; i <= length; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[(int) ((255 - j) * (tan(radian))) + i][j][k] = RGBinputImage[i][j][k];
            }
        }
    }
}

void colored_merge() {
    cout << "Please enter name of Image file to merge with:";
    cin >> mergeRGBFile;
    strcat(mergeRGBFile, ".bmp");
    readRGBBMP(mergeRGBFile, RGBmergeImage);
    // For merging we take the average of both images.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++) {
                RGBresultImage[i][j][k] = (RGBinputImage[i][j][k] + RGBmergeImage[i][j][k]) / 2;
            }
        }
    }
}

void RGB_menu() {
    char action;
    cout << "Please select a filter to apply or 0 to exit:\n"
            "1-Black & White Filter          9-Shrink Image\n"
            "2-Invert Filter                 a-Mirror 1/2 Image\n"
            "3-Merge Filter                  b-Shuffle Image\n"
            "4-Flip Image                    c-Blur Image\n"
            "5-Darken and Lighten Image      d-Crop Image\n"
            "6-Rotate Image                  e-Skew Image Right  \n"
            "7-Detect Image Edges            f-Skew Image Up\n"
            "8-Enlarge Image                 s-Save the Image to a file\n"
            "9-Shrink Image                  0-Exit\n";
    cin >> action;
    if (action == '0')
        return;
    switch (action) {
        case '1': //black and white
            RGB_black_and_white();
            break;
        case '2': //invert
            break;
        case '3': // merger
            colored_merge();
            break;
        case '4': //flip
            flipImage();
            break;
        case '5': //darken and lighten
            colored_darken_and_lighten();
            break;
        case '6': //rotate
            break;
        case '7': //detect edges
            colored_detectEdges();
            break;
        case '8': //enlarge
            break;
        case '9': //colored_shrink
            colored_shrink();
            break;
        case 'a': //mirrorImage
            mirrorImage();
            break;
        case 'b': //shuffle
            break;
        case 'c': //colored_blur
            colored_blur();
            break;
        case 'd': //crop
            cropImage();
            break;
        case 'e': //skew right
            colored_skewHorizontal();
            break;
        case 'f': //skew up
            colored_skewVertical();
            break;
        case 's': // save
            saveRGBImage();
            break;
    }
    RGB_menu();
}
