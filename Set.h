#ifndef SET_H
#define SET_H
#include <algorithm>
#include <iostream>
#include <ostream>
#include <cassert>
#include <iterator> // std::forward_iterator_tag
#include <cstddef> // std::ptrdiff_t
#include "set_index_out_of_bound.h"
/**
 * @brief Classe Set
 * 
 * La classe implementa un generico set in cui ogni elemento compare
 * una e una sola volta
 * 
 * @tparam T 
 */
template<typename T, typename Eql> class Set{
    /**
     * @brief Struttura nodo
     */
    struct nodo{
        T value;///< valore memorizzato
        nodo *next;///< puntatore al nodo successivo della lista
        /**
         * Costuttore di default
         * @post next == nullptr
         */
        nodo() : next(nullptr) {}
        /**
         * @brief Costruttore secondario
         * 
         * @param val valore da memorizzare
         * @param n puntatore al nodo successivo
         * 
         * @post value == val
         * @post next == n
         */
        nodo(const T &val, nodo *n) : value(val), next(n) {}

        /**
         * @brief Costruttore secondario
         * 
         * @param val valore da memorizzare
         * 
         * @post value == val
         * @post next == nullptr
         */
        explicit nodo(const T &val) : value(val), next(nullptr) {}

        /**
         * Copy constructor
         * @brief Costruisce un nodo a partire da un altro nodo copiando i dati membro a membro
         * 
         * @param other oggetto nodo da copiare
         */
        nodo(const nodo &other){
            if (this != &other){
                value = other.value;
                next = other.next;
            }
        }
        /**
         * Operatore assegnamento
         * @brief Assegna ad un oggetto nodo un altro nodo copiando i dati membro a membro
         * 
         * @param other nodo da copiare
         * @return reference del nodo this
         */
        nodo& operator=(const nodo &other){
            value = other.value;
            next = other.next;
            return *this;
        }
        /**
         * Distruttore
         */
        ~nodo() {}

        /**
         * Funzione che implementa l'operatore di stream
         * 
         * @param os stream di output
         * @param n nodo da spedire sullo stream
         * @return reference dello stream di output
         */
        friend std::ostream& operator<<(std::ostream &os, const nodo &n){
            return os<<n.value;
        }
    };

    nodo *_head;///< puntatore al primo nodo della lista
    unsigned int _size;///< numero di elementi salvati
    Eql _equals;///< funtore di uguaglianza tra due valori di tipo T

public:
    /**
     * @brief Costruttore di default
     * 
     * @post _head == nullptr
     * @post _size == 0
     * 
     */
    Set() : _head(nullptr), _size(0) {}

    /**
     * @brief Copy construtor
     *  
     * @param other set da copiare
     * @post _head == other._head
     * @post _size == other._size
     * 
     * @throw set_index_out_of_bound eccezzione indici fuori range
     * @throw std::bad_alloc eccezione durante l'allocazione di un nodo
     */
    Set(const Set &other) : _head(nullptr), _size(0){
        nodo *current = other._head;
        try{
            while (current != nullptr){
                add(current->value);
                current = current->next;
            }
        }catch (...){
            clear();
            throw;
        }
    }
    /**
     * @brief Operatore assegnamento
     * 
     * @param other set da copiare
     * @return reference al set this
     * 
     * @post head == other._head
     * @post _size == other._size
     */

    Set& operator=(const Set &other){
        if (this != &other){
            Set tmp(other);
            std::swap(_head, tmp._head);
            std::swap(_size, tmp._size);
        }
        return *this;
    }
    /**
     * @brief Distruttore
     * @post _head == nullptr
     * @post _size == 0
     * 
     */
    ~Set(){
        clear();
    }

    /**
     * @brief Costruttore secondario, costruisce un set a partire da due iteratori sul tipo Q
     * 
     * @tparam Q tipo dell'iteratore
     * @param b iteratore di inizio
     * @param e iteratore di fine
     * 
     */
    template<typename Q> Set(Q b, Q e) : _head(nullptr), _size(0){
        try{
            for(; b!=e; ++b)
                add(static_cast<T>(*b));
        }catch(...){
            clear();
            throw;
        }
    }
    /**
     * @brief Aggiunge un nuovo valore alla lista solo se quest'ultimo non
     * è presente
     * In caso fosse presente, non viene memorizzato
     * @param value valore da memorizzare
     * 
     * @throw std::bad_alloc possibile eccezione di allocazione
     */
    void add(const T &value){
        if (!contains(value)){
            nodo *current = _head;
            nodo *aus = new nodo(value);
            if (current == nullptr){ //set vuoto
                _head = aus;
                _size++;
                return;
            }else{
                nodo *previous = _head;
                while(current!=nullptr){//set pieno
                    previous=current;
                    current=current->next;
                }
                previous->next=aus;
                _size++;
            }
        }
    }
    /**
     * Rimuove il valore passato come parametro dalla lista solo
     * se è presente
     * 
     * @param value valore da rimuovere
     */
    void remove(const T& value){
        if(contains(value)){
            nodo *current=_head;
            nodo *previous=_head;

            if(_equals(current->value, value)){ //rimozione in testa
                _head=current->next;
                delete current;
                _size--;
                return;
            }

            while(current!=nullptr){ //rimozione in coda e al centro della lista
                if(_equals(value, current->value)){
                    previous->next=current->next;
                    delete current;
                    _size--;
                    return;
                }
                previous=current;
                current=current->next;
            }
        }
    }
    /**
     * @brief Svuota la lista
     * @post _head == nullptr
     * @post _size == 0
     */
    void clear(){
        nodo *current = _head;
        while (current != nullptr){
            nodo *next_node = current->next;
            delete current;
            current = next_node;
        }
        _head = nullptr;
        _size = 0;
    }
    /** Ritorna il numero degli elementi salvati
     * 
     * @return copia del valore degli elementi salvati
     */
    unsigned int size() const{
        return _size;
    }
    /**
     * @brief Verifica che la lista sia vuota
     * 
     * @return true se la lista è vuota
     * @return false se la lista non è vuota
     */
    bool isEmpty() const{
        return _size == 0;
    }
    /**
     * @brief Verifica se il valore passato come parametro è contenuto nella lista
     * 
     * @param value valore da cercare
     * @return true se il valore è presente
     * @return false se il valore non è presente
     */
    bool contains(const T &value) const{
        nodo *current = _head;
        while (current != nullptr){
            if (_equals(current->value, value))
                return true;
            current = current->next;
        }
        return false;
    }
    /**
     * @brief Ritorna l'i-esimo valore della lista
     * 
     * @param index indice del valore nella lista
     * @return const T& reference del valore ritornato
     * 
     * @throw set_index_out_of_bound eccezione indice fuori range
     */
    const T& operator[](int index) const{ 
        if (index < 0 || index >= _size)
            throw set_index_out_of_bound("Cannot read the value with an index out of bound");
        
        int i = 0;
        nodo *current = _head;
        bool found=false;
        nodo *previous=_head;
        while (current != nullptr && !found) {
            if (index == i)
                found=true;
            
            i++;
            previous=current;
            current = current->next;
        }
        return previous->value;
         
    }
    /**
     * @brief Operatore == che verifica che due set sono uguali, cioè contengono gli stessi elementi
     * 
     * 
     * @param other set con cui fare il confronto 
     * @return true se il set this contiene gli stessi dati di other, o se entrambi sono vuoti
     * @return false se il set this non contiene gli stessi dati di other, o uno dei due è vuoto o se le dimensione 
     * dei due sono diverse
     */
    bool operator==(const Set &other) const{
        if(_size != other._size)
            return false;
        
        nodo *current = other._head;    

        if(isEmpty() && other.isEmpty())
            return true;

        bool equals=false;
        while(current!=nullptr){
            equals=contains(current->value);
            if(!equals)
                return false;
            current=current->next;
        }
        return equals;
    }
    /**
     * @brief Operatore di stream
     * @param os stream di output
     * @param s set da spedire sullo stream
     * @return reference dello stream di output
     */
    friend std::ostream& operator<<(std::ostream &os, const Set &s){
        nodo *current = s._head;
        while(current!=nullptr){
            os<<*current<<" ";
            current=current->next;
        }
        return os;
    }

     /**
     * Classe const_iterator
     * Gli iteratori iterano sui dati contenuti nel set
     * @brief Classe const_iterator
     */
	class const_iterator {
		
        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef T                         value_type;
            typedef ptrdiff_t                 difference_type;
            typedef const T*                  pointer;
            typedef const T&                  reference;

            /**
             * @brief Costruttore di default
             * 
             */
            const_iterator() : ptr(nullptr) {}
            /**
             * @brief Copy constructor
             * 
             * @param other iteratore da cui copiare i dati
             */
            const_iterator(const const_iterator &other) : ptr(other.ptr){}
            /**
             * @brief Operatore assegnamento
             * 
             * @param other iteratore da cui copiare i dati
             * @return reference all'iteratore this 
             */
            const_iterator& operator=(const const_iterator &other) {
                ptr=other.ptr;
                return *this;
            }
            /**
             * @brief Distruttore
             * 
             */
            ~const_iterator() {}

           /**
            * @brief Opeatore*
            * 
            * @return reference al dato riferito dall'iteratore (dereferenziamento) 
            */
            reference operator*() const {
                return ptr->value;
            }

            /**
             * @brief Operatore-> 
             * 
             * @return puntatore al dato riferito dall'iteratore 
             */
            pointer operator->() const {
                return &(ptr->value);
            }
            
           /**
            * @brief Operatore++ di post-incremento
            * @return copia dell'iteratore che punta al valore precedente
            */
            const_iterator operator++(int) {
                const_iterator tmp(*this);
                ptr=ptr->next;
                return tmp;
            }

            /**
            * @brief Operatore++ pre-incremento
            * @return reference all'teratore this
            */
            const_iterator& operator++() {
                ptr=ptr->next;
                return *this;
            }

            /**
             * @brief Operatore==
             * 
             * @param other iteratore con cui fare il confronto
             * @return true se l'iteratore this e other puntano allo stesso dato
             * @return false se l'iteratore this e other non puntano allo stesso dato
             */
            bool operator==(const const_iterator &other) const {
                return ptr==other.ptr;
            }
            
            /**
             * @brief Operatore!=
             * 
             * @param other iteratore con cui fare il confronto
             * @return true se l'iteratore this e other non puntano allo stesso dato
             * @return false se l'iteratore this e other puntano allo stesso dato
             */
            bool operator!=(const const_iterator &other) const {
                return !(*this == other); 
            }

        private:
            friend class Set;///< friend della classe const_iterator
            const nodo *ptr;///< nodo di partenza dell'iterator

            /**
             * @brief Costruttore privato
             * 
             * @param p nodo con cui inizializzare il dato membro
             */
            const_iterator(const nodo *p) : ptr(p){}
           
		
	};
	
	/**
	 * @brief Iteratore di inzio
	 * 
	 * @return const_iterator
	 */
	const_iterator begin() const {
		return const_iterator(_head);
	}
	/**
	 * @brief Iteratore fine
	 * 
	 * @return const_iterator
	 */
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	
};
/**
 * @brief Filtra dal set S i valori che soffisfano il predicato P
 * 
 * @tparam T tipo dell'oggetto set
 * @tparam Eql funtore di uguaglianza dell'oggetto set
 * @tparam P tipo del funtore
 * @param S oggetto set
 * @param pred funtore predicato
 * @return Set<T, Eql> nuovo set che contiene i valori di S che soddisfano il predicato P
 * @throw std::bad_alloc eccezzione nel caso di cattiva allocazione della memoria
 */
template<typename T, typename Eql, typename P> 
Set<T, Eql> filter_out(const Set<T, Eql> &S, P pred){
    Set<T, Eql> filtered_set;
    typename Set<T, Eql>::const_iterator b, e;
    try{
        for(b=S.begin(),e=S.end(); b!=e; ++b)
            if(pred(*b))
                filtered_set.add(*b);
    }catch(...){
        filtered_set.clear();
        throw;
    }
    
    return filtered_set;
}

/**
 * @brief Operator+
 * 
 * @tparam T tipo dell'oggetto set
 * @tparam Eql funtore di uguaglianza dell'oggetto set
 * @param A oggetto set di sinistra
 * @param B oggetto set di destra
 * @return Set<T, Eql> nuovo set che contiene i valori presenti in A o B
 * @throw std::bad_alloc eccezzione nel caso di cattiva allocazione della memoria
 */
template<typename T, typename Eql>
Set<T, Eql> operator+(const Set<T, Eql> &A, const Set<T, Eql> &B){
    Set<T, Eql> union_set(A);
    typename Set<T, Eql>::const_iterator b, e;
    try{
        for(b=B.begin(),e=B.end(); b!=e; ++b)
            union_set.add(*b);
    }catch(...){
        union_set.clear();
        throw;
    }

    return union_set;
}
/**
 * @brief Operator-
 * 
 * @tparam T tipo dell'oggetto set
 * @tparam Eql funtore di uguaglianza dell'oggetto set
 * @param A oggetto set di sinistra
 * @param B oggetto set di destra
 * @return Set<T, Eql> nuovo set che contiene i valori presenti in A e B
 * @throw std::bad_alloc eccezzione nel caso di cattiva allocazione della memoria
 */
template<typename T, typename Eql>
Set<T, Eql> operator-(const Set<T, Eql> &A, const Set<T, Eql> &B){
    Set<T, Eql> intersect_set;
    typename Set<T, Eql>::const_iterator b, e;
    try{
        for(b=A.begin(),e=A.end(); b!=e; ++b)
            if(B.contains(*b))
                intersect_set.add(*b);
    }catch(...){
        intersect_set.clear();
        throw;
    }
    return intersect_set;
}


#endif