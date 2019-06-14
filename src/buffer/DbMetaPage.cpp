//
// Created by y on 2019-06-14.
//

#include "DbMetaPage.h"
#include <iostream>

using namespace std;

DbMetaPage::DbMetaPage(int recordCount) : recordCount(recordCount)
{}

DbMetaPage::~DbMetaPage()
{

}

void DbMetaPage::parsePage()
{
    cout << "Parsing page ..." << endl;
    printData();

}
