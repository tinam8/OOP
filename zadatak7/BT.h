#include <memory>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stack>

class Grid {
    private:
        class Segment{
            public:
                // Konstruktor.
                Segment(double left, double right, Segment * parent);
                // Sve metode kontrole kopiranja neka su izbrisane.
                Segment(Segment const &) = delete;
                Segment & operator=(Segment const &) = delete;
                Segment(Segment &&) = delete;
                Segment & operator=(Segment &&) = delete;

                // Da li je segment list (nema djece) ?
                bool isLeaf() const;
                // Profini segment. Ako već ima djecu ne radi ništa.
                void refine();
                // Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
                // list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak
                // std::runtime_error() s opisom greške.
                void coarse();
                // Vrati pokazivač na lijevi podsegment ili nullptr.
                Segment * getLeft()  { return mseg_l.get(); }
                // Vrati pokazivač na desni podsegment ili nullptr.
                Segment * getRight() { return mseg_r.get(); }
                // Ispiši segment.
                void print(){std::cout << "(" << mpt_l <<","<<mpt_r<<") ";}
                // Vrati pokazivač na roditelja.
                Segment * parent() { return mparent; }
                // Da li je x u [mpt_l,mpt_r) ?
                bool isIn(double x) const;
                // lijevi kraj segmenta
                double left()  const { return mpt_l; }
                // desni kraj segmenta
                double right() const { return mpt_r; }
                // duljina segmenta.
                double length() const { return mpt_r - mpt_l;}

                class GridLeafIterator{
                    public:
                        GridLeafIterator(Segment* root);
                        // operator inkrementiranja (dovoljna je prefiks verzija)
                        GridLeafIterator& operator++();
                        // operatori dohvata - dereferenciranje i operator strelica
                        const Segment& operator*() const { return *mRoot; }
                        Segment& operator*(){ return *mRoot; }

                        const Segment* operator->() const { return mRoot; }
                        Segment* operator->(){ return mRoot; }


                    private:
                        Segment *  mRoot;
                        std::unique_ptr<std::stack<Segment*>> mStack;
                        void last() {mRoot = nullptr;}
                        // implementacijski detalji
                        // ...
                        friend
                        bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
                        friend
                        bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
                };

            private:
              // lijevi kraj segmenta
              double mpt_l;
              // desni kraj segmenta
              double mpt_r;
              // djeca segementa
              std::unique_ptr<Segment> mseg_l;  // lijevi podsegment
              std::unique_ptr<Segment> mseg_r;  // desni podsegment
              // segment roditelj
              Segment * mparent;
              // deklaracija iteratora
            //  friend class GridLeafIterator;
            };



    public:
       using iterator = Segment::GridLeafIterator;

       Grid(double a, double b): root(a,b, nullptr) {//std::cout << "Grid konstruktor\n" << std::endl;}
}
       iterator begin();
       iterator end();

       // Profini svaki segment list u trenutnoj mreži.
       void uniform_refine();
       // Ispiši sve segmente listove mreže.
       void print();
       // Broj segmenata listova u mreži.
       int  nOfSegments();
       // Profini segment list koji sadrži točku x. Izbaci
       // izuzetak ako je točka izvan domene.
       void refine_selected(double x);
        // Eliminiraj  segment list koji sadrži točku x. Ako segment
        // rođak nije list izbaci izuzetak. Učini isto ako je točka izvan domene.
       void coarse_selected(double x);
       // lijevi kraj domene
       double left() const { return root.left(); }
       // desni kraj domene
       double right() const { return root.right(); }

    private:
       Segment root;
};




