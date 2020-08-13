//
// Created by y on 2019-06-15.
//

#include "IndexPage.h"
void IndexPage::composePage(TreeNode *node, map<TreeNode *, page_id_t>  id,string type) {
    resetMemory();
    int size=4;
    if(type=="char")
        size=node->keys[0].type;
    memwrite_int(data,node->IsLeaf);
    memwrite_int(data+4,node->num);
    if(node->IsLeaf){
        int i;
        for( i=0;i<node->num;i++){
            memwrite_int(data+8+size*i+4*i,node->vals[i]);
            if(type=="int")
                memwrite_int(data+12+size*i+4*i,node->keys[i].i);
            else if(type=="float")
                memwrite_float(data+12+size*i+4*i,node->keys[i].f);
            else if(type=="char")
                memcpy(data+12+size*i+4*i,node->keys[i].s.c_str(),size);
        }
        memwrite_int(data+8+size*i+4*i,id[node->nextleaf]);

    }
    else{
        int i;
        for(i=0;i<node->num;i++){
            memwrite_int(data+8+size*i+4*i,id[node->childs[i]]);
            if(type=="int")
                memwrite_int(data+12+size*i+4*i,node->keys[i].i);
            else if(type=="float")
                memwrite_float(data+12+size*i+4*i,node->keys[i].f);
            else if(type=="char")
                memcpy(data+12+size*i+4*i,node->keys[i].s.c_str(),size);
        }
        memwrite_int(data+8+size*node->num+4*node->num,id[node->childs[node->num]]);
    }

}
void IndexPage::parsePage(string type,int keysize,vector<page_id_t >& id) {
    memread_int(data,(int*)&Isleaf);
    memread_int(data+4,&num);
    if(Isleaf){
        int i;
        for(i=0;i<num;i++){
            int value;
            memread_int(data+8+4*i+keysize*i,&value);
            vals.push_back(value);
            if(type=="int"){
                int key;
                memread_int(data+12+4*i+keysize*i,&key);
                keys.push_back(Data(key));
            }
            else if(type=="float"){
                float key;
                memread_float(data+12+4*i+keysize*i,&key);
                keys.push_back(Data(key));
            }
            else if(type=="char"){
                char key[keysize];
                memcpy(key,data+12+4*i+keysize*i,keysize);
                keys.push_back(Data(key,keysize));
            }
        }
        memread_int(data+4*i+keysize*i,&nextleaf);
    }
    else{
        int i;
        for(i=0;i<num;i++){
            int childId;
            memread_int(data+8+i*keysize+4*i,&childId);
            childsId.push_back(childId);
            id.push_back(childId);
            if(type=="int"){
                int key;
                memread_int(data+12+i*keysize+4*i,&key);
                keys.push_back(Data(key));
            }
            else if(type=="float"){
                float key;
                memread_float(data+12+i*keysize+4*i,&key);
                keys.push_back(Data(key));
            }
            else if(type=="char"){
                char key[keysize];
                memcpy(key,data+12+i*keysize+4*i,keysize);
                keys.push_back(Data(key,keysize));
            }
        }
        int childId;
        memread_int(data+8+i*keysize+4*i,&childId);
        childsId.push_back(childId);
        id.push_back(childId);
    }
}

