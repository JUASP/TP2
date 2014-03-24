/**
 * \file DicoSynonymes.h
 * \brief Interface du type DicoSynonymes
 * \author ...
 * \version 0.1
 * \date ...
 *
 * Travail pratique num�ro 2
 *
 */

#include <stdexcept>
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <list>
#include <queue>

#ifndef _DICOSYNONYMES__H
#define _DICOSYNONYMES__H

namespace TP2
{

/**
* \class DicoSynonymes
*
* \brief classe repr�sentant un dictionnaire des synonymes
*
*/
class DicoSynonymes
{
public:

	/*
	*\brief		Constructeur 
	*
	*\post		Une instance vide de la classe a �t� initialis�e
	*
	*/
	DicoSynonymes();

	/*
	*\brief		Constructeur de dictionnaire � partir d'un fichier
	*
	*\pre		Il y a suffisament de m�moire
	*\pre		Le fichier est ouvert au pr�alable
	*
	*\post		Si le fichier est ouvert, l'instance de la classe a �t� initialis�e � partir
	*			du fichier de dictionnaire. Sinon, on g�n�re une classe vide.
	*
	*\exception	bad_alloc s'il n'y a pas assez de m�moire
	*
	*/
	DicoSynonymes(std::ifstream &fichier);


	/*
	*\brief		Destructeur.
	*
	*\post		Une instance de la classe est d�truite.
	*
	*/
	~DicoSynonymes();

	/*
	*\brief		Ajouter un radical au dictionnaire des synonymes tout en s�assurant de maintenir l'�quilibre de l'arbre.
	*
	*\pre		Il y a suffisament de m�moire.
	*
	*\post		Le mot est ajout� au dictionnaire des synonymes.
	*
	*\exception	bad_alloc si il n'y a pas suffisament de m�moire.
	*\exception	logic_error si le radical existe d�j�.
	*/
	void ajouterRadical(const std::string& motRadical);

	/*
	*\brief		Ajouter une flexion (motFlexion) d'un radical (motRadical) � sa liste de flexions.
	*
	*\pre		Il y a suffisament de m�moire.
	*
	*\post		La flexion est ajout�e au dictionnaire des synonymes.
	*
	*\exception	bad_alloc si il n'y a pas suffisament de m�moire.
	*\exception	logic_error si motFlexion existe d�j� ou motRadical n'existe pas.
	*/
	void ajouterFlexion(const std::string& motRadical, const std::string& motFlexion);

	/*
	*\brief		Ajouter un synonyme (motSynonyme) d'un radical (motRadical) � un de ses groupes de synonymes.
	*
	*\pre		Le radical se trouve d�j� dans le dictionnaire
	*\			Il y a suffisament de m�moire 
	*
	*\post		Le synonyme est ajout� au dictionnaire des synonymes
	*\			Si *numGroupe vaut �1, le synonyme est ajout� dans un nouveau groupe de synonymes 
	*\			et retourne le num�ro de ce nouveau groupe dans *numgroupe.
	*
	*\exception	bad_alloc si il n'y a pas suffisament de m�moire
	*\exception	logic_error si motSynonyme est d�j� dans la liste des synonymes du motRadical 
	*\exception	logic_error si numGroupe n'est pas correct ou motRadical n'existe pas.
	*/
	void ajouterSynonyme(const std::string& motRadical, const std::string& motSynonyme, int *numGroupe);

	/*
	*\brief		Supprimer un radical du dictionnaire des synonymes tout en s�assurant de maintenir l'�quilibre de l'arbre.
	*
	*\pre		motRadical fait parti de l'arbre.
	*
	*\post		Si le radical appartient au dictionnaire, on l'enl�ve et on �quilibre.
	*\			Il faut lib�rer la liste des synonymes du radical en question ainsi que sa liste des flexions. 
	*\			Il faut aussi s�assurer d��liminer tout pointeur pointant sur le n�ud contenant le radical. 
	*
	*\exception	logic_error si l'arbre est vide ou motRadical n'existe pas.
	*/
	void supprimerRadical(const std::string& motRadical);

	/*
	*\brief		Supprimer une flexion (motFlexion) d'un radical (motRadical) de sa liste de flexions.
	*
	*\pre		motRadical et motFlexion font parti de l'arbre.
	*
	*\post		La flexion est enlev�e du dictionnaire des synonymes.
	*
	*\exception	logic_error si si l'arbre est vide ou motFlexion n'existe pas ou motRadical n'existe pas.
	*/
	void supprimerFlexion(const std::string& motRadical, const std::string& motFlexion);

	/*
	*\brief		Retirer motSynonyme faisant partie du num�ro de groupe *numGroupe du motRadical.
	*
	*\pre		motRadical et motSynonyme existent et motRadical a une appartenance au groupe numGroupe 
	*
	*\post		Le synonyme est enlev� du dictionnaire des synonymes.
	*
	*\exception	logic_error si motSynonyme ou motRadical ou numGroupe n'existent pas.
	*/
	void supprimerSynonyme(const std::string& motRadical, const std::string& motSynonyme, int *numGroupe);

	/*
	*\brief		V�rifier si le dictionnaire est vide
	*
	*\post		Le dictionnaire est inchang�e
	*
	*/
	bool estVide() const;

	/**
	* \brief Retourne le nombre de radicaux dans le dictionnaire
	*
	* \post Le dictionnaire reste inchang�.
	*
	*/
	int nombreRadicaux() const;

	//Vous pouvez ajoutez d'autres m�thodes publiques si vous sentez leur n�cessit�
	//De plus, vous devez compl�ter ce fichier DicoSynonymes.h par la sp�cification 
	//du reste des m�thodes demand�es, voir l'�nonc� de ce travail pratique




	/*
	 * \fn std::vector<std::string>  rechercherIntervalle(const std::string& mot1, std::string& mot2) const
	 *
	 * \param[in] les mots delimitant l'intervalle
	 *
	 * \param[out] l'intervalle voulu
	 *
	 */
	std::vector<std::string>  rechercherIntervalle(const std::string& mot1, std::string& mot2) const;

	/*
	 * \fn std::string rechercherRadical(const std::string& mot) const
	 *
	 * \param[in] le mot dont on recherche le radical
	 *
	 * \param[out] le radical recherche
	 *
	 */
	std::string rechercherRadical(const std::string& mot) const;

   /**
   *  \fn  void valider(std::ofstream & SortieFichier) const;
   *  \brief Cette méthode devra écrire (dans un fichier de type texte) tous les nœuds de l’arbre non vide niveau par
niveau
   *
   *
   *  \pre SortieFichier est valide.
   *
   *  \post DicoSynonymes est inchangé et l'ecriture a fonctionner.
   *
   */
	void valider(std::ofstream & SortieFichier) const;

	/**
	*  \fn friend std::ostream& operator <<(std::ostream& out, const DicoSynonymes& d)
   *  \brief Affiche le dictionnaire de synonymes.
   *  \brief "Friend" pour permettre d'utiliser les données privées pour faire son travail.
   *
   *  \pre DicoSynonymes est valide.
   *
   *  \post DicoSynonymes est inchangé.
   *
   */
friend std::ostream& operator <<(std::ostream& out, const DicoSynonymes& d)
{
   if (d.estVide() == 0)
      out << "Le dictionnaire est vide" << std::endl;
   else{
       NoeudDicoSynonymes * lePlusPetitRadical = d._min(d.racine); // place le pointeur du noeud le plus bas a gauche dans lePlusPetitRadical
       NoeudDicoSynonymes * courant = lePlusPetitRadical;
       int compteur=1;
       while (compteur <= d.nbRadicaux){// parcours de tous les radical
           out << std::endl << "Radical numero " << compteur << ": " << std::endl;
           out << courant->radical << std::endl;
           out << "Liste des Flexion : " ;

           for (std::list<std::string>::iterator it = courant->flexions.begin() ; it != courant->flexions.end(); ++it){ // parcours de tous les flexions
              out << *it << " "  ;
           }//fin for

           for (std::vector<int>::iterator intIt = courant->appSynonymes.begin() ; intIt != courant->appSynonymes.end(); ++intIt){ // on parcours tous les appSynonymes
              out << std::endl << "Liste des Synonymes le pour sens du groupe " << *intIt << ": ";

              for (std::list<NoeudDicoSynonymes*>::const_iterator nodeIt = d.groupesSynonymes[*intIt].begin() ; nodeIt != d.groupesSynonymes[*intIt].end(); ++nodeIt){ // parcours de tous les synonymes
                 out << (*nodeIt)->radical << " "  ;
              }//fin for  pour la list des synonyme

           } // fin for pour les sens des synonymes.
           if(courant == d._max(d.racine)){ // si notre courant = _max alors apres l'avoir print on sors du do while
              break;
           }
           else{ // sinon on continue de changer le courant pour son successeur
           courant = d._successeur(d.racine,courant); // courant change pour le prochain radical.
           compteur++;
           }
     }// fin while   On reste dans la boucle tant que le compteur est plus petit ou égale au nbRadicaux
   }
   return out;
}

private:



	/**
	* \class NoeudDicoSynonymes
	*
	* \brief classe repr�sentant un noeud dans un dictionnaire (arbre AVL)
	*
	*/
	class NoeudDicoSynonymes
	{
		public:
			std::string radical;					// Un radical qui est un �l�ment fondamental d'un mot, auquel s'ajoutent suffixes et pr�fixes.
			std::list<std::string> flexions;		// Une liste cha�n�e de cha�ne de caract�res repr�sentant les flexions du radical.
			std::vector<int> appSynonymes;			// Un tableau contenant les indices (entiers) des groupes de synonymes auquel appartient le radical.
			int hauteur;							// La hauteur de ce noeud (afin de maintenir l'�quilibre de l'arbre AVL).
			NoeudDicoSynonymes *gauche, *droit;		// Les pointeurs sur les enfants du noeud.
			NoeudDicoSynonymes(const std::string& m): radical(m),hauteur(0),gauche(0),droit(0) { }
	};

   NoeudDicoSynonymes *racine;										// pointeur vers la racine de l'arbre des radicaux.
   int nbRadicaux;													// Nombre de noeuds dans l'arbre
   std::vector< std::list<NoeudDicoSynonymes*> > groupesSynonymes;	// Tableau de groupes de synonymes dont chaque �l�ment est une liste 
																	// de pointeurs sur des noeuds de l'arbre repr�sentant les radicaux.



   /**
    *  \fn const NoeudDicoSynonymes & _min(NoeudDicoSynonymes*)const
    *  \brief Retourner la valeur minimum dans un sous-arbre
    *
    * Fonction auxiliaire (r�cursive)
    *
    * \pre Le sous-arbre n'est pas vide
    * \post Le sous-arbre est inchang�
    * \exception logic_error si le sous-arbre est vide
    */
   NoeudDicoSynonymes* _min(NoeudDicoSynonymes*) const ;

   /**
    *  \fn NoeudDicoSynonymes & _max(NoeudDicoSynonymes*)const;
    *  \brief Retourner la valeur maximum dans un sous-arbre
    *
    * Fonction auxiliaire (r�cursive)
    *
    * \pre Le sous-arbre n'est pas vide
    * \post Le sous-arbre est inchang�
    * \exception logic_error si le sous-arbre est vide
    */
   NoeudDicoSynonymes* _max(NoeudDicoSynonymes*) const ;


   /**
    *  \fn const NoeudDicoSynonymes* _parent(NoeudDicoSynonymes* arb, NoeudDicoSynonymes* sArb)
    *  \brief Retourner le parent d'un �l�ment dans sous-arbre
    *
    * Fonction auxiliaire (r�cursive)
    *
    * \pre Le sous-arbre n'est pas vide
    * \pre L'�l�ment fait partie du sous-arbre
    * \post L'arbre est inchang�
    * \exception logic_error si le sous-arbre est vide
    * \exception logic_error si l'�l�ment n'est pas dans le sous-arbre
    */
   NoeudDicoSynonymes* _parent(NoeudDicoSynonymes* arb, NoeudDicoSynonymes* sArb) const ;

   /**
    *  \fn const NoeudDicoSynonymes* _successeur(NoeudDicoSynonymes*)
    *  \brief Retourner le successeur d'un �l�ment dans un sous-arbre
    *
    *  Fonction auxiliaire (r�cursive)
    *
    * \pre Le sous-arbre n'est pas vide
    * \post Le sous-arbre est inchang�
    */
   NoeudDicoSynonymes* _successeur(NoeudDicoSynonymes*,NoeudDicoSynonymes*) const ;

   /*
    * \fn float _similitude(const std::string& mot1, const std::string& mot2) const
    *
    * \param[in] mot1 le premier mot a compare
    * \param[in] mot2 le deuxieme mot a compare
    *
    * return le pourcetage de similitude entre les deux mots
    *
    */
   float _similitude(const std::string& mot1, const std::string& mot2) const;


   /**
   	 *  \brief Détruire un sous-arbre
   	 *
   	 * \post Le sous-arbre est détruit
   	 */
   void _auxDetruire(NoeudDicoSynonymes* &n);

   /**
   	 *  \brief Retourne le noeud recherché
   	 *
   	 * \post Le noeud est retourné
   	 */
   NoeudDicoSynonymes* _auxElement(NoeudDicoSynonymes* el, const std::string r);

   /**
   	 *  \brief Insérer élément dans un sous-arbre
   	 *
   	 * Fonction auxiliaire (récursive). Insertion avec balancement
   	 *
   	 * \post Le sous-arbre contient un élément de plus
   	 */
   void _auxAjouterRadical(NoeudDicoSynonymes* arbre, const std::string& motRadical);

   /**
   	 *  \brief Enlever un élément dans un sous-arbre
   	 *
   	 * Fonction auxiliaire (récursive). Suppression avec balancement.
   	 *
   	 * \post Le sous-arbre contient un élément de moins
   	 */
   void _auxSupprimerRadical(NoeudDicoSynonymes* arbre, const std::string& motRadical);

   /**
   	 *  \brief Enlever un élément dans une liste
   	 *
   	 * \post La liste contient un élément de moins
   	 */
   void _auxSupprimerFlexion(NoeudDicoSynonymes* arbre, const std::string& motRadical, const std::string& motFlexion);

   /**
   	 *  \brief Enlever l'élément minimum dans un sous-arbre
   	 *
   	 * Fonction auxiliaire (récursive).
   	 *
   	 * \post Le sous-arbre contient un élément de moins
   	 */
   void _auxRetireMin(NoeudDicoSynonymes* arbre) const throw(std::logic_error);

   /**
   	 *  \brief Simple rotation - Déséquilibre gauche-gauche
   	 *
   	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
   	 */
   void _zigZigGauche(NoeudDicoSynonymes* &K2);

   /**
   	 *  \brief Simple rotation - Déséquilibre droite-droite
   	 *
   	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
   	 */
   void _zigZigDroit(NoeudDicoSynonymes* &K2);

   /**
   	 *  \brief Double rotation - Déséquilibre gauche-droite
   	 *
   	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
   	 */
   void _zigZagGauche(NoeudDicoSynonymes* &K3);

   /**
   	 *  \brief Double rotation - Déséquilibre droite-gauche
   	 *
   	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
   	 */
   void _zigZagDroit(NoeudDicoSynonymes* &K3);

   /**
   	 *  \brief Retourner le maximum entre deux entiers
   	 */
   int _maximum (int a, int b) const;

   /**
   	 *  \brief Retourner la hauteur d'un noeud
   	 */
   int _hauteur(NoeudDicoSynonymes* arbre) const;
};


}//Fin du namespace

#endif
