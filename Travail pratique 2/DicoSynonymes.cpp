/**
 * \file DicoSynonymes.cpp
 * \brief Le code des op�rateurs du DicoSynonymes.
 * \author ...
 * \version 0.1
 * \date ...
 *
 * Travail pratique num�ro 2
 *
 */

#include "DicoSynonymes.h"

//vous pouvez inclure d'autres librairies si c'est n�cessaire

namespace TP2
{

	/**
	 * \fn DicoSynonymes::DicoSynonymes()
	 */
	DicoSynonymes::DicoSynonymes()
	{
		racine = 0;
		nbRadicaux = 0;
	}

	/**
	 * \fn DicoSynonymes::DicoSynonymes(std::ifstream &fichier)
	 *
	 * \param[in] &fichier Une référence vers un fichier texte
	 */
	DicoSynonymes::DicoSynonymes(std::ifstream& fichier)
	{
		//incomplete

		if (!fichier.is_open())
		{
			racine = 0;
			nbRadicaux = 0;
		}
	}

	/**
	 * \fn DicoSynonymes::~DicoSynonymes()
	 */
	DicoSynonymes::~DicoSynonymes()
	{
		_auxDetruire(racine);
	}

	/*
	 * \fn DIcoSynonymes::ajouterRadical(const std::string& motRadical)
	 *
	 * \param[in] motRadical le radical à ajouter
	 */
	void DicoSynonymes::ajouterRadical(const std::string& motRadical)
	{
		_auxAjouterRadical(racine, motRadical);
	}

	/*
	 * \fn DicoSynonymes::_auxAjouterRadical(NoeudDicoSynonymes* arbre, const std::string& motRadical)
	 *
	 * \param[in] arbre le sous-arbre à traiter
	 * \param[in] motRadical le radical à ajouter au sous-arbre
	 */
	void DicoSynonymes::_auxAjouterRadical(NoeudDicoSynonymes* arbre, const std::string& motRadical)
	{
		if (arbre == 0)
		{
			arbre = new NoeudDicoSynonymes(motRadical);
			nbRadicaux++;
			return;
		}
		if (arbre->radical > motRadical)
		{
			_auxAjouterRadical(arbre->gauche, motRadical);
			if (arbre->gauche->hauteur - arbre->droit->hauteur == 2)
			{
				if (arbre->gauche->radical > motRadical) _zigZigGauche(arbre);
				else _zigZagGauche(arbre);
			}
			else
			{
				arbre->hauteur = 1 + ((arbre->gauche->hauteur <= arbre->droit->hauteur) ? arbre->droit->hauteur : arbre->gauche->hauteur);
			}
		}
		else
		{
			_auxAjouterRadical(arbre->droit, motRadical);
			if (arbre->droit->hauteur - arbre->gauche->hauteur == 2)
			{
				if (arbre->droit->radical <= motRadical) _zigZigDroit(arbre);
				else _zigZagDroit(arbre);
			}
			else
			{
				arbre->hauteur = 1 + ((arbre->droit->hauteur <= arbre->gauche->hauteur) ? arbre->gauche->hauteur : arbre->droit->hauteur);
			}
		}
	}

	/*
	 * \fn void DicoSynonymes::ajouterFlexion(const std::string& motRadical, const std::string& motFlexion)
	 *
	 * \param[in] motRadical le radical auquel on ajoute une flexion
	 * \param[in] motFlexion la flexion à ajouter
	 */
	void DicoSynonymes::ajouterFlexion(const std::string& motRadical, const std::string& motFlexion)
	{
		DicoSynonymes::NoeudDicoSynonymes* trouve = 0;
		trouve = DicoSynonymes::_auxElement(racine, motRadical);
		trouve->flexions.push_back(motFlexion);
	}

	/*
	 * \fn void DicoSynonymes::supprimerRadical(const std::string& motRadical)
	 *
	 * \param[in] motRadical le radical à supprimer
	 */
	void DicoSynonymes::supprimerRadical(const std::string& motRadical)
	{
		_auxSupprimerRadical(racine, motRadical);
	}

	/*
	 * \fn void DicoSynonymes::_auxSupprimerRadical(NoeudDicoSynonymes *arbre, const std::string& motRadical)
	 *
	 * \param[in] arbre le sous-arbre à traiter
	 * \param[in] motRadical le radical à supprimer
	 */
	void DicoSynonymes::_auxSupprimerRadical(NoeudDicoSynonymes *arbre, const std::string& motRadical)
	{
		if (arbre->radical > motRadical)
		{
			_auxSupprimerRadical(arbre->gauche, motRadical);
		}
		else if (arbre->radical < motRadical)
		{
			_auxSupprimerRadical(arbre->droit, motRadical);
		}

		else if(arbre->gauche != 0 && arbre->droit != 0)
		{
			NoeudDicoSynonymes* temp = arbre->droit;
			while (temp->gauche != 0) temp = temp->gauche;
			arbre->radical = temp->radical;
			_auxRetireMin(arbre->droit);

		}
		else
		{
			NoeudDicoSynonymes* vieuxNoeud = arbre;
			arbre = (arbre->gauche != 0) ? arbre->gauche : arbre->droit;
			delete vieuxNoeud;
			nbRadicaux--;
			if (arbre->droit->hauteur - arbre->gauche->hauteur == 2)
			{
				if (arbre->droit->radical <= motRadical) _zigZigDroit(arbre);
				else _zigZagDroit(arbre);
			}
			else
			{
				arbre->hauteur = 1 + (arbre->droit->hauteur <= arbre->gauche->hauteur ? arbre->gauche->hauteur : arbre->droit->hauteur);
			}
		}
	}

	/*
	 * \fn void DicoSynonymes::supprimerFlexion(const std::string& motRadical, const std::string& motFlexion)
	 *
	 * \param[in] motRadical le radical à traiter
	 * \param[in] motFlexion la flexion à supprimer
	 */
	void DicoSynonymes::supprimerFlexion(const std::string& motRadical, const std::string& motFlexion)
	{
		_auxSupprimerFlexion(racine, motRadical, motFlexion);
	}

	/*
	 * \fn void DicoSynonymes::_auxSupprimerFlexion(NoeudDicoSynonymes* arbre, const std::string& motRadical, const std::string& motFlexion)
	 *
	 * \param[in] arbre le sous arbre à traiter
	 * \param[in] motRadical le radical à traiter
	 * \param[in] motFlexion la flexion à supprimer
	 */
	void DicoSynonymes::_auxSupprimerFlexion(NoeudDicoSynonymes* arbre, const std::string& motRadical, const std::string& motFlexion)
	{
		if (arbre->radical == motRadical)
		{
			arbre->flexions.remove(motFlexion);
		}
		else if(arbre->radical > motRadical) _auxSupprimerFlexion(arbre->gauche, motRadical, motFlexion);
		else _auxSupprimerFlexion(arbre->droit, motRadical, motFlexion);
	}

	/*
	 * \fn int DicoSynonymes::nombreRadicaux() const
	 */
	int DicoSynonymes::nombreRadicaux() const
	{
		return nbRadicaux;
	}

	/*
	 * \fn bool DicoSynonymes::estVide() const
	 */
	bool DicoSynonymes::estVide() const
	{
		return nbRadicaux == 0;
	}

	/*
	 * \fn void DicoSynonymes::_auxRetireMin(NoeudDicoSynonymes* arbre) const throw(std::logic_error)
	 *
	 * \param[in] arbre le sous-arbre à traiter
	 */
	void DicoSynonymes::_auxRetireMin(NoeudDicoSynonymes* arbre) const throw(std::logic_error)
	{
		if (arbre == 0) throw std::logic_error("_auxRetireMin: probleme pointeur NULL");
		else if (arbre->gauche != 0) _auxRetireMin(arbre->gauche);
		else
		{
			NoeudDicoSynonymes* temp = arbre;
			arbre = arbre->droit;
			delete temp;
		}
	}

	/**
	 * \fn DicoSynonymes::_auxDetruire(NoeudDicoSynonymes* &n)
	 *
	 * \param[in] n Le noeud à détruire
	 */
	void DicoSynonymes::_auxDetruire(NoeudDicoSynonymes* &n)
	{
		if (n != 0)
		{
			_auxDetruire(n->gauche);
			_auxDetruire(n->droit);
			delete n;
			nbRadicaux--;
			n = 0;
		}
	}

	DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_auxElement(NoeudDicoSynonymes* el, const std::string r) const
	{

		/*if (el == 0)
		{
			throw std::logic_error("le radical n'est pas présent dans le dictionnaire");
			return 0;
		}
		if (el->radical == r)
		{
			return el;
		}
		else
		{
			//rec
		}*/

		NoeudDicoSynonymes* courant = racine;

		while (courant->radical != r)
		{
			if (courant->radical < r && courant->gauche != 0)
			{
				courant = courant->gauche;
			}
			else if (courant->radical > r && courant->droit != 0)
			{
				courant = courant->droit;
			}
			else return 0;
		}

		return courant;
	}

	/*
	 * \fn int DicoSynonymes::_hauteur(NoeudDicoSynonymes* arbre) const
	 *
	 * \param[in] arbre le sous-arbre à traiter
	 */
	int DicoSynonymes::_hauteur(NoeudDicoSynonymes* arbre) const
	{
		if (arbre == 0) return -1;
		return arbre->hauteur;
	}

	/*
	 * \fn int DicoSynonymes::_maximum(int a, int b) const
	 *
	 * \param[in] a un entier à comparer
	 * \param[in] b un entier à comparer
	 */
	int DicoSynonymes::_maximum(int a, int b) const
	{
		if (a <= b) return b;
		return a;
	}

	/*
	 * \fn void DicoSynonymes::_zigZigGauche(NoeudDicoSynonymes* &K2)
	 *
	 * \param[in] K2 le noeud critique
	 */
	void DicoSynonymes::_zigZigGauche(NoeudDicoSynonymes* &K2)
	{
		NoeudDicoSynonymes *K1;

		K1 = K2->gauche;
		K2->gauche = K1->droit;
		K1->gauche = K2;
		K2->hauteur = 1 + _maximum(_hauteur(K2->gauche), _hauteur(K2->droit));
		K1->hauteur = 1 + _maximum(_hauteur(K1->gauche), K2->hauteur);

		K2 = K1;
	}

	/*
	 * \fn void DicoSynonymes::_zigZigDroit(NoeudDicoSynonymes* &K2)
	 *
	 * \param[in] K2 le sous-noeud critique
	 */
	void DicoSynonymes::_zigZigDroit(NoeudDicoSynonymes* &K2)
	{
		NoeudDicoSynonymes *K1;

		K1 = K2->droit;
		K2->droit = K1->gauche;
		K1->gauche = K2;
		K2->hauteur = 1 + _maximum(_hauteur(K2->droit), _hauteur(K2->gauche));
		K1->hauteur = 1 + _maximum(_hauteur(K1->droit), K2->hauteur);
		K2 = K1;
	}

	/*
	 * \fn void DicoSynonymes::_zigZagGauche(NoeudDicoSynonymes* &K3)
	 *
	 * \param[in] K3 le sous-noeud critique
	 */
	void DicoSynonymes::_zigZagGauche(NoeudDicoSynonymes* &K3)
	{
		_zigZigDroit(K3->gauche);
		_zigZigGauche(K3);
	}

	/*
	 * \fn void DicoSynonymes::_zigZagDroit(NoeudDicoSynonymes* &K3)
	 *
	 * \param[in] K3 le sous-noeud critique
	 */
	void DicoSynonymes::_zigZagDroit(NoeudDicoSynonymes* &K3)
	{
		_zigZigGauche(K3->droit);
		_zigZigDroit(K3);
	}

   /**
    * \fn DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_min(NoeudDicoSynonymes*racine) const
    *
    * \param[in] racine L'adresse du noeud racine du sous-arbre en entr�e
    * \exception si la racine est vide on lance un logic error
    * \return le noeudDicoSynonymes le plus a gauche.
    */
DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_min(NoeudDicoSynonymes*racine) const
{
   if (racine==0)
      throw std::logic_error("min: l'arbre (sous-arbre) est vide!\n");

   if (racine->gauche == 0)
   {
      return racine;// on retourne le noeud
   }

   return _min(racine->gauche);
}// fin _min





   /**
    * \fn DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_max(NoeudDicoSynonymes*racine) const
    *
    * \param[in] racine L'adresse du noeud racine du sous-arbre en entr�e
    * \return le noeudDicoSynonymes le plus a droit.
    */
DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_max(NoeudDicoSynonymes*racine) const
{
   if (racine==0)
      throw std::logic_error("max: l'arbre (sous-arbre) est vide!\n");

   if (racine->droit == 0)
   {
      return racine;// on retourne le noeud
   }

   return _max(racine->droit); // deplacement vers la droite dans l'Arbre
}// fin _max






/**
       * \fn DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_parent(NoeudDicoSynonymes* arb, NoeudDicoSynonymes* sArb) const
       *
       * \param[in] arb L'adresse du sous-arbre dans lequel on effectue la recherche du parent
       * \param[in] sArb L'adresse du noeud dont on cherche son parent
       *
       * \return L'adresse du noeud parent
 */
DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_parent(NoeudDicoSynonymes* arb, NoeudDicoSynonymes* sArb) const
{
   if (arb == 0)
      throw std::logic_error("parent: l'arbre est vide!\n");

   if (sArb == 0)
      throw std::logic_error("parent: l'element dont on cherche son parent n'existe pas!\n");

   if (sArb == arb)
      throw std::logic_error("parent: Le parent de la racine d'existe pas!\n");

   if ( sArb->radical < arb-> radical ) // si radical est plus petit que la racine
   {
      if (arb->gauche == sArb)
      {
         return arb; // on a trouver le parent
      }else
      {
         return _parent(arb->gauche, sArb);// sinon on se déplace vers la gauche
      }
   }else // si radical plus grand que celui de la racine
   {
      if (arb->droit == sArb) // si le sous arbre droit = notre sous arbre en param
      {
         return arb; // on a trouver le parent
      }else
      {
         return _parent(arb->droit, sArb); // sinon on se déplace vers la droite
      }
   }
}// fin _parent





/**
 * \fn DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_successeur(NoeudDicoSynonymes* arb,NoeudDicoSynonymes* sArb) const
 *
 * \param[in] arb Le sous-arbre dans lequel on cherche le successeur
 * \param[in] info La donn�e dont on cherche son successeur
 * \exception envois un logic_error si une exception survient
 *
 * \return E- Le successeur de info
 */
DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_successeur(NoeudDicoSynonymes* arb,NoeudDicoSynonymes* sArb) const
{
   if (arb == 0)
      throw std::logic_error("successeur: l'arbre est vide!\n");

   if (sArb == 0)
      throw std::logic_error("successeur: l'element dont on cherche son successeur n'existe pas!\n");

   if ( sArb->radical == _max(arb)->radical)
      throw std::logic_error("successeur: l'element est le max dans l'arbre, il n'a pas de successeur!\n");

   if (sArb->droit != 0)
   {
      return _min(sArb->droit); // si l'arbre contient un sous arbre droit alors son successeur sera la plus petite valeur dans cette branche la
   }
   else
   {
      NoeudDicoSynonymes* pere = _parent(arb, sArb);
      while (pere->radical < sArb->radical )
      {
         pere = _parent(arb,pere);
      }

      return pere;
   }
}// fin _successeur




/*
* \fn void DicoSynonymes::ajouterSynonyme(const std::string& motRadical, const std::string& motSynonyme, int *numGroupe)
*\brief     Ajouter un synonyme (motSynonyme) d'un radical (motRadical) � un de ses groupes de synonymes.
*
*\pre    Le radical se trouve d�j� dans le dictionnaire
*\       Il y a suffisament de m�moire
*
*\post      Le synonyme est ajout� au dictionnaire des synonymes
*\       Si *numGroupe vaut �1, le synonyme est ajout� dans un nouveau groupe de synonymes
*\       et retourne le num�ro de ce nouveau groupe dans *numgroupe.
*
*\exception bad_alloc si il n'y a pas suffisament de m�moire
*\exception logic_error si motSynonyme est d�j� dans la liste des synonymes du motRadical
*\exception logic_error si numGroupe n'est pas correct ou motRadical n'existe pas.
*/
void DicoSynonymes::ajouterSynonyme(const std::string& motRadical, const std::string& motSynonyme, int *numGroupe){

   // Gestion des exceptions
   NoeudDicoSynonymes* radMotRadical = _auxElement(racine,motRadical);
   if (radMotRadical == 0){// si on retourne rien ca veux dire que le radical n'existe pas
      throw std::logic_error("ajouterSynonyme : Le radical " + motRadical + " est inexistant.");
   }

   if ((unsigned int)(*numGroupe) >= groupesSynonymes.size()){ // si l'indice de *numGroupe est trop grand, on lance un logic_error
      throw std::logic_error("ajouterSynonyme : Le numéro de groupe est invalide.");
   }




   // Gestion des différents cas
   if (*numGroupe == -1){ //Si *numGroupe vaut -1, le synonyme est ajoute dans un nouveau groupe de synonymes
      NoeudDicoSynonymes* radSynonyme = _auxElement(racine,motSynonyme); // on chercher le radical du synonyme
      if (radSynonyme == 0){ // on vérifie si le synonyme existe deja
         ajouterRadical(motSynonyme); // on ajoute le synonyme
      } // fin if
      std::list<NoeudDicoSynonymes*> nouvelleListe; // creation d'une nouvelle liste, pour l'indice -1 qui sera changer plus loin
      nouvelleListe.push_back(radMotRadical); // ajoute radMotRadical au nouveau groupe.
      nouvelleListe.push_back(radSynonyme);  // ajoute le radSynonyme au nouveau groupe.

      groupesSynonymes.push_back(nouvelleListe); // ajoute la nouvelle liste au groupe de synonymes

      // Ensuite ont met a jour les indices des elements de la liste pour les faire correspondre au bon indice du groupe de synonyme.
      *numGroupe = (groupesSynonymes.size() -1); // mise a jour de *numGroupe pour qu'il prenne la valeur de la taille de groupesSynonymes -1.
      radMotRadical->appSynonymes.push_back(*numGroupe);  // ajoute l'indice du nouveau groupe au radical. l'indice est a groupesSynonymes.size() -1
      radSynonyme->appSynonymes.push_back(*numGroupe);   // ajoute l'index du nouveau groupe au radical du synonyme. l'indice est a groupesSynonymes.size()
   }// fin if pour la condition ou numGroupe == -1
   // si l'indice n'est pas -1
   else{

     // On prouve la derniere exception
      bool trouver = false;
      for (std::list<NoeudDicoSynonymes*>::const_iterator nodeIt = groupesSynonymes[*numGroupe].begin() ; nodeIt != groupesSynonymes[*numGroupe].end(); ++nodeIt){ // parcours de tous les synonymes
         if((*nodeIt)->radical == motSynonyme ){//motSynonyme est deja dans la liste des synonymes du motRadical
            trouver = true;
            break; // on sort du for
         }
      }//fin for  pour la list des synonyme
      if (trouver == true){
         throw std::logic_error("ajouterSynonyme : motSynonyme est deja dans la liste des synonymes du motRadical");
      }// fin if exception

      //on peut maintenant faire l'ajout
      ajouterRadical(motSynonyme); // le synonyme s'ajoute aux radical de l'arbre.
      NoeudDicoSynonymes* nouveauSynonyme = _auxElement(racine,motSynonyme); //on donne le pointeur du nouveau Radical
      nouveauSynonyme->appSynonymes.push_back(*numGroupe); // on met a jour l'indice du groupe

      groupesSynonymes[*numGroupe].push_back(nouveauSynonyme); // puis on ajoute le nouveauSynonyme au groupe de l'indice *numGroupe
   }// fin else
}// fin ajouterSynonyme




/*
 *\fn void DicoSynonymes::supprimerSynonyme(const std::string& motRadical, const std::string& motSynonyme, int *numGroupe)
*\brief     Retirer motSynonyme faisant partie du num�ro de groupe *numGroupe du motRadical.
*
*\pre    motRadical et motSynonyme existent et motRadical a une appartenance au groupe numGroupe
*
*\post      Le synonyme est enlev� du dictionnaire des synonymes.
*
*\exception logic_error si motSynonyme ou motRadical ou numGroupe n'existent pas.
*/
void DicoSynonymes::supprimerSynonyme(const std::string& motRadical, const std::string& motSynonyme, int *numGroupe){
   // Gestion des exceptions
   NoeudDicoSynonymes* radMotRadical = _auxElement(racine,motRadical);
   NoeudDicoSynonymes* radSynonyme = _auxElement(racine, motSynonyme);
   if (radMotRadical == 0){// si on retourne rien ca veux dire que le radical n'existe pas
      throw std::logic_error("ajouterSynonyme : Le radical " + motRadical + " est inexistant.");
   }

   if ((unsigned int)(*numGroupe) >= groupesSynonymes.size()){ // si l'indice de *numGroupe est trop grand, on lance un logic_error
      throw std::logic_error("ajouterSynonyme : Le numéro de groupe est invalide.");
   }
   if (radSynonyme == 0){   // on valide l'existance du synonyme
      throw std::logic_error("supprimerSynonyme : Le synonyme est inexistant.");
   }

   groupesSynonymes[*numGroupe].remove(radSynonyme);
   //std::vector<int>::iterator it = find(radSynonyme->appSynonymes.begin(), radSynonyme->appSynonymes.end(), *numGroupe); // ne fonctionne pas -_- http://stackoverflow.com/questions/571394/how-to-find-an-item-in-a-stdvector
   for(std::vector<int>::iterator it = radSynonyme->appSynonymes.begin(); it <=radSynonyme->appSynonymes.end(); it++){ // parcours le vector
      if(*it == *numGroupe){ // une fois que nous avons une correspondance entre l'iterator et *numGroupe
         radSynonyme->appSynonymes.erase(it);// on retire la valeur
         break;// on sort de la boucle
      }//fin if
   }// fin for
}// fin supprimerSynonyme



/**
*  \fn  void DicoSynonymes::valider(std::ofstream & SortieFichier) const
*  \brief Cette méthode devra écrire (dans un fichier de type texte) tous les nœuds de l’arbre non vide niveau par niveau
*  \pre SortieFichier est valide.
*
*  \post DicoSynonymes est inchangé et l'ecriture a fonctionner.
*
*/
void DicoSynonymes::valider(std::ofstream & SortieFichier) const{
   if(SortieFichier){

      std::queue<NoeudDicoSynonymes*> fileNode;
      NoeudDicoSynonymes * temp;
      NoeudDicoSynonymes * courant;
      fileNode.push(racine);
      std::string hierarchie = "1";
      std::string hierarchieGauche = ".1";
      std::string hierarchieDroite = ".2";

      while (!fileNode.empty()){ // parcours la file tant quelle n'Est pas vide

          hierarchie = "1"; // on reset notre hierarchie a 1
          courant = racine; // notre noeud commence toujours sur racine
          temp= fileNode.front();// on met la valeur au debut de la file dans temp
          fileNode.pop(); // puis on retire ce dernier de la file

          if(temp->gauche!=0){ // si l'arbre n'est pas vide a gauche on ajoute a la file le sous-arbre gauche

             fileNode.push(temp->gauche);

          }
          if(temp->droit!=0){// si l'arbre n'est pas vide a gauche on ajoute a la file le sous-arbre droite

             fileNode.push(temp->droit);

          }

          SortieFichier << "Radical: " << temp->radical << " son balancement:  " <<  ( _hauteur(temp->gauche) - _hauteur(temp->droit) );




          if(temp == racine){

             SortieFichier<< " hierarchie :" << "1" << std::endl;

          }
          else {
             while(courant != temp){ // boucle pour la fabrication de la hierarchie.

                if(temp->radical < courant->radical){// si temp->radical < que courant alors on ajoute .1
                  hierarchie = hierarchie+hierarchieGauche;// incremente hierarchieImpair pour le cote gauche
                  courant = courant->gauche;// on change courant pour le sous-arbre gauche
                }
                else {// si temp->radical > que courant alors on ajoute .2
                    hierarchie = hierarchie+hierarchieDroite; // incremente hierarchiePair pour le cote droite
                    courant = courant->droit; // on change courant pour le sous-arbre droit
                }
             }// fin while pour le la fabrication de la hierarchie
             SortieFichier<< " hierarchie :" << hierarchie << std::endl;
          }// fin else. pour la condition temp==racine
     }// fin while pour la file

   }
   else{
         throw std::invalid_argument("sauvegarderSE:le fichier texte n'est pas correctement ouvert");
   }
} // fin valider




/*
 * \fn std::string rechercherRadical(const std::string& mot) const throw (std::logic_error)
 *
 * \param[in] le mot dont on recherche le radical
 *
 * \param[out] le radical recherche
 *
 */
std::string DicoSynonymes::rechercherRadical(const std::string& mot) const
{
   NoeudDicoSynonymes* courant = racine;
   std::string radicalPlusSemblable; //chaine de caractere representant le radical le plus semblable
   float tauxSimilarite = 0; //le plus haut taux de similitude

   while (courant->radical != mot)
   {
      if (courant->radical < mot && courant->gauche != 0) //on cherche le radical dans l'arbre de gauche
      {
         float tauxSimilariteCourant = _similitude(mot, courant->radical); //on regarde le taux de similitude entre le mot rechercher et le radical courant

         if(tauxSimilariteCourant > tauxSimilarite)  //si le taux de similitude du radical courant est plus grand que le plus haut precedent
         {                                           //alors on met a jour le taux de similarite et on remplace le radical par le nouveau plus semblable et on continue
            tauxSimilarite = tauxSimilariteCourant;
            radicalPlusSemblable = courant->radical;
         }
         courant = courant->gauche;
      }
      else if (courant->radical > mot && courant->droit != 0) //on cherche le radical dans l'arbre de droit
      {
         float tauxSimilariteCourant = _similitude(mot, courant->radical);

         if(tauxSimilariteCourant > tauxSimilarite)
         {
            tauxSimilarite = tauxSimilariteCourant;
            radicalPlusSemblable = courant->radical;
         }
         courant = courant->droit;
      }
      else throw std::logic_error("Le mot n'existe pas");
   }

   return radicalPlusSemblable; // on retourne le radical le plus semblable
}





/*
 * \fn std::vector<std::string> DicoSynonymes::rechercherIntervalle(const std::string& mot1, const std::string& mot2) const
 *
 * \param[in] les mots delimitant l'intervalle
 *
 * \param[out] l'intervalle voulu
 *
 */
std::vector<std::string>  DicoSynonymes::rechercherIntervalle(const std::string& mot1, std::string& mot2) const
{
   NoeudDicoSynonymes* courant;
   courant = _auxElement(racine, mot1);  //on fait la recherche du premier element
   std::vector<std::string> vectorRetour;

   while(courant->radical != mot2)
   {
      vectorRetour.push_back(courant->radical); //tant que l'on a pas atteind le mot final, on ajoute les mots intermediaires dans le vecteur de retour
      courant = _successeur(racine,courant);
   }

   return vectorRetour;
}





/*
 * \fn float _similitude(const std::string& mot1, const std::string& mot2) const
 *
 * \param[in] mot1 le premier mot a compare
 * \param[in] mot2 le deuxieme mot a compare
 *
 * return le pourcetage de similitude entre les deux mots
 *
 */
float DicoSynonymes::_similitude(const std::string& mot1, const std::string& mot2) const
{
   int list1Length, list2Length, commonItemLength; // les items contenants les longueurs des differentes chaines de caracteres

   std::string string_intersection; //chaine de caractere contenant l'intersection du radical et du mot

   std::set_intersection(mot1.begin(), mot1.end(), mot2.begin(), mot2.end(), std::back_inserter(string_intersection));

   list1Length = mot1.length();
   list2Length = mot2.length();
   commonItemLength = string_intersection.length();

   float similarity = 100 * (commonItemLength * 2) / (list1Length + list2Length); // on calcul le pourcentage de similarite entre les 2 mots

   return similarity;
}
}//Fin du namespace
