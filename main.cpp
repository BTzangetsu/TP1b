#include "Vecteur.h"

int main() {
	/*/deux Vecteur de float et affichage de la somme
	Vecteur<float> v1;
	std::cin >> v1;

	Vecteur<float> v2;
	std::cin >> v2;


	std::cout << v1 + v2 << std::endl;
	*/

	//deux vecteur de string et affichage de la somme
	Vecteur<float> v1;
	std::cin >> v1;

	Vecteur<int> v2;
	std::cin >> v2;

	//resultat dcimal
	std::cout << v1 * v2 << std::endl;

	//resultat entier
	std::cout << v2 * v1 << std::endl;

	//test du constructeur de copie generique
	//resultat entier
	std::cout << v2 + v1 << std::endl;
}