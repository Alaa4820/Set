# Set<T>
> Progetto del corso 'Programmazione C++' del febbraio del 2021 (Università Milano-Bicocca)

Il progetto richiede la progettazione e realizzazione di una classe che implementa un Set di elementi generici T. Un Set è una collezione di dati che NON può contenere duplicati: es. S={1,6,4,9,7,10,12}.

A parte i metodi essenziali per il suo corretto uso, la classe deve implementare anche le seguenti funzionalità:
1. Accesso, in sola lettura, all'i-esimo elemento tramite operator[ ]
2. Deve esistere un metodo add per l’aggiunta di un elemento.
3. Deve esistere un metodo remove per la rimozione di un elemento.
4. Deve essere possibile creare un Set a partire da una sequenza di dati definita da una coppia generica di iteratori su tipi Q. Lasciate al compilatore la gestione della compatibilità tra i tipi attraverso l'uso del cast.
5. La classe deve essere dotata solo di const_iterator.
6. Deve essere possibile stampare il contenuto del set utilizzando operator<<
7. Implementare un metodo, tramite operator==, per confrontare due set e ritornare true se i due set contengono gli stessi dati.
Implementare una funzione globale e generica filter_out che, dato un Set generico S su tipi T e un predicato booleano generico P, ritorna un nuovo set di tipi T ottenuto prendendo da S tutti gli elementi che soddisfano il predicato P.
Implementare una funzione globale operator+ che, dati in input due Set generici su tipi T, ritorna un Set di tipi T che contiene gli elementi di entrambi i set (“concatenazione” di set).
Implementare una funzione globale operator- che, dati in input due Set generici su tipi T, ritorna un Set di tipi T che contiene gli elementi comuni a entrambi i set (“intersezione” di set).
