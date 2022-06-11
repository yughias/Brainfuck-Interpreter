#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

bool isKeyWord(char);
void loadBrainfuck(vector<char>&, const char*);
void push(int);
int pop();
void skip();
void emulate();


char keywords[8] = { '>', '<', '+', '-', '.', ',', '[', ']'};

vector<char> bCode;
int codeIndex = 0;
int memoryIndex = 0;

vector<int> stack;

char memory[128];


int main(){
    loadBrainfuck(bCode, "brainfuck.txt");
    while(codeIndex != bCode.size()) {
        emulate();
    }
}

bool isKeyWord(char c){
    for(int i = 0; i < 8; i++)
        if(c == keywords[i])
            return true;
    return false;
}

void loadBrainfuck(vector<char>& vec, const char* filename){
    fstream file;
    file.open(filename);
    char character;
    while(file >> character){
        if(isKeyWord(character))
            vec.push_back(character);
    }
    file.close();
}

void emulate(){
    char instruction = bCode[codeIndex];
    switch(instruction){
        case '>':
        memoryIndex++;
        break;

        case '<':
        memoryIndex--;
        break;

        case '+':
        memory[memoryIndex]++;
        break;

        case '-':
        memory[memoryIndex]--;
        break;

        case '.':
        putchar(memory[memoryIndex]);
        break;

        case ',':
        memory[memoryIndex] = getchar();
        break;

        case '[':
        if(memory[memoryIndex] == 0)
            skip();
        else
           push(codeIndex);
        break;

        case ']':
        codeIndex = pop()-1;
        break;

    }
    codeIndex++;
}

void skip(){
    int counter = 1;
    while(counter != 0){
        codeIndex++;
        switch(bCode[codeIndex]){
            case '[':
            counter++;
            break;

            case ']':
            counter--;
            break;
        }
    }
}

void push(int val){
    stack.push_back(val);
}

int pop(){
    int val = stack.back();
    stack.pop_back();
    return val;
}