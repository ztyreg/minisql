//
// Created by y on 2019-06-15.
//

#ifndef MINISQL_INDEXPAGE_H
#define MINISQL_INDEXPAGE_H


/**
 * IndexPage.h
 *
 *
 *
 *  --------------------------------------------------------------------------
 * | Type(1)|  NodeNum(4)| ......| FreeSpacePointer(4) |
 *  --------------------------------------------------------------------------
 *  Branch Node
 *  --------------------------------------------------------------
 * | 0 | NodeNum (4) | Child0 id(4) | Key0( ) | Child1(4)| Key1() | ......Childi(4) |
 *  --------------------------------------------------------------
 *  Leaf  Node
 *  --------------------------------------------------------------
 * | 1 | NodeNum (4) | Offset0 (4) | Key0( ) | Offset1(4)| Key1() | ......NextLeafid(4) |
 *  --------------------------------------------------------------
 */
#include "Page.h"
#include <string>
#include"../index/BTree.h"

class IndexPage : public Page {
    friend class DbInterface;

private:
    bool Isleaf;    //是否为叶节点
    vector<page_id_t> childsId;    //儿子节点id
    vector<Data> keys;  //关键字
    vector<int> vals;   //value
    int nextleaf;   //下一个叶节点的id
    int num;    //该节点中的关键字数目
public:
    /* initialize header */
    explicit IndexPage(Page *p) : Page(*p)
    {};

    void composePage(TreeNode *node, map<TreeNode *, page_id_t>, string type);   //写入
    void parsePage(string type, int keysize, vector<page_id_t> &);    //解析
};


#endif //MINISQL_INDEXPAGE_H
