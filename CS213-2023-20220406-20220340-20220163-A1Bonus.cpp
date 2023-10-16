// Assignment 1.

/* This assignment is done by Students:

Yussuf Mohammad Taha, ID:20220406

Moaz Gehad, ID: 20220340

Shaher Saeed, ID: 20220163

Last modification: 16 / 10 / 2023

*/


#include <iostream>
#include <cmath>
#include "bmplib.cpp"
#include "bmplib.h"

using namespace std;
unsigned char inputImage[SIZE][SIZE];
unsigned char mergeImage[SIZE][SIZE];
unsigned char resultImage[SIZE][SIZE];
char imageName[100];
char mergeFile[100];
void menu();

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

void skewVertical();

void skewHorizontal();

void enlargeImage();

void detectEdges();

int main()
{
    cout << "Ahlan ya user ya habibi\n";
    cout << "Please enter file name of the image to process: ";
    loadImage();
    menu();
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
    cout << "Please enter name of Image file to merge with: ";
    cin >> mergeFile;
    strcat(mergeFile, ".bmp");
    readGSBMP(mergeFile, mergeImage);
    // For merging we take the average of both images.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            resultImage[i][j] = (inputImage[i][j] + mergeImage[i][j]) / 2;
        }
    }
}

void darken_and_lighten(){
    cout << "Do you want to (d)arken or (l)ighten the Image: ";
    string brightness; cin >> brightness;
    if(brightness[0] == 'd') {
        // For darkening the image, we subtract the current value of the pixel by half its value.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (inputImage[i][j] != 0) {
                    resultImage[i][j] = inputImage[i][j] - (inputImage[i][j] / 2);
                }
            }
        }
    }
    else{
        // For lightening the image, we add half the value of the current pixel to itself unless the value is greater than 170 we just make it 255.
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
    // For blurring, I used box blur which takes the average of 9 pixels around the target pixel, including the pixel itself.
    for(int i = 1; i < SIZE - 1; i++){
        for(int j = 1; j < SIZE - 1; j++){
            resultImage[i][j] = (inputImage[i][j - 1] + inputImage[i - 1][j] + inputImage[i + 1][j - 1] + inputImage[i - 1][j + 1] + inputImage[i][j] + inputImage[i + 1][j + 1] +
                                 inputImage[i][j + 1] + inputImage[i + 1][j] + inputImage[i - 1][j - 1]) / 9;
        }
    }
}

void shrink(){
    cout << "Do you want to shrink to (1/2), (1/3), (1/4): ";
    string shrink_ratio;
    cin >> shrink_ratio;
    cout << '\n';
    // Using the ".back()" method, we take the denominator of the ratio and subtract it by char(0) to get the integer value.
    int shrink = (shrink_ratio.back() - '0');
    // Whitening the image.
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            resultImage[i][j] = 255;
        }
    }
    // Shrinking the image by accessing the current pixel and putting it in the current index divided by the shrink ratio.
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
    if (mir == 'r') {
        //right side
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                resultImage[i][j] = resultImage[i][255 - j];
            }
        }
    }
        //left side
    else if (mir == 'l') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                resultImage[i][255 - j] = resultImage[i][j];
            }
        }
    }
        //upper
    else if (mir == 'u') {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                resultImage[255 - i][j] = resultImage[i][j];
            }
        }
    }
        //down
    else if (mir == 'd') {
        for (int i = 255; i >= SIZE / 2; i--) {
            for (int j = 0; j < SIZE; j++) {
                resultImage[255 - i][j] = resultImage[i][j];
            }
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

void skewVertical(){
    cout << "Enter the degree to skew up: ";
    double angle; cin >> angle;
    double radian;
    radian = (22 * angle) / (7 * 180);
    // The length is used for compressing the image and also skewing.
    int length = 256 - (256*(tan(radian)));
    // Whitening the image.
    for(int i = 0 ; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            resultImage[i][j] = 255;
        }
    }
    // Compressing the image.
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j <= length; j++){
            inputImage[i][j] = inputImage[i][(256 * j) / length];
        }
    }
    // Using shearing, which is an algorithm used for skewing images using a 2x2 matrix.
    for(int i = 0 ; i < SIZE; i++){
        for(int j = 0; j <= length; j++){
            resultImage[i][j + (int)((tan(radian)) * (255 - i))] = inputImage[i][j];
        }
    }
}

void skewHorizontal(){
    cout << "Enter the degree to skew right: ";
    double angle; cin >> angle;
    double radian;
    radian = (22 * angle) / (7 * 180);
    // The length is used for compressing the image and also skewing.
    int length = 256 - (256*(tan(radian)));
    // Whitening the image.
    for(int i = 0 ; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            resultImage[i][j] = 255;
        }
    }
    // Compressing the image.
    for(int i = 0; i <= length; i++){
        for(int j = 0; j < SIZE; j++){
            inputImage[i][j] = inputImage[(256 * i) / length][j];
        }
    }
    // Using shearing, which is an algorithm used for skewing images using a 2x2 matrix.
    for(int i = 0 ; i <= length; i++){
        for(int j = 0; j < SIZE; j++){
            resultImage[(int)((255 - j) * (tan(radian))) + i][j] = inputImage[i][j];
        }
    }
}

void enlargeImage(){
    int quarter;
    cout << "Which quarter to enlarge : 1, 2, 3 or 4 ? ";
    cin >> quarter ;
    if (quarter == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[i/2][j/2];
            }
        }
    }
    else if (quarter == 2)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[i/2][(j/2)+128];
            }
        }
    }
    else if (quarter == 3)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[(i/2)+128][(j/2)];
            }
        }
    }
    else if (quarter == 4)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                resultImage[i][j] = inputImage[(i/2)+128][(j/2)+128];
            }
        }
    }
}
void detectEdges() {
    blur();
    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE;j++) {
            if(abs(resultImage[i][j] - resultImage[i][j + 1]) > 15 || abs(resultImage[i][j] - resultImage[i + 1][j]) > 15)
                resultImage[i][j] = 0;
            else
                resultImage[i][j] = 255;
        }
    }
}

void menu(){
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
    if(action == '0')
        return;
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
            detectEdges();
            break;
        case '8': //enlarge
            enlargeImage();
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
            skewHorizontal();
            break;
        case 'f': //skew up
            skewVertical();
            break;
        case 's': // save
            saveImage();
            break;
    }
    menu();
}
