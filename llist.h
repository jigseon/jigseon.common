#pragma once
#include "ExceptionClass.h"
#include <iostream>
#include <string>

namespace jigseon
{

    template <class T>
    struct llist_node
    {
        T data;
        llist_node<T>* next;
        llist_node<T>* prev;
        llist_node()
        {
            next = NULL;
            prev = NULL;
        }
        llist_node(T& d)
        {

            next = NULL;
            prev = NULL;
            data = d;
        }
    };

    template <class T>
    class llist
    {
        llist_node<T>* head;
        llist_node<T>* tail;
        int nr_llist_nodes;

        bool InsertHead(T);
        bool InsertTail(T);
        bool InsertAt(int, T);

        bool Delete(llist_node<T>*);
        bool DeleteHead();
        bool DeleteTail();
        bool DeleteAt(int);

        llist_node<T>* GetHead() const;
        llist_node<T>* GetTail() const;

    public:
        llist();
        llist(T);
        llist(const llist&);
        ~llist();

        T& operator[] (int);
        class iterator // llist::iteraor 는 static 참조
        {
        private:
            llist_node<T>* currentP;
            bool direction;
        public:
            enum directions { forward, backward };
            iterator(llist_node<T>* current, bool dir = forward) { currentP = current; direction = dir; }

            void operator++() { currentP = (direction == forward) ? currentP->next : currentP->prev; }
            void operator++(int none) { currentP = (direction == forward) ? currentP->next : currentP->prev;; }
            void operator--() { currentP = (direction == forward) ? currentP->prev : currentP->next; }
            void operator--(int none) { currentP = (direction == forward) ? currentP->prev : currentP->next; }
            bool operator==(iterator i) { return (this->currentP == i.currentP) ? true : false; } // iterator &i 로 받을 경우 begin()에서 나온 iterator가  
            bool operator!=(iterator i) { return (this->currentP != i.currentP) ? true : false; }
            llist_node<T>& operator*() { return *currentP; }
            llist_node<T>* operator->() { return currentP; }

            /* ->를 오버로딩하면 x->f() 는 다음과 같이 해석된다
            (x.operator->())->f().
            */
        };
        iterator begin() { return iterator(GetHead()); }
        iterator end() { return iterator(NULL); }
        iterator rbegin() { return iterator(GetTail(), iterator::backward); }
        iterator rend() { return iterator(NULL, iterator::backward); }


        void append(T n) { this->InsertTail(n); }
        void clear() { while (this->DeleteHead()); }
        llist<T>& copy();
        int count() const { return this->nr_llist_nodes; };
        void extend(const llist<T> l);
        void remove(T);
        void reverse();
        void sort();
    };

    template <class T>
    llist<T>::llist()
    {
        nr_llist_nodes = 0;
        tail = NULL;
        head = NULL;
        return;
    }


    template <class T>
    llist<T>::llist(T data)
    {
        head = new llist_node<T>(data);
        if (head == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
        nr_llist_nodes = 1;
        head->next = NULL;
        head->prev = NULL;
        tail = head;
        return;
    }

    template <class T>
    llist<T>::llist(const llist<T>& l) // 복사생성자
    {
        llist_node<T>* temp = l.GetHead();

        nr_llist_nodes = 0;
        tail = NULL;
        head = NULL;

        while (temp != NULL)
        {
            this->InsertTail(temp->data);
            temp = temp->next;
        }
        this->nr_llist_nodes = l.nr_llist_nodes;
    }

    template <class T>
    bool llist<T>::InsertHead(T data)
    {
        if (head == NULL)
        {
            head = new llist_node<T>(data);
            if (head == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
            head->next = NULL;
            head->prev = NULL;
            tail = head;
        }
        else
        {
            llist_node<T>* temp = head;
            head = new llist_node<T>(data);
            if (head == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
            head->next = temp;
            temp->prev = head;
            head->prev = NULL;
        }
        nr_llist_nodes++;
        return true;
    }

    template <class T>
    bool llist<T>::InsertTail(T data)
    {
        if (tail == NULL)
        {
            tail = new llist_node<T>(data);
            if (tail == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
            tail->next = NULL;
            tail->prev = NULL;
            head = tail;
        }
        else
        {
            llist_node<T>* temp = tail;
            tail = new llist_node<T>(data);
            if (tail == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
            tail->prev = temp;
            temp->next = tail;
            tail->next = NULL;
        }
        nr_llist_nodes++;
        return true;
    }

    template <class T>
    bool llist<T>::InsertAt(int index, T data)
    {
        nr_llist_nodes++;
        llist_node<T>* temp = head, * newllist_node;

        if (index < 0)
        {
            throw InvalidInputException(__LINE__, __FUNCTION__, __FILE__);
        }

        if (head == NULL || index == 0)
        {
            InsertHead(data);
            return true;
        }
        else
        {
            for (int i = 1; i <= index - 1; i++)
            {
                if (temp->next == NULL) // 목표에 도달하지 못하였는데 널이라면..
                {
                    InsertTail(data);
                    return true;
                }
                temp = temp->next;
            }

            newllist_node = new llist_node<T>(data);
            if (head == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
            newllist_node->next = temp->next;
            newllist_node->next->prev = newllist_node;
            temp->next = newllist_node;
            newllist_node->prev = temp;
            return true;
        }
    }

    template<class T>
    inline bool llist<T>::Delete(llist_node<T>* node)
    {
        nr_llist_nodes--;

        if (node->prev == NULL)
            head = node->next;
        else
            node->prev->next = node->next;

        if (node->next == NULL)
            tail = node->prev;
        else
            node->next->prev = node->next;

        delete node;

        return false;
    }

    template <class T>
    bool llist<T>::DeleteHead()
    {
        nr_llist_nodes--;
        llist_node<T>* temp = head;

        if (head == NULL)
            return false;

        head = head->next;
        if (head == NULL)
            tail = NULL;
        delete temp;

        return true;
    }

    template <class T>
    bool llist<T>::DeleteTail()
    {
        nr_llist_nodes--;
        llist_node<T>* temp = tail;

        if (tail == NULL)
            return false;
        if (tail == head)
        {
            tail = NULL;
            head = NULL;
            delete tail;
            return true;
        }

        tail = tail->prev;
        if (tail == NULL)
            head = NULL;
        else
            tail->next = NULL;

        delete temp;

        return true;
    }

    template <class T>
    bool llist<T>::DeleteAt(int index)
    {
        nr_llist_nodes--;
        llist_node<T>* temp = head;
        if (index < 0)
            return false;

        if (tail == NULL || head == NULL)
            return false;
        else if (index == 0)
        {
            DeleteHead();
            return true;
        }
        else
        {
            for (int i = 1; i <= index; i++)
            {
                temp = temp->next;
                if (temp->next == NULL) // 목표에 도달하지 못하였는데 널이라면..
                {
                    DeleteTail();
                    return true;
                }
            }

            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;

            return true;
        }
    }

    template <class T>
    llist_node<T>* llist<T>::GetHead() const
    {
        return head;
    }

    template <class T>
    llist_node<T>* llist<T>::GetTail() const
    {
        return tail;
    }

    template <class T>
    llist<T>::~llist()
    {
        this->clear();
    }

    template <class T>
    T& llist<T>::operator[](int index)
    {
        if (index >= this->nr_llist_nodes || -index > this->nr_llist_nodes)
        {
            throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
        }


        auto it = (index >= 0) ? this->begin() : this->rbegin();

        for (int i = 0; i < index; i++)
            it++;


        return it->data;

    }

    template <class T>
    llist<T>& llist<T>::copy()
    {
        return new llist<T>(*this);
    }

    template <class T>
    void llist<T>::extend(const llist<T> l)
    {
        llist<T>* temp = new llist<T>(l);
        this->tail->next = temp->head;
        temp->head->prev = this->tail;
        this->nr_llist_nodes += temp->nr_llist_nodes;
        this->tail = temp->tail;
    }

    template <class T>
    void llist<T>::remove(T value)
    {
        for (llist<T>::iterator it = this->begin(); it != this->end(); it++)
        {
            if (it->data == value) {
                this->Delete(&*it);
                return;
            }
        }
    }

    template <class T>
    void llist<T>::reverse()
    {

    }

    template <class T>
    void llist<T>::sort()
    {

    }

}
