#include <iostream>
#include "bin_stablo_ch.h"


using namespace std;
/**Konstruktor */
template <typename T>
BinarySTree<T>::BinarySTree(){
    root = nullptr;
}
/** Destruktor.  */
template <typename T>
BinarySTree<T>::~BinarySTree(){

}
/** Vraca true ako je stablo prazno. */
template <typename T>
bool BinarySTree<T>::empty() const{
    if(root == nullptr){
        return true;
    }
    return false;
}

/** Obilazi stablo u preorder poretku:
*  root, lijevo podstablo, desno podstablo.
*  Na svakom cvoru x stabla poziva visit(x->data).
*/
template <typename T>
void BinarySTree<T>::preOrder(Funct visit){
    preorder(root,visit);
    }

/** Obilazi stablo u postorder poretku:
*  lijevo podstablo, desno podstablo, root.
*  Na svakom cvoru x stabla poziva visit(x->data).
*/
template <typename T>
void BinarySTree<T>::postOrder(Funct visit){
    postorder(root,visit);
    }

/** Obilazi stablo u inorder poretku:
*  lijevo podstablo, root, desno podstablo.
*  Na svakom cvoru x stabla poziva visit(x->data).
*/
template <typename T>
void BinarySTree<T>::inOrder(Funct visit){
    inorder(root,visit);
    }

/** Broj čvorova u stablu.  */
template <typename T>
int BinarySTree<T>::size(){
    return sizepom(root);
}

/** Obriši čitavo stablo. Dealociraj memoriju.  */
template <typename T>
void BinarySTree<T>::clear(){
    clearpom(root);
}

/** Ubaci element u stablo tako da ostane uređeno. Ako element već postoji
* u stablu ne radi ništa i vraća  kod "duplicate". Ako je element uspješno
* ubačen vraća kod "success". */
template <typename T>
ErrorCode BinarySTree<T>::insert(T const & t){
    if(root == nullptr){
        root = new Node<T>(t);
        return success;
    }
    return insertpom(root,t);
}

/** Vraća istinu ako je t u stablu; inače vraća laž.  */
template <typename T>
bool BinarySTree<T>::isInTree(T const & t) const{
    return isinTree(root,t);;
}

/** Ukloni element t iz stabla ukoliko je prisutan. Vraća kod "notfound" ako
* t nije u stablu. Nakon brisanja binarno stablo mora ostati uređeno.
* Vraća  "success" nakon uspješnog izbacivanja čvora iz stabla.  */
template <typename T>
ErrorCode BinarySTree<T>::remove(T const & t){

    Node<T>* found = find(root,t);
    if(found == nullptr){
        return notfound;
    }
    if(found->left != nullptr){
        found->data = max(found,found->left);
        return success;
    } else {
         if(found->right != nullptr){
            found->data = min(found,found->right);
            return success;
            } else {
               Node<T>* parent = findParent(root,found->data);
               if(parent->left != nullptr && parent->left->data == found->data){ //dodala sam provjeru parent->left != nullptr
                    parent->left = nullptr;
                    return success;
               } else {
                    parent->right = nullptr;
                    return success;
               }
            }
    }
}

template <typename T>
void BinarySTree<T>::preorder(Node<T>* root,Funct visit){
    if(root != nullptr){
        visit(root->data);
        //cout << root->data <<endl;
        preorder(root->left,visit);
        preorder(root->right,visit);
    }
}

template <typename T>
void BinarySTree<T>::postorder(Node<T>* root,Funct visit){
    if(root != nullptr){
        postorder(root->left,visit);
        postorder(root->right,visit);
        visit(root->data);
    }
}

template <typename T>
void BinarySTree<T>::inorder(Node<T>* root,Funct visit){
    if(root != nullptr){
        inorder(root->left,visit);
        visit(root->data);
        inorder(root->right,visit);
    }
}

template <typename T>
ErrorCode BinarySTree<T>::insertpom(Node<T>* start,T const & t){
    ErrorCode code = success;

    if(t == start->data){
        return duplicate;
    }

    if(t < start->data){
        if(start->left == nullptr){
           start->left = new Node<T>(t);

        } else {
            code = insertpom(start->left,t);
        }

    } else {
        if(start->right == nullptr){
           start->right = new Node<T>(t);
        } else {
            code = insertpom(start->right,t);
        }

    }

    return code;

}

template <typename T>
int BinarySTree<T>::sizepom(Node<T>* node){
    if(node == nullptr){
        return 0;
    }
    return sizepom(node->left)+1+sizepom(node->right);
}

template <typename T>
bool BinarySTree<T>::isinTree(Node<T>* node,T const & t) const {
    if(node == nullptr){
        return false;
    }

    if(t == node->data){
        return true;

    }

    if(t < node->data){
        return isinTree(node->left,t);
    }
    if(t > node->data){
        return isinTree(node->right,t);
    }

    return false;

}

template <typename T>
void BinarySTree<T>::clearpom(Node<T>* node){
    if(node == nullptr){
        return;
    }

    //za unistiti lijevu stranu
    if(node->left != nullptr){
        if(node->left->left == nullptr && node->left->right == nullptr){
            delete[] node->left;
        }else{
            clearpom(node->left);
        }
    }

    if(node->right != nullptr){
        if(node->right->left == nullptr && node->right->right == nullptr){
            delete[] node->right;
        }else{
            clearpom(node->right);
        }
    }
}

/**Metoda nalazi minimalni element u podstablu node stabla patent, vraca njegovu
oznaku i brise ga iz stabla*/
template <typename T>
T BinarySTree<T>::min(Node<T>* parent,Node<T>* node){
	if(node->left == nullptr){   //u slucaju da uopće ne idemo lijevo
		T ozn = node->data;
		parent->right = node->right;
		return ozn;
	}
    while(node ->left!= nullptr){
        parent = node;
        node = parent->left;
    }
    T ozn = node->data;//spremanje oznake
    parent->left = parent->right;//izbaci ga iz stabla
    return ozn;
}

/**Metoda nalazi maksimalni element u podstablu node stabla patent, vraca njegovu
oznaku i brise ga iz stabla*/
template <typename T>
T BinarySTree<T>::max(Node<T>* parent, Node<T>* node){
    if(node->right == nullptr){    // u slučaju da uopće ne idemo desno
		T ozn = node->data;
		parent->left = node->left;
		return ozn;
	}
    while(node->right != nullptr ){
        parent = node;
        node = parent->right;
    }
    T ozn = node->data;
    parent->right = node->left;
    return ozn;
}

/**Metoda nalazi i vraca(preko pintera )cvor u stablu node  s oznakom t*/
template <typename T>
Node<T>* BinarySTree<T>::find(Node<T>* node,T const & t) {
    if(node == nullptr){
        return nullptr;
    }

    if(t == node->data){
        return node;

    }

    if(t < node->data){
        return find(node->left,t);
    }
    if(t > node->data){
        return find(node->right,t);
    }

    return nullptr;

}

template <typename T>
Node<T>* BinarySTree<T>::findParent(Node<T>* start,T const & t) {
    if(start -> data == t){
        return nullptr; //nema roditelja
    }

    if(t < start->data){
        if(start->left != nullptr){
            if(t == start->left->data){
                return start;
            }
            return findParent(start->left,t);  //find->findParent
        }
    }
    if(t > start->data){
        if(start->right != nullptr){
            if(t == start->right->data){
                return start;
            }
            return findParent(start->right,t);  //find->findParent
        }
    }

    return nullptr;

}


using namespace std;
template <typename T>
void visit(T & ch)
{
    std::cout << ch << " ";
}

int main()
{

    BinarySTree<int> bst;

    std::cout << bst.empty() << std::endl;
    char cset[]={1,2,3,4,5,6};
    //char cset[]={'t','p','q','s','g','v','y','l','h'};

    for(auto c : cset){ bst.insert(c); //bst.inOrder(visit); cout << endl;
                                }
    bst.remove(6); bst.inOrder(visit); cout << endl;

    std::cout << "No of elements = " << bst.size() << "\n";

    std::cout << "Preorder :\n";
    bst.preOrder(visit);
    std::cout << "\n";

    std::cout << "Postorder :\n";
    bst.postOrder(visit);
    std::cout << "\n";

    std::cout << "Inorder :\n";
    bst.inOrder(visit);
    std::cout << "\n";

    std::cout << bst.isInTree(8) <<" " << bst.isInTree(2) << "\n";

    return 0;
}

