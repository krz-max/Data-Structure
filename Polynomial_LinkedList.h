#ifndef _109511028_H_
#define _109511028_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Term{
    public:
        int coeff;
        int px;
        int py;
        int pz;
        Term* NextTerm;
        Term():coeff(0), px(0), py(0), pz(0), NextTerm(NULL){;};
        Term(int co, int x, int y, int z):coeff(co), px(x), py(y), pz(z), NextTerm(NULL){;};
        Term(const Term& t2):coeff(t2.coeff), px(t2.px), py(t2.py), pz(t2.pz), NextTerm(NULL){;};
        ~Term(){;};
        
        bool operator==(const Term& t2) { return (px == t2.px) && (py == t2.py) && (pz == t2.pz); };
        bool operator>(const Term& t2);
};

struct Polynomial{
    public:
        int Terms;
        Term* Front;
        Term* Rear;
        Polynomial* NextPoly;

        Polynomial():Terms(0), Front(NULL), Rear(NULL), NextPoly(NULL){;};
        Polynomial(const Polynomial& p2);
        ~Polynomial();
        
        Polynomial operator+(const Polynomial& p2);
        Polynomial operator-(const Polynomial& p2);
        Polynomial operator*(const Polynomial& p2);
        void operator=(const Polynomial& p2);
 
        void insert(const Term& temp);
        void printP(ofstream& f_out);
};

class PolynomialList{
    private:
        int size;
        Polynomial* Head;
        Polynomial* Tail;
    public:
        PolynomialList():size(0), Head(NULL), Tail(NULL){;};
        ~PolynomialList();

        void Append(const Polynomial& p);
        void Add(int index1, int index2);
        void Sub(int index1, int index2);
        void Mul(int index1, int index2);
        void Del(int index);
        bool isEmpty() { return size == 0 && Head == NULL && Tail == NULL; };

        void printResult(ofstream& f_out);
};

bool Term::operator>(const Term& t2){
    if(px < t2.px) return false;
    if(px > t2.px) return true;
    if(py < t2.py) return false;
    if(py > t2.py) return true;
    if(pz < t2.pz) return false;
    if(pz > t2.pz) return true;
    return false;
}

Polynomial::Polynomial(const Polynomial& p2){
    NextPoly = NULL;
    if(p2.Terms == 0){
        Terms = 1;
        Front = Rear = new Term(0, 0, 0, 0);
    }
    else{
        Terms = p2.Terms;
        Front = Rear = new Term(*p2.Front);
        Term* walk1 = Front, *walk2 = p2.Front->NextTerm;
        while(walk2){
            Rear = Rear->NextTerm = new Term(*walk2);
            walk2 = walk2->NextTerm;
        }
    }
}

Polynomial::~Polynomial(){
    while(Front){
        Term* old = Front;
        Front = Front->NextTerm;
        delete old;
    }
    Front = Rear = NULL;
    Terms = 0;
};

Polynomial Polynomial::operator+(const Polynomial& p2){
    Polynomial sum;
    Term* walk1 = Front, *walk2 = p2.Front;
    while(walk1 && walk2){
        if(*walk1 == *walk2){
            if(walk1->coeff+walk2->coeff != 0)
                sum.insert(Term(walk1->coeff+walk2->coeff, walk1->px, walk1->py, walk1->pz));
            walk1 = walk1->NextTerm;
            walk2 = walk2->NextTerm;
        }
        else if(*walk1 > *walk2){
            sum.insert(Term(walk1->coeff, walk1->px, walk1->py, walk1->pz));
            walk1 = walk1->NextTerm;
        }
        else{
            sum.insert(Term(walk2->coeff, walk2->px, walk2->py, walk2->pz));
            walk2 = walk2->NextTerm;
        }
    }
    while(walk1){
        sum.insert(*walk1);
        walk1 = walk1->NextTerm;
    }
    while (walk2){
        sum.insert(*walk2);
        walk2 = walk2->NextTerm;
    }
    return sum;
}

Polynomial Polynomial::operator-(const Polynomial& p2){
    Polynomial sub;
    Term* walk1 = Front, *walk2 = p2.Front;
    while(walk1 && walk2){
        if(*walk1 == *walk2){
            if(walk1->coeff - walk2->coeff != 0)
                sub.insert(Term(walk1->coeff - walk2->coeff, walk1->px, walk1->py, walk1->pz));
            walk1 = walk1->NextTerm;
            walk2 = walk2->NextTerm;
        }
        else if(*walk1 > *walk2){
            sub.insert(Term(walk1->coeff, walk1->px, walk1->py, walk1->pz));
            walk1 = walk1->NextTerm;
        }
        else{
            sub.insert(Term(-walk2->coeff, walk2->px, walk2->py, walk2->pz));
            walk2 = walk2->NextTerm;
        }
    }
    while(walk1){
        sub.insert(*walk1);
        walk1 = walk1->NextTerm;
    }
    while (walk2){
        sub.insert(Term(-walk2->coeff, walk2->px, walk2->py, walk2->pz));
        walk2 = walk2->NextTerm;
    }
    return sub;
}

Polynomial Polynomial::operator*(const Polynomial& p2){
    Polynomial mul;
    Term* walk1 = Front;
    while(walk1){
        Polynomial now;
        Term* walk2 = p2.Front;
        while(walk2){
            if(walk1->coeff != 0 && walk2->coeff != 0)
                now.insert(Term(walk1->coeff * walk2->coeff, walk1->px+walk2->px, walk1->py+walk2->py, walk1->pz+walk2->pz));
            walk2 = walk2->NextTerm;
        }
        mul = mul + now;
        walk1 = walk1->NextTerm;
    }
    return mul;
}

void Polynomial::operator=(const Polynomial& p2){
    if(Front != NULL) this->~Polynomial();
    if(p2.Terms == 0){
        Terms = 1;
        Front = Rear = new Term(0, 0, 0, 0);
    }
    else{
        Terms = p2.Terms;
        Front = Rear = new Term(*p2.Front);
        Term* walk1 = Front, *walk2 = p2.Front->NextTerm;
        while(walk2){
            Rear = Rear->NextTerm = new Term(*walk2);
            walk2 = walk2->NextTerm;
        }
    }
    return ;
}

void Polynomial::insert(const Term& temp){
    if(Terms != 0 && temp.coeff == 0) return ;
    Terms++;
    if(Front == NULL && Rear == NULL){
        Front = Rear = new Term(temp);
        return ;
    }
    Rear = Rear->NextTerm = new Term(temp);
    return ;
}

void Polynomial::printP(ofstream& f_out){
    f_out << Terms << endl;
    Term *walk = Front;
    while(walk){
        f_out << walk->coeff << " " << walk->px << " " << walk->py << " " << walk->pz << endl;
        walk = walk->NextTerm;
    }
    return ;
}

PolynomialList::~PolynomialList(){
    size = 0;
    while (Head){
        Polynomial* old = Head;
        Head = Head->NextPoly;
        delete old;
    }
    Head = Tail = NULL;
}

void PolynomialList::Append(const Polynomial& temp){
    Polynomial *newPolynomial = new Polynomial(temp);
    if(size == 0){
        Head = Tail = newPolynomial;
        size++;
        return ;
    }
    Tail = Tail->NextPoly = newPolynomial;
    size++;
    return ;
}

void PolynomialList::Add(int index1, int index2){
    Polynomial* p1 = Head, *p2 = Head;
    while(index1--){
        p1 = p1->NextPoly;
    }
    while(index2--){
        p2 = p2->NextPoly;
    }
    Polynomial temp = *p1 + *p2;
    Append(temp);
    return ;
}

void PolynomialList::Sub(int index1, int index2){
    Polynomial* p1 = Head, *p2 = Head;
    while(index1--){
        p1 = p1->NextPoly;
    }
    while(index2--){
        p2 = p2->NextPoly;
    }
    Polynomial temp = *p1 - *p2;
    Append(temp);
    return ;
}

void PolynomialList::Mul(int index1, int index2){
    Polynomial* p1 = Head, *p2 = Head;
    while(index1--){
        p1 = p1->NextPoly;
    }
    while(index2--){
        p2 = p2->NextPoly;
    }
    Polynomial temp = *p1 * *p2;
    Append(temp);
    return ;
}

void PolynomialList::Del(int index){
    size--;
    Polynomial* old = Head;
    if(index == 0){
        Head = Head->NextPoly;
        delete old;
        return ;
    }
    Polynomial* walk = Head->NextPoly;
    while(--index){
        old = old->NextPoly;
        walk = walk->NextPoly;       
    }
    old->NextPoly = walk->NextPoly;
    delete walk;
    return ;
}

void PolynomialList::printResult(ofstream& f_out){
    Polynomial* walk = Head;
    while(walk){
        walk->printP(f_out);
        walk = walk->NextPoly;
    }
    return ;
}

#endif
