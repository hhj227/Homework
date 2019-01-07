//
//  InfixToPostfixConvertAndCalculate.cpp
//  Data Structure Programming Report#1
//  Convert infix expression to Postfix expression and calculate the result
//
//  Created by 한혜정 on 06/01/2019.
//  Copyright © 2019 한혜정. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

//check if the character is operator
bool isOperator(char c);

//put weight to operator
int GetOperatorWeight(char op);

//compare weight between two operators
bool hasHigherPrecedence(char op1, char op2);

//convert infix expression to postfix expression
string infixPostfixTranslation(string exp);

//print results
void printResult(string exp, int num);

//insert spaces to expression
string insertSpace(string exp);

//calculate the expression
double calculatePostfixExp(string exp);

int main(int argc, const char * argv[]){
    int count = 1;
    string line;
    ifstream fin;
    fin.open("infix.txt", ios::in);
    if(!fin) cout << "File Open Error" << endl;
    
    getline(fin, line);
    while (getline(fin, line)){
        printResult(line, count);
        count++;
    }
    
    fin.close();
    
    return 0;
}

void printResult(string exp, int num){
    exp = exp.substr(0,exp.length()-1);
    string postfixExp = infixPostfixTranslation(exp);
    cout << "#" << num << endl;
    cout << "infix notation = " << insertSpace(exp) << endl;
    cout << "postfix notation = " << insertSpace(postfixExp) << endl;
    cout << "value = " << calculatePostfixExp(postfixExp) << endl;
    cout << endl;
}

string infixPostfixTranslation(string exp){
    stack<char> Stack;
    string postfix = "";
    for(int i=0;i<exp.length();i++){
        char token = exp[i];
        if(token==';') break;
        else if (token>='0'&&token<='9') postfix+=token;
        else if (token=='(') Stack.push(token);
        else if (token==')'){
            while (!Stack.empty()&&Stack.top()!='(') {
                postfix += Stack.top();
                Stack.pop();
            }
            Stack.pop();
        }else if (isOperator(token)){
            while (!Stack.empty() && Stack.top()!='(' && hasHigherPrecedence(Stack.top(), token)) {
                postfix += Stack.top();
                Stack.pop();
            }
            Stack.push(token);
        }
    }
    while (!Stack.empty()) {
        postfix += Stack.top();
        Stack.pop();
    }
    postfix += ';';
    
    return postfix;
}

bool isOperator(char c){
    if (c == '+'||c == '-'||c == '*'||c == '/'||c == '%'||c == '^')
        return true;
    else
        return false;
}

bool hasHigherPrecedence(char op1, char op2){
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);
    
    return op1Weight>=op2Weight?true:false;
}

int GetOperatorWeight(char op)
{
    int weight = -1;
    switch(op)
    {
        case '+':
        case '-':
            weight = 1;
            break;
        case '*':
        case '/':
        case '%':
            weight = 2;
            break;
        case '^':
            weight = 3;
            break;
    }
    return weight;
}

string insertSpace(string exp){
    string output = "";
    for (int i=0; i<exp.length(); i++) {
        output += exp.substr(i,1) + " ";
    }
    return output;
}

double calculatePostfixExp(string exp){
    stack<double> Stack;
    double num1, num2;
    double num3 = 0.0;
    double result;
    for(int i=0;i<exp.length();i++) {
        char token = exp[i];
        if (token>='0'&&token<='9') Stack.push((int)token - 48);
        else if (isOperator(token)){
            num2 = Stack.top();
            Stack.pop();
            num1 = Stack.top();
            Stack.pop();
            
            switch (token) {
                case '+':
                    num3 = num1+num2;
                    break;
                    
                case '-':
                    num3 = num1-num2;
                    break;
                    
                case '*':
                    num3 = num1*num2;
                    break;
                    
                case '/':
                    num3 = num1/num2;
                    break;
                    
                case '%':
                    num3 = (int)num1%(int)num2;
                    break;
                    
                case '^':
                    num3 = pow(num1, num2);
                    break;
                    
                default:
                    break;
            }
            Stack.push(num3);
        }
    }
    result = Stack.top();
    Stack.pop();
    
    return result;
}

