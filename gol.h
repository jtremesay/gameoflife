#ifndef GOL_H
#define GOL_H

#include <stdbool.h>

struct world;

/**
 * Crée un nouveau monde.
 *
 * Si le monde ne peut être crée, NULL est retourné.
 * Si au moins une des dimensions ert nulle, NULL est retourné.
 *
 * @brief world_create
 * @param width Largeur du monde
 * @param height Hauteur du monde
 * @return un monde ou NULL
 */
struct world * world_create(unsigned int width, unsigned int height);

/**
 * Libère un monde
 *
 * @brief world_free
 * @param world Le monde à libérer
 */
void world_free(struct world * world);

/**
 * Retourne la largeur d'un monde
 *
 * @brief world_get_width
 * @param world Le monde dont on veut connaitre la largeur
 * @return La largeur du monde
 */
unsigned int world_get_width(const struct world * world);

/**
 * Retourne la hauteur d'un monde
 *
 * @brief world_get_height
 * @param world Le monde dont on veut connaitre la hauteur
 * @return La hauteur du monde
 */
unsigned int world_get_height(const struct world * world);

/**
 * Récupère l'état (vivant ou mort) d'une cellule dans le monde
 *
 * Les coordonnées doivent être dans les limites du monde.
 *
 * @brief world_cell_get_is_alive
 * @param world Le monde
 * @param x Abscisse de la cellule
 * @param y Ordonnée de la cellule
 * @return true si la cellule est vivante, false sinon
 */
bool world_cell_get_is_alive(const struct world * world, unsigned int x, unsigned int y);

/**
 * Défini l'état (vivant ou mort) d'une cellule dans le monde
 *
 * Les coordonnées doivent être dans les limites du monde.
 *
 * @brief world_cell_set_is_alive
 * @param world Le monde
 * @param x Abscisse de la cellule
 * @param y Ordonnée de la cellule
 * @param is_alive Le nouvelle état de la cellule (true si vivant, false sinon)
 */
void world_cell_set_is_alive(struct world * world, unsigned int x, unsigned int y, bool is_alive);

/**
 * Détermine le nouveau status d'une cellule
 *
 * @brief world_cell_is_alive
 * @param neighbors_count Nombre de voisins de la cellule
 * @param is_alive Le status actuel de la cellule (true si vivant, false sinon)
 * @return Le nouveau status de la cellule (true si vivant, false sinon)
 */
bool world_cell_is_alive(unsigned int neighbors_count, bool is_alive);

/**
 * Peuple le monde de manière aléatoire
 *
 * @brief world_populate
 * @param world Le monde à peupler
 * @param probability La probabilité qu'une cellule soit vivante (1 pour 100%, 0 pour 0%)
 */
void world_populate(struct world * world, float probability);

/**
 * Fait évoluer le monde d'une génération
 *
 * @brief world_update
 * @param world Le monde à faire évoluer
 */
void world_update(struct world * world);

/**
 * Imprime le monde sur la sortie standard
 *
 * @brief world_print
 * @param world Le monde à imprimer
 */
void world_print(const struct world * world);

/**
 * Calcul le nombre de voisins d'une cellule
 *
 * @brief world_neighbors_count
 * @param world Le monde
 * @param x Abscisse
 * @param y Ordonnée
 * @return Le nombre de voisins
 */
unsigned int world_neighbors_count(struct world * world, unsigned int x, unsigned int y);

#endif // GOL_H
