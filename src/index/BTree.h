//
// Created by lenovo on 2019/6/22.
//

#ifndef FINISHED_SELECT_ALL_BTREE_H
#define FINISHED_SELECT_ALL_BTREE_H


#include<vector>
#include<string>
#include <map>
#include <iostream>
#include <sstream>
#include"../common/Data.h"

using namespace std;

//extern BufferManager bm;
class TreeNode {
public:
    int num;
    TreeNode *parent;
    vector<Data> keys;
    vector<TreeNode *> childs;
    vector<int> vals;
    TreeNode *nextleaf;
    bool IsLeaf;
    int degree;

    TreeNode(int indegree, bool isLeaf);

    TreeNode();

    ~TreeNode();

    bool IsRoot();

    bool FindKey(const Data &key, int &index);

    TreeNode *SplitNode(Data &key);

    int AddKey(const Data &key);

    int AddKey(const Data &key, int val);

    bool DeleteKey(int index);

    void Shift(int index, int shiftmode);

private:
    void Rebuild(int index, TreeNode *node, int mode);
};

class Tree {
    friend class DbInterface;

private:
    typedef TreeNode *Node; //重命名TreeNode指针，方便后边进行操作
    struct SearchNode {     //用于临时存储查找的key值及所处的位置，方便进行操作
        Node node;  //包含对应key的节点指针
        int index;  //key在节点中的index
        bool IsFound;   //是否找到该key
    };
    string filename;
    Node root;  //根节点
    Node LeafHead;  //叶的最左端，用于便利结果用
    int keynum; //关键字数目
    int level;  //树的层数
    int nodenum;    //节点数目
    int degree;     //每个节点的度
public:
    Tree(int indegree, vector<Data>);    //利用key数组建立给定degree的树
    Tree();     //空树
    Tree(TreeNode *root, int Keynum, int Nodenum, int indegree);

    ~Tree();

    int SearchVal(const Data &key); //搜索key值，即搜索索引
    bool InsertKey(const Data &key, int val);   //插入key
    bool DeleteKey(const Data &key);    //删除键值
    void DropTree(Node node);   //删除树
    vector<TreeNode *> print();  //level order输出树的key值，用于debug

private:
    void Init();    //初始化
    bool AdjustAfterInsert(Node node);  //插入后调整
    bool AdjustAfterDelete(Node node);  //删除后调整
    void FindtoLeaf(Node node, const Data &key, SearchNode &snode);  //在叶子节点中找值
};

#endif //FINISHED_SELECT_ALL_BTREE_H
