#include <vector>
#include <algorithm>
#include <iostream>
#include "coding.cpp"

using std::string; using std::vector;

// A function that splits string by delimiter and returns a vector<string>
vector<string> split(string str, string delimiter) {
    vector<string> retvec;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        retvec.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    retvec.push_back(str);

    return retvec;    
}

int find_in_vector(vector<treeData> treeVec, char data_to_find) 
{
    auto iter = std::find_if(treeVec.begin(), treeVec.end(), [&](const treeData& data) {
        return data.data == data_to_find;
    });
    
    if (iter == treeVec.end() || treeVec.size() == 0) {
        return -1;
    }
    return iter - treeVec.begin();
        
}

// Generating encoding tree from given string
BinaryTree generateTree(string input_data)
{
    vector<BinaryTree> trees;
    vector<treeData> datas = vector<treeData>();
    vector<char> known_chars = vector<char>();
    for (char c : input_data)
    {
        int index = find_in_vector(datas, c);
        if (index == -1)
            datas.push_back(treeData(c));
        else
            datas.at(index).occurence += 1;
    }

    for (treeData data : datas)
    {
        trees.push_back(BinaryTree(data));
    }
    std::sort(trees.begin(), trees.end(), compareTree); // Sorting trees by their total weights
    while (trees.size() > 1)
    {
        BinaryTree *mergedTree = mergeTree(trees.at(0), trees.at(1)); 
        trees.at(0) = (*mergedTree);
        trees.erase(trees.begin() + 1);
        std::sort(trees.begin(), trees.end(), compareTree);
    }

    return trees.at(0);
}

// Binary trees that generated for encoding are stored in "treedump" file for using it later, this function generates tree from "treedump"
BinaryTree generateTreeFromFile(vector<string> file_content) {
    BinaryTree newTree = BinaryTree();
    vector<string> split_vec = vector<string>();
    treeNode* currNode = newTree.rootNode;

    for (string line: file_content) {
        currNode = newTree.rootNode;
        split_vec = split(line, "-");
        for (char c : split_vec[0])
        {
            if (c == '0')
            {
                if (currNode->left == nullptr)
                    currNode->left = new treeNode();
                currNode = currNode->left;
            }
            if (c == '1')
            {
                if (currNode->right == nullptr)
                    currNode->right = new treeNode();
                currNode = currNode->right;
            }
        }

        currNode->data = split_vec[1][0];

    }

    return newTree;
}

