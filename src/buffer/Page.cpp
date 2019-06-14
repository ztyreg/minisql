//
// Created by y on 2019-06-05.
//

#include "Page.h"
#include <iostream>
using namespace std;

void Page::printData()
{
    cout << "Page physical data ... ";
    for (int i = 0; i < PAGE_SIZE; ++i) {
        cout << data[i];
    }
    cout << endl;

}
