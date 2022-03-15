#include "Set.h"
#include <iostream>
#include <cassert>
#include <cmath>
/**
 * @brief Struttura che implementa un punto 
 * 
 */
struct point{
    int x;///< coordinata x
    int y;///< coordinta y

public:
    /**
     * @brief costruttore di default
     * 
     */
    point() : x(), y() {}
    /**
     * @brief Costruttore secondario
     * 
     * @param i coordinata x
     * @param j coordinata y
     */
    point(int i, int j) : x(i), y(j) {}
    
    /**
     * @brief Copy constructor
     * 
     * @param other oggetto point da cui copiare i dati
     */
    point(const point &other) : x(other.x), y(other.y) {}
    
    /**
     * @brief Distruttore
     * 
     */
    ~point() {}

    /**
     * @brief Operatore assegnamento
     * 
     * @param other oggetto point da cui copiare i dati
     * @return reference all'oggetto this
     */
    point &operator=(const point &other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    /**
     * @brief Operatore==
     * 
     * @param other oggetto point 
     * @return true se i gue oggetti hanno le stesse coordinate
     * @return false se i gue oggetti non hanno le stesse coordinate
     */
    bool operator==(const point &other) const{
        return (x == other.x) && (y == other.y);
    }
    /**
     * @brief Operatore di strea,
     * 
     * @param os oggetto stream
     * @param p oggetto point
     * @return reference all'oggetto os
     */
    friend std::ostream &operator<<(std::ostream &os, const point &p){
        return os<<"("<<p.x<<", "<<p.y<<")";
    }
    /**
     * @brief getter della coordinata x
     * 
     * @return int x
     */
    int getX()const{
        return x;
    }
    /**
     * @brief getter della coordinata y
     * 
     * @return int y
     */
    int getY() const{
        return y;
    }
    /**
     * @brief Calcola la distanza tra il punto this e il punto
     * passato come parametro
     * 
     * @param p punto da cui calcolare la distanza
     * @return double valore della distanza tra i due punti
     */
    double distance_from(const point &p) const{
        return sqrt(pow(x-p.x, 2) + pow(y-p.y, 2));
    }
};
/**
 * @brief Classe Concessionaria che utilizza la classe Set
 * per memorizzare una collezione di auto
 * 
 */
class Concessionaria{
    public:
        /**
         * @brief Struttura che implementa un'auto
         */
        struct Auto{
            std::string targa;///< targa dell'auto
            std::string modello;///< modello dell'auto

            public:
                /**
                 * @brief Costruttore di default
                 * 
                 */
                Auto():targa(""), modello(""){}

                /**
                 * @brief Costruttore secondario
                 * 
                 * @param t targa
                 * @param m modello
                 */
                Auto(const std::string &t, const std::string &m):targa(t), modello(m){}

                /**
                 * @brief Copy constructor
                 * 
                 * @param other oggetto auto da cui copiare i dati
                 */
                Auto(const Auto &other) : targa(other.targa), modello(other.modello){}
                /**
                 * @brief Operatore assegnamento
                 * 
                 * @param other oggetto auto da cui copiare i dati
                 * @return oggetto this
                 */
                Auto& operator=(const Auto &other){
                    targa=other.targa;
                    modello=other.modello;
                    return *this;
                }
                /**
                 * @brief Distruttore
                 * 
                 */
                ~Auto(){}
                /**
                 * @brief Operatore di stream
                 * 
                 * @param os oggetto di stream
                 * @param a oggetto auto da spedire sullo stream
                 * @return reference os
                 */
                friend std::ostream& operator<<(std::ostream &os, const Auto& a){
                    return os<<"[" <<a.modello <<", "<<a.targa<<"]";
                }  
                /**
                 * @brief Opeatore ==
                 * 
                 * @param a oggetto auto
                 * @return true se l'oggetto this ha la stessa targa dell'oggetto a
                 * @return false se l'oggetto this non ha la stessa targa dell'oggetto a
                 */
                bool operator==(const Auto& a)const{
                    return targa==a.targa;
                }
        };
        /**
         * @brief Funtore predicato di uguaglianza tra due auto
         * 
         */
        struct equals_auto{
            bool operator()(const Auto &a, const Auto &b)const{
                return a==b;
            }
        };
        
    private:
        Set<Auto, equals_auto> _veicoli;///< insieme delle auto

    public:
        /**
         * @brief Costruttore di default
         * 
         */
        Concessionaria():_veicoli(){}

        /**
         * @brief Copy constructor
         * 
         * @param other oggetto da cui copiare
         */
        Concessionaria(const Concessionaria &other):_veicoli(){
            Set<Auto, equals_auto>::const_iterator b,e;
            try{
                for(b=other._veicoli.begin(), e=other._veicoli.end(); b!=e; ++b)
                    _veicoli.add(*b);
            }catch(...){
                _veicoli.clear();
                throw;
            }
        }
        /**
         * @brief Operatore assegnamento
         * 
         * @param other oggetto da cui copiare 
         * @return oggetto this
         */
        Concessionaria& operator=(const Concessionaria &other){
            if(this != &other){
                Concessionaria tmp(other);
                std::swap(_veicoli, tmp._veicoli);
            }
            return *this;
        }
        /**
         * @brief Distruttore
         * 
         */
        ~Concessionaria(){
            #ifndef NDEBUG
                std::cout<<"~Concessionaria()"<<std::endl;
            #endif
        }
        /**
         * @brief Aggiunge un'auto solo se non esiste nella concessionaria
         * 
         * @param a 
         */
        void add(const Auto &a){
            _veicoli.add(a);
        }
        /**
         * @brief Rimuove un'auto solo se esiste nella concessionaria
         * 
         * @param a 
         */
        void remove(const Auto &a){
            _veicoli.remove(a);
        }
        /**
         * @brief Verifica che un'auto sia presente nella concessionaria
         * 
         * @param a auto da cercare
         * @return true se l'auto è presente
         * @return false altrimenti
         */
        bool contains(const Auto &a) const{
            return _veicoli.contains(a);
        }
        /**
         * @brief Numero delle auto
         * 
         * @return unsigned int numero delle auto
         */
        unsigned int veicoli() const{
            return _veicoli.size();
        }
        /**
         * @brief Operatore[]
         * 
         * @param index indice della posizione dell'auto
         * @return const Auto& auto 
         */
        const Auto& operator[](int index) const{
            return _veicoli[index];
        }
        /**
         * @brief Getter di tutte le auto presenti nella concessionaria
         * 
         * @return const Set<Auto, equals_auto>& set contenente tuttle le auto
         */
        const Set<Auto, equals_auto>& get_veicoli() const{
            return _veicoli;
        }
        /**
         * @brief Opeatore di stream
         * 
         * @param os oggetto di stream
         * @param c oggetto da spedire sullo stream
         * @return std::ostream& reference os
         */
        friend std::ostream& operator<<(std::ostream &os, const Concessionaria &c){
            Set<Auto, equals_auto>::const_iterator b,e;
            for(b=c._veicoli.begin(), e=c._veicoli.end(); b!=e; ++b)
                os<<*b<<" ";
            return os;
        }
        /**
         * @brief Aggiunge alla lista di auto presenti nuove auto,
         * senza avere duplicati
         * 
         * @param veicoli lista di auto da aggiungere
         */
        void addAll(const Set<Auto, equals_auto> &veicoli){
            _veicoli=_veicoli+veicoli; //se viene lanciata l'eccezione _veicoli non viene alterato
        }
        /**
         * @brief Rimuove tutte la auto
         * 
         */
        void removeAll(){
            _veicoli.clear();
        }
        
};
/**
 * @brief Funtore predicato di uguaglianza tra due point
 * 
 */
struct equals_point{
    bool operator()(const point &p1, const point &p2) const{
        return p1==p2;
    }
};
/**
 * @brief Funtore predicato di uguaglianza tra due interi
 * 
 */
struct equals_int{
    bool operator()(int a, int b) const{
        return a==b;
    }
};
/**
 * @brief Funtore predicato di uguaglianza tra due stringhe
 * 
 */
struct equals_string{
    bool operator()(const std::string &a, const std::string &b) const{
        return a==b;;
    }
};
/**
 * @brief Funtore predicato(generico) di uguaglianza tra due set
 * 
 */
struct equals_set{
    template<typename T, typename Eql>
    bool operator()(const Set<T, Eql> &s1, const Set<T, Eql> &s2) const{
        return s1==s2;
    }
};
/**
 * @brief Funtore predicato, valuta se un intero è pari o dispari
 * 
 */
bool is_even(int x){
    return x%2==0;
}
/**
 * @brief Funtore predicato, valuta se una stringa ha una lunghezza pari a 4
 * 
 */
bool lenght_equal_4(const std::string &s){
    return s.size()==4;
}
/**
 * @brief Funtore predicato, valuta se un punto si trova nel quarto quadrante
 * 
 */
bool is_located_in_quadrant_4(const point &p){
    return p.x<0 && p.y<0;
}
/**
 * @brief Funtore predicato, valuta se una lista di punti contiene meno di 5 valori
 * 
 */
bool set_size_less_than_5(const Set<point, equals_point> &s){
    return s.size()<5;
}


/**
 * @brief Test set int
 * 
 */
void test_set_int(){
    Set<int, equals_int> a,b,c,empty;
    Set<int, equals_int> pari, dispari;
    for(unsigned int i=0; i <20; ++i)
        if(i%2==0) 
            pari.add(i);
        else
            dispari.add(i);
    Set<int, equals_int> copy(a);
    Set<int, equals_int> result;
    //unione di due set vuoti
    result=a+b;
    assert(result.isEmpty());
    assert(pari.contains(18));
    assert(!dispari.contains(0));
    assert(copy.size()==0);
    assert(result.size()==0 && a.size()==0 && b.size()==0);
    assert(a==b);
    assert(!result.contains(1));
    
    result.remove(1);
    try{
        result[1];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what()<<std::endl;
    }
    for(unsigned int i=0; i < 10;++i, a.add(i), b.add(i-5));
    Set<int, equals_int> sottoinsiemeA;
    for(unsigned int i=0; i < 5; ++i, sottoinsiemeA.add(i));
    std::cout<<"Insieme A={ ";
    std::cout<<a<<"}"<<std::endl;
    std::cout<<"Insieme B={ ";
    std::cout<<b<<"}"<<std::endl;

    //Test proprietà unione
    assert(a+b == b+a);
    assert(a+a==a);
    assert(a+empty==a);
    assert((a+b)+c == a+(b+c));
    assert(a+sottoinsiemeA==a);
    //Test proprietà intersezione
    assert(pari-dispari==empty);
    assert(a-b==b-a);
    assert(a-a==a);
    assert(a-empty==empty);
    assert(a-b-pari==pari-a-b);
    assert(a-sottoinsiemeA==sottoinsiemeA);
    //Test casuali
    result=a+b;
    std::cout<<"Result size: "<<result.size()<<std::endl;
    std::cout<<"Result set={ "<<result<<"}"<<std::endl;
    result=a+a;
    result=result-a;
    Set<int, equals_int> d(result);
    assert(d==result);
}

/**
 * @brief Test set std::string
 * 
 */
void test_set_string(){
    std::string veicoli[7]={"audi", "bmw", "citroen", "bugatti", "ferrari", "mclauren", "fiat"};
    Set<std::string, equals_string> a,b,c,empty;
    Set<std::string, equals_string> copy(a);
    Set<std::string, equals_string> result;
    Set<std::string, equals_string> pari, dispari;
    for(unsigned int i=0; i <7; ++i)
        if(i%2==0) 
            pari.add(veicoli[i]);
        else
            dispari.add(veicoli[i]);
    //unione di due set vuoti
   result=a+b;
    assert(result.isEmpty());
    
    assert(copy.size()==0);
    assert(result.size()==0 && a.size()==0 && b.size()==0);
    assert(a==b);
    assert(!result.contains("stringa che bon esiste"));
    result.remove("");
    try{
        result[1];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what()<<std::endl;
    }
    for(unsigned int i=0; i < 6; ++i, a.add(veicoli[i]), b.add(veicoli[i]));
    
    b.remove("audi");
    b.remove("fiat");
    Set<std::string, equals_string> sottoinsiemeA;
    for(unsigned int i=0; i < 3; ++i, sottoinsiemeA.add(veicoli[i]));
    std::cout<<"Insieme A={ ";
    std::cout<<a<<"}"<<std::endl;
    std::cout<<"Insieme B={ ";
    std::cout<<b<<"}"<<std::endl;

    //Test proprietà unione
    assert(a+b == b+a);
    assert(a+a==a);
    assert(a+empty==a);
    assert((a+b)+c == a+(b+c));
    assert(a+sottoinsiemeA==a);
    //Test proprietà intersezione
    assert(pari-dispari==empty);
    assert(a-b==b-a);
    assert(a-a==a);
    assert(a-empty==empty);
    assert(a-b-pari==pari-a-b);
    assert(a-sottoinsiemeA==sottoinsiemeA);
    //Test casuali
    result=a+b;
    std::cout<<"Result size: "<<result.size()<<std::endl;
    std::cout<<result<<std::endl;
    result=a+a;
    result=result-a;
    std::cout<<result<<std::endl;
    Set<std::string, equals_string> d(result);
    assert(d==result);
}

/**
 * @brief Test set point
 * 
 */
void test_set_point(){
    Set<point, equals_point> a,b,c,empty;
    Set<point, equals_point> copy(a);
    Set<point, equals_point> result;
    Set<point, equals_point> pari, dispari;
    for(unsigned int i=0; i <20; ++i)
        if(i%2==0) 
            pari.add(point(i+2,i));
        else
            dispari.add(point(i,i+1));
    //unione di due set vuoti
    result=a+b;
    assert(result.isEmpty());
    assert(copy.size()==0);
    assert(result.size()==0 && a.size()==0 && b.size()==0);
    assert(a==b);
    assert(!result.contains(point(0,0)));
    result.remove(point(0,0));
    try{
        result[1];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what()<<std::endl;
    }
    for(unsigned int i=0; i < 10; ++i){
        a.add(point(i,i+2));
        b.add(point(i,i+2));
    }
    Set<point, equals_point> sottoinsiemeA;
    for(unsigned int i=0; i < 5; ++i, sottoinsiemeA.add(point(i,i+2)));
    std::cout<<"Insieme A={ ";
    std::cout<<a<<"}"<<std::endl;
    std::cout<<"Insieme B={ ";
    std::cout<<b<<"}"<<std::endl;


    //Test proprietà unione
    assert(a+b == b+a);
    assert(a+a==a);
    assert(a+empty==a);
    assert((a+b)+c == a+(b+c));
    assert(a+sottoinsiemeA==a);
    //Test proprietà intersezione
    assert(pari-dispari==empty);
    assert(a-b==b-a);
    assert(a-a==a);
    assert(a-empty==empty);
    assert(a-b-pari==pari-a-b);
    assert(a-sottoinsiemeA==sottoinsiemeA);
    //Test casuali
    result=a+b;
    std::cout<<"Result size: "<<result.size()<<std::endl;
    std::cout<<result<<std::endl;
    result=a+a;
    result=result-a;
    Set<point, equals_point> d(result);
    assert(d==result);
}


/**
 * @brief Test set filter_out sui tipi: int, std::string, Set<point, equals_point>
 * 
 */
void test_filter_out_int_string_custom(){
    std::string dati[8]={"rosso", "verde","blue", "nero", "bianco", "rosa", "giallo", "marronone"};
    
    
    point set_of_points[9]={point(-1,-5),point(0,0),point(1,-4),point(-4,-3),point(10,3),point(4,-1),point(-2,1),point(-9,-7),point(2,1)};
    Set<std::string, equals_string> setString(dati, dati+8);
    Set<int, equals_int> setInt;
    Set<point, equals_point> setPoint(set_of_points, set_of_points+9);
    Set<Set<point, equals_point>, equals_set> matrix; //set di set
    //test int 
    for(unsigned int i=0; i<100; setInt.add(i), ++i);
    Set<int, equals_int> risInt=filter_out(setInt, is_even);
    assert(risInt.size()==50);
    std::cout<<"Insieme pari: "<<risInt;
    //test string
    Set<std::string, equals_string> risString(filter_out(setString, lenght_equal_4));
    assert(risString.size()==3);
    std::cout<<"Insieme stringhe lunghezza 4: "<<risString<<std::endl;
    //test point
    Set<point, equals_point>risPoint=filter_out(setPoint, is_located_in_quadrant_4);
    assert(risPoint.size()==3);
    std::cout<<"Insieme dei punti nel 4 quadrante: "<<risPoint<<std::endl;
    //test set of set of point
    
    matrix.add(risPoint);  
    matrix.add(setPoint);
    risPoint.remove(point(-1, -5));
    matrix.add(risPoint);
      
    std::cout<<matrix<<std::endl;
    Set<Set<point, equals_point>, equals_set> risMatrix(filter_out(matrix, set_size_less_than_5));
    assert(risMatrix.size()==2);
}
/**
 * @brief Test const set

 */
int test_const_set(const Set<point, equals_point> &s){
    Set<point, equals_point> copy(s);
    typename Set<point, equals_point>::const_iterator b,e;
    std::cout<<"Insieme costante={ ";
    for(b=s.begin(), e=s.end(); b!=e; ++b)
        std::cout<<*b<<" ";
    std::cout<<"}"<<"\n";
    std::cout<<"Size: "<<s.size()<<std::endl;
    assert(!s.isEmpty());
    assert(s.contains(point(0,0)));
    assert(s[0]==point(-1,-5));
    assert(copy==s);
    return 0;
}
/**
 * @brief Test set funzione clear
 */
template<typename T, typename Eql>
int test_clear(Set<T, Eql> &s){
    s.clear();
    assert(s.size()==0);
    assert(s.isEmpty());
    return 0;
}

/**
 * @brief Test operatore ==
 * 
 */
int test_operator_uguale_uguale(){
    point set_of_points[9]={point(-1,-5),point(0,0),point(1,-4),point(-4,-3),point(10,3),point(4,-1),point(-2,1),point(-9,-7),point(2,1)};
    Set<point, equals_point> s(set_of_points, set_of_points+9);
    Set<point, equals_point> ss(set_of_points, set_of_points+9);
    assert(s==ss);
    s.clear();
    assert(!(s==ss));
    ss.clear();
    assert(s==ss);

    return 0;
}
/**
 * @brief Test operatore[]
 * 
 */
int test_operator_parentesi_quadre(){
    point set_of_points[9]={point(-1,-5),point(0,0),point(1,-4),point(-4,-3),point(10,3),point(4,-1),point(-2,1),point(-9,-7),point(2,1)};
    Set<point, equals_point> s(set_of_points, set_of_points+9);
    Set<point, equals_point> ss(set_of_points, set_of_points+9);
    Set<point, equals_point> single(set_of_points, set_of_points+1);

    assert(s[0]==point(-1,-5));
    assert(s[7]==ss[7]);

    try{
        s[-1];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        ss[9];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what()<<std::endl;
    }
    assert(single[0]==point(-1,-5));
    try{
        single[1];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what()<<std::endl;
    }

    return 0;
}
/**
 * @brief Test dei 4 metodi fondamentali
 * 
 */
int test_funzioni_fontamentali(){
    point set_of_points[3]={point(-1,-5),point(0,0),point(1,-4)};
    Set<point, equals_point> s(set_of_points, set_of_points+3);
    Set<point, equals_point> ss=s;
    assert(s==ss);
    assert(s.size()==3);
    assert(ss.size()==3);
    s.clear();
    ss=s;
    assert(s.size()==0);
    assert(ss.isEmpty());
    return 0;
}
/**
 * @brief Test set costruttore a partire da due iteratori 
 *  
 */
int test_costruttore_con_iteratori(){
    std::cout<<"Set costruiti a partire da iteratori:"<<std::endl;
    float vettore[5]={1.1, 3.4, 4.9, -0.001, 0.000001};
    Set<int, equals_int>s(vettore, vettore+5);
    std::cout<<"A: { "<<s<<"}"<<std::endl;

    int v[5]={1,2,4,5,5};
    Set<double, equals_int>ss(v, v+5);
    std::cout<<"B: { "<<s<<"}"<<std::endl;

    bool vv[5]={1,1,0,1,0};
    Set<double, equals_int>sss(vv, vv+5);
    std::cout<<"C: { "<<s<<"}"<<std::endl;

    return 0;
}
/**
 * @brief Test classe const_iterator
 * 
 */
int test_const_iterator(){
    int vettore[5]={1, 5, 9, 3, 0};
    Set<int, equals_int>s(vettore, vettore+5);
    Set<int, equals_int>::const_iterator iterator_1,a,b;
    assert(a==b);
    iterator_1=s.begin();
    Set<int, equals_int>::const_iterator iterator_2(iterator_1);
    assert(iterator_1==iterator_2);
    assert((*iterator_1) == (*iterator_2));
    iterator_1++;
    iterator_2++;
    assert(iterator_1==iterator_2);
    assert((*iterator_1) == (*iterator_2));
    ++iterator_1;
    iterator_2++;
    assert(iterator_1==iterator_2);
    assert((*iterator_1) == (*iterator_2));

    assert(*iterator_1 == 9 && *iterator_2==9);
    iterator_1++;
    assert(iterator_1!=iterator_2);
    assert((*iterator_1) != (*iterator_2));
    const int *p=&(*iterator_1);
    assert(*p==3);
    ((++iterator_1)++)++;
    Set<int, equals_int>::const_iterator iterator_3; 
    assert(iterator_1 == iterator_3);
    
    point set_of_points[9]={point(3,3),point(55,89),point(7,9),point(-4,-69),point(6,0),point(-3,1),point(-2,1),point(-9,-7),point(100,100)};
    Set<point, equals_point> my_set(set_of_points, set_of_points+9);
    Set<point, equals_point>::const_iterator iterator;
    Set<point, equals_point>::const_iterator iterator2;
    assert(iterator==iterator2);
    iterator=my_set.begin();
    Set<point, equals_point>::const_iterator copy(iterator);
    assert(copy==iterator);
    copy++;
    assert(*copy == point(55,89));
    ++(++copy);
    assert(*copy == point(-4,-69));
    assert(copy!=iterator2);

    iterator=my_set.begin();
    assert((iterator->x)==3);
    assert((iterator->y)==3);
    iterator++;
    ++iterator;
    assert((iterator->x)==7);
    assert((iterator->y)==9);
    assert(((int)iterator->distance_from(*(++iterator)))==78); 
    return 0;
}

/**
 * @brief Test classe concessionaria
 */
int test_classe_complessa_concessionaria(){
    Set<Concessionaria::Auto, Concessionaria::equals_auto> nuoveAuto;

    Concessionaria c;
    Concessionaria::Auto a("targa123", "audi");
    Concessionaria::Auto b("targa222", "bmw");
    Concessionaria::Auto f("targa003", "fiat");
    Concessionaria::Auto d("targa744", "tesla");
    Concessionaria::Auto e("targa667", "mercedes");
    assert(c.veicoli()==0);
    assert(!c.contains(a));
    Concessionaria copia=c;
    Concessionaria copia2(c);
    assert(copia.get_veicoli()==c.get_veicoli()); //usa operator== di set
    assert(copia.get_veicoli()==copia2.get_veicoli());
    c.add(a);
    c.add(a);
    c.add(b);
    c.add(f);
    c.add(d);
    c.add(e);
    nuoveAuto=nuoveAuto+c.get_veicoli();
    assert(c.veicoli()==5);
    assert(c.contains(b));
    c.remove(a);
    assert(c.veicoli()==4);
    std::cout<<c<<std::endl;
    assert(c[0]==b);
    assert(c[3]==e);
    try{
        c[4];
    }catch(set_index_out_of_bound &e){
        std::cout<<e.what() <<std::endl;
    }
    copia=copia2=c;
    assert(copia.get_veicoli()==c.get_veicoli());
    assert(copia2.get_veicoli()==c.get_veicoli());
    assert((copia.get_veicoli()+c.get_veicoli()).size()==4);
    assert((copia.get_veicoli()-c.get_veicoli()).size()==4);

    nuoveAuto.add(Concessionaria::Auto("targa043", "bentley"));
    nuoveAuto.add(Concessionaria::Auto("targa323", "mitsubishi"));
    nuoveAuto.add(Concessionaria::Auto("targa787", "bentley"));
    nuoveAuto.add(Concessionaria::Auto("targa220", "cadillac"));
    assert(nuoveAuto.size()==9);
    c.addAll(nuoveAuto); //contiene tutte le auto 
    std::cout<<c<<std::endl;
    assert(c.veicoli()==9); //c non contiene l'auto "a" quindi viene aggiunta
    c.removeAll();
    assert(c.veicoli()==0);
    for(int i=0 ;i<1000;i++)
        c.add(Concessionaria::Auto(std::to_string(i), "cadillac"));
    assert(c.veicoli()==1000);
    c.addAll(Set<Concessionaria::Auto, Concessionaria::equals_auto>());
    assert(c.veicoli()==1000);
    return 0;
}


int main(){
    point set_of_points[9]={point(-1,-5),point(0,0),point(1,-4),point(-4,-3),point(10,3),point(4,-1),point(-2,1),point(-9,-7),point(2,1)};
    Set<point, equals_point> setPoint(set_of_points, set_of_points+9);

    test_const_set(setPoint);

    test_clear(setPoint);

    test_operator_uguale_uguale();

    test_set_int();

    test_set_string();

    test_set_point();

    test_filter_out_int_string_custom();

    test_operator_parentesi_quadre();

    test_funzioni_fontamentali();

    test_costruttore_con_iteratori();

    test_const_iterator();

    test_classe_complessa_concessionaria();


    return 0;
}

