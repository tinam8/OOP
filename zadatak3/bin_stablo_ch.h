enum ErrorCode{ success, duplicate, notfound};

template<typename T>
struct Node{
// konstruktori
    Node(){ left = nullptr; right = nullptr;}
    Node(T const & t){left = nullptr; right = nullptr; data = t;}
// podaci
    Node *left;
    Node *right;
    T data;
};


template<class T>
class BinarySTree{
public:
    /** Tip funkcije (vizitora) koja se poziva na svakom elementu pri obilasku stabla. */
     using Funct = void (*)(T&);
     /** Konstruktor. Kreira prazno stablo. */
     BinarySTree();
     /** Destruktor.  */
     ~BinarySTree();
     /** Vraca true ako je stablo prazno. */
     bool empty() const;
     /** Obilazi stablo u preorder poretku:
      *  root, lijevo podstablo, desno podstablo.
      *  Na svakom cvoru x stabla poziva visit(x->data).
      */
     void preOrder(Funct visit);
     /** Obilazi stablo u postorder poretku:
      *  lijevo podstablo, desno podstablo, root.
      *  Na svakom cvoru x stabla poziva visit(x->data).
      */
     void postOrder(Funct visit);
      /** Obilazi stablo u inorder poretku:
      *  lijevo podstablo, root, desno podstablo.
      *  Na svakom cvoru x stabla poziva visit(x->data).
      */
     void inOrder(Funct visit);
     /** Broj čvorova u stablu.  */
     int size();
     /** Obriši čitavo stablo. Dealociraj memoriju.  */
     void clear();
     /** Ubaci element u stablo tako da ostane uređeno. Ako element već postoji
      * u stablu ne radi ništa i vraća  kod "duplicate". Ako je element uspješno
      * ubačen vraća kod "success". */
     ErrorCode insert(T const & t);
     /** Vraća istinu ako je t u stablu; inače vraća laž.  */
     bool isInTree(T const & t) const;
     /** Ukloni element t iz stabla ukoliko je prisutan. Vraća kod "notfound" ako
      * t nije u stablu. Nakon brisanja binarno stablo mora ostati uređeno.
      * Vraća  "success" nakon uspješnog izbacivanja čvora iz stabla.  */
     ErrorCode remove(T const & t);
protected:
    Node<T> *root;
private:
    void preorder(Node<T>* root,Funct);
    void postorder(Node<T>* root,Funct);
    void inorder(Node<T>* root,Funct);
    ErrorCode insertpom(Node<T>* node,T const & t);
    int sizepom(Node<T>* node);
    bool isinTree(Node<T>* node,T const & t) const;
    void clearpom(Node<T>* node);
    T min(Node<T>* parent,Node<T>* node);
    T max(Node<T>* parent,Node<T>* node);
    Node<T>* find(Node<T>* node,T const & t);
    Node<T>* findParent(Node<T>* node,T const & t);
};

