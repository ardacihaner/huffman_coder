#include <iostream>
#include "binary_tree.cpp"

using std::string;

/**
 * decode() function takes two arguments, the first one is the encoding tree that is going to be used
 * The second one is the encoded data.
 */
string decode(BinaryTree &tree, string input_string)
{
    string ret_str = "";
    treeNode *const rootNode = tree.rootNode;
    treeNode *node = rootNode;
    for (char c : input_string)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            ret_str += node->data.data;
            node = rootNode;
        }
        if (c == '0')
            node = node->left;
        if (c == '1')
            node = node->right;
    }
    ret_str += node->data.data;
    return ret_str;
}

/**
 * encode() function takes two arguments, the first one is the encoding tree that is going to be used
 * The second one is the strint to be encoded
 */
string encode(BinaryTree &tree, string input_data)
{
    string ret_string = "";

    map<char, string> charMap = tree.getCharMap();
    for (char c : input_data)
    {
        ret_string += charMap.at(c);
    }

    return ret_string;
}
