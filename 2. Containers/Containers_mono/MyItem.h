#pragma once

#include <iostream>
#include <string>

using namespace std;

class MyItem
{
private:
    string _name;
public:
    MyItem()
    {
        cout << "MyItem()" << endl;
        _name = "";
    }
    MyItem(string name) : _name(name)
    {
        cout << "MyItem(string name)" << endl;
    }
    MyItem(const MyItem& other) : _name(other._name)
    {
        cout << "MyItem(const MyItem& other)" << endl;
    }
    MyItem(MyItem&& other) noexcept : _name("")
    {
        cout << "MyItem(MyItem&& other)" << endl;

        _name = move(other._name);
    }

    ~MyItem()
    {
        cout << "~MyItem() - " << _name << endl;
    }

    MyItem& operator=(const MyItem& other)
    {
        cout << "MyItem& operator=(const MyItem& other)" << endl;
        if (this != &other)
        {
            _name = other._name;
        }
        return *this;
    }
    MyItem& operator=(MyItem&& other) noexcept
    {
        cout << "MyItem& operator=(MyItem&& other)" << endl;
        if (this != &other)
        {
            _name = move(other._name);
        }
        return *this;
    }

    string getName() const
    {
        return _name;
    }
};