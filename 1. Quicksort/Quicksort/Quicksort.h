#pragma once

#include "iostream"

using namespace std;

const char MAGIC_NUMBER = 16;

template<typename T>
void myinsort(T* first, T* last, bool (*comp)(T, T))
{
    T* current = first + 1;
    T* end = last + 1;

    while (current != end)
    {
        T* temp = current;
        while (temp != first && comp(*temp, *(temp - 1)))
        {
            swap(*temp, *(temp - 1));
            temp--;
        }
        current++;
    }
}

template<typename T>
void myqsort(T* first, T* last, bool (*comp)(T, T))
{
    T* _first = first;
    T* _last = last;

    while (_first < _last)
    {
        // ≈сли сортируемый отрезок меньше MAGIC_NUMBER, то используем сортировку вставками 
        if (_last - _first <= MAGIC_NUMBER)
        {
            myinsort(_first, _last, comp);
            return;
        }

        // »щем мединный элемент
        T* mid = _first + ((_last - _first) / 2);
        if (comp(*mid, *_first))
            swap(*mid, *_first);
        if (comp(*_last, *_first))
            swap(*_last, *_first);
        if (comp(*_last, *mid))
            swap(*mid, *_last);
        T median = *mid;

        // Ёлементы меньше медианного переставл€ем слева от него, а бќльшие вправо
        T* new_median;
        T* l = _first;
        T* r = _last;
        while (true)
        {
            while (comp(*l, median))
            {
                l++;
            }
            while (comp(median, *r))
            {
                r--;
            }
            if (l >= r)
            {
                new_median = r;
                break;
            }
            swap(*r, *l);
        }

        // –екурсивно вызываем этот же алгоритм дл€ меньшего отрезка 
        if (new_median - _first < _last - new_median)
        {
            myqsort(_first, new_median, comp);
            _first = ++new_median;
        }
        else
        {
            myqsort(new_median + 1, _last, comp);
            _last = new_median;
        }
    }
}