#ifndef SET_INDEX_OUT_OF_BOUND
#define SET_INDEX_OUT_OF_BOUND
#include <stdexcept>
/**
 * @brief Classe Eccezione
 * 
 * La classe implementa un'eccezione a run time in
 * caso di indice fuori dal range
 * 
 */
class set_index_out_of_bound : public std::runtime_error {
	
	public:
		/**
		 * @brief Costruttore 
		 * 
		 * @param message stringa contenente il messaggio
		 */
		set_index_out_of_bound(const std::string &message);

};

#endif