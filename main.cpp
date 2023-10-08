// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <bits/stdc++.h>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage();

void saveImage();

void BW();

void FLIP();

void MIRROR();

void CROP();

int main() {
    cout << "Please enter file name of the image to process\n";
    loadImage();
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
            "s-Save the image to a file\n"
            "0-Exit\n";
    char action;
    while (cin >> action, action != '0') {
        switch (action) {
            case '1':
                BW();
                break;
            case '2':

                break;
            case '3':

                break;
            case '4':
                FLIP();
                break;
            case '5':

                break;
            case '6':

                break;
            case '7':
                EDGE();
                break;
            case '8':

                break;
            case '9':

                break;
            case 'a':
                MIRROR();
                break;
            case 'b':

                break;
            case 'c':

                break;
            case 'd':
                CROP();
                break;
            case 'e':
                
                break;
            case 'f':
                
                break;
            case 's':
                saveImage();
                break;
        }
    
    }
    return 0;
}

//_________________________________________
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void BW() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int avg = (image[i][j] + 127) / 2;
            if (avg > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

void FLIP() {
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    char HorV;
    cin >> HorV;
    if (HorV == 'h') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(image[i][j], image[i][255 - j]);
            }
        }
    } else {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE / 2; i++) {
                swap(image[i][j], image[255 - i][j]);
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void MIRROR() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    char mir;
    cin >> mir;
    if (mir == 'r')
        //right side
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = image[i][255 - j];
            }
        }
        //left side
    else if (mir = 'l')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][255 - j] = image[i][j];
            }
        }
        //upper
    else if (mir = 'u')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[255 - i][j] = image[i][j];
            }
        }
        //down
    else if (mir = 'd')
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = image[255 - i][j];
            }
        }
}
//////////////////////////////////////////////////////////////////////////////////////////////

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
                image[i][j] = 255;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
