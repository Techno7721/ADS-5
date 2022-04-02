// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
using namespace std;

int prior(char op)
{
    switch (op)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case ' ':
        return -10;
    default:
        return -1;
    }
}

string infx2pstfx(string inf) {
    TStack<char, 100> stack1;
    string str = "";
    int length = inf.length();
    for (int i = 0; i < length; ++i) {
        if (prior(inf[i]) == -1) {
            while ((prior(inf[i]) == -1) && (i < length)) {
                str += inf[i];
                ++i;
                //cout << 1;
            }
            str += " ";
        }
        if ((prior(inf[i]) == 0) || (prior(inf[i]) > prior(stack1.get())) || (stack1.isEmpty())) {
            stack1.push(inf[i]);
        } else {
            if (prior(inf[i]) == 1) {
                while (prior(stack1.get()) != 0) {
                    str += stack1.get();
                    str += " ";
                    stack1.pop();
                    //cout << 2;
                }
                stack1.pop();
            }
            else if (prior(inf[i]) <= prior(stack1.get())) {
                while (prior(stack1.get()) > 1) {
                    str += stack1.get();
                    str += " ";
                    stack1.pop();
                    //cout << 3;
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        str += stack1.get();
        str += " ";
        stack1.pop();
        //cout << 4;
    }
    str.erase(str.size() - 1);
    return str;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    int k = post.length() - 1;
    for (int i = 0; i < k; ++i) {
        string str1 = "";
        while ((prior(post[i]) == -1) && (i < k)) {
            str1 += post[i];
            ++i;
            //cout << 5;
        }
        if (prior(post[i]) > 1) {
            int x = stack2.get();
            stack2.pop();
            int y = stack2.get();
            stack2.pop();
            if (post[i] == '+') {
                stack2.push((y + x));
            }
            if (post[i] == '-') {
                stack2.push((y - x));
            }
            if (post[i] == '*') {
                stack2.push((y * x));
            }
            if ((post[i] == '/') && (x != 0)) {
                stack2.push((y / x));
            }
        }
        if (str1 != "") {
            stack2.push(stoi(str1));
        }
    }
    return stack2.get();
}
