#pragma once
#include <iostream>
#include <cassert>

template<class T>
class Vecteur{
private:
    T* donnees; // Pointeur vers le tableau stockant les composantes.
    int dimension_vecteur; // Nombre de composantes du vecteur.

public:

    Vecteur(int Dimension = 3) {
        // Vérification que la dimension fournie est positive.
        if (Dimension < 0) {
            std::cout << "La dimension doit être strictement positive." << std::endl;
        }
        assert(Dimension > 0);

        dimension_vecteur = Dimension;

        // Allocation dynamique du tableau pour les composantes.
        donnees = new T[dimension_vecteur];

        // Indication de la dimension du vecteur créé.
        std::cout << "Vecteur de " << dimension_vecteur << " dimensions initialisé." << std::endl;
    }

    template <typename U>
    Vecteur(const Vecteur<U>& other) {
        dimension_vecteur = other.obtenir_dimension(); // Récupération de la dimension de l'autre vecteur.
        donnees = new T[dimension_vecteur]; // Allocation pour les nouvelles composantes.

        // Copie et conversion des composantes de l'autre vecteur.
        for (int i = 0; i < dimension_vecteur; i++) {
            donnees[i] = other.obtenir_element(i); // Lecture de l'élément et conversion.
        }
    }

    ~Vecteur() {
        delete[] donnees;
        donnees = nullptr; // Sécurité : éviter les pointeurs orphelins.
    }

    // ACCESSEURS

    const T& obtenir_element(const int position) const {
        // Vérification de la validité de l'indice demandé.
        assert(position < dimension_vecteur);
        return donnees[position];
    }

    void definir_element(const int position, T& valeur) {
        // Vérification de la validité de l'indice à modifier.
        assert(position < dimension_vecteur);

        donnees[position] = valeur;
    }

    const int obtenir_dimension() const {
        return dimension_vecteur;
    }

    Vecteur<T> operator+(const Vecteur<T>& other) const {
        assert(this->dimension_vecteur == other.dimension_vecteur);

        Vecteur<T> resultat(this->dimension_vecteur);
        for (int i = 0; i < this->dimension_vecteur; i++) {
            resultat[i] = this->obtenir_element(i) + other.obtenir_element(i);
        }
        return resultat;
    }

    // Nécessaire comme ami pour modifier les membres privés directement.
    friend inline std::istream& operator>>(std::istream& in, Vecteur<T>& vect) {
        // Libération de l'ancien tableau de composantes.
        delete[] vect.donnees;

        T valeur_entree;
        int dim_entree;
        std::cout << "Saisie des informations du vecteur." << std::endl;

        // Demande et lecture de la dimension du vecteur.
        std::cout << "Entrez la dimension du vecteur : " << std::endl;
        in >> dim_entree;

        // Mise à jour de la dimension et allocation du nouveau tableau.
        vect.dimension_vecteur = dim_entree;
        vect.donnees = new T[dim_entree];

        // Lecture des valeurs pour chaque composante.
        for (int i = 0; i < dim_entree; i++) {
            // Demande de la valeur pour la i-ème composante.
            std::cout << "Valeur pour la composante " << i + 1 << " : " << std::endl;
            in >> valeur_entree;
            vect.definir_element(i, valeur_entree);
        }
        return in;
    }

    // Surcharge de l'opérateur [] pour accéder et modifier les composantes.
    T& operator[](const int position) {
        // Vérification de la validité de la position.
        assert(this->dimension_vecteur > position);
        return *(this->donnees + position);
    }

    Vecteur<T>& operator=(const Vecteur<T>& other) {
        // Vérification que les dimensions sont compatibles pour l'assignation.
        assert(this->dimension_vecteur == other.dimension_vecteur);

        // Copie des composantes de l'autre vecteur.
        for (int i = 0; i < this->dimension_vecteur; i++) {
            this->donnees[i] = other.obtenir_element(i);
        }

        return *this;
    }

};

template<class T>
// Fonction d'affichage du vecteur.
std::ostream& operator<<(std::ostream& out, const Vecteur<T>& vect) {
    afficher_vecteur(&vect, out);
    return out;
}

template<class T>
// Fonction pour additionner deux vecteurs.
Vecteur<T> additionner_vecteurs(const Vecteur<T>* v1, const Vecteur<T>* v2) {
    // Vérification que les deux vecteurs ont la même dimension.
    int dim1, dim2;
    dim1 = v1->obtenir_dimension();
    dim2 = v2->obtenir_dimension();
    assert(dim1 == dim2);

    // Création du vecteur résultat.
    Vecteur<T> vecteur_resultat(dim1);

    // Calcul de la somme composante par composante.
    for (int i = 0; i < dim1; i++) {
        vecteur_resultat.definir_element(i, v1->obtenir_element(i) + v2->obtenir_element(i));
    }
    // Retourne le vecteur somme.
    return vecteur_resultat;
}

template<class T>
// Fonction utilitaire pour afficher un vecteur.
void afficher_vecteur(const Vecteur<T>* v, std::ostream& out) {
    const int dim = v->obtenir_dimension();
    out << "Vecteur de " << dim << " dimensions : (";
    for (int i = 0; i < dim; i++) {
        if (i + 1 == dim) {
            out << v->obtenir_element(i) << ")";
            break;
        }
        out << v->obtenir_element(i) << ", ";
    }
    out << std::endl;
}

template <typename T,typename U>
// Opérateur de produit scalaire entre deux vecteurs.
T operator*(const Vecteur<T>& v1, const Vecteur<U>& v2) {
    // Le produit scalaire est défini pour des vecteurs de même dimension.
    assert(v1.obtenir_dimension() == v2.obtenir_dimension());

    T produit_scalaire = 0;
    for (int i = 0; i < v1.obtenir_dimension(); i++) {
        produit_scalaire += v1.obtenir_element(i) * v2.obtenir_element(i);
    }
    return produit_scalaire;
}