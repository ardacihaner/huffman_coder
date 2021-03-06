# huffman_coder

A Huffman coder implemented in C++ for educational purposes.

# Usage

I wrote this program to run on Linux, but should be compatible with macOS as well. I don't use Windows, but it should work on WSL(Windows Subsystem for Linux).\
GCC with C++ support should be installed on your system. You can compile the project by just typing make on your terminal.\
```make```\
To run your program, ensure the executable file has permission to execute.\
```chmod +x huffmancoder```\
Then, run the executable file.\
```./huffmancoder```

# For Huffman encoding

```./huffmancoder -i input_file.txt -encode``` to encode the given file\
```./huffmancoder -i input_file.txt -encode -s <char>``` to get Huffman encoding of the specified character. 

# For Huffman 

```./huffmancoder -i input_file.txt -decode``` to decode the given file
 
# Misc

```./huffmancoder -l``` to visualize the created tree during encoding process. This can be improved.
