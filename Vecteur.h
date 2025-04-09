#pragma once
#include  <iostream>
#include <cassert>

template<class T>
class Vecteur{
private:
	T* m_tab;
	int m_dim;
	

public:

	Vecteur(int Dimension = 3) {
		//on verifie si la dimension est strictement superieur a zero
		if (Dimension < 0) {
			std::cout << "la dimension d'un vecteur doit etre superieur a zero" << std::endl;
		}
		assert(Dimension > 0);

		m_dim = Dimension;

		//ensuite on alloue un tableau dynamique
		m_tab = new T[m_dim];

		//ensuite on remplie le tableau avec la valeur par defaut
		/*for (int i = 0; i < m_dim; i++) {
			m_tab[i] = value;
		}*/
		//message de fin de construction
		std::cout << "initialisation d'un vecteur a, " << m_dim << " dimensions" << std::endl;
	}

	template <typename U>
	Vecteur(const Vecteur<U>& other) {
		m_dim = other.dimensions();  // On copie la dimension
		m_tab = new T[m_dim];         // On alloue un tableau de type T

		// Conversion de chaque élément de U à T
		for (int i = 0; i < m_dim; i++) {
			m_tab[i] = other.get(i); // Conversion explicite
		}
	}

	~Vecteur() {
		delete[] m_tab;
		m_tab = nullptr;
	}

	//GETTRES

	const T& get(const int position) const {
		//on verifie que la position demander est bien valide
		assert(position < m_dim);
		return m_tab[position];
	}

	void set(const int position, T& value) {
		//on verifie que la position que 'on sohaite modifie est bien valide
		assert(position < m_dim);

		m_tab[position] = value;
	}

	const int dimensions(void)const {
		return m_dim;
	}

	Vecteur<T> operator+(const Vecteur<T>& other) const {
		assert(this->m_dim == other.m_dim);

		Vecteur<T> result(this->m_dim);
		for (int i = 0; i < this->m_dim; i++) {
			result[i] = this->get(i) + other.get(i);
		}
		return result;
	}



	//Et je me suis rendu compte qu'il fallait que cette operateur soit ami de la classe 
	//pour poupoir acceder a sa dimension et la modifie ainsi que son tableau et liberer la mémoire
	friend inline std::istream& operator>>(std::istream& in, Vecteur<T>& vect) {
		//on libere d'abord le tableau de vect
		delete[] vect.m_tab;

		T value;
		int dim;
		std::cout << "i am here" << std::endl;

		//Messsage pour demander la dim du vecteur
		std::cout << "Entrez la dimension de votre vecteur" << std::endl;
		in >> dim;

		//on change la dim du vecteur
		vect.m_dim = dim;
		vect.m_tab = new T[dim];

		//Boucle pour personnalizer le vecteur
		for (int i = 0; i < dim; i++) {
			//on demande a l'utilisateur de rentre la valeur de la i +1 ieme dimension
			std::cout << "Quel valeur pour la coordonnée " << i + 1 << std::endl;
			in >> value;
			vect.set(i, value);
		}
		return in;
	}

	//Redefinition de l'operateur [] pour acceder au element et pourvoir les modifier
	T&  operator[](const int position) {
		//On verifie d'abord si la postion qu'on souhaite est valide
		assert(this->m_dim > position);
		return *(this->m_tab + position);
	}

	Vecteur<T>& operator=(const Vecteur<T>& other) {
		//On verifie d'abord que les deux vecteurs ont les memes dimensions*
		assert(this->m_dim == other.m_dim);

		//en suit on copie les elements un a un
		for (int i = 0; i < this->m_dim; i++) {
			this->m_tab[i] = other.get(i);
		}

		return *this;
	}

};

template<class T>
//operateur d'affichage de vecteur
std::ostream& operator<<(std::ostream& out, const Vecteur<T>& vect) {
	afficherVecteur(&vect, out);
	return out;
}

template<class T>
Vecteur<T> add(const Vecteur<T>* v1, const Vecteur<T>* v2) {
	//on verifie d'abord que les deux vecteurs v1 et v2 ont la meme dimension
	int dim1, dim2;
	dim1 = v1->dimensions();
	dim2 = v2->dimensions();
	assert(dim1 == dim2);

	//on instancie un vecteur de dimension dim1 = dim2
	Vecteur<T> my_vect(dim1);

	//ensuite on peut faire la somme des deux vecteurs
	for (int i = 0; i < dim1; i++) {
		my_vect.set(i, v1->get(i) + v2->get(i));
	}
	//on retourne le resulta;t
	return my_vect;
}

template<class T>
void afficherVecteur(const Vecteur<T>* v, std::ostream& out) {
	const int dim = v->dimensions();
	out << "Vecteur a " << dim << " dimensions: (";
	for (int i = 0; i < dim; i++) {
		if (i + 1 == dim) {
			out << v->get(i) << ")";
			break;
		}
		out << v->get(i) << ", ";
	}
	out << std::endl;
}

template <typename T,typename U>
T operator*(const Vecteur<T>& v1, const Vecteur<U>& v2) {
	//etant donné que le produit scalaire n'est valide que pour les types artihmetique
	//je rechercher sur internet comment verifie qu'on a bien affaire a un type arithmetique
	//static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, "Le produit scalaire est uniquement défini pour les types numériques !");

	assert(v1.dimensions() == v2.dimensions());

	T produit = 0;
	for (int i = 0; i < v1.dimensions(); i++) {
		produit += v1.get(i) * v2.get(i);
	}
	return produit;
}