#include <map>
#include <string>
#include <vector>
#include <iostream>

using std::map; using std::string;
using std::vector;

struct treeData
{
    char data;
    int occurence;
    treeData()
    {
        data = ' ';
        occurence = -1;
    };
    treeData(char dat)
    {
        data = dat;
        occurence = 1;
    }
    treeData(char dat, int occur)
    {
        data = dat;
        occurence = occur;
    };
};

bool compareData(const treeData &n1, const treeData &n2)
{
    return n1.occurence < n2.occurence;
}

struct treeNode
{
    treeData data;
    treeNode *left;
    treeNode *right;
    treeNode()
    {
        data = treeData();
        left = nullptr;
        right = nullptr;
    }
    treeNode(treeData tdata)
    {
        data = tdata;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree
{
public:
    treeNode *rootNode;
    BinaryTree()
    {
        rootNode = new treeNode();
    }
    BinaryTree(treeData tdata)
    {
        rootNode = new treeNode(tdata);
    }
    int getWeight()
    {
        int count = 0;
        calcWeight(rootNode, count);
        return count;
    }
    map<char, string> getCharMap()
    {
        map<char, string> retMap = map<char, string>();
        calcCodes(rootNode, retMap, "");
        return retMap;
    }
    string printTree()
    {
        string ret_str = "";
        getTreeOutput("", rootNode, ret_str);
        return ret_str;
    }

    /**
     * This method is used for storing trees in a file.
     * It's done by creating Huffman encoding map for the tree and writing all data in the map into a file.
     */
    string getFileDump()
    {
        string ret_str = "";
        map<char, string> charMap = getCharMap();
        
        for (auto const& mapobj: charMap) {
            ret_str += mapobj.second + "-" + mapobj.first + "\n";
        }
        return ret_str;
    }

private:
    /**
     * This function traverses all the tree recursively and gets sum of all occurences in the tree
     */
    void calcWeight(treeNode *node, int &count)
    {
        if (node == nullptr)
            return;

        calcWeight(node->left, count);
        if (node->data.occurence != -1)
            count += node->data.occurence;
        calcWeight(node->right, count);
    }
    /**
     * Recursive function for calculation of code table
     */
    void calcCodes(treeNode *node, map<char, string> &charMap, string currLoc)
    {
        if (node == nullptr)
            return;
        calcCodes(node->left, charMap, currLoc + '0');
        if (node->data.occurence != -1)
            charMap.insert(std::pair<char, string>(node->data.data, currLoc));
        calcCodes(node->right, charMap, currLoc + '1');
    }
    void getTreeOutput(string preStr, treeNode *node, string &currStr)
    {
        if (node != nullptr)
        {
            if (node == rootNode)
                currStr += " -- > root\n";
            else if (node->data.occurence == - 1)
                currStr += preStr +  "•\n";
            else 
                currStr += preStr + node->data.data + "\n";
            getTreeOutput(preStr + " -- > ", node->left, currStr);
            getTreeOutput(preStr + " -- > ", node->right, currStr);
        }
    }
};

bool compareTree(BinaryTree tr1, BinaryTree tr2)
{
    int w1 = tr1.getWeight();
    int w2 = tr2.getWeight();
    if (w1 == w2 && w1 == 1)
    {
        return tr1.rootNode->data.data < tr2.rootNode->data.data;
    }
    return tr1.getWeight() < tr2.getWeight();
}
/**
 * Tree merging function
 */
BinaryTree *mergeTree(BinaryTree tr1, BinaryTree tr2)
{
    treeNode *rn1 = tr1.rootNode;
    treeNode *rn2 = tr2.rootNode;

    BinaryTree *newTree = new BinaryTree();
    newTree->rootNode->left = rn1;
    newTree->rootNode->right = rn2;
    return newTree;
}
