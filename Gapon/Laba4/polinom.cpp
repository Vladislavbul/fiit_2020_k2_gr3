#include <iostream>
#include "polinom.h"
#include "monom.h"

using namespace std;

polinom::polinom() 
{
    h = NULL;
    tail = NULL;
}

void polinom::add(int powx, int powy, int powz, double a) 
{
    link* t = new link(powx, powy, powz, a);
    if (h == NULL) 
    {
        h = new link(*t);
        delete t;
        return;
    }
    link* p = h;
    if (*p < *t)
    {
        t->next = p;
        h = t;
        return;
    }
    while (p->next != NULL && *p->next >= *t) p = p->next;
    if (*p == *t)
    {
        p->a += t->a;
        delete t;
        return;
    }
    if (p->next == NULL) 
    {
        p->next = t;
        tail = t;
        return;
    }
    if (p->next < t)
    {
        t->next = p->next;
        p->next = t;
        return;
    }
}

void polinom::add(const link& x)
{
    
    link* t = new link(x);
    if (h == NULL) {
        h = new link(x);
        delete t;
        return;
    }
    link* p = h;
    if (*p < *t) 
    {
        t->next = p;
        h = t;
        return;
    }
    link* parent = NULL;
    while (p->next != NULL && *p->next >= *t) { parent = p; p = p->next; }
    if (*p == *t)
    {
        p->a += t->a;
        if (abs(p->a) < 0.0000000001)
        {
            if (parent == NULL)
            {
                h = p->next;
                delete p;
            }
            else {
                parent->next = p->next;
                delete p;
            }
        }
        delete t;
        return;
    }
    if (p->next == NULL)
    {
        p->next = t;
        tail = t;
        return;
    }
    if (p->next < t) 
    {
        t->next = p->next;
        p->next = t;
        return;
    }
}

void polinom::add_to_tail(const link& x)
{
    if (tail == NULL) 
    {
        h = tail = new link(x);
        return;
    }

  


    link* t = new link(x);
    tail->next = t;
    tail = t;
}

void polinom::add_to_tail(int pow, double a)
{
    if (tail == NULL)
    {
        h = tail = new link(pow, a);
        return;
    }
    link* t = new link(pow, a);
    tail->next = t;
    tail = t;
}



ostream& operator<<(ostream& out, const polinom& t) 
{
    if (t.h != NULL) {
        link* p = t.h;
        while (p != NULL) {
            out << *p;
            if (p->next != NULL) out << " + ";
            p = p->next;
        }
    }
    return out;
}

polinom operator+(const polinom& x, const polinom& y)
{
    link* i = x.h;
    link* j = y.h;
    polinom res;
    while (i != NULL &&  j != NULL) 
    {

        if (i->pow==j->pow)
        {
            if (i->a + j->a)
            {
                
                res.add_to_tail(i->pow, i->a + j->a);
            }

            i = i->next;
            j = j->next;
        }
        else if (i->pow < j->pow)
        {
            res.add_to_tail(i->pow, i->a);
            i = i->next;
        }
        else
        {
            res.add_to_tail(j->pow, j->a);
            j = j->next;
        }
    }
    while (i != NULL) res.add_to_tail(*i), i = i->next;
    while (j != NULL) res.add_to_tail(*j), j = j->next;
    return res;
}

polinom operator*(const polinom& x, const polinom& y) 
{
    polinom res;
    for (link* i = x.h; i != NULL; i = i->next) 
    {
        for (link* j = y.h; j != NULL; j = j->next) 
        {
            link* ans = new link((*i) * (*j));
            res.add(*ans);
        }
    }
    return res;
}

void polinom::operator= (const polinom& x) 
{
    if (x.h == NULL) { h = NULL; return; }
    h = new link(*x.h);
    link* t = h;
    for (link* i = x.h->next; i != NULL; i = i->next) 
    {
        t->next = new link(*i);
        t = t->next;
    }
}
