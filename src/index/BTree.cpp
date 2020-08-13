//
// Created by lenovo on 2019/6/22.
//

#include "BTree.h"

void TreeNode::Rebuild(int index, TreeNode *node, int mode)
{
    int i;
    switch (mode) {
        case 1: {
            for (i = index; i < degree; i++) {
                node->keys[i - index] = keys[i];
                keys[i] = Data();
                node->vals[i - index] = vals[i];
                vals[i] = 0;
            }
        }
            break;
        case 2: {
            for (i = index; i < degree + 1; i++) {

                node->childs[i - index] = childs[i];
                node->childs[i - index]->parent = node;
                childs[i] = NULL;
            }
            for (i = index; i < degree; i++) {
                node->keys[i - index] = this->keys[i];
                this->keys[i] = Data();
            }
        }
            break;

    }
}

void TreeNode::Shift(int index, int mode)
{
    int i;
    switch (mode) {
        case 1: {
            for (i = num; i > index; i--)
                keys[i] = keys[i - 1];
            for (i = num + 1; i > index + 1; i--)
                childs[i] = childs[i - 1];
        }
            break;
        case 2: {
            for (i = num; i > index; i--) {
                keys[i] = keys[i - 1];
                vals[i] = vals[i - 1];
            }
        }
            break;
        case 3: {
            for (i = index; i < num - 1; i++) {
                keys[i] = keys[i + 1];
                vals[i] = vals[i + 1];
            }
        }
            break;
        case 4: {
            for (i = index; i < num - 1; i++) {
                keys[i] = keys[i + 1];
                childs[i + 1] = childs[i + 2];
            }
        }
            break;
    }
}

TreeNode::TreeNode(int degreein, bool isLeaf)
{
    num = 0;
    parent = NULL;
    nextleaf = NULL;
    this->IsLeaf = isLeaf;
    degree = degreein;
    int i;
    for (i = 0; i < degree + 1; i++) {
        childs.push_back(NULL);
        keys.push_back(Data());
        vals.push_back(0);
    }
    childs.push_back(NULL);
}

TreeNode::TreeNode()
{
    num = 0;
    parent = NULL;
    nextleaf = NULL;
    this->IsLeaf = 0;
    degree = 15;
    int i;
    for (i = 0; i < degree + 1; i++) {
        childs.push_back(NULL);
        keys.push_back(Data());
        vals.push_back(0);
    }
    childs.push_back(NULL);
}

TreeNode::~TreeNode()
{};

bool TreeNode::IsRoot()
{
    if (parent == NULL)
        return true;
    else return false;
}
//取大于它最接近的index值，若超过，则取num

bool TreeNode::FindKey(const Data &key, int &index)
{
    if (num == 0) {
        index = 0;
        return false;
    } else {
        if (keys[num - 1] < key) {
            index = num;
            return false;
        } else if (keys[0] > key) {
            index = 0;
            return false;
        } else if (num <= 15) {
            int i;
            for (i = 0; i < num; i++) {
                if (keys[i] == key) {
                    index = i;
                    return true;
                } else if (keys[i] < key) continue;
                else if (keys[i] > key) {
                    index = i;
                    return false;
                }
            }
        } else if (num > 15) {
            int left = 0, right = num - 1, pos = 0;
            while (right > left + 1) {
                pos = (right + left) / 2;
                if (keys[pos] == key) {
                    index = pos;
                    return true;
                } else if (keys[pos] < key)
                    left = pos;
                else if (keys[pos] > key)
                    right = pos;
            }
            if (keys[left] >= key) {    //3种情况
                index = left;
                return (keys[left] == key);
            } else if (keys[right] >= key) {
                index = right;
                return (keys[right] == key);
            } else if (keys[right] < key) {
                index = right + 1;
                return false;
            }
        }

    }
    return false;//应该不许用
}

TreeNode *TreeNode::SplitNode(Data &key)
{
    int i;
    int min;
    TreeNode *node = new TreeNode(this->degree, this->IsLeaf);
    if (IsLeaf) {
        min = (degree + 1) / 2;
        key = keys[min];    //放置到父亲节点中的key
        this->Rebuild(min, node, 1);
        node->nextleaf = this->nextleaf;
        this->nextleaf = node;
        node->parent = this->parent;
        node->num = (degree % 2 == 0) ? min : (min - 1);
        this->num = min;    //奇偶情况不同
    } else {
        min = degree / 2;
        key = keys[min];
        this->Rebuild(min + 1, node, 2);
        keys[min] = Data();
        node->parent = this->parent;
        node->num = (degree % 2 == 0) ? (min - 1) : min;
        this->num = min;    //奇偶情况不同
    }
    return node;

}

int TreeNode::AddKey(const Data &key)
{
    if (num == 0) {
        keys[0] = key;
        num++;
        return 0;
    } else {
        int index = 0;
        bool here = FindKey(key, index);
        if (here) {}
        else {//不存在插入
            this->Shift(index, 1);
            keys[index] = key;
            childs[index + 1] = NULL;
            num++;
            return index;
        }

    }
    return 0;
}

int TreeNode::AddKey(const Data &key, int val)
{
    if (IsLeaf) {
        if (num == 0) {
            keys[0] = key;
            vals[0] = val;
            num++;
            return 0;
        } else {
            int index = 0;
            bool here = FindKey(key, index);
            if (here) {}
            else {
                this->Shift(index, 2);
                keys[index] = key;
                vals[index] = val;
                num++;
                return index;   //直接插入，以后再调整
            }
        }
    } else
        return -1;
    return 0;
}

bool TreeNode::DeleteKey(int index)
{
    int i;
    if (index > num) return false;
    else {
        if (IsLeaf) {
            this->Shift(index, 3);
            keys[num - 1] = Data();
            vals[num - 1] = 0;

        } else {
            this->Shift(index, 4);
            keys[num - 1] = Data();
            childs[num] = NULL;
        }
        num--;
        return true;
    }
    return false;   //异常
}

Tree::Tree(int indegree, vector<Data> keys)
{
    //cout << 1 << endl;
    //cout << 2 << endl;
    keynum = 0;
    level = 0;
    nodenum = 0;
    root = NULL;
    LeafHead = NULL;
    degree = indegree;
    for (int i = 0; i < keys.size(); i++) {
        InsertKey(keys[i], i);
    }
    //从磁盘读入
}

Tree::Tree(TreeNode *Root, int Keynum, int Nodenum, int indegree)
{
    root = Root;
    keynum = Keynum;
    nodenum = Nodenum;
    degree = indegree;
    TreeNode *node = root;
    level = 1;
    while (node->childs[0] != NULL) {
        node = node->childs[0];
        level++;
    }
    LeafHead = node;
}

Tree::~Tree()
{

    keynum = 0;
    root = NULL;
    level = 0;
}

Tree::Tree()
{
    root = NULL;
    keynum = 0;
    level = 0;
    nodenum = 0;
    LeafHead = NULL;
    degree = 15;
}

void Tree::Init()
{
    root = new TreeNode(degree, true);
    keynum = 0;
    level = 1;
    nodenum = 1;
    LeafHead = root;
}

void Tree::FindtoLeaf(Node node, const Data &key, SearchNode &snode)
{
    int index = 0;
    if (node->FindKey(key, index)) {
        if (node->IsLeaf) {
            snode.node = node;
            snode.index = index;
            snode.IsFound = true;
        } else {   //不是叶节点，找下一层
            node = node->childs[index + 1];
            while (!node->IsLeaf) {
                node = node->childs[0];
            }
            snode.node = node;
            snode.index = 0;  //maybe problem
            snode.IsFound = true;

        }

    } else {
        if (node->IsLeaf) {
            snode.IsFound = false;
            snode.node = node;
            snode.index = index;
        } else {//递归查找
            FindtoLeaf(node->childs[index], key, snode);
        }
    }
    //return;
}

bool Tree::InsertKey(const Data &key, int val)
{
    SearchNode snode;
    if (!root) {
        Init();
    }
    FindtoLeaf(root, key, snode); //找到叶节点
    if (snode.IsFound) {
        return false;
    } else {
        snode.node->AddKey(key, val);
        if (snode.node->num == degree)
            AdjustAfterInsert(snode.node);
        keynum++;
        return true;

    }
}

bool Tree::AdjustAfterInsert(Node node)
{
    Data key;
    Node newnode = node->SplitNode(key);
    nodenum++;
    if (node->IsRoot()) {
        Node root = new TreeNode(degree, false);
        if (root != NULL) {
            level++;
            nodenum++;
            this->root = root;
            node->parent = root;
            newnode->parent = root;
            root->childs[0] = node;
            root->childs[1] = newnode;
            root->AddKey(key);
            return true;
        }

    } else {
        Node parent = node->parent;
        int index = parent->AddKey(key);
        parent->childs[index + 1] = newnode;
        newnode->parent = parent;
        if (parent->num == degree)
            AdjustAfterInsert(parent);
        return true;
    }
    return false;
}

int Tree::SearchVal(Data const &key)
{
    if (!root) return -1;
    SearchNode snode;
    FindtoLeaf(root, key, snode);
    if (!snode.IsFound) return -1;
    else return snode.node->vals[snode.index];
}

bool Tree::DeleteKey(Data const &key)
{
    SearchNode snode;
    if (!root) return false; //空树返回
    else {
        FindtoLeaf(root, key, snode); //搜索到叶节点
        if (snode.IsFound) {  //找不到返回false
            if (snode.node->IsRoot()) {   //根节点直接删除
                snode.node->DeleteKey(snode.index);
                keynum--;
                return AdjustAfterDelete(snode.node);
            } else {
                if (snode.index == 0 && LeafHead != snode.node) {   //不只存在与叶节点
                    int index = 0;
                    Node parentnow = snode.node->parent;
                    bool isfind = parentnow->FindKey(key, index);
                    while (!isfind) {
                        if (parentnow->parent)
                            parentnow = parentnow->parent;
                        else
                            break;
                        isfind = parentnow->FindKey(key, index);
                    }

                    parentnow->keys[index] = snode.node->keys[1]; //用第二个关键字代替
                    snode.node->DeleteKey(0);
                    keynum--;
                    return AdjustAfterDelete(snode.node);

                } else {//仅存在于叶节点
                    snode.node->DeleteKey(snode.index);
                    keynum--;
                    return AdjustAfterDelete(snode.node);

                }


            }
        }
    }
    return false;
}

bool Tree::AdjustAfterDelete(Node node)
{
    int min = degree / 2;   //degree为3时min为1，degree为4时min为2
    //if (degree == 3 && !node->IsLeaf&&node->num<0) return true;  //函数递归调用时会有用
    if (node->IsLeaf && node->num >= min)return true;
    else if (!node->IsLeaf && (node->num >= min - 1) && degree != 3) return true;
    if (node->IsRoot()) {
        if (node->num <= 0) {
            if (root->IsLeaf) {   //空树删除
                delete node;
                root = NULL;
                LeafHead = NULL;
                level--;
                nodenum--;
            } else {
                root = node->childs[0];
                delete node;
                level--;
                nodenum--;
                root->parent = NULL;
            }

        }
    } else {   //非根节点
        Node parent = node->parent;
        Node brother = NULL;
        if (node->IsLeaf) {
            int index = 0;
            parent->FindKey(node->keys[0], index);
            if ((parent->childs[0] != node) && (index + 1 == parent->num))
                //没有右兄弟且key值在该节点，选择左兄弟
            {
                brother = parent->childs[index];  //左兄弟
                if (brother->num <= min) {  //兄弟节点数目不足，合并两个节点
                    parent->DeleteKey(index);   //删除需要递归
                    int i;
                    for (i = 0; i < node->num; i++) {
                        brother->keys[i + brother->num] = node->keys[i];
                        brother->vals[i + brother->num] = node->vals[i];
                    }
                    brother->num += node->num;
                    brother->nextleaf = node->nextleaf;
                    delete node;
                    nodenum--;
                    return AdjustAfterDelete(parent);
                } else {   //兄弟节点数目充足，分一个节点
                    node->Shift(0, 2);
                    node->keys[0] = brother->keys[brother->num - 1];
                    node->vals[0] = brother->vals[brother->num - 1];
                    node->num++;
                    parent->keys[index] = node->keys[0];  // 替换掉，不许用递归
                    brother->DeleteKey(brother->num - 1);
                    return true;
                }

            } else {
                if (parent->childs[0] == node)
                    brother = parent->childs[1];  //选择右兄弟
                else
                    brother = parent->childs[index + 2];
                if (brother->num <= min) {
                    int i;
                    for (i = 0; i < brother->num; i++) {
                        node->keys[i + node->num] = brother->keys[i];
                        node->vals[i + node->num] = brother->vals[i];
                    }
                    if (node == parent->childs[0])
                        parent->DeleteKey(0);
                    else
                        parent->DeleteKey(index + 1);
                    node->num += brother->num;
                    node->nextleaf = brother->nextleaf;
                    nodenum--;
                    delete brother;
                    return AdjustAfterDelete(parent);
                } else {
                    node->keys[node->num] = brother->keys[0];
                    node->vals[node->num] = brother->vals[0];
                    brother->DeleteKey(0);
                    node->num++;
                    if (parent->childs[0] == node)
                        parent->keys[0] = brother->keys[0];
                    else
                        parent->keys[index + 1] = brother->keys[0];
                    return true;
                }

            }
        } else {   //非根非叶节点
            int index;
            parent->FindKey(node->childs[0]->keys[0], index);
            if (index == parent->num) index--;
            if ((parent->childs[0] != node) && (index + 1 == parent->num)) {
                brother = parent->childs[index];
                if (brother->num <= min - 1) {
                    brother->keys[brother->num] = parent->keys[index];
                    brother->num++;
                    parent->DeleteKey(index);   //需要递归
                    int i;
                    for (i = 0; i < node->num; i++) {
                        brother->childs[brother->num + i] = node->childs[i];
                        brother->keys[brother->num + i] = node->keys[i];
                        brother->childs[brother->num + i]->parent = brother;
                    }
                    brother->childs[brother->num + node->num] = node->childs[node->num];
                    brother->childs[brother->num + node->num]->parent = brother;
                    brother->num += node->num;
                    nodenum--;
                    delete node;
                    return AdjustAfterDelete(parent);
                } else {
                    node->childs[node->num + 1] = node->childs[node->num];
                    node->Shift(0, 0);
                    node->childs[1] = node->childs[0];
                    node->childs[0] = brother->childs[brother->num];
                    node->keys[0] = node->childs[1]->keys[0];
                    node->num++;
                    parent->keys[index] = brother->keys[brother->num - 1];
                    if (brother->childs[brother->num] != NULL)
                        brother->childs[brother->num]->parent = node;
                    brother->DeleteKey(brother->num - 1);
                    return true;
                }
            } else {
                if (parent->childs[0] == node)
                    brother = parent->childs[1];
                else
                    brother = parent->childs[index + 2];
                if (brother->num <= min - 1) {
                    node->keys[node->num] = parent->keys[index];
                    if (node == parent->childs[0])
                        parent->DeleteKey(0);
                    else
                        parent->DeleteKey(index + 1);
                    node->num++;
                    int i;
                    for (i = 0; i < brother->num; i++) {
                        node->childs[node->num + i] = brother->childs[i];
                        node->keys[node->num + i] = brother->keys[i];
                        node->childs[node->num + i]->parent = node;
                    }
                    node->childs[node->num + brother->num] = brother->childs[brother->num];
                    node->childs[node->num + brother->num]->parent = node;
                    node->num += brother->num;
                    for (i = 0; i < node->num; i++) {
                        node->keys[i] = node->childs[i + 1]->keys[0];
                    }
                    nodenum--;
                    delete brother;
                    return AdjustAfterDelete(parent);
                } else {
                    node->keys[node->num] = brother->keys[0];
                    node->childs[node->num + 1] = brother->childs[0];
                    node->childs[node->num + 1]->parent = node;
                    node->keys[node->num] = node->childs[node->num + 1]->keys[0];
                    node->num++;
                    if (parent->childs[0] == node)
                        parent->keys[0] = parent->childs[1]->keys[0];
                    else
                        parent->keys[index + 1] = parent->childs[index + 2]->keys[0];
                    brother->childs[0] = brother->childs[1];
                    brother->DeleteKey(0);
                    return true;
                }
            }
        }
    }
    return false;
}

vector<TreeNode *> Tree::print()
{
    Node node;
    vector<Node> nodes;
    vector<Node> output;
    nodes.push_back(root);
    output.push_back(root);
    while (nodes[0] != NULL) {
        node = nodes[0];
        int i;
        for (i = 0; i < node->num; i++) {
            cout << node->keys[i] << "\t";

            nodes.push_back(node->childs[i]);
            output.push_back(node->childs[i]);

        }

        nodes.push_back(node->childs[i]);
        output.push_back(node->childs[i]);

        cout << endl;
        nodes.erase(nodes.begin());

    }
    return output;
}
