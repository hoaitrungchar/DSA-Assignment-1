#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"
class CharALNode {
public:
    CharALNode* next;
    string CharArrayList;
    long long sizeCharArrayList;
public:
    CharALNode() {
        next = NULL;
        sizeCharArrayList = 0;
        CharArrayList = "";
    };
    CharALNode(string s) {
        sizeCharArrayList = s.length();
        CharArrayList = s;
    };
};
class RefNode {
public: 
    CharALNode* address;
    long long numref=0;
    RefNode* next;
public:
    RefNode() {
        address =NULL;
        next = NULL;
        numref = 0;
    }
    RefNode(CharALNode* p) {
        address = p;
        numref=1;
    }
};
class DelNode {
public:
    DelNode* next;
    CharALNode* addressdelhead;
    CharALNode* addressdeltail;
    RefNode* addressrefhead;
    RefNode* addressreftail;
public:
    DelNode() {
        next = NULL;
        addressdelhead = NULL;
        addressdeltail = NULL;
        addressrefhead = NULL;
        addressreftail = NULL;
    }
    DelNode(CharALNode* addressdelhead, CharALNode* addressdeltail, RefNode* addressrefhead, RefNode* addressreftail) {
        this->addressdelhead = addressdelhead;
        this->addressdeltail = addressdeltail;
        this->addressrefhead = addressrefhead;
        this->addressreftail = addressreftail;
        next = NULL;

    }
};
class ConcatStringList {
public:
    CharALNode* head;
    CharALNode* tail;
    long long listlength;


public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes

public:
    ConcatStringList() {
        head = NULL;
        tail = NULL;
        listlength = 0;
    }
    void addALNode(CharALNode* p) {
        if (head == NULL)
        {
            head = tail = p;
            listlength += p->CharArrayList.length();
        }
        else {
            tail->next = p;
            tail = p;
            listlength += p->CharArrayList.length();
        }
    }
    void addALNodehead(CharALNode* p) {
        if (head == NULL)
        {
            head = tail = p;
            listlength += p->CharArrayList.length();
        }
        else {
            p->next = head;
            head = p;
            listlength += p->CharArrayList.length();
        }
    }
    ConcatStringList(const char* s) {
        CharALNode* p;
        p = new CharALNode;
        p->CharArrayList = s;
        p->sizeCharArrayList = (p->CharArrayList).length();
        if (head == NULL) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
        listlength += (p->sizeCharArrayList);
        refList.addreflist(head,tail);
    };
    ConcatStringList(string s) {
        CharALNode* p;
        p = new CharALNode;
        p->CharArrayList = s;
        p->sizeCharArrayList = (p->CharArrayList).length();
        if (head == NULL) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
        listlength += (p->sizeCharArrayList);
        refList.addreflist(head, tail);
    };
    int length()  const {
        return listlength;
    };
    char get(int index) const {
        if (index<0 || index>listlength - 1) throw out_of_range("Index of string is invalid!");

        CharALNode* p = head;
        while (index > (p->sizeCharArrayList))
        {
            index -= p->sizeCharArrayList;
            p = p->next;
        }
        return p->CharArrayList[index];
    };
    int indexOf(char c) const {
        CharALNode* p = head;
        int prelength = 0;
        while (p != NULL)
        {
            for (int i = 0; i < p->CharArrayList.length(); i++)
            {
                if (p->CharArrayList[i] == c) return prelength + i;
            }
            prelength += p->CharArrayList.length();
            p = p->next;
        }
        return -1;
    };
    std::string toString() const {
        string res = "";
        if (head != NULL)
        {
            CharALNode* p = head;
            while (p != NULL) {
                res += p->CharArrayList;
                p = p->next;
            }
        }
        return res;
    };
    ConcatStringList concat(const ConcatStringList& otherS) const {
        ConcatStringList *s =new  ConcatStringList();
        s->tail = otherS.tail;
        this->tail->next = otherS.head;
        s->head = this->head;

        refList.addreflist(s->head, s->tail);
        return *s;
    };
    ConcatStringList subString(int from, int to) const {
        if (from >= to) throw logic_error("Invalid range");
        if (from<0 || from>this->listlength - 1)out_of_range("Index of string is invalid");
        if (to<0 || to>this->listlength - 1)out_of_range("Index of string is invalid");
        ConcatStringList s;
        CharALNode* p = head;
        int tong = 0;
        while (p != NULL) {
            tong += p->CharArrayList.length();
            if (tong >= from) break;
            else {
                p = p->next;
            }
        }
        int vitristart = from - (tong - p->CharArrayList.length());
        to--;
        CharALNode* start = p;
        CharALNode* endt = p;
        if (tong >= to) CharALNode* endt = p;
        else {
            p = p->next;
            while (p != NULL) {
                tong += p->CharArrayList.length();
                if (tong >= to) break;
                else {
                    p = p->next;
                }
            }
            endt = p;
        }
        int vitriend = to - (tong - p->CharArrayList.length());
        if (start == endt) {
            ConcatStringList s1(p->CharArrayList.substr(from, to - from + 1));
            return s1;
        }
        p = start;
        cout << p->CharArrayList.substr(vitristart, p->CharArrayList.length() - vitristart) << endl;
        CharALNode* addes = new CharALNode(p->CharArrayList.substr(vitristart, p->CharArrayList.length() - vitristart));
        s.addALNode(addes);

        while (p->next != endt) {
            p = p->next;
            CharALNode* adde = new CharALNode(p->CharArrayList.substr(0, p->CharArrayList.length()));
            cout << p->CharArrayList << ' ' << p->CharArrayList.substr(0, p->CharArrayList.length()) << endl;
            s.addALNode(adde);
        }
        p = p->next;
        CharALNode* addee = new CharALNode(p->CharArrayList.substr(0, vitriend));
        cout << addee->CharArrayList << ' ' << vitriend << ' ' << p->CharArrayList.substr(0, vitriend) << endl;
        s.addALNode(addee);
        return s;
    };
    ConcatStringList reverse() const {
        ConcatStringList s;
        CharALNode* p = head;
        while (p != NULL)
        {
            string adds = "";
            for (int i = p->CharArrayList.length() - 1; i >= 0; i--)
            {
                adds += p->CharArrayList[i];

            }
            CharALNode* add = new CharALNode(adds);
            s.addALNodehead(add);
            p = p->next;
        }
        return s;

    };
    ~ConcatStringList() {
        if (head == tail) {
            delStrList.adddelnode(head,tail, refList.getnode(head), refList.getnode(tail));
            refList.delrefnode(head, 2);

        }
        else {
            delStrList.adddelnode(head, tail, refList.getnode(head), refList.getnode(tail));
            refList.delrefnode(head, 1);
           refList.delrefnode(tail, 1);
        }
        /*if (refList.refCountAtNode(head) == 0 && refList.refCountAtNode(tail) == 0)
        {
            delStrList.adddelnode(head, tail, refList.getnode(head), refList.getnode(tail));
            CharALNode* p = head;
            CharALNode* cur = p;
            while (p != NULL)
            {
                p = p->next;
                delete cur;
                cur = p;
            }
            head = tail = NULL;
        }saicansua*/
    };

public:
    class ReferencesList {
        // TODO: may provide some attributes
    public:
        RefNode* head;
        RefNode* tail;
        int count = 0;
        int totalrefcount = 0;
    public:
        
        int size() const {
            return count;
        };
        ReferencesList() {
            head = tail = NULL;
        }
        
        void addreflist(CharALNode*a, CharALNode*b) {
            if (count == 0) {
                if (a == b) {
                    head = new RefNode(a);
                    tail = head;
                    (head->numref)= (head->numref)+1;
                    totalrefcount = 2;
                    count = 1;
                    return;

                }
                else {
                    head = new RefNode(a);
                    tail = new RefNode(b);
                    head->next = tail;
                    count = 2;
                    totalrefcount = 2;
                    return;
                }
            }
           
            //if (a == b) {
                themrefnode(a);
                themrefnode(b);
            /*}
            else {
                CharALNode* p = a;
                while (p != NULL)
                {
                    themrefnode(p);
                    p = p->next;
                }
            }*/ 

        }
        void themrefnode(CharALNode*a) {
            int check = 0;
            RefNode* p = head;
            while (p != NULL) {
                if (p->address == a)
                {
                    check = 1;
                    p->numref = p->numref+1;
                    break;
                }
                p = p->next;
            }
            if (check == 0) {
                RefNode* b=new RefNode(a);
                b->next=head;
                head = b;
                count++;
            }
           
            if (p!=NULL&&p->next != NULL && p->numref > p->next->numref) {
                RefNode* prep = head;
                while (prep->next != p)
                {
                    prep = prep->next;
                }
                RefNode* cur = p;
                RefNode* pre = NULL;
                while (cur!=NULL&&cur->numref <= p->numref)
                {
                    pre = cur;
                    cur = cur->next;
                }
                prep->next = p->next;
                pre->next = p;
                p->next = cur;
            }
            totalrefcount ++;
            
        }
        int refCountAtNode(CharALNode* a) {
            RefNode* p = head;
            while (p != NULL) {
                if (p->address == a)
                    return p->numref;
                p = p->next;
            }
            return -1;
        };
        RefNode* getnode(CharALNode* a) {
            RefNode* p = this->head;
            while (p != NULL) {
                if (p->address == a)
                    return p;
                p = p->next;
            }
            return p;
        }
        int refCountAt(int index) const {
            if (index < 0 || index >= count) throw out_of_range("Index of references list is invalid!");
            RefNode* p = head;
            int i = 0;
            while (i != index) {
                i++;
                p = p->next;
            }
            return p->numref;
        };
        std::string refCountsString() const {
            string s = "RefCounts[";
            if(totalrefcount==0) return "RefCounts[]";
            RefNode* p = head;
            if (p != NULL) {
                while (p->next != NULL) {
                    int x = p->numref;
                    stringstream a; a << x;
                    string s1;
                    a >> s1;
                    s = s + s1;
                    s += ",";
                    p = p->next;
                }
                int x = p->numref;
                stringstream a; a << x;
                string s2;
                a >> s2;
                s = s + s2;
            }
            s += "]";
            return s;
        };
        void delrefnode(CharALNode* a, int numdel) {
            RefNode* p = head;
            while (p != NULL) {
                if (p->address == a)
                {
                    p->numref = p->numref -numdel;
                    break;
                }
                p = p->next;
            }
            if (p->numref == 0) {
                if (p == tail) {
                    totalrefcount = totalrefcount - numdel;
                    return;
                }
                if (p == head) {
                    head = p->next;
                    totalrefcount = totalrefcount - numdel;
                    tail->next = p;
                    tail = p;
                    p->next = NULL;
                    return;
                }
                RefNode* prep = head;
                while (prep->next != p)
                {
                    prep = prep->next;
                }
                if (tail != NULL) {
                    prep->next = p->next;
                    tail->next = p;
                    tail = p;
               }
            }
            else {
                if (p == head) {

                    totalrefcount = totalrefcount - numdel;
                    return;
                }
               

                if (p == tail) {
                    RefNode* temp = head;
                    while (temp != NULL) {
                        if (temp->next == p) break;
                        temp = temp->next;
                    }
                    if (head->numref > p->numref)
                    {
                        tail = temp;
                        p->next = head;
                        head = p;
                        temp->next = NULL;
                        totalrefcount = totalrefcount - numdel;
                        return;
                    }
                    if (temp->numref <= p->numref)
                    {
                        totalrefcount = totalrefcount - numdel;
                        return;
                    }
                    RefNode* cur=head;
                    RefNode* pre = head;
                    while (cur->numref < p->numref) {
                        pre = cur;
                        cur = cur->next;
                    }
                    p->next = pre->next;
                    pre->next = p;
                    temp->next = NULL;
                    tail = temp;
                    totalrefcount = totalrefcount - numdel;
                    return;
                }
                RefNode* prep = head;
                while (prep->next != p)
                {
                    prep = prep->next;
                }
                if (head->numref >= p->numref) {
                    prep->next = p->next;
                    p->next = head;
                    head = p;
                    totalrefcount= totalrefcount-numdel;
                    return;
                }
                RefNode* cur = head;
                RefNode* pre = NULL;
                while (cur != NULL && cur->numref <= p->numref)
                {
                    pre = cur;
                    cur = cur->next;
                }
                prep->next = p->next;
                pre->next = p;
                p->next = cur;
            }
            totalrefcount = totalrefcount - numdel;
        }
        void delreflist(CharALNode* a, CharALNode* b) {
            if (totalrefcount != 0) return;
            this->~ReferencesList();
        }
        ~ReferencesList() {
            /*RefNode* p = head;
            RefNode* pre = p;
            while (p != NULL) {
                p = p->next;
                delete pre;
                pre = p;
            }*/
            head = tail = NULL;
        };
    };

    class DeleteStringList {
    public:
        int count = 0;
        DelNode* head;
        DelNode* tail;
    public:
        DeleteStringList() {
            count = 0;
            head = tail = NULL;
        };
        int size() const {
            return count;
        };
        long long totalref() const {
            DelNode* p = head;
            long long totalref = 0;
            while (p != NULL)
            {
                if (p->addressrefhead == p->addressreftail)
                    totalref += p->addressrefhead->numref;
                else {
                    totalref += p->addressrefhead->numref;
                    totalref += p->addressreftail->numref;
                }
                p = p->next;
            }
            return totalref;
        };
        std::string totalRefCountsString() const {
            if (this->totalref() == 0) return "TotalRefCounts[]";
            string s="TotalRefCounts[";
            stringstream a; a << this->totalref();
            string s1;
            a >> s1;
            s = s + s1;
            s += "]";
            return s;

        };
        void adddelnode(CharALNode* a, CharALNode* b, RefNode*c, RefNode* d) {
            DelNode* p = new DelNode(a, b,c,d);
            if (head == NULL) {
                head = tail = p;
                count = 1;
                return;
            }
            tail->next = p;
            tail = p;
        };
        /*void delnode(CharALNode* a) {
            if (head->addressdel == a)
            {
                DelNode* temp = head;
                if (head == tail) {
                    delete head;
                    head = tail = NULL;
                    return;
                }
                head = head->next;
                delete temp;
                return;
            }
            if (tail->addressdel == a)
            {
                DelNode* p = head;
                while (p->next != tail) {
                    p = p->next;
                }
                p->next = NULL;
                delete tail;
                tail = p;
                return;
            }
            DelNode* p = head;
            while (p->next != tail) {
                if (p->next->addressdel == a) {
                    DelNode* temp = p->next;
                    p->next = p->next->next;
                    delete temp;
                    return;
                }
                p = p->next;
            }
        };saicansua */
        ~DeleteStringList() {
            /*DelNode* temp = head;
            DelNode* p = head;
            while (p != NULL)
            {
                p = p->next;
                delete temp;
                temp = p;
            }
            count = 0;*/
            head = tail = NULL;

        }
    };
    
};

#endif // __CONCAT_STRING_LIST_H__#pragma once
