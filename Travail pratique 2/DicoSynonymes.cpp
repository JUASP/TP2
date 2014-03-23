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

	DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_auxElement(NoeudDicoSynonymes* el, const std::string r)
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
       * \fn DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_parent(NoeudDicoSynonymes* arb, NoeudDicoSynonymes* sArb)const
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
 * \fn DicoSynonymes::NoeudDicoSynonymes* DicoSynonymes::_successeur(NoeudDicoSynonymes* arb,NoeudDicoSynonymes* sArb)const
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
}//Fin du namespace
